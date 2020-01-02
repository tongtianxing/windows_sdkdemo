// DownObject.cpp: implementation of the CDownObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DownObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDownObject::CDownObject()
{
	m_pFile = NULL;
	memset(m_szDownFileName, 0, sizeof(m_szDownFileName));

	m_nDevID = 0;
	m_nChn = 0;
	m_lHandle = 0;

	m_hDownHwnd = NULL;
	m_uDownMsg = 0;
}

CDownObject::~CDownObject()
{
	StopDown();
	CloseDownFile();
}

BOOL CDownObject::StartDown()
{
	return FALSE;
}

BOOL CDownObject::StopDown()
{
	return FALSE;
}

CString	CDownObject::GetDownTitle()
{
	return "";
}

void CDownObject::FUNMsgCB(int nMsg, int nParam, void* pUsr)
{
	CDownObject* pThis = (CDownObject*)pUsr;
	pThis->DoMsgCB(nMsg, nParam);
}

void CDownObject::DoMsgCB(int nMsg, int nParam)
{
	if (GPS_DOWNLOAD_MSG_BEGIN == nMsg)
	{
	}
	else
	{
		PostDownMsg(nMsg, nParam);
	}
}

void CDownObject::FUNDataCB(const char* pData, int nDataLen, long nPos, void* pUsr)
{
	CDownObject* pThis = (CDownObject*)pUsr;
	pThis->DoDataCB(pData, nDataLen, nPos);
}

void CDownObject::DoDataCB(const char* pData, int nDataLen, long nPos)
{
	if (m_pFile)
	{
		long nCurPos = ftell(m_pFile);
		if (nPos > nCurPos)
		{
			int nWriteLen = nPos - nCurPos;
			char* pTempBuf = new char[nWriteLen];
			memset(pTempBuf, 0, nWriteLen);
			int nFileWriteLen = fwrite(pTempBuf, 1, nWriteLen, m_pFile);
			SAFE_DELETE_ARRAY(pTempBuf);
		}
		else if (nPos < nCurPos)
		{
			fseek(m_pFile, nPos, SEEK_SET);
		}
		
		fwrite(pData, 1, nDataLen, m_pFile);
	}
}

void CDownObject::PostDownMsg(int wParam, int lParam)
{
	if (m_hDownHwnd)
	{
		PostMessage(m_hDownHwnd, m_uDownMsg, wParam, lParam);
	}
}

void CDownObject::OpenDownFile()
{
	ASSERT(NULL == m_pFile);
	m_pFile = _tfopen(m_szDownFileName, _T("wb+"));
}

void CDownObject::CloseDownFile()
{
	if (m_pFile)
	{
		fclose(m_pFile);	m_pFile = NULL;
	}
}