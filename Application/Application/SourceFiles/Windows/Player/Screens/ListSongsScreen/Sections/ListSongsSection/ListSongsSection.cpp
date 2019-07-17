#include "ListSongsSection.h"

ListSongsSection::ListSongsSection(const EParams* const params)
	: ISectionListView(params, Q_NULLPTR, Q_NULLPTR, Q_NULLPTR, Q_NULLPTR)
{
	m_model = new VerticalModel1::List;
	params->m_pRootContext->setContextProperty(QStringLiteral("songsModelList"), m_model);
	params->m_pRootContext->setContextProperty(QStringLiteral("listSongsSection"), this);
}

ListSongsSection::~ListSongsSection()
{
}

void ListSongsSection::Initialize()
{
	connect(this, &ListSongsSection::onInitializeList, this, &ListSongsSection::InitializeList);
	connect(this, &ListSongsSection::onDeleteImageItem, this, &ListSongsSection::DeleteImageItem);
	connect(this, &ListSongsSection::onLoadImageItem, this, &ListSongsSection::LoadImageItem);

	Load(ETypeLoad::GetTableMedia, Query());
	m_requests.append(ETypeLoad::GetTableMedia);

	Load(ETypeLoad::GetTableArtists, Query());
	m_requests.append(ETypeLoad::GetTableArtists);

	Load(ETypeLoad::GetTableAlbums, Query());
	m_requests.append(ETypeLoad::GetTableAlbums);
}

void ListSongsSection::ReadyRead(QByteArray package)
{
}

void ListSongsSection::InitializeList()
{
	m_current_item = 0;
	m_model->Clear();

	for (int i = 0; i < m_pMediaTable->Rows(); ++i)
	{
		VerticalModel1::Item item;
		item.id = m_pMediaTable->ValueAt("id_media", i).toInt();
		item.coverKey = "default";
		item.textLineFirst = m_pMediaTable->ValueAt("title", i).toString();
		item.expression = false;

		int idArtist = m_pMediaTable->ValueAt("id_artist", i).toInt();
		int idAlbum = m_pMediaTable->ValueAt("id_album", i).toInt();

		int localIdArtit = m_pArtistsTable->IndexAt("id_artist", idArtist);
		item.textLineSecond = m_pArtistsTable->ValueAt("name", localIdArtit).toString();

		int localIdAlbum = m_pAlbumsTable->IndexAt("id_album", idAlbum);
		item.textLineThird = m_pAlbumsTable->ValueAt("title", localIdAlbum).toString();

		int duration = m_pMediaTable->ValueAt("duration", i).toInt();

		int minutes = 0;
		while (duration > 59)
		{
			++minutes;
			duration -= 60;
		}
		int seconds = duration;

		item.textLineFourth = QString::number(minutes) + ':';

		QString sec = QString::number(seconds);

		if (sec.size() == 1)
		{
			sec.insert(0, '0');
		}

		item.textLineFourth += sec;

		m_listIndex.insert(item.id, i);

		m_model->AppendItem(item);
	}
}

void ListSongsSection::GottenData(QByteArray data)
{
	Query q;
	q.fromByteArray(data);

	switch (m_requests.first())
	{
	case ETypeLoad::GetTableMedia:
	{
		GetMediaTable(q);
		break;
	}
	case ETypeLoad::GetTableAlbums:
	{
		GetAlbumsTable(q);
		emit onInitializeList();
		break;
	}
	case ETypeLoad::GetTableArtists:
	{
		GetArtistsTable(q);
		break;
	}
	case ETypeLoad::GetArtCover:
	{
		QByteArray& t = q.GetFromBody("cover-art").toVariant().toString().toLatin1();
		UpdateImageItem(t);
		break;
	}
	default:
	{
		MSG(ETypeMessage::Error, "Unknown Type Loading");
		return;
	}
	}
	m_requests.removeFirst();
}

void ListSongsSection::ClickedItem(int id)
{
	for (int i = 0; i < m_model->Size(); ++i)
	{
		VerticalModel1::Item* t = &m_model->At(i);

		if (t->id == id)
		{
			VerticalModel1::Item item = m_model->At(i);
			item.expression = !item.expression;

			if (item.expression)
			{
				emit onChangeTitleSong(item.textLineFirst);
				emit onChangeArtistSong(item.textLineSecond);
				emit onChangeCoverArtSong(item.coverKey);
				emit onChangeTime(item.textLineFourth);
			}

			m_model->RemoveItem(i);
			m_model->InsertItem(i, item);
		}
		else if (t->expression)
		{
			VerticalModel1::Item item = m_model->At(i);
			item.expression = false;
			m_model->RemoveItem(i);
			m_model->InsertItem(i, item);
		}
	}
}

void ListSongsSection::FirstIndex()
{
	int id = *m_listIndex.keyBegin();
	emit onFirstIndex(id);
}

void ListSongsSection::EndIndex()
{
	int id = *m_listIndex.keyEnd();
	emit onEndIndex(id);
}

void ListSongsSection::NextIndex(int id)
{
	int arrayPosition = m_listIndex.value(id);
	if (arrayPosition + 1 < m_listIndex.size())
	{
		int id = m_listIndex.key(arrayPosition + 1);
		emit onNextIndex(id);
	}
	else
	{
		emit onNextIndex(-1);
	}
}

void ListSongsSection::PreviousIndex(int id)
{
	int arrayPosition = m_listIndex.value(id);
	if (arrayPosition - 1 >= 0)
	{
		int id = m_listIndex.key(arrayPosition - 1);
		emit onPreviousIndex(id);
	}
	else
	{
		emit onPreviousIndex(-1);
	}
}

void ListSongsSection::UpdateImageItem(QByteArray image)
{
	QImage p;
	p.loadFromData(image, "JPG");

	QString id;

	if (p == QImage())
	{
		id = "default";
	}
	else if (m_pRootImageProvider->Contains(p))
	{
		id = m_pRootImageProvider->Find(p);
	}
	else
	{
		id = QString::number(m_pRootImageProvider->SafeId());
		m_pRootImageProvider->AppendImage(p, id);
	}

	VerticalModel1::Item newItem;
	int idImageModel = m_listIndex.value(m_idLoadImage.first());

	m_model->SetValueItemAt(idImageModel, id, VerticalModel1::List::COVER_KEY);

	m_idLoadImage.removeFirst();

	m_isQueueFree = true;

	if (!m_idLoadImage.isEmpty())
	{
		m_isQueueFree = false;

		Query q;
		int idImageModel = m_listIndex.value(m_idLoadImage.first());
		int id_album = m_pMediaTable->ValueAt("id_album", idImageModel).toInt();
		q.InsertIntoBody("id-album", id_album);

		Load(ETypeLoad::GetArtCover, q);
		m_requests.append(ETypeLoad::GetArtCover);
	}
}

void ListSongsSection::LoadImageItem(int id)
{
	m_idLoadImage.append(id);

	if (m_isQueueFree)
	{
		m_isQueueFree = false;

		Query q;
		int idImageModel = m_listIndex.value(m_idLoadImage.first());
		int id_album = m_pMediaTable->ValueAt("id_album", idImageModel).toInt();
		q.InsertIntoBody("id-album", id_album);

		Load(ETypeLoad::GetArtCover, q);
		m_requests.append(ETypeLoad::GetArtCover);
	}
}

void ListSongsSection::DeleteImageItem(int id)
{
	for (int i = 0; i < m_model->Size(); ++i)
	{
		VerticalModel1::Item* t = &m_model->At(i);

		if (t->id == id)
		{
			m_pRootImageProvider->Remove(t->coverKey);

			VerticalModel1::Item newItem;
			VerticalModel1::Item oldItem = m_model->At(i);

			newItem.id = oldItem.id;
			newItem.coverKey = "default";
			newItem.textLineFirst = oldItem.textLineFirst;
			newItem.textLineSecond = oldItem.textLineSecond;
			newItem.textLineThird = oldItem.textLineThird;
			newItem.textLineFourth = oldItem.textLineFourth;
			newItem.expression = oldItem.expression;

			m_model->RemoveItem(i);
			m_model->InsertItem(i, newItem);

			break;
		}
	}
}
