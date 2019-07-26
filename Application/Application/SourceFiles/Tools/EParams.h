#ifndef _EPARAMS_H_
#define _EPARAMS_H_

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QSettings>

#include "Network/Socket/Socket.h"
#include "Interfaces/IMediaPlayer.h"
#include "ImageProvider/ImageProvider.h"
#include "Settings/Settings.h"

struct Params
{
	Params() {};

	QQmlApplicationEngine*	pEngine;
	QQmlContext*			pRootContext ;
	Socket*					pSocket;
	ImageProvider*			pRootImageProvider;
	Settings*				pSettings;
	IMediaPlayer*			pMediaPlayer;
};

extern Params* gParams;

#endif
