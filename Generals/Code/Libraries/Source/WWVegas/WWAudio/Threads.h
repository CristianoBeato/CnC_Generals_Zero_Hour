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
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WWAudio                                                      *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/WWAudio/Threads.h                                                                                                                                                                                                                                                                                                                               $Modtime:: 7/17/99 3:32p                                               $*
 *                                                                                             *
 *                    $Revision:: 6                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __WWAUDIO_THREADS_H
#define __WWAUDIO_THREADS_H

#include "WWLib/vector.h"
#include "WWLib/mutex.h"

#include <SDL3/SDL_thread.hpp>
#include <SDL3/SDL_mutex.hpp>

// Forward declarations
class RefCountClass;

//////////////////////////////////////////////////////////////////////////
//
//	WWAudioThreadsClass
//
//	Simple class that provides a common namespace for tying thread
// information together.
//
//////////////////////////////////////////////////////////////////////////
class WWAudioThreadsClass
{
	public:

		//////////////////////////////////////////////////////////////////////
		//	Public constructors/destructors
		//////////////////////////////////////////////////////////////////////
		WWAudioThreadsClass (void);
		~WWAudioThreadsClass (void);

		//////////////////////////////////////////////////////////////////////
		//	Public methods
		//////////////////////////////////////////////////////////////////////
		
		//
		//	Delayed release mechanism
		//
		static SDL::Thread	Create_Delayed_Release_Thread( void* param = nullptr );
		static void			End_Delayed_Release_Thread( uint32_t timeout = 20000 );
		static void			Add_Delayed_Release_Object( RefCountClass *object, uint32_t delay = 2000 );
		static void			Flush_Delayed_Release_Objects( void );

	private:

		//////////////////////////////////////////////////////////////////////
		//	Private methods
		//////////////////////////////////////////////////////////////////////
		static int	__cdecl Delayed_Release_Thread_Proc( void* param );

		//////////////////////////////////////////////////////////////////////
		//	Private data types
		//////////////////////////////////////////////////////////////////////
		typedef struct _DELAYED_RELEASE_INFO
		{
			uint32_t		time = 0;
			RefCountClass *	object = nullptr;
			_DELAYED_RELEASE_INFO *next;

		} DELAYED_RELEASE_INFO;

		//typedef DynamicVectorClass<DELAYED_RELEASE_INFO *>	RELEASE_LIST;

		//////////////////////////////////////////////////////////////////////
		//	Private member data
		//////////////////////////////////////////////////////////////////////
		static SDL::Thread				m_hDelayedReleaseThread;
		static SDL::Semaphore			m_hDelayedReleaseEvent;
		//static RELEASE_LIST			m_ReleaseList;
		static CriticalSectionClass		m_CriticalSection;
		static DELAYED_RELEASE_INFO *	m_ReleaseListHead;
		static CriticalSectionClass		m_ListMutex;
		static bool						m_IsShuttingDown;
};

#endif //__WWAUDIO_THREADS_H

