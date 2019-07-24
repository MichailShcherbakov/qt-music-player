#include "StdAfx.h"
#include "LogSystem.h"

void LogSystem::Msg(ETypeMessage type, QString log, QString file, QString func, int line)
{
	QTime time;
	QString msg;

	switch (type)
	{
	case ETypeMessage::Log:
	{
		msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Log] [" + func + "] [" + QString::number(line) + "] " + log;
		break;
	}
	case ETypeMessage::Warning:
	{
		msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Warning] [" + func + "] [" + QString::number(line) + "] " + log;
		break;
	}
	case ETypeMessage::Success:
	{
		msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Success] [" + func + "] [" + QString::number(line) + "] " + log;
		break;
	}
	case ETypeMessage::Error:
	{
		msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Error] [" + func + "] [" + QString::number(line) + "] " + log;
		break;
	}
	case ETypeMessage::FatalError:
	{
		msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [Fatal Error] [" + func + "] [" + QString::number(line) + "] " + log;
		break;
	}
	}
	WriteLog(msg);
	qDebug() << msg;
}

void LogSystem::WriteLog(QString msg)
{
	if (!fileIsCreated)
	{
		if (!QDir("Logs").exists())
		{
			QDir().mkdir("Logs");
		}
		m_fileName = "Logs/Log_" + QDateTime().currentDateTime().toString("yyyy.mm.dd_hh.mm.ss") + ".txt";
		fileIsCreated = true;
	}

	QFile f(m_fileName);
	f.open(QIODevice::Append | QIODevice::WriteOnly);
	f.write(msg.toUtf8() + '\n');
	f.close();
}
