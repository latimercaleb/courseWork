#if !defined(AFX_DLGGUIDE_H__809F33D4_D831_487A_BAB0_20CE13143B5B__INCLUDED_)
#define AFX_DLGGUIDE_H__809F33D4_D831_487A_BAB0_20CE13143B5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGuide.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGuide dialog
#include "picture.h"

class CDlgGuide : public CDialog
{
// Construction
public:
	CDlgGuide(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGuide)
	enum { IDD = IDD_DLGGUIDE };
	BOOL	m_bDontShowAgain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGuide)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGuide)
	afx_msg void OnNext();
	afx_msg void OnPrevious();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFinish();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int			m_iPage;				// What page are we at
	CPicture	m_pImage;				// The image 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGUIDE_H__809F33D4_D831_487A_BAB0_20CE13143B5B__INCLUDED_)
