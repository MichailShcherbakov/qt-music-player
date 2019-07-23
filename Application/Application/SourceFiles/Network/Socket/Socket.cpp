#include "Socket.h"



Socket::Socket()
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
		if (!m_requestsList.isEmpty())
		{
			m_isQueueFree = false;

			QByteArray& query = m_requestsList.first().second;
			INetwork* key = m_requestsList.first().first;

			QByteArray msg;
			QDataStream out(&msg, QIODevice::WriteOnly);
			out.setVersion(QDataStream::Qt_5_12);
			out << query.size();
			msg.append(query);

			this->write(msg);
		}

		MSG(ETypeMessage::Log, "Connected to the server");
	}
}

void Socket::SendToServer(INetwork* sender, const QByteArray query)
{
	MSG(ETypeMessage::Log, "Sending data to server");

	QByteArray msg;
	QDataStream out(&msg, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_12);
	out << query.size();
	msg.append(query);

	m_requestsList.append(QPair<INetwork*, QByteArray>(sender, query));

	if (m_isQueueFree)
	{
		m_isQueueFree = false;
		this->write(msg);
	}
}

void Socket::ReadyRead()
{
	QByteArray buffer = this->readAll();
	m_size_packages += buffer.size();

	if (m_size_msg == 0)
	{
		QByteArray sizeArray;
		for (int i = 0; i < sizeof(int); ++i) sizeArray.append(buffer.at(i));

		QDataStream out(&sizeArray, QIODevice::ReadOnly);
		out.setVersion(QDataStream::Qt_5_12);
		out >> m_size_msg;

		MSG(ETypeMessage::Log, "Size of msg: " + QString::number(m_size_msg) + " bits");

		connect(this, &Socket::onSizeData, m_requestsList.first().first, &INetwork::GetSizeData);
		emit onSizeData(m_size_msg);
		disconnect(this, &Socket::onSizeData, m_requestsList.first().first, &INetwork::GetSizeData);

		buffer.remove(0, sizeof(int));
		m_size_packages -= sizeof(int);
	}

	connect(this, &Socket::onGetFromServer, m_requestsList.first().first, &INetwork::GetFromSocket);
	emit onGetFromServer(buffer);
	disconnect(this, &Socket::onGetFromServer, m_requestsList.first().first, &INetwork::GetFromSocket);

	if (m_size_msg == m_size_packages)
	{
		MSG(ETypeMessage::Success, "Data is gotten from the server fully");

		m_size_msg = 0;
		m_size_packages = 0;
		m_isQueueFree = true;

		INetwork* key = m_requestsList.first().first;
		emit key->onLoaded();
		m_requestsList.removeFirst();

		if (!m_requestsList.isEmpty())
		{
			m_isQueueFree = false;

			QByteArray& query = m_requestsList.first().second;
			INetwork* key = m_requestsList.first().first;
			
			QByteArray msg;
			QDataStream out(&msg, QIODevice::WriteOnly);
			out.setVersion(QDataStream::Qt_5_12);
			out << query.size();
			msg.append(query);

			this->write(msg);
		}
	}
}