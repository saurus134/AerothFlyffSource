#include "stdafx.h"
#include "host.h"
#include "dpconsolesrvr.h"
#include "monitordlg.h"

CDPConsoleSrvr::CDPConsoleSrvr( CMonitorDlg* pMonitorDlg )
{
	m_pMonitorDlg	= pMonitorDlg;
	BEGIN_MSG;
	ON_MSG( PACKETTYPE_CONSOLE_COMMAND, OnCommand );
}

CDPConsoleSrvr::~CDPConsoleSrvr()
{
}

void CDPConsoleSrvr::SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
{
	switch( lpMsg->dwType )
	{
		case DPSYS_CREATEPLAYERORGROUP:
			{
				LPDPMSG_CREATEPLAYERORGROUP lpCreatePlayer	= (LPDPMSG_CREATEPLAYERORGROUP)lpMsg;
				OnAddConnection( lpCreatePlayer->dpId );
				break;
			}
		case DPSYS_DESTROYPLAYERORGROUP:
			{
				LPDPMSG_DESTROYPLAYERORGROUP lpDestroyPlayer	= (LPDPMSG_DESTROYPLAYERORGROUP)lpMsg;
				OnRemoveConnection( lpDestroyPlayer->dpId );
				break;
			}
	}
}

void CDPConsoleSrvr::UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
{
	CAr ar( (LPBYTE)lpMsg, dwMsgSize );
	GETTYPE( ar );
	void ( theClass::*pfn )( theParameters )
		=	GetHandler( dw );
	
	if( pfn ) {
		( this->*( pfn ) )( ar, dpid );
	}
	else {
//		ASSERT( 0 );
	}
}

void CDPConsoleSrvr::OnAddConnection( DPID dpid )
{
	SendOverview( dpid );
}

void CDPConsoleSrvr::OnRemoveConnection( DPID dpid )
{
}

char	sOverview[1024*32]	= { 0, };
void CDPConsoleSrvr::SendOverview( DPID dpid )
{
	*sOverview	= '\0';
	int nSizeOfItem		= (int)m_pMonitorDlg->m_tree.GetSize();
	for( int i = 0; i < nSizeOfItem; i++ )
	{
		HTREEITEM hItem	= m_pMonitorDlg->m_tree.GethItem( i );
		if( NULL != hItem )
		{
			CString sItem;
			PSrvrData pData
				= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( hItem );
			sItem.Format( "\t%-32s ---- %s\n", m_pMonitorDlg->m_tree.GetItemText( hItem ), m_pMonitorDlg->m_tree.GetCheck( hItem )?"x":"o" );
			strcat( sOverview, (LPCSTR)sItem );
		}
	}

	BEFORESEND( ar, PACKETTYPE_CONSOLE_OVERVIEW );
	ar.WriteString( sOverview );
	SEND( ar, this, dpid );
}

void CDPConsoleSrvr::SendError( long lError, DPID dpid )
{
	BEFORESEND( ar, PACKETTYPE_ERROR );
	ar << lError;
	SEND( ar, this, dpid );
}

void CDPConsoleSrvr::OnCommand( CAr & ar, DPID dpid )
{
	char buffer[260]	= { 0,};

	ar.ReadString( buffer, 260 );
	
	Error( buffer );

	CScanner s( buffer );

	s.GetToken();
	if( s.Token == "r" )
	{
		DWORD dwId	= 0;
		dwId	= (DWORD)s.GetNumber();
		HTREEITEM hFind		= m_pMonitorDlg->m_tree.FindItem( m_pMonitorDlg->m_tree.GetRootItem(), dwId, true );
		
		if( NULL == hFind ) {
			SendError( ERROR_NODE_NOT_FOUND, dpid );
			return;
		}

		m_pMonitorDlg->m_tree.EnumItem( hFind, true );
		PSrvrData pData	= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( m_pMonitorDlg->m_tree.m_ahEnumItem[0] );
		m_pMonitorDlg->m_pHost->SendHdr( PACKETTYPE_CREATE_PROCESS, pData->dpid );
	}
	else if( s.Token == "s" )
	{
		DWORD dwId	= 0;
		dwId	= (DWORD)s.GetNumber();
		HTREEITEM hFind		= m_pMonitorDlg->m_tree.FindItem( m_pMonitorDlg->m_tree.GetRootItem(), dwId, true );

		if( NULL == hFind ) {
			SendError( ERROR_NODE_NOT_FOUND, dpid );
			return;
		}

		if( FALSE == m_pMonitorDlg->m_tree.IsEnumerating() )
		{
			m_pMonitorDlg->m_tree.EnumItem( hFind, true );
			m_pMonitorDlg->m_pHost->SendTerminateLwrProcess();
			m_pMonitorDlg->m_tree.CleanupEnumItem();
		}
	}
	else if( s.Token == "" )
	{
		SendOverview( dpid );
	}
}
