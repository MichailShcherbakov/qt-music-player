#include "FWindow.h"

FWindow::FWindow(QQuickWindow* parent) :
	QQuickWindow(parent)
{
	this->setFlags(Qt::Window | Qt::FramelessWindowHint);
	this->setWidth(m_width);
	this->setHeight(m_height);
}

void FWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (m_fieldType == EFieldType::TitleBar)
		{
			m_mousePoint = event->pos();
			isMoving = true;
		}
		else
		{
			isResizing = true;
		}
	}

	QQuickWindow::mousePressEvent(event);
}

void FWindow::mouseMoveEvent(QMouseEvent* event)
{
	QQuickWindow::mouseMoveEvent(event);

	if (isMoving)
	{
		const QPointF delta = event->globalPos() - m_mousePoint;
		this->setGeometry(delta.toPoint().x(), delta.toPoint().y(), width(), height());
		return;
	}
	else if (isResizing)
	{
		switch (m_fieldType)
		{
		case EFieldType::Left:
		{
			int dx = (x() - event->globalPos().x()) + width();

			if (dx >= m_minWidth &&
				dx <= m_maxWidth)
			{
				this->setGeometry(event->globalPos().x(), y(), dx, height());
			}
			break;
		}
		case EFieldType::Right:
		{
			int dx = event->globalPos().x() - x();

			if (dx >= m_minWidth &&
				dx <= m_maxWidth)
			{
				this->setGeometry(x(), y(), dx, height());
			}
			break;
		}
		case EFieldType::Top:
		{
			int dy = (y() - event->globalPos().y()) + height();

			if (dy >= m_minHeight &&
				dy <= m_maxHeight)
			{
				this->setGeometry(x(), event->globalPos().y(), width(), dy);
			}
			break;
		}
		case EFieldType::Botton:
		{
			int dy = event->globalPos().y() - y();

			if (dy >= m_minHeight &&
				dy <= m_maxHeight)
			{
				this->setGeometry(x(), y(), width(), dy);
			}
			break;
		}
		case EFieldType::Left_Botton:
		{
			int dx = (x() - event->globalPos().x()) + width();
			int dy = event->globalPos().y() - y();

			if (dx >= m_minWidth &&
				dx <= m_maxWidth &&
				dy >= m_minHeight &&
				dy <= m_maxHeight)
			{
				this->setGeometry(event->globalPos().x(), y(), dx, dy);
			}
			else if (dx >= m_minWidth &&
				dx <= m_maxWidth)
			{
				this->setGeometry(event->globalPos().x(), y(), dx, height());
			}
			else if (dy <= m_maxHeight &&
				dy >= m_minHeight)
			{
				this->setGeometry(x(), y(), width(), dy);
			}
			break;
		}
		case EFieldType::Right_Botton:
		{
			int dx = event->globalPos().x() - x();
			int dy = event->globalPos().y() - y();

			if (dx >= m_minWidth &&
				dx <= m_maxWidth &&
				dy >= m_minHeight &&
				dy <= m_maxHeight)
			{
				this->setGeometry(x(), y(), dx, dy);
			}
			else if (dx >= m_minWidth &&
					dx <= m_maxWidth)
			{
				this->setGeometry(x(), y(), dx, height());
			}
			else if (dy <= m_maxHeight &&
					dy >= m_minHeight)
			{
				this->setGeometry(x(), y(), width(), dy);
			}
			break;
		}
		case EFieldType::Left_Top:
		{
			int dx = (x() - event->globalPos().x()) + width();
			int dy = (y() - event->globalPos().y()) + height();

			if (dx >= m_minWidth &&
				dx <= m_maxWidth &&
				dy >= m_minHeight &&
				dy <= m_maxHeight)
			{
				this->setGeometry(event->globalPos().x(), event->globalPos().y(), dx, dy);
			}
			else if (dx >= m_minWidth &&
				dx <= m_maxWidth)
			{
				this->setGeometry(event->globalPos().x(), y(), dx, height());
			}
			else if (dy <= m_maxHeight &&
				dy >= m_minHeight)
			{
				this->setGeometry(x(), event->globalPos().y(), width(), dy);
			}
			break;
		}
		case EFieldType::Right_Top:
		{
			int dx = event->globalPos().x() - x();
			int dy = (y() - event->globalPos().y()) + height();

			if (dx >= m_minWidth &&
				dx <= m_maxWidth &&
				dy >= m_minHeight &&
				dy <= m_maxHeight)
			{
				this->setGeometry(x(), event->globalPos().y(), dx, dy);
			}
			else if (dx >= m_minWidth &&
					dx <= m_maxWidth)
			{
				this->setGeometry(x(), y(), dx, height());
			}
			else if (dy <= m_maxHeight &&
					dy >= m_minHeight)
			{
				this->setGeometry(x(), event->globalPos().y(), width(), dy);
			}
			break;
		}
		}
		return;
	}
	m_fieldType = GetFieldType(event);
	SetCursor(m_fieldType);
}

void FWindow::mouseReleaseEvent(QMouseEvent* event)
{
	QQuickWindow::mouseReleaseEvent(event);

	if (isMoving)
	{
		isMoving = false;
	}
	if (isResizing)
	{
		isResizing = false;
	}
	m_fieldType = EFieldType::Unknown;
}

EFieldType FWindow::GetFieldType(QMouseEvent* event)
{
	// Left Field
	if (event->pos().x() < m_edge &&
		event->pos().y() > m_edge &&
		event->pos().y() < height() - m_edge)
	{
		return EFieldType::Left;
	}
	// Right Field
	else if (event->pos().x() > width() - m_edge &&
		event->pos().y() > m_edge &&
		event->pos().y() < height() - m_edge)
	{
		return EFieldType::Right;
	}
	// Top Field
	else if (event->pos().x() < width() - m_edge &&
		event->pos().x() > m_edge &&
		event->pos().y() < m_edge)
	{
		return EFieldType::Top;
	}
	// Botton Field
	else if (event->pos().x() < width() - m_edge &&
		event->pos().x() > m_edge &&
		event->pos().y() > height() - m_edge)
	{
		return EFieldType::Botton;
	}
	// Left-Botton Field
	else if (event->pos().x() <= m_edge &&
		event->pos().y() >= height() - m_edge)
	{
		return EFieldType::Left_Botton;
	}
	// Right-Botton Field
	else if (event->pos().x() >= width() - m_edge &&
		event->pos().y() >= height() - m_edge)
	{
		return EFieldType::Right_Botton;
	}
	// Right-Top Field
	else if (event->pos().x() >= width() - m_edge &&
		event->pos().y() <= m_edge)
	{
		return EFieldType::Right_Top;
	}
	// Left-Top Field
	else if (event->pos().x() <= m_edge &&
		event->pos().y() <= m_edge)
	{
		return EFieldType::Left_Top;
	}
	// TitleBar Field
	else if (event->pos().x() >= m_edge && 
			event->pos().x() <= width() - m_edge &&
			event->pos().y() >= m_edge && 
			event->pos().y() <= m_hTitleBar)
	{
		return EFieldType::TitleBar;
	}
	else
	{
		return EFieldType::Unknown;
	}
}

void FWindow::SetCursor(EFieldType field)
{
	if (field == EFieldType::Left || field == EFieldType::Right)
	{
		this->setCursor(Qt::SizeHorCursor);
		isNormalCursor = false;
	}
	else if (field == EFieldType::Top || field == EFieldType::Botton)
	{
		this->setCursor(Qt::SizeVerCursor);
		isNormalCursor = false;
	}
	else if (field == EFieldType::Left_Botton || field == EFieldType::Right_Top)
	{
		this->setCursor(Qt::SizeBDiagCursor);
		isNormalCursor = false;
	}
	else if (field == EFieldType::Right_Botton || field == EFieldType::Left_Top)
	{
		this->setCursor(Qt::SizeFDiagCursor);
		isNormalCursor = false;
	}
	else
	{
		if (!isNormalCursor)
		{
			this->setCursor(Qt::ArrowCursor);
			isNormalCursor = true;
		}
	}
}

void FWindow::MoveToCenter()
{
	QScreen* screen = QGuiApplication::screens().first();
	QSize size = screen->availableSize();

	this->setX(size.width() / 2 - m_width / 2);
	this->setY(size.height() / 2 - m_height / 2);
}

int FWindow::GetWidth()
{
	return m_width;
}

void FWindow::SetWidth(int width)
{
	m_width = width;
	this->setWidth(m_width); 
	MoveToCenter();
}

int FWindow::GetMaxWidth()
{
	return m_maxWidth;
}

void FWindow::SetMaxWidth(int maxWidth)
{
	m_maxWidth = maxWidth;
}

int FWindow::GetMinWidth()
{
	return m_minWidth;
}

void FWindow::SetMinWidth(int minWidth)
{
	m_minWidth = minWidth;
}

int FWindow::GetHeight()
{
	return m_height;
}

void FWindow::SetHeight(int height)
{
	m_height = height;
	this->setHeight(m_height);
	MoveToCenter();
}

int FWindow::GetMaxHeight()
{
	return m_maxWidth;
}

void FWindow::SetMaxHeight(int maxHeight)
{
	m_maxHeight = maxHeight;
}

int FWindow::GetMinHeight()
{
	return m_minHeight;
}

void FWindow::SetMinHeight(int minHeight)
{
	m_minHeight = minHeight;
}
