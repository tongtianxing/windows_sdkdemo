// Language.h: interface for the CLanguage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGE_H__7BD99134_5302_423A_BE03_FEE100F15376__INCLUDED_)
#define AFX_LANGUAGE_H__7BD99134_5302_423A_BE03_FEE100F15376__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*****************************************************************************

** �ļ���: Language.h

** Copyright (c) 2006 

** ������: yfli

** ��  ��: 2008-04-15

** �޸���:

** ��  ��:

** ��  ��:	��Դ�����࣬�������ļ��м�����Դ

**

** ��  ��: v1.0

*****************************************************************************/

#pragma warning(disable:4786)
#include <map>
#include <string>

#ifdef __AFX_H__  //ʹ��MFCʱ,תΪCString
#define LOADSTRINGEX(ID)	(CString(CLanguage::GetInstance()->LoadResource(ID).c_str()))
#else
#define LOADSTRINGEX(ID)	(CLanguage::GetInstance()->LoadResource(ID).c_str())
#endif // __AFX_H__

// ͳһ�ַ�����������
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
	typedef std::map<int, tstring >	mapRes;		// ��Դ������Ϣ
	typedef	mapRes::iterator		mapResIter;


public:
	//---------------------------------------------------------------------------------------------
	//˵�������ü��ص���Դ�ļ�
	//������[in]strResouce:��Դ���ļ���
	//���أ��ɹ�����TRUE��ʧ�ܷ���FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	SetLanguage(const tstring& strResource);
	BOOL	SetLanguage(const TCHAR* tszResource);

	//---------------------------------------------------------------------------------------------
	//˵����ȡ������Ҫ����Դ
	//������[in]ID:��Դ��ID
	//���أ��ɹ����������ص���Դ
	//---------------------------------------------------------------------------------------------
	tstring	LoadResource(UINT nID);

	//---------------------------------------------------------------------------------------------
	//˵����ȡ������Ҫ����Դ
	//������[in]ID:��Դ��ID
	//		[out]strResource:��Դ�ַ�
	//���أ��ɹ�����TRUE��ʧ�ܷ���FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	LoadResource(UINT nID, tstring& strRes);

	//---------------------------------------------------------------------------------------------
	//˵����д�ַ���
	//������[in]strID:��Դ��ID
	//		[in]strRes:��Դ�ַ�
	//���أ��ɹ�����TRUE��ʧ�ܷ���FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	WriteString(const tstring& strID, const tstring& strRes);

private:
//	CMutexLock	m_lock;
	CRITICAL_SECTION m_csRes;
	tstring		m_strResFile;		//��Դ�ļ�
	mapRes		m_mapRes;			//
};

#ifdef MULTI_LANGUAGE
// ���õ�����, ���ö�����
# undef LOADSTRINGEX

# ifdef __AFX_H__  //ʹ��MFCʱ,תΪCString
#  define LOADSTRINGEX(ID)	(CString(CMultiLanguage::GetInstance()->LoadResource(ID).c_str()))
# else
#  define LOADSTRINGEX(ID)	(CMultiLanguage::GetInstance()->LoadResource(ID).c_str())
# endif // __AFX_H__
#endif


// ͬʱ�洢������������
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
	typedef std::map<tstring, CLanguage*> mapMultiRes;// ��Դ������Ϣ


public:
	//---------------------------------------------------------------------------------------------
	//˵�������ü��ص���Դ�ļ�
	//������[in]szLanguage:��������,�������ֲ�ͬ���Ե�Ψһ��ʶ
	//		[in]strResouce:��Դ���ļ���
	//���أ��ɹ�����TRUE��ʧ�ܷ���FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	SetLanguage(const TCHAR* szLanguage, const tstring& strResource);
	BOOL	SetLanguage(const TCHAR* szLanguage, const TCHAR* szResource);

	//---------------------------------------------------------------------------------------------
	//˵����ȡ������Ҫ����Դ
	//������[in]ID:��Դ��ID
	//		[in]szLanguage:��������,Ϊ��ʹ��Ĭ������
	//���أ��ɹ����������ص���Դ
	//---------------------------------------------------------------------------------------------
	tstring	LoadResource(UINT nID, const TCHAR* szLanguage = nullptr);

	//---------------------------------------------------------------------------------------------
	//˵����ȡ������Ҫ����Դ
	//������[in]ID:��Դ��ID
	//		[out]strResource:��Դ�ַ�
	//		[in]szLanguage:��������,Ϊ��ʹ��Ĭ������
	//���أ��ɹ�����TRUE��ʧ�ܷ���FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	LoadResource(UINT nID, tstring& strRes, const TCHAR* szLanguage = nullptr);

	//---------------------------------------------------------------------------------------------
	//˵�������õ�ǰѡ�������
	//������[in]szLanguage:��������,Ϊ��ʹ��Ĭ������
	//���أ��ɹ�����TRUE��ʧ�ܷ���FASLE
	//---------------------------------------------------------------------------------------------
	BOOL	SelectLanguage(const TCHAR* szLanguage);

protected:
	CLanguage* GetLanguage(const TCHAR* szLanguage = nullptr);

private:
	CRITICAL_SECTION m_csRes;
	tstring		m_strResFile;		//��Դ�ļ�
	CLanguage*	m_pCurrLanguage;	//��ǰѡ�������
	mapMultiRes m_mapMultiRes;
};

#endif // !defined(AFX_LANGUAGE_H__7BD99134_5302_423A_BE03_FEE100F15376__INCLUDED_)
