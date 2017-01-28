#if !defined(AFX_DLGCREATENEWLANGUAGE_H__01706D6D_83A2_4491_B0FA_68D46A0A7294__INCLUDED_)
#define AFX_DLGCREATENEWLANGUAGE_H__01706D6D_83A2_4491_B0FA_68D46A0A7294__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCreateNewLanguage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateNewLanguage dialog

class CDlgCreateNewLanguage : public CDialog
{
// Construction
public:
	CDlgCreateNewLanguage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCreateNewLanguage)
	enum { IDD = IDD_CREATENEWLANGUAGE };
	CString	m_szIniFile;
	CString	m_szEnglishName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateNewLanguage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCreateNewLanguage)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATENEWLANGUAGE_H__01706D6D_83A2_4491_B0FA_68D46A0A7294__INCLUDED_)
