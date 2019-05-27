#include "CMain.h"



CMain::CMain() :
	m_engine(nullptr),
	m_context(nullptr),
	m_query(nullptr),
	m_socket(nullptr),
	m_thread(nullptr),
	m_handleWindow(nullptr),
	m_handleDialog(nullptr)
{
}

CMain::~CMain()
{
	SAFE_DELETE(m_handleDialog);
	SAFE_DELETE(m_handleWindow);
	m_thread->terminate();
	SAFE_DELETE(m_thread);
	SAFE_DELETE(m_socket);
	SAFE_DELETE(m_query);
	SAFE_DELETE(m_engine);
}

void CMain::Initialize()
{
	qmlRegisterType<CModel>("models", 1, 0, "CModel");
	qmlRegisterUncreatableType<CList>("models", 1, 0, "CList", QStringLiteral("ToDoList should not be created in QML"));

	m_engine = new QQmlApplicationEngine;
	m_context = m_engine->rootContext();

	/*m_engine->rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());*/
	
	m_query = new CQuery;

	// Network
	m_socket = new CSocket;
	m_socket->Initialize();

	// Thread for socket
	m_thread = new QThread;
	m_socket->moveToThread(m_thread);
	m_thread->start();

	this->openNewWindow(EWindowType::WLogin);
}

void CMain::windowIsClosed(EWindowType type)
{
	m_handleWindow->Window()->close();
	this->openNewWindow(type);
	m_handleWindow->Window()->show();
}

void CMain::openNewWindow(EWindowType type)
{
	SAFE_DELETE(m_handleWindow);

	switch (type)
	{
	case EWindowType::WLogin:
	{
		m_engine->load(QUrl(QStringLiteral("qrc:/Qml/Windows/wlogin.qml")));
		m_handleWindow = new CLogin((QQuickWindow*)m_engine->rootObjects().first(), m_query);
		m_context->setContextProperty("window_login", m_handleWindow);
		break;
	}
	case EWindowType::WPlayer:
	{	
		CList* list = new CList;
		m_engine->rootContext()->setContextProperty(QStringLiteral("cList"), list);

		CImageProvider* imageProvider = new CImageProvider;
		m_engine->addImageProvider(QLatin1String("imageProvider"), imageProvider);

		m_engine->load(QUrl(QStringLiteral("qrc:/Qml/Windows/wplayer.qml")));
		m_handleWindow = new CPlayer((QQuickWindow*)m_engine->rootObjects().first(), m_query, list, imageProvider);
		m_context->setContextProperty("window_player", m_handleWindow);

		connect(m_handleWindow, &IWindow::openDialog, this, &CMain::openDialog);
		break;
	}
	}

	if (m_handleWindow)
	{
		connect(m_handleWindow, &IWindow::sendToSocket, m_socket, &CSocket::sendToServer);
		connect(m_socket, &CSocket::getFromServer, m_handleWindow, &IWindow::getFromSocket);
		connect(m_handleWindow, &IWindow::closing, this, &CMain::windowIsClosed);
		m_handleWindow->Initialize();
	}
}

void CMain::openDialog(EDialogType type)
{
	switch (type)
	{
	case EDialogType::File:
	{
		CList* list = new CList;

		CImageProvider* imageProvider = new CImageProvider;
		m_engine->addImageProvider(QLatin1String("imageProviderDF"), imageProvider);

		m_engine->rootContext()->setContextProperty(QStringLiteral("listNewMusic"), list);
		m_engine->load(QUrl(QStringLiteral("qrc:/Qml/Dialogs/dfile.qml")));
		m_handleDialog = new CFileDialog((QQuickWindow*)m_engine->rootObjects().at(0), list, imageProvider);
		m_context->setContextProperty("dialog_file", m_handleDialog);
		m_handleDialog->Window()->setModality(Qt::ApplicationModal);
		break;
	}
	}
	if (m_handleDialog)
	{
		connect(m_handleDialog, &IDialog::closing, m_handleWindow, &IWindow::getFromDialog);
		m_handleDialog->Initialize();
	}
}
