#include "StdAfx.h"
#include "WhiteTheme.h"

WhiteTheme::WhiteTheme()
{
	CenterFieldPlayer.FoneColor = QColor("#FFF");
	CenterFieldPlayer.FontColor = QColor("#000");
	CenterFieldPlayer.HoveredFontColor = QColor("#111");
	CenterFieldPlayer.HoveredColor = QColor("#DBDBDB");

	LeftFieldPlayer.Background = QColor("#F6F8F9");
	LeftFieldPlayer.HoveredBackgroundItem = QColor("#ECEEEE");
	LeftFieldPlayer.SingItemMenu = QColor("#515C6B");
}