#ifndef IOSQQPARSER_H
#define IOSQQPARSER_H

#include "QQParser.h"

class IOSQQParser : public QQParser
{
public:

	IOSQQParser(const std::wstring& dataPath);
	void Init();
	const std::list<std::wstring>& GetAccountList();
	const FriendList& GetFriendList(const std::wstring& account);
	const ChatHistoryList& GetChatHistory(
		const std::wstring& account, 
		const std::wstring& friendAccount);
	GroupInfo GetGroupInfo(const std::wstring& account, int groupId);
	const TroopList& GetTroopList(const std::wstring& account);
	const ChatHistoryList& GetTroopChatHistory(
		const std::wstring& account, 
		const std::wstring& troopNumber);

private:
	std::wstring m_qqRootPath;
	std::list<std::wstring> m_accountList;
	FriendList m_friendList;
	ChatHistoryList m_chatList;
	TroopList m_troopList;
};

#endif // IOSQQPARSER_H