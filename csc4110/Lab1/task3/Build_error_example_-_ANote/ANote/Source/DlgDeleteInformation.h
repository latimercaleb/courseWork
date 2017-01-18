#if !defined(AFX_DLGDELETEINFORMATION_H__E57FAC20_3284_4973_AC2D_C654040D952C__INCLUDED_)
#define AFX_DLGDELETEINFORMATION_H__E57FAC20_3284_4973_AC2D_C654040D952C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeleteInformation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeleteInformation dialog

class CDlgDeleteInformation : public CDialog
{
// Construction
public:
	CDlgDeleteInformation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDeleteInformation)
	enum { IDD = IDD_DELETEINFORMATION };
	BOOL	m_bShowAgain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeleteInformation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeleteInformation)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDELETEINFORMATION_H__E57FAC20_3284_4973_AC2D_C654040D952C__INCLUDED_)
