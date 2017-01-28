// DlgUseUserInformation.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgUseUserInformation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUseUserInformation dialog


CDlgUseUserInformation::CDlgUseUserInformation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUseUserInformation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUseUserInformation)
	m_szUserName = _T("");
	m_szPassword = _T("");
	//}}AFX_DATA_INIT
}


void CDlgUseUserInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUseUserInformation)
	DDX_Text(pDX, IDC_USERNAME, m_szUserName);
	DDX_Text(pDX, IDC_PASSWORD, m_szPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUseUserInformation, CDialog)
	//{{AFX_MSG_MAP(CDlgUseUserInformation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUseUserInformation message handlers

BOOL CDlgUseUserInformation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// Language stuff
	((CStatic *) GetDlgItem (IDC_STATIC1))->SetWindowText (CTranslate::ReadString (161, "User name"));
	((CStatic *) GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (162, "Password"));
	((CStatic *) GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (36, "OK"));
	((CStatic *) GetDlgItem (IDCANCEL))->SetWindowText (CTranslate::ReadString (37, "Cancel"));

	SetWindowText (CTranslate::ReadString (165, "User information"));


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
