/***************************************************************************
 * Module:											(BuildNum:0001-20090322)
 *       AdkPE.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Time:
 *		2007-12-28,Nanjing
 *
 * Notes:
 *		PE�ļ�����
 *
 * Functions:
 *
 *    2014-04-18
 *       AdkIsWin32PEW(A)               - �ж�PE�Ƿ���32λ����
 *       AdkIsWin64PEW(A)               - �ж�PE�Ƿ���64λ����
 *
 *    2013-04-17
 *      AdkIsPEFileW
 *      AdkGetSectionDataByName
 *      AdkAddSectionToPEFileW
 *      AdkGetSectionHdrByName
 *      AdkPEComputeAlig
 *
 *		AdkComputeAlignSizes		    - ��������ĳ���
 *		AdkInjectFileInLastSectionA(W)	- ���ļ�Ƕ�뵽���һ������
 *		AdkExtractFileFromSectionA(W)	- ��ĳ���ڵ������ͷ�Ϊһ���ļ�
 *
 */

#pragma once

#ifndef _ADK_TUOJIE_PE_H_
#define _ADK_TUOJIE_PE_H_

#ifdef __cplusplus
extern "C"{
#endif//__cplusplus

#ifdef UNICODE

#define AdkInjectFileInLastSection			AdkInjectFileInLastSectionW
#define AdkExtractFileFromSection			AdkExtractFileFromSectionW
#define AdkIsWin64PE                        AdkIsWin64PEW
#define AdkIsWin32PE                        AdkIsWin32PEW

#else

#define AdkInjectFileInLastSection			AdkInjectFileInLastSectionA
#define AdkExtractFileFromSection			AdkExtractFileFromSectionA
#define AdkIsWin64PE                        AdkIsWin64PEA
#define AdkIsWin32PE                        AdkIsWin32PEA

#endif // !UNICODE

/****************************************************************************
 * AdkIsWin32PEW
 *
 */
__inline
BOOL WINAPI AdkIsWin32PEW(LPCWSTR lpwzFileName)
{
	HANDLE									hFile            = INVALID_HANDLE_VALUE;
	HANDLE									hFileMapping     = NULL;
	LPVOID                                  lpFileBase       = NULL;
	PIMAGE_NT_HEADERS						pNtHeader        ;
	PIMAGE_DOS_HEADER						pDosHeader       ;
	PIMAGE_OPTIONAL_HEADER32                pOptionalHeader32;
	BOOL                                    bIsWin32PE       = FALSE;

	do
	{
		// ��PE�ļ�
		//
		hFile =	CreateFileW(
			lpwzFileName,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			NULL); 
		if ( INVALID_HANDLE_VALUE == hFile )
		{
			break;
		}
		// �����ļ�ӳ��
		//
		hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);  
		if ( NULL == hFileMapping )
		{
			break;
		}
		// �ļ�ӳ��
		//
		lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
		if ( NULL == lpFileBase )
		{
			break;
		}
		// �ļ�ͷ
		//
		pDosHeader  = (PIMAGE_DOS_HEADER)lpFileBase	;
		pNtHeader   = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + pDosHeader->e_lfanew);
		pOptionalHeader32 = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pDosHeader + pDosHeader->e_lfanew + 24);
		// �ж�PEǩ��
		//
		if ( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE 
			|| pNtHeader->Signature != IMAGE_NT_SIGNATURE
			|| pOptionalHeader32->Magic != 0x010b
			)
		{ 
			break;
		}
		
		bIsWin32PE = TRUE;

	} while (FALSE);

	if ( lpFileBase )
	{
		UnmapViewOfFile(lpFileBase);
	}
	if ( hFileMapping )
	{
		CloseHandle(hFileMapping);  // xieb 2009.10.11
	}
	if ( INVALID_HANDLE_VALUE != hFile )
	{
		CloseHandle(hFile);
	}
	return bIsWin32PE;
}

/****************************************************************************
 * AdkIsWin32PEA
 *
 */
__inline
BOOL WINAPI AdkIsWin32PEA(LPCSTR lpszFileName)
{
	BOOL	bRet = FALSE;
	PWCHAR  lpwzFile = AdkStrToWStr(lpszFileName);
	if (lpwzFile)
	{
		bRet = AdkIsWin32PEW(lpwzFile);
		AdkFree(lpwzFile);
	}

	return bRet;
}

/****************************************************************************
 * AdkIsWin64PEW
 *
 */
__inline
BOOL WINAPI AdkIsWin64PEW(LPCWSTR lpwzFileName)
{
	HANDLE									hFile            = INVALID_HANDLE_VALUE;
	HANDLE									hFileMapping     = NULL;
	LPVOID                                  lpFileBase       = NULL;
	PIMAGE_NT_HEADERS						pNtHeader        ;
	PIMAGE_DOS_HEADER						pDosHeader       ;
	PIMAGE_OPTIONAL_HEADER32                pOptionalHeader32;
	BOOL                                    bIsWin64PE       = FALSE;

	do
	{
		// ��PE�ļ�
		//
		hFile =	CreateFileW(
			lpwzFileName,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			NULL); 
		if ( INVALID_HANDLE_VALUE == hFile )
		{
			break;
		}
		// �����ļ�ӳ��
		//
		hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);  
		if ( NULL == hFileMapping )
		{
			break;
		}
		// �ļ�ӳ��
		//
		lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
		if ( NULL == lpFileBase )
		{
			break;
		}
		// �ļ�ͷ
		//
		pDosHeader  = (PIMAGE_DOS_HEADER)lpFileBase	;
		pNtHeader   = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + pDosHeader->e_lfanew);
		pOptionalHeader32 = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pDosHeader + pDosHeader->e_lfanew + 24);
		// �ж�PEǩ��
		//
		if ( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE 
			|| pNtHeader->Signature != IMAGE_NT_SIGNATURE
			|| pOptionalHeader32->Magic != 0x020b
			)
		{ 
			break;
		}
		
		bIsWin64PE = TRUE;

	} while (FALSE);

	if ( lpFileBase )
	{
		UnmapViewOfFile(lpFileBase);
	}
	if ( hFileMapping )
	{
		CloseHandle(hFileMapping);  // xieb 2009.10.11
	}
	if ( INVALID_HANDLE_VALUE != hFile )
	{
		CloseHandle(hFile);
	}
	return bIsWin64PE;
}

/****************************************************************************
 * AdkIsWin64PEA
 *
 */
__inline
BOOL WINAPI AdkIsWin64PEA(LPCSTR lpszFileName)
{
	BOOL	bRet = FALSE;
	PWCHAR  lpwzFile = AdkStrToWStr(lpszFileName);
	if (lpwzFile)
	{
		bRet = AdkIsWin64PEW(lpwzFile);
		AdkFree(lpwzFile);
	}

	return bRet;
}

/****************************************************************************
 * AdkComputeAlignSizes
 *
 */
__inline
int WINAPI AdkComputeAlignSizes(int size, unsigned int align)
{
	// ��������������ݺ�Ĵ�С
	//
	if(size%align!=0)
	{
		return (size/align+1)*align;
	}

	return size;
}

/**************************************************************
 * AdkInjectFileInLastSectionW
 *	
 *	@@TODO: ������ļ����ܲ���̫��
 *	
 */
__inline
BOOL WINAPI AdkInjectFileInLastSectionW(PWCHAR lpwzPEFile, PWCHAR lpwzInputFile)
{
	BOOL					bRet		= FALSE;
	HANDLE					hPeFile		= INVALID_HANDLE_VALUE;
	HANDLE					hInjectFile = INVALID_HANDLE_VALUE;
	IMAGE_NT_HEADERS		NTHeader;
	DWORD					dwNTHeaderOffset;
	DWORD					dwByteReaded;
	DWORD					dwByteWritten;
	INT						nOldSectionNo;
	IMAGE_SECTION_HEADER	LastSection;			// ���ԭ�ļ����һ���������Ϣ
	IMAGE_SECTION_HEADER	NewSection;				// �½�����
	PBYTE					lpData	= NULL;
	PBYTE					lpPad	= NULL;
	DWORD					dwDataLen = 32*1024;	// һ�ζ�ȡ32K
	DWORD					dwInjectFileSize;
	DWORD					dwAlignFileSize;
	DWORD					dwPadLen;

	xASSERT((lpwzPEFile));
	xASSERT((lpwzInputFile));

	do
	{
		hPeFile = CreateFileW(lpwzPEFile,
							GENERIC_ALL, 
							FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

		if (hPeFile == INVALID_HANDLE_VALUE)
		{
			break;
		}

		hInjectFile = CreateFileW(lpwzInputFile,
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING, 
								FILE_ATTRIBUTE_NORMAL, 
								NULL);

		if (hInjectFile == INVALID_HANDLE_VALUE)
		{
			break;
		}

		dwInjectFileSize = GetFileSize(hInjectFile, NULL);

		// ��ȡPE�ļ�ͷ��
		//
		SetFilePointer(hPeFile, 0x3c, NULL, FILE_BEGIN);
		if ( ! ReadFile(hPeFile, &dwNTHeaderOffset, sizeof(DWORD), &dwByteReaded, NULL))
		{
			break;
		}

		SetFilePointer(hPeFile, dwNTHeaderOffset, NULL, FILE_BEGIN);
		if ( ! ReadFile(hPeFile, &NTHeader, sizeof(IMAGE_NT_HEADERS), &dwByteReaded, NULL))
		{
			break;	
		}

		if (NTHeader.Signature != IMAGE_NT_SIGNATURE)
		{
			break;
		}

		// ��λ�����һ���ڣ�����ȡ������
		//
		nOldSectionNo = NTHeader.FileHeader.NumberOfSections;

		SetFilePointer(hPeFile, dwNTHeaderOffset + 248, NULL, FILE_BEGIN);
		SetFilePointer(hPeFile, (nOldSectionNo - 1) * sizeof(IMAGE_SECTION_HEADER), NULL, FILE_CURRENT);

		if ( ! ReadFile(hPeFile, &LastSection, sizeof(IMAGE_SECTION_HEADER), &dwByteReaded, NULL))
		{
			break;
		}

		// ѭ�����룬д��Injected���ļ�
		//
		SetFilePointer(hPeFile, LastSection.PointerToRawData + LastSection.SizeOfRawData, NULL, FILE_BEGIN);

		lpData = (PBYTE)AdkMalloc(dwDataLen);
		while( ReadFile(hInjectFile, lpData, dwDataLen, &dwByteReaded, NULL))
		{
			if (dwByteReaded == 0)
			{
				break;
			}

			if ( ! WriteFile(hPeFile, lpData, dwByteReaded, &dwByteWritten, NULL))
			{
				break;
			}
		}

		if (dwByteReaded != 0)
		{
			break;
		}

		// ��������ӵ�������0��������ļ��ж���Ĵ�С
		//
		dwAlignFileSize = AdkComputeAlignSizes(dwInjectFileSize, NTHeader.OptionalHeader.FileAlignment);
		dwPadLen = dwAlignFileSize - dwInjectFileSize;
		if (dwPadLen > 0)
		{
			lpPad = (PBYTE)AdkMalloc(dwPadLen);
			WriteFile(hPeFile, lpPad, dwPadLen, &dwByteWritten, NULL);
		}

		// �����������е�����,д���µĿ��
		//
		ZeroMemory(&NewSection, sizeof(IMAGE_SECTION_HEADER));

		lstrcpyA((char*)NewSection.Name, ".cdata");

		NewSection.VirtualAddress = LastSection.VirtualAddress + AdkComputeAlignSizes(LastSection.Misc.VirtualSize, NTHeader.OptionalHeader.SectionAlignment);

		NewSection.PointerToRawData = LastSection.PointerToRawData + LastSection.SizeOfRawData;
		NewSection.Misc.VirtualSize = dwInjectFileSize;
		NewSection.SizeOfRawData	= dwAlignFileSize;
		NewSection.Characteristics	= 0xE0000020;
        
		SetFilePointer(hPeFile, dwNTHeaderOffset + 248 + sizeof(IMAGE_SECTION_HEADER) * nOldSectionNo, NULL, FILE_BEGIN);
		WriteFile(hPeFile, &NewSection, sizeof(IMAGE_SECTION_HEADER), &dwByteWritten, NULL);

		// ����PEͷ�ṹ
		//
		NTHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		NTHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;
		NTHeader.OptionalHeader.SizeOfCode		= NTHeader.OptionalHeader.SizeOfCode + dwAlignFileSize; 
		NTHeader.OptionalHeader.SizeOfImage		= NTHeader.OptionalHeader.SizeOfImage + dwAlignFileSize;
		NTHeader.FileHeader.NumberOfSections	= nOldSectionNo + 1;

		SetFilePointer(hPeFile, dwNTHeaderOffset, NULL, FILE_BEGIN);
		WriteFile(hPeFile, &NTHeader, sizeof(IMAGE_NT_HEADERS), &dwByteWritten, NULL);

		bRet = TRUE;

	} while(FALSE);

	if (lpData)
	{
		AdkFree(lpData);
	}

	if (lpPad)
	{
		AdkFree(lpPad);
	}

	if (hPeFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hPeFile);
	}

	if (hInjectFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hInjectFile);
	}

	return bRet;
}

/**************************************************************
 * AdkInjectFileInLastSectionA
 *	
 *	@@TODO: ������ļ����ܲ���̫��
 *	
 */
__inline
BOOL WINAPI AdkInjectFileInLastSectionA(PCHAR lpszPEFile, PCHAR lpszInputFile)
{
	BOOL	bRet;
	PWCHAR	lpwzPEFile;
	PWCHAR	lpwzInputFile;

	lpwzPEFile = AdkStrToWStr(lpszPEFile);
	if (lpwzPEFile == NULL)
	{
		return FALSE;
	}

	lpwzInputFile = AdkStrToWStr(lpszInputFile);
	if (lpwzInputFile == NULL)
	{
		AdkFree(lpwzPEFile);
		return FALSE;
	}

	bRet = AdkInjectFileInLastSectionW(lpwzPEFile, lpwzInputFile);

	AdkFree(lpwzPEFile);
	AdkFree(lpwzInputFile);

	return bRet;
}

/**************************************************************
 * AdkExtractFileFromSectionW
 *
 *	dwSectionNum: �ڱ�ţ� -1˵��Ϊ���һ����
 *	
 */
__inline
BOOL WINAPI AdkExtractFileFromSectionW(PWCHAR	lpwzPEFile, 
								DWORD	dwSectionNum, 
								PWCHAR	lpwzOutputFile)
{
	BOOL					bRet		= FALSE;
	HANDLE					hPeFile		= INVALID_HANDLE_VALUE;
	HANDLE					hOutputFile = INVALID_HANDLE_VALUE;
	DWORD					dwNTHeaderOffset;
	IMAGE_NT_HEADERS		NTHeader;
	DWORD					dwByteReaded;
	DWORD					dwByteWritten;
	IMAGE_SECTION_HEADER	SectionHeader;			// ����ļ��Ŀ�
	PBYTE					lpData	= NULL;
	DWORD					dwDataLen = 32*1024;	// һ�ζ�ȡ32K
	DWORD					dwFileSize;
	DWORD					dwReadSize = 0;

	do
	{
		hPeFile = CreateFileW(lpwzPEFile,
							GENERIC_READ, 
							FILE_SHARE_READ,
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

		if (hPeFile == INVALID_HANDLE_VALUE)
		{
			break;
		}

		hOutputFile = CreateFileW(lpwzOutputFile,
								GENERIC_ALL,
								FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
								NULL,
								CREATE_ALWAYS, 
								FILE_ATTRIBUTE_NORMAL, 
								NULL);

		if (hOutputFile == INVALID_HANDLE_VALUE)
		{
			break;
		}

		// ��ȡPE�ļ�ͷ��
		//
		SetFilePointer(hPeFile, 0x3c, NULL, FILE_BEGIN);
		if ( ! ReadFile(hPeFile, &dwNTHeaderOffset, sizeof(DWORD), &dwByteReaded, NULL))
		{
			break;
		}

		SetFilePointer(hPeFile, dwNTHeaderOffset, NULL, FILE_BEGIN);
		if ( ! ReadFile(hPeFile, &NTHeader, sizeof(IMAGE_NT_HEADERS), &dwByteReaded, NULL))
		{
			break;	
		}

		if (NTHeader.Signature != IMAGE_NT_SIGNATURE)
		{
			break;
		}

		// ��λ��Ӧ�Ľ�ͷ��
		//
		if (dwSectionNum == -1)
		{
			dwSectionNum = NTHeader.FileHeader.NumberOfSections;
		}
		else
		{
			if (dwSectionNum > NTHeader.FileHeader.NumberOfSections)
			{
				break;
			}
		}

		SetFilePointer(hPeFile, dwNTHeaderOffset + 248, NULL, FILE_BEGIN);
		if (dwSectionNum > 1)
		{
			SetFilePointer(hPeFile, (dwSectionNum - 1) * sizeof(IMAGE_SECTION_HEADER), NULL, FILE_CURRENT);
		}

		if ( ! ReadFile(hPeFile, &SectionHeader, sizeof(IMAGE_SECTION_HEADER), &dwByteReaded, NULL))
		{
			break;
		}

		dwFileSize = SectionHeader.Misc.VirtualSize;		// ����洢����ʵ���ļ���С

		// ѭ�����룬д��������ļ�
		//
		SetFilePointer(hPeFile, SectionHeader.PointerToRawData, NULL, FILE_BEGIN);

		lpData = (PBYTE)AdkMalloc(dwDataLen);

		while( ReadFile(hPeFile, lpData, dwDataLen, &dwByteReaded, NULL))
		{
			if (dwByteReaded == 0)
			{
				break;
			}

			if ((dwReadSize + dwByteReaded) <= dwFileSize)
			{
				WriteFile(hOutputFile, lpData, dwByteReaded, &dwByteWritten, NULL);
				dwReadSize += dwByteReaded;
			}
			else
			{
				WriteFile(hOutputFile, lpData, dwFileSize - dwReadSize, &dwByteWritten, NULL);
				break;
			}
		}

		bRet = TRUE;

	} while(FALSE);

	if (hPeFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hPeFile);
	}

	if (hOutputFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hOutputFile);
	}

	if (lpData)
	{
		AdkFree(lpData);
	}

	return bRet;
}

/**************************************************************
 * AdkExtractFileFromSectionA
 *
 *	dwSectionNum: �ڱ�ţ� -1˵��Ϊ���һ����
 *		
 */
__inline
BOOL WINAPI AdkExtractFileFromSectionA(PCHAR	lpszPEFile, 
								DWORD	dwSectionNum, 
								PCHAR	lpszOutputFile)
{
	BOOL	bRet;
	PWCHAR	lpwzPEFile;
	PWCHAR	lpwzOutputFile;

	lpwzPEFile = AdkStrToWStr(lpszPEFile);
	if (lpwzPEFile == NULL)
	{
		return FALSE;
	}

	lpwzOutputFile = AdkStrToWStr(lpszOutputFile);
	if (lpwzOutputFile == NULL)
	{
		AdkFree(lpwzPEFile);
		return FALSE;
	}

	bRet = AdkExtractFileFromSectionW(lpwzPEFile, dwSectionNum, lpwzOutputFile);

	AdkFree(lpwzPEFile);
	AdkFree(lpwzOutputFile);

	return bRet;
}


/****************************************************************************
 * ComputeAlig
 *
 */
INLINE int WINAPI AdkPEComputeAlig(int size, unsigned int align)
{
	// ��������������ݺ�Ĵ�С
	//
	if(size%align!=0)
	{
		return (size/align+1)*align;
	}

	return size;
}

/****************************************************************************
 * _AdkGetSectionHdrByName
 * ���ݽ����õ���ͷ
 *
 */
INLINE BOOL WINAPI AdkGetSectionHdrByName(PIMAGE_NT_HEADERS pNtHeader, IMAGE_SECTION_HEADER *secHeader, LPBYTE lpbSection)
{
	PIMAGE_SECTION_HEADER pSecHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeader + sizeof(IMAGE_NT_HEADERS));
	int nSections = pNtHeader->FileHeader.NumberOfSections;
	int i;
	if ( pSecHeader )
	{
		for (i = 0; i < nSections; i++)
		{
			if ( 0 == lstrcmpA((PCHAR)pSecHeader->Name, (PCHAR)lpbSection))
			{
				CopyMemory((LPVOID)secHeader, (LPVOID)pSecHeader, sizeof(IMAGE_SECTION_HEADER));
				return TRUE;
			}
			pSecHeader++;
		}
	}
	return FALSE;
}

/****************************************************************************
 * _AdkGetSectionDataByName
 * ���ݽ�����ȡ����
 *
 * ����˵����
 *     lpwzPeFile         -    PE�ļ�
 *     lpbSecName         -    ����
 *     lpBuf              -    �ڵ�����
 *     dwBufLen           -    ���ݵĳ���
 * ע��
 *     lpBuf ����ΪNULL�� �������ڲ�ʹ��AdkMalloc�����ڴ棬��ʹ��AdkFree�ͷ�
 *     dwLen ����Ϊ0�����ý�����Ϊ���ݵĳ���
 */
INLINE VOID WINAPI AdkGetSectionDataByName(IN LPCWSTR lpwzPEFile, IN LPBYTE lpbSecName, OUT LPVOID *lpBuf, OUT LPDWORD dwLen)
{
	HANDLE									hFile        = INVALID_HANDLE_VALUE;
	HANDLE									hFileMapping = NULL;
	LPVOID                                  lpFileBase   = NULL;
	PIMAGE_NT_HEADERS						pNtHeader    ;
	PIMAGE_DOS_HEADER						pDosHeader   ;
	IMAGE_SECTION_HEADER                    secHeader    ;
	DWORD                                   dwByteRead   ;

	do
	{
		// ��EXE�ļ�
		//
		hFile =	CreateFileW(
			lpwzPEFile,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			NULL); 
		if ( INVALID_HANDLE_VALUE == hFile )
		{
			break;
		}
		// �����ļ�ӳ��
		//
		hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);  
		if ( NULL == hFileMapping )
		{
			break;
		}
		// �ļ�ӳ��
		//
		lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
		if ( NULL == lpFileBase )
		{
			break;
		}
		// �ļ�ͷ
		//
		pDosHeader  = (PIMAGE_DOS_HEADER)lpFileBase;
		pNtHeader   = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + pDosHeader->e_lfanew);
		// �ж�PEǩ��
		//
		if ( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE 
			|| pNtHeader->Signature != IMAGE_NT_SIGNATURE )
		{
			break;
		}
		// ͨ�������õ���Ӧ��ͷ��Ϣ
		//
		if ( !AdkGetSectionHdrByName(pNtHeader, &secHeader, lpbSecName) )
		{
			break;
		}
		*lpBuf = (PCHAR)AdkMalloc(secHeader.Misc.VirtualSize + 1);
		if ( !lpBuf )
		{
			break;
		}
		SetFilePointer(hFile, secHeader.PointerToRawData, NULL, FILE_BEGIN);
		ReadFile(hFile, *lpBuf, secHeader.Misc.VirtualSize, &dwByteRead, NULL);

		*dwLen = secHeader.Misc.VirtualSize;

	} while (FALSE);

	if ( lpFileBase )
	{
		UnmapViewOfFile(lpFileBase);
	}
	if ( hFileMapping )
	{
		CloseHandle(hFileMapping);  // xieb 2009.10.11
	}
	if ( INVALID_HANDLE_VALUE != hFile )
	{
		CloseHandle(hFile);
	}

	return ;
}

/****************************************************************************
 * _AdkAddSectionToPEFileW
 * ��PE�ļ��м���ڣ�����������
 *
 * ����˵����
 *     lpwzPeFile         -    ������ڵ�PE�ļ�
 *     lpbSecName         -    ����
 *     dwSecNameLen       -    ��������
 *     dwCharacteristics  -    �ڵ�����
 *     lpBuf              -    �½ڵ�����
 *     dwBufLen           -    �½����ݵĳ���
 */
INLINE BOOL WINAPI AdkAddSectionToPEFileW(LPCWSTR lpwzPEFile, LPBYTE lpbSecName, DWORD dwSecNameLen, DWORD dwCharacteristics, LPVOID lpBuf, DWORD dwBufLen)
{
	BOOL                                    bSuccess     = FALSE;
	HANDLE									hFile        = INVALID_HANDLE_VALUE;
	HANDLE									hFileMapping = NULL;
	LPVOID                                  lpFileBase   = NULL;
	PIMAGE_NT_HEADERS						pNtHeader    ;
	PIMAGE_DOS_HEADER						pDosHeader   ;
	PIMAGE_SECTION_HEADER                   pNewSec      = NULL;
	PIMAGE_SECTION_HEADER                   pLastSec     = NULL;
	DWORD                                   dwNewSecAlign;
	DWORD                                   dwNewFileAlign;
	DWORD                                   dwByteWritten;
	DWORD					                dwPadLen;
	PBYTE					                lpPad;

	AdkASSERT(dwSecNameLen<8);
	do
	{
		// ��EXE�ļ�
		//
		hFile =	CreateFileW(
			lpwzPEFile,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			NULL); 
		if ( INVALID_HANDLE_VALUE == hFile )
		{
			break;
		}
		// �����ļ�ӳ��
		//
		hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);  
		if ( NULL == hFileMapping )
		{
			break;
		}
		// �ļ�ӳ��
		//
		lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if ( NULL == lpFileBase )
		{
			break;
		}
		// �ļ�ͷ
		//
		pDosHeader  = (PIMAGE_DOS_HEADER)lpFileBase;
		pNtHeader   = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + pDosHeader->e_lfanew);
		// �ж�PEǩ��
		//
		if ( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE 
			|| pNtHeader->Signature != IMAGE_NT_SIGNATURE )
		{
			break;
		}
        // �ж��Ƿ��п�϶���˴�Ĭ���п�϶
		// TO_DO
		pLastSec = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeader + sizeof(IMAGE_NT_HEADERS) + (pNtHeader->FileHeader.NumberOfSections -  1) * sizeof(IMAGE_SECTION_HEADER));
        pNewSec  = (PIMAGE_SECTION_HEADER)((DWORD)pLastSec + sizeof(IMAGE_SECTION_HEADER));

        dwNewSecAlign  = AdkPEComputeAlig(pLastSec->VirtualAddress + pLastSec->Misc.VirtualSize, pNtHeader->OptionalHeader.SectionAlignment);
        dwNewFileAlign = AdkPEComputeAlig(pLastSec->PointerToRawData + pLastSec->SizeOfRawData, pNtHeader->OptionalHeader.FileAlignment);

        memcpy(pNewSec->Name, lpbSecName, dwSecNameLen);
       
		pNewSec->VirtualAddress = dwNewSecAlign;
        pNewSec->Misc.VirtualSize = dwBufLen;
        pNewSec->PointerToRawData = dwNewFileAlign;
        pNewSec->Characteristics = dwCharacteristics;
		pNewSec->SizeOfRawData = AdkPEComputeAlig(dwBufLen, pNtHeader->OptionalHeader.FileAlignment);

		// ����ͷ
		//
        pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;
        pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		pNtHeader->OptionalHeader.SizeOfImage += AdkPEComputeAlig(dwBufLen, pNtHeader->OptionalHeader.SectionAlignment);
		pNtHeader->OptionalHeader.SizeOfCode  += AdkPEComputeAlig(dwBufLen, pNtHeader->OptionalHeader.FileAlignment);

		pNtHeader->FileHeader.NumberOfSections++;

		// д���½�����
		//
		if ( !SetFilePointer(hFile, dwNewFileAlign, NULL, FILE_BEGIN) )
		{
			break;
		}
		WriteFile(hFile, lpBuf, dwBufLen, &dwByteWritten, NULL);

		// ��������ӵ�������0��������ļ��ж���Ĵ�С
		//
		dwPadLen = AdkPEComputeAlig(dwBufLen, pNtHeader->OptionalHeader.FileAlignment) - dwBufLen;
		lpPad = (PBYTE)GlobalAlloc(GPTR, dwPadLen);
		WriteFile(hFile, lpPad, dwPadLen, &dwByteWritten, NULL);
		GlobalFree(lpPad);

	} while (FALSE);
	
	if ( lpFileBase )
	{
		UnmapViewOfFile(lpFileBase);
	}
	if ( hFileMapping )
	{
		CloseHandle(hFileMapping);  // xieb 2009.10.11
	}
	if ( INVALID_HANDLE_VALUE != hFile )
	{
		CloseHandle(hFile);
	}

	return bSuccess;
}

/****************************************************************************
 * _AdkIsPEFileW
 *
 */
INLINE BOOL WINAPI AdkIsPEFileW(LPCWSTR lpwzFile)
{
	HANDLE									hFile        = INVALID_HANDLE_VALUE;
	HANDLE									hFileMapping = NULL;
	LPVOID                                  lpFileBase   = NULL;
	PIMAGE_NT_HEADERS						pNtHeader     ;
	PIMAGE_DOS_HEADER						pDosHeader    ;
	BOOL                                    bIsPE        = FALSE;

	do
	{
		// ��EXE�ļ�
		//
		hFile =	CreateFileW(
			lpwzFile,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			NULL); 
		if ( INVALID_HANDLE_VALUE == hFile )
		{
			break;
		}
		// �����ļ�ӳ��
		//
		hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);  
		if ( NULL == hFileMapping )
		{
			break;
		}
		// �ļ�ӳ��
		//
		lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
		if ( NULL == lpFileBase )
		{
			break;
		}
		// �ļ�ͷ
		//
		pDosHeader  = (PIMAGE_DOS_HEADER)lpFileBase	;
		pNtHeader   = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + pDosHeader->e_lfanew);
		// �ж�PEǩ��
		//
		if ( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE 
			|| pNtHeader->Signature != IMAGE_NT_SIGNATURE )
		{ 
			break;
		}
		bIsPE = TRUE;

	} while (FALSE);

	if ( lpFileBase )
	{
		UnmapViewOfFile(lpFileBase);
	}
	if ( hFileMapping )
	{
		CloseHandle(hFileMapping);  // xieb 2009.10.11
	}
	if ( INVALID_HANDLE_VALUE != hFile )
	{
		CloseHandle(hFile);
	}
	return bIsPE;
}

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // _ADK_TUOJIE_PE_H_