#include "CTagEditer.h"



CTagEditer::CTagEditer()
{
}


CTagEditer::~CTagEditer()
{
}

void CTagEditer::Open(QString path)
{
	m_path = path;
}

Tags CTagEditer::GetTags()
{
	QFile file(m_path);
	file.open(QIODevice::ReadOnly);

	QTextStream in(&file);
	in.setCodec("UTF-8");

	Tags tags;
	m_tag = ETag::Title;

	while (!in.atEnd())
	{
		QString line = in.readLine();

		switch (m_tag)
		{
		case ETag::Title:
			tags.Title = line;
			m_tag = ETag::Artist;
			break;
		case ETag::Artist:
			tags.Artist = line;
			m_tag = ETag::Album;
			break;
		case ETag::Album:
			tags.Album = line;
			m_tag = ETag::Genre;
			break;
		case ETag::Genre:
			tags.Genre = line;
			m_tag = ETag::Year;
			break;
		case ETag::Year:
			tags.Year = line;
			m_tag = ETag::Bitrate;
			break;
		case ETag::Bitrate:
			tags.Bitrate = line;
			m_tag = ETag::Duraction;
			break;
		case ETag::Duraction:
			tags.Duraction = line;
			m_tag = ETag::Unknown;
			break;
		}
	}
	file.close();
	return tags;
}
