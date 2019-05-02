#include "cmodel.h"

CModel::CModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_list(nullptr)
{
}

int CModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_list->GetItems().size();
}

QVariant CModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const Item item = m_list->GetItems().at(index.row());

    switch (role)
    {
    case TEXT_NAMEFILE:
        return QVariant(item.nameFile); 
	case IMAGE:
        return QVariant(item.image);
    case TEXT_TITLE:
        return QVariant(item.title);
    case TEXT_ARTIST:
        return QVariant(item.artist);
    case TEXT_ALBUM:
        return QVariant(item.album);
	case TEXT_GENRE:
		return QVariant(item.genre);
	case TEXT_YEAR:
		return QVariant(item.year);
	case TEXT_PLAYLIST:
		return QVariant(item.playlist);
	case TEXT_TIME:
		return QVariant(item.time);
	case TEXT_SIZE:
		return QVariant(item.size);
	case RESERVE:
		return QVariant(item.reserve);
    }

    return QVariant();
}

bool CModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!m_list)
        return false;

    Item item = m_list->GetItems().at(index.row());

    switch (role)
    {
	case TEXT_NAMEFILE:
		item.nameFile = value.toString();
		break;
    case IMAGE:
        item.image = value.toByteArray();
        break;
    case TEXT_TITLE:
        item.title = value.toString();
        break;
    case TEXT_ARTIST:
        item.artist = value.toString();
        break;
    case TEXT_ALBUM:
        item.album = value.toString();
        break;
	case TEXT_GENRE:
		item.genre = value.toString();
		break;
	case TEXT_YEAR :
		item.year = value.toString();
		break;
	case TEXT_PLAYLIST:
		item.playlist = value.toString();
		break;
	case TEXT_TIME:
		item.time = value.toString();
		break;
	case TEXT_SIZE:
		item.size = value.toString();
		break;
	case RESERVE:
		item.reserve = value.toBool();
		break;

    }

    if (m_list->SetItemAt(index.row(), item))
    {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

QHash<int, QByteArray> CModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TEXT_NAMEFILE] = "namefile";
    names[IMAGE] = "image";
    names[TEXT_TITLE] = "title";
    names[TEXT_ARTIST] = "artist";
	names[TEXT_ALBUM] = "album";
	names[TEXT_GENRE] = "genre";
	names[TEXT_YEAR] = "year";
	names[TEXT_PLAYLIST] = "playlist";
    names[TEXT_TIME] = "time";
    names[TEXT_SIZE] = "size";
    names[RESERVE] = "reserve";
    return names;
}

CList* CModel::GetList() const
{
    return m_list;
}

void CModel::SetList(CList *list)
{
    beginResetModel();

    if (m_list)
        m_list->disconnect(this);

    m_list = list;

    if (m_list)
    {
        connect(m_list, &CList::preItemAppended, this, [=]()
        {
            const int index = m_list->GetItems().size();
            beginInsertRows(QModelIndex(), index, index);
        });

        connect(m_list, &CList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(m_list, &CList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(m_list, &CList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

		connect(m_list, &CList::preItemInserted, this, [=](int index) {
			beginInsertRows(QModelIndex(), index, index);
			});

		connect(m_list, &CList::postItemInserted, this, [=]() {
			endInsertRows();
			});
    }

    endResetModel();
}
