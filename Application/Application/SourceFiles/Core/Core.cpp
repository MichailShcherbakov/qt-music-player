#include "StdAfx.h"
#include "Core.h"

Core::Core() :
	m_pThread(Q_NULLPTR),
	m_pWinManager(Q_NULLPTR)
{
}

Core::~Core()
{
	m_pThread->terminate();
	SAFE_DELETE(m_pWinManager);
	SAFE_DELETE(m_pThread);
}

void Core::Run()
{
	MSG(ETypeMessage::Log, "Registration custom types");
	
	// Windows
	qmlRegisterType<FWindow>("windows.fwindow", 1, 0, "FWindow");

	// Items
	qmlRegisterType<UnblockedMouseArea>("tools.mousearea", 1, 0, "UnblockedMouseArea");

	// Models
	//qmlRegisterType<HorizontalModel1::Model>("models.horizontalModel1", 1, 0, "HorizontalModel1");
	//qmlRegisterUncreatableType<HorizontalModel1::List>("models.horizontalModel1", 1, 0, "ListHorModel1", QStringLiteral("Upps.. :)"));

	qmlRegisterType<VerticalModel1::Model>("models.verticalModel1", 1, 0, "VerticalModel1");
	qmlRegisterUncreatableType<VerticalModel1::List>("models.verticalModel1", 1, 0, "ListVerModel1", QStringLiteral("Upps.. :)"));

	gParams->pSettings = new QSettings("settings.ini", QSettings::IniFormat);

	MSG(ETypeMessage::Log, "Qml engine initialization");

	gParams->pEngine = new QQmlApplicationEngine();
	gParams->pRootContext = gParams->pEngine->rootContext();

	MSG(ETypeMessage::Log, "Root image provider initialization");

	gParams->pRootImageProvider = new ImageProvider();
	gParams->pEngine->addImageProvider(QLatin1String("rootImageDirectory"), gParams->pRootImageProvider);

	MSG(ETypeMessage::Log, "Socket initialization and connect to the server");

	// Network
	gParams->pSocket = new Socket();
	gParams->pSocket->Initialize();

	// Thread for socket
	m_pThread = new QThread();
	gParams->pSocket->moveToThread(m_pThread);
	m_pThread->start();

	gParams->pMediaPlayer = new MediaPlayer();
	gParams->pMediaPlayer->Initialize();

	connect(m_pThread, &QThread::finished, gParams->pSocket, &QObject::deleteLater);

	MSG(ETypeMessage::Log, "Window manager parameters initialization");

	MSG(ETypeMessage::Log, "Initialization window manager");

	m_pWinManager = new WinManager();
	m_pWinManager->Initialize();
}
