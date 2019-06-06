#include "cserver.h"

CServer::CServer()
{
}

CServer::~CServer()
{
}

void CServer::Initialize()
{
	CreateDataBase();
	StartServer();

	if (!QDir(m_path).exists())
		QDir().mkdir(m_path);
}

void CServer::StartServer()
{
	if (this->listen(QHostAddress::Any, 6150))
		STools::Msg(EMessage::Success, "Server is started");
	else
		STools::Msg(EMessage::Error, "Server isn't started");
}

void CServer::incomingConnection(qintptr socketDescriptor)
{
	QTcpSocket* socket = new QTcpSocket;
	socket->setSocketDescriptor(socketDescriptor);
	User user;
	user.m_socket = socket;
	user.m_loadState = ELoadState::Unknown;
	m_users[socketDescriptor] = user;

	connect(user.m_socket, &QTcpSocket::readyRead, this, &CServer::SocketReady);
	connect(user.m_socket, &QTcpSocket::disconnected, this, &CServer::SocketDisconnected);

	STools::Msg(EMessage::Success, "Client " + QString::number(socketDescriptor) + " is connected");

	QJsonDocument doc;
	QJsonObject obj;
}

void CServer::SocketReady()
{
	QTcpSocket* socket = (QTcpSocket*)sender();
	int id = socket->socketDescriptor();

	QJsonDocument doc;

	switch (m_users[id].m_loadState)
	{
	case ELoadState::Unknown: {
		doc = QJsonDocument::fromJson(socket->readAll());

		if (!doc.isEmpty())
		{
			QString username = doc["username"].toString();
			QString password = doc["password"].toString();

			m_users[id].m_typeQuery = static_cast<ETypeQuery>(doc["type-query"].toInt());

			m_users[id].m_size_end = doc["size-body"].toInt();

			m_users[id].m_loadState = ELoadState::Header;
			m_users[id].m_size_now = 0;
		}
		break;
	}
	case ELoadState::Header: {
		m_users[id].m_size_now += socket->bytesAvailable();
		m_users[id].m_buffer.append(socket->readAll());

		Msg(EMessage::Log, "Size of File: " + QString::number(m_users[id].m_buffer.size()) + " bytes");

		if (m_users[id].m_size_end == m_users[id].m_size_now)
		{
			m_users[id].m_loadState = ELoadState::Body;

			doc = QJsonDocument::fromJson(m_users[id].m_buffer);
			
			switch (m_users[id].m_typeQuery)
			{
			case ETypeQuery::Create_New_User:
			{
				CreateNewUser(m_users[id].m_username, m_users[id].m_password);
			}
			}

			m_users[id].m_loadState = ELoadState::Footer;
		}
		break;
	}
	case ELoadState::Footer: {
		doc = QJsonDocument::fromJson(socket->readAll());
		m_users[id].m_loadState = ELoadState::Unknown;
		m_users[id].m_buffer.clear();
		m_users[id].m_size_now = 0;
		m_users[id].m_size_end = 0;
		break;
	}
	}
}

void CServer::SocketDisconnected()
{
	/*STools::Msg(EMessage::Log,"Client is disconnected");

	QTcpSocket* clientSocket = (QTcpSocket*)sender();

	int key = m_listClients.key(clientSocket);

	clientSocket->close();
	m_listClients.remove(key);
	m_size_end.remove(key);
	m_size_now.remove(key);
	m_queryCreateArtist.remove(key);
	m_queryCreateAlbum.remove(key);
	m_idUser.remove(key);*/
}
 
void CServer::CreateDataBase()
{
	/*db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setUserName("root");
	db.setPassword("root");

	if (!db.open())
		STools::Msg(EMessage::Error, "Can't open the database");
	else
		STools::Msg(EMessage::Success, "The database is opened");

	QSqlQuery query("CREATE DATABASE data_server;");
	query.exec("USE data_server;");
	query.exec("CREATE TABLE users ( id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(30) NOT NULL UNIQUE, password VARCHAR(30) NOT NULL, registration_time DATETIME NOT NULL);");
	*/
}

void CServer::SendTable(ETypeTable type)
{
	/*switch (static_cast<ETable>(query.GetValue_1().toInt()))
	{
	case ETable::ALL_MEDIA:
	{
		QSqlQuery q;
		q.exec("USE user_" + QString::number(query.GetID()) + ';');
		q.exec("SELECT id_media, title, id_artist, id_album, year, id_genre, duraction, bitrate, add_time FROM media;");

		QVector<QVector<QString>> table;
		QString qr;
		int rows = 0;
		int column = q.record().count();
		while (q.next())
		{
			rows++;
			QVector<QString> temp;
			for (int i = 0; i < column; ++i)
				temp.push_back('[' + q.value(i).toString() + ']');
			table.push_back(temp);
		}
		qr += '[' + QString::number(column) + ']' + '[' + QString::number(rows) + ']';
		for (int i = 0; i < column; ++i)
		{
			for (int j = 0; j < table.size(); ++j)
			{
				qr += table.at(j).at(i);
			}
		}
		QByteArray data = qr.toUtf8();
		QByteArray size;
		QDataStream out(&size, QIODevice::WriteOnly);
		out << (int)(data.length());
		socket->write(size);
		socket->write(data);
		break;
	}
	case ETable::ALL_ALBUMS:
	{
		QSqlQuery q;
		q.exec("USE user_" + QString::number(query.GetID()) + ';');
		q.exec("select * from albums;");

		QVector<QVector<QString>> table;
		QString qr;
		int rows = 0;
		int column = q.record().count();
		while (q.next())
		{
			rows++;
			QVector<QString> temp;
			for (int i = 0; i < column; ++i)
				temp.push_back('[' + q.value(i).toString() + ']');
			table.push_back(temp);
		}
		qr += '[' + QString::number(column) + ']' + '[' + QString::number(rows) + ']';
		for (int i = 0; i < column; ++i)
		{
			for (int j = 0; j < table.size(); ++j)
			{
				qr += table.at(j).at(i);
			}
		}
		QByteArray data = qr.toUtf8();
		QByteArray size;
		QDataStream out(&size, QIODevice::WriteOnly);
		out << (int)(data.length());
		socket->write(size);
		socket->write(data);
		break;
	}
	case ETable::ALL_ARTISTS:
	{
		QSqlQuery q;
		q.exec("USE user_" + QString::number(query.GetID()) + ';');
		q.exec("select * from artists;");

		QVector<QVector<QString>> table;
		QString qr;
		int rows = 0;
		int column = q.record().count();
		while (q.next())
		{
			rows++;
			QVector<QString> temp;
			for (int i = 0; i < column; ++i)
				temp.push_back('[' + q.value(i).toString() + ']');
			table.push_back(temp);
		}
		qr += '[' + QString::number(column) + ']' + '[' + QString::number(rows) + ']';
		for (int i = 0; i < column; ++i)
		{
			for (int j = 0; j < table.size(); ++j)
			{
				qr += table.at(j).at(i);
			}
		}
		QByteArray data = qr.toUtf8();
		QByteArray size;
		QDataStream out(&size, QIODevice::WriteOnly);
		out << (int)(data.length());
		socket->write(size);
		socket->write(data);
		break;
	}
	case ETable::ALL_GENRES:
	{
		QSqlQuery q;
		q.exec("USE user_" + QString::number(query.GetID()) + ';');
		q.exec("select * from genres;");

		QVector<QVector<QString>> table;
		QString qr;
		int rows = 0;
		int column = q.record().count();
		while (q.next())
		{
			rows++;
			QVector<QString> temp;
			for (int i = 0; i < column; ++i)
				temp.push_back('[' + q.value(i).toString() + ']');
			table.push_back(temp);
		}
		qr += '[' + QString::number(column) + ']' + '[' + QString::number(rows) + ']';
		for (int i = 0; i < column; ++i)
		{
			for (int j = 0; j < table.size(); ++j)
			{
				qr += table.at(j).at(i);
			}
		}
		QByteArray data = qr.toUtf8();
		QByteArray size;
		QDataStream out(&size, QIODevice::WriteOnly);
		out << (int)(data.length());
		socket->write(size);
		socket->write(data);
		break;
	}
	}*/
}

void CServer::CheckUser()
{
	/*QByteArray answer;
	QByteArray size;
	ELoginAndRegistration temp;

	if (query.Check())
		temp = ELoginAndRegistration::Success;
	else
		temp = ELoginAndRegistration::Success;

	QDataStream anw(&answer, QIODevice::WriteOnly);
	anw.setVersion(QDataStream::Qt_5_12);
	anw << static_cast<int>(temp);

	QDataStream sz(&size, QIODevice::WriteOnly);
	sz.setVersion(QDataStream::Qt_5_12);
	sz << answer.size();

	socket->write(size);
	socket->write(answer);*/
}

void CServer::AddNewMedia()
{
	/* Формирование пути к новому айдиофайлу */
			/*
			QSqlQuery q;
			q.exec("USE user_" + m_idUser[id] + ";");
			q.exec("SELECT * FROM media;");
			int rows = q.size();
			QString path = m_path + "/user_" + m_idUser[id] + "/id_" + QString::number(++rows) + ".mp3";
			/* Запись в файл новой медия */
			/*QFile f(path);
			f.open(QIODevice::WriteOnly);
			f.write(m_file[id]);
			f.close();
			/* Получение основных тегов из медия */
			/*CTagEditer tagEditer;
			Tags tags = tagEditer.GetTags(path);
			/* Создание (если было указано) нового альбома и/или артиста  */
			/*int id_album = 1;
			int id_artist = 1;
			if (m_queryCreateAlbum[id])
			{
				q.exec("SELECT * FROM albums;");
				id_album = q.size() + 1;
				q.exec("INSERT INTO albums (title) VALUES ('" + tags.Album + "');");
			}
			else
			{
				q.exec("SELECT * FROM albums WHERE title='" + tags.Album + "';");
				if (q.next())  id_album = q.value(0).toInt();
			}

			if (m_queryCreateArtist[id])
			{
				q.exec("SELECT * FROM artists;");
				id_artist = q.size() + 1;
				q.exec("INSERT INTO artists (name) VALUES ('" + tags.Artist + "');");
			}
			else
			{
				q.exec("SELECT * FROM artists WHERE name='" + tags.Artist + "';");
				if (q.next())  id_artist = q.value(0).toInt();
			}
			/* Поиск номер жанра данной медия */
			/*q.exec("SELECT id_genre FROM genres WHERE title='" + tags.Genre + "';");
			int id_genre = 1;
			if (q.next())  id_genre = q.value(0).toInt();
			/* Добавление новой записи в таблицы 'media' */
			/*QString query;
			query += "INSERT INTO media (title, id_artist, id_album, year, id_genre, duraction, bitrate, path, add_time) ";
			query += "VALUES (";
			query += "'" + tags.Title + "'";
			query += ",";
			query += QString::number(id_artist);
			query += ",";
			query += QString::number(id_album);
			query += ",";
			query += tags.Year;
			query += ",";
			query += QString::number(id_genre);
			query += ",";
			query += tags.Duraction;
			query += ",";
			query += tags.Bitrate;
			query += ",";
			query += "'" + path + "'";
			query += ", NOW() );";
			q.exec(query);

			/* Чистка  */
			/*m_size_end[id] = 0;
			m_size_now[id] = 0;
			m_queryCreateArtist[id] = false;
			m_queryCreateAlbum[id] = false;
			m_file[id].clear();
			m_typeQuery[id] = EQuery::UNKNOWN;*/
}

void CServer::SendCoverArt()
{
	/*QSqlQuery q("SELECT path FROM media WHERE id_media=" + query.GetValue_1() + ";");
	if (q.next())
	{
		CTagEditer tagEditer;
		socket->write(tagEditer.GetCoverArt(q.value(0).toString()));
	}*/
}

void CServer::SendMedia()
{
	/*QSqlQuery q("SELECT path FROM media WHERE id_media=" + query.GetValue_1() + ";");
	if (q.next())
	{
		QFile f(q.value(0).toString());
		f.open(QIODevice::ReadOnly);
		QByteArray arr = f.readAll();
		f.close();
		socket->write(arr);
	}*/
}

bool CServer::CreateNewUser(QString username, QString password)
{
	QSqlQuery q("USE data_server;");
	if (!q.exec("INSERT INTO users (username, password, registration_time) VALUES (\'" + username + "\', \'" + password + "\', NOW());"))
		return false;
	q.exec("SELECT * FROM users;");
	int id = q.size();
	q.exec("CREATE DATABASE user_" + QString::number(id) + ";");
	q.exec("USE user_" + QString::number(id) + ";");
	q.exec("CREATE TABLE artists (id_artist INT PRIMARY KEY AUTO_INCREMENT,name VARCHAR(150) NOT NULL);");
	q.exec("CREATE TABLE albums (id_album INT PRIMARY KEY AUTO_INCREMENT,title VARCHAR(150) NOT NULL);");
	q.exec("CREATE TABLE genres (id_genre INT PRIMARY KEY AUTO_INCREMENT,title VARCHAR(150) NOT NULL UNIQUE);");
	q.exec("INSERT INTO genres (title) VALUES ('Alternative Metal');");
	q.exec("CREATE TABLE media (id_media INT PRIMARY KEY AUTO_INCREMENT,title VARCHAR(150) NOT NULL,id_artist INT NOT NULL,id_album INT NOT NULL,year INT NOT NULL,id_genre INT NOT NULL,duraction INT NOT NULL,bitrate INT NOT NULL,add_time DATETIME NOT NULL,path VARCHAR(150) NOT NULL UNIQUE,FOREIGN KEY(id_artist) REFERENCES artists(id_artist) ON DELETE CASCADE,FOREIGN KEY(id_album) REFERENCES albums(id_album) ON DELETE CASCADE,FOREIGN KEY(id_genre) REFERENCES genres(id_genre) ON DELETE CASCADE);");

	/*

	CREATE TABLE artists (
		id_artist INT PRIMARY KEY AUTO_INCREMENT,
		name VARCHAR(150) NOT NULL
	);

	CREATE TABLE albums (
		id_album INT PRIMARY KEY AUTO_INCREMENT,
		title VARCHAR(150) NOT NULL,
		image_path VARCHAR(150) NOT NULL UNIQUE
	);

	CREATE TABLE genres (
		id_genre INT PRIMARY KEY AUTO_INCREMENT,
		title VARCHAR(150) NOT NULL UNIQUE
	);

	CREATE TABLE media (
		id_media INT PRIMARY KEY AUTO_INCREMENT,
		title VARCHAR(150) NOT NULL,
		id_artist INT NOT NULL,
		id_album INT NOT NULL,
		year INT NOT NULL,
		id_genre INT NOT NULL,
		duraction INT NOT NULL,
		bitrate INT NOT NULL,
		path VARCHAR(150) NOT NULL UNIQUE,
		add_time DATETIME NOT NULL,
		FOREIGN KEY (id_artist) REFERENCES artists (id_artist) ON DELETE CASCADE,
		FOREIGN KEY (id_album) REFERENCES albums (id_album) ON DELETE CASCADE,
		FOREIGN KEY (id_genre) REFERENCES genres (id_genre) ON DELETE CASCADE
	);

	select id_media, media.title as title, albums.title as album, name as artist, year, duraction, bitrate, path, add_time from media
	inner join artists using(id_artist) inner join albums using(id_album) inner join genres using(id_genre);

	*/

	QDir().mkdir(m_path + "/user_" + QString::number(id));
	return true;
}
