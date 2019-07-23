#ifndef _CORE_H_
#define _CORE_H_

#include "StdAfx.h"

#include <QObject>
#include <QThread>

// Parameters
#include "EParams.h"

// Network
#include "Network/Socket/Socket.h"

// Custom Window
#include "FWindow/FWindow.h"

// Models
#include "ListViewModels/Horizontal/Type 1/Model/Hor1Model.h"
#include "ListViewModels/Vertical/Type 1/Model/Ver1Model.h"

// Window Manager
#include "Windows Manager/WindowManager.h"

// Custom Items
#include "Items/UnblockedMouseArea/UnblockedMouseArea.h"

class Core : public QObject
{
	Q_OBJECT

public:
	Core();
	~Core();

public:
	void Run();

signals:
	void Push(QByteArray);

private:
	QThread* m_pThread;
	WinManager* m_pWinManager;
	EParams* m_pParams;
};

#endif