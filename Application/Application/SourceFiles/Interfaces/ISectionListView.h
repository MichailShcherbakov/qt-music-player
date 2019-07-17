#ifndef _ISECTION__LISTVIEW_H_
#define _ISECTION__LISTVIEW_H_

#include "StdAfx.h"

#include <QObject>

#include "Table/Table.h"
#include "Tools/Query.h"
#include "EParams.h"
#include "Interfaces/INetworkManager.h"
#include "ImageProvider/ImageProvider.h"

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

class ISectionListView : public INetworkManager
{
	Q_OBJECT

public:
	ISectionListView(
		const EParams* const pParams,
		Table* pMediaTable,
		Table* pArtistsTable,
		Table* pGenresTable,
		Table* pAlbumsTable
	) :
		INetworkManager(pParams->m_pSocket),
		m_pRootImageProvider(pParams->m_pRootImageProvider),
		m_pMediaTable(pMediaTable),
		m_pArtistsTable(pArtistsTable),
		m_pGenresTable(pGenresTable),
		m_pAlbumsTable(pAlbumsTable)
	{
		connect(this, &INetwork::onGetFromSocket, this, &ISectionListView::ReadyRead);
		connect(this, &ISectionListView::onGottenData, this, &ISectionListView::GottenData);
		connect(this, &INetwork::onLoaded, this, [=]() {
			QByteArray t = m_pBuffer;
			m_pBuffer.clear();
			emit onGottenData(t);
			});
	}

	virtual ~ISectionListView() {}

signals:
	void onGottenData(const QByteArray data);
	void onFirstIndex(int id);
	void onEndIndex(int id);
	void onNextIndex(int id);
	void onPreviousIndex(int id);

public slots:
	virtual void Initialize() = 0;
	virtual void ReadyRead(QByteArray package) = 0;
	virtual void GottenData(QByteArray data) = 0;
	virtual void ClickedItem(int id) = 0;
	virtual void FirstIndex() = 0;
	virtual void EndIndex() = 0;
	virtual void NextIndex(int id) = 0;
	virtual void PreviousIndex(int id) = 0;

public:
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
		m_pMediaTable->AddColumn("year");
		m_pMediaTable->AddColumn("id_genre");
		m_pMediaTable->AddColumn("duration");
		m_pMediaTable->AddColumn("bitrate");
		m_pMediaTable->AddColumn("add_time");

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

protected:
	Table* m_pMediaTable = Q_NULLPTR;
	Table* m_pArtistsTable = Q_NULLPTR;
	Table* m_pGenresTable = Q_NULLPTR;
	Table* m_pAlbumsTable = Q_NULLPTR;
	ImageProvider* m_pRootImageProvider;
	EParams* m_pParams;
};

#endif