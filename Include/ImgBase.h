#pragma once

//#define IMAGE_TYPE_GDIPLUS		1
//#define IMAGE_TYPE_CXIMAGE		2

/*
ע��,ʹ�ô˿��������GdiPlus��
#pragma comment(lib, "GdiPlus.lib")

�ڳ����ʼ����
*/

#include <COMDEF.H>
#include <gdiplus/gdiplus.h>
using namespace Gdiplus;

// �����ʽ���Ͷ���
#define IMAGE_SAVE_TYPE_JPG		1	//JPG��ʽ
#define IMAGE_SAVE_TYPE_BMP		2	//BMP��ʽ
#define IMAGE_SAVE_TYPE_PNG		3	//PNG��ʽ


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
	// �ⲿ�������CImgBase::SDeleteImage(pImg)���ͷ���Դ [2020-6-19 ydl]
	virtual ~CImgBase();
	friend class CImgCacheMgr;

public:
	// ���ļ�����ͼƬ
	BOOL LoadFileA(LPCSTR szFileName);
	BOOL LoadFileW(LPCWSTR wszFileName);
	BOOL LoadFile(LPCSTR tszFileName);
	BOOL LoadFile(LPCWSTR tszFileName);


	//BOOL LoadFile(const TCHAR* pFileName);

	BOOL LoadBuf(char* pBuf, int nSize, int nPicType);

	BOOL LoadHBITMAP(HBITMAP hBm, HPALETTE hpal);
	BOOL LoadHICON(HICON hIcon);

	// �ڵ�ǰͼƬ�������ٴλ���һ�β����е�ͼƬ
	BOOL AppendDrawImage(Image* pImage);
	BOOL AppendDrawImage(CImgBase* pImg);


	// �ͷ�ͼƬ��Դ
	void FreeImg();

	// ��ȡ����
	int	GetWidth();
	int	GetHeight();
	int	GetType();

	// ���Ƶ���ӦDC
	long Draw(HDC hdc, long x = 0, long y = 0, long cx = -1, long cy = -1, RECT* pClipRect = NULL);
	long Draw(HDC hdc, const RECT& rect, RECT* pClipRect = NULL);
	// ʹ��pClipRect�Ļ��ƺ���
	long DrawEx(HDC hdc, long x = 0, long y = 0, long cx = -1, long cy = -1, RECT* pClipRect = NULL);
	long DrawEx(HDC hdc, const RECT& rect, const LPRECT pClipRect = NULL);

	// �жϵ�ǰ�Ƿ����ͼƬ�Ƿ���Ч
	BOOL HasPic();

	// ����ͼƬ���ļ�
	BOOL SaveToFileA(int nSaveType, LPCSTR lpFile);
	BOOL SaveToFileW(int nSaveType, LPCWSTR lpFile);
	BOOL SaveToFile(int nSaveType, LPCSTR lpFile);
	BOOL SaveToFile(int nSaveType, LPCWSTR lpFile);


	// ����ͼƬ���ļ�(��ָ���ߴ�)
	BOOL SaveAndChangeSizeToFileA(int nSaveType, LPCSTR lpFile, int nSaveWidth = 0, int nSaveHeight = 0);
	BOOL SaveAndChangeSizeToFileW(int nSaveType, LPCWSTR lpFile, int nSaveWidth = 0, int nSaveHeight = 0);
	BOOL SaveAndChangeSizeToFile(int nSaveType, LPCSTR lpFile, int nSaveWidth = 0, int nSaveHeight = 0);
	BOOL SaveAndChangeSizeToFile(int nSaveType, LPCWSTR lpFile, int nSaveWidth = 0, int nSaveHeight = 0);


	// ���ӳ��ø�ʽ�Ľӿ�
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


	// ��ȡ�ض���ʽ����ID ��:"image/jpeg"
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	// ��ȡͼƬ������������,����������Graphics����
	Image* GetImage() { return m_pImage; }


protected:
	Image* m_pImage;
	void*  m_pParam;
};

#define CImgGdiPlus	CImgBase