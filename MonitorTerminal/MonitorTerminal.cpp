// MonitorTerminal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "dpconsole.h"
#include <conio.h>
#include <iostream>

extern	HANDLE	hPrompt;

int main(int argc, char* argv[])
{
	hPrompt		= CreateEvent( NULL, FALSE, FALSE, NULL );

	CDPConsole dpConsole;
#ifdef __QLORD
//	char sAddr[16]	= "211.39.157.173";
	char sAddr[16]	= "218.145.91.6";
#else	// __QLORD
	char sAddr[16]	= "127.0.0.1";
#endif	// __QLORD

//	char sAddr[16]	= "218.145.91.6";
//	char sAddr[16]	= "192.168.1.103";
//	char sAddr[16]	= "211.39.157.173";

	LOAD_WS2_32_DLL;

	if( FALSE == dpConsole.ConnectToServer( sAddr, PN_MONITOR_1, FALSE ) )
		return 0;

	WaitForSingleObject( hPrompt, INFINITE );

	char buffer[260], lpCommand[260];

	*lpCommand	= '\0';
	while( 1 )
	{
		cin.getline( buffer, 260 );
		CScanner s( buffer );
		s.GetToken();

#ifndef __QLORD
		if( s.Token == "r" )
		{
			dpConsole.SendCommand( buffer );
			WaitForSingleObject( hPrompt, INFINITE );
		}
		 else if ( s.Token == "s" )
		 {
			 dpConsole.SendCommand( buffer );
			 printf( "Command: r, s, q>" );
		 }
		else if( s.Token == "q" )
#else	// __QLORD
		if( s.Token == "q" )
#endif	// __QLORD
		{
			break;
		}
		else if( s.Token == "" )
		{
			dpConsole.SendCommand( buffer );
			WaitForSingleObject( hPrompt, INFINITE );
			sndPlaySound( NULL, SND_ASYNC );
		}
		else if( s.Token == "m" )
		{
			sndPlaySound( NULL, SND_ASYNC );
			printf( "Command: q>" );
		}
		else
		{
			printf( "Command not found\n" );
#ifdef __QLORD
			printf( "Command: q>" );
#else	// __QLORD
			printf( "Command: r, s, q>" );
#endif	// __QLORD
		}
	}

	dpConsole.DeleteDPObject();

	SAFE_DELETE( CAr::m_pHeapMng );
	SAFE_DELETE( CClientSock::m_pPool );
	SAFE_DELETE( CClientSockE::m_pPool );
	SAFE_DELETE( CBuffer::m_pPool );
	SAFE_DELETE( CBuffer::m_pHeapMng );

	UNLOAD_WS2_32_DLL;
	
	return 0;
}