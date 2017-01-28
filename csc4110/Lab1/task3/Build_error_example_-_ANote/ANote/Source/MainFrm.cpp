#include "stdafx.h"
#include "A Note.h"
#include <atlconv.h>

#include "MainFrm.h"
#include "Note.h"
#include "SAPrefsDialog.h"

#include "DlgOptionsGeneral.h"
#include "DlgOptionsLooks.h"
#include "DlgSnooze.h"
#include "DlgOptionsAlarm.h"
#include "DlgOptionsDatabase.h"
#include "DlgUserInformation.h"
#include "DlgUseUserInformation.h"
#include "DlgOptionsFont.h"
#include "DlgOptionsNewNote.h"
#include "DlgOptionsTransparancy.h"
#include "DlgOptionsHotKey.h"
#include "DlgOptionsServer.h"

#include "DlgRecycleBin.h"
#include "DlgOptionsRecycleBin.h"
#include "DlgOptionsToolbar.h"
#include "DlgOptionsBehaviour.h"
#include "DlgOptionsLanguage.h"
#include "DlgLanguage.h"
#include "DlgOptionsCharset.h"

#include "Translate.h"
#include "RecycleBin.h"
#include <afx.h>
#include <afxwin.h>
#include <afxinet.h>
#include <atlbase.h>
#include <afxpriv.h>
#include "Base64.h"
#include "CMapi.h"
#include "xml.h"
#include "Backup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	WM_ICON_NOTIFY			WM_APP+10



IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_TRAYMAIN_NEWNOTE, OnTraymainNewnote)
	ON_COMMAND(ID_TRAYMAIN_RESTOREALL, OnTraymainRestoreall)
	ON_COMMAND(ID_TRAYMAIN_MINIMIZEALL, OnTraymainMinimizeall)
	ON_COMMAND(ID_TRAYMAIN_OPTIONS, OnTraymainOptions)
	ON_COMMAND(ID_TRAYMAIN_STAYONTOP, OnTraymainStayontop)
	ON_UPDATE_COMMAND_UI(ID_TRAYMAIN_STAYONTOP, OnUpdateTraymainStayontop)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_TRAYMAIN_VISITANOTEWEBSITE, OnTraymainVisitanotewebsite)
	ON_UPDATE_COMMAND_UI(ID_TRAYMAIN_MINIMIZEALL, OnUpdateTraymainMinimizeall)
	ON_UPDATE_COMMAND_UI(ID_TRAYMAIN_RESTOREALL, OnUpdateTraymainRestoreall)
	ON_COMMAND(ID_TRAYMAIN_IMPORTEXPORT_IMPORT, OnTraymainImportexportImport)
	ON_COMMAND_RANGE(ID_MINIMIZEDMENUITEM, ID_MINIMIZEDMENUITEM19, OnRestoreMinimizedNote)
	ON_COMMAND(ID_TRAYMAIN_IMPORTEXPORT_EXPORT, OnTraymainImportexportExport)
	ON_MESSAGE (ID_GETNOTESFROMTHREAD, OnGetNotesThread)
	ON_MESSAGE (ID_GETVERSIONFROMTHREAD, OnGetLatesVersionThread)
	ON_COMMAND(ID_TRAYMAIN_UPLOADDOWNLOAD_DOWNLOADNOTES, OnTraymainUploaddownloadDownloadnotes)
	ON_COMMAND(ID_TRAYMAIN_UPLOADDOWNLOAD_UPLOADNOTES, OnTraymainUploaddownloadUploadnotes)
	ON_UPDATE_COMMAND_UI(ID_TRAYMAIN_UPLOADDOWNLOAD_UPLOADNOTES, OnUpdateTraymainUploaddownloadUploadnotes)
	ON_COMMAND(ID_TRAYMAIN_SENDBUGG, OnTraymainSendbugg)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_COMMAND(ID_TRAYMAIN_FAQ, OnTraymainFaq)
	ON_WM_QUERYENDSESSION()
	ON_COMMAND(ID_TRAYMAIN_RECYCLEBIN, OnTraymainRecyclebin)
	ON_COMMAND(ID_TRAYMAIN_RESTORE_RESTOREALL, OnTraymainRestoreall)
	ON_COMMAND(ID_TRAYMAIN_CHECKFORUPDATES, OnTraymainCheckforupdates)
	ON_COMMAND(ID_PRESSEDLEFTBUTTONONTRAYICON, OnPressedLeftButtonOnTrayIcon)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


CMainFrame::CMainFrame()
{
	m_bNotesAreHidden = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

// Create the backup-file
	CBackup backup;
	backup.CreateBackup ();

// Initialize the XML-Parser	
	::CoInitialize(NULL);

	HRESULT hr = m_plDomDocument.CreateInstance(::CLSID_DOMDocument);
	if (FAILED(hr))		{
		CErrorLog::CErrorLog (ERR, _T("Could not initialize the xml parser"));
	}

	ShowWindow (SW_HIDE);


// Create the tray icon
	if (!m_TrayIcon.Create(NULL,                            // Parent window
                           WM_ICON_NOTIFY,                  // Icon notify message to use
                          _T("A Note"),  // tooltip
                           NULL,							// Icon to use
                           IDR_MAINFRAME))//IDR_TRAYMAIN))	// ID of tray icon
		return FALSE;		   

// When I'm debugging the code it's easier for me to know if I'm running
// in UNICODE-mode or not. 
// UNICODE -> Blue tray-icon
// !UNICODE -> Yellow tray-icon
#if (defined (_DEBUG) && (defined(_UNICODE) || defined(UNICODE)))
	m_TrayIcon.SetIcon (MAKEINTRESOURCE (IDI_TRAYMAIN1));
#else
	m_TrayIcon.SetIcon (MAKEINTRESOURCE (IDI_TRAYMAIN));
#endif
	m_TrayIcon.MinimiseToTray (this);

// Set the transparancy to zero to avoid ugly coloring
	theApp.m_iTransparantNormal = theApp.m_iTransparantMinimized = 0;

// See if whe should have hot keys enabled
	if (theApp.m_bUseHotKey)	{
		UINT iModifiers = 0;
		theApp.m_iHotKeyID = GlobalAddAtom(_T("A Note"));

		if (theApp.m_bHotKeyCtrl)	iModifiers += MOD_CONTROL;
		if (theApp.m_bHotKeyShift)	iModifiers += MOD_SHIFT;
		if (theApp.m_bHotKeyAlt)	iModifiers += MOD_ALT;
		if (theApp.m_bHotKeyWin)	iModifiers += MOD_WIN;

		::RegisterHotKey(GetSafeHwnd(), theApp.m_iHotKeyID, iModifiers, 65 + theApp.m_iHotKeyCharacter);	
	}

// To prevent the cursor to jump around on the screen because the notes are minimized,
// we fake that the cursor shouldn't move when the notes are minimized
	theApp.m_bMinimizeMoveCursor = FALSE;

// Load the notes	
	CString szFile;
	szFile.Format (_T("%s\\notes.xml"), GetApplicationDataPath ());
	Load (szFile);

// Start the timer that shows when we want to connect to internet and download the notes
	SetTimer (ID_STARTCONNECTTOINTERNET, 1000 * theApp.m_iStartDownloadingAfter, (TIMERPROC) NULL);

// Start the timer for the alarm
	SetTimer (ID_ALARMTIMER, 1000, (TIMERPROC) NULL);

// Start the autosave timer
	SetTimer (ID_SAVETIMER, 10000, (TIMERPROC) NULL);

// Restore the transparancy color
	theApp.m_iTransparantNormal		= AfxGetApp ()->GetProfileInt	(_T("Settings\\Options"), _T("Transparancy"), 100);
	theApp.m_iTransparantMinimized	= AfxGetApp ()->GetProfileInt	(_T("Settings\\Options"), _T("Transparancy When Minimized"), 100);


	POSITION pos = m_pNotes.GetHeadPosition ();

	while (pos)	{
		CNote * pNote = (CNote *) m_pNotes.GetNext (pos);		

		pNote->SetTransparancy (theApp.m_iTransparantNormal, theApp.m_iTransparantMinimized);
	}

// We alow the cursor to move when the notes are minimized (see a bit up in the code here)
	theApp.m_bMinimizeMoveCursor = AfxGetApp ()->GetProfileInt (_T("Settings\\Options"), _T("When Minimized Move Cursor"), 1);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}


#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif 

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnTraymainNewnote() 
{
// Add a new note and show it
	CNote *pNote = new CNote ();
	pNote->Create (IDD_NOTE, this);
	CRect rc;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);
	CRect rcnote;

// Where should the note appear?
	if (theApp.m_bDockable && theApp.m_bNewNoteDockLeft)	rcnote.left = 0;
	else													rcnote.left = theApp.m_iNewNoteLeft;

	if (theApp.m_bDockable && theApp.m_bNewNoteDockTop)		rcnote.top = 0;
	else													rcnote.top = theApp.m_iNewNoteTop;

	if (theApp.m_bDockable && theApp.m_bNewNoteDockRight)	rcnote.left = rc.right - theApp.m_iNewNoteWidth;
	if (theApp.m_bDockable && theApp.m_bNewNoteDockBottom)	rcnote.top = rc.bottom - 50;

	rcnote.right  = rcnote.left + theApp.m_iNewNoteWidth;
	rcnote.bottom = rcnote.top + 50;

	pNote->MoveWindow (rcnote);
	pNote->SetPosition (CRect (rcnote.left, rcnote.top, theApp.m_iNewNoteWidth, 50), FALSE);
	pNote->SetDockedBottom	(theApp.m_bNewNoteDockBottom, FALSE);
	pNote->SetDockedRight	(theApp.m_bNewNoteDockRight, FALSE);
	pNote->SetDockedLeft	(theApp.m_bNewNoteDockLeft, FALSE);
	pNote->SetDockedTop		(theApp.m_bNewNoteDockTop, FALSE);
	pNote->FixNotePosition	(pNote);

	pNote->ShowWindow (SW_SHOW);

	AddNote ((void *) pNote);
}

void CMainFrame::AddNote(void *pNote)
{
// Add one note to the list

	ASSERT (pNote);

	m_pNotes.AddTail (pNote);
}

void CMainFrame::DeleteNote(void *pNote, bool bSaveDeletedNote)
{
// Delete one note in the list

	ASSERT (pNote);

	POSITION pos = m_pNotes.GetHeadPosition ();
	while (pos)	{
		POSITION delpos = pos;
		void *note = m_pNotes.GetNext (pos);

		if (note == pNote)		{

		// Save the note in the deleted notes.xml
			if (bSaveDeletedNote)	{
				CRecycleBin bin;
				bin.SaveDeletedNote (pNote);
			}

		// Remove the note from the linked list
			m_pNotes.RemoveAt (delpos);
		}
	}
}




void CMainFrame::OnTraymainRestoreall() 
{
// Restore all notes
	POSITION pos = m_pNotes.GetHeadPosition ();

// We don't want the cursor to jump like h-ll
	BOOL bMoveCursor;
	bMoveCursor = theApp.m_bMinimizeMoveCursor;
	theApp.m_bMinimizeMoveCursor = FALSE;

	while (pos)	{
		CNote * pNote = (CNote *) m_pNotes.GetNext (pos);

		if (!pNote->GetSlidedLeft () && !pNote->GetSlidedRight ())
			pNote->RestoreNote ();
	}

	theApp.m_bMinimizeMoveCursor = bMoveCursor;
}

void CMainFrame::OnRestoreMinimizedNote (UINT nID)
{
// Restore the note that is minimized (this functions is called from the traymenu)
	int iCount = nID - ID_MINIMIZEDMENUITEM;

	POSITION pos = m_pNotes.GetHeadPosition ();

	while (pos)	{
		CNote *note = (CNote *) m_pNotes.GetNext (pos);

		if (!note->GetVisible () && iCount == 0)	{
			note->RestoreNote ();
			return;
		}
		if (!note->GetVisible ())
			iCount --;
	}
}

void CMainFrame::OnTraymainMinimizeall() 
{
// Minimize all notes
	POSITION pos = m_pNotes.GetHeadPosition ();

// We don't want the cursor to jump like h-ll
	BOOL bMoveCursor;
	bMoveCursor = theApp.m_bMinimizeMoveCursor;
	theApp.m_bMinimizeMoveCursor = FALSE;

	while (pos)	{
		CNote * pNote = (CNote *) m_pNotes.GetNext (pos);

		if (!pNote->GetSlidedLeft () && !pNote->GetSlidedRight ())
			pNote->MinimizeNote ();
	}
	theApp.m_bMinimizeMoveCursor = bMoveCursor;
}



BOOL CMainFrame::DateGreaterThanOrEqual(COleDateTime &odt1, COleDateTime &odt2)
{
    if (DatesEqual(odt1, odt2)) 
        return TRUE;
    else 
        return odt1 > odt2;
}

BOOL CMainFrame::DatesEqual(COleDateTime &odt1, COleDateTime &odt2)
{
    CString str1 = odt1.Format();
    CString str2 = odt2.Format();

    return (!str1.Compare(str2));
}


void CMainFrame::AnimateTrayAlarm()
{
// Start to animate the tray so that the user knows that
// the alarm is shouting
	m_TrayIcon.SetIconList (IDI_ALARM, IDI_ALARM1);
	m_TrayIcon.Animate (300, -1);
}

void CMainFrame::NoAnimate()
{
// Stop the animation
	m_TrayIcon.StopAnimation ();
}

void CMainFrame::OnTraymainOptions() 
{
	CSAPrefsDialog			dlg;
	CDlgOptionsGeneral		general;
	CDlgOptionsBehaviour	behaviour;
	CDlgOptionsLooks		looks;
	CDlgOptionsNewNote		newnote;
	CDlgOptionsFont			font;
	CDlgOptionsAlarm		alarm;
	CDlgOptionsDatabase		database;
	CDlgOptionsTransparancy transparancy;
	CDlgOptionsHotKey		hotkey;
	CDlgOptionsServer		server;
	CDlgOptionsRecycleBin	recyclebin;
	CDlgOptionsToolbar		toolbar;
	CDlgOptionsLanguage		language;
	CDlgOptionsCharset		charset;

	dlg.AddPage (general,		CTranslate::ReadString (54, _T("General")));
	dlg.AddPage (looks,			CTranslate::ReadString (55, _T("Looks")));
	dlg.AddPage (behaviour,		CTranslate::ReadString (56, _T("Behaviour")));
	dlg.AddPage (newnote,		CTranslate::ReadString (57, _T("New note")));
	dlg.AddPage (font,			CTranslate::ReadString (58, _T("Font")));
	dlg.AddPage (alarm,			CTranslate::ReadString (59, _T("Alarm")));
	dlg.AddPage (database,		CTranslate::ReadString (60, _T("Database")));
	dlg.AddPage (server,		CTranslate::ReadString (61, _T("Server")));
	dlg.AddPage (transparancy,	CTranslate::ReadString (62, _T("Transparancy")));
	dlg.AddPage (hotkey,		CTranslate::ReadString (63, _T("Hot key")));
	dlg.AddPage (recyclebin,	CTranslate::ReadString (64, _T("Recycle bin")));
	dlg.AddPage (toolbar,		CTranslate::ReadString (65, _T("Toolbar")));
	dlg.AddPage (language,		CTranslate::ReadString (66, _T("Language")));
	dlg.AddPage (charset,		CTranslate::ReadString (195, _T("Charset")));


	general.m_bWarnOnDelete		= theApp.m_bWarnOnDelete;
	general.m_szDefaultTitle	= theApp.m_szDefaultTitle;
	general.m_bVersionCheck		= theApp.m_bCheckLatestVersion;

	looks.m_bRndColor			= theApp.m_bRndNoteColor;
	looks.m_bThinBorder			= theApp.m_bThinNoteBorder;
	looks.m_cfColor				= theApp.m_cfNoteColor;

	behaviour.m_bHideOnMinimize			= theApp.m_bMinimizeShrink;
	behaviour.m_bDockable				= theApp.m_bDockable;
	behaviour.m_bDoubleClickOnTitlebar	= theApp.m_bDoubleClickOnTitleBar;
	behaviour.m_bMinimizeMoveCursor		= theApp.m_bMinimizeMoveCursor;
	behaviour.m_iClickOnce				= theApp.m_iLeftClickOnTrayIcon;

	newnote.m_bDockBottom		= theApp.m_bNewNoteDockBottom;
	newnote.m_bDockLeft			= theApp.m_bNewNoteDockLeft;
	newnote.m_bDockRight		= theApp.m_bNewNoteDockRight;
	newnote.m_bDockTop			= theApp.m_bNewNoteDockTop;
	newnote.m_szLeft.Format		(_T("%d"), theApp.m_iNewNoteLeft);
	newnote.m_szTop.Format		(_T("%d"), theApp.m_iNewNoteTop);
	newnote.m_szWidth.Format	(_T("%d"), theApp.m_iNewNoteWidth);

	alarm.m_bBlink				= theApp.m_bBlinkNote;
	alarm.m_bPlaySound			= theApp.m_bPlayAlarmSound;
	alarm.m_szSoundFile			= theApp.m_szAlarmSoundFile;

	database.m_bUploadDownload	= theApp.m_bUploadDownload;
	database.m_szPassword		= theApp.m_szPassword;
	database.m_szUserName		= theApp.m_szUserName;
	database.m_szDownloadAfter.Format (_T("%d"), theApp.m_iStartDownloadingAfter);

	server.m_szAddress			= theApp.m_szServerAddress;
	server.m_szPath				= theApp.m_szServerPath;
	server.m_szPort				= theApp.m_szServerPort;
	server.m_bUseDefaultServer	= theApp.m_bUseDefaultServer;

	transparancy.m_iTransparantMinimized = theApp.m_iTransparantMinimized;
	transparancy.m_iTransparantNormal	 = theApp.m_iTransparantNormal;

	hotkey.m_bAlt				= theApp.m_bHotKeyAlt;
	hotkey.m_bCtrl				= theApp.m_bHotKeyCtrl;
	hotkey.m_bShift				= theApp.m_bHotKeyShift;
	hotkey.m_bWin				= theApp.m_bHotKeyWin;
	hotkey.m_bUseHotKey			= theApp.m_bUseHotKey;
	hotkey.m_iCharacter			= theApp.m_iHotKeyCharacter;

	recyclebin.m_bSortDescending 	= theApp.m_bSortRecycleBinDescending;
	recyclebin.m_szNumberOfNotes	= theApp.m_szRecycleBinNumberOfNotes;

	toolbar.m_iInUseBold		= theApp.m_iToolBarUseBold;
	toolbar.m_iInUseBullet		= theApp.m_iToolBarUseBullet;
	toolbar.m_iInUseItalic		= theApp.m_iToolBarUseItalic;
	toolbar.m_iInUseMinimize	= theApp.m_iToolBarUseMinimize;
	toolbar.m_iInUseSlideLeft	= theApp.m_iToolBarUseSlideLeft;
	toolbar.m_iInUseSlideRight	= theApp.m_iToolBarUseSlideRight;
	toolbar.m_iInUseUnderline	= theApp.m_iToolBarUseUnderline;
	toolbar.m_iInUseStrikeOut	= theApp.m_iToolBarUseStrikeOut;
	toolbar.m_iButtonWidth		= theApp.m_iToolBarButtonWidth;

	language.m_szLanguageIni	= theApp.m_szLanguageIni;

	charset.m_iCharset			= theApp.m_iCharset;
	charset.m_szCharsetName		= theApp.m_szCharsetName;

// The prefs dialog title
	dlg.SetTitle(CTranslate::ReadString (67, _T("Options")));
	dlg.SetConstantText(_T(""));

// Launch it like any other dialog...
	if (dlg.DoModal() == IDOK)	{
	
		theApp.m_bWarnOnDelete			= general.m_bWarnOnDelete;
		theApp.m_szDefaultTitle			= general.m_szDefaultTitle;	
		theApp.m_bCheckLatestVersion	= general.m_bVersionCheck;

		theApp.m_bRndNoteColor			= looks.m_bRndColor;
		theApp.m_bThinNoteBorder		= looks.m_bThinBorder;
		theApp.m_cfNoteColor			= looks.m_cfColor;

		theApp.m_bMinimizeShrink		= behaviour.m_bHideOnMinimize;
		theApp.m_bDockable				= behaviour.m_bDockable;
		theApp.m_bDoubleClickOnTitleBar	= behaviour.m_bDoubleClickOnTitlebar;
		theApp.m_bMinimizeMoveCursor	= behaviour.m_bMinimizeMoveCursor;
		theApp.m_iLeftClickOnTrayIcon	= behaviour.m_iClickOnce;
		
		theApp.m_bNewNoteDockBottom		= newnote.m_bDockBottom;
		theApp.m_bNewNoteDockLeft		= newnote.m_bDockLeft;
		theApp.m_bNewNoteDockRight		= newnote.m_bDockRight;
		theApp.m_bNewNoteDockTop		= newnote.m_bDockTop;
		theApp.m_iNewNoteLeft			= _ttoi (newnote.m_szLeft);
		theApp.m_iNewNoteTop			= _ttoi (newnote.m_szTop);
		theApp.m_iNewNoteWidth			= _ttoi (newnote.m_szWidth);

		theApp.m_bBlinkNote				= alarm.m_bBlink;
		theApp.m_bPlayAlarmSound		= alarm.m_bPlaySound;
		theApp.m_szAlarmSoundFile		= alarm.m_szSoundFile;

		theApp.m_bUploadDownload		= database.m_bUploadDownload;
		theApp.m_szPassword				= database.m_szPassword;
		theApp.m_szUserName				= database.m_szUserName;
		theApp.m_iStartDownloadingAfter	= _ttoi (database.m_szDownloadAfter);

		theApp.m_szLanguageIni			= language.m_szLanguageIni;

		server.m_szAddress.MakeLower ();
		if (server.m_szAddress.Find (_T("http://")) == 0)
			server.m_szAddress.Replace (_T("http://"), _T(""));

		theApp.m_szServerAddress		= server.m_szAddress;
		theApp.m_szServerPath			= server.m_szPath;
		theApp.m_szServerPort			= server.m_szPort;
		theApp.m_bUseDefaultServer		= server.m_bUseDefaultServer;

		theApp.m_iTransparantMinimized	= transparancy.m_iTransparantMinimized;
		theApp.m_iTransparantNormal		= transparancy.m_iTransparantNormal;

		theApp.m_bHotKeyAlt				= hotkey.m_bAlt;
		theApp.m_bHotKeyCtrl			= hotkey.m_bCtrl;
		theApp.m_bHotKeyShift			= hotkey.m_bShift;
		theApp.m_bHotKeyWin				= hotkey.m_bWin;
		theApp.m_bUseHotKey				= hotkey.m_bUseHotKey;
		theApp.m_iHotKeyCharacter		= hotkey.m_iCharacter;

		theApp.m_bSortRecycleBinDescending = recyclebin.m_bSortDescending;
		theApp.m_szRecycleBinNumberOfNotes = recyclebin.m_szNumberOfNotes;

		theApp.m_iToolBarUseBold			= toolbar.m_iInUseBold;
		theApp.m_iToolBarUseItalic			= toolbar.m_iInUseItalic;
		theApp.m_iToolBarUseUnderline		= toolbar.m_iInUseUnderline;
		theApp.m_iToolBarUseBullet			= toolbar.m_iInUseBullet;
		theApp.m_iToolBarUseMinimize		= toolbar.m_iInUseMinimize;
		theApp.m_iToolBarUseSlideLeft		= toolbar.m_iInUseSlideLeft;
		theApp.m_iToolBarUseSlideRight		= toolbar.m_iInUseSlideRight;
		theApp.m_iToolBarUseStrikeOut		= toolbar.m_iInUseStrikeOut;
		theApp.m_iToolBarButtonWidth		= toolbar.m_iButtonWidth;

		theApp.m_szCharsetName				= charset.m_szCharsetName;
		theApp.m_iCharset					= charset.m_iCharset;

		AfxGetApp ()->WriteProfileInt 		( _T("Settings\\Options"), _T("Warn On Delete"),			general.m_bWarnOnDelete);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Check For Latest Version"),	general.m_bVersionCheck);
		AfxGetApp ()->WriteProfileString 	( _T("Settings\\Options"), _T("Default Title"),				general.m_szDefaultTitle);

		AfxGetApp ()->WriteProfileInt 		( _T("Settings\\Options"), _T("Shrinked When Minimized"),	behaviour.m_bHideOnMinimize);
		AfxGetApp ()->WriteProfileInt 		( _T("Settings\\Options"), _T("Randomize Note Color"),		looks.m_bRndColor);
		AfxGetApp ()->WriteProfileInt 		( _T("Settings\\Options"), _T("Thin Note border"),			looks.m_bThinBorder);
		AfxGetApp ()->WriteProfileInt 		( _T("Settings\\Options"), _T("Default Note Color"),		looks.m_cfColor);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Notes Are Dockable"),		behaviour.m_bDockable);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Double Click On The TitleBar"),	behaviour.m_bDoubleClickOnTitlebar);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("When Minimized Move Cursor"),	behaviour.m_bMinimizeMoveCursor);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Action For Single Left Click On The Tray Icon"), behaviour.m_iClickOnce);

		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("New Note Docked Left"),		newnote.m_bDockLeft);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("New Note Docked Top"),		newnote.m_bDockTop);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("New Note Docked Right"),		newnote.m_bDockRight);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("New Note Docked Bottom"),	newnote.m_bDockBottom);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("New Note Left"),				_ttoi (newnote.m_szLeft));
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("New Note Top"),				_ttoi (newnote.m_szTop));
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("New Note Width"),			_ttoi (newnote.m_szWidth));

		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Blink On Alarm"),			alarm.m_bBlink);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Play Sound On Alarm"),		alarm.m_bPlaySound);
		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Alarm Sound File"),			alarm.m_szSoundFile);			

		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Upload And Download Notes"),	database.m_bUploadDownload);
		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Database User Name"),		database.m_szUserName);
		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Database Password"),			database.m_szPassword);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Start Downloading After"),	_ttoi (database.m_szDownloadAfter));

		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Server Address"),			server.m_szAddress);
		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Server Port"),				server.m_szPort);
		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Server Path"),				server.m_szPath);	
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Use Default Server"),		server.m_bUseDefaultServer);

		AfxGetApp ()->WriteProfileInt 		( _T("Settings\\Options"), _T("Transparancy"),				transparancy.m_iTransparantNormal);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Transparancy When Minimized"), transparancy.m_iTransparantMinimized);

		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Hot Key Alt"),				hotkey.m_bAlt);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Hot Key Ctrl"),				hotkey.m_bCtrl);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Hot Key Shift"),				hotkey.m_bShift);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Hot Key Win"),				hotkey.m_bWin);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Hot Key Use It"),			hotkey.m_bUseHotKey);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Hot Key Character"),			hotkey.m_iCharacter);

		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Sort Recycle Bin Descending"), recyclebin.m_bSortDescending);
		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Save Total Number Of Notes For The Recycle Bin"), recyclebin.m_szNumberOfNotes);

		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("ToolBar Use Bold Button Where"),		toolbar.m_iInUseBold);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("ToolBar Use Italic Button Where"),		toolbar.m_iInUseItalic);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("ToolBar Use Underline Button Where"),	toolbar.m_iInUseUnderline);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("ToolBar Use Bullet Button Where"),		toolbar.m_iInUseBullet);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("ToolBar Use Minimize Button Where"),	toolbar.m_iInUseMinimize);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("ToolBar Use Slide Left Button Where"),	toolbar.m_iInUseSlideLeft);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("ToolBar Use Slide Right Button Where"),toolbar.m_iInUseSlideRight);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("ToolBar Use Strikeout Where"),			toolbar.m_iInUseStrikeOut);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("ToolBar Button Width"),			toolbar.m_iButtonWidth);

		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Ini File Used For Language"),	language.m_szLanguageIni);

		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Selected Charset Readable Name"), charset.m_szCharsetName);
		AfxGetApp ()->WriteProfileInt		( _T("Settings\\Options"), _T("Selected Charset Value"),			charset.m_iCharset);

	// See if the number of buttons won't fit when the default note widht is not enough (30 is for the alarm and title
		if (theApp.m_iNewNoteWidth < theApp.m_iToolBarButtonWidth + 30)	{
			CString szTemp;
			szTemp.Format (_T("%s\n%s"), CTranslate::ReadString (175, _T("You have selected to use more toolbar-bottons that will fit in the default notewidth."), CTranslate::ReadString (176, "Would you like to change the default size for new notes?")));
			if (MessageBox (szTemp, _T("A Note"), MB_YESNO) == IDYES)	{
				AfxGetApp ()->WriteProfileInt ( _T("Settings\\Options"), _T("New Note Width"), toolbar.m_iButtonWidth + 60);
				theApp.m_iNewNoteWidth = toolbar.m_iButtonWidth + 60;
			}
		}

	// Set the transparancy and if changed border size
		POSITION pos = m_pNotes.GetHeadPosition ();

		while (pos)	{
			CNote * pNote = (CNote *) m_pNotes.GetNext (pos);		

			pNote->SetTransparancy (theApp.m_iTransparantNormal, theApp.m_iTransparantMinimized);
			pNote->SetBorderStyle (theApp.m_bThinNoteBorder);
			if (!pNote->GetSlidedLeft () && !pNote->GetSlidedRight ())	{
				pNote->HideButtons ();
				pNote->ShowButtons ();
			}

			pNote->Invalidate (TRUE);
		}

	// Should we have hot key or not?
		if (!hotkey.m_bUseHotKey)
			UnregisterHotKey (m_hWnd, theApp.m_iHotKeyID);
	}

	
}

void CMainFrame::OnTraymainStayontop() 
{
	theApp.m_bStayOnTop ? theApp.m_bStayOnTop = FALSE : theApp.m_bStayOnTop = TRUE;
	AfxGetApp ()->WriteProfileInt	( _T("Settings\\Options"), _T("Stay On Top"), theApp.m_bStayOnTop);

	POSITION pos = m_pNotes.GetHeadPosition ();

	while (pos)	{
		CNote * pNote = (CNote *) m_pNotes.GetNext (pos);		

		if (theApp.m_bStayOnTop)
			pNote->SetWindowPos( &wndTopMost,   0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		else
			pNote->SetWindowPos( &wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}

void CMainFrame::OnUpdateTraymainStayontop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (theApp.m_bStayOnTop);
}

void CMainFrame::OnClose() 
{

// Delete the timer
	KillTimer (ID_ALARMTIMER);
	KillTimer (ID_SAVETIMER);


// Save any note	
	CString szFile;
	szFile.Format (_T("%s\\notes.xml"), GetApplicationDataPath ());
	Save (szFile);

// Send the notes to the web
	if (theApp.m_bUploadDownload)
		SendNotesToWeb ();

// Unregister any hotkey
	UnregisterHotKey (m_hWnd, theApp.m_iHotKeyID);


	CFrameWnd::OnClose();
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{

// See if we want to connect to internet
	if (nIDEvent == ID_STARTCONNECTTOINTERNET)	{

		KillTimer (ID_STARTCONNECTTOINTERNET);
	// Get the notes from the website
		if (theApp.m_bUploadDownload)	{
			theApp.m_bMinimizeMoveCursor = FALSE;
			GetNotesFromServer ();
			theApp.m_bMinimizeMoveCursor = AfxGetApp ()->GetProfileInt (_T("Settings\\Options"), _T("When Minimized Move Cursor"), 1);
		}

	// Check for newer version
		if (theApp.m_bCheckLatestVersion)
			CheckForNewerVersion ();
	}

// See if any alarm is beating
	if (nIDEvent == ID_ALARMTIMER)	{

		COleDateTime time = COleDateTime::GetCurrentTime ();
		POSITION pos = m_pNotes.GetHeadPosition ();

		while (pos)	{
			CNote * pNote = (CNote *) m_pNotes.GetNext (pos);		

			if (pNote->GetUseAlarm () && !pNote->IsAlarmShouting ())	{
				if (DateGreaterThanOrEqual (time, pNote->GetAlarm ()))	{
					pNote->ShowAlarm ();
				}
			}
		}
	}
	
// See if we should autosave
	if (nIDEvent == ID_SAVETIMER)	{
		CString szFile;
		szFile.Format (_T("%s\\notes.xml"), GetApplicationDataPath ());
		Save (szFile);
	}


	CFrameWnd::OnTimer(nIDEvent);
}


HMENU CMainFrame::NewMenu()
{
  // Load the menu from the resources
  m_menu.LoadMenu(IDR_MAINFRAME);//IDR_TRAYMAIN);  // ****replace IDR_MAINFRAME with your menu ID****
 
  // Use ModifyODMenu to add a bitmap to a menu options.The first parameter
  // is the menu option text string.If it's NULL, keep the current text
  // string.The second option is the ID of the menu option to change.
  // The third option is the resource ID of the bitmap.This can also be a
  // toolbar ID in which case the class searches the toolbar for the
  // appropriate bitmap.Only Bitmap and Toolbar resources are supported.
  // m_menu.ModifyODMenu(NULL,ID_ZOOM,IDB_ZOOM);
 
  // Another method for adding bitmaps to menu options is through the
  // LoadToolbar member function.This method allows you to add all
  // the bitmaps in a toolbar object to menu options (if they exist).
  // The function parameter is an the toolbar id.
  // There is also a function called LoadToolbars that takes an
  // array of id's.

	m_menu.LoadToolbar(IDR_MENUBAR);
 
	return(m_menu.Detach());
}

void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
 BOOL setflag=FALSE;
  if(lpMeasureItemStruct->CtlType==ODT_MENU){
    if(IsMenu((HMENU)lpMeasureItemStruct->itemID)){
      CMenu* cmenu=CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
      if(BCMenu::IsMenu(cmenu)){
        m_menu.MeasureItem(lpMeasureItemStruct);
        setflag=TRUE;
      }
    }
  }
  if(!setflag)CFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
 LRESULT lresult;
  if(BCMenu::IsMenu(pMenu))
    lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
  else
    lresult=CFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
  return(lresult);
}

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
 CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
  if(!bSysMenu){
    if(BCMenu::IsMenu(pPopupMenu))BCMenu::UpdateMenu(pPopupMenu);
  }
}


void CMainFrame::OnTraymainVisitanotewebsite() 
{
// Go to A Note's website with the default web browser
	CString szTemp;
	TCHAR sPath [MAX_PATH];
	szTemp.Format (_T("%stemp.htm"), GetApplicationDataPath ());
	CFile fp;
	fp.Open (szTemp, CFile::modeCreate | CFile::modeWrite);
	fp.Close ();
	HINSTANCE hINst = FindExecutable (szTemp, GetApplicationDataPath (), sPath);
	DeleteFile (szTemp);
	ShellExecute(NULL, _T("open"),sPath, _T("http://a-note.sourceforge.net"), NULL, SW_SHOWMAXIMIZED);
}

void CMainFrame::OnUpdateTraymainMinimizeall(CCmdUI* pCmdUI) 
{
// See if any is minimized
	bool bMinimize = FALSE;

	POSITION pos = m_pNotes.GetHeadPosition ();

	while (pos)	{
		CNote * pNote = (CNote *) m_pNotes.GetNext (pos);		

		if (pNote->GetVisible ())
			bMinimize = TRUE;
	}

	pCmdUI->Enable (bMinimize);
}

void CMainFrame::OnUpdateTraymainRestoreall(CCmdUI* pCmdUI) 
{
// See if any is minimized
	bool bMinimize = FALSE;

	POSITION pos = m_pNotes.GetHeadPosition ();

	while (pos)	{
		CNote * pNote = (CNote *) m_pNotes.GetNext (pos);		

		if (!pNote->GetVisible ())
			bMinimize = TRUE;
	}

	pCmdUI->Enable (bMinimize);
}


void CMainFrame::OnTraymainImportexportImport() 
{
// Import notes	

	OPENFILENAME ofn;      
	TCHAR szFile[260];      

	szFile[0] = NULL;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter=_T("A Note file (*.xml)\0*.xml");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName (&ofn) != TRUE) return;

	CString szName;
	szName = CString (ofn.lpstrFile);

	Load (szName);
}

void CMainFrame::OnTraymainImportexportExport() 
{
// Export notes	

	OPENFILENAME ofn;      
	TCHAR szFile[260];      

	szFile[0] = NULL;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter=_T("A Note file (*.xml)\0*.xml");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName (&ofn) != TRUE) return;

	CString szName;
	szName = CString (ofn.lpstrFile);

	// Add .xml
	szName.MakeLower ();
	if (szName.Right (4) != _T(".xml"))
		szName += _T(".xml");

// Save the file
	Save (szName);
}



bool CMainFrame::ShowAlarmDialog()
{
// If we have an alarm show the snooze dialog
// This function will be called from the systemtray
// if the user presses on the tray icon

	bool bAlarm = FALSE;
	COleDateTime time = COleDateTime::GetCurrentTime ();
	POSITION pos = m_pNotes.GetHeadPosition ();

	while (pos)	{
		CNote * pNote = (CNote *) m_pNotes.GetNext (pos);		

		if (pNote->GetUseAlarm () && pNote->IsAlarmShouting ())	{
			if (DateGreaterThanOrEqual (time, pNote->GetAlarm ()))	{
				bAlarm = TRUE;
			}
		}
	}

	if (bAlarm)	{
		CDlgSnooze dlg;
	
		if (dlg.DoModal () == IDOK)	{

			pos = m_pNotes.GetHeadPosition ();
			while (pos)	{

				CNote * pNote = (CNote *) m_pNotes.GetNext (pos);		

				if (pNote->GetUseAlarm () && pNote->IsAlarmShouting ())	{
					if (DateGreaterThanOrEqual (time, pNote->GetAlarm ()))	{

					// Snooze -> Set the alarm 10 minutes forward from now
						COleDateTime t1 = COleDateTime::GetCurrentTime ();
						COleDateTime t2; t2.SetTime (0, 10, 0);
						pNote->SetAlarm (t1 + t2);
						CString a;
						a = pNote->GetAlarm ().Format ();
			
						pNote->CloseAlarm ();
						pNote->SetUseAlarm (TRUE);
						pNote->ShowWindow (SW_SHOW);							 
						pNote->Invalidate ();
					}
				}
			}
		}
		else	{

			pos = m_pNotes.GetHeadPosition ();
			while (pos)	{

				CNote * pNote = (CNote *) m_pNotes.GetNext (pos);		

				if (pNote->GetUseAlarm () && pNote->IsAlarmShouting ())	{
					if (DateGreaterThanOrEqual (time, pNote->GetAlarm ()))	{

					// Turn off
						CRect rc;
						rc = pNote->GetPosition ();		
						pNote->CloseAlarm ();
						pNote->SetUseAlarm (FALSE);
						pNote->m_pAlarm.ShowWindow (SW_HIDE);
						pNote->ShowWindow (SW_SHOW);							 
						pNote->Invalidate ();
					}
				}
			}
		}

		return TRUE;
	}


	return FALSE;
}



void CMainFrame::ParseXML(CString szXML)
{
// Parse the XML

// Save the XML
	CString szXMLFile;
	szXMLFile.Format (_T("%s\\tmp.xml"), GetApplicationDataPath ());
	CStdioFile fp;
	if (!fp.Open (szXMLFile, CFile::modeCreate | CFile::modeWrite))	{
		CErrorLog::CErrorLog (ERR, _T("Could not open the tmp.xml file for parsing the xml-file"));
		return;
	}

	TRY
	{
#if (defined (UNICODE) || defined (_UNICODE))
		int iLength, iMultibyte;
		CString szResult;

		iLength	= szXML.GetLength ();
		WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
		char *pcDest = new char [2 * (iLength + 1)];

	// To UTF-8
		iMultibyte = WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
		fp.Write (pcDest, iLength);
		delete []pwcUnicode;
		delete []pcDest;
#else
		fp.Write (szXML, szXML.GetLength ());
#endif
		fp.Close ();
	}
	CATCH (CFileException, e)
	{
		CErrorLog::CErrorLog (ERR, _T("Could not read the tmp.xml-file for parsing the xml"));
		return;
	}
	END_CATCH

// Convert xml file name string to something COM can handle (BSTR)
	_bstr_t bstrFileName;
	bstrFileName = szXMLFile.AllocSysString();

// Call the IXMLDOMDocumentPtr's load function to load the XML document
	variant_t vResult;
	vResult = m_plDomDocument->load(bstrFileName);
	if (((bool)vResult) == TRUE) 	{
	// now that the document is loaded, we need to initialize the root pointer
		m_pDocRoot = m_plDomDocument->documentElement;
	}
	else	{
		DeleteFile (szXMLFile);
		return;
	}

	GetXMLChildren (m_pDocRoot);

// Delete the XML File
	DeleteFile (szXMLFile);
}

void CMainFrame::GetXMLChildren(MSXML2::IXMLDOMNodePtr pParent)
{	
// Determine what type of XML document it is	
	_bstr_t sType = pParent->GetnodeName ( ); 	

// Display the current node's name
	GetXMLChild(pParent);

// Simple for loop to get all children
	for (MSXML2::IXMLDOMNodePtr pChild = pParent->firstChild; NULL != pChild; pChild = pChild->nextSibling) 	{
	// For each child, call this function so that we get its children as well
		GetXMLChildren(pChild);
	}
}


void CMainFrame::GetXMLChild(MSXML2::IXMLDOMNodePtr pChild)
{
	CString szName, szValue;

	MSXML2::IXMLDOMNamedNodeMapPtr pAttribs = pChild->Getattributes(); 
	if (pAttribs != NULL)	{ 
		long nAttriCnt = pAttribs->Getlength(); 

		for(int i = 0; i < nAttriCnt; ++i)	{ 
			MSXML2::IXMLDOMNodePtr pAttrib = pAttribs->Getitem(i); 
			if(pAttrib != NULL) { 
				_bstr_t sName = pAttrib->GetnodeName ( ); 	
				_variant_t vVal = pAttrib->GetnodeValue ( ); 
		
				AfxBSTR2CString (&szName, sName);
				szValue = (const char *) _bstr_t(vVal);

				tagCString string;
				string.szName = szName;
				string.szValue = szValue;
				m_sString.AddTail (string);

			} 
		} 
	} 


	if (MSXML2::NODE_TEXT != pChild->nodeType)	 {
		CString szName, szData;
		AfxBSTR2CString (&szName, pChild->nodeName);

		if (szName == _T("version"))	{

			POSITION pos = m_sString.GetHeadPosition ();
	
			while (pos)	{
			
				tagCString item = m_sString.GetNext (pos);


				if (item.szName == _T("version"))	{				
					m_szVersion = item.szValue;
				}

				if (item.szName == _T("text"))	{
					
					item.szValue = StringDecode (item.szValue);
					if (m_szVersion != GetProgramVersion ())	{
						if (MessageBox ((CString) item.szValue/*basetext.DecodedMessage ()*/,_T("New version"), MB_YESNO | MB_SYSTEMMODAL) == IDYES)	{

						// Visit the download site
							CString szTemp;
							TCHAR sPath [MAX_PATH];
							szTemp.Format (_T("%stemp.htm"), GetApplicationDataPath ());
							CFile fp;
							fp.Open (szTemp, CFile::modeCreate | CFile::modeWrite);
							fp.Close ();
							HINSTANCE hINst = FindExecutable (szTemp, GetApplicationDataPath (), sPath);
							DeleteFile (szTemp);
							ShellExecute(NULL, _T("open"),sPath, _T("http://sourceforge.net/project/showfiles.php?group_id=85069"), NULL, SW_SHOWMAXIMIZED);							
						}
					}
				}
			}	
			m_sString.RemoveAll ();
		}

		if (szName == _T("info"))	{

			POSITION pos = m_sString.GetHeadPosition ();
	
			while (pos)	{
			
				tagCString item = m_sString.GetNext (pos);


				if (item.szName == _T("info"))	{				

				// Email password
					if (item.szValue == _T("password has been emailed"))	{

						AfxMessageBox (CTranslate::ReadString (22, _T("The password has been emailed")));
						m_sString.RemoveAll ();
						return;
					}

				// Wrong password
					if (item.szValue == _T("username exists but wrong password"))	{
						CString szTemp;
						szTemp.Format (_T("%s\n%s"), CTranslate::ReadString (177, _T("Wrong password. If you want the password to be sent to the user's email address, press 'YES'")), CTranslate::ReadString (178, _T("If you want to enter the password yourself, press 'NO'.")));
						if (MessageBox (szTemp, CTranslate::ReadString (179, _T("Wrong password")), MB_YESNO | MB_ICONQUESTION) == IDYES)	{
							
							m_sString.RemoveAll ();
							SendPasswordToEmail ();
						}
						else	{
							m_sString.RemoveAll ();
							UseUser ();

							return;
						}
					}

				// Creation of new user
					if (item.szValue == _T("Creation of new user was successfull"))	{

					
					// Get the notes from the website
						m_sString.RemoveAll ();
						GetNotesFromServer ();
						return;
					}

				// Mysql is down
					if (item.szValue == _T("unable to select database"))	{
						m_sString.RemoveAll ();
						return;
					}
		
				// No notes in the database
					if (item.szValue == _T("no notes"))	{
						m_sString.RemoveAll ();
						return;
					}
				
				// No user or password
					if (item.szValue == _T("no user or password"))	{
						CString szTemp;
						szTemp.Format (_T("%s\n%s"), CTranslate::ReadString (180, _T("To be able to upload and download your notes, you have to create a new user."), CTranslate::ReadString (181, _T("Do you want to create a new user? Press 'YES' or if you already have a username and want to use it press 'NO'"))));
						if (MessageBox (szTemp, CTranslate::ReadString (182, _T("No user or password")), MB_YESNO | MB_ICONQUESTION) == IDYES)	{
							m_sString.RemoveAll ();
							CreateNewUser ();
							return;
						}
						else	{
						}
							m_sString.RemoveAll ();
							UseUser ();
							return;
					}
	
				// The notes couldn't be deleted in the database
					if (item.szValue == _T("The notes couldn't be deleted"))	{
						AfxMessageBox (CTranslate::ReadString (23, _T("The notes couldn't be deleted")));
						m_sString.RemoveAll ();
						return;
					}
				
				// The note couldn't be inserted
					if (item.szValue == _T("The notes couldn't be inserted"))	{
						AfxMessageBox (CTranslate::ReadString (24, _T("The note couldn't be inserted")));
						m_sString.RemoveAll ();
						return;
					}
	
				// The notes was uploaded
					if (item.szValue == _T("The notes was uploaded"))	{
						m_sString.RemoveAll ();
						return;
					}
	
				// No user
					if (item.szValue == _T("no user"))	{
						CString szTemp;
						szTemp.Format (_T("%s\n%s"), CTranslate::ReadString (180, _T("To be able to upload and download your notes, you have to create a new user.")), CTranslate::ReadString (181, _T("Do you want to create a new user? Press 'YES' or if you already have a username and want to use it press 'NO'")));
						if (MessageBox (szTemp, CTranslate::ReadString (182, _T("No user or password")), MB_YESNO | MB_ICONQUESTION) == IDYES)	{
							m_sString.RemoveAll ();
							CreateNewUser ();
							return;
						}
						else	{
							m_sString.RemoveAll ();
							UseUser ();
							return;
						}
					}
				}
			}
		}


		if (szName == _T("note"))	{

			CString szNoteID, szTitle, szAlarmTime, szText;
			int iNoteVersion = 0;
			CRect rect1, rect2;
			bool bUseAlarm, bVisible, bDockedLeft, bDockedTop, bDockedRight, bDockedBottom, bSlidedLeft, bSlidedRight;
			bUseAlarm = bDockedLeft = bDockedTop = bDockedRight = bDockedBottom = FALSE;
			COLORREF cfNoteColor;

			POSITION pos = m_sString.GetHeadPosition ();

			while (pos)	{
				tagCString item = m_sString.GetNext (pos);

				if (item.szName == _T("noteversion"))			iNoteVersion	= _ttoi (item.szValue);
				if (item.szName == _T("notecolor"))				cfNoteColor		= _ttoi (item.szValue);
				if (item.szName == _T("positionleft"))			rect1.left		= _ttoi (item.szValue);
				if (item.szName == _T("positiontop"))			rect1.top		= _ttoi (item.szValue);
				if (item.szName == _T("width"))					rect1.right		= _ttoi (item.szValue);
				if (item.szName == _T("height"))				rect1.bottom	= _ttoi (item.szValue);
				if (item.szName == _T("noteid"))				szNoteID		= item.szValue;
				if (item.szName == _T("alarmtime"))				szAlarmTime		= item.szValue;
				if (item.szName == _T("title"))					szTitle			= item.szValue;
				if (item.szName == _T("usealarm"))				item.szValue	== _T("true") ? bUseAlarm		= TRUE : bUseAlarm		= FALSE;
				if (item.szName == _T("visible"))				item.szValue	== _T("true") ? bVisible		= TRUE : bVisible		= FALSE;
				if (item.szName == _T("dockedleft"))			item.szValue	== _T("true") ? bDockedLeft		= TRUE : bDockedLeft	= FALSE;
				if (item.szName == _T("dockedtop"))				item.szValue	== _T("true") ? bDockedTop		= TRUE : bDockedTop		= FALSE;
				if (item.szName == _T("dockedright"))			item.szValue	== _T("true") ? bDockedRight	= TRUE : bDockedRight	= FALSE;
				if (item.szName == _T("dockedbottom"))			item.szValue	== _T("true") ? bDockedBottom	= TRUE : bDockedBottom	= FALSE;
				if (item.szName == _T("slided-right"))			item.szValue	== _T("true") ? bSlidedRight	= TRUE : bSlidedRight	= FALSE;
				if (item.szName == _T("slided-left"))			item.szValue	== _T("true") ? bSlidedLeft		= TRUE : bSlidedLeft	= FALSE;
				if (item.szName == _T("slidepositionleft"))		rect2.left		= _ttoi (item.szValue);
				if (item.szName == _T("slidepositiontop"))		rect2.top		= _ttoi (item.szValue);
				if (item.szName == _T("slidepositionright"))	rect2.right		= _ttoi (item.szValue);
				if (item.szName == _T("slidepositionbottom"))	rect2.bottom	= _ttoi (item.szValue);			}

			AfxBSTR2CString (&szText, pChild->text);

		// Base 64 decode
			szNoteID	= StringDecode (szNoteID);
			szTitle		= StringDecode (szTitle);
			szAlarmTime = StringDecode (szAlarmTime);
			szText		= StringDecode (szText);

		// Loop to see if the note exists
			bool bCreate = TRUE;
			CNote *pNoteExist = NULL;

			pos = m_pNotes.GetHeadPosition ();
			while (pos)	{
				CNote *pNote = (CNote *) m_pNotes.GetNext (pos);		

				if (pNote->GetNoteID () == szNoteID)	{
					bCreate = FALSE;

					if (pNote->GetNoteVersion () <= iNoteVersion)
						pNoteExist = pNote;
				}
			}			

		// See if we should make a new note
			if (bCreate)	{
				COleDateTime pTime;
				pTime.ParseDateTime (szAlarmTime);//, LOCALE_NOUSEROVERRIDE);
				CNote *pNote = new CNote ();
				pNote->Create			(IDD_NOTE, this);
				iNoteVersion++;
				pNote->SetNoteVersion	(iNoteVersion);
				pNote->SetNoteID		(szNoteID);
				pNote->SetAlarm			(pTime); 
				pNote->SetUseAlarm		(bUseAlarm);				
				pNote->SetTitle			(szTitle);
				pNote->SetVisible		(bVisible);
				pNote->SetNoteColor		(cfNoteColor);
				pNote->SetPosition		(rect1, pNote);
				pNote->SetText			(szText);
				pNote->SetDockedLeft	(bDockedLeft, FALSE);
				pNote->SetDockedTop		(bDockedTop, FALSE);
				pNote->SetDockedRight	(bDockedRight, FALSE);
				pNote->SetDockedBottom	(bDockedBottom, FALSE);
				pNote->SetSlideLeft		(bSlidedLeft, FALSE);
				pNote->SetSlideRight	(bSlidedRight, FALSE);
				pNote->SetSlidePosition (rect2, FALSE);
				pNote->Initialize	();

				AddNote ((void *) pNote);
			}

		// See if we should only update an existing note
			if (pNoteExist)	{
				COleDateTime pTime;
				pTime.ParseDateTime				(szAlarmTime);//, LOCALE_NOUSEROVERRIDE);
				iNoteVersion++;
				pNoteExist->SetNoteVersion		(iNoteVersion);
				pNoteExist->SetAlarm			(pTime);
				pNoteExist->SetUseAlarm			(bUseAlarm);				
				pNoteExist->SetTitle			(szTitle);
				pNoteExist->SetVisible			(bVisible);
				pNoteExist->SetNoteColor		(cfNoteColor);
				pNoteExist->SetPosition			(rect1, FALSE);
				pNoteExist->SetText				(szText);
				pNoteExist->SetDockedLeft		(bDockedLeft, FALSE);
				pNoteExist->SetDockedTop		(bDockedTop, FALSE);
				pNoteExist->SetDockedRight		(bDockedRight, FALSE);
				pNoteExist->SetDockedBottom		(bDockedBottom, FALSE);
				pNoteExist->SetSlideLeft		(bSlidedLeft, FALSE);
				pNoteExist->SetSlideRight		(bSlidedRight, FALSE);
				pNoteExist->SetSlidePosition	(rect2, FALSE);
				pNoteExist->Initialize			();
			}

			m_sString.RemoveAll ();
		}
	}
}


void CMainFrame::AnimateTrayDownload()
{
// Start to animate the tray so that the user knows that
// the notes is being downloaded from the web
	m_TrayIcon.SetIconList (IDI_DOWNLOADNOTE, IDI_DOWNLOADNOTE7);
	m_TrayIcon.Animate (300, -1);
}

void CMainFrame::AnimateTrayUpload()
{
// Start to animate the tray so that the user knows that
// the notes is being uploaded from the web
	m_TrayIcon.SetIconList (IDI_UPLOADNOTE, IDI_UPLOADNOTE7);
	m_TrayIcon.Animate (300, -1);
}

HRESULT CMainFrame::OnGetLatesVersionThread (WPARAM wParam, LPARAM lParam)
{
	ASSERT (wParam || lParam);

// Determin what we should do

// Show the download tray icon arrows
	if (wParam == 1 && lParam == 0)	{
		AnimateTrayDownload ();
	}


// Show the normal tray icon
	if (wParam == 3 && lParam == 0)	{
		NoAnimate ();
	}


// Parse the xml and see if we have an older version than sourceforge
	if (wParam == 4 && lParam != NULL)	{
		CString *szXML = (CString *) lParam;

		ParseXML (*szXML);
	}

	return 0;
}


HRESULT CMainFrame::OnGetNotesThread (WPARAM wParam, LPARAM lParam)
{
	ASSERT (wParam || lParam);

// Determin what we should do

// Show the download tray icon arrows
	if (wParam == 1 && lParam == 0)	{
		AnimateTrayDownload ();
	}


// Show the upload tray icon arrows
	if (wParam == 2 && lParam == 0)	{
		AnimateTrayUpload ();
	}

// Show the normal tray icon
	if (wParam == 3 && lParam == 0)	{
		NoAnimate ();
	}


// Parse the xml and create the notes
	if (wParam == 4 && lParam != NULL)	{
		CString *szXML = (CString *) lParam;

		ParseXML (*szXML);
	}

	return 0;
}


CString CMainFrame::CreateSendXML()
{
// Create the xml that will be sent to A Note's database
	POSITION pos = m_pNotes.GetHeadPosition ();

	CXml xml;
	xml.StartCreateUploadXml ();
	while (pos)	{
		void *pNote = (void *) m_pNotes.GetNext (pos);

		xml.CreateUploadXml (pNote);
	}

	xml.EndCreateUploadXml ();
	return xml.GetCreateUploadXml ();
}


void CMainFrame::SendNotesToWeb()
{

// Change the tray icon to show arrows
	AnimateTrayUpload ();

	CString szPath, szSendXML, szXML;
	szPath.Format (_T("%ssendnotes.php?user=%s&password=%s"), theApp.m_szServerPath, StringEncode (theApp.m_szUserName), StringEncode (theApp.m_szPassword));

// Get the send xml
	szSendXML = CreateSendXML ();

	if (Send (theApp.m_szServerAddress, szPath, szSendXML, szXML))	{

		CStdioFile f;
		if (!f.Open (GetApplicationDataPath () + _T("\\Send Notes.xml"), CFile::modeCreate | CFile::modeWrite))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open the file Send Notes.xml for writing"));
			return;
		}

		TRY
		{
#if (defined (UNICODE) || defined (_UNICODE))
			int iLength;
			iLength	= szSendXML.GetLength ();
			WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
			char * pcDest	  = new	char [ 2 * (iLength + 1)];

		// To UTF-8
			WideCharToMultiByte (CP_UTF8, 0, szSendXML, iLength , pcDest, 2*iLength, NULL, NULL);
			f.Write (pcDest, iLength);
			delete []pcDest;
			delete []pwcUnicode;
#else
			f.Write (szSendXML, szSendXML.GetLength ());
#endif
			f.Close ();
		}
		CATCH (CFileException, e)
		{
			CErrorLog::CErrorLog (ERR, _T("Could not write the file Send Notes.xml"));
			return;
		}
		END_CATCH

		CStdioFile fp;
		if (!fp.Open (GetApplicationDataPath () + _T("\\Send Answer.xml"), CFile::modeCreate | CFile::modeWrite))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open the file Send Answer.xml for writing"));
			return;
		}

		TRY
		{
#if (defined (UNICODE) || defined (_UNICODE))
			int iLength;
			iLength	= szXML.GetLength ();
			WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
			char * pcDest	  = new	char [ 2 * (iLength + 1)];

		// To UTF-8
			WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
			fp.Write (pcDest, iLength);
			delete []pcDest;
			delete []pwcUnicode;
#else
			fp.Write (szXML, szXML.GetLength ());
#endif
			fp.Close ();
		}
		CATCH (CFileException, e)
		{
			CErrorLog::CErrorLog (ERR, _T("Could not write the file Send Answer.xml"));
			return;
		}
		END_CATCH
	}
}

void CMainFrame::OnTraymainUploaddownloadDownloadnotes() 
{
// Download the notes
	GetNotesFromServer ();
}


void CMainFrame::OnTraymainUploaddownloadUploadnotes() 
{
// Send the notes to the web
	SendNotesToWeb ();
}



void CMainFrame::OnUpdateTraymainUploaddownloadUploadnotes(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_pNotes.GetCount () > 0 ? TRUE : FALSE);	
}


void CMainFrame::CreateMinimizedMenu(BCMenu *pMainMenu, BCMenu *pMinimize)
{
// Show the minimized notes on the system tray menu (max 20)
	pMainMenu->EnableMenuItem (6, MF_GRAYED | MF_BYPOSITION);

	for (int i = 0; i < 20; i++)
		pMinimize->RemoveMenu (0, MF_BYPOSITION);

	int iCount = 0;

	POSITION pos = m_pNotes.GetHeadPosition ();

	while (pos)	{
		CNote *note = (CNote *) m_pNotes.GetNext (pos);		

		if (!note->GetVisible () && iCount <= 20)	{

	USES_CONVERSION;
	char *pTemp = (char *) malloc (note->GetTitle ().GetLength () + 1);
	for (int i = 0; i < note->GetTitle ().GetLength (); i++)
		pTemp[i] = note->GetTitle ().GetAt (i);
	pTemp [note->GetTitle ().GetLength () + 1] = '\0';
	TCHAR* szWide = A2T( pTemp );
	delete pTemp;

			pMinimize->AppendMenu (MF_STRING ,ID_MINIMIZEDMENUITEM + iCount, szWide);
			pMainMenu->EnableMenuItem (6, MF_ENABLED | MF_BYPOSITION);

			iCount++;
		}
	}
}



void CMainFrame::CreateNewUser()
{
// Create a new user
	CDlgUserInformation dlg;
	dlg.m_szPassword	= theApp.m_szPassword;
	dlg.m_szUserName	= theApp.m_szUserName;

	if (dlg.DoModal () == IDOK)	{

	// Save the new user
		theApp.m_szUserName = dlg.m_szUserName;
		theApp.m_szPassword	= dlg.m_szPassword;

		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Database User Name"),	dlg.m_szUserName);
		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Database Password"),		dlg.m_szPassword);

	// Try to create the new user
		CString szPath, szData, szTemp, szXML;

		szPath.Format (_T("%screateuser.php"), theApp.m_szServerPath);
		szData = _T("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><UserInformation>");

		szTemp.Format (_T("<username>%s</username>"), StringEncode (theApp.m_szUserName));
		szData += szTemp;
		szTemp.Format (_T("<password>%s</password>"), StringEncode (theApp.m_szPassword));
		szData += szTemp;
		szTemp.Format (_T("<email>%s</email>"), StringEncode (dlg.m_szEmail));
		szData += szTemp;
		szData += _T("</UserInformation>");

		if (Send (theApp.m_szServerAddress, szPath, szData, szXML))	{
		
			CStdioFile f;
			if (!f.Open (GetApplicationDataPath () + _T("\\Send UserName.xml"), CFile::modeCreate | CFile::modeWrite))	{
				CErrorLog::CErrorLog (INFO, _T("Could not open the file Send UserName.xml"));
				return;
			}

			TRY
			{
#if (defined (UNICODE) || defined (_UNICODE))
				int iLength;
				iLength	= szData.GetLength ();
				WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
				char * pcDest	  = new	char [ 2 * (iLength + 1)];

			// To UTF-8
				WideCharToMultiByte (CP_UTF8, 0, szData, iLength , pcDest, 2*iLength, NULL, NULL);
				f.Write (pcDest, iLength);
				delete []pcDest;
				delete []pwcUnicode;
#else
				f.Write (szData, szData.GetLength ());
#endif
				f.Close ();
			}
			CATCH (CFileException, E)
			{
				CErrorLog::CErrorLog (ERR, _T("Could not write in the file Send UserName.xml"));
				return;
			}
			END_CATCH
	
			CStdioFile fp;
			if (!fp.Open (GetApplicationDataPath () + _T("\\Create new user answer.xml"), CFile::modeCreate | CFile::modeWrite))	{
				CErrorLog::CErrorLog (INFO, _T("Could not open the file Create new user answer.xml"));
				return;
			}

			TRY
			{
#if (defined (UNICODE) || defined (_UNICODE))
				int iLength;
				iLength	= szXML.GetLength ();
				WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
				char * pcDest	  = new	char [ 2 * (iLength + 1)];

			// To UTF-8
				WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
				fp.Write (pcDest, iLength);
				delete []pcDest;
				delete []pwcUnicode;
#else
				fp.Write (szXML, szXML.GetLength ());
#endif
				fp.Close ();
			}
			CATCH (CFileException, e)
			{
				CErrorLog::CErrorLog (ERR, _T("Could not write the file Create new user answer.xml"));
				return;
			}
			END_CATCH

			ParseXML (szXML);
		}		
	}
}

void CMainFrame::SendPasswordToEmail()
{
// Send the right password to the email address that is associated to the user
	CString szData, szTemp, szPath, szXML;

	szPath.Format (_T("%ssendpasswordtoemail.php"), theApp.m_szServerPath);
	szData = _T("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><SendEmail>");
	szTemp.Format (_T("<username>%s</username>"), StringEncode (theApp.m_szUserName));
	szData += szTemp;
	szData += _T("</UserInformation>");

	if (Send (theApp.m_szServerAddress, szPath, szData, szXML))	{

		CStdioFile f;
		if (!f.Open (GetApplicationDataPath () + _T("\\Send Email.xml"), CFile::modeCreate | CFile::modeWrite))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open the file Send Email.xml"));
			return;
		}

		TRY
		{
#if (defined (UNICODE) || defined (_UNICODE))
			int iLength;
			iLength	= szData.GetLength ();
			WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
			char * pcDest	  = new	char [ 2 * (iLength + 1)];

		// To UTF-8
			WideCharToMultiByte (CP_UTF8, 0, szData, iLength , pcDest, 2*iLength, NULL, NULL);
			f.Write (pcDest, iLength);
			delete []pcDest;
			delete []pwcUnicode;
#else
			f.Write (szData, szData.GetLength ());
#endif
			f.Close ();
		}
		CATCH (CFileException, e)
		{
			CErrorLog::CErrorLog (ERR, _T("Could not write the file Send Eamil.xml"));
			return;
		}
		END_CATCH

		CStdioFile fp;
		if (!fp.Open (GetApplicationDataPath () + _T("\\Send email answer.xml"), CFile::modeCreate | CFile::modeWrite))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open the file Send email answer.xml"));
			return;
		}

		TRY
		{
#if (defined (UNICODE) || defined (_UNICODE))
			int iLength;
			iLength	= szXML.GetLength ();
			WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
			char * pcDest	  = new	char [ 2 * (iLength + 1)];

		// To UTF-8
			WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
			fp.Write (pcDest, iLength);
			delete []pcDest;
			delete []pwcUnicode;
#else
			fp.Write (szXML, szXML.GetLength ());
#endif
			fp.Close ();
		}
		CATCH (CFileException, e)
		{
			CErrorLog::CErrorLog (ERR, _T("Could not write the file Send email answer.xml"));
			return;
		}
		END_CATCH

		ParseXML (szXML);
	}
}


void CMainFrame::CheckForNewerVersion()
{
	CString szUserID;
	szUserID = AfxGetApp ()->GetProfileString (_T("Settings\\Extra"), _T("User ID Used To Count Number Of Users In Database"), _T(""));

	if (szUserID == _T(""))	{
		szUserID				= _T("                                                  ");
		srand( (unsigned)time( NULL ) );
		for (int i = 0; i < 50; i++)
			szUserID.SetAt (i, (rand () % (1 + 25 - 1)) + 65);

		AfxGetApp ()->WriteProfileString (_T("Settings\\Extra"), _T("User ID Used To Count Number Of Users In Database"), szUserID);
	}

	CString szPath, szXML;

	szPath.Format (_T("%sgetversion.php?userid=%s"), theApp.m_szServerPath, szUserID);

// See if there are any newer version on the database
	if (Send (_T("a-note.sourceforge.net"), szPath, "", szXML))	{
		CStdioFile f;
		if (!f.Open (GetApplicationDataPath () + _T("\\Get Latest Version.xml"), CFile::modeCreate | CFile::modeWrite))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open the file Get Latest Version.xml"));
			return;
		}

		TRY
		{
#if (defined (UNICODE) || defined (_UNICODE))
			int iLength, iMultibyte;
			CString szResult;

			iLength	= szXML.GetLength ();
			WCHAR *pwcUnicode = new WCHAR[sizeof (WCHAR) * (iLength + 1)];
			char *pcDest = new char[2 * (iLength + 1)];
		// To UTF-8
			iMultibyte = WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
			f.Write (pcDest, iMultibyte);
			delete []pwcUnicode;
			delete []pcDest;
#else
			f.Write (szXML, szXML.GetLength ());
#endif
			f.Close ();
		}
		CATCH (CFileException, e)
		{
			CErrorLog::CErrorLog (ERR, _T("Could not write the file Get Latest Version.xml"));
			return;
		}
		END_CATCH

		ParseXML (szXML);
	}
}

void CMainFrame::GetNotesFromServer()
{
// Change the tray icon to show arrows
	AnimateTrayDownload ();

	CString szTemp, szXML, szPath;

	szPath.Format (_T("%sgetnotes.php?user=%s&password=%s"), theApp.m_szServerPath, StringEncode (theApp.m_szUserName), StringEncode (theApp.m_szPassword));

	if (Send (theApp.m_szServerAddress, szPath, "", szXML))	{

		CFile f;
		if (!f.Open (GetApplicationDataPath () + _T("\\Get Notes Answer.xml"), CFile::modeCreate | CFile::modeWrite))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open Get Notes Anser.xml"));
			return;
		}

		TRY
		{
			f.Write (szXML, szXML.GetLength ());
			f.Close ();
		}
		CATCH (CFileException, e)
		{
			CErrorLog::CErrorLog (ERR, _T("Could not write file Get Notes Answer.xml"));
			return;
		}
		END_CATCH

		ParseXML (szXML);
	}
}

void CMainFrame::UseUser()
{
// Create a new user
	CDlgUseUserInformation dlg;
	dlg.m_szPassword	= theApp.m_szPassword;
	dlg.m_szUserName	= theApp.m_szUserName;

	if (dlg.DoModal () == IDOK)	{

	// Save the new user
		theApp.m_szUserName = dlg.m_szUserName;
		theApp.m_szPassword	= dlg.m_szPassword;

		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Database User Name"),	dlg.m_szUserName);
		AfxGetApp ()->WriteProfileString	( _T("Settings\\Options"), _T("Database Password"),		dlg.m_szPassword);

	// Get the notes
		GetNotesFromServer ();
	}
}

void CMainFrame::OnTraymainSendbugg() 
{
// Send bugg or feedback email to A Note's admin

//Create the message
	CMapiMessage message;

//Setup the all the recipient types for this message
	message.AddMultipleRecipients(_T("brummelisa@users.sourceforge.net"), CMapiMessage::TO);

//Add the Subject and Body
	message.m_sBody = _T("[Place your bugg or feedback here]");
	message.m_sSubject = _T("Bug / Feedback from A Note");

//connect to server
	CMapiSession connection;
    BOOL bLogon = FALSE;
    bLogon = connection.SharedLogon();

	if (!bLogon)       {
	}
	else       {

	//Send the message
        BOOL bSuccess = FALSE;

		if (!connection.Send(message, 1, 1, this))         {
			CString sMsg;
			sMsg.Format(_T("%s\nError: %d"), CTranslate::ReadString (25, _T("Couldn't send message!")), connection.GetLastError());
			AfxMessageBox(sMsg, MB_ICONSTOP);
		}
	}	
	
}


LRESULT CMainFrame::OnHotKey(WPARAM wParam, LPARAM lParam)
{

// The hot key was pressed
	OnTraymainNewnote ();

	return 0;
}
void CMainFrame::OnTraymainFaq() 
{
// Show the faq	
	ShellExecute(NULL, _T("open"), GetProgramPath () + _T("\\faq.html"), _T(""), NULL, SW_SHOWMAXIMIZED);
}



BOOL CMainFrame::OnQueryEndSession() 
{
	if (!CFrameWnd::OnQueryEndSession())
		return FALSE;
	

// Windows is shutting down -> save
	CMainFrame *pMain = (CMainFrame*) ::AfxGetMainWnd ();
	CString szFile;
	szFile.Format (_T("%s\\notes.xml"), GetApplicationDataPath ());
	Save (szFile);

// Send the notes to the web
	if (theApp.m_bUploadDownload)
		pMain->SendNotesToWeb ();
	
	return TRUE;
}

BOOL CMainFrame::Send(CString szServerAddress, CString szPath, CString szXML, CString &szDataBack)
{
// Send the xml to the server. This function is being called whenever 
// anything should be sent to the server
	BOOL bRead = TRUE;
	DWORD dwReply;
	CInternetSession session;
	CHttpConnection *connect;
	CHttpFile *file;
	CString szTemp;

// Connect to the server	
	connect = session.GetHttpConnection ((LPCTSTR) szServerAddress,
										NULL,
										_ttoi (theApp.m_szServerPort),
										NULL,
										NULL);

// Write a post and get the services
	file = connect->OpenRequest (_T("POST"),szPath);
	file->AddRequestHeaders(_T("Content-Type:text/xml; charset=utf-8\n"));

	try {
	#if (defined (UNICODE) || defined (_UNICODE))
		int iLength, iMultibyte;
		iLength	= szXML.GetLength ();
		WCHAR *pwcUnicode = new WCHAR[sizeof (WCHAR) * (iLength + 1)];
		char *pcDest = new char[2 * (iLength + 1)];
		char *res;
		_tcscpy(pwcUnicode, szXML);

	// To UTF-8
		iMultibyte = WideCharToMultiByte (CP_UTF8, 0,pwcUnicode, iLength , pcDest, 2*iLength, NULL, NULL);
		pcDest [iMultibyte] = '\0';
		pcDest [iMultibyte+1] = '\0';

		file->SendRequest(NULL, 0, (LPVOID)(LPCTSTR) pcDest, iMultibyte);
		delete []pcDest;
		delete []pwcUnicode;
	#else
		file->SendRequest(NULL, 0, (LPVOID)(LPCTSTR) szXML, szXML.GetLength ());
	#endif
	}
	catch (CInternetException *e)
	{
		e->Delete ();

	// Change the tray icon to normal
		NoAnimate ();

		delete connect;
		delete file;

		return FALSE;
	}	


// See what the server replied
	file->QueryInfoStatusCode (dwReply);

	if (dwReply != 200)	{

		connect->Close ();
		file->Close ();

		delete connect;
		delete file;

	// Change the tray icon to normal
		NoAnimate ();

		return FALSE;
	}

// 200 (ok) -> Read the reply to receive the services and send it back

// Since the string on the server is ansi-coded we have to read it like that
#if (defined(UNICODE) || defined(_UNICODE))

	char *pTemp, *pData;
	BOOL bDone = TRUE;
	DWORD dwTotal = 0;

	pData = (char *) malloc (100);
	memset (pData, NULL, 100);
	pTemp = (char *) malloc (100);	
	memset (pTemp, NULL, 100);

	while (bRead)	{
		memset (pTemp, NULL,100);
		bRead = (bool) file->ReadString ((LPTSTR)pTemp,50);
		dwTotal += strlen (pTemp)/2;
		if (strlen (pTemp) != 0)	{
			pData = (char *) realloc (pData, dwTotal+2);
			int a = strlen (pTemp);
			memcpy ((pData + dwTotal - strlen (pTemp)/2), pTemp, strlen (pTemp)/2); 
		}
	}

// Fix the end
	pData[dwTotal] = '\0';
	pData[dwTotal+1] = '\0';
	szDataBack = (CString) pData;
	free (pData);
	free (pTemp);
#else
// Read the ansi-coded string from the server
	while (bRead)	{
		bRead = (bool) file->ReadString (szTemp);
		szDataBack += szTemp;
	}
#endif



// Close the session
	session.Close ();

	connect->Close ();
	file->Close ();

	delete connect;
	delete file;

// Change the tray icon to normal
	NoAnimate ();

	return TRUE;
}


void CMainFrame::OnTraymainRecyclebin() 
{
// Start the recycle bin part so we can find our deleted notes
	CDlgRecycleBin dlg;
	dlg.DoModal ();
}

void CMainFrame::OnTraymainCheckforupdates() 
{
	CheckForNewerVersion ();	

	if (m_szVersion == GetProgramVersion ())
		AfxMessageBox (CTranslate::ReadString (26, _T("You have the latest version of A Note")));
}


void CMainFrame::OnPressedLeftButtonOnTrayIcon ()
{
// The user has pressed on the tray icon with the left button
// and no alarm is on.
// Determin what we should do.
	POSITION pos;

	switch (theApp.m_iLeftClickOnTrayIcon)	{

	case 0: // Create a new note fast
		OnTraymainNewnote ();
		break;

	case 1: // Hide / Show all notes
		pos = m_pNotes.GetHeadPosition ();

		while (pos)	{
			CNote * pNote = (CNote *) m_pNotes.GetNext (pos);
			if (m_bNotesAreHidden)	{
				pNote->ShowWindow (SW_SHOW);
				m_TrayIcon.SetTooltipText (_T("A Note"));
			}
			else	{
				pNote->ShowWindow (SW_HIDE);
				CString szTemp;
				szTemp.Format (_T("A Note\n%s"), CTranslate::ReadString (19, _T("Notes are hidden")));
				m_TrayIcon.SetTooltipText (szTemp);
			}
		}
		m_bNotesAreHidden = !m_bNotesAreHidden;
		break;

	default: // Oups, something is wrong here
		ASSERT (FALSE);
		break;
	}
}

// Since the program don't use ::Serialize anymore, we save the notes with this one
void CMainFrame::Save(CString szFileName)
{
	CRect rc1, rc2;
	CString szXML;
	COleDateTime pTime;

// Save the data as xml
	CXml xml;
	xml.StartCreateSaveXml ();

// Save the notes
	POSITION pos = m_pNotes.GetHeadPosition ();

	while (pos)	{
		void *pNote = (void *) m_pNotes.GetNext (pos);
			
		xml.CreateSaveXml (pNote);
	}

	xml.EndCreateSaveXml ();
	szXML = xml.GetCreateSaveXml ();

	CStdioFile cf;
	if (!cf.Open (szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText))	{
		CErrorLog::CErrorLog (INFO, _T("Could not open the file notes.xml when saving the notes"));
		return;
	}

	TRY
	{
#if (defined (UNICODE) || defined (_UNICODE))
		int iLength;
		iLength	= szXML.GetLength ();
		WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
		char * pcDest	  = new	char [ 2 * (iLength + 1)];

	// To UTF-8
		WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
		cf.Write (pcDest, iLength);
		delete []pcDest;
		delete []pwcUnicode;
#else
		cf.Write (szXML, szXML.GetLength ());
#endif
		cf.Close();
	}
	CATCH (CFileException, e)	{
		CErrorLog::CErrorLog (ERR, _T("Could not write the notes.xml-file"));
		return;
	}
	END_CATCH
}


void CMainFrame::Load (CString szFileName)
{
// Read the xml file
	CString szXML;
	char *pTemp, *pData;
	DWORD dwRead = 1, dwTotal = 0;

// Try to open the file
	CStdioFile cf;
	if (!cf.Open (szFileName, CFile::modeRead | CFile::typeText))	{
		return;
	}

	pData = (char*) malloc (BUFFERSIZE);
	memset (pData, NULL, BUFFERSIZE);
	pTemp = (char *) malloc (BUFFERSIZE);	
	memset (pTemp, NULL, BUFFERSIZE);

	while (dwRead)	{
		memset (pTemp, NULL,BUFFERSIZE);
		TRY
		{
				dwRead = cf.Read (pTemp, BUFFERSIZE);
		}
		CATCH (CFileException, e)	
		{
			CErrorLog::CErrorLog (ERR, _T("Could not read the file notes.xml"));
			free (pTemp);
			free (pData);
			return;
		}
		END_CATCH

		dwTotal += dwRead;
		if (dwRead != 0)	{
			pData = (char *) realloc (pData, dwTotal+1);
			memcpy ((pData + (dwTotal - dwRead)), pTemp, dwRead); 
		}
	}

	pData[dwTotal] = '\0';

	TRY
	{
		cf.Close ();
	}
	CATCH (CFileException, e)	
	{
		CErrorLog::CErrorLog (INFO, _T("Could not close the file notes.xml when reading"));
		free (pTemp);
		free (pData);
	}
	END_CATCH

// Parse the xml
	ParseXML (CString (pData));

	free (pTemp);
	free (pData);
}
