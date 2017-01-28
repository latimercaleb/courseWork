// Xml.h: interface for the CXml class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XML_H__E0170EE2_42D0_4542_9101_57E1AFEAC139__INCLUDED_)
#define AFX_XML_H__E0170EE2_42D0_4542_9101_57E1AFEAC139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXml  
{
public:
	CString GetDeleteXml ();

// The user wants to create the delete xml --------
	void StartCreateRecycleBinXml				();
	void CreateRecycleBinXml					(tagNote note);
	void EndCreateRecycleBinXml					();
	CString GetCreateRecycleBinXml				()			{return m_szRecycleBinXml;};
// ------------------------------------------------

// The user wants to save the notes ---------------
	void StartCreateSaveXml						();
	void CreateSaveXml							(void *pNote);
	void EndCreateSaveXml						();
	CString GetCreateSaveXml					()			{return m_szSaveXml;};
// ------------------------------------------------

// The user wants to upload the notes -------------
	void StartCreateUploadXml					();
	void CreateUploadXml						(void *pNote);
	void EndCreateUploadXml						();
	CString GetCreateUploadXml					()			{return m_szUploadXml;};
// ------------------------------------------------
	CXml();
	virtual ~CXml();

private:
	CString m_szRecycleBinXml;
	CString m_szSaveXml;
	CString	m_szUploadXml;
protected:
	CString GetOneNoteXml (void *pNote);
};

#endif // !defined(AFX_XML_H__E0170EE2_42D0_4542_9101_57E1AFEAC139__INCLUDED_)
