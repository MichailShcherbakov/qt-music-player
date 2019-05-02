#ifndef _I_DIALOG_H_
#define _I_DIALOG_H_

#include <QObject>
#include <QQuickWindow>

class IDialog : public QObject
{
	Q_OBJECT

public:
	IDialog(QQuickWindow* window) : m_window(window) {}
	virtual ~IDialog() { delete m_window; }

public:
	QQuickWindow* Window(void) { return m_window; }
	virtual void Initialize(void) = 0;
	Q_INVOKABLE QPointF cursorPos() { return QCursor::pos(); }

signals:
	void closing(void);

protected:
	QQuickWindow* m_window;
};

#endif
