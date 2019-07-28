#include "StdAfx.h"
#include "ChaptersManager.h"

ChaptersManager::ChaptersManager()
{
	m_p—hapterMediaPlayer = new ChapterMediaPlayer;
	m_pChapterSortTables = new ChapterSortTables;
	m_pChapterUser = new ChapterUser;
}

ChaptersManager::~ChaptersManager()
{
}
