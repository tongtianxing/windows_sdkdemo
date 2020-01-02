#ifndef _PUBLIC_FUNCTION_H_
#define _PUBLIC_FUNCTION_H_

#include <crtdbg.h>

#ifndef ASSERT
	#ifdef _DEBUG
	#define ASSERT(expr)	\
					do {    \
					if (!(expr) && \
					(1 == _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr))) \
					__asm { int 3 }; \
					} while (0)
	#else
	#define ASSERT(expr)
	#endif
#endif

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
#define put8(p, dat) ( (p)[0] = (u8)((dat)>>0)&0xff )
#define putle16(p, dat) ( (p)[0] = ((u16)(dat)>>0)&0xff, (p)[1] = ((u16)(dat)>>8)&0xff )
#define putle24(p, dat) ( (p)[0] = (u8)((u32)(dat)>>0)&0xff, (p)[1] = (u8)((u32)(dat)>>8)&0xff, (p)[2] = (u8)((u32)(dat)>>16)&0xff )
#define putle32(p, dat) ( (p)[0] = (u8)((u32)(dat)>>0)&0xff, (p)[1] = (u8)((u32)(dat)>>8)&0xff, (p)[2] = (u8)((u32)(dat)>>16)&0xff, (p)[3] = (u8)((u32)(dat)>>24)&0xff )
#define putbe16(p, dat) ( (p)[0] = ((u16)(dat)>>8)&0xff, (p)[1] = ((u16)(dat)>>0)&0xff )
#define putbe24(p, dat) ( (p)[0] = (u8)((u32)(dat)>>16)&0xff, (p)[1] = (u8)((u32)(dat)>>8)&0xff, (p)[2] = (u8)((u32)(dat)>>0)&0xff )
#define putbe32(p, dat) ( (p)[0] = (u8)((u32)(dat)>>24)&0xff, (p)[1] = (u8)((u32)(dat)>>16)&0xff, (p)[2] = (u8)((u32)(dat)>>8)&0xff, (p)[3] = (u8)((u32)(dat)>>0)&0xff )
	
#define get8(p) ( (p)[0] )
#define getle16(p) ( ((u8)(p)[0] << 0) | ((u8)(p)[1] << 8) )
#define getle24(p) ( ((u8)(p)[0] << 0) | ((u8)(p)[1] << 8) | ((u8)(p)[2] << 16) )
#define getle32(p) ( ((u8)(p)[0] << 0) | ((u8)(p)[1] << 8) | ((u8)(p)[2] << 16) | ((u8)(p)[3] << 24) )
#define getbe16(p) ( ((u8)(p)[0] << 8) | ((u8)(p)[1] << 0) )
#define getbe24(p) ( ((u8)(p)[0] << 16) | ((u8)(p)[1] << 8) | ((u8)(p)[2] << 0) )
#define getbe32(p) ( ((u8)(p)[0] << 24) | ((u8)(p)[1] << 16) | ((u8)(p)[2] << 8) | ((u8)(p)[3] << 0) )

#include "StringSTL.h"
#include <vector>

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

/**
 * @Description: 输出日志到 Studio的Output窗口
 * @param: fmt
 * @return: void 
 * @Author: leeafu	2012-04-15
 */
void DEBUGTraceOutput(LPCTSTR fmt, ...);

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

/*
 * 打印16进制
*/
void DEBUGTraceHexConsole(const char* pBuffer, int nLength);

/*****************************************************************************
//路径相关函数
******************************************************************************/

/**
 * @Description: 获取程序名称
 * @return: const char* 程序名称
 * @Author: leeafu	2013-04-25
 */
LPCTSTR	PATHGetAppName();

/**
 * @Description: 获取程序路径
 * @return: const char* 程序路径 
 * @Author: leeafu	2012-04-15
 */
LPCTSTR	PATHGetAppPath();

/**
 * @Description: 获取程序路径
 * @param: hModule 模块句柄，为空值表示所在程序
 * @return: szPath 模块目录，必须保证长度为MAX_PATH
 * @Author: leeafu	2013-08-19
 */
void PATHGetModulePath(HMODULE hModule, TCHAR* szPath);

/**
 * @Description: 获取程序父目录路径
 * @return: const char* 程序父目录路径  
 * @Author: leeafu	2012-04-15
 */
LPCTSTR	PATHGetAppParentPath();

/**
 * @Description: 获取用户配置文件的路径	C:Documents and Settings\用户名\Local Settings\Application Data
 * @param: szPath 用户配置文件路径，必须保证szPath可用长度为  MAX_PATH
 * @return: void 
 * @Author: leeafu	2012-04-15
 */
void PATHGetAppDataPath(TCHAR* szPath);

/**
 * @Description: 获取模块配置文件的路径	配置文件与模块同名称 如：network.dll配置文件为程序目录下的network.ini，和network.dll可能不在同一个目录
 * @param: hModule 模块
 * @param: szFile 配置文件，必须保证文件长度为MAX_PATH
 * @return: void 
 * @Author: leeafu	2012-04-15
 */
void PATHGetDllCfgFile(HANDLE hModule, TCHAR* szFile);

/**
 * @Description: 获取模块配置文件的路径	配置文件与模块同名称 如：network.dll配置文件为程序目录下的network.ini，和network.dll在同一目录下
 * @param: hModule 模块
 * @param: szFile 配置文件，必须保证文件长度为MAX_PATH
 * @return: void 
 * @Author: leeafu	2014-05-28
 */
void PATHGetModuleCfgFile(HMODULE hModule, TCHAR* szFile);

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
bool PATHCreateDirectory(LPCTSTR szDirectory);

/**
 * @Description: 创建目录，如果目录不存在会循环进行创建
 * @param: szDirectory 目录
 * @return: true表示成功，false表示失败 
 * @Author: leeafu	2012-04-15
 */
bool PATHCreateDirectoryW(wchar_t* tszDirectory);

/**
 * @Description: 删除目录，如果存在目录，则会循环进行删除操作
 * @param: szDirectory 目录
 * @return: true表示成功，false表示失败  
 * @Author: leeafu	2012-10-03
 */
bool PATHDeleteDirectory(LPCTSTR szDirectory);

/**
 * @Description: 创建目录，如果目录不存在会循环进行创建
 * @param: szDest 目标目录，必须以'/'结尾
 * @param: szSrc 源目录，必须以'/'结尾
 * @return: true表示成功，false表示失败 
 * @Author: leeafu	2012-04-15
 */
bool PATHCopyFolder(LPCTSTR szDest, LPCTSTR szSrc);

/**
 * @Description: 判断目录是否存在
 * @param: lpPath 目录, 如  c:\\abcd
 * @return: true表示成功，false表示失败 
 * @Author: leeafu	2016-11-18
 */
BOOL PATHFolderExists(LPCTSTR lpPath);

/*****************************************************************************
//文件相关函数
******************************************************************************/
/**
 * @Description: 判断文件是否存在
 * @param: szFile 文件
 * @return: true表示存在，false表示不存在 
 * @Author: leeafu	2012-04-15
 */
bool FILEIsFileExist(LPCTSTR szFile);

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

/**
 * @Description: 快速创建大文件
 * @param: szFile 文件信息
 * @param: nFileSize 文件长度，字节
 * @return: true表示成功，false表示失败  
 * @Author: leeafu	2012-04-15
 */
bool FILEFastCreateFile(LPCTSTR szFile, long nFileSize);

/**
 * @Description: 取得文件最后修改时间
 * @param: szFile 文件
 * @param: lpTime 空间大小，字节
 * @return: true表示成功，false表示失败  
 * @Author: leeafu	2012-04-15
 */
bool FILEGetFileModifyTime(LPCTSTR szFile, LPSYSTEMTIME lpTime);

/**
 * @Description: 检测目录空间，如果超过指定大小，则执行删除文件操作
 * @param: szPath 目录
 * @param: nMaxMBSize 空间大小，字节
 * @return: void
 * @Author: leeafu	2012-04-15
 */
void FILECheckPathFileSize(LPCTSTR szPath, int nMaxMBSize);

//当小文件比较多时，bRemoveTimeout超出范围时，可以将多余日志全部删除
void FILECheckPathFileSizeEx(LPCTSTR szPath, int nMaxMBSize, BOOL bRemoveTimeout);

/**
 * @Description: 判断文件是否存在
 * @param: szFile 文件
 * @return: true表示存在，false表示不存在 
 * @Author: leeafu	2014-04-23
 */
long FILEGetFileLength(LPCTSTR szFile);

long FILEGetFileLengthW(wchar_t* wszFile);

/**
 * @Description: 判断文件后缀名
 * @param: szFile 文件
 * @param: szExt 后缀名
 * @return: true表示存在，false表示不存在 
 * @Author: leeafu	2015-09-27
 */
BOOL FILECheckExt(LPCTSTR szFile, LPCTSTR szExt);

/**
 * @Description: 将缓存数据写入到文件中
 */
BOOL FILESaveBufferToFile(const char* szFile, char* pData, int nDataLen);

/**
 * @Description: 从文件中读取全部数据到缓存中
 */
BOOL FILEReadBufferFromFile(const char* szFile, char** ppData, int& nDataLen);

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
void PROCESSGetProcessFile(DWORD dwProcessID, char* szExeFile);

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

/**
 * @Description: 生产GUID
 * @param: szGUID GUID字符长度包含/0结束符时为37个字节
 * @Author: leeafu	2012-04-15
 */
void STRINGGenerateGUID(TCHAR* szGUID);

/**
 * @Description: 字符串分割函数
 * @param: szStr 字符串
 * @param: cSplit 分割符
 * @param: vecStr 返回字符串数组
 * @Author: leeafu	2012-08-03
 */
void STRINGSplit(const char* szStr, char cSplit, std::vector<std::string>& vecStr);

void STRINGSplitW(const wchar_t* szStr, wchar_t cSplit, std::vector<std::wstring>& vecStr);

/**
 * @Description: 字符串分割函数，直接使用c函数，不构造对象，提升效率
 * @Author: leeafu	2016-01-16
 */
void STRINGSplitArray(const char* szStr, char cSplit, STRINGMyArray_S* pArray, int nNum);
void STRINGSplitArrayW(const wchar_t* wszStr, wchar_t wSplit, STRINGMyArrayW_S* pArray, int nNum);

/**
 * @Description: 字符替换函数（替换单个字符
 * @param: szStr 字符串
 * @param: cOld 要替换的字符
 * @param: cNew 替换后的字符
 * @Author: leeafu	2012-09-21
 */
void STRINGReplaceChar(TCHAR* szStr, TCHAR cOld, TCHAR cNew);

// @Author: leeafu	2016-03-24
//字符数组转换成16进制的字符串
//上层需要释放返回的数据  SAFE_DELETE_ARRAY(ppStrHex), SAFE_DELETE_ARRAY(ppData)
void STRINGCharArr2Hex(const unsigned char* pData, int nDataLen, char** ppStrHex);
//16进制字符串转换成数组
void STRINGHex2CharArr(const std::string& strHex, unsigned char** ppData, int& nDataLen);

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
void STRINGToUpper(char* szStr);

/**
 * @Description: 将字符串转换成小写
 * @param: szStr ，源字符串，输出为小写
 * @return: 无
 * @Author: leeafu	2014-09-06
 */
void STRINGToLower(char* szStr);

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

/**
 * @Description: 取得当前时间字符串
 * @return: 成功返回字符串
 * @Author: leeafu	2012-04-15
 */
CStringSTL TIMEGetCurrentTimeString();

/**
 * @Description: 格式化时间字体串，2011-04-12 23:34:34
 * @param: Time 时间信息
 * @return: 成功返回字符串
 * @Author: leeafu	2012-04-15
 */
CStringSTL TIMEFormatTime2String(const SYSTEMTIME& Time);

/**
 * @Description: 格式化成日期格式，2012-04-12
 * @param: Time 时间信息
 * @return: 成功返回字符串
 * @Author: leeafu	2012-04-15
 */
CStringSTL TIMEFormatTime2DateString(const SYSTEMTIME& Time);

/**
 * @Description: 时间比较
 * @return: 如果tm1 > tm2 返回1， = 返回0，< 返回-1
 * @Author: leeafu	2012-04-15
 */
int	TIMECompareTime(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);

/**
 * @Description: 将日期转换成long秒方式，以1900开始
 * @param: tm 时间
 * @return: 时间秒
 * @Author: leeafu	2012-04-15 hw 2014/1/17 1970-->1900 开始
 */
long TIMEFormatTime2Long(const SYSTEMTIME& tm);

/**
 * @Description: 时间增删操作
 * @param: tm 时间
 * @param: nSecond 秒，如果秒数为负责，则为减少
 * @return: 时间秒
 * @Author: leeafu	2012-04-15
 */
SYSTEMTIME TIMEIncrease(const SYSTEMTIME& tm, int nSecond);

/**
 * @Description: 判断两个时间差，返回秒数
 * @return: 两个时间差，秒数
 * @Author: leeafu	2012-09-13
 */
int TIMECompare(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);

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
* @Description: 取得两个时间段之间有月份信息
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
//通用相关函数
******************************************************************************/

#endif /*	_PUBLIC_H_	*/