// DlgOptionsFont.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgOptionsFont.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsFont dialog


CDlgOptionsFont::CDlgOptionsFont(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsFont::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsFont)
	//}}AFX_DATA_INIT
}


void CDlgOptionsFont::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsFont)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsFont, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsFont)
	ON_BN_CLICKED(IDC_CHANGEFONT, OnChangefont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsFont message handlers

BOOL CDlgOptionsFont::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();


// Initialize
	m_pText.Create (	WS_CHILD |
						ES_WANTRETURN |
						ES_AUTOVSCROLL |
						WS_TABSTOP |
						WS_VISIBLE,
						CRect(20,85,300,110), 
						this,
						1);

	CHARFORMAT c;

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
	{
		m_pText.SetSel (0, -1);
		m_pText.SetSelectionCharFormat (c);
	}

	m_pText.SetWindowText (CTranslate::ReadString (92, _T("This is the font for a new note ...")));

// Language stuff
	szTemp.Format (_T(" %s "), CTranslate::ReadString (89, _T("Default note font")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (90, _T("Try here:")));
	((CButton *)GetDlgItem (IDC_CHANGEFONT))->SetWindowText (CTranslate::ReadString (91, _T("Change font...")));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOptionsFont::OnChangefont() 
{
// Show the change font dialog
	CHARFORMAT c;
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


	CFontDialog dlg (c);

	if (dlg.DoModal () == IDOK)	{
		CHARFORMAT cf;
		dlg.GetCharFormat (cf);
		m_pText.SetSel (0, -1);
		m_pText.SetSelectionCharFormat (cf);

		AfxGetApp ()->WriteProfileInt	 (_T("Options\\Font"), _T("cbSize"),			cf.cbSize);
		AfxGetApp ()->WriteProfileInt	 (_T("Options\\Font"), _T("dwMask"),			cf.dwMask);
		AfxGetApp ()->WriteProfileInt	 (_T("Options\\Font"), _T("dwEffects"),			cf.dwEffects);
		AfxGetApp ()->WriteProfileInt	 (_T("Options\\Font"), _T("yHeight"),			cf.yHeight);
		AfxGetApp ()->WriteProfileInt	 (_T("Options\\Font"), _T("yOffset"),			cf.yOffset);
		AfxGetApp ()->WriteProfileInt	 (_T("Options\\Font"), _T("crTextColor"),		cf.crTextColor);
		AfxGetApp ()->WriteProfileInt	 (_T("Options\\Font"), _T("bCharSet"),			cf.bCharSet);
		AfxGetApp ()->WriteProfileInt	 (_T("Options\\Font"), _T("bPitchAndFamily"),	cf.bPitchAndFamily);
		AfxGetApp ()->WriteProfileString (_T("Options\\Font"), _T("szFaceName"),		cf.szFaceName);
	}
}
