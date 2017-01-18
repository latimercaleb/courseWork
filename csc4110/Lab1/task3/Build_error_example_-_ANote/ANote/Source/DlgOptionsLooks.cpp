// DlgOptionsLooks.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgOptionsLooks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsLooks dialog


CDlgOptionsLooks::CDlgOptionsLooks(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsLooks::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsLooks)
	m_bRndColor = FALSE;
	m_bThinBorder = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsLooks::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsLooks)
	DDX_Check(pDX, IDC_RNDCOLOR, m_bRndColor);
	DDX_Check(pDX, IDC_THINBORDER, m_bThinBorder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsLooks, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsLooks)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHANGENOTECOLOR, OnChangenotecolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsLooks message handlers



void CDlgOptionsLooks::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush brush;
	brush.CreateSolidBrush (m_cfColor);
	CBrush *pOldBrush = (CBrush *) dc.SelectObject (brush);

	dc.Rectangle (20,47,41, 68);
	dc.SelectObject (&pOldBrush);
}




void CDlgOptionsLooks::OnChangenotecolor() 
{
	CColorDialog dlg;
	
	if (dlg.DoModal() == IDOK)	{
		m_cfColor = dlg.GetColor ();
		Invalidate ();
	}
}


BOOL CDlgOptionsLooks::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
// Langugage stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (110, _T("Looks")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (111, _T("Default note color")));
	((CButton *)GetDlgItem (IDC_RNDCOLOR))->SetWindowText (CTranslate::ReadString (112, _T("Randomize the note color")));
	((CButton *)GetDlgItem (IDC_THINBORDER))->SetWindowText (CTranslate::ReadString (113, _T("Thin border")));
	((CButton *)GetDlgItem (IDC_CHANGENOTECOLOR))->SetWindowText (CTranslate::ReadString (114, _T("Change...")));


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
