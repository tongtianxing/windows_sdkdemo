#ifndef _CHAR_SET_CONVERT_H
#define _CHAR_SET_CONVERT_H

#include <windows.h>
#include <string>


#if defined(_UNICODE) || defined(UNICODE)  
#define Str2Utf8	UcsToUtf8
#define Str2CUtf8(s)	UcsToUtf8(s).c_str()
#define Str2Utf8Ex	UcsToUtf8Ex
#define Str2CUtf8Ex(s)	UcsToUtf8Ex(s).c_str()
#define Utf2Str		Utf8ToUcs
#define Utf2CStr(s)	Utf8ToUcs(s).c_str()
#define Str2Ansi	UcsToAnsi
#define Str2CAnsi(s)	UcsToAnsi(s).c_str()
#define Str2Ucs(s)	std::wstring(s)
#define Str2CUcs(s)	Str2Ucs(s).c_str()
#define Ansi2Str	AnsiToUcs
#define Ansi2CStr(s) AnsiToUcs(s).c_str()
#define Ucs2Str		Str2Ucs
#define Ucs2CStr(s)	Ucs2Str(s).c_str()
#define UrlGB2312Encode	UrlGB2312EncodeW
#else
#define Str2Utf8	AnsiToUtf8
#define Str2CUtf8(s)	AnsiToUtf8(s).c_str()
#define Str2Utf8Ex	AnsiToUtf8Ex
#define Str2CUtf8Ex(s)	AnsiToUtf8Ex(s).c_str()
#define Utf2Str		Utf8ToAnsi
#define Utf2CStr(s)	Utf8ToAnsi(s).c_str()
#define Str2Ansi(s)	std::string(s)
#define Str2CAnsi(s) Str2Ansi(s).c_str()
#define Str2Ucs		AnsiToUcs
#define Str2CUcs(s)	AnsiToUcs(s).c_str()
#define Ansi2Str	Str2Ansi
#define Ansi2CStr(s) Str2Ansi(s).c_str()
#define Ucs2Str		UcsToAnsi
#define Ucs2CStr(s)	UcsToAnsi(s).c_str()
#define UrlGB2312Encode	UrlGB2312EncodeA
#endif

#define Wide2Asc	UcsToAnsi
#define Asc2Wide	AnsiToUcs



int Utf8ToUcsEx(const char* lpszUtf8, wchar_t** ppUcsBuf);
int UcsToAnsiEx(const wchar_t* lpWUcs, char** ppAnsiBuf);
int Utf8ToAnsiEx(const char* lpszUtf8, char** ppAnsiBuf);
int UcsToUtf8Ex(const wchar_t* lpwUcs, char** ppUtf8Buf);
int AnsiToUcsEx(const char* lpszAnsi, wchar_t** ppUcsBuf);
int AnsiToUtf8Ex(const char* lpszAnsi, char** ppUtf8Buf);


int Utf8ToUcs(const char* lpszUtf8, wchar_t* lpUcsBuf, int nBufSize);
template <int nBufSize> int Utf8ToUcs(const char* lpszUtf8, wchar_t(&szUcsBuf)[nBufSize]) { return Utf8ToUcs(lpszUtf8, szUcsBuf, nBufSize); }
int UcsToAnsi(const wchar_t* lpWUcs, char* pAnsiBuf, int nBufSize);
template <int nBufSize> int UcsToAnsi(const wchar_t* lpWUcs, char(&szAnsiBuf)[nBufSize]) { return UcsToAnsi(lpWUcs, szAnsiBuf, nBufSize); }
int Utf8ToAnsi(const char* lpszUtf8, char* pAnsiBuf, int nBufSize);
template <int nBufSize> int Utf8ToAnsi(const char* lpszUtf8, char(&szAnsiBuf)[nBufSize]) { return Utf8ToAnsi(lpszUtf8, szAnsiBuf, nBufSize); }
int UcsToUtf8(const wchar_t* lpwUcs, char* pUtf8Buf, int nBufSize);
template <int nBufSize> int UcsToUtf8(const wchar_t* lpwUcs, char(&szUtf8Buf)[nBufSize]) { return UcsToUtf8(lpwUcs, szUtf8Buf, nBufSize); }
int AnsiToUcs(const char* lpszAnsi, wchar_t* pUcsBuf, int nBufSize);
template <int nBufSize> int AnsiToUcs(const char* lpszAnsi, wchar_t(&szUcsBuf)[nBufSize]) { return AnsiToUcs(lpszAnsi, szUcsBuf, nBufSize); }
int AnsiToUtf8(const char* lpszAnsi, char* pUtf8Buf, int nBufSize);
template <int nBufSize> int AnsiToUtf8(const char* lpszAnsi, char(&szUtf8Buf)[nBufSize]) { return AnsiToUtf8(lpszAnsi, szUtf8Buf, nBufSize); }

int UcsToGB2312(const wchar_t* lpWUcs, char* pGB2312Buf, int nBufSize);
template <int nBufSize> int UcsToGB2312(const wchar_t* lpWUcs, char(&szGB2312Buf)[nBufSize]) { return UcsToGB2312(lpWUcs, szGB2312Buf, nBufSize); }

int Utf8ToGB2312(const char* lpszUtf8, char* pGB2312Buf, int nBufSize);
template <int nBufSize> int Utf8ToGB2312(const char* lpszUtf8, char(&szGB2312Buf)[nBufSize]) { return Utf8ToGB2312(lpszUtf8, szGB2312Buf, nBufSize); }

int UcsToBIG5(const wchar_t* lpWUcs, char* pBig5Buf, int nBufSize);
template <int nBufSize> int UcsToBIG5(const wchar_t* lpWUcs, char(&szBig5Buf)[nBufSize]) { return UcsToBIG5(lpWUcs, szBig5Buf, nBufSize); }

int Utf8ToBIG5(const char* lpszUtf8, char* pBig5Buf, int nBufSize);
template <int nBufSize> int Utf8ToBIG5(const char* lpszUtf8, char(&szBig5Buf)[nBufSize]) { return Utf8ToBIG5(lpszUtf8, szBig5Buf, nBufSize); }
	


// 直接返回转换后的字符串,不用定义临时对象
// 增加长度参数,默认-1表示自动计算 [2018-6-14 ydl]
std::wstring Utf8ToUcs(const char* lpszUtf8, int nBufLen = -1);
std::wstring Utf8ToUcs(const std::string& strUtf8);
std::wstring AnsiToUcs(const char* lpszAnsi, int nBufLen = -1);
std::wstring AnsiToUcs(const std::string& strAnsi);
std::string UcsToAnsi(const wchar_t* lpWUcs, int nBufLen = -1);
std::string UcsToAnsi(const std::wstring& strWUcs);
std::string Utf8ToAnsi(const char* lpszUtf8, int nBufLen = -1);
std::string Utf8ToAnsi(const std::string& strUtf8);
std::string UcsToUtf8(const wchar_t* lpwUcs, int nBufLen = -1);
std::string UcsToUtf8(const std::wstring& strWUcs);
std::string AnsiToUtf8(const char* lpszAnsi, int nBufLen = -1);
std::string AnsiToUtf8(const std::string& strAnsi);
std::string UcsToGB2312(const wchar_t* lpWUcs, int nBufLen = -1);
std::string UcsToGB2312(const std::wstring& strWUcs);
std::string Utf8ToGB2312(const char* lpszUtf8, int nBufLen = -1);
std::string Utf8ToGB2312(const std::string& strUtf8);



//判断文件是否utf8格式(有BOM: Byte Order Mark)
bool IsUtf8File(LPCSTR lpszFileName);
bool IsUtf8File(LPCWSTR lpszFileName);

//将URL链接进行解码
std::string UrlGB2312Decode(const std::string& str);

//编码为GB2312编码并按URL编码特殊字符
std::string UrlGB2312EncodeA(const char* lpszAnsi);
std::string UrlGB2312EncodeW(const wchar_t* lpwUcs);


//进行Utf8转换到ios8859的编码
//int Utf8ToISO8859_1(const char* szUtf8Buf, char* pISO8859, int nBufSize);
//因链接libiconv.lib会导致程序在不使用此库代码时,体积大幅增加,此处将此函数移动到另一文件
// 如想使用,添加 #include <libiconv.h>,里面有相关代码
#define Utf8ToISO8859_1(...)		static_assert(false, "error:Utf8ToISO8859_1 deprecated!")

#endif //_CHAR_SET_CONVERT_H