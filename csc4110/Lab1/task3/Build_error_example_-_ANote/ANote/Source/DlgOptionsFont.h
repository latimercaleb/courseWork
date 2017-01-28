#if !defined(AFX_DLGOPTIONSFONT_H__64CF7D1B_633C_4CD3_9496_A7806C1D73B1__INCLUDED_)
#define AFX_DLGOPTIONSFONT_H__64CF7D1B_633C_4CD3_9496_A7806C1D73B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsFont.h : header file
//
#include "SAPrefsSubDlg.h"
#include "AutoRichEditCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsFont dialog

class CDlgOptionsFont : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsFont(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsFont)
	enum { IDD = IDD_OPTIONSFONT };
	//}}AFX_DATA



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsFont)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsFont)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangefont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CAutoRichEditCtrl m_pText;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSFONT_H__64CF7D1B_633C_4CD3_9496_A7806C1D73B1__INCLUDED_)
