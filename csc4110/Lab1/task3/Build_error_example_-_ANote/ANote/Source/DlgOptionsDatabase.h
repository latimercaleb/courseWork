#if !defined(AFX_DLGOPTIONSDATABASE_H__07687D68_EF78_459B_A5D9_9DE4646BA0DA__INCLUDED_)
#define AFX_DLGOPTIONSDATABASE_H__07687D68_EF78_459B_A5D9_9DE4646BA0DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsDatabase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsDatabase dialog
#include "SAPrefsSubDlg.h"

class CDlgOptionsDatabase : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsDatabase(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsDatabase)
	enum { IDD = IDD_OPTIONSDATABASE };
	CString	m_szPassword;
	CString	m_szUserName;
	BOOL	m_bUploadDownload;
	CString	m_szDownloadAfter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsDatabase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsDatabase)
	afx_msg void OnDeletenotes();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSDATABASE_H__07687D68_EF78_459B_A5D9_9DE4646BA0DA__INCLUDED_)
