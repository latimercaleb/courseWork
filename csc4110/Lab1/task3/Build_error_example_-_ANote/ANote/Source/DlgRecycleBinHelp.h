#if !defined(AFX_DLGRECYCLEBINHELP_H__D0793756_A227_40D8_BEA2_C7BFD1CFC722__INCLUDED_)
#define AFX_DLGRECYCLEBINHELP_H__D0793756_A227_40D8_BEA2_C7BFD1CFC722__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecycleBinHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecycleBinHelp dialog

class CDlgRecycleBinHelp : public CDialog
{
// Construction
public:
	CDlgRecycleBinHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecycleBinHelp)
	enum { IDD = IDD_RECYCLEBINHELP };
	BOOL	m_bShowNextTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecycleBinHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecycleBinHelp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECYCLEBINHELP_H__D0793756_A227_40D8_BEA2_C7BFD1CFC722__INCLUDED_)
