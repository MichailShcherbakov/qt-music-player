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
		Msg(EMessage::Success, "Server is started");
	else
		Msg(EMessage::Error, "Server isn't started");
}

void CServer::incomingConnection(qintptr socketDescriptor)
{
	QTcpSocket* socket = new QTcpSocket;
	socket->setSocketDescriptor(socketDescriptor);
	m_listClients[socketDescriptor] = socket;
	/*m_isFile[socketDescriptor] = false;*/
	connect(m_listClients[socketDescriptor], &QTcpSocket::readyRead, this, &CServer::SocketReady);
	connect(m_listClients[socketDescriptor], &QTcpSocket::disconnected, this, &CServer::SocketDisconnected);

	Msg(EMessage::Success, "Client " + QString::number(socketDescriptor) + " is connected");
	socket->write("You are connected");
}

void CServer::SocketReady()
{
	QTcpSocket* socket = (QTcpSocket*)sender();
	int id = socket->socketDescriptor();

	CQuery query;

	if (m_typeQuery[id] != EQuery::ADD_NEW_MEDIA_RETURN)
	{
		QByteArray arr = socket->readAll();
		query = CQuery(arr);
		m_typeQuery[id] = (EQuery)query.GetType().toInt();
		m_idUser[id] = QString::number(query.GetID());
	}

	switch (m_typeQuery[id])
	{
	case EQuery::SEND_TABLE: 
	{
		m_typeQuery[id] = EQuery::SEND_TABLE;

		switch (query.GetValue_1().toInt())
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
		}
		break;
	}
	case EQuery::CREATE_NEW_USER:
	{
		m_typeQuery[id] = EQuery::CREATE_NEW_USER;

		QSqlQuery q("USE data_server;");
		q.exec("INSERT INTO users (username, password, registration_time) VALUES (\'" + query.GetUser() + "\', \'" + query.GetPassword() + "\', NOW());");
		q.exec("SELECT * FROM users;");
		int id = query.GetID();
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

		QByteArray answer;
		QByteArray size;
		QString str;

		if (query.Check())
			str = "Success";
		else
			str = "Error";

		QDataStream anw(&answer, QIODevice::WriteOnly);
		anw.setVersion(QDataStream::Qt_5_12);
		anw << str.toUtf8();

		QDataStream sz(&size, QIODevice::WriteOnly);
		sz.setVersion(QDataStream::Qt_5_12);
		sz << str.length();

		socket->write(answer);
		socket->write(size);

		break;
	}
	case EQuery::CHECK_USER:
	{
		m_typeQuery[id] = EQuery::CHECK_USER;

		QByteArray answer;
		QByteArray size;
		QString str;

		if (query.Check())
			str = "Success";
		else
			str = "Error";
		
		QDataStream anw(&answer, QIODevice::WriteOnly);
		anw.setVersion(QDataStream::Qt_5_12);
		anw << str.toUtf8();

		QDataStream sz(&size, QIODevice::WriteOnly);
		sz.setVersion(QDataStream::Qt_5_12);
		sz << str.length();

		socket->write(answer);
		socket->write(size);
		break;
	}
	case EQuery::ADD_NEW_MEDIA:
	{
		m_typeQuery[id] = EQuery::ADD_NEW_MEDIA_RETURN;

		if (query.GetValue_1() == "true")
			m_queryCreateAlbum[id] = true;
		else
			m_queryCreateAlbum[id] = false;

		if (query.GetValue_2() == "true")
			m_queryCreateArtist[id] = true;
		else
			m_queryCreateArtist[id] = false;
		break;
	}
	case EQuery::ADD_NEW_MEDIA_RETURN:
	{
		if (m_size_end[id] == 0)
		{
			QByteArray arr = socket->readAll();

			QByteArray size;
			for (int i = 0; i < 4; ++i) size.append(arr[i]);
			arr.remove(0, 4);

			QDataStream in(&size, QIODevice::ReadOnly);
			in >> m_size_end[id];

			m_size_now[id] += arr.length();
			m_file[id].append(arr);

			Msg(EMessage::Warning, QString::number(m_size_end[id]));
		}
		else
		{
			m_size_now[id] += socket->bytesAvailable();

			QString size = QString::number((float)m_size_now[id] / 1024 / 1024);
			QString Size;
			Size.append(size[0]);
			Size.append(size[1]);
			Size.append(size[2]);
			Size.append(size[3]);
			Msg(EMessage::Log, "Size: " + QString::number(m_size_now[id]) + " BYTE (" + Size + "MB)");

			QByteArray arr = socket->readAll();
			m_file[id].append(arr);
		}
		if (m_size_end[id] == m_size_now[id])
		{
			Msg(EMessage::Success, "End");
			/* Формирование пути к новому айдиофайлу */
			QSqlQuery q;
			q.exec("USE user_" + m_idUser[id] + ";");
			q.exec("SELECT * FROM media;");
			int rows = q.size();
			QString path = m_path + "/user_" + m_idUser[id] + "/id_" + QString::number(++rows) + ".mp3";
			/* Запись в файл новой медия */
			QFile f(path);
			f.open(QIODevice::WriteOnly);
			f.write(m_file[id]);
			f.close();
			/* Получение основных тегов из медия */
			CTagEditer tagEditer;
			Tags tags = tagEditer.GetTags(path);
			/* Создание (если было указано) нового альбома и/или артиста  */
			int id_album = 1;
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
			q.exec("SELECT id_genre FROM genres WHERE title='" + tags.Genre + "';");
			int id_genre = 1;
			if (q.next())  id_genre = q.value(0).toInt();
			/* Добавление новой записи в таблицы 'media' */
			QString query;
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
			m_size_end[id] = 0;
			m_size_now[id] = 0;
			m_queryCreateArtist[id] = false;
			m_queryCreateAlbum[id] = false;
			m_file[id].clear();
			m_typeQuery[id] = EQuery::UNKNOWN;
		}
		break;
	}
	case EQuery::SEND_IMAGE:
	{
		QSqlQuery q("SELECT path FROM media WHERE id_media=" + query.GetValue_1() + ";");
		if (q.next())
		{
			CTagEditer tagEditer;
			socket->write(tagEditer.GetCoverArt(q.value(0).toString()));
		}
		break;
	}
	case EQuery::SEND_MEDIA:
	{
		QSqlQuery q("SELECT path FROM media WHERE id_media=" + query.GetValue_1() + ";");
		if (q.next())
		{
			QFile f(q.value(0).toString());
			f.open(QIODevice::ReadOnly);
			QByteArray arr = f.readAll();
			f.close();
			socket->write(arr);
		}
		break;
	}
	}
}

void CServer::SocketDisconnected()
{
	Msg(EMessage::Log,"Client is disconnected");

	QTcpSocket* clientSocket = (QTcpSocket*)sender();

	int key = m_listClients.key(clientSocket);

	clientSocket->close();
	m_listClients.remove(key);
	m_size_end.remove(key);
	m_size_now.remove(key);
	m_queryCreateArtist.remove(key);
	m_queryCreateAlbum.remove(key);
	m_idUser.remove(key);
}
 
void CServer::CreateDataBase()
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setUserName("root");
	db.setPassword("root");

	if (!db.open())
		Msg(EMessage::Error, "Can't open the database");
	else
		Msg(EMessage::Success, "The database is opened");

	QSqlQuery query("CREATE DATABASE data_server;");
	query.exec("USE data_server;");
	query.exec("CREATE TABLE users ( id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(30) NOT NULL UNIQUE, password VARCHAR(30) NOT NULL, registration_time DATETIME NOT NULL);");
}
