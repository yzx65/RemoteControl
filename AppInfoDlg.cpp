#include "AppInfoDlg.h"
#include "ui_AppInfoDlg.h"
#include "utility.h"

#include "ParserFactory.h"

#include <QLabel>
#include <QTreeWidget>
#include <QThread>
#include "waitdlg.h"

#include "AmrDecoder.h"
#include "AmrPlayer.h"

#pragma comment(lib, "AmrDecoder.lib")

AppInfoThread::AppInfoThread(int system, std::wstring dataPath)
	: m_dataPath(dataPath)
	, m_system(system)
	, m_weixinParser(NULL)
	, m_qqParser(NULL)
{

}

void AppInfoThread::Init()
{
	ParserFactory fac((ParserFactory::SystemType)4, m_dataPath);

	if ( m_weixinParser )
		delete m_weixinParser;

	if ( m_qqParser )
		delete m_qqParser;

	m_weixinParser = fac.CreateWeixinParser();

	if ( m_weixinParser )
		m_weixinParser->Init();

	m_qqParser = fac.CreateQQParser();

	if ( m_qqParser )
		m_qqParser->Init();

	emit emitParser((unsigned int)m_qqParser, (unsigned int)m_weixinParser);
}

AppInfoDlg::AppInfoDlg(QWidget *parent, int system, std::wstring dataPath) :
    QDialog(parent),
    ui(new Ui::AppInfoDlg),
	m_dataPath(dataPath),
	m_system(system),
	m_weixin(0),
	m_qq(0),
	m_amr(NULL)
{
    ui->setupUi(this);
	//ui->btnRefresh->hide();
	ui->btnGetData->hide();

	m_waitDlg = new WaitDlg(this);
	m_waitDlg->hide();

	ui->trQQFriends->header()->resizeSection(0, 150);
	ui->trWeixinFriends->header()->resizeSection(0, 250);
	ui->trWeixinFriends->header()->resizeSection(1, 250);

	InitApplicationList();
	InitConnection();

	m_workThread = new AppInfoThread(system, dataPath);
	connect(this, SIGNAL(Init()), m_workThread, SLOT(Init()));
	connect(m_workThread, SIGNAL(emitParser(unsigned int, unsigned int)), this, SLOT(GetParser(unsigned int, unsigned int)));
	QThread* workHost = new QThread;
	m_workThread->moveToThread(workHost);
	workHost->start();

	Reload();

	ui->toolbar->hide();
}

AppInfoDlg::~AppInfoDlg()
{
    delete ui;
}

void AppInfoDlg::InitApplicationList()
{
	const std::wstring appNames[] = {L"微信", L"QQ"};
	const char* appIcons[] = {":/image/weixin.png", ":/image/qq.png"};

	for ( int i = 0; i < sizeof(appNames) / sizeof(std::wstring); ++i )
	{
		QListWidgetItem* item = new QListWidgetItem;
		item->setIcon(QIcon(QPixmap(appIcons[i])));
		item->setText(QString::fromStdWString(appNames[i]));
		ui->lstApplication->addItem(item);
	}
}

void AppInfoDlg::InitConnection()
{
	connect(
		ui->lstApplication, 
		SIGNAL(itemClicked(QListWidgetItem*)), 
		this, 
		SLOT(OnLstApplicationItemClicked(QListWidgetItem*)));

	connect(
		ui->trWeixinFriends, 
		SIGNAL(itemClicked(QTreeWidgetItem*, int)), 
		this, 
		SLOT(OnTrWeixinFriendsItemClicked(QTreeWidgetItem*, int)));

	connect(
		ui->cmbQQAccount,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(OnCmbQQAccountCurrentIndexChanged(int)));

	connect(
		ui->cmbWeixinAccount,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(OnCmbWeixinAccountCurrentIndexChanged(int)));

	connect(
		ui->trQQFriends, 
		SIGNAL(itemClicked(QTreeWidgetItem*, int)), 
		this, 
		SLOT(OnTrQQFriendsItemClicked(QTreeWidgetItem*, int)));

	connect(
		ui->trQQTroops,
		SIGNAL(itemClicked(QTreeWidgetItem*, int)), 
		this, 
		SLOT(OnTrQQTroopsItemClicked(QTreeWidgetItem*, int)));

	connect(
		ui->btnRefresh,
		SIGNAL(clicked()),
		this,
		SLOT(OnBtnRefreshClicked()));

	connect(
		ui->btnClean,
		SIGNAL(clicked()),
		this,
		SLOT(OnBtnCleanClicked()));

	connect(
		ui->btnGetData,
		SIGNAL(clicked()),
		this,
		SIGNAL(emitGetAppData()));

	connect(
		ui->btnExport,
		SIGNAL(clicked()),
		this,
		SIGNAL(emitExportData()));

	connect(
		ui->edtWeixinChactHistory,
		SIGNAL(anchorClicked(const QUrl&)),
		this,
		SLOT(OnLinkClicked(const QUrl&)));

	connect(
		ui->edtQQChatHistory,
		SIGNAL(anchorClicked(const QUrl&)),
		this,
		SLOT(OnLinkClicked(const QUrl&)));

	connect(
		ui->edtQQTroopHistory,
		SIGNAL(anchorClicked(const QUrl&)),
		this,
		SLOT(OnLinkClicked(const QUrl&)));
}

void AppInfoDlg::InitWeixinInfo()
{
	const WeixinParser::AccountList& accounts = m_weixin->GetAccountList();

	for ( WeixinParser::AccountList::const_iterator it = accounts.begin();
		  it != accounts.end();
		  ++it )
	{
		if ( it->nickName == L" " )
			ui->cmbWeixinAccount->addItem(
			QString::fromStdWString(it->weixinId), QString::fromStdWString(it->weixinId));
		else
			ui->cmbWeixinAccount->addItem(
			QString::fromStdWString(it->nickName), QString::fromStdWString(it->weixinId));
	}

	if ( accounts.size() > 0 )
		OnCmbWeixinAccountCurrentIndexChanged(0);
}

void AppInfoDlg::OnCmbWeixinAccountCurrentIndexChanged(int index)
{
	std::wstring account = ui->cmbWeixinAccount->itemData(ui->cmbWeixinAccount->currentIndex()).toString().toStdWString();

	const WeixinParser::FriendList& friends = m_weixin->GetFriendList(account);
	ui->trWeixinFriends->clear();

	for ( WeixinParser::FriendList::const_iterator it = friends.begin();
		it != friends.end();
		++it )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setIcon(0, QIcon(QPixmap(":/image/wuser.png")));
		item->setText(0, QString::fromStdWString(it->userName));
		item->setText(1, QString::fromStdWString(it->nickName));
		item->setText(2, QString::fromStdWString(it->alias));
		item->setData(0, Qt::UserRole, QString::fromStdWString(it->userName));
		ui->trWeixinFriends->addTopLevelItem(item);
	}
}

void AppInfoDlg::InitQQInfo()
{
	const std::list<std::wstring>& accounts = m_qq->GetAccountList();

	ui->cmbQQAccount->clear();

	for ( std::list<std::wstring>::const_iterator it = accounts.begin();
		  it != accounts.end();
		  ++it )
	{
		ui->cmbQQAccount->addItem(QString::fromStdWString(*it));
	}

	if ( accounts.size() > 0 )
		OnCmbQQAccountCurrentIndexChanged(0);
}

void AppInfoDlg::OnCmbQQAccountCurrentIndexChanged(int index)
{
	std::wstring account = ui->cmbQQAccount->currentText().toStdWString();

	if ( account.empty() )
		return;

	InitQQFriends(account);
	InitQQTroops(account);

}

void AppInfoDlg::InitQQFriends(const std::wstring& account)
{
	const QQParser::FriendList& friends = m_qq->GetFriendList(account);
	ui->trQQFriends->clear();

	for ( QQParser::FriendList::const_iterator it = friends.begin();
		it != friends.end();
		++it )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setIcon(0, QIcon(QPixmap(":/image/qq.png")));
		item->setText(0, QString::fromStdWString(it->account));
		item->setText(1, QString::fromStdWString(it->nickName));
		item->setText(2, QString::fromStdWString(it->remark));
		item->setText(3, QString::fromStdWString(it->signature));

		QTreeWidgetItem* parent = FindQQGroup(ui->trQQFriends, it->groupId, it->groupName);

		parent->addChild(item);
	}
}

void AppInfoDlg::InitQQTroops(const std::wstring& account)
{
	ui->trQQTroops->clear();
	const QQParser::TroopList& troops = m_qq->GetTroopList(account);

	for ( QQParser::TroopList::const_iterator it = troops.begin();
		  it != troops.end();
		  ++it )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setIcon(0, QIcon(QPixmap(":/image/troop.png")));
		item->setText(0, QString::fromStdWString(it->troopNumber));
		item->setText(1, QString::fromStdWString(it->troopName));
		item->setData(0, Qt::UserRole, QString::fromStdWString(it->troopMemo));

		ui->trQQTroops->addTopLevelItem(item);
	}
}

QTreeWidgetItem* AppInfoDlg::FindQQGroup(QTreeWidget* widget, int groupId, const std::wstring& groupName)
{
	QTreeWidgetItem* parent = NULL;

	std::wstring grpName = groupName;

	if ( grpName == L" " )
		grpName = L"好友列表";

	std::wstring account = ui->cmbQQAccount->currentText().toStdWString();

	for ( int i = 0; i < widget->topLevelItemCount(); ++i )
	{
		QTreeWidgetItem* root = widget->topLevelItem(i);

		if ( root->text(0).toStdWString() == grpName )
		{
			parent = root;
			break;
		}
	}

	if ( NULL == parent )
	{
		parent = new QTreeWidgetItem;
		QQParser::GroupInfo info = m_qq->GetGroupInfo(account, groupId);
		//parent->setIcon(0, QIcon(QPixmap(":/image/group.png")));

		parent->setText(0, QString::fromStdWString(grpName));

		parent->setData(0, Qt::UserRole, info.groupId);
		widget->addTopLevelItem(parent);
	}

	return parent;
}

void AppInfoDlg::OnLstApplicationItemClicked(QListWidgetItem* item)
{
	int index = ui->lstApplication->row(item);
	ui->stkApplicationInfo->setCurrentIndex(index);
}

void AppInfoDlg::OnTrWeixinFriendsItemClicked(QTreeWidgetItem* item, int column)
{
	std::wstring userName = item->data(0, Qt::UserRole).toString().toStdWString();
	std::wstring account = ui->cmbWeixinAccount->itemData(ui->cmbWeixinAccount->currentIndex()).toString().toStdWString();
	const WeixinParser::ChatHistoryList& history = m_weixin->GetChatHistory(account, userName);

	std::wstring content;

	for ( WeixinParser::ChatHistoryList::const_iterator it = history.begin();
		  it != history.end();
		  ++it )
	{
		content += L"<p><span style='color:#0055ff'>";
		content += it->time;
		content += it->isSend ? L" 发送 " : L" 接收 ";
		content += L"</span></p>";
		content += L"<p>";

		if ( it->msgType == 0 )
			content += it->message;
		else if ( it->msgType == 1 )
		{
			content += L"<img src=\"";
			std::wstring path = it->message;
			std::replace(path.begin(), path.end(), L'\\', L'/');
			content += path;
			content += L"\" />";
		}
		else if ( it->msgType == 2 )
		{
			// <a href="www.baidu.com"><span style=" font-size:13px; text-decoration: underline; color:#0000ff;">测试</span></a>
			content += L"<a href=\"";
			content += it->message;
			content += L"\"><span style=\" font-size:13px; text-decoration: underline; color:#0000ff;\">点击播放语音</span></a>&nbsp;&nbsp;&nbsp;";
			content += L"<a href=\"StopAmr\"><span style=\" font-size:13px; text-decoration: underline; color:#0000ff;\">停止播放</span></a>";
		}
		else
		{
			content += L"<a href=\"";
			content += it->message;
			content += L"\"><span style=\" font-size:13px; text-decoration: underline; color:#0000ff;\">点击播放视频</span></a>";
		}

		content += L"</p>";
	}

	ui->edtWeixinChactHistory->setHtml(QString::fromStdWString(content));
}

void AppInfoDlg::OnTrQQFriendsItemClicked(QTreeWidgetItem* item, int column)
{
	if ( NULL == item->parent() )
		return;

	std::wstring account = ui->cmbQQAccount->currentText().toStdWString();
	std::wstring friendAccount = item->text(0).toStdWString();
	const QQParser::ChatHistoryList& history = m_qq->GetChatHistory(account, friendAccount);

	std::wstring content;
	GenerateHistoryText(content, history);

	ui->edtQQChatHistory->setHtml(QString::fromStdWString(content));
}

void AppInfoDlg::GenerateHistoryText(std::wstring& content, const QQParser::ChatHistoryList& history)
{
	for ( QQParser::ChatHistoryList::const_iterator it = history.begin();
		it != history.end();
		++it )
	{
		content += L"<p><span style='color:#0055ff'>";
		content += it->senderName;
		content += L" ";
		content += it->time;
		content += L"</span></p>";
		content += L"<p>";

		if ( it->msgType == 0 )
			content += it->message;
		else if ( it->msgType == 1 )
		{
			content += L"<img src=\"";
			std::wstring path = it->message;
			std::replace(path.begin(), path.end(), L'\\', L'/');
			content += path;
			content += L"\" />";
		}
		else if ( it->msgType == 2 )
		{
			// <a href="www.baidu.com"><span style=" font-size:13px; text-decoration: underline; color:#0000ff;">测试</span></a>
			content += L"<a href=\"";
			content += it->message;
			content += L"\"><span style=\" font-size:13px; text-decoration: underline; color:#0000ff;\">点击播放语音</span></a>&nbsp;&nbsp;&nbsp;";
			content += L"<a href=\"StopAmr\"><span style=\" font-size:13px; text-decoration: underline; color:#0000ff;\">停止播放</span></a>";
		}
		else
		{
			content += L"<a href=\"";
			content += it->message;
			content += L"\"><span style=\" font-size:13px; text-decoration: underline; color:#0000ff;\">点击打开文件</span></a>";
		}

		content += L"</p>";
	}
}

void AppInfoDlg::OnTrQQTroopsItemClicked(QTreeWidgetItem* item, int column)
{
	std::wstring account = ui->cmbQQAccount->currentText().toStdWString();
	std::wstring troopNum = item->text(0).toStdWString();
	const QQParser::ChatHistoryList& history = m_qq->GetTroopChatHistory(account, troopNum);

	std::wstring content;
	GenerateHistoryText(content,history);

	ui->edtQQTroopHistory->setHtml(QString::fromStdWString(content));
	ui->edtTroopMemo->setPlainText(item->data(0, Qt::UserRole).toString());
}

void AppInfoDlg::OnBtnRefreshClicked()
{
	Reload();
}

void AppInfoDlg::OnLinkClicked(const QUrl& url)
{
	std::wstring filePath = url.toString().toStdWString();

	const wchar_t* ext = wcsrchr(filePath.c_str(), L'.');

	if ( ext != NULL && 0 == _wcsicmp(ext, L".amr") )
	{
		if ( m_amr == NULL )
			m_amr = new AmrPlayer(this->winId(), filePath.c_str());
		else
			m_amr->Load(filePath.c_str());

		m_amr->Start();
		return;
	}

	if ( filePath == L"StopAmr" )
	{
		if ( m_amr )
			m_amr->Stop();
	}

	if ( 32 >= (int)(ShellExecute(NULL, L"open", filePath.c_str(), NULL, NULL, SW_SHOW)) )
	{

		filePath = filePath.substr(0, filePath.rfind(L'\\'));
		ShellExecute(NULL, L"open", filePath.c_str(), NULL, NULL, SW_SHOW);
	}
}

void AppInfoDlg::OnBtnCleanClicked()
{
	emit emitCleanData();
}

void AppInfoDlg::GetParser(unsigned int qqParser, unsigned int weixinParser)
{
	m_qq = (QQParser*)qqParser;
	m_weixin = (WeixinParser*)weixinParser;

	m_waitDlg->hide();

	ui->edtWeixinChactHistory->clear();
	ui->edtQQTroopHistory->clear();
	ui->edtQQChatHistory->clear();
	ui->cmbQQAccount->clear();
	ui->cmbWeixinAccount->clear();
	ui->trWeixinFriends->clear();
	ui->trQQFriends->clear();
	ui->trQQTroops->clear();

	InitQQInfo();
	InitWeixinInfo();

	ui->btnGetData->setEnabled(true);
	ui->btnGetData->setText(QString::fromLocal8Bit(" 获取数据"));

	if ( ui->lstApplication->selectedItems().count() == 0 )
	{
		QListWidgetItem* item = ui->lstApplication->item(0);
		item->setSelected(true);
		OnLstApplicationItemClicked(item);
	}
}

void AppInfoDlg::Reload()
{
	m_waitDlg->show();
	emit Init();
}

void AppInfoDlg::DisableGetData()
{
	ui->btnGetData->setEnabled(false);
	ui->btnGetData->setText(QString::fromLocal8Bit(" 正在获取 ..."));
}

void AppInfoDlg::InsertQQAccount( std::wstring qqNumber )
{
	ui->cmbQQAccount->addItem(QString::fromStdWString(qqNumber));
}

void AppInfoDlg::InsertQQFriend( 
	std::wstring owner, 
	std::wstring number, 
	std::wstring nickName, 
	std::wstring remark, 
	std::wstring signature, 
	std::wstring group )
{
	if ( ui->cmbQQAccount->currentText().toStdWString() == owner )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setIcon(0, QIcon(QPixmap(":/image/qq.png")));
		item->setText(0, QString::fromStdWString(number));
		item->setText(1, QString::fromStdWString(nickName));
		item->setText(2, QString::fromStdWString(remark));
		item->setText(3, QString::fromStdWString(signature));

		QTreeWidgetItem* parent = FindQQGroup(ui->trQQFriends, -1, group);
		parent->addChild(item);
	}
}

void AppInfoDlg::InsertQQTroop( 
	std::wstring owner, 
	std::wstring number, 
	std::wstring troopName, 
	std::wstring troopMemo )
{
	if ( ui->cmbQQAccount->currentText().toStdWString() == owner )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setIcon(0, QIcon(QPixmap(":/image/troop.png")));
		item->setText(0, QString::fromStdWString(number));
		item->setText(1, QString::fromStdWString(troopName));
		item->setData(0, Qt::UserRole, QString::fromStdWString(troopMemo));

		ui->trQQTroops->addTopLevelItem(item);
	}
}

void AppInfoDlg::InsertQQMessage( 
	std::wstring owner, 
	int type, 
	std::wstring containerNumber, 
	std::wstring senderNumber, 
	std::wstring senderNickName, 
	std::wstring time, int msgType, 
	std::wstring content )
{

}

void AppInfoDlg::InsertWeixinAccount( 
	std::wstring weixinId, 
	std::wstring nickName )
{
	if ( nickName == L" " )
		ui->cmbWeixinAccount->addItem(QString::fromStdWString(weixinId), QString::fromStdWString(weixinId));
	else
		ui->cmbWeixinAccount->addItem(QString::fromStdWString(nickName), QString::fromStdWString(weixinId));
}

void AppInfoDlg::InsertWeixinFrineds( 
	std::wstring weixinId, 
	std::wstring friendId, 
	std::wstring nickName )
{
	if ( ui->cmbWeixinAccount->currentText().toStdWString() == weixinId )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setIcon(0, QIcon(QPixmap(":/image/wuser.png")));
		item->setText(0, QString::fromStdWString(friendId));
		item->setText(1, QString::fromStdWString(nickName));
		item->setData(0, Qt::UserRole, QString::fromStdWString(friendId));
		ui->trWeixinFriends->addTopLevelItem(item);
	}
}

void AppInfoDlg::InsertWeixinMessage( 
	std::wstring weixinId, 
	std::wstring friendId,
	std::wstring senderId,
	std::wstring time, 
	int type, 
	std::wstring content )
{

}
