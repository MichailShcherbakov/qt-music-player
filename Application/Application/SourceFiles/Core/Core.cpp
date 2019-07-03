#include "Core.h"

Core::Core(QObject* parent)
	: QObject(parent),
	m_thread(Q_NULLPTR),
	m_window(Q_NULLPTR),
	m_openWindow(ETypeWindow::Player)
{
}

Core::~Core()
{
}

void Core::Run()
{
	qmlRegisterType<FWindow>("my.window", 1, 0, "FWindow");

	qmlRegisterType<HorizontalModel1::Model>("horizontalModel1", 1, 0, "HorizontalModel1");
	qmlRegisterUncreatableType<HorizontalModel1::List>("horizontalModel1", 1, 0, "ListHorModel1", QStringLiteral("Upps.. :)"));

	m_engine = new QQmlApplicationEngine;
	m_rootContext = m_engine->rootContext();

	m_rootImageProvider = new ImageProvider;
	m_engine->addImageProvider(QLatin1String("rootImageDirectory"), m_rootImageProvider);

	// Network
	m_socket = new Socket;
	m_socket->Initialize();

	// Thread for socket
	m_thread = new QThread;
	m_socket->moveToThread(m_thread);
	m_thread->start();


	// Temp
	connect(this, &Core::onSendToSocket, m_socket, &Socket::SendToServer);

	Query query;
	query.InsertIntoHeader("username", "123");
	query.InsertIntoHeader("password", "123");
	query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Check_This_User));
	emit onSendToSocket(query.toByteArray());

	m_engine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Player/main.qml")));
}

void Core::WindowIsClosed()
{
	switch (m_openWindow)
	{
	case ETypeWindow::Login:
	{
		m_window->Window()->close();
		m_openWindow = ETypeWindow::Player;
		createWindow(m_openWindow);
		m_window->Window()->show();
		break;
	}
	case ETypeWindow::Player:
	{
		m_window->Window()->close();
		m_openWindow = ETypeWindow::Unknown;
		break;
	}
	}
}

void Core::createWindow(ETypeWindow type)
{
	if (m_window)
	{
		SAFE_DELETE(m_window);
	}

	switch (type)
	{
	case ETypeWindow::Login:
	{
		m_engine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Login/main.qml")));
		m_window = new Login((QQuickWindow*)m_engine->rootObjects().first());
		m_rootContext->setContextProperty("wlRoot", m_window);
		m_window->Initialize();
		break;
	}
	case ETypeWindow::Player:
	{
		m_window = new Player(m_engine->rootContext(), m_rootImageProvider);
		connect(m_window, &IWindow::onSendToSocket, m_socket, &Socket::SendToServer);
		connect(m_socket, &Socket::onGetFromServer, m_window, &IWindow::GetFromSocket);
		connect(m_window, &IWindow::onClosing, this, &Core::WindowIsClosed);
		m_window->Initialize();
		m_engine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Player/main.qml")));
		m_window->SetWindowHandle((QQuickWindow*)m_engine->rootObjects().first());
		m_rootContext->setContextProperty("wpRoot", m_window);
		break;
	}
	}

	if (m_window)
	{
		connect(m_window, &IWindow::onSendToSocket, m_socket, &Socket::SendToServer);
		connect(m_socket, &Socket::onGetFromServer, m_window, &IWindow::GetFromSocket);
		connect(m_window, &IWindow::onClosing, this, &Core::WindowIsClosed);
		m_window->Window()->show();
	}
}
