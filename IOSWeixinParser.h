#ifndef IOSWEIXINPARSER_H
#define IOSWEIXINPARSER_H

#include "WeixinParser.h"

class IOSWeixinParser : public WeixinParser
{
public:
	IOSWeixinParser(const std::wstring& dataPath);

	void Init();
	const AccountList& GetAccountList();
	const FriendList& GetFriendList(const std::wstring& account);
	const ChatHistoryList& GetChatHistory(const std::wstring& account, const std::wstring& userName);

private:
	std::wstring GetAccountDir();
	std::wstring GetTableNameFromUserName(const std::wstring& userName);

private:
	std::wstring m_dbFile;
	std::wstring m_weixinRoot;
	AccountList m_accountList;
	FriendList m_friendList;
	ChatHistoryList m_chatHistory;
};

#endif // IOSWEIXINPARSER_H