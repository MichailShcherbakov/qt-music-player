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

	m_typeScreen = ETypeScreen::ListSongs;
}
