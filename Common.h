// Common.h: interface for the CCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMON_H__B8403CD4_6ED4_4E06_B9AB_F2CA19C02CD9__INCLUDED_)
#define AFX_COMMON_H__B8403CD4_6ED4_4E06_B9AB_F2CA19C02CD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

void GetUserLog(GPSUsrLog_S* pUserLog, CString& strMainType, CString& strSubType, CString& strInfo);
// CString GetClientSubTypeLog(int nLogType, CString& strSubType, CString& strInfo);
// CString GetDevCtrlSubTypeLog(int nLogType, CString& strSubType, CString& strInfo);
// CString GetMediaSubTypeLog(int nLogType, CString& strSubType, CString& strInfo);

#endif // !defined(AFX_COMMON_H__B8403CD4_6ED4_4E06_B9AB_F2CA19C02CD9__INCLUDED_)
