// DlgSnooze.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgSnooze.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSnooze dialog


CDlgSnooze::CDlgSnooze(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSnooze::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSnooze)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSnooze::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSnooze)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSnooze, CDialog)
	//{{AFX_MSG_MAP(CDlgSnooze)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSnooze message handlers

BOOL CDlgSnooze::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// Language stuff
	((CButton *) GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (158, "Snooze"));
	((CButton *) GetDlgItem (IDCANCEL))->SetWindowText (CTranslate::ReadString (159, "Turn off"));

	SetWindowText (CTranslate::ReadString (160, "Snooze or turn off"));


// Move the window above the tray
	CRect rc;
	CRect rect;
	SystemParametersInfo (SPI_GETWORKAREA , 0, &rc, 0);
	GetClientRect (&rect);

	MoveWindow (rc.right - rect.right - 10,
				rc.bottom - rect.bottom - 10,
				rect.right  + 10,
				rect.bottom + 20);

	
	return TRUE;
}