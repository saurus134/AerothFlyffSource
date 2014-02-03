#ifndef __DPCONSOLESRVR_H__
#define	__DPCONSOLESRVR_H__

#include "dpmng.h"
#include "msghdr.h"

class CMonitorDlg;

#undef	theClass
#define	theClass	CDPConsoleSrvr
#undef theParameters
#define theParameters	CAr & ar, DPID

class CDPConsoleSrvr : public CDPMng
{
private:
	CMonitorDlg*	m_pMonitorDlg;
public:
//	Constructions
	CDPConsoleSrvr( CMonitorDlg* pMonitorDlg );
	~CDPConsoleSrvr();
//	Overrides
	virtual void	SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
	virtual void	UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
//	Operations
	void	SendOverview( DPID );
	void	SendError( long lError, DPID dpid );

	USES_PFNENTRIES;
//	Handlers
	void	OnAddConnection( DPID );
	void	OnRemoveConnection( DPID );
	void	OnCommand( CAr & ar, DPID );
};

#endif	// __DPCONSOLESRVR_H__