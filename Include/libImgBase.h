
#ifdef LIBIMGBASE_EXPORTS
#define LIBIMGBASE_API __declspec(dllexport)
#else
#define LIBIMGBASE_API __declspec(dllimport)
#endif

#include "ImgBase.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ����ͼƬ����,Ԥ���ؿ���߰�ť�ļ���/�����ٶ� [2019-6-13 ydl]
	LIBIMGBASE_API void AddBindImgA(LPCSTR lpszPic);
	LIBIMGBASE_API void AddBindImgW(LPCWSTR lpszPic);

#ifdef _UNICODE
#define AddBindImgT	AddBindImgW
#else
#define AddBindImgT	AddBindImgA
#endif

#ifndef LIBIMGBASE_EXPORTS
#ifdef _UNICODE
#define AddBindImg	AddBindImgW
#else
#define AddBindImg	AddBindImgA
#endif
#endif

	LIBIMGBASE_API CImgBase* LoadImgByFileA(LPCSTR lpszPic, BOOL bAdd = TRUE);
	LIBIMGBASE_API CImgBase* LoadImgByFileW(LPCWSTR lpszPic, BOOL bAdd = TRUE);

#ifdef _UNICODE
#define LoadImgByFileT	LoadImgByFileW
#else
#define LoadImgByFileT	LoadImgByFileA
#endif

#ifndef LIBIMGBASE_EXPORTS
#ifdef _UNICODE
#define LoadImgByFile	LoadImgByFileW
#else
#define LoadImgByFile	LoadImgByFileA
#endif
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */