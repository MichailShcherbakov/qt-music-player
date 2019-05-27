#include "CSocket.h"



CSocket::CSocket()
{
}

CSocket::~CSocket()
{
}

void CSocket::Initialize()
{
	this->connectToHost(m_ip, m_port);

	connect(this, &QTcpSocket::readyRead, this, &CSocket::ReadyRead);

	m_stream.setDevice(this);
	m_stream.setVersion(QDataStream::Qt_5_12);
}

void CSocket::sendToServer(QByteArray* query)
{
	this->write(*query);
}

void CSocket::ReadyRead()
{
	if (!m_isConnected)
	{
		if (this->readAll() == "You are connected")
		{
			qDebug() << "Connected to the server";
			m_isConnected = true;
			return;
		}
	}

	if (m_size == 0)
	{
		m_stream >> m_size;
	}

	if (this->bytesAvailable() == m_size)
	{
		m_buffer = new QByteArray(this->readAll());
		m_size = 0;
		emit getFromServer(m_buffer);
	}
}