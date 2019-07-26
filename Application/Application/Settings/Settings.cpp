#include "StdAfx.h"
#include "Settings.h"

Settings::Settings()
{
	m_pChapters = new IniChapters();
}

Settings::~Settings()
{
	SAFE_DELETE(m_pChapters);
}
