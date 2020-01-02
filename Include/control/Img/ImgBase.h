// ImgBase.h: interface for the CImgBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGBASE_H__8FF29B63_ED3E_4030_8603_64CA4C005396__INCLUDED_)
#define AFX_IMGBASE_H__8FF29B63_ED3E_4030_8603_64CA4C005396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IMAGE_TYPE_GDIPLUS		1
#define IMAGE_TYPE_CXIMAGE		2

class CImgBase  
{
public:
	static CImgBase*	SCreateImage(int nType = IMAGE_TYPE_GDIPLUS);

public:
	CImgBase();
	virtual ~CImgBase();

public:
//	virtual BOOL LoadFile(const char* pFileName) = 0;
	virtual BOOL LoadFile(const TCHAR* pFileName) = 0;
	virtual BOOL LoadBuf(TCHAR* pBuf, int nSize, int nPicType) = 0;
	virtual int	GetWidth()  = 0;
	virtual int	GetHeight()  = 0;
	virtual int	GetType() = 0;
	virtual long Draw(HDC hdc, long x=0, long y=0, long cx = -1, long cy = -1, RECT* pClipRect = 0) = 0;
	virtual long Draw(HDC hdc, const RECT& rect, RECT* pClipRect=NULL) = 0;
	virtual BOOL HasPic() = 0;
	virtual BOOL SaveToJPGFile(const TCHAR* pJPGFile) = 0;

protected:
	virtual int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) = 0;
};

#endif // !defined(AFX_IMGBASE_H__8FF29B63_ED3E_4030_8603_64CA4C005396__INCLUDED_)
