/*!
	Description : Subclass of WeixinParser
	Author		: Ruining Song
	Date		: 2014/08/18
*/

#ifndef ANDROIDWEIXINPARSER_H
#define ANDROIDWEIXINPARSER_H

#include "WeixinParser.h"

class AndroidWeinxinParser : public WeixinParser
{
public:
	AndroidWeinxinParser(const std::wstring& datapath);
	~AndroidWeinxinParser();
	void Init();
	const AccountList& GetAccountList();
	const FriendList& GetFriendList(const std::wstring& account);
	const ChatHistoryList& GetChatHistory(const std::wstring& account, const std::wstring& userName);

private:
	void GetDbPath();

private:
	AccountList m_accountList;
	FriendList m_friendList;
	ChatHistoryList m_chatHistoryList;
	std::list<std::wstring> m_dbFileName;
	std::wstring m_dbDecryptFileName;
};

#endif // ANDROIDWEIXINPARSER_H