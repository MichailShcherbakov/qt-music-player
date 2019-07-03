#ifndef _SOCKET_H_
#define _SOCKET_H_


#include <QString>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

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
	void SendToServer(const QByteArray& query);

signals:
	void onGetFromServer(QByteArray data);
	void onNextLoad(QByteArray data);
	void onCheckConnect();

private:
	int			m_port = 6150;
	QString		m_ip = "192.168.0.108";
	int			m_size_msg = 0;
	bool		m_isConnected = false;
	bool		m_isDataSent = false;
	QByteArray  m_buffer;
	QList<QByteArray> m_list;
};

#endif // !_CSOCKET_H_





