#include "Core.h"

Core::Core() :
	m_pEngine(Q_NULLPTR),
	m_pRootImageProvider(Q_NULLPTR),
	m_pSocket(Q_NULLPTR),
	m_pThread(Q_NULLPTR),
	m_pWinManager(Q_NULLPTR)
{
}

Core::~Core()
{
	m_pThread->terminate();
	SAFE_DELETE(m_pWinManager);
	SAFE_DELETE(m_pThread);
	SAFE_DELETE(m_pSocket);
	SAFE_DELETE(m_pRootImageProvider);
	SAFE_DELETE(m_pEngine);
}

void Core::Run()
{
	qmlRegisterType<FWindow>("my.window", 1, 0, "FWindow");

	qmlRegisterType<HorizontalModel1::Model>("horizontalModel1", 1, 0, "HorizontalModel1");
	qmlRegisterUncreatableType<HorizontalModel1::List>("horizontalModel1", 1, 0, "ListHorModel1", QStringLiteral("Upps.. :)"));

	m_pEngine = new QQmlApplicationEngine;

	m_pRootImageProvider = new ImageProvider;
	m_pEngine->addImageProvider(QLatin1String("rootImageDirectory"), m_pRootImageProvider);

	// Network
	m_pSocket = new Socket;
	m_pSocket->Initialize();

	// Thread for socket
	m_pThread = new QThread;
	m_pSocket->moveToThread(m_pThread);
	m_pThread->start();

	EParams params(m_pEngine, m_pEngine->rootContext(), m_pSocket, m_pRootImageProvider);

	m_pWinManager = new WinManager(params);
	m_pWinManager->Initialize();
}
