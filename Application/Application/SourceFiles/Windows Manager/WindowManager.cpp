#include "WindowManager.h"

WinManager::WinManager(const EParams* const params) :
	m_pParams(params),
	m_typeWindow(ETypeWindow::Login),
	m_pHandleWindow(Q_NULLPTR)
{
}

WinManager::~WinManager()
{
	SAFE_DELETE(m_pHandleWindow);
}

void WinManager::Initialize()
{
	MSG(ETypeMessage::Log, "Default window initialisation");
	InitializeWindow(ETypeWindow::Login);

	MSG(ETypeMessage::Log, "Opening a window");
	//OpenWindow();
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

		m_pHandleWindow = new Login(m_pParams);

		m_pHandleWindow->Initialize();

		/*m_pParams->m_pRootContext->setContextProperty("wlRoot", m_pHandleWindow);
		m_pParams->m_pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Login/main.qml")));
		m_pHandleWindow->SetWindowHandle(qobject_cast<QQuickWindow*>(m_pParams->m_pEngine->rootObjects().first()));*/
		break;
	}
	case ETypeWindow::Player:
	{
		MSG(ETypeMessage::Log, "Creating palyer window");

		m_pHandleWindow = new Player(m_pParams);

		m_pHandleWindow->Initialize();

		m_pParams->m_pRootContext->setContextProperty("wpRoot", m_pHandleWindow);
		m_pParams->m_pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Player/main.qml")));
		m_pHandleWindow->SetWindowHandle(qobject_cast<QQuickWindow*>(m_pParams->m_pEngine->rootObjects().first()));
		break;
	}
	}

	if (m_pHandleWindow)
	{
		connect(m_pHandleWindow, &IWindow::onClosing, this, &WinManager::WindowIsClosed);
	}
}

void WinManager::OpenWindow()
{
	m_pHandleWindow->Window()->show();
}

void WinManager::WindowIsClosed()
{
	bool openWindow = false;

	switch (m_typeWindow)
	{
	case ETypeWindow::Login:
	{
		m_typeWindow = ETypeWindow::Player;
		openWindow = true;
		break;
	}
	case ETypeWindow::Player:
	{
		m_typeWindow = ETypeWindow::Unknown;
		break;
	}
	default:
		SAFE_DELETE(m_pHandleWindow);
	}

	if (openWindow)
	{
		MSG(ETypeMessage::Log, "Default window initialisation");
		InitializeWindow(m_typeWindow);

		MSG(ETypeMessage::Log, "Opening a window");
		OpenWindow();
	}
}