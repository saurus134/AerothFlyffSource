#ifndef __DPCONSOLE_H__
#define	__DPCONSOLE_H__

#include "dpmng.h"
#include "msghdr.h"

#undef	theClass
#define theClass	CDPConsole
#undef theParameters
#define theParameters	CAr & ar

class CDPConsole : public CDPMng
{
public:
//	Constructions
	CDPConsole();
	virtual	~CDPConsole();
//	Overrides
	virtual void	SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
	virtual void	UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
//	Operations
	void	SendCommand( char* buffer );
	void	HideAddr( char* sOverview );
//	Handlers
	USES_PFNENTRIES;
	void	OnOverview( CAr & ar );
	void	OnError( CAr & ar );
};

#endif	// __DPCONSOLE_H__