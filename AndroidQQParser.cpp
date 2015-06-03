#include "AndroidQQParser.h"

#include <Windows.h>
#include <QtSql>

#include "utility.h"
#include "SQLiteHelper.h"
#include "XmlReader.h"

#include <openssl/md5.h>
#include <algorithm>
#include <cwctype>

const std::wstring QQSubPath(L"\\data\\data\\com.tencent.mobileqq");
const std::wstring DbSubPath(L"\\databases");

const std::wstring Xml_IMEI(L"\\shared_prefs\\appcenter_mobileinfo.xml");
const std::wstring Xml_IMEI2(L"\\shared_prefs\\contact_bind_info");

AndroidQQParser::AndroidQQParser(const std::wstring& dataPath)
	: QQParser(dataPath)
{

}

AndroidQQParser::~AndroidQQParser()
{

}

void AndroidQQParser::Init()
{
	GetIMEI();
}

void AndroidQQParser::GetIMEI()
{
	QtXmlReader xml;
	xml.Load(m_dataPath + QQSubPath + Xml_IMEI);

	m_imei = xml.GetContentByName(L"string", L"imei");

	// Some device made in China needs to get the unique ID in upper case.
	/*if ( m_imei.empty() )
	{
		xml.Load(m_dataPath + QQSubPath + Xml_IMEI2);
		m_imei = xml.GetContentByName(L"string", L"QIMEI_DENGTA");
		std::transform(m_imei.begin(), m_imei.end(), m_imei.begin(), std::towupper);
	}*/
}

const std::list<std::wstring>& AndroidQQParser::GetAccountList()
{
	m_accountList.clear();

	WIN32_FIND_DATAW fd = {0};
	std::wstring findPath = m_dataPath + QQSubPath + DbSubPath;
	std::wstring findStr = findPath + L"\\*.db";

	HANDLE findHandle = FindFirstFile(findStr.c_str(), &fd);

	try
	{
		if ( INVALID_HANDLE_VALUE == findHandle )
			throw 1;

		do 
		{
			if ( fd.cFileName[0] > L'0' && fd.cFileName[0] <= L'9' )
			{
				std::wstring dbName = fd.cFileName;
				std::wstring account = dbName.substr(0, dbName.length() - 3);
				m_accountList.push_back(account);
			}

		} while ( FindNextFile(findHandle, &fd) );

		FindClose(findHandle);
	}
	catch (...)
	{
	}

	return m_accountList;
}

const QQParser::FriendList& AndroidQQParser::GetFriendList(const std::wstring& account)
{
	m_friendList.clear();

	std::wstring dbFile = GenerateDbPath(account);

	if ( m_imei.empty() )
	{
		QtXmlReader xml;
		xml.Load(m_dataPath + QQSubPath + Xml_IMEI2 + account + L".xml");
		m_imei = xml.GetContentByName(L"string", L"contact_bind_info_unique");

		assert(m_imei.size() > 15);
		m_imei = m_imei.substr(0, 15);
	}

	std::string key = WideToAnsi(m_imei);

	SQLiteHelper sqlite;

	try
	{

		if ( !sqlite.ConnectToDatabase(dbFile) )
			throw 1;

		if ( !sqlite.Exec(L"select uin, name, remark, signature, richBuffer, groupId from Friends") )
			throw 1;

		while ( sqlite.Step() )
		{
			__int64 size = 0;

			const char* enUin = sqlite.GetData(0, &size);
			std::wstring uin = XorDecrypt(enUin, size, key.c_str());

			const char* enName = sqlite.GetData(1, &size);
			std::wstring name = XorDecrypt(enName, size, key.c_str());

			const char* enRemark = sqlite.GetData(2, &size);
			std::wstring remark = XorDecrypt(enRemark, size, key.c_str());

			const char* enSignature = sqlite.GetData(4, &size);
			std::wstring signature = XorDecrypt(enSignature, size, key.c_str(), true);

			FriendInfo info = {uin, name, remark, signature, sqlite.GetValue(5)};
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

const QQParser::ChatHistoryList&
AndroidQQParser::GetChatHistory(const std::wstring& account, const std::wstring& friendAccount)
{
	std::wstring hash = GetHashFromAccount(friendAccount);
	wchar_t sqlValue[1024] = {0};
	wsprintfW(
		sqlValue, 
		L"select mr_friend_%s_New.msgData, "
		L"datetime(mr_friend_%s_New.time,'unixepoch','localtime'), "
		L"mr_friend_%s_New.issend, "
		L"Friends.name "
		L"from mr_friend_%s_New, Friends "
		L"where mr_friend_%s_New.senderuin = Friends.uin", 
		hash.c_str(),
		hash.c_str(),
		hash.c_str(),
		hash.c_str(),
		hash.c_str());

	return GetChatHistoryImpl(account, sqlValue);
}

const QQParser::ChatHistoryList& 
AndroidQQParser::GetChatHistoryImpl(const std::wstring& account, const std::wstring& sqlValue)
{
	m_chatHistoryList.clear();
	std::wstring dbFile = GenerateDbPath(account);
	SQLiteHelper sqlite;

	std::string key = WideToAnsi(m_imei).c_str();

	try
	{
		sqlite.ConnectToDatabase(dbFile);

		// If the table didn't exist, this function failed.
		if ( !sqlite.Exec(sqlValue) )
			throw 1;

		while ( sqlite.Step() )
		{
			__int64 size = 0;
			const char* msgData = sqlite.GetData(0, &size);
			std::wstring msgString = XorDecrypt(msgData, size, key.c_str(), true);

			ChatHistory info;
			info.time = sqlite.GetText(1);
			info.message = msgString;
			info.isSend = sqlite.GetValue(2);

			const char* enSender = sqlite.GetData(3, &size);
			info.senderName = XorDecrypt(enSender, size, key.c_str());
			m_chatHistoryList.push_back(info);
		}
	}
	catch( ... )
	{
	}

	sqlite.Finalize();
	sqlite.CloseDatabase();

	return m_chatHistoryList;
}

QQParser::GroupInfo AndroidQQParser::GetGroupInfo(const std::wstring& account, int groupId)
{
	GroupInfo group;
	group.groupId = -1;
	group.groupName = L"自己";
	group.memberCount = 1;

	wchar_t sqlValue[1024] = {0};
	wsprintfW(sqlValue, L"select group_name, group_friend_count from Groups where group_id = %d", groupId);

	std::wstring dbFile = GenerateDbPath(account);
	SQLiteHelper sqlite;

	std::string key = WideToAnsi(m_imei).c_str();

	try
	{
		sqlite.ConnectToDatabase(dbFile);

		if ( !sqlite.Exec(sqlValue) )
			throw 1;

		while ( sqlite.Step() )
		{
			__int64 size;
			const char* enGroupName = sqlite.GetData(0, &size);
			group.groupId = groupId;
			group.groupName = XorDecrypt(enGroupName, size, key.c_str());
			group.memberCount = sqlite.GetValue(1);
		}
	}
	catch( ... )
	{
	}

	sqlite.Finalize();
	sqlite.CloseDatabase();

	return group;
}

const QQParser::TroopList& AndroidQQParser::GetTroopList(const std::wstring& account)
{
	m_troopList.clear();
	std::wstring dbFile = GenerateDbPath(account);

	SQLiteHelper sqlite;

	std::string key = WideToAnsi(m_imei);

	try
	{
		if ( !sqlite.ConnectToDatabase(dbFile) )
			throw 1;

		if ( !sqlite.Exec(L"select troopuin, troopname, troopmemo from TroopInfo") )
			throw 1;

		while ( sqlite.Step() )
		{
			__int64 size = 0;
			const char* enTroopNumber = sqlite.GetData(0, &size);
			std::wstring troopNumber = XorDecrypt(enTroopNumber, size, key.c_str());
			const char* enTroopName = sqlite.GetData(1, &size);
			std::wstring troopName = XorDecrypt(enTroopName, size, key.c_str());
			const char* enTroopMemo = sqlite.GetData(2, &size);
			std::wstring troopMemo = XorDecrypt(enTroopMemo, size, key.c_str());

			TroopInfo info = {troopNumber, troopName, troopMemo};
			m_troopList.push_back(info);

			//__TRACE(L"%s\r\n%s\r\n%s\r\n%s\r\n\r\n", troopNumber.c_str(), troopName.c_str(), troopMemo.c_str(), admin.c_str());
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
AndroidQQParser::GetTroopChatHistory(const std::wstring& account, const std::wstring& troopNumber)
{
	std::wstring hash = GetHashFromAccount(troopNumber);
	wchar_t sqlValue[1024] = {0};

	wsprintfW(
		sqlValue, 
		L"select mr_troop_%s_New.msgData, "
		L"datetime(mr_troop_%s_New.time,'unixepoch','localtime'), "
		L"mr_troop_%s_New.issend, "
		L"TroopMemberInfo.troopnick "
		L"from mr_troop_%s_New, TroopMemberInfo "
		L"where mr_troop_%s_New.senderuin = TroopMemberInfo.memberuin",
		hash.c_str(),
		hash.c_str(),
		hash.c_str(),
		hash.c_str(),
		hash.c_str());

	return GetChatHistoryImpl(account, sqlValue);
}

std::wstring AndroidQQParser::XorDecrypt(const char* src, int srcLen, const char* key, bool isNew)
{
	int keyLen = strlen(key);
	char buffer[1024 * 10] = {0};

	if ( keyLen == 0 || srcLen > 1024*10 )
		return L"";

	int magic = 0;

	for ( int i = 0, decode = 0; i < srcLen; ++i, ++decode )
	{
		if ( !isNew && (BYTE)src[i] >= 128 )
		{
			char curChar = key[decode%keyLen];

			// 根据分析得知，当遍历到某个单字时，
			// 如果 src 为汉字且 key 为字母，
			// 需要用此种异或方式来解密 :
			// 第一个字节原封不动，第二个字节和 1 异或，
			// 第三个字节和字母转换成的数字异或 ( A - 1， B - 2 ) ...
			if ( curChar >= 'A'
				&& curChar <= 'Z' )
			{
				buffer[i] = src[i];
				buffer[i+1] = src[i+1] ^ 0x01;
				buffer[i+2] = src[i+2] ^ (curChar-'A'+1);
				i += 2;
				continue;
			}

			buffer[i] = src[i];
			buffer[i+1] = src[i+1];
			i += 2;
		}

		buffer[i] = src[i] ^ key[decode%keyLen];
	}

	return Utf8ToWide(buffer);
}

std::wstring AndroidQQParser::GetHashFromAccount(const std::wstring& account)
{
	std::string md5Src = WideToAnsi(account);
	unsigned char hash[16] = {0};
	MD5_CTX c = {0};
	MD5_Init(&c);
	MD5_Update(&c, md5Src.c_str(), strlen(md5Src.c_str()));
	MD5_Final(hash, &c);

	char hex[1024] = {0};
	for ( int i = 0; i < 16; ++i )
		sprintf(hex+2*i, "%.2X", hash[i]);

	return AnsiToWide(hex);
}

std::wstring AndroidQQParser::GenerateDbPath( const std::wstring& account )
{
	return m_dataPath + QQSubPath + DbSubPath + L"\\" + account + L".db";
}
