#ifndef _SERVER_TOOLS_H_
#define _SERVER_TOOLS_H_

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

#include <QTime>
#include <QString>
#include <QVector>

#include <iostream>

/*taglib specific includes*/
#include <fileref.h>
#include <tbytevector.h>			//ByteVector
#include <mpegfile.h>				//mp3 file
#include <id3v2tag.h>				//tag
#include <id3v2frame.h>				//frame
#include <attachedPictureFrame.h>	//attachedPictureFrame

using namespace TagLib::ID3v2;

namespace STools
{
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
}

#endif // ! _SERVER_TOOLS_H_

