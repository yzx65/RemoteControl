/*!
	Description : Used this class to get ios application's data path
	Author		: Ruining Song
	Date		: 2014/09/05
*/
#ifndef APPLICATIONPATHPARSER_H
#define APPLICATIONPATHPARSER_H

#include <string>
#include <map>
#include <boost/any.hpp>

class ApplicationPathParer
{
public:
	static ApplicationPathParer& CreateInstance();

	/*!
	\param
		IOS root path.
	*/
	bool Load(const std::wstring& dataPath);

	/*!
	\param
		Application domain name.
		eg. com.tencent.xin
	*/
	std::wstring GetApplicationPath(const std::wstring& appName);

	std::wstring GetApplicationPathOrigin(const std::wstring& appName);

private:
	ApplicationPathParer(){};

private:
	std::map<std::string, boost::any> m_dict;
	std::wstring m_plistPath;
};
#endif // APPLICATIONPATHPARSER_H