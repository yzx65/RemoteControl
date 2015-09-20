#include <Windows.h>
#include <tchar.h>
#include <QtGui>
#include <QFileDialog>

#include "generatetardlg.h"
#include "Pakage.h"
#include "Utility.h"

const wchar_t* SysPath_x86 = L"\\InitiativeTarget\\DrvFltIp_x86.sys";
const wchar_t* SysPath_Temp_x86 = L"\\InitiativeTarget\\Temp\\DrvFltIp_x86.sys";
const wchar_t* DllPath_x86 = L"\\InitiativeTarget\\1.x86.dll";
const wchar_t* DllPath_Temp_x86 = L"\\InitiativeTarget\\Temp\\1.x86.dll";
const wchar_t* SysPath_x64 = L"\\InitiativeTarget\\DrvFltIp_x64.sys";
const wchar_t* SysPath_Temp_x64 = L"\\InitiativeTarget\\Temp\\DrvFltIp_x64.sys";
const wchar_t* DllPath_x64 = L"\\InitiativeTarget\\1.x64.dll";
const wchar_t* DllPath_Temp_x64 = L"\\InitiativeTarget\\Temp\\1.x64.dll";

const wchar_t* ExePath = L"\\InitiativeTarget\\install.exe";
const wchar_t* ExePath_Temp = L"\\InitiativeTarget\\Temp\\install.exe";
const wchar_t* DatPath = L"\\InitiativeTarget\\dtl.dat";
const wchar_t* UinPath = L"\\InitiativeTarget\\glp.uin";

GenerateTarDlg::GenerateTarDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("生成目标"));
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.btnGenerate, SIGNAL(clicked()), this, SLOT(OnGenerate()));
}

GenerateTarDlg::~GenerateTarDlg()
{

}

void GenerateTarDlg::OnGenerate()
{
	if (ui.edtPassword->text().isEmpty())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("密码不能为空"));
		return;
	}
	QString path = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("输入文件名..."),
		"install.exe", "(*.exe)");
	path.replace("/", "\\");
	if (path.isEmpty())
	{
		return;
	}

	std::wstring libPath = GetExePath() + L"\\Pakage.dll";
	HINSTANCE hdll = LoadLibraryW(libPath.c_str());
	if (NULL == hdll)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("dll 加载失败"));
		return;
	}

	SetPwdRes setPwdRes = (SetPwdRes)(GetProcAddress(hdll, "SetPwdRes"));
	EncryptDriverFile encryptDriverFile = (EncryptDriverFile)(GetProcAddress(hdll, "EncryptDriverFile"));
	AddDriverFile addDriverFile = (AddDriverFile)GetProcAddress(hdll, "AddDriverFile");
	AddDLLFile addDllFile = (AddDLLFile)GetProcAddress(hdll, "AddDLLFile");
	AddResFile addResFle = (AddResFile)GetProcAddress(hdll, "AddResFile");

	if (!setPwdRes || !encryptDriverFile || !addDriverFile || !addDllFile)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("找不到接口"));
		FreeLibrary(hdll);
		return;
	}

	wchar_t* exePath = new wchar_t[1024];
	wchar_t* exePathTemp = new wchar_t[1024];

	wchar_t* dllPath_x86 = new wchar_t[1024];
	wchar_t* sysPath_x86 = new wchar_t[1024];
	wchar_t* dllPathTemp_x86 = new wchar_t[1024];
	wchar_t* sysPathTemp_x86 = new wchar_t[1024];
	wchar_t* dllPath_x64 = new wchar_t[1024];
	wchar_t* sysPath_x64 = new wchar_t[1024];
	wchar_t* dllPathTemp_x64 = new wchar_t[1024];
	wchar_t* sysPathTemp_x64 = new wchar_t[1024];
	wchar_t* config1 = new wchar_t[1024];
	wchar_t* config2 = new wchar_t[1024];
	wchar_t* config1Name = new wchar_t[1024];
	wchar_t* config2Name = new wchar_t[1024];

	wsprintf(exePath, L"%s%s", GetExePath().c_str(), ExePath);
	wsprintf(exePathTemp, L"%s%s", GetExePath().c_str(), ExePath_Temp);

	wsprintf(dllPath_x86, L"%s%s", GetExePath().c_str(), DllPath_x86);
	wsprintf(sysPath_x86, L"%s%s", GetExePath().c_str(), SysPath_x86);
	wsprintf(sysPathTemp_x86, L"%s%s", GetExePath().c_str(), SysPath_Temp_x86);
	wsprintf(dllPathTemp_x86, L"%s%s", GetExePath().c_str(), DllPath_Temp_x86);

	wsprintf(dllPath_x64, L"%s%s", GetExePath().c_str(), DllPath_x64);
	wsprintf(sysPath_x64, L"%s%s", GetExePath().c_str(), SysPath_x64);
	wsprintf(sysPathTemp_x64, L"%s%s", GetExePath().c_str(), SysPath_Temp_x64);
	wsprintf(dllPathTemp_x64, L"%s%s", GetExePath().c_str(), DllPath_Temp_x64);

	wsprintf(config1, L"%s%s", GetExePath().c_str(), DatPath);
	wsprintf(config2, L"%s%s", GetExePath().c_str(), UinPath);
	wsprintf(config1Name, L"config1");
	wsprintf(config2Name, L"config2");

	wchar_t* password = new wchar_t[1024];
	wsprintf(password, L"%s", ui.edtPassword->text().toStdWString().c_str());

	if (!setPwdRes(GetModuleHandle(NULL), dllPath_x86, password))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("SetPwdRes false"));
		FreeLibrary(hdll);
		return;
	}
	DeleteFileW(sysPathTemp_x86);
	if (!encryptDriverFile(GetModuleHandle(NULL), sysPath_x86, sysPathTemp_x86))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("EncryptDriverFile false"));
		FreeLibrary(hdll);
		return;
	}
	CopyFile(dllPath_x86, dllPathTemp_x86, false);
	if (!addDriverFile(GetModuleHandle(NULL), sysPathTemp_x86, dllPathTemp_x86))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("AddDriverFile false"));
		FreeLibrary(hdll);
		return;
	}
	CopyFile(exePath, exePathTemp, false);
	if (!addDllFile(GetModuleHandle(NULL), dllPathTemp_x86, exePathTemp))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("AddDLLFile false"));
		FreeLibrary(hdll);
		return;
	}

	///////////////////////////////////////////////////////////////////////////////////
	
	if (!FileExist(dllPath_x64))
		goto ADD_RES_FILE;

	if (!setPwdRes(GetModuleHandle(NULL), dllPath_x64, password))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("SetPwdRes false"));
		FreeLibrary(hdll);
		return;
	}
	DeleteFileW(sysPathTemp_x86);
	if (!encryptDriverFile(GetModuleHandle(NULL), sysPath_x64, sysPathTemp_x64))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("EncryptDriverFile false"));
		FreeLibrary(hdll);
		return;
	}
	CopyFile(dllPath_x86, dllPathTemp_x86, false);
	if (!addDriverFile(GetModuleHandle(NULL), sysPathTemp_x64, dllPathTemp_x64))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("AddDriverFile false"));
		FreeLibrary(hdll);
		return;
	}
	CopyFile(exePath, exePathTemp, false);
	if (!addDllFile(GetModuleHandle(NULL), dllPathTemp_x64, exePathTemp))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("AddDLLFile false"));
		FreeLibrary(hdll);
		return;
	}

	///////////////////////////////////////////////////////////////////////////////////////

ADD_RES_FILE:
	if (!addResFle(GetModuleHandle(NULL), config1, exePathTemp, config1Name))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("addResFle false"));
		FreeLibrary(hdll);
		return;
	}


	if (!addResFle(GetModuleHandle(NULL), config2, exePathTemp, config2Name))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("addResFle false"));
		FreeLibrary(hdll);
		return;
	}

	CopyFile(exePathTemp, path.toStdWString().c_str(), false);
	FreeLibrary(hdll);

	QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("生成成功"));
}
