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

	QQmlApplicationEngine* const m_pEngine;
	QQmlContext* const m_pRootContext;
	Socket* const m_pSocket;
	ImageProvider* const m_pRootImageProvider;
};

class WinManager : public QObject
{
public:
	WinManager(EParams params);
	~WinManager();

public:
	void Initialize();

private:
	void OpenWindow();
	void SetConnections();
	void InitializeWindow(ETypeWindow type);

public slots:
	void WindowIsClosed();

private:
	IWindow* m_pHandleWindow;
	EParams m_params;
};

#endif