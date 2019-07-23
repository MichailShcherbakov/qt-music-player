#ifndef _MSG_H_
#define _MSG_H_

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
	FatalError
};

namespace LogSystem
{
	static void Msg(EMessage type, QString log, QString file, QString func, int line)
	{
		QTime time;
		QString msg;

#ifdef Q_OS_WIN32
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

		switch (type)
		{
		case EMessage::Log:
		{
#ifdef Q_OS_WIN32
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#endif
			msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Log] [" + func + "] [" + QString::number(line) + "] " + log;
			break;
		}
		case EMessage::Warning:
		{
#ifdef Q_OS_WIN32
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#endif
			msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Warning] [" + func + "] [" + QString::number(line) + "] " + log;
			break;
		}
		case EMessage::Success:
		{
#ifdef Q_OS_WIN32
			SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#endif
			msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Success] [" + func + "] [" + QString::number(line) + "] " + log;
			break;
		}
		case EMessage::Error:
		{
#ifdef Q_OS_WIN32
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
#endif
			msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Error] [" + func + "] [" + QString::number(line) + "] " + log;
			break;
		}
		case EMessage::FatalError:
		{
#ifdef Q_OS_WIN32
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
#endif
			msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Fatal Error] [" + func + "] [" + QString::number(line) + "] " + log;
			break;
		}
		}
		std::cout << msg.toStdString() << std::endl;
	}
}

#define MSG(type, msg) \
LogSystem::Msg(type, msg, __FILE__, __FUNCTION__, __LINE__);

#endif // ! _SERVER_TOOLS_H_

