#include "MediaPlayer.h"

MediaPlayer::MediaPlayer(const EParams* const paramas) :
	ISection(paramas),
	m_playMode(EPlayMode::Sequential),
	m_playState(EPlayerState::Stop),
	m_pPlayer(Q_NULLPTR),
	m_pBuffer(Q_NULLPTR),
	m_pHandleSection(Q_NULLPTR)
{
}

MediaPlayer::~MediaPlayer()
{
}

void MediaPlayer::Initialize()
{
	//m_pPlayer = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
	m_pBuffer = new QBuffer;
	m_pBuffer->open(QIODevice::ReadWrite);

	connect(&m_pPlayer, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayer::MediaStatusChanged);
	connect(&m_pPlayer, &QMediaPlayer::positionChanged, this, &MediaPlayer::ChangeCurrentTime);
	connect(&m_pPlayer, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
		emit onPositionChanged(position);
			});
	connect(&m_pPlayer, &QMediaPlayer::durationChanged, this, [=](qint64 duration) {
		emit onDurationChanged(duration);
		});
}

void MediaPlayer::ReadyRead(QByteArray package)
{
	int oldSize = m_pBuffer->size();
	m_pBuffer->seek(oldSize);
	m_pBuffer->write(package); 
	m_pBuffer->seek(oldSize);

	if (m_playState == EPlayerState::Stop)
	{
		m_pPlayer.setMedia(QMediaContent(), m_pBuffer);
		m_pPlayer.setVolume(30);
		m_pPlayer.play();
		m_playState = EPlayerState::Play;
		emit onStarted(m_currentID);

		m_pHandleSection->ClickedItem(m_currentID);
	}
}

void MediaPlayer::GottenData(QByteArray data)
{
}

void MediaPlayer::Next()
{
	m_pHandleSection->ClickedItem(m_currentID);
	emit onPaused(m_currentID);
	m_playState = EPlayerState::Stop;
	emit onGetNextIndex(m_currentID);
}

void MediaPlayer::Previous()
{
	m_pHandleSection->ClickedItem(m_currentID);
	emit onPaused(m_currentID);
	m_playState = EPlayerState::Stop;
	emit onGetNextIndex(m_currentID);
}

void MediaPlayer::SetConnnectWithSection(ISectionListView* section)
{
	if (m_pHandleSection)
	{
		disconnect(m_pHandleSection, &ISectionListView::onNextIndex, this, &MediaPlayer::GetID);
		disconnect(m_pHandleSection, &ISectionListView::onFirstIndex, this, &MediaPlayer::GetID);
		disconnect(m_pHandleSection, &ISectionListView::onPreviousIndex, this, &MediaPlayer::GetID);
		disconnect(m_pHandleSection, &ISectionListView::onEndIndex, this, &MediaPlayer::GetID);

		disconnect(this, &MediaPlayer::onGetNextIndex, m_pHandleSection, &ISectionListView::NextIndex);
		disconnect(this, &MediaPlayer::onGetFirstIndex, m_pHandleSection, &ISectionListView::FirstIndex);
		disconnect(this, &MediaPlayer::onGetPreviousIndex, m_pHandleSection, &ISectionListView::PreviousIndex);
		disconnect(this, &MediaPlayer::onGetEndIndex, m_pHandleSection, &ISectionListView::EndIndex);
	}

	m_pHandleSection = section;

	connect(m_pHandleSection, &ISectionListView::onNextIndex, this, &MediaPlayer::GetID);
	connect(m_pHandleSection, &ISectionListView::onFirstIndex, this, &MediaPlayer::GetID);
	connect(m_pHandleSection, &ISectionListView::onPreviousIndex, this, &MediaPlayer::GetID);
	connect(m_pHandleSection, &ISectionListView::onEndIndex, this, &MediaPlayer::GetID);

	connect(this, &MediaPlayer::onGetNextIndex, m_pHandleSection, &ISectionListView::NextIndex);
	connect(this, &MediaPlayer::onGetFirstIndex, m_pHandleSection, &ISectionListView::FirstIndex);
	connect(this, &MediaPlayer::onGetPreviousIndex, m_pHandleSection, &ISectionListView::PreviousIndex);
	connect(this, &MediaPlayer::onGetEndIndex, m_pHandleSection, &ISectionListView::EndIndex);
}

void MediaPlayer::PlayTheSong(int id)
{
	if (m_pHandleSection)
	{
		if (m_currentID == id)
		{
			if (m_playState == EPlayerState::Play)
			{
				m_pPlayer.pause();
				m_playState = EPlayerState::Stop;
				emit onPaused(m_currentID);
				m_pHandleSection->ClickedItem(m_currentID);
			}
			else
			{
				m_pPlayer.play();
				m_playState = EPlayerState::Play;
				emit onStarted(m_currentID);
				m_pHandleSection->ClickedItem(m_currentID);
			}
		}
		else
		{
			if (m_playState == EPlayerState::Play)
			{
				m_pBuffer->buffer().clear();
				m_playState = EPlayerState::Stop;
				emit onPaused(m_currentID);
				m_pHandleSection->ClickedItem(m_currentID);
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
		emit onPaused(m_currentID);

		switch (m_playMode)
		{
		case EPlayMode::Sequential:
		{
			emit onGetNextIndex(m_currentID);
			break;
		}
		case EPlayMode::Loop:
		{
			emit onGetNextIndex(m_currentID);
			break;
		}
		case EPlayMode::Current_item_in_loop:
		{
			m_pPlayer.play();
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

	emit onCurrentTimeChanged(currentTime);
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

			q.InsertIntoBody("id-media", m_currentID);
			emit onSendToSocket(this, q.toByteArray());
		}
		else
		{
			m_currentID = 0;
			emit onPaused(m_currentID);
		}
		break;
	}
	case EPlayMode::Loop:
	{
		if (newID != -1)
		{
			m_currentID = newID;

			q.InsertIntoBody("id-media", m_currentID);
			emit onSendToSocket(this, q.toByteArray());
		}
		else
		{
			emit onGetFirstIndex(m_currentID);
		}
		break;
	}
	}
}