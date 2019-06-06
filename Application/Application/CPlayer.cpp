#include "cplayer.h"



CPlayer::CPlayer(QQuickWindow* window, CQuery* query, CList* list, CImageProvider* imageProvider) :
	IWindow(window, query),
	m_list(list),
	m_buffer(nullptr),
	m_player(nullptr),
	m_current_media_loadding(0),
	m_playMode(EPlayMode::SEQUENTIAL),
	m_stateNetwork(EStateNetwork::WAITING),
	m_statePlayer(EStatePlayer::Pause),
	m_current_media(0),
	m_imageProvider(imageProvider)
{
}

CPlayer::~CPlayer()
{
	delete m_list, m_imageProvider, m_buffer, m_player;
}

void CPlayer::Initialize()
{
	m_player = new QMediaPlayer(this);

	connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &CPlayer::MediaStatusChanged);
	connect(m_player, &QMediaPlayer::positionChanged, this, &CPlayer::positionChanged);
	connect(m_player, &QMediaPlayer::durationChanged, this, &CPlayer::mediaChanged);

	m_query->NewQuery(EQuery::GET_TABLE, ETable::All_Media);
	m_stateNetwork = EStateNetwork::Initialize_All_Media;
	m_updateList = ETypeList::Main;
	emit sendToSocket(m_query->toByteArray());

	m_query->NewQuery(EQuery::GET_TABLE, ETable::All_Albums);
	m_stateNetwork = EStateNetwork::Initialize_All_Albums;
	emit sendToSocket(m_query->toByteArray());

	m_query->NewQuery(EQuery::GET_TABLE, ETable::All_Genres);
	m_stateNetwork = EStateNetwork::Initialize_All_Genres;
	emit sendToSocket(m_query->toByteArray());

	m_query->NewQuery(EQuery::GET_TABLE, ETable::All_Artists);
	m_stateNetwork = EStateNetwork::Initialize_All_Artists;
	emit sendToSocket(m_query->toByteArray());

	UpDateList(m_updateList);
}

void CPlayer::MediaStatusChanged(QMediaPlayer::MediaStatus status)
{
	if (status == QMediaPlayer::EndOfMedia)
	{
		switch (m_playMode)
		{
		case EPlayMode::SEQUENTIAL:
		{
			if (m_current_media < m_list->Size() - 1)
			{
				++m_current_media;
				PlayMedia();
			}
			else
			{
				m_player->pause();
				m_statePlayer = EStatePlayer::Pause;
				emit changeImagePlayButton("qrc:/Images/play.svg");
			}
			break;
		}
		case EPlayMode::LOOP:
		{
			if (m_current_media < m_list->Size() - 1)
				++m_current_media;
			else
				m_current_media = 0;
			PlayMedia();
			break;
		}
		case EPlayMode::CURRENT_ITEM_IN_LOOP:
		{
			m_player->play();
			break;
		}
		}
	}
}

void CPlayer::getFromSocket(QByteArray* data)
{
	switch (m_stateNetwork)
	{
	case EStateNetwork::Initialize_All_Media:
	{
		m_listMedia = new CTable;

		m_listMedia->AddColumn("id");
		m_listMedia->AddColumn("title");
		m_listMedia->AddColumn("id_artist");
		m_listMedia->AddColumn("id_album");
		m_listMedia->AddColumn("year");
		m_listMedia->AddColumn("id_genre");
		m_listMedia->AddColumn("duraction");
		m_listMedia->AddColumn("bitrate");
		m_listMedia->AddColumn("add_time");

		int columns = 0;
		int rows = 0;

		for (int i = 0, k = 0; i < data->size(); ++i)
		{
			if (data->at(i) == '[')
			{
				QString temp;
				++i;
				while (i < data->size() && data->at(i) != ']')
				{
					temp += data->at(i++);
				}
				if (k == 0)
				{
					columns = temp.toInt();
					++k;
				}
				else
				{
					rows = temp.toInt();
					data->remove(0, ++i);
					break;
				}
			}
		}

		for (int i = 0, k = 0; i < rows; ++i)
		{
			Row row;
			for (int j = 0; j < columns; ++j, ++k)
			{
				if (data->at(k) == '[')
				{
					QString temp;
					++k;
					while (k < data->size() && data->at(k) != ']')
					{
						temp += data->at(k++);
					}
					row.Append(temp);
				}
			}
			m_listMedia->AddRow(row);
		}
		break;
	}
	case EStateNetwork::Initialize_All_Albums:
	{
		m_listAlbums = new CTable;

		m_listAlbums->AddColumn("id_album");
		m_listAlbums->AddColumn("title");

		int columns = 0;
		int rows = 0;

		for (int i = 0, k = 0; i < data->size(); ++i)
		{
			if (data->at(i) == '[')
			{
				QString temp;
				++i;
				while (i < data->size() && data->at(i) != ']')
				{
					temp += data->at(i++);
				}
				if (k == 0)
				{
					columns = temp.toInt();
					++k;
				}
				else
				{
					rows = temp.toInt();
					data->remove(0, ++i);
					break;
				}
			}
		}

		for (int i = 0, k = 0; i < rows; ++i)
		{
			Row row;
			for (int j = 0; j < columns; ++j, ++k)
			{
				if (data->at(k) == '[')
				{
					QString temp;
					++k;
					while (k < data->size() && data->at(k) != ']')
					{
						temp += data->at(k++);
					}
					row.Append(temp);
				}
			}
			m_listAlbums->AddRow(row);
		}
		break;
	}
	case EStateNetwork::Initialize_All_Genres:
	{
		m_listGenres = new CTable;

		m_listGenres->AddColumn("id_genre");
		m_listGenres->AddColumn("title");

		int columns = 0;
		int rows = 0;

		for (int i = 0, k = 0; i < data->size(); ++i)
		{
			if (data->at(i) == '[')
			{
				QString temp;
				++i;
				while (i < data->size() && data->at(i) != ']')
				{
					temp += data->at(i++);
				}
				if (k == 0)
				{
					columns = temp.toInt();
					++k;
				}
				else
				{
					rows = temp.toInt();
					data->remove(0, ++i);
					break;
				}
			}
		}

		for (int i = 0, k = 0; i < rows; ++i)
		{
			Row row;
			for (int j = 0; j < columns; ++j, ++k)
			{
				if (data->at(k) == '[')
				{
					QString temp;
					++k;
					while (k < data->size() && data->at(k) != ']')
					{
						temp += data->at(k++);
					}
					row.Append(temp);
				}
			}
			m_listGenres->AddRow(row);
		}
		break;
	}
	case EStateNetwork::Initialize_All_Artists:
	{
		m_listArtists = new CTable;

		m_listArtists->AddColumn("id_artist");
		m_listArtists->AddColumn("name");

		int columns = 0;
		int rows = 0;

		for (int i = 0, k = 0; i < data->size(); ++i)
		{
			if (data->at(i) == '[')
			{
				QString temp;
				++i;
				while (i < data->size() && data->at(i) != ']')
				{
					temp += data->at(i++);
				}
				if (k == 0)
				{
					columns = temp.toInt();
					++k;
				}
				else
				{
					rows = temp.toInt();
					data->remove(0, ++i);
					break;
				}
			}
		}

		for (int i = 0, k = 0; i < rows; ++i)
		{
			Row row;
			for (int j = 0; j < columns; ++j, ++k)
			{
				if (data->at(k) == '[')
				{
					QString temp;
					++k;
					while (k < data->size() && data->at(k) != ']')
					{
						temp += data->at(k++);
					}
					row.Append(temp);
				}
			}
			m_listArtists->AddRow(row);
		}
		break;
	}
	case EStateNetwork::GETTING_NEEDED_MUSIC:
	{
		break;
	}
	case EStateNetwork::GETTING_NEEDED_IMAGE:
	{
		/*QImage p;
		p.loadFromData(*data, "JPG");

		m_imageProvider->AppendImage(p, QString::number(m_current_media_loadding));

		//m_list->AppendItem("", QString::number(m_current_media_loadding), m_table->GetTable()->at(1).at(m_current_media_loadding), m_table->GetTable()->at(2).at(m_current_media_loadding), "", "", "","","");
		++m_current_media_loadding;
		m_stateNetwork = EStateNetwork::INITIALIZE_ALL_MUSIC;
		this->getFromSocket(nullptr);*/
		break;
	}
	}
	SAFE_DELETE(data);
}

void CPlayer::getFromDialog(CTable table)
{
}

Q_INVOKABLE void CPlayer::button_play()
{
	switch (m_statePlayer)
	{
	case EStatePlayer::Pause:
	{
		m_player->play();
		m_statePlayer = EStatePlayer::Play;
		emit changeImagePlayButton("qrc:/Images/pause.svg");
		break;
	}
	case EStatePlayer::Play:
	{
		m_player->pause();
		m_statePlayer = EStatePlayer::Pause;
		emit changeImagePlayButton("qrc:/Images/play.svg");
		break;
	}
	}
}

Q_INVOKABLE void CPlayer::button_next()
{
	switch (m_playMode)
	{
	case EPlayMode::SEQUENTIAL:
	{
		if (m_current_media < m_list->Size() - 1)
		{
			++m_current_media;
			PlayMedia();
		}
		else
		{
			m_player->pause();
			m_statePlayer = EStatePlayer::Pause;
			emit changeImagePlayButton("qrc:/Images/play.svg");
		}
		break;
	}
	case EPlayMode::LOOP:
	{
		if (m_current_media < m_list->Size() - 1)
			++m_current_media;
		else
			m_current_media = 0;
		PlayMedia();
		break;
	}
	case EPlayMode::CURRENT_ITEM_IN_LOOP:
	{
		if (m_current_media < m_list->Size() - 1)
		{
			++m_current_media;
			PlayMedia();
		}
		else 
		{
			m_player->pause();
			m_statePlayer = EStatePlayer::Pause;
			emit changeImagePlayButton("qrc:/Images/play.svg");
		}
		break;
	}
	}
}

Q_INVOKABLE void CPlayer::button_back()
{
	switch (m_playMode)
	{
	case EPlayMode::SEQUENTIAL:
	{
		if (m_current_media > 0)
		{
			--m_current_media;
			PlayMedia();
		}
		else
		{
			m_player->pause();
			m_statePlayer = EStatePlayer::Pause;
			emit changeImagePlayButton("qrc:/Images/play.svg");
		}
		break;
	}
	case EPlayMode::LOOP:
	{
		if (m_current_media > 0)
			--m_current_media;
		else
			m_current_media = m_list->Size() - 1;
		PlayMedia();
		break;
	}
	case EPlayMode::CURRENT_ITEM_IN_LOOP:
	{
		if (m_current_media > 0)
		{
			--m_current_media;
			PlayMedia();
		}
		else
		{
			m_player->pause();
			m_statePlayer = EStatePlayer::Pause;
			emit changeImagePlayButton("qrc:/Images/play.svg");
		}
		break;
	}
	}
}

Q_INVOKABLE void CPlayer::button_local_files()
{
	emit openDialog(EDialogType::File);
}

Q_INVOKABLE void CPlayer::positionChanging(qint64 pos)
{
	m_player->setPosition(pos);
}

Q_INVOKABLE void CPlayer::list_view(QString author, QString title)
{
	/*m_query->NewQuery(m_query->GET_MEDIA, title, author);
	emit sendToSocket(m_query->toByteArray());

	m_current_media = m_table->Find(1, title, 2, author);

	m_stateNetwork = EStateNetwork::GETTING_NEEDED_MUSIC;*/
}

void CPlayer::PlayMedia()
{
	/*m_query->NewQuery(m_query->GET_MEDIA, m_table->GetTable()->at(1).at(m_current_media+3), m_table->GetTable()->at(2).at(m_current_media));
	emit sendToSocket(m_query->toByteArray());*/
}

void CPlayer::UpDateList(ETypeList type)
{
	switch (type)
	{
	case ETypeList::Main:
	{
		/* Cover Arts */
		QString path = QGuiApplication::applicationDirPath();
		for (int i = path.length() - 1, k = 0; 0 < i; --i)
			if (path[i] == '/')
			{
				++k;
			}
			else if (k == 2)
			{
				path.remove(i + 2, path.length());
				break;
			}
		QFile f(path + "Application/Themes/White/standard_cover_x1000.jpg");
		f.open(QIODevice::ReadOnly);
		QImage img = QImage::fromData(f.readAll(), "JPEG");
		m_imageProvider->AppendImage(img, QString::number(0));

		for (int i = 0; i < m_listMedia->Rows(); ++i)
		{
			Item item;
			/* Title */
			item.title = m_listMedia->ValueAt("title", i).toString();
			/* Year */
			item.year = m_listMedia->ValueAt("year", i).toString();
			/* Duraction */
			int seconds = m_listMedia->ValueAt("duraction", i).toInt();
			int minutes = 0;
			while (seconds > 59)
			{
				seconds -= 60;
				minutes++;
			}
			item.time = QString::number(minutes) + ':' + QString::number(seconds);
			/* Album */
			for (int i = 0; i < m_listAlbums->Rows(); ++i)
			{
				if (m_listAlbums->ValueAt("id_album", i).toInt() == m_listMedia->ValueAt("id_album", i).toInt())
				{
					item.album = m_listAlbums->ValueAt("title", i).toString();
					break;
				}
			}
			/* Artrist */
			for (int i = 0; i < m_listArtists->Rows(); ++i)
			{
				if (m_listArtists->ValueAt("id_artist", i).toInt() == m_listMedia->ValueAt("id_artist", i).toInt())
				{
					item.artist = m_listArtists->ValueAt("name", i).toString();
					break;
				}
			}
			/* Genre */
			for (int i = 0; i < m_listGenres->Rows(); ++i)
			{
				if (m_listGenres->ValueAt("id_genre", i).toInt() == m_listMedia->ValueAt("id_genre", i).toInt())
				{
					item.genre = m_listGenres->ValueAt("title", i).toString();
					break;
				}
			}
			/* Cover Art */
			item.image = QString::number(0).toUtf8();
			/* Load*/
			m_list->AppendItem(item);
		}
		break;
	}
	}
	m_updateList = ETypeList::Unknown;
}
