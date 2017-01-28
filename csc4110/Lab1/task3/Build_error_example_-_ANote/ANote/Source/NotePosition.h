#pragma once
class CNotePosition
{
public:

	CNotePosition(void);
	~CNotePosition(void);

	void FixNotePosition		(void *pNote);		// Run this to be sure that the note is within the display

	void SlidePositionToLeft	(void *pNote);		// Slide the note to the left side
	void SlidePositionToRight	(void *pNote);		// Slide the note to the right side
	void RestoreSlideFromLeft	(void *pNote);		// Restore the note from the left side
	void RestoreSlideFromRight	(void *pNote);		// Restore the note from the right side

// The point where the note is docked. Not serialized
	void SetDockedPoint			(CPoint cPoint)	{m_pDockPnt = cPoint;};
	CPoint GetDockedPoint		()				{return m_pDockPnt;};

// The display has changed the resolution -> reposition the notes
	void SetNotePositionDisplayResolutionChanged (void *pNote, CPoint pScreen);		

// Load and Save --------------
	BOOL GetSlidedToLeft		()	{return m_bSlidedToLeft;};
	BOOL GetSlidedToRight		()	{return m_bSlidedToRight;};
	BOOL GetDockedLeft			()	{return m_bDockedLeft;};
	BOOL GetDockedTop			()	{return m_bDockedTop;};
	BOOL GetDockedRight			()	{return m_bDockedRight;};
	BOOL GetDockedBottom		()	{return m_bDockedBottom;};
	CRect GetNotePosition		()	{return m_cNotePosition;};
	CRect GetSlidedNotePosition ()	{return m_cBeforeSlidedPosition;};
	void SetSlidedToLeft		(BOOL bSlided, void *pNote, bool bFixPosition);
	void SetSlidedToRight		(BOOL bSlided, void *pNote, bool bFixPosition);
	void SetDockedLeft			(BOOL bDocked, void *pNote, bool bFixPosition);
	void SetDockedTop			(BOOL bDocked, void *pNote, bool bFixPosition);
	void SetDockedRight			(BOOL bDocked, void *pNote, bool bFixPosition);
	void SetDockedBottom		(BOOL bDocked, void *pNote, bool bFixPosition);
	void SetNotePosition		(CRect cRect,  void *pNote, bool bFixPosition);
	void SetSlidedNotePosition	(CRect cRect,  void *pNote, bool bFixPosition);
// ----------------------------


private:
// General ---------------------
	CRect	m_cNotePosition;			// The position of the note (in normal mode)
	CSize	m_csScreenResolution;		// The last known resolution of the screen. It's used when the user changes the resolution
// -----------------------------

// Slided ----------------------
	BOOL	m_bSlidedToLeft;			// TRUE -> The note is slided to the side
	BOOL	m_bSlidedToRight;			// TRUE -> The note is slided to the side
	CRect	m_cBeforeSlidedPosition;	// The position of the note before the note were slided
// -----------------------------

// Docked ----------------------
	BOOL	m_bDockedLeft;				// TRUE -> The note is docked on the left side
	BOOL	m_bDockedTop;				// TRUE -> The note is docked on the top side
	BOOL	m_bDockedRight;				// TRUE -> The note is docked on the right side
	BOOL	m_bDockedBottom;			// TRUE -> The note is docked on the bottom side
	CPoint	m_pDockPnt;					// The position where the note are docked (not serialized)
// -----------------------------
};
