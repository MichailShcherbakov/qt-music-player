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

ISectionListView* ListSongsScreen::Section(ETypeSection type)
{
	if (m_listSections.contains(type))
	{
		return m_listSections.value(type);
	}
	return Q_NULLPTR;
}

void ListSongsScreen::Initialize()
{
	m_pRegistrationSection = new ListSongsSection(m_pParams);
	m_pRegistrationSection->Initialize();
	m_listSections.insert(ETypeSection::ListSongsSection, m_pRegistrationSection);
}