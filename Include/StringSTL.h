/********************************************************************

��Ȩ���� (c) 2011-2099, Howard's Studio

V 1.0

����:	Howard <howe703@126.com>

����:	CStringSTL�࣬��һ��string�İ�װ��
		����MFC��CString��װ��һЩ�ӿ�

��ʷ:	1��2011-07-12 ����
		2��2011-07-21 ����GetData�ӿ�
		3������TrimLeft( const char* )��TrimeRight( const char*) �ӿ�

����:	1��CStringSTL str = "ABC";
		   printf("%s %d", str, 1 );
		   ��ʾ�Ľ�����£�
		   ABC -858993460
		   ��str������ʾ�ĸ�ʽ����������
		   Ҫ�� printf("%s %d", str.GetData(), 1 ) ����ʽ

*********************************************************************/

#ifndef HOWARD_STRINGSTL_H 
#define HOWARD_STRINGSTL_H


#pragma warning(disable:4786) 
#pragma warning(disable:4275) 

#include <string>

// ͳһ�ַ�����������
#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

class CStringSTL
{
public:
	CStringSTL(const CStringSTL& string1);
	CStringSTL(const std::string string1);
	CStringSTL(const char *lpsz);
	CStringSTL(const char ch);
	CStringSTL();
	~CStringSTL();

	// ���ļ����ݰ������Ƽ��ص��ַ���,���ض�ȡ�����ֽ���
	// szFile:�ļ�·��
	// nStart:�ļ����ص���ʼλ��,Ϊ0��ʾ�ļ���ͷ
	// nMaxBytes:�����ص��ֽ���,Ϊ0ʱʹ���ļ�ʵ�ʴ�С
	// ע��:����֮ǰ������ַ���
	int LoadFileA(const char* szFile, unsigned int nMaxBytes = 0);
	int LoadFileW(const wchar_t* wszFile, unsigned int nMaxBytes = 0);
	int LoadFileT(const char* szFile, unsigned int nMaxBytes = 0);
	int LoadFileT(const wchar_t* wszFile, unsigned int nMaxBytes = 0);
	int LoadFileMidA(const char* szFile, unsigned int nStart = 0, unsigned int nMaxBytes = 0);
	int LoadFileMidW(const wchar_t* wszFile, unsigned int nStart = 0, unsigned int nMaxBytes = 0);
	int LoadFileMidT(const char* szFile, unsigned int nStart = 0, unsigned int nMaxBytes = 0);
	int LoadFileMidT(const wchar_t* wszFile, unsigned int nStart = 0, unsigned int nMaxBytes = 0);

protected:
	int LoadFileByFile(FILE* pFile, unsigned int nMaxBytes = 0);
	int LoadFileByFileMid(FILE* pFile, unsigned int nStart = 0, unsigned int nMaxBytes = 0);

public:
	const char* GetData() const;
	int Delete(int nIndex, int nCount = 1);
	int Insert(int nIndex, const char * lpsz);
	int Insert(int nIndex, char ch);
	int Remove(char ch);
	void MakeReverse();
	int Find(char ch) const;
	int Find(const char * lpszSub) const;
	int Find(char ch, int nStart) const;
	int Find(const char * lpsz, int nStart) const;
	int ReverseFind(char ch) const;
	int FindOneOf(const char * lpsz) const;
	int Format(const char* lpszFormat, ...);
	int GetLength() const;
	std::string Left(int nCount) const;
	std::string Right(int nCount) const;
	std::string Mid(int nFirst) const;
	std::string Mid(int nFirst, int nCount) const;

	void MakeUpper();
	void MakeLower();

	bool IsEmpty() const;
	void Empty();

	char GetAt(int nIndex) const;
	void SetAt(int nIndex, char ch);

	int Compare(const char * lpsz) const;
	int Compare(const CStringSTL& str) const;
	int Compare(const std::string& str) const;
	int CompareNoCase(const char * lpsz) const;
	int CompareNoCase(const CStringSTL& string1) const;
	int CompareNoCase(const std::string& str) const;

	void TrimLeft();
	void TrimLeft(char chTarget);
	void TrimLeft(const char* lpsz);
	void TrimRight();
	void TrimRight(char chTarget);
	void TrimRight(const char* lpsz);

	void Replace(char chOld, char chNew);
	void Replace(const char* lpszOld, const char* lpszNew);
	char * GetBuffer(int nMinBufLength);
	void ReleaseBuffer(int nNewLength = -1);

	// �����ַ���,�������м丽�ӷָ���
	void AddSeparator(const char* szSeparator = ",");
	void AddStringStatus(const char* szAdd, const char* szSeparator = ",");

	char operator [](int nIndex) const;
	operator const char* () const;

	//operator const std::string& () const;

	// ��ȡ�ַ�������(��ת��)
	const std::string& str() const;
	// ��ȡutf8�ַ���
	//std::string utf()
	// ��ȡUnicode�ַ���
	//std::wstring wstr();

	// ��ȡ��ǰ�ַ�����MD5ֵ
	//std::string md5();

	CStringSTL& operator = (const std::string& str);
	CStringSTL& operator = (char ch);
	CStringSTL& operator = (const char * lpsz);
	CStringSTL& operator = (const CStringSTL& str);

	const CStringSTL& operator += (const char* lpsz);
	const CStringSTL& operator += (char ch);
	const CStringSTL& operator += (const CStringSTL& string1);

	friend std::string operator + (const CStringSTL& string1, const CStringSTL& string2);
	friend std::string operator + (const CStringSTL& string1, char ch);
	friend std::string operator + (char ch, const CStringSTL& string1);
	friend std::string operator + (const CStringSTL& string1, const char* lpsz);
	friend std::string operator + (const char* lpsz, const CStringSTL& string1);
	friend std::string operator + (const std::string& string1, const CStringSTL& string2);
	friend std::string operator + (const CStringSTL& string1, const std::string& string2);

protected:
	//CStringSTL str = "ABC";
	//printf("%s %d", str, 1 );��str�����ʽ����ʾ���������󣬸������·�ʽ����
	//printf("%s %d", str.GetData(), 1 );
#if !defined(_WIN64)
	// ��ָ�����κ�����,ȡ��ʹ�� [2018-8-11 ydl]
	char* m_pData;
#endif
	std::string m_str;
};

// Compare helpers
bool  operator == (const CStringSTL& str1, const CStringSTL& str2);
bool  operator == (const CStringSTL& str1, const char* lpsz);
bool  operator == (const char* lpsz, const CStringSTL& str2);
bool  operator == (const std::string& str1, const CStringSTL& str2);
bool  operator == (const CStringSTL& str1, const std::string& str2);
bool  operator != (const CStringSTL& str1, const CStringSTL& str2);
bool  operator != (const CStringSTL& str1, const char* lpsz);
bool  operator != (const char* lpsz, const CStringSTL& str2);
bool  operator != (const std::string& str1, const CStringSTL& str2);
bool  operator != (const CStringSTL& str1, const std::string& str2);
bool  operator <  (const CStringSTL& str1, const CStringSTL& str2);
bool  operator <  (const CStringSTL& str1, const char* lpsz);
bool  operator <  (const char* lpsz, const CStringSTL& str2);
bool  operator < (const std::string& str1, const CStringSTL& str2);
bool  operator < (const CStringSTL& str1, const std::string& str2);
bool  operator >  (const CStringSTL& str1, const CStringSTL& str2);
bool  operator >  (const CStringSTL& str1, const char* lpsz);
bool  operator >  (const char* lpsz, const CStringSTL& str2);
bool  operator > (const std::string& str1, const CStringSTL& str2);
bool  operator > (const CStringSTL& str1, const std::string& str2);
bool  operator <= (const CStringSTL& str1, const CStringSTL& str2);
bool  operator <= (const CStringSTL& str1, const char* lpsz);
bool  operator <= (const char* lpsz, const CStringSTL& str2);
bool  operator <= (const std::string& str1, const CStringSTL& str2);
bool  operator <= (const CStringSTL& str1, const std::string& str2);
bool  operator >= (const CStringSTL& str1, const CStringSTL& str2);
bool  operator >= (const CStringSTL& str1, const char* lpsz);
bool  operator >= (const char* lpsz, const CStringSTL& str2);
bool  operator >= (const std::string& str1, const CStringSTL& str2);
bool  operator >= (const CStringSTL& str1, const std::string& str2);

CStringSTL to_stringstl(int nValue, const char* szFmt = NULL);//Ĭ��Ϊ"%d"
CStringSTL to_stringstl(unsigned int uValue, const char* szFmt = NULL);	//Ĭ��Ϊ"%u"
CStringSTL to_stringstl(__int64 nValue, const char* szFmt = NULL);//Ĭ��Ϊ"%I64d"
CStringSTL to_stringstl(unsigned __int64 uValue, const char* szFmt = NULL);	//Ĭ��Ϊ"%I64u"
CStringSTL to_stringstl(double lfValue, const char* szFmt = NULL);	//Ĭ��Ϊ"%lf",ɾ��С����֮����ظ�0(���ٱ���1λ)
CStringSTL to_stringstl(const char* szValue);
CStringSTL to_stringstl(const std::string& strValue);


/**
 * @Description: ��map������first��ʽ��Ϊ�ַ���
 * @param: MapObj: ����.begin()
 * @param: szSplit: �ָ�����
 * @return: void
 * @Author:
 */
template <class _Iter>
CStringSTL STRINGFormatIntFromMap1st(_Iter IterB, _Iter IterE, const CStringSTL& strSplit = ",")
{
	CStringSTL str;
	while (IterB != IterE)
	{
		str.AddStringStatus(to_stringstl((*IterB++).first), strSplit);
	}
	return str;
}

template <class _Map>
CStringSTL STRINGFormatIntFromMap1st(const _Map& MapObj, const CStringSTL& strSplit = ",")
{
	return STRINGFormatIntFromMap1st(std::begin(MapObj), std::end(MapObj), strSplit);
}

/**
 * @Description: ��map������second��ʽ��Ϊ�ַ���
 * @param: MapObj: ����.begin()
 * @param: szSplit: �ָ�����
 * @return: void
 * @Author:
 */
template <class _Iter>
CStringSTL STRINGFormatIntFromMap2nd(_Iter IterB, _Iter IterE, const CStringSTL& strSplit = ",")
{
	CStringSTL str;
	while (IterB != IterE)
	{
		str.AddStringStatus(to_stringstl((*IterB++).second), strSplit);
	}
	return str;
}

template <class _Map>
CStringSTL STRINGFormatIntFromMap2nd(const _Map& MapObj, const CStringSTL& strSplit = ",")
{
	return STRINGFormatIntFromMap2nd(std::begin(MapObj), std::end(MapObj), strSplit);
}



/**
 * @Description: �����������ݸ�ʽ��Ϊ�ַ���
 * @param: Obj: ����
 * @param: cSplit: �ָ�����
 * @return: szSplit
 * @Author:
 */
template <class _Iter>
CStringSTL STRINGFormatIntFromObj(_Iter IterB, _Iter IterE, const CStringSTL& strSplit = ",")
{
	CStringSTL str;
	while (IterB != IterE)
	{
		str.AddStringStatus(to_stringstl(*IterB++), strSplit);
	}
	return str;
}

template <class _Obj>
CStringSTL STRINGFormatIntFromObj(const _Obj& Obj, const CStringSTL& strSplit = ",")
{
	return STRINGFormatIntFromObj(std::begin(Obj), std::end(Obj), strSplit);
}

// Mysql ��ʽ��Ϊ%s=VALUES(%s)
template <class T>
CStringSTL STRINGFormatUpdateColumn1(T szColumn)
{
	CStringSTL str;
	str.Format("%s=VALUES(%s)", szColumn, szColumn);
	return str;
}

template <int nSize>
CStringSTL STRINGFormatUpdateColumn(const char* (&pColumnStr)[nSize])
{
	CStringSTL str;
	for (int i = 0; i < nSize; i++)
	{
		str.AddStringStatus(STRINGFormatUpdateColumn1(pColumnStr[i]));
	}
	return str;
}

#endif // HOWARD_STRINGSTL_H
