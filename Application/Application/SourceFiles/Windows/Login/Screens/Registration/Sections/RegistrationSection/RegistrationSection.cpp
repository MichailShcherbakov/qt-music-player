#include "RegistrationSection.h"

#include "TagEditer/TagEditer.h"

RegistrationSection::RegistrationSection(const EParams* const params)
	: ISectionObject(params->m_pSocket),
	m_pParams(params)
{
}

RegistrationSection::~RegistrationSection()
{
}

void RegistrationSection::Initialize()
{
}

void RegistrationSection::ReadyRead(QByteArray package)
{
}

void RegistrationSection::GottenData(QByteArray data)
{
	Query result;
	result.fromByteArray(data);

	ETypeResultQuery res = static_cast<ETypeResultQuery>(result.GetFromHeader("query-result").toInt());

	switch (res)
	{
	case ETypeResultQuery::Success:
	{
		emit onSuccess();
		break;
	}
	case ETypeResultQuery::DuplicateUsername:
	{
		emit onDuplicateUsername();
		break;
	}
	case ETypeResultQuery::UserIsNotFound:
	{
		emit onUserIsNotFound();
		break;
	}
	}
}


/*QFile f("C:/Users/User/Desktop/music/" + QString::number(i) + ".mp3");
				f.open(QIODevice::ReadOnly);
				QByteArray media = f.readAll();
				f.close();

				CTagEditer tag;
				Tags tags = tag.GetTags("C:/Users/User/Desktop/music/" + QString::number(i) + ".mp3");
				QByteArray image = tag.GetCoverArt("C:/Users/User/Desktop/music/" + QString::number(i) + ".mp3");

				Query q;
				q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Add_New_Media));
				q.InsertIntoBody("media", QString::fromLatin1(media, media.size()));
				q.InsertIntoBody("title", tags.Title);
				q.InsertIntoBody("album", tags.Album);
				q.InsertIntoBody("artist", tags.Artist);
				q.InsertIntoBody("bitrate", tags.Bitrate);
				q.InsertIntoBody("duration", tags.Duration);
				q.InsertIntoBody("genre", tags.Genre);
				q.InsertIntoBody("cover-art", QString::fromLatin1(image, image.size()));
				q.InsertIntoBody("lyric", tags.Lyric);
				q.InsertIntoBody("lyrics-translation", tags.LyricsTranslation);

				if (!albums.isEmpty() && albums.contains(tags.Album))
				{
					q.InsertIntoBody("create-new-album", false);
				}
				else
				{
					q.InsertIntoBody("create-new-album", true);
					albums.append(tags.Album);
				}

				if (!artist.isEmpty() && artist.contains(tags.Artist))
				{
					q.InsertIntoBody("create-new-artist", false);
				}
				else
				{
					q.InsertIntoBody("create-new-artist", true);
					artist.append(tags.Artist);
				}

				emit onSendToSocket(this, q.toByteArray());*/