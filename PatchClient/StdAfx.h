// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C3FD7543_3660_400F_96AB_3D447E42A6EA__INCLUDED_)
#define AFX_STDAFX_H__C3FD7543_3660_400F_96AB_3D447E42A6EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define	_WIN32_WINNT	0x0500
#define	WINVER	0x0500

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
//#include <afxinet.h>	    // MFC Internet support
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxhtml.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxpriv2.h>

#include <atlbase.h>
#include <windows.h>
#include <oleauto.h>
#include <assert.h>
#include <dsetup.h>
#include <wininet.h>
#include <mmsystem.h>
#include <list>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;


#include "VersionCommon.h"
#include "memtrace.h"
#include "vutil.h"
#include "CmnHdr.h"
#include "File.h"
#include "Scanner.h"
#include "Debug.h"


#define NOTICE_REFRESH ( WM_USER + 1 )
#define SEND_PROCESSID ( WM_USER + 2 )


#define PATCH_LOGFILE	"PatchLog.txt"

#define _S _fnLoadString
CString _fnLoadString( UINT id, ... );

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C3FD7543_3660_400F_96AB_3D447E42A6EA__INCLUDED_)
