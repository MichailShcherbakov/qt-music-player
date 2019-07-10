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
	// TEMP
	connect(this, &WinManager::onSendToServer, m_params.m_pSocket, &Socket::SendToServer);
	connect(m_params.m_pSocket, &Socket::onGetFromServer, this, &WinManager::Continue);

	Query query;
	query.InsertIntoHeader("username", "1");
	query.InsertIntoHeader("password", "1");
	query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Check_This_User));
	emit onSendToServer(query.toByteArray());

	/*MSG(ETypeMessage::Log, "Default window initialisation");
	InitializeWindow(ETypeWindow::Player);

	MSG(ETypeMessage::Log, "Opening a window");
	OpenWindow();*/
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
		MSG(ETypeMessage::Log, "Creating login window");

		m_pHandleWindow = new Login();

		SetConnections();

		m_pHandleWindow->Initialize();

		m_params.m_pRootContext->setContextProperty("wlRoot", m_pHandleWindow);
		m_params.m_pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Login/main.qml")));
		m_pHandleWindow->SetWindowHandle(qobject_cast<QQuickWindow*>(m_params.m_pEngine->rootObjects().first()));
		
		break;
	}
	case ETypeWindow::Player:
	{
		MSG(ETypeMessage::Log, "Creating palyer window");

		m_pHandleWindow = new Player(m_params.m_pRootContext, m_params.m_pRootImageProvider);

		SetConnections();

		m_pHandleWindow->Initialize();

		m_params.m_pRootContext->setContextProperty("wpRoot", m_pHandleWindow);
		m_params.m_pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Player/main.qml")));
		m_pHandleWindow->SetWindowHandle(qobject_cast<QQuickWindow*>(m_params.m_pEngine->rootObjects().first()));
		break;
	}
	}
}

void WinManager::Continue(QByteArray d)
{
	if (t)
	{
		disconnect(m_params.m_pSocket, &Socket::onGetFromServer, this, &WinManager::Continue);
		
		MSG(ETypeMessage::Log, "Default window initialisation");
		InitializeWindow(ETypeWindow::Player);

		MSG(ETypeMessage::Log, "Opening a window");
		OpenWindow();
	}
	else
	{
		t = true;
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

void WinManager::WindowIsClosed()
{

}