#include "Ver1List.h"

using namespace VerticalModel1;

List::List(QObject* parent) :
	QObject(parent)
{
}

List::List(const List& list)
{
	m_list = list.m_list;
}

List::~List()
{

}

QVector<Item> List::GetItems() const
{
    return m_list;
}

bool List::SetItemAt(int index, const Item &item)
{
    if (index < 0 || index >= m_list.size())
            return false;

    const Item &oldItem = m_list.at(index);

    if (item.id == oldItem.id &&
		item.coverKey == oldItem.coverKey &&
		item.textLineFirst == oldItem.textLineFirst &&
		item.textLineSecond == oldItem.textLineSecond &&
		item.textLineThird == oldItem.textLineThird &&
		item.textLineFourth == oldItem.textLineFourth &&
		item.expression == oldItem.expression &&
		item.expression2 == oldItem.expression2)
        return false;

    m_list[index] = item;
    return true;
}

void List::AppendItem(Item item)
{
    emit preItemAppended();

    Item newItem;

	newItem.id = item.id;
	newItem.coverKey = item.coverKey;
	newItem.textLineFirst = item.textLineFirst;
	newItem.textLineSecond = item.textLineSecond;
	newItem.textLineThird = item.textLineThird;
	newItem.textLineFourth = item.textLineFourth;
	newItem.expression = item.expression;
	newItem.expression2 = item.expression2;

    m_list.append(newItem);

    emit postItemAppended();
}

void List::RemoveItem(int index)
{
	if (index >= 0 && m_list.size() > index)
	{
		emit preItemRemoved(index);

		m_list.removeAt(index);

		emit postItemRemoved();
	}
}

void List::InsertItem(int index, Item item)
{
	emit preItemInserted(index);

	m_list.insert(index, item);
	
	emit postItemInserted();
}

Item List::At(int index)
{
	return m_list.at(index);
}

int List::Size()
{
	return m_list.size();
}

void VerticalModel1::List::SetValueItemAt(int index, const QVariant& value, int role)
{
	emit ItemChanged(index, value, role);
}

bool VerticalModel1::List::isEmpty()
{
	return m_list.isEmpty();
}

void VerticalModel1::List::ClearList()
{
	for (auto it : m_list)
	{
		emit preItemRemoved(0);

		m_list.removeFirst();

		emit postItemRemoved();
	}
}
