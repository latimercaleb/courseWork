#if !defined(AFX_NOTE_H__B0DA5563_9C15_40A2_991B_BE8C3F9C9EB0__INCLUDED_)
#define AFX_NOTE_H__B0DA5563_9C15_40A2_991B_BE8C3F9C9EB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "BtnST.h"
#include "AutoRichEditCtrl.h"
#include "NotePosition.h"

class CNote : public CDialog
{
public:

// Used from CMainFrame ---
	void ShowButtons				();
	void HideButtons				();
	void CloseAlarm					();
	void SetBorderStyle				(BOOL bThin);
	void StayNotOnTop				();
	void StayOnTop					();
	void SetTransparancy			(int iNormal, int iMinimized);
	BOOL IsAlarmShouting			()						{return m_bIsAlarmShouting;};
	void ShowAlarm					();
	void Vanish						()						{OnOK ();};
	CNote							(CWnd* pParent = NULL);
	void FixNotePosition			(void *pNote)			{m_pPosition.FixNotePosition (pNote);};
// ------------------------

	void SetButtonColor				(COLORREF cfColor);
	void Initialize					();					// Use it after the data has been loaded from file	

	void RestoreNote				();
	void MinimizeNote				();					

	void AutoIncNoteVersion			()						{m_iNoteVersion++;};

// From Recycle Bin -------
	void BelongsToRecycleBin		()						{m_bBelongsToRecycleBin = TRUE;};
// ------------------------

// Save ---
	CString GetReadableText			();
	CRect GetPosition				();
	CRect GetSlidePosition			();		// Get the position where the note was when the user started to slide it
	BOOL GetVisible					()							{return m_bVisible;};
	COLORREF GetNoteColor			()							{return m_cfNoteColor;};
	CString GetText					()							{return m_pText.GetRTF ();};
	CString GetTitle				()							{return m_szTitle;};
	int GetNoteVersion				()							{return m_iNoteVersion;};
	CString GetNoteID				()							{return m_szNoteID;};
	BOOL GetDockedLeft				()							{return m_pPosition.GetDockedLeft ();};
	BOOL GetDockedTop				()							{return m_pPosition.GetDockedTop ();};
	BOOL GetDockedRight				()							{return m_pPosition.GetDockedRight ();};
	BOOL GetDockedBottom			()							{return m_pPosition.GetDockedBottom ();};
	BOOL GetSlidedRight				()							{return m_pPosition.GetSlidedToRight ();};
	BOOL GetSlidedLeft				()							{return m_pPosition.GetSlidedToLeft ();};

	void SetVisible					(BOOL bVisible)				{m_bVisible		= bVisible;};
	void SetNoteColor				(COLORREF cfColor)			{m_cfNoteColor	= cfColor;};
	void SetPosition				(CRect cRect, bool bFix)	{m_pPosition.SetNotePosition (cRect, this, bFix);};
	void SetText					(CString szText)			{m_szText		= szText;};
	void SetTitle					(CString szTitle)			{m_szTitle		= szTitle;};
	void SetNoteVersion				(int iVersion)				{m_iNoteVersion = iVersion;};
	void SetNoteID					(CString szID)				{m_szNoteID		= szID;};
	void SetDockedLeft				(BOOL bLeft, bool bFix)		{m_pPosition.SetDockedLeft			(bLeft, this, bFix);};
	void SetDockedTop				(BOOL bTop, bool bFix)		{m_pPosition.SetDockedTop			(bTop, this, bFix);};
	void SetDockedRight				(BOOL bRight, bool bFix)	{m_pPosition.SetDockedRight			(bRight, this, bFix);};
	void SetDockedBottom			(BOOL bBottom, bool bFix)	{m_pPosition.SetDockedBottom		(bBottom, this, bFix);};
	void SetSlideRight				(BOOL bSlide, bool bFix)	{m_pPosition.SetSlidedToRight		(bSlide, this, bFix);};
	void SetSlideLeft				(BOOL bSlide, bool bFix)	{m_pPosition.SetSlidedToLeft		(bSlide, this, bFix);};
	void SetSlidePosition			(CRect cRect, bool bFix)	{m_pPosition.SetSlidedNotePosition	(cRect, this, bFix);};
// --------

// Normal alarm ---
	COleDateTime GetAlarm			()							{return m_Alarm ;};
	BOOL GetUseAlarm				()							{return m_bUseAlarm;};
	void SetUseAlarm				(BOOL bAlarm)				{m_bUseAlarm = bAlarm;};
	void SetAlarm					(COleDateTime pAlarm)		{m_Alarm = pAlarm;};
// ----------------

	CButtonST			m_pAlarm;							// The alarm button

	afx_msg void OnContextMenu			(CWnd* pWnd, CPoint point);
	CAutoRichEditCtrl	m_pText;							// The text control
	//{{AFX_DATA(CNote)
	enum { IDD = IDD_NOTE };
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CNote)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange			(CDataExchange* pDX); 
	//}}AFX_VIRTUAL

protected:
// For Slide --
	void RestoreFromRightSlide		();
	void RestoreFromLeftSlide		();
// ------------

	CString GetDefaultTitle			();
	void PaintThinBorder			(CDC *pDC);
	void PaintThickBorder			(CDC *pDC);

	//{{AFX_MSG(CNote)
	virtual BOOL OnInitDialog			();
	afx_msg BOOL OnEraseBkgnd			(CDC* pDC);
	afx_msg void OnPaint				();
	afx_msg void OnDestroy				();
	afx_msg UINT OnNcHitTest			(CPoint point);
	afx_msg void OnSize					(UINT nType, int cx, int cy);
	afx_msg void OnMove					(int x, int y);
	afx_msg void OnCloseNote			();
	afx_msg void OnAlarm				();
	afx_msg void OnMinimize				();
	afx_msg void OnBullet				();
	afx_msg void OnBold					();
	afx_msg void OnItalic				();
	afx_msg void OnStrikeOut			();
	afx_msg void OnUnderline			();
	afx_msg void OnSlideRight			();
	afx_msg void OnSlideLeft			();
	afx_msg void OnPopupmenuCut			();
	afx_msg void OnPopupmenuCopy		();
	afx_msg void OnPopupmenuPaste		();
	afx_msg void OnPopupmenuNotecolor	();
	afx_msg void OnPopupmenuFont		();
	afx_msg void OnNcLButtonDblClk		(UINT nHitTest, CPoint point);
	afx_msg void OnPopupmenuAlarm		();
	afx_msg void OnPopupmenuSettitle	();
	afx_msg void OnTextLink				(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer				(UINT nIDEvent);
	afx_msg void OnRequestResize		(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMoving				(UINT fwSide, LPRECT pRect);
	afx_msg void OnPopupmenuEmail		();
	afx_msg void OnPopupmenuPrint		();
	afx_msg void OnNcMouseMove			(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnDisplayChange		(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
// Buttons ----------------
	CButtonST			m_pBullet;							// The bullet button
	CButtonST			m_pMinimize;						// The minimize button
	CButtonST			m_pClose;							// The close button
	CButtonST			m_pSlideRight;						// The slide right button
	CButtonST			m_pSlideLeft;						// The slide left button
	CButtonST			m_pBold;							// The bold button
	CButtonST			m_pItalic;							// The italic button
	CButtonST			m_pUnderline;						// The underline button
	CButtonST			m_pStrikeOut;						// The strikeout button
// ------------------------

// General ----------------

	int					m_iNoteVersion;						// The version to know what note that have been uploaded (autoinc)
	CString				m_szNoteID;							// The unique id to know what note it is on the database
	CString				m_szText;							// The text (only used from Initialize ()
	CString				m_szTitle;							// The title (only used from Initialize ()
	BOOL				m_bVisible;							// TRUE -> Visible
	COLORREF			m_cfNoteColor;						// The note's color
	int					m_iTitleMaxWidth;					// The width the title can have before it hits the toolbarbuttons
// ------------------------

// From Recycle Bin -------
	bool				m_bBelongsToRecycleBin;				// --------------------------------------------------------------------------------------
															// TRUE -> The note is created temporarilly from the recycle bin to let the user view 
															// the note. If the user then deletes this note, the delete-warning should not be visible
															// (it looks ugly, since we don't want a warning about that)
// ------------------------									// --------------------------------------------------------------------------------------

// Alarm --
	BOOL				m_bUseAlarm;						// TRUE -> The alarm is set
	BOOL				m_bIsAlarmShouting;					// TRUE -> The alarm is shouting right now
	COleDateTime		m_Alarm;							// The alarm's time and date
// --------

// Position --
	CNotePosition		m_pPosition;						// The class that holds the position of the note
															// That class holds the check-function to be sure
															// that the note never gets odd heights or is moved
															// outside of the screen (ie when changin the resolution)
// --------

	int					m_iOldHeight;						// The height the notes has before it is minimized
};

//{{AFX_INSERT_LOCATION}}

#endif
