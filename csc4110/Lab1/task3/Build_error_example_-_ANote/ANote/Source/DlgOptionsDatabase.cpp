// DlgOptionsDatabase.cpp : implementation file
//

#include "stdafx.h"
#include "A Note.h"
#include "DlgOptionsDatabase.h"

#include "Xml.h"
#include <afx.h>
#include <afxwin.h>
#include <afxinet.h>
#include <atlbase.h>
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsDatabase dialog


CDlgOptionsDatabase::CDlgOptionsDatabase(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CDlgOptionsDatabase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsDatabase)
	m_szPassword = _T("");
	m_szUserName = _T("");
	m_bUploadDownload = FALSE;
	m_szDownloadAfter = _T("0");
	//}}AFX_DATA_INIT
}


void CDlgOptionsDatabase::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsDatabase)
	DDX_Text(pDX, IDC_PASSWORD, m_szPassword);
	DDX_Text(pDX, IDC_USERNAME, m_szUserName);
	DDX_Check(pDX, IDC_UPLOADDOWNLOAD, m_bUploadDownload);
	DDX_Text(pDX, IDC_DOWNLOADAFTER, m_szDownloadAfter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsDatabase, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CDlgOptionsDatabase)
	ON_BN_CLICKED(IDC_DELETENOTES, OnDeletenotes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsDatabase message handlers



void CDlgOptionsDatabase::OnDeletenotes() 
{
	CMainFrame *pMain = (CMainFrame*) ::AfxGetMainWnd ();

// Delete all the notes that the user has on his/hers account
	CString szTemp;
	szTemp.Format (_T("%s\n%s"), CTranslate::ReadString (172, _T("Do you want to delete all of your notes on the server?")), CTranslate::ReadString (173, _T("Note that the notes on your desktop will NOT be deleted now.")));
	if (MessageBox (szTemp, CTranslate::ReadString (174, _T("Delete notes")), MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;

	CString szPath, szXML, szData;

	szPath.Format (_T("%ssendnotes.php?user=%s&password=%s"), theApp.m_szServerPath, StringEncode (theApp.m_szUserName), StringEncode (theApp.m_szPassword));

// Create the delete xml
	CXml xml;
	szData = xml.GetDeleteXml ();

	if (pMain->Send (theApp.m_szServerAddress, szPath, szData, szXML))	{

		CStdioFile f;
		if (!f.Open (GetApplicationDataPath () + _T("\\Delete Notes At Server.xml"), CFile::modeCreate | CFile::modeWrite))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open the Delete Notes.xml-file"));
			return;		
		}
			
		TRY
		{
#if (defined (UNICODE) || defined (_UNICODE))
			int iLength;
			iLength	= szData.GetLength ();
			WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
			char * pcDest	  = new	char [ 2 * (iLength + 1)];

		// To UTF-8
			WideCharToMultiByte (CP_UTF8, 0, szData, iLength , pcDest, 2*iLength, NULL, NULL);
			f.Write (pcDest, iLength);
			delete []pcDest;
			delete []pwcUnicode;
#else
			f.Write (szData, szData.GetLength ());
#endif
			f.Close ();
		}
		CATCH (CFileException, e)
		{
			CErrorLog::CErrorLog (ERR, _T("Could not write the Delete Notes.xml-file"));
			return;
		}
		END_CATCH

		CStdioFile fp;
		if (!fp.Open (GetApplicationDataPath () + _T("\\Delete Notes Answer.xml"), CFile::modeCreate | CFile::modeWrite))	{
			CErrorLog::CErrorLog (INFO, _T("Could not open the Delete Notes Answer.xml-file"));
			return;			
		}

		TRY
		{
#if (defined (UNICODE) || defined (_UNICODE))
			int iLength;
			iLength	= szXML.GetLength ();
			WCHAR *pwcUnicode = new WCHAR [sizeof (WCHAR) * (iLength + 1)];
			char * pcDest	  = new	char [ 2 * (iLength + 1)];

		// To UTF-8
			WideCharToMultiByte (CP_UTF8, 0, szXML, iLength , pcDest, 2*iLength, NULL, NULL);
			fp.Write (pcDest, iLength);
			delete []pcDest;
			delete []pwcUnicode;
#else
			fp.Write (szXML, szXML.GetLength ());
#endif
			fp.Close ();
		}
		CATCH (CFileException, e)	
		{
			CErrorLog::CErrorLog (ERR, _T("Could not write the Delete Notes Answer.xml-file"));
			return;
		}
		END_CATCH


			AfxMessageBox (CTranslate::ReadString (20, _T("The notes have now been deleted")));
	}
}


BOOL CDlgOptionsDatabase::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
// Language stuff
	CString szTemp;
	szTemp.Format (_T(" %s "), CTranslate::ReadString (81, _T("User information")));
	((CStatic *)GetDlgItem (IDC_STATIC1))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC2))->SetWindowText (CTranslate::ReadString (82, _T("User name")));
	((CStatic *)GetDlgItem (IDC_STATIC3))->SetWindowText (CTranslate::ReadString (83, _T("Password")));
	szTemp.Format (_T(" %s "), CTranslate::ReadString (84, _T("Upload / Download")));
	((CStatic *)GetDlgItem (IDC_STATIC4))->SetWindowText (szTemp);
	((CStatic *)GetDlgItem (IDC_STATIC5))->SetWindowText (CTranslate::ReadString (85, _T("Start to download the notes after (seconds)")));
	((CStatic *)GetDlgItem (IDC_STATIC6))->SetWindowText (CTranslate::ReadString (86, _T("Delete all my notes that I have on the server")));
	((CButton *)GetDlgItem (IDC_UPLOADDOWNLOAD))->SetWindowText (CTranslate::ReadString (87, _T("Download the notes when the program starts and upload them on exit")));
	((CButton *)GetDlgItem (IDC_DELETENOTES))->SetWindowText (CTranslate::ReadString (88, _T("Delete Notes")));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
