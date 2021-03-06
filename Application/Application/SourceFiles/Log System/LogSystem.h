#ifndef _LOG_SYSTEM_H_
#define _LOG_SYSTEM_H_

#include <QTime>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>

#include <stdexcept>

enum class ETypeMessage
{
	Unknown = 0,
	Log,
	Success,
	Warning,
	Error,
	FatalError,
};

namespace LogSystem
{
	void Msg(ETypeMessage type, QString log, QString file, QString func, int line);
	void WriteLog(QString msg);

	static QString m_fileName;
	static bool fileIsCreated = false;
};

#define MSG(type, msg) \
LogSystem::Msg(type, msg, __FILE__, __FUNCTION__, __LINE__);

#endif
