#include "StdAfx.h"
#include "ThemeManager.h"

ThemeManager::ThemeManager()
{
	m_pAppSettings = new QSettings("settings.ini", QSettings::IniFormat);

	m_typeTheme = static_cast<IThemeManager::ETypeTheme>(m_pAppSettings->value("Theme/type").toInt());

	SetTheme(m_typeTheme);

	gParams->pRootContext->setContextProperty("Themes", this);
}

ThemeManager::~ThemeManager()
{
	SAFE_DELETE(m_pAppSettings);
}

void ThemeManager::SetTheme(ETypeTheme typeTheme)
{
	m_typeTheme = typeTheme;

	switch (typeTheme)
	{
	case IThemeManager::ETypeTheme::White:
	{
		m_pTheme = new WhiteTheme();
		break;
	}
	case IThemeManager::ETypeTheme::Dark:
	{
		break;
	}
	}
}

QColor ThemeManager::FoneColor()
{
	return m_pTheme->CenterFieldPlayer.FoneColor;
}

QColor ThemeManager::FontColor()
{
	return m_pTheme->CenterFieldPlayer.FontColor;
}

QColor ThemeManager::FontHoveredColor()
{
	return m_pTheme->CenterFieldPlayer.HoveredFontColor;
}

QColor ThemeManager::HoveredColor()
{
	return m_pTheme->CenterFieldPlayer.HoveredColor;
}

QColor ThemeManager::LeftFieldBackground()
{
	return m_pTheme->LeftFieldPlayer.Background;
}

QColor ThemeManager::LeftFieldHoveredBackgroundItem()
{
	return m_pTheme->LeftFieldPlayer.HoveredBackgroundItem;
}

QColor ThemeManager::LeftFieldSingItemMenu()
{
	return m_pTheme->LeftFieldPlayer.SingItemMenu;
}
