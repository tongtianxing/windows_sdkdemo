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

#define LOADSTRINGEX(ID)	(CLanguage::GetInstance()->LoadResource(ID))

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
	typedef std::map<int, CString >	mapRes;		// 资源关联信息
	typedef	mapRes::iterator		mapResIter;


public:
	//---------------------------------------------------------------------------------------------
	//说明：设置加载的资源文件
	//参数：[in]strResouce:资源的文件名
	//返回：成功返回TRUE，失败返回FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	SetLanguage(const CString& strResource);

	//---------------------------------------------------------------------------------------------
	//说明：取得所需要的资源
	//参数：[in]ID:资源的ID
	//返回：成功返回所加载的资源
	//---------------------------------------------------------------------------------------------
	CString	LoadResource(UINT nID);

	//---------------------------------------------------------------------------------------------
	//说明：取得所需要的资源
	//参数：[in]ID:资源的ID
	//		[out]strResource:资源字符
	//返回：成功返回TRUE，失败返回FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	LoadResource(UINT nID, CString& strRes);

	//---------------------------------------------------------------------------------------------
	//说明：写字符串
	//参数：[in]strID:资源的ID
	//		[in]strRes:资源字符
	//返回：成功返回TRUE，失败返回FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	WriteString(const CString& strID, const CString& strRes);

private:
//	CMutexLock	m_lock;
	CRITICAL_SECTION m_csRes;
	CString		m_strResFile;		//资源文件
	mapRes		m_mapRes;			//
};

#endif // !defined(AFX_LANGUAGE_H__7BD99134_5302_423A_BE03_FEE100F15376__INCLUDED_)
