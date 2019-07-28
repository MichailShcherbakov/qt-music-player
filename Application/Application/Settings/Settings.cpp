#include "StdAfx.h"
#include "Settings.h"

Settings::Settings()
{
}

Settings::~Settings()
{
	SAFE_DELETE(m_pChapters);
}
