// MonitorDlg.h : header file
//

#if !defined(AFX_MONITORDLG_H__690CED3C_957A_44E4_9654_F1691C718831__INCLUDED_)
#define AFX_MONITORDLG_H__690CED3C_957A_44E4_9654_F1691C718831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "mytreectrl.h"
/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg dialog
class CDPMonitor;
class CDPConsoleSrvr;
class CHost;

class CMonitorDlg : public CDialog
{
public:
	CDPConsoleSrvr*	m_pDPConsoleSrvr;
	CHost*	m_pHost;
private:
	void	MakeTree( HTREEITEM hParent, CScanner& s );
// Construction
public:
	CMonitorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMonitorDlg)
	enum { IDD = IDD_MONITOR_DIALOG };
	CMyTreeCtrl	m_tree;
	UINT	m_dwID;
	BOOL	m_bCheckSendSms;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMonitorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnClickTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonSndStop();
	afx_msg void OnCheckSendsms();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORDLG_H__690CED3C_957A_44E4_9654_F1691C718831__INCLUDED_)
