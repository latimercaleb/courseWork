#if !defined(AFX_DLGOPTIONSGENERAL_H__CC2C2F28_FAEA_46E2_A983_F44A13E2F46D__INCLUDED_)
#define AFX_DLGOPTIONSGENERAL_H__CC2C2F28_FAEA_46E2_A983_F44A13E2F46D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsGeneral dialog
#include "SAPrefsSubDlg.h"

class CDlgOptionsGeneral : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsGeneral(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsGeneral)
	enum { IDD = IDD_OPTIONSGENERAL };
	CString	m_szDefaultTitle;
	BOOL	m_bWarnOnDelete;
	BOOL	m_bVersionCheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsGeneral)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSGENERAL_H__CC2C2F28_FAEA_46E2_A983_F44A13E2F46D__INCLUDED_)
