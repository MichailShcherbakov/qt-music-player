#ifndef _CORE_H_
#define _CORE_H_

#include <QObject>
#include <QThread>

// Custom Window
#include "FWindow/FWindow.h"

// Models
//#include "ListViewModels/Horizontal/Type 1/Model/Hor1Model.h"
#include "ListViewModels/Vertical/Type 1/Model/Ver1Model.h"

// Window Manager
#include "Windows Manager/WindowManager.h"

// Custom Items
#include "Items/UnblockedMouseArea/UnblockedMouseArea.h"

#include "MediaPlayer/MediaPlayer.h"

#include "Settings/Pallete/Manager/ThemeManager.h"
#include "Settings/Chapters/Manager/ChaptersManager.h"

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
};

#endif