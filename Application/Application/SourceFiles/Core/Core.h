#ifndef _CORE_H_
#define _CORE_H_

#include "Tools/StdAfx.h"

#include <QObject>
#include <QThread>

// Network
#include "Network/Socket.h"

// Custom Window
#include "FWindow/FWindow.h"

// Models
#include "ListViewModels/Horizontal/Type 1/Model/Model.h"

// Window Manager
#include "Windows Manager/WindowManager.h"

class Core : public QObject
{
	Q_OBJECT

public:
	Core();
	~Core();

public:
	void Run();

private:
	QThread* m_pThread;
	Socket* m_pSocket;
	QQmlApplicationEngine* m_pEngine;
	WinManager* m_pWinManager;
	ImageProvider* m_pRootImageProvider;
};

#endif