#ifndef _LOG_SYSTEM_H_
#define _LOG_SYSTEM_H_

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

#include <QTime>
#include <QString>
#include <QVector>
#include <QFile>

#include <iostream>

enum class EMessage : ushort
{
	Log = 0,
	Warning,
	Success,
	Error,
};

static void Msg(EMessage typeMsg, QString string)
{
	QTime time;

	#ifdef Q_OS_WIN32
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	#endif

	switch (typeMsg)
	{
	case EMessage::Log:
	{		
		#ifdef Q_OS_WIN32
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		#endif
		QString str = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Log] " + string;
		std::cout << str.toStdString() << std::endl;
		break;
	}
	case EMessage::Warning:
	{
		#ifdef Q_OS_WIN32
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		#endif
		QString str = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Warning] " + string;
		std::cout << str.toStdString() << std::endl;
		break;
	}
	case EMessage::Success:
	{
		#ifdef Q_OS_WIN32
		SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		#endif
		QString str = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Success] " + string;
		std::cout << str.toStdString() << std::endl;
		break;
	}
	case EMessage::Error:
	{
		#ifdef Q_OS_WIN32
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
		#endif
		QString str = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Error] " + string;
		std::cout << str.toStdString() << std::endl;
		break;
	}
	}
}

#endif // ! _LOG_SYSTEM_H_

