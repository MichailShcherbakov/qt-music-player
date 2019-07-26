#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <QObject>

#include "Chapters/ChapterUser/ChapterUser.h"
#include "Chapters/ChapterSortTables/ChapterSortTables.h"
#include "Chapters/ChapterMediaPlayer/ChapterMediaPlayer.h"

class IniChapters
{
public:
	IniChapters()
	{
		m_pAppSettings = new QSettings("settings.ini", QSettings::IniFormat);

		m_p—hapterMediaPlayer = new ChapterMediaPlayer(m_pAppSettings);
		m_pChapterSortTables = new ChapterSortTables(m_pAppSettings);
		m_pChapterUser = new ChapterUser(m_pAppSettings);
	}

	~IniChapters() 
	{
		SAFE_DELETE(m_pChapterUser);
		SAFE_DELETE(m_pChapterSortTables);
		SAFE_DELETE(m_p—hapterMediaPlayer);
		SAFE_DELETE(m_pAppSettings);
	}

public:
	inline ChapterMediaPlayer* MediaPlayer() { return m_p—hapterMediaPlayer; }
	inline ChapterSortTables* SortTables() { return m_pChapterSortTables; }
	inline ChapterUser* User() { return m_pChapterUser; }

private:
	QSettings* m_pAppSettings;
	ChapterMediaPlayer* m_p—hapterMediaPlayer;
	ChapterSortTables* m_pChapterSortTables;
	ChapterUser* m_pChapterUser;
};

class Settings : public QObject
{
	Q_OBJECT

public:
	Settings();
	~Settings();

public:
	inline IniChapters* Chapters() { return m_pChapters; }

private:
	IniChapters* m_pChapters;
};

#endif
