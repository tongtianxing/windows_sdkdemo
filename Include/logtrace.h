#ifndef __LOGFILE_H_
#define __LOGFILE_H_

#if defined(LOG_USE_STATIC_LINK)

#include "StaticObject.h"

/******************************************************************************
  Version       : 1.0
  Author        : leeafu
  Created       : 2012/04/15
  Last Modified :
  Description   : ͨ����־ģ��
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

// ��־��ӡʱ,���ӵ�ǰ������ǰ��
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

// ��ʱ��,��ӡʱ�䵽����̨,DEBUGTraceOutput ��ʽ="%s: %d ms",��ӡ��ɾ��
void TimeBegin(LPCTSTR lpszTimer);
void TimeEnd(LPCTSTR lpszTimer);
// ��TimeEnd�������޸�,��ӡ��ɾ��,������ʱ���Ϊ��ǰ,�����ظ����û�ȡÿ�ε�ʱ��
void TimeEndEx(LPCTSTR lpszTimer);
// ��ʱ��,��ӡʱ�䵽��־,Ĭ����־����ΪLOG_LEVEL_NORMAL ��ʽ="%s: %d ms",��ӡ��ɾ��
void TimeEndToLog(LPCTSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);
// ��TimeEnd�������޸�,��ӡ��ɾ��,������ʱ���Ϊ��ǰ,�����ظ����û�ȡÿ�ε�ʱ��
void TimeEndToLogEx(LPCTSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);

#define LogTimeBegin			TimeBegin
#define LogTimeEnd				TimeEndToLog
#define LogTimeEndEx			TimeEndToLogEx
// ��debugģʽ��ӡ�ĺ궨��
#ifdef _DEBUG
#define LOG_TIMEBEGIN_DEBUG		LogTimeBegin
#define LOG_TIMEEND_DEBUG		LogTimeEnd
#else
#define LOG_TIMEBEGIN_DEBUG		__noop
#define LOG_TIMEEND_DEBUG		__noop
#endif // _DEBUG

/*
����ʹ�ö�������ļ�,�����ȼ��ߵ������ļ�����ʱ,���ȡ�����ȼ���
1.{����·��}\LOG.ini						���г������,���ȼ����
2.{����·��}\LOG(��������,������׺).ini		�˳���������صĲ����,���ȼ�����1
3.{���·��}\LOG(�����,����׺).ini			���˽��,���ȼ�����2

�����ͻ���cmsv6.exe+libmapu.dll
��libmapu.dll���ȼ�Ϊ LOG(libmapu.dll).ini > LOG(cmsv6).ini > LOG.ini
��cmsv6.exe���ȼ�Ϊ LOG(cmsv6.exe).ini > LOG(cmsv6).ini > LOG.ini

[LOG]
LEVEL=0
;��Χ��0-2��ֵԽС��д��־Խ��
SIZE=100
;��λ��MB����Χ��5-1024
*/

// ��Ҫ���� #include <PublicApi.h>
#ifdef _PUBLIC_FUNCTION_H_
// ���ݺ�ʱ,���ز�ͬ����־����
// ������0,��ʾĬ�ϼ���
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


//˽�м̳�,�ݲ��ֶ�����GetInstance
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
	TCHAR		m_szFileName[MAX_PATH];	//��־�ļ���
	SYSTEMTIME	m_tmFileBegin;
	SYSTEMTIME	m_tmFileEnd;
	DWORD		m_dwFilePos;	//��־�ļ�ָ��λ��
	HANDLE		m_hFile;		//��־�ļ����
	CRITICAL_SECTION	m_csFile;	//��־�����
	TCHAR		m_szLogName[MAX_PATH];
	char		m_szLogData[LOG_MAX_LEN];
	TCHAR		m_szLogVa[LOG_MAX_LEN];
	char		m_szLogWrite[LOG_MAX_LEN];
	DWORD		m_dwReadLogFlagTime;
	BOOL		m_bDeleteFile;
	int			m_nLogFileSize;	//�����ļ���,��Χ1-10
	BOOL		m_bIsDll;	//�Ƿ�Ϊ���,TRUE��ʾdll,FALSE��ʾexe/ocx

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

	// ���д�뼶���Ƿ���Ҫд��,����TRUE��ʾд��
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

	// ������־����
	void	LogFILECheckPathFileSizeEx(BOOL bRemoveTimeout);

	// �����ڴ洢��־
	BOOL	IsLogDate() const;
};

CLogTrace*	LogIns();
void		DELLog();

#else

#include "logfileapi.h"

#endif
#endif