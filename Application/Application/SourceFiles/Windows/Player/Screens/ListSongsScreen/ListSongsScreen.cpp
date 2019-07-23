#include "ListSongsScreen.h"

ListSongsScreen::ListSongsScreen(const EParams* const params)
	: IScreen(params)
{
}

ListSongsScreen::~ListSongsScreen()
{
	for (auto it : m_listSections)
	{
		SAFE_DELETE(it);
	}
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
	m_pListSongsSection = new ListSongsSection(m_pParams);
	m_pListSongsSection->Initialize();
	m_listSections.insert(ETypeSection::ListSongsSection, m_pListSongsSection);

	m_pSortListSection = new SortListSection(m_pParams);
	m_pSortListSection->Initialize();
	m_listSections.insert(ETypeSection::SortListSection, m_pSortListSection);

	m_pFooterPanel = new FooterPanel(m_pParams);
	m_pFooterPanel->Initialize();
	m_listSections.insert(ETypeSection::FooterPanel, m_pFooterPanel);

	connect(m_pSortListSection, &SortListSection::onSortChanged, m_pListSongsSection, &ListSongsSection::LoadData);
}