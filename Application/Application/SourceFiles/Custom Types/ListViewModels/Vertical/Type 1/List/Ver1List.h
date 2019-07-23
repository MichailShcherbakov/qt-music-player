#ifndef _LIST_VER_TYPE_1_H_
#define _LIST_VER_TYPE_1_H_

#include <QObject>
#include <QVector>
#include <QVariant>

namespace VerticalModel1
{
	struct Item
	{
		int id;
		QString coverKey;
		QString textLineFirst;
		QString textLineSecond;
		QString textLineThird;
		QString textLineFourth;
		bool expression;
		bool expression2;
	};

	class List : public QObject
	{
		Q_OBJECT

	public:
		List(QObject* parent = Q_NULLPTR);
		List(const List& list);
		~List();

		enum
		{
			ID = Qt::UserRole,
			COVER_KEY,
			TEXT_LINE_FIRST,
			TEXT_LINE_SECOND,
			TEXT_LINE_THIRD,
			TEXT_LINE_FOUTH,
			EXPRESSION,
			EXPRESSION2,
		};

		QVector<Item> GetItems() const;
		bool SetItemAt(int index, const Item& item);
		void SetValueItemAt(int index, const QVariant& value, int role);

	signals:
		void preItemAppended();
		void postItemAppended();

		void preItemInserted(int index);
		void postItemInserted();

		void preItemRemoved(int index);
		void postItemRemoved();

		void Clear(int index, int count);
		void ItemChanged(int id, QVariant value, int role);

	public slots:
		void AppendItem(Item item);
		void RemoveItem(int index);
		void InsertItem(int index, Item item);
		Item At(int index);

	public:
		int Size();
		bool isEmpty();
		void ClearList();

	private:
		QVector <Item> m_list;
	};
}

#endif // CLIST_H
