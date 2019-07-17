#ifndef _REGISTRATION_SCREEN_H_
#define _REGISTRATION_SCREEN_H_

#include "StdAfx.h"

#include "Interfaces/IScreen.h"
#include "Sections/RegistrationSection/RegistrationSection.h"

class RegistrationScreen : public IScreen
{
	Q_OBJECT

public:
	enum class ETypeSection : int
	{
		Unknown = 0,
		RegistrationField,
	};

public:
	RegistrationScreen(const EParams* const params);
	~RegistrationScreen();

public slots:
	// IScreen
	virtual void Initialize() override;
	// ~IScreen

public:
	ISection* Section(ETypeSection type);

private:
	// Sections
	RegistrationSection* m_pRegistrationSection;

private:
	// List sections
	QMap<ETypeSection, ISection*> m_listSections;
};


#endif
