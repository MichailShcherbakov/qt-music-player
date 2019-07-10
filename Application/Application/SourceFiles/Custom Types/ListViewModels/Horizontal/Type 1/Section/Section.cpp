#include "Section.h"

using namespace HorizontalModel1;

Section::Section(HorizontalModel1::List* m_listHorModel, ImageProvider* imageProvider) 
	: ISection(imageProvider),
	m_listHorModel(m_listHorModel)
{
}

Section::~Section()
{
}

void Section::UpdateImageItem(QByteArray data)
{
	QImage p;
	p.loadFromData(data, "JPG");

	QString id;

	if (p == QImage())
	{
		id = "default";
	}
	else if (m_rootImageProvider->Contains(p))
	{
		id = m_rootImageProvider->Find(p);
	}
	else
	{
		id = QString::number(m_rootImageProvider->SafeId());
		m_rootImageProvider->AppendImage(p, id);
	}

	HorizontalModel1::Item newItem;
	HorizontalModel1::Item oldItem = m_listHorModel->At(m_current_item);

	newItem.id = oldItem.id;
	newItem.coverKey = id;
	newItem.textLineFirst = oldItem.textLineFirst;
	newItem.textLineSecond = oldItem.textLineSecond;

	m_listHorModel->RemoveItem(m_current_item);
	m_listHorModel->InsertItem(m_current_item, newItem);

	++m_current_item;

	if (m_current_item < m_pAlbumsTable->Rows())
	{
		Query query;
		query.InsertIntoBody("id-album", m_pAlbumsTable->ValueAt("id_album", m_current_item).toInt());
		emit onSendQuery(this, ENetworkState::GetArtCover, query);
		m_request.append(ENetworkState::GetArtCover);
	}
}

void Section::Initialize()
{
	connect(this, SIGNAL(onGetByteArray(QByteArray)), this, SLOT(Load(QByteArray)));
	connect(this, SIGNAL(onGetTable(Table*)), this, SLOT(Load(Table*)));

	connect(this, &Section::onInitializeList, this, &Section::InitializeList);

	emit onSendQuery(this, ENetworkState::GetTableMedia, Query());
	m_request.append(ENetworkState::GetTableMedia);

	emit onSendQuery(this, ENetworkState::GetTableArtists, Query());
	m_request.append(ENetworkState::GetTableArtists);

	emit onSendQuery(this, ENetworkState::GetTableAlbums, Query());
	m_request.append(ENetworkState::GetTableAlbums);
}

void HorizontalModel1::Section::Load(QByteArray data)
{
	switch (m_request.first())
	{
	case ENetworkState::GetMedia:
	{
		break;
	}
	case ENetworkState::GetArtCover:
	{
		UpdateImageItem(data);
		break;
	}
	}

	m_request.removeFirst();
}

void HorizontalModel1::Section::Load(Table* table)
{
	switch (m_request.first())
	{
	case ENetworkState::GetTableMedia:
	{
		m_pMediaTable = table;
		break;
	}
	case ENetworkState::GetTableAlbums:
	{
		m_pAlbumsTable = table;
		break;
	}
	case ENetworkState::GetTableArtists:
	{
		m_pArtistsTable = table;
		break;
	}
	case ENetworkState::GetTableGenres:
	{
		//m_pGenresTable = table;
		break;
	}
	default:
	{
		MSG(ETypeMessage::Error, "Unknown Nnetwork State");
		return;
	}
	}

	m_request.removeFirst();

	if (m_request.isEmpty())
	{
		emit onInitializeList();
	}
}

void HorizontalModel1::Section::InitializeList()
{
	m_current_item = 0;
	m_listHorModel->Clear();

	for (int i = 0; i < m_pAlbumsTable->Rows(); ++i)
	{
		HorizontalModel1::Item item;
		item.id = i;
		item.coverKey = "default";
		item.textLineFirst = m_pAlbumsTable->ValueAt("title", i).toString();

		for (int j = 0; j < m_pMediaTable->Rows(); ++j)
		{
			if (m_pMediaTable->ValueAt("id_album", j).toInt() == m_pAlbumsTable->ValueAt("id_album", i).toInt())
			{
				int idArtist = m_pMediaTable->ValueAt("id_artist", j).toInt();
				int idLocalArtist = m_pArtistsTable->IndexAt("id_artist", idArtist);

				item.textLineSecond = m_pArtistsTable->ValueAt("name", idLocalArtist).toString();
				break;
			}
		}
		m_listHorModel->AppendItem(item);
	}

	Query query;
	query.InsertIntoBody("id-album", m_pAlbumsTable->ValueAt("id_album", m_current_item).toInt());
	emit onSendQuery(this, ENetworkState::GetArtCover, query);
	m_request.append(ENetworkState::GetArtCover);
}