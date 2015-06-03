/*!
	Description : Use this class to parse weixin information.
	Author		: Ruining Song
	Date		: 2014/08/18
*/

#ifndef WEIXINPARSER_H
#define WEIXINPARSER_H

#include <string>
#include <list>

class WeixinParser
{
public:

	struct AccountInfo
	{
		std::wstring weixinId;
		std::wstring nickName;
	};

	typedef std::list<AccountInfo> AccountList;

	struct FriendInfo
	{
		std::wstring userName;
		std::wstring nickName;
		std::wstring alias;
		unsigned int type;
	};

	typedef std::list<FriendInfo> FriendList;

	enum MessageType
	{
		PLAIN_TEXT = 1,
		PICTURE = 3,
		AUDIO = 34,
		VIDEO = 35
	};

	struct ChatHistory
	{
		std::wstring time;				// 时间
		unsigned int msgType;			// 消息类型
		unsigned int isSend;			// 发送 - 1 接收 - 0
		std::wstring message;			// 文本消息正文
		std::wstring filePath;			// 图片/录音/视频文件路径
	};

	typedef std::list<ChatHistory> ChatHistoryList;

	WeixinParser(const std::wstring& dataPath) : m_dataPath(dataPath) {}
	virtual ~WeixinParser(){}

	/*!
	\brief
		Initialize.
	*/
	virtual void Init() = 0;

	/*!
	\brief
		Get account list
	*/
	virtual const AccountList& GetAccountList() = 0;

	/*!
	\brief
		Get friends list
	*/
	virtual const FriendList& GetFriendList(const std::wstring& account) = 0;

	/*!
	\brief
		Get chat history of the specified friend.
	*/
	virtual const ChatHistoryList& GetChatHistory(const std::wstring& account, const std::wstring& userName) = 0;

protected:
	std::wstring m_dataPath;
};

inline WeixinParser* GetWeixinParser()
{
	return NULL;
}

#endif // WEIXINPARSER_H