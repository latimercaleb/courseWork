// DlgOptionsHotKey.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgOptionsHotKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsHotKey dialog


CDlgOptionsHotKey::CDlgOptionsHotKey(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsHotKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsHotKey)
	m_bAlt = FALSE;
	m_bCtrl = FALSE;
	m_bShift = FALSE;
	m_bWin = FALSE;
	m_bUseHotKey = FALSE;
	m_iCharacter = 0;
	//}}AFX_DATA_INIT
}


void CDlgOptionsHotKey::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsHotKey)
	DDX_Control(pDX, IDC_CHARACTER, m_pCharacter);
	DDX_Check(pDX, IDC_ALT, m_bAlt);
	DDX_Check(pDX, IDC_CTRL, m_bCtrl);
	DDX_Check(pDX, IDC_SHIFT, m_bShift);
	DDX_Check(pDX, IDC_WIN, m_bWin);
	DDX_Check(pDX, IDC_USEHOTKEY, m_bUseHotKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsHotKey, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsHotKey)
	ON_BN_CLICKED(IDC_USEHOTKEY, OnUsehotkey)
	ON_BN_CLICKED(IDC_SETHOTKEY, OnSethotkey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsHotKey message handlers

BOOL CDlgOptionsHotKey::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (100, _T("Hot key")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	szTemp.Format (_T(" %s "), CTranslate::ReadString (101, _T("Character")));
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (szTemp);
	((CButton *)GetDlgItem (IDC_SHIFT))->SetWindowText (CTranslate::ReadString (102, _T("SHIFT")));
	((CButton *)GetDlgItem (IDC_WIN))->SetWindowText (CTranslate::ReadString (103, _T("WIN")));
	((CButton *)GetDlgItem (IDC_ALT))->SetWindowText (CTranslate::ReadString (104, _T("ALT")));
	((CButton *)GetDlgItem (IDC_CTRL))->SetWindowText (CTranslate::ReadString (105, _T("CTRL")));
	((CButton *)GetDlgItem (IDC_USEHOTKEY))->SetWindowText (CTranslate::ReadString (106, _T("Use hot key")));
	((CButton *)GetDlgItem (IDC_SETHOTKEY))->SetWindowText (CTranslate::ReadString (109, _T("Set hot key")));
	

// Set the combobox to the default value
	int iIndex = m_iCharacter;
	m_pCharacter.GetLBText (iIndex, szTemp);
	m_pCharacter.SelectString (0, szTemp);

// Set the controls to the right statement
	OnUsehotkey ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOptionsHotKey::OnUsehotkey() 
{
	UpdateData ();
	

	((CButton *)GetDlgItem (IDC_SHIFT))->EnableWindow		(m_bUseHotKey ? TRUE : FALSE);
	((CButton *)GetDlgItem (IDC_ALT))->EnableWindow			(m_bUseHotKey ? TRUE : FALSE);
	((CButton *)GetDlgItem (IDC_CTRL))->EnableWindow		(m_bUseHotKey ? TRUE : FALSE);
	((CButton *)GetDlgItem (IDC_WIN))->EnableWindow			(m_bUseHotKey ? TRUE : FALSE);
	((CButton *)GetDlgItem (IDC_CHARACTER))->EnableWindow	(m_bUseHotKey ? TRUE : FALSE);
	((CButton *)GetDlgItem (IDC_SETHOTKEY))->EnableWindow	(m_bUseHotKey ? TRUE : FALSE);
}

void CDlgOptionsHotKey::OnSethotkey() 
{
	UpdateData ();	


// Try to set the hot key
	m_iCharacter = m_pCharacter.GetCurSel ();

	UINT iModifiers = 0;
	theApp.m_iHotKeyID = GlobalAddAtom(_T("A Note"));

	if (m_bCtrl)	iModifiers += MOD_CONTROL;
	if (m_bShift)	iModifiers += MOD_SHIFT;
	if (m_bAlt)		iModifiers += MOD_ALT;
	if (m_bWin)		iModifiers += MOD_WIN;
		

	CMainFrame *pMain = (CMainFrame*) ::AfxGetMainWnd ();
	if(::RegisterHotKey(pMain->GetSafeHwnd(), theApp.m_iHotKeyID, iModifiers, 65 + m_iCharacter))	
		((CButton *)GetDlgItem (IDC_STATUSTEXT))->SetWindowText (CTranslate::ReadString (107, _T("The hot key was set...")));
	else
		((CButton *)GetDlgItem (IDC_STATUSTEXT))->SetWindowText (CTranslate::ReadString (108, _T("The combination could not be set")));


// Show if it worked or not

}
