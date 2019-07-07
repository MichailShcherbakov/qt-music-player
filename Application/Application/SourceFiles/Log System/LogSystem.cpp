#include "Log System/LogSystem.h"

void LogSystem::Msg(ETypeMessage type, QString log, QString file, QString func, int line)
{
	QTime time;
	QString msg;

	switch (type)
	{
	case ETypeMessage::Log:
	{
		msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [" + func + "] [" + QString::number(line) + "] [Log] " + log;
		break;
	}
	case ETypeMessage::Warning:
	{
		msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [" + func + "] [" + QString::number(line) + "] [Warning] " + log;
		break;
	}
	case ETypeMessage::Success:
	{
		msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [" + func + "] [" + QString::number(line) + "] [Success] " + log;
		break;
	}
	case ETypeMessage::Error:
	{
		msg = "[" + time.currentTime().toString("hh:mm:ss.zzz") + "] [" + func + "] [" + QString::number(line) + "] [Error] " + log;
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
		m_fileName = "Logs/Log_" + QDateTime().currentDateTime().toString("yyyy.mm.dd_hh.mm.ss") + ".txt";
		fileIsCreated = false;
	}

	QFile f(m_fileName);
	f.open(QIODevice::Append | QIODevice::WriteOnly);
	f.write(msg.toUtf8());
	f.close();
}
