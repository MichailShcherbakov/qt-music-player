#ifndef _C_MAIN_H_
#define _C_MAIN_H_

#include "StdAfx.h"

#include <QObject>
#include <QThread>
#include <QQmlContext>
#include <QQuickView>
#include <QQmlApplicationEngine>

// Network
#include "CSocket.h"
/*
// Window Loign
#include "CLogin.h"

// Window Player
#include "CPlayer.h"
*/
// Dialog Player
#include "CFileDialog.h"

// List
#include "CModel.h"
#include "CList.h"

class CMain : public QObject
{
	Q_OBJECT

public:
	CMain();
	~CMain();

public:
	void Initialize();

private:
	void CreateNewWindow(EWindowType type);

public slots:
	void windowIsClosed();
	void openDialog(EDialogType type);

private:
	/*CQuery* m_query;*/
	QThread* m_thread;
	CSocket* m_socket;
	/*IWindow* m_window;*/
	IDialog* m_dialog;
	QQmlApplicationEngine* m_engine;
	QQmlContext* m_context;
	EWindowType openedWindow;
};

#endif // !_CMAIN_H_




