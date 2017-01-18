// DlgOptionsBehaviour.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgOptionsBehaviour.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsBehaviour dialog


CDlgOptionsBehaviour::CDlgOptionsBehaviour(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsBehaviour::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsBehaviour)
	m_bHideOnMinimize = FALSE;
	m_bDockable = FALSE;
	m_bDoubleClickOnTitlebar = FALSE;
	m_bMinimizeMoveCursor = FALSE;
	m_iClickOnce = -1;
	//}}AFX_DATA_INIT
}


void CDlgOptionsBehaviour::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsBehaviour)
	DDX_Check(pDX, IDC_HIDEONMINIMIZE, m_bHideOnMinimize);
	DDX_Check(pDX, IDC_DOCKABLE, m_bDockable);
	DDX_Check(pDX, IDC_DOUBLECLICKTITLEBAR, m_bDoubleClickOnTitlebar);
	DDX_Check(pDX, IDC_MINIMIZEMOVECURSOR, m_bMinimizeMoveCursor);
	DDX_Radio(pDX, IDC_CLICKONCE, m_iClickOnce);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsBehaviour, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsBehaviour)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsBehaviour message handlers

BOOL CDlgOptionsBehaviour::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (73, _T("Behaviour")));
	((CStatic *)GetDlgItem (IDC_STATIC4))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC3))->SetWindowText (CTranslate::ReadString (74, "What happens when you click once on the tray icon?"));
	((CButton *)GetDlgItem (IDC_CLICKONCE))->SetWindowText (CTranslate::ReadString (75, "Create a new note"));
	((CButton *)GetDlgItem (IDC_RADIO2))->SetWindowText (CTranslate::ReadString (76, "Hide and show the notes"));
	((CButton *)GetDlgItem (IDC_DOUBLECLICKTITLEBAR))->SetWindowText (CTranslate::ReadString (77, "Doubleclick on titlebar -> restore / minimize the note"));
	((CButton *)GetDlgItem (IDC_MINIMIZEMOVECURSOR))->SetWindowText (CTranslate::ReadString (78, "When minimized move the cursor to minimize-button"));
	((CButton *)GetDlgItem (IDC_DOCKABLE))->SetWindowText (CTranslate::ReadString (79, "Dockable"));
	((CButton *)GetDlgItem (IDC_HIDEONMINIMIZE))->SetWindowText (CTranslate::ReadString (80, "When minimized show only the titlebar"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
