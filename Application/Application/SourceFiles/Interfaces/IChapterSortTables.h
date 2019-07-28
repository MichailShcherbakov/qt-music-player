#ifndef _ICHAPTER_SORT_TABLES_H_
#define _ICHAPTER_SORT_TABLES_H_

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

class IChapterSortTables : public IÑhapter
{
	Q_OBJECT
	Q_PROPERTY(SortTypeEnum::ESortType type MEMBER m_type NOTIFY typeChanged)
	Q_PROPERTY(SortStateEnum::ESortState state MEMBER m_state NOTIFY stateChanged)

public:
	IChapterSortTables() {}
	virtual ~IChapterSortTables() {}

public:
	virtual void SetType(SortTypeEnum::ESortType type) = 0;
	virtual SortTypeEnum::ESortType Type() = 0;
	virtual void SetState(SortStateEnum::ESortState state) = 0;
	virtual SortStateEnum::ESortState State() = 0;

signals:
	void typeChanged();
	void stateChanged();
	void changeType();
	void changeState();

protected:
	SortTypeEnum::ESortType m_type = SortTypeEnum::ESortType::Unknown;
	SortStateEnum::ESortState m_state = SortStateEnum::ESortState::Unknown;
};

#endif 
