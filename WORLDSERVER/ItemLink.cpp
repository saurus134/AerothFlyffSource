#include "stdafx.h"

#ifdef __ITEM_LINK
#include "ItemLink.h"
int CLinkedItemMgr::AddLinkedItem(CItemElem *pItem)
{
	if(!pItem)
		return 0;
	m_mapLinkedItems.insert(make_pair<DWORD,CItemElem*>(++m_dwLinkedItemCount,pItem));
	return m_dwLinkedItemCount;
}
CItemElem *CLinkedItemMgr::GetLinkedItem(DWORD dwIndex)
{
	map<DWORD,CItemElem*>::iterator it = m_mapLinkedItems.find(dwIndex);
	if(it == m_mapLinkedItems.end())
		return FALSE;
	return it->second;
}
#endif