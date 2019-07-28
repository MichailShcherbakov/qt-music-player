#ifndef _ICHAPTERS_MANAGER_H_
#define _ICHAPTERS_MANAGER_H_

#include "Interfaces/IChapterMediaPlayer.h"
#include "Interfaces/IChapterSortTables.h"
#include "Interfaces/IChapterUser.h"

class IChaptersManager : public QObject
{
	Q_OBJECT

public:
	IChaptersManager() {}
	~IChaptersManager()
	{
		SAFE_DELETE(m_pChapterUser);
		SAFE_DELETE(m_pChapterSortTables);
		SAFE_DELETE(m_p—hapterMediaPlayer);
	}

public:
	inline IChapterMediaPlayer* MediaPlayer() { return m_p—hapterMediaPlayer; }
	inline IChapterSortTables* SortTables() { return m_pChapterSortTables; }
	inline IChapterUser* User() { return m_pChapterUser; }

protected:
	IChapterMediaPlayer* m_p—hapterMediaPlayer;
	IChapterSortTables* m_pChapterSortTables;
	IChapterUser* m_pChapterUser;
};

#endif
