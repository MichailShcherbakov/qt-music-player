#ifndef _ISECTION_H_
#define _ISECTION_H_

#include "StdAfx.h"

#include <QObject>

#include "Interfaces/ISection.h"

class ISectionObject : public ISection
{
	Q_OBJECT

public:
	ISectionObject(Socket* socket)
		: ISection(socket)
	{
		connect(this, &INetwork::onGetFromSocket, this, &ISectionObject::ReadyRead);
		connect(this, &ISection::onGottenData, this, &ISectionObject::GottenData);
	}
	virtual ~ISectionObject() {}

public slots:
	virtual void Initialize() = 0;
	virtual void ReadyRead(QByteArray package) = 0;
	virtual void GottenData(QByteArray data) = 0;
};

#endif