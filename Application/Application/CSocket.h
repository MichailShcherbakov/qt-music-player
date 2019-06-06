#ifndef _CSOCKET_H_
#define _CSOCKET_H_


#include <QString>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

class CSocket : public QTcpSocket
{
	Q_OBJECT

public:
	CSocket();
	~CSocket();

public:
	void Initialize();

private slots:
	void ReadyRead();

public slots:
	void sendToServer(QByteArray* query);

signals:
	void getFromServer(QByteArray* data);

private:
	int			m_port = 6150;
	QString		m_ip = "192.168.0.108";
	QDataStream m_stream;
	int			m_size = 0;
	bool		m_isConnected = true;
	QByteArray* m_buffer;
};

#endif // !_CSOCKET_H_





