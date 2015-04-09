#include "maindlg.h"
#include "widget.h"
#include <QtGui/QApplication>
#include <QtPlugin>
#include <windows.h>

#include "Utility.h"
#include "DbgHelper.h"

#include "target.h"

#include <string>
#include <list>
#include <algorithm>

//#define CHECK_LICENSE

Q_IMPORT_PLUGIN(qsqlodbc)

#include <AdkLicense.h>

BOOL WINAPI AdkGrandDogCheck(char *szProductName, char* szPassword);

BOOL WINAPI CheckLicense()
{
	WCHAR	wzLicence[MAX_PATH] = {0};
	
	GetModuleFileNameW(NULL, wzLicence, MAX_PATH);
	*wcsrchr(wzLicence, L'\\') = L'\0';
	lstrcatW(wzLicence, L"\\License.dat");

	TUOJIE_LICENSE	tjLicence = {0};

	if (!AdkGetLicenseInfo(wzLicence, &tjLicence))
	{
		MessageBoxW(NULL, L"未找到Licence.dat文件", L"警告", MB_OK);
		return FALSE;
	}
	
	if ( !AdkGrandDogCheck(tjLicence.szDogName, tjLicence.szDogPass) )
	{
		MessageBoxW(NULL, L"对应的硬件狗不存在", L"警告", MB_OK);
		return FALSE;
	}

	return true;
}

//#include "lua.hpp"
//#pragma comment(lib, "lua5.1.lib")

//#include "ProcessFileTask.h"

void SomeTest()
{
	//lua_State* L = lua_open();
	//AmrDecoder decoder(L"1.amr");
	//decoder.Play();
	//FileTask task;
	//task.aniTmpTaskPath = WideToAnsi(GetExePath()) + "\\data\\1421404300\\BackSound\\tmp_502297.502297";
	//Target tar;
	//tar.widBackSoundPath = GetExePath() + L"\\data\\1421404300\\BackSound\\";
	//WCHAR wzZlibPath[MAX_PATH] = {0};
	//GetModuleFileNameW(0, wzZlibPath, MAX_PATH);
	//LPWSTR wzName = wcsrchr(wzZlibPath, L'\\');
	//wcscpy(wzName+1, L"zlib1.dll");
	//HMODULE hLibrary = LoadLibrary(wzZlibPath);
	//extern ZlibUncompress g_zlibUncompress;
	//if (hLibrary)
	//{
	//	g_zlibUncompress = (ZlibUncompress)GetProcAddress(hLibrary, "uncompress");
	//}
	//ProcessBackSoundPluginData(&task, &tar);

}

int main(int argc, char *argv[])
{

#ifdef CHECK_LICENSE
	if ( !CheckLicense() )
		return -1;
#endif

	DbgHelper::InstallDbgHelper();

	// 删除旧的日志文件
	std::wstring logFile = GetExePath()+L"\\log.txt";
	DeleteFileW(logFile.c_str());

	// 设置 lineedit 右键菜单等显示为中文
	QTranslator trans;  
	trans.load(":/qt_zh_CN.qm");  

	SetCurrentDirectoryW(GetExePath().c_str());

	QApplication a(argc, argv);
	SomeTest();
	a.installTranslator(&trans);
	a.setWindowIcon(QIcon(QPixmap(":/image/icon.png")));

	MainDlg w;
	w.resize(900, 500);
	CenterWindow(w);
	w.show();

	w.StartAction();
	return a.exec();

	return 1;
}
