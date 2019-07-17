#ifndef _EPARAMS_H_
#define _EPARAMS_H_

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Network/Socket/Socket.h"
#include "ImageProvider/ImageProvider.h"

struct EParams
{
	EParams() :
		m_pSocket(Q_NULLPTR),
		m_pEngine(Q_NULLPTR),
		m_pRootContext(Q_NULLPTR),
		m_pRootImageProvider(Q_NULLPTR)
	{
	}

	EParams(QQmlApplicationEngine* engine, QQmlContext* context, Socket* socket, ImageProvider* imageProvider) :
		m_pSocket(socket),
		m_pEngine(engine),
		m_pRootContext(context),
		m_pRootImageProvider(imageProvider)
	{
	}

	QQmlApplicationEngine* m_pEngine;
	QQmlContext* m_pRootContext;
	Socket* m_pSocket;
	ImageProvider* m_pRootImageProvider;
};

#endif
