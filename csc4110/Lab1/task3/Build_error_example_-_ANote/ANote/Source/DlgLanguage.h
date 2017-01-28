#if !defined(AFX_DLGLANGUAGE_H__14363E61_EA8A_4536_9D36_6C0CB894FD7B__INCLUDED_)
#define AFX_DLGLANGUAGE_H__14363E61_EA8A_4536_9D36_6C0CB894FD7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLanguage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLanguage dialog

class CDlgLanguage : public CDialog
{
// Construction
public:
	CDlgLanguage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLanguage)
	enum { IDD = IDD_LANGUAGE };
	CComboBox	m_pLanguage;
	CListCtrl	m_pEnglish;
	CString	m_szOtherLanguage;
	//}}AFX_DATA

	CString m_szLanguageIni; // The selected ini-file
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLanguage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EmailIniFiles ();

	// Generated message map functions
	//{{AFX_MSG(CDlgLanguage)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickEnglish(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeOtherlanguage();
	afx_msg void OnKillfocusOtherlanguage();
	afx_msg void OnSelchangeLanguage();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_iRow;		// Which row has the user pressed?
	bool m_bChanged; // We have updated a new word
	bool m_bAskToSave; // We have updated the ini-file. Ask the user if the ini-files should be sent via email
	CFont			m_font;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLANGUAGE_H__14363E61_EA8A_4536_9D36_6C0CB894FD7B__INCLUDED_)
