#include "Player/Player.h"

Player::Player(const EParams* const params, QQuickWindow* window)
	: IWindow(params, window),
	m_pListSongsScreen(Q_NULLPTR)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	MSG(ETypeMessage::Log, "Initialization");

	MSG(ETypeMessage::Log, "Sections Loading");

	m_pListSongsScreen = new ListSongsScreen(m_pParams);
	m_pListSongsScreen->Initialize();

	ListSongsSection* section = qobject_cast<ListSongsSection*>(m_pListSongsScreen->Section(ListSongsScreen::ETypeSection::ListSongsSection));

	connect(section, &ListSongsSection::onChangeTitleSong, this, &Player::changeTitleSong);
	connect(section, &ListSongsSection::onChangeArtistSong, this, &Player::changeArtistSong);
	connect(section, &ListSongsSection::onChangeCoverArtSong, this, &Player::changeCoverArtSong);
	connect(section, &ListSongsSection::onChangeTime, this, &Player::changeTime);

	m_pMediaPlayer = new MediaPlayer(m_pParams);
	m_pMediaPlayer->Initialize();

	connect(m_pMediaPlayer, &MediaPlayer::onPositionChanged, this, &Player::positionChanged);
	connect(m_pMediaPlayer, &MediaPlayer::onDurationChanged, this, &Player::durationChanged);
	connect(m_pMediaPlayer, &MediaPlayer::onCurrentTimeChanged, this, &Player::currentTimeChanged);
	connect(this, &Player::sliderPositionChanged, m_pMediaPlayer, &MediaPlayer::SetPosition);
	connect(this, &Player::playModeChanged, m_pMediaPlayer, &MediaPlayer::SetPlayMode);

	m_typeScreen = ETypeScreen::ListSongs;
}

void Player::next()
{
	m_pMediaPlayer->Next();
}

void Player::play()
{
	int id = m_pMediaPlayer->CurrentID();
	m_pMediaPlayer->PlayTheSong(id);
}

void Player::previous()
{
	m_pMediaPlayer->Previous();
}

void Player::clickedItem(int type, int id)
{
	switch (m_typeScreen)
	{
	case ETypeScreen::ListSongs:
	{
		ListSongsScreen::ETypeSection typeSection = static_cast<ListSongsScreen::ETypeSection>(type);

		switch (typeSection)
		{
		case ListSongsScreen::ETypeSection::ListSongsSection:
		{
			ListSongsSection* section = qobject_cast<ListSongsSection*>(m_pListSongsScreen->Section(typeSection));

			m_pMediaPlayer->SetConnnectWithSection(section);
			m_pMediaPlayer->PlayTheSong(id);
			break;
		}
		}
		break;
	}
	}
}
