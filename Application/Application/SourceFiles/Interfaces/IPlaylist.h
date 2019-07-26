#ifndef _IPLAYLIST_H_
#define _IPLAYLIST_H_

#include <QObject>

#include "Interfaces/ISection.h"

class IPlaylist : public ISection
{
	Q_OBJECT

public:
	IPlaylist(Socket* socket)
		: ISection(socket)
	{
		connect(this, &INetwork::getFromSocket, this, &IPlaylist::ReadyRead);
		connect(this, &ISection::gottenData, this, &IPlaylist::GottenData);
	}
	virtual ~IPlaylist() {}

public slots:
	virtual void Initialize() = 0;
	virtual void ReadyRead(QByteArray package) = 0;
	virtual void GottenData(QByteArray data) = 0;
	virtual void LoadData() = 0;
	virtual uint FirstIndex() = 0;
	virtual uint EndIndex() = 0;
	virtual uint NextIndex(uint index) = 0;
	virtual uint PreviousIndex(uint index) = 0;
	virtual bool Contains(uint index) = 0;
	virtual uint Size() = 0;
	virtual uint IndexOf(uint index) = 0;
};

#endif