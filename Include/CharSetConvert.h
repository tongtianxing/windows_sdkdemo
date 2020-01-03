#ifndef _CHAR_SET_CONVERT_H
#define _CHAR_SET_CONVERT_H

#include <windows.h>
#include <string>


#if defined(_UNICODE) || defined(UNICODE)  
#define Str2Utf8	UcsToUtf8
#define Str2Utf8Ex	UcsToUtf8Ex
#define Utf2Str		Utf8ToUcs
#else
#define Str2Utf8	AnsiToUtf8
#define Str2Utf8Ex	AnsiToUtf8Ex
#define Utf2Str		Utf8ToAnsi
#endif

#define Wide2Asc	UcsToAnsi
#define Asc2Wide	AnsiToUcs

#if defined(_UNICODE) || defined(UNICODE)  
#define Str2Utf8	UcsToUtf8
#define Str2Utf8Ex	UcsToUtf8Ex
#define Utf2Str		Utf8ToUcs
#else
#define Str2Utf8	AnsiToUtf8
#define Str2Utf8Ex	AnsiToUtf8Ex
#define Utf2Str		Utf8ToAnsi
#endif


int Utf8ToUcsEx( const char* lpszUtf8, wchar_t** ppUcsBuf );
int UcsToAnsiEx( const wchar_t* lpWUcs, char** ppAnsiBuf );
int Utf8ToAnsiEx( const char* lpszUtf8, char** ppAnsiBuf );
int UcsToUtf8Ex( const wchar_t* lpwUcs, char** ppUtf8Buf );
int AnsiToUcsEx( const char* lpszAnsi, wchar_t** ppUcsBuf );
int AnsiToUtf8Ex( const char* lpszAnsi, char** ppUtf8Buf);


int Utf8ToUcs( const char* lpszUtf8, wchar_t* lpUcsBuf, int nBufSize);
int UcsToAnsi( const wchar_t* lpWUcs, char* pAnsiBuf, int nBufSize );
int Utf8ToAnsi( const char* lpszUtf8, char* pAnsiBuf, int nBufSize );
int UcsToUtf8( const wchar_t* lpwUcs, char* pUtf8Buf, int nBufSize);
int AnsiToUcs( const char* lpszAnsi, wchar_t* pUcsBuf, int nBufSize );
int AnsiToUtf8( const char* lpszAnsi, char* pUtf8Buf, int nBufSize);
int UcsToGB2312(const wchar_t* lpWUcs, char* pGB2312Buf, int nBufSize);
int Utf8ToGB2312(const char* lpszUtf8, char* pGB2312Buf, int nBufSize);
int UcsToBIG5(const wchar_t* lpWUcs, char* pBig5Buf, int nBufSize); 
int Utf8ToBIG5(const char* lpszUtf8, char* pBig5Buf, int nBufSize);  

//判断文件是否utf8格式(有BOM: Byte Order Mark)
bool IsUtf8File( const char* lpszFileName );

//将URL链接进行解码
std::string UrlGB2312Decode(const std::string& str);

//进行Utf8转换到ios8859的编码
int Utf8ToISO8859_1(const char* szUtf8Buf, char* pISO8859, int nBufSize);

#endif //_CHAR_SET_CONVERT_H