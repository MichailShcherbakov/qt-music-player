#include "StdAfx.h"
#include "MediaPlayer.h"

MediaPlayer::MediaPlayer() 
	: IMediaPlayer(gParams->pSocket),
	m_playState(EPlayerState::Pause),
	m_pPlayer(Q_NULLPTR),
	m_pPlaylist(Q_NULLPTR),
	m_pBuffer(Q_NULLPTR)
{
	gParams->pRootContext->setContextProperty(QStringLiteral("mediaPlayer"), this);

	m_playMode = gParams->pSettings->Chapters()->MediaPlayer()->PlayMode();
}

MediaPlayer::~MediaPlayer()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pPlaylist);
	SAFE_DELETE(m_pBuffer);
}

void MediaPlayer::Initialize()
{
	m_pPlayer = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
	m_pBuffer = new QBuffer;
	m_pBuffer->open(QIODevice::ReadWrite);

	m_currentIndex = gParams->pSettings->Chapters()->MediaPlayer()->Index();

	connect(m_pPlayer, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayer::MediaStatusChanged);
	connect(m_pPlayer, &QMediaPlayer::positionChanged, this, &MediaPlayer::ChangeCurrentTime);
	connect(this, &MediaPlayer::previous, this, &MediaPlayer::Previous);
	connect(this, &MediaPlayer::next, this, &MediaPlayer::Next);

	connect(m_pPlayer, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
		emit positionChanged(static_cast<int>(position / 1000));
			});
	connect(m_pPlayer, &QMediaPlayer::durationChanged, this, [=](qint64 duration) {
		emit durationChanged(static_cast<int>(duration / 1000));
		});
	connect(this, &MediaPlayer::play, this, [=]() {
		Play(m_currentIndex);
		});
	connect(this, &MediaPlayer::setPosition, this, [=](int position) {
		m_pPlayer->setPosition(position * 1000);
		});
	connect(this, &MediaPlayer::getSizeData, this, [=](const unsigned int size) {
		m_pBuffer->buffer().clear();
		m_pBuffer->buffer().resize(size);
		m_oldSizeBuffer = 0;
		});
}

void MediaPlayer::ReadyRead(QByteArray package)
{
	m_pBuffer->seek(m_oldSizeBuffer);
	m_pBuffer->write(package);
	m_oldSizeBuffer += package.size();

	if (m_playState == EPlayerState::Pause)
	{
		m_pPlayer->setMedia(QMediaContent(), m_pBuffer);
		m_pPlayer->setVolume(10);
		m_pPlayer->play();
		m_playState = EPlayerState::Play;
		emit started(m_currentIndex);
	}
}

void MediaPlayer::GottenData(QByteArray data)
{
}

void MediaPlayer::Next()
{
	emit paused(m_currentIndex);
	m_playState = EPlayerState::Pause;
}

void MediaPlayer::Previous()
{
	emit paused(m_currentIndex);
	m_playState = EPlayerState::Pause;
}

void MediaPlayer::SetPlaylist(IPlaylist* const playlist)
{
	m_pPlaylist = playlist;
}

int MediaPlayer::CurrentIndex()
{
	return m_currentIndex;
}

void MediaPlayer::Play(int id)
{
	if (m_currentIndex == id)
	{
		if (m_playState == EPlayerState::Play)
		{
			m_pPlayer->pause();
			m_playState = EPlayerState::Pause;
			emit paused(m_currentIndex);
		}
		else
		{
			m_pPlayer->play();
			m_playState = EPlayerState::Play;
			emit started(m_currentIndex);
		}
	}
	else
	{
		if (m_playState == EPlayerState::Play)
		{
			m_playState = EPlayerState::Pause;
			emit paused(m_currentIndex);
		}

		m_currentIndex = id;

		Query q;
		q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Media));
		q.InsertIntoBody("id-media", m_currentIndex);
		emit sendToSocket(this, q.toByteArray());
	}
}

void MediaPlayer::MediaStatusChanged(QMediaPlayer::MediaStatus status)
{
	if (status == QMediaPlayer::MediaStatus::EndOfMedia)
	{
		m_playState = EPlayerState::Pause;
		emit paused(m_currentIndex);

		Query q;

		switch (m_playMode)
		{
		case PlayModeEnum::EPlayMode::Sequential:
		{
			m_currentIndex = m_pPlaylist->NextIndex(m_currentIndex);

			q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Media));
			q.InsertIntoBody("id-media", m_currentIndex);

			emit sendToSocket(this, q.toByteArray());
			break;
		}
		case PlayModeEnum::EPlayMode::Loop:
		{
			if (m_pPlaylist->IndexOf(m_currentIndex) < m_pPlaylist->Size())
			{
				m_currentIndex = m_pPlaylist->NextIndex(m_currentIndex);
			}
			else
			{
				m_currentIndex = m_pPlaylist->FirstIndex();
			}

			q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Media));
			q.InsertIntoBody("id-media", m_currentIndex);

			emit sendToSocket(this, q.toByteArray());
			break;
		}
		case PlayModeEnum::EPlayMode::CurrentItemInLoop:
		{
			m_pPlayer->play();
			break;
		}
		}
	}
}

void MediaPlayer::ChangeCurrentTime(qint64 position)
{
	int time = position / 1000;
	QString currentTime;

	int minutes = 0;
	while (time > 59)
	{
		++minutes;
		time -= 60;
	}
	int seconds = time;

	currentTime = QString::number(minutes) + ':';

	QString sec = QString::number(seconds);

	if (sec.size() == 1)
	{
		sec.insert(0, '0');
	}

	currentTime += sec;

	emit currentTimeChanged(currentTime);
}

/*void MediaPlayer::GetID(int newID)
{
	Query q;
	q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Media));

	m_pBuffer->buffer().clear();

	switch (m_playMode)
	{
	case EPlayMode::Sequential:
	{
		if (newID != -1)
		{
			m_currentID = newID;

			m_pHandleSection->SetCurrentItem(m_currentID);

			q.InsertIntoBody("id-media", m_currentID);
			emit onSendToSocket(this, q.toByteArray());
		}
		else
		{
			m_currentID = 0;
			emit paused(m_currentID);
		}
		break;
	}
	case EPlayMode::Loop:
	{
		if (newID != -1)
		{
			m_currentID = newID;

			m_pHandleSection->SetCurrentItem(m_currentID);

			q.InsertIntoBody("id-media", m_currentID);
			emit onSendToSocket(this, q.toByteArray());
		}
		else
		{
			emit getFirstIndex(m_currentID);
		}
		break;
	}
	}
}*/