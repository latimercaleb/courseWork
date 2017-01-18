#include "stdafx.h"
#include "noteposition.h"
#include "A Note.h"
#include "note.h"


CNotePosition::CNotePosition(void)
{
// Initialize the variables;
	m_cNotePosition.SetRectEmpty   ();
	m_cBeforeSlidedPosition.SetRectEmpty ();		
	m_bSlidedToLeft		= FALSE;
	m_bSlidedToRight	= FALSE;
	m_bDockedLeft		= FALSE;			
	m_bDockedTop		= FALSE;		
	m_bDockedRight		= FALSE;		
	m_bDockedBottom		= FALSE;
	m_pDockPnt.x		= 0;
	m_pDockPnt.y		= 0;

// Save the screen's resolution
	CRect rc;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);
	m_csScreenResolution.cx = rc.right;
	m_csScreenResolution.cy = rc.bottom;
}

CNotePosition::~CNotePosition(void)
{
}

void CNotePosition::SetSlidedToLeft (BOOL bSlided, void *pNote, bool bFixPosition)
{
	CNote *note = (CNote *)pNote;
	m_bSlidedToLeft		= bSlided;
	if (bFixPosition)	FixNotePosition (note);
}

void CNotePosition::SetSlidedToRight (BOOL bSlided, void *pNote, bool bFixPosition)
{
	CNote *note = (CNote *)pNote;
	m_bSlidedToRight	= bSlided;
	if (bFixPosition)	FixNotePosition (note);
}

void CNotePosition::SetDockedLeft (BOOL bDocked, void *pNote, bool bFixPosition)
{
	CNote *note = (CNote *)pNote;
	m_bDockedLeft		= bDocked;
	if (bFixPosition)	FixNotePosition (note);
}

void CNotePosition::SetDockedTop (BOOL bDocked, void *pNote, bool bFixPosition)
{
	CNote *note = (CNote *)pNote;
	m_bDockedTop		= bDocked;
	if (bFixPosition)	FixNotePosition (note);
}

void CNotePosition::SetDockedRight (BOOL bDocked, void *pNote, bool bFixPosition)
{
	CNote *note = (CNote *)pNote;
	m_bDockedRight		= bDocked;
	if (bFixPosition)	FixNotePosition (note);
}

void CNotePosition::SetDockedBottom (BOOL bDocked, void *pNote, bool bFixPosition)
{
	CNote *note = (CNote *)pNote;
	m_bDockedBottom		= bDocked;
	if (bFixPosition)	FixNotePosition (note);
}

void CNotePosition::SetNotePosition (CRect cRect,  void *pNote, bool bFixPosition)
{
	CNote *note = (CNote *)pNote;
	m_cNotePosition		= cRect;
	if (bFixPosition)	FixNotePosition (note);
}

void CNotePosition::SetSlidedNotePosition (CRect cRect,  void *pNote, bool bFixPosition)
{
	CNote *note = (CNote *)pNote;
	m_cBeforeSlidedPosition	= cRect;
	if (bFixPosition)	FixNotePosition (note);
}

void CNotePosition::SlidePositionToLeft (void *pNote)
{
// Slide the note to the left side
	CNote *note = (CNote *) pNote;

// Show that we have slided the note
	m_bSlidedToLeft = TRUE;

// Remember where we were
	m_cBeforeSlidedPosition = m_cNotePosition;

// Calculate the distance
	CRect rc;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);
	int iDist, iTotal, iSpeed;
	iDist = iTotal = m_cNotePosition.left;
	iSpeed = (m_cNotePosition.left) / 10;

	while ((iDist) > 20)	{
		note->MoveWindow (iDist, m_cNotePosition.top, m_cNotePosition.right, m_cNotePosition.bottom);

		Sleep (10);
		iDist -= iSpeed;
	}	

// Correct any error (and make the window at least 300 px higher than the text, but never shorter than 100 px)
	CSize Size;
	CDC *pDC;
	pDC = note->GetDC ();
	CFont font;
	CFont * pFont;
	font.CreateFont(-12,0,900,0,FW_NORMAL,FALSE,FALSE,0,theApp.m_iCharset,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,_T("Arial"));
	pFont = pDC->SelectObject(&font);
	Size = pDC->GetTextExtent(note->GetTitle (), note->GetTitle ().GetLength ());
	Size.cx += 30;
	if (Size.cx < 100)
		Size.cx = 100;
	m_cNotePosition.bottom = Size.cx;
	m_cNotePosition.top = m_cNotePosition.top + m_cNotePosition.bottom > rc.bottom ? rc.bottom - m_cNotePosition.bottom : m_cNotePosition.top;
	m_cNotePosition.left = 0;
	m_cNotePosition.right = 30;
	note->MoveWindow (0, m_cNotePosition.top, 30, m_cNotePosition.bottom);
}

void CNotePosition::SlidePositionToRight (void *pNote)
{
	CNote *note = (CNote *) pNote;

// Slide the note to the right

// Show that we have slided the note
	m_bSlidedToRight = TRUE;

// Remember where we were
	m_cBeforeSlidedPosition = m_cNotePosition;

// Calculate the distance
	CRect rc;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);
	int iDist, iTotal, iSpeed;
	iTotal = rc.right - m_cNotePosition.left;
	iDist = m_cNotePosition.left;
	iSpeed = (rc.right - m_cNotePosition.left) / 10;

	while ((iDist) < rc.right - 20)	{
		note->MoveWindow (iDist, m_cNotePosition.top, m_cNotePosition.right, m_cNotePosition.bottom);

		Sleep (10);
		iDist += iSpeed;
	}	

// Correct any error (and make the window at least 30 px higher than the text, but never shorter than 100 px)
	CSize Size;
	CDC *pDC;
	pDC = note->GetDC ();
	CFont font;
	CFont * pFont;
	font.CreateFont(-12,0,900,0,FW_NORMAL,FALSE,FALSE,0,theApp.m_iCharset,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,_T("Arial"));
	pFont = pDC->SelectObject(&font);
	Size = pDC->GetTextExtent(note->GetTitle (), note->GetTitle ().GetLength ());
	Size.cx += 30;
	if (Size.cx < 100)
		Size.cx = 100;
	m_cNotePosition.bottom = Size.cx;
	m_cNotePosition.right = 30;
	m_cNotePosition.left = rc.right - 30;
	m_cNotePosition.top = m_cNotePosition.top + m_cNotePosition.bottom > rc.bottom ? rc.bottom - m_cNotePosition.bottom : m_cNotePosition.top;
	note->MoveWindow (rc.right - 30, m_cNotePosition.top, 30, m_cNotePosition.bottom);
}

void CNotePosition::RestoreSlideFromLeft (void *pNote)
{
	CNote *note = (CNote *) pNote;
// We are in the right sliding mode and the use has pressed on the note
// and therefore we want to slide back where the note were

// Calculate the distance
	CRect rc;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);
	int iDist, iTotal, iSpeed;
	iDist = 0;
	iTotal = m_cBeforeSlidedPosition.left;
	iSpeed = (m_cBeforeSlidedPosition.left) / 10;

	while (iDist < m_cBeforeSlidedPosition.left)	{
		note->MoveWindow (iDist, m_cBeforeSlidedPosition.top, m_cBeforeSlidedPosition.right, m_cBeforeSlidedPosition.bottom);

		Sleep (10);
		iDist += iSpeed;
	}	

// Correct any error 
	note->MoveWindow (m_cBeforeSlidedPosition.left, m_cBeforeSlidedPosition.top, m_cBeforeSlidedPosition.right, m_cBeforeSlidedPosition.bottom);
	
	m_cNotePosition = m_cBeforeSlidedPosition;

// Show that we have slided the note
	m_bSlidedToLeft = FALSE;
	m_cBeforeSlidedPosition.SetRectEmpty ();

// Be realy sure it is visible
	FixNotePosition (note);
}

void CNotePosition::RestoreSlideFromRight (void *pNote)
{
// Restore the note from a right slide
	CNote *note = (CNote *) pNote;

// Calculate the distance
	CRect rc;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);
	int iDist, iTotal, iSpeed;
	iDist = m_cBeforeSlidedPosition.left;
	iTotal = iDist;
	iSpeed = (rc.right - m_cBeforeSlidedPosition.left) / 10;

	while ((rc.right - iTotal + iDist) > m_cBeforeSlidedPosition.left)	{
		note->MoveWindow (rc.right - iTotal + iDist, m_cBeforeSlidedPosition.top, m_cBeforeSlidedPosition.right, m_cBeforeSlidedPosition.bottom);

		Sleep (10);
		iDist -= iSpeed;
	}	

// Correct any error 
	note->MoveWindow (m_cBeforeSlidedPosition.left, m_cBeforeSlidedPosition.top, m_cBeforeSlidedPosition.right, m_cBeforeSlidedPosition.bottom);

	m_cNotePosition = m_cBeforeSlidedPosition;

// Show that we have slided the note
	m_bSlidedToRight = FALSE;
	m_cBeforeSlidedPosition.SetRectEmpty ();

// Be realy sure it is visible
	FixNotePosition (note);
}

void CNotePosition::SetNotePositionDisplayResolutionChanged	(void *pNote, CPoint pScreen)
{
// Calculate the new position of the note
	CNote *note = (CNote *)pNote;
	float iX, iY;

	iX = (float) float (m_cNotePosition.left) / float (m_csScreenResolution.cx);
	iX *= (float) pScreen.x;
	iX = (int) iX;
	iY = (float) float (m_cNotePosition.top) / float (m_csScreenResolution.cy);
	iY *= (float) pScreen.y;
	iY = (int) iY;

	m_cBeforeSlidedPosition.left = m_cNotePosition.left = iX;
	m_cBeforeSlidedPosition.top  = m_cNotePosition.top  = iY;
	
// Make sure that the note is still within the monitor
	if (iX + m_cNotePosition.right > pScreen.x)	
		iX = pScreen.x - m_cNotePosition.right;
	if (iY + m_cNotePosition.bottom > pScreen.y)
		iY = pScreen.y - m_cNotePosition.bottom;

// Move the note to it's new position
	note->MoveWindow (iX, iY, m_cNotePosition.right, m_cNotePosition.bottom);

// Save the new resolution
	m_csScreenResolution.cx = pScreen.x;
	m_csScreenResolution.cy = pScreen.y;
}

void CNotePosition::FixNotePosition (void *pNote)
{
// The main function.
// It will look into all of the variables and maybe
// change the note's position because the note will not
// appear correct within the display
	CNote *note = (CNote *)pNote;
	CRect rc;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);

// Be sure that the note is within the boundaries of the display
	if (rc.right < m_cNotePosition.left)		m_cNotePosition.left = rc.right - m_cNotePosition.right;
	if (rc.bottom < m_cNotePosition.top)		m_cNotePosition.top = rc.bottom - (note->GetVisible () ? m_cNotePosition.bottom : 23);
	if (rc.left > m_cNotePosition.left)			m_cNotePosition.left = rc.left;
	if (rc.top > m_cNotePosition.top)			m_cNotePosition.top = rc.top;
	note->MoveWindow (m_cNotePosition.left, m_cNotePosition.top, m_cNotePosition.right, m_cNotePosition.bottom);

// Is it docked
	if (theApp.m_bDockable)	{
		if (m_bDockedRight)		m_cNotePosition.left = rc.right - m_cNotePosition.right;
		if (m_bDockedBottom)	m_cNotePosition.top  = rc.bottom - (note->GetVisible () ? m_cNotePosition.bottom : 23);
		if (m_bDockedLeft)		m_cNotePosition.left = rc.left;
		if (m_bDockedTop)		m_cNotePosition.top  = rc.top;
		note->MoveWindow (m_cNotePosition.left, m_cNotePosition.top, m_cNotePosition.right, m_cNotePosition.bottom);
	}

// Is it slided to the left
	if (m_bSlidedToLeft)	{
		m_cNotePosition.left = 0;
		m_cNotePosition.right = 30;
		note->MoveWindow (m_cNotePosition.left, m_cNotePosition.top, m_cNotePosition.right, m_cNotePosition.bottom);
	}

// Is it slided to the right
	if (m_bSlidedToRight)	{
		m_cNotePosition.left = rc.right - 30;
		m_cNotePosition.right = 30;
		note->MoveWindow (m_cNotePosition.right, m_cNotePosition.top, m_cNotePosition.right, m_cNotePosition.bottom);
	}

// Be sure that the note's height is always larger than 0
	if (m_cNotePosition.bottom <= 0)	{
		m_cNotePosition.bottom = 50;
		note->MoveWindow (m_cNotePosition.right, m_cNotePosition.top, m_cNotePosition.right, m_cNotePosition.bottom);
	}

// Be sure that the note's width is always larger than 0
	if (m_cNotePosition.right <= 0)	{
		m_cNotePosition.right = 100;
		note->MoveWindow (m_cNotePosition.right, m_cNotePosition.top, m_cNotePosition.right, m_cNotePosition.bottom);
	}

// Be sure that the note's position before it was slided is larger than 0
	if (m_cBeforeSlidedPosition.left < 0)
		m_cBeforeSlidedPosition.left = 0;
	if (m_cBeforeSlidedPosition.top < 0)
		m_cBeforeSlidedPosition.top = 0;
	if (m_cBeforeSlidedPosition.right <= 0)
		m_cBeforeSlidedPosition.right = 100;
	if (m_cBeforeSlidedPosition.bottom <= 0)
		m_cBeforeSlidedPosition.bottom = 100;
}