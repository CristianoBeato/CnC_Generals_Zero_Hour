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

#include "WWprecompiled.h"
#include "mutex.h"
#include "WWDebug/wwdebug.h"

// ----------------------------------------------------------------------------

MutexClass::MutexClass(const char* name) : handle(NULL), locked(false)
{
		handle=CreateMutex(NULL,false,name);
		WWASSERT(handle);
}

MutexClass::~MutexClass( void )
{
	WWASSERT( !locked ); // Can't delete locked mutex!
	SDL_( handle );
}

bool MutexClass::Lock(int time)
{

	SDL_TryLockMutex( )
	#ifdef _UNIX
		//assert(0);
		return true;
	#else
		int res = WaitForSingleObject(handle,time==WAIT_INFINITE ? INFINITE : time);
		if (res!=WAIT_OBJECT_0) return false;
		locked++;
		return true;
	#endif
}

void MutexClass::Unlock( void )
{
	WWASSERT(locked);
	SDL_UnlockMutex( );
	locked--;
}

// ----------------------------------------------------------------------------

MutexClass::LockClass::LockClass(MutexClass& mutex_,int time) : mutex(mutex_)
{
	failed=!mutex.Lock(time);
}

MutexClass::LockClass::~LockClass()
{
	if (!failed) mutex.Unlock();
}

// ----------------------------------------------------------------------------

CriticalSectionClass::CriticalSectionClass() : handle( nullptr ), locked(false)
{
	handle = SDL_CreateMutex();
	WWASSERT( handle );
}

CriticalSectionClass::~CriticalSectionClass()
{
	WWASSERT(!locked); // Can't delete locked mutex!
	SDL_DestroyMutex( handle );
}

void CriticalSectionClass::Lock( void )
{
	SDL_LockMutex( handle );
	locked++;
}

void CriticalSectionClass::Unlock( void )
{
	WWASSERT(locked);
	SDL_UnlockMutex( handle );
	locked--;
}

// ----------------------------------------------------------------------------

CriticalSectionClass::LockClass::LockClass(CriticalSectionClass& critical_section) : CriticalSection(critical_section)
{
	CriticalSection.Lock();
}

CriticalSectionClass::LockClass::~LockClass()
{
	CriticalSection.Unlock();
}


