#ifndef _C_MAIN_H_
#define _C_MAIN_H_

#include "StdAfx.h"

#include "CSocket.h"
#include "CLogin.h"
#include "CPlayer.h"
#include "CQuery.h"
#include "CFileDialog.h"
#include "CModel.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

class CMain : public QObject
{
	Q_OBJECT

public:
	CMain();
	~CMain();

public:
	void Initialize();

public slots:
	void windowIsClosed(EWindowType type);
	
private:
	void openNewWindow(EWindowType type);
	void openDialog(EDialogType type);

private:
	QQmlApplicationEngine* m_engine;
	QQmlContext* m_context;
	CSocket* m_socket;
	QThread* m_thread;
	IWindow* m_handleWindow;
	IDialog* m_handleDialog;
	CQuery* m_query;
};

#endif