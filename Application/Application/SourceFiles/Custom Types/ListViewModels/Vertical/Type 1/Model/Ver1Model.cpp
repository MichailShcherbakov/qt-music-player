#include "StdAfx.h"
#include "Ver1Model.h"

using namespace VerticalModel1;

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
	case List::ID:
        return QVariant(item.id); 
	case List::COVER_KEY:
        return QVariant(item.coverKey);
    case List::TEXT_LINE_FIRST:
        return QVariant(item.textLineFirst);
    case List::TEXT_LINE_SECOND:
        return QVariant(item.textLineSecond);
	case List::TEXT_LINE_THIRD:
        return QVariant(item.textLineThird);
	case List::TEXT_LINE_FOUTH:
		return QVariant(item.textLineFourth);
	case List::EXPRESSION:
		return QVariant(item.expression);
	case List::EXPRESSION2:
		return QVariant(item.expression2);
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
	case List::ID:
		item.id = value.toInt();
		break;
    case List::COVER_KEY:
        item.coverKey = value.toString();
        break;
    case List::TEXT_LINE_FIRST:
        item.textLineFirst = value.toString();
        break;
    case List::TEXT_LINE_SECOND:
        item.textLineSecond = value.toString();
		break;
	case List::TEXT_LINE_THIRD:
        item.textLineThird = value.toString();
		break;
	case List::TEXT_LINE_FOUTH:
        item.textLineThird = value.toString();
		break;
	case List::EXPRESSION:
        item.expression = value.toBool();
        break;
	case List::EXPRESSION2:
        item.expression2 = value.toBool();
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
    names[List::ID] = "id";
    names[List::COVER_KEY] = "cover_key";
    names[List::TEXT_LINE_FIRST] = "text_line_first";
    names[List::TEXT_LINE_SECOND] = "text_line_second";
    names[List::TEXT_LINE_THIRD] = "text_line_third";
    names[List::TEXT_LINE_FOUTH] = "text_line_fourth";
    names[List::EXPRESSION] = "expression";
    names[List::EXPRESSION2] = "expression2";
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
		connect(m_list, &List::ItemChanged, this, [=](int id, QVariant value, int role) {
			setData(index(id, 0, QModelIndex()), value, role);
		});
    }

    endResetModel();
}
