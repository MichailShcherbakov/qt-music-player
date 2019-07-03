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
	void createWindow(ETypeWindow type);

public slots:
	void WindowIsClosed();

// Temp
signals:
	void onSendToSocket(const QByteArray& data);

private:
	QThread* m_thread;
	Socket* m_socket;
	IWindow* m_window;
	QQmlApplicationEngine* m_engine;
	QQmlContext* m_rootContext;
	ETypeWindow m_openWindow;
	ImageProvider* m_rootImageProvider;
};

#endif