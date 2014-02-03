// Launcher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "launcher.h"
#include "peer.h"

/////////////////////////////////////////////////////////////////////////////
CWinApp theApp;

using namespace std;

int _tmain( int argc, TCHAR* argv[], TCHAR* envp[] )
{
	CTime time	= CTime::GetCurrentTime();
	printf( "%s\n", time.Format( "%Y/%m/%d %H:%M:%S" ) );

	LOAD_WS2_32_DLL;

	CPeer peer;

	if( AfxWinInit( GetModuleHandle( NULL ), NULL, GetCommandLine(), 0) && peer.InitializeMyProcess() )
	{
//		InitInstance
		if( FALSE == peer.ConnectToServer( peer.m_lpAddr, PN_MONITOR_2, FALSE ) )
			goto lbl_exit;
		peer.SendMyProcess();

		char buffer[256];
		while( 1 )
		{
			cin >> buffer;
				
			if( !strcmp( buffer, "q" ) )
			{
				break;
			}
		}
	}
lbl_exit:
//	ExitInstance
	peer.DeleteDPObject();
	SAFE_DELETE( CAr::m_pHeapMng );
	SAFE_DELETE( CClientSock::m_pPool );
	SAFE_DELETE( CClientSockE::m_pPool );
	SAFE_DELETE( CBuffer::m_pPool );
	SAFE_DELETE( CBuffer::m_pHeapMng );
	UNLOAD_WS2_32_DLL;
	return 0;
}