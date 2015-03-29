#include "uploadthirdplugindlg.h"
#include "Utility.h"
#include "target.h"
#include "TargetConnection.h"
#include <QtGui>

#include "ZipTools.h"

UploadThirdPluginDlg::UploadThirdPluginDlg(Target* tar, QWidget *parent, int ver, int productId, QString pluginName)
	: QDialog(parent)
	, m_oldVersion(ver)
	, m_productId(productId)
	, m_tar(tar)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	if ( pluginName != "" )
	{
		ui.edtPluginName->setText(pluginName);
		ui.edtPluginName->setReadOnly(true);
	}

	WCHAR tempPath[MAX_PATH] = {0};
	GetTempPath(MAX_PATH, tempPath);

	WCHAR tarDirName[MAX_PATH] = {0};
	wsprintfW(tarDirName, L"%st9_3rd_plugin_temp_%d", tempPath, GetTickCount());
	if ( !m_productId ) m_productId = GetTickCount();
	m_targetDir = tarDirName;

	QRegExpValidator* mask = new QRegExpValidator(QRegExp("[a-z,A-Z,_][0-9,a-z,A-Z,_]+"));
	ui.edtInitFunction->setValidator(mask);
	ui.edtUnInitFunction->setValidator(mask);

	connect(ui.btnGetPath, SIGNAL(clicked()), this, SLOT(onBtnGetPathClicked()));
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(onBtnOKclicked()));
	connect(ui.btnAdvance, SIGNAL(clicked()), this, SLOT(onBtnAdvanceClicked()));

	ui.frameSplit->hide();
	ui.frameFunc1->hide();
	ui.frameFunc2->hide();
	ui.frameDataDir->hide();
	ui.frameInterval->hide();
	adjustSize();
}

UploadThirdPluginDlg::~UploadThirdPluginDlg()
{

}

void UploadThirdPluginDlg::onBtnGetPathClicked()
{
	QString path = QFileDialog::getOpenFileName(this, "", "", "(*.dat);;(*.exe)");

	if ( path == "" )
		return;

	path.replace("/", "\\");

	if ( path.endsWith(".exe") )
	{
		//ui.frameFunc1->hide();
		//ui.frameFunc2->hide();
		m_isDll = false;
	}
	else
	{
		//ui.frameFunc1->show();
		//ui.frameFunc2->show();
		m_isDll = true;
	}

	this->adjustSize();

	ui.edtPluginPath->setText(path);
}

void UploadThirdPluginDlg::onBtnOKclicked()
{
	if ( !ValidateValue() )
		return;

	std::wstring packageName;
	if ( !CompressPlugin(packageName) )
		return;

	if ( !DoUpload(packageName) )
		return;

	accept();
}

bool UploadThirdPluginDlg::ValidateValue()
{
	if ( ui.edtPluginName->text().isEmpty() )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("产品名称不能为空"));
		return false;
	}

	if ( ui.edtPluginName->text().isEmpty() )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("插件路径不能为空"));
		return false;
	}

	/*if ( ui.edtInitFunction->text().isEmpty() && m_isDll )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("初始化函数不能为空"));
		return false;
	}

	if ( ui.edtUnInitFunction->text().isEmpty() && m_isDll )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("卸载函数不能为空"));
		return false;
	}

	if ( ui.edtDataDir->text().isEmpty() )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("插件数据目录不能为空"));
		return false;
	}*/

	return true;
}

bool UploadThirdPluginDlg::CompressPlugin(std::wstring& packageName)
{

	if ( !CreateDirectoryW(m_targetDir.c_str(), NULL) )
	{
		__TRACE(
			L"[UploadThirdPluginDlg] CreateDirectory Failed. [%s] [%d]\r\n",
			m_targetDir.c_str(),
			GetLastError());
		return false;
	}

	std::wstring pluginPath = ui.edtPluginPath->text().toStdWString();
	std::wstring::size_type pos = pluginPath.rfind(L'\\');
	std::wstring pluginName = pluginPath.substr(pos+1, pluginPath.length()-pos-1);
	std::wstring pluginCopy = m_targetDir + L"\\" + pluginName;

	if ( !CopyFileW(pluginPath.c_str(), pluginCopy.c_str(), false) )
	{
		__TRACE(
			L"[UploadThirdPluginDlg] CopyFileW Failed.[%d]\r\n %s\r\n %s\r\n",
			GetLastError(),
			pluginPath.c_str(),
			pluginCopy.c_str());
		return false;
	}

	/*if ( m_isDll )
	{
		// convert dll to dat
		WCHAR cmd[MAX_PATH] = {0};
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		ZeroMemory(&pi, sizeof(pi));
		si.wShowWindow = SW_HIDE;
		wsprintfW(cmd, L"%s\\Config\\dll_to_dat.exe %s", GetExePath().c_str(), pluginCopy.c_str());
		if ( !CreateProcessW(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) )
		{
			__TRACE(L"[UploadThirdPluginDlg] CreateProcess Failed.[%d] %s\r\n", GetLastError(), cmd);
			return false;
		}

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		int nameWithNoExt = pluginName.length() - 4;
		std::wstring pureName = pluginName.substr(0, nameWithNoExt);
		std::wstring dl_ = pureName + L".dl_";
		std::wstring dat = pureName + L".dat";
		pluginName = dat;
		DeleteFile(pluginCopy.c_str());
		std::wstring oriFile = m_targetDir + L"\\" + dl_.c_str();
		std::wstring newFile = m_targetDir + L"\\" + dat.c_str();
		MoveFile(oriFile.c_str(), newFile.c_str());
	}*/

	std::wstring iniPath = m_targetDir + L"\\Config.ini";
	std::wstring initFunction = ui.edtInitFunction->text().toStdWString();
	std::wstring uninitFunction = ui.edtUnInitFunction->text().toStdWString();
	std::wstring dataDir = ui.edtDataDir->text().toStdWString();
	int interval = ui.spnInterval->value();

	WritePolicyToLocal(L"ProductId", L"Value", m_productId, iniPath.c_str());
	WritePolicyToLocal(L"Version", L"Value", m_oldVersion+1, iniPath.c_str());
	WriteStringPolicyToLocal(L"FileName", L"Value", pluginName.c_str(), iniPath.c_str());
	WriteStringPolicyToLocal(L"ExportFunction", L"StartRoutine", initFunction.c_str(), iniPath.c_str());
	WriteStringPolicyToLocal(L"ExportFunction", L"EndRoutine", uninitFunction.c_str(), iniPath.c_str());
	WriteStringPolicyToLocal(L"DataSaveDir", L"Value", dataDir.c_str(), iniPath.c_str());
	WritePolicyToLocal(L"SleepSeconds", L"Value", interval, iniPath.c_str());

	WCHAR productIdStr[MAX_PATH] = {0};
	wsprintfW(productIdStr, L"%d", m_productId);
	std::wstring productName = ui.edtPluginName->text().toStdWString();
	WritePolicyToLocal(productIdStr, L"Version", m_oldVersion+1, m_cfgPath.c_str());
	WriteStringPolicyToLocal(productIdStr, L"Name", productName.c_str(), m_cfgPath.c_str());

	// 版本号为 0 说明为新增的插件
	if ( 0 == m_oldVersion )
	{
		int pluginCount = ReadValueFromLocal(L"Global", L"PluginCount", m_cfgPath.c_str());
		WritePolicyToLocal(L"Global", L"PluginCount", pluginCount+1, m_cfgPath.c_str());
		WCHAR pluginCountStr[MAX_PATH] = {0};
		wsprintfW(pluginCountStr, L"Plugin_%d", pluginCount+1);
		WriteStringPolicyToLocal(L"Global", pluginCountStr, productIdStr, m_cfgPath.c_str());
	}

	std::wstring zipName = m_targetDir + L".zip";
	ZipTools::Zip(m_targetDir.c_str(), zipName.c_str());
	
	packageName = m_targetDir + L".xul";

	XorFile(zipName, packageName, 9);

	return true;
}

bool UploadThirdPluginDlg::DoUpload(const std::wstring& plugin)
{
	HANDLE fileHandle = CreateFileW(
		plugin.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if ( INVALID_HANDLE_VALUE == fileHandle )
	{
		__TRACE(L"[UploadThirdPluginDlg] CreatFile Failed.[%s] [%d] \r\n", plugin.c_str(), GetLastError());
		return false;
	}

	ULONG fileSize = GetFileSize(fileHandle, NULL);
	CloseHandle(fileHandle);

	if ( m_tar->tarStatus == TARONLINE
		&& m_tar->tarConn )
		m_tar->tarConn->Send_AFT(
			m_tar->dwTargetID,
			FILEUP,
			GetBase64FromWide(plugin).c_str(),
			GetBase64FromWide(plugin).c_str(),
			fileSize);
	return true;
}

void UploadThirdPluginDlg::SetCfgPath( const std::wstring& cfgPath )
{
	m_cfgPath = cfgPath;
}

void UploadThirdPluginDlg::onBtnAdvanceClicked()
{
	if ( ui.btnAdvance->text() == QString::fromLocal8Bit("高级设置") )
	{
		ui.frameSplit->show();
		ui.frameFunc1->show();
		ui.frameFunc2->show();
		ui.frameDataDir->show();
		ui.frameInterval->show();
		ui.btnAdvance->setText(QString::fromLocal8Bit("收起"));
	}
	else
	{
		ui.frameSplit->hide();
		ui.frameFunc1->hide();
		ui.frameFunc2->hide();
		ui.frameDataDir->hide();
		ui.frameInterval->hide();
		ui.btnAdvance->setText(QString::fromLocal8Bit("高级设置"));
	}

	adjustSize();
}
