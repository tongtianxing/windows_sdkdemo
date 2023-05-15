#pragma once

// 日志功能,使用静态库模式 [2021-6-23 ydl]
#ifndef LOG_USE_STATIC_LINK


#include <tchar.h>	

#ifdef LIBLOGFILE_EXPORTS
#define LOGFILE_API __declspec(dllexport)
#else
#define LOGFILE_API __declspec(dllimport)
#endif

#define LOG_WRITE	

#define LOG_LEVEL_LOWEST	0
#define LOG_LEVEL_NORMAL	1
#define LOG_LEVEL_HIGHEST	2	

// #define LOG_DEFAULT_MBSIZE	5
// #define LOG_MIN_MBSIZE		5
// #define LOG_MAX_MBSIZE		(1024 * 40)
const int LOG_MAX_LEN = 10240;
// 
// #define LOG_ONE_FILE_MIN_MB	1
// #define LOG_ONE_FILE_MAX_MB	100

#define LogIns()	LogIns2<CLogFile2>()
#define DELLog()	DELLog2<CLogFile2>()

#ifdef LOG_WRITE
#define LOG_TRACE		(LogIns()->WriteStrInfoEx)
#define LOG_TRACEA		(LogIns()->WriteStrInfoEx)
#define LOG_TRACEW		(LogIns()->WriteStrInfoEx)
#define LOG_HEX			(LogIns()->WriteHex)
#define LOG_HEXA		(LogIns()->WriteHex)
#define LOG_HEXW		(LogIns()->WriteHex)
// 极少数情况下使用,用于输出超长的文本 [2022-4-15 ydl]
#define LOG_TRACE_LONG	(LogIns()->WriteLongStr)
#define LOG_TRACEA_LONG	(LogIns()->WriteLongStr)
#define LOG_TRACEW_LONG	(LogIns()->WriteLongStr)

// 日志打印时,附加当前函数在前面
#define LOG_TRACE_FUNC(level, fmt, ...)		do \
{ \
	LOG_TRACE(level, _T("%s ") fmt, __FUNCTIONT__, __VA_ARGS__); \
} while (0);

#define LOG_HEX_FUNC(level, buf, buflen, fmt, ...)		do \
{ \
	LOG_HEX(level, buf, buflen, _T("%s ") fmt, __FUNCTIONT__, __VA_ARGS__); \
} while (0);


#define LOG_TRACEA_FUNC(level, fmt, ...)		do \
{ \
	LOG_TRACEA(level, "%s " fmt, __FUNCTION__, __VA_ARGS__); \
} while (0);

#define LOG_HEXA_FUNC(level, buf, buflen, fmt, ...)		do \
{ \
	LOG_HEXA(level, buf, buflen, "%s " fmt, __FUNCTION__, __VA_ARGS__); \
} while (0);

#define LOG_TRACEA_FUNC_DEBUG(level, fmt, ...)		do \
{ \
	LOG_TRACEA(level, "%s " fmt, __FUNCTION__, __VA_ARGS__); \
	DEBUGTraceConsoleA("%s " fmt, __FUNCTION__, __VA_ARGS__); \
} while (0);



#else
#define LOG_TRACE
#define LOG_HEX	
#endif

#if defined(_DEBUG)
#define LOG_TRACE_DEBUG	LOG_TRACE
#define LOG_HEX_DEBUG	LOG_HEX
#else
#define LOG_TRACE_DEBUG	__noop
#define LOG_HEX_DEBUG	__noop
#endif


/*
增加使用多个配置文件,当优先级高的配置文件存在时,会读取高优先级的
1.{程序路径}\LOG.ini						所有程序可用,优先级最低
2.{程序路径}\LOG(主程序名,不含后缀).ini		此程序和所加载的插件用,优先级大于1
3.{程序路径}\LOG(主程序名+插件名,都不含后缀).ini  此程序和指定插件用,优先级大于2(程序无此配置)
4.{插件路径}\LOG(插件名,含后缀).ini			插件私有,优先级大于3

举例客户端cmsv6.exe+libmap.dll
对libmapu.dll优先级为 LOG(libmap.dll).ini > LOG(cmsv6+libmap).ini > LOG(cmsv6).ini > LOG.ini
对cmsv6.exe优先级为 LOG(cmsv6.exe).ini > LOG(cmsv6).ini > LOG.ini

[LOG]
LEVEL=0
;范围：0-2，值越小，写日志越多
SIZE=100
;单位：MB，范围：5-10240
FILESIZE=1
;单个日志文件占用大小，单位：MB，范围：1-10
*/

#ifdef _PUBLIC_FUNCTION_H_
// 根据耗时,返回不同的日志级别
// 参数传0,表示默认级别
template<class T>
int Tick2LogLevel(T dwStart, DWORD dwLogHighest = 1500, DWORD dwLogNormal = 500)
{
	if (dwLogHighest == 0 || TIMEIsTimeOut(dwStart, dwLogHighest))
	{
		return LOG_LEVEL_HIGHEST;
	}

	if (dwLogNormal == 0 || TIMEIsTimeOut(dwStart, dwLogNormal))
	{
		return LOG_LEVEL_NORMAL;
	}

	return LOG_LEVEL_LOWEST;
}
#endif

namespace _nsLog
{
	class CLogFile;
}

class LOGFILE_API CLogFile2
{
public:
	//template <class _LogTy> _LogTy*	LogIns2(int nMode = 0);		//0: 查(不增) 1:查(增) 2:删 
	template <class _LogTy>
	friend _LogTy*	LogIns2(bool bCreate);
	template <class _LogTy>
	friend void		DELLog2();

private:
	CLogFile2(HMODULE hModule);
	CLogFile2(const CLogFile2&);
	~CLogFile2();

	CLogFile2& operator = (const CLogFile2&);

public:
	void	ReadConfig();
	//void	WriteHex(int nLevel, const char* pBuffer, int nLength, LPCTSTR szInfo, ...);
	void	WriteHex(int nLevel, const char* pBuffer, int nLength, LPCSTR szInfo, ...);
	void	WriteHex(int nLevel, const char* pBuffer, int nLength, LPCWSTR szInfo, ...);
	// 新接口,用于长文本输出,szText直接拼接在格式化文本后面,nTextLen等于-1时,表示需要计算 [2022-4-15 ydl]
	void	WriteLongStr(int nLevel, LPCSTR szText, int nTextLen, LPCSTR szInfo, ...);
	void	WriteLongStr(int nLevel, LPCWSTR szText, int nTextLen, LPCWSTR szInfo, ...);
	//void	WriteStrInfo(int nLevel, LPCTSTR lpszInfo);
	//void	WriteStrInfoEx(int nLevel, LPCTSTR szInfo, ...);
	void	WriteStrInfoEx(int nLevel, LPCSTR szInfo, ...);
	void	WriteStrInfoEx(int nLevel, LPCWSTR szInfo, ...);
	void	SetLogName(LPCSTR szLogname);
	void	SetLogName(LPCWSTR szLogname);
	//const TCHAR*	GetLogPathA();
	//const TCHAR*	GetLogPathW();
	void	GetLogPath(LPSTR szPath);
	void	GetLogPath(LPWSTR szPath);
	int		GetLogMBSize();
	void	SetLogParam(LPCSTR szDir, LPCSTR szLogname, BOOL bDeleteFile = TRUE);
	void	SetLogParam(LPCWSTR szDir, LPCWSTR szLogname, BOOL bDeleteFile = TRUE);

	// 关闭当前日志文件
	BOOL	Close();


	// 清理日志磁盘
	void	LogFILECheckPathFileSizeEx(BOOL bRemoveTimeout);

	// 按日期存储日志
	BOOL	IsLogDate() const;
private:
	_nsLog::CLogFile* m_pLog;
};

template <class _LogTy>
_LogTy*	LogIns2(bool bCreate = true)		//int nMode = 0; //0: 查(不增) 1:查(增) 2:删 
{
	static HMODULE s_hModule = NULL;
	if (s_hModule == NULL)
	{
		if (!bCreate)
		{
			return nullptr;
		}
		::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, _T(""), &s_hModule);
	}
	static _LogTy s_Log(s_hModule);
	return &s_Log;
}

template <class _LogTy>
void		DELLog2()
{
	_LogTy* pLog = LogIns2<_LogTy>(false);
	if (pLog)
	{
		pLog->Close();
	}
}

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN64
	// 日志工作线程(目前只有x64版本才有效)
	// 启用标志
	// bit0: 是否启用zip压缩
	// bit1: 是否启用809插件的zip压缩(支持多个)
	// bit2: 是否启用libmdvrnet插件的zip压缩(只有一个路径)
	LOGFILE_API void LOGFILE_Start(int nEnableFlag);
	LOGFILE_API void LOGFILE_Stop();

	// 启用或关闭bit1
	LOGFILE_API void LOGFILE_SetEnable809Zip();
	LOGFILE_API void LOGFILE_Add809LogPath(CLogFile2* pLog);

	// 启用或关闭bit2
	LOGFILE_API void LOGFILE_SetEnableMdvrZip();
	LOGFILE_API void LOGFILE_AddMdvrLogPath(CLogFile2* pLog);
#endif

	// 计时器,打印时间到控制台,DEBUGTraceOutput 格式="%s: %d ms",打印后删除
	LOGFILE_API void LOGFILE_TimeBeginA(LPCSTR lpszTimer);
	LOGFILE_API void LOGFILE_TimeBeginW(LPCWSTR lpszTimer);
	LOGFILE_API void LOGFILE_TimeEndA(LPCSTR lpszTimer);
	LOGFILE_API void LOGFILE_TimeEndW(LPCWSTR lpszTimer);
	// 在TimeEnd基础上修改,打印后不删除,会重置时间戳为当前,可以重复调用获取每段的时间
	LOGFILE_API void LOGFILE_TimeEndExA(LPCSTR lpszTimer);
	LOGFILE_API void LOGFILE_TimeEndExW(LPCWSTR lpszTimer);
	// 计时器,打印时间到日志,默认日志级别为LOG_LEVEL_NORMAL 格式="%s: %d ms",打印后删除
	LOGFILE_API void LOGFILE_TimeEndToLogA(CLogFile2* pLog, LPCSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);
	LOGFILE_API void LOGFILE_TimeEndToLogW(CLogFile2* pLog, LPCWSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);
	// 在TimeEnd基础上修改,打印后不删除,会重置时间戳为当前,可以重复调用获取每段的时间
	LOGFILE_API void LOGFILE_TimeEndToLogExA(CLogFile2* pLog, LPCSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);
	LOGFILE_API void LOGFILE_TimeEndToLogExW(CLogFile2* pLog, LPCWSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);

#ifdef _UNICODE
#define LOGFILE_TimeBegin		LOGFILE_TimeBeginW
#define LOGFILE_TimeEnd			LOGFILE_TimeEndW
#define LOGFILE_TimeEndEx		LOGFILE_TimeEndExW
#define LOGFILE_TimeEndToLog	LOGFILE_TimeEndToLogW
#define LOGFILE_TimeEndToLogEx	LOGFILE_TimeEndToLogExW
#else
#define LOGFILE_TimeBegin		LOGFILE_TimeBeginA
#define LOGFILE_TimeEnd			LOGFILE_TimeEndA
#define LOGFILE_TimeEndEx		LOGFILE_TimeEndExA
#define LOGFILE_TimeEndToLog	LOGFILE_TimeEndToLogA
#define LOGFILE_TimeEndToLogEx	LOGFILE_TimeEndToLogExA
#endif


#define TimeBegin				LOGFILE_TimeBegin
#define TimeEnd					LOGFILE_TimeEnd
#define TimeEndEx				LOGFILE_TimeEndEx
#define LogTimeBegin			LOGFILE_TimeBegin
#define LogTimeEnd(...)			LOGFILE_TimeEndToLog(LogIns(), __VA_ARGS__)
#define LogTimeEndEx(...)		LOGFILE_TimeEndToLogEx(LogIns(), __VA_ARGS__)
	// 仅debug模式打印的宏定义
#ifdef _DEBUG
#define LOG_TIMEBEGIN_DEBUG		LogTimeBegin
#define LOG_TIMEEND_DEBUG		LogTimeEnd
#else
#define LOG_TIMEBEGIN_DEBUG		__noop
#define LOG_TIMEEND_DEBUG		__noop
#endif // _DEBUG

#ifdef __cplusplus
}
#endif

#endif