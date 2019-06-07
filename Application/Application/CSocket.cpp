#include "CSocket.h"



CSocket::CSocket() :
	m_buffer(nullptr)
{
}

CSocket::~CSocket()
{
}

void CSocket::Initialize()
{
	this->connectToHost(m_ip, m_port);
	connect(this, &QTcpSocket::readyRead, this, &CSocket::ReadyRead);
}

void CSocket::sendToServer(QByteArray* query)
{
	QByteArray msg;
	QDataStream out(&msg, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_12);
	out << query->size();
	msg.append(*query);

	this->write(msg);
}

void CSocket::ReadyRead()
{
	if (!m_buffer)
		m_buffer = new QByteArray();
	else
		m_buffer->clear();

	m_buffer->append(this->readAll());

	if (m_size_msg == 0)
	{
		QByteArray sizeArray;
		for (int i = 0; i < sizeof(int); ++i) sizeArray.append(m_buffer->at(i));

		QDataStream out(&sizeArray, QIODevice::ReadOnly);
		out.setVersion(QDataStream::Qt_5_12);
		out >> m_size_msg;

		m_buffer->remove(0, sizeof(int));
	}

	if (m_size_msg == m_buffer->size())
	{
		m_size_msg = 0;
		emit getFromServer(m_buffer);
	}
}