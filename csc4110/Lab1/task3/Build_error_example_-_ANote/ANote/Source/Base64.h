// Base64.h: interface for the CBase64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__4EE0BA2E_59A3_49C4_83E1_29E113C563AC__INCLUDED_)
#define AFX_BASE64_H__4EE0BA2E_59A3_49C4_83E1_29E113C563AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _AFXDLL
	#include <afx.h>
	typedef CString		String;
#else
	#include <windows.h>
	#include <string>
	typedef std::string	String;
#endif


class CBase64  
{

	// Internal bucket class.
	class TempBucket
	{
	public:
		BYTE		nData[4];
		BYTE		nSize;
		void		Clear() { ::ZeroMemory(nData, 4); nSize = 0; };
	};

	PBYTE					m_pDBuffer;
	PBYTE					m_pEBuffer;
	DWORD					m_nDBufLen;
	DWORD					m_nEBufLen;
	DWORD					m_nDDataLen;
	DWORD					m_nEDataLen;

public:
	CBase64();
	virtual ~CBase64();

public:
	virtual void		Encode(const PBYTE, DWORD);
	virtual void		Decode(const PBYTE, DWORD);
	virtual void		Encode(char * sMessage);
	virtual void		Decode(char * /*LPCTSTR*/ sMessage);

	virtual int			GetLength () const;

	virtual char * /*LPCTSTR*/	DecodedMessage() const;
	virtual char *	/*LPCTSTR*/ EncodedMessage() const;

	virtual void		AllocEncode(DWORD);
	virtual void		AllocDecode(DWORD);
	virtual void		SetEncodeBuffer(const PBYTE pBuffer, DWORD nBufLen);
	virtual void		SetDecodeBuffer(const PBYTE pBuffer, DWORD nBufLen);

protected:
	virtual void		_EncodeToBuffer(const TempBucket &Decode, PBYTE pBuffer);
	virtual ULONG		_DecodeToBuffer(const TempBucket &Decode, PBYTE pBuffer);
	virtual void		_EncodeRaw(TempBucket &, const TempBucket &);
	virtual void		_DecodeRaw(TempBucket &, const TempBucket &);
	virtual BOOL		_IsBadMimeChar(BYTE);

	static  char		m_DecodeTable[256];
	static  BOOL		m_Init;
	void					_Init();

};

#endif // !defined(AFX_BASE64_H__4EE0BA2E_59A3_49C4_83E1_29E113C563AC__INCLUDED_)
