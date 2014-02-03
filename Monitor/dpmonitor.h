#ifndef __DPMONITOR_H__
#define	__DPMONITOR_H__

#include "dpmng.h"
#include "msghdr.h"

class CMonitorDlg;

#undef	theClass
#define	theClass	CDPMonitor
#undef theParameters
#define theParameters	CAr & ar, DPID

class CDPMonitor : public CDPMng
{
private:
	CMonitorDlg*	m_pMonitorDlg;
public:
//	Constructions
	CDPMonitor( CMonitorDlg* pMonitorDlg );
	~CDPMonitor();
//	Overrides
	virtual void	SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
	virtual void	UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
//	Operations

	USES_PFNENTRIES;
//	Handlers
	void	OnAddConnection( CAr &, DPID );
	void	OnRemoveConnection( DPID );
	void	OnPing( CAr & ar, DPID );
};

#endif	// __DPMONITOR_H__