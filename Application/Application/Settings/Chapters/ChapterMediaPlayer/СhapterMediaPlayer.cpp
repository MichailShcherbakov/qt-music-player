#include "StdAfx.h"
#include "ChapterMediaPlayer.h"

�hapterMediaPlayer::�hapterMediaPlayer(QSettings* settings)
{
	m_pAppSettings = settings;

	qmlRegisterUncreatableType<PlayModeEnum>("packages.enums.playmode", 1, 0, "PlayModeEnum", "");
	qRegisterMetaType<PlayModeEnum::EPlayMode>("EPlayMode");

	m_pAppSettings->beginGroup("MediaPlayer");
	m_index = m_pAppSettings->value("id").toInt();
	m_title = m_pAppSettings->value("title").toString();
	m_artist = m_pAppSettings->value("artist").toString();
	m_time = m_pAppSettings->value("time").toString();
	m_playMode = static_cast<PlayModeEnum::EPlayMode>(m_pAppSettings->value("playMode").toInt());
	m_pAppSettings->endGroup();
}

�hapterMediaPlayer::~�hapterMediaPlayer()
{
}

void �hapterMediaPlayer::SetIndex(int index)
{
	m_index = index;
	m_pAppSettings->setValue("MediaPlayer/id", m_index);
	emit changeIndex();
}

int �hapterMediaPlayer::Index()
{
	return m_index;
}

void �hapterMediaPlayer::SetTitle(QString title)
{
	m_title = title;
	m_pAppSettings->setValue("MediaPlayer/title", m_title);
	emit changeTitle();
}

QString �hapterMediaPlayer::Title()
{
	return m_title;
}

void �hapterMediaPlayer::SetArtist(QString artist)
{
	m_artist = artist;
	m_pAppSettings->setValue("MediaPlayer/artist", m_artist);
	emit changeArtist();
}

QString �hapterMediaPlayer::Artist()
{
	return m_artist;
}

void �hapterMediaPlayer::SetTime(QString time)
{
	m_time = time;
	m_pAppSettings->setValue("MediaPlayer/time", m_time);
	emit changeTime();
}

QString �hapterMediaPlayer::Time()
{
	return m_time;
}

void �hapterMediaPlayer::SetPlayMode(PlayModeEnum::EPlayMode mode)
{
	m_playMode = mode;
	m_pAppSettings->setValue("MediaPlayer/playMode", static_cast<int>(m_playMode));
	emit changePlayMode();
}

PlayModeEnum::EPlayMode �hapterMediaPlayer::PlayMode()
{
	return m_playMode;
}
