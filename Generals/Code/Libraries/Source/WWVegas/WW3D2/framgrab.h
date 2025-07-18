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
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/framgrab.h                             $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 1/08/01 10:04a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if defined(_MSC_VER)
#pragma once
#endif

#ifndef FRAMEGRAB_H
#define FRAMEGRAB_H

#ifndef ALWAYS_H
#include "WWLib/always.h"
#endif

#if defined (_MSC_VER)
#pragma warning (push, 3)	// (gth) system headers complain at warning level 4...
#endif

#if defined( _WIN32 )
#ifndef _WINDOWS_
#include "windows.h"
#endif

#ifndef _INC_WINDOWSX
#include "windowsx.h"
#endif

#ifndef _INC_VFW
#include "vfw.h"
#endif
#endif //_WIN32

#if defined (_MSC_VER)
#pragma warning (pop)
#endif

// FramGrab.h: interface for the FrameGrabClass class.
//
//////////////////////////////////////////////////////////////////////

class FrameGrabClass  
{
public:
	enum MODE 
	{
		RAW,
		AVI
	};

	// depending on which mode you select, it will produce either frames or an AVI.
	FrameGrabClass(const char *filename, MODE mode, int width, int height, int bitdepth, float framerate );

	virtual ~FrameGrabClass( void );

	void ConvertGrab(void *BitmapPointer);
	void Grab(void *BitmapPointer);

	long * GetBuffer( void ) { return Bitmap; }
	float	GetFrameRate( void ) { return FrameRate; }

protected:
// BEATO Begin:
	MODE 				Mode;
	float				FrameRate;
	int 				Width;
	int 				Height;
	uint64_t 			Counter; // used for incrementing filename cunter, etc.
	const char*			Filename;
	long*				Bitmap;
	// avi settings
	AVFormatContext* 	fmt_ctx;
	AVCodecContext* 	codec_ctx;
	SwsContext* 		sws_ctx;
	AVStream* 			stream;
    AVFrame* 			frame;
// BEATO end

	
	// general purpose cleanup routine
	void CleanupAVI();

	// convert the SR image into AVI byte ordering
	void ConvertFrame(void *BitmapPointer);

	void GrabAVI(void *BitmapPointer);
	void GrabRawFrame(void *BitmapPointer);
};

#endif
