#ifndef _PUBLIC_FUNCTION_H_
#define _PUBLIC_FUNCTION_H_

#include <crtdbg.h>

#ifndef ASSERT
	#if defined(_DEBUG)
		#if !defined(_WIN64)
		#define ASSERT(expr)	\
						do {    \
						if (!(expr) && \
						(1 == _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr))) \
						__asm { int 3 }; \
						} while (0)
		#else
		#define ASSERT	_ASSERT
		#endif
	#else
	#define ASSERT(expr)
	#endif
#endif

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
#define put8(p, dat) ( (p)[0] = (u8)(((dat)>>0)&0xff) )
#define putle16(p, dat) ( (p)[0] = (u8)(((u16)(dat)>>0)&0xff), (p)[1] = (u8)(((u16)(dat)>>8)&0xff) )
#define putle24(p, dat) ( (p)[0] = (u8)(((u32)(dat)>>0)&0xff), (p)[1] = (u8)(((u32)(dat)>>8)&0xff), (p)[2] = (u8)(((u32)(dat)>>16)&0xff) )
#define putle32(p, dat) ( (p)[0] = (u8)(((u32)(dat)>>0)&0xff), (p)[1] = (u8)(((u32)(dat)>>8)&0xff), (p)[2] = (u8)(((u32)(dat)>>16)&0xff), (p)[3] = (u8)(((u32)(dat)>>24)&0xff) )
#define putbe16(p, dat) ( (p)[0] = (u8)(((u16)(dat)>>8)&0xff), (p)[1] = (u8)(((u16)(dat)>>0)&0xff) )
#define putbe24(p, dat) ( (p)[0] = (u8)(((u32)(dat)>>16)&0xff), (p)[1] = (u8)(((u32)(dat)>>8)&0xff), (p)[2] = (u8)(((u32)(dat)>>0)&0xff) )
#define putbe32(p, dat) ( (p)[0] = (u8)(((u32)(dat)>>24)&0xff), (p)[1] = (u8)(((u32)(dat)>>16)&0xff), (p)[2] = (u8)(((u32)(dat)>>8)&0xff), (p)[3] = (u8)(((u32)(dat)>>0)&0xff) )
#define putbcd(p, dat)	do { u8 _n = (u8)(dat); (p)[0] = (u8)(_n % 100) / 10 * 16 + (u8)(_n) % 10; } while (0)
#define putbcd2(p, dat)	do { putbcd(p, dat / 100 % 100); putbcd(p + 1, dat % 100); } while (0);
#define putbcd3(p, dat)	do { putbcd(p, dat / 10000 % 100); putbcd2(p + 1, dat % 10000); } while (0);
#define putbcd4(p, dat)	do { putbcd2(p, dat / 10000 % 10000); putbcd2(p + 2, dat % 10000); } while (0);

	
#define get8(p) ( (u8)(p)[0] )
#define getle16(p) ( ((u8)(p)[0] << 0) | ((u8)(p)[1] << 8) )
#define getle24(p) ( ((u8)(p)[0] << 0) | ((u8)(p)[1] << 8) | ((u8)(p)[2] << 16) )
#define getle32(p) ( ((u8)(p)[0] << 0) | ((u8)(p)[1] << 8) | ((u8)(p)[2] << 16) | ((u8)(p)[3] << 24) )
#define getbe16(p) ( ((u8)(p)[0] << 8) | ((u8)(p)[1] << 0) )
#define getbe24(p) ( ((u8)(p)[0] << 16) | ((u8)(p)[1] << 8) | ((u8)(p)[2] << 0) )
#define getbe32(p) ( ((u8)(p)[0] << 24) | ((u8)(p)[1] << 16) | ((u8)(p)[2] << 8) | ((u8)(p)[3] << 0) )
#define getbcd(p) ( (u8)(p)[0] / 16 * 10 + (u8)(p)[0] % 16 )
#define getbcd2(p) ( getbcd(p) * (u32)100 + getbcd(p + 1) )
#define getbcd3(p) ( getbcd(p) * (u32)10000 + getbcd2(p + 1) )
#define getbcd4(p) ( getbcd2(p) * (u32)10000 + getbcd2(p + 2) )


#include "StringSTL.h"
#include <vector>
#include <map>

typedef struct tagFILEFileInfo
{
	char	szFileName[MAX_PATH];
	long	nFileLength;
	WORD	wFatDate;
	WORD	wFatTime;
}FILEFileInfo_S;
typedef struct tagFILEFileInfoW
{
	wchar_t	szFileName[MAX_PATH];
	long	nFileLength;
	WORD	wFatDate;
	WORD	wFatTime;
}FILEFileInfoW_S;
typedef std::vector<FILEFileInfo_S>	lstTtxFileInfo;
typedef lstTtxFileInfo::iterator	iterTtxFileInfo;
typedef std::vector<FILEFileInfoW_S>	lstTtxFileInfoW;

#ifdef _UNICODE
#define tagFILEFileInfoT	tagFILEFileInfoW
#define FILEFileInfoT_S		FILEFileInfoW_S
#define lstTtxFileInfoT		lstTtxFileInfoW
#else
#define tagFILEFileInfoT	tagFILEFileInfo
#define FILEFileInfoT_S		FILEFileInfo_S
#define lstTtxFileInfoT		lstTtxFileInfo
#endif

#pragma pack(1)

typedef struct _tagSTRINGMyArray
{
	char szVal[64];
}STRINGMyArray_S, *LPSTRINGMyArray_S;

typedef struct _tagSTRINGMyArrayW
{
	wchar_t wszVal[64];
}STRINGMyArrayW_S, *LPSTRINGMyArrayW_S;

typedef struct _tagTIMEMonth
{
	SYSTEMTIME beg;
	SYSTEMTIME end;
}TIMEMonth_S, *LPTIMEMonth_S;

#pragma pack()

// struct map_string_hash
// {
// 	static const size_t   bucket_size = 4;   // 猜测这个变量是初始化hash_map的大小  
// 	static const size_t   min_buckets = 8; 
// 
// 	//BKDR hash algorithm，有关字符串hash函数，可以去找找资料看看
// 	size_t operator()(const char* str) const
// 	{
// 		//return atoi(str);
// 		//return __stl_hash_string(str);
// 		int seed = 131;//31  131 1313 13131131313 etc//
// 		int hash = 0;
// 		while(*str)
// 		{
// 			hash = (hash * seed) + (*str);
// 			str ++;
// 		}
// 
// 		return size_t(hash); 
// 	}
// 
// 	bool operator()(const char* s1, const char* s2) const 
// 	{
// 		return strcmp(s1,s2) == 0 ? true : false;
// 	}
// };

struct map_string_cmp
{
	bool operator()( const char * s1, const char * s2 ) const
	{
		return strcmp( s1, s2 ) < 0;
	}
};

struct map_std_string_cmp
{
	bool operator()( const std::string& str1, const std::string& str2 ) const
	{
		return str1.compare(str2) < 0;
	}
};

#ifdef _UNICODE
typedef std::wstring tstring;
#define __FUNCTIONT__	__FUNCTIONW__
#else
typedef std::string tstring;
#define __FUNCTIONT__	__FUNCTION__
#endif

// #ifdef _UNICODE
// 	typedef TCHAR wchar_t
// #else
// 	typedef TCHAR char
// #endif

/*****************************************************************************
//调试相关函数
******************************************************************************/

/**
 * @Description: 将字符串格式化成16进制的形式
 * @Author: leeafu	2015-04-10
 */
void DEBUGFormatHex(TCHAR* pDestBuf, int nDestLen, const char* pBuffer, int nLength);
void DEBUGFormatHexA(char* pDestBuf, int nDestLen, const char* pBuffer, int nLength);
void DEBUGFormatHexW(wchar_t* pDestBuf, int nDestLen, const char* pBuffer, int nLength);
#ifdef _UNICODE
#define	DEBUGFormatHexT DEBUGFormatHexW
#else
#define DEBUGFormatHexT DEBUGFormatHexA
#endif

/**
 * @Description: 输出日志到 Studio的Output窗口
 * @param: fmt
 * @return: void 
 * @Author: leeafu	2012-04-15
  DEBUGTraceOutput 输出长度缓存是char[512]和wchar_t[512]
  DEBUGTraceOutputLong 先计算格式化字符串长度,最大支持char[65536]和wchar_t[32768]
 */
void DEBUGTraceOutput(LPCTSTR fmt, ...);
void DEBUGTraceOutputA(LPCSTR fmt, ...);
void DEBUGTraceOutputW(LPCWSTR fmt, ...);
void DEBUGTraceOutputLongA(LPCSTR fmt, ...);
void DEBUGTraceOutputLongW(LPCWSTR fmt, ...);
#ifdef _UNICODE
#define	DEBUGTraceOutputT DEBUGTraceOutputW
#define DEBUGTraceOutputLong DEBUGTraceOutputLongW
#else
#define DEBUGTraceOutputT DEBUGTraceOutputA
#define DEBUGTraceOutputLong DEBUGTraceOutputLongA
#endif

// 默认使用Long接口打印 [2022-2-18 ydl]
#define DEBUG_TRACE_OUTPUT		DEBUGTraceOutputLong
#define DEBUG_TRACE_OUTPUT_FUNC(fmt, ...)		do \
{ \
	DEBUGTraceOutputLong(_T("%s ") fmt, __FUNCTIONT__, __VA_ARGS__); \
} while (0);


#define DEBUG_TRACE_OUTPUTA		DEBUGTraceOutputLongA
#define DEBUG_TRACE_OUTPUTA_FUNC(fmt, ...)		do \
{ \
	DEBUGTraceOutputLongA("%s " fmt, __FUNCTION__, __VA_ARGS__); \
} while (0);

/*
 * 打印16进制
*/
void DEBUGTraceHexOutput(const char* pBuffer, int nLength);

/**
 * @Description: 输出日志到控制台窗口
 * @param: fmt
 * @return: void 
 * @Author: leeafu	2012-04-15
 */
void DEBUGTraceConsole(LPCTSTR fmt, ...);
void DEBUGTraceConsoleA(LPCSTR fmt, ...);
void DEBUGTraceConsoleW(LPCWSTR fmt, ...);

/*
 * 打印16进制
*/
void DEBUGTraceHexConsole(const char* pBuffer, int nLength);

/*****************************************************************************
//路径相关函数
******************************************************************************/

/**
 * @Description: 获取程序名称
 * @return: const char* 程序名称(主程序名)
 * @Author: leeafu	2013-04-25
 */
LPCTSTR	PATHGetAppName();
LPCSTR	PATHGetAppNameA();
LPCWSTR	PATHGetAppNameW();
#ifdef _UNICODE
#define	PATHGetAppNameT PATHGetAppNameW
#else
#define PATHGetAppNameT PATHGetAppNameA
#endif

/**
 * @Description: 获取程序路径
 * @return: const char* 程序路径 
 * @Author: leeafu	2012-04-15
 */
LPCTSTR	PATHGetAppPath();
LPCSTR	PATHGetAppPathA();
LPCWSTR	PATHGetAppPathW();
#ifdef _UNICODE
#define	PATHGetAppPathT PATHGetAppPathW
#else
#define PATHGetAppPathT PATHGetAppPathA
#endif

/**
 * @Description: 获取调用程序或库的模块句柄
 * @return: HMODULE 句柄
 * @Author: ydl	2018-11-29
 */
HMODULE	PATHGetModuleHandle();

/**
 * @Description: 获取指定模块名称
 * @param: hModule 模块句柄,为空表示调用此接口的程序或库(注意:不支持通过此接口获取其他库的名称)
 * @param: bIsDelSuffix 是否需要删除后缀,默认返回
 * @return: LPCTSTR 模块名称
 * @Author: ydl 2018-5-24
 */
LPCTSTR PATHGetModuleName(HMODULE hModule = NULL, BOOL bIsDelSuffix = TRUE);
LPCSTR PATHGetModuleNameA(HMODULE hModule = NULL, BOOL bIsDelSuffix = TRUE);
LPCWSTR PATHGetModuleNameW(HMODULE hModule = NULL, BOOL bIsDelSuffix = TRUE);
#ifdef _UNICODE
#define	PATHGetModuleNameT PATHGetModuleNameW
#else
#define PATHGetModuleNameT PATHGetModuleNameA
#endif

/**
 * @Description: 获取程序路径
 * @param: hModule 模块句柄，为空值表示所在程序
 * @return: szPath 模块目录，必须保证长度为MAX_PATH
 * @Author: leeafu	2013-08-19
 */
void PATHGetModulePath(HMODULE hModule, TCHAR* szPath);
void PATHGetModulePathA(HMODULE hModule, char* szPath);
void PATHGetModulePathW(HMODULE hModule, wchar_t* szPath);
#ifdef _UNICODE
#define	PATHGetModulePathT PATHGetModulePathW
#else
#define PATHGetModulePathT PATHGetModulePathA
#endif

/**
 * @Description: 获取程序父目录路径
 * @return: const char* 程序父目录路径  
 * @Author: leeafu	2012-04-15
 */
LPCTSTR	PATHGetAppParentPath();
LPCSTR	PATHGetAppParentPathA();
LPCWSTR	PATHGetAppParentPathW();
#ifdef _UNICODE
#define	PATHGetAppParentPathT PATHGetAppParentPathW
#else
#define PATHGetAppParentPathT PATHGetAppParentPathA
#endif

/**
 * @Description: 获取用户配置文件的路径	C:Documents and Settings\用户名\Local Settings\Application Data
 * @param: szPath 用户配置文件路径，必须保证szPath可用长度为  MAX_PATH
 * @return: void 
 * @Author: leeafu	2012-04-15
 */
void PATHGetAppDataPath(TCHAR* szPath);
void PATHGetAppDataPathA(char* szPath);
void PATHGetAppDataPathW(wchar_t* szPath);
#ifdef _UNICODE
#define	PATHGetAppDataPathT PATHGetAppDataPathW
#else
#define PATHGetAppDataPathT PATHGetAppDataPathA
#endif

/**
 * @Description: 获取模块配置文件的路径	配置文件与模块同名称 如：network.dll配置文件为程序目录下的network.ini，和network.dll可能不在同一个目录
 * @param: hModule 模块,	// 此参数已无作用 [2018-11-29 ydl]
 * @param: szFile 配置文件，必须保证文件长度为MAX_PATH
 * @return: void 
 * @Author: leeafu	2012-04-15
 */
void PATHGetDllCfgFile(HANDLE hModule, TCHAR* szFile);
void PATHGetDllCfgFileA(HANDLE hModule, char* szFile);
void PATHGetDllCfgFileW(HANDLE hModule, wchar_t* szFile);
#ifdef _UNICODE
#define	PATHGetDllCfgFileT PATHGetDllCfgFileW
#else
#define PATHGetDllCfgFileT PATHGetDllCfgFileA
#endif

/**
 * @Description: 获取模块配置文件的路径	配置文件与模块同名称 如：network.dll配置文件为程序目录下的network.ini，和network.dll在同一目录下
 * @param: hModule 模块,为空时表示调用程序或库
 * @param: szFile 配置文件，必须保证文件长度为MAX_PATH
 * @return: void 
 * @Author: leeafu	2014-05-28
 */
void PATHGetModuleCfgFile(HMODULE hModule, TCHAR* szFile);
void PATHGetModuleCfgFileA(HMODULE hModule, char* szFile);
void PATHGetModuleCfgFileW(HMODULE hModule, wchar_t* szFile);
#ifdef _UNICODE
#define	PATHGetModuleCfgFileT PATHGetModuleCfgFileW
#else
#define PATHGetModuleCfgFileT PATHGetModuleCfgFileA
#endif

/**
 * @Description: 获取默认路径
 * @param: hModule 模块
 * @param: cDisk 盘符
 * @param: szDefaut 默认路径
 * @param: szPath 返回默认路径，必须保证文件长度为MAX_PATH
 * @return: void 
 * @Author: leeafu	2012-04-15
 */
void PATHGetDefaultPath(TCHAR cDisk, LPCTSTR szDefaut, TCHAR* szPath);

/**
 * @Description: 创建目录，如果目录不存在会循环进行创建
 * @param: szDirectory 目录
 * @return: true表示成功，false表示失败 
 * @Author: leeafu	2012-04-15
 */
bool PATHCreateDirectoryA(LPCSTR szDirectory);
bool PATHCreateDirectoryW(LPCWSTR wszDirectory);
bool PATHCreateDirectory(LPCTSTR szDirectory);
#ifdef _UNICODE
#define	PATHCreateDirectoryT PATHCreateDirectoryW
#else
#define PATHCreateDirectoryT PATHCreateDirectoryA
#endif

/**
 * @Description: 删除目录，如果存在目录，则会循环进行删除操作
 * @param: szDirectory 目录
 * @return: true表示成功，false表示失败  
 * @Author: leeafu	2012-10-03
 */
bool PATHDeleteDirectory(LPCTSTR szDirectory);
bool PATHDeleteDirectoryA(LPCSTR szDirectory);
bool PATHDeleteDirectoryW(LPCWSTR szDirectory);
#ifdef _UNICODE
#define	PATHDeleteDirectoryT PATHDeleteDirectoryW
#else
#define PATHDeleteDirectoryT PATHDeleteDirectoryA
#endif

/**
 * @Description: 创建目录，如果目录不存在会循环进行创建
 * @param: szDest 目标目录，必须以'/'结尾
 * @param: szSrc 源目录，必须以'/'结尾
 * @return: true表示成功，false表示失败 
 * @Author: leeafu	2012-04-15
 */
bool PATHCopyFolder(LPCTSTR szDest, LPCTSTR szSrc);
bool PATHCopyFolderA(LPCSTR szDest, LPCSTR szSrc);
bool PATHCopyFolderW(LPCWSTR szDest, LPCWSTR szSrc);
#ifdef _UNICODE
#define	PATHCopyFolderT PATHCopyFolderW
#else
#define PATHCopyFolderT PATHCopyFolderA
#endif

/**
 * @Description: 判断目录是否存在(判断目录属性),注意:如果参数是文件,也会返回false
 * @param: lpPath 目录, 如  c:\\abcd等效于C:\\abcd\\
 * @return: true表示成功，false表示失败 
 * @Author: leeafu	2016-11-18
 */
BOOL PATHFolderExists(LPCTSTR lpPath);
BOOL PATHFolderExistsA(LPCSTR lpPath);
BOOL PATHFolderExistsW(LPCWSTR lpPath);
#ifdef _UNICODE
#define	PATHFolderExistsT PATHFolderExistsW
#else
#define PATHFolderExistsT PATHFolderExistsA
#endif

/**
 * @Description: 判断路径是否存在(不判断目录属性)
 * @param: lpPath 全路径
 * @param: pIsFolder 当函数返回TRUE时,*pIsFolder=TRUE:说明路径是目录 FALSE:说明路径是文件
 * @return: TRUE表示成功，FALSE表示失败 
 * @Author: ydl	 2018-8-20
 */
BOOL PATHExists(LPCTSTR lpPath, BOOL* pIsFolder = NULL);
BOOL PATHExistsA(LPCSTR lpPath, BOOL* pIsFolder = NULL);
BOOL PATHExistsW(LPCWSTR lpPath, BOOL* pIsFolder = NULL);
#ifdef _UNICODE
#define	PATHExistsT PATHExistsW
#else
#define PATHExistsT PATHExistsA
#endif

/*****************************************************************************
//文件相关函数
******************************************************************************/
/**
 * @Description: 判断文件是否存在(判断非目录属性),注意:如果参数是路径,也会返回false
 * @param: szFile 文件
 * @return: true表示存在，false表示不存在 
 * @Author: leeafu	2012-04-15
 */
bool FILEIsFileExist(LPCTSTR szFile);
bool FILEIsFileExistA(LPCSTR szFile);
bool FILEIsFileExistW(LPCWSTR szFile);
#ifdef _UNICODE
#define	FILEIsFileExistT FILEIsFileExistW
#else
#define FILEIsFileExistT FILEIsFileExistA
#endif

/**
 * @Description: 创建一个新文件
 * @param: szFile 文件
 * @return: true表示成功，false表示失败   
 * @Author: leeafu	2012-04-15
 */
bool FILENewFile(LPCTSTR szFile);

/**
 * @Description: 获取程序版本
 * @param: szVer 版本信息，必须保证szVer可用长度为  MAX_PATH
 * @return: true表示成功，false表示失败  
 * @Author: leeafu	2012-04-15
 */
bool FILEGetAppVersion(TCHAR* szVer);

/**
 * @Description: 获取文件版本
 * @param: szFile 文件信息
 * @param: szVer 版本信息，必须保证szVer可用长度为  MAX_PATH
 * @return: true表示成功，false表示失败  
 * @Author: leeafu	2012-04-15
 */
bool FILEGetFileVersionEx(LPCTSTR szPath, TCHAR* szVer);
bool FILEGetFileVersionExA(LPCSTR szPath, char* szVer);
bool FILEGetFileVersionExW(LPCWSTR szPath, wchar_t* szVer);
#ifdef _UNICODE
#define	FILEGetFileVersionExT FILEGetFileVersionExW
#else
#define FILEGetFileVersionExT FILEGetFileVersionExA
#endif

/**
 * @Description: 快速创建大文件
 * @param: szFile 文件信息
 * @param: nFileSize 文件长度，字节
 * @return: true表示成功，false表示失败  
 * @Author: leeafu	2012-04-15
 */
bool FILEFastCreateFile(LPCTSTR szFile, long nFileSize);
bool FILEFastCreateFileA(LPCSTR szFile, long nFileSize);
bool FILEFastCreateFileW(LPCWSTR szFile, long nFileSize);
#ifdef _UNICODE
#define	FILEFastCreateFileT FILEFastCreateFileW
#else
#define FILEFastCreateFileT FILEFastCreateFileA
#endif

/**
 * @Description: 取得文件最后修改时间
 * @param: szFile 文件
 * @param: lpTime 空间大小，字节
 * @return: true表示成功，false表示失败  
 * @Author: leeafu	2012-04-15
 */
bool FILEGetFileModifyTime(LPCTSTR szFile, LPSYSTEMTIME lpTime);
bool FILEGetFileModifyTimeA(LPCSTR szFile, LPSYSTEMTIME lpTime);
bool FILEGetFileModifyTimeW(LPCWSTR szFile, LPSYSTEMTIME lpTime);
#ifdef _UNICODE
#define	FILEGetFileModifyTimeT FILEGetFileModifyTimeW
#else
#define FILEGetFileModifyTimeT FILEGetFileModifyTimeA
#endif

/**
 * @Description: 获取目录下所有的文件  (注意：以下接口都不支持超过4GB的单个文件)
 * @param: szDir 纯目录，不含通配符
 * @param: lstFile 获取到的文件列表
 * @param: lTotalLength 目录下所有文件的总大小
 * @param: bOvertime 接口获取目录是否超过一定时间(当前是1秒)
 * @return: true表示成功，false表示失败
 * @Author: ydl 2022-09-08 补充说明
 */
void FILEGetPathAllFile(LPCTSTR szDir, lstTtxFileInfoT& lstFile, unsigned __int64& lTotalLength);
void FILEGetPathAllFileA(LPCSTR szDir, lstTtxFileInfo& lstFile, unsigned __int64& lTotalLength);
void FILEGetPathAllFileW(LPCWSTR szDir, lstTtxFileInfoW& lstFile, unsigned __int64& lTotalLength);
void FILEGetPathAllFileEx(LPCTSTR szDir, lstTtxFileInfoT& lstFile, unsigned __int64& lTotalLength, BOOL& bOvertime);
void FILEGetPathAllFileExA(LPCSTR szDir, lstTtxFileInfo& lstFile, unsigned __int64& lTotalLength, BOOL& bOvertime);
void FILEGetPathAllFileExW(LPCWSTR szDir, lstTtxFileInfoW& lstFile, unsigned __int64& lTotalLength, BOOL& bOvertime);

#ifdef _UNICODE
#define	FILEGetPathAllFileT FILEGetPathAllFileW
#define	FILEGetPathAllFileExT FILEGetPathAllFileExW
#else
#define FILEGetPathAllFileT FILEGetPathAllFileA
#define	FILEGetPathAllFileExT FILEGetPathAllFileExA
#endif


//取文件列表，和FILEGetPathAllFile接口功能保持一致
void FILEGetPathFileList(LPCTSTR szDir, lstTtxFileInfoT& lstFile);
void FILEGetPathFileListA(LPCSTR szDir, lstTtxFileInfo& lstFile);
void FILEGetPathFileListW(LPCWSTR szDir, lstTtxFileInfoW& lstFile);
#ifdef _UNICODE
#define	FILEGetPathFileListT FILEGetPathFileListW
#else
#define FILEGetPathFileListT FILEGetPathFileListA
#endif

/**
 * @Description: 检测目录空间，如果超过指定大小，则执行删除文件操作
 * @param: szPath 目录
 * @param: nMaxMBSize 空间大小，字节
 * @return: void
 * @Author: leeafu	2012-04-15
 */
void FILECheckPathFileSize(LPCTSTR szPath, int nMaxMBSize);
void FILECheckPathFileSizeA(LPCSTR szPath, int nMaxMBSize);
void FILECheckPathFileSizeW(LPCWSTR szPath, int nMaxMBSize);
#ifdef _UNICODE
#define	FILECheckPathFileSizeT FILECheckPathFileSizeW
#else
#define FILECheckPathFileSizeT FILECheckPathFileSizeA
#endif

//当小文件比较多时，bRemoveTimeout超出范围时，可以将多余日志全部删除
void FILECheckPathFileSizeEx(LPCTSTR szPath, int nMaxMBSize, BOOL bRemoveTimeout);
void FILECheckPathFileSizeExA(LPCSTR szPath, int nMaxMBSize, BOOL bRemoveTimeout);
void FILECheckPathFileSizeExW(LPCWSTR szPath, int nMaxMBSize, BOOL bRemoveTimeout);
#ifdef _UNICODE
#define	FILECheckPathFileSizeExT FILECheckPathFileSizeExW
#else
#define FILECheckPathFileSizeExT FILECheckPathFileSizeExA
#endif

/**
 * @Description: 判断文件是否存在		注意：非64长度的接口，如果文件超过2GB，会返回LONG_MAX [2023-4-14 ydl]
 * @param: szFile 文件
 * @return: true表示存在，false表示不存在 
 * @Author: leeafu	2014-04-23
 */
long FILEGetFileLengthA(LPCSTR szFile);
long FILEGetFileLengthW(LPCWSTR wszFile);
long FILEGetFileLength(LPCTSTR szFile);
__int64 FILEGetFileLength64A(LPCSTR szFile);
__int64 FILEGetFileLength64W(LPCWSTR wszFile);
#ifdef _UNICODE
#define	FILEGetFileLengthT FILEGetFileLengthW
#define	FILEGetFileLength64 FILEGetFileLength64W
#else
#define FILEGetFileLengthT FILEGetFileLengthA
#define	FILEGetFileLength64 FILEGetFileLength64A
#endif

/**
 * @Description: 判断文件后缀名
 * @param: szFile 文件
 * @param: szExt 后缀名(不加点)
 * @return: true表示存在，false表示不存在 
 * @Author: leeafu	2015-09-27
 */
BOOL FILECheckExtA(LPCSTR szFile, LPCSTR szExt);
BOOL FILECheckExtW(LPCWSTR wszFile, LPCWSTR wszExt);
BOOL FILECheckExt(LPCTSTR szFile, LPCTSTR szExt);
#ifdef _UNICODE
#define	FILECheckExtT FILECheckExtW
#else
#define FILECheckExtT FILECheckExtA
#endif

/**
 * @Description: 获取文件后缀名(不加点)
 * @param: szFile 文件
 * @param: szExt 后缀名缓存区
 * @param: nExtLen 后缀名缓存区长度
 * @return: true表示成功，false表示失败 
 * @Author: leeafu	2015-09-27
 */
BOOL FILEGetExtA(LPCSTR szFile, LPSTR szExt, int nExtLen);
BOOL FILEGetExtW(LPCWSTR szFile, LPWSTR szExt, int nExtLen);
BOOL FILEGetExt(LPCTSTR szFile, LPTSTR szExt, int nExtLen);
#ifdef _UNICODE
#define	FILEGetExtT FILEGetExtW
#else
#define FILEGetExtT FILEGetExtA
#endif

/**
 * @Description: 将缓存数据写入到文件中
 */
BOOL FILESaveBufferToFile(LPCSTR szFile, char* pData, int nDataLen);
BOOL FILESaveBufferToFileW(LPCWSTR szFile, char* pData, int nDataLen);
#ifdef _UNICODE
#define	FILESaveBufferToFileT FILESaveBufferToFileW
#else
#define FILESaveBufferToFileT FILESaveBufferToFile
#endif


/**
 * @Description: 从文件中读取全部数据到缓存中		注意：不支持超过2GB的文件读取 [2023-4-14 ydl]
 */
BOOL FILEReadBufferFromFile(LPCSTR szFile, char** ppData, int& nDataLen);
BOOL FILEReadBufferFromFileW(LPCWSTR szFile, char** ppData, int& nDataLen);
#ifdef _UNICODE
#define	FILEReadBufferFromFileT FILEReadBufferFromFileW
#else
#define FILEReadBufferFromFileT FILEReadBufferFromFile
#endif

//nDataLen返回读取到的长度
BOOL FILEReadFixBufFromFile(LPCSTR szFile, char* pData, int& nDataLen);
BOOL FILEReadFixBufFromFileW(LPCWSTR szFile, char* pData, int& nDataLen);
#ifdef _UNICODE
#define	FILEReadFixBufFromFileT FILEReadFixBufFromFileW
#else
#define FILEReadFixBufFromFileT FILEReadFixBufFromFile
#endif

/**
 * @Description: 根据路径搜索文件,支持通配符(*表示多个字符,?表示单个字符)  FILESearchFileA("D:\\*.exe", ..)表示搜索D盘目录下的exe文件
 * @param: szFind 搜索文件的路径,支持多级通配符,不支持子目录搜索
 * @param: vecFile 搜索到的文件信息
 * @param: bFullPath 是否将结构体中cFileName会扩展为全路径,默认为TRUE(使用全路径),FALSE(使用文件名)
 * @return: TRUE表示成功，FALSE表示失败 
 * @Author: ydl 2018-8-14
 */
BOOL FILESearchFileA(LPCSTR szFind, std::vector<WIN32_FIND_DATAA>& vecFile, BOOL bFullPath = TRUE);
BOOL FILESearchFileW(LPCWSTR szFind, std::vector<WIN32_FIND_DATAW>& vecFile, BOOL bFullPath = TRUE);

#ifdef _UNICODE
#define FILESearchFile	FILESearchFileW
#else
#define FILESearchFile	FILESearchFileA
#endif


/**
 * @Description: 根据路径搜索文件,支持通配符(*表示多个字符,?表示单个字符)  FILESearchFileA("D:\\", "*.exe", ..)表示搜索D盘和所有子目录下的exe文件
 * @param: szPathFind 搜索目录的路径,支持多级通配符,支持子目录搜索
 * @param: szFileFind 搜索文件名称,支持通配符
 * @param: vecFile 搜索到的文件信息
 * @param: bFullPath 是否将结构体中cFileName会扩展为全路径,默认为TRUE(使用全路径),FALSE(使用文件名)
 * @return: TRUE表示成功，FALSE表示失败 
 * @Author: ydl 2018-8-14
 */
BOOL FILESearchFileExA(LPCSTR szPathFind, LPCSTR szFileFind, std::vector<WIN32_FIND_DATAA>& vecFile, BOOL bFullPath = TRUE);
BOOL FILESearchFileExW(LPCWSTR szPathFind, LPCWSTR szFileFind, std::vector<WIN32_FIND_DATAW>& vecFile, BOOL bFullPath = TRUE);

#ifdef _UNICODE
#define FILESearchFileEx	FILESearchFileExW
#else
#define FILESearchFileEx	FILESearchFileExA
#endif


/**
 * @Description: 校验文件名,保证文件名路径是有效的 
 * @param: szFile 应传入文件路径
 * @return: TRUE表示参数有效,未替换，FALSE表示参数无效,有替换字符
 * @Author: ydl 2018-12-3
 字符变换规则:
 特殊字符 \/:*?"<>|,这些符号不能用作文件名或文件路径
 0.忽略前两个字节,如C: \\ 等,暂时只考虑本级路径
 1.连续重复的\或/会被删除,保留第一个
 2.冒号(:)替换为分号(;)
 3.星号(*)替换为加号(+)
 4.问号(?)替换为感叹号(!)
 5.双引号(")替换为单引号(')
 6.尖括号(<>)替换为小括号(())
 7.竖线(|)替换为横线(-)
 */
BOOL FILECheckValidA(LPSTR szFile);
BOOL FILECheckValidW(LPWSTR szFile);

#ifdef _UNICODE
#define FILECheckValid	FILECheckValidW
#else
#define FILECheckValid	FILECheckValidA
#endif


/*****************************************************************************
//进程相关函数
******************************************************************************/
/**
 * @Description: 查找当前进程的映像
 * @return: 成功返回true，失败返回false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSFindProcessSnapshot();

/**
 * @Description: 进程是否正在运行，通过互斥体进行判断
 * @param: szMutexName 互斥体名称
 * @return: 成功返回进程句柄
 * @Author: leeafu	2012-04-15
 */
HANDLE PROCESSIsProcessRunning(LPCTSTR szMutexName);

/**
 * @Description: 通过进程名称进行查找
 * @param: lpAppName 进程名称如，abc.exe
 * @param: dwProcessID 进程号，如果成功，则返回
 * @return: 成功返回true，失败返回false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSFindProcess(LPCTSTR lpAppName, DWORD& dwProcessID);


/**
 * @Description: 通过进程名称进行查找ID（多个进程）
 * @param: szServiceName 服务名
 * @param: ppdwProcessID 进程ID指针 函数内会new[]，使用完成后需要调用delete[]释放
 * @param: nProcessCount 进程ID数量
 * @return: 进程数量大于等于1表示成功，成功返回TRUE，失败返回FALSE
 * @Author: ydl 2022-09-27
 */
BOOL PROCESSFindProcessMulti(LPCTSTR lpAppName, DWORD** ppdwProcessID, int& nProcessCount);

/**
 * @Description: 杀死进程
 * @param: lpAppName 进程名称如，abc.exe
 * @return: 成功返回true，失败返回false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSKillAppProcess(LPCTSTR lpAppName);

/**
 * @Description: 提升进程权限
 * @return: 成功返回true，失败返回false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSEnablePriv();

/**
 * @Description: 杀死进程
 * @param: dwProcessID 进程号
 * @return: 成功返回true，失败返回false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSKillProcess(DWORD dwProcessID);

/**
 * @Description: 创建新进程
 * @param: pszExeName 进程名称
 * @param: pszCommand 进程参数
 * @return: 成功返回true，失败返回false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSCreateNewProcess(LPCTSTR pszExeName, LPTSTR pszCommand);

/**
 * @Description: 重启进程
 * @return: 无
 * @Author: leeafu	2012-04-15
 */
void PROCESSRebootProcess();

/**
 * @Description: 获取进程路径
 * @param: dwProcessID 进程ID
 * @param: szExeFile 进程路径，szExeFile长度必须大于等于MAX_PATH，返回参数
 * @return: 无
 * @Author: leeafu	2012-06-08
 */
void PROCESSGetProcessFile(DWORD dwProcessID, TCHAR* szExeFile);

/**
 * @Description: 获取进程运行时长
 * @param: dwProcessID 进程ID
 * @param: runTime 进程运行时长
 * @return: 成功返回TRUE，失败返回FALSE
 * @Author: leeafu	2012-09-25
 */
BOOL PROCESSGetProcessTimes(DWORD dwProcessID, SYSTEMTIME& runTime);


/**
 * @Description: 根据进程ID获取服务名称
 * @param: dwProcessID 进程ID
 * @param: szServiceName 服务名
 * @param: nLength 服务名长度
 * @return: 成功返回TRUE，失败返回FALSE
 * @Author: zjt	2016-10-08
 */
BOOL QueryServiceNameByThreadID(DWORD dwProcessID, TCHAR* szServiceName, int nLength);

/**
 * @Description: 根据服务名获取进程ID
 * @param: szServiceName 服务名
 * @param: dwProcessID 进程ID
 * @return: 成功返回TRUE，失败返回FALSE
 * @Author: zjt	2016-10-08
 */
BOOL QueryThreadIDByServiceName(LPCTSTR lpServiceName, DWORD& dwProcessID);

/*****************************************************************************
//字符相关函数
******************************************************************************/

/**
 * @Description: 判断字符串是否为数字
 * @param: szStr 字符串
 * @return: 成功返回true，失败返回false
 * @Author: leeafu	2012-04-15
 */
bool STRINGIsDigit(LPCTSTR szStr);
bool STRINGIsDigitA(LPCSTR szStr);
bool STRINGIsDigitW(LPCWSTR szStr);
#ifdef _UNICODE
#define	STRINGIsDigitT STRINGIsDigitW
#else
#define STRINGIsDigitT STRINGIsDigitA
#endif

/**
 * @Description: 生产GUID
 * @param: szGUID GUID字符长度包含/0结束符时为37个字节
 * @Author: leeafu	2012-04-15
 */
void STRINGGenerateGUID(TCHAR* szGUID);
void STRINGGenerateGUIDA(char* szGUID);
void STRINGGenerateGUIDW(wchar_t* szGUID);

#if defined(_UNICODE)
#define STRINGGenerateGUIDT	STRINGGenerateGUIDW
#else
#define STRINGGenerateGUIDT	STRINGGenerateGUIDA
#endif
/**
 * @Description: 字符串分割函数
 * @param: szStr 字符串
 * @param: cSplit 分割符
 * @param: vecStr 返回字符串数组
 * @Author: leeafu	2012-08-03
 */
void STRINGSplit(LPCSTR szStr, char cSplit, std::vector<std::string>& vecStr);
void STRINGSplitW(LPCWSTR szStr, wchar_t cSplit, std::vector<std::wstring>& vecStr);

#if defined(_UNICODE)
#define STRINGSplitT	STRINGSplitW
#else
#define STRINGSplitT	STRINGSplit
#endif

/**
 * @Description: 字符串分割函数(整数型数据)
 * @param: szStr 字符串
 * @param: cSplit 分割符
 * @param: vecValue 返回整数型数组  注意:字符串为空时会忽略  如"1,2,,3," STRINGSplit返回5个元素["1","2","","3",""]  STRINGSplitInt只会返回[1,2,3]3个元素
 * @Author: ydl	2018-5-26
 */
void STRINGSplitIntA(LPCSTR szStr, char cSplit, std::vector<int>& vecValue);
void STRINGSplitIntA(LPCSTR szStr, char cSplit, std::map<int, int>& mapValue);
void STRINGSplitIntW(LPCWSTR szStr, wchar_t cSplit, std::vector<int>& vecValue);
void STRINGSplitIntW(LPCWSTR szStr, wchar_t cSplit, std::map<int, int>& mapValue);

#if defined(_UNICODE)
#define STRINGSplitInt	STRINGSplitIntW
#else
#define STRINGSplitInt	STRINGSplitIntA
#endif

/**
 * @Description: 字符串拼接函数(整数型数据)
 * @param: vecValue/mapValue 数据
 * @param: szJoin 连接字符串,默认为英文逗号
 * @return: 返回拼接的字符串  如{1,2,3} 返回1,2,3
 * @Author: ydl 2022-1-14
 */
std::string STRINGJoinIntA(const std::vector<int>& vecValue, const char* szJoin = NULL);
std::string STRINGJoinIntA(const std::map<int, int>& mapValue, const char* szJoin = NULL);
std::wstring STRINGJoinIntW(const std::vector<int>& vecValue, const wchar_t* szJoin = NULL);
std::wstring STRINGJoinIntW(const std::map<int, int>& mapValue, const wchar_t* szJoin = NULL);


#if defined(_UNICODE)
#define STRINGJoinInt	STRINGJoinIntW
#else
#define STRINGJoinInt	STRINGJoinIntA
#endif

/**
 * @Description: 字符串拼接函数(整数型数据) 保证结果尽可能短
 * @param: mapValue 数据,必须从小到大排序
 * @param: szJoin 连接字符串,默认为英文逗号
 * @return: 返回拼接的字符串  如[-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,-10,-8,-7,-6,-5,-4,-3,-2,-1,0,2,3,4,5,6,7,8,9,10,11] 返回 "-20--10,-8-0,2-11"
 * @Author: ydl	2022-1-14
 */
std::string STRINGJoinIntShortA(const std::map<int, int>& mapValue, const char* szJoin = NULL);
std::wstring STRINGJoinIntShortW(const std::map<int, int>& mapValue, const wchar_t* szJoin = NULL);


#if defined(_UNICODE)
#define STRINGJoinIntShort	STRINGJoinIntShortW
#else
#define STRINGJoinIntShort	STRINGJoinIntShortA
#endif

/**
 * @Description: 字符串分割函数(整数型数据)
 * @param: szStr STRINGJoinIntShortA相关接口返回的字符串
 * @param: cSplit 分割符
 * @param: vecValue 返回整数型数组
			"-20--10,-8-0,2-11" 解析后为 [-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,-10,-8,-7,-6,-5,-4,-3,-2,-1,0,2,3,4,5,6,7,8,9,10,11]
 * @Author: ydl 2022-1-14
 */
void STRINGShortSplitIntA(LPCSTR szStr, char cSplit, std::vector<int>& vecValue);
void STRINGShortSplitIntA(LPCSTR szStr, char cSplit, std::map<int, int>& mapValue);
void STRINGShortSplitIntW(LPCWSTR szStr, wchar_t cSplit, std::vector<int>& vecValue);
void STRINGShortSplitIntW(LPCWSTR szStr, wchar_t cSplit, std::map<int, int>& mapValue);

#if defined(_UNICODE)
#define STRINGShortSplitInt	STRINGShortSplitIntW
#else
#define STRINGShortSplitInt	STRINGShortSplitIntA
#endif

/**
 * @Description: 字符串分割函数，直接使用c函数，不构造对象，提升效率
 * @Author: leeafu	2016-01-16
 */
void STRINGSplitArray(LPCSTR szStr, char cSplit, STRINGMyArray_S* pArray, int nNum);
void STRINGSplitArrayW(LPCWSTR wszStr, wchar_t wSplit, STRINGMyArrayW_S* pArray, int nNum);

#if defined(_UNICODE)
#define STRINGSplitArrayT	STRINGSplitArrayW
#else
#define STRINGSplitArrayT	STRINGSplitArray
#endif

/**
 * @Description: 字符替换函数（替换单个字符
 * @param: szStr 字符串
 * @param: cOld 要替换的字符
 * @param: cNew 替换后的字符
 * @Author: leeafu	2012-09-21
 */
void STRINGReplaceChar(LPTSTR szStr, TCHAR cOld, TCHAR cNew);
void STRINGReplaceCharA(LPSTR szStr, char cOld, char cNew);
void STRINGReplaceCharW(LPWSTR szStr, wchar_t cOld, wchar_t cNew);

#if defined(_UNICODE)
#define STRINGReplaceCharT	STRINGReplaceCharW
#else
#define STRINGReplaceCharT	STRINGReplaceCharA
#endif
/**
 * @Description: 字符替换函数(替换字符串)
 * @param: szStr 字符串
 * @param: szOld 要替换的字符串
 * @param: szNew 替换后的字符串
 * @Author: ydl  2018-04-27

 特例一: szOld和szNew都是单字符的字符串,如"1","?",调用std::replace替换
 特例二: szOld为单字符,szNew为空字符串(不能为NULL),调用std::remove删除
 */
void STRINGReplaceStringA(std::string& str, LPCSTR szOld, LPCSTR szNew);
void STRINGReplaceStringW(std::wstring& str, LPCWSTR szOld, LPCWSTR szNew);
/**
 * @Description: 字符替换函数(替换字符串)
 * @param: szStr 常量字符串
 * @param: szOld 要替换的字符串
 * @param: szNew 替换后的字符串
 * @return: 替换之后的字符串
 * @Author: ydl  2018-04-27
 */
std::string STRINGReplaceStringRetA(LPCSTR str, LPCSTR szOld, LPCSTR szNew);
std::wstring STRINGReplaceStringRetW(LPCWSTR str, LPCWSTR szOld, LPCWSTR szNew);

#if defined(_UNICODE)
#define STRINGReplaceStringT	STRINGReplaceStringW
#define STRINGReplaceStringRetT	STRINGReplaceStringRetW
#else
#define STRINGReplaceStringT	STRINGReplaceStringA
#define STRINGReplaceStringRetT	STRINGReplaceStringRetA
#endif
// @Author: leeafu	2016-03-24
//字符数组转换成16进制的字符串
//上层需要释放返回的数据  SAFE_DELETE_ARRAY(ppStrHex), SAFE_DELETE_ARRAY(ppData)
void STRINGCharArr2Hex(const unsigned char* pData, int nDataLen, char** ppStrHex);
//16进制字符串转换成数组
void STRINGHex2CharArr(const std::string& strHex, unsigned char** ppData, int& nDataLen);

/**
 * @Description: 字符数组转换成字符串,初始数据为pHead
 * @param: pData 字符数组
 * @param: nLen 字符个数
 * @param: pHead 初始数据
 * @param: pSeparator 间隔符号
 * @Author: ydl  2018-0705
 */
// 示例:STRINGCharArr2HexExA("123", 3, "Data=", " ") 返回Data=31 32 33
std::string STRINGCharArr2HexExA(const void* pData, int nLen, const char* pHead = NULL, const char* pSeparator = NULL);
std::wstring STRINGCharArr2HexExW(const void* pData, int nLen, const wchar_t* pHead = NULL, const wchar_t* pSeparator = NULL);

#if defined(_UNICODE)
#define STRINGCharArr2HexEx	STRINGCharArr2HexExW
#else
#define STRINGCharArr2HexEx	STRINGCharArr2HexExA
#endif

/**
 * @Description: 字符替换函数(替换字符串)
 * @param: pData 常量字符串,注意:只处理偶数字节的数据
 * @param: nLen 字符串长度,为0时自动计算
 * @return: 格式化的字符串,如313233,返回123
 * @Author: ydl  2018-04-27
 */
std::string STRINGHexStr2CharArrA(const char* pData, int nLen = 0);

template <class T>
T STRINGHexStdStr2CharArrA(const T& str)
{
	return STRINGHexStr2CharArrA(str.data(), (int)str.size());
}

/**
 * @Description: 'FA' = 15*16 + 10  16进行转换成char
 * @param: pBuf 字符串
 * @Author: leeafu	2013-06-11
 */
unsigned char STRINGHex2Char(char* pBuf);

/**
 * @Description: 将字符串转换成大写
 * @param: szStr ，源字符串，输出为大写
 * @return: 无
 * @Author: leeafu	2014-09-06
 */
void STRINGToUpperA(LPSTR szStr);
void STRINGToUpperW(LPWSTR wszStr);
void STRINGToUpper(LPTSTR tszStr);
void STRINGStdToUpperA(std::string& str);
void STRINGStdToUpperW(std::wstring& str);
#ifdef _UNICODE
#define	STRINGToUpperT STRINGToUpperW
#define STRINGStdToUpper STRINGStdToUpperW
#else
#define STRINGToUpperT STRINGToUpperA
#define STRINGStdToUpper STRINGStdToUpperA
#endif


/**
 * @Description: 将字符串转换成小写
 * @param: szStr ，源字符串，输出为小写
 * @return: 无
 * @Author: leeafu	2014-09-06
 */
void STRINGToLowerA(LPSTR szStr);
void STRINGToLowerW(LPWSTR wszStr);
void STRINGToLower(LPTSTR tszStr);
void STRINGStdToLowerA(std::string& str);
void STRINGStdToLowerW(std::wstring& str);
#ifdef _UNICODE
#define	STRINGToLowerT STRINGToLowerW
#define STRINGStdToLower STRINGStdToLowerW
#else
#define STRINGToLowerT STRINGToLowerA
#define STRINGStdToLower STRINGStdToLowerA
#endif

/**
 * @Description: 将指针类型格式化为字符串
 * @param: pVoid 指针值
 * @return: 32位按%d格式化 64位按%lld格式化 Hex:32位下=%X 64位=%llX
 * @Author: ydl 2018-5-25
 */
std::string STRINGFormatPointerA(void* pVoid);
std::wstring STRINGFormatPointerW(void* pVoid);
std::string STRINGFormatPointerHexA(void* pVoid);
std::wstring STRINGFormatPointerHexW(void* pVoid);

#if defined(_UNICODE)
#define STRINGFormatPointer	STRINGFormatPointerW
#define STRINGFormatPointerHex	STRINGFormatPointerHexW
#else
#define STRINGFormatPointer	STRINGFormatPointerA
#define STRINGFormatPointerHex	STRINGFormatPointerHexA
#endif


/**
 * @Description: 将多段内存的字符串组合为一个,如STRINGMergeMulti(2, "123", -1, "456", -1)=123456
 * @param: nCount,字符串个数
 * @param: ...,多个字符串,应包含成对的参数(字符串指针和长度)
 * @return: 组合之后的字符串
 * @Author: ydl 2018-6-14
 */

std::string STRINGMergeMulti(int nCount, ...);

std::string STRINGMerge2(const char *szBuf1, int nBufLen1, const char *szBuf2, int nBufLen2);
// 模板STRINGMerge2
template <int nBufLen1, int nBufLen2>
std::string STRINGMerge2(const char (&szBuf1)[nBufLen1], const char (&szBuf2)[nBufLen2])
{
	return STRINGMergeMulti(2, szBuf1, nBufLen1, szBuf2, nBufLen2);
}

std::string STRINGMerge3(const char *szBuf1, int nBufLen1, const char *szBuf2, int nBufLen2, const char *szBuf3, int nBufLen3);
// 模板STRINGMerge3
template <int nBufLen1, int nBufLen2, int nBufLen3>
std::string STRINGMerge2(const char (&szBuf1)[nBufLen1], const char (&szBuf2)[nBufLen2], const char (&szBuf3)[nBufLen3])
{
	return STRINGMergeMulti(3, szBuf1, nBufLen1, szBuf2, nBufLen2, szBuf3, nBufLen3);
}

/**
 * @Description: 将一个字符串划分到多段内存,如STRINGDivideMulti("123456", 2, buf1, 3, buf2, 3) buf1=12 buf2=34 返回值=56
 * @param: szData,字符串
 * @param: nCount,字符串缓存个数
 * @param: ...,多个字符串,应包含成对的参数(字符串指针和长度),注意:BufLen传入实际大小,拷贝时会减一
 * @return: 未保存的字符串,返回0表示所有数据都成功存储
 * @Author: ydl 2018-6-14
 */
std::string STRINGDivideMulti(const char* szData, int nCount, ...);

// 模板STRINGDivide1
template <int nBufLen>
std::string STRINGDivide1(const char* szData, char(&szBuf)[nBufLen])
{
	return STRINGDivideMulti(szData, 1, szBuf, nBufLen);
}

std::string STRINGDivide2(const char* szData, char *szBuf1, int nBufLen1, char *szBuf2, int nBufLen2);
// 模板STRINGDivide2
template <int nBufLen1, int nBufLen2>
std::string STRINGDivide2(const char* szData, char (&szBuf1)[nBufLen1], char (&szBuf2)[nBufLen2])
{
	return STRINGDivide2(szData, szBuf1, nBufLen1, szBuf2, nBufLen2);
}

std::string STRINGDivide3(const char* szData, char *szBuf1, int nBufLen1, char *szBuf2, int nBufLen2, char *szBuf3, int nBufLen3);
// 模板STRINGDivide3
template <int nBufLen1, int nBufLen2, int nBufLen3>
std::string STRINGDivide3(const char* szData, char (&szBuf1)[nBufLen1], char (&szBuf2)[nBufLen2], char (&szBuf3)[nBufLen3])
{
	return STRINGDivide3(szData, szBuf1, nBufLen1, szBuf2, nBufLen2, szBuf3, nBufLen3);
}


/*****************************************************************************
//时间相关函数
******************************************************************************/
/**
 * @Description: 判断时间是否已经过了指定的时间
 * @param: dwTime 之前的时间
 * @param: dwTimeout 超时的时间，毫秒
 * @return: 成功返回true，失败返回false
 * @Author: leeafu	2012-04-15
 */
bool TIMEIsTimeOut(DWORD& dwTime, DWORD dwMinSecond);

/**
 * @Description: 判断时间是否已经过了指定的时间
 * @param: dwTime 之前的时间
 * @param: dwTimeout 超时的时间，毫秒
 * @return: 成功返回true，失败返回false
 * @Author: leeafu	2012-04-15
 */
bool TIMEIsTimeOutEx(DWORD& dwBeginTime, DWORD dwEndTime, DWORD dwMinSecond);

#ifdef WINBASEAPI
template <class T>
bool TIMEIsTimeOutSleep(DWORD& dwTime, DWORD dwMinSecond, T nSleepSocond)
{
	DWORD dwNow = GetTickCount();
	if (TIMEIsTimeOutEx(dwTime, dwNow, dwMinSecond))
	{
		Sleep(nSleepSocond);
		dwTime = GetTickCount();
		return true;
	}
	return false;
}
#endif

/**
 * @Description: 取得当前时间戳
 * @return: 成功返回时间戳
 * @Author: leeafu	2012-04-15
 */
time_t TIMEGetCurrentTimestamp();	//秒时间戳
time_t TIMEGetCurrentTimestampMS();	//毫秒时间戳

/**
 * @Description: 取得当前时间字符串
 * @return: 成功返回字符串
 * @Author: leeafu	2012-04-15
 */
CStringSTL TIMEGetCurrentTimeString();
std::string TIMEGetCurrentTimeStringA();
std::wstring TIMEGetCurrentTimeStringW();
#ifdef _UNICODE
#define	TIMEGetCurrentTimeStringT TIMEGetCurrentTimeStringW
#else
#define TIMEGetCurrentTimeStringT TIMEGetCurrentTimeStringA
#endif

/**
 * @Description: 格式化时间字体串，2011-04-12 23:34:34
 * @param: Time 时间信息
 * @return: 成功返回字符串
 * @Author: leeafu	2012-04-15
 */
CStringSTL TIMEFormatTime2String(const SYSTEMTIME& Time);
std::string TIMEFormatTime2StringA(const SYSTEMTIME& Time);
std::wstring TIMEFormatTime2StringW(const SYSTEMTIME& Time);

#ifdef _UNICODE
#define	TIMEFormatTime2StringT TIMEFormatTime2StringW
#else
#define TIMEFormatTime2StringT TIMEFormatTime2StringA
#endif

/**
 * @Description: 格式化成日期格式，2012-04-12
 * @param: Time 时间信息
 * @return: 成功返回字符串
 * @Author: leeafu	2012-04-15
 */
CStringSTL TIMEFormatTime2DateString(const SYSTEMTIME& Time);
std::string TIMEFormatTime2DateStringA(const SYSTEMTIME& Time);
std::wstring TIMEFormatTime2DateStringW(const SYSTEMTIME& Time);
#ifdef _UNICODE
#define	TIMEFormatTime2DateStringT TIMEFormatTime2DateStringW
#else
#define TIMEFormatTime2DateStringT TIMEFormatTime2DateStringA
#endif

/**
 * @Description: 将日期字符串转为时间结构体   
					默认接口只保证年月日有效,Full接口会保证返回的参数全部有效
 * @param: szTime 时间字符串，支持格式:1."2018-01-01"  2."2018-01-01 00:00:00"，'-'和':'可以替换为任何非数字的内容
 * @param: Time 时间信息,成功解析的数据存储到此结构体
 * @return: 成功返回true
 * @Author: ydl	2018-10-30
 */
bool TIMEString2TimeA(LPCSTR szTime, SYSTEMTIME& Time);
bool TIMEString2TimeW(LPCWSTR szTime, SYSTEMTIME& Time);
bool TIMEString2TimeFullA(LPCSTR szTime, SYSTEMTIME& Time);
bool TIMEString2TimeFullW(LPCWSTR szTime, SYSTEMTIME& Time);

#ifdef _UNICODE
#define TIMEString2Time		TIMEString2TimeW
#define TIMEString2TimeFull	TIMEString2TimeFullW
#else
#define TIMEString2Time		TIMEString2TimeA
#define TIMEString2TimeFull	TIMEString2TimeFullA
#endif



/**
 * @Description: 时间比较
 * @return: 如果tm1 > tm2 返回1， = 返回0，< 返回-1
 * @Author: leeafu	2012-04-15
 */
int	TIMECompareTime(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);


/**
 * @Description: 时间快速比较,不校验时间是否有效,依次判断年月日时分秒
 * @return: 如果tm1 > tm2 返回1， = 返回0，< 返回-1
 * @Author: ydl 2020-8-13
 */
int	TIMEQuickCompareTime(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);


/**
 * @Description: 计算日期的周数
 * @param: 待计算的日期  每年的1号,如果不是周一,第1周截止到第1个周一,第1个周一算作第2周
 * @return: 周数
 * @Author: ydl 2020-8-13
 */
int	TIMEGetWeekly(const SYSTEMTIME& tmDate);
int	TIMEGetWeekly(int nYear, int nMonth, int nDay);


/**
 * @Description: 将年+周转换为时间
 * @param: nYear 年份
 * @param: nWeekly 周数
 * @param: stDate 返回日期,周数开始,不跨年时是周一,跨年第一周是1月1号
 * @param: nDayOfWeek 指定优先按此星期返回日期,默认为-1(周一 > 周日) 1-6(周一到周六) 0(周日)
					注意:第一周可能只有周日,最后一周可能只有周一,获取其他值会导致失败
 * @return: 成功返回TRUE
 * @Author: ydl 2020-8-13
 */
BOOL	TIMEYearWeeklyTime(int nYear, int nWeekly, SYSTEMTIME& stDate, int nDayOfWeek = -1);



/**
 * @Description: 获取上一周的范围
 * @param: stTime 按指定日期获取上一周  注意:此参数的wDayOfWeek必须为有效值
 * @param: nYear 日期的年份
 * @param: nWeekly 周数,从1开始
 * @param: tmBeg 周数开始,不跨年时是周一,跨年第一周是1月1号
 * @param: tmEnd 周数结束,不跨年时是周日,跨年最后一周是12月31号
 * @return: 成功返回TRUE
 * @Author: ydl 2020-8-13
 */
BOOL	TIMEGetLastWeeklyRange(SYSTEMTIME stTime, SYSTEMTIME& tmBeg, SYSTEMTIME& tmEnd);
BOOL	TIMEGetLastWeeklyRange(int nYear, int nWeekly, SYSTEMTIME& tmBeg, SYSTEMTIME& tmEnd);


/**
 * @Description: 获取一周的范围
 * @param: stTime 日期  注意:此参数的wDayOfWeek必须为有效值
 * @param: nYear 日期的年份
 * @param: nWeekly 周数,从1开始
 * @param: tmBeg 周数开始,不跨年时是周一,跨年第一周是1月1号
 * @param: tmEnd 周数结束,不跨年时是周日,跨年最后一周是12月31号
 * @return: 成功返回TRUE
 * @Author: ydl 2020-8-13
 */
BOOL	TIMEGetWeeklyRange(SYSTEMTIME stTime, SYSTEMTIME& tmBeg, SYSTEMTIME& tmEnd);
BOOL	TIMEGetWeeklyRange(int nYear, int nWeekly, SYSTEMTIME& tmBeg, SYSTEMTIME& tmEnd);

/**
 * @Description: 将日期转换成long秒方式，以1900开始
 * @param: tm 时间
 * @return: 时间秒
 * @Author: leeafu	2012-04-15 hw 2014/1/17 1970-->1900 开始
 */
long TIMEFormatTime2Long(const SYSTEMTIME& tm);
long long TIMEFormatTime2LongLong(const SYSTEMTIME& tm);


/**
 * @Description: 将时间的年月日转为时间戳（毫秒）
 * @param: tm 日期  会忽略时分秒
 * @return: 时间戳 单位毫秒
 * @Author: ydl 2022-11-24
 */
long long TIMEFormatDateTimeMS(SYSTEMTIME tm);
long long TIMEFormatDateTimeMS(int nYear, int nMonth, int nDay);


/**
 * @Description: 将时间转为时间戳（毫秒）
 * @param: tm 日期
 * @return: 时间戳 单位毫秒
 * @Author: ydl 2022-11-24
 */
long long TIMEFormatTimeMS(const SYSTEMTIME& tm);

/**
 * @Description: 时间增删操作
 * @param: tm 时间
 * @param: nSecond 秒，如果秒数为负数，则为减少
 * @return: 新时间
 * @Author: leeafu	2012-04-15
 */
SYSTEMTIME TIMEIncrease(const SYSTEMTIME& tm, int nSecond);

/**
 * @Description: 时间增删操作  默认接口只保证年月日有效,Ex接口会保证返回的参数全部有效
 * @param: tm 时间
 * @param: nYear 年，如果为负数，则为减少
 * @param: nMonth 月，如果为负数，则为减少
 * @param: nDay 日，如果为负数，则为减少
 * @return: 新时间
 * @Author: ydl	2018-5-18
 * 注意:当月份天数不一致时,跨月可能导致时间不完全一致,加减一个月后,日期可能不会跟原始的一致
     如:3-30向前定位1个月,返回2-28(闰年返回2-29),再向后定位1个月,返回3-28(闰年29)
	 如果日期需要操作后能正确还原,必须使用天数操作
 */
SYSTEMTIME TIMEIncreaseYMD(const SYSTEMTIME& tm, int nYear, int nMonth, int nDay = 0);
SYSTEMTIME TIMEIncreaseYMDEx(const SYSTEMTIME& tm, int nYear, int nMonth, int nDay = 0);
SYSTEMTIME TIMEIncreaseD(const SYSTEMTIME& tm, int nDay);
SYSTEMTIME TIMEIncreaseDEx(const SYSTEMTIME& tm, int nDay);

/**
 * @Description: 判断两个时间差，返回秒数
 * @return: 两个时间差，秒数
 * @Author: leeafu	2012-09-13
 */
int TIMECompare(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);
__int64 TIMECompare64(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);

/**
 * @Description: time_t转换成SYSTEMTIME
 * @return: SYSTEMTIME
 * @Author: hw	2013-09-14
 */
SYSTEMTIME TIMETimeToSystemTime(time_t t);

/**
 * @Description: SYSTEMTIME转换成time_t
 * @return: time_t
 * @Author: hw	2013-09-14
 */
time_t TIMESystemTime2Time(const SYSTEMTIME& st);

/*
* @Description: 取得两个时间段之间有月份信息		注意：如果输入无效时间（年或月为0），不会解析月份
*				2023-03-09 增加判断时间参数的大小，开始时间取较小值，结束时间取较大值
*/
void	TIMESplitMonth(const SYSTEMTIME& beg, const SYSTEMTIME& end, std::vector<TIMEMonth_S>& lstMonth);

/*****************************************************************************
//操作系统相关函数
******************************************************************************/
//判断OS的版本
BOOL	OSCheckOsVersion(DWORD nMajorVer, DWORD nMinVer);
//判断是否为XP系统
BOOL	OSIsWinXP();

/*****************************************************************************
//缓存操作相关函数
******************************************************************************/
//追加缓存，如果缓存不够，则会新增
BOOL	BUFFAppend(const char* pAddBuf, int nAddLen, char** ppDestBuffer, int& nDestBufLen, int& nDestDataLen, int nNewLength = 50 * 1024);
//分配缓存，返回成功分配的长度，失败返回0
//分配前，会先释放*ppBuffer，确保 *ppBuffer启动时，要初始化为NULL
int		BUFFAlloc(char** ppBuffer, int nBufLen);


/*****************************************************************************
//压缩解压内存数据
******************************************************************************/
/**
* @Description: 压缩内存数据(XZip)
* @param: pSrcBuffer 原始缓存数据
* @param: nSrcLen	原始缓存数据长度
* @param: szFlag   标签(压缩和解压对应)
* @param: ppDestBuf  压缩或者解压后的缓存数据 外部释放
* @param: nDestLen  压缩或者解压后的缓存数据长度
* @return: 成功返回TRUE， 失败返回FALSE	
* @Author: zjt	2018-07-25
 */
BOOL CompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, LPCTSTR szFlag, char **ppDestBuf, unsigned int& uiDestLen);
BOOL UnCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, LPCTSTR szFlag, char **ppDestBuf, unsigned int& uiDestLen);

/**
* @Description: 压缩或解压内存数据,并使用对象存储(XZip)
* @param: pSrcBuffer 原始缓存数据
* @param: nSrcLen	原始缓存数据长度
* @param: szFlag   标签(压缩和解压对应)
* @param: vecBuf  压缩或者解压后的缓存数据,会在原有数据之后增加新数据
* @return: 成功返回TRUE， 失败返回FALSE	
* @Author: ydl	2018-08-03
 */

BOOL CompressBufferToObj(const char* pSrcBuffer, unsigned int uiSrcLen, LPCTSTR szFlag, std::vector<char>& vecBuf);
BOOL UnCompressBufferToObj(const char* pSrcBuffer, unsigned int uiSrcLen, LPCTSTR szFlag, std::vector<char>& vecBuf);

/**
* @Description: 压缩内存数据(GZIP),使用此接口需要包含头文件libzlib.h
* @param: pSrcBuffer 原始缓存数据
* @param: nSrcLen	原始缓存数据长度
* @param: strDest  压缩或者解压后的缓存数据
* @return: 成功返回TRUE， 失败返回FALSE
* @Author: ydl 2019-7-19
 */
BOOL ZlibCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, std::string& strDest);
BOOL ZlibUnCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, std::string& strDest);

/**
* @Description: 采用压缩文件方式(GZIP),使用此接口需要包含头文件libzlib.h
* @param: pSrcBuffer 原始缓存数据
* @param: nSrcLen	原始缓存数据长度
* @param: strDest  压缩或者解压后的缓存数据
* @return: 成功返回TRUE， 失败返回FALSE
* @Author: ydl 2019-7-19
 */
BOOL GZlibCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, std::string& strDest, int level = -1);
BOOL GZlibUnCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, std::string& strDest);


/*****************************************************************************
//通用相关函数
******************************************************************************/


#endif /*	_PUBLIC_H_	*/