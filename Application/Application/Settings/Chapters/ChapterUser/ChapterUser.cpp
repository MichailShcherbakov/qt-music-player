#include "StdAfx.h"
#include "ChapterUser.h"

ChapterUser::ChapterUser()
{
	m_pAppSettings = new QSettings("settings.ini", QSettings::IniFormat);

	m_pAppSettings->beginGroup("User");
	m_remember = m_pAppSettings->value("remember").toBool();
	m_hashCode = m_pAppSettings->value("hashCode").toString();
	m_pAppSettings->endGroup();
}

ChapterUser::~ChapterUser()
{
}

void ChapterUser::SetRemember(bool remember)
{
	m_remember = remember;
	m_pAppSettings->setValue("User/remember", m_remember);
	emit changeRemember();
}

bool ChapterUser::Remember()
{
	return m_remember;
}

void ChapterUser::SetHashCode(QString hash)
{
	m_hashCode = hash;
	m_pAppSettings->setValue("User/hashCode", m_hashCode);
	emit changeHashCode();
}

QString ChapterUser::HashCode()
{
	return m_hashCode;
}
