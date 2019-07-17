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
	user.m_size_msg = 0;
	user.m_buffer.clear();
	m_users[socketDescriptor] = user;

	connect(user.m_socket, &QTcpSocket::readyRead, this, &CServer::SocketReady);
	connect(user.m_socket, &QTcpSocket::disconnected, this, &CServer::SocketDisconnected);

	STools::Msg(EMessage::Log, "Client " + QString::number(socketDescriptor) + " is connected");

	// TEMP

	/*QJsonDocument doc;
	QJsonObject mainObj, header, body, footer;

	header.insert("query-result", "You are Connected");

	mainObj.insert("header", header);
	mainObj.insert("body", body);
	mainObj.insert("footer", footer);

	doc.setObject(mainObj);

	Send(socket, doc.toJson());*/
}

void CServer::SocketReady()
{
	QTcpSocket* socket = (QTcpSocket*)sender();
	int id = socket->socketDescriptor();

	m_users[id].m_buffer.append(socket->readAll());

	if (m_users[id].m_size_msg == 0)
	{
		QByteArray sizeArray;
		for (int i = 0; i < sizeof(int); ++i) sizeArray.append(m_users[id].m_buffer[i]);

		QDataStream out(&sizeArray, QIODevice::ReadOnly);
		out.setVersion(QDataStream::Qt_5_12);
		out >> m_users[id].m_size_msg;

		STools::Msg(EMessage::Log, "Size msg: " + QString::number(m_users[id].m_size_msg) + " bytes");

		m_users[id].m_buffer.remove(0, sizeof(int));
	}

	if (m_users[id].m_size_msg == m_users[id].m_buffer.size())
	{
		STools::Msg(EMessage::Success, "Data is came fully");

		QJsonDocument doc = QJsonDocument::fromJson(m_users[id].m_buffer);

		QJsonObject header = doc["header"].toObject();
		QJsonObject body = doc["body"].toObject();
		QJsonObject footer = doc["footer"].toObject();

		ETypeQuery type_query = static_cast<ETypeQuery>(header["type-query"].toInt());

		QJsonDocument sendDoc;
		QJsonObject sendMainObj, sendHeader, sendBody, sendFooter;

		TypeResultQuery* res = new TypeResultQuery;

		switch (type_query)
		{
		case ETypeQuery::Create_New_User:
		{
			STools::Msg(EMessage::Log, "The request for creating a new user");

			CreateNewUser(id, header["username"].toString(), header["password"].toString(), res);
			break;
		}
		case ETypeQuery::Check_This_User:
		{
			STools::Msg(EMessage::Log, "The request for checking the user");

			CheckThisUser(id, header["username"].toString(), header["password"].toString(), res);
			break;
		}
		case ETypeQuery::Add_New_Media:
		{
			STools::Msg(EMessage::Log, "The request for adding a new media");

			if (m_users[id].isProven)
			{
				QByteArray media = body["media"].toString().toLatin1();
				AddNewMedia(id, &media, body["create-new-artist"].toBool(), body["create-new-album"].toBool(), res);
			}
			else
			{
				res->SetValue(ETypeResultQuery::UserIsNotAuthorized);
				STools::Msg(EMessage::Error, "User is not authorized");
			}
			break;
		}
		case ETypeQuery::Send_Table:
		{
			STools::Msg(EMessage::Log, "The request for sending the table");

			if (m_users[id].isProven)
			{
				ETypeTable type_table = static_cast<ETypeTable>(header["type-table"].toInt());
				QJsonArray table = GetTable(id, type_table, res);
				sendBody.insert("table", table);
			}
			else
			{
				res->SetValue(ETypeResultQuery::UserIsNotAuthorized);
				STools::Msg(EMessage::Error, "User is not authorized");
			}
			break;
		}
		case ETypeQuery::Send_Cover_Art:
		{
			STools::Msg(EMessage::Log, "The request for sending the art cover");

			if (m_users[id].isProven)
			{
				QByteArray coverArt;
				GetCoverArt(id, body["id-album"].toInt(), &coverArt, res);
				QString t = QString::fromLatin1(coverArt, coverArt.size());
				sendBody.insert("cover-art", t);
			}
			else
			{
				res->SetValue(ETypeResultQuery::UserIsNotAuthorized);
				STools::Msg(EMessage::Error, "User is not authorized");
			}
			break;
		}
		case ETypeQuery::Send_Media:
		{
			STools::Msg(EMessage::Log, "The request for sending the media");

			if (m_users[id].isProven)
			{
				QByteArray media;
				GetMedia(id, body["id-media"].toInt(), &media, res);
				Send(socket, media);

				m_users[id].m_size_msg = 0;
				m_users[id].m_buffer.clear();

				STools::Msg(EMessage::Log, "Reply has been sent");
				return;
			}
			else
			{
				res->SetValue(ETypeResultQuery::UserIsNotAuthorized);
				STools::Msg(EMessage::Error, "User is not authorized");
			}
			break;
		}
		default:
		{
			STools::Msg(EMessage::Error, "Unknown type query");
		}
		}

		sendHeader.insert("query-result", res->toInt());

		sendMainObj.insert("header", sendHeader);
		sendMainObj.insert("body", sendBody);
		sendMainObj.insert("footer", sendFooter);

		sendDoc.setObject(sendMainObj);

		Send(socket, sendDoc.toJson());

		m_users[id].m_size_msg = 0;
		m_users[id].m_buffer.clear();

		STools::Msg(EMessage::Log, "Reply has been sent");
	}
}

void CServer::SocketDisconnected()
{
	STools::Msg(EMessage::Log, "Client is disconnected");

	QTcpSocket* clientSocket = (QTcpSocket*)sender();

	for (auto it : m_users)
	{
		if (it.m_socket == clientSocket)
		{
			clientSocket->close();
			int key = m_users.key(it);
			m_users.remove(key);
			break;
		}
	}
}

void CServer::Send(QTcpSocket* socket, QByteArray data)
{
	QByteArray msg;
	QDataStream out(&msg, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_12);
	out << data.size();
	msg.append(data);

	socket->write(msg);
}
 
void CServer::CreateDataBase()
{
	STools::Msg(EMessage::Log, "Creating a database");

	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setUserName("root");
	db.setPassword("root");

	if (!db.open())
	{
		STools::Msg(EMessage::Error, "Can't open the database");
		return;
	}
	else
	{
		STools::Msg(EMessage::Success, "The database is opened");
	}
		
	QSqlQuery query("CREATE DATABASE data_server;");
	query.exec("USE data_server;");
	query.exec("CREATE TABLE users ( id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(30) NOT NULL UNIQUE, password VARCHAR(30) NOT NULL, registration_time DATETIME NOT NULL);");
}

QJsonArray CServer::GetTable(const int id, ETypeTable type, TypeResultQuery* res)
{
	QSqlQuery q("USE data_server;");
	int idUser = GetIdUser(m_users[id].m_username, m_users[id].m_password);
	if (idUser != -1)
	{
		QSqlQuery q;
		q.exec("USE user_" + QString::number(idUser) + ';');

		QStringList names;

		switch (type)
		{
		case ETypeTable::All_Media:
		{
			q.exec("SELECT id_media, title, id_artist, id_album, year, id_genre, duraction, bitrate, add_time FROM media;");
			names.append("id_media");
			names.append("title");
			names.append("id_artist");
			names.append("id_album");
			names.append("year");
			names.append("id_genre");
			names.append("duraction");
			names.append("bitrate");
			names.append("add_time");
			break;
		}
		case ETypeTable::All_Albums:
		{
			q.exec("select * from albums;");
			names.append("id_album");
			names.append("title");
			break;
		}
		case ETypeTable::All_Artists:
		{
			q.exec("select * from artists;");
			names.append("id_artist");
			names.append("name");
			break;
		}
		case ETypeTable::All_Genres:
		{
			q.exec("select * from genres;");
			names.append("id_genre");
			names.append("title");
			break;
		}
		}

		QJsonArray table;

		int rows = 0;
		int count = names.size();

		while (q.next())
		{
			QJsonArray row;
			for (int i = 0; i < count; ++i)
			{
				QJsonObject obj;
				obj.insert(names[i], q.value(i).toJsonValue());
				row.append(obj);
			}
			table.append(row);
			++rows;
		}
		res->SetValue(ETypeResultQuery::Success);
		return table;
	}
	else
	{
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		STools::Msg(EMessage::Error, "User is not found");
		return QJsonArray();
	}
}

void CServer::CheckThisUser(const int id, QString username, QString password, TypeResultQuery* res)
{
	QSqlQuery q("USE data_server;");
	q.exec("SELECT * FROM users WHERE username='" + username + "' and password='" + password + "';");
	if (!q.next())
	{
		STools::Msg(EMessage::Error, "User is not found");
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		return;
	}
	m_users[id].isProven = true;
	m_users[id].m_username = username;
	m_users[id].m_password = password;
	res->SetValue(ETypeResultQuery::Success);
}

void CServer::AddNewMedia(const int idUser, QByteArray* data, bool newArtist, bool newAlbum, TypeResultQuery* res)
{
	/* Формирование пути к новому айдиофайлу */
	QSqlQuery q;
	QString id = QString::number(GetIdUser(m_users[idUser].m_username, m_users[idUser].m_password));
	if (id == -1)
	{
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		STools::Msg(EMessage::Error, "User is not found");
		return;
	}
	q.exec("USE user_" + id + ";");
	q.exec("SELECT * FROM media;");
	int rows = q.size();
	QDir().mkdir(m_path + "/user_" + id);
	QString path = m_path + "/user_" + id + "/id_" + QString::number(++rows) + ".mp3";
	/* Запись в файл новой медия */
	QFile f(path);
	if (!f.open(QIODevice::WriteOnly))
	{
		res->SetValue(ETypeResultQuery::WriteError);
		STools::Msg(EMessage::Error, "Write error");
		return;
	}
	f.write(*data);
	f.close();
	/* Получение основных тегов из медия */
	CTagEditer tagEditer;
	Tags tags = tagEditer.GetTags(path);
	/* Создание (если было указано) новой записи альбома */
	int id_album = 1;
	int id_artist = 1;
	if (newArtist)
	{
		q.exec("SELECT * FROM albums;");
		id_album = q.size() + 1;
		q.exec("INSERT INTO albums (title) VALUES ('" + tags.Album + "');");
	}
	else
	{
		q.exec("SELECT * FROM albums WHERE title='" + tags.Album + "';");
		if (q.next())  
			id_album = q.value(0).toInt();
	}
	/* Создание (если было указано) новой записи артиста */
	if (newAlbum)
	{
		q.exec("SELECT * FROM artists;");
		id_artist = q.size() + 1;
		q.exec("INSERT INTO artists (name) VALUES ('" + tags.Artist + "');");
	}
	else
	{
		q.exec("SELECT * FROM artists WHERE name='" + tags.Artist + "';");
		if (q.next())  
			id_artist = q.value(0).toInt();
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
	res->SetValue(ETypeResultQuery::Success);
}

void CServer::GetCoverArt(const int id, const int id_media, QByteArray* data, TypeResultQuery* res)
{
	QSqlQuery q;
	if (!q.exec("USE user_" + QString::number(GetIdUser(m_users[id].m_username, m_users[id].m_password)) + ";"))
	{
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		STools::Msg(EMessage::Error, "User is not found");
		return;
	}
	if (!q.exec("SELECT path FROM media WHERE id_album=" + QString::number(id_media) + ";"))
	{
		res->SetValue(ETypeResultQuery::IsNotFound);
		STools::Msg(EMessage::Error, "Is Not Found");
		return;
	}
	if (q.next())
	{
		CTagEditer tagEditer;
		data->clear();
		data->append(tagEditer.GetCoverArt(q.value(0).toString()));
	}
	else
	{
		res->SetValue(ETypeResultQuery::IsNotFound);
		STools::Msg(EMessage::Error, "Is Not Found");
		return;
	}
	res->SetValue(ETypeResultQuery::Success);
}

void CServer::GetMedia(const int id, const int id_media, QByteArray* data, TypeResultQuery* res)
{
	QSqlQuery q;
	if (!q.exec("USE user_" + QString::number(GetIdUser(m_users[id].m_username, m_users[id].m_password)) + ";"))
	{
		res->SetValue(ETypeResultQuery::UserIsNotFound);
		return;
	}
	if (!q.exec("SELECT path FROM media WHERE id_media=" + QString::number(id_media) + ";")) 
	{
		res->SetValue(ETypeResultQuery::IsNotFound);
		return;
	}
	QByteArray arr;
	if (q.next())
	{
		QFile f(q.value(0).toString());
		f.open(QIODevice::ReadOnly);
		data->clear();
		data->append(f.readAll());
		f.close();
	}
	else
	{
		res->SetValue(ETypeResultQuery::IsNotFound);
		return;
	}
	if (data->isEmpty())
	{
		res->SetValue(ETypeResultQuery::ReadError);
		return;
	}
	res->SetValue(ETypeResultQuery::Success);
}

int CServer::GetIdUser(QString username, QString password)
{
	QSqlQuery q("USE data_server;");
	q.exec("SELECT * FROM users WHERE username='" + username + "' and password='" + password + "';");
	if (q.next())
	{
		return q.value(0).toInt();
	}
	return -1;
}

void CServer::CreateNewUser(const int idUser, const QString username, const QString password, TypeResultQuery* res)
{
	QSqlQuery q("USE data_server;");
	if (!q.exec("INSERT INTO users (username, password, registration_time) VALUES (\'" + username + "\', \'" + password + "\', NOW());"))
	{
		res->SetValue(ETypeResultQuery::DuplicateUsername);
		return;
	}
	q.exec("SELECT * FROM users;");
	int id = q.size();
	q.exec("CREATE DATABASE user_" + QString::number(id) + ";");
	q.exec("USE user_" + QString::number(id) + ";");
	q.exec("CREATE TABLE artists (id_artist INT PRIMARY KEY AUTO_INCREMENT,name VARCHAR(150) NOT NULL);");
	q.exec("CREATE TABLE albums (id_album INT PRIMARY KEY AUTO_INCREMENT,title VARCHAR(150) NOT NULL);");
	q.exec("CREATE TABLE genres (id_genre INT PRIMARY KEY AUTO_INCREMENT,title VARCHAR(150) NOT NULL UNIQUE);");
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
	m_users[idUser].isProven = true;
	m_users[idUser].m_username = username;
	m_users[idUser].m_password = password;
	QDir().mkdir(m_path + "/user_" + QString::number(id));
	res->SetValue(ETypeResultQuery::Success);
}

bool operator==(const User& left, const User& right)
{

	if (left.m_socket == right.m_socket)
		return true;
	else
		return false;
}
