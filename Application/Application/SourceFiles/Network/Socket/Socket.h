#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "StdAfx.h"

#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

#include "Interfaces/INetwork.h"

class Socket : public QTcpSocket
{
	Q_OBJECT

public:
	Socket();
	~Socket();

public:
	void Initialize();

private slots:
	void ReadyRead();
	void Disconnected();
	void CheckConnect();

public slots:
	void SendToServer(INetwork* sender, const QByteArray query);

signals:
	void onGetFromServer(QByteArray data);
	void onNextLoad(INetwork* sender, const QByteArray query);
	void onCheckConnect();

private:
	int			m_port = 6150;
	QString		m_ip = "192.168.0.108"; // Laptop - 192.168.0.105  Desktop - 192.168.0.108
	int			m_size_msg = 0;
	int			m_size_packages = 0;
	bool		m_isConnected = false;
	bool		m_isQueueFree = true;
	QList<QPair<INetwork*, QByteArray>> m_requestsList;
};

#endif // !_CSOCKET_H_





