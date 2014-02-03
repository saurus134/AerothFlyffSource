#include "stdafx.h"
#include "monitordlg.h"
#include <mmsystem.h>
#include "dpconsolesrvr.h"
#include "dpmonitor.h"
#include "dbmanager.h"

extern	CDbManager	g_DbManager;

CDPMonitor::CDPMonitor( CMonitorDlg* pMonitorDlg )
{
	m_pMonitorDlg	= pMonitorDlg;
	BEGIN_MSG;
	ON_MSG( PACKETTYPE_MONITOR_ID, OnAddConnection );
	ON_MSG( PACKETTYPE_PING, OnPing );
}

CDPMonitor::~CDPMonitor()
{
}

void CDPMonitor::SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
{
	switch( lpMsg->dwType )
	{
		case DPSYS_DESTROYPLAYERORGROUP:
			{
				LPDPMSG_DESTROYPLAYERORGROUP lpDestroyPlayer	= (LPDPMSG_DESTROYPLAYERORGROUP)lpMsg;
				OnRemoveConnection( lpDestroyPlayer->dpId );
				break;
			}
	}
}

void CDPMonitor::UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
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

void CDPMonitor::OnAddConnection( CAr & ar, DPID dpid )
{
	DWORD dwId;
	BOOL fsndPing;

	ar >> dwId >> fsndPing;

	HTREEITEM hItem
							= m_pMonitorDlg->m_tree.FindItem( m_pMonitorDlg->m_tree.GetRootItem(), dwId, true );
	if( hItem != NULL ) {
		PSrvrData pData	= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( hItem );
		pData->dpid		= dpid;
		pData->dwPing	= timeGetTime();
		pData->fsndPing		= fsndPing;
		pData->tm	= CTime::GetCurrentTime();
		m_pMonitorDlg->m_tree.SetCheck( hItem, FALSE );

		sndPlaySound( NULL, SND_ASYNC );

		CString sItem	= m_pMonitorDlg->m_tree.GetItemText( hItem );
		if( sItem.Find( ".", 0 ) == -1 )
		{	
			char lpAddr[16]	= { 0, };
			GetPlayerAddr( dpid, lpAddr );
			sItem	+= "        ";
			sItem	+= lpAddr;
			m_pMonitorDlg->m_tree.SetItemText( hItem, (LPCSTR)sItem );
		}

		m_pMonitorDlg->m_pDPConsoleSrvr->SendOverview( DPID_ALLPLAYERS );
	}
}

void CDPMonitor::OnRemoveConnection( DPID dpid )
{
	HTREEITEM hItem
							= m_pMonitorDlg->m_tree.FindItem( m_pMonitorDlg->m_tree.GetRootItem(), dpid, false );
	if( hItem != NULL ) {
		PSrvrData pData
			= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( hItem );

		g_DbManager.WriteLogofServerDown( pData->dwId, pData->tm );
	
//		pData->dpid		= 0;
		m_pMonitorDlg->m_tree.SelectItem( hItem );
		m_pMonitorDlg->m_tree.SetCheck( hItem, TRUE );
		m_pMonitorDlg->m_tree.SetFocus();

		sndPlaySound( "type.wav", SND_ASYNC | SND_LOOP );

		m_pMonitorDlg->m_pDPConsoleSrvr->SendOverview( DPID_ALLPLAYERS );
	}
}

void CDPMonitor::OnPing( CAr & ar, DPID dpid )
{
	HTREEITEM hItem
							= m_pMonitorDlg->m_tree.FindItem( m_pMonitorDlg->m_tree.GetRootItem(), dpid, false );
	if( hItem != NULL ) {
		PSrvrData pData
			= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( hItem );
		pData->dwPing	= timeGetTime();
	}
}