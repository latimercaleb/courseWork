#if !defined(AFX_DLGUSEUSERINFORMATION_H__81B746FB_E7BC_4711_B46C_D2B10200146F__INCLUDED_)
#define AFX_DLGUSEUSERINFORMATION_H__81B746FB_E7BC_4711_B46C_D2B10200146F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUseUserInformation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUseUserInformation dialog

class CDlgUseUserInformation : public CDialog
{
// Construction
public:
	CDlgUseUserInformation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUseUserInformation)
	enum { IDD = IDD_USEUSERINFORMATION };
	CString	m_szUserName;
	CString	m_szPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUseUserInformation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUseUserInformation)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSEUSERINFORMATION_H__81B746FB_E7BC_4711_B46C_D2B10200146F__INCLUDED_)
