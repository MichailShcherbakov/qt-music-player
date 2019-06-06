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

#include "CQuery.h"
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
	void SendTable(ETable type);
	void CheckUser();
	void AddNewMedia();
	void SendCoverArt();
	void SendMedia();
	void CreateNewUSer(QString username, QString password);

private:
	QString m_path = QCoreApplication::applicationDirPath() + "/DataServer";
	
	QTcpServer* server;
	QMap<int, QTcpSocket*> m_listClients;
	QMap<int, ETypeQuery> m_typeQuery;
	QMap<int, QByteArray> m_buffer;
	QMap<int, ELoadState> m_loadState;
	QMap<int, int> m_size_end;
	QMap<int, int> m_size_now;
	QSqlDatabase db;

};



#endif
