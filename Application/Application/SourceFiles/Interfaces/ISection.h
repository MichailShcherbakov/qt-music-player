#ifndef _IBUFSECTION_H_
#define _IBUFSECTION_H_

#include "StdAfx.h"

#include <QObject>

#include "INetworkManager.h"

class ISection : public INetworkManager
{
	Q_OBJECT

public:
	ISection(Socket* const socket)
		: INetworkManager(socket) 
	{
		connect(this, &INetwork::onLoaded, this, [=]() {
			QByteArray t = m_pBuffer;
			m_pBuffer.clear();
			emit onGottenData(t);
			});
	}
	~ISection() {}

signals:
	void onGottenData(const QByteArray data);
};

#endif