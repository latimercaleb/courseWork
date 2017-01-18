#if !defined(AFX_DLGSNOOZE_H__F625AF8C_5B2D_48E2_B701_4BDF2174BD8C__INCLUDED_)
#define AFX_DLGSNOOZE_H__F625AF8C_5B2D_48E2_B701_4BDF2174BD8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSnooze.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSnooze dialog

class CDlgSnooze : public CDialog
{
// Construction
public:
	CDlgSnooze(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSnooze)
	enum { IDD = IDD_SNOOZE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSnooze)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSnooze)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSNOOZE_H__F625AF8C_5B2D_48E2_B701_4BDF2174BD8C__INCLUDED_)
