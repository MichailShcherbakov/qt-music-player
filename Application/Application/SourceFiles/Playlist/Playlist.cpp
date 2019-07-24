#include "StdAfx.h"
#include "Playlist.h"

Playlist::Playlist(unsigned int index, const Query& query) :
	IPlaylist(gParams->pSocket),
	m_rootLoadQuery(query)
{
	LoadData(index);
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

}

uint Playlist::FirstIndex()
{
	return 0;
}

uint Playlist::EndIndex()
{
	return 0;
}

uint Playlist::NextIndex(unsigned int index)
{
	return 0;
}

uint Playlist::PreviousIndex(unsigned int index)
{
	return 0;
}

bool Playlist::Contains(unsigned int index)
{
	return false;
}

void Playlist::LoadData(unsigned int index)
{
	m_rootLoadQuery.InsertIntoBody("limit", static_cast<int>(m_localSize + m_sizeCacheBuffer));
	m_rootLoadQuery.InsertIntoBody("offset", static_cast<int>(m_localSize));

	m_localSize += m_sizeCacheBuffer;
}