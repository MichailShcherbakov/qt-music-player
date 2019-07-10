#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include "Tools/StdAfx.h"

#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "Network/Socket.h"
#include "Windows/Login/Login.h"
#include "Windows/Player/Player.h"

struct EParams
{
	EParams(QQmlApplicationEngine* engine, QQmlContext* context, Socket* socket,  ImageProvider* imageProvider) :
		m_pSocket(socket),
		m_pEngine(engine),
		m_pRootContext(context),
		m_pRootImageProvider(imageProvider)
	{
	}

	QQmlApplicationEngine* m_pEngine;
	QQmlContext* m_pRootContext;
	Socket* m_pSocket;
	ImageProvider* m_pRootImageProvider;
};

class WinManager : public QObject
{
	Q_OBJECT

public:
	WinManager(EParams params);
	~WinManager();

public:
	void Initialize();

private:
	void OpenWindow();
	void SetConnections();
	void InitializeWindow(ETypeWindow type);

signals:
	void Push(QByteArray);
	void onSendToServer(QByteArray);

public slots:
	void WindowIsClosed();
	void Continue(QByteArray);

private:
	IWindow* m_pHandleWindow;
	EParams m_params;

	// Temp 
	bool t = true;
};

#endif