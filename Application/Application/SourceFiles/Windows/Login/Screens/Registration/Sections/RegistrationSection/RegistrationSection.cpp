#include "StdAfx.h"
#include "RegistrationSection.h"

RegistrationSection::RegistrationSection()
	: ISectionObject(gParams->pSocket)
{
	gParams->pRootContext->setContextProperty("RegistrationSection", this);
}

RegistrationSection::~RegistrationSection()
{
}

void RegistrationSection::Initialize()
{
	connect(this, &RegistrationSection::entered, this, [=](){

		QCryptographicHash hash(QCryptographicHash::Keccak_512);
		int length = hash.hashLength(QCryptographicHash::Keccak_512);

		hash.addData(QString(m_username + m_password).toLatin1());

		Query query;
		query.InsertIntoHeader("hashCode", QString::fromLatin1(hash.result(), length));

		gParams->pSettings->setValue("User/remember", m_remember);
		gParams->pSettings->setValue("User/hashCode", QString::fromLatin1(hash.result(), length));

		if (m_type == Enum::ETypeEnter::Login)
		{
			query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Check_This_User));
		}
		else if (m_type == Enum::ETypeEnter::Registration)
		{
			query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Create_New_User));
		}

		emit sendToSocket(this, query.toByteArray());

	});

	qmlRegisterUncreatableMetaObject(Enum::staticMetaObject, "packages.sections.registration", 1, 0, "Enum", QStringLiteral("Cannot create RegistrationSection in QML"));
	qRegisterMetaType<Enum::ETypeEnter>("ETypeEnter");

	m_remember = gParams->pSettings->value("User/remember").toBool();

	if (m_remember)
	{
		QString hash = gParams->pSettings->value("User/hashCode").toString();

		Query query;
		query.InsertIntoHeader("hashCode", hash);
		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Check_This_User));
		
		emit sendToSocket(this, query.toByteArray());
	}
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
		emit success();
		break;
	}
	case ETypeResultQuery::DuplicateUsername:
	{
		emit duplicateUsername();
		break;
	}
	case ETypeResultQuery::UserIsNotFound:
	{
		emit userIsNotFound();
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