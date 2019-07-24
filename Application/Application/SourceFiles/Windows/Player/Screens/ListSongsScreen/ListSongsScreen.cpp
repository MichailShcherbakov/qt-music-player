#include "ListSongsScreen.h"

ListSongsScreen::ListSongsScreen()
	: IScreen()
{
}

ListSongsScreen::~ListSongsScreen()
{
	for (auto it : m_listSections)
	{
		SAFE_DELETE(it);
	}

	SAFE_DELETE(m_pManagerMediaPlayer);
}

ISection* ListSongsScreen::Section(ETypeSection type)
{
	if (m_listSections.contains(type))
	{
		return m_listSections.value(type);
	}
	return Q_NULLPTR;
}

void ListSongsScreen::Initialize()
{
	m_pListSongsSection = new ListSongsSection();
	m_pListSongsSection->Initialize();
	m_listSections.insert(ETypeSection::ListSongsSection, m_pListSongsSection);

	m_pSortListSection = new SortListSection();
	m_pSortListSection->Initialize();
	m_listSections.insert(ETypeSection::SortListSection, m_pSortListSection);

	m_pFooterPanel = new FooterPanel();
	m_pFooterPanel->Initialize();
	m_listSections.insert(ETypeSection::FooterPanel, m_pFooterPanel);

	connect(m_pSortListSection, &SortListSection::onSortChanged, m_pListSongsSection, &ListSongsSection::LoadData);

	m_pManagerMediaPlayer = new ManagerMediaPlayer();
	m_pManagerMediaPlayer->SetConnectionWithSection(m_pListSongsSection);
}