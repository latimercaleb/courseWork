#if !defined(AFX_DLGOPTIONSBEHAVIOUR_H__95AE4DFB_FDD6_4A1E_A9FA_D9807FBABB6B__INCLUDED_)
#define AFX_DLGOPTIONSBEHAVIOUR_H__95AE4DFB_FDD6_4A1E_A9FA_D9807FBABB6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsBehaviour.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsBehaviour dialog
#include "SAPrefsSubDlg.h"

class CDlgOptionsBehaviour : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsBehaviour(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsBehaviour)
	enum { IDD = IDD_OPTIONSBEHAVIOUR };
	BOOL	m_bHideOnMinimize;
	BOOL	m_bDockable;
	BOOL	m_bDoubleClickOnTitlebar;
	BOOL	m_bMinimizeMoveCursor;
	int		m_iClickOnce;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsBehaviour)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsBehaviour)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSBEHAVIOUR_H__95AE4DFB_FDD6_4A1E_A9FA_D9807FBABB6B__INCLUDED_)
