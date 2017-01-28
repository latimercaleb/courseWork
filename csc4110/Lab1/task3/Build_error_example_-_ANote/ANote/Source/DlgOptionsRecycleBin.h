#if !defined(AFX_DLGOPTIONSRECYCLEBIN_H__5F7C6EA3_B4CE_45F5_B9EF_B20E0BC64A67__INCLUDED_)
#define AFX_DLGOPTIONSRECYCLEBIN_H__5F7C6EA3_B4CE_45F5_B9EF_B20E0BC64A67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsRecycleBin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsRecycleBin dialog
#include "SAPrefsSubDlg.h"
class CDlgOptionsRecycleBin : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsRecycleBin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsRecycleBin)
	enum { IDD = IDD_OPTIONSRECYCLEBIN };
	CString	m_szNumberOfNotes;
	BOOL	m_bSortDescending;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsRecycleBin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsRecycleBin)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSRECYCLEBIN_H__5F7C6EA3_B4CE_45F5_B9EF_B20E0BC64A67__INCLUDED_)
