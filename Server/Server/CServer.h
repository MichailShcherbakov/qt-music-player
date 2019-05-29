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

#include "CQuery.h"
#include "CTagEditer.h"

using namespace STools;

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

public:
	void CreateDataBase();

private:
	QString m_path = QCoreApplication::applicationDirPath() + "/DataServer";
	
	QTcpServer* server;
	QMap<int, QTcpSocket*> m_listClients;
	QMap<int, EQuery> m_typeQuery;
	QMap<int, QByteArray> m_file;
	QMap<int, QString> m_idUser;
	QMap<int, bool> m_queryCreateAlbum;
	QMap<int, bool> m_queryCreateArtist;
	QMap<int, int> m_size_end;
	QMap<int, int> m_size_now;
	QSqlDatabase db;

};



#endif
