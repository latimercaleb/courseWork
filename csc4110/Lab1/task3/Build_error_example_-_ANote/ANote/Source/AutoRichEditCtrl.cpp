// AutoRichEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AutoRichEditCtrl.h"

#include "A Note.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CAutoRichEditCtrl::CAutoRichEditCtrl()
{
}

CAutoRichEditCtrl::~CAutoRichEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CAutoRichEditCtrl, CRichEditCtrl)
	//{{AFX_MSG_MAP(CAutoRichEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoRichEditCtrl message handlers

CString CAutoRichEditCtrl::GetRTF()
{
	// Return the RTF string of the text in the control.
	
	// Stream out here.
	EDITSTREAM es;
	es.dwError = 0;
	es.pfnCallback = CBStreamOut;		// Set the callback

	CString sRTF = "";

	es.dwCookie = (DWORD) &sRTF;	// so sRTF receives the string
	
	StreamOut(SF_RTF | SF_UNICODE, es);			// Call CRichEditCtrl::StreamOut to get the string.
	///

	return sRTF;

}

void CAutoRichEditCtrl::SetRTF(CString sRTF)
{
	// Put the RTF string sRTF into the rich edit control.

	// Read the text in
	EDITSTREAM es;
	es.dwError = 0;
	es.pfnCallback = CBStreamIn;
	es.dwCookie = (DWORD) &sRTF;
	StreamIn(SF_RTF | SF_UNICODE, es);	// Do it.
}


//	Callback function to stream an RTF string into the rich edit control.

DWORD CALLBACK CAutoRichEditCtrl::CBStreamIn(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CString *pstr = (CString *) dwCookie;
	*pcb = pstr->GetLength();

#if (defined (UNICODE) || defined(_UNICODE))
	CString a = *pstr;
	int iLength, iMultibyte;
	WCHAR *pwcUnicode;
	char *pcDest;
	CString szResult;

	iLength	= pstr->GetLength ();
	pwcUnicode	= (WCHAR*)	malloc ( sizeof (WCHAR)	* (iLength + 1));
	pcDest		= (char*)	malloc ( 2	* (iLength + 1) );
	memset (pwcUnicode, 0, sizeof (WCHAR)	* (iLength + 1));
	memset (pcDest, 0, sizeof (char)	* (iLength + 1));
	_tcscpy(pwcUnicode, a);
// To UTF-8
	iMultibyte = WideCharToMultiByte (CP_UTF8, 0,pwcUnicode, iLength , pcDest, 2*iLength, NULL, NULL);
	szResult = (CString) pcDest;
	szResult = szResult.Left ( iMultibyte );
	pcDest[iMultibyte] = '\0';
	if (pstr->GetLength () < cb)
		memcpy(pbBuff, pcDest, iMultibyte);
	else	{
		*pcb = cb;
		memcpy(pbBuff, pcDest, cb);
		*pstr = pstr->Right(pstr->GetLength() - cb);
	}
	free (pwcUnicode);
	free (pcDest);
	return 0;

#else
	if (pstr->GetLength() < cb)	{
		*pcb = pstr->GetLength();
		memcpy(pbBuff, *pstr, *pcb);
		pstr->Empty();
	}
	else	{
		*pcb = cb;
		memcpy(pbBuff, *pstr, *pcb);
		*pstr = pstr->Right(pstr->GetLength() - cb);
	}
	return 0;
#endif
}

DWORD CALLBACK CAutoRichEditCtrl::CBStreamOut(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	// Address of our string var is in psEntry
	CString *psEntry = (CString*) dwCookie;
	

	CString tmpEntry = "";
	tmpEntry = (CString) pbBuff;

	// And write it!!!
	*psEntry += tmpEntry.Left(cb);

	return 0;
}

bool CAutoRichEditCtrl::SelectionIsBold()
{
	CHARFORMAT cf = GetCharFormat();	
	
	if (cf.dwEffects & CFM_BOLD)
		return true;
	else
		return false;
}

bool CAutoRichEditCtrl::SelectionIsItalic()
{
	CHARFORMAT cf = GetCharFormat();	
	
	if (cf.dwEffects & CFM_ITALIC)
		return true;
	else
		return false;
}

bool CAutoRichEditCtrl::SelectionIsUnderlined()
{
	CHARFORMAT cf = GetCharFormat();	
	
	if (cf.dwEffects & CFM_UNDERLINE)
		return true;
	else
		return false;
}

  
CHARFORMAT CAutoRichEditCtrl::GetCharFormat(DWORD dwMask)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);

	cf.dwMask = dwMask;

	GetSelectionCharFormat(cf);

	return cf;
}

void CAutoRichEditCtrl::SetCharStyle(int MASK, int STYLE, int nStart, int nEnd)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);

	//cf.dwMask = MASK;
	
	GetSelectionCharFormat(cf);
	
	if (cf.dwMask & MASK)	// selection is all the same
	{
		cf.dwEffects ^= STYLE; 
	}
	else
	{
		cf.dwEffects |= STYLE;
	}
	
	cf.dwMask = MASK;

	SetSelectionCharFormat(cf);

}

void CAutoRichEditCtrl::SetSelectionBold()
{
	long start=0, end=0;
	GetSel(start, end);		// Get the current selection

	SetCharStyle(CFM_BOLD, CFE_BOLD, start, end);	// Make it bold
}

void CAutoRichEditCtrl::SetSelectionItalic()
{
	long start=0, end=0;
	GetSel(start, end);

	SetCharStyle(CFM_ITALIC, CFE_ITALIC, start, end);
}

void CAutoRichEditCtrl::SetSelectionUnderlined()
{
	long start=0, end=0;
	GetSel(start, end);

	SetCharStyle(CFM_UNDERLINE, CFE_UNDERLINE, start, end);
}

void CAutoRichEditCtrl::SetSelectionStrikeOut ()
{
	long start=0, end=0;
	GetSel(start, end);

	SetCharStyle(CFM_STRIKEOUT, CFE_STRIKEOUT, start, end);
}


void CAutoRichEditCtrl::SetParagraphCenter()
{
	PARAFORMAT paraFormat;    
	paraFormat.cbSize = sizeof(PARAFORMAT);
	paraFormat.dwMask = PFM_ALIGNMENT;    
	paraFormat.wAlignment = PFA_CENTER;
	
	SetParaFormat(paraFormat);	// Set the paragraph.
}

void CAutoRichEditCtrl::SetParagraphLeft()
{
	PARAFORMAT paraFormat;
	paraFormat.cbSize = sizeof(PARAFORMAT);
	paraFormat.dwMask = PFM_ALIGNMENT;    
	paraFormat.wAlignment = PFA_LEFT;
	
	SetParaFormat(paraFormat);
}

void CAutoRichEditCtrl::SetParagraphRight()
{
	PARAFORMAT paraFormat;
	paraFormat.cbSize = sizeof(PARAFORMAT);
	paraFormat.dwMask = PFM_ALIGNMENT;    
	paraFormat.wAlignment = PFA_RIGHT;
	
	SetParaFormat(paraFormat);
}

bool CAutoRichEditCtrl::ParagraphIsCentered()
{
	PARAFORMAT pf = GetParagraphFormat();

	if (pf.wAlignment == PFA_CENTER)
		return true;
	else
		return false;
}

bool CAutoRichEditCtrl::ParagraphIsLeft()
{
	PARAFORMAT pf = GetParagraphFormat();

	if (pf.wAlignment == PFA_LEFT)
		return true;
	else
		return false;
}

bool CAutoRichEditCtrl::ParagraphIsRight()
{
	PARAFORMAT pf = GetParagraphFormat();

	if (pf.wAlignment == PFA_RIGHT)
		return true;
	else
		return false;
}

PARAFORMAT CAutoRichEditCtrl::GetParagraphFormat()
{
	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);

	pf.dwMask = PFM_ALIGNMENT | PFM_NUMBERING;    	

	GetParaFormat(pf);

	return pf;
}

void CAutoRichEditCtrl::SetParagraphBulleted()
{
	PARAFORMAT paraformat = GetParagraphFormat();

	if ( (paraformat.dwMask & PFM_NUMBERING) && (paraformat.wNumbering == PFN_BULLET) )
	{
		paraformat.wNumbering = 0;
		paraformat.dxOffset = 0;
		paraformat.dxStartIndent = 0;
		paraformat.dwMask = PFM_NUMBERING | PFM_STARTINDENT | PFM_OFFSET;
	}
	else
	{
		paraformat.wNumbering = PFN_BULLET;
		paraformat.dwMask = PFM_NUMBERING;
		if (paraformat.dxOffset == 0)
		{
			paraformat.dxOffset = 4;
			paraformat.dwMask = PFM_NUMBERING | PFM_STARTINDENT | PFM_OFFSET;
		}
	}
	
	SetParaFormat(paraformat);

}

bool CAutoRichEditCtrl::ParagraphIsBulleted()
{
	PARAFORMAT pf = GetParagraphFormat();

	if (pf.wNumbering == PFN_BULLET)
		return true;
	else
		return false;
}

void CAutoRichEditCtrl::SelectColor()
{
	CColorDialog dlg;

	CHARFORMAT cf = GetCharFormat();

	if (cf.dwEffects & CFE_AUTOCOLOR) cf.dwEffects -= CFE_AUTOCOLOR;

	// Get a color from the common color dialog.
	if( dlg.DoModal() == IDOK )
	{	
		cf.crTextColor = dlg.GetColor();
	}

	cf.dwMask = CFM_COLOR;

	SetSelectionCharFormat(cf);
}

void CAutoRichEditCtrl::SetFontName(CString sFontName)
{
	CHARFORMAT cf = GetCharFormat();

	// Set the font name.
	for (int i = 0; i <= sFontName.GetLength()-1; i++)
		cf.szFaceName[i] = sFontName[i];


	cf.dwMask = CFM_FACE;

	SetSelectionCharFormat(cf);
}

void CAutoRichEditCtrl::SetFontSize(int nPointSize)
{
	CHARFORMAT cf = GetCharFormat();

	nPointSize *= 20;	// convert from to twips
	cf.yHeight = nPointSize;
	
	cf.dwMask = CFM_SIZE;

	SetSelectionCharFormat(cf);
}

void CAutoRichEditCtrl::GetSystemFonts(CStringArray &saFontList)
{
	CDC *pDC = GetDC ();

	EnumFonts (pDC->GetSafeHdc(),NULL,(FONTENUMPROC) CBEnumFonts,(LPARAM)&saFontList);//Enumerate

}

BOOL CALLBACK CAutoRichEditCtrl::CBEnumFonts(LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData)
{
	// This function was written with the help of CCustComboBox, by Girish Bharadwaj.
	// Available from Codeguru.

	if (dwType == TRUETYPE_FONTTYPE) 
	{
		((CStringArray *) lpData)->Add( lplf->lfFaceName );
	}

	return true;
}

CString CAutoRichEditCtrl::GetSelectionFontName()
{
	CHARFORMAT cf = GetCharFormat();

	CString sName = cf.szFaceName;

	return sName;
}

long CAutoRichEditCtrl::GetSelectionFontSize()
{
	CHARFORMAT cf = GetCharFormat();

	long nSize = cf.yHeight/20;

	return nSize;
}


void CAutoRichEditCtrl::SetTextColor(COLORREF cfColor)
{
	CHARFORMAT cf = GetCharFormat();

	if (cf.dwEffects & CFE_AUTOCOLOR) cf.dwEffects -= CFE_AUTOCOLOR;

	cf.crTextColor = cfColor;
	cf.dwMask = CFM_COLOR;

	SetSelectionCharFormat(cf);

}


UINT CAutoRichEditCtrl::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;
}

void CAutoRichEditCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
// So we will get the popup in win 9x
	CNote *pNote = (CNote *) GetParent ();
	ClientToScreen (&point);
	pNote->OnContextMenu (this, point);
}
