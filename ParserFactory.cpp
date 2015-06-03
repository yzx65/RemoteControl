#include "ParserFactory.h"

#include "AndroidWeinxinParser.h"
#include "AndroidQQParser.h"
#include "IOSQQParser.h"
#include "IOSWeixinParser.h"
#include "RemoteQQParser.h"
#include "RemoteWeixinParser.h"

ParserFactory::ParserFactory(ParserFactory::SystemType system, const std::wstring& dataPath)
	: m_system(system)
	, m_dataPath(dataPath)
{

}

WeixinParser* ParserFactory::CreateWeixinParser()
{
	WeixinParser* parser = NULL;

	switch ( m_system )
	{
	case ANDROID:
		parser = new AndroidWeinxinParser(m_dataPath);
		break;

	case IOS:
		parser = new IOSWeixinParser(m_dataPath);
		break;

	case REMOTE:
		parser = new RemoteWeixinParser(m_dataPath);
		break;
	}

	return parser;
}

QQParser* ParserFactory::CreateQQParser()
{
	QQParser* parser = NULL;

	switch ( m_system )
	{
	case ANDROID:
		parser = new AndroidQQParser(m_dataPath);
		break;

	case IOS:
		parser = new IOSQQParser(m_dataPath);
		break;

	case REMOTE:
		parser = new RemoteQQParser(m_dataPath);
		break;
	}

	return parser;
}