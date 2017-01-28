// DlgSetTitle.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgSetTitle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetTitle dialog


CDlgSetTitle::CDlgSetTitle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetTitle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetTitle)
	m_szTitle = _T("");
	//}}AFX_DATA_INIT
}


void CDlgSetTitle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetTitle)
	DDX_Text(pDX, IDC_TITLE, m_szTitle);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TITLE, m_pTitle);
}


BEGIN_MESSAGE_MAP(CDlgSetTitle, CDialog)
	//{{AFX_MSG_MAP(CDlgSetTitle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetTitle message handlers



BOOL CDlgSetTitle::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// Set correct language text
	((CButton *)GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (36, "OK"));
	((CButton *)GetDlgItem (IDCANCEL))->SetWindowText (CTranslate::ReadString (37, "Cancel"));	
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (CTranslate::ReadString (38, "Title"));	

	SetWindowText (CTranslate::ReadString (39, "Change title"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
