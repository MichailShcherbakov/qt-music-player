#include "CTable.h"



CTable::CTable()
{
}


CTable::~CTable()
{
}

void CTable::AddColumn(const QString& title)
{
	if (this->Contains(title))
	{
		QPair<QString, Column> temp;
		temp.first = title;
		temp.second = Column();
		m_list.append(temp);
		m_size = m_list.size();
	}
}

void CTable::AddRow(Row& row)
{
	for (auto value : row.List())
	{
		for (auto it : m_list)
		{
			it.second.AddRow(value);
		}
	}
}

void CTable::RemoveColumn(const QString& title)
{
	if (this->Contains(title))
		m_list.removeAt(this->IdColumn(title));
}

int CTable::Rows()
{
	return 0;
}

int CTable::Columns()
{
	return m_size;
}

bool CTable::Contains(const QString& title)
{
	for (auto it : m_list)
	{
		if (it.first == title)
		{
			return false;
			break;
		}
	}
	return true;
}

void CTable::RemoveRow(const QString& title, const int& index)
{
	/*if (m_list.contains(title))
		m_list.find(title).value().RemoveRow(index);*/
}

void CTable::InsertAt(const QString& title, const int& index, const QVariant& row)
{
	/*if (m_list.contains(title))
		m_list.find(title).value().InsertAt(index, row);*/
}

QVariant CTable::ValueAt(const QString& title, const int& index)
{
	/*if (m_list.contains(title))
		return m_list.find(title).value().ValueAt(index);
	else return QVariant();*/
	return QVariant();
}

int CTable::IndexAt(const QString& title, const QVariant& row)
{
	/*if (m_list.contains(title))
		return m_list.find(title).value().IndexAt(row);
	else return -1;*/
	return 0;
}

void CTable::Clear()
{
	if (!m_list.isEmpty())
	{
		m_list.clear();
		m_size = 0;
	}
}

int CTable::IdColumn(const QString& title)
{
	int pos = 0;
	for (auto it : m_list)
	{
		if (it.first == title)
		{
			return pos;
			break;
		}
		++pos;
	}
	return -1;
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

Row::Row()
{
}

Row::~Row()
{
}

void Row::Append(const QVariant& value)
{
	m_list.append(value);
}

int Row::Size()
{
	return m_list.size();
}

void Row::InsertAt(const int& index, const QVariant& value)
{
	m_list.insert(index, value);
}

void Row::Remove(const int& index)
{
	m_list.removeAt(index);
}

QList<QVariant> Row::List()
{
	return m_list;
}
