#ifndef __LOGFILE_H_
#define __LOGFILE_H_

#if defined(LOG_USE_STATIC_LINK)

#include "StaticObject.h"

/******************************************************************************
  Version       : 1.0
  Author        : leeafu
  Created       : 2012/04/15
  Last Modified :
  Description   : 通用日志模块
  Function List :
  History       :
	  1.Date        : 2012/04/15
		Author      : leeafu
		Modification: Created file

******************************************************************************/



#define LOG_WRITE	

#define LOG_LEVEL_LOWEST	0
#define LOG_LEVEL_NORMAL	1
#define LOG_LEVEL_HIGHEST	2	

#define LOG_DEFAULT_MBSIZE	5
#define LOG_MIN_MBSIZE		5
#define LOG_MAX_MBSIZE		10240
const int LOG_MAX_LEN = 10240;

#define LOG_ONE_FILE_MIN_MB	1
#define LOG_ONE_FILE_MAX_MB	10

#ifdef LOG_WRITE
#define LOG_TRACE		(LogIns()->WriteStrInfoEx)
#define LOG_TRACEA		(LogIns()->WriteStrInfoExA)
#define LOG_TRACEW		(LogIns()->WriteStrInfoExW)
#define LOG_HEX			(LogIns()->WriteHex)
#define LOG_HEXA		(LogIns()->WriteHexA)
#define LOG_HEXW		(LogIns()->WriteHexW)
#define LOG_TRACE_LONG(level, text, textlen, fmt, ...)	LOG_TRACE(level, fmt _T("%s"), __VA_ARGS__, text)
#define LOG_TRACEA_LONG(level, text, textlen, fmt, ...)	LOG_TRACEA(level, fmt "%s", __VA_ARGS__, text)
#define LOG_TRACEW_LONG(level, text, textlen, fmt, ...)	LOG_TRACEW(level, fmt L"%s", __VA_ARGS__, text)

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

// 计时器,打印时间到控制台,DEBUGTraceOutput 格式="%s: %d ms",打印后删除
void TimeBegin(LPCTSTR lpszTimer);
void TimeEnd(LPCTSTR lpszTimer);
// 在TimeEnd基础上修改,打印后不删除,会重置时间戳为当前,可以重复调用获取每段的时间
void TimeEndEx(LPCTSTR lpszTimer);
// 计时器,打印时间到日志,默认日志级别为LOG_LEVEL_NORMAL 格式="%s: %d ms",打印后删除
void TimeEndToLog(LPCTSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);
// 在TimeEnd基础上修改,打印后不删除,会重置时间戳为当前,可以重复调用获取每段的时间
void TimeEndToLogEx(LPCTSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);

#define LogTimeBegin			TimeBegin
#define LogTimeEnd				TimeEndToLog
#define LogTimeEndEx			TimeEndToLogEx
// 仅debug模式打印的宏定义
#ifdef _DEBUG
#define LOG_TIMEBEGIN_DEBUG		LogTimeBegin
#define LOG_TIMEEND_DEBUG		LogTimeEnd
#else
#define LOG_TIMEBEGIN_DEBUG		__noop
#define LOG_TIMEEND_DEBUG		__noop
#endif // _DEBUG

/*
增加使用多个配置文件,当优先级高的配置文件存在时,会读取高优先级的
1.{程序路径}\LOG.ini						所有程序可用,优先级最低
2.{程序路径}\LOG(主程序名,不含后缀).ini		此程序和所加载的插件用,优先级大于1
3.{插件路径}\LOG(插件名,含后缀).ini			插件私有,优先级大于2

举例客户端cmsv6.exe+libmapu.dll
对libmapu.dll优先级为 LOG(libmapu.dll).ini > LOG(cmsv6).ini > LOG.ini
对cmsv6.exe优先级为 LOG(cmsv6.exe).ini > LOG(cmsv6).ini > LOG.ini

[LOG]
LEVEL=0
;范围：0-2，值越小，写日志越多
SIZE=100
;单位：MB，范围：5-1024
*/

// 需要包含 #include <PublicApi.h>
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


//私有继承,暂不手动调用GetInstance
class CLogTrace : private CStaticObject<CLogTrace>
{
public:
	friend CLogTrace*	LogIns();
	friend void		DELLog();

private:
	TCHAR		m_szLogConfig[MAX_PATH];
	int			m_nLogMBSize;
	int			m_nLogLevel;
	TCHAR		m_szLogPath[MAX_PATH];
	TCHAR		m_szFileName[MAX_PATH];	//日志文件名
	SYSTEMTIME	m_tmFileBegin;
	SYSTEMTIME	m_tmFileEnd;
	DWORD		m_dwFilePos;	//日志文件指针位置
	HANDLE		m_hFile;		//日志文件句柄
	CRITICAL_SECTION	m_csFile;	//日志监界区
	TCHAR		m_szLogName[MAX_PATH];
	char		m_szLogData[LOG_MAX_LEN];
	TCHAR		m_szLogVa[LOG_MAX_LEN];
	char		m_szLogWrite[LOG_MAX_LEN];
	DWORD		m_dwReadLogFlagTime;
	BOOL		m_bDeleteFile;
	int			m_nLogFileSize;	//单个文件的,范围1-10
	BOOL		m_bIsDll;	//是否为插件,TRUE表示dll,FALSE表示exe/ocx

private:
	CLogTrace();
	CLogTrace(const CLogTrace& );
	~CLogTrace();
	friend CStaticObject<CLogTrace>;
	
	CLogTrace& operator = (const CLogTrace&);
	
protected:
	void	SetLogLevel(int nLevel) {	m_nLogLevel = nLevel; }
	void	SetLogSize(int nMBSize) 
	{
		m_nLogMBSize = nMBSize;		
		if (m_nLogMBSize <= LOG_MIN_MBSIZE || m_nLogMBSize > LOG_MAX_MBSIZE)
		{
			m_nLogMBSize = LOG_DEFAULT_MBSIZE;
		}
	}
	void	SetLogFileSize(int nLogOneMaxSize)
	{
		m_nLogFileSize = nLogOneMaxSize;
		if (m_nLogFileSize <= LOG_ONE_FILE_MIN_MB || m_nLogFileSize > LOG_ONE_FILE_MAX_MB)
		{
			m_nLogFileSize = LOG_ONE_FILE_MIN_MB;
		}
	}
	BOOL	Close();
	BOOL	Open();
	void	WriteLog(LPCTSTR lpszLog);
	void	WriteLogA(LPCSTR lpszLog);
	void	WriteLogW(LPCWSTR lpszLog);
	void	GetLogFileName();

	// 检查写入级别是否需要写入,返回TRUE表示写入
	BOOL	CheckLogLevel(int nLevel);

public:
	void	ReadConfig();
	void	WriteHex(int nLevel, const char* pBuffer, int nLength, LPCTSTR szInfo, ...);
	void	WriteHexA(int nLevel, const char* pBuffer, int nLength, LPCSTR szInfo, ...);
	void	WriteHexW(int nLevel, const char* pBuffer, int nLength, LPCWSTR szInfo, ...);
	void	WriteStrInfo(int nLevel, LPCTSTR lpszInfo);
	void	WriteStrInfoEx(int nLevel, LPCTSTR szInfo, ...);
	void	WriteStrInfoExA(int nLevel, LPCSTR szInfo, ...);
	void	WriteStrInfoExW(int nLevel, LPCWSTR szInfo, ...);
	void	SetLogName(const TCHAR* szLogname);
	//const TCHAR*	GetLogPath() { return m_szLogPath; }
	void	GetLogPath(LPSTR szPath);
	void	GetLogPath(LPWSTR szPath);
	int		GetLogMBSize() {	return m_nLogMBSize;	}
	void	SetLogParam(const TCHAR* szDir, const TCHAR* szLogname, BOOL bDeleteFile = TRUE);

	// 清理日志磁盘
	void	LogFILECheckPathFileSizeEx(BOOL bRemoveTimeout);

	// 按日期存储日志
	BOOL	IsLogDate() const;
};

CLogTrace*	LogIns();
void		DELLog();

#else

#include "logfileapi.h"

#endif
#endif