#include "FavoriteParser.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

#include "Utility.h"

FavoriteParser::FavoriteParser()
	: m_file(NULL)
	, m_stream(NULL)
	, m_doc(NULL)
{
	m_doc = new QDomDocument;
}

FavoriteParser::~FavoriteParser()
{
	if ( m_stream && m_doc )
		m_doc->save(*m_stream, 4);

	if ( m_file )
		m_file->close();

	if ( m_file )
		delete m_file;

	if ( m_stream )
		delete m_stream;

	if ( m_doc )
		delete m_doc;
}

bool FavoriteParser::Load( const std::wstring& file )
{
	if ( m_file )
	{
		m_file->close();
		delete m_file;
		m_file = NULL;
	}

	m_file = new QFile(QString::fromStdWString(file));

	if ( !m_file->open(QIODevice::ReadWrite | QIODevice::Text) )
	{
		__TRACE(L"[XmlReader] Load XML File Failed.[%s]\r\n", file.c_str());
		m_file = NULL;
		return false;
	}

	m_stream = new QTextStream(m_file);
	m_stream->setCodec("UTF-8");
	QString text = m_stream->readAll();

	m_file->close();
	m_file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate );
	m_stream->setDevice(m_file);

	QString errMsg;
	if ( !m_doc->setContent(text, &errMsg) )
	{
		QDomElement root = m_doc->createElement("root");
		m_doc->appendChild(root);
	}

	int count = m_doc->childNodes().count();

	return true;
}

void FavoriteParser::AddFavorite(const std::wstring& name, const std::wstring& path )
{
	QDomElement node = m_doc->createElement("favorite");
	node.setAttribute("name", QString::fromStdWString(name));
	node.setAttribute("path", QString::fromStdWString(path));
	
	m_doc->documentElement().appendChild(node);
}

void FavoriteParser::RemoveFavorite(const std::wstring& name)
{
	QDomElement root = m_doc->documentElement();
	QDomNodeList list = root.childNodes();

	for ( int i = 0; i != list.count(); )
	{
		QDomElement element = list.at(i).toElement();

		if ( element.attribute("name").toStdWString() == name )
			root.removeChild(list.at(i));
		else
			++i;
	}
}

const FavoriteParser::FavoriteList& FavoriteParser::GetFavoriteList()
{
	m_favoriteList.clear();

	QDomElement root = m_doc->documentElement();
	QDomNodeList list = root.childNodes();

	for ( int i = 0; i != list.count(); ++i )
	{
		QDomElement element = list.at(i).toElement();

		FavoriteInfo info = { element.attribute("name").toStdWString(), element.attribute("path").toStdWString() };
		m_favoriteList.push_back(info);
	}

	return m_favoriteList;
}
