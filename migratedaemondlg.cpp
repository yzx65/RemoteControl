#include "MigrateDaemonDlg.h"
#include <Windows.h>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include "include/T5.h"

#include "maindlg.h"

MigrateDaemonDlg::MigrateDaemonDlg(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	m_ipMask = new QRegExpValidator(QRegExp("[0-9,\\.]+"));
	ui.edtIP->setValidator(m_ipMask);
	ui.edtIP2->setValidator(m_ipMask);
	QIntValidator* portMask = new QIntValidator(0, 65535);
	ui.edtPort->setValidator(portMask);
	ui.edtPort2->setValidator(portMask);

	connect(ui.cmbIP, SIGNAL(currentIndexChanged(int)), this, SLOT(ServerTypeChanged_1(int)));
	connect(ui.cmbIP2, SIGNAL(currentIndexChanged(int)), this, SLOT(ServerTypeChanged_2(int)));
	connect(ui.btnAnalyze, SIGNAL(clicked()), this, SLOT(GetIP()));
	connect(ui.btnAnalyze2, SIGNAL(clicked()), this, SLOT(GetIP()));
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(StartMigration()));
}

MigrateDaemonDlg::~MigrateDaemonDlg()
{
	delete m_ipMask;
}


void MigrateDaemonDlg::ServerTypeChanged_1(int index)
{
	ui.edtIP->clear();
	ui.edtIP->setValidator( index ? NULL : m_ipMask);
	ui.btnAnalyze->setEnabled( index ? true : false);
}

void MigrateDaemonDlg::ServerTypeChanged_2(int index)
{
	ui.edtIP2->clear();
	ui.edtIP2->setValidator( index ? NULL : m_ipMask);
	ui.btnAnalyze2->setEnabled( index ? true : false);
}

void MigrateDaemonDlg::GetIP()
{
	QLineEdit* edtIP = sender()->objectName() == "btnAnalyze" ? ui.edtIP : ui.edtIP2;

	DWORD addr = inet_addr(edtIP->text().toStdString().c_str());

	if (INADDR_NONE != addr)
	{
		MessageBoxA(NULL, "主中转服务器输入地址不是域名格式!", "提示", MB_OK | MB_ICONINFORMATION);
		return;
	}

	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags    = AI_CANONNAME;
	hints.ai_family   = AF_INET;      // only support IPv4
	hints.ai_socktype = SOCK_STREAM;  // only support TCP
	hints.ai_protocol = IPPROTO_TCP;  // TCP protocol

	int iRes = getaddrinfo(edtIP->text().toStdString().c_str(), NULL, &hints, &res);

	if ( iRes == 0 )
	{
		struct sockaddr_in *inaddr = (struct sockaddr_in *)(res->ai_addr);
		char text[512] = {0};
		sprintf(text, "域名:%s\nIP地址:%s", edtIP->text().toStdString().c_str(), inet_ntoa(inaddr->sin_addr));
		MessageBoxA(NULL, text, "提示", MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBoxA(NULL, "域名解析失败,无法获知其对应IP地址", "提示", MB_OK | MB_ICONINFORMATION);
	}
}

void MigrateDaemonDlg::StartMigration()
{
	DAEMONADDR  daemonAddr1;
	DAEMONADDR  daemonAddr2;

	ZeroMemory(daemonAddr1.szDomainName, 64);
	ZeroMemory(daemonAddr2.szDomainName, 64);

	daemonAddr1.dwIp    = 0;
	daemonAddr1.dwPort  = 0;
	daemonAddr2.dwIp    = 0;
	daemonAddr2.dwPort  = 0;

	daemonAddr1.dwAddrType = ui.cmbIP->currentIndex();
	if ( daemonAddr1.dwAddrType == 0 )
	{
		// IP地址
		//
		daemonAddr1.dwIp = inet_addr(ui.edtIP->text().toStdString().c_str());

		if (INADDR_NONE == daemonAddr1.dwIp || 0 == ui.edtIP->text().length() )
		{
			MessageBoxA((HWND)winId(), "主中转服务器地址输入不正确!", "提示", MB_OK | MB_ICONINFORMATION);
			return;
		}
	}
	else
	{
		// 域名
		//
		DWORD dwAddr = inet_addr(ui.edtIP->text().toStdString().c_str());
		if (INADDR_NONE != dwAddr)
		{
			MessageBoxA((HWND)winId(), "主中转服务器输入地址不是域名格式!", "提示", MB_OK | MB_ICONINFORMATION);
			return;
		}

		strcpy(daemonAddr1.szDomainName, ui.edtIP->text().toStdString().c_str());
	}

	long port = ui.edtPort->text().toInt();

	if (INADDR_NONE == port)
	{
		MessageBoxA((HWND)winId(), "主中转反弹端口输入不正确!", "提示", MB_OK | MB_ICONINFORMATION);
		return;
	}

	daemonAddr1.dwPort = port;

	//
	// 备用中转参数
	//
	if ( ui.grpExtra->isChecked() )
	{
		daemonAddr2.dwAddrType = ui.cmbIP2->currentIndex();

		if ( daemonAddr2.dwAddrType == 0 )
		{
			// IP地址
			//
			daemonAddr2.dwIp = inet_addr(ui.edtIP2->text().toStdString().c_str());

			if (INADDR_NONE == daemonAddr2.dwIp || 0 == ui.edtIP2->text().length())
			{
				MessageBoxA((HWND)winId(), "备用中转服务器地址输入不正确!", "提示", MB_OK | MB_ICONINFORMATION);
				return;
			}
		}
		else
		{
			// 域名
			//
			DWORD dwAddr = inet_addr(ui.edtIP2->text().toStdString().c_str());
			if (INADDR_NONE != dwAddr)
			{
				MessageBoxA((HWND)winId(), "备用中转服务器输入地址不是域名格式!", "提示", MB_OK | MB_ICONINFORMATION);
				return;
			}

			strcpy(daemonAddr2.szDomainName, ui.edtIP2->text().toStdString().c_str());
		}

		port = ui.edtPort2->text().toInt();

		if (INADDR_NONE == port)
		{
			MessageBoxA((HWND)winId(), "备用中转反弹端口输入不正确!", "提示", MB_OK | MB_ICONINFORMATION);
			return;
		}

		daemonAddr2.dwPort = port;
	}

	BYTE byData[512] = {0};
	DWORD dwSize = sizeof(DAEMONADDR);
	memcpy(byData, &daemonAddr1, sizeof(DAEMONADDR));
	if ( ui.grpExtra->isChecked() )
	{
		memcpy(byData + dwSize, &daemonAddr2, sizeof(DAEMONADDR));
		dwSize += sizeof(DAEMONADDR);
	}

	FrmMain->ctrConn->Send_SDA(byData, dwSize);
	m_newDaemonAddress = ui.edtIP->text().toStdWString();
	accept();
}