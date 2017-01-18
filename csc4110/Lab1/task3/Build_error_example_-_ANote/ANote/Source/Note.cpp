// Note.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "Note.h"
#include "BCMenu.h"
#include "DlgSetTitle.h"
#include "DlgSetAlarm.h"
#include "DlgSnooze.h"
#include "Mmsystem.h"
#include "CMapi.h"
#include "DlgDeleteInformation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 #define ON_WM_NCHITTEST() \
    { WM_NCHITTEST, 0, 0, 0, AfxSig_l_p, \
        (AFX_PMSG)(AFX_PMSGW) \
        (static_cast< UINT (AFX_MSG_CALL CWnd::*)(CPoint) > (&ThisClass :: OnNcHitTest)) },

/////////////////////////////////////////////////////////////////////////////
// CNote dialog


CNote::CNote(CWnd* pParent /*=NULL*/)
	: CDialog(CNote::IDD, pParent)
{

// Initialize
	m_bBelongsToRecycleBin	= FALSE;
	m_szNoteID				= "                                                  ";
	m_iNoteVersion			= 0;
	m_bIsAlarmShouting		= FALSE;
	m_bUseAlarm				= FALSE;
	m_Alarm					= COleDateTime::GetCurrentTime ();
	m_szTitle				= GetDefaultTitle ();
	m_szText				= "";
	m_bVisible				= TRUE;

	srand( (unsigned)time( NULL ) );
	for (int i = 0; i < 50; i++)
		m_szNoteID.SetAt (i, (rand () % (1 + 70 - 1)) + 33);

// The note's color
	if (theApp.m_bRndNoteColor)	{
		int iColor [8] = {RGB (255, 128, 128),
						  RGB (255, 255, 128),	
						  RGB (128, 255, 128),
						  RGB (128, 255, 255),
						  RGB (255, 128, 64),
						  RGB (0,   128, 128),
						  RGB (0,   128, 192),
						  RGB (255, 0,   0),
		};
		int iRnd = rand() % (1 + (8 - 1));
		m_cfNoteColor = iColor [iRnd];	
	}
	else
		m_cfNoteColor = theApp.m_cfNoteColor;			

	//{{AFX_DATA_INIT(CNote)
	//}}AFX_DATA_INIT
}


void CNote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNote)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNote, CDialog)
	//{{AFX_MSG_MAP(CNote)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_BN_CLICKED(ID_NOTECLOSE, OnCloseNote)
	ON_BN_CLICKED(ID_NOTEALARM, OnAlarm)
	ON_BN_CLICKED(ID_NOTEMINIMIZE, OnMinimize)
	ON_BN_CLICKED(ID_NOTEBULLET, OnBullet)
	ON_BN_CLICKED(ID_BOLD, OnBold)
	ON_BN_CLICKED(ID_ITALIC, OnItalic)
	ON_BN_CLICKED(ID_STRIKEOUT, OnStrikeOut)
	ON_BN_CLICKED(ID_UNDERLINE, OnUnderline)
	ON_BN_CLICKED(ID_SLIDERIGHT, OnSlideRight)
	ON_BN_CLICKED(ID_SLIDELEFT, OnSlideLeft)
	ON_COMMAND(ID_POPUPMENU_CUT, OnPopupmenuCut)
	ON_COMMAND(ID_POPUPMENU_COPY, OnPopupmenuCopy)
	ON_COMMAND(ID_POPUPMENU_PASTE, OnPopupmenuPaste)
	ON_COMMAND(ID_POPUPMENU_NOTECOLOR, OnPopupmenuNotecolor)
	ON_COMMAND(ID_POPUPMENU_FONT, OnPopupmenuFont)
	ON_WM_NCLBUTTONDBLCLK()
	ON_COMMAND(ID_POPUPMENU_ALARM, OnPopupmenuAlarm)
	ON_COMMAND(ID_POPUPMENU_SETTITLE, OnPopupmenuSettitle)
	ON_NOTIFY(EN_LINK, ID_NOTETEXT, OnTextLink)
	ON_WM_TIMER()
	ON_NOTIFY(EN_REQUESTRESIZE , ID_NOTETEXT, OnRequestResize)
	ON_WM_MOVING()
	ON_COMMAND(ID_POPUPMENU_EMAIL, OnPopupmenuEmail)
	ON_COMMAND(ID_POPUPMENU_PRINT, OnPopupmenuPrint)
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCRBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE( WM_DISPLAYCHANGE, OnDisplayChange )
	ON_WM_CONTEXTMENU()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP




END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNote message handlers

BOOL CNote::OnInitDialog() 
{
	CDialog::OnInitDialog();

// Modify the style
	theApp.m_Layered.AddLayeredStyle(m_hWnd);

// Set the trasparency (only Win2K and XP)
	SetTransparancy (theApp.m_iTransparantNormal, theApp.m_iTransparantMinimized);

// Create the Text
	m_pText.Create (	WS_CHILD |
						ES_WANTRETURN |
						ES_AUTOVSCROLL |
						ES_MULTILINE |
						WS_VISIBLE,
						CRect(0,0,0,0), 
						this,
						ID_NOTETEXT);
	CHARFORMAT2 c;
	c.cbSize			= AfxGetApp ()->GetProfileInt	 (_T("Options\\Font"), _T("cbSize"),			0);
	c.dwMask			= AfxGetApp ()->GetProfileInt	 (_T("Options\\Font"), _T("dwMask"),			0);
	c.dwEffects			= AfxGetApp ()->GetProfileInt	 (_T("Options\\Font"), _T("dwEffects"),			0);
	c.yHeight			= AfxGetApp ()->GetProfileInt	 (_T("Options\\Font"), _T("yHeight"),			0);
	c.yOffset			= AfxGetApp ()->GetProfileInt	 (_T("Options\\Font"), _T("yOffset"),			0);
	c.crTextColor		= AfxGetApp ()->GetProfileInt	 (_T("Options\\Font"), _T("crTextColor"),		0);
	c.bCharSet			= AfxGetApp ()->GetProfileInt	 (_T("Options\\Font"), _T("bCharSet"),			0);
	c.bPitchAndFamily	= AfxGetApp ()->GetProfileInt	 (_T("Options\\Font"), _T("bPitchAndFamily"),	0);
	CString szTemp		(AfxGetApp ()->GetProfileString  (_T("Options\\Font"), _T("szFaceName"),		_T("")));
	_tcscpy( c.szFaceName, szTemp );

// First time
	if (c.cbSize == 0)
		m_pText.SetFont (GetFont (), FALSE);
	else
		m_pText.SetSelectionCharFormat (c);


	m_pText.SendMessage  (EM_AUTOURLDETECT, 1, 0);
	m_pText.SetEventMask (ENM_REQUESTRESIZE | ENM_LINK);
	

// Create the alarm button
	m_pAlarm.Create (	_T(""),
						WS_CHILD ,
				//		WS_VISIBLE,
						CRect (0,0,0,0),
						this,
						ID_NOTEALARM);

// Create the minimize button
	m_pMinimize.Create (	_T(""),
							WS_CHILD |
							WS_VISIBLE,
							CRect (0,0,0,0),
							this,
							ID_NOTEMINIMIZE);


// Create the close button
	m_pClose.Create (	_T(""),
						WS_CHILD |
						WS_VISIBLE,
						CRect (0,0,0,0),
						this,
						ID_NOTECLOSE);


// Create the bullet button
	m_pBullet.Create (	_T(""),
						WS_CHILD |
						WS_VISIBLE,
						CRect (0,0,0,0),
						this,
						ID_NOTEBULLET);

// Create the slide right button
	m_pSlideRight.Create (_T(""),
						WS_CHILD |
						WS_VISIBLE,
						CRect (0,0,0,0),
						this,
						ID_SLIDERIGHT);

// Create the slide left button
	m_pSlideLeft.Create	 (_T(""),
						WS_CHILD |
						WS_VISIBLE,
						CRect (0,0,0,0),
						this,
						ID_SLIDELEFT);

// Create the bold button
	m_pBold.Create	 (_T(""),
						WS_CHILD |
						WS_VISIBLE,
						CRect (0,0,0,0),
						this,
						ID_BOLD);	

// Create the italic button
	m_pItalic.Create	 (_T(""),
						WS_CHILD |
						WS_VISIBLE,
						CRect (0,0,0,0),
						this,
						ID_ITALIC);

// Create the underline button
	m_pUnderline.Create	 (_T(""),
						WS_CHILD |
						WS_VISIBLE,
						CRect (0,0,0,0),
						this,
						ID_UNDERLINE);

// Creazte the strikeout button
	m_pStrikeOut.Create	 (_T(""),
						 WS_CHILD |
						 WS_VISIBLE,
						 CRect (0,0,0,0),
						 this,
						 ID_STRIKEOUT);

// Should it stay on top or not
	if (theApp.m_bStayOnTop)
		SetWindowPos( &wndTopMost,   0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	else
		SetWindowPos( &wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	SetBorderStyle (theApp.m_bThinNoteBorder);

	m_pText.SetFocus ();

	return FALSE;	            
}

BOOL CNote::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	
}

void CNote::OnPaint() 
{
	CPaintDC dc(this);

	CDC *pDC;
	pDC = GetDC ();
	if (theApp.m_bThinNoteBorder)
		PaintThinBorder (pDC);
	else
		PaintThickBorder (pDC);

// Write the title's text
// Note that we have to check if the title won't fit to the left of the buttons
// If the text doesn't fit -> End the title with ... in the right place
	if (!m_pPosition.GetSlidedToLeft () && !m_pPosition.GetSlidedToRight ())	{
		int iStart;
		CFont font;
		CFont * pFont;
		font.CreateFont(-12,0,0,0,FW_NORMAL,FALSE,FALSE,0,theApp.m_iCharset,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,_T("Arial"));
		pFont = pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor (GetNoteColor ());
	// Be sure that the text isn't too long, if so -> terminate the text with ...
		CSize Size;
		CString szTitle;
		szTitle = GetTitle ();
		Size = pDC->GetTextExtent(szTitle, szTitle.GetLength ());
		if (Size.cx > m_iTitleMaxWidth)	{
			while (Size.cx >= m_iTitleMaxWidth)	{

			// Is this the first time?
				if (szTitle.Right (3) != _T("..."))	{
					if (szTitle.GetLength () >= 3)	{
						szTitle = szTitle.Left (szTitle.GetLength () - 3);
						szTitle += _T("...");
					}
					else	{
						szTitle = _T("...");
					}
				}
				else	{
					if (szTitle.GetLength () >=4)	{
						szTitle = szTitle.Left (szTitle.GetLength () - 4);
						szTitle += _T("...");
					}
					else	{
						szTitle = _T("...");
					}
				}

				if (szTitle == _T("..."))
					break;

			// Get the new length (in pixels)
				Size = pDC->GetTextExtent(szTitle, szTitle.GetLength ());
			}
		}

	// Where should the text start
		iStart = m_bUseAlarm ? 22 : 5;
#if (defined (UNICODE) || defined (_UNICODE))
		TextOutW( pDC->GetSafeHdc(), iStart, 5, szTitle, szTitle.GetLength ());
#else
		pDC->TextOut(iStart, 5, szTitle, szTitle.GetLength ());
#endif
	}

	if (m_pPosition.GetSlidedToLeft ())	{
		CFont font;
		CFont * pFont;
		font.CreateFont(-12,0,900,0,FW_NORMAL,FALSE,FALSE,0,theApp.m_iCharset,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,_T("Arial"));
		pFont = pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor (GetNoteColor ());
		CSize Size;
		Size = pDC->GetTextExtent(GetTitle (), GetTitle ().GetLength ());
#if (defined (UNICODE) || defined (_UNICODE))
		TextOutW( pDC->GetSafeHdc(), 5, m_pPosition.GetNotePosition ().bottom - ((m_pPosition.GetNotePosition ().bottom - Size.cx) / 2), GetTitle (), GetTitle ().GetLength ());
#else
		pDC->TextOut(5, m_pPosition.GetNotePosition ().bottom - ((m_pPosition.GetNotePosition ().bottom - Size.cx) / 2), GetTitle (), GetTitle ().GetLength ());
#endif
	}

	if (m_pPosition.GetSlidedToRight ())	{
		CFont font;
		CFont * pFont;
		font.CreateFont(-12,0,900,0,FW_NORMAL,FALSE,FALSE,0,theApp.m_iCharset,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,_T("Arial"));
		pFont = pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor (GetNoteColor ());
		CSize Size;
		Size = pDC->GetTextExtent(GetTitle (),GetTitle ().GetLength ());
#if (defined (UNICODE) || defined (_UNICODE))
		TextOutW( pDC->GetSafeHdc(),5,m_pPosition.GetNotePosition ().bottom - ((m_pPosition.GetNotePosition ().bottom - Size.cx) / 2),GetTitle (), GetTitle ().GetLength ());
#else
		pDC->TextOut(5,m_pPosition.GetNotePosition ().bottom - ((m_pPosition.GetNotePosition ().bottom - Size.cx) / 2),GetTitle (), GetTitle ().GetLength ());
#endif
	}

	m_pMinimize.Invalidate		(FALSE);
	m_pClose.Invalidate			(FALSE);
	m_pText.Invalidate			(FALSE);
	m_pSlideRight.Invalidate	(FALSE);
	m_pSlideLeft.Invalidate		(FALSE);
	m_pBullet.Invalidate		(FALSE);
	m_pStrikeOut.Invalidate		(FALSE);
	m_pItalic.Invalidate		(FALSE);
	m_pUnderline.Invalidate		(FALSE);
	m_pBold.Invalidate			(FALSE);
}



void CNote::OnDestroy() 
{
	CDialog::OnDestroy();
	
// To avoid memory leakage
	delete this;	
}

UINT CNote::OnNcHitTest(CPoint point) 
{
	CRect rc;
	ScreenToClient (&point);
	GetClientRect (&rc);


// Minimized -> caption
	if (!m_pPosition.GetSlidedToLeft () && !m_pPosition.GetSlidedToRight () && !m_bVisible && theApp.m_bMinimizeShrink && (point.y < 25 && point.y >= 3 && point.x > 3 && point.x < rc.right - 3))
		return HTCAPTION;
	else if (!m_pPosition.GetSlidedToLeft () && !m_pPosition.GetSlidedToRight () && !m_bVisible && theApp.m_bMinimizeShrink)
		return 0;

// Caption (when not slided
	if (!m_pPosition.GetSlidedToLeft () && !m_pPosition.GetSlidedToRight () && point.y < 25 && point.y >= 3 && point.x > 3 && point.x < rc.right - 3)
		return	HTCAPTION;

// Caption when slided
	if (m_pPosition.GetSlidedToLeft () || m_pPosition.GetSlidedToRight ())
		return	HTCLIENT;

// Top
	if (point.x > 20 && point.x < rc.right - 20 && point.y < 3)
		return HTTOP;

// Left
	if (point.y >= 20 && point.y < rc.bottom - 20 && point.x < 3)
		return HTLEFT;

// Bottom
	if (point.y > rc.bottom - 3 && point.x > 20 && point.x < rc.right - 20)
		return HTBOTTOM;

// Right
	if (point.y >= 25 && point.y < rc.bottom - 20 && point.x > rc.right - 3)
		return HTRIGHT;

// Upper left
	if (point.x < 20 && point.y < 20)
		return HTTOPLEFT;

// Upper right
	if (point.x > rc.right - 20 && point.y < 20)
		return HTTOPRIGHT;

// Lower left
	if (point.x < 20 && point.y > rc.bottom - 20)
		return HTBOTTOMLEFT;

// Lower right
	if (point.x > rc.right - 20 && point.y > rc.bottom - 20)
		return HTBOTTOMRIGHT;
	
	return HTCLIENT;
}

void CNote::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	ShowButtons ();

// Save the windows state
	if (!m_pPosition.GetSlidedToLeft () && !m_pPosition.GetSlidedToRight ())	{
		CRect cRect;
		cRect = m_pPosition.GetNotePosition ();
		cRect.right = cx;
		cRect.bottom = cy;
		m_pPosition.SetNotePosition (cRect, this, TRUE);
	}


	if (m_pText.GetSafeHwnd ())	
		m_pText.MoveWindow (5, 25, cx - 12, cy - 35);


	Invalidate (FALSE);
}



void CNote::Initialize()
{
// Initialize the note

	CRect r, r1;
	r1 = m_pPosition.GetNotePosition ();
	r = m_pPosition.GetSlidedNotePosition ();
	m_pText.SetRTF	(m_szText);
	m_pPosition.SetSlidedNotePosition (r, this, FALSE);
	m_pPosition.SetNotePosition (r1, this, FALSE);

// Make sure that the note is within the monitor
	m_pPosition.FixNotePosition (this);

// Is it slided to the left
	if (m_pPosition.GetSlidedToLeft ())	{
		m_pText.ShowWindow  (SW_HIDE);
		HideButtons ();
	}

// Is it slided to the right
	if (m_pPosition.GetSlidedToRight ())	{
		m_pText.ShowWindow  (SW_HIDE);
		HideButtons ();
	}

	m_bVisible ? m_bVisible = FALSE : m_bVisible = TRUE;
	m_iOldHeight = m_pPosition.GetNotePosition ().bottom;
	OnMinimize ();


	if (theApp.m_bMinimizeShrink)
		ShowWindow (SW_SHOW);

	if (m_bUseAlarm && (!m_pPosition.GetSlidedToLeft () && !m_pPosition.GetSlidedToRight ()))
		m_pAlarm.ShowWindow (SW_SHOW);

	SetBorderStyle (theApp.m_bThinNoteBorder);

	Invalidate ();
}


void CNote::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
}

void CNote::OnCloseNote ()
{
// Remove the note
	if (theApp.m_bShowDeleteMessage)	{
		CDlgDeleteInformation dlg;
		dlg.DoModal ();

		AfxGetApp ()->WriteProfileInt ( _T("Settings\\Options"), _T("Show Delete Message"), dlg.m_bShowAgain);
		theApp.m_bShowDeleteMessage = dlg.m_bShowAgain;
	}

// See if the user wants to delete it without saving it in deleted notes.xml
	bool bShift = (GetKeyState(VK_SHIFT) & 0x8000) ? true : false;	

	if (theApp.m_bWarnOnDelete && !m_bBelongsToRecycleBin)	{
		if (MessageBox (CTranslate::ReadString (183, _T("Do you want to delete the note?")), _T("A Note"), MB_ICONEXCLAMATION | MB_YESNO) == IDNO)
			return;
	}

	CMainFrame *pMain = (CMainFrame*) ::AfxGetMainWnd ();
	pMain->DeleteNote (this, !bShift);

	OnOK ();
}

 
void CNote::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	BCMenu menu;
	menu.LoadMenu(IDR_POPUPMENU);
	menu.LoadToolbar(IDR_MENUBAR);
	BCMenu *psub = (BCMenu *)menu.GetSubMenu(0);

	psub->SetMenuText (ID_POPUPMENU_CUT,		CTranslate::ReadString (27, _T("Cut")),				MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_COPY, 		CTranslate::ReadString (28, _T("Copy")),			MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_PASTE,	 	CTranslate::ReadString (29, _T("Paste")),			MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_FONT, 		CTranslate::ReadString (30, _T("Font...")),			MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_NOTECOLOR, 	CTranslate::ReadString (31, _T("Note color...")),	MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_SETTITLE, 	CTranslate::ReadString (32, _T("Set title...")),	MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_ALARM,	 	CTranslate::ReadString (33, _T("Alarm...")),		MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_EMAIL, 		CTranslate::ReadString (34, _T("Email...")),		MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_PRINT, 		CTranslate::ReadString (35, _T("Print...")),		MF_STRING);
	
	psub->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	menu.DestroyMenu();
}

void CNote::OnPopupmenuCut() 
{
	m_pText.Cut ();
}

void CNote::OnPopupmenuCopy() 
{
	m_pText.Copy ();	
}

void CNote::OnPopupmenuPaste() 
{
	m_pText.Paste ();
}

void CNote::OnPopupmenuNotecolor() 
{
// Change the note color
	CColorDialog dlg (m_cfNoteColor);

	if (dlg.DoModal () == IDOK)	{
		m_cfNoteColor = dlg.GetColor ();
		SetBorderStyle (theApp.m_bThinNoteBorder);
		Invalidate (FALSE);
	}
}

void CNote::OnMinimize ()
{
// Minimize the note or restore it
	if (theApp.m_bMinimizeShrink)	{
		if (m_bVisible)	{
			CRect rc;
			SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);
			if (m_pPosition.GetDockedBottom ())	{
				CRect cRect;
				cRect = m_pPosition.GetNotePosition ();
				cRect.top = rc.bottom - 23;
				m_pPosition.SetNotePosition (cRect, this, FALSE);

			// Move the cursor to the minimize-button
				if (theApp.m_bMinimizeMoveCursor)	{
					CRect rect;
					m_pMinimize.GetWindowRect (rect);
					SetCursorPos (rect.left + 8, m_pPosition.GetNotePosition ().top + 10);
				}
			}
			m_iOldHeight = m_pPosition.GetNotePosition ().bottom;
			MoveWindow (m_pPosition.GetNotePosition ().left, m_pPosition.GetNotePosition ().top, m_pPosition.GetNotePosition ().right, 23);
			if (theApp.m_bThinNoteBorder)
				m_pMinimize.SetBitmaps (IDB_NOTEMINIMIZE2, RGB (100,100,100), IDB_NOTEMINIMIZE2, RGB (100,100,100));
			else
				m_pMinimize.SetBitmaps (IDB_NOTEMINIMIZE3, RGB (100,100,100), IDB_NOTEMINIMIZE3, RGB (100,100,100));
			m_bVisible = FALSE;
			SetTransparancy (theApp.m_iTransparantNormal, theApp.m_iTransparantMinimized);
		}
		else	{	
			RestoreNote ();		
			SetTransparancy (theApp.m_iTransparantNormal, theApp.m_iTransparantMinimized);
		}
	}
	else	{
		if (m_bVisible)	{
			m_bVisible = FALSE;

			SetTransparancy (theApp.m_iTransparantNormal, theApp.m_iTransparantMinimized);

		// Added by Leonardo Zide (lmz) -----
			MoveWindow (m_pPosition.GetNotePosition ().left, m_pPosition.GetNotePosition ().top, m_pPosition.GetNotePosition ().right, m_pPosition.GetNotePosition ().bottom);
		// ----------------------------------
			ShowWindow (SW_HIDE);
		}
		else
			RestoreNote ();
	}

}

void CNote::RestoreNote()
{
// Show it again
	if (theApp.m_bMinimizeShrink)	{
		m_bVisible = TRUE;
		CRect rc;
		SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);

		SetTransparancy (theApp.m_iTransparantNormal, theApp.m_iTransparantMinimized);

		if (rc.bottom < (m_pPosition.GetNotePosition ().top + m_iOldHeight))	{
			CRect cRect;
			cRect = m_pPosition.GetNotePosition ();
			cRect.top = rc.bottom - m_iOldHeight;
			m_pPosition.SetNotePosition (cRect, this, FALSE);
			m_pPosition.SetDockedBottom (TRUE, this, TRUE);
		}
		MoveWindow (m_pPosition.GetNotePosition ().left, m_pPosition.GetNotePosition ().top, m_pPosition.GetNotePosition ().right, m_iOldHeight);

	// Move the cursor to the minimize-button
		if (theApp.m_bMinimizeMoveCursor)	{
			CRect rect;
			m_pMinimize.GetWindowRect (rect);
			SetCursorPos (rect.left + 8, m_pPosition.GetNotePosition ().top + 10);
		}

// Changed by Leonardo Zide (lmz) -----
	}
	else	{
		m_bVisible = TRUE;

		SetTransparancy (theApp.m_iTransparantNormal, theApp.m_iTransparantMinimized);
		ShowWindow (SW_SHOW);
	}
	
	if (theApp.m_bThinNoteBorder)
		m_pMinimize.SetBitmaps (IDB_NOTEMINIMIZE1, RGB (100,100,100), IDB_NOTEMINIMIZE1, RGB (100,100,100));
	else
		m_pMinimize.SetBitmaps (IDB_NOTEMINIMIZE, RGB (100,100,100), IDB_NOTEMINIMIZE, RGB (100,100,100));
// ------------------------------------
}

void CNote::OnPopupmenuFont() 
{
// Change the font
	CFontDialog dlg (m_pText.GetCharFormat ());	

	if (dlg.DoModal () == IDOK)	{
		CHARFORMAT cf;
		dlg.GetCharFormat (cf);
		m_pText.SetSelectionCharFormat (cf);
	}
}


void CNote::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
// Double click on the title -> either set it or restore the window
	if (theApp.m_bDoubleClickOnTitleBar){
		OnMinimize ();
	}
	else	{
		CDlgSetTitle dlg;
		CPoint pnt = point;
		ScreenToClient (&pnt);
	
		if (pnt.y < 30)	{
			dlg.m_szTitle = m_szTitle;
			if (dlg.DoModal () == IDOK)	{
				m_szTitle = dlg.m_szTitle;
				Invalidate ();
			}
		}
	}
	
	CDialog::OnNcLButtonDblClk(nHitTest, point);
}

void CNote::OnPopupmenuAlarm() 
{
// Change the alarm
	CRect rc;
	GetClientRect (&rc);
	CDlgSetAlarm dlg;
	COleDateTime tid;
	dlg.m_bUseAlarm	= m_bUseAlarm;
	dlg.m_Time		= m_Alarm;

	if (dlg.DoModal () == IDOK)	{

		m_bUseAlarm		= dlg.m_bUseAlarm;
		m_Alarm			= dlg.m_Time;

		if (m_bUseAlarm)	{
			if (theApp.m_bThinNoteBorder)
				m_pAlarm.SetBitmaps (IDB_NOTEALARM1, RGB (100,100,100), IDB_NOTEALARM1, RGB (100,100,100));
			else
				m_pAlarm.SetBitmaps (IDB_NOTEALARM, RGB (100,100,100), IDB_NOTEALARM, RGB (100,100,100));

			ShowButtons ();
		}
		else	{
			m_bUseAlarm = FALSE;
			ShowButtons ();
			m_pAlarm.ShowWindow (SW_HIDE);
			CloseAlarm ();
		}
	}
}


void CNote::OnAlarm ()
{
// Snooze or something and close the sound
	CDlgSnooze dlg;

	if (m_bIsAlarmShouting)	{
		if (dlg.DoModal () == IDOK)	{

		// Snooze -> Set the alarm 10 minutes forward from now
			COleDateTime t1 = COleDateTime::GetCurrentTime () ;
			COleDateTime t2; t2.SetTime (0, 10, 0);
			m_Alarm = t1 + t2;

			CloseAlarm ();
			m_bUseAlarm = TRUE;
		}
		else	{

		// Turn off
			CRect rc;
			GetClientRect (&rc);
			CloseAlarm ();
			m_bUseAlarm = FALSE;
			m_pAlarm.ShowWindow (SW_HIDE);
			Invalidate ();
		}
	}
	else	{ // The alarm is not shouting -> show the alarm dialog
		OnPopupmenuAlarm ();
	}
}

void CNote::OnBullet ()
{
// The user pressed the bullet button
	m_pText.SetParagraphBulleted ();
}

void CNote::OnItalic ()
{
// The user pressed the italic button
	m_pText.SetSelectionItalic ();
}

void CNote::OnBold ()
{
// The user pressed the bold button
	m_pText.SetSelectionBold ();
}

void CNote::OnUnderline ()
{
// The user pressed the underline button
	m_pText.SetSelectionUnderlined ();
}

void CNote::OnPopupmenuSettitle() 
{
// Set the title
	CDlgSetTitle dlg;
	dlg.m_szTitle = m_szTitle;

	if (dlg.DoModal () == IDOK)	{
		m_szTitle = dlg.m_szTitle;
		Invalidate ();
	}
}


void CNote::ShowAlarm()
{
	CMainFrame *pMain = (CMainFrame*) ::AfxGetMainWnd ();

// The alarm will be "played"
	if (theApp.m_bPlayAlarmSound && !theApp.m_szAlarmSoundFile.IsEmpty ())
		PlaySound (theApp.m_szAlarmSoundFile, AfxGetInstanceHandle(), SND_FILENAME | SND_ASYNC);

// Change the tray icon
	pMain->AnimateTrayAlarm ();

// Set the window to top
	SetWindowPos (&wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

// Start to blink
	SetTimer (ID_NOTEBLINK, 1000, (TIMERPROC) NULL);

// Show that the alarm is shouting
	m_bIsAlarmShouting = TRUE;
}



void CNote::CloseAlarm()
{
	CMainFrame *pMain = (CMainFrame*) ::AfxGetMainWnd ();

// Close the alarm and reset everything
	PlaySound (NULL, AfxGetInstanceHandle (),  SND_RESOURCE | SND_ASYNC);
	KillTimer (ID_NOTEBLINK);
	ShowWindow (SW_SHOW);
	pMain->NoAnimate ();
	m_bIsAlarmShouting = FALSE;

}

void CNote::SetTransparancy(int iNormal, int iMinimized)
{
// Set the trasparency (only Win2K and XP)
	if (m_bVisible && ! (m_pPosition.GetSlidedToLeft () || m_pPosition.GetSlidedToRight ()))
		theApp.m_Layered.SetTransparentPercentage(m_hWnd, iNormal);
	else
		theApp.m_Layered.SetTransparentPercentage(m_hWnd, iMinimized);
}

void CNote::StayOnTop()
{
// Stay on top
	SetWindowPos( &wndTopMost,   0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void CNote::StayNotOnTop()
{
// Stay not on top
	SetWindowPos( &wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}


void CNote::OnTextLink(NMHDR* pNMHDR, LRESULT* pResult) 
{
// Open the url that the user pressed on
	ENLINK* pENLink = ( ENLINK* )pNMHDR;

	*pResult = 0 ;

	switch( pENLink->msg ) {

	case WM_LBUTTONDOWN:  {
		CString szURL;
		CHARRANGE saveRange;
        saveRange.cpMin = 0;
        saveRange.cpMax = 0;
		m_pText.GetSel( saveRange ) ;
		m_pText.SetSel( pENLink->chrg ) ;
		szURL = m_pText.GetSelText() ;
		m_pText.SetSel( saveRange ) ;

		CWaitCursor wait;
        szURL.TrimLeft();

        if (!szURL.IsEmpty()) 
			ShellExecute( GetParent()->GetSafeHwnd(), _T("open" ), szURL, NULL, NULL, SW_SHOWNORMAL ) ;
        else
			*pResult = 0;
            
		*pResult = 1;
	}
	break;

	case WM_LBUTTONUP:  {
	   *pResult = 1 ;
	}
		break ;
	}
}

void CNote::PaintThickBorder(CDC *pDC)
{
// Create pens and brushes
	CRect rc;
	GetClientRect (&rc);

	CPen lightpen;
	CPen darkpen;
	CPen blackpen;
	CPen darkestpen;
	CBrush notebrush;
	CBrush borderbrush;

	lightpen.CreatePen	(PS_SOLID, 1, RGB (195, 195, 195));
	darkpen.CreatePen	(PS_SOLID, 1, RGB (130, 130, 130));
	darkestpen.CreatePen (PS_SOLID, 1, RGB (80, 80, 80));
	blackpen.CreatePen	(PS_SOLID, 1, RGB (0,	0,	 0));

	notebrush.CreateSolidBrush	 (m_cfNoteColor);
	borderbrush.CreateSolidBrush (RGB (130, 130, 130));


// Create a bitmap in memory -> avoid flicker
	CDC pMemDC;
	pMemDC.CreateCompatibleDC (pDC);
	HBITMAP hBitmap;
	hBitmap = CreateCompatibleBitmap (pDC->m_hDC, rc.right, rc.bottom);
	HBITMAP pOldBmp = (HBITMAP) pMemDC.SelectObject (hBitmap);

// Paint the note
	pMemDC.SelectObject (notebrush);
	pMemDC.Rectangle (&rc);

	HGDIOBJ pOldPen = (HGDIOBJ) pMemDC.SelectObject (darkpen);
	pMemDC.MoveTo (0, rc.bottom - 2);	pMemDC.LineTo (0, 0);
	pMemDC.MoveTo (0, 0);				pMemDC.LineTo (rc.right, 0);
	pMemDC.MoveTo (2, rc.bottom - 3);	pMemDC.LineTo (2, 1);
	pMemDC.MoveTo (3, rc.bottom - 3);	pMemDC.LineTo (3, 1);
	pMemDC.MoveTo (2, rc.bottom - 3);	pMemDC.LineTo (rc.right - 2, rc.bottom - 3);
	pMemDC.MoveTo (2, rc.bottom - 4);	pMemDC.LineTo (rc.right - 2, rc.bottom - 4);

	if (!m_pPosition.GetSlidedToRight () && m_pPosition.GetSlidedToLeft ())	{
		pMemDC.MoveTo (rc.right - 4, rc.bottom - 4);	pMemDC.LineTo (rc.right - 4, 1);
		pMemDC.MoveTo (rc.right - 3, rc.bottom - 4);	pMemDC.LineTo (rc.right - 3, 1);
		pMemDC.MoveTo (rc.right - 5, rc.bottom - 5);	pMemDC.LineTo (rc.right - 4, rc.bottom - 4);
		pMemDC.MoveTo (rc.right - 9, rc.bottom - 5);	pMemDC.LineTo (rc.right - 4, rc.bottom - 10);
		pMemDC.MoveTo (rc.right - 13, rc.bottom - 5);	pMemDC.LineTo (rc.right - 4, rc.bottom - 14);
	}

	HGDIOBJ pOldBrush = (HGDIOBJ) pMemDC.SelectObject (borderbrush);

	if (m_pPosition.GetSlidedToRight () || m_pPosition.GetSlidedToLeft ())
		pMemDC.Rectangle (2, 2, rc.right - 1, 3);
	else
		pMemDC.Rectangle (2, 2, rc.right - 1, 22);

	if (!m_pPosition.GetSlidedToRight () && !m_pPosition.GetSlidedToLeft ())	{
		pMemDC.SelectObject (lightpen);
		pMemDC.MoveTo (1, rc.bottom	- 2);	pMemDC.LineTo (1,1);
		pMemDC.MoveTo (1,1);				pMemDC.LineTo (rc.right- 2, 1);
		pMemDC.MoveTo (rc.right - 8, rc.bottom - 5);	pMemDC.LineTo (rc.right - 4, rc.bottom - 9);
		pMemDC.MoveTo (rc.right - 12, rc.bottom - 5);	pMemDC.LineTo (rc.right - 4, rc.bottom - 13);

		pMemDC.SelectObject (blackpen);
		pMemDC.MoveTo (1, rc.bottom);		pMemDC.LineTo (rc.right, rc.bottom);	pMemDC.LineTo (rc.right, 0);
		pMemDC.MoveTo (rc.right - 6, rc.bottom - 5);	pMemDC.LineTo (rc.right - 4, rc.bottom - 7);
		pMemDC.MoveTo (rc.right - 7, rc.bottom - 5);	pMemDC.LineTo (rc.right - 4, rc.bottom - 8);
		pMemDC.MoveTo (rc.right - 10, rc.bottom - 5);	pMemDC.LineTo (rc.right - 4, rc.bottom - 11);
		pMemDC.MoveTo (rc.right - 11, rc.bottom - 5);	pMemDC.LineTo (rc.right - 4, rc.bottom - 12);
	}

	pMemDC.SelectObject (darkestpen);
	pMemDC.MoveTo (1, rc.bottom -2);	pMemDC.LineTo (rc.right - 2, rc.bottom - 2);pMemDC.LineTo (rc.right - 2, 0);

// BitBlt the in memory bitmap
	pDC->BitBlt (0, 0, rc.right, rc.bottom, &pMemDC, 0, 0, SRCCOPY);


// Clean up
	pMemDC.SelectObject			(pOldPen);
	pMemDC.SelectObject			(pOldBrush);
	pMemDC.SelectObject			(pOldBmp);
	DeleteObject				(hBitmap);
	lightpen.DeleteObject		();
	darkpen.DeleteObject		();
	blackpen.DeleteObject		();
	darkestpen.DeleteObject		();
	notebrush.DeleteObject		();
	borderbrush.DeleteObject	();
}

void CNote::PaintThinBorder(CDC *pDC)
{
// Create pens and brushes
	CRect rc;
	GetClientRect (&rc);

	CPen blackpen;
	CBrush notebrush;

	blackpen.CreatePen	(PS_SOLID, 1, RGB (0,	0,	 0));
	notebrush.CreateSolidBrush	 (m_cfNoteColor);


// Create a bitmap in memory -> avoid flicker
	CDC pMemDC;
	pMemDC.CreateCompatibleDC (pDC);
	HBITMAP hBitmap;
	hBitmap = CreateCompatibleBitmap (pDC->m_hDC, rc.right, rc.bottom);
	HBITMAP pOldBmp = (HBITMAP) pMemDC.SelectObject (hBitmap);

// Paint the note
	HGDIOBJ pOldPen = (HGDIOBJ) pMemDC.SelectObject (blackpen);
	HGDIOBJ pOldBrush = (HGDIOBJ) pMemDC.SelectObject (notebrush);

	pMemDC.SelectObject (notebrush);
	pMemDC.Rectangle (&rc);

	if (!m_pPosition.GetSlidedToRight () && !m_pPosition.GetSlidedToLeft ())	{
		pMemDC.MoveTo (3, 22);
		pMemDC.LineTo (rc.right - 3, 22);
	}

// BitBlt the in memory bitmap
	pDC->BitBlt (0, 0, rc.right, rc.bottom, &pMemDC, 0, 0, SRCCOPY);


// Clean up
	pMemDC.SelectObject			(pOldPen);
	pMemDC.SelectObject			(pOldBrush);
	pMemDC.SelectObject			(pOldBmp);
	DeleteObject				(hBitmap);
	blackpen.DeleteObject		();
	notebrush.DeleteObject		();
}


void CNote::SetButtonColor(COLORREF cfColor)
{
	for (int i = 0; i < 6; i++)	{
		m_pClose.SetColor		(i, cfColor, TRUE);
		m_pMinimize.SetColor	(i, cfColor, TRUE);
		m_pAlarm.SetColor		(i, cfColor, TRUE);
		m_pBullet.SetColor		(i, cfColor, TRUE);
		m_pSlideRight.SetColor	(i, cfColor, TRUE);
		m_pSlideLeft.SetColor	(i, cfColor, TRUE);
		m_pBold.SetColor		(i, cfColor, TRUE);
		m_pUnderline.SetColor	(i, cfColor, TRUE);
		m_pItalic.SetColor		(i, cfColor, TRUE);
		m_pStrikeOut.SetColor	(i, cfColor, TRUE);
	}
}

void CNote::SetBorderStyle(BOOL bThin)
{
// Set if the border should be thin or thick
	if (bThin)	{
		SetButtonColor (m_cfNoteColor);
		if (m_bVisible)
			m_pMinimize.SetBitmaps (IDB_NOTEMINIMIZE1, RGB (100,100,100), IDB_NOTEMINIMIZE1, RGB (100,100,100));
		else
			m_pMinimize.SetBitmaps (IDB_NOTEMINIMIZE2, RGB (100,100,100), IDB_NOTEMINIMIZE2, RGB (100,100,100));
		if (m_bUseAlarm)
			m_pAlarm.SetBitmaps (IDB_NOTEALARM1, RGB (100,100,100), IDB_NOTEALARM1, RGB (100,100,100));
		m_pBullet.SetBitmaps (IDB_NOTEBULLET1, RGB (100,100,100), IDB_NOTEBULLET1, RGB (100,100,100));
		m_pClose.SetBitmaps (IDB_NOTECLOSE1, RGB (100,100,100), IDB_NOTECLOSE1, RGB (100,100,100));
		m_pSlideRight.SetBitmaps (IDB_SLIDERIGHT1, RGB (100,100,100), IDB_SLIDERIGHT1, RGB (100,100,100));
		m_pSlideLeft.SetBitmaps (IDB_SLIDELEFT1, RGB (100,100,100), IDB_SLIDELEFT1, RGB (100,100,100)); 
		m_pBold.SetBitmaps (IDB_BOLD1, RGB (100,100,100), IDB_BOLD1, RGB (100,100,100));
		m_pUnderline.SetBitmaps (IDB_UNDERLINE1, RGB (100,100,100), IDB_UNDERLINE1, RGB (100,100,100));
		m_pStrikeOut.SetBitmaps (IDB_STRIKEOUT1, RGB (100,100,100), IDB_STRIKEOUT1, RGB (100,100,100));
		m_pItalic.SetBitmaps (IDB_ITALIC1, RGB (100,100,100), IDB_ITALIC1, RGB (100,100,100));
		m_pText.SetBackgroundColor (FALSE, m_cfNoteColor);
		Invalidate ();
	}
	else	{
		SetButtonColor (RGB (130, 130, 130));
		m_pBullet.SetBitmaps (IDB_NOTEBULLET, RGB (100,100,100), IDB_NOTEBULLET, RGB (100,100,100));
		m_pClose.SetBitmaps (IDB_NOTECLOSE, RGB (100,100,100), IDB_NOTECLOSE, RGB (100,100,100));
		m_pSlideRight.SetBitmaps (IDB_SLIDERIGHT, RGB (100,100,100), IDB_SLIDERIGHT, RGB (100,100,100));
		m_pSlideLeft.SetBitmaps (IDB_SLIDELEFT, RGB (100,100,100), IDB_SLIDELEFT, RGB (100,100,100)); 
		m_pUnderline.SetBitmaps (IDB_UNDERLINE, RGB (100,100,100), IDB_UNDERLINE, RGB (100,100,100));
		m_pStrikeOut.SetBitmaps (IDB_STRIKEOUT, RGB (100,100,100), IDB_STRIKEOUT, RGB (100,100,100));
		m_pItalic.SetBitmaps (IDB_ITALIC, RGB (100,100,100), IDB_ITALIC, RGB (100,100,100));
		if (m_bVisible)
			m_pMinimize.SetBitmaps (IDB_NOTEMINIMIZE, RGB (100,100,100), IDB_NOTEMINIMIZE, RGB (100,100,100));
		else
			m_pMinimize.SetBitmaps (IDB_NOTEMINIMIZE3, RGB (100,100,100), IDB_NOTEMINIMIZE3, RGB (100,100,100));
		m_pAlarm.SetBitmaps (IDB_NOTEALARM, RGB (100,100,100), IDB_NOTEALARM, RGB (100,100,100));
		m_pText.SetBackgroundColor (FALSE, m_cfNoteColor);
		Invalidate ();
	}

}


CRect CNote::GetPosition()
{
	if (m_bVisible)
		return m_pPosition.GetNotePosition ();
	else
		return CRect (m_pPosition.GetNotePosition ().left, m_pPosition.GetNotePosition ().top, m_pPosition.GetNotePosition ().right, m_iOldHeight);
}

CRect CNote::GetSlidePosition ()
{
	return CRect (m_pPosition.GetSlidedNotePosition ().left, m_pPosition.GetSlidedNotePosition ().top, m_pPosition.GetSlidedNotePosition ().right, m_pPosition.GetSlidedNotePosition ().bottom);
}

void CNote::OnPopupmenuEmail() 
{
// Send the note as email
	CWaitCursor wc;

//Create the message
	CMapiMessage message;

//Setup the all the recipient types for this message
	message.AddMultipleRecipients(_T("to@someone.com"), CMapiMessage::TO);

//Add the Subject and Body
	CString szText;
	m_pText.GetWindowText (szText);
	message.m_sBody = szText;
	message.m_sSubject = m_szTitle;

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


BOOL CNote::PreTranslateMessage(MSG* pMsg) 
{
	if((pMsg->message == WM_KEYDOWN) && (GetKeyState(VK_CONTROL) & 0x8000))	{
		switch(pMsg->wParam)	{

		case 0x42: //Ctrl-B
			m_pText.SetSelectionBold ();
			break;

		case 0x49:  //Ctrl-I
			m_pText.SetSelectionItalic ();
			pMsg->wParam = WM_NULL; // To avoid that Ctrl+I becomes a tab
			break;

		case 0x55:  //Ctrl-U
			m_pText.SetSelectionUnderlined ();
			break;

		case 0x50:  // Ctrl-P
			OnPopupmenuPrint ();
			break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CNote::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == ID_NOTEBLINK && theApp.m_bBlinkNote)	{

		static bool bShow = TRUE;

		ShowWindow (bShow ? SW_SHOW : SW_HIDE);

		bShow ? bShow = FALSE: bShow = TRUE;
	}



	CDialog::OnTimer(nIDEvent);
}


void CNote::OnRequestResize( NMHDR* pNMHDR, LRESULT* pResult )
{
	_ASSERT( pNMHDR->code == EN_REQUESTRESIZE );


// Storing the requested sized to be used in the binary search
	REQRESIZE* prr = (REQRESIZE*)pNMHDR;

	CRect rect;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rect, 0);

	if (m_pPosition.GetSlidedToLeft () || m_pPosition.GetSlidedToRight ())	{
		*pResult = 0;
		return;
	}

	if (m_pPosition.GetDockedBottom ())	{
		CRect cRect;
		cRect = m_pPosition.GetNotePosition ();
		cRect.top = rect.bottom - (prr->rc.bottom + 10);
		m_pPosition.SetNotePosition (cRect, this, TRUE);
	}

	if (m_bVisible)
		MoveWindow (m_pPosition.GetNotePosition ().left, m_pPosition.GetNotePosition ().top, m_pPosition.GetNotePosition ().right, prr->rc.bottom + 10);

	*pResult = 0;
}

void CNote::OnMoving(UINT fwSide, LPRECT pRect) 
{
	CPoint pnt;
	CRect rc, rect, cRect;

	cRect = m_pPosition.GetNotePosition ();
	cRect.left = pRect->left;
	cRect.top = pRect->top;
	m_pPosition.SetNotePosition (cRect, this, TRUE);

// If we have slided the note we don't want it to change it's height here
	if (m_pPosition.GetSlidedToLeft () || m_pPosition.GetSlidedToRight ())
		return;

// See if we should dock the window
	if (theApp.m_bDockable)	{

	// Where are we?
		GetCursorPos (&pnt);
		GetClientRect (&rc);
		SystemParametersInfo (SPI_GETWORKAREA , 0, &rect, 0);

	// Is it docked from serialization?
		if (m_pPosition.GetDockedPoint ().x == 0 && m_pPosition.GetDockedPoint ().y == 0)	{

			if (m_pPosition.GetDockedLeft ())		m_pPosition.SetDockedPoint (CPoint (pnt.x, m_pPosition.GetDockedPoint ().y));
			if (m_pPosition.GetDockedTop ())		m_pPosition.SetDockedPoint (CPoint (m_pPosition.GetDockedPoint ().x, pnt.y));
			if (m_pPosition.GetDockedRight ())		m_pPosition.SetDockedPoint (CPoint (pnt.x, m_pPosition.GetDockedPoint ().y));
			if (m_pPosition.GetDockedBottom ())		m_pPosition.SetDockedPoint (CPoint (m_pPosition.GetDockedPoint ().x, pnt.y));
		}

	// Left
		if (m_pPosition.GetDockedLeft ())	{
			if (pnt.x > m_pPosition.GetDockedPoint ().x + 3)	{
				m_pPosition.SetDockedLeft (FALSE, this, FALSE);
				pRect->left		= 23;
				pRect->right	= rc.right + 23;
			}
			else	{
				pRect->left		= 0;
				pRect->right	= rc.right;
			}
		}
		else if (!m_pPosition.GetDockedLeft () && pRect->left < 20)	{
			m_pPosition.SetDockedLeft (TRUE, this, FALSE);
			pRect->left			= 0;
			pRect->right		= rc.right;
			m_pPosition.SetDockedPoint (pnt);
		}
	
	// Top
		if (m_pPosition.GetDockedTop ())	{
			if (pnt.y > (m_pPosition.GetDockedPoint ().y + 3))	{
				m_pPosition.SetDockedTop (FALSE, this, FALSE);
				pRect->top		= 23;
				pRect->bottom	= rc.bottom + 23;
			}
			else	{
				pRect->top		= 0;
				pRect->bottom	= rc.bottom;
			}
		}
		else if (!m_pPosition.GetDockedTop () && pRect->top < 20)	{
			m_pPosition.SetDockedTop (TRUE, this, FALSE);
			pRect->top			= 0;
			pRect->bottom		= rc.bottom;
			m_pPosition.SetDockedPoint (pnt);
		}
	
	// Right
		if (m_pPosition.GetDockedRight ())	{
			if (pnt.x < (m_pPosition.GetDockedPoint ().x - 3))	{
				m_pPosition.SetDockedRight (FALSE, this, FALSE);
				pRect->right	= rect.right - 23;
				pRect->left		= rect.right - rc.right - 23;
			}
			else	{
				pRect->right	= rect.right;
				pRect->left		= rect.right - rc.right;
			}
		}
		else if (!m_pPosition.GetDockedRight () && pRect->right > (rect.right - 20))	{
			m_pPosition.SetDockedRight (TRUE, this, FALSE);
			pRect->left			= rect.right - rc.right;
			pRect->right		= rect.right;
			m_pPosition.SetDockedPoint (pnt);
		}
	
	// Bottom
		if (m_pPosition.GetDockedBottom ())	{
			if (pnt.y < (m_pPosition.GetDockedPoint ().y - 3))	{
				m_pPosition.SetDockedBottom (FALSE, this, FALSE);
				pRect->bottom	= rect.bottom - 23;
				pRect->top		= rect.bottom - rc.bottom - 23;
			}
			else	{
				pRect->bottom	= rect.bottom;
				pRect->top		= rect.bottom - rc.bottom;
			}
		}
		else if (!m_pPosition.GetDockedBottom () && pRect->bottom > (rect.bottom - 20))	{
			m_pPosition.SetDockedBottom (TRUE, this, FALSE);
			pRect->top			= rect.bottom - rc.bottom;
			pRect->bottom		= rect.bottom;
			m_pPosition.SetDockedPoint (pnt);
		}
	}

	CDialog::OnMoving(fwSide, pRect);
}


void CNote::OnPopupmenuPrint() 
{
	CPrintDialog dlg(	FALSE, 
						PD_ALLPAGES | 
						PD_RETURNDC |
						PD_NOSELECTION | 
						PD_HIDEPRINTTOFILE | 
						PD_NOPAGENUMS,
						this);

	dlg.m_pd.nCopies = 1;
	dlg.m_pd.hDevMode = NULL;
	dlg.m_pd.hDevNames = NULL;

	if (dlg.DoModal() != IDOK)
	    return;

	HDC hdc = dlg.GetPrinterDC();

	CDC *printDC;
	printDC = CDC::FromHandle (hdc);

	ASSERT(hdc);
	::GlobalFree(dlg.m_pd.hDevMode);
	::GlobalFree(dlg.m_pd.hDevNames);

	CDC *pPrintDC = CDC::FromHandle(hdc);

	pPrintDC->StartDoc(m_szTitle);

	FORMATRANGE fr;

// Get the page width and height from the printer.
	long lPageWidth = ::MulDiv(printDC->GetDeviceCaps (PHYSICALWIDTH), 1440, printDC->GetDeviceCaps (LOGPIXELSX));
	long lPageHeight = ::MulDiv(printDC->GetDeviceCaps (PHYSICALHEIGHT), 1440, printDC->GetDeviceCaps (LOGPIXELSY));
	CRect rcPage(0, 0, lPageWidth, lPageHeight);

	pPrintDC->StartPage();

// Format the text and render it to the printer->
	fr.hdc = printDC->m_hDC;
	fr.hdcTarget = printDC->m_hDC;
	fr.rc = rcPage;
	fr.rcPage = rcPage;
	fr.chrg.cpMin = 0;
	fr.chrg.cpMax = -1;

	m_pText.FormatRange(&fr, TRUE);

// Update the display with the new formatting.
	RECT rcClient;
	m_pText.GetClientRect(&rcClient);
	m_pText.DisplayBand(&rcClient);

	pPrintDC->EndPage();
	pPrintDC->EndDoc();

	pPrintDC->DeleteDC();
}

void CNote::MinimizeNote ()
{
	if (m_bVisible)
		OnMinimize ();
}


void CNote::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
  	
	if (m_pPosition.GetDockedLeft ())		m_pPosition.SetDockedPoint (CPoint (point.x, m_pPosition.GetDockedPoint ().y)) ;
	if (m_pPosition.GetDockedTop ())		m_pPosition.SetDockedPoint (CPoint (m_pPosition.GetDockedPoint ().x, point.y));
	if (m_pPosition.GetDockedRight ())		m_pPosition.SetDockedPoint (CPoint (point.x, m_pPosition.GetDockedPoint ().y)) ;
	if (m_pPosition.GetDockedBottom ())		m_pPosition.SetDockedPoint (CPoint (m_pPosition.GetDockedPoint ().x, point.y));
	
	CDialog::OnNcMouseMove(nHitTest, point);
}


CString CNote::GetDefaultTitle()
{
// Look if the default title is %date% or %time%
// If %date% or %time% is not used then use the
// default word as stated
	CString szTemp = theApp.m_szDefaultTitle;
	CString szRetur = szTemp;
	szTemp.MakeLower ();

	int i = szTemp.Find (_T("%time%"));
	if (i != -1)	{
		CString szTime = COleDateTime::GetCurrentTime ().Format (_T("%H:%M:%S"));
		szRetur.Replace (_T("%time%"), szTime);
	}

	i = szTemp.Find (_T("%date%"));
	if (i != -1)	{
		CString szTime = COleDateTime::GetCurrentTime ().Format (_T("%m/%d/%Y")) ;
		szRetur.Replace (_T("%date%"), szTime);
	}

	COleDateTime pTime;
	pTime.ParseDateTime (szRetur);

	return szRetur;
}
 

void CNote::OnNcRButtonUp(UINT nHitTest, CPoint point) 
{
	BCMenu menu;
	menu.LoadMenu(IDR_POPUPMENU);
	menu.LoadToolbar(IDR_MENUBAR);
	BCMenu *psub = (BCMenu *)menu.GetSubMenu(0);

	psub->SetMenuText (ID_POPUPMENU_CUT,		CTranslate::ReadString (27, _T("Cut")),				MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_COPY, 		CTranslate::ReadString (28, _T("Copy")),			MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_PASTE,	 	CTranslate::ReadString (29, _T("Paste")),			MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_FONT, 		CTranslate::ReadString (30, _T("Font...")),			MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_NOTECOLOR, 	CTranslate::ReadString (31, _T("Note color...")),	MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_SETTITLE, 	CTranslate::ReadString (32, _T("Set title...")),	MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_ALARM,	 	CTranslate::ReadString (33, _T("Alarm...")),		MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_EMAIL, 		CTranslate::ReadString (34, _T("Email...")),		MF_STRING);
	psub->SetMenuText (ID_POPUPMENU_PRINT, 		CTranslate::ReadString (35, _T("Print...")),		MF_STRING);

	psub->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	menu.DestroyMenu();

//	CDialog::OnNcRButtonUp(nHitTest, point);
}

void CNote::OnSlideRight ()
{
	m_pPosition.SlidePositionToRight (this);

// Hide the text and title
	Invalidate ();
	m_pText.ShowWindow (SW_HIDE);
	HideButtons ();

	theApp.m_Layered.SetTransparentPercentage(m_hWnd, theApp.m_iTransparantMinimized);

// Write the title vertically
	Invalidate ();

}

void CNote::OnLButtonDown(UINT nFlags, CPoint point) 
{
// If we have slided the note -> positionate it were it was
	if (m_pPosition.GetSlidedToRight ())	RestoreFromRightSlide ();
	if (m_pPosition.GetSlidedToLeft ())		RestoreFromLeftSlide  ();

	CDialog::OnLButtonDown(nFlags, point);
}

void CNote::RestoreFromRightSlide()
{
// We are in the right sliding mode and the use has pressed on the note
// and therefore we want to slide back where the note were

	m_pPosition.RestoreSlideFromRight (this);

// Show the text and title
	m_pText.ShowWindow (SW_SHOW);
	ShowButtons ();

	theApp.m_Layered.SetTransparentPercentage(m_hWnd, theApp.m_iTransparantNormal);

	Invalidate (TRUE);
}


void CNote::OnSlideLeft ()
{
// Slide the note to the right
	m_pPosition.SlidePositionToLeft (this);

// Hide the text and title
	m_pText.ShowWindow (SW_HIDE);
	HideButtons ();

	theApp.m_Layered.SetTransparentPercentage(m_hWnd, theApp.m_iTransparantMinimized);

// Write the title vertically
	Invalidate ();
}

void CNote::RestoreFromLeftSlide()
{
// We are in the right sliding mode and the use has pressed on the note
// and therefore we want to slide back where the note were
	m_pPosition.RestoreSlideFromLeft (this);

// Show the text and title and the buttons
	m_pText.ShowWindow (SW_SHOW);
	ShowButtons ();

	theApp.m_Layered.SetTransparentPercentage(m_hWnd, theApp.m_iTransparantNormal);

	Invalidate (TRUE);
}

void CNote::HideButtons()
{
	m_pAlarm.ShowWindow			(SW_HIDE);
	m_pClose.ShowWindow			(SW_HIDE);
	m_pBullet.ShowWindow		(SW_HIDE);
	m_pMinimize.ShowWindow		(SW_HIDE);
	m_pClose.ShowWindow			(SW_HIDE);	
	m_pSlideRight.ShowWindow	(SW_HIDE);
	m_pSlideLeft.ShowWindow		(SW_HIDE);
	m_pBold.ShowWindow			(SW_HIDE);
	m_pItalic.ShowWindow		(SW_HIDE);
	m_pUnderline.ShowWindow		(SW_HIDE);
	m_pStrikeOut.ShowWindow		(SW_HIDE);
}

void CNote::ShowButtons()
{
// Determine which buttons to show and where to show them
	CRect rc;
	GetClientRect (&rc);
	int iWhere = rc.right - 20;

// Show the alarm button
	if (m_bUseAlarm && m_pAlarm.GetSafeHwnd ())	{
		m_pAlarm.MoveWindow (5, 4, 16, 16);
		m_pAlarm.ShowWindow (SW_SHOW);
	}

// Always show the close button
	if (m_pClose.GetSafeHwnd ())	{
		m_pClose.MoveWindow (iWhere, 4, 16, 16);
		m_pClose.ShowWindow (SW_SHOW);
		iWhere -= 18;
	}

// Place the rest of the buttons
	for (int i = 1; i < 10; i++)	{

	// Minimize
		if (theApp.m_iToolBarUseMinimize == i && m_pMinimize.GetSafeHwnd ())	{
			m_pMinimize.MoveWindow (iWhere, 4, 16, 16);
			m_pMinimize.ShowWindow (SW_SHOW);
			iWhere -= 18;
		}

	// Slide right
		if (theApp.m_iToolBarUseSlideRight == i && m_pSlideRight.GetSafeHwnd ())	{
			m_pSlideRight.MoveWindow (iWhere, 4, 16, 16);
			m_pSlideRight.ShowWindow (SW_SHOW);
			iWhere -= 18;
		}

	// Slide left
		if (theApp.m_iToolBarUseSlideLeft == i && m_pSlideLeft.GetSafeHwnd ())	{
			m_pSlideLeft.MoveWindow (iWhere, 4, 16, 16);
			m_pSlideLeft.ShowWindow (SW_SHOW);
			iWhere -= 18;
		}

	// Bullet
		if (theApp.m_iToolBarUseBullet == i && m_pBullet.GetSafeHwnd ())	{
			m_pBullet.MoveWindow (iWhere, 4, 16, 16);
			m_pBullet.ShowWindow (SW_SHOW);
			iWhere -= 18;
		}

	// Underline
		if (theApp.m_iToolBarUseUnderline == i && m_pUnderline.GetSafeHwnd ())	{
			m_pUnderline.MoveWindow (iWhere, 4, 16, 16);
			m_pUnderline.ShowWindow (SW_SHOW);
			iWhere -= 18;
		}

	// Strikeout
		if (theApp.m_iToolBarUseStrikeOut == i && m_pStrikeOut.GetSafeHwnd ())	{
			m_pStrikeOut.MoveWindow (iWhere, 4, 16, 16);
			m_pStrikeOut.ShowWindow (SW_SHOW);
			iWhere -= 18;
		}

	// Italic
		if (theApp.m_iToolBarUseItalic == i && m_pItalic.GetSafeHwnd ())	{
			m_pItalic.MoveWindow (iWhere, 4, 16, 16);
			m_pItalic.ShowWindow (SW_SHOW);
			iWhere -= 18;
		}

	// Bold
		if (theApp.m_iToolBarUseBold == i && m_pBold.GetSafeHwnd ())	{
			m_pBold.MoveWindow (iWhere, 4, 16, 16);
			m_pBold.ShowWindow (SW_SHOW);
			iWhere -= 18;
		}
	}

// Calculate the maximal length of the title (to avoid that the text is crashing into the toolbar-buttons
	if (m_bUseAlarm)
		m_iTitleMaxWidth = iWhere - 5;
	else
		m_iTitleMaxWidth = iWhere +18;

// Resize the title (via OnPaint (...)
	Invalidate ();
}


LRESULT CNote::OnDisplayChange(WPARAM wParam, LPARAM lParam)
{
// Retrive the new size
	int cxScreen = LOWORD(lParam); 
	int cyScreen = HIWORD(lParam); 

// The display has changed the size -> Move the note's where they should be
	m_pPosition.SetNotePositionDisplayResolutionChanged (this, CPoint (cxScreen, cyScreen));

 return 0;
}


void CNote::OnStrikeOut ()
{
	m_pText.SetSelectionStrikeOut ();

}


CString CNote::GetReadableText ()
{
// Get the text from the textbox in a readable mode (not RTF)
// This is used so we can read the text from the server if we
// want to read the notes from the web
	CString szText;
	m_pText.GetWindowText (szText);

	return szText;
}

void CNote::OnNcPaint() 
{
	OnPaint ();	
}
