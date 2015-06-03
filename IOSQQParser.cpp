#include "IOSQQParser.h"
#include "ApplicationPathParser.h"
#include "utility.h"
#include "SQLiteHelper.h"

#include <Windows.h>

const std::wstring QQDomain(L"com.tencent.mqq");
const std::wstring QQSubPath(L"\\Documents\\contents");
const std::wstring DBName(L"\\QQ.db");

IOSQQParser::IOSQQParser( const std::wstring& dataPath )
	: QQParser(dataPath)
{

}

void IOSQQParser::Init()
{
	ApplicationPathParer& pathParser = ApplicationPathParer::CreateInstance();
	
	if ( !pathParser.Load(m_dataPath) )
		return;

	m_qqRootPath = m_dataPath + pathParser.GetApplicationPath(QQDomain) + QQSubPath;
}

const std::list<std::wstring>& 
IOSQQParser::GetAccountList()
{
	m_accountList.clear();
	
	if ( m_qqRootPath.empty() )
		return m_accountList;

	std::wstring findStr = m_qqRootPath + L"\\*.*";

	try
	{
		WIN32_FIND_DATAW fd = {0};
		HANDLE hf = FindFirstFileW(findStr.c_str(), &fd);
		if ( INVALID_HANDLE_VALUE == hf )
			throw 1;

		do 
		{
			if ( fd.cFileName[0] >= L'0'
				&& fd.cFileName[0] <= L'9'
				&& wcslen(fd.cFileName) > 5 )
				m_accountList.push_back(fd.cFileName);

		} while ( FindNextFile(hf, &fd) );

		FindClose(hf);
	}
	catch ( ... )
	{

	}

	return m_accountList;
}

const QQParser::FriendList& 
IOSQQParser::GetFriendList( const std::wstring& account )
{
	m_friendList.clear();
	std::wstring dbPath = m_qqRootPath + L"\\" + account + DBName;
	SQLiteHelper sqlite;

	try
	{
		if ( account.empty() )
			throw 1;

		if ( !sqlite.ConnectToDatabase(dbPath) )
			throw 1;

		if ( !sqlite.Exec(L"select distinct tbl_name from sqlite_master where tbl_name like 'tb_c2cMsg_%'") )
			throw 1;

		while ( sqlite.Step() )
		{
			FriendInfo info;
			info.account = sqlite.GetText(0);
			info.account = info.account.substr(10, info.account.length()-10);
			info.groupId = 0;
			m_friendList.push_back(info);
		}

		sqlite.Finalize();
	}
	catch ( ... )
	{

	}

	sqlite.CloseDatabase();
	return m_friendList;
}

const QQParser::ChatHistoryList& 
IOSQQParser::GetChatHistory( const std::wstring& account, const std::wstring& friendAccount )
{
	m_chatList.clear();
	std::wstring dbPath = m_qqRootPath + L"\\" + account + DBName;
	SQLiteHelper sqlite;

	try
	{
		if ( !sqlite.ConnectToDatabase(dbPath) )
			throw 1;

		std::wstring tableName = L"tb_c2cMsg_";
		tableName += friendAccount;

		std::wstring sqlValue = L"select datetime(time,'unixepoch','localtime'), content, flag from ";
		sqlValue += tableName;

		if ( !sqlite.Exec(sqlValue) )
			throw 1;

		while ( sqlite.Step() )
		{
			ChatHistory info;
			info.time = sqlite.GetText(0);
			info.message = sqlite.GetText(1);
			info.isSend = ( sqlite.GetValue(2) == 0 );
			info.senderName = ( info.isSend ? account : friendAccount );
			m_chatList.push_back(info);
		}

		sqlite.Finalize();
	}
	catch ( ... )
	{

	}

	sqlite.CloseDatabase();
	return m_chatList;
}

QQParser::GroupInfo 
IOSQQParser::GetGroupInfo( const std::wstring& account, int groupId )
{
	GroupInfo grpInfo;
	grpInfo.groupName = L"∫√”—¡–±Ì";
	grpInfo.groupId = 0;
	grpInfo.memberCount = m_friendList.size();

	return grpInfo;
}

const QQParser::TroopList& 
IOSQQParser::GetTroopList( const std::wstring& account )
{
	m_troopList.clear();
	std::wstring dbPath = m_qqRootPath + L"\\" + account + DBName;
	SQLiteHelper sqlite;

	try
	{
		if ( !sqlite.ConnectToDatabase(dbPath) )
			throw 1;

		if ( !sqlite.Exec(L"select groupcode, groupName from tb_troop") )
			throw 1;

		while ( sqlite.Step() )
		{
			TroopInfo info;
			info.troopNumber = sqlite.GetText(0);
			info.troopName = sqlite.GetText(1);
			m_troopList.push_back(info);
		}

		sqlite.Finalize();
	}
	catch ( ... )
	{

	}

	sqlite.CloseDatabase();
	return m_troopList;
}	

const QQParser::ChatHistoryList& 
IOSQQParser::GetTroopChatHistory( const std::wstring& account, const std::wstring& troopNumber )
{
	m_chatList.clear();
	std::wstring dbPath = m_qqRootPath + L"\\" + account + DBName;
	SQLiteHelper sqlite;

	try
	{
		if ( !sqlite.ConnectToDatabase(dbPath) )
			throw 1;

		std::wstring tableName = L"tb_TroopMsg_";
		tableName += troopNumber;

		std::wstring sqlValue = L"select count(*) from sqlite_master where tbl_name = '";
		sqlValue += tableName;
		sqlValue += L"'";

		if ( !sqlite.Exec(sqlValue) )
			throw 1;

		sqlite.Step();
		int count = sqlite.GetValue(0);

		if ( 0 == count )
			throw 1;

		sqlite.Finalize();

		sqlValue = L"select datetime(MsgTime,'unixepoch','localtime'), strMsg, nickName from ";
		sqlValue += tableName;

		if ( !sqlite.Exec(sqlValue) )
			throw 1;

		while ( sqlite.Step() )
		{
			ChatHistory info;
			info.time = sqlite.GetText(0);
			info.message = sqlite.GetText(1);
			info.isSend = false;
			info.senderName = sqlite.GetText(2);
			m_chatList.push_back(info);
		}

		sqlite.Finalize();
	}
	catch ( ... )
	{

	}

	sqlite.CloseDatabase();
	return m_chatList;
}
