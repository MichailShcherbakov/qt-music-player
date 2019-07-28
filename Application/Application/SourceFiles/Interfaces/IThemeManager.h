#ifndef _ITHEME_MANAGER_H_
#define _ITHEME_MANAGER_H_

#include "Interfaces/ITheme.h"

class IThemeManager : public QObject
{
	Q_OBJECT

public:
	enum class ETypeTheme : uint
	{
		Unknown = 0,
		White,
		Dark
	};

public:
	IThemeManager() {}
	virtual ~IThemeManager() {}

public:
	virtual void SetTheme(ETypeTheme m_typeTheme) = 0;
	inline ITheme* Theme() { return m_pTheme; }

protected:
	ITheme* m_pTheme;
	QSettings* m_pAppSettings;
	ETypeTheme m_typeTheme = ETypeTheme::Unknown;
};

#endif