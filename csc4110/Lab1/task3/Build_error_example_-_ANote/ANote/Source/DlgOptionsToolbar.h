#if !defined(AFX_DLGOPTIONSTOOLBAR_H__0CFE5B17_E16C_475D_9B22_2626282AB841__INCLUDED_)
#define AFX_DLGOPTIONSTOOLBAR_H__0CFE5B17_E16C_475D_9B22_2626282AB841__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsToolbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsToolbar dialog
#include "SAPrefsSubDlg.h"

class CDlgOptionsToolbar : public CSAPrefsSubDlg
{
// Construction
public:
	CDlgOptionsToolbar(CWnd* pParent = NULL);   // standard constructor

	int m_iInUseBold;
	int m_iInUseUnderline;
	int m_iInUseItalic;
	int m_iInUseBullet;
	int m_iInUseSlideLeft;
	int m_iInUseSlideRight;
	int m_iInUseMinimize;
	int m_iInUseStrikeOut;


	int	m_iButtonWidth;
// Dialog Data
	//{{AFX_DATA(CDlgOptionsToolbar)
	enum { IDD = IDD_OPTIONSTOOLBAR };
	CListCtrl	m_pInUse;
	CListCtrl	m_pAvailable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsToolbar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillListBoxes ();
	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsToolbar)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnDblclkAvailable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkInuse(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CImageList		m_imgIcon;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONSTOOLBAR_H__0CFE5B17_E16C_475D_9B22_2626282AB841__INCLUDED_)
