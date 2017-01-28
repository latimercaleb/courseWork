// DlgUserInformation.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgUserInformation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUserInformation dialog


CDlgUserInformation::CDlgUserInformation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserInformation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUserInformation)
	m_szUserName = _T("");
	m_szPassword = _T("");
	m_szEmail = _T("");
	//}}AFX_DATA_INIT
}


void CDlgUserInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUserInformation)
	DDX_Text(pDX, IDC_USERNAME, m_szUserName);
	DDX_Text(pDX, IDC_PASSWORD, m_szPassword);
	DDX_Text(pDX, IDC_EMAIL, m_szEmail);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUserInformation, CDialog)
	//{{AFX_MSG_MAP(CDlgUserInformation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUserInformation message handlers

void CDlgUserInformation::OnOK() 
{
	UpdateData (TRUE);
	
	if (m_szUserName.IsEmpty () || m_szPassword.IsEmpty ())	{
		AfxMessageBox (CTranslate::ReadString (21, "Username and password must be filled in"));
		return;
	}

	CDialog::OnOK();
}

BOOL CDlgUserInformation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// Language stuff
	((CStatic *) GetDlgItem (IDC_STATIC1))->SetWindowText (CTranslate::ReadString (161, "User name"));
	((CStatic *) GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (162, "Password"));
	((CStatic *) GetDlgItem (IDC_STATIC3))->SetWindowText (CTranslate::ReadString (163, "Email (optional)"));
	((CStatic *) GetDlgItem (IDC_STATIC4))->SetWindowText (CTranslate::ReadString (164, "Note: The email will not be shared, but only used to send you the password (in case you forget it)"));

	((CButton *) GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (36, "OK"));
	((CButton *) GetDlgItem (IDCANCEL))->SetWindowText (CTranslate::ReadString (37, "Cancel"));

	SetWindowText (CTranslate::ReadString (165, "User information"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
