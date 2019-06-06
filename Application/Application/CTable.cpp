#include "CTable.h"



CTable::CTable()
{
}


CTable::~CTable()
{
}

void CTable::AddColumn(const QString& title)
{
	if (!this->Contains(title))
	{
		Column* col = new Column;
		m_list.append(QPair<QString, Column*>(title, col));
	}
}

void CTable::AddRow(Row row)
{
	try
	{
		if (row.Size() != m_list.size())
			throw QString("The size of the table does not match the size of the row");
		else
		{
			int i = 0;
			for (auto it : m_list)
				it.second->AddRow(row.ValueAt(i++));
		}
	}
	catch (QString e)
	{
		qDebug() << "[" +  QString(__FUNCTION__) + "] [Error] " + e;
	}
}

void CTable::RemoveColumn(const QString& title)
{
	try
	{
		int pos = this->Contains(title);

		if (pos)
			m_list.removeAt(this->IdColumn(title));
		else
			throw "No such column";
	}
	catch (QString e)
	{
		qDebug() << "[" + QString(__FUNCTION__) + "] [Error] " + e;
	}
	
}

int CTable::Rows()
{
	return m_list.at(0).second->Size();
}

int CTable::Columns()
{
	return m_list.size();
}

bool CTable::Contains(const QString& title)
{
	for (auto it : m_list)
	{
		if (it.first == title)
		{
			return true;
			break;
		}
	}
	return false;
}

void CTable::RemoveRow(const int& index)
{
	if (m_list.at(0).second->Contains(index))
	{
		int pos = 0;
		for (auto it : m_list)
			m_list.at(pos++).second->RemoveRow(index);
	}
}

void CTable::InsertAt(const int index, Row row)
{
	for (auto it : m_list)
		for (auto value : row.List())
			it.second->InsertAt(index, value);
}

QVariant CTable::ValueAt(const QString& title, const int& index)
{
	for (auto it : m_list)
	{
		if (it.first == title)
		{
			return it.second->ValueAt(index);
		}
	}
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

void Column::AddRow(QVariant row)
{
	m_list.insert(m_size++, row);
}

void Column::RemoveRow(const int& index)
{
	try
	{
		if (index >= 0 && index <= m_size)
		{
			m_list.removeAt(index);
			m_size -= 1;
		}
		else
			throw "The index is beyond the array bounds";
	}
	catch (QString e)
	{
		qDebug() << "[" + QString(__FUNCTION__) + "] [Error] " + e;
	}
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
	try
	{
		if (index >= 0 && index < m_list.size())
			return m_list.at(index);
		else
			throw "No such index";
	}
	catch (QString e)
	{
		qDebug() << "[" + QString(__FUNCTION__) + "] [Error] " + e;
	}
}

int Column::IndexAt(const QVariant& row)
{
	return m_list.indexOf(row);
}

int Column::Size()
{
	return m_list.size();
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

QList<QVariant> Row::List()
{
	return m_list;
}

void Row::InsertAt(const int& index, const QVariant& value)
{
	m_list.insert(index, value);
}

void Row::Remove(const int& index)
{
	m_list.removeAt(index);
}

QVariant Row::ValueAt(const int index)
{
	return m_list.at(index);
}
