// DlgRecycleBinHelp.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgRecycleBinHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecycleBinHelp dialog


CDlgRecycleBinHelp::CDlgRecycleBinHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecycleBinHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecycleBinHelp)
	m_bShowNextTime = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgRecycleBinHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecycleBinHelp)
	DDX_Check(pDX, IDC_CHECK1, m_bShowNextTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecycleBinHelp, CDialog)
	//{{AFX_MSG_MAP(CDlgRecycleBinHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecycleBinHelp message handlers

BOOL CDlgRecycleBinHelp::OnInitDialog() 
{
	CDialog::OnInitDialog();

// Language stuff
	((CStatic *) GetDlgItem (IDC_STATIC1))->SetWindowText (CTranslate::ReadString (153, "The notes' title will appear in a box. If you want to look at that note you simply doubleclick on it and the note will be created as it were when you deleted it."));
	((CStatic *) GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (154, "If you want to restore a note you simply select one or multiple with shift and ctrl and then restore it with the restore-button. The same goes for delete."));
	((CStatic *) GetDlgItem (IDC_STATIC3))->SetWindowText (CTranslate::ReadString (155, "NOTE: If you delete one or several notes they will be deleted permanently."));
	((CButton *) GetDlgItem (IDC_CHECK1))->SetWindowText (CTranslate::ReadString (156, "Show time message next time"));
	((CButton *) GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (36, "OK"));
	
	SetWindowText (CTranslate::ReadString (157, "Recycle bin help"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
