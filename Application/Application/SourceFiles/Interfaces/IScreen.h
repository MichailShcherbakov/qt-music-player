#ifndef _ISCREEN_H_
#define _ISCREEN_H_

#include "StdAfx.h"

#include <QObject>

#include "EParams.h"

class IScreen : public QObject
{
	Q_OBJECT

public:
	IScreen(const EParams* const params) : m_pParams(params) {}
	virtual ~IScreen() {}

public slots:
	virtual void Initialize() = 0;

protected:
	const EParams* const m_pParams;
};

#endif