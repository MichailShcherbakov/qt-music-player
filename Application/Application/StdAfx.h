#ifndef _STDAFX_H_
#define _STDAFX_H_

#define SAFE_DELETE(ptr) if (ptr) { delete ptr; ptr = nullptr; } else {ptr = nullptr;}

#include "LogSystem/LogSystem.h"
#include "Tools/Query.h"
#include "Tools/Table/Table.h"
#include "Tools/EParams.h"
#include "Tools/BaseTypes.h"
#include "Tools/TagEditer/TagEditer.h"

#endif
