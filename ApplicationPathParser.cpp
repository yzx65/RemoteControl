#include "ApplicationPathParser.h"
#include <Plist.hpp>
#include "utility.h"

#ifdef _DEBUG
#pragma comment(lib, "PlistCppd.lib")
#else
#pragma comment(lib, "PlistCpp.lib")
#endif

const std::wstring PlistPath(L"\\var\\mobile\\Library\\Caches\\com.apple.mobile.installation.plist");

ApplicationPathParer& ApplicationPathParer::CreateInstance()
{
	static ApplicationPathParer parser;
	return parser;
}

bool ApplicationPathParer::Load( const std::wstring& dataPath )
{
	std::wstring plistFile = dataPath + PlistPath;


	if ( !FileExist(plistFile) )
		return false;

	if ( m_plistPath == plistFile )
		return true;

	m_plistPath = plistFile;
	
	m_dict.clear();
	Plist::readPlist(m_plistPath.c_str(), m_dict);
	return true;
}

std::wstring ApplicationPathParer::GetApplicationPath( const std::wstring& appName )
{
	std::map<std::string, boost::any> users
		= boost::any_cast<std::map<std::string, boost::any> >(m_dict["User"]);

	if ( users.end() == users.find(WideToAnsi(appName)) )
		return L"";

	std::map<std::string, boost::any> appDict
		= boost::any_cast<std::map<std::string, boost::any> >(users[WideToAnsi(appName)]);

	std::wstring result = AnsiToWide( boost::any_cast<std::string>(appDict["Container"]) );
	
	std::wstring::size_type pos = result.find(L'/');

	while ( pos != std::wstring::npos )
	{
		result = result.replace(pos, 1, L"\\");
		++pos;
		pos = result.find(L'/', pos);
	}

	return result;
}

std::wstring ApplicationPathParer::GetApplicationPathOrigin( const std::wstring& appName )
{
	std::map<std::string, boost::any> users
		= boost::any_cast<std::map<std::string, boost::any> >(m_dict["User"]);

	if ( users.end() == users.find(WideToAnsi(appName)) )
		return L"";

	std::map<std::string, boost::any> appDict
		= boost::any_cast<std::map<std::string, boost::any> >(users[WideToAnsi(appName)]);

	std::wstring result = AnsiToWide( boost::any_cast<std::string>(appDict["Container"]) );

	return result;
}

