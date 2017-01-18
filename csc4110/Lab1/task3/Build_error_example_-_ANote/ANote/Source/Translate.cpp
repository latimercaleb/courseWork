// Translate.cpp: implementation of the CTranslate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "a note.h"
#include "Translate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTranslate::CTranslate ()
{
}

CTranslate::~CTranslate ()
{
}


CString CTranslate::ReadString (int iWhat, CString szDefault)
{
	ASSERT (iWhat < TextSize);

	CString szFile;
	szFile.Format (_T("%s\\Language\\%s"), GetProgramPath (), theApp.m_szLanguageIni);

// Find the text from the default inifile
	TCHAR cText[255];
	CString szTemp;
	szTemp.Format (_T("%d"), iWhat);

	GetPrivateProfileString (_T("TRANSLATION"), szTemp, szDefault, cText, 255, szFile);

							  
	return CString (cText);
}

CString CTranslate::ReadString (int iWhat, CString szDefault, CString szIniFile)
{
	ASSERT (iWhat < TextSize);

// Find the text from the selected inifile
	TCHAR cText[255];
	CString szTemp;
	szTemp.Format (_T("%d"), iWhat);

	GetPrivateProfileString (_T("TRANSLATION"), szTemp, szDefault, cText, 255, szIniFile);

							  
	return CString (cText);

}

void CTranslate::SaveString(int iWhat, CString szText, CString szIniFile)
{
	ASSERT (iWhat < TextSize);

// Save the text
	CString szTemp;
	szTemp.Format (_T("%d"), iWhat);
	WritePrivateProfileString(_T("TRANSLATION"), szTemp, szText, szIniFile);
}
