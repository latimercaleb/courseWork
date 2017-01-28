#if !defined(AFX_DLGOPTIONSLOOKS_H__CAB1C8BB_6932_42A8_BC8A_7C394DB597DE__INCLUDED_)
#define AFX_DLGOPTIONSLOOKS_H__CAB1C8BB_6932_42A8_BC8A_7C394DB597DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsLooks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsLooks dialog
#include "SAPrefsSubDlg.h"

class CDlgOptionsLooks : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsLooks(CWnd* pParent = NULL);   // standard constructor
	COLORREF m_cfColor;

// Dialog Data
	//{{AFX_DATA(CDlgOptionsLooks)
	enum { IDD = IDD_OPTIONSLOOKS };
	BOOL	m_bRndColor;
	BOOL	m_bThinBorder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsLooks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsLooks)
	afx_msg void OnPaint();
	afx_msg void OnChangenotecolor();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSLOOKS_H__CAB1C8BB_6932_42A8_BC8A_7C394DB597DE__INCLUDED_)
