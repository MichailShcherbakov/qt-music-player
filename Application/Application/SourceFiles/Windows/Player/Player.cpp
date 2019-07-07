#include "Player/Player.h"

Player::Player(QQmlContext* context, ImageProvider* imapeProvider, QQuickWindow* window) :
	IWindow(window, context, imapeProvider)
{

}

Player::~Player()
{
}

void Player::Initialize()
{
	RootContext()->setContextProperty(QStringLiteral("albumsModelList"), &m_listHorModel);

	RootImageProvider()->DeleteList();

	LoadNext(ENetworkState::GetTableMedia);
	LoadNext(ENetworkState::GetTableAlbums);
	LoadNext(ENetworkState::GetTableArtists);
	LoadNext(ENetworkState::GetTableGenres);

	m_networkListStates.append(ENetworkState::End);
}

void Player::GetFromSocket(QByteArray data)
{
	Query result;
	result.fromByteArray(data);

	ETypeResultQuery res = static_cast<ETypeResultQuery>(result.GetFromHeader("query-result").toInt());

	if (res == ETypeResultQuery::Success)
	{
		switch (m_networkListStates.first())
		{
		case ENetworkState::GetTableMedia:
		{
			GetMediaTable(result);
			emit onGotMediaTable();
			break;
		}
		case ENetworkState::GetTableArtists:
		{
			GetArtistsTable(result);
			emit onGotArtistsTable();
			break;
		}
		case ENetworkState::GetTableAlbums:
		{
			GetAlbumsTable(result);
			emit onGotAlbumsTable();
			break;
		}
		case ENetworkState::GetTableGenres:
		{
			GetGenresTable(result);
			emit onGotGenresTable();
			break;
		}
		case ENetworkState::GetArtCover:
		{
			GetArtCover(result);
			emit onGotArtCover();
			break;
		}
		case ENetworkState::GetMedia:
		{
			GetMedia(result);
			emit onGotMedia();
			break;
		}
		case ENetworkState::End:
		{
				temp = new Section(m_tables.m_mediaTable, m_tables.m_artistsTable, m_tables.m_genresTable, m_tables.m_albumsTable, &m_listHorModel, RootImageProvider());

				connect(temp, &Section::onSendToSocket, this, &Player::GetFromSection);
				connect(this, &Player::onSendToSection, temp, &Section::GetFromServer);

				temp->Initialize();
			
			break;
		}
		}
		m_networkListStates.removeFirst();
	}
}

void Player::LoadNext(ENetworkState state, Query query)
{
	m_networkListStates.append(state);

	switch (state)
	{
	case ENetworkState::GetTableMedia:
	{
		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
		query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Media));
		break;
	}
	case ENetworkState::GetTableAlbums:
	{
		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
		query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Albums));
		break;
	}
	case ENetworkState::GetTableArtists:
	{
		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
		query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Artists));
		break;
	}
	case ENetworkState::GetTableGenres:
	{
		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
		query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Genres));
		break;
	}
	case ENetworkState::GetArtCover:
	{
		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
		break;
	}
	case ENetworkState::GetMedia:
	{
		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Media));
		break;
	}
	}
	emit onSendToSocket(query.toByteArray());
}

void Player::GetFromSection(const QByteArray& data)
{
	Query t;
	t.fromByteArray(data);
	LoadNext(ENetworkState::GetArtCover, t);
}

void Player::GetMediaTable(Query data)
{
	QJsonArray table = data.GetFromBody("table").toArray();

	if (m_tables.m_mediaTable)
	{
		SAFE_DELETE(m_tables.m_mediaTable);
	}

	m_tables.m_mediaTable = new Table;

	m_tables.m_mediaTable->AddColumn("id_media");
	m_tables.m_mediaTable->AddColumn("title");
	m_tables.m_mediaTable->AddColumn("id_artist");
	m_tables.m_mediaTable->AddColumn("id_album");
	m_tables.m_mediaTable->AddColumn("year");
	m_tables.m_mediaTable->AddColumn("id_genre");
	m_tables.m_mediaTable->AddColumn("duraction");
	m_tables.m_mediaTable->AddColumn("bitrate");
	m_tables.m_mediaTable->AddColumn("add_time");

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
			m_tables.m_mediaTable->AddRow(rowMedia);
		}
	}
}

void Player::GetArtistsTable(Query data)
{
	QJsonArray table = data.GetFromBody("table").toArray();

	if (m_tables.m_artistsTable)
	{
		SAFE_DELETE(m_tables.m_artistsTable);
	}

	m_tables.m_artistsTable = new Table;

	m_tables.m_artistsTable->AddColumn("id_artist");
	m_tables.m_artistsTable->AddColumn("name");

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
			m_tables.m_artistsTable->AddRow(rowMedia);
		}
	}
}

void Player::GetAlbumsTable(Query data)
{
	QJsonArray table = data.GetFromBody("table").toArray();

	if (m_tables.m_albumsTable)
	{
		SAFE_DELETE(m_tables.m_albumsTable);
	}

	m_tables.m_albumsTable = new Table;

	m_tables.m_albumsTable->AddColumn("id_album");
	m_tables.m_albumsTable->AddColumn("title");

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
			m_tables.m_albumsTable->AddRow(rowMedia);
		}
	}
}

void Player::GetGenresTable(Query data)
{
	QJsonArray table = data.GetFromBody("table").toArray();

	if (m_tables.m_genresTable)
	{
		SAFE_DELETE(m_tables.m_genresTable);
	}

	m_tables.m_genresTable = new Table;

	m_tables.m_genresTable->AddColumn("id_genre");
	m_tables.m_genresTable->AddColumn("title");

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
			m_tables.m_genresTable->AddRow(rowMedia);
		}
	}
}

void Player::GetMedia(Query data)
{
	QByteArray t = data.GetFromBody("media").toVariant().toByteArray();
}

void Player::GetArtCover(Query data)
{
	QByteArray t = data.GetFromBody("cover-art").toVariant().toString().toLatin1();
	emit onSendToSection(t);
}