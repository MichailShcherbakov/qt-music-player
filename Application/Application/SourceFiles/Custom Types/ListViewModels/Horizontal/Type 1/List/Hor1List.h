#ifndef _LIST_HOR_TYPE_1_H_
#define _LIST_HOR_TYPE_1_H_

#include <QObject>
#include <QVector>
#include <QVariant>

namespace HorizontalModel1
{
	struct Item
	{
		int id;
		QString coverKey;
		QString textLineFirst;
		QString textLineSecond;
	};

	class List : public QObject
	{
		Q_OBJECT

	public:
		List(QObject* parent = Q_NULLPTR);
		List(const List& list);
		~List();

		QVector<Item> GetItems() const;
		bool SetItemAt(int index, const Item& item);

	signals:
		void preItemAppended();
		void postItemAppended();

		void preItemInserted(int index);
		void postItemInserted();

		void preItemRemoved(int index);
		void postItemRemoved();

	public slots:
		void AppendItem(Item item);
		void RemoveItem(int index);
		void InsertItem(int index, Item item);
		Item At(int index);

	public:
		int Size();
		void Clear();

	private:
		QVector <Item> m_list;

	};
}

#endif // CLIST_H
