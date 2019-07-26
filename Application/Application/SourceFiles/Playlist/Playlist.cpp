#include "StdAfx.h"
#include "Playlist.h"

Playlist::Playlist(uint index, const Query& query) :
	IPlaylist(gParams->pSocket),
	m_rootLoadQuery(query)
{
	LoadData();
}

Playlist::~Playlist()
{
}

void Playlist::Initialize()
{

}
void Playlist::ReadyRead(QByteArray package)
{
}

void Playlist::GottenData(QByteArray data)
{
	Query q;
	q.fromByteArray(data);

	if (m_fullSize == 0)
	{
		m_fullSize = q.GetFromBody("table-size").toInt();

		LoadData();
	}
	else
	{

	}
}

uint Playlist::FirstIndex()
{
	return 0;
}

uint Playlist::EndIndex()
{
	return 0;
}

uint Playlist::NextIndex(uint index)
{
	return 0;
}

uint Playlist::PreviousIndex(uint index)
{
	return 0;
}

bool Playlist::Contains(uint index)
{
	return false;
}

uint Playlist::Size()
{
	return uint();
}

uint Playlist::IndexOf(uint index)
{
	return uint();
}

void Playlist::LoadData()
{
	if (m_fullSize == 0)
	{
		Query q;
		q.InsertIntoHeader("type-query", static_cast<int>(ETypeQuery::Send_Table_Size));
		q.InsertIntoHeader("type-table", static_cast<int>(ETypeTable::All_Media));

		emit sendToSocket(this, q.toByteArray());
	}
	else
	{
		if (m_localSize + m_sizeCacheBuffer < m_fullSize)
		{
			m_rootLoadQuery.InsertIntoBody("limit", static_cast<int>(m_sizeCacheBuffer));
			m_rootLoadQuery.InsertIntoBody("offset", static_cast<int>(m_localSize));
		}
		else if (m_localSize != m_fullSize)
		{
			m_rootLoadQuery.InsertIntoBody("limit", static_cast<int>(m_fullSize - m_localSize));
			m_rootLoadQuery.InsertIntoBody("offset", static_cast<int>(m_localSize));
		}

		m_localSize += m_sizeCacheBuffer;

		emit sendToSocket(this, m_rootLoadQuery.toByteArray());
	}
}