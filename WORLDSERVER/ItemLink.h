#ifndef __ITEM_LINK__H
#define __ITEM_LINK__H
#ifdef __ITEM_LINK
class CLinkedItemMgr
{
private:
	CLinkedItemMgr(){ m_dwLinkedItemCount = 0;};
	~CLinkedItemMgr(){};
	DWORD m_dwLinkedItemCount;
public:
	map<DWORD,CItemElem*> m_mapLinkedItems;

	static CLinkedItemMgr *GetInstance()
	{
		static CLinkedItemMgr instance;
		return &instance;
	}
	int AddLinkedItem(CItemElem *pItem);
	CItemElem *GetLinkedItem(DWORD dwIndex);
};
#endif
#endif