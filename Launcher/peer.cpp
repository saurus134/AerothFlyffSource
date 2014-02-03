#include "stdafx.h"
#include "peer.h"

CPeer::CPeer()
{
	*m_lpAddr	= 0;
	m_hProcess	= (HANDLE)0;
	*m_lpApplicationName	= '\0';
	*m_lpCurrentDirectory	= '\0';
	m_dwId	= 0;
	m_dwMilliseconds	= INFINITE;

	m_hWorkerThread		= (HANDLE)0;
	m_hCloseWorker	= (HANDLE)0;

	m_hReadInheritable	= (HANDLE)0;

	m_hWait		= CreateEvent( NULL, FALSE, FALSE, NULL );
	m_bWait		= FALSE;

	BEGIN_MSG;
	ON_MSG( PACKETTYPE_CREATE_PROCESS, OnCreateProcess );
	ON_MSG( PACKETTYPE_TERMINATE_PROCESS, OnTerminateProcess );
}

CPeer::~CPeer()
{
	CloseHandle( m_hHeartbeat );
	CloseHandle( m_hWait );
}

void CPeer::SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
{
	switch( lpMsg->dwType )
	{
		case DPSYS_CREATEPLAYERORGROUP:
			break;
		case DPSYS_DESTROYPLAYERORGROUP:
			break;
	}
}

void CPeer::UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
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

BOOL CPeer::InitializeMyProcess( void )
{
	CScanner s;
	if( s.Load( "launcher.ini" ) )
	{
		s.GetToken();
		while( s.tok != FINISHED )
		{
			if( s.Token == "lpAddr" )
			{
				s.GetToken();	// =
				s.GetToken();
				strcpy( m_lpAddr, s.Token );
			}
			else if( s.Token == "lpApplicationName" )
			{
				s.GetToken();	// =
				s.GetToken();
				strcpy( m_lpApplicationName, s.Token );
			}
			else if( s.Token == "lpCurrentDirectory" )
			{
				s.GetToken();	// =
				s.GetToken();
				strcpy( m_lpCurrentDirectory, s.Token );
			}
			else if( s.Token == "dwId" )
			{
				s.GetToken();	// =
				m_dwId	= (DWORD)s.GetNumber();
				char lpName[32];
				sprintf( lpName, "%d", m_dwId );
				if( !( m_hHeartbeat = CreateEvent( NULL, FALSE, FALSE, lpName ) ) )
					m_hHeartbeat	= OpenEvent( EVENT_MODIFY_STATE, FALSE, lpName );
				if( !m_hHeartbeat )
					AfxMessageBox( "MAPI_E_NOT_ENOUGH_RESOURCES" );
			}
			else if( s.Token == "dwMiliseconds" )
			{
				s.GetToken();	// =
				m_dwMilliseconds	= (DWORD)s.GetNumber();
			}
			else if( s.Token == "bWait" )
			{
				s.GetToken();	// =
				m_bWait	= (BOOL)s.GetNumber();
			}
			s.GetToken();
		}
		return TRUE;
	}
	return FALSE;
}

void CPeer::CreateMyProcess( void )
{
	ASSERT( *m_lpApplicationName != '\0' );

//	KillProcess( m_lpApplicationName );
	TerminateMyProcess();

//	HANDLE hWriteUninheritable;
	HANDLE hWriteInheritable;
	HANDLE hSaveStdOut;
	
//	char lpCurrentDirectory[MAX_PATH], lpCommandLine[MAX_PATH];
//	GetCurrentDirectory( MAX_PATH, lpCurrentDirectory );
//	sprintf( lpCommandLine, "%s\\%s", lpCurrentDirectory, m_lpApplicationName );

	SECURITY_ATTRIBUTES	sa;
	sa.nLength	= sizeof(sa);
	sa.lpSecurityDescriptor	= NULL;
	sa.bInheritHandle	= TRUE;
	if( !CreatePipe( &m_hReadInheritable, &hWriteInheritable, &sa, 0 ) )
		AfxMessageBox( "Unable to create pipe." );
//	if( !DuplicateHandle( GetCurrentProcess(), hWriteInheritable, GetCurrentProcess(), &hWriteUninheritable, 0, TRUE, DUPLICATE_SAME_ACCESS ) )
//		AfxMessageBox( "Unable to duplicate handle." );
//	CloseHandle( hWriteInheritable );
	hSaveStdOut		= GetStdHandle( STD_OUTPUT_HANDLE );
	SetStdHandle( STD_OUTPUT_HANDLE, hWriteInheritable );

	STARTUPINFO si;
	memset( &si, 0, sizeof(STARTUPINFO) );
	si.cb	= sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	if( FALSE == ::CreateProcess( NULL, m_lpApplicationName, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, m_lpCurrentDirectory, &si, &pi ) )	{
		ASSERT( 0 );
	}
	CloseHandle( pi.hThread );

	SetStdHandle( STD_OUTPUT_HANDLE, hSaveStdOut );
	CloseHandle(  hWriteInheritable );

	m_hProcess	= pi.hProcess;

	CreateWorker();

	if( m_bWait )
		WaitForSingleObject( m_hWait, INFINITE );

	SendHdr( PACKETTYPE_PROCESS_CREATED );
}

void CPeer::CreateWorker( void )
{
	CloseWorker();

	DWORD dwThreadId;
	m_hCloseWorker	= CreateEvent( NULL, FALSE, FALSE, NULL );
	m_hWorkerThread		= chBEGINTHREADEX( NULL, 0, _WorkerThread, this,  0, &dwThreadId );
	ASSERT( m_hWorkerThread );

	HANDLE hThread	= (HANDLE)_beginthread( _pipe_read, 0, this );
	ASSERT( hThread );
}

void CPeer::CloseWorker( void )
{
	CLOSE_THREAD( m_hWorkerThread, m_hCloseWorker );
}

void CPeer::TerminateMyProcess( void )
{
	CloseWorker();

	if( m_hProcess )
	{
		DWORD dwExitCode;
		GetExitCodeProcess( m_hProcess, &dwExitCode );
		TerminateProcess( m_hProcess, dwExitCode );
		WaitForSingleObject( m_hProcess, INFINITE );
		CloseHandle( m_hProcess );
		m_hProcess	= (HANDLE)0;
	}
}

UINT CPeer::_WorkerThread( LPVOID pParam )
{
	CPeer* pPeer	= (CPeer*)pParam;
//	ASSERT( pPeer );
	return pPeer->WorkerThread();
}

BOOL CPeer::WorkerThread( void )
{
	DWORD dw;
	HANDLE lpHandles[3];

	lpHandles[0]	= m_hCloseWorker;
	lpHandles[1]	= m_hProcess;
	lpHandles[2]	= m_hHeartbeat;

	while( 1 )
	{
		dw	= WaitForMultipleObjects( 3, lpHandles, FALSE, m_dwMilliseconds );
		switch( dw )
		{
			case ( WAIT_OBJECT_0 ):
				return( 0 );
			case ( WAIT_OBJECT_0 + 1 ):
				{
					CloseHandle( m_hProcess );
					CloseHandle( m_hCloseWorker );
					CloseHandle( m_hWorkerThread );
					m_hProcess	= (HANDLE)0;
					m_hCloseWorker	= (HANDLE)0;
					m_hWorkerThread		= (HANDLE)0;
					SendHdr( PACKETTYPE_PROCESS_TERMINATED );
					Sleep( 3000 );
					return( 0 );
				}
			case ( WAIT_TIMEOUT ):
				{
					OutputDebugString( "Heartbeat timeout" );
					CTime time	= CTime::GetCurrentTime();
					printf( "%s\tdeadlock\n", time.Format( "%Y/%m/%d %H:%M:%S" ) );
					DWORD dwExitCode;
					GetExitCodeProcess( m_hProcess, &dwExitCode );
					TerminateProcess( m_hProcess, dwExitCode );
					break;
				}
			case ( WAIT_OBJECT_0 + 2 ):
				{
					OutputDebugString( "Heartbeat received" );
					//TRACE( "( WAIT_OBJECT_0 + 2 )\n" );
					break;
				}
		}
	}
	return( 0 );
}

void CPeer::SendMyProcess( void )
{
	BEFORESEND( ar, PACKETTYPE_MY_PROCESS );
	ar << m_dwId;
	SEND( ar, this, DPID_SERVERPLAYER );
}

void CPeer::OnCreateProcess( CAr & ar )
{
	CreateMyProcess();
}

void CPeer::OnTerminateProcess( CAr & ar )
{
	TerminateMyProcess();
}

void _cdecl CPeer::_pipe_read( LPVOID pParam )
{
	CPeer* pPeer	= (CPeer*)pParam;
	pPeer->pipe_read();
}

void CPeer::pipe_read( void )
{
	BOOL bStatus;
	do {
		DWORD dwData	= 0;
		DWORD dwBytesRead;
		bStatus		= ReadFile( m_hReadInheritable, &dwData, sizeof(dwData), &dwBytesRead, NULL );
//		TRACE( "Child successfully read, %ld\n", dwData );
		switch( dwData )
		{
			case 0x00000001:	// is started
				{
					SetEvent( m_hWait );
					break;
				}
		}
	} while( bStatus );

	CloseHandle( m_hReadInheritable );
	m_hReadInheritable	= (HANDLE)0;

	return;
}
