#ifndef _SERVER_TOOLS_H_
#define _SERVER_TOOLS_H_

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

#include <QTime>
#include <QString>
#include <QVector>
#include <QFile>

#include <iostream>

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

	class CTempFile
	{
	public:
		CTempFile() {}
		CTempFile(QString path) { CreateTempFile(path); }
		CTempFile(QString path, QByteArray data) { CreateTempFile(path, data); }
		~CTempFile() { delete m_file; }
	public:
		bool CreateTempFile(QString path) { 
			m_file = new QFile(path);
			if (m_file->open(QFile::WriteOnly))
			{
				m_file->close();
				return true;
			}
			else
			{
				return false;
			}
		}
		bool CreateTempFile(QString path, QByteArray data) {
			m_file = new QFile(path);
			if (m_file->open(QFile::WriteOnly))
			{
				m_file->write(data);
				m_file->close();
				return true;
			}
			else
			{
				return false;
			}
		}
		bool RemoveTempFile() { 
			if (m_file->remove())
			{
				delete m_file;
				return true;
			}
			else
			{
				return false;
			}			
		}
		bool Write(QByteArray data)
		{
			if (m_file)
			{
				m_file->open(QIODevice::ReadOnly);
				if (m_file->write(data) > 0) 
				{
					return true;
				}
				else
				{
					return false;
				}
				m_file->close();
			}
			else
			{
				return false;
			}
		}
		QByteArray ReadAll()
		{
			if (m_file)
			{
				m_file->open(QIODevice::ReadOnly);
				QByteArray data = m_file->readAll();
				m_file->close();
				return data;
			}
			else
			{
				return false;
			}
		}
	private:
		QFile* m_file;
	};

}

#endif // ! _SERVER_TOOLS_H_

