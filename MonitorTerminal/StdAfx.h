// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__7AF470FF_FC3C_479B_895B_4B810584EDAE__INCLUDED_)
#define AFX_STDAFX_H__7AF470FF_FC3C_479B_895B_4B810584EDAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define	_WIN32_WINNT	0x0500
#define	WINVER		0x0500

#include <afxwin.h>
#include <stdio.h>
#include <winsock2.h>
#include <mmsystem.h>

#include "compile.h"
#include "cmnhdr.h"
#include "chassert.h"

#include <list>
using	namespace	std;

#include "xUtil.h"
#include "memtrace.h"
#include "dxutil.h"
#include "data.h"
#include "debug.h"
#include "file.h"
#include "scanner.h"
#include "vutil.h"
#include "targa.h"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7AF470FF_FC3C_479B_895B_4B810584EDAE__INCLUDED_)
