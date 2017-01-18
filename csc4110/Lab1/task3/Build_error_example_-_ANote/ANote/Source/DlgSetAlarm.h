#if !defined(AFX_DLGSETALARM_H__F72ABFE0_95AD_4FAF_8076_BC67878D0E06__INCLUDED_)
#define AFX_DLGSETALARM_H__F72ABFE0_95AD_4FAF_8076_BC67878D0E06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgSetAlarm : public CDialog
{

public:
	CDlgSetAlarm(CWnd* pParent = NULL);   

	//{{AFX_DATA(CDlgSetAlarm)
	enum { IDD = IDD_SETALARM };
	CMonthCalCtrl	m_pDate;
	BOOL	m_bUseAlarm;
	COleDateTime	m_pTime;
	//}}AFX_DATA

	COleDateTime m_Time;


	//{{AFX_VIRTUAL(CDlgSetAlarm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	//}}AFX_VIRTUAL

	void FillComboBox ();

	//{{AFX_MSG(CDlgSetAlarm)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnUsealarm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
