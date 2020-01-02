// RecSearch.cpp: implementation of the CRecSearch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Search.h"
//#include "DlgRecSearch.h"
#include "VDvsDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSearch::CSearch()
{
	m_lHandle = NULL;
	m_nSearchType = 0;
	m_hWnd = NULL;
	m_nSearchMsgCB = 0;
	m_nSearchFileCB = 0;
	m_nFileType = 0;
}

CSearch::CSearch(int nSrcType, int nFileType /*= GPS_FILE_ATTRIBUTE_RECORD*/)
{
	m_lHandle = NULL;
	m_nSearchType = nSrcType;
	m_nFileType = nFileType;
	m_hWnd = NULL;
	m_nSearchMsgCB = 0;
	m_nSearchFileCB = 0;
}

CSearch::~CSearch()
{

}

CSearch* CSearch::GetNewRecSearch(int nSrcType, int nFileType /* = GPS_FILE_ATTRIBUTE_RECORD */)
{
	if (GPS_FILE_LOCATION_DEVICE == nSrcType 
		|| GPS_FILE_LOCATION_DOWNSVR == nSrcType
		|| GPS_FILE_LOCATION_STOSVR == nSrcType)
	{
		return new CNetSearch(nSrcType, nFileType);
	}
// 	else if (RECCTRL_FILE_LOCATION_DISK == nSrcType)
// 	{
// 		return new CLocalRecSearch(nSrcType);
// 	}
	else
	{
		ASSERT(NULL);
		return NULL;
	}
}

void CSearch::SetWndAndMsg(HWND hWnd, int nSearchMsgCB, int nSearchFileCB)
{
	m_hWnd = hWnd;
	m_nSearchMsgCB = nSearchMsgCB;
	m_nSearchFileCB = nSearchFileCB;
}

void CSearch::FUNSearchMsgCB(int nMsg, int nParam, void* pUsr)
{
	CSearch* pThis = (CSearch*)pUsr;
	pThis->DoSearchMsgCB(nMsg, nParam);
}

void CSearch::DoSearchMsgCB(int nMsg, int nParam)
{
	if (NULL != m_hWnd)
	{
		::PostMessage(m_hWnd, m_nSearchMsgCB, nMsg, nParam);
	}
}

void CSearch::FUNSearchFileCB(GPSFile_S* pFile, void* pUsr)
{
	CSearch* pThis = (CSearch*)pUsr;
	pThis->DoSearchFileCB(pFile);
}

void CSearch::DoSearchFileCB(GPSFile_S* pFile)
{
	if (NULL != m_hWnd)
	{
	 	GPSFile_S* pNewFile  = new GPSFile_S;
 		*pNewFile = *pFile;
		::PostMessage(m_hWnd, m_nSearchFileCB, WPARAM(pNewFile), 0);
	}
}
//////////////////////////////////////////////////////////////////////////
CNetSearch::CNetSearch()
{
	m_lHandle = NULL;
	m_nSearchType = 0;
	m_hWnd = NULL;
	m_nSearchMsgCB = 0;
	m_nSearchFileCB = 0;
}

CNetSearch::CNetSearch(int nSrcType, int nFileTyoe):CSearch(nSrcType, nFileTyoe)
{

}

CNetSearch::~CNetSearch()
{
	StopSearch();
}

void CNetSearch::StartSearch(const char* szDevIDNO, int nChn, int nRecType, int nYear, int nMonth, int nDay,
								int nBegSec, int nEndSec)
{
	NETMEDIA_SFOpenSrchFile(&m_lHandle, szDevIDNO, m_nSearchType, m_nFileType);
	NETMEDIA_SFSetSearchMsgCB(m_lHandle, this, FUNSearchMsgCB);
	NETMEDIA_SFSetSearchFileCB(m_lHandle, this, FUNSearchFileCB);
	NETMEDIA_SFStartSearchFile(m_lHandle, nYear, nMonth, nDay, nRecType, nChn, nBegSec, nEndSec);
}

void CNetSearch::StartSearchEx(const char* szDevIDNO, int nChn, int nRecType, 
							   int nYear, int nMonth, int nDay, int nBegSec,
							   int nYearEnd, int nMonthEnd, int nDayEnd, int nEndSec)
{
	NETMEDIA_SFOpenSrchFile(&m_lHandle, szDevIDNO, m_nSearchType, m_nFileType);
	NETMEDIA_SFSetSearchMsgCB(m_lHandle, this, FUNSearchMsgCB);
	NETMEDIA_SFSetSearchFileCB(m_lHandle, this, FUNSearchFileCB);
	NETMEDIA_SFStartSearchFileEx(m_lHandle, nYear, nMonth, nDay, nBegSec, nYearEnd, nMonthEnd, nDayEnd, nEndSec, nRecType, nChn);
}


void CNetSearch::StopSearch()
{
	if(NULL != m_lHandle)
	{
		NETMEDIA_SFStopSearchFile(m_lHandle);
		NETMEDIA_SFCloseSearchFile(m_lHandle); 
		m_lHandle = NULL;
		m_hWnd = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////

CDownFile::CDownFile()
{

}

CDownFile::CDownFile(int nFileType)
{
	m_nFileType = nFileType;
	m_lDownHandle = NULL;
	m_hWnd = NULL;
	m_nMsg = 0;
	m_pUser = NULL;
	m_pfDwonFileMsgCB = NULL;
}

CDownFile::~CDownFile()
{

}

int CDownFile::GetDownFlowRate()
{
	int nFlowRate = 0;
	NETMEDIA_DFGetFlowRate(m_lDownHandle, &nFlowRate);
	return nFlowRate;
}

BOOL CDownFile::StartDownFile(GPSFile_S* pFile, char* szFilePath)
{
	NETMEDIA_DFOpenDownFile(&m_lDownHandle, m_nFileType);
	NETMEDIA_DFSetDFileMsgCB(m_lDownHandle, this, FUNDownMsgCB);
	if (GPS_OK == NETMEDIA_DFStartDownFile(m_lDownHandle, pFile, szFilePath))
	{
		m_pFile = pFile;
		return TRUE;
	}
	else
	{
		NETMEDIA_DFCloseDownFile(m_lDownHandle);
		m_lDownHandle = NULL;
		return FALSE;
	}
}

BOOL CDownFile::StopDowndFile()
{
	if (m_lDownHandle)
	{
		NETMEDIA_DFStopDownFile(m_lDownHandle);
		NETMEDIA_DFCloseDownFile(m_lDownHandle);
		m_lDownHandle = NULL;
		return TRUE;
	}
	return FALSE;
}

void CDownFile::SetWndAndMsg(HWND hWnd, int nDownMsg)
{
	m_hWnd = hWnd;
	m_nMsg = nDownMsg;
}

void CDownFile::SetDownFileMsgCB(void* pUsr, FUNDownFileMsgCB pfDwonFileMsgCB)
{
	m_pUser = pUsr;
	m_pfDwonFileMsgCB = pfDwonFileMsgCB;
}

void CDownFile::FUNDownMsgCB(int nMsg, int nParam, void* pUsr)
{
	CDownFile* pThis = (CDownFile*)pUsr;
	pThis->DoDownMsgCB(nMsg, nParam);
}

void CDownFile::DoDownMsgCB(int nMsg, int nParam)
{
	if (NULL != m_hWnd)
	{
		::PostMessage(m_hWnd, m_nMsg, nMsg, nParam);
	}

	if (m_pfDwonFileMsgCB)
	{
		m_pfDwonFileMsgCB(nMsg, nParam, m_pUser);
	}
}
