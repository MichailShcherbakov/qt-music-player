#ifndef _ICHAPTER_H_
#define _ICHAPTER_H_

#include <QObject>
#include <QSettings>

struct I�hapter : public QObject
{
	Q_OBJECT

public:
	virtual ~I�hapter() {}

protected:
	QSettings* m_pAppSettings;
};


#endif
