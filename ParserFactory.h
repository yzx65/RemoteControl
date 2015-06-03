/*!
	Description : Use this class to create parser.
	Author		: Ruining Song
	Date		: 2014/08/20
*/

#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H

#include <string>

class QQParser;
class WeixinParser;

class ParserFactory
{
public:
	enum SystemType{WINDOWS, MACOSX, IOS, ANDROID, REMOTE};

	ParserFactory(SystemType system, const std::wstring& dataPath);
	QQParser* CreateQQParser();
	WeixinParser* CreateWeixinParser();

private:
	SystemType m_system;
	const std::wstring& m_dataPath;
};

#endif // PARSERFACTORY_H