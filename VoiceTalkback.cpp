// VoiceTalkback.cpp: implementation of the CVoiceTalkback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoiceTalkback.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVoiceTalkback* CVoiceTalkback::g_pVoiceTalkback = NULL;

CVoiceTalkback* VOICETalkback()
{
	if (NULL == CVoiceTalkback::g_pVoiceTalkback)
	{
		CVoiceTalkback::g_pVoiceTalkback = new CVoiceTalkback;
	}
	return CVoiceTalkback::g_pVoiceTalkback;
}

void DELTalkback()
{
	SAFE_DELETE_OBJECT(CVoiceTalkback::g_pVoiceTalkback);
}

CVoiceTalkback::CVoiceTalkback()
{
	memset(m_szDevIDNO, 0, sizeof(m_szDevIDNO));
	m_lTalkback = NULL;
	m_hTalkHwnd = NULL;
	m_uiTalkMsg = 0;
	m_bTBTrac = false;
	m_pFile = NULL;
	m_lAudioDec = NULL;
}

CVoiceTalkback::~CVoiceTalkback()
{
	StopTalkback();
}

int CVoiceTalkback::StartTalkback(LPCTSTR szDevIDNO, int nChn, bool bTBTrac)
{
	if (NULL == m_lTalkback)
	{
		int nTbRet = 0;
		if (bTBTrac)
		{
#if defined(_UNICODE) || defined(UNICODE)  
			USES_CONVERSION;
			NETMEDIA_TBOpenTalkbackTran(W2A(szDevIDNO), nChn, 0, &m_lTalkback);
#else
			nTbRet = NETMEDIA_TBOpenTalkbackTran(szDevIDNO, nChn, 0, &m_lTalkback);
#endif
			nTbRet = NETMEDIA_TBSetAudioDataCB(m_lTalkback, this, FUNAudioDataCB);
			CloseAudioFile();
			OpenAudioFile();
		}
		else
		{
#if defined(_UNICODE) || defined(UNICODE)  
			USES_CONVERSION;
			NETMEDIA_TBOpenTalkback(W2A(szDevIDNO), nChn, 0, &m_lTalkback);
#else
			NETMEDIA_TBOpenTalkback(szDevIDNO, nChn, 0, &m_lTalkback);
#endif
			//if (INI_ReadInt(E_CFG_INTERCOM_PTT_16K))
			//{
			//	NETMEDIA_TBSetAudioType(m_lTalkback, AVDEC_PLAY_A_TYPE_AAC_16KBPS);
			//}	
		}
	//	NETMEDIA_TBSetRealServer(m_lTalkback, "192.168.1.108", 6605, NULL);
		NETMEDIA_TBSetTalkbackMsgCallBack(m_lTalkback, this, FUNTalkbackMsgCB);
		int nRet = NETMEDIA_TBStartTalkback(m_lTalkback);
		if (nRet != GPS_OK)
		{
			NETMEDIA_TBCloseTalkback(m_lTalkback); 
			m_lTalkback = NULL;
			return nRet;
		}
		else
		{
			_tcscpy(m_szDevIDNO, szDevIDNO);
			return GPS_OK;
		}
	}
	else
	{
		return GPS_FALSE;
	}
}

int CVoiceTalkback::StopTalkback()
{
	if (NULL != m_lTalkback)
	{
		NETMEDIA_TBStopTalkback(m_lTalkback);
		NETMEDIA_TBCloseTalkback(m_lTalkback); 
		m_lTalkback = NULL;
		memset(m_szDevIDNO, 0, sizeof(m_szDevIDNO));
		CloseAudioFile();
		if(m_lAudioDec)
		{
			AVDEC_CloseAudioDecoder(m_lAudioDec);
			m_lAudioDec = NULL;
		}
		return GPS_OK;
	}
	else
	{
		return GPS_FALSE;
	}
}

int CVoiceTalkback::OpenSound()
{
	if (NULL != m_lTalkback)
	{
		NETMEDIA_TBPlaySound(m_lTalkback, TRUE);
		NETMEDIA_TBSetVolume(m_lTalkback, 100);
		return GPS_OK;
	}
	else
	{
		return GPS_FALSE;
	}
}

int CVoiceTalkback::CloseSound()
{
	if (NULL != m_lTalkback)
	{
		NETMEDIA_TBPlaySound(m_lTalkback, FALSE);
		return GPS_OK;
	}
	else
	{
		return GPS_FALSE;
	}
}

void CVoiceTalkback::ChangeVolume(WORD wVolume)
{
	if (NULL != m_lTalkback)
	{
		NETMEDIA_TBSetVolume(m_lTalkback, wVolume);
	}
}

void CVoiceTalkback::SetTalkbackMsg(HWND hTback, UINT uiMsg)
{
	m_hTalkHwnd =  hTback;
	m_uiTalkMsg = uiMsg;
}

void CVoiceTalkback::FUNTalkbackMsgCB(int nMsg, void* pUsr)
{
	CVoiceTalkback* pThis = (CVoiceTalkback*)pUsr;
	pThis->DoTalkbackMsg(nMsg);
}

void CVoiceTalkback::DoTalkbackMsg(int nMsg)
{
	if (m_hTalkHwnd)
	{		
		PostMessage(m_hTalkHwnd, m_uiTalkMsg, nMsg, NULL);
	}
}

BOOL CVoiceTalkback::IsTalkback() 
{ 
	return (m_lTalkback != NULL) ? TRUE : FALSE ; 
} 

BOOL CVoiceTalkback::CheckDevTalkback(LPCTSTR szDevIDNO)
{
	if (0 == _tcscmp(m_szDevIDNO, szDevIDNO))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CVoiceTalkback::FUNAudioDataCB(const char* pFrameBuf, int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp, void* pUsr)
{
	CVoiceTalkback* pThis = (CVoiceTalkback*)pUsr;
	pThis->DoAudioData(pFrameBuf, nFrameLen, nFrameType, llFrameStamp);
}

typedef struct tagFrameHdr
{
	int		nFrameType;
	int		nFrameLen;
	unsigned __int64 llStamp;
}FrameHdr_S;
void CVoiceTalkback::DoAudioData(const char* pFrameBuf, int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp)
{
	if (m_lAudioDec == NULL)
	{
		AVDEC_OpenAudioDecoder(AVDEC_GetDecHandle(), &m_lAudioDec);
	}

	char szTmpBuf[10240] = {0};
	memset(szTmpBuf, 0, 10240);
	int nTmpBuf = 10240;
	if (0 == nFrameType)
	{
		//WriteAudioData(pFrameBuf+sizeof(FrameHdr_S), nFrameLen - sizeof(FrameHdr_S));
		AVDEC_AudioDecoderFrame(m_lAudioDec, (char*)pFrameBuf+28, nFrameLen, szTmpBuf, &nTmpBuf);
	}
	else
	{
		AVDEC_AudioDecoderHead(m_lAudioDec, (char*)pFrameBuf, nFrameLen);
	}
}

void CVoiceTalkback::OpenAudioFile()
{
	m_pFile = _tfopen(_T("H:\\123"), _T("wb+"));

}

void CVoiceTalkback::CloseAudioFile()
{
	if(m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
}

void CVoiceTalkback::WriteAudioData(const char* pBuf, int nLen)
{
	if (m_pFile)
	{
		fwrite(pBuf+8, 1, nLen-8, m_pFile);
	}
}