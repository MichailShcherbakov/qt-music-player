#include "StdAfx.h"
#include "WindowManager.h"

WinManager::WinManager() :
	m_typeWindow(ETypeWindow::WinLogin),
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
	InitializeWindow(ETypeWindow::WinLogin);

	MSG(ETypeMessage::Log, "Opening a window");
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
	case ETypeWindow::WinLogin:
	{
		MSG(ETypeMessage::Log, "Creating login window");

		m_pHandleWindow = new Login();
		break;
	}
	case ETypeWindow::WinPlayer:
	{
		MSG(ETypeMessage::Log, "Creating palyer window");

		m_pHandleWindow = new Player();
		break;
	}
	}

	if (m_pHandleWindow)
	{
		connect(m_pHandleWindow, &IWindow::closing, this, &WinManager::WindowIsClosed);

		m_pHandleWindow->Initialize();
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
	case ETypeWindow::WinLogin:
	{
		m_typeWindow = ETypeWindow::WinPlayer;
		openWindow = true;
		break;
	}
	case ETypeWindow::WinPlayer:
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