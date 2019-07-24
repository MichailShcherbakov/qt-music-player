#ifndef _FOOTER_PANEL_H_
#define _FOOTER_PANEL_H_

#include "StdAfx.h"
#include "EParams.h"

#include <QObject>

#include "Interfaces/ISectionObject.h"

class FooterPanel : public ISectionObject
{
	Q_OBJECT

	Q_PROPERTY(int id MEMBER m_id NOTIFY idChanged);
	Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged);
	Q_PROPERTY(QString artist MEMBER m_artist NOTIFY artistChanged);
	Q_PROPERTY(QString currentTime MEMBER m_currentTime NOTIFY currentTimeChanged);
	Q_PROPERTY(QString time MEMBER m_time NOTIFY timeChanged);
	Q_PROPERTY(QString coverID MEMBER m_coverID NOTIFY coverIDChanged);

public:
	FooterPanel();
	~FooterPanel();

public slots:
	virtual void Initialize() override;
	virtual void ReadyRead(QByteArray package) override;
	virtual void GottenData(QByteArray data) override;

signals:
	void titleChanged();
	void idChanged();
	void artistChanged();
	void currentTimeChanged();
	void timeChanged();
	void coverIDChanged();

private:
	int m_id;
	QString m_title;
	QString m_artist;
	QString m_time;
	QString m_currentTime;
	QString m_coverID;
};

#endif