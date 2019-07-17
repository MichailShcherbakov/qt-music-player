#ifndef _INETWORK_H_
#define _INETWORK_H_

#include "StdAfx.h"

#include <QObject>
#include "Query.h"

class INetwork : public QObject
{
	Q_OBJECT

public:
	INetwork()
		: m_pBuffer(Q_NULLPTR)
	{
		connect(this, &INetwork::onGetFromSocket, this, [=](QByteArray data) { m_pBuffer.append(data); });
	}
	~INetwork() {}

public slots:
	inline void GetFromSocket(const QByteArray data) { emit onGetFromSocket(data); }

signals:
	void onGetFromSocket(const QByteArray data);
	void onSendToSocket(INetwork* sender, const QByteArray query);
	void onLoaded();

protected:
	QByteArray m_pBuffer;
};

#endif // !_CSOCKET_H_





