#ifndef _SERVER_H_
#define _SERVER_H_

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QMap>

#include "Database/Database.h"

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

struct User
{
	friend bool operator==(const User left, const User right) // for QMap
	{
		if (left.m_pSocket == right.m_pSocket && 
			left.m_buffer == right.m_buffer &&
			left.isProven == right.isProven &&
			left.m_hashUsers == right.m_hashUsers &&
			left.m_size_msg == right.m_size_msg)
		{
			return true;
		}
		return false;
	}
	QTcpSocket* m_pSocket;
	QByteArray  m_buffer;
	bool isProven = false;
	QByteArray m_hashUsers;
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

private:
	Database* m_pDatabase;
	QTcpServer* m_pServer;
	QMap<int, User> m_users;
	QString m_path = QCoreApplication::applicationDirPath() + "/Data";
};

#endif
