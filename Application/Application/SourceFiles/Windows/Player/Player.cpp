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
	MSG(ETypeMessage::Log, "Initialization");

	RootContext()->setContextProperty(QStringLiteral("albumsModelList"), &m_listHorModel);

	RootImageProvider()->DeleteList();

	connect(this, &Player::onLoad, this, &Player::Load);

	QFile img("Resources/Icons/cover.jpg");
	img.open(QIODevice::ReadOnly);
	QByteArray arrayImg = img.readAll();
	img.close();

	QImage p;
	p.loadFromData(arrayImg, "JPG");

	RootImageProvider()->AppendImage(p, "default");

	MSG(ETypeMessage::Log, "Sections Loading");

	m_hor1section = new HorizontalModel1::Section(&m_listHorModel, RootImageProvider());
	m_sections.append(m_hor1section);

	MSG(ETypeMessage::Log, "Set connections with sections");

	for (auto it : m_sections)
	{
		connect(it, &ISection::onSendQuery, this, &Player::GetFromSection);
		it->Initialize();
	}
}

void Player::GetFromSocket(QByteArray data)
{
	Query result;
	result.fromByteArray(data);

	ETypeResultQuery res = static_cast<ETypeResultQuery>(result.GetFromHeader("query-result").toInt());

	if (res == ETypeResultQuery::Success)
	{
		MSG(ETypeMessage::Log, "The query was done correctly");

		ISection* section = m_requests.first().first;
		SectionQuery query = m_requests.first().second;
		const char* signal;
		const char* slot;

		switch (query.first)
		{
		case ENetworkState::GetTableMedia:
		{
			GetMediaTable(result);
			signal = SIGNAL(onGotMediaTable(Table*));
			slot = SLOT(GetTable(Table*));

			for (auto it : m_requests)
			{
				ISection* s = it.first;
				SectionQuery q = it.second;

				if (q.first == query.first)
				{
					connect(this, signal, s, slot);
				}
			}

			emit onGotMediaTable(m_pMediaTable);
			break;
		}
		case ENetworkState::GetTableArtists:
		{
			GetArtistsTable(result);
			signal = SIGNAL(onGotArtistsTable(Table*));
			slot = SLOT(GetTable(Table*));

			for (auto it : m_requests)
			{
				ISection* s = it.first;
				SectionQuery q = it.second;

				if (q.first == query.first)
				{
					connect(this, signal, s, slot);
				}
			}

			emit onGotArtistsTable(m_pArtistsTable);
			break;
		}
		case ENetworkState::GetTableAlbums:
		{
			GetAlbumsTable(result);
			signal = SIGNAL(onGotAlbumsTable(Table*));
			slot = SLOT(GetTable(Table*));

			for (auto it : m_requests)
			{
				ISection* s = it.first;
				SectionQuery q = it.second;

				if (q.first == query.first)
				{
					connect(this, signal, s, slot);
				}
			}

			emit onGotAlbumsTable(m_pAlbumsTable);
			break;
		}
		case ENetworkState::GetTableGenres:
		{
			GetGenresTable(result);
			signal = SIGNAL(onGotGenresTable(Table*));
			slot = SLOT(GetTable(Table*));

			for (auto it : m_requests)
			{
				ISection* s = it.first;
				SectionQuery q = it.second;

				if (q.first == query.first)
				{
					connect(this, signal, s, slot);
				}
			}

			emit onGotGenresTable(m_pGenresTable);
			break;
		}
		case ENetworkState::GetArtCover:
		{
			GetArtCover(result);
			signal = SIGNAL(onGotArtCover(QByteArray));
			slot = SLOT(GetByteArray(QByteArray));
			
			connect(this, signal, section, slot);

			emit onGotArtCover(m_buffer);
			break;
		}
		case ENetworkState::GetMedia:
		{
			GetMedia(result);
			signal = SIGNAL(onGotMedia(QByteArray));
			slot = SLOT(GetByteArray(QByteArray));

			connect(this, signal, section, slot);

			emit onGotMedia(m_buffer);
			break;
		}
		default: 
		{
			MSG(ETypeMessage::Error, "Unknown network state");
			return;
		}
		}

		if (ENetworkState::GetArtCover != query.first && ENetworkState::GetMedia != query.first)
		{
			for (auto it : m_requests)
			{
				ISection* s = it.first;
				SectionQuery q = it.second;

				if (q.first == query.first)
				{
					disconnect(this, signal, s, slot);

					int id = m_requests.indexOf(it);
					m_requests.removeAt(id);
				}
			}
		}
		else
		{
			disconnect(this, signal, section, slot);
			m_requests.removeFirst();
		}
	}
	else
	{
		MSG(ETypeMessage::Error, "The query was not done");
	}
}

void Player::Load(const ENetworkState type, Query query)
{
	switch (type)
	{
	case ENetworkState::GetTableMedia:
	{
		MSG(ETypeMessage::Log, "The query for getting a table of media");

		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
		query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Media));
		break;
	}
	case ENetworkState::GetTableAlbums:
	{
		MSG(ETypeMessage::Log, "The query for getting a table of albums");

		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
		query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Albums));
		break;
	}
	case ENetworkState::GetTableArtists:
	{
		MSG(ETypeMessage::Log, "The query for getting a table of artists");

		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
		query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Artists));
		break;
	}
	case ENetworkState::GetTableGenres:
	{
		MSG(ETypeMessage::Log, "The query for getting a table of genres");

		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
		query.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Genres));
		break;
	}
	case ENetworkState::GetArtCover:
	{
		MSG(ETypeMessage::Log, "The query for getting a cover art");

		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Cover_Art));
		break;
	}
	case ENetworkState::GetMedia:
	{
		MSG(ETypeMessage::Log, "The query for getting a media");

		query.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Media));
		break;
	}
	default:
	{
		MSG(ETypeMessage::Error, "Unknown network state");
		return;
	}
	}

	emit onSendToSocket(query.toByteArray());
}

void Player::GetMediaTable(Query data)
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
	m_pMediaTable->AddColumn("duraction");
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

void Player::GetArtistsTable(Query data)
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

void Player::GetAlbumsTable(Query data)
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

void Player::GetGenresTable(Query data)
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

void Player::GetMedia(Query data)
{
	m_buffer.clear();
	m_buffer = data.GetFromBody("media").toVariant().toString().toLatin1();
}

void Player::GetArtCover(Query data)
{
	m_buffer.clear();
	m_buffer = data.GetFromBody("cover-art").toVariant().toString().toLatin1();
}

void Player::GetFromSection(ISection* section, ENetworkState type, Query query)
{
	MSG(ETypeMessage::Log, "The query was gave from the section");

	SectionQuery q;
	q.first = type;
	q.second = query;

	m_requests.append(QPair<ISection*, SectionQuery>(section, q));

	emit onLoad(type, query);
}

