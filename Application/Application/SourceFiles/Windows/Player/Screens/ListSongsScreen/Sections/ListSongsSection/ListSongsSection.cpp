#include "StdAfx.h"
#include "ListSongsSection.h"

ListSongsSection::ListSongsSection() : 
	ISectionListView(gParams->pSocket)
{
	m_pModel = new VerticalModel1::List;
	gParams->pRootContext->setContextProperty(QStringLiteral("songsModelList"), m_pModel);
	gParams->pRootContext->setContextProperty(QStringLiteral("listSongsSection"), this);
}

ListSongsSection::~ListSongsSection()
{
	m_pThread->terminate();

	SAFE_DELETE(m_pThread);
	SAFE_DELETE(m_pImageManager);
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pTable);
}

void ListSongsSection::Initialize()
{
	connect(this, &ListSongsSection::clickedItem, this, &ListSongsSection::ClickedItem);

	m_pImageManager = new VerticalModel1::ImageLoader(m_pModel, &m_listIndex, QStringLiteral("imageProvider"));
	m_pImageManager->Initialize();

	m_pThread = new QThread;
	m_pImageManager->moveToThread(m_pThread);
	m_pThread->start();

	LoadData();
}

void ListSongsSection::ReadyRead(QByteArray package)
{
}

void ListSongsSection::GottenData(QByteArray data)
{
	Query q;
	q.fromByteArray(data);

	GetMediaMergedTable(q);
	InitializeList();
}

void ListSongsSection::InitializeList()
{
	m_pImageManager->Clear();
	m_pImageManager->SetAvailable(false);

	m_pModel->ClearList();
	
	for (int i = 0; i < m_pTable->Rows(); ++i)
	{
		VerticalModel1::Item item;
		item.id = m_pTable->ValueAt("id_media", i).toInt();
		item.coverKey = "default";
		item.textLineFirst = m_pTable->ValueAt("title", i).toString();
		item.textLineSecond = m_pTable->ValueAt("artist", i).toString();
		item.textLineThird = m_pTable->ValueAt("album", i).toString();
		item.expression = false;
		item.expression2 = false;

		int duration = m_pTable->ValueAt("duration", i).toInt();

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

void ListSongsSection::ClickedItem(int id)
{
	SetCurrentItem(id);

	emit clicked();
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

				gParams->pSettings->setValue("MediaPlayer/id", t->id);
				gParams->pSettings->setValue("MediaPlayer/title", t->textLineFirst);
				gParams->pSettings->setValue("MediaPlayer/artist", t->textLineSecond);
				gParams->pSettings->setValue("MediaPlayer/time", t->textLineFourth);
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
	q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table));
	q.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Media));

	q.InsertIntoBody("limit", static_cast<int>(m_localSize));
	q.InsertIntoBody("offset", static_cast<int>(m_localSize + m_sizeCacheBuffer));
	q.InsertIntoBody("merger", true);
	q.InsertIntoBody("type-sort", gParams->pSettings->value("SortTables/sortType").toInt());
	q.InsertIntoBody("state-sort", gParams->pSettings->value("SortTables/sortState").toInt());
}

void ListSongsSection::GetMediaMergedTable(Query& data)
{
	QJsonArray table = data.GetFromBody("table").toArray();

	if (m_pTable)
	{
		SAFE_DELETE(m_pTable);
	}

	m_pTable = new Table;

	m_pTable->AddColumn("id_media");
	m_pTable->AddColumn("title");
	m_pTable->AddColumn("artist");
	m_pTable->AddColumn("album");
	m_pTable->AddColumn("genre");
	m_pTable->AddColumn("year");
	m_pTable->AddColumn("duration");
	m_pTable->AddColumn("bitrate");
	m_pTable->AddColumn("add_time");
	m_pTable->AddColumn("last_listened");
	m_pTable->AddColumn("number_times_listened");
	m_pTable->AddColumn("lyric");
	m_pTable->AddColumn("lyrics_translation");

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
			m_pTable->AddRow(rowMedia);
		}
	}
}
