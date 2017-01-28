#pragma once
#include "afxwin.h"


// CDlgOptionsUnicode dialog
#include "SAPrefsSubDlg.h"

class CDlgOptionsCharset : public CSAPrefsSubDlg
{
	DECLARE_DYNAMIC(CDlgOptionsCharset)

public:
	CDlgOptionsCharset(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOptionsCharset();

// Dialog Data
	enum { IDD = IDD_OPTIONSCHARSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_pCharset;
	CString m_szCharsetName;
	int m_iCharset;
	virtual BOOL OnInitDialog();

private:
	CFont m_font;
public:
	afx_msg void OnCbnSelchangeCharset();
};
