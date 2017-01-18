// ErrorLog.cpp: implementation of the CErrorLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "a note.h"
#include "ErrorLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CErrorLog::CErrorLog()
{

}

CErrorLog::~CErrorLog()
{

}

CErrorLog::CErrorLog(int iType, CString szErrorText)
{
	CString szTime, szText, szFile, szType;
	CStdioFile fp;

// Get the time
	szTime = GetTime ();

// Format the text
	switch (iType)	{
	case 1:			szType = _T("INFO ");	break;
	case 2:			szType = _T("ERROR");	break;
	default:		ASSERT (FALSE);		break;			  
	}

	szText.Format (_T("%s  %s   %s\r\n"), szType, szTime, szErrorText);

// Try to write the text
	szFile.Format (_T("%s\\ErrorLog.txt"), GetApplicationDataPath ());

	if (!fp.Open (szFile, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))	{
		ASSERT (FALSE); // Something went wrong and we could not open the file
		return;
	}


	TRY
	{
		DWORD dw = fp.SeekToEnd ();
#if (defined (UNICODE) || defined (_UNICODE))
		int iLength;
		iLength	= szText.GetLength ();
		WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
		char * pcDest	  = new	char [ 2 * (iLength + 1)];

	// To UTF-8
		iLength = WideCharToMultiByte (CP_UTF8, 0, szText, iLength , pcDest, 2*iLength, NULL, NULL);
		fp.Write (pcDest, iLength);
		delete []pcDest;
		delete []pwcUnicode;
#else
		fp.Write (szText, szText.GetLength ());
#endif
		fp.Close ();
	}
	CATCH (CFileException, e)
	{
		ASSERT (FALSE);	// We could not write to the file
		return;
	}
	END_CATCH

}

CString CErrorLog::GetTime()
{
// Return the current time as:
// 2004-09-30 - 21:34:30
	return CTime::GetCurrentTime ().Format (_T("%Y-%m-%d - %H:%M:%S"));
}
