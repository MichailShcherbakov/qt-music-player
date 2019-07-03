#include "Socket.h"



Socket::Socket() :
	m_buffer(nullptr)
{
}

Socket::~Socket()
{
}

void Socket::Initialize()
{
	this->connectToHost(m_ip, m_port);

	connect(this, &QTcpSocket::readyRead, this, &Socket::ReadyRead);
	connect(this, &QTcpSocket::disconnected, this, &Socket::Disconnected);
	connect(this, &Socket::onNextLoad, this, &Socket::SendToServer);
	connect(this, &Socket::onCheckConnect, this, &Socket::CheckConnect);

	emit onCheckConnect();
}

void Socket::Disconnected()
{
}

void Socket::CheckConnect()
{
	this->connectToHost(m_ip, m_port);

	if (this->state() != QTcpSocket::ConnectedState)
	{
		QMetaObject::invokeMethod(this, "CheckConnect", Qt::QueuedConnection);
	}
}

void Socket::SendToServer(const QByteArray& query)
{
	QByteArray msg;
	QDataStream out(&msg, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_12);
	out << query.size();
	msg.append(query);

	if (!m_isDataSent)
	{
		m_isDataSent = true;
		this->write(msg);
	}
	else
	{
		m_list.append(query);
	}
}

void Socket::ReadyRead()
{
	m_buffer.append(this->readAll());

	if (m_size_msg == 0)
	{
		QByteArray sizeArray;
		for (int i = 0; i < sizeof(int); ++i) sizeArray.append(m_buffer.at(i));

		QDataStream out(&sizeArray, QIODevice::ReadOnly);
		out.setVersion(QDataStream::Qt_5_12);
		out >> m_size_msg;

		m_buffer.remove(0, sizeof(int));
	}

	if (m_size_msg == m_buffer.size())
	{
		m_size_msg = 0;
		emit onGetFromServer(m_buffer);
		m_buffer.clear();

		m_isDataSent = false;
		if (!m_list.isEmpty())
		{
			QByteArray t = m_list.first();
			m_list.removeFirst();
			emit onNextLoad(t);
		}
	}
}