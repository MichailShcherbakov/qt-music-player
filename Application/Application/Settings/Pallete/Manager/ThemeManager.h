#ifndef _THEME_MANAGER_H_
#define _THEME_MANAGER_H_

#include "Interfaces/IThemeManager.h"

#include "Settings/Pallete/WhiteTheme/WhiteTheme.h"

class ThemeManager : public IThemeManager
{
	Q_OBJECT
	Q_PROPERTY(QColor FoneColor READ FoneColor NOTIFY colorChanged);
	Q_PROPERTY(QColor FontColor READ FontColor NOTIFY colorChanged);
	Q_PROPERTY(QColor FontHoveredColor READ FontHoveredColor NOTIFY colorChanged);
	Q_PROPERTY(QColor HoveredColor READ HoveredColor NOTIFY colorChanged);
	Q_PROPERTY(QColor LeftFieldBackground READ LeftFieldBackground NOTIFY colorChanged);
	Q_PROPERTY(QColor LeftFieldHoveredBackgroundItem READ LeftFieldHoveredBackgroundItem NOTIFY colorChanged);
	Q_PROPERTY(QColor LeftFieldSingItemMenu READ LeftFieldSingItemMenu NOTIFY colorChanged);

public:
	ThemeManager();
	~ThemeManager() override;

public:
	virtual void SetTheme(ETypeTheme m_typeTheme) override;

public:
	QColor FoneColor();
	QColor FontColor();
	QColor FontHoveredColor();
	QColor HoveredColor();
	QColor LeftFieldBackground();
	QColor LeftFieldHoveredBackgroundItem();
	QColor LeftFieldSingItemMenu();

signals:
	void themeChanged();
	void colorChanged();

private:
	QSettings* m_pAppSettings;
};

#endif
