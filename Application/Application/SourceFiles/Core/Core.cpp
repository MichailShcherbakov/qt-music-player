#include "Core.h"

Core::Core() :
	m_pParams(Q_NULLPTR),
	m_pThread(Q_NULLPTR),
	m_pWinManager(Q_NULLPTR)
{
}

Core::~Core()
{
	m_pThread->terminate();
	SAFE_DELETE(m_pWinManager);
	SAFE_DELETE(m_pThread);
	SAFE_DELETE(m_pParams->m_pRootImageProvider);
	SAFE_DELETE(m_pParams->m_pSocket);
	SAFE_DELETE(m_pParams->m_pEngine);
}

void Core::Run()
{
	m_pParams = new EParams;

	MSG(ETypeMessage::Log, "Registration custom types");
	
	// Windows
	qmlRegisterType<FWindow>("windows.fwindow", 1, 0, "FWindow");

	// Items
	qmlRegisterType<UnblockedMouseArea>("tools.mousearea", 1, 0, "UnblockedMouseArea");

	// Models
	qmlRegisterType<HorizontalModel1::Model>("models.horizontalModel1", 1, 0, "HorizontalModel1");
	qmlRegisterUncreatableType<HorizontalModel1::List>("models.horizontalModel1", 1, 0, "ListHorModel1", QStringLiteral("Upps.. :)"));

	qmlRegisterType<VerticalModel1::Model>("models.verticalModel1", 1, 0, "VerticalModel1");
	qmlRegisterUncreatableType<VerticalModel1::List>("models.verticalModel1", 1, 0, "ListVerModel1", QStringLiteral("Upps.. :)"));

	MSG(ETypeMessage::Log, "Qml engine initialization");

	m_pParams->m_pEngine = new QQmlApplicationEngine;
	m_pParams->m_pRootContext = m_pParams->m_pEngine->rootContext();

	MSG(ETypeMessage::Log, "Root image provider initialization");

	m_pParams->m_pRootImageProvider = new ImageProvider;
	m_pParams->m_pEngine->addImageProvider(QLatin1String("rootImageDirectory"), m_pParams->m_pRootImageProvider);

	MSG(ETypeMessage::Log, "Loading default cover art");

	QFile img("Resources/Icons/cover.jpg");
	img.open(QIODevice::ReadOnly);
	QByteArray arrayImg = img.readAll();
	img.close();

	QImage p;
	p.loadFromData(arrayImg, "JPG");

	m_pParams->m_pRootImageProvider->AppendImage(p, "default");

	MSG(ETypeMessage::Log, "Socket initialization and connect to the server");

	// Network
	m_pParams->m_pSocket = new Socket;
	m_pParams->m_pSocket->Initialize();

	// Thread for socket
	m_pThread = new QThread;
	m_pParams->m_pSocket->moveToThread(m_pThread);
	m_pThread->start();

	connect(m_pThread, &QThread::finished, m_pParams->m_pSocket, &QObject::deleteLater);

	MSG(ETypeMessage::Log, "Window manager parameters initialization");

	MSG(ETypeMessage::Log, "Initialization window manager");

	m_pWinManager = new WinManager(m_pParams);
	m_pWinManager->Initialize();
}
