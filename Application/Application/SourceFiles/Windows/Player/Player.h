#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Tools/StdAfx.h"

#include "Interfaces/IWindow.h"
#include "Tools/Table/Table.h"
#include "ListViewModels/Horizontal/Type 1/Model/Model.h"

enum class ENetworkState : int
{
	Unknown = 0,
	GetTableMedia,
	GetTableAlbums,
	GetTableArtists,
	GetTableGenres,
	GetArtCover,
	GetMedia,
	End,
};

class Section : public QObject
{
	Q_OBJECT

public:
	Section(Table* m_mediaTable,
		Table* m_artistsTable,
		Table* m_genresTable,
		Table* m_albumsTable,
		HorizontalModel1::List* m_listHorModel,
		ImageProvider* imageProvider)
		:
		m_mediaTable(m_mediaTable),
		m_artistsTable(m_artistsTable),
		m_genresTable(m_genresTable),
		m_albumsTable(m_albumsTable),
		m_rootImageProvider(imageProvider),
		m_listHorModel(m_listHorModel)
	{}
	~Section() {}

public:
	void Initialize() 
	{
		QFile img("Resources/Icons/cover.jpg");
		img.open(QIODevice::ReadOnly);
		QByteArray arrayImg = img.readAll();
		img.close();

		QImage p;
		p.loadFromData(arrayImg, "JPG");

		m_rootImageProvider->AppendImage(p, "default");

		for (int i = 0; i < m_albumsTable->Rows(); ++i)
		{
			HorizontalModel1::Item item;
			item.id = i;
			item.coverKey = "default";
			item.textLineFirst = m_albumsTable->ValueAt("title", i).toString();

			for (int j = 0; j < m_mediaTable->Rows(); ++j)
			{
				if (m_mediaTable->ValueAt("id_album", j).toInt() == m_albumsTable->ValueAt("id_album", i).toInt())
				{
					int idArtist = m_mediaTable->ValueAt("id_artist", j).toInt();
					item.textLineSecond = m_artistsTable->ValueAt("name", idArtist - 1).toString();
					break;
				}
			}

			m_listHorModel->AppendItem(item);
		}

		Query query;
		query.InsertIntoBody("id-album", m_genresTable->ValueAt("id_album", m_current_item).toInt() + 1);
		emit onSendToSocket(query.toByteArray());
	}

public slots:
	void GetFromServer(QByteArray data)
	{
		QImage p;
		p.loadFromData(data, "JPG");

		m_rootImageProvider->AppendImage(p, QString::number(m_rootImageProvider->SafeId()));

		if (m_current_item < m_albumsTable->Rows())
		{
			Query query;
			query.InsertIntoBody("id-album", m_genresTable->ValueAt("id_album", ++m_current_item).toInt() + 1);
			emit onSendToSocket(query.toByteArray());
		}
	}

signals:
	void onSendToSocket(const QByteArray& data);

private:
	int m_current_item = 0;
	Table* m_mediaTable = Q_NULLPTR;
	Table* m_artistsTable = Q_NULLPTR;
	Table* m_genresTable = Q_NULLPTR;
	Table* m_albumsTable = Q_NULLPTR;
	HorizontalModel1::List* m_listHorModel;
	ImageProvider* m_rootImageProvider;
};



















struct Tables
{
	Table* m_mediaTable = Q_NULLPTR;
	Table* m_artistsTable = Q_NULLPTR;
	Table* m_genresTable = Q_NULLPTR;
	Table* m_albumsTable = Q_NULLPTR;
};






class Player : public IWindow
{
	Q_OBJECT

public:
	Player(QQmlContext* context, ImageProvider* imageProvider, QQuickWindow* window = Q_NULLPTR);
	virtual ~Player();

public:
	// IWindow
	virtual void Initialize() override;
	virtual void GetFromSocket(QByteArray data) override;
	// ~IWindow

private:
	void LoadNext(ENetworkState state, Query query = Query());
	void GetMediaTable(Query data);
	void GetArtistsTable(Query data);
	void GetAlbumsTable(Query data);
	void GetGenresTable(Query data);
	void GetMedia(Query data);
	void GetArtCover(Query data);

public slots:
	void GetFromSection(const QByteArray& data);

signals:
	void onSendToSection(const QByteArray& data);
	void onGotMediaTable();
	void onGotArtistsTable();
	void onGotAlbumsTable();
	void onGotGenresTable();
	void onGotArtCover();
	void onGotMedia();

private:
	Tables m_tables;
	HorizontalModel1::List m_listHorModel;
	QList<ENetworkState> m_networkListStates;
	Section* temp;
};

#endif
