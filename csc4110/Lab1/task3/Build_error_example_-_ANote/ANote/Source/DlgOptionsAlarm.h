#if !defined(AFX_DLGOPTIONSALARM_H__1B0EC7C2_ECEA_446F_9343_D03CC83F56DF__INCLUDED_)
#define AFX_DLGOPTIONSALARM_H__1B0EC7C2_ECEA_446F_9343_D03CC83F56DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsAlarm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsAlarm dialog
#include "SAPrefsSubDlg.h"

class CDlgOptionsAlarm : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsAlarm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsAlarm)
	enum { IDD = IDD_OPTIONSALARM };
	BOOL	m_bBlink;
	BOOL	m_bPlaySound;
	CString	m_szSoundFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsAlarm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsAlarm)
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSALARM_H__1B0EC7C2_ECEA_446F_9343_D03CC83F56DF__INCLUDED_)
