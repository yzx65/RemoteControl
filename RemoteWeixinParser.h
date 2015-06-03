/*!
	Description : This class used to read weixin info from local database directly.
	              Analysis of weixin info was already done by  the remote side.
	Author		: Ruining Song
	Remark		: 2014/10/23
*/

#ifndef REMOTEWEIXINPARSER_H
#define REMOTEWEIXINPARSER_H

#include "WeixinParser.h"

class RemoteWeixinParser : public WeixinParser
{
public:
	RemoteWeixinParser(const std::wstring& dataPath) : WeixinParser(dataPath){}
	~RemoteWeixinParser(){}

	void Init();
	const AccountList& GetAccountList();
	const FriendList& GetFriendList(const std::wstring& account);
	const ChatHistoryList& GetChatHistory(const std::wstring& acount, const std::wstring& userName);

private:
	unsigned int m_targetId;
	AccountList m_accountList;
	FriendList m_friendList;
	ChatHistoryList m_chatHistory;
};

#endif // REMOTEWEIXINPARSER_H