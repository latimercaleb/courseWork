#if !defined(AFX_DLGUSERINFORMATION_H__A7263952_DE55_417C_9B00_86C2C17A9A8F__INCLUDED_)
#define AFX_DLGUSERINFORMATION_H__A7263952_DE55_417C_9B00_86C2C17A9A8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUserInformation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUserInformation dialog

class CDlgUserInformation : public CDialog
{
// Construction
public:
	CDlgUserInformation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUserInformation)
	enum { IDD = IDD_USERINFORMATION };
	CString	m_szUserName;
	CString	m_szPassword;
	CString	m_szEmail;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUserInformation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUserInformation)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSERINFORMATION_H__A7263952_DE55_417C_9B00_86C2C17A9A8F__INCLUDED_)
