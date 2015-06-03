/*!
	Description : Subclass of QQParser.
	Author		: Ruining Song
	Date		: 2014/08/18
*/

#ifndef ANDROIDQQPARSER_H
#define ANDROIDQQPARSER_H

#include "QQParser.h"

class AndroidQQParser : public QQParser
{
public:
	AndroidQQParser(const std::wstring& dataPath);
	~AndroidQQParser();

	void Init();
	const std::list<std::wstring>& GetAccountList();
	const FriendList& GetFriendList(const std::wstring& account);
	const ChatHistoryList& GetChatHistory(const std::wstring& account, const std::wstring& friendAccount);
	GroupInfo GetGroupInfo(const std::wstring& account, int groupId);
	const TroopList& GetTroopList(const std::wstring& account);
	const ChatHistoryList& GetTroopChatHistory(const std::wstring& account, const std::wstring& troopNumber);

private:
	void GetIMEI();
	static std::wstring XorDecrypt(const char* src, int srcLen, const char* key, bool isNew = false);
	static std::wstring GetHashFromAccount(const std::wstring& account);
	const ChatHistoryList& GetChatHistoryImpl(const std::wstring& account, const std::wstring& sqlValue);
	std::wstring GenerateDbPath(const std::wstring& account);

private:
	std::wstring m_imei;
	std::list<std::wstring> m_accountList;
	FriendList m_friendList;
	ChatHistoryList m_chatHistoryList;
	TroopList m_troopList;
};

#endif // ANDROIDQQPARSER_H
