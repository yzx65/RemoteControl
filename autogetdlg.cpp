#include "autogetdlg.h"

#include "target.h"
#include "DatabaseManager.h"

#include "maindlg.h"
#include "Utility.h"

AutoGetDlg::AutoGetDlg(Target* tar)
	: QDialog(0)
	, m_tar(tar)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	//int oldDepth = DM->QueryTargetAutoGetStatus(tar->dwTargetID);
	std::wstring iniPath = GetExePath() + L"\\setting.ini";
	std::wstring oldDepth = ReadStringPolicyFromLocal(L"Control", L"AutoGetDirInfo", iniPath.c_str());

	if ( L"-1" == oldDepth )
		ui.chkAutoGet->setChecked(false);
	else
	{
		ui.chkAutoGet->setChecked(true);
		ui.spnDepth->setValue(_wtoi(oldDepth.c_str()));
		if ( L"0" == oldDepth )
			ui.chkFullDepth->setChecked(true);
		else
			ui.chkFullDepth->setChecked(false);
	}

	connect(ui.chkAutoGet, SIGNAL(clicked()), this, SLOT(OnChkAutoGetClicked()));
	connect(ui.btnOK, SIGNAL(clicked()), this,SLOT(OnOK()));
	OnChkAutoGetClicked();

	InitCustomText(this);
}

AutoGetDlg::~AutoGetDlg()
{

}

void AutoGetDlg::OnChkAutoGetClicked()
{
	if ( ui.chkAutoGet->isChecked() )
	{
		ui.frmDetail->show();
	}
	else
	{
		ui.frmDetail->hide();
	}

	this->adjustSize();
}

void AutoGetDlg::OnOK()
{
	int depth = -1;

	if ( ui.chkAutoGet->isChecked() )
	{
		if ( ui.chkFullDepth->isChecked() )
			depth = 0;
		else
			depth = ui.spnDepth->value();
	}

	//m_tar->m_autoGetDirInfoDepth = depth;
	//DM->UpdateTargetAutoGetStatus(m_tar->dwTargetID, depth);
	WCHAR value[256] = {0};
	wsprintfW(value, L"%d", depth);

	std::wstring iniPath = GetExePath() + L"\\setting.ini";
	WriteStringPolicyToLocal(L"Control", L"AutoGetDirInfo", value, iniPath.c_str());

	m_tar->tarConn->Send_AGT(0, FILEDOWN, GetBase64FromAnsi("/").c_str(), depth, 0);

	accept();
}