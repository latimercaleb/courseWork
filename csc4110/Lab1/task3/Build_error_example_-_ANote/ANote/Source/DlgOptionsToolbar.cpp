// DlgOptionsToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgOptionsToolbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsToolbar dialog


CDlgOptionsToolbar::CDlgOptionsToolbar(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsToolbar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsToolbar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOptionsToolbar::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsToolbar)
	DDX_Control(pDX, IDC_INUSE, m_pInUse);
	DDX_Control(pDX, IDC_AVAILABLE, m_pAvailable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsToolbar, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsToolbar)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_NOTIFY(NM_DBLCLK, IDC_AVAILABLE, OnDblclkAvailable)
	ON_NOTIFY(NM_DBLCLK, IDC_INUSE, OnDblclkInuse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsToolbar message handlers

BOOL CDlgOptionsToolbar::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();

// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (132, _T("Toolbar")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (133, _T("Available")));
	((CStatic *)GetDlgItem (IDC_STATIC3))->SetWindowText (CTranslate::ReadString (134, _T("In use")));
	((CButton *)GetDlgItem (IDC_UP))->SetWindowText (CTranslate::ReadString (193, _T("Up")));
	((CButton *)GetDlgItem (IDC_DOWN))->SetWindowText (CTranslate::ReadString (194, _T("Down")));

// Initialize listboxes
	m_imgIcon.Create( IDB_TOOLBAR, 16, 1, (COLORREF)-1); 
	m_pAvailable.SetImageList( &m_imgIcon, LVSIL_SMALL );
	m_pInUse.SetImageList( &m_imgIcon, LVSIL_SMALL );
	
// Fill the two listboxes
	FillListBoxes ();


	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOptionsToolbar::OnAdd() 
{
// Find out which one that we want to add
	CString szItem;

// Get the text of the button
	szItem = m_pAvailable.GetItemText (m_pAvailable.GetSelectionMark (), 0);

	if (szItem == _T(" ") + CTranslate::ReadString (135, _T("Bold")))			m_iInUseBold		= m_pInUse.GetItemCount () + 1;
	if (szItem == _T(" ") + CTranslate::ReadString (136, _T("Underline")))		m_iInUseUnderline	= m_pInUse.GetItemCount () + 1;
	if (szItem == _T(" ") + CTranslate::ReadString (137, _T("Italic")))			m_iInUseItalic		= m_pInUse.GetItemCount () + 1;
	if (szItem == _T(" ") + CTranslate::ReadString (138, _T("Bullet")))			m_iInUseBullet		= m_pInUse.GetItemCount () + 1;
	if (szItem == _T(" ") + CTranslate::ReadString (139, _T("Minimera")))		m_iInUseMinimize	= m_pInUse.GetItemCount () + 1;
	if (szItem == _T(" ") + CTranslate::ReadString (140, _T("Slide left")))		m_iInUseSlideLeft	= m_pInUse.GetItemCount () + 1;
	if (szItem == _T(" ") + CTranslate::ReadString (141, _T("Slide right")))	m_iInUseSlideRight	= m_pInUse.GetItemCount () + 1;
	if (szItem == _T(" ") + CTranslate::ReadString (142, _T("Strikeout"))) 		m_iInUseStrikeOut	= m_pInUse.GetItemCount () + 1;

	FillListBoxes ();
}

void CDlgOptionsToolbar::OnRemove() 
{
// Find out which one that we want to remove
	CString szItem;

// Get the text of the button
	szItem = m_pInUse.GetItemText (m_pInUse.GetSelectionMark (), 0);

	if (szItem == _T(" ") + CTranslate::ReadString (135, _T("Bold")))			m_iInUseBold		= 0;
	if (szItem == _T(" ") + CTranslate::ReadString (136, _T("Underline")))		m_iInUseUnderline	= 0;
	if (szItem == _T(" ") + CTranslate::ReadString (137, _T("Italic")))			m_iInUseItalic		= 0;
	if (szItem == _T(" ") + CTranslate::ReadString (138, _T("Bullet")))			m_iInUseBullet		= 0;
	if (szItem == _T(" ") + CTranslate::ReadString (139, _T("Minimera")))		m_iInUseMinimize	= 0;
	if (szItem == _T(" ") + CTranslate::ReadString (140, _T("Slide left")))		m_iInUseSlideLeft	= 0;
	if (szItem == _T(" ") + CTranslate::ReadString (141, _T("Slide right")))	m_iInUseSlideRight	= 0;
	if (szItem == _T(" ") + CTranslate::ReadString (142, _T("Strikeout")))		m_iInUseStrikeOut	= 0;

// Fix the buttons
	int iSel = m_pInUse.GetSelectionMark ();
	iSel++;

	if (m_iInUseBold > iSel)		m_iInUseBold--;
	if (m_iInUseUnderline > iSel)	m_iInUseUnderline--;
	if (m_iInUseItalic > iSel)		m_iInUseItalic--;
	if (m_iInUseBullet > iSel)		m_iInUseBullet--;
	if (m_iInUseMinimize > iSel)	m_iInUseMinimize--;
	if (m_iInUseSlideLeft > iSel)	m_iInUseSlideLeft--;
	if (m_iInUseSlideRight > iSel)	m_iInUseSlideRight--;
	if (m_iInUseStrikeOut > iSel)	m_iInUseStrikeOut--;

	FillListBoxes ();
}


void CDlgOptionsToolbar::FillListBoxes()
{
// Fill the list boxes
	m_pAvailable.DeleteAllItems ();
	m_pInUse.DeleteAllItems ();

	int iA, iI;
	iA = iI = 0;
	m_iButtonWidth = 20; // We always have the close button

	for (int i = 1; i < 10; i++)	{

	// In use
		if (m_iInUseBold == i)		{	m_pInUse.InsertItem (i, _T(" ") + CTranslate::ReadString (135, _T("Bold")),			0); m_iButtonWidth += 20;}
		if (m_iInUseUnderline == i)	{	m_pInUse.InsertItem (i, _T(" ") + CTranslate::ReadString (136, _T("Underline")),	1); m_iButtonWidth += 20;}
		if (m_iInUseItalic == i)	{	m_pInUse.InsertItem (i, _T(" ") + CTranslate::ReadString (137, _T("Italic")),		2); m_iButtonWidth += 20;}
		if (m_iInUseBullet == i)	{	m_pInUse.InsertItem (i, _T(" ") + CTranslate::ReadString (138, _T("Bullet")),		3); m_iButtonWidth += 20;}
		if (m_iInUseMinimize == i)	{	m_pInUse.InsertItem (i, _T(" ") + CTranslate::ReadString (139, _T("Minimize")),		4); m_iButtonWidth += 20;}
		if (m_iInUseSlideLeft == i)	{	m_pInUse.InsertItem (i, _T(" ") + CTranslate::ReadString (140, _T("Slide left")),	5); m_iButtonWidth += 20;}
		if (m_iInUseSlideRight == i){	m_pInUse.InsertItem (i, _T(" ") + CTranslate::ReadString (141, _T("Slide right")),	6); m_iButtonWidth += 20;}
		if (m_iInUseStrikeOut == i)	{	m_pInUse.InsertItem (i, _T(" ") + CTranslate::ReadString (142, _T("Strikeout")),	7); m_iButtonWidth += 20;}
	}

	// Available
		if (m_iInUseBold == 0)			m_pAvailable.InsertItem (0, _T(" ") + CTranslate::ReadString (135, _T("Bold")),			0);
		if (m_iInUseUnderline == 0)		m_pAvailable.InsertItem (0, _T(" ") + CTranslate::ReadString (136, _T("Underline")),	1);
		if (m_iInUseItalic == 0)		m_pAvailable.InsertItem (0, _T(" ") + CTranslate::ReadString (137, _T("Italic")),		2);
		if (m_iInUseBullet == 0)		m_pAvailable.InsertItem (0, _T(" ") + CTranslate::ReadString (138, _T("Bullet")),		3);
		if (m_iInUseMinimize == 0)		m_pAvailable.InsertItem (0, _T(" ") + CTranslate::ReadString (139, _T("Minimize")),		4);
		if (m_iInUseSlideLeft == 0)		m_pAvailable.InsertItem (0, _T(" ") + CTranslate::ReadString (140, _T("Slide left")),	5);
		if (m_iInUseSlideRight == 0)	m_pAvailable.InsertItem (0, _T(" ") + CTranslate::ReadString (141, _T("Slide right")),	6);	
		if (m_iInUseStrikeOut == 0)		m_pAvailable.InsertItem (0, _T(" ") + CTranslate::ReadString (142, _T("Strikeout")),	7);	
}

void CDlgOptionsToolbar::OnUp() 
{
// Move the marked toolbarbutton up one step
	int iSel;

// Get the text of the button
	iSel = m_pInUse.GetSelectionMark ();
	iSel++;

// We can't move the item at the top or we have to have one selected
	if (iSel == 1 || iSel == 0)
		return;

// Is this the item that we clicked on -> move it up or if it is the item that should move down -> do so.
	if (m_iInUseBold ==			iSel)	m_iInUseBold--;			else if ((m_iInUseBold + 1) == iSel)		m_iInUseBold++;
	if (m_iInUseUnderline ==	iSel)	m_iInUseUnderline--;	else if ((m_iInUseUnderline + 1) == iSel)	m_iInUseUnderline++;
	if (m_iInUseItalic ==		iSel)	m_iInUseItalic--;		else if ((m_iInUseItalic + 1) == iSel)		m_iInUseItalic++;
	if (m_iInUseBullet ==		iSel)	m_iInUseBullet--;		else if ((m_iInUseBullet + 1) == iSel)		m_iInUseBullet++;
	if (m_iInUseMinimize ==		iSel)	m_iInUseMinimize--;		else if ((m_iInUseMinimize + 1) == iSel)	m_iInUseMinimize++;
	if (m_iInUseSlideLeft ==	iSel)	m_iInUseSlideLeft--;	else if ((m_iInUseSlideLeft + 1) == iSel)	m_iInUseSlideLeft++;
	if (m_iInUseSlideRight ==	iSel)	m_iInUseSlideRight--;	else if ((m_iInUseSlideRight + 1) == iSel)	m_iInUseSlideRight++;
	if (m_iInUseStrikeOut ==	iSel)	m_iInUseStrikeOut--;	else if ((m_iInUseStrikeOut + 1) == iSel)	m_iInUseStrikeOut++;

	FillListBoxes ();
}

void CDlgOptionsToolbar::OnDown() 
{
// Move the marked toolbarbutton down one step
	int iSel;

// Get the text of the button
	iSel = m_pInUse.GetSelectionMark ();
	iSel++;

// We can't move the item at the top or we have to have one selected
	if (iSel == m_pInUse.GetItemCount () || iSel == 0)
		return;

// Is this the item that we clicked on -> move it up or if it is the item that should move down -> do so.
	if (m_iInUseBold ==			iSel)	m_iInUseBold++;			else if ((m_iInUseBold - 1) == iSel)		m_iInUseBold--;
	if (m_iInUseUnderline ==	iSel)	m_iInUseUnderline++;	else if ((m_iInUseUnderline - 1) == iSel)	m_iInUseUnderline--;
	if (m_iInUseItalic ==		iSel)	m_iInUseItalic++;		else if ((m_iInUseItalic - 1) == iSel)		m_iInUseItalic--;
	if (m_iInUseBullet ==		iSel)	m_iInUseBullet++;		else if ((m_iInUseBullet - 1) == iSel)		m_iInUseBullet--;
	if (m_iInUseMinimize ==		iSel)	m_iInUseMinimize++;		else if ((m_iInUseMinimize - 1) == iSel)	m_iInUseMinimize--;
	if (m_iInUseSlideLeft ==	iSel)	m_iInUseSlideLeft++;	else if ((m_iInUseSlideLeft - 1) == iSel)	m_iInUseSlideLeft--;
	if (m_iInUseSlideRight ==	iSel)	m_iInUseSlideRight++;	else if ((m_iInUseSlideRight - 1) == iSel)	m_iInUseSlideRight--;
	if (m_iInUseStrikeOut ==	iSel)	m_iInUseStrikeOut++;	else if ((m_iInUseStrikeOut - 1) == iSel)	m_iInUseStrikeOut--;

	FillListBoxes ();
	
}

void CDlgOptionsToolbar::OnDblclkAvailable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnAdd ();
	
	*pResult = 0;
}

void CDlgOptionsToolbar::OnDblclkInuse(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnRemove ();
	
	*pResult = 0;
}
