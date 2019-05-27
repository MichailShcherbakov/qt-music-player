#ifndef _CSEVER_H_
#define _CSEVER_H_

#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QDatastream>
#include <QSqlQuery>
#include <QBuffer>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QImage>

#include "CQuery.h"
#include "CMediaData.h"

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
	QByteArray Write(QVariant data);

private:
	QString m_path = "C:\\Users\\User\\Desktop\\Server\\DataServer";
	QTcpServer* server;
	QMap<int, QTcpSocket*> m_listClients;
	QMap<int, bool> m_isFile;
	QMap<int, QByteArray> m_file;
	QMap<int, QString> m_idUser;
	QMap<int, int> m_countMedia;
	QMap<int, int> m_size_end;
	QMap<int, int> m_size_now;
	QSqlDatabase db;

};



#endif
