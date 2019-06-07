#ifndef _CSEVER_H_
#define _CSEVER_H_

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
	Unknown = -1,
	Create_New_User,
	Check_This_User,
	Add_New_Media,
	Send_Table,
	Send_Cover_Art,
	Send_Media,
};

enum class ETypeTable : int
{
	Unknown = -1,
	All_Media,
	All_Genres,
	All_Albums,
	All_Artists,
};

enum class ETypeResult : int {
	Unknown = -1,
	Success,
	Error,
	Duplicate_Username,
};

struct User
{
	QTcpSocket* m_socket;
	QByteArray  m_buffer;
	int m_size_msg;

	bool operator==(const User& right)
	{
		if (right.m_socket == this->m_socket)
			return true;
		else
			return false;
	}

	friend bool operator==(const User& left, const User& right);
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
	void Send(QTcpSocket* socket, QByteArray* data);

private:
	void CreateDataBase();
	void SendTable(ETypeTable type);
	void CheckUser();
	void AddNewMedia();
	void SendCoverArt();
	void SendMedia();
	bool CreateNewUser(QString username, QString password);

private:
	QString m_path = QCoreApplication::applicationDirPath() + "/DataServer";
	QTcpServer* server;
	QMap<int, User> m_users;
	QSqlDatabase db;

};



#endif
