#pragma once

// ��־����,ʹ�þ�̬��ģʽ [2021-6-23 ydl]
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
// �����������ʹ��,��������������ı� [2022-4-15 ydl]
#define LOG_TRACE_LONG	(LogIns()->WriteLongStr)
#define LOG_TRACEA_LONG	(LogIns()->WriteLongStr)
#define LOG_TRACEW_LONG	(LogIns()->WriteLongStr)

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


/*
����ʹ�ö�������ļ�,�����ȼ��ߵ������ļ�����ʱ,���ȡ�����ȼ���
1.{����·��}\LOG.ini						���г������,���ȼ����
2.{����·��}\LOG(��������,������׺).ini		�˳���������صĲ����,���ȼ�����1
3.{����·��}\LOG(��������+�����,��������׺).ini  �˳����ָ�������,���ȼ�����2(�����޴�����)
4.{���·��}\LOG(�����,����׺).ini			���˽��,���ȼ�����3

�����ͻ���cmsv6.exe+libmap.dll
��libmapu.dll���ȼ�Ϊ LOG(libmap.dll).ini > LOG(cmsv6+libmap).ini > LOG(cmsv6).ini > LOG.ini
��cmsv6.exe���ȼ�Ϊ LOG(cmsv6.exe).ini > LOG(cmsv6).ini > LOG.ini

[LOG]
LEVEL=0
;��Χ��0-2��ֵԽС��д��־Խ��
SIZE=100
;��λ��MB����Χ��5-10240
FILESIZE=1
;������־�ļ�ռ�ô�С����λ��MB����Χ��1-10
*/

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

namespace _nsLog
{
	class CLogFile;
}

class LOGFILE_API CLogFile2
{
public:
	//template <class _LogTy> _LogTy*	LogIns2(int nMode = 0);		//0: ��(����) 1:��(��) 2:ɾ 
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
	// �½ӿ�,���ڳ��ı����,szTextֱ��ƴ���ڸ�ʽ���ı�����,nTextLen����-1ʱ,��ʾ��Ҫ���� [2022-4-15 ydl]
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

	// �رյ�ǰ��־�ļ�
	BOOL	Close();


	// ������־����
	void	LogFILECheckPathFileSizeEx(BOOL bRemoveTimeout);

	// �����ڴ洢��־
	BOOL	IsLogDate() const;
private:
	_nsLog::CLogFile* m_pLog;
};

template <class _LogTy>
_LogTy*	LogIns2(bool bCreate = true)		//int nMode = 0; //0: ��(����) 1:��(��) 2:ɾ 
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
	// ��־�����߳�(Ŀǰֻ��x64�汾����Ч)
	// ���ñ�־
	// bit0: �Ƿ�����zipѹ��
	// bit1: �Ƿ�����809�����zipѹ��(֧�ֶ��)
	// bit2: �Ƿ�����libmdvrnet�����zipѹ��(ֻ��һ��·��)
	LOGFILE_API void LOGFILE_Start(int nEnableFlag);
	LOGFILE_API void LOGFILE_Stop();

	// ���û�ر�bit1
	LOGFILE_API void LOGFILE_SetEnable809Zip();
	LOGFILE_API void LOGFILE_Add809LogPath(CLogFile2* pLog);

	// ���û�ر�bit2
	LOGFILE_API void LOGFILE_SetEnableMdvrZip();
	LOGFILE_API void LOGFILE_AddMdvrLogPath(CLogFile2* pLog);
#endif

	// ��ʱ��,��ӡʱ�䵽����̨,DEBUGTraceOutput ��ʽ="%s: %d ms",��ӡ��ɾ��
	LOGFILE_API void LOGFILE_TimeBeginA(LPCSTR lpszTimer);
	LOGFILE_API void LOGFILE_TimeBeginW(LPCWSTR lpszTimer);
	LOGFILE_API void LOGFILE_TimeEndA(LPCSTR lpszTimer);
	LOGFILE_API void LOGFILE_TimeEndW(LPCWSTR lpszTimer);
	// ��TimeEnd�������޸�,��ӡ��ɾ��,������ʱ���Ϊ��ǰ,�����ظ����û�ȡÿ�ε�ʱ��
	LOGFILE_API void LOGFILE_TimeEndExA(LPCSTR lpszTimer);
	LOGFILE_API void LOGFILE_TimeEndExW(LPCWSTR lpszTimer);
	// ��ʱ��,��ӡʱ�䵽��־,Ĭ����־����ΪLOG_LEVEL_NORMAL ��ʽ="%s: %d ms",��ӡ��ɾ��
	LOGFILE_API void LOGFILE_TimeEndToLogA(CLogFile2* pLog, LPCSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);
	LOGFILE_API void LOGFILE_TimeEndToLogW(CLogFile2* pLog, LPCWSTR lpszTimer, int nLevel = LOG_LEVEL_NORMAL);
	// ��TimeEnd�������޸�,��ӡ��ɾ��,������ʱ���Ϊ��ǰ,�����ظ����û�ȡÿ�ε�ʱ��
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
	// ��debugģʽ��ӡ�ĺ궨��
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