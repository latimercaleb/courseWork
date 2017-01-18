// DlgOptionsTransparancy.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgOptionsTransparancy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsTransparancy dialog


CDlgOptionsTransparancy::CDlgOptionsTransparancy(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsTransparancy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsTransparancy)
	m_iTransparantNormal = 0;
	m_iTransparantMinimized = 0;
	//}}AFX_DATA_INIT
}


void CDlgOptionsTransparancy::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsTransparancy)
	DDX_Control(pDX, IDC_TRANSPARANCYNORMAL, m_pTransparancyNormal);
	DDX_Control(pDX, IDC_TRANSPARANCYMINIMIZE, m_pTransparancyMinimized);
	DDX_Slider(pDX,  IDC_TRANSPARANCYNORMAL, m_iTransparantNormal);
	DDX_Slider(pDX, IDC_TRANSPARANCYMINIMIZE, m_iTransparantMinimized);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsTransparancy, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsTransparancy)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsTransparancy message handlers

BOOL CDlgOptionsTransparancy::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();

// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (143, _T("Transparancy (only Windows 2000/XP)")));
	((CStatic *) GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *) GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (144, _T("When the notes are in normal mode")));
	((CStatic *) GetDlgItem (IDC_STATIC3))->SetWindowText (CTranslate::ReadString (145, _T("When the notes are minimized, but still visible")));

	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYNORMAL))->SetRange (1,100, FALSE);
	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYNORMAL))->SetPos (theApp.m_iTransparantNormal);
	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYNORMAL))->SetTic (50);

	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYNORMAL))->SendMessage(WM_LBUTTONDOWN);
	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYNORMAL))->SendMessage(WM_LBUTTONUP);	

	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYMINIMIZE))->SetRange (1,100, FALSE);
	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYMINIMIZE))->SetPos (theApp.m_iTransparantMinimized);
	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYMINIMIZE))->SetTic (50);

	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYMINIMIZE))->SendMessage(WM_LBUTTONDOWN);
	((CSliderCtrl*) GetDlgItem (IDC_TRANSPARANCYMINIMIZE))->SendMessage(WM_LBUTTONUP);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOptionsTransparancy::OnDestroy() 
{
	CSAPrefsSubDlg::OnDestroy();
	
	m_iTransparantNormal	= m_pTransparancyNormal.GetPos ();		
	m_iTransparantMinimized = m_pTransparancyMinimized.GetPos ();
}
