#include "MediaPlayer.h"

MediaPlayer::MediaPlayer(Socket* const socket, QQmlContext* const context, QSettings* const settings) :
	ISectionObject(socket),
	m_pSocket(socket),
	m_pRootContext(context),
	m_pSettings(settings),
	m_playMode(static_cast<EPlayMode>(settings->value("MediaPlayer/playMode").toInt())),
	m_playState(EPlayerState::Stop),
	m_pPlayer(Q_NULLPTR),
	m_pBuffer(Q_NULLPTR),
	m_pHandleSection(Q_NULLPTR)
{
	m_pRootContext->setContextProperty(QStringLiteral("mediaPlayer"), this);
}

MediaPlayer::~MediaPlayer()
{
}

void MediaPlayer::Initialize()
{
	m_pPlayer = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
	m_pBuffer = new QBuffer;
	m_pBuffer->open(QIODevice::ReadWrite);

	m_currentID = m_pSettings->value("MediaPlayer/id").toInt();

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
		m_pHandleSection->SetCurrentItem(m_currentID);
		PlayTheSong(m_currentID);
		});
	connect(this, &MediaPlayer::setPosition, this, [=](int position) {
		m_pPlayer->setPosition(position * 1000);
		});
	connect(this, &MediaPlayer::onGetSizeData, this, [=](const unsigned int size) {
		m_pBuffer->buffer().clear();
		m_pBuffer->buffer().resize(size);
		oldSize = 0;
		});
}

void MediaPlayer::ReadyRead(QByteArray package)
{
	m_pBuffer->seek(oldSize);
	m_pBuffer->write(package);
	oldSize += package.size();

	if (m_playState == EPlayerState::Stop)
	{
		m_pPlayer->setMedia(QMediaContent(), m_pBuffer);
		m_pPlayer->setVolume(5);
		m_pPlayer->play();
		m_playState = EPlayerState::Play;
		emit started(m_currentID);
	}
}

void MediaPlayer::GottenData(QByteArray data)
{
}

void MediaPlayer::Next()
{
	m_pHandleSection->SetCurrentItem(m_currentID);
	emit paused(m_currentID);
	m_playState = EPlayerState::Stop;
	emit getNextIndex(m_currentID);
}

void MediaPlayer::Previous()
{
	m_pHandleSection->SetCurrentItem(m_currentID);
	emit paused(m_currentID);
	m_playState = EPlayerState::Stop;
	emit getPreviousIndex(m_currentID);
}

void MediaPlayer::SetConnnectWithSection(ISectionListView* section)
{
	if (m_pHandleSection)
	{
		disconnect(m_pHandleSection, &ISectionListView::onNextIndex, this, &MediaPlayer::GetID);
		disconnect(m_pHandleSection, &ISectionListView::onFirstIndex, this, &MediaPlayer::GetID);
		disconnect(m_pHandleSection, &ISectionListView::onPreviousIndex, this, &MediaPlayer::GetID);
		disconnect(m_pHandleSection, &ISectionListView::onEndIndex, this, &MediaPlayer::GetID);

		disconnect(this, &MediaPlayer::getNextIndex, m_pHandleSection, &ISectionListView::NextIndex);
		disconnect(this, &MediaPlayer::getFirstIndex, m_pHandleSection, &ISectionListView::FirstIndex);
		disconnect(this, &MediaPlayer::getPreviousIndex, m_pHandleSection, &ISectionListView::PreviousIndex);
		disconnect(this, &MediaPlayer::getEndIndex, m_pHandleSection, &ISectionListView::EndIndex);
	}

	m_pHandleSection = section;

	connect(m_pHandleSection, &ISectionListView::onNextIndex, this, &MediaPlayer::GetID);
	connect(m_pHandleSection, &ISectionListView::onFirstIndex, this, &MediaPlayer::GetID);
	connect(m_pHandleSection, &ISectionListView::onPreviousIndex, this, &MediaPlayer::GetID);
	connect(m_pHandleSection, &ISectionListView::onEndIndex, this, &MediaPlayer::GetID);

	connect(this, &MediaPlayer::getNextIndex, m_pHandleSection, &ISectionListView::NextIndex);
	connect(this, &MediaPlayer::getFirstIndex, m_pHandleSection, &ISectionListView::FirstIndex);
	connect(this, &MediaPlayer::getPreviousIndex, m_pHandleSection, &ISectionListView::PreviousIndex);
	connect(this, &MediaPlayer::getEndIndex, m_pHandleSection, &ISectionListView::EndIndex);
}

void MediaPlayer::PlayTheSong(int id)
{
	if (m_pHandleSection)
	{
		if (m_currentID == id)
		{
			if (m_playState == EPlayerState::Play)
			{
				m_pPlayer->pause();
				m_playState = EPlayerState::Stop;
				emit paused(m_currentID);
			}
			else
			{
				m_pPlayer->play();
				m_playState = EPlayerState::Play;
				emit started(m_currentID);
			}
		}
		else
		{
			if (m_playState == EPlayerState::Play)
			{
				m_playState = EPlayerState::Stop;
				emit paused(m_currentID);
			}

			m_currentID = id;

			Query q;
			q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Media));
			q.InsertIntoBody("id-media", m_currentID);
			emit onSendToSocket(this, q.toByteArray());
		}
	}
}

void MediaPlayer::MediaStatusChanged(QMediaPlayer::MediaStatus status)
{
	if (status == QMediaPlayer::MediaStatus::EndOfMedia)
	{
		m_playState = EPlayerState::Stop;
		emit paused(m_currentID);

		switch (m_playMode)
		{
		case EPlayMode::Sequential:
		{
			emit getNextIndex(m_currentID);
			break;
		}
		case EPlayMode::Loop:
		{
			emit getNextIndex(m_currentID);
			break;
		}
		case EPlayMode::Current_item_in_loop:
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

void MediaPlayer::GetID(int newID)
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
}