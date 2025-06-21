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

/***********************************************************************************************
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/systimer.h                             $*
 *                                                                                             *
 *                      $Author:: Steve_t                                                     $*
 *                                                                                             *
 *                     $Modtime:: 12/09/01 6:41p                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once
#ifndef _SYSTIMER_H

#include "WWLib/always.h"
#include "mmsys.h"

#ifdef _WIN32
#include <windows.h>
#endif _WIN32

#define TIMEGETTIME SystemTime.Get

//
// Class that just wraps around timeGetTime()
//
//
//
class SysTimeClass
{

	public:

		SysTimeClass(void);	//default constructor
		~SysTimeClass();	//default destructor

		//
		// Get. Use everywhere you would use timeGetTime
		//
		WWINLINE uint64_t Get(void);
		WWINLINE uint64_t operator () (void) { return( Get() ); }
		WWINLINE operator uint64_t(void) { return( Get()); }

		//
		// Use periodically (like every few days!) to make sure the timer doesn't wrap.
		//
		void Reset(void);

		//
		// See if the timer is about to wrap.
		//
		bool Is_Getting_Late(void);

	private:

		//
		// Time we were first called.
		//
		uint64_t StartTime;

		//
		// Time to add after timer wraps.
		//
		uint64_t WrapAdd;

};

extern SysTimeClass SystemTime;


/***********************************************************************************************
 * SysTimeClass::Get -- Wrapper around system timeGetTime() api call                           *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Current system time in ms                                                         *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/25/2001 1:38PM ST : Created                                                            *
 *=============================================================================================*/
WWINLINE uint64_t SysTimeClass::Get(void)
{
	/*
	** This has to be static here since we don't know if we will get called in a global constructor of another object before our
	** constructor gets called. In fact, we don't even have a constructor because it's pointless.
	*/
	static bool is_init = false;

	if (!is_init) 
	{
		Reset();
		is_init = true;
	}

	uint64_t time = timeGetTime();
	if (time > StartTime) {
		return(time - StartTime);
	}

	/*
	** Timer wrapped around. Eeek.
	*/
	return(time + WrapAdd);
}



#ifdef timeGetTime
#undef timeGetTime
#define timeGetTime SystemTime.Get
#endif //timeGetTime




#endif //_SYSTIMER_H
