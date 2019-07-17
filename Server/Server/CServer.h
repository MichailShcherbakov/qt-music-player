#ifndef _SERVER_H_
#define _SERVER_H_

#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QDatastream>
#include <QSqlQuery>
#include <QBuffer>
#include <QDir>
#include <QCoreApplication>
#include <QFile>
#include <QMap>
#include <QSqlRecord>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "ServerTools.h"
#include "CTagEditer.h"

using namespace STools;

enum class ETypeQuery : int
{
	Unknown = 0,
	Create_New_User,
	Check_This_User,
	Add_New_Media,
	Send_Table,
	Send_Cover_Art,
	Send_Media,
};

enum class ETypeTable : int
{
	Unknown = 0,
	All_Media,
	All_Genres,
	All_Albums,
	All_Artists,
};

enum class ETypeResultQuery : int 
{
	Unknown = 0,
	Success,
	DuplicateUsername,
	IsNotFound,
	FileIsEmpty,
	UserIsNotFound,
	ReadError,
	InsertError,
	WriteError,
	UserIsNotAuthorized,
};

struct TypeResultQuery
{
public:
	TypeResultQuery(ETypeResultQuery t = ETypeResultQuery::Unknown) : m_result(t) {}

public:
	void operator=(ETypeResultQuery t)
	{
		this->m_result = t;
	}
	void operator=(TypeResultQuery t)
	{
		this->m_result = t.m_result;
	}
	int toInt()
	{
		return static_cast<int>(this->m_result);
	}
	operator int()
	{
		return static_cast<int>(this->m_result);
	}
	void SetValue(ETypeResultQuery t)
	{
		this->m_result = t;
	}

private:
	ETypeResultQuery m_result;
};

struct User
{
public:
	bool operator==(const User& right)
	{
		if (right.m_socket == this->m_socket)
			return true;
		else
			return false;
	}
	friend bool operator==(const User& left, const User& right);

public:
	QTcpSocket* m_socket;
	QByteArray  m_buffer;
	bool isProven = false;
	QString m_username;
	QString m_password;
	int m_size_msg;
};

class CServer : public QTcpServer
{
	Q_OBJECT

public:
	CServer();
	~CServer();

public:
	void Initialize();

public slots:
	void StartServer();
	void incomingConnection(qintptr socketDescriptor);
	void SocketReady();
	void SocketDisconnected();
	void Send(QTcpSocket* socket, QByteArray data);

private:
	void CreateDataBase();
	QJsonArray GetTable(int id, ETypeTable type, TypeResultQuery* res);
	void CheckThisUser(const int id, QString username, QString password, TypeResultQuery* res);
	void AddNewMedia(int id, QByteArray* data, bool createNewArtist, bool createNewAlbum, TypeResultQuery* res);
	void GetCoverArt(int id, int id_album, QByteArray* data, TypeResultQuery* res);
	void GetMedia(int id, int id_media, QByteArray* data, TypeResultQuery* res);
	int GetIdUser(QString username, QString password);
	void CreateNewUser(const int id, const QString username, const QString password, TypeResultQuery* res);

private:
	QString m_path = QCoreApplication::applicationDirPath() + "/DataServer";
	QTcpServer* server;
	QMap<int, User> m_users;
	QSqlDatabase db;
};

#endif
