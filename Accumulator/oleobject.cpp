// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "oleobject.h"


/////////////////////////////////////////////////////////////////////////////
// COLEObject properties

/////////////////////////////////////////////////////////////////////////////
// COLEObject operations

long COLEObject::GetIndex()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString COLEObject::GetKey()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void COLEObject::SetKey(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString COLEObject::GetClass()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long COLEObject::GetDisplayType()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void COLEObject::SetDisplayType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT COLEObject::GetObjectVerbs()
{
	VARIANT result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT COLEObject::GetObjectVerbFlags()
{
	VARIANT result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long COLEObject::GetObjectVerbsCount()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void COLEObject::DoVerb(const VARIANT& verb)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &verb);
}

long COLEObject::FetchVerbs()
{
	long result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}
