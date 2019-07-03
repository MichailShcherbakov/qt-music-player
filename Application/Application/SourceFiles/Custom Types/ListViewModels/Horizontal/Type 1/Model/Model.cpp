#include "ListViewModels/Horizontal/Type 1/Model/Model.h"

using namespace HorizontalModel1;

Model::Model(QObject *parent)
    : QAbstractListModel(parent)
    , m_list(nullptr)
{
}

int Model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_list->GetItems().size();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const Item item = m_list->GetItems().at(index.row());

    switch (role)
    {
    case ID:
        return QVariant(item.id); 
	case COVER_KEY:
        return QVariant(item.coverKey);
    case TEXT_LINE_FIRST:
        return QVariant(item.textLineFirst);
    case TEXT_LINE_SECOND:
        return QVariant(item.textLineSecond);
    }

    return QVariant();
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!m_list)
        return false;

    Item item = m_list->GetItems().at(index.row());

    switch (role)
    {
	case ID:
		item.id = value.toInt();
		break;
    case COVER_KEY:
        item.coverKey = value.toString();
        break;
    case TEXT_LINE_FIRST:
        item.textLineFirst = value.toString();
        break;
    case TEXT_LINE_SECOND:
        item.textLineSecond = value.toString();
        break;
    }

    if (m_list->SetItemAt(index.row(), item))
    {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ID] = "id";
    names[COVER_KEY] = "cover_key";
    names[TEXT_LINE_FIRST] = "text_line_first";
    names[TEXT_LINE_SECOND] = "text_line_second";
    return names;
}

List* Model::GetList() const
{
    return m_list;
}

void Model::SetList(List *list)
{
    beginResetModel();

    if (m_list)
        m_list->disconnect(this);

    m_list = list;

    if (m_list)
    {
        connect(m_list, &List::preItemAppended, this, [=]()
        {
            const int index = m_list->GetItems().size();
            beginInsertRows(QModelIndex(), index, index);
        });

        connect(m_list, &List::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(m_list, &List::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(m_list, &List::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

		connect(m_list, &List::preItemInserted, this, [=](int index) {
			beginInsertRows(QModelIndex(), index, index);
			});

		connect(m_list, &List::postItemInserted, this, [=]() {
			endInsertRows();
			});
    }

    endResetModel();
}
