/*
Module : CMAPI.H
Purpose: Defines the interface for an MFC wrapper class for sending an email using simple MAPI
Created: PJN / 11-05-1999


Copyright (c) 1999 - 2003 by PJ Naughter.  

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/

#ifndef __CMAPI_H__
#define __CMAPI_H__

#include <afxtempl.h>


#ifndef MAPI_H
#include <mapi.h>
#endif



//Class which encapsulates a MAPI recipient
class CMapiRecipient
{
public:
//Constructors / Destructors
  CMapiRecipient();
  CMapiRecipient(const CString& sAddress);
  CMapiRecipient(const CString& sFriendlyName, const CString& sAddress);

//Methods
  CMapiRecipient& operator=(const CMapiRecipient& recipient); 

//Member variables
  CString m_sAddress;      //The actual provider specific email address. For example if using the SMTP 
                           //transport provider such as in Outlook express, then this value would be
                           //"SMTP:pjna@naughter.com"
  CString m_sFriendlyName; //The friendy name of the recipient e.g. "PJ Naughter"
};


//Class which encapsulates a MAPI mail message
class CMapiMessage
{
public:
//Enums
	enum RECIPIENT_TYPE { TO, CC, BCC };

//Methods
  BOOL AddMultipleRecipients(const CString& sRecipients, RECIPIENT_TYPE RecipientType);

//Member variables
  CArray<CMapiRecipient, CMapiRecipient&>  m_To;               //The To: Recipients
  CArray<CMapiRecipient, CMapiRecipient&>  m_CC;               //The CC: Recipients
  CArray<CMapiRecipient, CMapiRecipient&>  m_BCC;              //The BCC Recipients
  CString                                  m_sSubject;         //The Subject of the message
  CString                                  m_sBody;            //The Body of the message
  CStringArray                             m_Attachments;      //Files to attach to the email
  CStringArray                             m_AttachmentTitles; //Titles to use for the email file attachments
};


//The class which encapsulates the MAPI connection
class CMapiSession
{
public:
//Constructors / Destructors
  CMapiSession();
  virtual ~CMapiSession();

//Logon / Logoff Methods
  BOOL Logon(const CString& sProfileName, const CString& sPassword = CString(), CWnd* pParentWnd = NULL);
  BOOL SharedLogon();
  BOOL LoggedOn() const;
  BOOL Logoff();

//Send a message
  BOOL Send(CMapiMessage& mesage, BOOL bResolve = FALSE, BOOL bInteractive = FALSE, CWnd* pParentWnd = NULL);

//General MAPI support
  BOOL MapiInstalled() const;

//Error Handling
  ULONG GetLastError() const;

protected:
//Methods
  void Initialise();
  void Deinitialise(); 
  BOOL Resolve(const CString& sName, lpMapiRecipDesc* lppRecip);

//Data
  LHANDLE m_hSession; //Mapi Session handle
  ULONG m_nLastError; //Last Mapi error value
  HINSTANCE m_hMapi; //Instance handle of the MAPI dll
  LPMAPILOGON m_lpfnMAPILogon; //MAPILogon function pointer
  LPMAPILOGOFF m_lpfnMAPILogoff; //MAPILogoff function pointer
  LPMAPISENDMAIL m_lpfnMAPISendMail; //MAPISendMail function pointer
  LPMAPIRESOLVENAME m_lpfnMAPIResolveName; //MAPIResolveName function pointer
  LPMAPIFREEBUFFER m_lpfnMAPIFreeBuffer; //MAPIFreeBuffer function pointer
};


#endif //__CMAPI_H__