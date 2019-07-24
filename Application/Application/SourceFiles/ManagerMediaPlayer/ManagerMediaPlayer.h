#ifndef _MANAGER_MEDIA_PLAYER_H_
#define _MANAGER_MEDIA_PLAYER_H_

#include "StdAfx.h"

#include <QObject>

#include "Interfaces/ISectionListView.h"
#include "Playlist/Playlist.h"

class ManagerMediaPlayer : public QObject
{
	Q_OBJECT

public:
	ManagerMediaPlayer(QObject* parent = Q_NULLPTR);
	~ManagerMediaPlayer();

public slots:
	void SetConnectionWithSection(ISectionListView* const section);
	void CreateNewPlaylist(unsigned int index);

private:
	ISectionListView* m_pSection;
};

#endif
