// Playback.cpp: implementation of the CPlayback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "clientdemo.h"
#include "Playback.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define CHECK_ZERO_VALUE( p, retValue ) \
	if( 0 == (p) )\
{\
	return retValue;\
}


CPlayback::CPlayback()
{
	m_lPlayback = NULL;
	m_hWndMsg = NULL;
	m_hWndViedo = NULL;
	m_uiMsg = 0;
	memset(&m_File, 0, sizeof(m_File));
	m_nChannel = 0;
	m_nProgressMax = 100;
}

CPlayback::~CPlayback()
{

}


void CPlayback::Init()
{
	if(NULL == m_lPlayback)
	{
		NETMEDIA_PBOpenPlayBack(&m_lPlayback);
		NETMEDIA_PBSetPlayMsgCallBack(m_lPlayback, this, FUNPlayMsgCB);
	}
}
void CPlayback::Uninit()
{
	if(m_lPlayback)
	{
		NETMEDIA_PBClosePlayback(m_lPlayback);
		m_lPlayback = NULL;
	}
}
void CPlayback::SetMsgWnd(HWND hWnd, UINT uiMsg)
{
	m_hWndMsg = hWnd;
	m_uiMsg = uiMsg;
}

void CPlayback::SetProgressMax(int nProgressMax)
{
	m_nProgressMax = nProgressMax;
}

int CPlayback::Play(GPSFile_S* pFile, int nChannel, int nBegMinSecond, int nEndMinSecond, BOOL bPlayOnlyIFrame, HWND hWnd)
{
	int bRet = S_FALSE;
	Init();
	StopPlay();
	if(pFile)
	{
		m_File = *pFile;
		m_nChannel = nChannel;
		m_hWndViedo = hWnd;
	}
	else if (m_hWndViedo == NULL)
	{
		return S_FALSE;
	}
	return NETMEDIA_PBStartPlayback(m_lPlayback, &m_File, m_nChannel, nBegMinSecond, nEndMinSecond
		, bPlayOnlyIFrame, m_hWndViedo);
}

int CPlayback::Down(GPSFile_S* pFile, int nChannel, int nBegMinSecond, int nEndMinSecond, BOOL bPlayOnlyIFrame, const char* pSaveFile, BOOL bResumeDown)
{
	int bRet = S_FALSE;
	Init();
	StopDown();
	if(pFile)
	{
		m_File = *pFile;
		m_nChannel = nChannel;
	}
	return NETMEDIA_PBStartDown(m_lPlayback, &m_File, m_nChannel, nBegMinSecond, nEndMinSecond
		, bPlayOnlyIFrame, pSaveFile, bResumeDown);	
}

int CPlayback::Pause(BOOL bPause)
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)
	return NETMEDIA_PBPause(m_lPlayback, bPause);
}

int CPlayback::StopPlay()
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)
	NETMEDIA_PBStopPlayback(m_lPlayback);
	InvalidateRect(m_hWndViedo,NULL,TRUE);
	return S_OK;
}

int CPlayback::StopDown()
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)
	NETMEDIA_PBStopDown(m_lPlayback);
	return S_OK;
}

int CPlayback::GetFlowRate(int* lpFlowRate)
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)
	return NETMEDIA_PBGetFlowRate(m_lPlayback, lpFlowRate);
}

int CPlayback::PlaySound(long lPlay)
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)
	return NETMEDIA_PBPlaySound(m_lPlayback, lPlay);
}

int CPlayback::SetVolume(WORD wVolume)
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)
	return NETMEDIA_PBSetVolume(m_lPlayback, wVolume);
}

int CPlayback::SetPlayProgress(int nProcess)
{
	int nRet = S_FALSE;
	int nFileTimeCount = GetFileSecond();
	if (nFileTimeCount >= 0)
	{
		int nTime = (nProcess * nFileTimeCount)/m_nProgressMax;
		nRet = NETMEDIA_PBSetPlayTime(m_lPlayback, nTime*1000);
	}

	return nRet;
}
int CPlayback::SetPlayIFrame(BOOL bIFrame)
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)
	return NETMEDIA_PBSetPlayIFrame(m_lPlayback, bIFrame);
}
int CPlayback::GetPlayProgress(int& nProgress, CString& strTime)
{
	int nRet = S_FALSE;
	CHECK_ZERO_VALUE(m_lPlayback, nRet)

	int nPlayTime = 0;
	if (S_OK == NETMEDIA_PBGetPlayTime(m_lPlayback, &nPlayTime))
	{
		int nFileTimeCount = GetFileMinSecond();
		if (nFileTimeCount > 0)
		{
			if (nPlayTime < 0)
			{
				nProgress = 0;
				strTime = FormatSecond(nPlayTime/1000 +m_File.uiBegintime);
			}
			else
			{
				if (nPlayTime < nFileTimeCount)
				{
					long nTmp = nPlayTime*m_nProgressMax;
					nProgress = nTmp/nFileTimeCount;
					strTime = FormatSecond(nPlayTime/1000 +m_File.uiBegintime);
					nRet = S_OK;
				}
			}
		}
	}

	return nRet;
}

int CPlayback::GetDownProgress(int& nProgress)
{
	int nRet = S_FALSE;
	int nDownMinSecond = 0;
	if (S_OK == GetDownTime(nDownMinSecond))
	{
		int nFileTimeCount = GetFileMinSecond();
		if (nFileTimeCount > 0 && nDownMinSecond > 0)
		{
			//if(nDownMinSecond <= nFileTimeCount)
			{
				long nTmp = nDownMinSecond*m_nProgressMax;
				nProgress = nTmp/nFileTimeCount;
				nRet = S_OK;
			}
		}
	}

	return nRet;
}

int CPlayback::GetDownTime(int& nDownMinSecond)
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)	
	return NETMEDIA_PBGetDownTime(m_lPlayback, &nDownMinSecond);
}

int CPlayback::CaptureBMP(LPCTSTR szBmpFile)
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)

#if defined(_UNICODE) || defined(UNICODE)  
		USES_CONVERSION;
	return NETMEDIA_PBCaptureBMP(m_lPlayback, W2A(szBmpFile));
#else
	return NETMEDIA_PBCaptureBMP(m_lPlayback, szBmpFile);
#endif
}
int CPlayback::AdjustedWndRect()
{
	CHECK_ZERO_VALUE(m_lPlayback, S_FALSE)
	return NETMEDIA_PBAdjustedWndRect(m_lPlayback);
}
int CPlayback::GetFileSecond()
{
	return (m_File.uiEndtime - m_File.uiBegintime);
}
int CPlayback::GetFileMinSecond()
{
	return GetFileSecond()*1000;
}
void CPlayback::GetFileDevAndChannel(TCHAR* szDevIDNO, int nSize, int& nChannel)
{
#if defined(_UNICODE) || defined(UNICODE)  
	USES_CONVERSION;
	_tcsnccpy(szDevIDNO, A2W(m_File.szDevIDNO), nSize);
#else
	_tcsnccpy(szDevIDNO, m_File.szDevIDNO, nSize);
#endif

	nChannel = m_nChannel;
}
void CPlayback::FUNPlayMsgCB(int nMsg, void* pUsr)
{
	CPlayback* pThis = (CPlayback*)pUsr;
	pThis->DoPlayMsgCB(nMsg);
}

void CPlayback::DoPlayMsgCB(int nMsg)
{
	if (m_hWndMsg)
	{
		switch(nMsg)
		{
		case NETMEDIA_REAL_MSG_SUCCESS:
		case NETMEDIA_REAL_MSG_CNT_MS_SUC:
		case NETMEDIA_REAL_MSG_CNT_DEV_SUC:
		case NETMEDIA_REAL_MSG_CNT_MS_FD:
		case NETMEDIA_REAL_MSG_UNKNOW:	//disconnect ignore
			break;
		case NETMEDIA_REAL_MSG_FINISHED:
			if (m_hWndViedo == NULL)
			{
				::PostMessage(m_hWndMsg, m_uiMsg, MSG_PALYBACK_DOWN_FINISHED, 0);
			}
			break;
		case NETMEDIA_REAL_MSG_PLAY_FINISHED:
			::PostMessage(m_hWndMsg, m_uiMsg, MSG_PALYBACK_FINISHED, 0);
			break;
		default:
			::PostMessage(m_hWndMsg, m_uiMsg, MSG_PALYBACK_FAILED, 0);
			break;
		}
	}
}
