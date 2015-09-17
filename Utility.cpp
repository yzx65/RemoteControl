#include "adkprecomp.h"
#include "adkbase64.h"
#include "maindlg.h"
#include "targetdlg.h"
//#include "datamodule.h"
#include "Utility.h"
#include "include/errorcode.h"
#include "include/T5.h"
#include "include/CtrAndDaeCommon.h"
#include "include/T5UsbConfig.h"
#include "DatabaseManager.h"

#include <QString>
#pragma comment(lib, "shell32.lib")

extern DatabaseManager* DM;

//---------------------------------------------------------------------------
void SetStatusInfoA(STATUS_LEVEL sl, const char* info)
{
    SendMessage(FrmMain->Handle, WM_SET_STATUSINFO_A, sl, (long)info);
}
//---------------------------------------------------------------------------
void SetStatusInfoW(STATUS_LEVEL sl, const wchar_t* info)
{
    SendMessage(FrmMain->Handle, WM_SET_STATUSINFO_W, sl, (long)info);
}
//---------------------------------------------------------------------------
void SetStatusInfoExA(STATUS_LEVEL sl, const char* format,...)
{
	char szStatusInfo[2048] = {0};

	va_list args;
	va_start(args,format);
	vsprintf(szStatusInfo, format, args);
	va_end(args);

    SendMessage(FrmMain->Handle, WM_SET_STATUSINFO_A, sl, (long)szStatusInfo);
}
//---------------------------------------------------------------------------
void SetStatusInfoExW(STATUS_LEVEL sl, const wchar_t* format,...)
{
    wchar_t wzStatusInfo[2048];

	va_list args;
	va_start(args,format);
	vswprintf(wzStatusInfo, format, args);
	va_end(args);

    SendMessage(FrmMain->Handle, WM_SET_STATUSINFO_W, sl, (long)wzStatusInfo);
}
//---------------------------------------------------------------------------
void SetTarStatusInfoExW(STATUS_LEVEL sl, Target *tarBlock, const wchar_t* format,...)
{
    wchar_t wzStatusInfo[2048];

	va_list args;
	va_start(args,format);
	vswprintf(wzStatusInfo, format, args);
	va_end(args);

    SendMessage(FrmMain->Handle, WM_SET_STATUSINFO_W, sl, (long)wzStatusInfo);

    if (tarBlock->frmTarControl)
    {
        TargetDlg *frm = (TargetDlg *)tarBlock->frmTarControl;
        SendMessage(frm->Handle, WM_SET_TAR_STATUSINFO_W, sl, (long)wzStatusInfo);
    }

	wchar_t *lpPartInfo = wcschr(wzStatusInfo, L']');

	if (lpPartInfo)
	{
		lpPartInfo++;
	}
	else
	{
		lpPartInfo = wzStatusInfo;
	}

	DM->InsertLogDetailInfo(tarBlock->dwTargetID, AnsiToWide(TGetCurrentTime()), std::wstring(lpPartInfo));
}
//---------------------------------------------------------------------------
void MsgBoxInfoA(HWND hWnd, const char *info)
{
    MessageBoxA(hWnd, info, "提示", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void MsgBoxInfoW(HWND hWnd, const wchar_t *info)
{
    MessageBoxW(hWnd, info, L"提示", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
int MsgBoxExW(HWND hWnd, UINT uType, const wchar_t *caption, const wchar_t *format, ...)
{
    wchar_t wzInfo[2048];

	va_list args;
	va_start(args, format);
	vswprintf(wzInfo, format, args);
	va_end(args);

    return MessageBoxW(hWnd, wzInfo, caption, uType);
}
//---------------------------------------------------------------------------
void MsgBoxInfoExW(HWND hWnd, const wchar_t *format,...)
{
    wchar_t wzInfo[2048];

	va_list args;
	va_start(args, format);
	vswprintf(wzInfo, format, args);
	va_end(args);

    MessageBoxW(hWnd, wzInfo, L"提示", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void MsgBoxErrorW(HWND hWnd, const wchar_t *info)
{
    MessageBoxW(hWnd, info, L"提示", MB_OK | MB_ICONWARNING);
}
//---------------------------------------------------------------------------
void MsgBoxErrorExW(HWND hWnd, const wchar_t *format,...)
{
    wchar_t wzInfo[2048];
    
	va_list args;
	va_start(args, format);
	vswprintf(wzInfo, format, args);
	va_end(args);

    MessageBoxW(hWnd, wzInfo, L"提示", MB_OK | MB_ICONWARNING);
}
//---------------------------------------------------------------------------
//time_t ConvertDataTimeToTimeT(TDateTime dt)
//{
//    time_t   t;   
//    struct   tm   tmWk;   
//    unsigned   short   iYear,iMonth,iDay,iHour,iMinute,iSecond,imlSec;   
//    dt.DecodeDate(&iYear,&iMonth,&iDay);
//    dt.DecodeTime(&iHour,&iMinute,&iSecond,&imlSec);   
//    tmWk.tm_year   =   iYear   -   1900;   
//    tmWk.tm_mon     =   iMonth   -1;   
//    tmWk.tm_mday   =   iDay;   
//    tmWk.tm_hour   =   iHour;   
//    tmWk.tm_min     =   iMinute;   
//    tmWk.tm_sec     =   iSecond;   
//    tmWk.tm_isdst   =   -1;   
//    tmWk.tm_wday   =   -1;   
//    tmWk.tm_yday   =   -1;
//      
//    t   =   mktime(&tmWk);   
//    return   t;
//}
//---------------------------------------------------------------------------
std::vector<std::string> SplitString(const std::string & s, const std::string & sep, bool suppressBlanks)
{
    std::vector<std::string> array;     
    size_t position, last_position;
    
    last_position = position = 0;
    while (position + sep.size() <= s.size())
    {
        if (s[position] == sep[0] && s.substr(position, sep.size()) == sep)
        {
            if (!suppressBlanks || position - last_position > 0)
			{
                array.push_back(s.substr(last_position, position - last_position));
			}
            last_position = position = position + sep.size();
        }
        else
            position++;
    }

    if (!suppressBlanks || last_position - s.size())
	{
        array.push_back(s.substr(last_position));
	}
    
    return array;
}
//---------------------------------------------------------------------------
std::vector<PFILE_BLOCK> SplitSearchString(const std::string & s,
                                           const std::string & outsep,
                                           const std::string & insep)
{
    // Format of DirInformation
    //     FileName*FilePath*FileAttributes*LastAccessTime*Size | FileName*...
    //
    std::vector<std::string> dirArray;
    std::vector<PFILE_BLOCK> fileArray;
    dirArray = SplitString(s,outsep);

    std::vector<std::string>::iterator i = dirArray.begin();
    for (; i != dirArray.end(); i++)
    {
        std::string dir = (*i);
        std::vector<std::string> entryArray = SplitString(dir,insep);

        if (entryArray.size() < 4)
        {
            continue;
        }
        
        std::vector<std::string>::iterator j = entryArray.begin();
        
        PFILE_BLOCK fileBlock = new FILE_BLOCK();
        fileBlock->widName = GetWideFromBase64((*j++).c_str());
        fileBlock->widPath = GetWideFromBase64((*j++).c_str());
        fileBlock->FileAttributes = strtoul((*j++).c_str(),NULL,10);
        fileBlock->LastWriteTime  = _atoi64((*j++).c_str());
        fileBlock->Size = _atoi64((*j).c_str());
        fileBlock->bDowned = false;
        fileBlock->bChanged = false;        
        fileArray.push_back(fileBlock);
    }
    
    return fileArray;

}
//---------------------------------------------------------------------------
std::vector<PFILE_BLOCK> SplitDirString(const std::string & s,
                                        const std::string & outsep,
                                        const std::string & insep)
{
    // Format of DirInformation
    //     FileName*FileAttributes*LastAccessTime*Size | FileName*...
    //
    std::vector<std::string> dirArray;
    std::vector<PFILE_BLOCK> fileArray;
    dirArray = SplitString(s,outsep);

    std::vector<std::string>::iterator i = dirArray.begin();
    for (; i != dirArray.end(); i++)
    {
        std::string dir = (*i);
        std::vector<std::string> entryArray = SplitString(dir,insep);

        if (entryArray.size() < 4)
        {
            continue;
        }
        
        std::vector<std::string>::iterator j = entryArray.begin();
        
        PFILE_BLOCK fileBlock = new FILE_BLOCK();
        fileBlock->widName = GetWideFromBase64((*j++).c_str());
        fileBlock->FileAttributes = strtoul((*j++).c_str(),NULL,10);
        fileBlock->LastWriteTime = _atoi64((*j++).c_str());

        if (fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            fileBlock->Size = -1;
        }
        else
        {
            fileBlock->Size = _atoi64((*j).c_str());
        }

        fileBlock->bDowned = false;
        fileBlock->bChanged = false;

        fileArray.push_back(fileBlock);
    }
    
    return fileArray;
}
//---------------------------------------------------------------------------
const wchar_t * ExtractFileNameW(const wchar_t *lpwzPath)
{
    const wchar_t* lpwzName = wcsrchr(lpwzPath, L'\\');
    if (lpwzName)
    {
        lpwzName++;
    }

    return lpwzName;
}
//---------------------------------------------------------------------------
std::wstring ExtractFilePathW(wchar_t *lpwzPath)
{
    std::wstring widPath = lpwzPath;

    wchar_t *lpwzName;
    lpwzName = wcsrchr(lpwzPath, L'\\');
    if (lpwzName)
    {
        widPath = widPath.substr(0, lpwzName - lpwzPath + 1);
    }

    return widPath;
}
//---------------------------------------------------------------------------

void ParamConvert(char * param, BOOLEAN direction)
{
	char * pFound = NULL;

	if (NULL == param)
		return;

	if (direction)
	{
		// Convert space to \t
		//
		do
		{
			pFound = strchr(param,' ');
            if ( !pFound )
            {
                break;
            }
			pFound[0] = '\t';
			param = pFound;

		} while(true);
	}
	else
	{
		// Convert \t to space
		//
		do
		{
			pFound = strchr(param,'\t');
            if ( !pFound )
            {
                break;
            }
			pFound[0] = ' ';
			param = pFound;
		} while(true);
	}
}
//---------------------------------------------------------------------------
void CryptData(BYTE *data, int len)
{
	//for (int i = 0; i < len; i++)
	//{
	//	*data = *data ^ 85;
	//	data ++;
	//}
}
//---------------------------------------------------------------------------
void ConvertSpaceToTab(char * param)
{
	char * pFound = NULL;
    
	if (NULL == param)
    {
		return;
    }
    
    // Convert space to \t
    //
    do
    {
        pFound = strchr(param,' ');
        if ( !pFound )
        {
            break;
        }
        pFound[0] = '\t';
        param = pFound;

    } while(true);

    return;
}
//---------------------------------------------------------------------------
void ConvertTabToSpace(char * param)
{
	char * pFound = NULL;

	if (NULL == param)
    {
		return;
    }
    
    // Convert \t to space
    //
    do
    {
        pFound = strchr(param,'\t');
        if ( !pFound )
        {
            break;
        }
        pFound[0] = ' ';
        param = pFound;
        
    } while(true);

    return;
}
//---------------------------------------------------------------------------
std::string GetTimeString(LONG time)
{
    struct tm *newtime = _localtime32((__time32_t*)&time);
	if ( newtime == NULL)
	{
		return std::string("");
	}
	char tmp[MAX_PATH] = {0};
	sprintf(tmp, "%.2d-%.2d-%.2d %.2d:%.2d:%.2d", newtime->tm_year+1900,newtime->tm_mon+1,
		newtime->tm_mday,newtime->tm_hour,newtime->tm_min,newtime->tm_sec);
	return std::string(tmp);
}
//---------------------------------------------------------------------------
std::string GetDateString(LONG time)
{
	struct tm *newtime = _localtime32((__time32_t*)&time);
	char tmp[MAX_PATH] = {0};
	sprintf(tmp, "%d-%d-%d", newtime->tm_year+1900,newtime->tm_mon+1,
		newtime->tm_mday);
	return std::string(tmp);
}
//---------------------------------------------------------------------------
std::string ConvertBuildNumberToStr(ULONG osBuildNumber)
{
    std::string ver;

	ULONG temp = osBuildNumber;
	osBuildNumber &= 0xEFFFFFFF;
     
    switch(osBuildNumber)
    {
    case OS_WIN2K:
        ver = std::string("Windows 2000");
        break;
        
    case OS_WINXP:
        ver = std::string("Windows XP");
        break;

    case OS_WIN2003:
        ver = std::string("Windows 2003");
        break;

    case OS_WINVISTA:
    case OS_WINVISTASP2:
        ver = std::string("Windows Vista");
        break;

    case OS_WIN2008:
        ver = std::string("Windows 2008");
        break;

    case OS_WIN7PRO:
        ver = std::string("Windows 7");
        break;

    case OS_WIN7SP1:
        ver = std::string("Windows 7 SP1");
        break;

	case OS_WIN8:
		ver = std::string("Windows 8");
		break;

	case OS_WIN81:
		ver = std::string("Windows 8.1");
		break;

	case OS_WIN8_PREVIEW:
		ver = std::string("Windows 8.1");
		break;

	case MACOS_X_VERSION_10_4:
		ver = std::string("Mac OS X 10.4");
		break;

	case MACOS_X_VERSION_10_6:
		ver = std::string("Mac OS X 10.6");
		break;

	case MACOS_X_VERSION_10_7:
		ver = std::string("Mac OS X 10.7");
		break;

	case MACOS_X_VERSION_10_8:
		ver = std::string("Mac OS X 10.8");
		break;

	case MACOS_X_VERSION_10_9:
		ver = std::string("Mac OS X 10.9");
		break;

	case MACOS_X_VERSION_10_10:
		ver = std::string("Mac OS X 10.10");
		break;

	case IOS_VERSION_1:
		ver = std::string("IOS 1");
		break;

	case IOS_VERSION_2:
		ver = std::string("IOS 2");
		break;

	case IOS_VERSION_3:
		ver = std::string("IOS 3");
		break;

	case IOS_VERSION_4:
		ver = std::string("IOS 4");
		break;

	case IOS_VERSION_5:
		ver = std::string("IOS 5");
		break;

	case IOS_VERSION_6:
		ver = std::string("IOS 6");
		break;

	case IOS_VERSION_7:
		ver = std::string("IOS 7");
		break;

	case IOS_VERSION_8:
		ver = std::string("IOS 8");
		break;

	case ANDROID_2_0_VERSION:
		ver = std::string("Android 2.0");
		break;

	case ANDROID_2_1_VERSION:
		ver = std::string("Android 2.1");
		break;

	case ANDROID_2_2_VERSION:
		ver = std::string("Android 2.2");
		break;

	case ANDROID_2_3_VERSION:
		ver = std::string("Android 2.3");
		break;

	case ANDROID_4_0_VERSION:
		ver = std::string("Android 4.0");
		break;

	case ANDROID_4_1_VERSION:
		ver = std::string("Android 4.1");
		break;

	case ANDROID_4_2_VERSION:
		ver = std::string("Android 4.2");
		break;

	case ANDROID_4_3_VERSION:
		ver = std::string("Android 4.3");
		break;

	case ANDROID_4_4_VERSION:
		ver = std::string("Android 4.4");
		break;

	case ANDROID_5_0_VERSION:
		ver = std::string("Android 5.0");
		break;

	case ANDROID_5_1_VERSION:
		ver = std::string("Android 5.1");
		break;

	case ANDROID_5_2_VERSION:
		ver = std::string("Android 5.2");
		break;

    default:
        ver = std::string("未知");
        break;
    }
	
	if ( temp & 0x10000000 )
		ver += " 64 位";

    return ver;
}
//---------------------------------------------------------------------------
std::string GetBase64FromAnsi(std::string aStr)
{
    // Temp Using
    //
    char base64Path[MAX_PATH * 4];
    ZeroMemory(base64Path, MAX_PATH * 4);

    PBYTE pData = (PBYTE)aStr.c_str();
    int   dataLen = aStr.length();
    
    AdkBase64Encode(pData, dataLen, base64Path, MAX_PATH * 4);

    std::string ansiStr = base64Path;
    return ansiStr;
}
//---------------------------------------------------------------------------
std::string GetBase64FromWide(std::wstring wStr)
{
    // Temp Using
    //
    char base64Path[MAX_PATH * 4];
    ZeroMemory(base64Path, MAX_PATH * 4);

    PBYTE pData = (PBYTE)wStr.c_str();
    int   dataLen = wStr.length() * 2;
    
    AdkBase64Encode(pData, dataLen, base64Path, MAX_PATH * 4);
    std::string ansiStr = base64Path;
    return ansiStr;
}
//---------------------------------------------------------------------------
std::wstring GetWideFromBase64(std::string base64Str)
{
    // Temp Using
    //
    BYTE widePath[MAX_PATH * 8];
    ZeroMemory(widePath, MAX_PATH * 8);

    AdkBase64Decode(base64Str.c_str(), base64Str.length(), widePath, MAX_PATH * 8);

    std::wstring wideStr = (wchar_t *)widePath;
    return wideStr;
}
//---------------------------------------------------------------------------
char *GetStringFromWBase64(const char * base64)
{
    std::wstring wideStr = GetWideFromBase64(base64);

    BYTE *ansPath = (BYTE *)malloc(MAX_PATH * 8);
    ZeroMemory(ansPath, MAX_PATH * 8);

    int nRet = WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), wideStr.length(), (LPSTR)ansPath, MAX_PATH * 8, NULL, NULL);

    if (nRet == 0)
    {
        free(ansPath);
        return NULL;
    }

    return (char*)ansPath;
}
//---------------------------------------------------------------------------
std::string ConvertErrorIdToStr(int lastErrCode)
{
    std::string errStr;

    switch(lastErrCode)
    {
    case ERR_UNKNOWN:
        errStr = std::string("未知错误");
        break;

    case ERR_ACCESS_DENIED:
        errStr = std::string("拒绝访问");
        break;

    case ERR_PATH_INCORRECT:
        errStr = std::string("路径不正确");
        break;

    case ERR_NO_MEDIA_INDEVICE:
        errStr = std::string("设备中没有磁盘");
        break;
        
    case ERR_ALLOC_FAILED:
        errStr = std::string("内存分配出错");
        break;
        
    case ERR_TARGET_OFFLINE:
        errStr = std::string("目标不在线");
        break;
        
    case ERR_CONTRL_FILECONN_OFFLINE:
        errStr = std::string("控制端数据通信连接断开");
        break;
        
    case ERR_TARGET_FILECONN_OFFLINE:
        errStr = std::string("目标端数据通信连接断开");
        break;
        
    case ERR_TARGET_INEXIST:
        errStr = std::string("对应目标不存在");
        break;
        
    case ERR_PLUGIN_INEXIST:
        errStr = std::string("对应插件不存在");
        break;
        
    case ERR_PLUGIN_UPDATE_TYPE_INMATCH:
        errStr = std::string("插件更新类型不匹配");
        break;
        
    case ERR_FILE_TASK_INEXIST:
        errStr = std::string("文件传输任务不存在");
        break;
        
    case ERR_RED_EFS_FILE:
        errStr = std::string("EFS文件");
        break;
        
    case ERR_RED_FILE_OPEN:
        errStr = std::string("文件打开错误");
        break;

    case ERR_WRT_FILE_OPEN:
        errStr = std::string("文件打开错误");
        break;
        
    case ERR_RED_FILE_SEEK:
        errStr = std::string("文件定位不正确");
        break;

    case ERR_WRT_FILE_SEEK:
        errStr = std::string("文件定位不正确");
        break;
        
    case ERR_RED_FILE_READ:
        errStr = std::string("读文件出错");
        break;
        
    case ERR_WRT_FILE_WRITE:
        errStr = std::string("写文件出错");
        break;
        
    case ERR_DEL_FILE_SHARING_VIOLATION:
        errStr = std::string("文件被其它程序打开");
        break;
        
    case ERR_KJET_ACCESS_FAILED:
        errStr = std::string("插件不能访问主模块");
        break;
        
    case ERR_PLG_FILE_INEXIST:
        errStr = std::string("插件文件不存在");
        break;
        
    case ERR_PLG_LOAD_FAILED:
        errStr = std::string("加载插件失败");
        break;
        
    case ERR_PLG_UNLOAD_FAILED:
        errStr = std::string("卸载插件失败");
        break;       

    default:    // ERR_UNKNOWN
        errStr = std::string("未知错误");
        break;
    }

    return errStr;    
}
//---------------------------------------------------------------------------
std::wstring   ConvertErrorIdToStrW(int lastErrCode)
{
    std::string errorA = ConvertErrorIdToStr(lastErrCode);

	QString tmp = QString::fromLocal8Bit(errorA.c_str());
    
    return tmp.toStdWString(); 
}
//---------------------------------------------------------------------------
std::string ConvertTaskStatusToLangA(TaskStatus taskStatus)
{
    std::string lang;
    switch(taskStatus)
    {
    case WORKING:
        lang = std::string("进行");
        break;
    case PAUSED:
        lang = std::string("暂停");
        break;
	case CANCELED:
        lang = std::string("取消");
        break;
	case ERRORED:
        lang = std::string("出错");
        break;
	case FINISHED:
        lang= std::string("完成");
        break;
    }
    return lang;
}
//---------------------------------------------------------------------------
std::wstring ConvertTaskStatusToLangW(TaskStatus taskStatus)
{
    std::wstring lang;
    switch(taskStatus)
    {
    case WORKING:
        lang = std::wstring(L"进行");
        break;
    case PAUSED:
        lang = std::wstring(L"暂停");
        break;
	case PAUSEDBYNET:
		lang = std::wstring(L"暂停");
		break;
	case CANCELED:
        lang = std::wstring(L"取消");
        break;
	case ERRORED:
        lang = std::wstring(L"出错");
        break;
	case FINISHED:
        lang= std::wstring(L"完成");
        break;
    }
    return lang;
}
//---------------------------------------------------------------------------
TaskDirect ConvertStrToTaskDirect(std::string taskStr)
{
    if (taskStr == "DOW")
    {
        return FILEDOWN;
    }

    return FILEUP;
}
//---------------------------------------------------------------------------
char* ConvertTaskDirectToStr(TaskDirect taskDirect)
{
    if (taskDirect == FILEUP)
    {
        return "UPL";
    }

    return "DOW";
}
//---------------------------------------------------------------------------
std::wstring ConvertTaskDirectToLangW(TaskDirect taskDirect)
{
    if (taskDirect == FILEUP)
    {
        return std::wstring(L"上传");
    }

    return std::wstring(L"下载");
}
//---------------------------------------------------------------------------
std::string PathMergeA(std::string aniPrepPath, std::string aniSuffixPath)
{
    if (L'\\' == aniPrepPath[aniPrepPath.length()])
        return aniPrepPath + aniSuffixPath;
    else
        return aniPrepPath + "\\" + aniSuffixPath;
}
//---------------------------------------------------------------------------
std::wstring PathMergeW(std::wstring widPrepPath, std::wstring widSuffixPath)
{
    if (L'\\' == widPrepPath[widPrepPath.length()-1])
        return widPrepPath + widSuffixPath;
    else
        return widPrepPath + L"\\" + widSuffixPath;
}
//---------------------------------------------------------------------------
std::wstring GenerateLocalFileSavedPath(std::wstring widTarLocalPath,
                                      std::wstring widRemoteFilePath,
									  bool isMac)
{
	std::wstring widLocalFilePath;

	if ( isMac )
	{
		std::wstring widRemPath = QString::fromStdWString(widRemoteFilePath).replace('/', '\\').toStdWString();

		widLocalFilePath = widTarLocalPath + L"\\Disk" + widRemPath;
	}
	else
	{
		std::wstring widRemLogicDirver = std::wstring(L"Disk\\") + widRemoteFilePath.substr(0,1);
		std::wstring widRemPath = widRemoteFilePath.substr(3, widRemoteFilePath.length() - 3); 

		widLocalFilePath = PathMergeW(widTarLocalPath, widRemLogicDirver);
		widLocalFilePath = widLocalFilePath + L"\\" + widRemPath;
	}

    return widLocalFilePath;
}
//---------------------------------------------------------------------------
bool CheckAndCreateDirectory(const char *dirPath)
{
	if (INVALID_FILE_ATTRIBUTES == GetFileAttributesA(dirPath))
	{
		if (FALSE == CreateDirectoryA(dirPath,NULL))
		{
			return FALSE;
		}
	}
    
	return TRUE;
}
//---------------------------------------------------------------------------
int ReadDataFromLocalFile(FileTask  *fileTask,

                          ULONG      startPos,

                          char      *readBuf,

                          ULONG      dataLen,

                          int       *byteReaded)

{

    // startPos同时也说明了之前的都已经被中转缓存了

    //

    fileTask->dwDaemonedLen = startPos;

    

	if (NULL == fileTask->hFile || INVALID_HANDLE_VALUE == fileTask->hFile)

	{
		fileTask->hFile = CreateFileW(fileTask->ctrPathW.c_str(),
										GENERIC_READ, 
										FILE_SHARE_READ,
										NULL,
										OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL,
										NULL);

		int err = GetLastError();

		if (INVALID_HANDLE_VALUE == fileTask->hFile)
		{
			/*WCHAR errMsg[MAX_PATH] = {0};
			wsprintfW(errMsg, L"CreateFile Failed.\r\nErrorID : %d", err);
			MessageBoxW(NULL, errMsg, errMsg, MB_OK);*/
            fileTask->hFile = NULL;
			return ERR_WRT_FILE_OPEN;
		}
	}


	DWORD dwRet = SetFilePointer(fileTask->hFile, startPos, NULL, FILE_BEGIN);

	if (dwRet == INVALID_SET_FILE_POINTER)
	{
		/*WCHAR errMsg[MAX_PATH] = {0};
		wsprintfW(errMsg, L"SetFilePointer Failed.\r\nErrorID : %d", GetLastError());
		MessageBoxW(NULL, errMsg, errMsg, MB_OK);*/

        CloseHandle(fileTask->hFile);
        fileTask->hFile = NULL;    
		return ERR_WRT_FILE_SEEK;
	}

	DWORD dwByteReaded;
	if ( !ReadFile(fileTask->hFile, readBuf, dataLen, &dwByteReaded, NULL))
	{
		/*WCHAR errMsg[MAX_PATH] = {0};
		wsprintfW(errMsg, L"ReadFile Failed.\r\nErrorID : %d", GetLastError());
		MessageBoxW(NULL, errMsg, errMsg, MB_OK);*/

        CloseHandle(fileTask->hFile);
        fileTask->hFile = NULL;
		return ERR_RED_FILE_READ;
	}

	if (dwByteReaded == 0)
	{
		return ERR_RED_FILE_END;
	}


    if (byteReaded)

    {

        *byteReaded = dwByteReaded;

    }

    

    return 0;

}

//---------------------------------------------------------------------------
int SaveDataToLocalFile(FileTask    *fileTask,
                        ULONG       startPos,
                        const char  *data,
                        ULONG       dataLen)
{
    xASSERT((fileTask));
    
    if (NULL == fileTask->hFile || INVALID_HANDLE_VALUE == fileTask->hFile)

    {

        fileTask->hFile = CreateFileA(fileTask->aniTmpTaskPath.c_str(),

                                      GENERIC_ALL,

                                      FILE_SHARE_READ | FILE_SHARE_WRITE,

                                      NULL,

                                      OPEN_ALWAYS,

                                      FILE_ATTRIBUTE_NORMAL,

                                      NULL);


        if (INVALID_HANDLE_VALUE == fileTask->hFile)

        {

            fileTask->hFile = NULL;

            return ERR_WRT_FILE_OPEN;

        }

    }


    if (dataLen == 0)

    {

        return 0;

    }

    

    DWORD dwRet = SetFilePointer(fileTask->hFile, startPos, NULL, FILE_BEGIN);

	if (dwRet == INVALID_SET_FILE_POINTER)
	{
        CloseHandle(fileTask->hFile);
        fileTask->hFile = NULL;
		return ERR_WRT_FILE_SEEK;
	}

	DWORD dwByteWritten = 0;
	if ( ! WriteFile(fileTask->hFile, data, dataLen, &dwByteWritten, NULL))
	{
        CloseHandle(fileTask->hFile);
        fileTask->hFile = NULL;    
		return ERR_WRT_FILE_WRITE;
	}


    // 这里都是已经完成的
    //
    fileTask->dwFinishedLen += dwByteWritten;
    return 0;
}

//---------------------------------------------------------------------------

std::string __fastcall GenerateLogicStr(LONG unitmask)
{
    std::string logicStr = "";
	char driverVolume;
	for (driverVolume = 'A'; driverVolume <= 'Z'; driverVolume++)
	{
		if (unitmask & 0x1)
		{
			logicStr = logicStr + driverVolume + ":\\ ; ";
		}
		unitmask = unitmask >> 1;
	}

    return logicStr;
}
//---------------------------------------------------------------------------

DpapiType ConvertStrToDpapiType(std::string dpapiStr)
{
    DpapiType dType = IMS;

    if ("ATO" == dpapiStr)
    {
        dType = IEAUTO;
    }
    else if ("PAS" == dpapiStr)
    {
        dType = IEPASS;
    }
    else if ("EMA" == dpapiStr)
    {
        dType = EMAIL;
    }

    return dType;
}

//---------------------------------------------------------------------------
PCHAR ConvertDpapiTypeToLang(DpapiType dType)
{
    switch(dType)
    {
    case IEAUTO:
        return "IE自动完成";

    case IEPASS:
        return "IE密码保护";

    case EMAIL:
        return "保存的即时通信帐号";

    case IMS:
        return "保存的邮件帐号";
    }

    return NULL;
}
//---------------------------------------------------------------------------
PWCHAR ConvertDpapiTypeToLangW(DpapiType dType)
{
    switch(dType)
    {
    case IEAUTO:
        return L"IE自动完成";

    case IEPASS:
        return L"IE密码保护";

    case EMAIL:
        return L"保存的即时通信帐号";

    case IMS:
        return L"保存的邮件帐号";
    }

    return NULL;
}
//---------------------------------------------------------------------------
std::string  ConvertPluginIdToLang(ULONG pid)
{
    std::string lang = "";

    switch(pid)
    {
    case PLUGIN_ZERO:
        lang = std::string("驻留插件");
        break;
    case PLUGIN_ONE:
        lang = std::string("主功能插件");
        break;
    case PLUGIN_TWO:
        lang = std::string("用户行为监控插件");
        break;
    case PLUGIN_THREE:
        lang = std::string("USB文件密取插件");
        break;
    case PLUGIN_FOUR:
        lang = std::string("多媒体插件");
        break;
    case PLUGIN_FIVE:
        lang = std::string("音视频监控插件");
        break;
    }
                
    return lang;
}
//---------------------------------------------------------------------------
std::wstring  ConvertPluginIdToLangW(ULONG pid)
{
    std::wstring lang = L"";
    
    switch(pid)
    {
    case PLUGIN_ZERO:
        lang = std::wstring(L"驻留插件");
        break;
    case PLUGIN_ONE:
        lang = std::wstring(L"主功能插件");
        break;
    case PLUGIN_TWO:
        lang = std::wstring(L"用户行为监控插件");
        break;
    case PLUGIN_THREE:
        lang = std::wstring(L"USB文件密取插件");
        break;
    case PLUGIN_FOUR:
        lang = std::wstring(L"屏幕监控插件");
        break;
    case PLUGIN_FIVE:
        lang = std::wstring(L"音视频监控插件");
        break;
    }
    
    return lang;
}
//---------------------------------------------------------------------------

std::string ConvertFileOpTypeToStr(FileOpType opType)
{
    std::string type;

    switch(opType)
    {
    case FO_CREATEFILE:
        type = std::string("新建文件");
        break;

    case FO_OPENFILE:
        type = std::string("打开文件");
        break;

    case FO_DELETEFILE:
        type = std::string("删除文件");
        break;

    case FO_MOVEFILE:
        type = std::string("移动文件");
        break;

    case FO_COPYFILE:
        type = std::string("拷贝文件");
        break;

    case FO_CREATEDIRECTORY:
        type = std::string("新建目录");
        break;

    case FO_REMOVEDIRECTORY:
        type = std::string("删除目录");
        break;
    }

    return type;
}

//---------------------------------------------------------------------------

std::string ConvertDiskTypeToStr(UINT diskType)
{
    std::string type;

    switch(diskType)
    {
    case 0:         // DRIVE_UNKNOWN
        type = std::string("未知设备");
        break;

    case 1:         // DRIVE_NO_ROOT_DIR
        type = std::string("无根目录设备");
        break;

    case 2:         // DRIVER_REMOVABLE
        type = std::string("移动存储");
        break;

    case 3:         // DRIVE_FIXED
        type = std::string("数据磁盘");
        break;

    case 4:         // DRIVE_REMOTE
        type = std::string("网络镜像");
        break;

    case 5:         // DRIVE_CDROM
        type = std::string("光盘存储");
        break;

    case 6:         // DRIVE_RAMDISK
        type = std::string("RAM介质");
        break;
    }

    return type;
}

//---------------------------------------------------------------------------
std::wstring __fastcall CreateSubSimulateDir(std::wstring widSimulatePath,
                                           std::wstring widTarRealpath,
										   bool bMac)
{
    LPCWSTR lpDriver = widTarRealpath.c_str();

    // 创建盘符对应的目录
    //

	std::wstring widLogicPath;
	if ( bMac )
	{
		widLogicPath = widSimulatePath;
	}
	else
	{
		widLogicPath = PathMergeW(widSimulatePath, widTarRealpath.substr(0, 1));
	}

    CreateDirectoryW(widLogicPath.c_str(), NULL);

	std::wstring widPath = widLogicPath;
	LPCWSTR lpwzPath = NULL;

	if ( bMac )
	{
		lpwzPath = lpDriver;
		LPCWSTR lpwzNext = wcschr(lpwzPath+1, L'/');

		while(lpwzNext)
		{
			int index = lpwzPath - lpDriver;
			int count = lpwzNext - lpwzPath;

			widPath = widPath + std::wstring(L"\\") + widTarRealpath.substr(index+1, count-1);         // widPath 前面有, 后面没有        
			CreateDirectoryW(widPath.c_str(), NULL);

			lpwzPath = lpwzNext;
			lpwzNext = wcschr(lpwzPath+1, L'/');        
		}
	}
	else
	{
		lpwzPath = lpDriver + 2;
		LPCWSTR lpwzNext = wcschr(lpwzPath+1, L'\\');

		while(lpwzNext)
		{
			int index = lpwzPath - lpDriver;
			int count = lpwzNext - lpwzPath;

			widPath = widPath + widTarRealpath.substr(index, count);         // widPath 前面有, 后面没有        
			CreateDirectoryW(widPath.c_str(), NULL);

			lpwzPath = lpwzNext;
			lpwzNext = wcschr(lpwzPath+1, L'\\');        
		}
	}

    // 把最后的文件名也加到路径上
    //
    return std::wstring(widPath);
}
//---------------------------------------------------------------------------
VOID FreePluginCxt(PPLUGIN_CXT lpPluginCxt)
{
	if (lpPluginCxt->lpszPluginName)
	{
		free(lpPluginCxt->lpszPluginName);
	}

	if (lpPluginCxt->lpszProcList)
	{
		free(lpPluginCxt->lpszProcList);
	}

	if (lpPluginCxt->lpbyData)
	{
		free(lpPluginCxt->lpbyData);
	}

	free(lpPluginCxt);
}


//
// 新增
//

// 获取当前时间字符串
std::string TGetCurrentTime()
{
	return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
}

// string -> wstring
std::wstring AnsiToWide(std::string str)
{
	WCHAR tmp[1024] = {0};

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, tmp, 1024);

	return std::wstring(tmp);
}

// wstring -> string
std::string WideToAnsi(std::wstring wstr)
{
	char tmp[1024] = {0};

	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, tmp, 1024, NULL, NULL);

	return std::string(tmp);
}

//---------------------------------------------------------------------------
std::wstring PathMergeMac(std::wstring widPrepPath, std::wstring widSuffixPath)
{
	if (L'/' == widPrepPath[widPrepPath.length()-1])
		return widPrepPath + widSuffixPath;
	else
		return widPrepPath + L"/" + widSuffixPath;
}

const wchar_t * ExtractFileNameMac(const wchar_t *lpwzPath)
{
	const wchar_t* lpwzName = wcsrchr(lpwzPath, L'/');
	if (lpwzName)
	{
		lpwzName++;
	}

	return lpwzName;
}

std::string GetPhoneNumberPrefix(std::string number)
{
	unsigned int startpos = number.find("(");
	number = number.substr(startpos+1, number.length()-2);

	unsigned int pos = number.find("+86");

	if ( pos != std::string::npos )
	{
		number = number.substr(3, number.length()-1);
	}

	if ( number.length() < 7 )
	{
		return "1234567";
	}

	return number.substr(0, 7);
}

std::wstring GetExePath()
{
	WCHAR wzExePath[MAX_PATH] = {0};
	GetModuleFileNameW(0, wzExePath, MAX_PATH);
	LPWSTR wzName = wcsrchr(wzExePath, L'\\');
	wcscpy(wzName, L"");

	return std::wstring(wzExePath);
}

bool SHCopy(LPCWSTR from, LPCWSTR to)
{
	//Log(_T("Recursive file copy from %s to %s"), from, to);

	SHFILEOPSTRUCT fileOp = {0};
	fileOp.wFunc = FO_COPY;
	TCHAR newFrom[MAX_PATH];
	wcscpy(newFrom, from);
	newFrom[wcslen(from) + 1] = NULL;
	fileOp.pFrom = newFrom;
	WCHAR newTo[MAX_PATH];
	wcscpy(newTo, to);
	newTo[wcslen(to) + 1] = NULL;
	fileOp.pTo = newTo;
	fileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;

	int result = SHFileOperation(&fileOp);

	//Log(_T("SHFileOperation return code: 0x%x"), result);

	return result == 0;
}

bool SHDel(LPCWSTR dir)
{
	WCHAR wzTemp[MAX_PATH] = {0};
	wcscpy(wzTemp, dir);
	SHFILEOPSTRUCTW FileOp;
	FileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI;
	FileOp.pFrom = wzTemp;
	FileOp.pTo = NULL;
	FileOp.wFunc = FO_DELETE;
	int result = SHFileOperationW(&FileOp);
	return result == 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// 从文件名得到图标
//
HICON GetIconFromFileName(LPCWSTR wzFileName)
{
	SHFILEINFOW sfi;
	LPCWSTR lpwzExt = wcsrchr(wzFileName, L'.');
	if (lpwzExt)
	{
		SHGetFileInfoW(lpwzExt,
			0,    //FILE_ATTRIBUTE_NORMAL,
			&sfi,
			sizeof(sfi),
			SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_TYPENAME);
	}
	else
	{
		SHGetFileInfoW(wzFileName,
			0,    //FILE_ATTRIBUTE_NORMAL,
			&sfi,
			sizeof(sfi),
			SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_TYPENAME);            
	}

	return sfi.hIcon;
}

// ////////////////////////////////////////////////////////////////////////////////
// 仅从路径判断指定文件是否在文件夹内
//
bool FileInDir(const std::wstring& filePath, const std::wstring& dirPath)
{
	if ( dirPath >= filePath )
	{
		return false;
	}

	int index = filePath.find(dirPath, 0);

	if ( 0 == index )
	{
		if ( L'/' == filePath[dirPath.length()] || L'\\' == filePath[dirPath.length()] )
		{
			return true;
		}
	}

	return false;
}

// ////////////////////////////////////////////////////////////////////////////////
// 从路径得到文件名
//
std::wstring GetNameFromPath(std::wstring path, WCHAR dot)
{
	LPCWSTR wzName = wcsrchr(path.c_str(), dot)+1;

	return std::wstring(wzName);
}

// ////////////////////////////////////////////////////////////////////////////////
// 获取时间字符串
//
std::wstring GetTimeFromLongLong(LONGLONG time)
{
	SYSTEMTIME  systime;
	FILETIME    local;
	FileTimeToLocalFileTime((FILETIME*)&time, &local);
	FileTimeToSystemTime(&local,&systime);
	WCHAR wzTime[MAX_PATH] = {0};
	wsprintf(wzTime, L"%.4d-%.2d-%.2d %.2d:%.2d", systime.wYear,systime.wMonth,
		systime.wDay ,systime.wHour ,systime.wMinute);

	return std::wstring(wzTime);
}

// ////////////////////////////////////////////////////////////////////////////////
// 将整型变量写入配置文件
//
void WritePolicyToLocal(LPCWSTR wzSection, 
								   LPCWSTR wzKey, 
								   ULONG nValue, 
								   LPCWSTR wzIniPath)
{
	WCHAR wzValue[MAX_PATH] = {0};
	wsprintf(wzValue, L"%d", nValue);
	WritePrivateProfileStringW(wzSection, wzKey, wzValue, wzIniPath);
}

// ////////////////////////////////////////////////////////////////////////////////
// 从配置文件中读出整型变量
//
ULONG ReadValueFromLocal(LPCWSTR wzSection, LPCWSTR wzKey, LPCWSTR wzIniPath)
{
	return GetPrivateProfileIntW(wzSection, wzKey, 0, wzIniPath);
}

// ////////////////////////////////////////////////////////////////////////////////
// 从配置文件中读出字符串
//
std::wstring ReadStringPolicyFromLocal(LPCWSTR wzSection, LPCWSTR wzKey, LPCWSTR wzIniPath)
{
	WCHAR wzString[MAX_PATH] = {0};
	GetPrivateProfileStringW(wzSection, wzKey, L"", wzString, MAX_PATH, wzIniPath);

	return std::wstring(wzString);
}

// ////////////////////////////////////////////////////////////////////////////////
// 将字符串写入配置文件
//
void WriteStringPolicyToLocal(LPCWSTR wzSection, LPCWSTR wzKey, LPCWSTR value, LPCWSTR wzIniPath)
{
	WCHAR wzString[MAX_PATH] = {0};
	WritePrivateProfileStringW(wzSection, wzKey, value, wzIniPath);
}

// ////////////////////////////////////////////////////////////////////////////////
// 获取系统类型
//
SystemType GetSystemType( DWORD dwOsBuildNumber )
{
	dwOsBuildNumber &= 0xEFFFFFFF;
	if ( dwOsBuildNumber == OS_WIN2K
		|| dwOsBuildNumber == OS_WINXP
		|| dwOsBuildNumber == OS_WIN2003
		|| dwOsBuildNumber == OS_WINVISTA
		|| dwOsBuildNumber == OS_WIN2008
		|| dwOsBuildNumber == OS_WINVISTASP2
		|| dwOsBuildNumber == OS_WIN7PRO
		|| dwOsBuildNumber == OS_WIN7SP1
		|| dwOsBuildNumber == OS_WIN8
		|| dwOsBuildNumber == OS_WIN81
		|| dwOsBuildNumber == OS_WIN8_PREVIEW )
	{
		return SYSTEM_WINDOWS;
	}
	else if ( dwOsBuildNumber  == MACOS_X_VERSION_10_4
		|| dwOsBuildNumber  == MACOS_X_VERSION_10_6
		|| dwOsBuildNumber == MACOS_X_VERSION_10_7
		|| dwOsBuildNumber == MACOS_X_VERSION_10_8
		|| dwOsBuildNumber == MACOS_X_VERSION_10_9
		|| dwOsBuildNumber == MACOS_X_VERSION_10_10 )
	{
		return SYSTEM_MACOSX;
	}
	else if ( dwOsBuildNumber == IOS_VERSION_1
		|| dwOsBuildNumber == IOS_VERSION_2
		|| dwOsBuildNumber == IOS_VERSION_3
		|| dwOsBuildNumber == IOS_VERSION_4
		|| dwOsBuildNumber == IOS_VERSION_5
		|| dwOsBuildNumber == IOS_VERSION_6
		|| dwOsBuildNumber == IOS_VERSION_7
		|| dwOsBuildNumber == IOS_VERSION_8)
	{
		return SYSTEM_IOS;
	}
	else if ( dwOsBuildNumber == ANDROID_2_0_VERSION 
		|| dwOsBuildNumber == ANDROID_2_1_VERSION 
		|| dwOsBuildNumber == ANDROID_2_2_VERSION
		|| dwOsBuildNumber == ANDROID_2_3_VERSION
		|| dwOsBuildNumber == ANDROID_4_0_VERSION 
		|| dwOsBuildNumber == ANDROID_4_1_VERSION
		|| dwOsBuildNumber == ANDROID_4_2_VERSION
		|| dwOsBuildNumber == ANDROID_4_3_VERSION
		|| dwOsBuildNumber == ANDROID_4_4_VERSION
		|| dwOsBuildNumber == ANDROID_5_0_VERSION
		|| dwOsBuildNumber == ANDROID_5_1_VERSION
		|| dwOsBuildNumber == ANDROID_5_2_VERSION)
	{
		return SYSTEM_ANDROID;
	}
	else
	{
		return SYSTEM_UNKNOWN;
	}
}

BOOL UnixLike( Target* tar )
{
	return ( tar->m_sysType != SYSTEM_WINDOWS );
}

BOOL MobileDevice( Target* tar )
{
	return ( tar->m_sysType != SYSTEM_WINDOWS && tar->m_sysType != SYSTEM_MACOSX );
}
