#include "configdlg.h"
#include "maindlg.h"

#include <QtGui>
#include "Utility.h"

ConfigDlg::ConfigDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	m_setting = GetExePath() + L"\\setting.ini";

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnOK()));

	InitDataBaseType();
	InitAutoConnect();
	InitAutoGet();
	InitDirInfoPolicy();
	InitAdvanceMonitorPolicy();
}

ConfigDlg::~ConfigDlg()
{

}

void ConfigDlg::InitDataBaseType()
{
	QButtonGroup* group = new QButtonGroup(this);
	group->addButton(ui.btnAccess);
	group->addButton(ui.btnSQLServer);
	std::wstring database = ReadStringPolicyFromLocal(L"Database", L"Type", m_setting.c_str());

	if ( database == L"Access" )
		ui.btnAccess->setChecked(true);
	else
		ui.btnSQLServer->setChecked(true);
}

void ConfigDlg::InitAutoConnect()
{
	int autoLogin = ReadValueFromLocal(L"Control", L"AutoLogin", m_setting.c_str());

	if ( autoLogin )
		ui.chkAutoConnect->setChecked(true);
	else
		ui.chkAutoConnect->setChecked(false);
}

void ConfigDlg::InitAutoGet()
{
	if ( FrmMain->ctrOnlineFlag )
	{
		std::wstring level = ReadStringPolicyFromLocal(L"Control", L"AutoGetDirInfo", m_setting.c_str());
		if ( L"-1" == level )
			ui.chkAutoGet->setChecked(false);
		else
		{
			ui.chkAutoGet->setChecked(true);

			if ( L"0" == level )
				ui.chkAutoGetAll->setChecked(true);

			ui.spnAutoGetLevel->setValue(_wtoi(level.c_str()));
		}
	}
	else
	{
		ui.frmAutoGet->hide();
		this->adjustSize();
	}
}

void ConfigDlg::InitDirInfoPolicy()
{
	QButtonGroup* group = new QButtonGroup(this);
	group->addButton(ui.btnReadDirInfoFromDb);
	group->addButton(ui.btnReadDirInfoFromTarget);

	int fromDb = ReadValueFromLocal(L"Control", L"ReadDirInfoFromDb", m_setting.c_str());

	if ( fromDb )
		ui.btnReadDirInfoFromDb->setChecked(true);
	else
		ui.btnReadDirInfoFromTarget->setChecked(true);
}

void ConfigDlg::InitAdvanceMonitorPolicy()
{
	QButtonGroup* group = new QButtonGroup(this);
	group->addButton(ui.btnDownloadAuto);
	group->addButton(ui.btnAskBeforeDownload);
	group->addButton(ui.btnDisableDownload);

	// 0 - Auto download
	// 1 - Ask before download
	// 2 - Disable download
	int download = ReadValueFromLocal(L"Control", L"AdvanceMonitorPolicy", m_setting.c_str());

	if ( 0 == download )
		ui.btnDownloadAuto->setChecked(true);
	else if ( 1 == download )
		ui.btnAskBeforeDownload->setChecked(true);
	else
		ui.btnDisableDownload->setChecked(true);
}

void ConfigDlg::OnOK()
{
	ApplyDataBaseType();
	ApplyAutoConnect();
	ApplyAutoGet();
	ApplyDirInfoPolicy();
	ApplyAdvanceMonitorPolicy();
	accept();
}

void ConfigDlg::ApplyDataBaseType()
{
	if ( ui.btnAccess->isChecked() )
		WriteStringPolicyToLocal(L"Database", L"Type", L"Access", m_setting.c_str());
	else
		WriteStringPolicyToLocal(L"Database", L"Type", L"SQL Server", m_setting.c_str());
}

void ConfigDlg::ApplyAutoConnect()
{
	if ( ui.chkAutoConnect->isChecked() )
		WritePolicyToLocal(L"Control", L"AutoLogin", 1, m_setting.c_str());
	else
		WritePolicyToLocal(L"Control", L"AutoLogin", 0, m_setting.c_str());
}

void ConfigDlg::ApplyAutoGet()
{
	if ( FrmMain->ctrOnlineFlag )
	{
		int depth = -1;

		if ( ui.chkAutoGet->isChecked() )
		{
			if ( ui.chkAutoGetAll->isChecked() )
				depth = 0;
			else
				depth = ui.spnAutoGetLevel->value();
		}

		WCHAR value[256] = {0};
		wsprintfW(value, L"%d", depth);
		WriteStringPolicyToLocal(L"Control", L"AutoGetDirInfo", value, m_setting.c_str());
		FrmMain->ctrConn->Send_AGT(0, FILEDOWN, GetBase64FromAnsi("/").c_str(), depth, 0);
	}
}

void ConfigDlg::ApplyDirInfoPolicy()
{
	if ( ui.btnReadDirInfoFromDb->isChecked() )
		WritePolicyToLocal(L"Control", L"ReadDirInfoFromDb", 1, m_setting.c_str());
	else
		WritePolicyToLocal(L"Control", L"ReadDirInfoFromDb", 0, m_setting.c_str());
}

void ConfigDlg::ApplyAdvanceMonitorPolicy()
{
	int download = 0;

	if ( ui.btnDownloadAuto->isChecked() )
		download = 0;

	if ( ui.btnAskBeforeDownload->isChecked() )
		download = 1;

	if ( ui.btnDisableDownload->isChecked() )
		download = 2;

	WritePolicyToLocal(L"Control", L"AdvanceMonitorPolicy", download, m_setting.c_str());
}
