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

// Download.h : Declaration of the CDownload

#ifndef __DOWNLOAD_H_
#define __DOWNLOAD_H_

//#include "../resource.h"       // main symbols
#include "WWDownload/ftp.h"
#include "WWDownload/downloaddefs.h"

/////////////////////////////////////////////////////////////////////////////
// CDownload

class IDownload
{
 public:
	virtual int OnError( int error )=0;
	virtual int OnEnd( void )=0;
	virtual int OnQueryResume( void )=0;
	virtual int OnProgressUpdate( size_t bytesread, size_t totalsize, int timetaken, int timeleft )=0;
	virtual int OnStatusUpdate(int status)=0;
};

class CDownload
{
public:
	CDownload( IDownload *listener ) : Listener( listener )
	{
		m_Status			= DOWNLOADSTATUS_NONE;
		m_TimeStarted		= 0;
		m_StartPosition		= 0;
		m_FileSize			= 0;
		m_BytesRead			= 0;
		m_Server[ 0 ]		= '\0';
		m_Login[ 0 ]		= '\0';
		m_Password[ 0 ]		= '\0';
		m_File[ 0 ]			= '\0';
		m_LocalFile[ 0 ]	= '\0';
		m_RegKey[ 0 ]		= '\0';
		m_Ftp				= new( Cftp );
		m_TryResume = false;

		m_predictions = 0;
		for (int i=0; i<8; ++i)
		{
			m_predictionTimes[i] = 0;
		}
	}

	~CDownload( void ) 
	{ 
		delete m_Ftp; 
	}

public:
	virtual int PumpMessages( void );
	virtual int Abort( void );
	virtual int DownloadFile( const char* server, const char* username, const char* password, const char* file, const char* localfile, const char* regkey, bool tryresume=true);
	virtual int GetLastLocalFile( char *local_file, size_t maxlen );

private:
	char m_Server[ 256 ];
	char m_Login[ 64 ];
	char m_Password[ 64 ];
	char m_File[ 256 ];
	char m_LocalFile[ 256 ];

	char m_LastLocalFile[ 256 ];

	char m_RegKey[ 256 ];
	int  m_Status;
	int  m_TimeStarted;
	int  m_StartPosition;
	int  m_FileSize;
	int  m_BytesRead;
	bool m_TryResume;

	int m_predictions;
	int m_predictionTimes[8];

	Cftp			*m_Ftp;
	IDownload	*Listener;
};

#endif //__DOWNLOAD_H_
