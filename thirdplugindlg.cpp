#include "thirdplugindlg.h"
#include "uploadthirdplugindlg.h"

#include "target.h"
#include "Utility.h"
#include "nofocusstyle.h"
#include "maindlg.h"

ThirdPluginDlg::ThirdPluginDlg(Target* tar)
	: QWidget(0)
	, m_tar(tar)
{
	ui.setupUi(this);

	NoFocusStyle* style = new NoFocusStyle(this);
	ui.tbThirdPluginList->setStyle(style);
	ui.tbThirdPluginList->horizontalHeader()->resizeSection(0, 120);
	ui.tbThirdPluginList->horizontalHeader()->setDefaultAlignment(Qt::AlignLeading | Qt::AlignVCenter);

	connect( ui.btnAddThirdPlugin, SIGNAL(clicked()), this, SLOT(OnBtnAddThirdPluginClicked()));
	connect( ui.btnUpdateThirdPlugin, SIGNAL(clicked()), this, SLOT(OnBtnUpdateThirdPluginClicked()));
	connect( ui.btnDeleteThirdPlugin, SIGNAL(clicked()), this, SLOT(OnBtnDeleteThirdPluginClicked()));
	connect(ui.tbThirdPluginList, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(OnTbThirdPluginListItemClicked(QTableWidgetItem*)));
	connect(
		ui.trThirdPluginFileList, 
		SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), 
		this, 
		SLOT(OnTrThirdPluginFileListItemDoubleClicked(QTreeWidgetItem*, int)));

	connect(
		ui.trThirdPluginFileList, 
		SIGNAL(itemClicked(QTreeWidgetItem*, int)), 
		this, 
		SLOT(OnTrThirdPluginFileListItemClicked(QTreeWidgetItem*, int)));

	ui.trThirdPluginFileList->header()->resizeSection(0, 300);

	InitPluginList();
}

ThirdPluginDlg::~ThirdPluginDlg()
{

}

void ThirdPluginDlg::OnBtnAddThirdPluginClicked()
{
	if ( FrmMain->ctrOnlineFlag == false
		|| m_tar->tarStatus == TAROFFLINE )
	{
		QMessageBox::information(
			this, 
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("离线状态下不能上传插件"));
		return;
	}

	UploadThirdPluginDlg dlg(m_tar);
	dlg.SetCfgPath(m_tar->wid3rdFilePath + L"\\Config.ini");

	dlg.exec();

	InitPluginList();
}

void ThirdPluginDlg::OnBtnUpdateThirdPluginClicked()
{
	if ( FrmMain->ctrOnlineFlag == false
		|| m_tar->tarStatus == TAROFFLINE )
	{
		QMessageBox::information(
			this, 
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("离线状态下不能上传插件"));
		return;
	}

	QList<QTableWidgetItem*> itemList = ui.tbThirdPluginList->selectedItems();

	if ( 0 == itemList.count() )
	{
		QMessageBox::information(
			this, 
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择要更新的插件"));
		return;
	}

	QTableWidgetItem* id = ui.tbThirdPluginList->item(itemList.at(0)->row(), 0);
	QTableWidgetItem* ver = ui.tbThirdPluginList->item(itemList.at(0)->row(), 1);

	int pluginId = id->data(Qt::UserRole).toInt();
	int version = ver->text().toUInt();

	UploadThirdPluginDlg dlg(m_tar, 0, version, pluginId, id->text());
	dlg.SetCfgPath(m_tar->wid3rdFilePath + L"\\Config.ini");
	dlg.exec();
	InitPluginList();
}

void ThirdPluginDlg::OnBtnDeleteThirdPluginClicked()
{
	QList<QTableWidgetItem*> itemList = ui.tbThirdPluginList->selectedItems();
	if ( 0 == itemList.count() )
	{
		QMessageBox::information(
			this, 
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请选择要删除的插件"));
		return;
	}

	QTableWidgetItem* item = itemList[0];
	item = ui.tbThirdPluginList->item(item->row(), 0);
	std::wstring id = item->data(Qt::UserRole).toString().toStdWString();

	std::wstring iniPath = m_tar->wid3rdFilePath + L"\\Config.ini";

	int pluginCount = ReadValueFromLocal(L"Global", L"PluginCount", iniPath.c_str());

	int curPlugin = 1;
	std::wstring pluginId;
	for ( ; curPlugin <= pluginCount; ++curPlugin )
	{
		WCHAR pluginKey[MAX_PATH] = {0};
		wsprintfW(pluginKey, L"Plugin_%d", curPlugin);
		pluginId = ReadStringPolicyFromLocal(L"Global", pluginKey, iniPath.c_str());

		if ( id == pluginId )
		{
			WritePrivateProfileSectionW(pluginId.c_str(), NULL, iniPath.c_str());
			WritePrivateProfileStringW(L"Global", pluginKey, NULL, iniPath.c_str());
			break;
		}
	}

	WCHAR pluginKey[MAX_PATH] = {0};
	WCHAR nextPluginKey[MAX_PATH] = {0};
	for ( ; curPlugin < pluginCount; ++curPlugin )
	{
		wsprintfW(pluginKey, L"Plugin_%d", curPlugin);
		wsprintfW(nextPluginKey, L"Plugin_%d", curPlugin+1);

		pluginId = ReadStringPolicyFromLocal(L"Global", nextPluginKey, iniPath.c_str());
		WriteStringPolicyToLocal(L"Global", pluginKey, pluginId.c_str(), iniPath.c_str());
	}

	WritePrivateProfileStringW(L"Global", nextPluginKey, NULL, iniPath.c_str());

	WritePolicyToLocal(L"Global", L"PluginCount", --pluginCount, iniPath.c_str());

	if ( 0 == pluginCount )
		DeleteFileW(iniPath.c_str());

	InitPluginList();
}

void ThirdPluginDlg::InitPluginList()
{
	ui.tbThirdPluginList->clearContents();
	ui.tbThirdPluginList->setRowCount(0);
	std::wstring iniFile = m_tar->wid3rdFilePath + L"\\Config.ini";

	if ( !Exist(iniFile) )
		return;

	int plgCount = ReadValueFromLocal(L"Global", L"PluginCount", iniFile.c_str());

	for ( int i = 1; i <= plgCount; ++i )
	{
		WCHAR keyName[MAX_PATH] = {0};
		wsprintfW(keyName, L"Plugin_%d", i);

		std::wstring pluginId = ReadStringPolicyFromLocal(L"Global", keyName, iniFile.c_str());
		std::wstring pluginName = ReadStringPolicyFromLocal(pluginId.c_str(), L"Name", iniFile.c_str());
		std::wstring pluginVersion = ReadStringPolicyFromLocal(pluginId.c_str(), L"Version", iniFile.c_str());

		ui.tbThirdPluginList->insertRow(0);
		QTableWidgetItem* name = new QTableWidgetItem;
		QTableWidgetItem* ver = new QTableWidgetItem;
		ver->setTextAlignment(Qt::AlignCenter);
		name->setText(QString::fromStdWString(pluginName));
		ver->setText(QString::fromStdWString(pluginVersion));
		name->setData(Qt::UserRole, QString::fromStdWString(pluginId));

		ui.tbThirdPluginList->setItem(0, 0, name);
		ui.tbThirdPluginList->setItem(0, 1, ver);
	}
}

void ThirdPluginDlg::GetNewPluginFile( MSG* msg )
{
	if ( 0 == ui.tbThirdPluginList->selectedItems().count() )
		return;

	const wchar_t* fileName = (const wchar_t*)msg->wParam;
	DWORD pluginId = (DWORD)msg->lParam;

	QTableWidgetItem* pluginItem = ui.tbThirdPluginList->selectedItems()[0];
	pluginItem = ui.tbThirdPluginList->item(pluginItem->row(), 0);

	if ( pluginItem->data(Qt::UserRole).toUInt() == pluginId )
	{
		AddFileToPluginFileList(fileName);
		//OnTbThirdPluginListItemClicked(pluginItem);
	}
}

void ThirdPluginDlg::OnTbThirdPluginListItemClicked(QTableWidgetItem* item)
{
	item = ui.tbThirdPluginList->item(item->row(), 0);
	DWORD pluginId = item->data(Qt::UserRole).toUInt();

	WCHAR fullPath[MAX_PATH] = {0};
	wsprintfW(fullPath, L"%s\\%d", m_tar->wid3rdFilePath.c_str(), pluginId);

	std::wstring findStr = std::wstring(fullPath) + L"\\*.*";

	WIN32_FIND_DATAW fd;
	HANDLE find;

	if ( INVALID_HANDLE_VALUE == (find = FindFirstFileW(findStr.c_str(), &fd) ) )
		return;

	ui.trThirdPluginFileList->clear();

	do 
	{
		if ( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			continue;

		AddFileToPluginFileList(fd.cFileName);

	} while ( FindNextFileW(find, &fd) );
}

void ThirdPluginDlg::AddFileToPluginFileList(const wchar_t* fileName)
{
	QTableWidgetItem* pluginItem = ui.tbThirdPluginList->selectedItems()[0];
	pluginItem = ui.tbThirdPluginList->item(pluginItem->row(), 0);
	DWORD pluginId = pluginItem->data(Qt::UserRole).toUInt();

	WCHAR fullPath[MAX_PATH] = {0};
	wsprintfW(fullPath, L"%s\\%d\\%s", m_tar->wid3rdFilePath.c_str(), pluginId, fileName);

	HANDLE hFile = CreateFile(fullPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hFile )
		return;

	int fileSize = GetFileSize(hFile, NULL);
	FILETIME lastWriteTime;
	GetFileTime(hFile, NULL, NULL, &lastWriteTime);

	char size[MAX_PATH] = {0};
	wsprintfA(size, "%d KB", fileSize / 1024 + 1);

	FILETIME localtime;
	SYSTEMTIME time;
	FileTimeToLocalFileTime(&lastWriteTime, &localtime);
	FileTimeToSystemTime(&localtime,&time);
	WCHAR wzTime[MAX_PATH] = {0};
	wsprintf(wzTime, L"%.4d-%.2d-%.2d %.2d:%.2d", time.wYear,time.wMonth,
		time.wDay ,time.wHour, time.wMinute);

	SHFILEINFOW sfi;
	LPCWSTR lpwzExt = wcsrchr(fileName, L'.');
	if (lpwzExt)
	{
		SHGetFileInfoW(lpwzExt,
			0,    //FILE_ATTRIBUTE_NORMAL,
			&sfi,
			sizeof(sfi),
			SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_TYPENAME);
	}

	QTreeWidgetItem* item = new QTreeWidgetItem;
	item->setText(0, QString::fromStdWString(std::wstring(fileName)));
	item->setIcon(0, QIcon(QPixmap::fromWinHICON(GetIconFromFileName(fileName))));
	item->setText(1, QString::fromStdWString(std::wstring(wzTime)));
	//item->setText(2, QString::fromStdWString(std::wstring(sfi.szTypeName)));
	//item->setText(3, size);

	item->setData(0, Qt::UserRole, QString::fromStdWString(std::wstring(fullPath)));

	ui.trThirdPluginFileList->insertTopLevelItem(0, item);

	CloseHandle(hFile);
}

void ThirdPluginDlg::OnTrThirdPluginFileListItemDoubleClicked( QTreeWidgetItem* item, int column )
{

	std::wstring fullPath = item->data(0, Qt::UserRole).toString().toStdWString();

	ShellExecuteW(NULL, L"open", fullPath.c_str(), NULL, NULL, SW_SHOW);
}

void ThirdPluginDlg::OnTrThirdPluginFileListItemClicked( QTreeWidgetItem* item, int column )
{
	std::wstring fullPath = item->data(0, Qt::UserRole).toString().toStdWString();

	const wchar_t* ext = wcsrchr(fullPath.c_str(), L'.');
	
	if ( NULL == ext || 0 != _wcsicmp(ext, L".txt") )
		return;

	HANDLE hf = CreateFileW(fullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if ( INVALID_HANDLE_VALUE == hf )
		return;

	int fileSize = GetFileSize(hf, NULL);
	char* buffer = new char[fileSize+1];
	memset(buffer, 0, fileSize+1);
	DWORD readed = 0;
	ReadFile(hf, buffer, fileSize, &readed, NULL);

	char* bufferTrimmed = new char[fileSize+1];
	memset(bufferTrimmed, 0, fileSize+1);

	for ( int i = 0, j = 0; i < fileSize; ++i )
		if ( buffer[i] != '\0' )
			bufferTrimmed[j++] = buffer[i];

	ui.edtPreview->setPlainText(QString::fromLocal8Bit(bufferTrimmed));

	delete [] buffer;
	delete [] bufferTrimmed;
	CloseHandle(hf);
}
