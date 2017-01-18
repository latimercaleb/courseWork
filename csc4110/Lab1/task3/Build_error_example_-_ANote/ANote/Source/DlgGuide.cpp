// DlgGuide.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgGuide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGuide dialog


CDlgGuide::CDlgGuide(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGuide::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGuide)
	m_bDontShowAgain = FALSE;
	//}}AFX_DATA_INIT

	m_iPage = 1;
}


void CDlgGuide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGuide)
	DDX_Check(pDX, IDC_SHOWAGAIN, m_bDontShowAgain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGuide, CDialog)
	//{{AFX_MSG_MAP(CDlgGuide)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_FINISH, OnFinish)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGuide message handlers

void CDlgGuide::OnNext() 
{
// Make sure that the previous button is enabled
	((CButton *) GetDlgItem (IDC_PREVIOUS))->EnableWindow (TRUE);

// Go to next page
	m_iPage++;

// Are we at the end?
	if (m_iPage == 10)
		((CButton *) GetDlgItem (IDC_NEXT))->EnableWindow (FALSE);

// Load the right image
	CString szName;
	szName.Format (_T("%s\\Guide\\guide_%d.jpg"), GetProgramPath (), m_iPage);
	m_pImage.Load (szName);

// Show the right page
	Invalidate (FALSE);
}

void CDlgGuide::OnPrevious() 
{
// Make sure that the next button is enabled
	((CButton *) GetDlgItem (IDC_NEXT))->EnableWindow (TRUE);

// Go to previous page
	m_iPage--;

// Are we at the first page
	if (m_iPage == 1)
		((CButton *) GetDlgItem (IDC_PREVIOUS))->EnableWindow (FALSE);

// Load the right image
	CString szName;
	szName.Format (_T("%s\\Guide\\guide_%d.jpg"), GetProgramPath (), m_iPage);
	m_pImage.Load (szName);

// Show the right page
	Invalidate (FALSE);
}

BOOL CDlgGuide::OnEraseBkgnd(CDC* pDC) 
{
// To avoid flicker
	return TRUE;
}

void CDlgGuide::OnFinish() 
{
// Close the dialog
	OnOK ();
}

void CDlgGuide::OnPaint() 
{
	CPaintDC dc(this); 
	

	CDC *pDC;
	pDC = GetDC ();
	CRect rect;
	GetClientRect (&rect);

	CBrush brush;
	brush.CreateSolidBrush (::GetSysColor (COLOR_3DFACE));
	CBrush *pOldBrush = (CBrush *) dc.SelectObject (brush);
	dc.Rectangle (rect);

	CPen pen;
	pen.CreatePen (PS_SOLID, 2, RGB (0,0,0));
	CPen *pOldPen = (CPen *) dc.SelectObject (pen);

	dc.MoveTo (0, 252);
	dc.LineTo (rect.right, 252);

	m_pImage.Draw(pDC, CPoint (1, 1), CPoint (400, 250));

//	dc.SelectObject (pOldBrush);
	
}

BOOL CDlgGuide::OnInitDialog() 
{


// Language stuff
	((CButton *) GetDlgItem (IDC_SHOWAGAIN))->SetWindowText (CTranslate::ReadString (46, "Don't show again"));
	((CButton *) GetDlgItem (IDC_PREVIOUS))->SetWindowText (CTranslate::ReadString (47, "Previous"));
	((CButton *) GetDlgItem (IDC_NEXT))->SetWindowText (CTranslate::ReadString (48, "Next"));
	((CButton *) GetDlgItem (IDC_FINISH))->SetWindowText (CTranslate::ReadString (49, "Finish"));



// Load the first image
	CString szName;
	szName.Format (_T("%s\\Guide\\guide_1.jpg"), GetProgramPath ());
	m_pImage.Load (szName);
	Invalidate (FALSE);

	CDialog::OnInitDialog();
	return TRUE;
}
