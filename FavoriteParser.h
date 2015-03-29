#ifndef FAVORITEPARSER_H
#define FAVORITEPARSER_H

#include <list>
#include <string>

class QDomDocument;
class QFile;
class QTextStream;
class FavoriteParser
{
public:
	FavoriteParser();
	~FavoriteParser();

	bool Load(const std::wstring& file);

	void AddFavorite(const std::wstring& name,  const std::wstring& path);
	void RemoveFavorite(const std::wstring& name);

	struct FavoriteInfo
	{
		std::wstring name;
		std::wstring path;
	};
	typedef std::list<FavoriteInfo> FavoriteList;
	const FavoriteList& GetFavoriteList();

private:
	QDomDocument* m_doc;
	QFile* m_file;
	QTextStream* m_stream;
	FavoriteList m_favoriteList;
};

#endif // FAVORITEPARSER_H