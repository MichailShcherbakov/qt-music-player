#ifndef _CHAPTER_SORT_TABLES_H_
#define _CHAPTER_SORT_TABLES_H_

#include "Interfaces/IChapter.h"

struct SortTypeEnum
{
	Q_GADGET

public:
	explicit SortTypeEnum();

	enum class ESortType : uint
	{
		Unknown = 0,
		Alphabetical,
		Album,
		Artist,
		DateAdded,
	};

	Q_ENUM(ESortType)
};

struct SortStateEnum
{
	Q_GADGET

public:
	explicit SortStateEnum();

	enum class ESortState : uint
	{
		Unknown = 0,
		Ascending,
		Descending,
	};

	Q_ENUM(ESortState)
};

class ChapterSortTables : public IÑhapter
{
	Q_OBJECT
	Q_PROPERTY(SortTypeEnum::ESortType type MEMBER m_type NOTIFY typeChanged)
	Q_PROPERTY(SortStateEnum::ESortState state MEMBER m_state NOTIFY stateChanged)

public:
	ChapterSortTables(QSettings* settings);
	~ChapterSortTables() override;

public:
	void SetType(SortTypeEnum::ESortType type);
	SortTypeEnum::ESortType Type();
	void SetState(SortStateEnum::ESortState state);
	SortStateEnum::ESortState State();

signals:
	void typeChanged();
	void stateChanged();
	void changeType();
	void changeState();

private:
	SortTypeEnum::ESortType m_type = SortTypeEnum::ESortType::Unknown;
	SortStateEnum::ESortState m_state = SortStateEnum::ESortState::Unknown;
};

#endif 