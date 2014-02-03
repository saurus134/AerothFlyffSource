#include "stdafx.h"

#ifdef __DB_CHECK
#ifdef __SEND_SMS
#include "MonitorDlg.h"
#include "host.h"
#endif // __SEND_SMS
#endif // __DB_CHECK

CDbManager::CDbManager()
{
//	if( FALSE == m_qry.Connect( 3, DSN_NAME, DB_ADMIN_ID, DB_ADMIN_PASS ) )
//	{
//		ASSERT( 0 );
//	}

#ifdef __DB_CHECK
	if( m_Lua.RunScript( "DBCheck.lua" ) != 0 )
	{
		AfxMessageBox( "DBCheck.lua Run Failed!!!" );
		exit(0);
	}
	
	m_Lua.GetGloabal( "tDB" );
	m_Lua.PushNil();
	
	char *strDSN, *strID, strPWD[256] = {0,};
	string	strQuery;
	for( int i=0; m_Lua.TableLoop( -2 ); i++ )
	{
		CQuery* pQuery = new CQuery;
		m_vecpQry.push_back(pQuery);
		
		strDSN	= const_cast<char*>(m_Lua.GetFieldToString( -1, "DSN_NAME" ));
		strID	= const_cast<char*>(m_Lua.GetFieldToString( -1, "DB_ADMIN_ID" ));
		::GetPWDFromToken( m_Lua.GetFieldToString( -1, "DB_PWD" ), strPWD );
		strQuery = m_Lua.GetFieldToString( -1, "QUERY" );
		m_vecstrQry.push_back(strQuery);
		if( m_vecpQry[i]->Connect( 3, strDSN, strID, strPWD ) == FALSE )
		{
			AfxMessageBox( "DB Connect Failed!!!" );
			exit(0);
		}

		m_Lua.Pop(1);
	}
	m_Lua.Pop(0);

	CheckDB();	// 시험 삼아 한번 체크 한다.
#endif // __DB_CHECK
}

CDbManager::~CDbManager()
{
//	m_qry.DisConnect();
#ifdef __DB_CHECK
	for( int i=0; i<m_vecpQry.size(); i++ )
	{
		m_vecpQry[i]->DisConnect();
		safe_delete( m_vecpQry[i] );
	}
#endif // __DB_CHECK
}

BOOL CDbManager::WriteLogofServerDown( DWORD dwId, CTime & tm )
{
/*
	CTime tmCur	= CTime::GetCurrentTime();
	CString sStart, sEnd;

	sStart	= tm.Format( "%Y%m%d%H%M%S" );
	sEnd	= tmCur.Format( "%Y%m%d%H%M%S" );

	char sQuery[128]	= { 0, };
	sprintf( sQuery, "AeonServerDown %d, '%s', '%s'", dwId, sStart, sEnd );

	if( FALSE == m_qry.Exec( sQuery ) )
		return FALSE;

	m_qry.Clear();
*/
	return TRUE;
}

#ifdef __DB_CHECK
void CDbManager::CheckDB()
{
	for( int i=0; i<m_vecpQry.size(); i++ )
	{
		if( m_vecpQry[i]->Exec(m_vecstrQry[i].c_str()) )
		{
			if( m_vecpQry[i]->Fetch() == TRUE )
			{
				int nColumnNum = m_vecpQry[i]->GetInt( const_cast<char*>(m_Lua.GetGlobalString( "CHECK_COLUMN" )) );
				if( nColumnNum > 0 )
				{
					TRACE("%s -> SUCCESS - %d\n", m_vecpQry[i]->DBName, nColumnNum);
					continue;
				}
			}
		}
		
		CTime tm	= CTime::GetCurrentTime();
		CString sTime	= tm.Format( "%Y%m%d%H%M%S" );
		WriteLog( "%s - DB %s", sTime, m_vecpQry[i]->DBName );
#ifdef __SEND_SMS
		SendSMS( m_vecpQry[i]->DBName );
#endif // __SEND_SMS

	}
}

#ifdef __SEND_SMS
void CDbManager::SendSMS( char* szMsg )
{
	if(	!m_pMonitorDlg->m_bCheckSendSms )
		return;

	CHost* pHost = m_pMonitorDlg->m_pHost;

	char szTranId[20] = {0,};
	char szTrandPwd[20] = {0,};
	char szTranMsg[256] = {0,};
	strcpy( szTranId,pHost->m_Lua.GetGlobalString("TRAN_ID") );
	strcpy( szTrandPwd, pHost->m_Lua.GetGlobalString("TRAN_PASSWORD") );
	sprintf( szTranMsg, "%s%s", m_Lua.GetGlobalString("TRAN_MSG"), szMsg );
		
	pHost->m_Lua.GetGloabal( "tSMS" );
	pHost->m_Lua.PushNil();
	while( pHost->m_Lua.TableLoop(-2) )
	{
		char szRcvNum[15] = {0,};
		strcpy( szRcvNum, pHost->m_Lua.GetFieldToString(-1, "strPhoneNum") );
		CSMS sms;
		sms.SendMsg( szTranId, szTrandPwd, szRcvNum, "02-563-6170", "0", szTranMsg );
		pHost->m_Lua.Pop(1);
	}
	pHost->m_Lua.Pop(0);

	m_pMonitorDlg->m_bCheckSendSms = FALSE;
	m_pMonitorDlg->UpdateData(FALSE);
}
#endif // __SEND_SMS

#endif // __DB_CHECK

CDbManager	g_DbManager;