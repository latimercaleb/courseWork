#include "afxcmn.h"
#if !defined(AFX_DLGSETTITLE_H__CB741D70_D913_4B30_9B90_683E6AD77965__INCLUDED_)
#define AFX_DLGSETTITLE_H__CB741D70_D913_4B30_9B90_683E6AD77965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetTitle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetTitle dialog

class CDlgSetTitle : public CDialog
{
// Construction
public:
	CDlgSetTitle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetTitle)
	enum { IDD = IDD_SETTITLE };
	CString	m_szTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetTitle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetTitle)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_pTitle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTITLE_H__CB741D70_D913_4B30_9B90_683E6AD77965__INCLUDED_)
