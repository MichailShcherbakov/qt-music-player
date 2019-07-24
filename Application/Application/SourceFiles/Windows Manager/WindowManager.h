#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include "Windows/Login/Login.h"
#include "Windows/Player/Player.h"

class WinManager : public QObject
{
	Q_OBJECT

public:
	enum class ETypeWindow : uint
	{
		Unknown = 0,
		WinLogin,
		WinPlayer
	};

public:
	WinManager();
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
};

#endif