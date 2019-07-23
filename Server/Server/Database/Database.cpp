#include "Database.h"

Database::Database(QObject *parent)
	: QObject(parent)
{
}

Database::~Database()
{
}

void Database::Initialize()
{
	m_pDatabase = &QSqlDatabase::addDatabase("QMYSQL");
	m_pDatabase->setHostName("localhost");
	m_pDatabase->setUserName("root");
	m_pDatabase->setPassword("root");

	if (!m_pDatabase->open())
	{
		MSG(EMessage::Error, "Can't open the database");
		return;
	}
	else
	{
		MSG(EMessage::Success, "The database is opened");
	}

	QSqlQuery query;

	if (!query.exec("CREATE DATABASE IF NOT EXISTS data_server;"))
	{
		MSG(EMessage::Warning, "Can't create database");
	}

	if (!query.exec("USE data_server;"))
	{
		MSG(EMessage::Error, "Can't use database");
	}

	QString q;
	q = "CREATE TABLE IF NOT EXISTS users ";
	q += "( ";
	q += "id_user INT AUTO_INCREMENT PRIMARY KEY,";
	q += "hashCodeUsers VARCHAR(64) NOT NULL UNIQUE,";
	q += "last_login DATETIME NOT NULL,";
	q += "registration_time DATETIME NOT NULL";
	q += " );";

	if (!query.exec(q))
	{
		MSG(EMessage::Error, "Can't create table");
	}
}

int Database::UsersID(const QByteArray& hash)
{
	QSqlQuery query;

	if (!query.exec("USE data_server;"))
	{
		MSG(EMessage::Error, "Can't use database");
	}

	if (!query.exec("SELECT id_user, hashCodeUsers FROM users;"))
	{
		MSG(EMessage::Error, "Empty or deleted table");
	}

	while (query.next())
	{
		QByteArray t = query.value(1).toString().toLatin1();
		if (t == hash)
		{
			MSG(EMessage::Success, "User is found");
			return query.value(0).toInt();
		}
	}
	MSG(EMessage::Error, "User is not found");
	return -1;
}

void Database::Media(const QByteArray& hash, const int id, QByteArray* const buffer, TypeResultQuery* res)
{
	QSqlQuery query;

	if (!query.exec("USE user_" + QString::number(UsersID(hash)) + ";"))
	{
		MSG(EMessage::Error, "User is not found");
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		return;
	}
	if (!query.exec("SELECT path FROM media WHERE id_media=" + QString::number(id) + ";"))
	{
		MSG(EMessage::Error, "Media is not found");
		res->SetValue(ETypeResultQuery::IsNotFound);
		return;
	}
	QByteArray arr;
	if (query.next())
	{
		QFile f(query.value(0).toString());
		f.open(QIODevice::ReadOnly);
		buffer->clear();
		buffer->append(f.readAll());
		f.close();
	}
	else
	{
		MSG(EMessage::Error, "Media is not found");
		res->SetValue(ETypeResultQuery::IsNotFound);
		return;
	}
	if (buffer->isEmpty())
	{
		MSG(EMessage::Error, "Read error");
		res->SetValue(ETypeResultQuery::ReadError);
		return;
	}

	if (!query.exec("USE user_" + QString::number(UsersID(hash)) + ";"))
	{
		MSG(EMessage::Error, "User is not found");
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		return;
	}

	if (!query.exec("UPDATE media SET last_listened = NOW(), number_times_listened = number_times_listened + 1 WHERE id_media=" + QString::number(id) + ";"))
	{
		MSG(EMessage::Error, "Can't update table \'media\'");
	}

	MSG(EMessage::Success, "Song successfully received");
	res->SetValue(ETypeResultQuery::Success);
}

void Database::CheckUser(const QByteArray& hash, TypeResultQuery* res)
{
	if (UsersID(hash) != -1)
	{
		QSqlQuery query;

		if (!query.exec("USE data_server;"))
		{
			MSG(EMessage::Error, "Can't use database");
		}

		if (!query.exec("UPDATE users SET last_login = NOW() WHERE hashCodeUsers = '" + QString::fromLatin1(hash, hash.size()) + "'; "))
		{
			MSG(EMessage::Error, "Can't update table \'users\'");
		}

		MSG(EMessage::Success, "User is found");
		res->SetValue(ETypeResultQuery::Success);
	}
	else
	{
		MSG(EMessage::Error, "Can't find user");
		res->SetValue(ETypeResultQuery::UserIsNotFound);
	}
}

void Database::CreateNewUser(const QByteArray& hash, TypeResultQuery* res)
{
	QSqlQuery query;

	if (!query.exec("USE data_server;"))
	{
		MSG(EMessage::Error, "Can't use database");
	}

	if (!query.exec("INSERT INTO users (hashCodeUsers, last_login, registration_time) VALUES (\'" + QString::fromLatin1(hash, hash.size()) + "\', NOW(), NOW());"))
	{
		MSG(EMessage::Error, "Duplicate hash");
		res->SetValue(ETypeResultQuery::DuplicateUsername);
		return;
	}

	int userID = UsersID(hash);

	query.exec("CREATE DATABASE user_" + QString::number(userID) + ";");
	query.exec("USE user_" + QString::number(userID) + ";");

	QString q;

	q = "CREATE TABLE artists";
	q += "(";
	q += "id_artist INT PRIMARY KEY AUTO_INCREMENT,";
	q += "name VARCHAR(128) NOT NULL";
	q += ");";

	if (!query.exec(q))
	{
		MSG(EMessage::Error, "Can't create table \'artists\'");
		res->SetValue(ETypeResultQuery::CantCreateTable);
		return;
	}

	q = "CREATE TABLE albums";
	q += "(";
	q += "id_album INT PRIMARY KEY AUTO_INCREMENT,";
	q += "title VARCHAR(128) NOT NULL,";
	q += "add_time DATETIME NOT NULL,";
	q += "last_listened DATETIME NOT NULL,";
	q += "number_times_listened INT NOT NULL,";
	q += "path_to_cover VARCHAR(256) NOT NULL";
	q += ");";

	if (!query.exec(q))
	{
		MSG(EMessage::Error, "Can't create table \'albums\'");
		res->SetValue(ETypeResultQuery::CantCreateTable);
		return;
	}

	q = "CREATE TABLE genres";
	q += "(";
	q += "id_genre INT PRIMARY KEY AUTO_INCREMENT,";
	q += "title VARCHAR(128) NOT NULL UNIQUE";
	q += ");";

	if (!query.exec(q))
	{
		MSG(EMessage::Error, "Can't create table \'genres\'");
		res->SetValue(ETypeResultQuery::CantCreateTable);
		return;
	}

	q = "CREATE TABLE media";
	q += "(";
	q += "id_media INT PRIMARY KEY AUTO_INCREMENT,";
	q += "title VARCHAR(128) NOT NULL,";
	q += "id_artist INT NOT NULL,";
	q += "id_album INT NOT NULL,";
	q += "id_genre INT NOT NULL,";
	q += "year INT NOT NULL,";
	q += "duration INT NOT NULL,";
	q += "bitrate INT NOT NULL,";
	q += "add_time DATETIME NOT NULL,";
	q += "last_listened DATETIME NOT NULL,";
	q += "number_times_listened INT NOT NULL DEFAULT 0,";
	q += "path VARCHAR(256) NOT NULL UNIQUE,";
	q += "lyric TEXT,";
	q += "lyrics_translation TEXT,";
	q += "FOREIGN KEY(id_artist) REFERENCES artists(id_artist) ON DELETE CASCADE,";
	q += "FOREIGN KEY(id_album) REFERENCES albums(id_album) ON DELETE CASCADE,";
	q += "FOREIGN KEY(id_genre) REFERENCES genres(id_genre) ON DELETE CASCADE";
	q += ");";

	if (!query.exec(q))
	{
		MSG(EMessage::Error, "Can't create table \'media\'");
		res->SetValue(ETypeResultQuery::CantCreateTable);
		return;
	}

	query.exec("INSERT INTO genres (title) VALUES (\'Русский рок\');");
	query.exec("INSERT INTO genres (title) VALUES (\'A Cappella\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Abstract\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Acid\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Acid Jazz\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Acid Punk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Acoustic\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Alt.Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Alternative\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Ambient\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Anime\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Art Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Audio Theatre\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Audiobook\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Avantgarde\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Ballad\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Baroque\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Bass\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Beat\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Bebob\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Bhangra\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Big Band\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Big Beat\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Black Metal\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Bluegrass\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Blues\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Booty Bass\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Breakbeat\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Britpop\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Cabaret\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Celtic\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Chamber Music\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Chanson\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Chillout\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Chorus\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Christian Gangsta Rap\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Christian Rap\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Christian Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Classic Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Classical\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Club\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Club-House\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Comedy\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Contemporary Christian\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Country\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Crossover\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Cult\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Dance\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Dance Hall\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Darkwave\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Death Metal\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Disco\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Downtempo\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Dream\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Drum & Bass\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Drum Solo\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Dub\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Dubstep\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Duet\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Easy Listening\');");
	query.exec("INSERT INTO genres (title) VALUES (\'EBM\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Eclectic\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Electro\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Electroclash\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Electronic\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Emo\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Ethnic\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Eurodance\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Euro-House\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Euro-Techno\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Experimental\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Fast Fusion\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Folk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Folklore\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Folk-Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Freestyle\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Funk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Fusion\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Game\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Gangsta\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Garage\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Garage Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'G-Funk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Global\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Goa\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Gospel\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Gothic\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Gothic Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Grunge\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Hard Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Hardcore\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Heavy Metal\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Hip-Hop\');");
	query.exec("INSERT INTO genres (title) VALUES (\'House\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Humour\');");
	query.exec("INSERT INTO genres (title) VALUES (\'IDM\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Illbient\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Indie\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Indie Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Industrial\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Industro - Goth\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Instrumental\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Instrumental Pop\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Instrumental Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Jam Band\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Jazz\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Jazz + Funk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'JPop\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Jungle\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Krautrock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Latin\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Leftfield\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Lo-Fi\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Lounge\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Math Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Meditative\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Merengue\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Metal\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Musical\');");
	query.exec("INSERT INTO genres (title) VALUES (\'National Folk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Native American\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Neoclassical\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Neue Deutsche Welle\');");
	query.exec("INSERT INTO genres (title) VALUES (\'New Age\');");
	query.exec("INSERT INTO genres (title) VALUES (\'New Romantic\');");
	query.exec("INSERT INTO genres (title) VALUES (\'New Wave\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Noise\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Nu-Breakz\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Oldies\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Opera\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Other\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Podcast\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Polka\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Polsk Punk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Pop\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Pop/Funk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Pop-Folk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Pop Punk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Post-Hardcore\');");
	//query.exec("INSERT INTO genres (title) VALUES (\'Porn Groove\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Post-Punk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Post-Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Power Ballad\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Pranks\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Primus\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Progressive Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Psybient\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Psychedelic\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Psychedelic Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Psytrance\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Punk\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Punk Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'R&B\');");
	query.exec("INSERT INTO genres (title) VALUES (\'R&B & Soul\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Rap\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Rave\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Reggae\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Retro\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Revival\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Rhythmic Soul\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Rock & Roll\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Salsa\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Samba\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Satire\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Shoegaze\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Showtunes\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Ska\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Slow Jam\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Slow Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Sonata\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Soul\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Sound Clip\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Soundtrack\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Southern Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Space\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Space Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Speech\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Swing\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Symphonic Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Symphony\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Synthpop\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Tango\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Techno\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Techno-Industrial\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Terror\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Thrash Metal\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Top 40\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Trailer\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Trance\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Tribal\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Trip-Hop\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Trop Rock\');");
	query.exec("INSERT INTO genres (title) VALUES (\'Vocal\');");
	query.exec("INSERT INTO genres (title) VALUES (\'World Music\');");

	MSG(EMessage::Success, "Database successfully created");
	res->SetValue(ETypeResultQuery::Success);
}

QJsonArray Database::GetTable(const QByteArray& hash, ETypeTable type, const bool merger, const int limit, const int offset, const ETypeSort typeSort, const EStateSort stateSort, TypeResultQuery* res)
{
	int idUser = UsersID(hash);

	if (idUser != -1)
	{
		QSqlQuery query;

		if (!query.exec("USE user_" + QString::number(idUser) + ';'))
		{
			MSG(EMessage::Error, "Can't use database");
			res->SetValue(ETypeResultQuery::CantUseDatabase);
			return QJsonArray();
		}

		QStringList names;

		switch (type)
		{
		case ETypeTable::All_Media:
		{
			MSG(EMessage::Log, "Got type table media");

			QString q;

			if (merger)
			{
				q = "SELECT ";
				q += "id_media, ";
				q += "media.title, ";
				q += "artists.name as artist, ";
				q += "albums.title as album, ";
				q += "genres.title as genre, ";
				q += "media.year, ";
				q += "media.duration, ";
				q += "media.bitrate, ";
				q += "media.add_time, ";
				q += "media.last_listened, ";
				q += "media.number_times_listened, ";
				q += "media.lyric, ";
				q += "media.lyrics_translation ";
				q += "FROM ";
				q += "media ";
				q += "INNER JOIN artists ON media.id_artist = artists.id_artist ";
				q += "INNER JOIN albums ON media.id_album = albums.id_album ";
				q += "INNER JOIN genres ON media.id_genre = genres.id_genre ";
			}
			else
			{
				q = "SELECT ";
				q += "media.id_media,";
				q += "media.title,";
				q += "media.id_artist,";
				q += "media.id_album,";
				q += "media.id_genre,";
				q += "media.year,";
				q += "media.duration,";
				q += "media.bitrate,";
				q += "media.add_time,";
				q += "media.last_listened,";
				q += "media.number_times_listened,";
				q += "media.lyric,";
				q += "media.lyrics_translation";
				q += " FROM ";
				q += "media ";

			}

			switch (typeSort)
			{
			case ETypeSort::Alphabetical:
			{
				q += "ORDER BY media.title ";
				break;
			}
			case ETypeSort::Artist:
			{
				if (merger)
				{
					q += "ORDER BY artists.name ";
				}
				else
				{
					q += "INNER JOIN artists ON media.id_artist = artists.id_artist ORDER BY artists.name ";
				}
				break;
			}
			case ETypeSort::Album:
			{
				if (merger)
				{
					q += "ORDER BY albums.title ";
				}
				else
				{
					q += "INNER JOIN albums ON media.id_album = albums.id_album ORDER BY albums.title ";
				}
				break;
			}
			case ETypeSort::DateAdded:
			{
				q += "ORDER BY media.add_time ";
				break;
			}
			}

			switch (stateSort)
			{
			case EStateSort::Ascending:
			{
				q += "ASC ";
				break;
			}
			case EStateSort::Descending:
			{
				q += "DESC ";
				break;
			}
			}

			if (limit == 0)
			{
				query.exec("SELECT * FROM media;");
				q += "LIMIT " + QString::number(query.size()) + " OFFSET " + QString::number(offset) + ";";
			}
			else
			{
				q += "LIMIT " + QString::number(limit) + " OFFSET " + QString::number(offset) + ";";
			}

			query.exec(q);

			names.append("id_media");
			names.append("title");
			names.append("id_artist");
			names.append("id_album");
			names.append("id_genre");
			names.append("year");
			names.append("duration");
			names.append("bitrate");
			names.append("add_time");
			names.append("last_listened");
			names.append("number_times_listened");
			names.append("lyric");
			names.append("lyrics_translation");

			break;
		}
		case ETypeTable::All_Albums:
		{
			MSG(EMessage::Log, "Got type table album");

			QString q;
			q = "SELECT ";
			q += "id_album,";
			q += "title,";
			q += "add_time,";
			q += "last_listened,";
			q += "number_times_listened";
			q += " FROM ";
			q += "albums ";

			switch (typeSort)
			{
			case ETypeSort::Alphabetical:
			{
				q += "ORDER BY title ";
				break;
			}
			case ETypeSort::DateAdded:
			{
				q += "ORDER BY add_time ";
				break;
			}
			}

			switch (stateSort)
			{
			case EStateSort::Ascending:
			{
				q += "ASC ";
				break;
			}
			case EStateSort::Descending:
			{
				q += "DESC ";
				break;
			}
			}

			if (limit == 0)
			{
				query.exec("SELECT * FROM albums;");
				q += "LIMIT " + QString::number(query.size()) + " OFFSET " + QString::number(offset) + ";";
			}
			else
			{
				q += "LIMIT " + QString::number(limit) + " OFFSET " + QString::number(offset) + ";";
			}

			query.exec(q);

			names.append("id_album");
			names.append("title");
			names.append("add_time");
			names.append("last_listened");
			names.append("number_times_listened");
			break;
		}
		case ETypeTable::All_Artists:
		{
			MSG(EMessage::Log, "Got type table artist");

			QString q = "SELECT id_artist, name FROM artists ";

			switch (typeSort)
			{
			case ETypeSort::Alphabetical:
			{
				q += "ORDER BY name ";
				break;
			}
			}

			switch (stateSort)
			{
			case EStateSort::Ascending:
			{
				q += "ASC ";
				break;
			}
			case EStateSort::Descending:
			{
				q += "DESC ";
				break;
			}
			}

			if (limit == 0)
			{
				query.exec("SELECT * FROM artists;");
				q += "LIMIT " + QString::number(query.size()) + " OFFSET " + QString::number(offset) + ";";
			}
			else
			{
				q += "LIMIT " + QString::number(limit) + " OFFSET " + QString::number(offset) + ";";
			}

			query.exec(q);

			names.append("id_artist");
			names.append("name");
			break;
		}
		case ETypeTable::All_Genres:
		{
			MSG(EMessage::Log, "Got type table genres");

			QString q = "SELECT id_genre, title FROM genres ";

			switch (typeSort)
			{
			case ETypeSort::Alphabetical:
			{
				q += "ORDER BY title ";
				break;
			}
			}

			switch (stateSort)
			{
			case EStateSort::Ascending:
			{
				q += "ASC ";
				break;
			}
			case EStateSort::Descending:
			{
				q += "DESC ";
				break;
			}
			}

			if (limit == 0)
			{
				query.exec("SELECT * FROM genres;");
				q += "LIMIT " + QString::number(query.size()) + " OFFSET " + QString::number(offset) + ";";
			}
			else
			{
				q += "LIMIT " + QString::number(limit) + " OFFSET " + QString::number(offset) + ";";
			}

			query.exec(q);

			names.append("id_genre");
			names.append("title");
			break;
		}
		}

		QJsonArray table;

		int rows = 0;
		int count = names.size();

		while (query.next())
		{
			QJsonArray row;
			for (int i = 0; i < count; ++i)
			{
				QJsonObject obj;
				obj.insert(names[i], query.value(i).toJsonValue());
				row.append(obj);
			}
			table.append(row);
			++rows;
		}

		MSG(EMessage::Success, "Got successfully table");
		res->SetValue(ETypeResultQuery::Success);
		return table;
	}
	else
	{
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		MSG(EMessage::Error, "User is not found");
		return QJsonArray();
	}
}

void Database::CoverArt(const QByteArray& hash, const int mediaID, QByteArray* const buffer, TypeResultQuery* res)
{
	QSqlQuery query;

	if (!query.exec("USE user_" + QString::number(UsersID(hash)) + ";"))
	{
		MSG(EMessage::Error, "User is not found");
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		return;
	}
	if (!query.exec("SELECT id_album FROM media WHERE id_media=" + QString::number(mediaID) + ";"))
	{
		MSG(EMessage::Error, "Is Not Found");
		res->SetValue(ETypeResultQuery::IsNotFound);
		return;
	}

	int idAlbum = 1;

	if (query.next())
	{
		idAlbum = query.value(0).toInt();
	}

	if (!query.exec("SELECT path_to_cover FROM albums WHERE id_album=" + QString::number(idAlbum) + ";"))
	{
		MSG(EMessage::Error, "Is Not Found");
		res->SetValue(ETypeResultQuery::IsNotFound);
		return;
	}
	if (query.next())
	{
		QFile img(query.value(0).toString());
		img.open(QIODevice::ReadOnly);
		buffer->clear();
		buffer->append(img.readAll());
		img.close();
	}
	else
	{
		MSG(EMessage::Error, "Is Not Found");
		res->SetValue(ETypeResultQuery::IsNotFound);
		return;
	}
	MSG(EMessage::Success, "Cover art successfully found");
	res->SetValue(ETypeResultQuery::Success);
}

void Database::AddNewMedia(const QByteArray& hash, QByteArray* const buffer, const Tags& tags, bool newArtist, bool newAlbum, TypeResultQuery* res)
{
	QSqlQuery query;

	/* Формирование пути к новому айдиофайлу */
	
	QString id = QString::number(UsersID(hash));

	if (id == -1)
	{
		MSG(EMessage::Error, "User is not found");
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		return;
	}

	query.exec("USE user_" + id + ";");
	query.exec("SELECT id_media FROM media ORDER BY id_media DESC LIMIT 1;");

	int mediaID;
	if (query.next())
	{
		mediaID = query.value(0).toInt() + 1;
	}
	
	QDir().mkdir(m_path + "/user_" + id);
	QDir().mkdir(m_path + "/user_" + id + "/media");
	QDir().mkdir(m_path + "/user_" + id + "/cover-arts");
	QString path = m_path + "/user_" + id + "/media/id_" + QString::number(mediaID) + ".mp3";

	/* Запись в файл новой медиа */

	QFile f(path);
	if (!f.open(QIODevice::WriteOnly))
	{
		MSG(EMessage::Error, "Write error");
		res->SetValue(ETypeResultQuery::WriteError);
		return;
	}
	f.write(*buffer);
	f.close();

	/* Создание (если было указано) новой записи альбома */

	int id_album = 1;
	int id_artist = 1;

	if (newAlbum)
	{
		query.exec("SELECT id_album FROM albums ORDER BY id_album DESC LIMIT 1;");
		if (query.next())
		{
			id_album = query.value(0).toInt() + 1;
		}

		QString pathCoverArt = m_path + "/user_" + id + "/cover-arts/id_" + QString::number(id_album) + ".jpg";

		QFile f(pathCoverArt);
		if (!f.open(QIODevice::WriteOnly))
		{
			MSG(EMessage::Error, "Write error");
			res->SetValue(ETypeResultQuery::WriteError);
			return;
		}
		f.write(tags.Image);
		f.close();

		query.exec("INSERT INTO albums (title, add_time, last_listened, number_times_listened, path_to_cover) VALUES ('" + tags.Album + "', NOW(), NOW(), 0, '" + pathCoverArt + "');");
	}
	else
	{
		query.exec("SELECT * FROM albums WHERE title='" + tags.Album + "';");

		if (query.next())
		{
			id_album = query.value(0).toInt();
		}
	}

	/* Создание (если было указано) новой записи артиста */

	if (newArtist)
	{
		query.exec("SELECT id_artist FROM artists ORDER BY id_artist DESC LIMIT 1;");
		if (query.next())
		{
			id_artist = query.value(0).toInt() + 1;
		}

		query.exec("INSERT INTO artists (name) VALUES ('" + tags.Artist + "');");
	}
	else
	{
		query.exec("SELECT * FROM artists WHERE name='" + tags.Artist + "';");

		if (query.next())
		{
			id_artist = query.value(0).toInt();
		}	
	}

	/* Поиск номер жанра данной медия */

	int id_genre = 1;
	query.exec("SELECT id_genre FROM genres WHERE title='" + tags.Genre + "';");
	if (query.next())
	{
		id_genre = query.value(0).toInt();
	}

	/* Добавление новой записи в таблицы 'media' */

	QString q;
	q += "INSERT INTO media (title, id_artist, id_album, id_genre, year, duration, bitrate, add_time, last_listened, number_times_listened, lyric, lyrics_translation, path) ";
	q += "VALUES (";
	q += "'" + tags.Title + "'";
	q += ",";
	q += QString::number(id_artist);
	q += ",";
	q += QString::number(id_album);
	q += ",";
	q += QString::number(id_genre);
	q += ",";
	q += tags.Year.isEmpty() ? "0" : tags.Year;
	q += ",";
	q += tags.Duration;
	q += ",";
	q += tags.Bitrate;
	q += ",";
	q += "NOW()";
	q += ",";
	q += "NOW()";
	q += ",";
	q += "0";
	q += ",'";
	q += tags.Lyric;
	q += "','";
	q += tags.LyricsTranslation;
	q += "',";
	q += "'" + path + "'";
	q += ");";
	
	query.exec(q);

	res->SetValue(ETypeResultQuery::Success);
}