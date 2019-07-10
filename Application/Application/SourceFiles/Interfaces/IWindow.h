#ifndef _IWINDOW_H_
#define _IWINDOW_H_

#include "Tools/StdAfx.h"

#include <QObject>
#include <QByteArray>
#include <QQuickWindow>
#include <QQmlContext>

#include "Tools/Query.h"
#include "ImageProvider/ImageProvider.h"

class IWindow : public QObject
{
	Q_OBJECT

public:
	IWindow(QQuickWindow* window = Q_NULLPTR, QQmlContext* context = Q_NULLPTR, ImageProvider* imageProvider = Q_NULLPTR) : m_window(window), m_context(context), m_imageProvider(imageProvider) {}
	virtual ~IWindow() { delete m_window; }

public:
	inline QQuickWindow* Window(void) { return m_window; }
	inline QQmlContext* RootContext(void) { return m_context; }
	inline ImageProvider* RootImageProvider(void) { return m_imageProvider; }
	inline void SetWindowHandle(QQuickWindow* win) { m_window = win; }
	virtual void Initialize(void) = 0;

public slots:
	virtual void GetFromSocket(QByteArray data) = 0;

signals:
	void onSendToSocket(const QByteArray& data);
	void onClosing();

private:
	QQuickWindow* m_window;
	QQmlContext* m_context;
	ImageProvider* m_imageProvider;
};

#endif