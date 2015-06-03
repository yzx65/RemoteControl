#include "daemondlg.h"
#include "maindlg.h"

#include "Utility.h"

#include "adkprecomp.h"
#include "adkmd5.h"

#include <QtGui>

// ////////////////////////////////////////////////////////////////////////////////
// @public ���캯��
//
DaemonDlg::DaemonDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

	QIntValidator* mask = new QIntValidator(0, 65535, this);
	ui.edtPort1->setValidator(mask);
	ui.edtPort2->setValidator(mask);
	ui.edtPort3->setValidator(mask);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnOk()));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��������
//
DaemonDlg::~DaemonDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ȷ��
//
void DaemonDlg::OnOk()
{
	//
	// ѡ����·��
	//
	QString dir = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("ѡ����·��"));

	if ( dir == "" )
	{
		return;
	}

	dir.replace("/", "\\");

	std::wstring daemondir;
	if ( dir[dir.length()-1] == '\\' )
		daemondir = dir.toStdWString() + L"Server\\";
	else
		daemondir = dir.toStdWString() + L"\\Server\\";

	// ɾ��ԭ����ת
	SHDel(daemondir.c_str());
	CreateDirectory(daemondir.c_str(), NULL);

	// hfs
	std::wstring hfsDir = daemondir + L"HttpFileServer\\";
	CreateDirectory(hfsDir.c_str(), NULL);
	std::wstring localPath = GetExePath() + L"\\Server\\HttpFileServer\\";
	const wchar_t* hfsFiles[] = {L"~temp.vfs", L"hfs.exe", L"hfs.ini"};

	for ( int i = 0; i != sizeof(hfsFiles) / 4; ++i )
	{
		std::wstring srcFile = localPath + hfsFiles[i];
		std::wstring dstFile = hfsDir + hfsFiles[i];
		if ( !CopyFile(srcFile.c_str(), dstFile.c_str(), FALSE) )
		{
			/*WCHAR errMsg[1024] = {0};
			wsprintfW(errMsg, L"�����ļ�����[%d].\r\n%s\r\n%s", GetLastError(), srcFile.c_str(), dstFile.c_str());
			MessageBox(NULL, errMsg, L"����", MB_OK);
			return;*/
		}
	}

	// Support/Windows/B  Support/Windows/C  Support/Windows/D
	std::wstring supportDir = daemondir + L"dependency\\";
	CreateDirectory(supportDir.c_str(), NULL);
	std::wstring localDir = GetExePath() + L"\\dependency\\Windows\\";
	const wchar_t* supportDirs[] = {L"B", L"C", L"D"};
	
	for ( int i = 0; i != sizeof(supportDirs) / 4; ++i )
	{
		std::wstring srcDir = localDir + supportDirs[i];
		std::wstring dstDir = supportDir + supportDirs[i];
		if ( !SHCopy(srcDir.c_str(), dstDir.c_str()) )
		{

		}
	}

	//
	// ���������ļ�
	//
	if ( !CreatePluginCfgFile(GetExePath() + L"\\components\\WINDOWS\\plg.cfg", FrmMain->WindowsPlgCxtVect) )
	{
		//return;
	}

	if ( !CreatePluginCfgFile(GetExePath() + L"\\components\\MACOSX\\plg.cfg", FrmMain->MacPlgCxtVect) )
	{
		//return;
	}

	if ( !CreatePluginCfgFile(GetExePath() + L"\\components\\IOS\\plg.cfg", FrmMain->IosPlgCxtVect) )
	{
		//return;
	}

	if ( !CreatePluginCfgFile(GetExePath() + L"\\components\\Android\\plg.cfg", FrmMain->AndroidPlgCxtVect) )
	{
		//return;
	}


	//
	// ������ת�ļ�
	//
	if ( !GenerateDaemonFileList(daemondir) )
	{
		return;
	}

	//
	// д������
	//
	std::wstring daemonPath = daemondir + L"Daemon.exe";

	if ( !UpdateDaemonResource(daemonPath) )
	{
		MsgBoxErrorW((HWND)this->winId(), L"������ת���������ó���!");
		return;
	}

	MsgBoxInfoW((HWND)this->winId(), L"�ɹ�������ת������!");
	SetStatusInfoW(STATUS_INFO, L"�ɹ�������ת������!");

	close();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ���� plg.cfg
//
bool DaemonDlg::CreatePluginCfgFile(std::wstring plgCfgPath, PPLUGIN_CXT PlgCxtVect[])
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

	BYTE sOutline[16 * 1024];
	PPLUGIN_CXT pluginCxt;
	int pos = 0;

	ZeroMemory(sOutline, 16 * 1024);

	// pluginId starts from 0
	//
	ULONG   vectKey = 0;
	ULONG	plgLen;
	int     nPluginNameLen;
	int     nProcListLen;
	int     nPluginDataLen;
	PVOID   lpPluginData;

	for (; vectKey < MAX_PLG_COUNT; vectKey++)
	{
		pluginCxt = PlgCxtVect[vectKey];
		if (pluginCxt == NULL)
		{
			continue;
		}

		nPluginNameLen = strlen(pluginCxt->lpszPluginName) + 1;
		nProcListLen = strlen(pluginCxt->lpszProcList) + 1;
		nPluginDataLen = 0;
		lpPluginData = NULL;

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

		// VER and UPDATEVER
		//
		memcpy(sOutline + pos, (void *)&pluginCxt->dwPluginVer, sizeof(ULONG));
		pos += sizeof(ULONG);

		memcpy(sOutline + pos, (void *)&pluginCxt->dwUpdateVer, sizeof(ULONG));
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

	HANDLE hFile = CreateFileW(plgCfgPath.c_str(),
		GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	DWORD dwByteWritten;
	bool bRet = WriteFile(hFile, sOutline, pos, &dwByteWritten, NULL);
	CloseHandle(hFile);

	return bRet;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ������ת�������ļ�
//
bool DaemonDlg::GenerateDaemonFileList(std::wstring daemonDir)
{
	std::wstring OrgDaemonPath = GetExePath() + L"\\Server\\";
	std::wstring OrgPluginPath = GetExePath() + L"\\components\\";

	do
	{
		std::wstring OrgDaemonExe = OrgDaemonPath + L"daemon.bin";
		std::wstring NewDaemonExe = daemonDir + L"daemon.exe";
		if (CopyFile(OrgDaemonExe.c_str(), NewDaemonExe.c_str(), false) == 0)
		{
			break;
		}

		OrgDaemonExe = OrgDaemonPath + L"DaemonService.bin";
		NewDaemonExe = daemonDir + L"DaemonService.exe";
		if (CopyFile(OrgDaemonExe.c_str(), NewDaemonExe.c_str(), false) == 0)
		{
			break;
		}

		OrgDaemonExe = OrgDaemonPath + L"StartService.bat";
		NewDaemonExe = daemonDir + L"StartService.bat";
		if (CopyFile(OrgDaemonExe.c_str(), NewDaemonExe.c_str(), false) == 0)
		{
			break;
		}

		OrgDaemonExe = OrgDaemonPath + L"StopService.bat";
		NewDaemonExe = daemonDir + L"StopService.bat";
		if (CopyFile(OrgDaemonExe.c_str(), NewDaemonExe.c_str(), false) == 0)
		{
			break;
		}

		std::wstring NewPluginPath = daemonDir + L"update\\";

		if (CreateDirectory(NewPluginPath.c_str(), NULL) == 0)
		{
			break;
		}

		std::wstring iniPath = GetExePath() + L"\\setting.ini";
		ULONG ver = ReadValueFromLocal(L"Application", L"version", iniPath.c_str());

		if ( ver == 6000 || ver == 9000 )
			if ( !CopyPlgToDaemon(OrgPluginPath+L"MACOSX\\", NewPluginPath+L"MACOSX\\", FrmMain->MacPlgCxtVect) )
			{
				//break;
			}

		if ( ver == 6000 || ver == 9000 )
			if ( !CopyPlgToDaemon(OrgPluginPath+L"IOS\\", NewPluginPath+L"IOS\\", FrmMain->IosPlgCxtVect) )
			{
				//break;
			}

		if ( ver == 5000 || ver == 8000 || ver == 9000 )
			if ( !CopyPlgToDaemon(OrgPluginPath+L"WINDOWS\\", NewPluginPath+L"WINDOWS\\", FrmMain->WindowsPlgCxtVect) )
			{
				//break;
			}

		if ( ver == 7000 || ver == 9000 )
			if ( !CopyPlgToDaemon(OrgPluginPath+L"ANDROID\\", NewPluginPath+L"ANDROID\\", FrmMain->WindowsPlgCxtVect) )
			{
				//break;
			}

		
		return true;

	}while(false);

	int errorId = GetLastError();
	MsgBoxErrorExW((HWND)this->winId(), L"������ת����������\r\nָ��Ŀ¼�Ѵ�����ת������!");
	SetStatusInfoExW(STATUS_ERROR, L"������ת����������\r\n������:%d", errorId);

	return false;    
}

// ////////////////////////////////////////////////////////////////////////////////
// @private \components Ŀ¼ -> ��ת \update Ŀ¼
//
bool DaemonDlg::CopyPlgToDaemon(std::wstring OrgPluginPath, std::wstring NewPluginPath, PPLUGIN_CXT PlgCxtVect[])
{

	if (CreateDirectory(NewPluginPath.c_str(), NULL) == 0)
	{
		return false;
	}

	std::wstring OrgUptIni = OrgPluginPath + L"plg.cfg";
	std::wstring NewUptIni = NewPluginPath + L"plg.cfg";

	if (CopyFile(OrgUptIni.c_str(), NewUptIni.c_str(), false) == 0)
	{
		RemoveDirectory(NewPluginPath.c_str());
		return false;
	}

	for (int vect = 1; vect < MAX_PLG_COUNT; vect ++)
	{
		PPLUGIN_CXT plgCxt = PlgCxtVect[vect];
		if (plgCxt == NULL || plgCxt->dwPluginVer == 0)
		{
			continue;
		}

		std::wstring OrgPlgFile = OrgPluginPath + QString("%1").arg(plgCxt->dwPluginId).toStdWString() + L".dat";
		std::wstring NewPlgFile = NewPluginPath + QString("%1").arg(plgCxt->dwPluginId).toStdWString();

		if ( ! CopyFile(OrgPlgFile.c_str(), NewPlgFile.c_str(), true))
		{
			MsgBoxErrorW((HWND)this->winId(), L"������ת����������\r\n���ɲ������ȷ");
			return false;
		}
	}

	return true;
}

bool DaemonDlg::UpdateDaemonResource(std::wstring daemonFile)
{
	do
	{
		HANDLE hUpdateRes = BeginUpdateResource(daemonFile.c_str(), true); 
		if (hUpdateRes == NULL)
		{
			break; 
		} 

		std::string passWord = ui.edtPassword->text().toStdString();

		PDAEMON_PARAM pData =(PDAEMON_PARAM)malloc(sizeof(DAEMON_PARAM));
		ZeroMemory(pData, sizeof(DAEMON_PARAM));

		pData->byShowWindow = ui.chkShowLog->isChecked()?1:0;
		pData->byLogFile    = ui.chkEnableLog->isChecked()?1:0;
		pData->usPortForTarget = ui.edtPort1->text().toUInt();
		pData->usCtrPortForControl = ui.edtPort2->text().toUInt();
		pData->usDataPortForControl = ui.edtPort3->text().toUInt();
		pData->usPortForManager = ui.edtPort2->text().toUInt();

		//
		// Compute MD5 Hash for password
		//
		MD5_CTX context;
		AdkMD5Init (&context);
		AdkMD5Update (&context, (PBYTE)passWord.c_str(), passWord.length());
		AdkMD5Final (&context, pData->byPassHash);

		BOOL result = UpdateResource(hUpdateRes,    // update resource handle 
			RT_RCDATA,          // change dialog box resource
			L"S_DATA",           // dialog box name
			MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),  // neutral language
			pData,              // ptr to resource info
			sizeof(DAEMON_PARAM));           // size of resource info.
		if (result == FALSE)
		{ 
			break; 
		}

		if (!EndUpdateResource(hUpdateRes, FALSE)) 
		{ 
			break;
		}

		return true;

	} while(false);

	return false;
}