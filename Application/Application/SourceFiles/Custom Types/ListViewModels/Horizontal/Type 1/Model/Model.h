#ifndef _MODEL_H_
#define _MODEL_H_

#include <QAbstractListModel>

#include "ListViewModels/Horizontal/Type 1/List/List.h"

namespace HorizontalModel1
{
	class List;

	class Model : public QAbstractListModel
	{
		Q_OBJECT

		Q_PROPERTY(List *list READ GetList WRITE SetList)

	public:
		explicit Model(QObject *parent = nullptr);

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


		List* GetList() const;
		void SetList(List* list);

	private:
		List* m_list;
	};
}
#endif // CMODEL_H
