/*!
	Description : Use this class to parse QQ information.
	Author		: Ruining Song
	Date		: 2014/08/18
*/

#ifndef QQPARSER_H
#define QQPARSER_H

#include <string>
#include <list>

class QQParser
{
public:

	/*!
	\brief
		Friend info.
	*/
	struct FriendInfo
	{
		std::wstring account;
		std::wstring nickName;
		std::wstring remark;
		std::wstring signature;
		int groupId;
		std::wstring groupName;
	};

	typedef std::list<FriendInfo> FriendList;

	/*!
	\brief
		Friends' group info.
	*/
	struct GroupInfo
	{
		GroupInfo(){}
		GroupInfo(const GroupInfo& info)
			: groupId(info.groupId)
			, groupName(info.groupName)
			, memberCount(info.memberCount)
		{

		}
		int groupId;
		std::wstring groupName;
		int memberCount;
	};

	/*!
	\brief
		Troop info
	*/
	struct TroopInfo
	{
		std::wstring troopNumber;
		std::wstring troopName;
		std::wstring troopMemo;
	};

	typedef std::list<TroopInfo> TroopList;

	/*!
	\brief
		Message info
	*/
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
		std::wstring senderName;		// 发送者昵称
	};

	typedef std::list<ChatHistory> ChatHistoryList;

	QQParser(const std::wstring& dataPath) : m_dataPath(dataPath) {}
	virtual ~QQParser(){}

	/*!
	\brief
		Initialize.
	*/
	virtual void Init() = 0;

	/*!
	\brief
		Get qq number list
	*/
	virtual const std::list<std::wstring>& GetAccountList() = 0;

	/*!
	\brief
		Get friends list
	*/
	virtual const FriendList& GetFriendList(const std::wstring& account) = 0;

	/*!
	\brief
		Get chat history of the specified friend.
	*/
	virtual const ChatHistoryList& GetChatHistory(
		const std::wstring& account, 
		const std::wstring& friendAccount) = 0;

	/*!
	\brief
		Get group info from group id
	*/
	virtual GroupInfo GetGroupInfo(const std::wstring& account, int groupId) = 0;

	/*!
	\brief
		Get troop list
	*/
	virtual const TroopList& GetTroopList(const std::wstring& account) = 0;

	/*!
	\brief
		Get chat history of the specified troop.
	*/
	virtual const ChatHistoryList& GetTroopChatHistory(
		const std::wstring& account, 
		const std::wstring& troopNumber) = 0;

protected:
	std::wstring m_dataPath;
};

#endif // QQPARSER_H