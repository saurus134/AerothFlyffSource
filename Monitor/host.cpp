#include "stdafx.h"
#include "dpconsolesrvr.h"
#include "host.h"
#include "monitordlg.h"
#include "dbmanager.h"

extern	CDbManager	g_DbManager;

CHost::CHost( CMonitorDlg* pMonitorDlg )
{
#ifdef __SEND_SMS
	if( m_Lua.RunScript( "SMSList.lua" ) != 0 )
	{
		AfxMessageBox( "SMSList.lua Run Failed!!!" );
		ASSERT(0);
	}
#endif // __SEND_SMS
	
	m_pMonitorDlg	= pMonitorDlg;
	BEGIN_MSG;
	ON_MSG( PACKETTYPE_MY_PROCESS, OnAddConnection );
	ON_MSG( PACKETTYPE_PROCESS_CREATED, OnProcessCreated );
	ON_MSG( PACKETTYPE_PROCESS_TERMINATED, OnProcessTerminated );
}

CHost::~CHost()
{
}

void CHost::SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
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

void CHost::UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid )
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

void CHost::OnAddConnection( CAr & ar, DPID dpid )
{
	DWORD dwId;
	ar >> dwId;

	HTREEITEM hItem
							= m_pMonitorDlg->m_tree.FindItem( m_pMonitorDlg->m_tree.GetRootItem(), dwId, true );
	if( hItem != NULL ) {
		PSrvrData pData	= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( hItem );
		pData->dpid		= dpid;

		CString sItem	= m_pMonitorDlg->m_tree.GetItemText( hItem );
		if( sItem.Find( ".", 0 ) == -1 )
		{	
			char lpAddr[16]	= { 0, };
			GetPlayerAddr( dpid, lpAddr );
			sItem	+= "        ";
			sItem	+= lpAddr;
			m_pMonitorDlg->m_tree.SetItemText( hItem, (LPCSTR)sItem );
		}
	}
}

void CHost::OnRemoveConnection( DPID dpid )
{
	HTREEITEM hItem
							= m_pMonitorDlg->m_tree.FindItem( m_pMonitorDlg->m_tree.GetRootItem(), dpid, false );
	if( hItem != NULL ) {
		PSrvrData pData
			= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( hItem );
		pData->dpid		= 0;
	}
}

void CHost::OnProcessCreated( CAr & ar, DPID dpid )
{
	HTREEITEM hItem
							= m_pMonitorDlg->m_tree.FindItem( m_pMonitorDlg->m_tree.GetRootItem(), dpid, false );
	if( hItem != NULL ) {
		m_pMonitorDlg->m_tree.SetCheck( hItem, FALSE );
//		sndPlaySound( NULL, SND_ASYNC );
		m_pMonitorDlg->m_pDPConsoleSrvr->SendOverview( DPID_ALLPLAYERS );

		if( m_pMonitorDlg->m_tree.IsEndofEnumItem() ) {
			m_pMonitorDlg->m_tree.CleanupEnumItem();
			if( m_pMonitorDlg->m_tree.PeekEnumItem() ) {
				SendTerminateLwrProcess();
				PSrvrData pData		= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( m_pMonitorDlg->m_tree.GetRootEnumItem() );
				SendHdr( PACKETTYPE_CREATE_PROCESS, pData->dpid );
				m_pMonitorDlg->m_dwID	= pData->dwId;
				m_pMonitorDlg->UpdateData( FALSE );
			}
			return;
		}

		HTREEITEM hFind		= m_pMonitorDlg->m_tree.GetEnumItem();

		PSrvrData pData
			= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( hFind );
		ASSERT( pData );
		ASSERT( pData->dpid );

		SendHdr( PACKETTYPE_CREATE_PROCESS, pData->dpid );
		m_pMonitorDlg->m_dwID	= pData->dwId;
		m_pMonitorDlg->UpdateData( FALSE );
	}
}

void CHost::OnProcessTerminated( CAr & ar, DPID dpid )
{
	HTREEITEM hItem
							= m_pMonitorDlg->m_tree.FindItem( m_pMonitorDlg->m_tree.GetRootItem(), dpid, false );
	if( hItem != NULL ) {
		PSrvrData pData
			= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( hItem );

//		g_DbManager.WriteLogofServerDown( pData->dwId, pData->tm );
		CTime tm	= CTime::GetCurrentTime();
		CString sTime	= tm.Format( "%Y%m%d%H%M%S" );
		WriteLog( "%s - %d", sTime, pData->dwId );

#ifdef __SEND_SMS
		if( m_pMonitorDlg->m_bCheckSendSms)
		{
			char szMsg[512] = {0,};
			sprintf( szMsg, "%d", pData->dwId );
			SendSmsMSg( szMsg );
			m_pMonitorDlg->m_bCheckSendSms = FALSE;
			m_pMonitorDlg->UpdateData(FALSE);
		}
#endif // __SEND_SMS

		m_pMonitorDlg->m_tree.SelectItem( hItem );
//		m_pMonitorDlg->m_tree.SetCheck( hItem, TRUE );
		m_pMonitorDlg->m_tree.SetFocus();
//		sndPlaySound( "type.wav", SND_ASYNC | SND_LOOP );

		if( m_pMonitorDlg->m_tree.IsEnumerating() )
		{
			m_pMonitorDlg->m_tree.PostEnumItem( hItem, true );
		}
		else
		{
			m_pMonitorDlg->m_tree.EnumItem( hItem, true );
			SendTerminateLwrProcess();
			SendHdr( PACKETTYPE_CREATE_PROCESS, pData->dpid );
		}

		m_pMonitorDlg->m_pDPConsoleSrvr->SendOverview( DPID_ALLPLAYERS );
	}
}

#ifdef __SEND_SMS
void CHost::SendSmsMSg( char* szMsg )
{
	char szTranId[20] = {0,};
	strcpy( szTranId, m_Lua.GetGlobalString("TRAN_ID") );
	char szTrandPwd[20] = {0,};
	strcpy(szTrandPwd, m_Lua.GetGlobalString("TRAN_PASSWORD") );
	
	char szDstMsg[256] = {0,};
	m_Lua.GetGloabal( "tServerName" );
	sprintf( szDstMsg, "%s%s\n", m_Lua.GetGlobalString("TRAN_MSG"), m_Lua.GetFieldToString(-1, szMsg) );
	m_Lua.Pop(1);
	
	m_Lua.GetGloabal( "tSMS" );
	if( m_Lua.IsTable( -1 ) )
	{
		m_Lua.PushNil();
		while( m_Lua.TableLoop(-2) )
		{
			char szRcvNum[15] = {0,};
			strcpy( szRcvNum, m_Lua.GetFieldToString(-1, "strPhoneNum") );
			CSMS sms;
			sms.SendMsg( szTranId, szTrandPwd, szRcvNum, "02-563-6170", "0", szDstMsg );
			m_Lua.Pop(1);
		}
	}
	m_Lua.Pop(0);
}
#endif // __SEND_SMS

void CHost::SendTerminateLwrProcess( void )
{
	for( u_long uIndex = 0; uIndex < m_pMonitorDlg->m_tree.m_uSizeofEnumItem; uIndex++ )
	{
		HTREEITEM hItem		= m_pMonitorDlg->m_tree.m_ahEnumItem[uIndex];
		ASSERT( hItem );
		m_pMonitorDlg->m_tree.SetCheck( hItem, TRUE );
		PSrvrData pData		= (PSrvrData)m_pMonitorDlg->m_tree.GetItemData( hItem );
		ASSERT( pData );
		ASSERT( pData->dpid );
		SendHdr( PACKETTYPE_TERMINATE_PROCESS, pData->dpid );
	}
}
