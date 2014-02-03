// MYTREECTRL.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "MYTREECTRL.h"

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl

CMyTreeCtrl::CMyTreeCtrl()
{
	m_nSizeOfahItem		= 0;
	m_uSizeofEnumItem	= 0;
	m_uIndexofEnumItem	= 0;
}

CMyTreeCtrl::~CMyTreeCtrl()
{
}

void CMyTreeCtrl::Clear( void )
{
	DeleteItemData( GetRootItem() );
	DeleteAllItems();
}

HTREEITEM CMyTreeCtrl::AddItem( DWORD dwId, LPTSTR sText, HTREEITEM hParent )
{
	TVINSERTSTRUCT t;
	ZeroMemory( &t, sizeof(TVINSERTSTRUCT) );
	t.hParent	= hParent;
	t.hInsertAfter	= TVI_SORT;
	t.item.mask		= TVIF_STATE | TVIF_TEXT;
	t.item.pszText	= sText;
	t.item.state	= TVIS_EXPANDED;
	t.item.stateMask	= TVIS_EXPANDED;
	HTREEITEM hItem	= InsertItem( &t );
	PSrvrData pData	= new SrvrData;
	pData->dwId	= dwId;
	SetItemData( hItem, (DWORD)pData );

	if( dwId < MAX_ID ) {
		SetCheck( hItem, TRUE );
		m_ahItem[m_nSizeOfahItem++]		= hItem;
	}

	return hItem;
}

HTREEITEM CMyTreeCtrl::FindItem( HTREEITEM hItem, DWORD dwData, bool f )
{
	if( hItem == (HTREEITEM)NULL )
		return (HTREEITEM)NULL;

	PSrvrData pSrvrData	= (PSrvrData)GetItemData( hItem );
	if( f == true ) {
		if( pSrvrData->dwId == dwData )
			return hItem;
	}
	else {
		if( pSrvrData->dpid == dwData )
			return hItem;
	}

	if( TRUE == ItemHasChildren( hItem ) )
	{
		HTREEITEM hFind		= FindItem( GetChildItem( hItem ), dwData, f );
		if( hFind != (HTREEITEM)NULL )
			return hFind;
		return FindItem( GetNextSiblingItem( hItem ), dwData, f );
	}
	else
	{
		return FindItem( GetNextSiblingItem( hItem ), dwData, f );
	}
}

void CMyTreeCtrl::DeleteItemData( HTREEITEM hItem )
{
	if( hItem == (HTREEITEM)NULL )
		return;

	PSrvrData pData		= (PSrvrData)GetItemData( hItem );
	if( NULL != pData )
	{
		safe_delete( pData );
		SetItemData( hItem, NULL );
	}
	
	if( TRUE == ItemHasChildren( hItem ) )
	{
		DeleteItemData( GetChildItem( hItem ) );
		DeleteItemData( GetNextSiblingItem( hItem ) );
	}
	else
	{
		DeleteItemData( GetNextSiblingItem( hItem ) );
	}
}

void CMyTreeCtrl::EnumItem( HTREEITEM hItem, bool f )
{
	if( hItem == (HTREEITEM)NULL )
		return;

	if( f == true ) {
		m_uSizeofEnumItem	= 0;
		m_uIndexofEnumItem	= 0;
	}

	PSrvrData pData		= (PSrvrData)GetItemData( hItem );
	ASSERT( pData );
	if( pData->dwId < MAX_ID )
		m_ahEnumItem[m_uSizeofEnumItem++]	= hItem;

	if( TRUE == ItemHasChildren( hItem ) )
	{
		if( f == false )
			EnumItem( GetNextSiblingItem( hItem ), false );
		EnumItem( GetChildItem( hItem ), false );
	}
	else
	{
		if( f == false )
			EnumItem( GetNextSiblingItem( hItem ), false );
	}
}

void CMyTreeCtrl::PostEnumItem( HTREEITEM hItem, bool f, PENUMITEM pEnumItem )
{
	if( hItem == (HTREEITEM)NULL )
		return;

	if( f == true )
		pEnumItem	= new ENUMITEM;

	PSrvrData pData		= (PSrvrData)GetItemData( hItem );
	ASSERT( pData );
	if( pData->dwId < MAX_ID )
		pEnumItem->m_ahEnumItem[pEnumItem->m_uSizeofEnumItem++]		= hItem;

	if( TRUE == ItemHasChildren( hItem ) )
	{
		if( f == false )
			PostEnumItem( GetNextSiblingItem( hItem ), false, pEnumItem );
		PostEnumItem( GetChildItem( hItem ), false, pEnumItem );
	}
	else
	{
		if( f == false )
			PostEnumItem( GetNextSiblingItem( hItem ), false, pEnumItem );
	}

	if( f == true )
	{
		m_lspEnumItem.push_back( pEnumItem );
	}
}

BOOL CMyTreeCtrl::PeekEnumItem( void )
{
	if( m_lspEnumItem.empty() )
		return FALSE;

	PENUMITEM pEnumItem		= m_lspEnumItem.front();
	m_lspEnumItem.pop_front();
	memcpy( m_ahEnumItem, pEnumItem->m_ahEnumItem, sizeof(HTREEITEM) * pEnumItem->m_uSizeofEnumItem );
	m_uSizeofEnumItem	= pEnumItem->m_uSizeofEnumItem;
	SAFE_DELETE( pEnumItem );
	return TRUE;
}

HTREEITEM CMyTreeCtrl::GethItem( int nIndex )
{
	if( nIndex >= 0 && nIndex < (int)( m_nSizeOfahItem ) )
		return m_ahItem[nIndex];
	return (HTREEITEM)NULL;
}

BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMyTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl message handlers
