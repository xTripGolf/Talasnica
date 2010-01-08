// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <cstdio>
#include <iostream>
#ifdef _DEBUG
	#include <fstream>
	#include <sstream>
#endif

#ifdef _DEBUG
	extern std::ofstream log;
#endif

#include "Exception.h"
#include "ostream.h"

#include "Type.h"
#include "Order.h"
#include "OrderManager.h"
