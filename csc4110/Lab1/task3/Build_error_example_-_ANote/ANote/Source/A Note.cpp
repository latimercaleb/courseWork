#include "stdafx.h"
#include "A Note.h"

#include "MainFrm.h"
#include <atlbase.h>
#include "DlgGuide.h"
#include "Picture.h"

#include <afx.h>
#include <afxwin.h>
#include <afxinet.h>
#include <atlbase.h>
#include <afxpriv.h>
#include "Base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CANoteApp, CWinApp)
	//{{AFX_MSG_MAP(CANoteApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CANoteApp::CANoteApp()
{
}



// GLOBAL FUNCTIONS AND THREADS --------------------------------

CANoteApp theApp;

// Get the application data path (where the notes.xml should be saved)
CString GetApplicationDataPath ()	{
	CString szPath;

	if (!SHGetSpecialFolderPath (NULL, szPath.GetBufferSetLength (MAX_PATH), CSIDL_APPDATA ,0))	{
		// Something went wrong and we return the program path instead (maybe the user runs Windows 1.0 :)     )
		return GetProgramPath ();
	}

	szPath.Format (_T("%s\\A Note"), szPath);

// Create the directory if it doesn't exist
	CreateDirectory (szPath, NULL);

	return szPath;
}


// Get the program path
CString GetProgramPath ()	
{
	CString szTempPath, szTemp, szAppPath;
	int i;
	TCHAR buf[_MAX_PATH + 1];

	::GetModuleFileName(NULL, buf, sizeof buf);
	szTemp = buf;
	i = szTemp.ReverseFind ('\\');
	szAppPath = szTemp.Left ( i );

	return szAppPath;
}

CString StringEncode(CString szText)
{
	int iLength, iMultibyte;
	CString szResult;
	iLength	= szText.GetLength ();
	WCHAR *pwcUnicode = new WCHAR[sizeof (WCHAR) * (iLength + 1)];
	char *pcDest = new char[2 * (iLength + 1)];
#if (defined (UNICODE) || defined (_UNICODE))
	_tcscpy(pwcUnicode, szText);
#else
// To Unicode (form current codepage)
	MultiByteToWideChar (CP_ACP, 0, szText, -1, pwcUnicode, iLength);
#endif
// To UTF-8
	iMultibyte = WideCharToMultiByte (CP_UTF8, 0,pwcUnicode, iLength , pcDest, 2*iLength, NULL, NULL);

	szResult = (CString) pcDest;
	szResult = szResult.Left ( iMultibyte );

	pcDest[iMultibyte] = '\0';

// Base 64
	CBase64 base;
	base.Encode (pcDest);
	szResult = base.EncodedMessage ();

	delete []pwcUnicode;
	delete []pcDest;

	return szResult;
}


CString StringDecode(CString szText)
{
	CString szResult;

// If the string already is empty we don't need to code it
	if (szText.IsEmpty ())
		return _T("");

#if (defined (UNICODE) || defined (_UNICODE))
	int iLength, iMultibyte;
	iLength	= szText.GetLength ();
	WCHAR *pwcUnicode = new WCHAR[sizeof (WCHAR) * (iLength + 1)];
	char *pcDest = new char[2 * (iLength + 1)];
	char *res;
	_tcscpy(pwcUnicode, szText);

// To UTF-8
	iMultibyte = WideCharToMultiByte (CP_UTF8, 0,pwcUnicode, iLength , pcDest, 2*iLength, NULL, NULL);
	pcDest [iMultibyte] = '\0';
// Base 64
	CBase64 base;
	base.Decode (pcDest);
	res = base.DecodedMessage ();
	int i = base.GetLength ();

// From UTF-8
	iMultibyte = MultiByteToWideChar (CP_UTF8, 0,res, strlen (res), pwcUnicode, 2 * iLength);
	pwcUnicode[i] = '\0';
	szResult = pwcUnicode;
	szResult = szResult.Left (iMultibyte);

	delete []pwcUnicode;
	delete []pcDest;
#else
	char *pTemp = new char [szText.GetLength ()+1];
	for (int i = 0; i < szText.GetLength (); i++)
		pTemp [i] = szText.GetAt (i);
	pTemp [szText.GetLength ()] = '\0';
	CBase64 base;
	base.Decode (pTemp);
	szResult = base.DecodedMessage ();
	delete []pTemp;
#endif

	return szResult;
}

CString GetProgramVersion()
{
// Calculate the version number
	CString szVersion;
	TCHAR szAppName[_MAX_PATH];
	::GetModuleFileName(AfxGetInstanceHandle(), szAppName, _MAX_PATH);

    TCHAR szFile[_MAX_PATH];
    GetModuleFileName(NULL, szFile, _MAX_PATH);

    DWORD dwVerHnd;
    DWORD dwVerInfoSize = GetFileVersionInfoSize(szFile, &dwVerHnd);
    if (!dwVerInfoSize)
		return "";

    BYTE* pVerInfo = new BYTE[dwVerInfoSize];
    if (!pVerInfo)
        return "";

    BOOL fRet = GetFileVersionInfo(szFile, 0L, dwVerInfoSize, pVerInfo);
    if (fRet)    {
		TCHAR* pVer = NULL;
        UINT ccVer = 0;
        fRet = VerQueryValue(pVerInfo, _T("\\StringFileInfo\\040904B0\\ProductVersion"), (void**)&pVer, &ccVer);
		szVersion = pVer;
    }
 
    delete pVerInfo;

	szVersion.Replace (_T(", "), _T("."));

	while (1)	{
		if (szVersion.Right (2) == ".0")
			szVersion = szVersion.Left (szVersion.GetLength () - 2);
		else
			break;
	}

	if (szVersion.Find ('.') == -1)
		szVersion += ".0";
	
	CString szTemp;
	szTemp.Format (_T("A Note Version %s"), szVersion);

	return szTemp;
}
// GLOBAL FUNCTIONS AND THREADS --------------------------------




BOOL CANoteApp::InitInstance()
{
	AfxEnableControlContainer();

	SetRegistryKey(_T("A Note"));

	m_bStayOnTop				= GetProfileInt			( _T("Settings\\Options"), _T("Stay On Top"),					1);
	m_cfNoteColor				= GetProfileInt			( _T("Settings\\Options"), _T("Default Note Color"),			RGB (255, 255, 125));
	m_iTransparantNormal		= GetProfileInt			( _T("Settings\\Options"), _T("Transparancy"),					100);
	m_iTransparantMinimized		= GetProfileInt			( _T("Settings\\Options"), _T("Transparancy When Minimized"),	100);
	m_bRndNoteColor				= GetProfileInt			( _T("Settings\\Options"), _T("Randomize Note Color"),			0);
	m_bThinNoteBorder			= GetProfileInt			( _T("Settings\\Options"), _T("Thin Note border"),				1);
	m_bMinimizeShrink			= GetProfileInt			( _T("Settings\\Options"), _T("Shrinked When Minimized"),		1);
	m_bWarnOnDelete				= GetProfileInt			( _T("Settings\\Options"), _T("Warn On Delete"),				0);
	m_bBlinkNote				= GetProfileInt			( _T("Settings\\Options"), _T("Blink On Alarm"),				1);
	m_bPlayAlarmSound			= GetProfileInt			( _T("Settings\\Options"), _T("Play Sound On Alarm"),			1);
	m_bDockable					= GetProfileInt			( _T("Settings\\Options"), _T("Notes Are Dockable"),			1);
	m_bCheckLatestVersion		= GetProfileInt			( _T("Settings\\Options"), _T("Check For Latest Version"),		1);
	m_bNewNoteDockLeft			= GetProfileInt			( _T("Settings\\Options"), _T("New Note Docked Left"),			0);
	m_bNewNoteDockTop			= GetProfileInt			( _T("Settings\\Options"), _T("New Note Docked Top"),			0);
	m_bNewNoteDockRight			= GetProfileInt			( _T("Settings\\Options"), _T("New Note Docked Right"),			1);
	m_bNewNoteDockBottom		= GetProfileInt			( _T("Settings\\Options"), _T("New Note Docked Bottom"),		1);
	m_iNewNoteLeft				= GetProfileInt			( _T("Settings\\Options"), _T("New Note Left"),					0);
	m_iNewNoteTop				= GetProfileInt			( _T("Settings\\Options"), _T("New Note Top"),					0);
	m_iNewNoteWidth				= GetProfileInt			( _T("Settings\\Options"), _T("New Note Width"),				150);
	m_bDoubleClickOnTitleBar	= GetProfileInt			( _T("Settings\\Options"), _T("Double Click On The TitleBar"),	0);
	m_bHotKeyAlt				= GetProfileInt			( _T("Settings\\Options"), _T("Hot Key Alt"),					0);
	m_bHotKeyCtrl				= GetProfileInt			( _T("Settings\\Options"), _T("Hot Key Ctrl"),					0);
	m_bHotKeyShift				= GetProfileInt			( _T("Settings\\Options"), _T("Hot Key Shift"),					0);
	m_bHotKeyWin				= GetProfileInt			( _T("Settings\\Options"), _T("Hot Key Win"),					0);
	m_bUseHotKey				= GetProfileInt			( _T("Settings\\Options"), _T("Hot Key Use It"),				0);
	m_iHotKeyCharacter			= GetProfileInt			( _T("Settings\\Options"), _T("Hot Key Character"),				0);
	m_bMinimizeMoveCursor		= GetProfileInt			( _T("Settings\\Options"), _T("When Minimized Move Cursor"),	1);
	m_szDefaultTitle			= GetProfileString		( _T("Settings\\Options"), _T("Default Title"),					_T("Untitled"));
	m_szServerAddress			= GetProfileString		( _T("Settings\\Options"), _T("Server Address"),				_T("http://a-note.sourceforge.net"));
	m_szServerPort				= GetProfileString		( _T("Settings\\Options"), _T("Server Port"),					_T("80"));
	m_szServerPath				= GetProfileString		( _T("Settings\\Options"), _T("Server Path"),					_T(""));
	m_bUseDefaultServer			= GetProfileInt			( _T("Settings\\Options"), _T("Use Default Server"),			1);
	m_bShowDeleteMessage		= GetProfileInt			( _T("Settings\\Options"), _T("Show Delete Message"),			1);
	m_iStartDownloadingAfter	= GetProfileInt			( _T("Settings\\Options"), _T("Start Downloading After"),		0);
	m_bSortRecycleBinDescending = GetProfileInt			( _T("Settings\\Options"), _T("Sort Recycle Bin Descending"), 1);
	m_szRecycleBinNumberOfNotes	= GetProfileString		( _T("Settings\\Options"), _T("Save Total Number Of Notes For The Recycle Bin"), _T("0"));
	m_iLeftClickOnTrayIcon		= GetProfileInt			( _T("Settings\\Options"), _T("Action For Single Left Click On The Tray Icon"), 0);
	m_szLanguageIni				= GetProfileString		( _T("Settings\\Options"), _T("Ini File Used For Language"),	_T("English.ini"));

	m_iToolBarUseBold			= GetProfileInt			( _T("Settings\\Options"), _T("ToolBar Use Bold Button Where"),			0);
	m_iToolBarUseItalic			= GetProfileInt			( _T("Settings\\Options"), _T("ToolBar Use Italic Button Where"),		0);
	m_iToolBarUseUnderline		= GetProfileInt			( _T("Settings\\Options"), _T("ToolBar Use Underline Button Where"),	0);
	m_iToolBarUseBullet			= GetProfileInt			( _T("Settings\\Options"), _T("ToolBar Use Bullet Button Where"),		0);
	m_iToolBarUseMinimize		= GetProfileInt			( _T("Settings\\Options"), _T("ToolBar Use Minimize Button Where"),		1);
	m_iToolBarUseSlideLeft		= GetProfileInt			( _T("Settings\\Options"), _T("ToolBar Use Slide Left Button Where"),	0);
	m_iToolBarUseSlideRight		= GetProfileInt			( _T("Settings\\Options"), _T("ToolBar Use Slide Right Button Where"),	2);
	m_iToolBarUseStrikeOut		= GetProfileInt			( _T("Settings\\Options"), _T("ToolBar Use Strikeout Where"),			0);
	m_iToolBarButtonWidth		= GetProfileInt			( _T("Settings\\Options"), _T("ToolBar Button Width"),					0);

	m_iCharset					= GetProfileInt			( _T("Settings\\Options"), _T("Selected Charset Value Unicode"), DEFAULT_CHARSET);
	m_szCharsetName				= GetProfileString		( _T("Settings\\Options"), _T("Selected Charset Readable Name Unicode"), _T("DEFAULT_CHARSET"));

	CString szTemp;
	szTemp.Format (_T("%s\\Alarm.wav"), GetProgramPath ());
	m_szAlarmSoundFile	= GetProfileString				( _T("Settings\\Options"), _T("Alarm Sound File"),				szTemp);			

	m_bUploadDownload	= GetProfileInt					( _T("Settings\\Options"), _T("Upload And Download Notes"),		1);
	m_szUserName		= GetProfileString				( _T("Settings\\Options"), _T("Database User Name"),			_T(""));
	m_szPassword		= GetProfileString				( _T("Settings\\Options"), _T("Database Password"),				_T(""));

// Show the help information that shows for beginner
#ifdef _SHOWHELP
	CDlgGuide dlgguide;
	if (GetProfileInt	( _T("Settings\\Help"), _T("Show Beginners Help"),0) == 0)	{
		dlgguide.DoModal ();
		WriteProfileInt (_T("Settings\\Help"), _T("Show Beginners Help"), dlgguide.m_bDontShowAgain);
	}
#endif

// NOTE: This will only happen the first time 
	if (GetProfileInt (_T("Settings\\Options"), _T("Ask questions first time the program runs"), 1))	{

	// Upload / download notes
		CString szTemp;
		szTemp.Format (_T("%s\n%s\n%s\n%s\n%s"), CTranslate::ReadString (166, _T("Every time A Note starts and ends it will contact a server")), CTranslate::ReadString (167, _T("and upload and download any notes that you have. This feature lets you share your")), CTranslate::ReadString (168, _T("notes between different computers. If you want this to happen automatically, press 'YES'.")), CTranslate::ReadString (169, _T("If you don't want this feature to start automatically, press 'NO'.")), CTranslate::ReadString (170, _T("You can always change this behaviour in the options menu")));
		if (MessageBox (NULL, szTemp, CTranslate::ReadString (171, "Upload / download notes"), MB_YESNO | MB_ICONQUESTION) == IDNO)	{
			m_bUploadDownload = FALSE;
			WriteProfileInt	( _T("Settings\\Options"), _T("Upload And Download Notes"),	0);
		}
			
		WriteProfileInt (_T("Settings\\Options"), _T("Ask questions first time the program runs"), 0);
	}

#ifdef _AFXDLL
	Enable3dControls();	
#else
	Enable3dControlsStatic();
#endif

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;


	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);


	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	CMenu* pMenu = m_pMainWnd->GetMenu();
	if (pMenu)
		pMenu->DestroyMenu();
	HMENU hMenu = ((CMainFrame*) m_pMainWnd)->NewMenu();
	pMenu = CMenu::FromHandle( hMenu );
	m_pMainWnd->SetMenu(pMenu);
	((CMainFrame*)m_pMainWnd)->m_hMenuDefault = hMenu;


	return TRUE;
}


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	CPicture	m_pImage;
	CString		m_szVersion;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CANoteApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this); 
	

	CDC *pDC;
	pDC = GetDC ();

	m_pImage.Draw(pDC, CPoint (0, 0), CPoint (400, 250));


// Version text
	HFONT hfont;
    LOGFONT lf; 
	GetObject(GetStockObject(ANSI_VAR_FONT), sizeof(LOGFONT), &lf); 
	lf.lfWeight = FW_EXTRALIGHT; 
	hfont =  CreateFont(lf.lfHeight, lf.lfWidth, 
		    lf.lfEscapement, lf.lfOrientation, lf.lfWeight, 
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, 
	        lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, 
			lf.lfPitchAndFamily, lf.lfFaceName); 

	HGDIOBJ oldfont = dc.SelectObject (hfont);
	dc.SetTextColor (RGB (0,0,0));
	dc.SetBkMode (TRANSPARENT);
	dc.TextOut (238, 190, m_szVersion);
	dc.TextOut (238, 205, "Freeware by...");
	dc.TextOut (238, 220, "Sourceforge");


	DeleteObject (hfont);
	dc.SelectObject (oldfont);

// Clean up
	ReleaseDC (pDC);

}

int CANoteApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
// Close the dialog
	CDialog::OnOK ();	
}


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// Load the image
	CString szName;
	szName.Format (_T("%s\\about.jpg"), GetProgramPath ());
	m_pImage.Load (szName);
	

// Calculate the version number
	CString szVersion;
	TCHAR szAppName[_MAX_PATH];
	::GetModuleFileName(AfxGetInstanceHandle(), szAppName, _MAX_PATH);

    TCHAR szFile[_MAX_PATH];
    GetModuleFileName(NULL, szFile, _MAX_PATH);

    DWORD dwVerHnd;
    DWORD dwVerInfoSize = GetFileVersionInfoSize(szFile, &dwVerHnd);
    if (!dwVerInfoSize)
		return FALSE;

    BYTE* pVerInfo = new BYTE[dwVerInfoSize];
    if (!pVerInfo)
        return FALSE;

    BOOL fRet = GetFileVersionInfo(szFile, 0L, dwVerInfoSize, pVerInfo);
    if (fRet)    {
		TCHAR* pVer = NULL;
        UINT ccVer = 0;
        fRet = VerQueryValue(pVerInfo, _T("\\StringFileInfo\\040904B0\\ProductVersion"), (void**)&pVer, &ccVer);
		szVersion = pVer;
    }
 
    delete pVerInfo;

	szVersion.Replace (_T(", "), _T("."));

	while (1)	{
		if (szVersion.Right (2) == ".0")
			szVersion = szVersion.Left (szVersion.GetLength () - 2);
		else
			break;
	}

	if (szVersion.Find ('.') == -1)
		szVersion += ".0";
	
	m_szVersion.Format (_T("Version %s"),szVersion);

	return TRUE;
}



