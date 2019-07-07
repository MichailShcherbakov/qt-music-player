#ifndef _STDAFX_H_
#define _STDAFX_H_

#define SAFE_DELETE(ptr) if (ptr) {delete ptr; ptr = nullptr;} else {ptr = nullptr;}

#include <QGuiApplication>

#include "Log System/LogSystem.h"

enum class ETypeWindow : int
{
	Unknown = -1,
	Login,
	Player,
};

#endif
