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

// ftp.cpp : Implementation of Cftp

/*************************************************************************/
/*_$                      Include Files                                  */
/*************************************************************************/

#if 1
#include "WWprecompiled.h"
#include "ftp.h"
#else
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <process.h>
#include <io.h>
#include "assert.h"
#include "ftp.h"
#include "winsock.h"
#include <direct.h>
//#include "wlib/wstring.h"
#endif

#if defined( __linux__ )
#	include <unistd.h>
#	include <pthread.h>
#	include <netdb.h>
#	include <sys/ioctl.h>

// match windows naming
#define SOCKET_ERROR -1
#define ioctlsocket ioctl
#define closesocket close

#elif defined( _WIN32 )

#define getcwd _getcwd
#define chmod _chmod
#define S_IWRITE _S_IWRITE 
#define S_IREAD _S_IREAD

#endif // _WIN23

#include "DownloadDebug.h"

// umm... what?? BGC 3/27/03
//#ifndef _DEBUG
//#define _DEBUG
//#endif

/*************************************************************************/
/*_$                      External References                            */
/*************************************************************************/

/*************************************************************************/
/*_$                      Private Datatypes                              */
/*************************************************************************/

/*************************************************************************/
/*_$                      Public Data                                    */
/*************************************************************************/

/*************************************************************************/
/*_$                      Private Data                                   */
/*************************************************************************/

//static HOSTENT  gThreadHost;
struct sockaddr_in  gThreadAddress;

static int		 gThreadFlag;

/*************************************************************************/
/*_$                      Private Prototypes                             */
/*************************************************************************/

/*************************************************************************/
/*_$                      Private Macros                                 */
/*************************************************************************/


/* Status flags */

#define FTPSTAT_INIT				0
#define FTPSTAT_CONNECTING			10
#define FTPSTAT_WAITINGSERVEROK		15
#define FTPSTAT_CONNECTED			20
#define FTPSTAT_SENDINGUSER			30
#define FTPSTAT_SENTUSER			40
#define FTPSTAT_SENDINGPASS			50
#define FTPSTAT_LOGGEDIN			60
#define FTPSTAT_LOGGINGOFF			70
#define FTPSTAT_SENDINGQUIT			80
#define FTPSTAT_SENTQUIT			90
#define FTPSTAT_FILEFOUND			100
#define FTPSTAT_SENDINGCWD			110
#define FTPSTAT_SENTCWD				120
#define FTPSTAT_SENTPORT			130
#define FTPSTAT_SENDINGLIST			140
#define FTPSTAT_SENTLIST			150
#define FTPSTAT_LISTDATAOPEN		160
#define FTPSTAT_LISTDATARECVD		170
#define FTPSTAT_FILEOPEN			180
#define FTPSTAT_SENTFILEPORT		190
#define FTPSTAT_SENDINGTYPE			200
#define FTPSTAT_SENTTYPE			210
#define FTPSTAT_SENDINGREST			220
#define FTPSTAT_SENTREST			230
#define FTPSTAT_SENDINGRETR			240
#define FTPSTAT_SENTRETR			250
#define FTPSTAT_FILEDATAOPEN		260
#define FTPSTAT_FILEDATACLOSED		270
#define FTPSTAT_TRANSFERREPLY		280


// Utility functions
bool Prepare_Directories(const char *rootdir, const char *filename);

//
// This is here as a hack...
// Some firewalls break the TCP stack so non-blocking sockets don't work right...
//
static bool Use_Non_Blocking_Mode(void) 
{
// BEATO Begin
#if defined( _WIN32 )
	HKEY regKey = 0;
	uint64_t regRetval = 0;
	uint32_t bufsiz=0;
	uint32_t type=0;
	uint32_t value=0;


	// Try and open the named key
	regRetval=RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Westwood\\Earth And Beyond Beta 2",0,KEY_READ,&regKey);
	if (regRetval!=ERROR_SUCCESS)
		return true;		// default TRUE

	// Fetch the flag
	bufsiz=sizeof(value);
	type=REG_DWORD;
	regRetval=RegQueryValueEx(regKey, "UseNonBlockingFTP", 0, &type, (BYTE*) &value, &bufsiz);

	RegCloseKey(regKey);

	if ((regRetval!=ERROR_SUCCESS) || (type != REG_DWORD))
		return true;

#endif
// BEATO End
	return false;
}



/////////////////////////////////////////////////////////////////////////////
// Cftp


/*$_Function****************************************************************
* $_Name        :
*	Cftp::Cftp()
*
* $_Description :
*	Constructor for the ftp class - initialises more or less all data 
*	members to zero.
*
* $_Parameters  :
*	None.
*
* $_ReturnValue :
*	None.
*
***************************************************************************/


Cftp::Cftp( void )
{
  ZeroStuff();
}

/*$_Function****************************************************************
* $_Name        :
*	Cftp::Cftp()
*
* $_Description :
*	Destructor for the ftp class - close sockets behind us as we leave.
*
* $_Parameters  :
*	None.
*
* $_ReturnValue :
*	None.
*
***************************************************************************/


Cftp::~Cftp( void )
{
  CloseSockets();

	if (m_pfLocalFile)
	{
		fclose(m_pfLocalFile);
		m_pfLocalFile = nullptr;
	}
}

void Cftp::CloseSockets(void)
{

	if( m_iDataSocket )
	{
		closesocket( m_iDataSocket );
		m_iDataSocket=0;
	}

	if( m_iCommandSocket )
	{
		closesocket( m_iCommandSocket );
		m_iCommandSocket=0;
	}

}

void Cftp::ZeroStuff(void)
{
	m_iBytesRead = 0;
	m_iFileSize = 0;
	m_szRemoteFilePath[ 0 ] = (char)0;
	m_szRemoteFileName[ 0 ] = (char)0;
	m_szLocalFilePath[ 0 ] = (char)0;
	m_szLocalFileName[ 0 ] = (char)0;
	m_szServerName[ 0 ] = (char)0;
	m_szUserName[ 0 ] = (char)0;
	m_szPassword[ 0 ] = (char)0;
	m_iDataSocket = 0;
	m_iCommandSocket = 0;
	m_iFilePos = 0;
	m_iStatus = FTPSTAT_INIT;
	m_sendNewPortStatus = 0;
	m_pfLocalFile = nullptr;
	m_findStart = 0;
	memset(&m_CommandSockAddr, 0, sizeof(m_CommandSockAddr));
	memset(&m_DataSockAddr, 0, sizeof(m_DataSockAddr));
}

// BEATO Begin:
#if defined( _WIN32 )
DWORD WINAPI gethostbynameA( void * szName )
{
	HOSTENT *he = gethostbyname( (const char *)szName );
   //////DBGMSG("Hostname copy start");

	if (he)
		memcpy((char *)&(gThreadAddress.sin_addr), he->h_addr, he->h_length );
	else
		memcpy((char *)&(gThreadAddress.sin_addr),"",strlen("")+1);
   /////DBGMSG("Hostname copy complete");

	gThreadFlag = 1;
	return 0;
}
#else
void* gethostbyname_thread( void* szName )
{
    const char* hostname = (const char*)szName;
    struct hostent* he = gethostbyname( hostname );

    if (he && he->h_addr_list && he->h_addr_list[0]) {
        memcpy(&( gThreadAddress.sin_addr ), he->h_addr_list[0], he->h_length);
    } else {
        memset(&( gThreadAddress.sin_addr ), 0, sizeof(gThreadAddress.sin_addr));
    }

    gThreadFlag = 1;
    return nullptr;
}
#endif
// BEATO End

int Cftp::AsyncGetHostByName(char * szName, struct sockaddr_in &address )
{
	static int            stat = 0;
	static unsigned long  threadid;

	if( stat == 0 )
	{
		// Kick off gethostname thread 
		gThreadFlag = 0;
    	memset(&gThreadAddress,0,sizeof(gThreadAddress));

// BEATO Begin:
#if defined( _WIN32 )
		if( CreateThread( NULL, 0, gethostbynameA, szName, 0, &threadid ) == NULL )
		#elif defined( __linux__ )
		if (pthread_create(&threadid, NULL, gethostbyname_thread, szName) != 0 )
#endif // __linux__
			return FTP_FAILED ;
// BEATO End

		stat = 1;
	}
	if( stat == 1 )
	{
		if( gThreadFlag )
		{
			/* Thread finished */
         address = gThreadAddress;
         address.sin_family=AF_INET;
			stat = 0;
			return FTP_SUCCEEDED ;
		}
	}

	return FTP_TRYING;
}

/*$_Function****************************************************************
* $_Name        :
*	int  Cftp::ConnectToServer(const char* szServerName)
*
* $_Description :
*	Overloaded funciton that makes a connection to a server.  Will probably
*	fail on (at least) the first call, as it may take a while for the server
*	to send it's "ready" reply.
*
* $_Parameters  :
*	-> const char * szServerName 
*	Optionally, the name of the server to connect to.  This must be specified
*	in the first call to the function.
*
* $_ReturnValue :
*	FTP_TRYING until the connection has succeeded, then FTP_SUCCEEDED.
*	FTP_FAILED on error.
*
***************************************************************************/


int  Cftp::ConnectToServer(const char* szServerName)
{
	struct sockaddr_in  address;
	unsigned long       uTemp;
	unsigned long       serverIP;
	char                buffer[ 256 ];
	int                 iReply, error;

	strncpy( m_szServerName, szServerName, 128 );

	if( m_iStatus == FTPSTAT_INIT )
	{
		/* Find the IP address of the server */

		serverIP = inet_addr( m_szServerName );

		memset( &m_CommandSockAddr, 0, sizeof( m_CommandSockAddr ) );
		m_CommandSockAddr.sin_family = AF_INET;

		if( serverIP == INADDR_NONE )
		{
			/* It's an FQDN - hopefully. */
         ////////DBGMSG("Async gethostbyname");
			if( AsyncGetHostByName( m_szServerName, address ) == FTP_TRYING )
				return FTP_TRYING;
			
         //////DBGMSG("Got hostbyname");

			if( address.sin_addr.s_addr == 0 )
            ///////DBGMSG("gethostbyname failed");
				return FTP_FAILED;


         m_CommandSockAddr=address;

			///////memcpy( (char *)&(m_CommandSockAddr.sin_addr), he.h_addr, he.h_length );

		serverIP = m_CommandSockAddr.sin_addr.s_addr;
         //////DBGMSG("ServerIP = "<<serverIP);

         /////DBGMSG("Memcpy OK");
		}
		else
		{
			m_CommandSockAddr.sin_addr.s_addr = serverIP;
		}


		/* Set port number. */

		m_CommandSockAddr.sin_port = htons( 21 );

		/* Open a socket. */

		m_iCommandSocket = socket( AF_INET, SOCK_STREAM, 0 );

		if( m_iCommandSocket < 0 )
			return FTP_FAILED;

      //////DBGMSG("Socket created");

		/* Set socket to non-blocking */

		uTemp = 1;

		if (Use_Non_Blocking_Mode()) 
		{
			if( ioctlsocket( m_iCommandSocket, FIONBIO, &uTemp ) == SOCKET_ERROR )
				return FTP_FAILED;
		}

		// Go ahead and advance the state....
		m_iStatus = FTPSTAT_CONNECTING;


		// Start the connection process....
		if( connect( m_iCommandSocket, (struct sockaddr *)&m_CommandSockAddr, sizeof( m_CommandSockAddr ) ) == -1 )
		{
#if defined( _WIN32 )
			error = WSAGetLastError();
			if( ( error == WSAEWOULDBLOCK ) || ( error == WSAEINVAL ) || ( error == WSAEALREADY ) )
				return FTP_TRYING;

			if( error != WSAEISCONN )
			{
				////////DBGMSG("Connect failed");
				closesocket( m_iCommandSocket );
				return FTP_FAILED;
			}
#elif defined( __linux__ )
			error = errno;
			if (error == EINPROGRESS || error == EALREADY || error == EINVAL)
				return FTP_TRYING;

			if( error != EISCONN )
			{
				////////DBGMSG("Connect failed");
				close( m_iCommandSocket );
				return FTP_FAILED;
			}
#endif
		}
	}

	if( m_iStatus == FTPSTAT_CONNECTING )
	{
		// Check to see if we're connected
		fd_set wset;
		fd_set eset;
		FD_ZERO(&wset);
		FD_ZERO(&eset);
		FD_SET(m_iCommandSocket,&wset);
		FD_SET(m_iCommandSocket,&eset);
		timeval tv;
		tv.tv_sec=0;
		tv.tv_usec=0;
		int retval=select(m_iCommandSocket+1,0,&wset,&eset,&tv);
		if (retval == 0)	// not ready yet....
			return(FTP_TRYING);
		if (FD_ISSET(m_iCommandSocket, &eset)) 
		{
			// OK, the exception flag is set, guess we couldn't connect....
#if defined( _WIN32 )
			closesocket( m_iCommandSocket );
#else
			close( m_iCommandSocket );
#endif
			return( FTP_FAILED );
		}
		if (FD_ISSET(m_iCommandSocket, &wset)) {
			// OK, the write flag is set, we're good to go...
			m_iStatus = FTPSTAT_WAITINGSERVEROK;
		}
	}

	if( m_iStatus == FTPSTAT_WAITINGSERVEROK )
	{
		iReply=0;
		if (RecvReply( buffer, 256, &iReply ) != FTP_SUCCEEDED) 
			return(FTP_TRYING);

		if (iReply != FTPREPLY_SERVEROK)
			return(FTP_FAILED);

		m_iStatus = FTPSTAT_CONNECTED;
		return( FTP_SUCCEEDED );
	}

	return( FTP_FAILED );

}




/*$_Function****************************************************************
* $_Name        :
*	STDMETHOD Cftp::LoginToServer( const char* szUserName, const char* szPassword )
*
* $_Description :
*	Logs into a server.  ConnectToServer() must have succeeded before this
*	call is made.
*
* $_Parameters  :
*	-> const char* szUserName
*	The username under which to log in.
*
*	-> const char* szPassword
*	The password to use.
*
* $_ReturnValue :
*	FTP_TRYING until the login has succeeded, then FTP_SUCCEEDED.
*	FTP_FAILED on error.
*
***************************************************************************/


int  Cftp::LoginToServer( const char* szUserName, const char* szPassword )
{
	char command[ 256 ];
	int iReply;

	strncpy( m_szUserName, szUserName, 128 );
	strncpy( m_szPassword, szPassword, 128 );

	memset( command, 0, 256 );

	if( m_iStatus == FTPSTAT_CONNECTED )
	{
		sprintf( command, "USER %s\r\n", m_szUserName );

		if( SendCommand( command, 7 + strlen( m_szUserName ) ) < 0 )
		{
			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_SENDINGUSER;
	}

	if( m_iStatus == FTPSTAT_SENDINGUSER )
	{
		if(RecvReply( command, 256, &iReply ) != FTP_SUCCEEDED ) 
			return( FTP_TRYING );

		if (iReply != FTPREPLY_PASSWORD)
			return( FTP_FAILED );

		m_iStatus = FTPSTAT_SENTUSER;
	}

	if( m_iStatus == FTPSTAT_SENTUSER )
	{
		sprintf( command, "PASS %s\r\n", m_szPassword );

		if( SendCommand( command, 7 + strlen( m_szPassword ) ) < 0 )
		{
			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_SENDINGPASS;
	}

	if( m_iStatus == FTPSTAT_SENDINGPASS )
	{
		if( RecvReply( command, 256, &iReply ) != FTP_SUCCEEDED )
		{
			return( FTP_TRYING );
		}

		if( iReply != FTPREPLY_LOGGEDIN )
		{
			if( iReply == FTPREPLY_CONTROLCLOSED )
			{
				return( FTP_FAILED );
			}

			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_LOGGEDIN;

		return( FTP_SUCCEEDED );
	}

	return( FTP_FAILED );
}


/*$_Function****************************************************************
* $_Name        :
*	STDMETHOD Cftp::LogoffFromServer( void )
*
* $_Description :
*	Logs off from a server.  LoginToServer() must have succeeded before this
*	call is made.
*
* $_Parameters  :
*	None.
*
* $_ReturnValue :
*	FTP_TRYING until the logoff has succeeded, then FTP_SUCCEEDED.
*	FTP_FAILED on error.
*
***************************************************************************/


int  Cftp::LogoffFromServer( void )
{
	char command[ 256 ];
	int iReply, iRetCode;

	memset( command, 0, 256 );

	switch( m_iStatus )
	{
		case FTPSTAT_LOGGINGOFF:
			if( SendCommand( "QUIT\r\n", 6 ) == FTP_SUCCEEDED )
			{
				m_iStatus = FTPSTAT_SENDINGQUIT;
			}
			else
			{
				return( FTP_FAILED );
			}

		case FTPSTAT_SENDINGQUIT:
		{
			char buf[ 50 ];

			if( ( iReply = RecvReply( buf, 50, &iRetCode ) ) == FTP_SUCCEEDED )
			{
				if( iRetCode == 221 )
				{
					//m_iStatus = FTPSTAT_SENTQUIT;

                    //m_iStatus = FTPSTAT_INIT;  // NAK

					CloseSockets();
					ZeroStuff();

					return( FTP_SUCCEEDED );
				}
			}
			else
			{
				if( iReply == FTP_FAILED )
				{
					return( FTP_FAILED );
				}
				return( FTP_TRYING );
			}
		}

		default:
			m_iStatus = FTPSTAT_LOGGINGOFF;
			return( FTP_TRYING );

	}

}






/*$_Function****************************************************************
* $_Name        :
*	int  Cftp::FindFile( const char* szRemoteFileName, int * piSize )
*
* $_Description :
*	Locates a file on the remote server.
*
* $_Parameters  :
*	-> const char* szRemoteFileName
*	Full path and file name of the file to be downloaded.
*
*	<- int * piSize
*	A pointer to an integer in which to return the size of the file, in bytes.
*
* $_ReturnValue :
*	FTP_SUCCEEDED on success.  Otherwise FTP_TRYING, or FTP_FAILED on error.
*
* $_Warnings    :
*	This function will continue to return FTP_TRYING if the file does not exist on 
*	the server.
*
***************************************************************************/



int  Cftp::FindFile( const char* szRemoteFileName, int * piSize )
{
	char command[ 256 ];
	static char listline[ 256 ];

	int i, iReply;
	char ext[ 10 ];

	if (m_findStart==0)
      m_findStart=time(NULL);

	if((time(NULL)-m_findStart) > 30)  // try for 30 seconds
	{
        /////////DBGMSG("FindFile: Tried for too long");
        m_findStart=0;
		return FTP_FAILED;
	}

#if 1
	// TODO: this is a temp fix, do a better way 
	int32_t e = 0;
	int32_t i = std::strlen( m_szRemoteFilePath );
	do
	{
		if ( ( i == 0 ) || ( m_szRemoteFilePath[i] == '/0' ) )
		{	
			e = 0;
			i = 0;
			break;
		}		
		
		if( m_szRemoteFilePath[i] == '.' )
			break;

		e++;
		i--;
	} while ( e < 10 );
	
	std::strncpy( ext, &m_szRemoteFilePath[i], e );

#else
	//strcpy(m_szRemoteFilePath, "/");  // start at home
	_splitpath( szRemoteFileName, NULL, m_szRemoteFilePath + strlen(m_szRemoteFilePath), m_szRemoteFileName, ext );
#endif

	strcat( m_szRemoteFileName, ext );

	for( i = 0; i < (int)strlen( m_szRemoteFilePath ); i++ )
	{
		if( m_szRemoteFilePath[ i ] == '\\' )
		{
			m_szRemoteFilePath[ i ] = '/';
		}
	}

	std::memset( command, 0, 256 );

	// Change directory
	if( ( m_iStatus == FTPSTAT_LOGGEDIN ) || ( m_iStatus == FTPSTAT_FILEFOUND ) )
	{
		sprintf( command, "CWD %s\r\n", m_szRemoteFilePath );

		if( SendCommand( command, 6 + strlen( m_szRemoteFilePath ) ) < 0 )
			return FTP_TRYING;

		m_iStatus = FTPSTAT_SENDINGCWD;
	}


	// Get reply 
	if( m_iStatus == FTPSTAT_SENDINGCWD )
	{
		int reply=RecvReply( command, 256, &iReply );

		if ((reply == FTP_SUCCEEDED) && (iReply == 550)) {
			m_findStart=0;
			return(FTP_FAILED);
		}

		if( ( reply != FTP_SUCCEEDED ) ||
			( iReply != FTPREPLY_CWDOK ) )
		{
			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_SENTCWD;
	}

	/* Set up data connection port */

	if( m_iStatus == FTPSTAT_SENTCWD )
	{
		i = 0;
		while( SendNewPort() == FTP_TRYING )
		{
			i++;

			if( i == 1000 )
			{
				return( FTP_TRYING );
			}
		}

		m_iStatus = FTPSTAT_SENTPORT;
	}

	/* Get directory listing for file. */

	if( m_iStatus == FTPSTAT_SENTPORT )
	{
		sprintf( command, "LIST %s\r\n", m_szRemoteFileName );

		if( SendCommand( command, 7 + strlen( m_szRemoteFileName ) ) < 0 )
		{
			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_SENDINGLIST;
	}


	/* Get reply */

	if( m_iStatus == FTPSTAT_SENDINGLIST )
	{
		if( ( RecvReply( command, 256, &iReply ) != FTP_SUCCEEDED ) ||
			( iReply != FTPREPLY_OPENASCII ) )
		{
			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_SENTLIST;
	}

	/* Open data connection */

	if( m_iStatus == FTPSTAT_SENTLIST )
	{
		i = OpenDataConnection();
		if( i != FTP_SUCCEEDED )
		{
            /////////DBGMSG("FindFile: OpenDataConnection failed: "<<i);
            m_findStart=0;
			return( i );
		}
		m_iStatus = FTPSTAT_LISTDATAOPEN;
		memset( listline, 0, 256 );
	}


	/* Get data */

	if( m_iStatus == FTPSTAT_LISTDATAOPEN )
	{
		RecvData( listline, 256 );

		if( strlen( listline ) == 0 )
		{
			return( FTP_TRYING );
		}
		m_iStatus = FTPSTAT_LISTDATARECVD;
	}

	/* Wait for confirmation of end of data stream */

	if( m_iStatus == FTPSTAT_LISTDATARECVD )
	{
		if( ( RecvReply( command, 256, &iReply ) != FTP_SUCCEEDED ) ||
			( iReply != FTPREPLY_COMPLETE ) )
		{
			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_FILEFOUND;
	}

	CloseDataConnection();

	m_findStart=0;

	/* Is the file there? */

	if( strncmp( listline, m_szRemoteFileName, sizeof( m_szRemoteFileName ) ) == 0 )
	{
		/* No */
        ////////DBGMSG("FindFile: File not in list: "<<listline);
		return( FTP_FAILED );
	}

	/* Yes - find out the size, in bytes */

	if( sscanf( &listline[ 32 ], " %d ", &i ) == 1 )
	{
		if( piSize != NULL )
		{
			*piSize = i;
			m_iFileSize = i;
		}
		return( FTP_SUCCEEDED );
	}
	
    ////////DBGMSG("Default fail case: "<<listline);
	return( FTP_FAILED );
}





/*$_Function****************************************************************
* $_Name        :
*	int  Cftp::SendCommand( const char* pCommand, int iSize )
*
* $_Description :
*	Sends a command to the server.  Commands are strings terminated with
*	"\r\n"
*
* $_Parameters  :
*	const char* pCommand
*	A pointer to a command
*
*	int iSize
*	The size of the command in bytes.
*	
* $_ReturnValue :
*	FTP_SUCCEEDED on success, or FTP_FAILED on error.
*
***************************************************************************/

int  Cftp::SendCommand( const char* pCommand, int iSize )
{
	int i;
	
	i = send( m_iCommandSocket, pCommand, iSize, 0 );

	if( i > 0 )
	{
#ifdef _DEBUG
		OutputDebugString( "-->" );
		OutputDebugString( pCommand );
#endif
		return( FTP_SUCCEEDED );
	}
	else
	{
		return( FTP_FAILED );
	}
}




/*$_Function****************************************************************
* $_Name        :
*	int  Cftp::RecvReply( const char* pReplyBuffer, int iSize, int * piRetCode )
*
* $_Description :
*	Receives a reply from the server and extracts the numerical reply
*	code.
*
* $_Parameters  :
*	-> const char* pReplyBuffer
*	A buffer for the reply - must be specified and be at least 4 bytes in 
*	length.
*
*	-> iSize
*	The size of the reply buffer.
*
*	<- piRetCode
*	A pointer to an integer to store the numeric return code for the message received.
*
* $_ReturnValue :
*	FTP_SUCCEEDED on success, FTP_FAILED otherwise.
*
***************************************************************************/


int  Cftp::RecvReply( const char* pReplyBuffer, int iSize, int * piRetCode )
{
	int readval;
	char * pc = (char *)pReplyBuffer;

	while(1) {
		// Preview whats on the socket so we can make the decision if there is enough
		// there to use.
		readval = recv(m_iCommandSocket, pc, iSize-1, MSG_PEEK);
		pc[iSize-1]=0;
		if (readval > 0)
			pc[readval]=0;

		// Did the endpoint close?
		if (readval < 0) 
		{
#if defined( _WIN32 )
			if ((WSAGetLastError() == WSAECONNRESET ) || ((WSAGetLastError() == WSAENOTCONN)))
#else
			if( ( errno == ECONNRESET ) || ( errno == ENOTCONN) )
#endif
				readval = 0;
			else 
				return FTP_TRYING; // nothing to read right now....
		}

		if (readval == 0) 
		{
			// endpoint closed
			*piRetCode=FTPREPLY_CONTROLCLOSED;
			return FTP_SUCCEEDED;		// we succeeded in getting a reply
		}

		if (readval < 3)  // minimal response
			return FTP_TRYING;

		// Verify that this is a complete line, if not we will keep trying til
		// we have one.
		char *end=strstr(pc, "\r\n");
		if (end == 0)
			return FTP_TRYING;

		// OK, we've got a line, pull it from the socket...
		recv(m_iCommandSocket, pc, end-pc+strlen("\r\n"), 0);
#ifdef _DEBUG
		OutputDebugString( "<--" );
		OutputDebugString( pc );
#endif

		// Is this an unrecognized command?  It's probably in response to our BOGUSCOMMAND, ignore it.
		// If we got this for some other reason then this FTP server doesn't support our required command set.
		// If this were a general purpose FTP library we probably couldn't get away with this because it's pretty lame.
		const char *BOGUS_RESPONSE="500";
#if defined( _WIN32 )
		if (_strnicmp(pc, BOGUS_RESPONSE, strlen(BOGUS_RESPONSE))==0)
			continue;
#elif defined( __linux__ )
		if (strncasecmp( pc, BOGUS_RESPONSE, strlen(BOGUS_RESPONSE))==0)
			continue;
#endif

		// If the line starts with a non-digit then we ignore it...
		if (isdigit(pc[0])==0)
			continue;

		if (piRetCode)
			*piRetCode=atol(pc);

		return( FTP_SUCCEEDED );
	}
}


/*$_Function****************************************************************
* $_Name        :
*	unsigned long MyIPAddress( int sockfd )
*
* $_Description :
*	Finds the IP address of the local host.
*
* $_Parameters  :
*	-> int sockfd
*	An optional socket descriptor - if this is given and the socket is connected
*   then the answer will guaranteed to be on the same interface as the connected 
*	socket.
*
* $_ReturnValue :
*	A unsigned integer containing the IP address of the local host.
*
***************************************************************************/


unsigned long MyIPAddress( int sockfd )
{
	int		 test = 99;
	socklen_t i = 0;
	char pBuffer[ 256 ];
	char * pAddr = nullptr;
	struct hostent * pHE;
	unsigned long ip;
	struct sockaddr_in sin;

	if( sockfd != -1 )
	{
		i = sizeof( sin );
		getsockname( sockfd, (struct sockaddr *)&sin, &i );

#ifdef _WIN32
		ip = sin.sin_addr.S_un.S_addr;
#else
		ip = sin.sin_addr.s_addr;
#endif
	}
	else
	{
		// Get this machine's name. 
		if( gethostname( pBuffer, 256 ) != 0 )
			return FTP_FAILED ;

		/* Look up the machine in "DNS" or whatever. */

		pHE = gethostbyname( pBuffer );

		if( pHE == NULL )
			return FTP_FAILED;

		/* Find a good IP address. */

		ip = 0;

		i = 0;
		
		while( ( pAddr = pHE->h_addr_list[ i++ ] ) != nullptr )
		{

			ip = *((unsigned long *)pAddr );

			if( ( ip != 0 ) && ( ip != inet_addr( "127.0.0.1" ) ) )
				break;
			else
				ip = 0;

		}
	}

	if( ip == 0 )
		return FTP_FAILED;

	return( ip );
}



/*$_Function****************************************************************
* $_Name        :
*	int Cftp::SendNewPort( void )
*
* $_Description :
*	Sends a PORT command to the server specifying a new ephemeral port to 
*	use for a data connection.  Opens the port in the process.
*
* $_Parameters  :
*	bool reset
*	Should be TRUE for the first attempt, FALSE subsequently.
*
* $_ReturnValue :
*	FTP_SUCCEEDED on success, FTP_FAILED on error, FTP_TRYING while
*	going through the stages.
*
***************************************************************************/


int Cftp::SendNewPort( void )
{
	unsigned long uTemp;
	char command[ 256 ];
	socklen_t i = 0; 
	int iReply;

	/* Open a socket */

	if( m_sendNewPortStatus == 0 )
	{

		m_iDataSocket = socket( AF_INET, SOCK_STREAM, 0 );

		if( m_iDataSocket < 0 )
			return FTP_FAILED;

		/* Set socket to non-blocking */

		uTemp = 1;

		if (Use_Non_Blocking_Mode()) 
		{
			if( ioctlsocket( m_iCommandSocket, FIONBIO, &uTemp ) == SOCKET_ERROR )
				return FTP_FAILED;
		}

		memset( &m_DataSockAddr, 0, sizeof( m_DataSockAddr ) );

		m_DataSockAddr.sin_family		 = AF_INET;
		m_DataSockAddr.sin_addr.s_addr = htonl( INADDR_ANY );
		m_DataSockAddr.sin_port		 = 0; // Winsock fills in an ephemeral port during bind...

		if( bind( m_iDataSocket, (struct sockaddr *)&m_DataSockAddr, sizeof( m_DataSockAddr ) ) < 0 )
			return FTP_FAILED;

		i = sizeof( m_DataSockAddr);

		getsockname( m_iDataSocket, (struct sockaddr *)&m_DataSockAddr, &i );

		listen( m_iDataSocket, 5 );


		// Set socket to non-blocking

		uTemp = 1;


		if (Use_Non_Blocking_Mode()) 
		{
			if( ioctlsocket( m_iDataSocket, FIONBIO, &uTemp ) == SOCKET_ERROR )
				return FTP_FAILED;
		}


		m_sendNewPortStatus = 1;
	}

	/* Send a port command. */

	if( m_sendNewPortStatus == 1 )
	{
		memset( command, 0, 256 );

		i = MyIPAddress( m_iCommandSocket );

		if( i == FTP_FAILED )
		{
			return( FTP_FAILED );
		}

		sprintf( command, "PORT %d,%d,%d,%d,%d,%d\r\n", 
				 i & 0xFF,
				 ( i >> 8 ) & 0xFF, 
				 ( i >> 16 ) & 0xFF, 
				 ( i >> 24 ) & 0xFF, 
				 m_DataSockAddr.sin_port & 0xFF,
				 m_DataSockAddr.sin_port >> 8 );

		if( SendCommand( command, strlen(command) ) < 0 )
		{
			return( FTP_TRYING );
		}

		m_sendNewPortStatus = 2;
	}

	/* Get reply */

	if( m_sendNewPortStatus == 2 )
	{
		if( ( RecvReply( command, 256, &iReply ) != FTP_SUCCEEDED ) ||
			( iReply != FTPREPLY_PORTOK ) )
		{
			return( FTP_TRYING );
		}

		m_sendNewPortStatus = 0;
	}

	return( FTP_SUCCEEDED );
}


/*$_Function****************************************************************
* $_Name        :
*	int Cftp::OpenDataConnection()
*
* $_Description :
*	Opens the data connection to the server.  Actually, the socket for the
*	data connection should have been opened by a call to SendNewPort before
*	this method is called - this just calls accept.
*
* $_Parameters  :
*	None.
*
* $_ReturnValue :
*	FTP_SUCCEEDED on success, FTP_FAILED otherwise.
*
* $_Warnings    :
*	This call may block.
*
***************************************************************************/



int Cftp::OpenDataConnection( void )
{
	int iNewSocket;

	if( m_iDataSocket == 0 )
	{
		return( FTP_FAILED );
	}

	if( ( iNewSocket = accept( m_iDataSocket, NULL, 0 ) ) < 0 ) 
	{
#if defined( _WIN32 )
		if( WSAGetLastError() != (WSAEWOULDBLOCK ) )
#elif defined( __linux__ )
		if( errno != EWOULDBLOCK )
#endif
			return FTP_FAILED;
		else
			return FTP_TRYING;
		
	}

	m_iDataSocket = iNewSocket;

	return( FTP_SUCCEEDED );
}



/*$_Function****************************************************************
* $_Name        :
*	void Cftp::CloseDataConnection()
*
* $_Description :
*	Closes the data connection.
*
* $_Parameters  :
*	None.
*
* $_ReturnValue :
*	None.
*
***************************************************************************/


void Cftp::CloseDataConnection()
{
	closesocket( m_iDataSocket );
	m_iDataSocket = 0;
}

/*$_Function****************************************************************
* $_Name        :
*	int  Cftp::DisconnectFromServer()
*
* $_Description :
*	Disconnects from the server.
*
* $_Parameters  :
*	None.
*
* $_ReturnValue :
*	None.
*
***************************************************************************/

int  Cftp::DisconnectFromServer()
{
	// Make the download file read-only so it's still there the next time
	// we're run.

	closesocket( m_iCommandSocket );
	return FTP_SUCCEEDED;
}




/*$_Function****************************************************************
* $_Name        :
*	int  Cftp::SendData( char * pData, int iSize )
*
* $_Description :
*	Sends data to the server.
*
* $_Parameters  :
*	-> char * pData
*	A pointer to some data to be sent.
*
*	-> int iSize
*	The size, in bytes, of the data.
*
* $_ReturnValue :
*	The number of bytes sent, or -1 on error.
*
***************************************************************************/

int  Cftp::SendData( char * pData, int iSize )
{
	return( send( m_iDataSocket, pData, iSize, 0 ) );
}


/*$_Function****************************************************************
* $_Name        :
*	int  Cftp::RecvData( char * pData, int iSize )
*
* $_Description :
*	Receives data from the server.
*
* $_Parameters  :
*	-> const char* pData
*	A pointer to a buffer for the data to be received.
*
*	-> int iSize
*	The size, in bytes, of the data buffer.
*
* $_ReturnValue :
*	The number of bytes received, or -1 on error.
*
***************************************************************************/

int  Cftp::RecvData( char * pData, int iSize )
{
/***** testing...
	int readval = recv(m_iDataSocket, pData, iSize, MSG_PEEK);
	if (readval <= 0)		// If there's nothing to read, don't read now...
		return(readval);
******/

	return( recv( m_iDataSocket, pData, iSize, 0 ) );
}


/*$_Function****************************************************************
* $_Name        :
*	int  Cftp::GetNextFileBlock( const char* szLocalFileName, int * piTotalRead )
*
* $_Description :
*	Retrieves the next block of data from the remote file and writes it into
*	the local file.  Deals with opening the local file and restarting a 
*	failed transfer if FileRecoveryPosition() returns non-zero.  To prevent
*	a restart after FileRecoveryPosition() returns non-zero, call 
*	Cftp::RestartFrom() with 0 as the offset parameter.
*	
*	The file is initally written to a temporary file and then copied to the local
*	file name when the transfer is complete.  If the transfer is halted, the 
*	temporary file will be used as the starting point for subsequent retries.
*
* $_Parameters  :
*	-> const char* szLocalFileName
*	A pointer to a string containing the local file name for the transferred file.
*
*	<- int * piTotalRead
*	A pointer to an integer in which to store the total number of bytes
*	transferred so far.
*
* $_ReturnValue :
*	FTP_TRYING while the transfer is in progress, FTP_SUCCEEDED on completion, 
*	FTP_FAILED on error.
*
***************************************************************************/

int  Cftp::GetNextFileBlock( const char* szLocalFileName, int * piTotalRead )
{
	char command[ 256 ];
	int read, totread = 0;

	const int max_data_len=10240;

	char data[ max_data_len ];
	int res, iReply;

	char downloadfilename[256];
	GetDownloadFilename(szLocalFileName, downloadfilename);


	//char str[ 256 ];
	std::strncpy( m_szLocalFileName, szLocalFileName, 128 );

	// Open local file

	if( m_iStatus == FTPSTAT_FILEFOUND )
	{
		if( m_iFilePos == 0 )
		{
			if( ( m_pfLocalFile = fopen( downloadfilename, "wb" ) ) == nullptr )
				return FTP_FAILED;
		}
		else
		{
			if( ( m_pfLocalFile = fopen( downloadfilename, "ab" ) ) == nullptr )
				return FTP_FAILED;
		}
		m_iStatus = FTPSTAT_FILEOPEN;
	}

	// Send the PORT command

	if( m_iStatus == FTPSTAT_FILEOPEN )
	{
		if( SendNewPort() == FTP_SUCCEEDED )
			m_iStatus = FTPSTAT_SENTFILEPORT;
		else
			return FTP_TRYING;
	}

	// Set type to BINARY

	if( m_iStatus == FTPSTAT_SENTFILEPORT )
	{
		sprintf( command, "TYPE I\r\n");

		if( SendCommand( command, strlen( command ) ) < 0 )
			return FTP_TRYING; 

		m_iStatus = FTPSTAT_SENDINGTYPE;
	}

	/* Get reply */

	if( m_iStatus == FTPSTAT_SENDINGTYPE )
	{
		if( ( RecvReply( command, 256, &iReply ) != FTP_SUCCEEDED ) || ( iReply != FTPREPLY_TYPEOK ) )
		{
			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_SENTTYPE;
	}

	// Send the RESTART command - if we are restarting a previous transfer.

	if( m_iStatus == FTPSTAT_SENTTYPE )
	{
		if( m_iFilePos == 0 )
		{
			m_iStatus = FTPSTAT_SENTREST;
		}
		else
		{
			sprintf( command, "REST %d\r\n", m_iFilePos );

			if( SendCommand( command, strlen( command ) ) < 0 )
			{
				return( FTP_TRYING ); 
			}

			m_iStatus = FTPSTAT_SENDINGREST;
		}
	}

	/* Get reply */

	if( m_iStatus == FTPSTAT_SENDINGREST )
	{
		int res=RecvReply( command, 256, &iReply );

		if ((res == FTP_FAILED) || (iReply == 502))  // unsupported command
		{
			m_iFilePos=0;
			fclose(m_pfLocalFile);
			m_pfLocalFile = fopen( downloadfilename, "wb" );
		}
		else if( ( res != FTP_SUCCEEDED ) ||
			( iReply != FTPREPLY_RESTARTOK ) )
		{
			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_SENTREST;
	}


	// Send the RETR command

	if( m_iStatus == FTPSTAT_SENTREST )
	{
		sprintf( command, "RETR %s\r\n", m_szRemoteFileName );

		if( SendCommand( command, strlen( command ) ) < 0 )
		{
			return( FTP_TRYING ); 
		}

		m_iStatus = FTPSTAT_SENDINGRETR;
	}

	/* Get reply */

	if( m_iStatus == FTPSTAT_SENDINGRETR )
	{

		if( ( RecvReply( command, 256, &iReply ) != FTP_SUCCEEDED ) ||
			( iReply != FTPREPLY_OPENBINARY ) )
		{
			return( FTP_TRYING );
		}

		m_iStatus = FTPSTAT_SENTRETR;
	}

	/* Open data connection */

	if( m_iStatus == FTPSTAT_SENTRETR )
	{
		res = OpenDataConnection();
		if( res != FTP_SUCCEEDED )
		{
			return( res );
		}
		m_iStatus = FTPSTAT_FILEDATAOPEN;
	}


	/* Get data */

	if( m_iStatus == FTPSTAT_FILEDATAOPEN )
	{
		do
		{
			read = RecvData( data, max_data_len );
			if( read > 0 )
			{
				fwrite( data, 1, read, m_pfLocalFile );
				totread += read;
			}
		}
		while( ( read > 0 ) && ( totread < (max_data_len * 20) ) );  // Don't read too much - 
															// must not block for too long


		m_iFilePos += totread;   // update read position

		if( piTotalRead != NULL )
			*piTotalRead = m_iFilePos;


		// look for all notices about endpoint closed...
		if (read < 0) 
		{
// BEATO Begin:
#if defined( _WIN32 )
			int wsa_err=WSAGetLastError();
			if ((wsa_err == WSAECONNRESET) || (wsa_err == WSAENOTCONN))
				read = 0;		// just treat it as a close....
#elif defined( __linux__ )
			int wsa_err = errno;
			if (( wsa_err == ECONNRESET ) || ( wsa_err == ENOTCONN ) )
				read = 0;		// just treat it as a close....
#endif
// BEATO End
		}


		/* See if the download has finished */

		if( read == 0 )
		{
			// Data connection reset 
			if( m_iFilePos != m_iFileSize ) {
				// Haven't got all the data
				return( FTP_FAILED );
			} else {
				// got all the data and the connection is closed so mark it so
				m_iStatus = FTPSTAT_FILEDATACLOSED;
			}
		} else {
			return( FTP_TRYING );
		}
	}

	// if we have gotten to here, we have all the data and the connection is 
	// closed.  The case where the connection was closed but we didn't get
	// everything is handled above.
	if( m_iStatus == FTPSTAT_FILEDATACLOSED )	
	{
		CloseDataConnection();
		fclose( m_pfLocalFile );
		m_pfLocalFile = NULL;

		//
		// Move the file from the temporary download location to its
		// final resting place
		//

		char downloadfilename[256];
		GetDownloadFilename(m_szLocalFileName, downloadfilename);

		// Make sure the path exists for the new file
		char curdir[256];
		getcwd(curdir,256);
		Prepare_Directories(curdir, m_szLocalFileName);
		DEBUG_LOG(("CWD: %s\n", curdir));

		if( rename( downloadfilename, m_szLocalFileName ) != 0 )	{
			DEBUG_LOG(("First rename of %s to %s failed with errno of %d\n", downloadfilename, m_szLocalFileName, errno));
			// Error moving file - remove file that's already there and try again. */
			chmod( m_szLocalFileName, S_IWRITE | S_IREAD );	// make sure it's not readonly
			DEBUG_LOG(("_chmod of %s failed with errno of %d\n", m_szLocalFileName, errno));
			remove( m_szLocalFileName );
			DEBUG_LOG(("remove of %s failed with errno of %d\n", m_szLocalFileName, errno));

			if( rename( downloadfilename, m_szLocalFileName ) != 0 )	{
				DEBUG_LOG(("Second rename of %s to %s failed with errno of %d\n", downloadfilename, m_szLocalFileName, errno));
				return( FTP_FAILED );
			}
		}

		// Send a bogus command.  If the firewall has closed our ftp command channel connection this 
		// will allow us to detect it.  (Obviously the data channel is closed or we wouldn't be here)
		// There are cases (firewall) where the connection will go away without having a close command
		// but writing to it will allow us to detect this case.
		// We will ignore the response because we don't know in which order the server will respond
		SendCommand("BOGUSCOMMAND\r\n", strlen("BOGUSCOMMAND\r\n"));

		OutputDebugString("File closed, waiting for response.\n");

		m_iStatus = FTPSTAT_TRANSFERREPLY;
	}


	if( m_iStatus == FTPSTAT_TRANSFERREPLY ) 
	{
		iReply=0;

		// Get the file complete reply
		if (RecvReply( command, 256, &iReply ) != FTP_SUCCEEDED )
			return(FTP_TRYING);

		if (iReply == FTPREPLY_CONTROLCLOSED) 
		{
			m_iStatus = FTPSTAT_INIT;
			m_iFilePos=0;
			CloseSockets();
		} 
		else 
		{
			m_iStatus = FTPSTAT_LOGGEDIN;
			m_iFilePos=0;
		}
		return FTP_SUCCEEDED;
	}

	return FTP_FAILED;
}



/*$_Function****************************************************************
* $_Name        :
*	int  Cftp::FileRecoveryPosition( const char* szLocalFileName )
*
* $_Description :
*	Finds the size of the specified file.  This size can be used
*
* $_Parameters  :
*	char & szLocalFileName
*	The full path name of the local file.
*
* $_ReturnValue :
*	The size of that file on the local disk.  0 if the file does not exist.
*
***************************************************************************/


//
// Do we have this file in the download directory?  If so then it's a partial download.
//
//
int  Cftp::FileRecoveryPosition( const char* szLocalFileName, const char* szRegistryRoot )
{
	char downloadfilename[256];
	GetDownloadFilename(szLocalFileName, downloadfilename);

	FILE *testfp = fopen( downloadfilename, "rb" );
	if( testfp == NULL )
	{
		m_iFilePos = 0;
		return 0;
	}

	fseek( testfp, 0, SEEK_END );
	m_iFilePos = ftell( testfp );
	fclose( testfp );

	return( m_iFilePos );
}

/*************8
	FILE * testfp;
	HKEY hkey;
	unsigned char regfilename[ 256 ];
	char regkey[ 512 ];
	unsigned long t1, t2;

	if( ( szRegistryRoot == NULL ) || ( szLocalFileName == NULL ) )
	{
		// Bail out
		return( 0 );
	}

	// Concatenate the registry key together

	strcpy( regkey, szRegistryRoot );
	if( regkey[ strlen( regkey ) - 1 ] != '\\' )
	{
		strcat( regkey, "\\Download" );
	}
	else
	{
		strcat( regkey, "Download" );
	}

	if( RegOpenKeyEx( HKEY_LOCAL_MACHINE, (LPCTSTR)regkey, 
		0, KEY_ALL_ACCESS, &hkey ) != ERROR_SUCCESS )
	{
		// Key doesn't exist, create it
		if( RegCreateKey( HKEY_LOCAL_MACHINE, (LPCTSTR)regkey, 
			&hkey ) != ERROR_SUCCESS )
		{
			// Error, bail out
			return( 0 );
		}

		RegSetValueEx( hkey, (LPCTSTR)"File", 0, REG_SZ, (const unsigned char *)szLocalFileName, strlen( szLocalFileName ) + 1 );
		RegCloseKey(hkey);

		return( 0 );
	}

	t2 = 256;

	if( RegQueryValueEx( hkey, (LPCTSTR)"File", 0, &t1, regfilename, &t2 ) != ERROR_SUCCESS )
	{
		RegSetValueEx( hkey, (LPCTSTR)"File", 0, REG_SZ, (const unsigned char *)szLocalFileName, strlen( szLocalFileName ) + 1 );
		RegCloseKey(hkey);
		return( 0 );
	}

	if( strcmp( szLocalFileName, (const char *)regfilename ) == 0 )
	{
		// File previously downloaded
		testfp = fopen( FTP_TEMPFILENAME, "rb" );

		if( testfp == NULL )
		{
			m_iFilePos = 0;
			RegCloseKey(hkey);
			return 0;
		}

		fseek( testfp, 0, SEEK_END );

		m_iFilePos = ftell( testfp );

		fclose( testfp );

		RegCloseKey(hkey);
		return( m_iFilePos );
	}

	// Download file doesn't exist
	RegSetValueEx( hkey, (LPCTSTR)"File", 0, REG_SZ, (const unsigned char *)szLocalFileName, strlen( szLocalFileName ) + 1 );
	RegCloseKey(hkey);

	// get rid of any temp downloads
	_unlink(FTP_TEMPFILENAME);

	return( 0 );
}
**************************************/



//
// convert a local name to a temp filename to use for downloading
//
void Cftp::GetDownloadFilename(const char *localname, char *downloadname)
{
	char *name = strdup(localname);
	char *s = name;
	while (*s)
	{
		if (*s == '\\' || *s == '.' || *s == ' ')
			*s = '_';
		++s;
	}
	sprintf(downloadname,"download\\%s_%d.tmp",name,m_iFileSize);
	free(name);
	/*
	Wstring name;
	name.set(localname);
	name.replace("\\","_");
	name.replace(".","_");
	name.replace(" ","_");
	sprintf(downloadname,"download\\%s_%d.tmp",name.get(),m_iFileSize);
	*/
	return;
}




//
// Build all the subdirectories for a given filename
//
bool Prepare_Directories(const char *rootdir, const char *filename)
{
	char tempstr[256];
	char newdir[256];

	const char *cptr=filename;
	while(cptr=strchr(cptr,'\\'))
	{
		memset(tempstr,0,256);
		strncpy(tempstr,filename,cptr-filename);
		sprintf(newdir,"%s\\%s",rootdir, tempstr);
#if defined( _WIN32 )
		if (!CreateDirectory(newdir, NULL))
			return false;
#elif defined( __linux__ )
		if ( ( mkdir( newdir, 0 ) == -1 ) && ( ( errno == ENOENT || errno == EACCES ) ) )
			return false;
#endif
		cptr++;
	}
	return true;
}




