// Xml.cpp: implementation of the CXml class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "a note.h"
#include "Xml.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	const CString	m_szXmlHeader = _T("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>");

CXml::CXml()
{
	m_szRecycleBinXml	= _T("");
	m_szSaveXml			= _T("");
	m_szUploadXml		= _T("");
}

CXml::~CXml()
{

}

CString CXml::GetDeleteXml()
{
// We want to delete all the notes on the server.
// We can delete all the notes on the server by uploading 0 notes
	CString szXML;

	szXML.Format (_T("%s<notes><note></note></notes>"), m_szXmlHeader);

	return szXML;
}

void CXml::StartCreateRecycleBinXml ()
{
	m_szRecycleBinXml.Format (_T("%s<deleted>"),m_szXmlHeader);
}

void CXml::CreateRecycleBinXml (tagNote note)
{
	ASSERT (!m_szRecycleBinXml.IsEmpty ());
	CRect rc1, rc2;
	CString szTemp;

	rc1 = note.cRect;
	rc2 = note.cRectPosition;
	szTemp.Format (_T("<note noteid=\"%s\" noteversion=\"%d\" dockedleft=\"%s\" dockedtop=\"%s\" dockedright=\"%s\" dockedbottom=\"%s\" alarmtime=\"%s\" usealarm=\"%s\" title=\"%s\" visible=\"%s\" notecolor=\"%d\" positionleft=\"%d\" positiontop=\"%d\" width=\"%d\" height=\"%d\" slided-left=\"%s\" slided-right=\"%s\" slidepositionleft=\"%d\" slidepositiontop=\"%d\" slidepositionright=\"%d\" slidepositionbottom=\"%d\">\n"),
		StringEncode (note.szNoteID),
		note.iNoteVersion, 
		note.bDockedLeft ?					_T("true") : _T("false"), 
		note.bDockedTop ?					_T("true") : _T("false"), 
		note.bDockedRight ?					_T("true") : _T("false"), 
		note.bDockedBottom ? _T("true") :	_T("false"), 
		StringEncode (note.szAlarmTime), 
		note.bUseAlarm ?					_T("true") : _T("false"), 
		StringEncode (note.szTitle), 
		note.bVisible ?						_T("true") : _T("false"), 
		note.cfNoteColor, 
		rc1.left, 
		rc1.top, 
		rc1.right, 
		rc1.bottom,
		note.bSlidedLeft ?					_T("true") : _T("false"),
		note.bSlidedRight ?					_T("true") : _T("false"),
		rc2.left,
		rc2.top,
		rc2.right,
		rc2.bottom);

	m_szRecycleBinXml += szTemp;

	szTemp.Format (_T("%s</note>"), StringEncode (note.szText));
	m_szRecycleBinXml += szTemp;

}

void CXml::EndCreateRecycleBinXml ()
{
	m_szRecycleBinXml += _T("</deleted>");
}


void CXml::StartCreateSaveXml ()
{
	m_szSaveXml.Format (_T("%s<save version=\"%s\"><notes>"),m_szXmlHeader, GetProgramVersion ());

}

void CXml::CreateSaveXml (void *pNote)
{
	ASSERT (!m_szSaveXml.IsEmpty ());
	ASSERT (pNote != NULL);

	m_szSaveXml += GetOneNoteXml (pNote);
}

void CXml::EndCreateSaveXml ()
{
	m_szSaveXml += _T("</notes>\n</save>");
}


void CXml::StartCreateUploadXml ()
{
	m_szUploadXml.Format (_T("%s<notes>"),m_szXmlHeader);
}

void CXml::CreateUploadXml (void *pNote)
{
	ASSERT (!m_szUploadXml.IsEmpty ());
	ASSERT (pNote != NULL);

	CNote *note = (CNote *) pNote;

// Create the xml for one note
	CString szXML, szTemp;

	m_szUploadXml += _T("<note>");
	szTemp.Format (_T("<noteversion>%d</noteversion>"),note->GetNoteVersion ());
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<noteid>%s</noteid>"), StringEncode (note->GetNoteID ()));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<alarmtime>%s</alarmtime>"), StringEncode (note->GetAlarm ().Format (_T("%m/%d/%Y %H:%M:%S"))));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<usealarm>%s</usealarm>"), note->GetUseAlarm () ? _T("true") : _T("false"));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<title>%s</title>"),StringEncode (note->GetTitle ()));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<visible>%s</visible>"), note->GetVisible () ? _T("true") : _T("false"));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<notecolor>%d</notecolor>"),note->GetNoteColor ());
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<positionleft>%d</positionleft>"),note->GetPosition ().left);
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<positiontop>%d</positiontop>"),note->GetPosition ().top);
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<width>%d</width>"),note->GetPosition ().right);
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<height>%d</height>"),note->GetPosition ().bottom);
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<text>%s</text>"), StringEncode (note->GetText ()));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<dockedleft>%s</dockedleft>"), note->GetDockedLeft () ? _T("true") : _T("false"));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<dockedtop>%s</dockedtop>"), note->GetDockedTop () ? _T("true") : _T("false"));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<dockedright>%s</dockedright>"), note->GetDockedRight () ? _T("true") : _T("false"));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<dockedbottom>%s</dockedbottom>"), note->GetDockedBottom () ? _T("true") : _T("false"));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<slided-left>%s</slided-left>"), note->GetSlidedLeft () ? _T("true") : _T("false"));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<slided-right>%s</slided-right>"), note->GetSlidedRight () ? _T("true") : _T("false"));
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<slidepositionleft>%d</slidepositionleft>"), note->GetSlidePosition ().left);
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<slidepositiontop>%d</slidepositiontop>"), note->GetSlidePosition ().top);
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<slidepositionright>%d</slidepositionright>"), note->GetSlidePosition ().right);
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<slidepositionbottom>%d</slidepositionbottom>"), note->GetSlidePosition ().bottom);
	m_szUploadXml += szTemp;
	szTemp.Format (_T("<readable-note-text>%s</readable-note-text>"), StringEncode (note->GetReadableText ()));
	m_szUploadXml += szTemp;
	m_szUploadXml += _T("</note>");
}

void CXml::EndCreateUploadXml ()
{
	m_szUploadXml += _T("</notes>");
}

CString CXml::GetOneNoteXml(void *pNote)
{
	CNote *note = (CNote *) pNote;

	CRect rc1, rc2;
	CString szTemp;
	CString szXML;
	rc1 = note->GetPosition ();
	rc2 = note->GetSlidePosition ();
	szTemp.Format (_T("<note noteid=\"%s\" noteversion=\"%d\" dockedleft=\"%s\" dockedtop=\"%s\" dockedright=\"%s\" dockedbottom=\"%s\" alarmtime=\"%s\" usealarm=\"%s\" title=\"%s\" visible=\"%s\" notecolor=\"%d\" positionleft=\"%d\" positiontop=\"%d\" width=\"%d\" height=\"%d\" slided-left=\"%s\" slided-right=\"%s\" slidepositionleft=\"%d\" slidepositiontop=\"%d\" slidepositionright=\"%d\" slidepositionbottom=\"%d\">\n"),
		StringEncode (note->GetNoteID ()),
		note->GetNoteVersion (), 
		note->GetDockedLeft () ? _T("true") : _T("false"), 
		note->GetDockedTop () ? _T("true") : _T("false"), 
		note->GetDockedRight () ? _T("true") : _T("false"), 
		note->GetDockedBottom () ? _T("true") : _T("false"), 
		StringEncode (note->GetAlarm ().Format (_T("%m/%d/%Y %H:%M:%S"))), 
		note->GetUseAlarm () ? _T("true") : _T("false"), 
		StringEncode (note->GetTitle ()), 
		note->GetVisible () ? _T("true") : _T("false"), 
		note->GetNoteColor (), 
		rc1.left, 
		rc1.top, 
		rc1.right, 
		rc1.bottom,
		note->GetSlidedLeft () ? _T("true") : _T("false"),
		note->GetSlidedRight () ? _T("true") : _T("false"),
		rc2.left,
		rc2.top,
		rc2.right,
		rc2.bottom);

	szXML += szTemp;

	szTemp.Format (_T("%s</note>\n"), StringEncode (note->GetText ()));
	szXML += szTemp;

	return szXML;
}
