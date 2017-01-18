// DlgLanguage.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgLanguage.h"
#include "CMapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLanguage dialog

	const TCHAR *TranslateText[TextSize] =	{
		_T("New note"),				// 0
		_T("Import / Export"),		// 1
		_T("Import"),				// 2
		_T("Export"),				// 3
		_T("Upload / Download"),	// 4
		_T("Upload"),				// 5
		_T("Download"),				// 6
		_T("Stay on top"),			// 7
		_T("Minimize all"),			// 8
		_T("Restore"),				// 9
		_T("Recycle bin..."),		// 10
		_T("Visit A Note's website"),
		_T("Check for updates"),
		_T("FAQ"),
		_T("Send Bug / Feedback..."),
		_T("Options"),
		_T("About"),
		_T("Exit"),
		_T("A Note"),
		_T("Notes are hidden"),
		_T("The notes have now been deleted"),// 20
		_T("Username and password must be filled in"),
		_T("The password has been emailed"),
		_T("The notes couldn't be deleted."),
		_T("The notes couldn't be inserted"),
		_T("Couldn't send message!"),
		_T("You have the latest version of A Note"),
		_T("Cut"),
		_T("Copy"),
		_T("Paste"),
		_T("Font..."),								// 30
		_T("Note color..."),
		_T("Set title..."),
		_T("Alarm..."),
		_T("Email..."),
		_T("Print..."),
		_T("OK"),
		_T("Cancel"),
		_T("Title"),
		_T("Change title"),
		_T("Use alarm"),							// 40
		_T("Set alarm"),
		_T("When you delete a note, it will be saved in a file. By selecting the recycle bin in the tray-menu, you will be able to either permanently delete a note or restore it."),
		_T(" If you hold the shift-button on your keyboard when you press the delete button on a note, the note will be permanently erased"),
		_T("Show this warning next time"),
		_T("Delete a note"),
		_T("Don't show again"),
		_T("Previous"),
		_T("Next"),
		_T("Finish"),
		_T("Language"),										// 50
		_T("Select language"),
		_T("Edit language..."),
		_T("Add language..."),
		_T("General"),
		_T("Looks"),
		_T("Behaviour"),
		_T("New note"),
		_T("Font"),
		_T("Alarm"),
		_T("Database"),											// 60
		_T("Server"),
		_T("Transparancy"),
		_T("Hot key"),
		_T("Recycle bin"),
		_T("Toolbar"),
		_T("Language"),
		_T("Options"),
		_T("Alarm"),
		_T("Sound file"),
		_T("Blink the note on alarm"),						// 70
		_T("Play a sound on alarm"),							
		_T("Browse..."),
		_T("Behaviour"),
		_T("What happens when you click once on the tray icon?"),
		_T("Create a new note"),
		_T("Hide and show the notes"),
		_T("Doubleclick on titlebar -> restore / minimize the note"),
		_T("When minimized move the cursor to minimize-button"),
		_T("Dockable"),
		_T("When minimized show only the titlebar"),			// 80
		_T("User information"),
		_T("User name"),
		_T("Password"),
		_T("Upload / Download"),
		_T("Start to download the notes after (seconds)"),
		_T("Delete all my notes that I have on the server"),
		_T("Download the notes when the program starts and upload them on exit"),
		_T("Delete Notes"),
		_T("Default note font"),
		_T("Try here:"),												// 90
		_T("Change font..."),
		_T("This is the font for a new note ..."),
		_T("Creation"),
		_T("Delete"),
		_T("Version check"),
		_T("Use %time% for the current time and %date% for the current date"),
		_T("Default title"),
		_T("Warn when deleting a note"),
		_T("See if there are any newer versions of the program"),
		_T("Hot key"),															// 100
		_T("Character"),
		_T("SHIFT"),
		_T("WIN"),
		_T("ALT"),
		_T("CTRL"),
		_T("Use hot key"),
		_T("The hot key was set..."),
		_T("The combination could not be set"),
		_T("Set hot key"),
		_T("Looks"),														// 110
		_T("Default note color"),
		_T("Randomize the note color"),
		_T("Thin border"),
		_T("Change..."),
		_T("Position of new notes"),
		_T("Your screen"),
		_T("From left"),
		_T("From top"),
		_T("Width"),
		_T("Dock left"),													// 120
		_T("Dock top"),
		_T("Dock right"),
		_T("Dock bottom"),
		_T("Recycle bin"),
		_T("Maximum deleted notes that will be saved (0 for infinitive)"),
		_T("Sort the notes descending"),
		_T("Server's address"),
		_T("Address (http://myserver.com)"),
		_T("Port (http://myserver.com:8080)"),
		_T("Path (http://myserver.com/MYPATH/) Must end with /"),		// 130
		_T("Use default server"),
		_T("Toolbar"),
		_T("Available"),
		_T("In use"),
		_T("Bold"),
		_T("Underline"),
		_T("Italic"),
		_T("Bullet"),
		_T("Minimize"),
		_T("Slide left"),														// 140
		_T("Slide right"),
		_T("Strikeout"),
		_T("Transparancy (only Windows 2000/XP)"),
		_T("When the notes are in normal mode"),
		_T("When the notes are minimized, but still visible"),
		_T("Title"),
		_T("Delete"),
		_T("Restore"),
		_T("Close"),
		_T("Recycle bin"),											// 150
		_T("Do you want to delete the note?"),
		_T("The note will be deleted permanently!"),
		_T("The notes' title will appear in a box. If you want to look at that note you simply doubleclick on it and the note will be created as it were when you deleted it."),
		_T("If you want to restore a note you simply select one or multiple with shift and ctrl and then restore it with the restore-button. The same goes for delete."),
		_T("NOTE: If you delete one or several notes they will be deleted permanently."),
		_T("Show time message next time"),
		_T("Recycle bin help"),
		_T("Snooze"),
		_T("Turn off"),
		_T("Snooze or turn off"),														// 160
		_T("User name"),
		_T("Password"),
		_T("Email (optional)"),
		_T("Note: The email will not be shared, but only used to send you the password (in case you forget it)"),
		_T("User information"),
		_T("Every time A Note starts and ends it will contact a server"),
		_T("and upload and download any notes that you have. This feature lets you share your"),
		_T("notes between different computers. If you want this to happen automatically, press 'YES'."),
		_T("If you don't want this feature to start automatically, press 'NO'."),
		_T("You can always change this behaviour in the options menu"),													// 170
		_T("Upload / download notes"),
		_T("Do you want to delete all of your notes on the server?"),
		_T("Note that the notes on your desktop will NOT be deleted now."),
		_T("Delete notes"),
		_T("You have selected to use more toolbar-bottons that will fit in the default notewidth."),
		_T("Would you like to change the default size for new notes?"),
		_T("Wrong password. If you want the password to be sent to the user's email address, press 'YES'"),
		_T("If you want to enter the password yourself, press 'NO'."),
		_T("Wrong password"),
		_T("To be able to upload and download your notes, you have to create a new user."),													// 180
		_T("Do you want to create a new user? Press 'YES' or if you already have a username and want to use it press 'NO'"),
		_T("No user or password"),
		_T("Do you want to delete the note?"),
		_T("English"),
		_T("Edit language"),
		_T("Enter the language you want to create"),
		_T("Add a new language"),
		_T("Since you have changed one or more language ini-files. We at A Note would appreciate it very much if you want to share the file with us."),
		_T("By doing so other of users may use your language-file."),
		_T("Do you want to send your language ini-files to A Note's author?"), // 190
		_T("Enter the english name for the language"),
		_T("You must enter both a language you want to create and the english name for it."),
		_T("Up"),
		_T("Down"),
		_T("Charset")
	};

CDlgLanguage::CDlgLanguage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLanguage::IDD, pParent)
{
	m_iRow = -1;
	m_bChanged = FALSE;
	m_szLanguageIni = theApp.m_szLanguageIni;
	m_bAskToSave = FALSE;
	//{{AFX_DATA_INIT(CDlgLanguage)
	m_szOtherLanguage = _T("");
	//}}AFX_DATA_INIT
}


void CDlgLanguage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLanguage)
	DDX_Control(pDX, IDC_LANGUAGE, m_pLanguage);
	DDX_Control(pDX, IDC_ENGLISH, m_pEnglish);
	DDX_Text(pDX, IDC_OTHERLANGUAGE, m_szOtherLanguage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLanguage, CDialog)
	//{{AFX_MSG_MAP(CDlgLanguage)
	ON_NOTIFY(NM_CLICK, IDC_ENGLISH, OnClickEnglish)
	ON_EN_CHANGE(IDC_OTHERLANGUAGE, OnChangeOtherlanguage)
	ON_EN_KILLFOCUS(IDC_OTHERLANGUAGE, OnKillfocusOtherlanguage)
	ON_CBN_SELCHANGE(IDC_LANGUAGE, OnSelchangeLanguage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLanguage message handlers

BOOL CDlgLanguage::OnInitDialog() 
{
	CDialog::OnInitDialog();

// Language stuff
	((CStatic *) GetDlgItem (IDC_STATIC1))->SetWindowText (CTranslate::ReadString (184, "English"));
	((CButton *) GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (36, "OK"));

	SetWindowText (CTranslate::ReadString (185, "Edit language"));

// Initialize the listbox
	LONG lStyle = m_pEnglish.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT;
	m_pEnglish.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);
	m_pEnglish.InsertColumn(0, _T("Information"), LVCFMT_LEFT, 800, 0);

// Fill the english list
	for (int i = 0; i < TextSize; i++)	{
		m_pEnglish.InsertItem (i, TranslateText[i]);
	}
	

// Fill the combobox with languages
	HANDLE hSearch;
	WIN32_FIND_DATA FileData; 
	bool bDone;
	CString szPath;
	szPath = GetProgramPath ();
	hSearch = FindFirstFile(szPath + "\\Language\\*.ini", &FileData);
	if (hSearch == INVALID_HANDLE_VALUE) 
		bDone = TRUE;
	else 
		bDone = FALSE;

	while (bDone == FALSE)	{
		m_pLanguage.AddString (FileData.cFileName);		
		

		if (!FindNextFile(hSearch, &FileData)) 
			bDone = TRUE; 
	}

	FindClose (hSearch);
	m_pLanguage.SetItemHeight (0, 17);

// Select the language we are using (by default, English.ini)
	if (m_szLanguageIni == "English.ini")
		m_pLanguage.SelectString (0,FileData.cFileName);
	else
		m_pLanguage.SelectString (0, m_szLanguageIni);

// Change the font
	LOGFONT lf;                        
	memset(&lf, 0, sizeof(LOGFONT));   
	lf.lfHeight = 15;                  
	lf.lfWeight = FW_EXTRALIGHT; 
	_tcscpy/*strcpy*/(lf.lfFaceName, _T("Microsoft Sans Serif"));
	m_font.CreateFontIndirect(&lf);    
	m_pLanguage.SetFont (&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLanguage::OnClickEnglish(NMHDR* pNMHDR, LRESULT* pResult) 
{
// We have selected an english word -> show the translated word
	m_iRow = m_pEnglish.GetNextItem (-1, LVNI_SELECTED);

	m_szOtherLanguage = CTranslate::ReadString (m_iRow, "", GetProgramPath () + "\\Language\\" + m_szLanguageIni);
	UpdateData (FALSE);


	*pResult = 0;
}

void CDlgLanguage::OnChangeOtherlanguage() 
{
// We have updated the control
	if (m_iRow == -1)
		return;

	m_bAskToSave = TRUE;
	m_bChanged = TRUE;
}

void CDlgLanguage::OnKillfocusOtherlanguage() 
{
// Check if we have updated the control and written in it -> save the new word
	if (m_bChanged)	{

	// Update the row
		UpdateData ();
		CTranslate::SaveString (m_iRow, m_szOtherLanguage, GetProgramPath () + "\\Language\\" + m_szLanguageIni);//m_szIniFile);

		m_bChanged = FALSE;
	}
}

void CDlgLanguage::OnSelchangeLanguage() 
{
// Remember the ini-file the user has selected
	int iIndex = m_pLanguage.GetCurSel ();
	m_pLanguage.GetLBText (iIndex, m_szLanguageIni);
	
}

void CDlgLanguage::OnOK() 
{
	OnKillfocusOtherlanguage ();
	
// Should we email the ini-files?
	if (m_bAskToSave)	{
		CString szTemp;
		szTemp.Format (_T("%s\n%s\n\n%s"), CTranslate::ReadString (188, _T("Since you have changed one or more language ini-files. We at A Note would appreciate it very much if you want to share the file with us.")), CTranslate::ReadString (189, _T("By doing so other of users may use your language-file.")), CTranslate::ReadString (190, _T("Do you want to send your language ini-files to A Note's author?")));
		if (MessageBox (szTemp, _T("A Note"), MB_YESNO) == IDYES)	{
			EmailIniFiles ();
		}
	}

	CDialog::OnOK();
}

void CDlgLanguage::EmailIniFiles()
{
// Email alla ini-files to A Note's creator

//Create the message
	CMapiMessage message;

//Setup the all the recipient types for this message
	message.AddMultipleRecipients(_T("brummelisa@users.sourceforge.net"), CMapiMessage::TO);

//Add the Subject and Body
	CString szText;
	message.m_sBody = _T("I have changed in one of the ini-files and wishes to send them to the author of A Note");
	message.m_sSubject = _T("Language-file updated");

// Search after all ini-files and add them
	HANDLE hSearch;
	WIN32_FIND_DATA FileData; 
	bool bDone;
	CString szPath;
	szPath = GetProgramPath ();
	hSearch = FindFirstFile(szPath + _T("\\Language\\*.ini"), &FileData);
	if (hSearch == INVALID_HANDLE_VALUE) 
		bDone = TRUE;
	else 
		bDone = FALSE;

	while (bDone == FALSE)	{
		message.m_Attachments.Add (szPath + _T("\\Language\\") + FileData.cFileName);		
		
		if (!FindNextFile(hSearch, &FileData)) 
			bDone = TRUE; 
	}

	FindClose (hSearch);


//connect to server
	CMapiSession connection;
    BOOL bLogon = FALSE;
    bLogon = connection.SharedLogon();

	if (!bLogon)       {
	}
	else       {

	//Send the message
        BOOL bSuccess = FALSE;

		if (!connection.Send(message, 1, 1, this))         {
			CString sMsg;
			sMsg.Format(_T("%s\nError: %d"), CTranslate::ReadString (25, "Couldn't send message!"), connection.GetLastError());
			AfxMessageBox(sMsg, MB_ICONSTOP);
		}
	}		
}
