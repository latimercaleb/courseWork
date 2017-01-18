// DlgDeleteInformation.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgDeleteInformation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDeleteInformation dialog


CDlgDeleteInformation::CDlgDeleteInformation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeleteInformation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDeleteInformation)
	m_bShowAgain = TRUE;
	//}}AFX_DATA_INIT
}


void CDlgDeleteInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeleteInformation)
	DDX_Check(pDX, IDC_SHOWAGAIN, m_bShowAgain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDeleteInformation, CDialog)
	//{{AFX_MSG_MAP(CDlgDeleteInformation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDeleteInformation message handlers

BOOL CDlgDeleteInformation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// Language stuff
	((CButton *) GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (36, "OK"));
	((CStatic *) GetDlgItem (IDC_STATIC1))->SetWindowText (CTranslate::ReadString (42, "When you delete a note, it will be saved in a file.\nBy selecting the recycle bin in the tray-menu, you will be\nable to either permanently delete a note or restore it."));
	((CStatic *) GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (43, " If you hold the shift-button on your keyboard when you press the delete button on a note, the note will be permanently erased."));
	((CButton *) GetDlgItem (IDC_SHOWAGAIN))->SetWindowText (CTranslate::ReadString (44, "Show this warning next time"));

	SetWindowText (CTranslate::ReadString (45, "Delete a note"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
