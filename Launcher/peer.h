#ifndef __PEER_H__
#define	__PEER_H__

#include "dpmng.h"
#include "msghdr.h"

#undef	theClass
#define theClass	CPeer 
#undef theParameters
#define theParameters	CAr & ar

class CPeer : public CDPMng
{
private:
	HANDLE	m_hProcess;
	HANDLE	m_hWorkerThread;
	HANDLE	m_hCloseWorker;
	HANDLE	m_hReadInheritable;

	HANDLE	m_hWait;
	HANDLE	m_hHeartbeat;
	DWORD	m_dwMilliseconds;
public:
	char	m_lpAddr[MAX_PATH];
	char	m_lpApplicationName[MAX_PATH];
	char	m_lpCurrentDirectory[MAX_PATH];
	DWORD	m_dwId;
	BOOL	m_bWait;

public:
//	Constructions
	CPeer ();
	virtual	~CPeer ();
//	Overrides
	virtual void	SysMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
	virtual void	UserMessageHandler( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID dpid );
//	Operations
	BOOL	InitializeMyProcess( void );
	void	CreateMyProcess( void );
	void	TerminateMyProcess( void );

protected:
	static	UINT	_WorkerThread( LPVOID pParam );
	BOOL	WorkerThread( void );

	void	CreateWorker( void );
	void	CloseWorker( void );

	static	void _cdecl _pipe_read( LPVOID pParam );
	void	pipe_read( void );

public:
	void	SendHdr( DWORD dwHdr );
	void	SendMyProcess( void );
//	Handlers
	USES_PFNENTRIES;

	void	OnCreateProcess( CAr & ar );
	void	OnTerminateProcess( CAr & ar );
};

inline void CPeer::SendHdr( DWORD dwHdr )
{
	BEFORESEND( ar, dwHdr );
	SEND( ar, this, DPID_SERVERPLAYER );
}
#endif	// __PEER_H__