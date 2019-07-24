#include "StdAfx.h"
#include "Items/UnblockedMouseArea/UnblockedMouseArea.h"

UnblockedMouseArea::UnblockedMouseArea(QQuickItem* parent)
	: QQuickItem(parent)
{
	setAcceptHoverEvents(true);
	setAcceptTouchEvents(true);
	setAcceptedMouseButtons(Qt::MouseButton::AllButtons);
}

UnblockedMouseArea::~UnblockedMouseArea()
{

}

void UnblockedMouseArea::mousePressEvent(QMouseEvent* event)
{
	QQuickItem::mousePressEvent(event);

	emit clicked();
}

void UnblockedMouseArea::hoverEnterEvent(QHoverEvent* event)
{
	QQuickItem::hoverEnterEvent(event);

	emit entered();
}

void UnblockedMouseArea::hoverLeaveEvent(QHoverEvent* event)
{
	QQuickItem::hoverLeaveEvent(event);

	emit exited();
}

void UnblockedMouseArea::hoverMoveEvent(QHoverEvent* event)
{
	QQuickItem::hoverMoveEvent(event);

	emit hoveredChanged();
}

Qt::CursorShape UnblockedMouseArea::GetCursorShape()
{
	return this->cursor().shape();
}

void UnblockedMouseArea::SetCursorShape(Qt::CursorShape shape)
{
	this->cursor().setShape(shape);
}