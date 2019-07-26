#ifndef _CHAPTER_USER_H_
#define _CHAPTER_USER_H_

#include "Interfaces/IChapter.h"

class ChapterUser : public IÑhapter
{
	Q_OBJECT
	Q_PROPERTY(bool remember MEMBER m_remember NOTIFY rememberChanged)
	Q_PROPERTY(QString hashCode MEMBER m_hashCode NOTIFY hashCodeChanged)

public:
	ChapterUser(QSettings* settings);
	~ChapterUser() override;

public:
	void SetRemember(bool remember);
	bool Remember();

public:
	void SetHashCode(QString hash);
	QString HashCode();

signals:
	void rememberChanged();
	void hashCodeChanged();

signals:
	void changeRemember();
	void changeHashCode();

private:
	bool m_remember;
	QString m_hashCode;
};

#endif 