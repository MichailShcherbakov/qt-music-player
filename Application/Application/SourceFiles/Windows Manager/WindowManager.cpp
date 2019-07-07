#include "WindowManager.h"

WinManager::WinManager(EParams params) :
	m_params(params),
	m_pHandleWindow(Q_NULLPTR)
{
}

WinManager::~WinManager()
{
}

void WinManager::Initialize()
{
	InitializeWindow(ETypeWindow::Login);
	OpenWindow();
}

void WinManager::InitializeWindow(ETypeWindow type)
{
	if (m_pHandleWindow)
	{
		SAFE_DELETE(m_pHandleWindow);
	}

	switch (type)
	{
	case ETypeWindow::Login:
	{
		m_pHandleWindow = new Login();
		m_pHandleWindow->Initialize();

		SetConnections();

		m_params.m_pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Login/main.qml")));
		m_pHandleWindow->SetWindowHandle(static_cast<QQuickWindow*>(m_params.m_pEngine->rootObjects().first()));

		m_params.m_pRootContext->setContextProperty("wlRoot", m_pHandleWindow);
		break;
	}
	case ETypeWindow::Player:
	{
		m_pHandleWindow = new Player(m_params.m_pRootContext, m_params.m_pRootImageProvider);
		m_pHandleWindow->Initialize();

		SetConnections();

		m_params.m_pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Player/main.qml")));
		m_pHandleWindow->SetWindowHandle(static_cast<QQuickWindow*>(m_params.m_pEngine->rootObjects().first()));

		m_params.m_pRootContext->setContextProperty("wpRoot", m_pHandleWindow);
		break;
	}
	}
}

void WinManager::OpenWindow()
{
	m_pHandleWindow->Window()->show();
}

void WinManager::SetConnections()
{
	connect(m_pHandleWindow, &IWindow::onSendToSocket, m_params.m_pSocket, &Socket::SendToServer);
	connect(m_params.m_pSocket, &Socket::onGetFromServer, m_pHandleWindow, &IWindow::GetFromSocket);
	connect(m_pHandleWindow, &IWindow::onClosing, this, &WinManager::WindowIsClosed);
}