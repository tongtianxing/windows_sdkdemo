// ImgGdiPlus.h: interface for the CImgGdiPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGGDIPLUS_H__BA95ECDB_7533_4CDA_8987_EF77F129912F__INCLUDED_)
#define AFX_IMGGDIPLUS_H__BA95ECDB_7533_4CDA_8987_EF77F129912F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ULONG_PTR ULONG
#include <COMDEF.H>
//#include <gdiplus/ObjSafe.h>
#include <gdiplus/gdiplus.h>
using namespace Gdiplus;

#include "ImgBase.h"

class CImgGdiPlus : public CImgBase  
{
public:
	static ULONG_PTR g_gdiplusToken;
	static void SInitGuidPlus();
	static void SFreeGuidPlus();

public:
	CImgGdiPlus();
	virtual ~CImgGdiPlus();

protected:
	void	FreeImg();

public:
//	virtual BOOL LoadFile(const char* pFileName);
	virtual BOOL LoadFile(const TCHAR* pFileName);
	virtual BOOL LoadBuf(TCHAR* pBuf, int nSize, int nPicType);
	virtual int	GetWidth();
	virtual int	GetHeight();
	virtual int	GetType();
	virtual long Draw(HDC hdc, long x=0, long y=0, long cx = -1, long cy = -1, RECT* pClipRect = 0);
	virtual long Draw(HDC hdc, const RECT& rect, RECT* pClipRect=NULL);
	virtual BOOL HasPic();
	virtual BOOL SaveToJPGFile(const TCHAR* pJPGFile);

protected:
	virtual int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

private:
	Image*	m_pImage;
};

#endif // !defined(AFX_IMGGDIPLUS_H__BA95ECDB_7533_4CDA_8987_EF77F129912F__INCLUDED_)
