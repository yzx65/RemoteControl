#include "aboutdlg.h"
#include "Utility.h"
#include "maindlg.h"

extern MainDlg* FrmMain;



AboutDlg::AboutDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Tool);

	std::wstring inifile = GetExePath()+L"\\setting.ini";
	std::wstring title = ReadStringPolicyFromLocal(L"Application", L"title", inifile.c_str());
	ui.lbTitle->setText(QString::fromStdWString(title));
	
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(close()));

	UpdatePluginInfo(ui.trWindows, FrmMain->WindowsPlgCxtVect);
	UpdatePluginInfo(ui.trMac, FrmMain->MacPlgCxtVect);
	UpdatePluginInfo(ui.trIOS, FrmMain->IosPlgCxtVect);
	UpdatePluginInfo(ui.trAndroid, FrmMain->AndroidPlgCxtVect);

	InitCustomGui();
	
}

AboutDlg::~AboutDlg()
{

}

void AboutDlg::UpdatePluginInfo( QTreeWidget* tree, PPLUGIN_CXT pluginInfo[] )
{
	tree->setIndentation(0);
	tree->header()->resizeSection(0, 200);

	for ( int i = 0; i != MAX_PLG_COUNT; i++ )
	{
		// Phone don't have plugin 3.
		if ( i == 3 && 
			( pluginInfo == FrmMain->AndroidPlgCxtVect
			|| pluginInfo == FrmMain->IosPlgCxtVect ) )
		{
			continue;
		}

		if ( pluginInfo[i] != 0 && pluginInfo[i]->dwPluginVer != 0 )
		{
			QTreeWidgetItem* item = new QTreeWidgetItem;
			item->setText(0, QString::fromLocal8Bit(ConvertPluginIdToLang(i).c_str()));
			item->setText(1, tr("%1").arg(pluginInfo[i]->dwPluginVer));
			tree->addTopLevelItem(item);
		}
	}
}

void AboutDlg::InitCustomGui()
{
	QWidget* windows = ui.tabwideget->widget(0);
	QWidget* mac = ui.tabwideget->widget(1);
	QWidget* ios = ui.tabwideget->widget(2);
	QWidget* android = ui.tabwideget->widget(3);

	ui.tabwideget->removeTab(0);
	ui.tabwideget->removeTab(0);
	ui.tabwideget->removeTab(0);
	ui.tabwideget->removeTab(0);


	if ( Exist(GetExePath() + L"\\components\\WINDOWS") )
		ui.tabwideget->addTab(windows, QIcon(QPixmap("image/windows_online.png")), "Windows");

	if ( Exist(GetExePath() + L"\\components\\MACOSX") )
		ui.tabwideget->addTab(mac, QIcon(QPixmap("image/mac_online.png")), "Mac");

	if ( Exist(GetExePath() + L"\\components\\IOS") )
		ui.tabwideget->addTab(ios, QIcon(QPixmap("image/iphone_online.png")), "IOS");

	if ( Exist(GetExePath() + L"\\components\\ANDROID") )
		ui.tabwideget->addTab(android, QIcon(QPixmap("image/android_online.png")), "Android");
}
