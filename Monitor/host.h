#ifndef __HOST_H__
#define	__HOST_H__

#include "dpmng.h"
#include "msghdr.h"
#ifdef __SEND_SMS
#include "SMS.h"
#include "LuaBase.h"
#endif // __SEND_SMS
#undef	theClass
#define	theClass	CHost
#undef theParameters
#define theParameters	CAr & ar, DPID

class CMonitorDlg;

class CHost : public CDPMng
{
private:
	CMonitorDlg*	m_pMonitorDlg;
public:
#ifdef __SEND_SMS
	CLuaBase	m_Lua;
#endif // __SEND_SMS
//	Constructions
	CHost( CMonitorDlg* pMonitorDlg );
	~CHost();
//	Overrides
	virtual void	SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
	virtual void	UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
//	Operations
	void	SendHdr( DWORD dwHdr, DPID dpid );
	void	SendTerminateLwrProcess( void );

#ifdef __SEND_SMS
	void	SendSmsMSg( char* szMsg );
#endif // __SEND_SMS

	USES_PFNENTRIES;
//	Handlers
	void	OnAddConnection( CAr & ar, DPID );
	void	OnRemoveConnection( DPID );

	void	OnProcessCreated( CAr & ar, DPID dpid );
	void	OnProcessTerminated( CAr & ar, DPID dpid );
};

inline void CHost::SendHdr( DWORD dwHdr, DPID dpid )
{
	BEFORESEND( ar, dwHdr );
	SEND( ar, this, dpid );
}

#endif	// __HOST_H__