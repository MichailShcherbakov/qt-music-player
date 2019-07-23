#ifndef _LIST_SONGS_SCREEN_H_
#define _LIST_SONGS_SCREEN_H_

#include "StdAfx.h"

#include "Interfaces/IScreen.h"
#include "Sections/ListSongsSection/ListSongsSection.h"
#include "Sections/SortListSection/SortListSection.h"
#include "Sections/FooterPanel/FooterPanel.h"

class ListSongsScreen : public IScreen
{
	Q_OBJECT

public:
	enum class ETypeSection : int
	{
		Unknown = 0,
		ListSongsSection,
		SortListSection,
		FooterPanel,
	};

public:
	ListSongsScreen(const EParams* const params);
	~ListSongsScreen() override;

public slots:
	// IScreen
	virtual void Initialize() override;
	// ~IScreen

public:
	ISection* Section(ETypeSection type);

private:
	// Sections
	ListSongsSection* m_pListSongsSection;
	SortListSection* m_pSortListSection;
	FooterPanel* m_pFooterPanel;

private:
	// List sections
	QMap<ETypeSection, ISection*> m_listSections;
};
#endif