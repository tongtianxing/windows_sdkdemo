/********************************************************************

版权所有 (c) 2011-2099, Howard's Studio

V 1.0

作者:	Howard <howe703@126.com>

描述:	CStringSTL类，是一个string的包装类
		仿照MFC的CString封装了一些接口

历史:	1、2011-07-12 创建
		2、2011-07-21 增加GetData接口
		3、增加TrimLeft( const char* )和TrimeRight( const char*) 接口

问题:	1、CStringSTL str = "ABC";
		   printf("%s %d", str, 1 );
		   显示的结果如下：
		   ABC -858993460
		   在str后面显示的格式化数据有误，
		   要用 printf("%s %d", str.GetData(), 1 ) 的形式

*********************************************************************/

#ifndef HOWARD_STRINGSTL_H 
#define HOWARD_STRINGSTL_H


#pragma warning(disable:4786) 
#pragma warning(disable:4275) 

#include <string>

// 统一字符串的类型名
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

	// 将文件内容按二进制加载到字符串,返回读取到的字节数
	// szFile:文件路径
	// nStart:文件加载的起始位置,为0表示文件开头
	// nMaxBytes:最大加载的字节数,为0时使用文件实际大小
	// 注意:加载之前会清空字符串
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

	// 附加字符串,并且在中间附加分隔符
	void AddSeparator(const char* szSeparator = ",");
	void AddStringStatus(const char* szAdd, const char* szSeparator = ",");

	char operator [](int nIndex) const;
	operator const char* () const;

	//operator const std::string& () const;

	// 获取字符串对象(不转码)
	const std::string& str() const;
	// 获取utf8字符串
	//std::string utf()
	// 获取Unicode字符串
	//std::wstring wstr();

	// 获取当前字符串的MD5值
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
	//printf("%s %d", str, 1 );在str后面格式化显示的数据有误，改用如下方式调用
	//printf("%s %d", str.GetData(), 1 );
#if !defined(_WIN64)
	// 此指针无任何作用,取消使用 [2018-8-11 ydl]
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

CStringSTL to_stringstl(int nValue, const char* szFmt = NULL);//默认为"%d"
CStringSTL to_stringstl(unsigned int uValue, const char* szFmt = NULL);	//默认为"%u"
CStringSTL to_stringstl(__int64 nValue, const char* szFmt = NULL);//默认为"%I64d"
CStringSTL to_stringstl(unsigned __int64 uValue, const char* szFmt = NULL);	//默认为"%I64u"
CStringSTL to_stringstl(double lfValue, const char* szFmt = NULL);	//默认为"%lf",删除小数点之后的重复0(最少保留1位)
CStringSTL to_stringstl(const char* szValue);
CStringSTL to_stringstl(const std::string& strValue);


/**
 * @Description: 将map容器的first格式化为字符串
 * @param: MapObj: 对象.begin()
 * @param: szSplit: 分隔符号
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
 * @Description: 将map容器的second格式化为字符串
 * @param: MapObj: 对象.begin()
 * @param: szSplit: 分隔符号
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
 * @Description: 将容器的数据格式化为字符串
 * @param: Obj: 对象
 * @param: cSplit: 分隔符号
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

// Mysql 格式化为%s=VALUES(%s)
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
