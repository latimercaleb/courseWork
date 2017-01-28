// ErrorLog.h: interface for the CErrorLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERRORLOG_H__35E439E0_3935_4DCC_AD5C_D74B8A5097C7__INCLUDED_)
#define AFX_ERRORLOG_H__35E439E0_3935_4DCC_AD5C_D74B8A5097C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define INFO	1
#define	ERR		2

class CErrorLog  
{
public:
	CErrorLog();
	CErrorLog (int iType, CString szErrorText);
	virtual ~CErrorLog();

protected:
	CString GetTime ();
};

#endif // !defined(AFX_ERRORLOG_H__35E439E0_3935_4DCC_AD5C_D74B8A5097C7__INCLUDED_)
