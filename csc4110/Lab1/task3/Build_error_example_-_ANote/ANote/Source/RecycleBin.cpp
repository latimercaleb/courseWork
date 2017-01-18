// RecycleBin.cpp: implementation of the CRecycleBin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "a note.h"
#include "RecycleBin.h"
#include "note.h"
#include "xml.h"
#include <afxpriv.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecycleBin::CRecycleBin()
{

}

CRecycleBin::~CRecycleBin()
{

}


void CRecycleBin::SaveDeletedNote(void *pNote)
{
// The note will be deleted and therefore the note
// and its data will be saved in the file
// \..\A Note\deleted notes.xml

// Read all the notes that are in the file deleted notes.xml
	::CoInitialize(NULL);
	HRESULT hr = m_plDomDocument.CreateInstance(::CLSID_DOMDocument);
	if (FAILED(hr))		{
		CErrorLog::CErrorLog (ERR, "Could not initialize the xml parser");
		return;
	}
	ParseXML ();

// Add the note that wants to be deleted
	AddDeletedNote (pNote);

// Find out if we have hit the total limit -> if so delete the first one
	if (_ttoi (theApp.m_szRecycleBinNumberOfNotes) != 0 && m_pNote.GetCount () > _ttoi (theApp.m_szRecycleBinNumberOfNotes))
		m_pNote.RemoveHead ();

// Save the notes in the file deleted notes.xml
	SaveDeletedNotes ();
}


void CRecycleBin::ParseXML()
{
// Parse the XML that was received from the server
	CString szFile;
	szFile.Format (_T("%s\\deleted notes.xml"), GetApplicationDataPath ());

// Convert xml file name string to something COM can handle (BSTR)
	_bstr_t bstrFileName;
	bstrFileName = szFile.AllocSysString();

// Call the IXMLDOMDocumentPtr's load function to load the XML document
	variant_t vResult;
	vResult = m_plDomDocument->load(bstrFileName);
	if (((bool)vResult) == TRUE) 	{
	// now that the document is loaded, we need to initialize the root pointer
		m_pDocRoot = m_plDomDocument->documentElement;
	}
	else	
		return;

	GetXMLChildren (m_pDocRoot);
}

void CRecycleBin::GetXMLChildren(MSXML2::IXMLDOMNodePtr pParent)
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


void CRecycleBin::GetXMLChild(MSXML2::IXMLDOMNodePtr pChild)
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

void CRecycleBin::AddDeletedNote(void *Note)
{
// Add the deleted note in the linked list (last)
	CNote *pNote = (CNote *) Note;
	tagNote note;

	note.bDockedBottom	= pNote->GetDockedBottom ();
	note.bDockedLeft	= pNote->GetDockedLeft ();
	note.bDockedRight	= pNote->GetDockedRight ();
	note.bDockedTop		= pNote->GetDockedTop ();
	note.bUseAlarm		= pNote->GetUseAlarm ();
	note.bVisible		= pNote->GetVisible ();
	note.cfNoteColor	= pNote->GetNoteColor ();
	note.cRect			= pNote->GetPosition ();
	note.iNoteVersion	= pNote->GetNoteVersion ();
	note.szAlarmTime	= pNote->GetAlarm ().Format (_T("%m/%d/%Y %H:%M:%S")), 
	note.szNoteID		= pNote->GetNoteID ();
	note.szText			= pNote->GetText ();
	note.szTitle		= pNote->GetTitle ();
	note.bSlidedLeft	= pNote->GetSlidedLeft ();
	note.bSlidedRight	= pNote->GetSlidedRight ();
	note.cRectPosition	= pNote->GetSlidePosition ();
		
	m_pNote.AddTail (note);
}

void CRecycleBin::SaveDeletedNotes()
{
// Save all deleted notes
	CString szFile, szXML, szTemp, szXmlStart;
	CStdioFile fp;
	CRect rc1, rc2;
	POSITION pos;

	CXml xml;
	xml.StartCreateRecycleBinXml ();

	pos = m_pNote.GetHeadPosition ();

	while (pos)	{

		tagNote note = m_pNote.GetNext (pos);

		xml.CreateRecycleBinXml (note);
	}

	xml.EndCreateRecycleBinXml ();
	szXML = xml.GetCreateRecycleBinXml ();

// Save the note now
	szFile.Format (_T("%s\\deleted notes.xml"), GetApplicationDataPath ());

	DeleteFile (szFile);

	if (!fp.Open (szFile, CFile::modeCreate | CFile::modeWrite))	{
			CErrorLog::CErrorLog (INFO, "Could not open the deleted notes.xml");
		return;
	}

	TRY
	{
#if (defined (UNICODE) || defined (_UNICODE))
		int iLength;
		iLength	= szXML.GetLength ();
		WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
		char * pcDest	  = new	char [ 2 * (iLength + 1)];

	// To UTF-8
		WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
		fp.Write (pcDest, iLength);
		delete []pcDest;
		delete []pwcUnicode;
#else
		fp.Write (szXML, szXML.GetLength ());
#endif
		fp.Close ();
	}
	CATCH (CFileException, e)
	{
		CErrorLog::CErrorLog (ERR, "Could not write file deleted notes.xml");
		return;
	}
	END_CATCH
}
