// DlgRecycleBin.cpp : implementation file
//

#include "stdafx.h"
#include "a note.h"
#include "DlgRecycleBin.h"
#include "DlgRecycleBinHelp.h"
#include "ErrorLog.h"
#include "xml.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecycleBin dialog


CDlgRecycleBin::CDlgRecycleBin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecycleBin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecycleBin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRecycleBin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecycleBin)
	DDX_Control(pDX, IDC_TITLES, m_pTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecycleBin, CDialog)
	//{{AFX_MSG_MAP(CDlgRecycleBin)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_RESTORE, OnRestore)
	ON_LBN_DBLCLK(IDC_TITLES, OnDblclkTitles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecycleBin message handlers

void CDlgRecycleBin::OnDelete() 
{
// Delete the selected notes
// They will be deleted permanently

// Loop through the linked list and erase the marked notes
// Create then a new delete notes.xml
// Fill the title list with the current ones

// We have to have atleast one title marked
	if (m_pTitle.GetCount () == 0)
		return;

// Do the user wants to delete this notes?
	CString szTemp;
	szTemp.Format (_T("%s\n\n%s"), CTranslate::ReadString (151, _T("Do you want to delete the note?")), CTranslate::ReadString (152, _T("The note will be deleted permanently!")));
	if (MessageBox (szTemp, _T("A Note"), MB_ICONEXCLAMATION | MB_YESNO) == IDNO)
		return;

// Loop through the linked list and erase the marked note
	DeleteMarkedNotes ();

// Create then a new delete notes.xml
	CreateDeleteNotesXml ();

// Fill the title list with the current ones
	FillTheList ();
}

void CDlgRecycleBin::DeleteMarkedNotes ()
{
	POSITION pos;

	if (theApp.m_bSortRecycleBinDescending)
		pos = m_pNote.GetTailPosition ();
	else
		pos = m_pNote.GetHeadPosition ();

	POSITION delpos;
	int rgIndex[BUFFERSIZE];
	m_pTitle.GetSelItems (BUFFERSIZE, rgIndex);
	int iRow = 0;
	int iCount = 0;

	while (pos)	{
		delpos = pos;
		tagNote note;

		if (theApp.m_bSortRecycleBinDescending)
			note = m_pNote.GetPrev (pos);
		else
			note = m_pNote.GetNext (pos);

		if (iRow == rgIndex[iCount])	{

			m_pNote.RemoveAt (delpos);
			iCount++;
		}
		
		iRow++;
	}
}

void CDlgRecycleBin::CreateDeleteNotesXml ()
{
	CString szFile, szXML, szTemp, szXmlStart;

	CXml xml;
	
	CStdioFile fp;
	CRect rc1, rc2;
	POSITION pos;

	pos = m_pNote.GetHeadPosition ();

// Create the xml-header
	xml.StartCreateRecycleBinXml ();

// Loop through the notes and create the xml
	while (pos)	{
			tagNote note = m_pNote.GetNext (pos);
			xml.CreateRecycleBinXml (note);
	}

// Add the end tag and receive the created xml
	xml.EndCreateRecycleBinXml ();
	szXML = xml.GetCreateRecycleBinXml ();

// Save the note now
	szFile.Format (_T("%s\\deleted notes.xml"), GetApplicationDataPath ());

	DeleteFile (szFile);

	if (!fp.Open (szFile, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open the deleted notes.xml"));
		return;
	}

	TRY
	{
#if (defined (UNICODE) || defined (_UNICODE))
	int iLength, iMultibyte;
	CString szResult;

	iLength	= szXML.GetLength ();
	WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
	char *pcDest = new char [2 * (iLength + 1)];

// To UTF-8
	iMultibyte = WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
	fp.Write (pcDest, iLength);
	delete []pwcUnicode;
	delete []pcDest;
#else
		fp.Write (szXML, szXML.GetLength ());
#endif
		fp.Close ();
	}
	CATCH (CFileException, e)
	{
		CErrorLog::CErrorLog (ERR, _T("Could not write file deleted notes.xml"));
		return;
	}
	END_CATCH
}


void CDlgRecycleBin::OnRestore() 
{
// Restore the selected notes

// We have to have atleast one title marked
	if (m_pTitle.GetCount () == 0)
		return;
	
// Create a temporarilly xml-file and import the note
	CString szImport;
	szImport.Format (_T("%s\\import.xml"), GetApplicationDataPath ());
	CreateImportXml (szImport);

// Import the notes
	ImportNotes (szImport);

// Erase then the xml-file
	DeleteFile (szImport);

// Erase the restored notes from the list
	CreateDeleteNotesXml ();
	FillTheList ();
}

BOOL CDlgRecycleBin::OnInitDialog() 
{
	CDialog::OnInitDialog();

// Language stuff
	((CStatic *) GetDlgItem (IDC_STATIC1))->SetWindowText (CTranslate::ReadString (146, _T("Title")));
	((CButton *) GetDlgItem (IDC_DELETE))->SetWindowText (CTranslate::ReadString (147, _T("Delete")));
	((CButton *) GetDlgItem (IDC_RESTORE))->SetWindowText (CTranslate::ReadString (148, _T("Restore")));
	((CButton *) GetDlgItem (IDOK))->SetWindowText (CTranslate::ReadString (149, _T("Close")));

	SetWindowText (CTranslate::ReadString (150, _T("Recycle bin")));


// See if it's the first time the user uses the recycle bin -> show the help dialog
	if (AfxGetApp ()->GetProfileInt (_T("Settings\\Options"), _T("Show Using Recycle Bin Help"), 1) == 1)	{

		CDlgRecycleBinHelp dlg;
		dlg.DoModal ();

		AfxGetApp ()->WriteProfileInt (_T("Settings\\Options"), _T("Show Using Recycle Bin Help"), dlg.m_bShowNextTime);
	}

// Fill the list
	FillTheList ();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDlgRecycleBin::ParseXML()
{
// Parse the XML that was received from the server

// Save the XML
	CString szXMLFile;
	szXMLFile.Format (_T("%s\\deleted notes.xml"), GetApplicationDataPath ());

// Convert xml file name string to something COM can handle (BSTR)
	_bstr_t bstrFileName;
	bstrFileName = szXMLFile.AllocSysString();

// Call the IXMLDOMDocumentPtr's load function to load the XML document
	variant_t vResult;
	vResult = m_plDomDocument->load (bstrFileName);
	if (((bool)vResult) == TRUE) 	{
	// now that the document is loaded, we need to initialize the root pointer
		m_pDocRoot = m_plDomDocument->documentElement;
	}
	else	{
		CErrorLog::CErrorLog (ERR, _T("Could not parse the deleted notes.xml-file in Recycle bin"));
		return FALSE;
	}

	GetXMLChildren (m_pDocRoot);

	return TRUE;
}

void CDlgRecycleBin::FillTheList()
{
// Erase any title
	m_pTitle.ResetContent ();
	m_pNote.RemoveAll ();

// Open the deleted notes.xml and fill the list with the note's title

// Initialize the XML-Parser	
	::CoInitialize(NULL);
	HRESULT hr = m_plDomDocument.CreateInstance(::CLSID_DOMDocument);
	if (FAILED(hr))		{
		CErrorLog::CErrorLog (ERR, _T("Could not initialize the xml parser"));
		return;
	}

// Parse the xml and fill the linked list
	if (!ParseXML ())	{
		return;
	}

// Walk through the linked list and fill in the titles in the list box (the latest first)
	POSITION pos;
	if (theApp.m_bSortRecycleBinDescending)
		pos = m_pNote.GetTailPosition ();
	else
		pos = m_pNote.GetHeadPosition ();

	while (pos)	{
		tagNote note;

		if (theApp.m_bSortRecycleBinDescending)
			note = m_pNote.GetPrev (pos);
		else
			note = m_pNote.GetNext (pos);

		m_pTitle.AddString (note.szTitle);
	}
}


void CDlgRecycleBin::GetXMLChildren(MSXML2::IXMLDOMNodePtr pParent)
{	
// Determine what type of XML document it is	
	_bstr_t sType = pParent->GetnodeName ( ); 	

// Display the current node's name
	GetXMLChild(pParent);

// Simple for loop to get all children
	for (MSXML2::IXMLDOMNodePtr pChild = pParent->firstChild; NULL != pChild; pChild = pChild->nextSibling) 	{
	// For each child, call this function so that we get its children as well
		GetXMLChildren(pChild);
	}
}


void CDlgRecycleBin::GetXMLChild(MSXML2::IXMLDOMNodePtr pChild)
{
	CString szName, szValue, szVersion;

	MSXML2::IXMLDOMNamedNodeMapPtr pAttribs = pChild->Getattributes(); 
	if (pAttribs != NULL)	{ 
		long nAttriCnt = pAttribs->Getlength(); 

		for(int i = 0; i < nAttriCnt; ++i)	{ 
			MSXML2::IXMLDOMNodePtr pAttrib = pAttribs->Getitem(i); 
			if(pAttrib != NULL) { 
				_bstr_t sName = pAttrib->GetnodeName ( ); 	
				_variant_t vVal = pAttrib->GetnodeValue ( ); 
		
				AfxBSTR2CString (&szName, sName);
				szValue = (const char *) _bstr_t(vVal);

				tagCString string;
				string.szName = szName;
				string.szValue = szValue;
				m_sString.AddTail (string);

			} 
		} 
	} 


	if (MSXML2::NODE_TEXT != pChild->nodeType)	 {
		CString szName, szData, szText;
		AfxBSTR2CString (&szName, pChild->nodeName);

		if (szName == _T("note"))	{

			POSITION pos = m_sString.GetHeadPosition ();
			tagNote note;

			while (pos)	{
				tagCString item = m_sString.GetNext (pos);
				
				if (item.szName == _T("noteversion"))	note.iNoteVersion	= _ttoi (item.szValue);
				if (item.szName == _T("notecolor"))		note.cfNoteColor	= _ttoi (item.szValue);
				if (item.szName == _T("positionleft"))	note.cRect.left		= _ttoi (item.szValue);
				if (item.szName == _T("positiontop"))	note.cRect.top		= _ttoi (item.szValue);
				if (item.szName == _T("width"))			note.cRect.right	= _ttoi (item.szValue);
				if (item.szName == _T("height"))		note.cRect.bottom	= _ttoi (item.szValue);
				if (item.szName == _T("noteid"))		note.szNoteID		= item.szValue;
				if (item.szName == _T("alarmtime"))		note.szAlarmTime	= item.szValue;
				if (item.szName == _T("title"))			note.szTitle		= item.szValue;
				if (item.szName == _T("usealarm"))		item.szValue	== _T("true") ? note.bUseAlarm		= TRUE : note.bUseAlarm		= FALSE;
				if (item.szName == _T("visible"))		item.szValue	== _T("true") ? note.bVisible		= TRUE : note.bVisible		= FALSE;
				if (item.szName == _T("dockedleft"))	item.szValue	== _T("true") ? note.bDockedLeft	= TRUE : note.bDockedLeft	= FALSE;
				if (item.szName == _T("dockedtop"))		item.szValue	== _T("true") ? note.bDockedTop		= TRUE : note.bDockedTop	= FALSE;
				if (item.szName == _T("dockedright"))	item.szValue	== _T("true") ? note.bDockedRight	= TRUE : note.bDockedRight	= FALSE;
				if (item.szName == _T("dockedbottom"))	item.szValue	== _T("true") ? note.bDockedBottom	= TRUE : note.bDockedBottom	= FALSE;
				if (item.szName == _T("slided-right"))			item.szValue	== _T("true") ? note.bSlidedRight	= TRUE : note.bSlidedRight	= FALSE;
				if (item.szName == _T("slided-left"))			item.szValue	== _T("true") ? note.bSlidedLeft	= TRUE : note.bSlidedLeft	= FALSE;
				if (item.szName == _T("slidepositionleft"))		note.cRectPosition.left		= _ttoi (item.szValue);
				if (item.szName == _T("slidepositiontop"))		note.cRectPosition.top		= _ttoi (item.szValue);
				if (item.szName == _T("slidepositionright"))	note.cRectPosition.right	= _ttoi (item.szValue);
				if (item.szName == _T("slidepositionbottom"))	note.cRectPosition.bottom	= _ttoi (item.szValue);	
			}

			AfxBSTR2CString (&szText, pChild->text);

		// Base 64 decode
			note.szNoteID		= StringDecode (note.szNoteID);
			note.szTitle		= StringDecode (note.szTitle);
			note.szAlarmTime	= StringDecode (note.szAlarmTime);
			note.szText			= StringDecode (szText);

			m_pNote.AddTail (note);
			m_sString.RemoveAll ();
		}
	}
}

void CDlgRecycleBin::OnDblclkTitles() 
{
// To prevent the cursor to jump around on the screen because the notes are minimized,
// we fake that the cursor shouldn't move when the notes are minimized
	theApp.m_bMinimizeMoveCursor = FALSE;

// Find the only one that the user double clicked on -> Create that note
	int iIndex;
	
// Find the note's title
	iIndex = m_pTitle.GetCaretIndex ();

// Walk through the linked list and create the note when found
	POSITION pos;
	if (theApp.m_bSortRecycleBinDescending)
		pos = m_pNote.GetTailPosition ();
	else
		pos = m_pNote.GetHeadPosition ();

	while (pos)	{
		tagNote note;

		if (theApp.m_bSortRecycleBinDescending)
			note = m_pNote.GetPrev (pos);
		else
			note = m_pNote.GetNext (pos);

	// Are we there yet? -> Create the note
		if (iIndex == 0)	{

				CNote *pNote = new CNote ();
				pNote->Create (IDD_NOTE, this);
	
	
				pNote->SetNoteID			(note.szNoteID);
				pNote->SetNoteVersion		(note.iNoteVersion);;	
				pNote->SetDockedLeft		(note.bDockedLeft, FALSE);
				pNote->SetDockedTop			(note.bDockedTop, FALSE);
				pNote->SetDockedRight		(note.bDockedRight, FALSE);
				pNote->SetDockedBottom		(note.bDockedBottom, FALSE);
				pNote->SetUseAlarm			(note.bUseAlarm);
				pNote->SetTitle				(note.szTitle);
				pNote->SetText				(note.szText);
				pNote->SetVisible			(note.bVisible);
				pNote->SetNoteColor			(note.cfNoteColor);
				pNote->SetPosition			(note.cRect, FALSE);
				COleDateTime pTime;
				pTime.ParseDateTime			(note.szAlarmTime);//, LOCALE_NOUSEROVERRIDE);
				pNote->SetAlarm				(pTime);

				pNote->BelongsToRecycleBin	();
				pNote->SetSlideLeft			(note.bSlidedLeft, FALSE);
				pNote->SetSlideRight		(note.bSlidedRight, FALSE);
				pNote->SetSlidePosition		(note.cRectPosition, FALSE);

				pNote->Initialize			();
		}

		iIndex--;
	}

// To prevent the cursor to jump around on the screen because the notes are minimized,
// we fake that the cursor shouldn't move when the notes are minimized
	theApp.m_bMinimizeMoveCursor = TRUE;
}

void CDlgRecycleBin::ImportNotes(CString szFile)
{
	CMainFrame *pMain = (CMainFrame*) ::AfxGetMainWnd ();

// To prevent the cursor to jump around on the screen because the notes are minimized,
// we fake that the cursor shouldn't move when the notes are minimized
	theApp.m_bMinimizeMoveCursor = FALSE;

	pMain->Load (szFile);

// We alow the cursor to move when the notes are minimized (see a bit up in the code here)
	theApp.m_bMinimizeMoveCursor = AfxGetApp ()->GetProfileInt (_T("Settings\\Options"), _T("When Minimized Move Cursor"), 1);

}

void CDlgRecycleBin::CreateImportXml(CString szFile)
{
// Create the import file where the restored note will be in

	POSITION pos;
	CString szXML, szTemp;
	CRect rc1, rc2;

	if (theApp.m_bSortRecycleBinDescending)
		pos = m_pNote.GetTailPosition ();
	else
		pos = m_pNote.GetHeadPosition ();

	POSITION delpos;
	int rgIndex[BUFFERSIZE];
	m_pTitle.GetSelItems (BUFFERSIZE, rgIndex);
	int iRow = 0;
	int iCount = 0;

	CXml xml;
	xml.StartCreateRecycleBinXml ();
	
	while (pos)	{
		delpos = pos;
		tagNote note;

		if (theApp.m_bSortRecycleBinDescending)
			note = m_pNote.GetPrev (pos);
		else
			note = m_pNote.GetNext (pos);

		if (iRow == rgIndex[iCount])	{

			xml.CreateRecycleBinXml (note);
		

		// Erase this note from the list
			m_pNote.RemoveAt (delpos);
		}
		
		iRow++;
	}

	xml.EndCreateRecycleBinXml ();
	szXML = xml.GetCreateRecycleBinXml ();

// Save the note now
	CStdioFile fp;
	if (!fp.Open (szFile, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open the import notes.xml"));
		return;
	}

	TRY
	{
#if (defined (UNICODE) || defined (_UNICODE))
	int iLength, iMultibyte;
	CString szResult;

	iLength	= szXML.GetLength ();
	WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
	char *pcDest = new char [2 * (iLength + 1)];

// To UTF-8
	iMultibyte = WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
	fp.Write (pcDest, iLength);
	delete []pwcUnicode;
	delete []pcDest;
#else
		fp.Write (szXML, szXML.GetLength ());
#endif
		fp.Close ();
	}
	CATCH (CFileException, e)
	{
		CErrorLog::CErrorLog (ERR, _T("Could not write file import notes.xml"));
		return;
	}
	END_CATCH
}
