#ifndef _ISECTION_H_
#define _ISECTION_H_

#include "StdAfx.h"

#include <QObject>

#include "EParams.h"
#include "INetworkManager.h"

class ISection : public INetworkManager
{
	Q_OBJECT

public:
	ISection(const EParams* const params) 
		: INetworkManager(params->m_pSocket) 
	{
		connect(this, &INetwork::onGetFromSocket, this, &ISection::ReadyRead);
		connect(this, &ISection::onGottenData, this, &ISection::GottenData);
		connect(this, &INetwork::onLoaded, this, [=]() {
			QByteArray t = m_pBuffer;
			m_pBuffer.clear();
			emit onGottenData(t);
			});
	}
	virtual ~ISection() {}

signals:
	void onGottenData(const QByteArray data);

public slots:
	virtual void Initialize() = 0;
	virtual void ReadyRead(QByteArray package) = 0;
	virtual void GottenData(QByteArray data) = 0;
};

#endif