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
		m_pWindow(window)
	{}

	virtual ~IWindow() { SAFE_DELETE(m_pWindow); }

public:
	virtual void Initialize(void) = 0;
	inline QQuickWindow* Window() { return m_pWindow; }

signals:
	void closing();

protected:
	QQuickWindow* m_pWindow;
};

#endif