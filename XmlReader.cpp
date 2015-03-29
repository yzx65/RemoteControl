#include "XmlReader.h"
#include <QDomDocument>
#include <QFile>

#include "utility.h"

QtXmlReader::QtXmlReader()
	: m_doc(NULL)
	, m_file(NULL)
{
	m_doc = new QDomDocument;
}

QtXmlReader::~QtXmlReader()
{
	if ( m_file )
		m_file->close();

	delete m_file;
	delete m_doc;
}

bool QtXmlReader::Load( const std::wstring& file )
{
	if ( m_file )
	{
		m_file->close();
		delete m_file;
	}

	m_file = new QFile(QString::fromStdWString(file));

	if ( !m_file->open(QIODevice::ReadOnly | QIODevice::Text) )
	{
		__TRACE(L"[XmlReader] Load XML File Failed.[%s]\r\n", file.c_str());
		m_file = NULL;
		return false;
	}

	if ( !m_doc->setContent(m_file, false) )
	{
		__TRACE(L"[XmlReader] Prase XML File Failed.[%s]\r\n", file.c_str());
		return false;
	}

	return true;
}

std::wstring QtXmlReader::GetValueByName(const std::wstring& tag, const std::wstring& name)
{
	QDomNodeList result = m_doc->elementsByTagName(QString::fromStdWString(tag));
	int count = result.count();

	for ( int i = 0; i < count; ++i )
	{
		QDomElement element = result.at(i).toElement();

		if ( element.attribute("name").toStdWString() == name )
			return element.attribute("value").toStdWString();
	}

	return L"";
}

std::wstring QtXmlReader::GetContentByName(const std::wstring& tag, const std::wstring& name)
{
	QDomNodeList result = m_doc->elementsByTagName(QString::fromStdWString(tag));
	int count = result.count();

	for ( int i = 0; i < count; ++i )
	{
		QDomElement element = result.at(i).toElement();

		if ( element.attribute("name").toStdWString() == name )
			return element.text().toStdWString();
	}

	return L"";
}
