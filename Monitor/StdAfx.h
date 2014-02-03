// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D3E3FEA1_F5A0_486E_9E54_7D5FDA64C524__INCLUDED_)
#define AFX_STDAFX_H__D3E3FEA1_F5A0_486E_9E54_7D5FDA64C524__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define	_WIN32_WINNT	0x0500
#define	WINVER		0x0500

//#define __SEND_SMS		// 서버 다운시 문자 전송
//#define __DB_CHECK		// DB를 주기적으로 체크

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <winsock2.h>
#include <mmsystem.h>

#include "compile.h"
#include "memtrace.h"
#include "cmnhdr.h"
#include "chassert.h"
#include "vutil.h"
#include "xUtil.h"
#include "targa.h"

#include <list>
#include <vector>
using	namespace	std;

#include "dxutil.h"
#include "file.h"
#include "scanner.h"
#include "data.h"
#include "debug.h"

#include "dbmanager.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D3E3FEA1_F5A0_486E_9E54_7D5FDA64C524__INCLUDED_)
