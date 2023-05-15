#pragma once

//#define IMAGE_TYPE_GDIPLUS		1
//#define IMAGE_TYPE_CXIMAGE		2

/*
注意,使用此库必须链接GdiPlus库
#pragma comment(lib, "GdiPlus.lib")

在程序初始化是
*/

#include <COMDEF.H>
#include <gdiplus/gdiplus.h>
using namespace Gdiplus;

// 保存格式类型定义
#define IMAGE_SAVE_TYPE_JPG		1	//JPG格式
#define IMAGE_SAVE_TYPE_BMP		2	//BMP格式
#define IMAGE_SAVE_TYPE_PNG		3	//PNG格式


class LIBIMGBASE_API CImgBase
{
public:
	static void SInitGuidPlus();
	static void SFreeGuidPlus();
	static CImgBase*	SCreateImage();
	static void SDeleteImage(CImgBase*& pImg);

public:
	CImgBase();
private:
	// 外部必须调用CImgBase::SDeleteImage(pImg)来释放资源 [2020-6-19 ydl]
	virtual ~CImgBase();
	friend class CImgCacheMgr;

public:
	// 从文件加载图片
	BOOL LoadFileA(LPCSTR szFileName);
	BOOL LoadFileW(LPCWSTR wszFileName);
	BOOL LoadFile(LPCSTR tszFileName);
	BOOL LoadFile(LPCWSTR tszFileName);


	//BOOL LoadFile(const TCHAR* pFileName);

	BOOL LoadBuf(char* pBuf, int nSize, int nPicType);

	BOOL LoadHBITMAP(HBITMAP hBm, HPALETTE hpal);
	BOOL LoadHICON(HICON hIcon);

	// 在当前图片对象上再次绘制一次参数中的图片
	BOOL AppendDrawImage(Image* pImage);
	BOOL AppendDrawImage(CImgBase* pImg);


	// 释放图片资源
	void FreeImg();

	// 获取属性
	int	GetWidth();
	int	GetHeight();
	int	GetType();

	// 绘制到对应DC
	long Draw(HDC hdc, long x = 0, long y = 0, long cx = -1, long cy = -1, RECT* pClipRect = NULL);
	long Draw(HDC hdc, const RECT& rect, RECT* pClipRect = NULL);
	// 使用pClipRect的绘制函数
	long DrawEx(HDC hdc, long x = 0, long y = 0, long cx = -1, long cy = -1, RECT* pClipRect = NULL);
	long DrawEx(HDC hdc, const RECT& rect, const LPRECT pClipRect = NULL);

	// 判断当前是否加载图片是否有效
	BOOL HasPic();

	// 保存图片到文件
	BOOL SaveToFileA(int nSaveType, LPCSTR lpFile);
	BOOL SaveToFileW(int nSaveType, LPCWSTR lpFile);
	BOOL SaveToFile(int nSaveType, LPCSTR lpFile);
	BOOL SaveToFile(int nSaveType, LPCWSTR lpFile);


	// 保存图片到文件(按指定尺寸)
	BOOL SaveAndChangeSizeToFileA(int nSaveType, LPCSTR lpFile, int nSaveWidth = 0, int nSaveHeight = 0);
	BOOL SaveAndChangeSizeToFileW(int nSaveType, LPCWSTR lpFile, int nSaveWidth = 0, int nSaveHeight = 0);
	BOOL SaveAndChangeSizeToFile(int nSaveType, LPCSTR lpFile, int nSaveWidth = 0, int nSaveHeight = 0);
	BOOL SaveAndChangeSizeToFile(int nSaveType, LPCWSTR lpFile, int nSaveWidth = 0, int nSaveHeight = 0);


	// 增加常用格式的接口
	BOOL SaveToJPGFileA(LPCSTR lpJPGFile) { return SaveToFileA(IMAGE_SAVE_TYPE_JPG, lpJPGFile); }
	BOOL SaveToBMPFileA(LPCSTR lpBMPFile) { return SaveToFileA(IMAGE_SAVE_TYPE_BMP, lpBMPFile); }
	BOOL SaveToPNGFileA(LPCSTR lpPNGFile) { return SaveToFileA(IMAGE_SAVE_TYPE_PNG, lpPNGFile); }

	BOOL SaveToJPGFileW(LPCWSTR lpJPGFile) { return SaveToFileW(IMAGE_SAVE_TYPE_JPG, lpJPGFile); }
	BOOL SaveToBMPFileW(LPCWSTR lpBMPFile) { return SaveToFileW(IMAGE_SAVE_TYPE_BMP, lpBMPFile); }
	BOOL SaveToPNGFileW(LPCWSTR lpPNGFile) { return SaveToFileW(IMAGE_SAVE_TYPE_PNG, lpPNGFile); }


	BOOL SaveToJPGFile(LPCSTR lpJPGFile) { return SaveToJPGFileA(lpJPGFile); }
	BOOL SaveToBMPFile(LPCSTR lpBMPFile) { return SaveToBMPFileA(lpBMPFile); }
	BOOL SaveToPNGFile(LPCSTR lpPNGFile) { return SaveToPNGFileA(lpPNGFile); }
	BOOL SaveToJPGFile(LPCWSTR lpJPGFile) { return SaveToJPGFileW(lpJPGFile); }
	BOOL SaveToBMPFile(LPCWSTR lpBMPFile) { return SaveToBMPFileW(lpBMPFile); }
	BOOL SaveToPNGFile(LPCWSTR lpPNGFile) { return SaveToPNGFileW(lpPNGFile); }


	// 获取特定格式的类ID 如:"image/jpeg"
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	// 获取图片对象用来操作,可用来构造Graphics对象
	Image* GetImage() { return m_pImage; }


protected:
	Image* m_pImage;
	void*  m_pParam;
};

#define CImgGdiPlus	CImgBase