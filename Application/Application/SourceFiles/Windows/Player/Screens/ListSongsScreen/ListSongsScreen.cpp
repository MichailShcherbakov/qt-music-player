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
	MSG(ETypeMessage::Log, "List song section initialization");

	m_pListSongsSection = new ListSongsSection();
	m_pListSongsSection->Initialize();
	m_listSections.insert(ETypeSection::ListSongsSection, m_pListSongsSection);

	MSG(ETypeMessage::Log, "Sort list section initialization");

	m_pSortListSection = new SortListSection();
	m_pSortListSection->Initialize();
	m_listSections.insert(ETypeSection::SortListSection, m_pSortListSection);

	MSG(ETypeMessage::Log, "Footer Panel initialization");

	m_pFooterPanel = new FooterPanel();
	m_pFooterPanel->Initialize();
	m_listSections.insert(ETypeSection::FooterPanel, m_pFooterPanel);

	connect(m_pSortListSection, &SortListSection::sortChanged, m_pListSongsSection, &ListSongsSection::LoadData);

	MSG(ETypeMessage::Log, "Manager media player initialization");

	m_pManagerMediaPlayer = new ManagerMediaPlayer();
	m_pManagerMediaPlayer->SetConnectionWithSection(m_pListSongsSection);
}