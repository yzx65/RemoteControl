#ifndef XMLREADER
#define XMLREADER

#include <string>

class XmlReader
{
public:
	virtual ~XmlReader() {}
	virtual bool Load(const std::wstring& file) = 0;
	virtual std::wstring GetValueByName(const std::wstring& tag, const std::wstring& name) = 0;
	virtual std::wstring GetContentByName(const std::wstring& tag, const std::wstring& name) = 0;
};

class QDomDocument;
class QFile;
class QtXmlReader : public XmlReader
{
public:
	QtXmlReader();
	~QtXmlReader();

	bool Load(const std::wstring& file);
	std::wstring GetValueByName(const std::wstring& tag, const std::wstring& name);
	std::wstring GetContentByName(const std::wstring& tag, const std::wstring& name);

private:
	QDomDocument* m_doc;
	QFile* m_file;
};

#endif // XMLREADER