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

enum class ETypeScreen : int
{
	Unknown = 0,
	Default,
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

private slots:
	void InitializeScreen();

private:
	Q_INVOKABLE void clicked();

signals:
	void onGotMediaTable();
	void onGotArtistsTable();
	void onGotAlbumsTable();
	void onGotGenresTable();
	void onGotArtCover();
	void onGotMedia();

private:
	Table* m_mediaTable = Q_NULLPTR;
	Table* m_artistsTable = Q_NULLPTR;
	Table* m_genresTable = Q_NULLPTR;
	Table* m_albumsTable = Q_NULLPTR;
	HorizontalModel1::List m_listHorModel;
	QList<ENetworkState> m_networkListStates;
};

#endif
