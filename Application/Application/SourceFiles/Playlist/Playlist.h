#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include <QObject>

#include "Interfaces/IPlaylist.h"

class Playlist : public IPlaylist
{
	Q_OBJECT

public:
	Playlist(unsigned int index, const Query& query);
	~Playlist() override;

public slots:
	// IPlaylist
	virtual void Initialize() override;
	virtual void ReadyRead(QByteArray package) override;
	virtual void GottenData(QByteArray data) override;
	virtual void LoadData(uint index) override;
	virtual uint FirstIndex() override;
	virtual uint EndIndex() override;
	virtual uint NextIndex(uint index) override;
	virtual uint PreviousIndex(uint index) override;
	virtual bool Contains(uint index) override;
	// ~IPlaylist

public slots:
	inline void SetLoadQuery(const Query& query) { m_rootLoadQuery = query; }

private:
	uint m_localSize = 0;
	uint m_fullSize = 0;
	const unsigned int m_sizeCacheBuffer = 8;
	Query m_rootLoadQuery;
	QHash<int, int> m_listIndex;
};

#endif