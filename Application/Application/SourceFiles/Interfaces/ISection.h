#ifndef _IBUFSECTION_H_
#define _IBUFSECTION_H_

#include <QObject>

#include "INetworkManager.h"

class ISection : public INetworkManager
{
	Q_OBJECT

public:
	ISection(Socket* const socket)
		: INetworkManager(socket) 
	{
		connect(this, &INetwork::loaded, this, [=]() {
			QByteArray t = m_pBuffer;
			m_pBuffer.clear();
			emit gottenData(t);
			});
	}
	~ISection() {}

signals:
	void gottenData(const QByteArray data);
};

#endif