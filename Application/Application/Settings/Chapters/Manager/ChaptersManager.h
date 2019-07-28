#ifndef _CHAPTERS_MANAGER_H_
#define _CHAPTERS_MANAGER_H_

#include "Interfaces/IChaptersManager.h"

#include "Settings/Chapters/ChapterMediaPlayer/ChapterMediaPlayer.h"
#include "Settings/Chapters/ChapterSortTables/ChapterSortTables.h"
#include "Settings/Chapters/ChapterUser/ChapterUser.h"

class ChaptersManager : public IChaptersManager
{
public:
	ChaptersManager();
	~ChaptersManager();
};

#endif
