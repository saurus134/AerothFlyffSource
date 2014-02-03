// Monitor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "monitor.h"
#include "monitordlg.h"
#include "dpmonitor.h"

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp

BEGIN_MESSAGE_MAP(CMonitorApp, CWinApp)
	//{{AFX_MSG_MAP(CMonitorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp construction

CMonitorApp::CMonitorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMonitorApp object

CMonitorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp initialization

BOOL CMonitorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LOAD_WS2_32_DLL;

	CMonitorDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CMonitorApp::ExitInstance() 
{
	SAFE_DELETE( CAr::m_pHeapMng );
	SAFE_DELETE( CClientSock::m_pPool );
	SAFE_DELETE( CClientSockE::m_pPool );
	SAFE_DELETE( CBuffer::m_pPool );
	SAFE_DELETE( CBuffer::m_pHeapMng );

	UNLOAD_WS2_32_DLL;
	
	return CWinApp::ExitInstance();
}
