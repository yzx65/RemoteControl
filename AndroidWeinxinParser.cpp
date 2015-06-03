#include "AndroidWeinxinParser.h"
#include "SQLiteHelper.h"
#include "XmlReader.h"
#include "utility.h"

#include <Windows.h>
#include <openssl/md5.h>
#include <QtSql>
#include <QDateTime>

const std::wstring WeixinSubPath(L"\\data\\data\\com.tencent.mm");
const std::wstring DbParentDir(L"\\MicroMsg");

const std::wstring DbName(L"\\EnMicroMsg.db");
const std::wstring DecryptDbName(L"\\DecryptMicroMsg.db");
const std::wstring Xml_IMEI(L"\\shared_prefs\\settinginfo.xml");
const std::wstring Xml_uin(L"\\shared_prefs\\system_config_prefs.xml");
const std::wstring Xml_IMEI2(L"\\MicroMsg\\CompatibleInfo.cfg");

std::wstring GetImeiFromQQ(const std::wstring& dataPath)
{
	const std::wstring QQSubPath(L"\\data\\data\\com.tencent.mobileqq");
	const std::wstring Xml_IMEI(L"\\shared_prefs\\appcenter_mobileinfo.xml");

	QtXmlReader xml;
	xml.Load(dataPath + QQSubPath + Xml_IMEI);

	std::wstring imei = xml.GetContentByName(L"string", L"imei");

	return imei;
}

std::wstring GetImeiFromJavaMap(const std::wstring& dataPath)
{
	std::wstring filePath = dataPath + WeixinSubPath + Xml_IMEI2;
	HANDLE hf = CreateFileW(filePath.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
		return L"";

	int fileSize = GetFileSize(hf, NULL);
	char* buffer = new char[fileSize];
	DWORD dump = 0;
	ReadFile(hf, buffer, fileSize, &dump, NULL);

	char imei[1024] = {0};
	memcpy(imei, buffer + 0x91, 15);

	delete [] buffer;
	CloseHandle(hf);
	return AnsiToWide(imei);
}

AndroidWeinxinParser::AndroidWeinxinParser(const std::wstring& datapath)
	: WeixinParser(datapath)
	, m_dbDecryptFileName(datapath + DecryptDbName)
{
	GetDbPath();
}

void AndroidWeinxinParser::GetDbPath()
{
	WIN32_FIND_DATAW fd = {0};
	std::wstring parentDir = m_dataPath + WeixinSubPath + DbParentDir;
	std::wstring findStr = parentDir + L"\\*.*";
	m_dbFileName.clear();

	HANDLE find = FindFirstFileW(findStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == find )
		return;


	do 
	{
		if ( wcslen(fd.cFileName) == wcslen(L"af090520275105bfa78a7759d43507b3") )
		{
			std::wstring dbFileName = parentDir;
			dbFileName += L"\\";
			dbFileName += fd.cFileName;
			dbFileName += DbName;
			AccountInfo info;
			info.weixinId = fd.cFileName;
			m_accountList.push_back(info);
			m_dbFileName.push_back(dbFileName);
		}
	} while ( FindNextFile(find, &fd) );

	FindClose(find);
}

AndroidWeinxinParser::~AndroidWeinxinParser()
{
	DeleteFileW(m_dbDecryptFileName.c_str());
}

void AndroidWeinxinParser::Init()
{
	QtXmlReader xml;
	xml.Load(m_dataPath + WeixinSubPath + Xml_uin);
	std::wstring uin = xml.GetValueByName(L"int", L"default_uin");

	xml.Load(m_dataPath + WeixinSubPath + Xml_IMEI);
	std::wstring imei = xml.GetContentByName(L"string", L"IMEI");

	// If we have got the imei, cast the first "imei:" string.
	// Otherwise, try to get the imei from QQ config file.
	if ( imei.empty() )
		imei = GetImeiFromQQ(m_dataPath);
	else
		imei = imei.substr(5, imei.length()-5);

	if ( imei.empty() )
		imei = GetImeiFromJavaMap(m_dataPath);

	if ( imei.empty() || uin.empty() )
		return;

	// Get MD5 hash
	std::string md5Src = WideToAnsi(imei + uin);
	unsigned char hash[16] = {0};
	MD5_CTX c = {0};
	MD5_Init(&c);
	MD5_Update(&c, md5Src.c_str(), strlen(md5Src.c_str()));
	MD5_Final(hash, &c);

	// Convert hash to Hex string
	char hex[1024] = {0};
	for ( int i = 0; i < 16; ++i )
		sprintf(hex+2*i, "%.2x", hash[i]);

	// Db's password is the first 7 characters.
	std::string password(hex);
	password = password.substr(0, 7);

	// Get a database which has a correct format.
	AccountList::iterator ita = m_accountList.begin();
	for ( std::list<std::wstring>::iterator it = m_dbFileName.begin();
		  it != m_dbFileName.end();
		  ++it, ++ita )
	{
		std::wstring dbFileName = (*it);
		SQLiteHelper::DecryptDatabaseFile(dbFileName, m_dbDecryptFileName, password.c_str());

		SQLiteHelper sqlite;

		if ( sqlite.ConnectToDatabase(m_dbDecryptFileName) )
		{
			if ( sqlite.Exec(L"select * from sqlite_master") )
			{
				sqlite.Finalize();
				sqlite.CloseDatabase();

				std::wstring account = ita->weixinId;
				m_accountList.clear();
				AccountInfo info;
				info.weixinId = account;
				m_accountList.push_back(info);

				break;
			}
		}

		DeleteFileW(m_dbDecryptFileName.c_str());
	}
}

const WeixinParser::AccountList& AndroidWeinxinParser::GetAccountList()
{
	return m_accountList;
}

const WeixinParser::FriendList& AndroidWeinxinParser::GetFriendList(const std::wstring& account)
{
	m_friendList.clear();

	SQLiteHelper sqlite;
	sqlite.ConnectToDatabase(m_dbDecryptFileName);

	try
	{
		if ( !sqlite.Exec(L"select userName, nickName, weiboNickname, type from rcontact") )
			throw 1;

		while ( sqlite.Step() )
		{
			FriendInfo info;
			info.userName = sqlite.GetText(0);
			info.nickName = sqlite.GetText(1);
			info.alias = sqlite.GetText(2);
			info.type = sqlite.GetValue(3);
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
AndroidWeinxinParser::GetChatHistory(const std::wstring& account, const std::wstring& userName)
{
	m_chatHistoryList.clear();

	SQLiteHelper sqlite;
	sqlite.ConnectToDatabase(m_dbDecryptFileName);

	wchar_t sqlValue[1024] = {0};
	wsprintfW(
		sqlValue, 
		L"select type, isSend, createTime, content, imgPath from message where talker = '%s' order by createTime",
		userName.c_str());

	sqlite.Exec(sqlValue);

	while ( sqlite.Step() )
	{
		ChatHistory historyNode;
		historyNode.msgType = sqlite.GetValue(0);
		historyNode.isSend = sqlite.GetValue(1);
		__int64 timeMs = sqlite.GetValue(2);
		QDateTime time = QDateTime::fromMSecsSinceEpoch(timeMs);
		historyNode.time = time.toString("yyyy-MM-dd hh:mm:ss").toStdWString();
		historyNode.message = sqlite.GetText(3);
		historyNode.filePath = sqlite.GetText(4);
		m_chatHistoryList.push_back(historyNode);
	}

	sqlite.Finalize();
	sqlite.CloseDatabase();

	return m_chatHistoryList;
}

