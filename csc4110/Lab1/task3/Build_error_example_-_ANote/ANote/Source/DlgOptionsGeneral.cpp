// DlgOptionsGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgOptionsGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsGeneral dialog


CDlgOptionsGeneral::CDlgOptionsGeneral(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsGeneral)

	m_szDefaultTitle = _T("");
	m_bWarnOnDelete = FALSE;
	m_bVersionCheck = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsGeneral::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsGeneral)
	DDX_Text(pDX, IDC_DEFAULTTITLE, m_szDefaultTitle);
	DDX_Check(pDX, IDC_WARNONDELETE, m_bWarnOnDelete);
	DDX_Check(pDX, IDC_VERSIONCHECK, m_bVersionCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsGeneral, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsGeneral)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsGeneral message handlers

BOOL CDlgOptionsGeneral::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();

// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (93, _T("Creation")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	szTemp.Format (_T(" %s "), CTranslate::ReadString (94, _T("Delete")));
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (szTemp);
	szTemp.Format (_T(" %s "), CTranslate::ReadString (95, _T("Version check")));
	((CStatic *)GetDlgItem (IDC_STATIC3))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC4))->SetWindowText (CTranslate::ReadString (96, _T("Use %time% for the current time and %date% for the current date")));
	((CStatic *)GetDlgItem (IDC_STATIC5))->SetWindowText (CTranslate::ReadString (97, _T("Default title")));
	((CButton *)GetDlgItem (IDC_WARNONDELETE))->SetWindowText (CTranslate::ReadString (98, _T("Warn when deleting a note")));
	((CButton *)GetDlgItem (IDC_VERSIONCHECK))->SetWindowText (CTranslate::ReadString (99, _T("See if there are any newer versions of the program")));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
