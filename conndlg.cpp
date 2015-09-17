#include "conndlg.h"
#include "Utility.h"
#include <Windows.h>
#include <algorithm>

// ////////////////////////////////////////////////////////////////////////////////
// 构造函数
//
ConnDlg::ConnDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

	QValidator* ipMask = new QRegExpValidator(QRegExp("[0-9,\\.]+"));
	ui.edtIP->setValidator(ipMask);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnClickOk()));
	//connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(OnClickCancel()));

	InitCustomText(this);
	ui.frmCtrlPort->hide();
}

// ////////////////////////////////////////////////////////////////////////////////
// 析构函数
//
ConnDlg::~ConnDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 取 Ip 地址
//
QString ConnDlg::GetIpAddress()
{
	return ui.edtIP->currentText();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 取 ctrl connection 端口号
//
QString ConnDlg::GetCtrlPort()
{
	return ui.edtCtrlPort->text();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 取 target connection 端口号
//
QString ConnDlg::GetTargetPort()
{
	return ui.edtTargetPort->text();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 取验证码
//
QString ConnDlg::GetPass()
{
	return ui.edtPass->text();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 是否自动保存 
//
bool ConnDlg::IsAutoConn()
{
	return ui.chkAutoConn->isChecked();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置 ip 地址
//
void ConnDlg::SetIpAddress(QString ipAddress)
{
	ui.edtIP->lineEdit()->setText(ipAddress);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置 ctrl connection 端口号
//
void ConnDlg::SetCtrlPort(QString port)
{
	ui.edtCtrlPort->setText(port);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置 target connection 端口号
//
void ConnDlg::SetTargetPort(QString port)
{
	ui.edtTargetPort->setText(port);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置验证码
//
void ConnDlg::SetPass(QString pass)
{
	ui.edtPass->setText(pass);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置自动登录
//
void ConnDlg::SetAutoConn(bool autoConn)
{
	ui.chkAutoConn->setChecked(autoConn);
}


// ////////////////////////////////////////////////////////////////////////////////
// @private slot 连接
//
void ConnDlg::OnClickOk()
{
	accept();
}

void ConnDlg::GetDaemonHistory()
{
	while ( 0 != ui.edtIP->count())
		ui.edtIP->removeItem(0);

	m_daemonHistory.clear();

	std::wstring iniPath = GetExePath() + L"\\setting.ini";

	std::wstring ip;
	WCHAR key[256] = {0};
	
	for ( int i = 1; i <= 5; ++i )
	{
		wsprintf(key, L"DaemonIp%d", i);
		std::wstring ip = ReadStringPolicyFromLocal(L"DaemonHistory", key, iniPath.c_str());

		if ( ip != L"" )
		{
			m_daemonHistory.push_back(ip);
			ui.edtIP->addItem(QString::fromStdWString(ip));
		}
		else
			break;
	}
}

void ConnDlg::ApplyDaemonHistory()
{
	std::list<std::wstring>::iterator result =
		std::find(m_daemonHistory.begin(), m_daemonHistory.end(), ui.edtIP->currentText().toStdWString());

	if ( m_daemonHistory.end() != 
		result )
	{
		std::wstring temp(*result);
		m_daemonHistory.erase(result);
		m_daemonHistory.push_front(temp);
	}
	else
	{
		if ( m_daemonHistory.size() > 5 )
		{
			m_daemonHistory.pop_back();
		}

		m_daemonHistory.push_front(ui.edtIP->currentText().toStdWString());
	}

	std::wstring iniPath = GetExePath() + L"\\setting.ini";

	int i = 1;
	WCHAR key[256] = {0};

	for ( std::list<std::wstring>::iterator it = m_daemonHistory.begin();
		it != m_daemonHistory.end() && i <= 5;
		++it, ++i )
	{
		wsprintf(key, L"DaemonIp%d", i);
		WriteStringPolicyToLocal(L"DaemonHistory", key, it->c_str(), iniPath.c_str());
	}
}
