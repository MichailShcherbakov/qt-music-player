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

	CQuery query(socket->readAll());

	switch (query.GetType().toInt())
	{
	case EQuery::CREATE_NEW_USER:
	{
		QSqlQuery q("USE data_server;");
		q.exec("INSERT INTO users (name, password, registration_time) VALUES (\'" + query.GetUser() + "\', \'" + query.GetPassword() + "\', NOW());");
		q.exec("SELECT * FROM users;");
		int id = query.GetID();
		q.exec("CREATE DATABASE user_" + QString::number(id) + ";");
		q.exec("USE user_" + QString::number(id) + ";");
		q.exec("CREATE TABLE main ( count_songs INT NOT NULL DEFAULT 0, count_album INT NOT NULL DEFAULT 0, count_play_list INT NOT NULL DEFAULT 0 );");
		q.exec("CREATE TABLE all_media ( id INT PRIMARY KEY AUTO_INCREMENT, title VARCHAR(45) NOT NULL, author VARCHAR(45) NOT NULL, genre VARCHAR(45) NOT NULL, year INT NOT NULL, path VARCHAR(150) NOT NULL);");

		/*
		
		CREATE TABLE artists (
			id_artist INT PRIMARY KEY AUTO_INCREMENT,
			name VARCHAR(150) NOT NULL UNIQUE
		);

		CREATE TABLE albums (
			id_album INT PRIMARY KEY AUTO_INCREMENT,
			title VARCHAR(150) NOT NULL UNIQUE
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
			FOREIGN KEY (id_artist) REFERENCES artists (id_artist) ON DELETE CASCADE,
			FOREIGN KEY (id_album) REFERENCES albums (id_album) ON DELETE CASCADE,
			FOREIGN KEY (id_genre) REFERENCES genres (id_genre) ON DELETE CASCADE,
		);
		
		*/

		QDir().mkdir(m_path + "\\user_" + QString::number(id));
		break;
	}
	case EQuery::CHECK_USER:
	{
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
	}

	/*if (m_isFile[id])
	{
		if (m_size_end[id] == 0)
		{
			QByteArray arr = socket->readAll();

			QDataStream in(&arr, QIODevice::ReadOnly);
			in >> m_size_end[id];

			Msg(Warning, QString::number(m_size_end[id]));
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
			Msg(Log, "Size: " + QString::number(m_size_now[id]) + " BYTE (" + Size + "MB)");

			QByteArray arr = socket->readAll();
			m_file[id].append(arr);
		}
		if (m_size_end[id] == m_size_now[id])
		{
			Msg(Success, "End");

			QString path = m_path + "\\user_" + m_idUser[id] + "\\id_" + QString::number(m_countMedia[id]+1) + ".mp3";
			QFile media(path);
			media.open(QFile::WriteOnly);
			media.write(m_file[id]);
			media.close();

			CMediaData data;
			data.GetMainData(path);
			
			QSqlQuery q;
			q.exec("USE user_" + m_idUser[id] + ";");
			QString first = "INSERT INTO all_media (title, author, genre, year, path) VALUES (";
			QString second = '\'' + data.GetTitle() + "\'," +
				'\'' + data.GetAuthor() + "\'," +
				'\'' + data.GetGenre() + "\'," +
				'\'' + data.GetYear() + "\'," +
				'\'' + path.replace('\\', "\\\\") + '\'' +
				");";
			QString h = first + second;
			q.exec(h);

			m_size_end[id] = 0;
			m_size_now[id] = 0;
			m_countMedia[id] = 0;
			m_idUser[id] = "";
			m_file[id].clear();
			m_isFile[id] = false;
		}
		return;
	}

	if (query.GetUser() != "" && query.GetPassword() != "")
	{
		if (query.GetType().toInt() != CREATE_NEW_USER && query.GetID() == "-1")
		{
			Msg(Error, "The user is not found");
			return;
		}	
	}

	switch (query.GetType().toInt())
	{
	case SEND_MEDIA:
	{
		Msg(Log, "Sending needed music");

		QSqlQuery q;
		q.exec("USE user_" + query.GetID() + ";");
		q.exec("SELECT * FROM all_media;");

		while (q.next())
		{
			if (q.value(1).toString() == query.GetValue_1() && q.value(2).toString() == query.GetValue_2())
			{
				QByteArray arr;

				QFile file;
				file.setFileName(q.value(5).toString().toUtf8());
				file.open(QFile::ReadOnly);

				// Отправка клиету размер файла
				QByteArray size_of_file;
				QDataStream strm(&size_of_file, QIODevice::WriteOnly);
				strm << (int)(file.size());
				socket->write(size_of_file);

				QString size = QString::number((float)file.size() / 1024 / 1024);
				QString Size;
				Size.append(size[0]);
				Size.append(size[1]);
				Size.append(size[2]);
				Size.append(size[3]);
				Msg(Log, "Size: " + QString::number(file.size()) + " BYTE (" + Size + "MB)");

				arr = file.readAll();
				socket->write(arr);
				file.close();
			}
		}
		break;
	}
	case CREATE_NEW_USER:
	{
		QSqlQuery q("USE mainserver;");
		q.exec("INSERT INTO users (name, password) VALUES (\'" + query.GetValue_1() + "\', \'" + query.GetValue_2() + "\');");
		q.exec("SELECT * FROM users;");
		int id;
		while (q.next())
		{
			if (q.value(1).toString() == query.GetValue_1() && q.value(2).toString() == query.GetValue_2())
				id = q.value(0).toInt();
		}
		q.exec("CREATE DATABASE user_" + QString::number(id) + ";");
		q.exec("USE user_" + QString::number(id) + ";");
		q.exec("CREATE TABLE main ( count_songs INT NOT NULL DEFAULT 0, count_album INT NOT NULL DEFAULT 0, count_play_list INT NOT NULL DEFAULT 0 );");
		q.exec("CREATE TABLE all_media ( id INT PRIMARY KEY AUTO_INCREMENT, title VARCHAR(45) NOT NULL, author VARCHAR(45) NOT NULL, genre VARCHAR(45) NOT NULL, year INT NOT NULL, path VARCHAR(150) NOT NULL);");

		QDir().mkdir(m_path + "\\user_" + QString::number(id));
		break;
	}
	case SEND_TABLE:
	{
		switch (query.GetValue_1().toInt())
		{
		case ALL_MUSIC:
		{
			QSqlQuery q;
			q.exec("USE user_" + query.GetID() + ";");
			q.exec("SELECT * FROM all_media;");
			QVector<QVector<QString>> table;
			QString qr;
			int rows = 0;
			int column = 5;
			while (q.next())
			{
				rows++;
				QVector<QString> temp;
				for (int i = 0; i < column; ++i)
					temp.push_back('[' + q.value(i).toString() +']');
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
			QDataStream o(&size, QIODevice::WriteOnly);
			o << (int)data.length();
			socket->write(size);

			
			socket->write(data);
			break;
		}
		}
		break;
	}
	case ADD_NEW_MUSIC:
	{
		m_isFile[id] = true;
		QSqlQuery q;
		q.exec("USE user_" + query.GetID() + ";");
		q.exec("SELECT * FROM all_media;");
		int count = 0;
		while (q.next())
		{
			++count;
		}
		m_countMedia[id] = count;
		m_idUser[id] = query.GetID();
		break;
	}
	case SEND_IMAGE:
	{
		QSqlQuery q;
		q.exec("USE user_" + query.GetID() + ";");
		q.exec("SELECT * FROM all_media;");
		while (q.next())
		{
			if (q.value(1).toString() == query.GetValue_1() && q.value(2).toString() == query.GetValue_2())
			{
				QString path = q.value(5).toString();
				CMediaData data;
				QByteArray img = data.GetImage(path);

				// Отправка клиету размер файла
				QByteArray size_of_img;
				QDataStream strm(&size_of_img, QIODevice::WriteOnly);
				strm << img.length();
				socket->write(size_of_img);

				QString size = QString::number((float)img.length() / 1024 / 1024);
				QString Size;
				Size.append(size[0]);
				Size.append(size[1]);
				Size.append(size[2]);
				Size.append(size[3]);
				Msg(Log, "Size: " + QString::number(img.length()) + " BYTE (" + Size + "MB)");

				socket->write(img);
			}
		}
	}
	}

	Msg(Log, "The data is sent");*/
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
	m_countMedia.remove(key);
	m_idUser.remove(key);
	m_isFile.remove(key);
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

QByteArray CServer::Write(QVariant data)
{
	QByteArray array;
	QDataStream out(&array, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_12);
	out << data;
	return array;
}
