/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// This file contains all the header files that shouldn't change frequently.
// Be careful what you stick in here, because putting files that change often in here will 
// tend to cheese people's goats.

#ifndef __PRERTS_H__
#define __PRERTS_H__

//-----------------------------------------------------------------------------
// srj sez: this must come first, first, first.
#define _STLP_USE_NEWALLOC					1
//#define _STLP_USE_CUSTOM_NEWALLOC		STLSpecialAlloc
class STLSpecialAlloc;

// BEATO Begin:
#include <cstdio>
#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <cstring>
#include <fstream>
#include <assert.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <cmath>
#include <float.h>
#include <memory.h>
#include <algorithm>

#if defined( __linux__)
#elif defined( _WIN32 )
// We actually don't use Windows for much other than timeGetTime, but it was included in 40 
// different .cpp files, so I bit the bullet and included it here.
// PLEASE DO NOT ABUSE WINDOWS OR IT WILL BE REMOVED ENTIRELY. :-)
//--------------------------------------------------------------------------------- System Includes 

#   define WIN32_LEAN_AND_MEAN
#   include <atlbase.h>
#   include <windows.h>
#   include <direct.h>
#   include <EXCPT.H>
#   include <imagehlp.h>
#   include <lmcons.h>
#   include <mapicode.h>
#   include <mmsystem.h>
#   include <objbase.h>
#   include <ocidl.h>
#   include <process.h>
#   include <shellapi.h>
#   include <shlobj.h>
#   include <shlguid.h>
#   include <snmp.h>
#   include <TCHAR.H>
#   include <vfw.h>
#   include <winerror.h>
#   include <wininet.h>
#   include <winreg.h>

#ifndef DIRECTINPUT_VERSION
#	define DIRECTINPUT_VERSION	0x800
#endif

#include <dinput.h>
#endif // _WIN32
// BEATO End

//------------------------------------------------------------------------------------ STL Includes
// srj sez: no, include STLTypesdefs below, instead, thanks
//#include <algorithm>
//#include <bitset>
//#include <hash_map>
//#include <list>
//#include <map>
//#include <queue>
//#include <set>
//#include <stack>
//#include <string>
//#include <vector>

//------------------------------------------------------------------------------------ RTS Includes
// Icky. These have to be in this order.
#include "Lib/BaseType.h"
#include "Common/STLTypedefs.h"
#include "Common/Errors.h"
#include "Common/Debug.h"
#include "Common/AsciiString.h"
#include "Common/SubsystemInterface.h"

#include "Common/GameCommon.h"
#include "Common/GameMemory.h"
#include "Common/GameType.h"
#include "Common/GlobalData.h"

// You might not want Kindof in here because it seems like it changes frequently, but the problem
// is that Kindof is included EVERYWHERE, so it might as well be precompiled.
#include "Common/INI.h"
#include "Common/KindOf.h"
#include "Common/DisabledTypes.h"
#include "Common/NameKeyGenerator.h"
#include "GameClient/ClientRandomValue.h"
#include "GameLogic/LogicRandomValue.h"

#include "Common/Thing.h"
#include "Common/UnicodeString.h"

#endif /* __PRERTS_H__ */
