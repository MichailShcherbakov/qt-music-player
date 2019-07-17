#ifndef _IWINDOW_H_
#define _IWINDOW_H_

#include "StdAfx.h"

#include <QObject>
#include <QByteArray>
#include <QQuickWindow>
#include <QQmlContext>

#include "Query.h"
#include "EParams.h"
#include "ImageProvider/ImageProvider.h"

class IWindow : public QObject
{
	Q_OBJECT

public:
	IWindow(const EParams* const params, QQuickWindow* window = Q_NULLPTR) :
		m_pParams(params),
		m_window(window)
	{}

	virtual ~IWindow() { SAFE_DELETE(m_window); }

public:
	inline QQuickWindow* Window(void) { return m_window; }
	inline void SetWindowHandle(QQuickWindow* win) { m_window = win; }
	virtual void Initialize(void) = 0;

signals:
	void onClosing();

protected:
	QQuickWindow* m_window;
	const EParams* const m_pParams;
};

#endif