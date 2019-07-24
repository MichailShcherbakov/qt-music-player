#ifndef _IWINDOW_H_
#define _IWINDOW_H_

#include <QObject>
#include <QByteArray>
#include <QQuickWindow>
#include <QQmlContext>

class IWindow : public QObject
{
	Q_OBJECT

public:
	IWindow(QQuickWindow* window = Q_NULLPTR) :
		m_window(window)
	{}

	virtual ~IWindow() { SAFE_DELETE(m_window); }

public:
	virtual void Initialize(void) = 0;
	inline QQuickWindow* Window() { return m_window; }

signals:
	void closing();

protected:
	QQuickWindow* m_window;
};

#endif