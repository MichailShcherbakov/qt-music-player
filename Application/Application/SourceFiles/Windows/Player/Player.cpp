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
	m_networkListStates.append(ENetworkState::GetTableMedia);

	LoadNext(ENetworkState::GetTableAlbums);
	m_networkListStates.append(ENetworkState::GetTableAlbums);

	LoadNext(ENetworkState::GetTableArtists);
	m_networkListStates.append(ENetworkState::GetTableArtists);

	LoadNext(ENetworkState::GetTableGenres);
	m_networkListStates.append(ENetworkState::GetTableGenres);

	connect(this, &Player::onGotGenresTable, this, &Player::InitializeScreen);
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
		}
		m_networkListStates.removeFirst();
	}
}

void Player::LoadNext(ENetworkState state, Query query)
{
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

void Player::GetMediaTable(Query data)
{
	QJsonArray table = data.GetFromBody("table").toArray();

	if (m_mediaTable)
	{
		SAFE_DELETE(m_mediaTable);
	}

	m_mediaTable = new Table;

	m_mediaTable->AddColumn("id_media");
	m_mediaTable->AddColumn("title");
	m_mediaTable->AddColumn("id_artist");
	m_mediaTable->AddColumn("id_album");
	m_mediaTable->AddColumn("year");
	m_mediaTable->AddColumn("id_genre");
	m_mediaTable->AddColumn("duraction");
	m_mediaTable->AddColumn("bitrate");
	m_mediaTable->AddColumn("add_time");

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
			m_mediaTable->AddRow(rowMedia);
		}
	}
}

void Player::GetArtistsTable(Query data)
{
	QJsonArray table = data.GetFromBody("table").toArray();

	if (m_artistsTable)
	{
		SAFE_DELETE(m_artistsTable);
	}

	m_artistsTable = new Table;

	m_artistsTable->AddColumn("id_artist");
	m_artistsTable->AddColumn("name");

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
			m_artistsTable->AddRow(rowMedia);
		}
	}
}

void Player::GetAlbumsTable(Query data)
{
	QJsonArray table = data.GetFromBody("table").toArray();

	if (m_albumsTable)
	{
		SAFE_DELETE(m_albumsTable);
	}

	m_albumsTable = new Table;

	m_albumsTable->AddColumn("id_album");
	m_albumsTable->AddColumn("title");

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
			m_albumsTable->AddRow(rowMedia);
		}
	}
}

void Player::GetGenresTable(Query data)
{
	QJsonArray table = data.GetFromBody("table").toArray();

	if (m_genresTable)
	{
		SAFE_DELETE(m_genresTable);
	}

	m_genresTable = new Table;

	m_genresTable->AddColumn("id_genre");
	m_genresTable->AddColumn("title");

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
			m_genresTable->AddRow(rowMedia);
		}
	}
}

void Player::GetMedia(Query data)
{
	QByteArray t = data.GetFromBody("media").toVariant().toByteArray();
}

void Player::GetArtCover(Query data)
{
	QByteArray t = data.GetFromBody("cover-art").toVariant().toByteArray();
}

void Player::InitializeScreen()
{
		QFile img("Resources/Icons/cover.jpg");
		img.open(QIODevice::ReadOnly);
		QByteArray arrayImg = img.readAll(); //"image://rootImageDirectory/x128/" + model.cover_key;
		img.close();

		QImage p;
		p.loadFromData(arrayImg, "JPG");

		RootImageProvider()->AppendImage(p, "default");

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
					item.textLineSecond = m_artistsTable->ValueAt("name", idArtist-1).toString();
					break;
				}
			}

			m_listHorModel.AppendItem(item);
		}

		/*Query query;
		query.InsertIntoHeader("id-album", m_genresTable->ValueAt("id_album", 0).toInt());
		LoadNext(ENetworkState::GetArtCover, query);*/
}

Q_INVOKABLE void Player::clicked()
{
	
}
