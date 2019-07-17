#ifndef _FWINDOW_H_
#define _FWINDOW_H_

#include "Tools/StdAfx.h"

#include <QObject>
#include <QScreen>
#include <QQuickWindow>

typedef unsigned short ushort;
typedef unsigned int uint;

enum class EFieldType : int
{
	Unknown = -1,
	TitleBar,
	Left,
	Right,
	Top,
	Botton,
	Left_Botton,
	Right_Botton,
	Left_Top,
	Right_Top,
};

class FWindow : public QQuickWindow
{
	Q_OBJECT
	Q_PROPERTY(int m_hTitleBar READ GetHeightTitleBar WRITE SetHeightTitleBar NOTIFY heightTitleBarChanged);
	Q_PROPERTY(int m_width READ GetWidth WRITE SetWidth);
	Q_PROPERTY(int m_maxWidth READ GetMaxWidth WRITE SetMaxWidth);
	Q_PROPERTY(int m_minWidth READ GetMinWidth WRITE SetMinWidth);
	Q_PROPERTY(int m_height READ GetHeight WRITE SetHeight);
	Q_PROPERTY(int m_maxHeight READ GetMaxHeight WRITE SetMaxHeight);
	Q_PROPERTY(int m_minHeight READ GetMinHeight WRITE SetMinHeight);

public:
	explicit FWindow(QQuickWindow* parent = Q_NULLPTR);

protected:
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;

private:
	EFieldType GetFieldType(QMouseEvent* event);
	void SetCursor(EFieldType field);
	void MoveToCenter();
	int GetWidth();
	void SetWidth(int width);
	int GetMinWidth();
	void SetMinWidth(int minHeight);
	int GetMaxWidth();
	void SetMaxWidth(int maxHeight);
	int GetHeight();
	void SetHeight(int height);
	int GetMinHeight();
	void SetMinHeight(int minHeight);
	int GetMaxHeight();
	void SetMaxHeight(int maxHeight);
	void SetHeightTitleBar(int size);
	int GetHeightTitleBar();

signals:
	void heightTitleBarChanged();
	void sizeChanged();

private:
	bool isMoving = false;
	bool isResizing = false;
	bool isNormalCursor = true;
	const ushort m_edge = 5;
	uint m_hTitleBar = 32; // Height of the title bar
	uint m_width = 640;
	uint m_height = 400;
	uint m_minWidth = 640;
	uint m_minHeight = 440;
	uint m_maxWidth = 1200;
	uint m_maxHeight = 720; 
	EFieldType m_fieldType = EFieldType::Unknown;
	QPointF m_mousePoint;
};

#endif
