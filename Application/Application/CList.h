#ifndef CLIST_H
#define CLIST_H

#include <QObject>
#include <QVector>
#include <QVariant>

struct Item
{
	QString nameFile;
    QByteArray image;
    QString title;
    QString artist;
	QString album;
	QString genre;
	QString year;
	QString playlist;
    QString time;
    QString size;
    QVariant reserve;
};

class CList : public QObject
{
    Q_OBJECT

public:
    explicit CList(QObject* parent = nullptr);
    ~CList();

    QVector<Item> GetItems() const;
    bool SetItemAt(int index, const Item &item);

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

private:
    QVector <Item> m_list;

};

#endif // CLIST_H
