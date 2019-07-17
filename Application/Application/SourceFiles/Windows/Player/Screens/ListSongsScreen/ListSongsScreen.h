#ifndef _LIST_SONGS_SCREEN_H_
#define _LIST_SONGS_SCREEN_H_

#include "StdAfx.h"

#include "Interfaces/IScreen.h"
#include "Sections/ListSongsSection/ListSongsSection.h"

class ListSongsScreen : public IScreen
{
	Q_OBJECT

public:
	enum class ETypeSection : int
	{
		Unknown = 0,
		ListSongsSection,
	};

public:
	ListSongsScreen(const EParams* const params);
	~ListSongsScreen() override;

public slots:
	// IScreen
	virtual void Initialize() override;
	// ~IScreen

public:
	ISectionListView* Section(ETypeSection type);

private:
	// Sections
	ListSongsSection* m_pRegistrationSection;

private:
	// List sections
	QMap<ETypeSection, ISectionListView*> m_listSections;
};
#endif