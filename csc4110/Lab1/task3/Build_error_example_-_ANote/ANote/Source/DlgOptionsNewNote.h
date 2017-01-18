#if !defined(AFX_DLGOPTIONSNEWNOTE_H__FFA9E757_019D_407C_B8B0_D5134EA27AFD__INCLUDED_)
#define AFX_DLGOPTIONSNEWNOTE_H__FFA9E757_019D_407C_B8B0_D5134EA27AFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsNewNote.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsNewNote dialog
#include "SAPrefsSubDlg.h"

class CDlgOptionsNewNote : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsNewNote(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsNewNote)
	enum { IDD = IDD_OPTIONSNEWNOTE };
	BOOL	m_bDockBottom;
	BOOL	m_bDockLeft;
	BOOL	m_bDockRight;
	BOOL	m_bDockTop;
	CString	m_szLeft;
	CString	m_szTop;
	CString	m_szWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsNewNote)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsNewNote)
	afx_msg void OnPaint();
	afx_msg void OnDockClick();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSNEWNOTE_H__FFA9E757_019D_407C_B8B0_D5134EA27AFD__INCLUDED_)
