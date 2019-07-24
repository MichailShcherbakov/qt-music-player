#ifndef _ISECTION_LISTVIEW_H_
#define _ISECTION_LISTVIEW_H_

#include <QObject>

#include "ISection.h"


enum class ETypeLoad : int
{
	Unknown = 0,
	GetTableMedia,
	GetTableAlbums,
	GetTableArtists,
	GetTableGenres,
	GetArtCover,
	GetMedia
};

class ISectionListView : public ISection
{
	Q_OBJECT

public:
	ISectionListView( Socket* const socket) :
		ISection(socket)
	{
		connect(this, &INetwork::getFromSocket, this, &ISectionListView::ReadyRead);
		connect(this, &ISectionListView::gottenData, this, &ISectionListView::GottenData);
	}
	virtual ~ISectionListView() {}

public slots:
	virtual void Initialize() = 0;
	virtual void ReadyRead(QByteArray package) = 0;
	virtual void GottenData(QByteArray data) = 0;
	virtual void ClickedItem(int id) = 0;
	virtual void SetCurrentItem(int index) = 0;

public slots:
	Query GetLoadQuery() { return m_rootLoadQuery; }

protected:
	unsigned int m_localSize = 0;
	unsigned int m_fullSize = 0;
	const unsigned int m_sizeCacheBuffer = 16;
	Query m_rootLoadQuery;
};


/*
static_cast<int>(m_localSize
void GetMediaTable(Query data)
	{
		QJsonArray table = data.GetFromBody("table").toArray();

		if (m_pMediaTable)
		{
			SAFE_DELETE(m_pMediaTable);
		}

		m_pMediaTable = new Table;

		m_pMediaTable->AddColumn("id_media");
		m_pMediaTable->AddColumn("title");
		m_pMediaTable->AddColumn("id_artist");
		m_pMediaTable->AddColumn("id_album");
		m_pMediaTable->AddColumn("id_genre");
		m_pMediaTable->AddColumn("year");
		m_pMediaTable->AddColumn("duration");
		m_pMediaTable->AddColumn("bitrate");
		m_pMediaTable->AddColumn("add_time");
		m_pMediaTable->AddColumn("last_listened");
		m_pMediaTable->AddColumn("number_times_listened");
		m_pMediaTable->AddColumn("lyric");
		m_pMediaTable->AddColumn("lyrics_translation");

		if (!table.isEmpty())
		{
			for (auto row : table)
			{
				Row rowMedia;
				QJsonArray jsonRow = row.toArray();

				for (auto column : jsonRow)
				{
					QJsonObject obj = column.toObject();
					auto value = obj.constBegin();
					rowMedia.Append(*value);
				}
				m_pMediaTable->AddRow(rowMedia);
			}
		}
	}
	void GetMediaMergedTable(Query data)
	{
		QJsonArray table = data.GetFromBody("table").toArray();

		if (m_pMediaTable)
		{
			SAFE_DELETE(m_pMediaTable);
		}

		m_pMediaTable = new Table;

		m_pMediaTable->AddColumn("id_media");
		m_pMediaTable->AddColumn("title");
		m_pMediaTable->AddColumn("artist");
		m_pMediaTable->AddColumn("album");
		m_pMediaTable->AddColumn("genre");
		m_pMediaTable->AddColumn("year");
		m_pMediaTable->AddColumn("duration");
		m_pMediaTable->AddColumn("bitrate");
		m_pMediaTable->AddColumn("add_time");
		m_pMediaTable->AddColumn("last_listened");
		m_pMediaTable->AddColumn("number_times_listened");
		m_pMediaTable->AddColumn("lyric");
		m_pMediaTable->AddColumn("lyrics_translation");

		if (!table.isEmpty())
		{
			for (auto row : table)
			{
				Row rowMedia;
				QJsonArray jsonRow = row.toArray();

				for (auto column : jsonRow)
				{
					QJsonObject obj = column.toObject();
					auto value = obj.constBegin();
					rowMedia.Append(*value);
				}
				m_pMediaTable->AddRow(rowMedia);
			}
		}
	}
	void GetArtistsTable(Query data)
	{
		QJsonArray table = data.GetFromBody("table").toArray();

		if (m_pArtistsTable)
		{
			SAFE_DELETE(m_pArtistsTable);
		}

		m_pArtistsTable = new Table;

		m_pArtistsTable->AddColumn("id_artist");
		m_pArtistsTable->AddColumn("name");

		if (!table.isEmpty())
		{
			for (auto row : table)
			{
				Row rowMedia;
				QJsonArray jsonRow = row.toArray();

				for (auto column : jsonRow)
				{
					QJsonObject obj = column.toObject();
					auto value = obj.constBegin();
					rowMedia.Append(*value);
				}
				m_pArtistsTable->AddRow(rowMedia);
			}
		}
	}
	void GetAlbumsTable(Query data)
	{
		QJsonArray table = data.GetFromBody("table").toArray();

		if (m_pAlbumsTable)
		{
			SAFE_DELETE(m_pAlbumsTable);
		}

		m_pAlbumsTable = new Table;

		m_pAlbumsTable->AddColumn("id_album");
		m_pAlbumsTable->AddColumn("title");
		m_pAlbumsTable->AddColumn("add_time");
		m_pAlbumsTable->AddColumn("last_listened");
		m_pAlbumsTable->AddColumn("number_times_listened");

		if (!table.isEmpty())
		{
			for (auto row : table)
			{
				Row rowMedia;
				QJsonArray jsonRow = row.toArray();

				for (auto column : jsonRow)
				{
					QJsonObject obj = column.toObject();
					auto value = obj.constBegin();
					rowMedia.Append(*value);
				}
				m_pAlbumsTable->AddRow(rowMedia);
			}
		}
	}
	void GetGenresTable(Query data)
	{
		QJsonArray table = data.GetFromBody("table").toArray();

		if (m_pGenresTable)
		{
			SAFE_DELETE(m_pGenresTable);
		}

		m_pGenresTable = new Table;

		m_pGenresTable->AddColumn("id_genre");
		m_pGenresTable->AddColumn("title");

		if (!table.isEmpty())
		{
			for (auto row : table)
			{
				Row rowMedia;
				QJsonArray jsonRow = row.toArray();

				for (auto column : jsonRow)
				{
					QJsonObject obj = column.toObject();
					auto value = obj.constBegin();
					rowMedia.Append(*value);
				}
				m_pGenresTable->AddRow(rowMedia);
			}
		}
	}

void Load(const ETypeLoad type, Query query)
	{
		switch (type)
		{
		case ETypeLoad::GetTableMedia:
		{
			MSG(ETypeMessage::Log, "The query for getting a table of media");

			query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
			query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Media));
			break;
		}
		case ETypeLoad::GetTableAlbums:
		{
			MSG(ETypeMessage::Log, "The query for getting a table of albums");

			query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
			query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Albums));
			break;
		}
		case ETypeLoad::GetTableArtists:
		{
			MSG(ETypeMessage::Log, "The query for getting a table of artists");

			query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
			query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Artists));
			break;
		}
		case ETypeLoad::GetTableGenres:
		{
			MSG(ETypeMessage::Log, "The query for getting a table of genres");

			query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
			query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Genres));
			break;
		}
		case ETypeLoad::GetArtCover:
		{
			MSG(ETypeMessage::Log, "The query for getting a cover art");

			query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
			break;
		}
		case ETypeLoad::GetMedia:
		{
			MSG(ETypeMessage::Log, "The query for getting a media");

			query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Media));
			break;
		}
		default:
		{
			MSG(ETypeMessage::Error, "Unknown type load");
			return;
		}
		}
		emit onSendToSocket(this, query.toByteArray());
	}
*/

#endif