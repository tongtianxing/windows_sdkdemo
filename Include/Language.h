// Language.h: interface for the CLanguage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGE_H__7BD99134_5302_423A_BE03_FEE100F15376__INCLUDED_)
#define AFX_LANGUAGE_H__7BD99134_5302_423A_BE03_FEE100F15376__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*****************************************************************************

** 文件名: Language.h

** Copyright (c) 2006 

** 创建人: yfli

** 日  期: 2008-04-15

** 修改人:

** 日  期:

** 描  述:	资源管理类，从配置文件中加载资源

**

** 版  本: v1.0

*****************************************************************************/

#pragma warning(disable:4786)
#include <map>
#include <string>

#ifdef __AFX_H__  //使用MFC时,转为CString
#define LOADSTRINGEX(ID)	(CString(CLanguage::GetInstance()->LoadResource(ID).c_str()))
#else
#define LOADSTRINGEX(ID)	(CLanguage::GetInstance()->LoadResource(ID).c_str())
#endif // __AFX_H__

// 统一字符串的类型名
#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

class CLanguage  
{
private:
	static CLanguage*		g_pLanguage;
	
public:
	static CLanguage* GetInstance();
	static void DelInstance();
	
public:
	CLanguage();
	virtual ~CLanguage();
	CLanguage(const CLanguage& Lang);
	CLanguage& operator = (const CLanguage& Lang);

private:
	typedef std::map<int, tstring >	mapRes;		// 资源关联信息
	typedef	mapRes::iterator		mapResIter;


public:
	//---------------------------------------------------------------------------------------------
	//说明：设置加载的资源文件
	//参数：[in]strResouce:资源的文件名
	//返回：成功返回TRUE，失败返回FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	SetLanguage(const tstring& strResource);
	BOOL	SetLanguage(const TCHAR* tszResource);

	//---------------------------------------------------------------------------------------------
	//说明：取得所需要的资源
	//参数：[in]ID:资源的ID
	//返回：成功返回所加载的资源
	//---------------------------------------------------------------------------------------------
	tstring	LoadResource(UINT nID);

	//---------------------------------------------------------------------------------------------
	//说明：取得所需要的资源
	//参数：[in]ID:资源的ID
	//		[out]strResource:资源字符
	//返回：成功返回TRUE，失败返回FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	LoadResource(UINT nID, tstring& strRes);

	//---------------------------------------------------------------------------------------------
	//说明：写字符串
	//参数：[in]strID:资源的ID
	//		[in]strRes:资源字符
	//返回：成功返回TRUE，失败返回FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	WriteString(const tstring& strID, const tstring& strRes);

private:
//	CMutexLock	m_lock;
	CRITICAL_SECTION m_csRes;
	tstring		m_strResFile;		//资源文件
	mapRes		m_mapRes;			//
};

#ifdef MULTI_LANGUAGE
// 禁用单语言, 改用多语言
# undef LOADSTRINGEX

# ifdef __AFX_H__  //使用MFC时,转为CString
#  define LOADSTRINGEX(ID)	(CString(CMultiLanguage::GetInstance()->LoadResource(ID).c_str()))
# else
#  define LOADSTRINGEX(ID)	(CMultiLanguage::GetInstance()->LoadResource(ID).c_str())
# endif // __AFX_H__
#endif


// 同时存储多种语言数据
class CMultiLanguage
{
private:
	static CMultiLanguage*		g_pMultiLanguage;

public:
	static CMultiLanguage* GetInstance();
	static void DelInstance();

public:
	CMultiLanguage();
	virtual ~CMultiLanguage();
	CMultiLanguage(const CMultiLanguage& Lang);
	CMultiLanguage& operator = (const CMultiLanguage& Lang);

private:
	typedef std::map<tstring, CLanguage*> mapMultiRes;// 资源关联信息


public:
	//---------------------------------------------------------------------------------------------
	//说明：设置加载的资源文件
	//参数：[in]szLanguage:语言类型,用来区分不同语言的唯一标识
	//		[in]strResouce:资源的文件名
	//返回：成功返回TRUE，失败返回FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	SetLanguage(const TCHAR* szLanguage, const tstring& strResource);
	BOOL	SetLanguage(const TCHAR* szLanguage, const TCHAR* szResource);

	//---------------------------------------------------------------------------------------------
	//说明：取得所需要的资源
	//参数：[in]ID:资源的ID
	//		[in]szLanguage:语言类型,为空使用默认语言
	//返回：成功返回所加载的资源
	//---------------------------------------------------------------------------------------------
	tstring	LoadResource(UINT nID, const TCHAR* szLanguage = nullptr);

	//---------------------------------------------------------------------------------------------
	//说明：取得所需要的资源
	//参数：[in]ID:资源的ID
	//		[out]strResource:资源字符
	//		[in]szLanguage:语言类型,为空使用默认语言
	//返回：成功返回TRUE，失败返回FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	LoadResource(UINT nID, tstring& strRes, const TCHAR* szLanguage = nullptr);

	//---------------------------------------------------------------------------------------------
	//说明：设置当前选择的语言
	//参数：[in]szLanguage:语言类型,为空使用默认语言
	//返回：成功返回TRUE，失败返回FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	SelectLanguage(const TCHAR* szLanguage);

protected:
	CLanguage* GetLanguage(const TCHAR* szLanguage = nullptr);

private:
	CRITICAL_SECTION m_csRes;
	tstring		m_strResFile;		//资源文件
	CLanguage*	m_pCurrLanguage;	//当前选择的语言
	mapMultiRes m_mapMultiRes;
};

#endif // !defined(AFX_LANGUAGE_H__7BD99134_5302_423A_BE03_FEE100F15376__INCLUDED_)
