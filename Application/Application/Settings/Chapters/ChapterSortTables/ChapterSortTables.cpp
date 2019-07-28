#include "StdAfx.h"
#include "ChapterSortTables.h"

ChapterSortTables::ChapterSortTables()
{
	m_pAppSettings = new QSettings("settings.ini", QSettings::IniFormat);

	qmlRegisterUncreatableType<SortTypeEnum>("packages.enums.sorttables", 1, 0, "SortTypeEnum", "");
	qRegisterMetaType<SortTypeEnum::ESortType>("ESortType");

	qmlRegisterUncreatableType<SortStateEnum>("packages.enums.sorttables", 1, 0, "SortStateEnum", "");
	qRegisterMetaType<SortStateEnum::ESortState>("ESortState");

	m_pAppSettings->beginGroup("SortTables");
	m_type = static_cast<SortTypeEnum::ESortType>(m_pAppSettings->value("sortType").toInt());
	m_state = static_cast<SortStateEnum::ESortState>(m_pAppSettings->value("sortState").toInt());
	m_pAppSettings->endGroup();
}

ChapterSortTables::~ChapterSortTables()
{

}

SortTypeEnum::ESortType ChapterSortTables::Type()
{
	return m_type;
}

SortStateEnum::ESortState ChapterSortTables::State()
{
	return m_state;
}

void ChapterSortTables::SetType(SortTypeEnum::ESortType type)
{
	m_type = type;
	m_pAppSettings->setValue("SortTables/sortType", static_cast<int>(m_state));
	emit changeType();
}

void ChapterSortTables::SetState(SortStateEnum::ESortState state)
{
	m_state = state;
	m_pAppSettings->setValue("SortTables/sortState", static_cast<int>(m_state));
	emit changeState();
}