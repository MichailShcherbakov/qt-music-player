#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include "StdAfx.h"
#include "EParams.h"

#include "Windows/Login/Login.h"
#include "Windows/Player/Player.h"

class WinManager : public QObject
{
	Q_OBJECT

public:
	WinManager(const EParams* const params);
	~WinManager();

public:
	void Initialize();

private:
	void InitializeWindow(ETypeWindow type);
	void OpenWindow();

public slots:
	void WindowIsClosed();

private:
	IWindow* m_pHandleWindow;
	ETypeWindow m_typeWindow;
	const EParams* const m_pParams;
};

#endif