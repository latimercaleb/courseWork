#if !defined(AFX_DLGRECYCLEBIN_H__9CD9F166_5034_4A78_A48F_901B99F3AFB2__INCLUDED_)
#define AFX_DLGRECYCLEBIN_H__9CD9F166_5034_4A78_A48F_901B99F3AFB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 


class CDlgRecycleBin : public CDialog
{
public:
	CDlgRecycleBin(CWnd* pParent = NULL);   

	//{{AFX_DATA(CDlgRecycleBin)
	enum { IDD = IDD_RECYCLEBIN };
	CListBox	m_pTitle;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CDlgRecycleBin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL


protected:
	void CreateImportXml (CString szFile);
	void ImportNotes (CString szFile);
	void DeleteMarkedNotes ();
	void CreateDeleteNotesXml ();
	void FillTheList ();
	bool ParseXML();
	void GetXMLChildren	(MSXML2::IXMLDOMNodePtr pParent);
	void GetXMLChild	(MSXML2::IXMLDOMNodePtr pChild);

	//{{AFX_MSG(CDlgRecycleBin)
	afx_msg void OnDelete();
	afx_msg void OnRestore();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkTitles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()



// For the xml parsing
	struct tagCString	{
		CString szName;
		CString szValue;	
	};

private:
	MSXML2::IXMLDOMDocumentPtr	m_plDomDocument;
	MSXML2::IXMLDOMElementPtr	m_pDocRoot;
	CList <tagCString, tagCString&>	m_sString;			// The strings in the XML file
	CList <tagNote, tagNote&>	m_pNote;				// The linked list that holds every note that is in the deleted notes.xml-file
};

//{{AFX_INSERT_LOCATION}}

#endif
