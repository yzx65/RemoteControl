#include "IOSWeixinParser.h"
#include "ApplicationPathParser.h"
#include "SQLiteHelper.h"
#include "utility.h"

#include <Windows.h>
#include <openssl/md5.h>

#include <QDateTime>

const std::wstring WeinxinDomain(L"com.tencent.xin");
const std::wstring WeixinSubPath(L"\\Documents");
const std::wstring DBName(L"\\DB\\MM.sqlite");

IOSWeixinParser::IOSWeixinParser( const std::wstring& dataPath )
	: WeixinParser(dataPath)
{

}

void IOSWeixinParser::Init()
{
	ApplicationPathParer& pathParser = ApplicationPathParer::CreateInstance();

	if ( !pathParser.Load(m_dataPath) )
		return;

	m_weixinRoot = m_dataPath + pathParser.GetApplicationPath(WeinxinDomain) + WeixinSubPath;
}

const WeixinParser::AccountList& IOSWeixinParser::GetAccountList()
{
	m_accountList.clear();

	std::wstring findStr = m_weixinRoot + L"\\*.*";
	std::wstring result;

	try
	{
		WIN32_FIND_DATAW fd = {0};
		HANDLE hf = FindFirstFileW(findStr.c_str(), &fd);

		if ( INVALID_HANDLE_VALUE == hf )
			throw 1;

		do 
		{
			if ( wcslen(fd.cFileName) == wcslen(L"aaf6e8a830a8e128101f0d611dd86c68") 
				&& fd.cFileName[0] != L'0' )
			{
				AccountInfo info;
				info.weixinId = fd.cFileName;
				m_accountList.push_back(info);
			}

		} while ( FindNextFileW(hf, &fd) );

		result = fd.cFileName;

		FindClose(hf);
	}
	catch( ... )
	{

	}

	return m_accountList;
}

const WeixinParser::FriendList& IOSWeixinParser::GetFriendList(const std::wstring& account)
{
	m_friendList.clear();

	m_dbFile = m_weixinRoot + L"\\" + account + DBName;

	if ( !FileExist(m_dbFile) )
		return m_friendList;

	SQLiteHelper sqlite;

	try
	{
		if ( !sqlite.ConnectToDatabase(m_dbFile) )
			throw 1;

		if ( !sqlite.Exec(L"select UsrName, NickName from Friend") )
			throw 1;

		while ( sqlite.Step() )
		{
			FriendInfo info;
			info.userName = sqlite.GetText(0);
			info.nickName = sqlite.GetText(1);
			m_friendList.push_back(info);
		}
	}
	catch ( ... )
	{

	}

	sqlite.Finalize();
	sqlite.CloseDatabase();

	return m_friendList;
}

const WeixinParser::ChatHistoryList& 
IOSWeixinParser::GetChatHistory(const std::wstring& account, const std::wstring& userName )
{
	m_chatHistory.clear();
	std::wstring tableName = GetTableNameFromUserName(userName);
	SQLiteHelper sqlite;
	m_dbFile = m_weixinRoot + L"\\" + account + DBName;

	try
	{
		if ( !sqlite.ConnectToDatabase(m_dbFile) )
			throw 1;

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

		sqlValue = L"select datetime(CreateTime,'unixepoch','localtime'), Type, Status, Message from ";
		sqlValue += tableName;
		if ( !sqlite.Exec(sqlValue) )
			throw 1;

		while ( sqlite.Step() )
		{
			ChatHistory history;
			history.time = sqlite.GetText(0);
			history.msgType = sqlite.GetValue(1);
			history.isSend = ( 2 == sqlite.GetValue(2) );
			history.message = sqlite.GetText(3);
			m_chatHistory.push_back(history);
		}
	}
	catch ( ... )
	{

	}

	sqlite.Finalize();
	sqlite.CloseDatabase();

	return m_chatHistory;
}

std::wstring IOSWeixinParser::GetAccountDir()
{
	std::wstring findStr = m_weixinRoot + L"\\*.*";
	std::wstring result;

	try
	{
		WIN32_FIND_DATAW fd = {0};
		HANDLE hf = FindFirstFileW(findStr.c_str(), &fd);

		if ( INVALID_HANDLE_VALUE == hf )
			throw 1;

		do 
		{
			if ( wcslen(fd.cFileName) == wcslen(L"aaf6e8a830a8e128101f0d611dd86c68") 
				&& fd.cFileName[0] != L'0' )
				break;

		} while ( FindNextFileW(hf, &fd) );

		result = fd.cFileName;

		FindClose(hf);
	}
	catch( ... )
	{

	}

	return result;
}

std::wstring IOSWeixinParser::GetTableNameFromUserName(const std::wstring& userName)
{
	std::string md5Src = WideToAnsi(userName);
	unsigned char hash[16] = {0};
	MD5_CTX c = {0};
	MD5_Init(&c);
	MD5_Update(&c, md5Src.c_str(), strlen(md5Src.c_str()));
	MD5_Final(hash, &c);

	char hex[1024] = {0};
	for ( int i = 0; i < 16; ++i )
		sprintf(hex+2*i, "%.2x", hash[i]);

	char table[1024] = {0};
	sprintf(table, "Chat_%s", hex);

	return AnsiToWide(table);
}
