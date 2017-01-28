// DlgCreateNewLanguage.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgCreateNewLanguage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateNewLanguage dialog


CDlgCreateNewLanguage::CDlgCreateNewLanguage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateNewLanguage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCreateNewLanguage)
	m_szIniFile = _T("");
	m_szEnglishName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCreateNewLanguage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateNewLanguage)
	DDX_Text(pDX, IDC_INIFILE, m_szIniFile);
	DDX_Text(pDX, IDC_ENGLISHNAME, m_szEnglishName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateNewLanguage, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateNewLanguage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateNewLanguage message handlers

void CDlgCreateNewLanguage::OnOK() 
{
	UpdateData ();

// Check so the fields are note empty
	if (m_szIniFile.IsEmpty () || m_szEnglishName.IsEmpty ())	{
		AfxMessageBox (CTranslate::ReadString (192, "You must enter both a language you want to create and the english name for it"));
		return;
	}

// Create the ini-file
	CString szFile, m_szIni;
	m_szIni = m_szIniFile;
	m_szIniFile = m_szIni + ".ini";

	szFile.Format (_T("%s\\Language\\%s"), GetProgramPath (), m_szIniFile);

// Write the language in the ini-file
	WritePrivateProfileString(_T("LANGUAGE"), _T("LANGUAGE"), m_szEnglishName, szFile);

	UpdateData (FALSE);

	CDialog::OnOK();
}

BOOL CDlgCreateNewLanguage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// Language stuff
	((CStatic *) GetDlgItem (IDC_STATIC1))->SetWindowText (CTranslate::ReadString (186, "Enter the language you want to create"));
	((CStatic *) GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (191, "Enter the english name for the language"));
	((CButton *) GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (36, "OK"));
	((CButton *) GetDlgItem (IDCANCEL))->SetWindowText (CTranslate::ReadString (37, "Cancel"));

	SetWindowText (CTranslate::ReadString (187, "Add a new language"));


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
