

// DlgOptionsUnicode.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgOptionsCharset.h"


// CDlgOptionsUnicode dialog

IMPLEMENT_DYNAMIC(CDlgOptionsCharset, CSAPrefsSubDlg)
CDlgOptionsCharset::CDlgOptionsCharset(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsCharset::IDD, pParent)
{
}

CDlgOptionsCharset::~CDlgOptionsCharset()
{
}

void CDlgOptionsCharset::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARSET, m_pCharset);
}


BEGIN_MESSAGE_MAP(CDlgOptionsCharset, CSAPrefsSubDlg)
	ON_CBN_SELCHANGE(IDC_CHARSET, OnCbnSelchangeCharset)
END_MESSAGE_MAP()


// CDlgOptionsUnicode message handlers

BOOL CDlgOptionsCharset::OnInitDialog()
{
	CSAPrefsSubDlg::OnInitDialog();

// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (195, _T("Charset")));
	((CStatic *) GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *) GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (195, _T("Charset")));

// Fill the combobox with different charset
	m_pCharset.AddString (_T("ANSI_CHARSET"));
	m_pCharset.AddString (_T("DEFAULT_CHARSET"));
	m_pCharset.AddString (_T("SYMBOL_CHARSET"));
	m_pCharset.AddString (_T("SHIFTJIS_CHARSET"));
	m_pCharset.AddString (_T("HANGEUL_CHARSET"));
	m_pCharset.AddString (_T("HANGUL_CHARSET"));
	m_pCharset.AddString (_T("GB2312_CHARSET"));
	m_pCharset.AddString (_T("CHINESEBIG5_CHARSET"));
	m_pCharset.AddString (_T("OEM_CHARSET"));
	m_pCharset.AddString (_T("JOHAB_CHARSET"));
	m_pCharset.AddString (_T("HEBREW_CHARSET"));
	m_pCharset.AddString (_T("ARABIC_CHARSET"));
	m_pCharset.AddString (_T("GREEK_CHARSET"));
	m_pCharset.AddString (_T("TURKISH_CHARSET"));
	m_pCharset.AddString (_T("VIETNAMESE_CHARSET"));
	m_pCharset.AddString (_T("THAI_CHARSET"));
	m_pCharset.AddString (_T("EASTEUROPE_CHARSET"));
	m_pCharset.AddString (_T("RUSSIAN_CHARSET"));
	m_pCharset.AddString (_T("BALTIC_CHARSET"));

	m_pCharset.SetItemHeight (0, 17);

// Select the charset wer are using
	m_pCharset.SelectString (0, m_szCharsetName);

// Change the font
	LOGFONT lf;                        
	memset(&lf, 0, sizeof(LOGFONT));   
	lf.lfHeight = 15;                  
	lf.lfWeight = FW_EXTRALIGHT; 
	_tcscpy(lf.lfFaceName, _T("Microsoft Sans Serif"));
	m_font.CreateFontIndirect(&lf);    
	m_pCharset.SetFont (&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgOptionsCharset::OnCbnSelchangeCharset()
{
// Remember the ini-file the user has selected
	int iIndex = m_pCharset.GetCurSel ();
	m_pCharset.GetLBText (iIndex, m_szCharsetName);

// Find the value of the name and save it
	if (m_szCharsetName == _T("ANSI_CHARSET"))			m_iCharset = ANSI_CHARSET;
	if (m_szCharsetName == _T("DEFAULT_CHARSET"))		m_iCharset = DEFAULT_CHARSET;
	if (m_szCharsetName == _T("SYMBOL_CHARSET"))		m_iCharset = SYMBOL_CHARSET;
	if (m_szCharsetName == _T("SHIFTJIS_CHARSET"))		m_iCharset = SHIFTJIS_CHARSET;
	if (m_szCharsetName == _T("HANGEUL_CHARSET"))		m_iCharset = HANGEUL_CHARSET;
	if (m_szCharsetName == _T("HANGUL_CHARSET"))		m_iCharset = HANGUL_CHARSET;
	if (m_szCharsetName == _T("GB2312_CHARSET"))		m_iCharset = GB2312_CHARSET;
	if (m_szCharsetName == _T("CHINESEBIG5_CHARSET"))	m_iCharset = CHINESEBIG5_CHARSET;
	if (m_szCharsetName == _T("OEM_CHARSET"))			m_iCharset = OEM_CHARSET;
	if (m_szCharsetName == _T("JOHAB_CHARSET"))			m_iCharset = JOHAB_CHARSET;
	if (m_szCharsetName == _T("HEBREW_CHARSET"))		m_iCharset = HEBREW_CHARSET;
	if (m_szCharsetName == _T("ARABIC_CHARSET"))		m_iCharset = ARABIC_CHARSET;
	if (m_szCharsetName == _T("GREEK_CHARSET"))			m_iCharset = GREEK_CHARSET;
	if (m_szCharsetName == _T("TURKISH_CHARSET"))		m_iCharset = TURKISH_CHARSET;
	if (m_szCharsetName == _T("VIETNAMESE_CHARSET"))	m_iCharset = VIETNAMESE_CHARSET;
	if (m_szCharsetName == _T("THAI_CHARSET"))			m_iCharset = THAI_CHARSET;
	if (m_szCharsetName == _T("EASTEUROPE_CHARSET"))	m_iCharset = EASTEUROPE_CHARSET;
	if (m_szCharsetName == _T("RUSSIAN_CHARSET"))		m_iCharset = RUSSIAN_CHARSET;
	if (m_szCharsetName == _T("BALTIC_CHARSET"))		m_iCharset = BALTIC_CHARSET;
}

