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

	//emit onCheckConnect();
}

void Socket::Disconnected()
{
	//emit onCheckConnect();
}

void Socket::CheckConnect()
{
	this->connectToHost(m_ip, m_port);

	if (this->state() != QTcpSocket::ConnectedState)
	{
		QMetaObject::invokeMethod(this, "CheckConnect", Qt::QueuedConnection);
	}
	else
	{
		MSG(ETypeMessage::Log, "Connected to the server");
	}
}

void Socket::SendToServer(const QByteArray& query)
{
	MSG(ETypeMessage::Log, "Sending data to server");

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

		MSG(ETypeMessage::Log, "Size of msg: " + QString::number(m_size_msg) + " bits");

		m_buffer.remove(0, sizeof(int));
	}

	if (m_size_msg == m_buffer.size())
	{
		MSG(ETypeMessage::Success, "Data is gotten from the server fully");

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