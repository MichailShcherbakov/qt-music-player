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

enum class ELoadState : int
{
	Unknown = -1,
	Header,
	Body,
	Footer
};

enum class ETypeQuery : int
{
	Unknown = -1,
	Create_New_User,
};

enum class ETypeTable : int
{
	Unknown = -1,
};

struct User
{
	QTcpSocket* m_socket;
	ETypeQuery m_typeQuery;
	QByteArray  m_buffer;
	ELoadState m_loadState;
	QString m_username;
	QString m_password;
	int m_size_end;
	int m_size_now;
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
