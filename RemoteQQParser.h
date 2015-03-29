/*!
	Description : This class used to read qq info from local database directly.
	              Analysis of qq info was already done by  the remote side.
	Author		: Ruining Song
	Remark		: 2014/10/23
*/

#ifndef REMOTEQQPARSER_H
#define REMOTEQQPARSER_H

#include "QQParser.h"

class RemoteQQParser : public QQParser
{
public:

	typedef std::list<ChatHistory> ChatHistoryList;

	RemoteQQParser(const std::wstring& dataPath) : QQParser(dataPath) {}
	virtual ~RemoteQQParser(){}

	virtual void Init();
	virtual const std::list<std::wstring>& GetAccountList();
	virtual const FriendList& GetFriendList(const std::wstring& account);
	virtual const ChatHistoryList& GetChatHistory(
		const std::wstring& account, 
		const std::wstring& friendAccount);
	virtual GroupInfo GetGroupInfo(const std::wstring& account, int groupId);
	virtual const TroopList& GetTroopList(const std::wstring& account);
	virtual const ChatHistoryList& GetTroopChatHistory(
		const std::wstring& account, 
		const std::wstring& troopNumber);

protected:
	unsigned int m_targetId;
	std::list<std::wstring> m_accountList;
	FriendList m_friendList;
	ChatHistoryList m_chatList;
	TroopList m_troopList;
};

#endif // REMOTEQQPARSER_H