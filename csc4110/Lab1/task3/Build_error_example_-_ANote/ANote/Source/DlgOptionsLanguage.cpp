// DlgOptionsLanguage.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgOptionsLanguage.h"
#include "DlgLanguage.h"
#include "DlgCreateNewLanguage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsLanguage dialog


CDlgOptionsLanguage::CDlgOptionsLanguage(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsLanguage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsLanguage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOptionsLanguage::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsLanguage)
	DDX_Control(pDX, IDC_LANGUAGE, m_pLanguage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsLanguage, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsLanguage)
	ON_CBN_SELCHANGE(IDC_LANGUAGE, OnSelchangeLanguage)
	ON_BN_CLICKED(IDC_EDITLANGUAGE, OnEditlanguage)
	ON_BN_CLICKED(IDC_ADDLANGUAGE, OnAddlanguage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsLanguage message handlers

BOOL CDlgOptionsLanguage::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();

// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (50, _T("Language")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (51, _T("Select language")));
	((CButton *)GetDlgItem (IDC_EDITLANGUAGE))->SetWindowText (CTranslate::ReadString (52, _T("Edit language...")));
	((CButton *)GetDlgItem (IDC_ADDLANGUAGE))->SetWindowText (CTranslate::ReadString (53, _T("Add language...")));


// Fill the combobox with languages
	HANDLE hSearch;
	WIN32_FIND_DATA FileData; 
	bool bDone;
	CString szPath;
	szPath = GetProgramPath ();
	hSearch = FindFirstFile(szPath + _T("\\Language\\*.ini"), &FileData);
	if (hSearch == INVALID_HANDLE_VALUE) 
		bDone = TRUE;
	else 
		bDone = FALSE;

	while (bDone == FALSE)	{
		m_pLanguage.AddString (FileData.cFileName);		
		

		if (!FindNextFile(hSearch, &FileData)) 
			bDone = TRUE; 
	}

	FindClose (hSearch);
	m_pLanguage.SetItemHeight (0, 17);

// Select the language we are using (by default, English.ini)
	m_pLanguage.SelectString (0, m_szLanguageIni);

// Change the font
	LOGFONT lf;                        
	memset(&lf, 0, sizeof(LOGFONT));   
	lf.lfHeight = 15;                  
	lf.lfWeight = FW_EXTRALIGHT; 
	_tcscpy(lf.lfFaceName, _T("Microsoft Sans Serif"));
	m_font.CreateFontIndirect(&lf);    
	m_pLanguage.SetFont (&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOptionsLanguage::OnSelchangeLanguage() 
{
// Remember the ini-file the user has selected
	int iIndex = m_pLanguage.GetCurSel ();
	m_pLanguage.GetLBText (iIndex, m_szLanguageIni);
}

void CDlgOptionsLanguage::OnEditlanguage() 
{
	CDlgLanguage dlg;
	dlg.DoModal ();
}

void CDlgOptionsLanguage::OnAddlanguage() 
{
// Let the user enter the new language
	CDlgCreateNewLanguage d;
	if (d.DoModal () == IDCANCEL)
		return;

	CDlgLanguage dlg;
	dlg.m_szLanguageIni = d.m_szIniFile;
	dlg.DoModal ();

// We have created a new ini-file. Make sure that exist in the combobox
	m_pLanguage.AddString (d.m_szIniFile + _T(".ini"));		
}
