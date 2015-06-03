/***************************************************************************
 * Module:
 *      AdkLicense.h
 *
 * Author:
 *		XieBo(1557360050@qq.com)
 *
 * Time:
 *		2014-2,Nanjing
 *
 * Notes:
 *		�������ڿ�����ص�һЩ����
 *
 * Functions:
 *
 *      1. 2014-04
 *			1. ��ȡʱ�亯�����ṩ��ȡ����ʱ��ʹ������ȡ��ǰ���ڵĺ���
 *				AdkGetCurrentTime()             ��ȡϵͳ�ĵ�ǰʱ�䣬���ص���һ��DWORDֵ
 *              AdkGetTmFromDword()             ��һ��DWORDֵ�õ������յ���Ϣ�������һ��time.h�ж�������ݽṹstruct tm
 *				AdkGetTimeFromInternet          �ɻ�������ȡʱ����Ϣ�������һ��time.h�ж�������ݽṹstruct tm
 *              AdkGetTmFromFileTime            ��һ���ļ�ʱ�䣬�õ�struct tmʱ��
 *		
 *          2. License��غ���
 *              AdkVerifyLicense0()             ��һ��DWORDʱ����License��Ϣ�Ƚϣ���֤���Ƿ����
 *              AdkVerifyLicense1()             ��һ��struct tmʱ����License��Ϣ�Ƚϣ���֤���Ƿ����
 *              AdkGetLicenseInfo()             ��License�ļ���ȡLicense��Ϣ
 *              AdkGenericLicenseFile()         ����License�ļ�����AdkGetLicenseInfo��Ӧ
 *
 *             �÷����£�
 *              ��Ҫ��֤License�ĳ���ʹ��AdkGetLicenseInfo()��License�ļ��л�ȡLicense��Ϣ����ʹ�û�׼ʱ�����AdkVerifyLicense��֤�Ƿ����
 *                  ��ʽ�������������ѹ�����ʾ�û����������ѹ�������Ӱ�칦��ʹ��֮�������
 *                  ���ð�����ֹ�����ѹ�����ʾ�û��������ѽ�������ϵ����֧��֮�������
 *              ����ʱ����׼ʱ��Ļ�ȡ�����ַ�ʽ��
 *                  1.��Ŀ��������ȡʱ�䣬��Tϵ�У�Hϵ�жԷ�����ʱ��E6
 *                  2.�ӻ�������ȡʱ�䣬��E7��C4
 *
 *          3. ��������
 *              AdkGTMToBJ                      ��GMTʱ��ת��Ϊ����ʱ��
 *              AdkGetTmFromGMTStr              �� Fri, 21 Feb 2014 01:32:33 GMT �ַ������õ�struct tmʱ�䣬�����tm���ݽṹ�У�ֻ�����������ʱ������Ϣ
 *
 */

#ifndef __ADK_TUOJIE_LICENSE_H__
#define __ADK_TUOJIE_LICENSE_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#pragma warning(disable:4146)
#pragma warning(disable:4018)

#include "AdkPrecomp.h"
#include <time.h>
#include "AdkSocket.h"
#include "AdkFile.h"
#include "AdkRc4.h"


typedef struct _TUOJIE_LICENSE {

	DWORD    dwLicenseMagic;           // �ҹ�˾License��ʶ����

	DWORD    dwDataKey;                // ÿ���û������ݱ�ʶ�����û���ȡ������ʱ���ɲ��ô�ֵ��Ϊ������Կ�����߽����ô�ֵ����ʶ���ݣ�����ļ������ֵ�޹ء�

	WCHAR    wzGuid[64];               // ΨһIDֵ
	WCHAR    wzUser[64];               // �û�����

#define TUOJIE_LICENSE_DEMO      0     // ���ð�
#define TUOJIE_LICENSE_BUSINESS  1     // ��ʽ��

	DWORD    dwLicenseType;
	int      iLastYear;                // �������
	int      iLastMonth;               // �����·�
	int      iLastDay;                 // ������

#define DOG_NONE                 0
#define DOG_TYPE_GRAND           1
#define DOG_TYPE_FD              2

	DWORD    dwDogType;                // ���������
	CHAR     szDogName[64];            // ���������
	CHAR     szDogPass[64];            // �������Կ

	// ����H6��H2��֤Ӳ��
	//
	BOOL     bCheckDisk;               // �Ƿ����Ӳ��
	BYTE     byteMd5Hash[16];          // ����Ӳ�̵����кŲ�����HASHֵ��AdkMd5.h���ļ��е�ϵ�к���������

} TUOJIE_LICENSE, *LPTUOJIE_LICENSE;


#ifdef UNICODE

#define AdkGetLicenseInfo			AdkGetLicenseInfoW
#define AdkGenericLicenseFile       AdkGenericLicenseFileW

#else

#define AdkGetLicenseInfo			AdkGetLicenseInfoA
#define AdkGenericLicenseFile       AdkGenericLicenseFileW

#endif

VOID AdkGetTmFromDword(IN DWORD dwTime, OUT tm *lpTime);

/***************************************************************
 * AdkVerifyLicense0
 *
 * ����ֵ˵����
 *    0 ������
 *    1 ������Ч��֮��
 *    2 ���ѹ���Ч��
 *
 */
INLINE
DWORD AdkVerifyLicense0(IN CONST LPTUOJIE_LICENSE lpTjLicense, IN CONST DWORD dwTime)
{
	DWORD  dwRet = 0;
	struct tm tmTime;

	AdkGetTmFromDword(dwTime, &tmTime);

	do
	{
		// �ж���
		//
		if ( tmTime.tm_year < lpTjLicense->iLastYear )
		{
			dwRet = 1;
			break;
		}
		if ( tmTime.tm_year == lpTjLicense->iLastYear )
		{
			// �ж���
			//
			if ( tmTime.tm_mon < lpTjLicense->iLastMonth )
			{
				dwRet = 1;
				break;
			}
			if ( tmTime.tm_mon == lpTjLicense->iLastMonth )
			{
				// �ж���
				//
				if ( tmTime.tm_mday < lpTjLicense->iLastDay )
				{
					dwRet = 1;
					break;
				}
				dwRet = 2;
			}
			dwRet = 2;
		}

		dwRet = 2;

	} while (FALSE);

	return dwRet;
}

/***************************************************************
 * AdkVerifyLicense1
 *
 * ����ֵ˵����
 *    0 ������
 *    1 ������Ч��֮��
 *    2 ���ѹ���Ч��
 *
 */
INLINE
DWORD AdkVerifyLicense1(IN CONST LPTUOJIE_LICENSE lpTjLicense, IN CONST struct tm *lpTime)
{
	DWORD dwRet = 0;

	do
	{
		// �ж���
		//
		if ( lpTime->tm_year < lpTjLicense->iLastYear )
		{
			dwRet = 1;
			break;
		}
		if ( lpTime->tm_year == lpTjLicense->iLastYear )
		{
			// �ж���
			//
			if ( lpTime->tm_mon < lpTjLicense->iLastMonth )
			{
				dwRet = 1;
				break;
			}
			if ( lpTime->tm_mon == lpTjLicense->iLastMonth )
			{
				// �ж���
				//
				if ( lpTime->tm_mday < lpTjLicense->iLastDay )
				{
					dwRet = 1;
					break;
				}
				dwRet = 2;
			}
			dwRet = 2;
		}

		dwRet = 2;

	} while (FALSE);

	return dwRet;
}


/***************************************************************
 * AdkGetLicenseInfoW
 *
 * lpTjLicenseΪ�����߷���Ĳ�С��sizeof(TUOJIE_LICENSE)���ڴ�ռ䣬�ɶ������TUOJIE_LICENSE ttt����&tttΪ��������
 *
 */
INLINE
BOOL AdkGetLicenseInfoW(IN LPCWSTR lpwzLicenseFile, OUT CONST LPTUOJIE_LICENSE lpTjLicense)
{
	BOOL bRet = FALSE;

	CHAR           szBuf[2048];
	DWORD          dwFileSize;
	DWORD          dwRead;
	CHAR           szKey[16];

	if ( !lpTjLicense )
	{
		return FALSE;
	}

	szKey[7] = '\0';
	szKey[5] = 'w';

	AdkZeroMemory(lpTjLicense, sizeof(TUOJIE_LICENSE));

	szKey[2] = '9';
	do
	{
		// ��ȡLicense
		//
		dwFileSize = AdkGetFileSizeFromNameW(lpwzLicenseFile);
		szKey[3] = 'x';
		if ( dwFileSize < 1200 || dwFileSize > 2000)
		{
			break;
		}
		
		szKey[0] = 'g';
		szKey[6] = 'y';

		if ( !AdkFileReaderW(lpwzLicenseFile, dwFileSize, &dwRead, szBuf, 2048) )
		{
			break;
		}
		szKey[4] = 's';
		szKey[1] = 'n';

		AdkRc4Buffer((unsigned char*)szBuf, dwFileSize, (unsigned char*)szKey, lstrlenA(szKey));

		AdkCopyMemory(lpTjLicense, &szBuf[1024], sizeof(TUOJIE_LICENSE));

		if ( lpTjLicense->dwLicenseMagic != 19820702 )
		{
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGetLicenseInfoA
 *
 * lpTjLicenseΪ�����߷���Ĳ�С��sizeof(TUOJIE_LICENSE)���ڴ�ռ䣬�ɶ������TUOJIE_LICENSE ttt����&tttΪ��������
 *
 */
INLINE
BOOL AdkGetLicenseInfoA(IN LPCSTR lpszLicenseFile, OUT CONST LPTUOJIE_LICENSE lpTjLicense)
{
	BOOL bRet = FALSE;

	CHAR           szBuf[2048];
	DWORD          dwFileSize;
	DWORD          dwRead;
	CHAR           szKey[16];

	if ( !lpTjLicense )
	{
		return FALSE;
	}

	szKey[7] = '\0';
	szKey[5] = 'w';

	AdkZeroMemory(lpTjLicense, sizeof(TUOJIE_LICENSE));

	szKey[2] = '9';
	do
	{
		// ��ȡLicense
		//
		dwFileSize = AdkGetFileSizeFromNameA(lpszLicenseFile);
		szKey[3] = 'x';
		if ( dwFileSize < 1200 || dwFileSize > 2000)
		{
			break;
		}
		
		szKey[0] = 'g';
		szKey[6] = 'y';

		if ( !AdkFileReaderA(lpszLicenseFile, dwFileSize, &dwRead, szBuf, 2048) )
		{
			break;
		}
		szKey[4] = 's';
		szKey[1] = 'n';

		AdkRc4Buffer((unsigned char*)szBuf, dwFileSize, (unsigned char*)szKey, lstrlenA(szKey));

		AdkCopyMemory(lpTjLicense, &szBuf[1024], sizeof(TUOJIE_LICENSE));

		if ( lpTjLicense->dwLicenseMagic != 19820702 )
		{
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGenericLicenseFileW
 *
 * ����License�ļ�
 *
 */
INLINE
BOOL AdkGenericLicenseFileW(IN LPCWSTR lpwzBaseFile, IN LPCWSTR lpwzLicenseFile, IN CONST LPTUOJIE_LICENSE lpTjLicense)
{
	BOOL bRet = FALSE;

	TUOJIE_LICENSE tjLicenseInfo;
	CHAR           szBuf[2048];
	DWORD          dwFileSize;
	DWORD          dwRead;
	CHAR           szKey[16];

	AdkCopyMemory(&tjLicenseInfo, lpTjLicense, sizeof(TUOJIE_LICENSE));

	szKey[7] = '\0';
	szKey[1] = 'n';
	
	do
	{
		szKey[2] = '9';
		szKey[0] = 'g';

		// ����License
		//
		dwFileSize = AdkGetFileSizeFromNameW(lpwzBaseFile);
		if ( dwFileSize < 1200 || dwFileSize > 2000)
		{
			AdkMsgBoxW(L"0 - δ�ܷ��ʻ����ļ� with %u", GetLastError());
			break;
		}
		szKey[4] = 's';
		szKey[6] = 'y';
		if ( !AdkFileReaderW(lpwzBaseFile, dwFileSize, &dwRead, szBuf, 2048) )
		{
			AdkMsgBoxW(L"1 - δ�ܷ��ʻ����ļ� with %u", GetLastError());
			break;
		}
		szKey[5] = 'w';
		szKey[3] = 'x';

		AdkCopyMemory(&szBuf[1024], &tjLicenseInfo, sizeof(TUOJIE_LICENSE));

		AdkRc4Buffer((unsigned char*)szBuf, dwFileSize, (unsigned char*)szKey, lstrlenA(szKey));

		if ( !AdkFileWriterW(lpwzLicenseFile, szBuf, dwFileSize) )
		{
			AdkMsgBoxW(L"2 - Internal error with %u", GetLastError());
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGenericLicenseFileA
 *
 * ����License�ļ�
 *
 */
INLINE
BOOL AdkGenericLicenseFileA(IN LPCSTR lpszBaseFile, IN LPCSTR lpszLicenseFile, IN CONST LPTUOJIE_LICENSE lpTjLicense)
{
	BOOL bRet = FALSE;

	TUOJIE_LICENSE tjLicenseInfo;
	CHAR           szBuf[2048];
	DWORD          dwFileSize;
	DWORD          dwRead;
	CHAR           szKey[16];

	AdkCopyMemory(&tjLicenseInfo, lpTjLicense, sizeof(TUOJIE_LICENSE));

	szKey[7] = '\0';
	szKey[1] = 'n';
	
	do
	{
		szKey[2] = '9';
		szKey[0] = 'g';

		// ����License
		//
		dwFileSize = AdkGetFileSizeFromNameA(lpszBaseFile);
		if ( dwFileSize < 1200 || dwFileSize > 2000)
		{
			AdkMsgBoxW(L"0 - δ�ܷ��ʻ����ļ� with %u", GetLastError());
			break;
		}
		szKey[4] = 's';
		szKey[6] = 'y';
		if ( !AdkFileReaderA(lpszBaseFile, dwFileSize, &dwRead, szBuf, 2048) )
		{
			AdkMsgBoxW(L"1 - δ�ܷ��ʻ����ļ� with %u", GetLastError());
			break;
		}
		szKey[5] = 'w';
		szKey[3] = 'x';

		AdkCopyMemory(&szBuf[1024], &tjLicenseInfo, sizeof(TUOJIE_LICENSE));

		AdkRc4Buffer((unsigned char*)szBuf, dwFileSize, (unsigned char*)szKey, lstrlenA(szKey));

		if ( !AdkFileWriterA(lpszLicenseFile, szBuf, dwFileSize) )
		{
			AdkMsgBoxW(L"2 - Internal error with %u", GetLastError());
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}

/***************************************************************
 * AdkGTMtoBJ
 *
 * ��GMTʱ��ת��ΪBJʱ��
 * tmGTM�е�tm_mon��ȡֵ��ΧΪ 1 - 12
 *
 */
INLINE
VOID AdkGTMtoBJ(tm *tmGTM)
{
	tmGTM->tm_hour += 8;

	if ( tmGTM->tm_hour > 23 )
	{
		tmGTM->tm_mday += 1;
		tmGTM->tm_wday = (tmGTM->tm_wday + 1) % 7;
		tmGTM->tm_yday += 1;
		tmGTM->tm_hour -= 24;

		if ( tmGTM->tm_mon == 1
			|| tmGTM->tm_mon == 3
			|| tmGTM->tm_mon == 5 
			|| tmGTM->tm_mon == 7 
			|| tmGTM->tm_mon == 8 
			|| tmGTM->tm_mon == 10 
			|| tmGTM->tm_mon == 12
			) //1,3,5,7,8,10,12�·�
		{
			if ( tmGTM->tm_mday > 31 )
			{
				tmGTM->tm_mon  += 1;
				tmGTM->tm_mday -= 31;

				if ( tmGTM->tm_mon > 11 )
				{
					tmGTM->tm_year += 1;
					tmGTM->tm_mon  -= 11;
				}
			}
		}
		else if ( tmGTM->tm_mon == 4
				  || tmGTM->tm_mon == 6
				  || tmGTM->tm_mon == 9
				  || tmGTM->tm_mon == 11
				  ) //4,6,9,11�·�
		{
			if ( tmGTM->tm_mday > 30 )
			{
				tmGTM->tm_mon  += 1;
				tmGTM->tm_mday -= 30;
			}
		}
		else //2�·�
		{
			if ( (tmGTM->tm_year %4 == 0 && tmGTM->tm_year % 100 != 0) 
				|| (tmGTM->tm_year % 400 == 0)
				) //���������
			{
				if ( tmGTM->tm_mday > 29 )
				{
					tmGTM->tm_mon  += 1;
					tmGTM->tm_mday -= 29;
				}
			}
			else
			{
				if ( tmGTM->tm_mday > 28 )
				{
					tmGTM->tm_mon  += 1;
					tmGTM->tm_mday -= 28;
				}
			}
		}
	}

}

/***************************************************************
 * AdkGetTmFromGMTStr
 *
 * �� Fri, 21 Feb 2014 01:32:33 GMT�õ�ʱ��
 *
 * �����tm���ݽṹ�У�ֻ�����������ʱ������Ϣ
 * 
 */
INLINE
BOOL AdkGetTmFromGMTStr(PCHAR lpszDate, DWORD dwDateLen, OUT tm *lpTime)
{
	BOOL   bRet = FALSE;
	PCHAR  lpszBegin;
	PCHAR  lpszEnd;
	DWORD  dwMonth = 0;

	if ( dwDateLen > 64 || !lpTime )
	{
		return bRet;
	}
	memset(lpTime, 0, sizeof(struct tm));

	// Date: Fri, 21 Feb 2014 01:32:33 GMT
	//
	do
	{
		// ����Ϣ
		// �ҵ�,
		//
		lpszBegin = AdkStrChr(lpszDate, ',');
		if ( !lpszBegin )
		{
			break;
		}
		lpszBegin++;
		// ����,��Ŀո񣬵õ��յ�λ��
		//
		while ( ' ' == *lpszBegin )
		{
			lpszBegin++;
		}
		// �ҵ��յĽ�β��
		//
		lpszEnd = AdkStrStr(lpszBegin, " ");
		if ( !lpszEnd )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_mday = atoi(lpszBegin);

		// �·���Ϣ
		// �õ��µ�λ��
		lpszBegin = lpszEnd + 1;
		// �ҵ��µĽ�β��
		//
		lpszEnd = AdkStrStr(lpszBegin, " ");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 3 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		if ( 0 == AdkStrCmpI(lpszBegin, "Jan") )
		{
			dwMonth = 1;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Feb") )
		{
			dwMonth = 2;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Mar") )
		{
			dwMonth = 3;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Apr") )
		{
			dwMonth = 4;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "May") )
		{
			dwMonth = 5;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Jun") )
		{
			dwMonth = 6;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Jul") )
		{
			dwMonth = 7;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Aug") )
		{
			dwMonth = 8;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Sept") )
		{
			dwMonth = 9;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Oct") )
		{
			dwMonth = 10;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Nov") )
		{
			dwMonth = 11;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Dec") )
		{
			dwMonth = 12;
		}
		AdkASSERT((dwMonth));
		lpTime->tm_mon = dwMonth;

		// �����Ϣ
		// �õ����λ��
		lpszBegin = lpszEnd + 1;
		// �ҵ���Ľ�β��
		//
		lpszEnd = AdkStrStr(lpszBegin, " ");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 4 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_year = atoi(lpszBegin);

		// Сʱ��Ϣ
		// �õ�Сʱ��λ��
		lpszBegin = lpszEnd + 1;
		// �ҵ�Сʱ�Ľ�β��
		//
		lpszEnd = AdkStrStr(lpszBegin, ":");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 2 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_hour = atoi(lpszBegin);

		// ������Ϣ
		// �õ����ӵ�λ��
		lpszBegin = lpszEnd + 1;
		// �ҵ����ӵĽ�β��
		//
		lpszEnd = AdkStrStr(lpszBegin, ":");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 2 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_min = atoi(lpszBegin);

		// ����Ϣ
		// �õ����λ��
		lpszBegin = lpszEnd + 1;
		// �ҵ���Ľ�β��
		//
		lpszEnd = AdkStrStr(lpszBegin, " ");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 2 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_sec = atoi(lpszBegin);

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGetTimeFromInternet
 *
 * lpTimeΪ�����߷���Ĳ�С��sizeof(tm)���ڴ�ռ䣬�ɶ������struct tm ttt����&tttΪ��������
 *
 */
INLINE
BOOL AdkGetTimeFromInternet(OUT tm *lpTime)
{
	BOOL   bRet       = FALSE;
	PCHAR  lpszHeader = NULL;
	PCHAR  lpszDate   = NULL;
	struct tm gmtTime ;

	AdkASSERT((lpTime));
	if ( !lpTime )
	{
		return FALSE;
	}

	do
	{
		// ��Microsoft�õ�
		//
		lpszHeader = AdkGetResHeaderFromHost("time.windows.com");
		if ( lpszHeader )
		{
			lpszDate = AdkQueryDateInResHeaders(lpszHeader);
			if ( lpszDate )
			{
				if ( AdkGetTmFromGMTStr(lpszDate, strlen(lpszDate), &gmtTime) )
				{
					bRet = TRUE;
					break;
				}
			}
		}

		// ��Google�õ�
		//
		lpszHeader = AdkGetResHeaderFromHost("www.google.com");
		if ( lpszHeader )
		{
			lpszDate = AdkQueryDateInResHeaders(lpszHeader);
			if ( lpszDate )
			{
				if ( AdkGetTmFromGMTStr(lpszDate, strlen(lpszDate), &gmtTime) )
				{
					bRet = TRUE;
					break;
				}
			}
		}

		// ��Wikipedia�õ�
		//
		lpszHeader = AdkGetResHeaderFromHost("www.wikipedia.org");
		if ( lpszHeader )
		{
			lpszDate = AdkQueryDateInResHeaders(lpszHeader);
			if ( lpszDate )
			{
				if ( AdkGetTmFromGMTStr(lpszDate, strlen(lpszDate), &gmtTime) )
				{
					bRet = TRUE;
					break;
				}
			}
		}

	} while (FALSE);

	if ( bRet )
	{
		AdkGTMtoBJ(&gmtTime);

		AdkCopyMemory(lpTime, &gmtTime, sizeof(struct tm));
	}
	if ( lpszHeader )
	{
		free(lpszHeader);
	}
	if ( lpszDate )
	{
		free(lpszDate);
	}

	return bRet;
}


/***************************************************************
 * AdkGetTmFromFileTime
 *
 * lpTimeΪ�����߷���Ĳ�С��sizeof(tm)���ڴ�ռ䣬�ɶ������struct tm ttt����&tttΪ��������
 *
 *
 */
INLINE
BOOL AdkGetTmFromFileTime(IN FILETIME *lpFileTime, OUT tm *lpTime)
{
	AdkASSERT((lpTime));
	if ( !lpTime )
	{
		return FALSE;
	}
	FILETIME   localTime ;
	SYSTEMTIME sysTime   ;
	BOOL       bRet      = FALSE;

	do
	{
		if ( !FileTimeToLocalFileTime(lpFileTime, &localTime) )
		{
			break;
		}

		if ( !FileTimeToSystemTime(&localTime, &sysTime) )
		{
			break;
		}
		lpTime->tm_hour  = sysTime.wHour;
		lpTime->tm_min   = sysTime.wMinute;
		lpTime->tm_mday  = sysTime.wDay;
		lpTime->tm_mon   = sysTime.wMonth;
		lpTime->tm_year  = sysTime.wYear;
		lpTime->tm_sec   = sysTime.wSecond;
		lpTime->tm_wday  = sysTime.wDay;
		lpTime->tm_yday  = sysTime.wYear;
		lpTime->tm_isdst = 0;

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGetTmFromDword
 *
 * lpTimeΪ�����߷���Ĳ�С��sizeof(tm)���ڴ�ռ䣬�ɶ������struct tm ttt����&tttΪ��������
 *
 */
INLINE
VOID AdkGetTmFromDword(IN DWORD dwTime, OUT tm *lpTime)
{
	AdkASSERT((lpTime));
	if ( !lpTime )
	{
		return;
	}

	time_t  aclock = dwTime;

	localtime_s(lpTime, &aclock);

	lpTime->tm_year += 1900;
	lpTime->tm_mon  += 1;

	return;
}

/***************************************************************
 * AdkGetCurrentTime
 *
 */
INLINE
DWORD AdkGetCurrentTime()
{
	return (DWORD)time(NULL);
}


#ifdef __cplusplus
}
#endif //__cplusplus

#endif // ! __ADK_TUOJIE_LICENSE_H__