#ifndef __DBMANAGER_H__
#define	__DBMANAGER_H__

#pragma once

#include "query.h"
#include "LuaBase.h"

class CMonitorDlg;
class CDbManager
{
private:
//	CQuery	m_qry;
public:
//	Constructions
	CDbManager();
	~CDbManager();
//	Operations
	BOOL	WriteLogofServerDown( DWORD dwId, CTime & tm );

#ifdef __DB_CHECK
	CLuaBase		m_Lua;
	vector<CQuery*>	m_vecpQry;
	vector<string>	m_vecstrQry;

	CMonitorDlg*	m_pMonitorDlg;

	void	CheckDB();
	void	SendSMS( char* szMsg );
#endif // __DB_CHECK

};

#endif	// __DBMANAGER_H__