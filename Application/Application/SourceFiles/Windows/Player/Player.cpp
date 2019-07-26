#include "StdAfx.h"
#include "Player/Player.h"

Player::Player(QQuickWindow* window)
	: IWindow(window),
	m_pListSongsScreen(Q_NULLPTR)
{
	gParams->pRootContext->setContextProperty("wpRoot", this);
}

Player::~Player()
{
}

void Player::Initialize()
{
	MSG(ETypeMessage::Log, "Initialization");

	MSG(ETypeMessage::Log, "Sections Loading");

	m_pListSongsScreen = new ListSongsScreen();
	m_pListSongsScreen->Initialize();

	m_typeScreen = ETypeScreen::ListSongs;

	gParams->pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Player/main.qml")));
	m_pWindow = static_cast<QQuickWindow*>(gParams->pEngine->rootObjects().first());
}
