#ifndef _ICHAPTER_USER_H_
#define _ICHAPTER_USER_H_

#include "Interfaces/IChapter.h"

class IChapterUser : public IÑhapter
{
	Q_OBJECT
	Q_PROPERTY(bool remember MEMBER m_remember NOTIFY rememberChanged)
	Q_PROPERTY(QString hashCode MEMBER m_hashCode NOTIFY hashCodeChanged)

public:
	IChapterUser() {}
	virtual ~IChapterUser() {}

public:
	virtual void SetRemember(bool remember) = 0;
	virtual bool Remember() = 0;

public:
	virtual void SetHashCode(QString hash) = 0;
	virtual QString HashCode() = 0;

signals:
	void rememberChanged();
	void hashCodeChanged();

signals:
	void changeRemember();
	void changeHashCode();

protected:
	bool m_remember;
	QString m_hashCode;
};

#endif 