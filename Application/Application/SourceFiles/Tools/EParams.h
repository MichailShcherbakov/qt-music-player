#ifndef _EPARAMS_H_
#define _EPARAMS_H_

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include "Network/Socket/Socket.h"
#include "MediaPlayer/MediaPlayer.h"
#include "ImageProvider/ImageProvider.h"

struct EParams
{
	EParams() :
		m_pSocket(Q_NULLPTR),
		m_pEngine(Q_NULLPTR),
		m_pRootContext(Q_NULLPTR),
		m_pRootImageProvider(Q_NULLPTR),
		m_pSettings(Q_NULLPTR),
		m_pMediaPlayer(Q_NULLPTR)
	{
	}

	QQmlApplicationEngine* m_pEngine;
	QQmlContext* m_pRootContext;
	Socket* m_pSocket;
	ImageProvider* m_pRootImageProvider;
	QSettings* m_pSettings;
	MediaPlayer* m_pMediaPlayer;
};

#endif
