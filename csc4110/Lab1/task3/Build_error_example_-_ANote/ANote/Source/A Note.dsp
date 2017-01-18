# Microsoft Developer Studio Project File - Name="A Note" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=A Note - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "A Note.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "A Note.mak" CFG="A Note - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "A Note - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "A Note - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "A Note - Win32 With Help" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "A Note - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Version.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "A Note - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MCBS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Version.lib /nologo /entry:"" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "A Note - Win32 With Help"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "A_Note___Win32_With_Help"
# PROP BASE Intermediate_Dir "A_Note___Win32_With_Help"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "With_Help"
# PROP Intermediate_Dir "With_Help"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_SHOWHELP" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG" /d "_SHOWHELP"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Version.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 Version.lib /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "A Note - Win32 Release"
# Name "A Note - Win32 Debug"
# Name "A Note - Win32 With Help"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\A Note.cpp"
# End Source File
# Begin Source File

SOURCE=".\A Note.rc"
# End Source File
# Begin Source File

SOURCE=.\AutoRichEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Base64.cpp
# End Source File
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\CMapi.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCreateNewLanguage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeleteInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGuide.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLanguage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsBehaviour.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsFont.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsHotKey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsLanguage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsLooks.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsNewNote.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsRecycleBin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsTransparancy.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecycleBin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecycleBinHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSnooze.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUserInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUseUserInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorLog.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\LayeredWindowHelperST.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Note.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\RecycleBin.cpp
# End Source File
# Begin Source File

SOURCE=.\SAPrefsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SAPrefsStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\SAPrefsSubDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemTray.cpp
# End Source File
# Begin Source File

SOURCE=.\Translate.cpp
# End Source File
# Begin Source File

SOURCE=.\Xml.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\A Note.h"
# End Source File
# Begin Source File

SOURCE=.\AutoRichEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Base64.h
# End Source File
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\CMapi.h
# End Source File
# Begin Source File

SOURCE=.\DlgCreateNewLanguage.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeleteInformation.h
# End Source File
# Begin Source File

SOURCE=.\DlgGuide.h
# End Source File
# Begin Source File

SOURCE=.\DlgLanguage.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsBehaviour.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsDatabase.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsFont.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsGeneral.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsHotKey.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsLanguage.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsLooks.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsNewNote.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsRecycleBin.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsToolbar.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsTransparancy.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecycleBin.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecycleBinHelp.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetTitle.h
# End Source File
# Begin Source File

SOURCE=.\DlgSnooze.h
# End Source File
# Begin Source File

SOURCE=.\DlgUserInformation.h
# End Source File
# Begin Source File

SOURCE=.\DlgUseUserInformation.h
# End Source File
# Begin Source File

SOURCE=.\ErrorLog.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\LayeredWindowHelperST.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Note.h
# End Source File
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=.\RecycleBin.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SAPrefsDialog.h
# End Source File
# Begin Source File

SOURCE=.\SAPrefsStatic.h
# End Source File
# Begin Source File

SOURCE=.\SAPrefsSubDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemTray.h
# End Source File
# Begin Source File

SOURCE=.\Translate.h
# End Source File
# Begin Source File

SOURCE=.\Xml.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\A Note.ico"
# End Source File
# Begin Source File

SOURCE=".\res\A Note.rc2"
# End Source File
# Begin Source File

SOURCE=.\res\alarm.ico
# End Source File
# Begin Source File

SOURCE=.\res\alarm1.ico
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bold.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bold1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bold2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close.bmp
# End Source File
# Begin Source File

SOURCE=.\res\download.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\italic.bmp
# End Source File
# Begin Source File

SOURCE=.\res\italic1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menubar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minimize.bmp
# End Source File
# Begin Source File

SOURCE=.\res\note.bmp
# End Source File
# Begin Source File

SOURCE=.\res\notealar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\notebull.bmp
# End Source File
# Begin Source File

SOURCE=.\res\noteclos.bmp
# End Source File
# Begin Source File

SOURCE=.\res\notemini.bmp
# End Source File
# Begin Source File

SOURCE=.\res\options.bmp
# End Source File
# Begin Source File

SOURCE=.\res\slidelef.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sliderig.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\strikeou.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\traymain.ico
# End Source File
# Begin Source File

SOURCE=.\res\underlin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\uploadno.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Alarm.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section A Note : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
