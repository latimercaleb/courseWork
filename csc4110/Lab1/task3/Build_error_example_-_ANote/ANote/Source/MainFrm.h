#if !defined(AFX_MAINFRM_H__4A5AD703_72B9_4F98_BE90_79943A2981C9__INCLUDED_)
#define AFX_MAINFRM_H__4A5AD703_72B9_4F98_BE90_79943A2981C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "ChildView.h"
#include "SystemTray.h"
#include "Note.h"
#include "afxtempl.h"
#include "BCMenu.h"
#include <afxmt.h>

class CMainFrame : public CFrameWnd
{
	
public:
	void Load				(CString szFileName);
	BOOL Send				(CString szServerAddress, CString szPath, CString szXML, CString &szDataBack);
	bool ShowAlarmDialog	();
	void SendNotesToWeb		();
	void ParseXML			(CString szXML);
	CMainFrame();

	void CreateMinimizedMenu(BCMenu *pMainMenu, BCMenu *pMinimized); // Show any minimized note on the system tray menu
	void NoAnimate			();									// Stop animate the tray icon
	void AnimateTrayAlarm	();									// We have an alarm -> animate the tray icon
	void DeleteNote			(void *pNote, bool bSaveDeletedNote);// Delete one note from the list
	void AddNote			(void *pNote);						// Add one note to the list

	HMENU NewMenu();
	BCMenu m_menu;

	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow			(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg					(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid				() const;
	virtual void Dump						(CDumpContext& dc) const;
#endif
	CChildView    m_wndView;

// XML ---
	protected:
// Struct that holds the key and it value in the XML file
	struct tagCString	{
		CString szName;
		CString szValue;	
	};

	MSXML2::IXMLDOMDocumentPtr m_plDomDocument;
	MSXML2::IXMLDOMElementPtr m_pDocRoot;
	CList <tagCString, tagCString&>	m_sString;			// The strings in the XML file
	CString m_szStatus;

	void GetXMLChildren				(MSXML2::IXMLDOMNodePtr pParent);
	void GetXMLChild				(MSXML2::IXMLDOMNodePtr pChild);

// -------


protected: 
// Since the program don't use ::Serialize anymore, we save the notes with this one
	void Save								(CString szFileName);
	void AnimateTrayUpload					();
	void AnimateTrayDownload				();
	void UseUser							();
	void GetNotesFromServer					();
	void CheckForNewerVersion				();
	void SendPasswordToEmail				();
	void CreateNewUser						();	
	CString CreateSendXML					();

	BOOL DateGreaterThanOrEqual				(COleDateTime &odt1, COleDateTime &odt2);
	BOOL DatesEqual							(COleDateTime &odt1, COleDateTime &odt2);


	DECLARE_DYNAMIC(CMainFrame)

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate					(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus					(CWnd *pOldWnd);
	afx_msg void OnTraymainNewnote			();
	afx_msg void OnTraymainRestoreall		();
	afx_msg void OnTraymainMinimizeall		();
	afx_msg void OnTraymainOptions			();
	afx_msg void OnTraymainStayontop		();
	afx_msg void OnUpdateTraymainStayontop	(CCmdUI* pCmdUI);
	afx_msg void OnClose					();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnTraymainVisitanotewebsite();
	afx_msg void OnUpdateTraymainMinimizeall(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTraymainRestoreall(CCmdUI* pCmdUI);
	afx_msg void OnTraymainImportexportImport();
	afx_msg void OnRestoreMinimizedNote (UINT nID);
	afx_msg void OnTraymainImportexportExport();
	afx_msg HRESULT OnGetNotesThread (WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT OnGetLatesVersionThread (WPARAM wParam, LPARAM lParam);
	afx_msg void OnTraymainUploaddownloadDownloadnotes();
	afx_msg void OnTraymainUploaddownloadUploadnotes();
	afx_msg void OnUpdateTraymainUploaddownloadUploadnotes(CCmdUI* pCmdUI);
	afx_msg void OnTraymainSendbugg();
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);	
	afx_msg void OnTraymainFaq();
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnTraymainRecyclebin();
	afx_msg void OnTraymainCheckforupdates();
	afx_msg void OnPressedLeftButtonOnTrayIcon ();
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()

private:
	CSystemTray				m_TrayIcon;							// The system tray
	CList <void *, void *>	m_pNotes;							// The note list
	CString m_szVersion;
	bool	m_bNotesAreHidden;									// TRUE -> The user has left click once on the tray icon and hidden all notes. We must have this variable so that we know if the notes should be hidded or not
};

//{{AFX_INSERT_LOCATION}}

#endif 
