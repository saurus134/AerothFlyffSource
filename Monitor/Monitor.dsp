# Microsoft Developer Studio Project File - Name="Monitor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Monitor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Monitor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Monitor.mak" CFG="Monitor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Monitor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Monitor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Neurospace/Program/Monitor", BHSYBAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Monitor - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /I "." /I "..\_DirectX" /I "..\_Common" /I "..\_network\mcl\include" /I "..\_network\misc\include" /I "..\_network\net\include" /I "..\_network" /I "..\_database" /I "..\..\Resource" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "__MONITORSRVR" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib winmm.lib ..\_network\mcl\lib\release\mcl.lib odbc32.lib odbccp32.lib d3dx9.lib /nologo /subsystem:windows /incremental:yes /map /debug /machine:I386

!ELSEIF  "$(CFG)" == "Monitor - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\_DirectX" /I "..\_Common" /I "..\_network\mcl\include" /I "..\_network\misc\include" /I "..\_Database" /I "..\_network\net\include" /I "..\_network" /I "..\_database" /I "..\..\Resource" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib winmm.lib ..\_network\mcl\lib\release\mcl.lib odbc32.lib odbccp32.lib d3dx9.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"MSVCRT" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Monitor - Win32 Release"
# Name "Monitor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dbmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\dpconsolesrvr.cpp
# End Source File
# Begin Source File

SOURCE=.\dpmonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\host.cpp
# End Source File
# Begin Source File

SOURCE=.\Monitor.cpp
# End Source File
# Begin Source File

SOURCE=.\Monitor.rc
# End Source File
# Begin Source File

SOURCE=.\MonitorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MYTREECTRL.cpp
# End Source File
# Begin Source File

SOURCE=.\scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\SMS.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\compile.h
# End Source File
# Begin Source File

SOURCE=.\dbmanager.h
# End Source File
# Begin Source File

SOURCE=.\dpconsolesrvr.h
# End Source File
# Begin Source File

SOURCE=.\dpmonitor.h
# End Source File
# Begin Source File

SOURCE=.\host.h
# End Source File
# Begin Source File

SOURCE=..\_Common\memtrace.h
# End Source File
# Begin Source File

SOURCE=.\Monitor.h
# End Source File
# Begin Source File

SOURCE=.\MonitorDlg.h
# End Source File
# Begin Source File

SOURCE=.\MYTREECTRL.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\scanner.h
# End Source File
# Begin Source File

SOURCE=.\SMS.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Monitor.ico
# End Source File
# Begin Source File

SOURCE=.\MONITOR.INI
# End Source File
# Begin Source File

SOURCE=.\res\Monitor.rc2
# End Source File
# Begin Source File

SOURCE=.\TEST.ini
# End Source File
# Begin Source File

SOURCE=.\type.wav
# End Source File
# End Group
# Begin Group "Neuz Files"

# PROP Default_Filter ""
# Begin Group "Dx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\_DirectX\dxutil.cpp
# End Source File
# Begin Source File

SOURCE=..\_DirectX\dxutil.h
# End Source File
# End Group
# Begin Group "Cmn"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\_Common\data.h
# End Source File
# Begin Source File

SOURCE=..\_Common\debug.cpp
# End Source File
# Begin Source File

SOURCE=..\_Common\debug.h
# End Source File
# Begin Source File

SOURCE=..\_Common\file.cpp
# End Source File
# Begin Source File

SOURCE=..\_Common\file.h
# End Source File
# Begin Source File

SOURCE=..\_Common\LuaBase.cpp
# End Source File
# Begin Source File

SOURCE=..\_Common\LuaBase.h
# End Source File
# Begin Source File

SOURCE=..\_common\targa.cpp
# End Source File
# Begin Source File

SOURCE=..\_common\targa.h
# End Source File
# Begin Source File

SOURCE=..\_common\vutil.cpp
# End Source File
# Begin Source File

SOURCE=..\_common\vutil.h
# End Source File
# Begin Source File

SOURCE=..\_Common\xUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\_Common\xUtil.h
# End Source File
# End Group
# Begin Group "Scr"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "Network Files"

# PROP Default_Filter ""
# Begin Group "Mcl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\_network\mcl\include\cmcl.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclautolock.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclautoptr.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclcritsec.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclevent.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclglobal.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclkernel.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmcllinkedlists.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclmailbox.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclmonitor.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclmutex.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclsemaphore.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclsharedmemory.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclthread.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclwaitablecollection.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\include\cmclwaitableobject.h
# End Source File
# Begin Source File

SOURCE=..\_network\mcl\lib\release\mcl.lib
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\_network\misc\src\ar.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\misc\include\ar.h
# End Source File
# Begin Source File

SOURCE=..\_network\misc\include\chassert.h
# End Source File
# Begin Source File

SOURCE=..\_Network\Misc\Src\heapmng.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\misc\include\heapmng.h
# End Source File
# Begin Source File

SOURCE=..\_network\misc\include\MEMPOOLER.H
# End Source File
# Begin Source File

SOURCE=..\_network\misc\include\mymap.h
# End Source File
# End Group
# Begin Group "Net"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\_network\net\src\buffer.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\net\include\buffer.h
# End Source File
# Begin Source File

SOURCE=..\_network\net\src\clientsock.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\net\include\clientsock.h
# End Source File
# Begin Source File

SOURCE=..\_network\net\src\clientsocke.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\net\include\clientsocke.h
# End Source File
# Begin Source File

SOURCE=..\_network\net\src\dpmng.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\net\include\dpmng.h
# End Source File
# Begin Source File

SOURCE=..\_network\net\src\dpsock.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\net\include\dpsock.h
# End Source File
# Begin Source File

SOURCE=..\_network\net\src\serversock.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\net\include\serversock.h
# End Source File
# Begin Source File

SOURCE=..\_network\net\src\serversocke.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\net\include\serversocke.h
# End Source File
# Begin Source File

SOURCE=..\_network\net\src\sock.cpp
# End Source File
# Begin Source File

SOURCE=..\_network\net\include\sock.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\_network\CmnHdr.h
# End Source File
# Begin Source File

SOURCE=..\_network\MsgHdr.h
# End Source File
# End Group
# Begin Group "Database Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\_Database\des.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\_Database\des.h
# End Source File
# Begin Source File

SOURCE=..\_Database\Query.cpp
# End Source File
# Begin Source File

SOURCE=..\_Database\Query.h
# End Source File
# End Group
# End Target
# End Project
