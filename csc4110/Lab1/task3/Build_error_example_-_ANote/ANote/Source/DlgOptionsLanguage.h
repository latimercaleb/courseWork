#if !defined(AFX_DLGOPTIONSLANGUAGE_H__4D7D224A_F115_473D_A693_5B759964F5E2__INCLUDED_)
#define AFX_DLGOPTIONSLANGUAGE_H__4D7D224A_F115_473D_A693_5B759964F5E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsLanguage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsLanguage dialog
#include "SAPrefsSubDlg.h"
class CDlgOptionsLanguage : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsLanguage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsLanguage)
	enum { IDD = IDD_OPTIONSLANGUAGE };
	CComboBox	m_pLanguage;
	//}}AFX_DATA

	CString m_szLanguageIni;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsLanguage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsLanguage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLanguage();
	afx_msg void OnEditlanguage();
	afx_msg void OnAddlanguage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CFont			m_font;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSLANGUAGE_H__4D7D224A_F115_473D_A693_5B759964F5E2__INCLUDED_)
