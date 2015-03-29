#ifndef APPINFODLG_H
#define APPINFODLG_H

#include <QDialog>

#include "WeixinParser.h"
#include "QQParser.h"

#include <QUrl>

namespace Ui {
class AppInfoDlg;
}

class QListWidgetItem;
class QTreeWidget;
class QTreeWidgetItem;
class WaitDlg;

class AmrDecoder;

class AppInfoThread : public QObject
{
	Q_OBJECT

public:
	AppInfoThread(int system, std::wstring dataPath);

signals:
	void emitParser(unsigned int pq, unsigned int pw);

public slots:
	void Init();

private:
	std::wstring m_dataPath;
	int m_system;
	QQParser* m_qqParser;
	WeixinParser* m_weixinParser;
};

class AppInfoDlg : public QDialog
{
    Q_OBJECT

public:
	explicit AppInfoDlg(QWidget *parent, int system, std::wstring dataPath);
    ~AppInfoDlg();

signals:
	void emitGetAppData();
	void emitCleanData();
	void emitExportData();
	void Init();

public:
	void Reload();
	void DisableGetData();

public slots:
	void GetParser(unsigned int qqParser, unsigned int weixinParser);

private slots:
	void OnLstApplicationItemClicked(QListWidgetItem* item);
	void OnTrWeixinFriendsItemClicked(QTreeWidgetItem* item, int);
	void OnCmbQQAccountCurrentIndexChanged(int index);
	void OnCmbWeixinAccountCurrentIndexChanged(int index);
	void OnTrQQFriendsItemClicked(QTreeWidgetItem* item, int column);
	void OnTrQQTroopsItemClicked(QTreeWidgetItem* item, int column);
	void OnBtnRefreshClicked();
	void OnLinkClicked(const QUrl& url);
	void OnBtnCleanClicked();

private:
	void InitApplicationList();
	void InitConnection();
	void InitWeixinInfo();
	void InitQQInfo();
	void InitQQFriends(const std::wstring& account);
	void InitQQTroops(const std::wstring& account);

	QTreeWidgetItem* FindQQGroup(QTreeWidget* widget, int groupId, const std::wstring& groupName);
	void GenerateHistoryText(std::wstring& content, const QQParser::ChatHistoryList& history);

public:

	// QQ相关
	void InsertQQAccount(std::wstring qqNumber);

	void InsertQQFriend(
		std::wstring owner, 
		std::wstring number, 
		std::wstring nickName, 
		std::wstring remark, 
		std::wstring signature,
		std::wstring group);

	void InsertQQTroop(
		std::wstring owner,
		std::wstring number,
		std::wstring troopName,
		std::wstring troopMemo);

	// 如果消息为图片或语音，则 content 存储路径
	void InsertQQMessage(
		std::wstring owner,
		int type,
		std::wstring containerNumber,
		std::wstring senderNumber,
		std::wstring senderNickName,
		std::wstring time,
		int msgType,
		std::wstring content);


	// 微信相关
	void InsertWeixinAccount(
		std::wstring weixinId,
		std::wstring nickName);

	void InsertWeixinFrineds(
		std::wstring weixinId,
		std::wstring friendId,
		std::wstring nickName);

	void InsertWeixinMessage(
		std::wstring weixinId,
		std::wstring friendId,
		std::wstring senderId,
		std::wstring time,
		int type,
		std::wstring content
		);

private:
    Ui::AppInfoDlg *ui;
	AppInfoThread* m_workThread;
	WeixinParser* m_weixin;
	QQParser* m_qq;

	std::wstring m_dataPath;
	int m_system;
	WaitDlg* m_waitDlg;

	AmrDecoder* m_amr;
};

#endif // APPINFODLG_H
