#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <QObject>

#include "Interfaces/IChaptersManager.h"
#include "Interfaces/IThemeManager.h"

class Settings : public QObject
{
	Q_OBJECT

public:
	Settings();
	~Settings();

public:
	inline IChaptersManager* Chapters() { return m_pChapters; }
	inline IThemeManager* Themes() { return m_pThemeManager; }

public:
	inline void SetChaptersManager(IChaptersManager* chaptersManager) { m_pChapters = chaptersManager; }
	inline void SetThemeManager(IThemeManager* themeManager) { m_pThemeManager = themeManager; }

private:
	IChaptersManager* m_pChapters;
	IThemeManager* m_pThemeManager;
};

#endif