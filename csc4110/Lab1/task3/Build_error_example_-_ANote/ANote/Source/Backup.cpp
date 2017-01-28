#include "stdafx.h"
#include "A Note.h"
#include "backup.h"

CBackup::CBackup(void)
{
}

CBackup::~CBackup(void)
{
}

void CBackup::CreateBackup(void)
{
// Create the backup by taking the notes.xml-file
// and copy it to the backup-folder and renaming
// the file to the date and time stamp

	CString szFromFile;
	CString szToFile;
	COleDateTime time;

// Get the file-name of the to file
	int iFile = AfxGetApp ()->GetProfileInt (_T("Settings\\Options"), _T("Backup File Name"), 0);
	iFile++;
	AfxGetApp ()->WriteProfileInt (_T("Settings\\Options"), _T("Backup File Name"), iFile);

	szFromFile.Format (_T("%s\\notes.xml"), GetApplicationDataPath ());
	szToFile.Format (_T("%s\\Backup\\%d.xml"), GetApplicationDataPath (), iFile);

// Create the backup-directory if it doesn't exist
	CString szFolder;
	szFolder.Format (_T("%s\\Backup"), GetApplicationDataPath ());
	CreateDirectory (szFolder, NULL);

// Copy the file
	CopyFile (szFromFile, szToFile, FALSE);
}
