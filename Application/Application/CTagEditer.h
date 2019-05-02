#ifndef _C_TagEditer_H_
#define _C_TagEditer_H_

#include <QString>
#include <QFile>

struct Tags
{
	QString Title;
	QString Artist;
	QString Album;
	QString Genre;
	QString Year;
	QString Bitrate;
	QString Duraction;
};

enum class ETag : ushort
{
	Unknown = 0,
	Title,
	Artist,
	Album,
	Genre,
	Year,
	Bitrate,
	Duraction,
};

class CTagEditer
{
public:
	CTagEditer();
	CTagEditer(QString path);
	~CTagEditer();

public:
	void Open(QString path);
	Tags GetTags();

private:
	QFile m_file;
	ETag m_tag = ETag::Unknown;
};

#endif

