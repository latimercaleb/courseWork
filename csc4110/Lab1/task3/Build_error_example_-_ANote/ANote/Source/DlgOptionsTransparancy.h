#if !defined(AFX_DLGOPTIONSTRANSPARANCY_H__C3AC2171_F7C7_4886_8E96_E709369D0DFA__INCLUDED_)
#define AFX_DLGOPTIONSTRANSPARANCY_H__C3AC2171_F7C7_4886_8E96_E709369D0DFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsTransparancy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsTransparancy dialog
#include "SAPrefsSubDlg.h"

class CDlgOptionsTransparancy : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsTransparancy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsTransparancy)
	enum { IDD = IDD_OPTIONSTRANSPARANCY };
	int		m_iTransparantNormal;
	int		m_iTransparantMinimized;
	CSliderCtrl	m_pTransparancyNormal;
	CSliderCtrl	m_pTransparancyMinimized;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsTransparancy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsTransparancy)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSTRANSPARANCY_H__C3AC2171_F7C7_4886_8E96_E709369D0DFA__INCLUDED_)
