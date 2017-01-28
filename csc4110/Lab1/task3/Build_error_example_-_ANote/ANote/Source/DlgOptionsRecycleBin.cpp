// DlgOptionsRecycleBin.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgOptionsRecycleBin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsRecycleBin dialog


CDlgOptionsRecycleBin::CDlgOptionsRecycleBin(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsRecycleBin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsRecycleBin)
	m_szNumberOfNotes = _T("");
	m_bSortDescending = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsRecycleBin::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsRecycleBin)
	DDX_Text(pDX, IDC_NUMBEROFDELETEDNOTES, m_szNumberOfNotes);
	DDX_Check(pDX, IDC_SORTDESCENDING, m_bSortDescending);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsRecycleBin, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsRecycleBin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsRecycleBin message handlers

BOOL CDlgOptionsRecycleBin::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (124, _T("Recycle bin")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (125, _T("Maximum deleted notes that will be saved (0 for infinitive)")));
	((CButton *)GetDlgItem (IDC_SORTDESCENDING))->SetWindowText (CTranslate::ReadString (126, _T("Sort the notes descending")));


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
