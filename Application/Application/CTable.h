#ifndef _C_TABLE_H_
#define _C_TABLE_H_

#include <QMap>
#include <QList>
#include <QVariant>
#include <QPair>

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

class Row
{
public:
	Row();
	~Row();

public:
	void Append(const QVariant& value);
	int Size();
	void InsertAt(const int& index, const QVariant& value);
	void Remove(const int& index);
	QList<QVariant> List();

private:
	QList<QVariant> m_list;
};

class CTable
{
public:
	CTable();
	~CTable();

public:
	void AddColumn(const QString& title);
	void AddRow(Row& row);
	void RemoveColumn(const QString& title);
	int Rows();
	int Columns();
	bool Contains(const QString& title);
	void RemoveRow(const QString& title, const int& index);
	void InsertAt(const QString& title, const int& index, const QVariant& row);
	QVariant ValueAt(const QString& title, const int& index);
	int IndexAt(const QString& title, const QVariant& row);
	void Clear();

private:
	int IdColumn(const QString& title);

private:
	QList<QPair<QString, Column>> m_list;
	int m_size = 0;
};

#endif