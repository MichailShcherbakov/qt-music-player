#ifndef _ISCREEN_H_
#define _ISCREEN_H_

#include <QObject>

class IScreen : public QObject
{
	Q_OBJECT

public:
	IScreen() {}
	virtual ~IScreen() {}

public slots:
	virtual void Initialize() = 0;
};

#endif