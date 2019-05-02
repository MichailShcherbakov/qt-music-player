#include "CMain.h"



CMain::CMain() :
	openedWindow(EWindowType::Unknown),
	m_engine(nullptr),
	m_context(nullptr),
	/*m_query(nullptr),*/
	m_socket(nullptr),
	m_thread(nullptr),
	/*m_window(nullptr),*/
	m_dialog(nullptr)
{
}

CMain::~CMain()
{
	SAFE_DELETE(m_dialog);
	/*SAFE_DELETE(m_window);*/
	m_thread->terminate();
	SAFE_DELETE(m_thread);
	SAFE_DELETE(m_socket);
	/*SAFE_DELETE(m_query);*/
	SAFE_DELETE(m_engine);
}

void CMain::Initialize()
{
	qmlRegisterType<CModel>("models", 1, 0, "CModel");
	qmlRegisterUncreatableType<CList>("models", 1, 0, "CList", QStringLiteral("ToDoList should not be created in QML"));

	m_engine = new QQmlApplicationEngine;
	m_context = m_engine->rootContext();

	m_engine->rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

	// Query
	/*m_query = new CQuery;*/
	
	// Network
	m_socket = new CSocket;
	m_socket->Initialize();

	// Thread for socket
	m_thread = new QThread;
	m_socket->moveToThread(m_thread);
	m_thread->start();

	openDialog(EDialogType::File);
}

void CMain::windowIsClosed()
{
	/*switch (openedWindow)
	{
	case EWindowType::WLogin:
	{
		m_window->Window()->close();

		CreateNewWindow(EWindowType::WPlayer);
		m_window->Window()->show();
		break;
	}
	case EWindowType::WPlayer:
	{
		openedWindow = EWindowType::Unknown;
		break;
	}
	}*/
}

void CMain::CreateNewWindow(EWindowType type)
{
	/*SAFE_DELETE(m_window);
	
	openedWindow = type;

	switch (type)
	{
	case EWindowType::WLogin:
	{
		m_engine->load(QUrl(QStringLiteral("qrc:/Qml/Windows/wlogin.qml")));
		m_window = new CLogin((QQuickWindow*)m_engine->rootObjects().first(), m_query);
		m_context->setContextProperty("window_login", m_window);
		break;
	}
	case EWindowType::WPlayer:
	{	
		CList* list = new CList;
		m_engine->rootContext()->setContextProperty(QStringLiteral("cList"), list);

		CImageProvider* imageProvider = new CImageProvider;
		m_engine->addImageProvider(QLatin1String("imageProvider"), imageProvider);

		m_engine->load(QUrl(QStringLiteral("qrc:/Qml/Windows/wplayer.qml")));
		m_window = new CPlayer((QQuickWindow*)m_engine->rootObjects().first(), m_query, list, imageProvider);
		m_context->setContextProperty("window_player", m_window);

		connect(m_window, &IWindow::openFileDialog, this, &CMain::openDialog);
		break;
	}
	}

	if (m_window)
	{
		connect(m_window, &IWindow::sendToSocket, m_socket, &CSocket::sendToServer);
		connect(m_socket, &CSocket::getFromServer, m_window, &IWindow::getFromSocket);
		connect(m_window, &IWindow::closing, this, &CMain::windowIsClosed);

		m_window->Initialize();
	}*/
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
		m_dialog = new CFileDialog((QQuickWindow*)m_engine->rootObjects().at(0), list, imageProvider);
		m_context->setContextProperty("dialog_file", m_dialog);
		m_dialog->Window()->setModality(Qt::ApplicationModal);
		break;
	}
	}
}
