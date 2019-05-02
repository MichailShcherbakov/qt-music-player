#ifndef _STDAFX_H_
#define _STDAFX_H_

#define SAFE_DELETE(ptr) if (ptr) {delete ptr; ptr = nullptr;} else {ptr = nullptr;}
#define ABSOLUTE_PATH() Tools::absolutePath();

#include <QString>
#include <QCoreApplication>
#include <QGuiApplication>

enum class EDialogType : int
{
	Unknown = -1,
	File,
};

enum class EWindowType : int
{
	Unknown = -1,
	WLogin,
	WPlayer,
};

namespace Tools
{
	static QString absolutePath()
	{
		QString p = QCoreApplication::applicationFilePath();

		for (int i = p.length() - 1, k = 0; i > 0; --i)
		{
			if (p[i] == '/') ++k;
			if (k == 3)
			{
				QString abs;
				for (int j = 0; j < i; ++j)
				{
					abs += p[j];
				}
				p = abs;
				break;
			}
		}
		return p;
	}

	static QString tagEditerPath()
	{
		return Tools::absolutePath() + "/DesktopMusicPlayer/\"Tag Editor\"/Audio.exe";
	}
}


#endif