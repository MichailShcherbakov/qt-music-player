#include "clist.h"

CList::CList(QObject *parent)
    : QObject (parent)
{
}

CList::~CList()
{

}

QVector<Item> CList::GetItems() const
{
    return m_list;
}

bool CList::SetItemAt(int index, const Item &item)
{
    if (index < 0 || index >= m_list.size())
            return false;

    const Item &oldItem = m_list.at(index);

    if (item.nameFile == oldItem.nameFile &&
		item.image == oldItem.image &&
		item.title == oldItem.title && 
		item.artist == oldItem.artist && 
		item.album == oldItem.album && 
		item.genre == oldItem.genre && 
		item.year == oldItem.year &&
		item.playlist == oldItem.playlist && 
		item.size == oldItem.size && 
		item.reserve == oldItem.reserve &&
		item.time == oldItem.time)
        return false;

    m_list[index] = item;
    return true;
}

void CList::AppendItem(Item item)
{
    emit preItemAppended();

    Item newItem;

	newItem.nameFile = item.nameFile;
	newItem.image = item.image;
	newItem.title = item.title;
	newItem.artist = item.artist;
	newItem.album = item.album;
	newItem.genre = item.genre;
	newItem.year = item.year;
	newItem.playlist = item.playlist;
	newItem.time = item.time;
	newItem.size = item.size;
	newItem.reserve = item.reserve;

    m_list.append(newItem);

    emit postItemAppended();
}

void CList::RemoveItem(int index)
{
	if (index >= 0 && m_list.size() > index)
	{
		emit preItemRemoved(index);

		m_list.removeAt(index);

		emit postItemRemoved();
	}
}

void CList::InsertItem(int index, Item item)
{
	emit preItemInserted(index);

	m_list.insert(index, item);
	
	emit postItemInserted();
}

Item CList::At(int index)
{
	return m_list.at(index);
}

int CList::Size()
{
	return m_list.size();
}
