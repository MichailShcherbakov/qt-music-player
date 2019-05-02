#include "CTable.h"



CTable::CTable()
{
}


CTable::~CTable()
{
}

void CTable::AddColumn(const QString& title)
{
	if (!m_list.contains(title))
	{
		m_list.insert(title, Column());
		m_size = m_list.size();
	}
}

void CTable::AddRow(const QString& title, const QVariant& row)
{
	if (m_list.contains(title))
		m_list.find(title).value().AddRow(row);
}

void CTable::RemoveColumn(const QString& title)
{
	if (m_list.contains(title))
		m_list.remove(title);
}

int CTable::Rows()
{
	return 0;
}

int CTable::Columns()
{
	return m_size;
}

void CTable::RemoveRow(const QString& title, const int& index)
{
	if (m_list.contains(title))
		m_list.find(title).value().RemoveRow(index);
}

void CTable::InsertAt(const QString& title, const int& index, const QVariant& row)
{
	if (m_list.contains(title))
		m_list.find(title).value().InsertAt(index, row);
}

QVariant CTable::ValueAt(const QString& title, const int& index)
{
	if (m_list.contains(title))
		return m_list.find(title).value().ValueAt(index);
	else return QVariant();
}

int CTable::IndexAt(const QString& title, const QVariant& row)
{
	if (m_list.contains(title))
		return m_list.find(title).value().IndexAt(row);
	else return -1;
}

void CTable::Clear()
{
	if (!m_list.isEmpty())
	{
		m_list.clear();
		m_size = 0;
	}
}







Column::Column()
{
}

Column::~Column()
{
}

void Column::AddRow(const QVariant& row)
{
	m_list.insert(m_size++, row);
}

void Column::RemoveRow(const int& index)
{
	if (index >= 0 && index <= m_size)
		m_list.remove(index);
}

void Column::InsertAt(const int& index, const QVariant& row)
{
	if (index >= 0 && index <= m_size)
		m_list.insert(index, row);
}

bool Column::isEmpty()
{
	return m_list.isEmpty();
}

bool Column::Contains(const int& index)
{
	return m_list.contains(index);
}

QVariant Column::ValueAt(const int& index)
{
	if (m_list.contains(index))
		return m_list.find(index).value();
	else
		return QVariant();
}

int Column::IndexAt(const QVariant& row)
{
	return m_list.key(row);
}
