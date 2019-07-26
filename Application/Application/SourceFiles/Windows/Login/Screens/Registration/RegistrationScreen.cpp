#include "StdAfx.h"
#include "RegistrationScreen.h"

RegistrationScreen::RegistrationScreen()
	: IScreen(),
	m_pRegistrationSection(Q_NULLPTR)
{
}

RegistrationScreen::~RegistrationScreen()
{
	for (auto it : m_listSections)
	{
		SAFE_DELETE(it);
	}
}

ISection* RegistrationScreen::Section(ETypeSection type)
{
	if (m_listSections.contains(type))
	{
		return m_listSections.value(type);
	}
	return Q_NULLPTR;	
}

void RegistrationScreen::Initialize()
{
	m_pRegistrationSection = new RegistrationSection();
	m_pRegistrationSection->Initialize();
	m_listSections.insert(ETypeSection::RegistrationField, m_pRegistrationSection);
}