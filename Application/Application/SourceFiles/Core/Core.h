#ifndef _CORE_H_
#define _CORE_H_

#include "Tools/StdAfx.h"

#include <QObject>
#include <QThread>
#include <QQmlContext>
#include <QQuickWindow>
#include <QQmlApplicationEngine>

// Network
#include "Network/Socket.h"

// Custom Window
#include "FWindow/FWindow.h"

// Windows
#include "Login/Login.h"
#include "Player/Player.h"

// Models
#include "ListViewModels/Horizontal/Type 1/Model/Model.h"

class Core : public QObject
{
	Q_OBJECT

public:
	Core(QObject* parent = Q_NULLPTR);
	~Core();

public:
	void Run();
	
private:
	void CreateNewWindow(ETypeWindow type);
	void SetConnections();

public slots:
	void WindowIsClosed();

// Temp
signals:
	void onSendToSocket(const QByteArray& data);

private:
	QThread* m_pThread;
	Socket* m_pSocket;
	IWindow* m_pWindow;
	QQmlApplicationEngine* m_pEngine;
	QQmlContext* m_pRootContext;
	ETypeWindow m_openWindow;
	ImageProvider* m_pRootImageProvider;
};

#endif