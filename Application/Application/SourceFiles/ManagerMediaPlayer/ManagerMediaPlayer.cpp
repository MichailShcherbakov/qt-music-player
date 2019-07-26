#include "StdAfx.h"
#include "ManagerMediaPlayer.h"

ManagerMediaPlayer::ManagerMediaPlayer(QObject* parent)
	: QObject(parent),
	m_pSection(Q_NULLPTR)
{
}

ManagerMediaPlayer::~ManagerMediaPlayer()
{
}

void ManagerMediaPlayer::CreateNewPlaylist(uint index)
{
	gParams->pMediaPlayer->SetPlaylist(new Playlist(index, m_pSection->GetLoadQuery()));
	gParams->pMediaPlayer->Play(index);
}

void ManagerMediaPlayer::SetConnectionWithSection(ISectionListView* const section)
{
	if (m_pSection)
	{
		disconnect(m_pSection, &ISectionListView::ClickedItem, this, &ManagerMediaPlayer::CreateNewPlaylist);
		disconnect(gParams->pMediaPlayer, &IMediaPlayer::started, m_pSection, &ISectionListView::SetCurrentItem);
		disconnect(gParams->pMediaPlayer, &IMediaPlayer::paused, m_pSection, &ISectionListView::SetCurrentItem);
	}

	m_pSection = section;

	connect(m_pSection, &ISectionListView::clicked, this, &ManagerMediaPlayer::CreateNewPlaylist);
	connect(gParams->pMediaPlayer, &IMediaPlayer::started, m_pSection, &ISectionListView::SetCurrentItem);
	connect(gParams->pMediaPlayer, &IMediaPlayer::paused, m_pSection, &ISectionListView::SetCurrentItem);

	if (gParams->pMediaPlayer->CurrentIndex() != 0)
	{
		m_pSection->SetCurrentItem(gParams->pMediaPlayer->CurrentIndex());
	}
}
