#ifndef _UNBLOCKED_MOUSE_AREA_H_
#define _UNBLOCKED_MOUSE_AREA_H_

#include <QQuickItem>
#include <QCursor>

class UnblockedMouseArea : public QQuickItem
{
	Q_OBJECT

	Q_PROPERTY(Qt::CursorShape cursorShape READ GetCursorShape WRITE SetCursorShape);

public:
	UnblockedMouseArea(QQuickItem* parent = Q_NULLPTR);
	~UnblockedMouseArea();

public:
	// QQuickItem
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void hoverEnterEvent(QHoverEvent* event) override;
	virtual void hoverLeaveEvent(QHoverEvent* event) override;
	virtual void hoverMoveEvent(QHoverEvent* event) override;
	// ~QQuickItem

public:
	Qt::CursorShape GetCursorShape();
	void SetCursorShape(Qt::CursorShape shape);

signals:
	void exited();
	void entered();
	void hoveredChanged();
	void clicked();
};

#endif

