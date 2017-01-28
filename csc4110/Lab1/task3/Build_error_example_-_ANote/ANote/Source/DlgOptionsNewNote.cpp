// DlgOptionsNewNote.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgOptionsNewNote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsNewNote dialog


CDlgOptionsNewNote::CDlgOptionsNewNote(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsNewNote::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsNewNote)
	m_bDockBottom = FALSE;
	m_bDockLeft = FALSE;
	m_bDockRight = FALSE;
	m_bDockTop = FALSE;
	m_szLeft = _T("");
	m_szTop = _T("");
	m_szWidth = _T("");
	//}}AFX_DATA_INIT
}


void CDlgOptionsNewNote::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsNewNote)
	DDX_Check(pDX, IDC_DOCKBOTTOM, m_bDockBottom);
	DDX_Check(pDX, IDC_DOCKLEFT, m_bDockLeft);
	DDX_Check(pDX, IDC_DOCKRIGHT, m_bDockRight);
	DDX_Check(pDX, IDC_DOCKTOP, m_bDockTop);
	DDX_Text(pDX, IDC_LEFT, m_szLeft);
	DDX_Text(pDX, IDC_TOP, m_szTop);
	DDX_Text(pDX, IDC_WIDTH, m_szWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsNewNote, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsNewNote)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DOCKBOTTOM,	OnDockClick)
	ON_BN_CLICKED(IDC_DOCKTOP,		OnDockClick)
	ON_BN_CLICKED(IDC_DOCKRIGHT,	OnDockClick)
	ON_BN_CLICKED(IDC_DOCKLEFT,		OnDockClick)
	ON_EN_CHANGE(IDC_LEFT,			OnDockClick)
	ON_EN_CHANGE(IDC_TOP,			OnDockClick)
	ON_EN_CHANGE(IDC_WIDTH,			OnDockClick)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsNewNote message handlers



void CDlgOptionsNewNote::OnPaint() 
{
	CPaintDC dc(this); 

	CPen pen;
	CBrush brush;

	pen.CreatePen (PS_SOLID, 1, RGB (0,0,0));
	brush.CreateSolidBrush (theApp.m_cfNoteColor);

	CPen *pOldPen = (CPen *) dc.SelectObject (pen);
	CBrush *pOldBrush = (CBrush *) dc.SelectObject (brush);

// Get monitor width and height
	CRect rc;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);
	CPoint tinyscreen (294 - 137, 223 - 102);

// Calculate where the notes will appear
	CRect rcnote;

	if (m_bDockLeft)	rcnote.left = 0;
	else				rcnote.left = (int) (float) _ttoi (m_szLeft) / (float) rc.Width () * tinyscreen.x;

	if (m_bDockTop)		rcnote.top = 0;
	else				rcnote.top = (int) (float) _ttoi (m_szTop) / (float) rc.Height () * tinyscreen.y;

	if (m_bDockRight)	rcnote.left = tinyscreen.x - ((int) (float) _ttoi (m_szWidth) / (float) rc.Width () * tinyscreen.x);

	if (m_bDockBottom)	rcnote.top = tinyscreen.y - 10;


	rcnote.right = rcnote.left + ((int) (float) _ttoi (m_szWidth) / (float) rc.Width () * tinyscreen.x);
	rcnote.bottom = rcnote.top + 10;

	rcnote.left		+= 137;
	rcnote.right	+= 137;
	rcnote.top		+= 102;
	rcnote.bottom	+= 102;

	dc.Rectangle (rcnote);

// Clean up
	dc.SelectObject (&pOldPen);
	dc.SelectObject (&pOldBrush);
}

void CDlgOptionsNewNote::OnDockClick() 
{
	UpdateData (TRUE);
	Invalidate ();

// Make some of the controls grey
	if (m_bDockLeft)	((CButton *)GetDlgItem (IDC_DOCKRIGHT))->EnableWindow (FALSE);
	else				((CButton *)GetDlgItem (IDC_DOCKRIGHT))->EnableWindow (TRUE);

	if (m_bDockTop)		((CButton *)GetDlgItem (IDC_DOCKBOTTOM))->EnableWindow (FALSE);
	else				((CButton *)GetDlgItem (IDC_DOCKBOTTOM))->EnableWindow (TRUE);

	if (m_bDockRight)	((CButton *)GetDlgItem (IDC_DOCKLEFT))->EnableWindow (FALSE);
	else				((CButton *)GetDlgItem (IDC_DOCKLEFT))->EnableWindow (TRUE);

	if (m_bDockBottom)	((CButton *)GetDlgItem (IDC_DOCKTOP))->EnableWindow (FALSE);
	else				((CButton *)GetDlgItem (IDC_DOCKTOP))->EnableWindow (TRUE);
}


BOOL CDlgOptionsNewNote::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();

// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (115, _T("Position of new notes")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (116, _T("Your screen")));
	((CStatic *)GetDlgItem (IDC_STATIC3))->SetWindowText (CTranslate::ReadString (117, _T("From left")));
	((CStatic *)GetDlgItem (IDC_STATIC4))->SetWindowText (CTranslate::ReadString (118, _T("From top")));
	((CStatic *)GetDlgItem (IDC_STATIC5))->SetWindowText (CTranslate::ReadString (119, _T("Width")));
	((CButton *)GetDlgItem (IDC_DOCKLEFT))->SetWindowText (CTranslate::ReadString (120, _T("Dock left")));
	((CButton *)GetDlgItem (IDC_DOCKTOP))->SetWindowText (CTranslate::ReadString (121, _T("Dock top")));
	((CButton *)GetDlgItem (IDC_DOCKRIGHT))->SetWindowText (CTranslate::ReadString (122, _T("Dock right")));
	((CButton *)GetDlgItem (IDC_DOCKBOTTOM))->SetWindowText (CTranslate::ReadString (123, _T("Dock bottom")));



// Make some of the controls grey
	if (m_bDockLeft)	((CButton *)GetDlgItem (IDC_DOCKRIGHT))->EnableWindow (FALSE);
	else				((CButton *)GetDlgItem (IDC_DOCKRIGHT))->EnableWindow (TRUE);

	if (m_bDockTop)		((CButton *)GetDlgItem (IDC_DOCKBOTTOM))->EnableWindow (FALSE);
	else				((CButton *)GetDlgItem (IDC_DOCKBOTTOM))->EnableWindow (TRUE);

	if (m_bDockRight)	((CButton *)GetDlgItem (IDC_DOCKLEFT))->EnableWindow (FALSE);
	else				((CButton *)GetDlgItem (IDC_DOCKLEFT))->EnableWindow (TRUE);

	if (m_bDockBottom)	((CButton *)GetDlgItem (IDC_DOCKTOP))->EnableWindow (FALSE);
	else				((CButton *)GetDlgItem (IDC_DOCKTOP))->EnableWindow (TRUE);
	
	return TRUE;
}

