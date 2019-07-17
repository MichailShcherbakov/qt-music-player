#ifndef _MODEL_VER_TYPE_1_H_
#define _MODEL_VER_TYPE_1_H_

#include <QAbstractListModel>

#include "ListViewModels/Vertical/Type 1/List/Ver1List.h"

namespace VerticalModel1
{
	class List;

	class Model : public QAbstractListModel
	{
		Q_OBJECT

		Q_PROPERTY(List *list READ GetList WRITE SetList)

	public:
		explicit Model(QObject *parent = Q_NULLPTR);

		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		bool setData(const QModelIndex &index, const QVariant &value, int role) override;
		virtual QHash<int, QByteArray> roleNames() const override;

	public:
		List* GetList() const;
		void SetList(List* list);

	private:
		List* m_list;
		QList<QModelIndex> m_listID;
	};
}
#endif // CMODEL_H
