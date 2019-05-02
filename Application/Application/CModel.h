#ifndef CMODEL_H
#define CMODEL_H

#include <QAbstractListModel>

#include "CList.h"

class CList;

class CModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(CList *list READ GetList WRITE SetList)

public:
    explicit CModel(QObject *parent = nullptr);

    enum
    {
		TEXT_NAMEFILE = Qt::UserRole,
        IMAGE,
        TEXT_TITLE,
        TEXT_ARTIST,
		TEXT_ALBUM,
		TEXT_GENRE,
		TEXT_YEAR,
		TEXT_PLAYLIST,
        TEXT_TIME,
        TEXT_SIZE,
        RESERVE,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    virtual QHash<int, QByteArray> roleNames() const override;


    CList* GetList() const;
    void SetList(CList* list);

private:
    CList* m_list;
};

#endif // CMODEL_H
