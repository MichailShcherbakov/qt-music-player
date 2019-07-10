#ifndef _ISECTION_H_
#define _ISECTION_H_

#include "Tools/StdAfx.h"

#include <QObject>

#include "Table/Table.h"
#include "Tools/Query.h"
#include "ImageProvider/ImageProvider.h"
#include "Interfaces/IList.h"

enum class ENetworkState : int
{
	Unknown = 0,
	GetTableMedia,
	GetTableAlbums,
	GetTableArtists,
	GetTableGenres,
	GetArtCover,
	GetMedia,
};

class ISection : public QObject
{
	Q_OBJECT

public:
	ISection(ImageProvider* imageProvider) :
		m_pMediaTable(Q_NULLPTR),
		m_pArtistsTable(Q_NULLPTR),
		m_pGenresTable(Q_NULLPTR),
		m_pAlbumsTable(Q_NULLPTR),
		m_rootImageProvider(imageProvider)
	{}
	ISection(Table* m_mediaTable, 
		Table* m_artistsTable,
		Table* m_genresTable,
		Table* m_albumsTable,
		ImageProvider* imageProvider
	) :
		m_pMediaTable(m_mediaTable),
		m_pArtistsTable(m_artistsTable),
		m_pGenresTable(m_genresTable),
		m_pAlbumsTable(m_albumsTable),
		m_rootImageProvider(imageProvider)
	{}
	

public:
	virtual void Initialize() = 0;

public slots:
	inline void GetByteArray(QByteArray data) { emit onGetByteArray(data); }
	inline void GetTable(Table* table) { emit onGetTable(table); }

signals:
	void onGetByteArray(QByteArray data);
	void onGetTable(Table* table);
	void onSendQuery(ISection* section, ENetworkState type, Query query);

protected:
	Table* m_pMediaTable = Q_NULLPTR;
	Table* m_pArtistsTable = Q_NULLPTR;
	Table* m_pGenresTable = Q_NULLPTR;
	Table* m_pAlbumsTable = Q_NULLPTR;
	QList<ENetworkState> m_request;
	ImageProvider* m_rootImageProvider;
};

#endif