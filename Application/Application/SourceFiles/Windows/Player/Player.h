#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Tools/StdAfx.h"

#include "Interfaces/IWindow.h"

#include "ListViewModels/Horizontal/Type 1/Section/Section.h"

typedef QPair<ENetworkState, Query> SectionQuery;

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
	void GetMediaTable(Query data);
	void GetArtistsTable(Query data);
	void GetAlbumsTable(Query data);
	void GetGenresTable(Query data);
	void GetMedia(Query data);
	void GetArtCover(Query data);

public slots:
	void Load(const ENetworkState type, Query query);
	void GetFromSection(ISection* section, ENetworkState type, Query query);

signals:
	void onLoad(const ENetworkState type, Query query);
	void onGotMediaTable(Table* table);
	void onGotArtistsTable(Table* table);
	void onGotAlbumsTable(Table* table);
	void onGotGenresTable(Table* table);
	void onGotArtCover(QByteArray data);
	void onGotMedia(QByteArray data);

private:
	QByteArray m_buffer;
	QList<ISection*> m_sections;
	QList< QPair<ISection*, SectionQuery> > m_requests;
	bool m_isHaveTables = false;
	bool m_isGotQuery = false;
	// Tables
	Table* m_pMediaTable = Q_NULLPTR;
	Table* m_pArtistsTable = Q_NULLPTR;
	Table* m_pGenresTable = Q_NULLPTR;
	Table* m_pAlbumsTable = Q_NULLPTR;
	// Models
	HorizontalModel1::List m_listHorModel;
	// Sections
	HorizontalModel1::Section* m_hor1section;
};

#endif
