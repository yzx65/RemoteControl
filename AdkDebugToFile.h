/***********************************************************************************
 * Module:												(BuildNum:0001-20111108)
 *       AdkDebugToFile.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Notes:
 *		���������������ļ���Ŀǰֻ֧���û�̬
 *
 *		Ĭ�ϵ�����ļ�ΪADK_DEBUG_FILE ������������ļ������ַ���
 *			1.��AdkPrecomp.h֮ǰ�������¶��弴��
 *				#define ADK_DEBUG_FILE	L"C:\\XXXX\\XXXX.txt"
 *
 *			2. AdkD2FTRACE�����ĵ�һ����������ָ��
 *				AdkD2FTRACEW((L"C:\1.log", L"[1] XXXX:%d\r\n", GetLastError()));		д�뵽1.log��
 *
 * Example:
 *
 *		AdkD2FTRACEA/AdkD2FTRACEW�����������Ϣ���ļ�������ֱ��ʹ��W��β�ĺ���
 *
 *		ʾ����
 *			AdkD2FTRACEA((NULL, "[1] XXXX:%d\r\n", GetLastError()));			д�뵽ADK_DEBUG_FILEA��
 *			AdkD2FTRACEA(("C:\1.log", "[1] XXXX:%d\r\n", GetLastError()));		д�뵽1.log��
 *			AdkD2FTRACEW((NULL, L"[1] XXXX:%d\r\n", GetLastError()));			д�뵽ADK_DEBUG_FILEW��
 *			AdkD2FTRACEW((L"C:\1.log", L"[1] XXXX:%d\r\n", GetLastError()));	д�뵽1.log��
 *
 * Histroy:
 *      1. 2012.08.13 xieb
 *          ����AdkLogToFileW(A)���������ڼ�¼��־���÷���AdkD2FTRACEW��ͬ
 *          Ҫ��ÿ����ӵ���־��Ϣ����С��2000(IN TCHAR)
 *      2. 2013.10.09 xieb
 *          ��vsprintfϵ�к�������ΪStringCchϵ�к�����������ܳ��ֵ�ջ�������ǿ������ȶ���
 */


#ifndef __ADK_DEBUGTOFILE_H__
#define __ADK_DEBUGTOFILE_H__

#include "AdkFile.h"
#include "AdkKernel32.h"
#include "AdkString.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#ifndef ADK_DEBUG_FILE
#define ADK_DEBUG_FILE L"C:\\adkdebug.txt"
#endif // ADK_DEBUG_FILE

#ifndef ADK_DEBUG_SYNCNAME
#define ADK_DEBUG_SYNCNAME		L"{7C022BFA-2D1F-44ef-AB3B-608891A02BF4}"
#endif // ADK_DEBUG_SYNCNAME

#ifndef  __KERNEL__

/***************************************************************
 * _AdkD2FDebuggerTraceW
 *
 */
INLINE
void _AdkD2FDebuggerTraceW(PWCHAR lpwzLogFile, PWSTR lpwzFormat,...)
{
	WCHAR		wzMsg[ADK_DBG_TRACE_BUFLEN];
	SYSTEMTIME  time;
	HANDLE		hMutex;
	UCHAR		flag[2] = {0xff, 0xfe};
	HRESULT     hResult;

	hMutex = AdkCreateMutexW(NULL, FALSE, ADK_DEBUG_SYNCNAME);
	if (hMutex == NULL)
	{
		return;
	}

	// ����BUFFER
	//
	GetLocalTime(&time);
	StringCchPrintfW(wzMsg, sizeof(wzMsg)/sizeof(wzMsg[0]), L"%.2d:%.2d:%.2d %d ", time.wHour, time.wMinute, time.wSecond, GetCurrentProcessId());

	va_list args;
	va_start(args, lpwzFormat);
	hResult = StringCchVPrintfW(wzMsg+AdkWcsLen(wzMsg), sizeof(wzMsg)/sizeof(wzMsg[0]) - AdkWcsLen(wzMsg), lpwzFormat, args);			// ��ʱ��ճ���
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(args);

	// д�ļ�
	//
	if (WAIT_OBJECT_0 == WaitForSingleObject(hMutex, INFINITE))
	{

		if (lpwzLogFile == NULL)
		{
			lpwzLogFile = ADK_DEBUG_FILE;
		}

		if ( 0 == AdkGetFileSizeFromNameW(lpwzLogFile))
		{
			AdkFileAppendWriterW(lpwzLogFile, flag, 2);
		}

		AdkFileAppendWriterW(lpwzLogFile, wzMsg, AdkWcsLen(wzMsg) * sizeof(WCHAR));

		ReleaseMutex(hMutex);
	}

	CloseHandle(hMutex);

	return ;
}

/***************************************************************
 * _AdkD2FDebuggerTraceA
 *
 */
INLINE
void _AdkD2FDebuggerTraceA(PCHAR lpszLogFile, PSTR p_szFormat,...)
{	
	CHAR		szMsg[ADK_DBG_TRACE_BUFLEN];
	PWCHAR		lpwzLogFile = NULL;
	PWCHAR		lpwzMsg;
	HRESULT     hResult;

	// ������־
	//
	va_list marker;
	va_start(marker, p_szFormat);
	hResult = StringCchVPrintfA(szMsg, sizeof(szMsg)/sizeof(szMsg[0]), p_szFormat, marker);
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(marker);

	if ( lpszLogFile )
	{
		lpwzLogFile = AdkStrToWStr(lpszLogFile);
	}
	lpwzMsg = AdkStrToWStr(szMsg);
	if ( lpwzLogFile && lpwzMsg )
	{
		_AdkD2FDebuggerTraceW(lpwzLogFile, L"%s", lpwzMsg);
	}

	if (lpwzLogFile)
	{
		AdkFree(lpwzLogFile);
	}

	if (lpwzMsg)
	{
		AdkFree(lpwzMsg);
	}

	return ;
}

//----------------------------------------------------------------
// ��¼��־
//
#define AdkLogToFileA(_x_)	_AdkD2FDebuggerTraceA _x_
#define AdkLogToFileW(_x_)	_AdkD2FDebuggerTraceW _x_ 

//----------------------------------------------------------------
//	Debug Trace Function 
//

#ifdef _DEBUG

#define AdkD2FTRACEA(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_TRACE)) \
									_AdkD2FDebuggerTraceA _x_ ; \
							} while(FALSE);

#define AdkD2FTRACEW(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_TRACE)) \
									_AdkD2FDebuggerTraceW _x_ ; \
							}while(FALSE);

#define AdkD2FWARNINGA(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_WARNING)) \
									_AdkD2FDebuggerTraceA _x_ ; \
							} while(FALSE);

#define AdkD2FWARNINGW(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_WARNING)) \
									_AdkD2FDebuggerTraceW _x_ ; \
							}while(FALSE);

#define AdkD2FERRORA(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_ERROR)) {\
									_AdkD2FDebuggerTraceA("*******file:%s lineno:%d******\r\n",__FILE__,__LINE__);\
									_AdkD2FDebuggerTraceA _x_ ; \
								}\
							} while(FALSE);

#define AdkD2FERRORW(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_ERROR)) {\
									_AdkD2FDebuggerTraceA("*******file:%s lineno:%d******\r\n",__FILE__,__LINE__);\
									_AdkD2FDebuggerTraceW _x_ ; \
								}\
							}while(FALSE);

#define AdkD2FPANICA(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_PANIC)) {\
									_AdkD2FDebuggerTraceA("*******file:%s lineno:%d******\r\n",__FILE__,__LINE__);\
									_AdkD2FDebuggerTraceA _x_ ; \
									AdkASSERT(FALSE);	\
								}\
							} while(FALSE);

#define AdkD2FPANICW(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_PANIC)) {\
									_AdkD2FDebuggerTraceA("*******file:%s lineno:%d******\r\n",__FILE__,__LINE__);\
									_AdkD2FDebuggerTraceW _x_ ; \
									AdkASSERT(FALSE);	\
								}\
							} while(FALSE);

#else	// RELEASE

#define AdkD2FTRACEA(_x_)
#define AdkD2FTRACEW(_x_)
#define	AdkD2FWARNINGA(_x_)
#define AdkD2FWARNINGW(_x_)
#define AdkD2FERRORA(_x_)
#define AdkD2FERRORW(_x_)
#define AdkD2FPANICA(_x_)
#define AdkD2FPANICW(_x_)

#endif // !_DEBUG

//----------------------------------------------------------------
// Surport UNICODE And ANSI Compile Options
//
#ifdef UNICODE

#define AdkD2FTRACE			AdkD2FTRACEW
#define AdkD2FWARNING		AdkD2FWARNINGW
#define AdkD2FERROR			AdkD2FERRORW
#define AdkD2FPANIC			AdkD2FPANICW

#else

#define AdkD2FTRACE			AdkD2FTRACEA
#define AdkD2FWARNING		AdkD2FWARNINGA
#define AdkD2FERROR			AdkD2FERRORA
#define AdkD2FPANIC			AdkD2FPANICA

#endif // !UNICODE

//----------------------------------------------------------------
// For short using
//

#define xD2FTRACE			AdkD2FTRACE
#define xD2FTRACEA			AdkD2FTRACEA
#define xD2FTRACEW			AdkD2FTRACEW

#define xD2FWARNING			AdkD2FWARNING
#define xD2FWARNINGA		AdkD2FWARNINGA
#define xD2FWARNINGW		AdkD2FWARNINGW

#define xD2FERROR			AdkD2FERROR
#define xD2FERRORA			AdkD2FERRORA
#define xD2FERRORW			AdkD2FERRORW

#define xD2FPANIC			AdkD2FPANIC
#define xD2FPANICA			AdkD2FPANICA
#define xD2FPANICW			AdkD2FPANICW

#endif // ! __KERNEL__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ADK_DEBUGTOFILE_H__

/*
 *      2. Second Version (0002-20120813)
 *         ����AdkLogToFileW(A)���������ڼ�¼��־
 *
 *		1. First Version (0001-20111108)
 *
 *****************************************************************************/