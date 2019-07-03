#ifndef _TABLE_H_
#define _TABLE_H_

#include <QMap>
#include <QList>
#include <QVariant>
#include <QDebug>

class Column
{
public:
	Column();
	~Column();

public:
	void AddRow(QVariant row);
	void RemoveRow(const int& index);
	void InsertAt(const int& index, const QVariant& row);
	bool isEmpty();
	bool Contains(const int& index);
	QVariant ValueAt(const int& index);
	int IndexAt(const QVariant& row);
	int Size();

private:
	int m_size = 0;
	QList<QVariant> m_list;
};

class Row
{
public:
	Row();
	~Row();

public:
	void Append(const QVariant& value);
	int Size();
	QList<QVariant> List();
	void InsertAt(const int& index, const QVariant& value);
	void Remove(const int& index);
	QVariant ValueAt(const int index);

private:
	QList<QVariant> m_list;
};

class Table
{
public:
	Table();
	~Table();

public:
	void AddColumn(const QString& title);
	void AddRow(Row row);
	void RemoveColumn(const QString& title);
	int Rows();
	int Columns();
	bool Contains(const QString& title);
	void RemoveRow(const int& index);
	void InsertAt(const int index, Row row);
	QVariant ValueAt(const QString& title, const int& index);
	int IndexAt(const QString& title, const QVariant& row);
	void Clear();

private:
	int IdColumn(const QString& title);

private:
	QList<QPair<QString, Column*>> m_list;
};

#endif