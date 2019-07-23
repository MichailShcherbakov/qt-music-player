#include "ListSongsSection.h"

ListSongsSection::ListSongsSection(const EParams* const params) : 
	ISectionListView(params->m_pSocket, params->m_pRootImageProvider, Q_NULLPTR, Q_NULLPTR, Q_NULLPTR, Q_NULLPTR),
	m_pParams(params)
{
	m_pModel = new VerticalModel1::List;
	params->m_pRootContext->setContextProperty(QStringLiteral("songsModelList"), m_pModel);
	params->m_pRootContext->setContextProperty(QStringLiteral("listSongsSection"), this);
}

ListSongsSection::~ListSongsSection()
{
}

void ListSongsSection::Initialize()
{
	connect(this, &ListSongsSection::initializeList, this, &ListSongsSection::InitializeList);
	connect(this, &ListSongsSection::clickedItem, this, &ListSongsSection::ClickedItem);

	m_pImageManager = new ImageManager(m_pParams, m_pModel, &m_listIndex);
	m_pImageManager->Initialize();

	m_pThread = new QThread;
	m_pImageManager->moveToThread(m_pThread);
	m_pThread->start();

	LoadData();
}

void ListSongsSection::ReadyRead(QByteArray package)
{
}

void ListSongsSection::InitializeList()
{
	m_pImageManager->Clear();
	m_pImageManager->SetAvailable(false);

	m_pModel->ClearList();
	
	for (int i = 0; i < m_pMediaTable->Rows(); ++i)
	{
		VerticalModel1::Item item;
		item.id = m_pMediaTable->ValueAt("id_media", i).toInt();
		item.coverKey = "default";
		item.textLineFirst = m_pMediaTable->ValueAt("title", i).toString();
		item.textLineSecond = m_pMediaTable->ValueAt("artist", i).toString();
		item.textLineThird = m_pAlbumsTable->ValueAt("album", i).toString();
		item.expression = false;
		item.expression2 = false;

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

		m_pModel->AppendItem(item);
	}
	m_pImageManager->SetAvailable(true);
}

void ListSongsSection::GottenData(QByteArray data)
{
	Query q;
	q.fromByteArray(data);

	switch (m_requests.first())
	{
	case ETypeLoad::GetTableMedia:
	{
		GetMediaMergedTable(q);
		break;
	}
	case ETypeLoad::GetTableAlbums:
	{
		GetAlbumsTable(q);
		emit initializeList();
		break;
	}
	case ETypeLoad::GetTableArtists:
	{
		GetArtistsTable(q);
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
	if (m_pParams->m_pMediaPlayer->GetSection() != this)
	{
		m_pParams->m_pMediaPlayer->SetConnnectWithSection(this);
	}

	SetCurrentItem(id);

	emit hasClicked();
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

void ListSongsSection::SetCurrentItem(int index)
{
	for (int i = 0; i < m_pModel->Size(); ++i)
	{
		VerticalModel1::Item* t = &m_pModel->At(i);

		if (t->id == index)
		{
			if (!t->expression) // has clicked
			{
				m_pModel->SetValueItemAt(i, true, VerticalModel1::List::EXPRESSION); // clicked
				m_pModel->SetValueItemAt(i, false, VerticalModel1::List::EXPRESSION2);

				m_pParams->m_pSettings->setValue("MediaPlayer/id", t->id);
				m_pParams->m_pSettings->setValue("MediaPlayer/title", t->textLineFirst);
				m_pParams->m_pSettings->setValue("MediaPlayer/artist", t->textLineSecond);
				m_pParams->m_pSettings->setValue("MediaPlayer/time", t->textLineFourth);
			}
			else
			{
				m_pModel->SetValueItemAt(i, false, VerticalModel1::List::EXPRESSION);
				m_pModel->SetValueItemAt(i, true, VerticalModel1::List::EXPRESSION2);
			}
		}
		else if (t->expression)
		{
			m_pModel->SetValueItemAt(i, false, VerticalModel1::List::EXPRESSION); // not clicked
		}
		else if (t->expression2)
		{
			m_pModel->SetValueItemAt(i, false, VerticalModel1::List::EXPRESSION2); // after clicked
		}
	}
}

void ListSongsSection::LoadData()
{
	Query q;
	q.InsertIntoBody("limit", 0);
	q.InsertIntoBody("offset", 0);
	q.InsertIntoBody("merger", true);

	q.InsertIntoBody("type-sort", m_pParams->m_pSettings->value("SortTables/sortType").toInt());
	q.InsertIntoBody("state-sort", m_pParams->m_pSettings->value("SortTables/sortState").toInt());

	Load(ETypeLoad::GetTableMedia, q);
	m_requests.append(ETypeLoad::GetTableMedia);

	Load(ETypeLoad::GetTableArtists, Query());
	m_requests.append(ETypeLoad::GetTableArtists);

	Load(ETypeLoad::GetTableAlbums, Query());
	m_requests.append(ETypeLoad::GetTableAlbums);
}
