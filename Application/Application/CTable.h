#ifndef _C_TABLE_H_
#define _C_TABLE_H_

#include <QMap>
#include <QVariant>

class Column
{
public:
	Column();
	~Column();

public:
	void AddRow(const QVariant& row);
	void RemoveRow(const int& index);
	void InsertAt(const int& index, const QVariant& row);
	bool isEmpty();
	bool Contains(const int& index);
	QVariant ValueAt(const int& index);
	int IndexAt(const QVariant& row);

private:
	int m_size = 0;
	QMap<int, QVariant> m_list;
};

class CTable
{
public:
	CTable();
	~CTable();

public:
	void AddColumn(const QString& title);
	void AddRow(const QString& title, const QVariant& row);
	void RemoveColumn(const QString& title);
	int Rows();
	int Columns();
	void RemoveRow(const QString& title, const int& index);
	void InsertAt(const QString& title, const int& index, const QVariant& row);
	QVariant ValueAt(const QString& title, const int& index);
	int IndexAt(const QString& title, const QVariant& row);
	void Clear();

private:
	QMap<QString, Column> m_list;
	int m_size = 0;
};

#endif