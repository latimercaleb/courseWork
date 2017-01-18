// RecycleBin.h: interface for the CRecycleBin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECYCLEBIN_H__7FE1B215_40E6_4268_B8FB_5D5C92578617__INCLUDED_)
#define AFX_RECYCLEBIN_H__7FE1B215_40E6_4268_B8FB_5D5C92578617__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRecycleBin  
{
public:
	void SaveDeletedNote(void *pNote);
	CRecycleBin();
	virtual ~CRecycleBin();

protected:
	void SaveDeletedNotes ();
	void AddDeletedNote (void *Note);

// Struct that holds the key and it value in the XML file
	struct tagCString	{
		CString szName;
		CString szValue;	
	};
	void ParseXML					();
	void GetXMLChildren				(MSXML2::IXMLDOMNodePtr pParent);
	void GetXMLChild				(MSXML2::IXMLDOMNodePtr pChild);

private:
	MSXML2::IXMLDOMDocumentPtr m_plDomDocument;
	MSXML2::IXMLDOMElementPtr m_pDocRoot;
	CList <tagCString, tagCString&>	m_sString;			// The strings in the XML file
	CList <tagNote, tagNote&> m_pNote;					// The notes in the file deleted notes.xml

};

#endif // !defined(AFX_RECYCLEBIN_H__7FE1B215_40E6_4268_B8FB_5D5C92578617__INCLUDED_)
