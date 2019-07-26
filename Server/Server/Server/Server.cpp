#include "Server.h"

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
	{
		MSG(EMessage::Success, "Server is started");
	}	
	else
	{
		MSG(EMessage::Error, "Server isn't started");
	}
}

void CServer::incomingConnection(qintptr socketDescriptor)
{
	QTcpSocket* socket = new QTcpSocket;
	socket->setSocketDescriptor(socketDescriptor);
	User user;
	user.m_pSocket = socket;
	user.m_size_msg = 0;
	user.m_buffer.clear();
	m_users[socketDescriptor] = user;

	connect(user.m_pSocket, &QTcpSocket::readyRead, this, &CServer::SocketReady);
	connect(user.m_pSocket, &QTcpSocket::disconnected, this, &CServer::SocketDisconnected);

	MSG(EMessage::Log, "Client " + QString::number(socketDescriptor) + " is connected");
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

		MSG(EMessage::Log, "Size msg: " + QString::number(m_users[id].m_size_msg) + " bytes");

		m_users[id].m_buffer.remove(0, sizeof(int));
	}

	if (m_users[id].m_size_msg == m_users[id].m_buffer.size())
	{
		MSG(EMessage::Success, "Data is came fully");

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
			MSG(EMessage::Log, "The request for creating a new user");

			QByteArray hash = header["hashCode"].toString().toLatin1();

			m_pDatabase->CreateNewUser(hash, res);

			if (res == ETypeResultQuery::Success)
			{
				m_users[id].isProven = true;
				m_users[id].m_hashUsers = hash;

				int dbIDUsers = m_pDatabase->UsersID(hash);
				QDir().mkdir(m_path + "/user_" + QString::number(dbIDUsers));
			}
			else
			{
				MSG(EMessage::Error, "Can't create new user");
			}
			break;
		}
		case ETypeQuery::Check_This_User:
		{
			MSG(EMessage::Log, "The request for checking the user");

			QByteArray hash = header["hashCode"].toString().toLatin1();

			m_pDatabase->CheckUser(hash, res);

			if (res == ETypeResultQuery::Success)
			{
				m_users[id].isProven = true;
				m_users[id].m_hashUsers = hash;
			}
			break;
		}
		case ETypeQuery::Add_New_Media:
		{
			MSG(EMessage::Log, "The request for adding a new media");

			if (m_users[id].isProven)
			{
				Tags tags;
				tags.Title = body["title"].toString();
				tags.Album = body["album"].toString();
				tags.Artist = body["artist"].toString();
				tags.Bitrate = body["bitrate"].toString();
				tags.Duration = body["duration"].toString();
				tags.Year = body["year"].toString();
				tags.Genre = body["genre"].toString();
				tags.Image = body["cover-art"].toString().toLatin1();
				tags.Lyric = body["lyric"].toString();
				tags.LyricsTranslation = body["lyrics-translation"].toString();

				QByteArray media = body["media"].toString().toLatin1();

				bool createNewArtsit = body["create-new-artist"].toBool();
				bool createNewAlbum = body["create-new-album"].toBool();

				m_pDatabase->AddNewMedia(m_users[id].m_hashUsers, &media, tags, createNewArtsit, createNewAlbum, res);
			}
			else
			{
				res->SetValue(ETypeResultQuery::UserIsNotAuthorized);
				MSG(EMessage::Error, "User is not authorized");
			}
			break;
		}
		case ETypeQuery::Send_Table:
		{
			MSG(EMessage::Log, "The request for sending the table");

			if (m_users[id].isProven)
			{
				ETypeTable typeTable = static_cast<ETypeTable>(header["type-table"].toInt());
				int limit = body["limit"].toInt();
				int offset = body["offset"].toInt();
				bool merger = body["merger"].toBool();
				ETypeSort typeSort = static_cast<ETypeSort>(body["type-sort"].toInt());
				EStateSort stateSort = static_cast<EStateSort>(body["state-sort"].toInt());
				QJsonArray table = m_pDatabase->GetTable(m_users[id].m_hashUsers, typeTable, merger, limit, offset, typeSort, stateSort, res);
				sendBody.insert("table", table);
			}
			else
			{
				res->SetValue(ETypeResultQuery::UserIsNotAuthorized);
				MSG(EMessage::Error, "User is not authorized");
			}
			break;
		}
		case ETypeQuery::Send_Table_Size:
		{
			MSG(EMessage::Log, "The request for sending the table size");

			if (m_users[id].isProven)
			{
				ETypeTable typeTable = static_cast<ETypeTable>(header["type-table"].toInt());
				int tableSize = m_pDatabase->FullSizeTable(m_users[id].m_hashUsers, typeTable, res);
				sendBody.insert("table-size", tableSize);
			}
			else
			{
				res->SetValue(ETypeResultQuery::UserIsNotAuthorized);
				MSG(EMessage::Error, "User is not authorized");
			}
			break;
		}
		case ETypeQuery::Send_Cover_Art:
		{
			MSG(EMessage::Log, "The request for sending the art cover");

			if (m_users[id].isProven)
			{
				QByteArray coverArt;
				const int width = body["width"].toInt();
				const int height = body["height"].toInt();
				m_pDatabase->CoverArt(m_users[id].m_hashUsers, width, height, body["id-media"].toInt(), &coverArt, res);
				QString t = QString::fromLatin1(coverArt, coverArt.size());
				sendBody.insert("cover-art", t);
			}
			else
			{
				res->SetValue(ETypeResultQuery::UserIsNotAuthorized);
				MSG(EMessage::Error, "User is not authorized");
			}
			break;
		}
		case ETypeQuery::Send_Media:
		{
			MSG(EMessage::Log, "The request for sending the media");

			if (m_users[id].isProven)
			{
				QByteArray media;
				m_pDatabase->Media(m_users[id].m_hashUsers, body["id-media"].toInt(), &media, res);
				Send(socket, media);

				m_users[id].m_size_msg = 0;
				m_users[id].m_buffer.clear();

				MSG(EMessage::Log, "Reply has been sent");
				return;
			}
			else
			{
				res->SetValue(ETypeResultQuery::UserIsNotAuthorized);
				MSG(EMessage::Error, "User is not authorized");
			}
			break;
		}
		default:
		{
			MSG(EMessage::Error, "Unknown type query");
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

		MSG(EMessage::Log, "Reply has been sent");
	}
}

void CServer::SocketDisconnected()
{
	MSG(EMessage::Log, "Client is disconnected");

	QTcpSocket* clientSocket = (QTcpSocket*)sender();

	for (auto it : m_users)
	{
		if (it.m_pSocket == clientSocket)
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
	m_pDatabase = new Database;
	m_pDatabase->Initialize();
}