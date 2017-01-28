// DlgOptionsAlarm.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgOptionsAlarm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsAlarm dialog




CDlgOptionsAlarm::CDlgOptionsAlarm(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsAlarm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsAlarm)
	m_bBlink = FALSE;
	m_bPlaySound = FALSE;
	m_szSoundFile = _T("");
	//}}AFX_DATA_INIT
}


void CDlgOptionsAlarm::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsAlarm)
	DDX_Check(pDX, IDC_BLINK, m_bBlink);
	DDX_Check(pDX, IDC_PLAYSOUND, m_bPlaySound);
	DDX_Text(pDX, IDC_SOUNDFILE, m_szSoundFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsAlarm, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsAlarm)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsAlarm message handlers


void CDlgOptionsAlarm::OnBrowse() 
{
	OPENFILENAME ofn;      
	TCHAR szFile[260];      

	szFile[0] = NULL;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter=_T("Sounds (*.wav)\0*.wav");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName (&ofn) != TRUE) 
		return;

	m_szSoundFile = CString (ofn.lpstrFile);	
	UpdateData (FALSE);
}

BOOL CDlgOptionsAlarm::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (68, _T("Alarm")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (69, "Sound file"));
	((CButton *)GetDlgItem (IDC_BLINK))->SetWindowText (CTranslate::ReadString (70, "Blink the note on alarm"));
	((CButton *)GetDlgItem (IDC_PLAYSOUND))->SetWindowText (CTranslate::ReadString (71, "Play a sound on alarm"));
	((CButton *)GetDlgItem (IDC_BROWSE))->SetWindowText (CTranslate::ReadString (72, "Browse..."));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
