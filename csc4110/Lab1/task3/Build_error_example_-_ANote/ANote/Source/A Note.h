#if !defined(AFX_ANOTE_H__D613E0FC_95B8_47A2_B4C8_B01C6DE46276__INCLUDED_)
#define AFX_ANOTE_H__D613E0FC_95B8_47A2_B4C8_B01C6DE46276__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "LayeredWindowHelperST.h"
#include "MainFrm.h"
#include "ErrorLog.h"
#include "Translate.h"

// The read and write buffer size
#define BUFFERSIZE 4096 * sizeof (TCHAR)
#define TextSize 196

// Information about one note that will occur in the linked list
	struct tagNote	{
		CString		szNoteID;
		CString		szAlarmTime;
		CString		szTitle;
		CString		szText;
		int			iNoteVersion;
		BOOL		bDockedLeft;
		BOOL		bDockedTop;
		BOOL		bDockedRight;
		BOOL		bDockedBottom;
		BOOL		bUseAlarm;
		BOOL		bVisible;
		COLORREF	cfNoteColor;
		CRect		cRect;
		CRect		cRectPosition;
		BOOL		bSlidedLeft;
		BOOL		bSlidedRight;
	};

class CANoteApp : public CWinApp
{
public:
	CANoteApp();

	CLayeredWindowHelperST	m_Layered;					// For transparancy

	BOOL		m_bStayOnTop;							// TRUE -> Stay on top
	COLORREF	m_cfNoteColor;							// The default note color
	COLORREF	m_cfHyperLinkColor;						// The hyperlink color in a note
	COLORREF	m_cfHyperVisitedColor;					// The hyperlink color (visited) in a note
	COLORREF	m_cfHyperHoverColor;					// The hyperlink color (hover) in a note
	CString		m_szDefaultTitle;						// The default title on the notes
	CString		m_szAlarmSoundFile;						// The sound file that will be played on alarm
	CString		m_szUserName;							// The user name that is used when uploading notes
	CString		m_szPassword;							// The password that is used when uploading notes
	CString		m_szServerAddress;						// The server's address
	CString		m_szServerPort;							// The server's port
	CString		m_szServerPath;							// The server's path;
	CString		m_szRecycleBinNumberOfNotes;			// The total number of notes that will be saved when they are deleted (in deleted notes.xml)
	CString		m_szLanguageIni;						// The ini-file that is being used for the languages (ie. English.ini)
	BOOL		m_bRndNoteColor;						// TRUE -> Randomize the note color
	BOOL		m_bThinNoteBorder;						// TRUE -> The note has only a very thin border
	BOOL		m_bMinimizeShrink;						// TRUE -> When minimized the note is shrinked and NOT invisible
	BOOL		m_bWarnOnDelete;						// TRUE -> Warn the user when deleting a note
	BOOL		m_bBlinkNote;							// TRUE -> When the alarm is shouting blink the note
	BOOL		m_bPlayAlarmSound;						// TRUE -> Play the sound when alarm is shouting
	BOOL		m_bDockable;							// TRUE -> The notes can be docked to the screen border
	BOOL		m_bUploadDownload;						// TRUE -> Upload the notes on start and download on exit
	BOOL		m_bCheckLatestVersion;					// TRUE -> Check if there are any newer version at sourceforge.net
	BOOL		m_bNewNoteDockLeft;						// TRUE -> When creating a new note it will be docked to the left side
	BOOL		m_bNewNoteDockTop;						// TRUE -> When creating a new note it will be docked to the top side
	BOOL		m_bNewNoteDockRight;					// TRUE -> When creating a new note it will be docked to the right side
	BOOL		m_bNewNoteDockBottom;					// TRUE -> When creating a new note it will be docked to the bottom side
	BOOL		m_bDoubleClickOnTitleBar;				// TRJE -> When double clicking on the titlebar -> restore/maximize the window otherwise set the title
	BOOL		m_bUseHotKey;							// TRUE -> The user can use a hot key to create a new note
	BOOL		m_bHotKeyShift;							// TRUE -> Press Shift as hot key
	BOOL		m_bHotKeyCtrl;							// TRUE -> Press Ctrl as hot key
	BOOL		m_bHotKeyWin;							// TRUE -> Press Win as hot key
	BOOL		m_bHotKeyAlt;							// TRUE -> Press Alt as hot key
	BOOL		m_bMinimizeMoveCursor;					// TRUE -> When the note is minimized move the cursor to the minimizebutton
	BOOL		m_bUseDefaultServer;					// TRUE -> Use the server at sourceforge.net
	BOOL		m_bSortRecycleBinDescending;			// TRUE -> Sort the deleted note descending (last deleted first)
	BOOL		m_bShowDeleteMessage;					// TRUE -> Show the dialog that learn the user how the recycle bin works
	int			m_iToolBarUseBold;						// if > 0 Show the bold button in the note's toolbar (the place)
	int			m_iToolBarUseItalic;					// if > 0 Show the italic button in the note's toolbar (the place)
	int			m_iToolBarUseUnderline;					// if > 0 Show the underline button in the note's toolbar (the place)
	int			m_iToolBarUseBullet;					// if > 0 Show the bullet button in the note's toolbar (the place)
	int			m_iToolBarUseMinimize;					// if > 0 Show the minimize button in the note's toolbar (the place)
	int			m_iToolBarUseSlideLeft;					// if > 0 Show the slide left button in the note's toolbar (the place)
	int			m_iToolBarUseSlideRight;				// if > 0 Show the slide right button in the note's toolbar (the place)
	int			m_iToolBarUseStrikeOut;					// if > 0 Show the strikeout button in the note's toolbar (the place)

	int			m_iToolBarButtonWidth;					// The width of the toolbar buttons
	int			m_iStartDownloadingAfter;				// Delay the internet connection (seconds)
	int			m_iTransparantNormal;					// The value of transparancy of normal notes
	int			m_iTransparantMinimized;				// The value of transparancy of minimized notes
	int			m_iHotKeyCharacter;						// TRUE -> Press this character as a hot key
	int			m_iHotKeyID;							// Used when setting the hot key
	int			m_iNewNoteLeft;							// When creating a new note where should the left side be (if not docked)
	int			m_iNewNoteTop;							// When creating a new note where should the top side be (if not docked)
	int			m_iNewNoteWidth;						// When creating a new note how wide should it be
	int			m_iLeftClickOnTrayIcon;					// Determin what will happend when the user single left clicks on the tray icon
	int			m_iCharset;								// The selected charset that the program will use when creating a font to write the slided title with
	CString		m_szCharsetName;						// The selected charset (in readable name) (see above)

	//{{AFX_VIRTUAL(CANoteApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL


	//{{AFX_MSG(CANoteApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// Global functions
extern CString GetApplicationDataPath ();				// Get the application data path (c:\documents and settings\username\Application Data\A Note)
extern CString GetProgramPath ();						// Get the program path (c:\program files\a note)
extern CANoteApp theApp;								// Pointer to the class CANoteApp
extern CString StringDecode(CString szText);			// Base 64 and UTF-8 Decode a CString
extern CString StringEncode(CString szText);			// Base 64 and UTF-8 Encode a CString
extern CString GetProgramVersion();						// Get the program version in plain text (A Note 0.2)


//{{AFX_INSERT_LOCATION}}

#endif
