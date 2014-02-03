#include "stdafx.h"
#include "dpconsole.h"

extern	HANDLE	hPrompt;

CDPConsole::CDPConsole()
{
	BEGIN_MSG;
	ON_MSG( PACKETTYPE_CONSOLE_OVERVIEW, OnOverview );
	ON_MSG( PACKETTYPE_ERROR, OnError );
}

CDPConsole::~CDPConsole()
{
}

void CDPConsole::SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
{
	switch( lpMsg->dwType )
	{
		case DPSYS_CREATEPLAYERORGROUP:
		case DPSYS_DESTROYPLAYERORGROUP:
			break;
	}
}

void CDPConsole::UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
{
	CAr ar( (LPBYTE)lpMsg, dwMsgSize );
	GETTYPE( ar );
	void ( theClass::*pfn )( theParameters )
		=	GetHandler( dw );
	
	if( pfn ) {
		( this->*( pfn ) )( ar );
	}
	else {
//		ASSERT( 0 );
	}
}

void CDPConsole::SendCommand( char* buffer )
{
	BEFORESEND( ar, PACKETTYPE_CONSOLE_COMMAND );
	ar.WriteString( buffer );
	SEND( ar, this, DPID_SERVERPLAYER );
}

char	sOverview[1024*32]	= { 0, };
void CDPConsole::OnOverview( CAr & ar )
{
	CTime tm	= CTime::GetCurrentTime();
	printf( "\n%s", tm.Format( "%Y/%m/%d %H:%M:%S" ) );
	printf( "\n--------------------------------------------------------------------------------" );
	*sOverview	= '\0';
	ar.ReadString( sOverview );
#ifdef __QLORD
	HideAddr( sOverview );
#endif	// __QLORD
	printf( "%s", sOverview );
	printf( "--------------------------------------------------------------------------------" );
#ifdef __QLORD
	printf( "\nCommand: q>" );
#else	// __QLORD
	printf( "\nCommand: r, s, q>" );
#endif	// __QLORD

	if( strstr( sOverview, "x" ) != NULL )
		sndPlaySound( "type.wav", SND_ASYNC | SND_LOOP );
	else
		sndPlaySound( NULL, SND_ASYNC );

	SetEvent( hPrompt );
}

void CDPConsole::HideAddr( char* sOverview )
{
	CString strtmp	= sOverview;
	*sOverview	= '\0';

	int nFirst	= 0;
	int nPos	= strtmp.Find( "\n", nFirst );

	while( nPos >= 0 )
	{
		CString str	= strtmp.Mid( nFirst, nPos - nFirst + 1 );

		int pos		= str.Find( ".", 0 );
		strcat( sOverview, str.Left( pos - 3 ) );
		pos		= str.Find( "-", 0 );
		strcat( sOverview, str.Right( str.GetLength() - pos ) );
					
		nFirst	= nPos + 1;
		nPos	= strtmp.Find( "\n", nFirst );
	}
}

void CDPConsole::OnError( CAr & ar )
{
	long lError;
	ar >> lError;
	switch( lError )
	{
		case ERROR_NODE_NOT_FOUND:
			{
				printf( "node not found" );
				printf( "\nCommand: r, s, q>" );
				SetEvent( hPrompt );
				break;
			}
	}
}