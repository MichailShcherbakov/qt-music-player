#ifndef _ITHEME_H_
#define _ITHEME_H_

#include <QObject>
#include <QColor>

struct CenterFieldPlayer
{
	QColor FoneColor;
	QColor FontColor;
	QColor HoveredFontColor;
	QColor HoveredColor;
};

struct LeftFieldPlayer
{
	QColor Background;
	QColor HoveredBackgroundItem;
	QColor SingItemMenu;
};

struct ITheme : public QObject
{
	Q_OBJECT

public:
	CenterFieldPlayer CenterFieldPlayer;
	LeftFieldPlayer LeftFieldPlayer;
};

#endif
