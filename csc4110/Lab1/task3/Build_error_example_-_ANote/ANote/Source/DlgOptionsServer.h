#if !defined(AFX_DLGOPTIONSSERVER_H__DCCFC7AE_F0F1_4D8A_968B_711065A536AB__INCLUDED_)
#define AFX_DLGOPTIONSSERVER_H__DCCFC7AE_F0F1_4D8A_968B_711065A536AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsServer dialog
#include "SAPrefsSubDlg.h"
class CDlgOptionsServer : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsServer)
	enum { IDD = IDD_OPTIONSSERVER };
	CString	m_szAddress;
	CString	m_szPath;
	CString	m_szPort;
	BOOL	m_bUseDefaultServer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsServer)
	afx_msg void OnUsedefaultserver();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSSERVER_H__DCCFC7AE_F0F1_4D8A_968B_711065A536AB__INCLUDED_)
