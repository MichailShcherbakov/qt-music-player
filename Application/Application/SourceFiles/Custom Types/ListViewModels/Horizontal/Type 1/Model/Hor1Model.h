#ifndef _MODEL_HOR_TYPE_1_H_
#define _MODEL_HOR_TYPE_1_H_

#include <QAbstractListModel>

#include "ListViewModels/Horizontal/Type 1/List/Hor1List.h"

namespace HorizontalModel1
{
	class List;

	class Model : public QAbstractListModel
	{
		Q_OBJECT

		Q_PROPERTY(List *list READ GetList WRITE SetList)

	public:
		explicit Model(QObject *parent = Q_NULLPTR);

		enum
		{
			ID = Qt::UserRole,
			COVER_KEY,
			TEXT_LINE_FIRST,
			TEXT_LINE_SECOND,
		};

		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		bool setData(const QModelIndex &index, const QVariant &value, int role) override;
		virtual QHash<int, QByteArray> roleNames() const override;

	public:
		List* GetList() const;
		void SetList(List* list);

	private:
		List* m_list;
	};
}
#endif // CMODEL_H
