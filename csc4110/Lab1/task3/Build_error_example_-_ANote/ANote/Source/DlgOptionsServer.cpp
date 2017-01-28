// DlgOptionsServer.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgOptionsServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsServer dialog


CDlgOptionsServer::CDlgOptionsServer(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsServer)
	m_szAddress = _T("");
	m_szPath = _T("");
	m_szPort = _T("");
	m_bUseDefaultServer = TRUE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsServer::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsServer)
	DDX_Text(pDX, IDC_ADDRESS, m_szAddress);
	DDX_Text(pDX, IDC_PATH, m_szPath);
	DDX_Text(pDX, IDC_PORT, m_szPort);
	DDX_Check(pDX, IDC_USEDEFAULTSERVER, m_bUseDefaultServer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsServer, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsServer)
	ON_BN_CLICKED(IDC_USEDEFAULTSERVER, OnUsedefaultserver)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsServer message handlers

void CDlgOptionsServer::OnUsedefaultserver() 
{
// Either set or make sure that the user can set his/hers own server address
	UpdateData (TRUE);

	if (m_bUseDefaultServer)	{
		((CButton *)GetDlgItem (IDC_ADDRESS))->EnableWindow	(FALSE);
		((CButton *)GetDlgItem (IDC_PATH))->EnableWindow	(FALSE);
		((CButton *)GetDlgItem (IDC_PORT))->EnableWindow	(FALSE);

		((CButton *)GetDlgItem (IDC_ADDRESS))->SetWindowText (_T("http://a-note.sourceforge.net"));
		((CButton *)GetDlgItem (IDC_PATH))->SetWindowText	 (_T(""));
		((CButton *)GetDlgItem (IDC_PORT))->SetWindowText    (_T("80"));

	}
	else	{
		((CButton *)GetDlgItem (IDC_ADDRESS))->EnableWindow	(TRUE);
		((CButton *)GetDlgItem (IDC_PATH))->EnableWindow	(TRUE);
		((CButton *)GetDlgItem (IDC_PORT))->EnableWindow	(TRUE);
	}
	
}


BOOL CDlgOptionsServer::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();

// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (127, _T("Server's address")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (128, _T("Address (http://myserver.com)")));
	((CStatic *)GetDlgItem (IDC_STATIC3))->SetWindowText (CTranslate::ReadString (129, _T("Port (http://myserver.com:8080)")));
	((CStatic *)GetDlgItem (IDC_STATIC4))->SetWindowText (CTranslate::ReadString (130, _T("Path (http://myserver.com/MYPATH/) Must end with /")));
	((CButton *)GetDlgItem (IDC_USEDEFAULTSERVER))->SetWindowText (CTranslate::ReadString (131, _T("Use default server")));

	OnUsedefaultserver ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
