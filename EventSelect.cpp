//---------------------------------------------------------------------------

#include "AdkPrecomp.h"
#include "maindlg.h"
#include "EventSelect.h"
#include "Connection.h"
#include "ControlConnection.h"
#include "TargetConnection.h"
//---------------------------------------------------------------------------
// 
//   Define maximum connections on every thread. It is a very 
// important parameter which will affect application's performanence
//
#define MAX_WAIT_EVENTS_EVERY_THREAD	32

//
// Define a THREAD_OBJ to support multi conn ( >64 ) for WSAEventSelect
//
// @@NOTE: events[0] is used as a notify, not for connection
//		  so corresponding connArray[0] is unused.
//

typedef struct _THREAD_OBJ
{
	_THREAD_OBJ			*pNext;

	WSAEVENT 			eventArray[MAX_WAIT_EVENTS_EVERY_THREAD];
	SOCKET				sockArray[MAX_WAIT_EVENTS_EVERY_THREAD];
    DWORD               targetIdArray[MAX_WAIT_EVENTS_EVERY_THREAD];
	Connection			*connArray[MAX_WAIT_EVENTS_EVERY_THREAD];

	int					eventCount;
	int					socketCount;

	CRITICAL_SECTION	critSection;

	bool				bCtrConnFlag;       // 区别是ControlConnection还是TargetConnection

} THREAD_OBJ,
*PTHREAD_OBJ;

CRITICAL_SECTION		g_csEventSelect	;				// 专用用于EventSelect.cpp中的线程资源同步
PTHREAD_OBJ				g_pThreadListHeader = NULL;		// 线程列表

//---------------------------------------------------------------------------
PTHREAD_OBJ NewThreadObj(bool bCtrConnFlag)
{
	PTHREAD_OBJ pThread = (PTHREAD_OBJ)GlobalAlloc(GPTR, sizeof(THREAD_OBJ));

	if (NULL != pThread)
	{
		InitializeCriticalSection(&pThread->critSection);

		// Event[0] is used to control event
		//
		pThread->eventArray[0] = ::WSACreateEvent();
		pThread->eventCount    = 1;
		pThread->bCtrConnFlag  = bCtrConnFlag;

		EnterCriticalSection(&g_csEventSelect);

		pThread->pNext	  = g_pThreadListHeader;
		g_pThreadListHeader = pThread;

		LeaveCriticalSection(&g_csEventSelect);
	}
#ifdef _DEBUG
	else
	{
		xTRACE((L"[EventSelect.cpp] GetThreadObj return NULL value, errorId is %d\r\n", GetLastError()));
	}
#endif // _DEBUG

	return pThread;
}

//---------------------------------------------------------------------------
void FreeThreadObj(PTHREAD_OBJ pThread)
{
	xASSERT((pThread->socketCount == 0));
	xASSERT((pThread->eventCount == 1));

	EnterCriticalSection(&g_csEventSelect);

	PTHREAD_OBJ pTh = g_pThreadListHeader;

	if (pTh == pThread)
	{
		g_pThreadListHeader = pThread->pNext;
	}
	else
	{
		while(pTh != NULL && pTh->pNext != pThread)
		{
			pTh = pTh->pNext;
		}

		if (NULL != pTh)
		{
			pTh->pNext	= pThread->pNext;
		}
	}

	LeaveCriticalSection(&g_csEventSelect);

	WSACloseEvent(pThread->eventArray[0]);
	DeleteCriticalSection(&pThread->critSection);
	GlobalFree(pThread);

	return;
}
//---------------------------------------------------------------------------
void CompressEventArray(PTHREAD_OBJ pThread)
{
	EnterCriticalSection(&pThread->critSection);
    
    int j = 1;
	for (int i = 1; i < MAX_WAIT_EVENTS_EVERY_THREAD ; i++)
	{
		if ((NULL == pThread->eventArray[i]) && (0 == pThread->sockArray[i]))
		{
			continue;
		}

		if (pThread->eventArray[i])
		{
			xASSERT((pThread->sockArray[i]));

			if (i == j)
			{
				j++;
				continue;
			}

			xASSERT((j < i));
		}

		if (j < i)
		{
			pThread->eventArray[j] = pThread->eventArray[i];
			pThread->connArray[j]  = pThread->connArray[i];
			pThread->sockArray[j]  = pThread->sockArray[i];
            pThread->targetIdArray[j] = pThread->targetIdArray[i];

			pThread->eventArray[i] = NULL;
			pThread->connArray[i]  = NULL;
			pThread->sockArray[i]  = 0;
            pThread->targetIdArray[i] = 0;

			j++;
		}
	}

	pThread->eventCount = j;

	LeaveCriticalSection(&pThread->critSection);

	return;
}
//---------------------------------------------------------------------------
bool InsertSockToThd(PTHREAD_OBJ pThread, SOCKET sock, bool bCtrConnFlag, DWORD dwTargetId)
{
	bool ret = false;

	if (bCtrConnFlag != pThread->bCtrConnFlag)
	{
		return ret;
	}

	EnterCriticalSection(&pThread->critSection);

	if (pThread->socketCount < MAX_WAIT_EVENTS_EVERY_THREAD - 1)
	{
		//
		// pThread->connArray[0] is unused
		//

		for (int i = 1; i < MAX_WAIT_EVENTS_EVERY_THREAD ; i++)
		{
			if (pThread->sockArray[i] == 0)
			{
				xASSERT((pThread->eventArray[i] == NULL));
				xASSERT((pThread->connArray[i] == NULL));

				WSAEVENT event = WSACreateEvent();
				WSAEventSelect(sock, event, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
				pThread->eventArray[i] = event;
				pThread->sockArray[i] = sock;
                pThread->targetIdArray[i] = dwTargetId;
				pThread->socketCount++;
				ret = true;
				break;
			}
		}
	}

	LeaveCriticalSection(&pThread->critSection);

	return ret;
}
//---------------------------------------------------------------------------
VOID RemoveSockFromThd(PTHREAD_OBJ pThread, int index)
{
	xASSERT((pThread->eventArray[index] ));
	xASSERT((pThread->sockArray[index] > 0));

	EnterCriticalSection(&pThread->critSection);

	WSACloseEvent(pThread->eventArray[index]);			// 关闭事件
	closesocket(pThread->sockArray[index]);				// 关闭SOCKET

	pThread->eventArray[index] = NULL;
	pThread->connArray[index] = NULL;
	pThread->sockArray[index] = 0;
    pThread->targetIdArray[index] = 0;
	pThread->socketCount--;

	LeaveCriticalSection(&pThread->critSection);
}
//---------------------------------------------------------------------------
unsigned int WINAPI ConnSelectThread(LPVOID lpParam)
{
	PTHREAD_OBJ	pThread = (PTHREAD_OBJ)lpParam;
	bool		bShuffle	;
	char		identity[32];
	int			nLen;

	while(TRUE)
	{
		int index = WSAWaitForMultipleEvents(pThread->eventCount, pThread->eventArray, FALSE, WSA_INFINITE, FALSE);
		if (WSA_WAIT_FAILED == index)
		{
			xPANIC((L"WSAWaitForMultipleEvents for __ConnSelectThread failed. error id:%d\r\n",WSAGetLastError()));
			continue;
		}

		//
		//    EventArray[0] in signaled state represents there may new connection from target
		// or connection closed.
		//	  So we need to rebuild EventArray of THREAD_OBJ
		//

		bShuffle = false;
		index = index - WSA_WAIT_EVENT_0;
		if (0 == index)
		{
			WSAResetEvent(pThread->eventArray[0]);
			bShuffle = TRUE;
		}
		else
		{
			bool bCloseConn = true;
			WSANETWORKEVENTS networkEvent;
			Connection *lpConn = pThread->connArray[index];

			memset(&networkEvent, 0, sizeof(networkEvent));

			do
			{
				if (0 != WSAEnumNetworkEvents(pThread->sockArray[index], pThread->eventArray[index], &networkEvent))
				{
                    // 如果主动关闭连接的话，可能会走到这里，错误码为WSAENOTSOCK
                    //
                    if (WSAGetLastError() != WSAENOTSOCK)
                    {
                        MessageBoxA(NULL, "网络出现异常错误", "提示", MB_OK | MB_ICONINFORMATION);
                    }
					break;
				}

				if (networkEvent.lNetworkEvents & FD_CLOSE)
				{
                    // 远端关闭连接
					break;
				}

                if (networkEvent.lNetworkEvents & FD_CONNECT)
                {
                    int iErrorCode = networkEvent.iErrorCode[FD_CONNECT_BIT];
					if (0 != iErrorCode)
					{
                        //if (pThread->bCtrConnFlag)
                        //{
                            SendMessage(FrmMain->Handle, WM_CONTROL_CONNFAILED, iErrorCode, NULL);
                        //}
						break;
					}
                                    
                    //
                    // 新建连接成功
                    //
                    if (lpConn == NULL)
                    {
                        if (pThread->bCtrConnFlag)
                        {
							lpConn = new TargetConnection(pThread->sockArray[index], pThread->targetIdArray[index]);
							((TargetConnection*)lpConn)->Send_IDE(FrmMain->aniPass.c_str());
							Sleep(15000);
							ConnectToServer(FrmMain->aniDaemonIpAddr.c_str(),FrmMain->nCtrPortForControl, false, FrmMain->targetID);
                        }
                        else
                        {
                            lpConn = new TargetConnection(pThread->sockArray[index], pThread->targetIdArray[index]);
							SendMessage(FrmMain->Handle, WM_CONTROL_CONNCOMPLETED, 0, 0);
                        }

                        pThread->connArray[index] = lpConn;
                        lpConn->ConnectionCompleted();      // 成功连接
                    }
                }

				if(networkEvent.lNetworkEvents & FD_READ)
				{
                    int iErrorCode = networkEvent.iErrorCode[FD_READ_BIT];
					if (0 != iErrorCode)
					{
						break;
                    }

					if (lpConn)
					{
						// 连接对象已经建立，则直接交给对应的连接进行处理
						//
						lpConn->DataArrivedOnSocket();
					}
				}

				bCloseConn = false;

			} while(FALSE);

			if (bCloseConn)
			{
				RemoveSockFromThd(pThread, index);

				if (lpConn)
				{
                    lpConn->ConnectionClosed();  // 连接关闭
					delete lpConn;
				}

				bShuffle = TRUE;
			}
		}

		// 重构数组
		//
		if (bShuffle)
		{
			CompressEventArray(pThread);

			if (1 == pThread->eventCount)
			{
				// Free thread which has no connection
				//
				FreeThreadObj(pThread);
				break;
			}
		}
	} 

	_endthreadex(0);

	return 0;
}

//---------------------------------------------------------------------------

bool  ConnectToServer(const char *ipAddr, USHORT port, bool bCtrConnFlag, DWORD dwTargetId)
{
    struct sockaddr_in sin;
	memset(&sin,0,sizeof(sin));
    sin.sin_family      = AF_INET;
    sin.sin_port        = htons((u_short)port);
    sin.sin_addr.s_addr = inet_addr(ipAddr);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == sock)
	{
        return false;
	}

    // 加到线程中，使用WSAEventSelect模型
    //
    DWORD dwThId;
    
	EnterCriticalSection(&g_csEventSelect);

	PTHREAD_OBJ pThread = g_pThreadListHeader;

	while(pThread)
	{
		if (InsertSockToThd(pThread, sock, bCtrConnFlag, dwTargetId))
		{
			break;
		}

		pThread = pThread->pNext;
	}

	//
	// Create a new thread for more connection
	//
	if (NULL == pThread)
	{
		pThread = NewThreadObj(bCtrConnFlag);

		if (pThread)
		{
			InsertSockToThd(pThread, sock, bCtrConnFlag, dwTargetId);

			_beginthreadex(NULL, 0, ConnSelectThread, pThread, 0, (unsigned int*)&dwThId);
		}
	}

	LeaveCriticalSection(&g_csEventSelect);

    // notify __ConnSelectThread to RebuildArray
	//
	WSASetEvent(pThread->eventArray[0]);

	// Start a nonblock connect
    //
    if (SOCKET_ERROR == connect(sock, (struct sockaddr *)&sin, sizeof sin))
    {
		int error = WSAGetLastError();
        if ( error!= WSAEWOULDBLOCK)
        {
            return false;               
		}
    }

    return true;
}
//---------------------------------------------------------------------------
bool  InitialEventSelect()
{
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2,2), &wsaData)) != NO_ERROR)
	{
        return false;
	}

    InitializeCriticalSection(&g_csEventSelect);

    return true;
}

