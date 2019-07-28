#ifndef _CHAPTER_SORT_TABLES_H_
#define _CHAPTER_SORT_TABLES_H_

#include "Interfaces/IChapterSortTables.h"

class ChapterSortTables : public IChapterSortTables
{
	Q_OBJECT

public:
	ChapterSortTables();
	~ChapterSortTables() override;

public:
	virtual void SetType(SortTypeEnum::ESortType type) override;
	virtual SortTypeEnum::ESortType Type() override;
	virtual void SetState(SortStateEnum::ESortState state) override;
	virtual SortStateEnum::ESortState State() override;
};

#endif 