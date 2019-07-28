#ifndef _ICHAPTER_H_
#define _ICHAPTER_H_

#include <QObject>
#include <QSettings>

struct IÑhapter : public QObject
{
	Q_OBJECT

protected:
	QSettings* m_pAppSettings;
};


#endif
