#ifndef _CHAPTER_USER_H_
#define _CHAPTER_USER_H_

#include "Interfaces/IChapterUser.h"

class ChapterUser : public IChapterUser
{
	Q_OBJECT

public:
	ChapterUser();
	~ChapterUser() override;

public:
	virtual void SetRemember(bool remember) override;
	virtual bool Remember() override;

public:
	virtual void SetHashCode(QString hash) override;
	virtual QString HashCode() override;
};

#endif 