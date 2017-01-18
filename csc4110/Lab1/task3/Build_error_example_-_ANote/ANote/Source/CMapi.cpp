/*
Module : CMAPI.CPP
Purpose: Defines the implementation for an MFC wrapper class for sending an email using simple MAPI
Created: PJN / 11-05-1999
History: PJN / 05-12-1999 1. Fixed potential problem where CMapi is used in a console app which was giving an ASSERT
                          2. Fixed an assert which can occur if you dismiss the login dialog when doing an 
                          interactive MAPI logon
               28-03-2000 1. Provision of a sample app which implements a mini mail sender.
                          2. Added a CMapiMessage::AddMultipleRecipients method similar to my SMTP class.
               02-04-2000 1. Password field in the configuration dialog now uses ES_PASSWORD edit control style.
                          2. Password value used for Mapi logon is now stored in the registry encrypted instead of as plain text.
               21-04-2000 1. Added an optional parameter to CMapi::SendMessage to allow you to decide whether or not addresses 
                          should be resolved.
               22-06-2000 1. Fixed a bug in CMapiMessage::AddMultipleRecipients where BCC recipients were not being added 
                          correctly.
               18-07-2000 1. Fixed check for MAPI being installed when client apps create an incorrect "MAPI" entry in win.ini
                          or the registry, Thanks to Chris Raethke for spotting this.
                          2. A "SharedLogon" method has been provided which tries to acquire a shared mapi session
                          3. SendMessage method has been extended to allow the message to be interactively edited.
               25-01-2003 1. Updated copyright messages.
                          2. Made CMapiSession destructor virtual
                          3. Made a new CMapiRecipient class. This allows finer control over setting the display name
                          and the address individually. Thanks to the people on the discussion board on codeproject.com
                          for reporting this problem. The problem arose when Outlook Express displays its security dialog 
                          about an unattended mapi mail being sent. In this dialog the "To" fields were all empty. It seems
                          that OE only displays the addresses in this dialog. Perhaps because so many viruses abound the 
                          address is more relevant that the actual friendy name.


Copyright (c) 1999  - 2003 by PJ Naughter.  

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/



/////////////////////////////////  Includes  //////////////////////////////////

#include "stdafx.h"
#include "CMapi.h"
#ifndef __AFXPRIV_H__
#include <afxpriv.h>
#endif




//////////////////////////////// Statics / Macros /////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif




////////////////////////////////// Implementation /////////////////////////////

CMapiRecipient::CMapiRecipient()
{
}

CMapiRecipient::CMapiRecipient(const CString& sAddress) : m_sAddress(sAddress)
{
}

CMapiRecipient::CMapiRecipient(const CString& sAddress, const CString& sFriendlyName) : m_sAddress(sAddress) , m_sFriendlyName(sFriendlyName)
{
}

CMapiRecipient& CMapiRecipient::operator=(const CMapiRecipient& recipient)
{
  m_sAddress = recipient.m_sAddress;
  m_sFriendlyName = recipient.m_sFriendlyName;

  return *this;
}



BOOL CMapiMessage::AddMultipleRecipients(const CString& sRecipients, RECIPIENT_TYPE RecipientType)
{
	ASSERT(sRecipients.GetLength()); //An empty string is now allowed
	
	//Loop through the whole string, adding recipients as they are encountered
	int length = sRecipients.GetLength();
	TCHAR* buf = new TCHAR[length + 1];	// Allocate a work area (don't touch parameter itself)
	_tcscpy(buf, sRecipients);
	for (int pos=0, start=0; pos<=length; pos++)
	{
		//Valid separators between addresses are ',' or ';'
		if ((buf[pos] == _T(',')) || (buf[pos] == _T(';')) || (buf[pos] == 0))
		{
			buf[pos] = 0;	//Redundant when at the end of string, but who cares.
      CString sTemp(&buf[start]);

			//Now divide the substring into friendly names and e-mail address
      CString sFriendly;
      CString sAddress;
      if (sTemp.GetLength())
      {
			  int nMark = sTemp.Find(_T('<'));
			  if (nMark >= 0)
			  {
				  sFriendly = sTemp.Left(nMark);
				  int nMark2 = sTemp.Find(_T('>'));
				  if (nMark2 > nMark)
				    sAddress = sTemp.Mid(nMark + 1, nMark2 - (nMark + 1));
			  }
			  else
  			  sAddress = sTemp;

        //finally add it to the correct array
        sFriendly.TrimRight();
        sFriendly.TrimLeft();
        sAddress.TrimRight();
        sAddress.TrimLeft();
        if (sFriendly.IsEmpty()) //If the friendly name is empty then just set it to the address
          sFriendly = sAddress;
        CMapiRecipient recipient(sFriendly, sAddress);
        switch (RecipientType)
        {
          case TO:  m_To.Add(recipient); break;
          case CC:  m_CC.Add(recipient); break;
          case BCC: m_BCC.Add(recipient); break;
          default: ASSERT(FALSE); break;
        }
      }

      //Move on to the next position
			start = pos + 1;
		}
	}
	delete[] buf;
	return TRUE;
}



CMapiSession::CMapiSession()
{
  m_hSession = 0;
  m_nLastError = 0;
  m_hMapi = NULL;
  m_lpfnMAPILogon = NULL;
  m_lpfnMAPILogoff = NULL;
  m_lpfnMAPISendMail = NULL;
  m_lpfnMAPIResolveName = NULL;
  m_lpfnMAPIFreeBuffer = NULL;
  Initialise();
}

CMapiSession::~CMapiSession()
{
  //Logoff if logged on
  Logoff();

  //Unload the MAPI dll
  Deinitialise();
}

void CMapiSession::Initialise() 
{
  //First make sure the MAPI32 dll is present on the system. Technically we should
  //be also testing by using the check "GetProfileInt(_T("MAIL"), _T("MAPI"), 0) != 0"
  //also, but some installs of MAPI screw this entry up.
	BOOL bMapiInstalled = (SearchPath(NULL, _T("MAPI32.DLL"), NULL, 0, NULL, NULL) != 0);

  if (bMapiInstalled)
  {
    //Load up the MAPI dll and get the function pointers we are interested in
    m_hMapi = LoadLibrary(_T("MAPI32.DLL"));
    if (m_hMapi)
    {
      m_lpfnMAPILogon = (LPMAPILOGON) GetProcAddress(m_hMapi, "MAPILogon");
      m_lpfnMAPILogoff = (LPMAPILOGOFF) GetProcAddress(m_hMapi, "MAPILogoff");
      m_lpfnMAPISendMail = (LPMAPISENDMAIL) GetProcAddress(m_hMapi, "MAPISendMail");
      m_lpfnMAPIResolveName = (LPMAPIRESOLVENAME) GetProcAddress(m_hMapi, "MAPIResolveName");
      m_lpfnMAPIFreeBuffer = (LPMAPIFREEBUFFER) GetProcAddress(m_hMapi, "MAPIFreeBuffer");
  
      //If any of the functions are not installed then fail the load
      if (m_lpfnMAPILogon == NULL || m_lpfnMAPILogoff == NULL ||
          m_lpfnMAPISendMail == NULL || m_lpfnMAPIResolveName == NULL || m_lpfnMAPIFreeBuffer == NULL)
      {
        TRACE(_T("Failed to get one of the functions pointer in MAPI32.DLL\n"));
        Deinitialise();
      }
    }
  }
  else
    TRACE(_T("Mapi is not installed on this computer\n"));
}

void CMapiSession::Deinitialise()
{
  if (m_hMapi)
  {
    //Unload the MAPI dll and reset the function pointers to NULL
    FreeLibrary(m_hMapi);
    m_hMapi = NULL;
    m_lpfnMAPILogon = NULL;
    m_lpfnMAPILogoff = NULL;
    m_lpfnMAPISendMail = NULL;
    m_lpfnMAPIResolveName = NULL;
    m_lpfnMAPIFreeBuffer = NULL;
  }
}

BOOL CMapiSession::Logon(const CString& sProfileName, const CString& sPassword, CWnd* pParentWnd)
{
	//For correct operation of the T2A macro, see MFC Tech Note 59
	USES_CONVERSION;

  ASSERT(MapiInstalled()); //MAPI must be installed
  ASSERT(m_lpfnMAPILogon); //Function pointer must be valid

  //Initialise the function return value
  BOOL bSuccess = FALSE;

  //Just in case we are already logged in
  Logoff();

  //Setup the ascii versions of the profile name and password
  int nProfileLength = sProfileName.GetLength();
  int nPasswordLength = sPassword.GetLength();
  LPSTR pszProfileName = NULL;
  LPSTR pszPassword = NULL;
  if (nProfileLength)
  {
    pszProfileName = T2A((LPTSTR) (LPCTSTR) sProfileName);
    pszPassword = T2A((LPTSTR) (LPCTSTR) sPassword);
  }

  //Setup the flags & UIParam parameters used in the MapiLogon call
  FLAGS flags = 0;
  ULONG nUIParam = 0;
  if (nProfileLength == 0)
  {
    //No profile name given, then we must interactively request a profile name
    if (pParentWnd)
    {
      nUIParam = (ULONG) pParentWnd->GetSafeHwnd();
      flags |= MAPI_LOGON_UI;
    }
    else
    {
      //No CWnd given, just use the main window of the app as the parent window
      if (AfxGetMainWnd())
      {
        nUIParam = (ULONG) AfxGetMainWnd()->GetSafeHwnd();
        flags |= MAPI_LOGON_UI;
      }
    }
  }
  
  //First try to acquire a new MAPI session using the supplied settings using the MAPILogon functio
  ULONG nError = m_lpfnMAPILogon(nUIParam, pszProfileName, pszPassword, flags | MAPI_NEW_SESSION, 0, &m_hSession);
  if (nError != SUCCESS_SUCCESS && nError != MAPI_E_USER_ABORT)
  {
    //Failed to create a create mapi session, try to acquire a shared mapi session
    TRACE(_T("Failed to logon to MAPI using a new session, trying to acquire a shared one\n"));
    nError = m_lpfnMAPILogon(nUIParam, NULL, NULL, 0, 0, &m_hSession);
    if (nError == SUCCESS_SUCCESS)
    {
      m_nLastError = SUCCESS_SUCCESS;
      bSuccess = TRUE;
    }
    else
    {
      TRACE(_T("Failed to logon to MAPI using a shared session, Error:%d\n"), nError);
      m_nLastError = nError;
    }
  }
  else if (nError == SUCCESS_SUCCESS)
  {
    m_nLastError = SUCCESS_SUCCESS;
    bSuccess = TRUE;
  }

  return bSuccess;
}

BOOL CMapiSession::SharedLogon()
{
  ASSERT(MapiInstalled()); //MAPI must be installed
  ASSERT(m_lpfnMAPILogon); //Function pointer must be valid

  //Initialise the function return value
  BOOL bSuccess = FALSE;

  //Just in case we are already logged in
  Logoff();

  //Try to acquire a shared mapi session
  ULONG nError = m_lpfnMAPILogon(0, NULL, NULL, 0, 0, &m_hSession);
  if (nError == SUCCESS_SUCCESS)
  {
    m_nLastError = SUCCESS_SUCCESS;
    bSuccess = TRUE;
  }
  else
    m_nLastError = nError;

  return bSuccess;
}

BOOL CMapiSession::LoggedOn() const
{
  return (m_hSession != 0);
}

BOOL CMapiSession::MapiInstalled() const
{
  return (m_hMapi != NULL);
}

BOOL CMapiSession::Logoff()
{
  ASSERT(MapiInstalled()); //MAPI must be installed
  ASSERT(m_lpfnMAPILogoff); //Function pointer must be valid

  //Initialise the function return value
  BOOL bSuccess = FALSE;

  if (m_hSession)
  {
    //Call the MAPILogoff function
    ULONG nError = m_lpfnMAPILogoff(m_hSession, 0, 0, 0); 
    if (nError != SUCCESS_SUCCESS)
    {
      TRACE(_T("Failed in call to MapiLogoff, Error:%d"), nError);
      m_nLastError = nError;
      bSuccess = TRUE;
    }
    else
    {
      m_nLastError = SUCCESS_SUCCESS;
      bSuccess = TRUE;
    }
    m_hSession = 0;
  }
    
  return bSuccess;
}

BOOL CMapiSession::Resolve(const CString& sName, lpMapiRecipDesc* lppRecip)
{
	//For correct operation of the T2A macro, see MFC Tech Note 59
	USES_CONVERSION;

  ASSERT(MapiInstalled()); //MAPI must be installed
  ASSERT(m_lpfnMAPIResolveName); //Function pointer must be valid
  ASSERT(LoggedOn()); //Must be logged on to MAPI
  ASSERT(m_hSession); //MAPI session handle must be valid

  //Call the MAPIResolveName function
  LPSTR lpszAsciiName = T2A((LPTSTR) (LPCTSTR) sName);
  ULONG nError = m_lpfnMAPIResolveName(m_hSession, 0, lpszAsciiName, 0, 0, lppRecip);
  if (nError != SUCCESS_SUCCESS)
  {
    TRACE(_T("Failed to resolve the name: %s, Error:%d\n"), sName, nError);
    m_nLastError = nError;
  }

  return (nError == SUCCESS_SUCCESS);
}

BOOL CMapiSession::Send(CMapiMessage& message, BOOL bResolve, BOOL bInteractive, CWnd* pParentWnd)
{
	//For correct operation of the T2A macro, see MFC Tech Note 59
	USES_CONVERSION;

  ASSERT(MapiInstalled()); //MAPI must be installed
  ASSERT(m_lpfnMAPISendMail); //Function pointer must be valid
  ASSERT(m_lpfnMAPIFreeBuffer); //Function pointer must be valid

  //Initialise the function return value
  BOOL bSuccess = FALSE;  

  //Create the MapiMessage structure to match the message parameter send into us
  MapiMessage mapiMessage;
  ZeroMemory(&mapiMessage, sizeof(mapiMessage));
  mapiMessage.lpszSubject = T2A((LPTSTR) (LPCTSTR) message.m_sSubject);
  mapiMessage.lpszNoteText = T2A((LPTSTR) (LPCTSTR) message.m_sBody);
  mapiMessage.nRecipCount = message.m_To.GetSize() + message.m_CC.GetSize() + message.m_BCC.GetSize(); 
  ASSERT(mapiMessage.nRecipCount); //Must have at least 1 recipient!

  //Allocate the recipients array
  mapiMessage.lpRecips = new MapiRecipDesc[mapiMessage.nRecipCount];

  //Setup the "To" recipients
  int nRecipIndex = 0;
  int nToSize = message.m_To.GetSize();
  for (int i=0; i<nToSize; i++)
  {
    MapiRecipDesc& recip = mapiMessage.lpRecips[nRecipIndex];
    ZeroMemory(&recip, sizeof(MapiRecipDesc));
    recip.ulRecipClass = MAPI_TO;
    CMapiRecipient& recipient = message.m_To.ElementAt(i);

    if (bResolve)
    {
      //Try to resolve the name
      lpMapiRecipDesc lpTempRecip;  
      if (Resolve(recipient.m_sFriendlyName, &lpTempRecip))
      {
        //Resolve worked, put the resolved name back into the sName
        recipient.m_sFriendlyName = lpTempRecip->lpszName;
        recipient.m_sAddress = lpTempRecip->lpszAddress;

        //Don't forget to free up the memory MAPI allocated for us
        m_lpfnMAPIFreeBuffer(lpTempRecip);
      }
    }
    recip.lpszName = T2A((LPTSTR) (LPCTSTR) recipient.m_sFriendlyName);
    recip.lpszAddress = T2A((LPTSTR) (LPCTSTR) recipient.m_sAddress);

    ++nRecipIndex;
  }

  //Setup the "CC" recipients
  int nCCSize = message.m_CC.GetSize();
  for (int i=0; i<nCCSize; i++)
  {
    MapiRecipDesc& recip = mapiMessage.lpRecips[nRecipIndex];
    ZeroMemory(&recip, sizeof(MapiRecipDesc));
    recip.ulRecipClass = MAPI_CC;
    CMapiRecipient& recipient = message.m_CC.ElementAt(i);

    if (bResolve)
    {    
      //Try to resolve the name
      lpMapiRecipDesc lpTempRecip;  
      if (Resolve(recipient.m_sFriendlyName, &lpTempRecip))
      {
        //Resolve worked, put the resolved name back into the sName
        recipient.m_sFriendlyName = lpTempRecip->lpszName;
        recipient.m_sAddress = lpTempRecip->lpszAddress;

        //Don't forget to free up the memory MAPI allocated for us
        m_lpfnMAPIFreeBuffer(lpTempRecip);
      }
    }
    recip.lpszName = T2A((LPTSTR) (LPCTSTR) recipient.m_sFriendlyName);
    recip.lpszAddress = T2A((LPTSTR) (LPCTSTR) recipient.m_sAddress);

    ++nRecipIndex;
  }

  //Setup the "BCC" recipients
  int nBCCSize = message.m_BCC.GetSize();
  for (int i=0; i<nBCCSize; i++)
  {
    MapiRecipDesc& recip = mapiMessage.lpRecips[nRecipIndex];
    ZeroMemory(&recip, sizeof(MapiRecipDesc));
    recip.ulRecipClass = MAPI_BCC;
    CMapiRecipient& recipient = message.m_BCC.ElementAt(i);

    if (bResolve)
    {
      //Try to resolve the name
      lpMapiRecipDesc lpTempRecip;  
      if (Resolve(recipient.m_sFriendlyName, &lpTempRecip))
      {
        //Resolve worked, put the resolved name back into the sName
        recipient.m_sFriendlyName = lpTempRecip->lpszName;
        recipient.m_sAddress = lpTempRecip->lpszAddress;

        //Don't forget to free up the memory MAPI allocated for us
        m_lpfnMAPIFreeBuffer(lpTempRecip);
      }
    }
    recip.lpszName = T2A((LPTSTR) (LPCTSTR) recipient.m_sFriendlyName);
    recip.lpszAddress = T2A((LPTSTR) (LPCTSTR) recipient.m_sAddress);

    ++nRecipIndex;
  }

  //Setup the attachments 
  int nAttachmentSize = message.m_Attachments.GetSize();
  int nTitleSize = message.m_AttachmentTitles.GetSize();
  if (nTitleSize)
  { 
    ASSERT(nTitleSize == nAttachmentSize); //If you are going to set the attachment titles then you must set 
                                           //the attachment title for each attachment
  }
  if (nAttachmentSize)
  {
    mapiMessage.nFileCount = nAttachmentSize;
    mapiMessage.lpFiles = new MapiFileDesc[nAttachmentSize];
    for (int i=0; i<nAttachmentSize; i++)
    {
      MapiFileDesc& file = mapiMessage.lpFiles[i];
      ZeroMemory(&file, sizeof(MapiFileDesc));
      file.nPosition = 0xFFFFFFFF;
      CString& sFilename = message.m_Attachments.ElementAt(i);
      file.lpszPathName = T2A((LPTSTR) (LPCTSTR) sFilename);
      file.lpszFileName = file.lpszPathName;
      if (nTitleSize)
      {
        CString& sTitle = message.m_AttachmentTitles.ElementAt(i);
        file.lpszFileName = T2A((LPTSTR) (LPCTSTR) sTitle);
      }
    }
  }

  //Setup the parameters into the function
  FLAGS flags = 0;
  ULONG uiParam = 0;
  if (!LoggedOn())
    flags |= MAPI_LOGON_UI;
  if (bInteractive)
  {
    flags |= MAPI_DIALOG;
    if (pParentWnd)
      uiParam = (ULONG) pParentWnd->GetSafeHwnd();
    else
    {
      ASSERT(AfxGetMainWnd());
      uiParam = (ULONG) AfxGetMainWnd()->GetSafeHwnd();
    }
  }

  //Do the actual send using MAPISendMail
  ULONG nError = m_lpfnMAPISendMail(m_hSession, uiParam, &mapiMessage, flags, 0);
  if (nError == SUCCESS_SUCCESS)
  {
    bSuccess = TRUE;
    m_nLastError = SUCCESS_SUCCESS;
  }
  else
  {
    TRACE(_T("Failed to send mail message, Error:%d\n"), nError);
    m_nLastError = nError;
  }

  //Tidy up the Attachements
  if (nAttachmentSize)
    delete [] mapiMessage.lpFiles;
  
  //Free up the Recipients memory
  delete [] mapiMessage.lpRecips;

  return bSuccess;
}

ULONG CMapiSession::GetLastError() const
{
  return m_nLastError;
}

