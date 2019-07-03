#include "ListViewModels/Horizontal/Type 1/List/List.h"

using namespace HorizontalModel1;

List::List(QObject* parent) :
	QObject(parent)
{
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
		item.textLineSecond == oldItem.textLineSecond)
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
