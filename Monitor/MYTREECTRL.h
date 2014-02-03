#if !defined(AFX_MYTREECTRL_H__3669FCC7_72B5_48C9_AD88_8C5D6C410042__INCLUDED_)
#define AFX_MYTREECTRL_H__3669FCC7_72B5_48C9_AD88_8C5D6C410042__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MYTREECTRL.h : header file
//

#include <list>
using	namespace	std;

typedef	struct	tagSrvrData
{
	DWORD	dwId;
	DWORD	dpid;

	DWORD	dwPing;
	CTime	tm;
	BOOL	fsndPing;

	tagSrvrData()
		{	dwId	= dpid	= dwPing	= 0;	fsndPing	= FALSE;	}
}
SrvrData,* PSrvrData;

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl window

#define	MAX_HTREEITEM_SIZE	256	
#define	MAX_ID	1000000

typedef	struct	tagENUMITEM
{
	HTREEITEM	m_ahEnumItem[MAX_HTREEITEM_SIZE];
	u_long	m_uSizeofEnumItem;
	tagENUMITEM()
		{	m_uSizeofEnumItem	= 0;	}
}
ENUMITEM,	*PENUMITEM;

class CMyTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CMyTreeCtrl();

// Attributes
public:
	HTREEITEM	m_ahItem[MAX_HTREEITEM_SIZE];
	u_long	m_nSizeOfahItem;

	HTREEITEM	m_ahEnumItem[MAX_HTREEITEM_SIZE];
	u_long	m_uSizeofEnumItem;
	u_long	m_uIndexofEnumItem;

	list<PENUMITEM>		m_lspEnumItem;
// Operations
public:
	HTREEITEM	AddItem( DWORD dwId, LPTSTR sText, HTREEITEM hParent );
	HTREEITEM	FindItem( HTREEITEM hItem, DWORD dwData, bool f );
	void	DeleteItemData( HTREEITEM hItem );
	void	Clear( void );

	void	EnumItem( HTREEITEM hItem, bool f );
	void	PostEnumItem( HTREEITEM hItem, bool f, PENUMITEM pEnumItem = NULL );
	BOOL	PeekEnumItem( void );

	HTREEITEM	GethItem( int nIndex );
	u_long	GetSize( void )		{	return m_nSizeOfahItem;		}

	BOOL	IsEndofEnumItem( void )		{	return( ++m_uIndexofEnumItem >= m_uSizeofEnumItem );	}
	BOOL	IsEnumerating( void )	{	return( m_uSizeofEnumItem > 0 );	}
	void	CleanupEnumItem( void )		{	m_uSizeofEnumItem	= m_uIndexofEnumItem	= 0;	}
	HTREEITEM	GetEnumItem( void )	{	return m_ahEnumItem[m_uIndexofEnumItem];	}
	HTREEITEM	GetRootEnumItem( void )		{	ASSERT( IsEnumerating() );	return m_ahEnumItem[0];	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREECTRL_H__3669FCC7_72B5_48C9_AD88_8C5D6C410042__INCLUDED_)
