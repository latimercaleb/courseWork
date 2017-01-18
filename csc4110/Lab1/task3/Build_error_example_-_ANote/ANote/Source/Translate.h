// Translate.h: interface for the CTranslate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSLATE_H__F48AA9A3_FCC3_4FBB_97CD_2A0BFC550B10__INCLUDED_)
#define AFX_TRANSLATE_H__F48AA9A3_FCC3_4FBB_97CD_2A0BFC550B10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTranslate  
{
public:
	CTranslate();
	virtual ~CTranslate();
	static CString ReadString (int iWhat, CString szDefault);		// Find the number in the selected ini-file and return the string
	static CString ReadString (int iWhat, CString szDefault, CString szIniFile);
	static void SaveString (int iWhat, CString szText, CString szIniFile);
};

#endif // !defined(AFX_TRANSLATE_H__F48AA9A3_FCC3_4FBB_97CD_2A0BFC550B10__INCLUDED_)
