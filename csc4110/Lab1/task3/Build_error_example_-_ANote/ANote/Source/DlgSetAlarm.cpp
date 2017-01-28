// DlgSetAlarm.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgSetAlarm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetAlarm dialog


CDlgSetAlarm::CDlgSetAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetAlarm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetAlarm)
	m_bUseAlarm = FALSE;
	m_pTime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CDlgSetAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetAlarm)
	DDX_Control(pDX, IDC_DATE, m_pDate);
	DDX_Check(pDX, IDC_USEALARM, m_bUseAlarm);
	DDX_DateTimeCtrl(pDX, IDC_TIME, m_pTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetAlarm, CDialog)
	//{{AFX_MSG_MAP(CDlgSetAlarm)
	ON_BN_CLICKED(IDC_USEALARM, OnUsealarm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetAlarm message handlers

BOOL CDlgSetAlarm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pDate.SetCurSel (m_Time);
	m_pTime = m_Time;

	UpdateData (FALSE);

// Set correct language text
	((CButton *)GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (36, "OK"));
	((CButton *)GetDlgItem (IDCANCEL))->SetWindowText (CTranslate::ReadString (37, "Cancel"));	
	((CStatic *)GetDlgItem (IDC_USEALARM))->SetWindowText (CTranslate::ReadString (40, "Use alarm"));	

	SetWindowText (CTranslate::ReadString (41, "Set alarm"));

	return TRUE;
}

void CDlgSetAlarm::OnOK() 
{
	UpdateData (TRUE);
	SYSTEMTIME st;

	m_pDate.GetCurSel (&st);

	st.wHour			= m_pTime.GetHour ();
	st.wMinute			= m_pTime.GetMinute ();
	st.wSecond			= m_pTime.GetSecond ();
	st.wMilliseconds	= 0;

	m_Time = st;
	

// Weekly

// Monthly
	CDialog::OnOK();
}

void CDlgSetAlarm::OnUsealarm() 
{
	UpdateData (TRUE);

// Toogle
	if (m_bUseAlarm)	{
		((CDateTimeCtrl *)GetDlgItem (IDC_TIME))->EnableWindow (TRUE);
		((CMonthCalCtrl *)GetDlgItem (IDC_DATE))->EnableWindow (TRUE);
	}
	else	{
		((CDateTimeCtrl *)GetDlgItem (IDC_TIME))->EnableWindow (FALSE);
		((CMonthCalCtrl *)GetDlgItem (IDC_DATE))->EnableWindow (FALSE);
	}
}

