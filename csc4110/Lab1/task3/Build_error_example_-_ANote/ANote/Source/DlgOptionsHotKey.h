#if !defined(AFX_DLGOPTIONSHOTKEY_H__6A52FE17_942A_4437_95E0_D12D3602515D__INCLUDED_)
#define AFX_DLGOPTIONSHOTKEY_H__6A52FE17_942A_4437_95E0_D12D3602515D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsHotKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsHotKey dialog
#include "SAPrefsSubDlg.h"
class CDlgOptionsHotKey : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsHotKey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsHotKey)
	enum { IDD = IDD_OPTIONSHOTKEY };
	CComboBox	m_pCharacter;
	BOOL	m_bAlt;
	BOOL	m_bCtrl;
	BOOL	m_bShift;
	BOOL	m_bWin;
	BOOL	m_bUseHotKey;
	int		m_iCharacter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsHotKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsHotKey)
	virtual BOOL OnInitDialog();
	afx_msg void OnUsehotkey();
	afx_msg void OnSethotkey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSHOTKEY_H__6A52FE17_942A_4437_95E0_D12D3602515D__INCLUDED_)
