// MonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "dpconsolesrvr.h"
#include "host.h"

#ifdef __DB_CHECK
extern CDbManager g_DbManager;
#endif // __DB_CHECK


/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg dialog

CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMonitorDlg)
	m_dwID = 0;
	m_bCheckSendSms = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitorDlg)
	DDX_Control(pDX, IDC_TREE_SERVER, m_tree);
	DDX_Text(pDX, IDC_EDIT_ID, m_dwID);
	DDX_Check(pDX, IDC_CHECK_SENDSMS, m_bCheckSendSms);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CMonitorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_TREE_SERVER, OnClickTree)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SND_STOP, OnButtonSndStop)
	ON_BN_CLICKED(IDC_CHECK_SENDSMS, OnCheckSendsms)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg message handlers

BOOL CMonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

#ifdef __DB_CHECK
	g_DbManager.m_pMonitorDlg = this;
#endif // __DB_CHECK

	m_tree.ModifyStyle( TVS_CHECKBOXES, 0 );
	m_tree.ModifyStyle( 0, TVS_CHECKBOXES );

	CScanner s;
	HTREEITEM hParent	= TVI_ROOT;
	if( TRUE == s.Load( "monitor.ini" ) )
	{
		s.GetToken();
		while( s.tok != FINISHED )
		{
			MakeTree( TVI_ROOT, s );
		}
	}

	m_pDPConsoleSrvr	= new CDPConsoleSrvr( this );
	if( FALSE == m_pDPConsoleSrvr->StartServer( PN_MONITOR_1, TRUE ) )
		return FALSE;
	m_pHost		= new CHost( this );
	if( FALSE == m_pHost->StartServer( PN_MONITOR_2, TRUE ) )
		return FALSE;

	SetTimer( 0, 1000 * 1, NULL );
#ifdef __DB_CHECK
	SetTimer( 2, 1000 * g_DbManager.m_Lua.GetGlobalNumber( "CHECK_TIME" ), NULL );
#endif // __DB_CHECK

#ifndef __SEND_SMS
	(CButton*)GetDlgItem( IDC_CHECK_SENDSMS )->ShowWindow( SW_HIDE );
#endif // __SEND_SMS

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMonitorDlg::MakeTree( HTREEITEM hParent, CScanner & s )
{
	DWORD dwId	= (DWORD)atoi( s.Token );
	s.GetToken();
	CString str		= s.Token;
	HTREEITEM hItem		= m_tree.AddItem( dwId, (LPTSTR)(LPCTSTR)str, hParent );
	s.GetToken();

	if( s.Token == "{" )
	{
		s.GetToken();
		while( 1 )
		{
			MakeTree( hItem, s );
			if( s.Token == "}" ) {
				s.GetToken();
				return;
			}	
		}
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMonitorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMonitorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMonitorDlg::OnDestroy() 
{
	KillTimer( 0 );
	CDialog::OnDestroy();

	m_tree.Clear();

	m_pDPConsoleSrvr->DeleteDPObject();
	m_pHost->DeleteDPObject();

	SAFE_DELETE( m_pDPConsoleSrvr );
	SAFE_DELETE( m_pHost );
}

void CMonitorDlg::OnClickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM hItem;
	CPoint point;
	TVHITTESTINFO tvht;
	CString strText;

	GetCursorPos( &point );
	m_tree.ScreenToClient( (LPPOINT)&point );
	tvht.pt.x	= point.x;
	tvht.pt.y	= point.y;

	UINT uFlags	= 0;
	hItem	= m_tree.HitTest( point, &uFlags );

	if( uFlags & TVHT_ONITEMSTATEICON )
	{
		m_tree.SetCheck( hItem, !m_tree.GetCheck( hItem ) );	
		m_tree.SelectItem( hItem );
	}
	
	*pResult = 0;
}

void CMonitorDlg::OnTimer(UINT nIDEvent) 
{
	switch( nIDEvent )
	{
		case 0:
			m_pDPConsoleSrvr->ReceiveMessage();
			m_pHost->ReceiveMessage();
			break;
#ifdef __DB_CHECK
		case 2:
			{
				g_DbManager.CheckDB();
				break;
			}
#endif // __DB_CHECK

		default:	break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CMonitorDlg::OnButtonSndStop() 
{
	sndPlaySound( NULL, SND_ASYNC );
}

void CMonitorDlg::OnCheckSendsms() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
