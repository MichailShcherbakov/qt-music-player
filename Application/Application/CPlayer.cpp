#include "cplayer.h"



CPlayer::CPlayer(QQuickWindow* window, CQuery* query, CList* list, CImageProvider* imageProvider) :
	IWindow(window, query),
	m_list(list),
	m_table(nullptr),
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
	delete m_table, m_list, m_imageProvider, m_buffer, m_player;
}

void CPlayer::Initialize()
{
	m_player = new QMediaPlayer(this);

	connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &CPlayer::MediaStatusChanged);
	connect(m_player, &QMediaPlayer::positionChanged, this, &CPlayer::positionChanged);
	connect(m_player, &QMediaPlayer::durationChanged, this, &CPlayer::mediaChanged);

	m_query->NewQuery(m_query->GET_TABLE, m_query->ALL_MUSIC);
	m_stateNetwork = EStateNetwork::INITIALIZE_ALL_MUSIC;
	emit sendToSocket(m_query->toByteArray());
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
	/*switch (m_stateNetwork)
	{
	case EStateNetwork::INITIALIZE_ALL_MUSIC:
	{
		if (data->toStdString() != "Table is empty")
		{
			if (!m_table) m_table = new CTable(data);

			if (m_current_media_loadding < m_table->GetCountRows())
			{
				m_query->NewQuery(m_query->GET_IMAGE, m_table->GetTable()->at(1).at(m_current_media_loadding), m_table->GetTable()->at(2).at(m_current_media_loadding));
				emit sendToSocket(m_query->toByteArray());
				m_stateNetwork = EStateNetwork::GETTING_NEEDED_IMAGE;
			}
		}
		break;
	}
	case EStateNetwork::GETTING_NEEDED_MUSIC:
	{
		SAFE_DELETE(m_buffer);
		m_buffer = new QBuffer;
		m_buffer->setData(*data);
		m_buffer->open(QIODevice::ReadOnly);
		m_player->setMedia(QMediaContent(), m_buffer);
		m_statePlayer = EStatePlayer::Play;
		emit changeImagePlayButton("qrc:/Images/pause.svg");
		QString pos = QString::number(m_current_media);
		m_window->findChild<QObject*>("title_label")->setProperty("text", m_table->GetTable()->at(1).at(m_current_media));
		m_window->findChild<QObject*>("author_label")->setProperty("text", m_table->GetTable()->at(2).at(m_current_media));
		emit changeImageCover(pos);
		m_player->play();
		break;
	}
	case EStateNetwork::GETTING_NEEDED_IMAGE:
	{
		QImage p;
		p.loadFromData(*data, "JPG");

		m_imageProvider->AppendImage(p, QString::number(m_current_media_loadding));

		//m_list->AppendItem("", QString::number(m_current_media_loadding), m_table->GetTable()->at(1).at(m_current_media_loadding), m_table->GetTable()->at(2).at(m_current_media_loadding), "", "", "","","");
		++m_current_media_loadding;
		m_stateNetwork = EStateNetwork::INITIALIZE_ALL_MUSIC;
		this->getFromSocket(nullptr);
		break;
	}
	}
	SAFE_DELETE(data);*/
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
