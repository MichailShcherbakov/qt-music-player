#ifndef _I_WINDOW_H_
#define _I_WINDOW_H_

#include "StdAfx.h"

#include "CQuery.h"

#include <QObject>
#include <QByteArray>
#include <QQuickWindow>

class IWindow : public QObject
{
	Q_OBJECT

public:
	IWindow(QQuickWindow* window, CQuery* query = nullptr) : m_window(window), m_query(query) {}
	virtual ~IWindow() { delete m_window, m_query; }

public:
	QQuickWindow* Window(void) { return m_window; }
	virtual void Initialize(void) = 0;
	Q_INVOKABLE QPointF cursorPos() { return QCursor::pos(); }

signals:
	void closing(EWindowType type = EWindowType::Unknown);
	void sendToSocket(QByteArray* data = nullptr);
	void openFileDialog(EDialogType type = EDialogType::Unknown);

public slots:
	virtual void getFromSocket(QByteArray* data) = 0;

protected:
	QQuickWindow* m_window;
	CQuery* m_query;
};

#endif