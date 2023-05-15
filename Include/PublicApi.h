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
// 	static const size_t   bucket_size = 4;   // �²���������ǳ�ʼ��hash_map�Ĵ�С  
// 	static const size_t   min_buckets = 8; 
// 
// 	//BKDR hash algorithm���й��ַ���hash����������ȥ�������Ͽ���
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
//������غ���
******************************************************************************/

/**
 * @Description: ���ַ�����ʽ����16���Ƶ���ʽ
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
 * @Description: �����־�� Studio��Output����
 * @param: fmt
 * @return: void 
 * @Author: leeafu	2012-04-15
  DEBUGTraceOutput ������Ȼ�����char[512]��wchar_t[512]
  DEBUGTraceOutputLong �ȼ����ʽ���ַ�������,���֧��char[65536]��wchar_t[32768]
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

// Ĭ��ʹ��Long�ӿڴ�ӡ [2022-2-18 ydl]
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
 * ��ӡ16����
*/
void DEBUGTraceHexOutput(const char* pBuffer, int nLength);

/**
 * @Description: �����־������̨����
 * @param: fmt
 * @return: void 
 * @Author: leeafu	2012-04-15
 */
void DEBUGTraceConsole(LPCTSTR fmt, ...);
void DEBUGTraceConsoleA(LPCSTR fmt, ...);
void DEBUGTraceConsoleW(LPCWSTR fmt, ...);

/*
 * ��ӡ16����
*/
void DEBUGTraceHexConsole(const char* pBuffer, int nLength);

/*****************************************************************************
//·����غ���
******************************************************************************/

/**
 * @Description: ��ȡ��������
 * @return: const char* ��������(��������)
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
 * @Description: ��ȡ����·��
 * @return: const char* ����·�� 
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
 * @Description: ��ȡ���ó������ģ����
 * @return: HMODULE ���
 * @Author: ydl	2018-11-29
 */
HMODULE	PATHGetModuleHandle();

/**
 * @Description: ��ȡָ��ģ������
 * @param: hModule ģ����,Ϊ�ձ�ʾ���ô˽ӿڵĳ�����(ע��:��֧��ͨ���˽ӿڻ�ȡ�����������)
 * @param: bIsDelSuffix �Ƿ���Ҫɾ����׺,Ĭ�Ϸ���
 * @return: LPCTSTR ģ������
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
 * @Description: ��ȡ����·��
 * @param: hModule ģ������Ϊ��ֵ��ʾ���ڳ���
 * @return: szPath ģ��Ŀ¼�����뱣֤����ΪMAX_PATH
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
 * @Description: ��ȡ����Ŀ¼·��
 * @return: const char* ����Ŀ¼·��  
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
 * @Description: ��ȡ�û������ļ���·��	C:Documents and Settings\�û���\Local Settings\Application Data
 * @param: szPath �û������ļ�·�������뱣֤szPath���ó���Ϊ  MAX_PATH
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
 * @Description: ��ȡģ�������ļ���·��	�����ļ���ģ��ͬ���� �磺network.dll�����ļ�Ϊ����Ŀ¼�µ�network.ini����network.dll���ܲ���ͬһ��Ŀ¼
 * @param: hModule ģ��,	// �˲����������� [2018-11-29 ydl]
 * @param: szFile �����ļ������뱣֤�ļ�����ΪMAX_PATH
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
 * @Description: ��ȡģ�������ļ���·��	�����ļ���ģ��ͬ���� �磺network.dll�����ļ�Ϊ����Ŀ¼�µ�network.ini����network.dll��ͬһĿ¼��
 * @param: hModule ģ��,Ϊ��ʱ��ʾ���ó�����
 * @param: szFile �����ļ������뱣֤�ļ�����ΪMAX_PATH
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
 * @Description: ��ȡĬ��·��
 * @param: hModule ģ��
 * @param: cDisk �̷�
 * @param: szDefaut Ĭ��·��
 * @param: szPath ����Ĭ��·�������뱣֤�ļ�����ΪMAX_PATH
 * @return: void 
 * @Author: leeafu	2012-04-15
 */
void PATHGetDefaultPath(TCHAR cDisk, LPCTSTR szDefaut, TCHAR* szPath);

/**
 * @Description: ����Ŀ¼�����Ŀ¼�����ڻ�ѭ�����д���
 * @param: szDirectory Ŀ¼
 * @return: true��ʾ�ɹ���false��ʾʧ�� 
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
 * @Description: ɾ��Ŀ¼���������Ŀ¼�����ѭ������ɾ������
 * @param: szDirectory Ŀ¼
 * @return: true��ʾ�ɹ���false��ʾʧ��  
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
 * @Description: ����Ŀ¼�����Ŀ¼�����ڻ�ѭ�����д���
 * @param: szDest Ŀ��Ŀ¼��������'/'��β
 * @param: szSrc ԴĿ¼��������'/'��β
 * @return: true��ʾ�ɹ���false��ʾʧ�� 
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
 * @Description: �ж�Ŀ¼�Ƿ����(�ж�Ŀ¼����),ע��:����������ļ�,Ҳ�᷵��false
 * @param: lpPath Ŀ¼, ��  c:\\abcd��Ч��C:\\abcd\\
 * @return: true��ʾ�ɹ���false��ʾʧ�� 
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
 * @Description: �ж�·���Ƿ����(���ж�Ŀ¼����)
 * @param: lpPath ȫ·��
 * @param: pIsFolder ����������TRUEʱ,*pIsFolder=TRUE:˵��·����Ŀ¼ FALSE:˵��·�����ļ�
 * @return: TRUE��ʾ�ɹ���FALSE��ʾʧ�� 
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
//�ļ���غ���
******************************************************************************/
/**
 * @Description: �ж��ļ��Ƿ����(�жϷ�Ŀ¼����),ע��:���������·��,Ҳ�᷵��false
 * @param: szFile �ļ�
 * @return: true��ʾ���ڣ�false��ʾ������ 
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
 * @Description: ����һ�����ļ�
 * @param: szFile �ļ�
 * @return: true��ʾ�ɹ���false��ʾʧ��   
 * @Author: leeafu	2012-04-15
 */
bool FILENewFile(LPCTSTR szFile);

/**
 * @Description: ��ȡ����汾
 * @param: szVer �汾��Ϣ�����뱣֤szVer���ó���Ϊ  MAX_PATH
 * @return: true��ʾ�ɹ���false��ʾʧ��  
 * @Author: leeafu	2012-04-15
 */
bool FILEGetAppVersion(TCHAR* szVer);

/**
 * @Description: ��ȡ�ļ��汾
 * @param: szFile �ļ���Ϣ
 * @param: szVer �汾��Ϣ�����뱣֤szVer���ó���Ϊ  MAX_PATH
 * @return: true��ʾ�ɹ���false��ʾʧ��  
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
 * @Description: ���ٴ������ļ�
 * @param: szFile �ļ���Ϣ
 * @param: nFileSize �ļ����ȣ��ֽ�
 * @return: true��ʾ�ɹ���false��ʾʧ��  
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
 * @Description: ȡ���ļ�����޸�ʱ��
 * @param: szFile �ļ�
 * @param: lpTime �ռ��С���ֽ�
 * @return: true��ʾ�ɹ���false��ʾʧ��  
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
 * @Description: ��ȡĿ¼�����е��ļ�  (ע�⣺���½ӿڶ���֧�ֳ���4GB�ĵ����ļ�)
 * @param: szDir ��Ŀ¼������ͨ���
 * @param: lstFile ��ȡ�����ļ��б�
 * @param: lTotalLength Ŀ¼�������ļ����ܴ�С
 * @param: bOvertime �ӿڻ�ȡĿ¼�Ƿ񳬹�һ��ʱ��(��ǰ��1��)
 * @return: true��ʾ�ɹ���false��ʾʧ��
 * @Author: ydl 2022-09-08 ����˵��
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


//ȡ�ļ��б���FILEGetPathAllFile�ӿڹ��ܱ���һ��
void FILEGetPathFileList(LPCTSTR szDir, lstTtxFileInfoT& lstFile);
void FILEGetPathFileListA(LPCSTR szDir, lstTtxFileInfo& lstFile);
void FILEGetPathFileListW(LPCWSTR szDir, lstTtxFileInfoW& lstFile);
#ifdef _UNICODE
#define	FILEGetPathFileListT FILEGetPathFileListW
#else
#define FILEGetPathFileListT FILEGetPathFileListA
#endif

/**
 * @Description: ���Ŀ¼�ռ䣬�������ָ����С����ִ��ɾ���ļ�����
 * @param: szPath Ŀ¼
 * @param: nMaxMBSize �ռ��С���ֽ�
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

//��С�ļ��Ƚ϶�ʱ��bRemoveTimeout������Χʱ�����Խ�������־ȫ��ɾ��
void FILECheckPathFileSizeEx(LPCTSTR szPath, int nMaxMBSize, BOOL bRemoveTimeout);
void FILECheckPathFileSizeExA(LPCSTR szPath, int nMaxMBSize, BOOL bRemoveTimeout);
void FILECheckPathFileSizeExW(LPCWSTR szPath, int nMaxMBSize, BOOL bRemoveTimeout);
#ifdef _UNICODE
#define	FILECheckPathFileSizeExT FILECheckPathFileSizeExW
#else
#define FILECheckPathFileSizeExT FILECheckPathFileSizeExA
#endif

/**
 * @Description: �ж��ļ��Ƿ����		ע�⣺��64���ȵĽӿڣ�����ļ�����2GB���᷵��LONG_MAX [2023-4-14 ydl]
 * @param: szFile �ļ�
 * @return: true��ʾ���ڣ�false��ʾ������ 
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
 * @Description: �ж��ļ���׺��
 * @param: szFile �ļ�
 * @param: szExt ��׺��(���ӵ�)
 * @return: true��ʾ���ڣ�false��ʾ������ 
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
 * @Description: ��ȡ�ļ���׺��(���ӵ�)
 * @param: szFile �ļ�
 * @param: szExt ��׺��������
 * @param: nExtLen ��׺������������
 * @return: true��ʾ�ɹ���false��ʾʧ�� 
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
 * @Description: ����������д�뵽�ļ���
 */
BOOL FILESaveBufferToFile(LPCSTR szFile, char* pData, int nDataLen);
BOOL FILESaveBufferToFileW(LPCWSTR szFile, char* pData, int nDataLen);
#ifdef _UNICODE
#define	FILESaveBufferToFileT FILESaveBufferToFileW
#else
#define FILESaveBufferToFileT FILESaveBufferToFile
#endif


/**
 * @Description: ���ļ��ж�ȡȫ�����ݵ�������		ע�⣺��֧�ֳ���2GB���ļ���ȡ [2023-4-14 ydl]
 */
BOOL FILEReadBufferFromFile(LPCSTR szFile, char** ppData, int& nDataLen);
BOOL FILEReadBufferFromFileW(LPCWSTR szFile, char** ppData, int& nDataLen);
#ifdef _UNICODE
#define	FILEReadBufferFromFileT FILEReadBufferFromFileW
#else
#define FILEReadBufferFromFileT FILEReadBufferFromFile
#endif

//nDataLen���ض�ȡ���ĳ���
BOOL FILEReadFixBufFromFile(LPCSTR szFile, char* pData, int& nDataLen);
BOOL FILEReadFixBufFromFileW(LPCWSTR szFile, char* pData, int& nDataLen);
#ifdef _UNICODE
#define	FILEReadFixBufFromFileT FILEReadFixBufFromFileW
#else
#define FILEReadFixBufFromFileT FILEReadFixBufFromFile
#endif

/**
 * @Description: ����·�������ļ�,֧��ͨ���(*��ʾ����ַ�,?��ʾ�����ַ�)  FILESearchFileA("D:\\*.exe", ..)��ʾ����D��Ŀ¼�µ�exe�ļ�
 * @param: szFind �����ļ���·��,֧�ֶ༶ͨ���,��֧����Ŀ¼����
 * @param: vecFile ���������ļ���Ϣ
 * @param: bFullPath �Ƿ񽫽ṹ����cFileName����չΪȫ·��,Ĭ��ΪTRUE(ʹ��ȫ·��),FALSE(ʹ���ļ���)
 * @return: TRUE��ʾ�ɹ���FALSE��ʾʧ�� 
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
 * @Description: ����·�������ļ�,֧��ͨ���(*��ʾ����ַ�,?��ʾ�����ַ�)  FILESearchFileA("D:\\", "*.exe", ..)��ʾ����D�̺�������Ŀ¼�µ�exe�ļ�
 * @param: szPathFind ����Ŀ¼��·��,֧�ֶ༶ͨ���,֧����Ŀ¼����
 * @param: szFileFind �����ļ�����,֧��ͨ���
 * @param: vecFile ���������ļ���Ϣ
 * @param: bFullPath �Ƿ񽫽ṹ����cFileName����չΪȫ·��,Ĭ��ΪTRUE(ʹ��ȫ·��),FALSE(ʹ���ļ���)
 * @return: TRUE��ʾ�ɹ���FALSE��ʾʧ�� 
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
 * @Description: У���ļ���,��֤�ļ���·������Ч�� 
 * @param: szFile Ӧ�����ļ�·��
 * @return: TRUE��ʾ������Ч,δ�滻��FALSE��ʾ������Ч,���滻�ַ�
 * @Author: ydl 2018-12-3
 �ַ��任����:
 �����ַ� \/:*?"<>|,��Щ���Ų��������ļ������ļ�·��
 0.����ǰ�����ֽ�,��C: \\ ��,��ʱֻ���Ǳ���·��
 1.�����ظ���\��/�ᱻɾ��,������һ��
 2.ð��(:)�滻Ϊ�ֺ�(;)
 3.�Ǻ�(*)�滻Ϊ�Ӻ�(+)
 4.�ʺ�(?)�滻Ϊ��̾��(!)
 5.˫����(")�滻Ϊ������(')
 6.������(<>)�滻ΪС����(())
 7.����(|)�滻Ϊ����(-)
 */
BOOL FILECheckValidA(LPSTR szFile);
BOOL FILECheckValidW(LPWSTR szFile);

#ifdef _UNICODE
#define FILECheckValid	FILECheckValidW
#else
#define FILECheckValid	FILECheckValidA
#endif


/*****************************************************************************
//������غ���
******************************************************************************/
/**
 * @Description: ���ҵ�ǰ���̵�ӳ��
 * @return: �ɹ�����true��ʧ�ܷ���false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSFindProcessSnapshot();

/**
 * @Description: �����Ƿ��������У�ͨ������������ж�
 * @param: szMutexName ����������
 * @return: �ɹ����ؽ��̾��
 * @Author: leeafu	2012-04-15
 */
HANDLE PROCESSIsProcessRunning(LPCTSTR szMutexName);

/**
 * @Description: ͨ���������ƽ��в���
 * @param: lpAppName ���������磬abc.exe
 * @param: dwProcessID ���̺ţ�����ɹ����򷵻�
 * @return: �ɹ�����true��ʧ�ܷ���false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSFindProcess(LPCTSTR lpAppName, DWORD& dwProcessID);


/**
 * @Description: ͨ���������ƽ��в���ID��������̣�
 * @param: szServiceName ������
 * @param: ppdwProcessID ����IDָ�� �����ڻ�new[]��ʹ����ɺ���Ҫ����delete[]�ͷ�
 * @param: nProcessCount ����ID����
 * @return: �����������ڵ���1��ʾ�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE
 * @Author: ydl 2022-09-27
 */
BOOL PROCESSFindProcessMulti(LPCTSTR lpAppName, DWORD** ppdwProcessID, int& nProcessCount);

/**
 * @Description: ɱ������
 * @param: lpAppName ���������磬abc.exe
 * @return: �ɹ�����true��ʧ�ܷ���false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSKillAppProcess(LPCTSTR lpAppName);

/**
 * @Description: ��������Ȩ��
 * @return: �ɹ�����true��ʧ�ܷ���false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSEnablePriv();

/**
 * @Description: ɱ������
 * @param: dwProcessID ���̺�
 * @return: �ɹ�����true��ʧ�ܷ���false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSKillProcess(DWORD dwProcessID);

/**
 * @Description: �����½���
 * @param: pszExeName ��������
 * @param: pszCommand ���̲���
 * @return: �ɹ�����true��ʧ�ܷ���false
 * @Author: leeafu	2012-04-15
 */
bool PROCESSCreateNewProcess(LPCTSTR pszExeName, LPTSTR pszCommand);

/**
 * @Description: ��������
 * @return: ��
 * @Author: leeafu	2012-04-15
 */
void PROCESSRebootProcess();

/**
 * @Description: ��ȡ����·��
 * @param: dwProcessID ����ID
 * @param: szExeFile ����·����szExeFile���ȱ�����ڵ���MAX_PATH�����ز���
 * @return: ��
 * @Author: leeafu	2012-06-08
 */
void PROCESSGetProcessFile(DWORD dwProcessID, TCHAR* szExeFile);

/**
 * @Description: ��ȡ��������ʱ��
 * @param: dwProcessID ����ID
 * @param: runTime ��������ʱ��
 * @return: �ɹ�����TRUE��ʧ�ܷ���FALSE
 * @Author: leeafu	2012-09-25
 */
BOOL PROCESSGetProcessTimes(DWORD dwProcessID, SYSTEMTIME& runTime);


/**
 * @Description: ���ݽ���ID��ȡ��������
 * @param: dwProcessID ����ID
 * @param: szServiceName ������
 * @param: nLength ����������
 * @return: �ɹ�����TRUE��ʧ�ܷ���FALSE
 * @Author: zjt	2016-10-08
 */
BOOL QueryServiceNameByThreadID(DWORD dwProcessID, TCHAR* szServiceName, int nLength);

/**
 * @Description: ���ݷ�������ȡ����ID
 * @param: szServiceName ������
 * @param: dwProcessID ����ID
 * @return: �ɹ�����TRUE��ʧ�ܷ���FALSE
 * @Author: zjt	2016-10-08
 */
BOOL QueryThreadIDByServiceName(LPCTSTR lpServiceName, DWORD& dwProcessID);

/*****************************************************************************
//�ַ���غ���
******************************************************************************/

/**
 * @Description: �ж��ַ����Ƿ�Ϊ����
 * @param: szStr �ַ���
 * @return: �ɹ�����true��ʧ�ܷ���false
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
 * @Description: ����GUID
 * @param: szGUID GUID�ַ����Ȱ���/0������ʱΪ37���ֽ�
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
 * @Description: �ַ����ָ��
 * @param: szStr �ַ���
 * @param: cSplit �ָ��
 * @param: vecStr �����ַ�������
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
 * @Description: �ַ����ָ��(����������)
 * @param: szStr �ַ���
 * @param: cSplit �ָ��
 * @param: vecValue ��������������  ע��:�ַ���Ϊ��ʱ�����  ��"1,2,,3," STRINGSplit����5��Ԫ��["1","2","","3",""]  STRINGSplitIntֻ�᷵��[1,2,3]3��Ԫ��
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
 * @Description: �ַ���ƴ�Ӻ���(����������)
 * @param: vecValue/mapValue ����
 * @param: szJoin �����ַ���,Ĭ��ΪӢ�Ķ���
 * @return: ����ƴ�ӵ��ַ���  ��{1,2,3} ����1,2,3
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
 * @Description: �ַ���ƴ�Ӻ���(����������) ��֤��������ܶ�
 * @param: mapValue ����,�����С��������
 * @param: szJoin �����ַ���,Ĭ��ΪӢ�Ķ���
 * @return: ����ƴ�ӵ��ַ���  ��[-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,-10,-8,-7,-6,-5,-4,-3,-2,-1,0,2,3,4,5,6,7,8,9,10,11] ���� "-20--10,-8-0,2-11"
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
 * @Description: �ַ����ָ��(����������)
 * @param: szStr STRINGJoinIntShortA��ؽӿڷ��ص��ַ���
 * @param: cSplit �ָ��
 * @param: vecValue ��������������
			"-20--10,-8-0,2-11" ������Ϊ [-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,-10,-8,-7,-6,-5,-4,-3,-2,-1,0,2,3,4,5,6,7,8,9,10,11]
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
 * @Description: �ַ����ָ����ֱ��ʹ��c�������������������Ч��
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
 * @Description: �ַ��滻�������滻�����ַ�
 * @param: szStr �ַ���
 * @param: cOld Ҫ�滻���ַ�
 * @param: cNew �滻����ַ�
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
 * @Description: �ַ��滻����(�滻�ַ���)
 * @param: szStr �ַ���
 * @param: szOld Ҫ�滻���ַ���
 * @param: szNew �滻����ַ���
 * @Author: ydl  2018-04-27

 ����һ: szOld��szNew���ǵ��ַ����ַ���,��"1","?",����std::replace�滻
 ������: szOldΪ���ַ�,szNewΪ���ַ���(����ΪNULL),����std::removeɾ��
 */
void STRINGReplaceStringA(std::string& str, LPCSTR szOld, LPCSTR szNew);
void STRINGReplaceStringW(std::wstring& str, LPCWSTR szOld, LPCWSTR szNew);
/**
 * @Description: �ַ��滻����(�滻�ַ���)
 * @param: szStr �����ַ���
 * @param: szOld Ҫ�滻���ַ���
 * @param: szNew �滻����ַ���
 * @return: �滻֮����ַ���
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
//�ַ�����ת����16���Ƶ��ַ���
//�ϲ���Ҫ�ͷŷ��ص�����  SAFE_DELETE_ARRAY(ppStrHex), SAFE_DELETE_ARRAY(ppData)
void STRINGCharArr2Hex(const unsigned char* pData, int nDataLen, char** ppStrHex);
//16�����ַ���ת��������
void STRINGHex2CharArr(const std::string& strHex, unsigned char** ppData, int& nDataLen);

/**
 * @Description: �ַ�����ת�����ַ���,��ʼ����ΪpHead
 * @param: pData �ַ�����
 * @param: nLen �ַ�����
 * @param: pHead ��ʼ����
 * @param: pSeparator �������
 * @Author: ydl  2018-0705
 */
// ʾ��:STRINGCharArr2HexExA("123", 3, "Data=", " ") ����Data=31 32 33
std::string STRINGCharArr2HexExA(const void* pData, int nLen, const char* pHead = NULL, const char* pSeparator = NULL);
std::wstring STRINGCharArr2HexExW(const void* pData, int nLen, const wchar_t* pHead = NULL, const wchar_t* pSeparator = NULL);

#if defined(_UNICODE)
#define STRINGCharArr2HexEx	STRINGCharArr2HexExW
#else
#define STRINGCharArr2HexEx	STRINGCharArr2HexExA
#endif

/**
 * @Description: �ַ��滻����(�滻�ַ���)
 * @param: pData �����ַ���,ע��:ֻ����ż���ֽڵ�����
 * @param: nLen �ַ�������,Ϊ0ʱ�Զ�����
 * @return: ��ʽ�����ַ���,��313233,����123
 * @Author: ydl  2018-04-27
 */
std::string STRINGHexStr2CharArrA(const char* pData, int nLen = 0);

template <class T>
T STRINGHexStdStr2CharArrA(const T& str)
{
	return STRINGHexStr2CharArrA(str.data(), (int)str.size());
}

/**
 * @Description: 'FA' = 15*16 + 10  16����ת����char
 * @param: pBuf �ַ���
 * @Author: leeafu	2013-06-11
 */
unsigned char STRINGHex2Char(char* pBuf);

/**
 * @Description: ���ַ���ת���ɴ�д
 * @param: szStr ��Դ�ַ��������Ϊ��д
 * @return: ��
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
 * @Description: ���ַ���ת����Сд
 * @param: szStr ��Դ�ַ��������ΪСд
 * @return: ��
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
 * @Description: ��ָ�����͸�ʽ��Ϊ�ַ���
 * @param: pVoid ָ��ֵ
 * @return: 32λ��%d��ʽ�� 64λ��%lld��ʽ�� Hex:32λ��=%X 64λ=%llX
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
 * @Description: ������ڴ���ַ������Ϊһ��,��STRINGMergeMulti(2, "123", -1, "456", -1)=123456
 * @param: nCount,�ַ�������
 * @param: ...,����ַ���,Ӧ�����ɶԵĲ���(�ַ���ָ��ͳ���)
 * @return: ���֮����ַ���
 * @Author: ydl 2018-6-14
 */

std::string STRINGMergeMulti(int nCount, ...);

std::string STRINGMerge2(const char *szBuf1, int nBufLen1, const char *szBuf2, int nBufLen2);
// ģ��STRINGMerge2
template <int nBufLen1, int nBufLen2>
std::string STRINGMerge2(const char (&szBuf1)[nBufLen1], const char (&szBuf2)[nBufLen2])
{
	return STRINGMergeMulti(2, szBuf1, nBufLen1, szBuf2, nBufLen2);
}

std::string STRINGMerge3(const char *szBuf1, int nBufLen1, const char *szBuf2, int nBufLen2, const char *szBuf3, int nBufLen3);
// ģ��STRINGMerge3
template <int nBufLen1, int nBufLen2, int nBufLen3>
std::string STRINGMerge2(const char (&szBuf1)[nBufLen1], const char (&szBuf2)[nBufLen2], const char (&szBuf3)[nBufLen3])
{
	return STRINGMergeMulti(3, szBuf1, nBufLen1, szBuf2, nBufLen2, szBuf3, nBufLen3);
}

/**
 * @Description: ��һ���ַ������ֵ�����ڴ�,��STRINGDivideMulti("123456", 2, buf1, 3, buf2, 3) buf1=12 buf2=34 ����ֵ=56
 * @param: szData,�ַ���
 * @param: nCount,�ַ����������
 * @param: ...,����ַ���,Ӧ�����ɶԵĲ���(�ַ���ָ��ͳ���),ע��:BufLen����ʵ�ʴ�С,����ʱ���һ
 * @return: δ������ַ���,����0��ʾ�������ݶ��ɹ��洢
 * @Author: ydl 2018-6-14
 */
std::string STRINGDivideMulti(const char* szData, int nCount, ...);

// ģ��STRINGDivide1
template <int nBufLen>
std::string STRINGDivide1(const char* szData, char(&szBuf)[nBufLen])
{
	return STRINGDivideMulti(szData, 1, szBuf, nBufLen);
}

std::string STRINGDivide2(const char* szData, char *szBuf1, int nBufLen1, char *szBuf2, int nBufLen2);
// ģ��STRINGDivide2
template <int nBufLen1, int nBufLen2>
std::string STRINGDivide2(const char* szData, char (&szBuf1)[nBufLen1], char (&szBuf2)[nBufLen2])
{
	return STRINGDivide2(szData, szBuf1, nBufLen1, szBuf2, nBufLen2);
}

std::string STRINGDivide3(const char* szData, char *szBuf1, int nBufLen1, char *szBuf2, int nBufLen2, char *szBuf3, int nBufLen3);
// ģ��STRINGDivide3
template <int nBufLen1, int nBufLen2, int nBufLen3>
std::string STRINGDivide3(const char* szData, char (&szBuf1)[nBufLen1], char (&szBuf2)[nBufLen2], char (&szBuf3)[nBufLen3])
{
	return STRINGDivide3(szData, szBuf1, nBufLen1, szBuf2, nBufLen2, szBuf3, nBufLen3);
}


/*****************************************************************************
//ʱ����غ���
******************************************************************************/
/**
 * @Description: �ж�ʱ���Ƿ��Ѿ�����ָ����ʱ��
 * @param: dwTime ֮ǰ��ʱ��
 * @param: dwTimeout ��ʱ��ʱ�䣬����
 * @return: �ɹ�����true��ʧ�ܷ���false
 * @Author: leeafu	2012-04-15
 */
bool TIMEIsTimeOut(DWORD& dwTime, DWORD dwMinSecond);

/**
 * @Description: �ж�ʱ���Ƿ��Ѿ�����ָ����ʱ��
 * @param: dwTime ֮ǰ��ʱ��
 * @param: dwTimeout ��ʱ��ʱ�䣬����
 * @return: �ɹ�����true��ʧ�ܷ���false
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
 * @Description: ȡ�õ�ǰʱ���
 * @return: �ɹ�����ʱ���
 * @Author: leeafu	2012-04-15
 */
time_t TIMEGetCurrentTimestamp();	//��ʱ���
time_t TIMEGetCurrentTimestampMS();	//����ʱ���

/**
 * @Description: ȡ�õ�ǰʱ���ַ���
 * @return: �ɹ������ַ���
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
 * @Description: ��ʽ��ʱ�����崮��2011-04-12 23:34:34
 * @param: Time ʱ����Ϣ
 * @return: �ɹ������ַ���
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
 * @Description: ��ʽ�������ڸ�ʽ��2012-04-12
 * @param: Time ʱ����Ϣ
 * @return: �ɹ������ַ���
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
 * @Description: �������ַ���תΪʱ��ṹ��   
					Ĭ�Ͻӿ�ֻ��֤��������Ч,Full�ӿڻᱣ֤���صĲ���ȫ����Ч
 * @param: szTime ʱ���ַ�����֧�ָ�ʽ:1."2018-01-01"  2."2018-01-01 00:00:00"��'-'��':'�����滻Ϊ�κη����ֵ�����
 * @param: Time ʱ����Ϣ,�ɹ����������ݴ洢���˽ṹ��
 * @return: �ɹ�����true
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
 * @Description: ʱ��Ƚ�
 * @return: ���tm1 > tm2 ����1�� = ����0��< ����-1
 * @Author: leeafu	2012-04-15
 */
int	TIMECompareTime(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);


/**
 * @Description: ʱ����ٱȽ�,��У��ʱ���Ƿ���Ч,�����ж�������ʱ����
 * @return: ���tm1 > tm2 ����1�� = ����0��< ����-1
 * @Author: ydl 2020-8-13
 */
int	TIMEQuickCompareTime(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);


/**
 * @Description: �������ڵ�����
 * @param: �����������  ÿ���1��,���������һ,��1�ܽ�ֹ����1����һ,��1����һ������2��
 * @return: ����
 * @Author: ydl 2020-8-13
 */
int	TIMEGetWeekly(const SYSTEMTIME& tmDate);
int	TIMEGetWeekly(int nYear, int nMonth, int nDay);


/**
 * @Description: ����+��ת��Ϊʱ��
 * @param: nYear ���
 * @param: nWeekly ����
 * @param: stDate ��������,������ʼ,������ʱ����һ,�����һ����1��1��
 * @param: nDayOfWeek ָ�����Ȱ������ڷ�������,Ĭ��Ϊ-1(��һ > ����) 1-6(��һ������) 0(����)
					ע��:��һ�ܿ���ֻ������,���һ�ܿ���ֻ����һ,��ȡ����ֵ�ᵼ��ʧ��
 * @return: �ɹ�����TRUE
 * @Author: ydl 2020-8-13
 */
BOOL	TIMEYearWeeklyTime(int nYear, int nWeekly, SYSTEMTIME& stDate, int nDayOfWeek = -1);



/**
 * @Description: ��ȡ��һ�ܵķ�Χ
 * @param: stTime ��ָ�����ڻ�ȡ��һ��  ע��:�˲�����wDayOfWeek����Ϊ��Чֵ
 * @param: nYear ���ڵ����
 * @param: nWeekly ����,��1��ʼ
 * @param: tmBeg ������ʼ,������ʱ����һ,�����һ����1��1��
 * @param: tmEnd ��������,������ʱ������,�������һ����12��31��
 * @return: �ɹ�����TRUE
 * @Author: ydl 2020-8-13
 */
BOOL	TIMEGetLastWeeklyRange(SYSTEMTIME stTime, SYSTEMTIME& tmBeg, SYSTEMTIME& tmEnd);
BOOL	TIMEGetLastWeeklyRange(int nYear, int nWeekly, SYSTEMTIME& tmBeg, SYSTEMTIME& tmEnd);


/**
 * @Description: ��ȡһ�ܵķ�Χ
 * @param: stTime ����  ע��:�˲�����wDayOfWeek����Ϊ��Чֵ
 * @param: nYear ���ڵ����
 * @param: nWeekly ����,��1��ʼ
 * @param: tmBeg ������ʼ,������ʱ����һ,�����һ����1��1��
 * @param: tmEnd ��������,������ʱ������,�������һ����12��31��
 * @return: �ɹ�����TRUE
 * @Author: ydl 2020-8-13
 */
BOOL	TIMEGetWeeklyRange(SYSTEMTIME stTime, SYSTEMTIME& tmBeg, SYSTEMTIME& tmEnd);
BOOL	TIMEGetWeeklyRange(int nYear, int nWeekly, SYSTEMTIME& tmBeg, SYSTEMTIME& tmEnd);

/**
 * @Description: ������ת����long�뷽ʽ����1900��ʼ
 * @param: tm ʱ��
 * @return: ʱ����
 * @Author: leeafu	2012-04-15 hw 2014/1/17 1970-->1900 ��ʼ
 */
long TIMEFormatTime2Long(const SYSTEMTIME& tm);
long long TIMEFormatTime2LongLong(const SYSTEMTIME& tm);


/**
 * @Description: ��ʱ���������תΪʱ��������룩
 * @param: tm ����  �����ʱ����
 * @return: ʱ��� ��λ����
 * @Author: ydl 2022-11-24
 */
long long TIMEFormatDateTimeMS(SYSTEMTIME tm);
long long TIMEFormatDateTimeMS(int nYear, int nMonth, int nDay);


/**
 * @Description: ��ʱ��תΪʱ��������룩
 * @param: tm ����
 * @return: ʱ��� ��λ����
 * @Author: ydl 2022-11-24
 */
long long TIMEFormatTimeMS(const SYSTEMTIME& tm);

/**
 * @Description: ʱ����ɾ����
 * @param: tm ʱ��
 * @param: nSecond �룬�������Ϊ��������Ϊ����
 * @return: ��ʱ��
 * @Author: leeafu	2012-04-15
 */
SYSTEMTIME TIMEIncrease(const SYSTEMTIME& tm, int nSecond);

/**
 * @Description: ʱ����ɾ����  Ĭ�Ͻӿ�ֻ��֤��������Ч,Ex�ӿڻᱣ֤���صĲ���ȫ����Ч
 * @param: tm ʱ��
 * @param: nYear �꣬���Ϊ��������Ϊ����
 * @param: nMonth �£����Ϊ��������Ϊ����
 * @param: nDay �գ����Ϊ��������Ϊ����
 * @return: ��ʱ��
 * @Author: ydl	2018-5-18
 * ע��:���·�������һ��ʱ,���¿��ܵ���ʱ�䲻��ȫһ��,�Ӽ�һ���º�,���ڿ��ܲ����ԭʼ��һ��
     ��:3-30��ǰ��λ1����,����2-28(���귵��2-29),�����λ1����,����3-28(����29)
	 ���������Ҫ����������ȷ��ԭ,����ʹ����������
 */
SYSTEMTIME TIMEIncreaseYMD(const SYSTEMTIME& tm, int nYear, int nMonth, int nDay = 0);
SYSTEMTIME TIMEIncreaseYMDEx(const SYSTEMTIME& tm, int nYear, int nMonth, int nDay = 0);
SYSTEMTIME TIMEIncreaseD(const SYSTEMTIME& tm, int nDay);
SYSTEMTIME TIMEIncreaseDEx(const SYSTEMTIME& tm, int nDay);

/**
 * @Description: �ж�����ʱ����������
 * @return: ����ʱ������
 * @Author: leeafu	2012-09-13
 */
int TIMECompare(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);
__int64 TIMECompare64(const SYSTEMTIME& tm1, const SYSTEMTIME& tm2);

/**
 * @Description: time_tת����SYSTEMTIME
 * @return: SYSTEMTIME
 * @Author: hw	2013-09-14
 */
SYSTEMTIME TIMETimeToSystemTime(time_t t);

/**
 * @Description: SYSTEMTIMEת����time_t
 * @return: time_t
 * @Author: hw	2013-09-14
 */
time_t TIMESystemTime2Time(const SYSTEMTIME& st);

/*
* @Description: ȡ������ʱ���֮�����·���Ϣ		ע�⣺���������Чʱ�䣨�����Ϊ0������������·�
*				2023-03-09 �����ж�ʱ������Ĵ�С����ʼʱ��ȡ��Сֵ������ʱ��ȡ�ϴ�ֵ
*/
void	TIMESplitMonth(const SYSTEMTIME& beg, const SYSTEMTIME& end, std::vector<TIMEMonth_S>& lstMonth);

/*****************************************************************************
//����ϵͳ��غ���
******************************************************************************/
//�ж�OS�İ汾
BOOL	OSCheckOsVersion(DWORD nMajorVer, DWORD nMinVer);
//�ж��Ƿ�ΪXPϵͳ
BOOL	OSIsWinXP();

/*****************************************************************************
//���������غ���
******************************************************************************/
//׷�ӻ��棬������治�����������
BOOL	BUFFAppend(const char* pAddBuf, int nAddLen, char** ppDestBuffer, int& nDestBufLen, int& nDestDataLen, int nNewLength = 50 * 1024);
//���仺�棬���سɹ�����ĳ��ȣ�ʧ�ܷ���0
//����ǰ�������ͷ�*ppBuffer��ȷ�� *ppBuffer����ʱ��Ҫ��ʼ��ΪNULL
int		BUFFAlloc(char** ppBuffer, int nBufLen);


/*****************************************************************************
//ѹ����ѹ�ڴ�����
******************************************************************************/
/**
* @Description: ѹ���ڴ�����(XZip)
* @param: pSrcBuffer ԭʼ��������
* @param: nSrcLen	ԭʼ�������ݳ���
* @param: szFlag   ��ǩ(ѹ���ͽ�ѹ��Ӧ)
* @param: ppDestBuf  ѹ�����߽�ѹ��Ļ������� �ⲿ�ͷ�
* @param: nDestLen  ѹ�����߽�ѹ��Ļ������ݳ���
* @return: �ɹ�����TRUE�� ʧ�ܷ���FALSE	
* @Author: zjt	2018-07-25
 */
BOOL CompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, LPCTSTR szFlag, char **ppDestBuf, unsigned int& uiDestLen);
BOOL UnCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, LPCTSTR szFlag, char **ppDestBuf, unsigned int& uiDestLen);

/**
* @Description: ѹ�����ѹ�ڴ�����,��ʹ�ö���洢(XZip)
* @param: pSrcBuffer ԭʼ��������
* @param: nSrcLen	ԭʼ�������ݳ���
* @param: szFlag   ��ǩ(ѹ���ͽ�ѹ��Ӧ)
* @param: vecBuf  ѹ�����߽�ѹ��Ļ�������,����ԭ������֮������������
* @return: �ɹ�����TRUE�� ʧ�ܷ���FALSE	
* @Author: ydl	2018-08-03
 */

BOOL CompressBufferToObj(const char* pSrcBuffer, unsigned int uiSrcLen, LPCTSTR szFlag, std::vector<char>& vecBuf);
BOOL UnCompressBufferToObj(const char* pSrcBuffer, unsigned int uiSrcLen, LPCTSTR szFlag, std::vector<char>& vecBuf);

/**
* @Description: ѹ���ڴ�����(GZIP),ʹ�ô˽ӿ���Ҫ����ͷ�ļ�libzlib.h
* @param: pSrcBuffer ԭʼ��������
* @param: nSrcLen	ԭʼ�������ݳ���
* @param: strDest  ѹ�����߽�ѹ��Ļ�������
* @return: �ɹ�����TRUE�� ʧ�ܷ���FALSE
* @Author: ydl 2019-7-19
 */
BOOL ZlibCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, std::string& strDest);
BOOL ZlibUnCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, std::string& strDest);

/**
* @Description: ����ѹ���ļ���ʽ(GZIP),ʹ�ô˽ӿ���Ҫ����ͷ�ļ�libzlib.h
* @param: pSrcBuffer ԭʼ��������
* @param: nSrcLen	ԭʼ�������ݳ���
* @param: strDest  ѹ�����߽�ѹ��Ļ�������
* @return: �ɹ�����TRUE�� ʧ�ܷ���FALSE
* @Author: ydl 2019-7-19
 */
BOOL GZlibCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, std::string& strDest, int level = -1);
BOOL GZlibUnCompressBuffer(const char* pSrcBuffer, unsigned int uiSrcLen, std::string& strDest);


/*****************************************************************************
//ͨ����غ���
******************************************************************************/


#endif /*	_PUBLIC_H_	*/