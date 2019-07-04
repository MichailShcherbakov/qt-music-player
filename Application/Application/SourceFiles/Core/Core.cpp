#include "Core.h"

Core::Core(QObject* parent)
	: QObject(parent),
	m_pThread(Q_NULLPTR),
	m_pWindow(Q_NULLPTR),
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

	m_pEngine = new QQmlApplicationEngine;
	m_pRootContext = m_pEngine->rootContext();

	m_pRootImageProvider = new ImageProvider;
	m_pEngine->addImageProvider(QLatin1String("rootImageDirectory"), m_pRootImageProvider);

	// Network
	m_pSocket = new Socket;
	m_pSocket->Initialize();

	// Thread for socket
	m_pThread = new QThread;
	m_pSocket->moveToThread(m_pThread);
	m_pThread->start();

	// Temp
	connect(this, &Core::onSendToSocket, m_pSocket, &Socket::SendToServer);

	Query query;
	query.InsertIntoHeader("username", "1");
	query.InsertIntoHeader("password", "1");
	query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Check_This_User));
	emit onSendToSocket(query.toByteArray());

	for (int i = 1; i < 14; ++i)
	{
		QFile f("C:/Users/User/Desktop/Panic! At The Disco - 2005 - A Fever You Can't Sweat Out/" + QString::number(i) + ".mp3");
		f.open(QIODevice::ReadOnly);
		QByteArray song = f.readAll();
		f.close();

		Query q;
		q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Add_New_Media));
		QString t = QString::fromLatin1(song, song.size());
		q.InsertIntoBody("media", t);
		q.InsertIntoBody("create-new-artist", true);
		q.InsertIntoBody("create-new-album", true);
		emit onSendToSocket(q.toByteArray());
	}

	//CreateNewWindow(ETypeWindow::Player);
}

void Core::WindowIsClosed()
{
	switch (m_openWindow)
	{
	case ETypeWindow::Login:
	{
		m_pWindow->Window()->close();
		m_openWindow = ETypeWindow::Player;
		CreateNewWindow(m_openWindow);
		m_pWindow->Window()->show();
		break;
	}
	case ETypeWindow::Player:
	{
		m_pWindow->Window()->close();
		m_openWindow = ETypeWindow::Unknown;
		break;
	}
	}
}

void Core::CreateNewWindow(ETypeWindow type)
{
	if (m_pWindow)
	{
		SAFE_DELETE(m_pWindow);
	}

	switch (type)
	{
	case ETypeWindow::Login:
	{
		m_pWindow = new Login();
		m_pWindow->Initialize();

		SetConnections();

		m_pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Login/main.qml")));
		m_pWindow->SetWindowHandle(static_cast<QQuickWindow*>(m_pEngine->rootObjects().first()));

		m_pRootContext->setContextProperty("wlRoot", m_pWindow);
		break;
	}
	case ETypeWindow::Player:
	{
		m_pWindow = new Player(m_pEngine->rootContext(), m_pRootImageProvider);
		m_pWindow->Initialize();

		SetConnections();

		m_pEngine->load(QUrl(QStringLiteral("qrc:/SourceFiles/Qml Files/Windows/Player/main.qml")));
		m_pWindow->SetWindowHandle(static_cast<QQuickWindow*>(m_pEngine->rootObjects().first()));
		
		m_pRootContext->setContextProperty("wpRoot", m_pWindow);
		break;
	}
	}

	if (m_pWindow)
	{
		m_pWindow->Window()->show();
	}
}

void Core::SetConnections()
{
	connect(m_pWindow, &IWindow::onSendToSocket, m_pSocket, &Socket::SendToServer);
	connect(m_pSocket, &Socket::onGetFromServer, m_pWindow, &IWindow::GetFromSocket);
	connect(m_pWindow, &IWindow::onClosing, this, &Core::WindowIsClosed);
}
