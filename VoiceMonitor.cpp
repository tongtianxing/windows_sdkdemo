// VoiceMonitor.cpp: implementation of the CVoiceMonitor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoiceMonitor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVoiceMonitor* CVoiceMonitor::g_pVoiceMonitor = NULL;

CVoiceMonitor* VOICEMonitor()
{
	if (NULL == CVoiceMonitor::g_pVoiceMonitor)
	{
		CVoiceMonitor::g_pVoiceMonitor = new CVoiceMonitor;
	}
	return CVoiceMonitor::g_pVoiceMonitor;
}

void DELMonitor()
{
	SAFE_DELETE_OBJECT(CVoiceMonitor::g_pVoiceMonitor);
}

CVoiceMonitor::CVoiceMonitor()
{
	m_lMonitor = NULL;
	m_hMonitorHwnd = NULL;
	m_uiMonitorMsg = 0;
	m_nMonitorDevID = 0;
	m_nMonitorChan = -1;
}

CVoiceMonitor::~CVoiceMonitor()
{
	StopMonitor();
}

//nDevID为设备ID，如果
int CVoiceMonitor::StartMonitor(int nDevID, int nChan /* = 0 */)
{
	if (NULL == m_lMonitor)
	{
		m_nMonitorDevID = 0;
		CDevBase* pDev = NULL;
		if (NETMEDIA_AUDIO_MIC_CHANNEL == nChan)    //如果通道为98,即直接取设备ID对应的设备就可以了，如果不是即要通过通道号找到对应设备
		{
			pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);
		}
		else
		{
			CVehicleBase* pDevice = CVehicleBaseMgr::GetInstance()->FindVechicleFromDevID(nDevID);
			if (pDevice != NULL)
			{
				pDev = pDevice->GetDevByChn(nChan);
				if (pDev != NULL)
				{
					//GetRealChn是从1开始查询，实际通道是从0开始
					nChan = pDev->GetRealChn(nChan+1);
					nChan--;
				}
			}
		}
		
		NETMEDIA_RAOpenRealAudio(pDev->GetDevIDNOForChar(), nChan, 0, NETMEDIA_CNT_TYPE_TCP
				, TRUE, &m_lMonitor);
		NETMEDIA_RASetRAudioMsgCallBack(m_lMonitor, this, FUNMonitorMsgCB);
		int nRet = NETMEDIA_RAStartRealAudio(m_lMonitor);
		if (nRet != GPS_OK)
		{
			NETMEDIA_RAStopRealAudio(m_lMonitor);
			NETMEDIA_RACloseRealAudio(m_lMonitor);	
			m_lMonitor = NULL;
			return nRet;
		}
		else
		{
//			NETMEDIA_RAPlaySound(m_lMonitor, TRUE);
			m_nMonitorDevID = nDevID;
			m_nMonitorChan = nChan;
			return GPS_OK;
		}
	}
	else
	{
		return GPS_FALSE;
	}
}

int CVoiceMonitor::StopMonitor()
{
	if (NULL != m_lMonitor)
	{
		NETMEDIA_RAStopRealAudio(m_lMonitor);
		NETMEDIA_RACloseRealAudio(m_lMonitor);	
		m_lMonitor = NULL;
		m_nMonitorDevID = 0;
		m_nMonitorChan = -1;
		return GPS_OK;
	}
	else
	{
		return GPS_FALSE;
	}
}

int CVoiceMonitor::PlayMonitorSound(long bPlay)
{
	if (NULL != m_lMonitor)
	{
		NETMEDIA_RAPlaySound(m_lMonitor, bPlay);
		
		return GPS_OK;
	}
	else
	{
		return GPS_FALSE;
	}
}

void CVoiceMonitor::SetMonitorMsg(HWND hMonitor, UINT uiMsg)
{
	m_hMonitorHwnd = hMonitor;
	m_uiMonitorMsg = uiMsg;
}

void CVoiceMonitor::ChangeVolume(WORD wVolume)
{
	if (NULL != m_lMonitor)
	{
		NETMEDIA_RASetVolume(m_lMonitor, wVolume);
	}
}

int	CVoiceMonitor::GetMonitorDevID() 
{
	return m_nMonitorDevID; 
}

BOOL CVoiceMonitor::IsMonitor() 
{ 
	return (m_lMonitor != NULL) ? TRUE : FALSE ;
} 

BOOL CVoiceMonitor::IsDevMonitor() 
{ 
	return (m_nMonitorDevID != 0) ? TRUE : FALSE; 
}

void CVoiceMonitor::FUNMonitorMsgCB(int nMsg, void* pUsr)
{
	CVoiceMonitor* pThis = (CVoiceMonitor*)pUsr;
	pThis->DoMonitorMsg(nMsg);
}

void CVoiceMonitor::DoMonitorMsg(int nMsg)
{
	if (m_hMonitorHwnd)
	{		
		PostMessage(m_hMonitorHwnd, m_uiMonitorMsg, nMsg, 0);
	}
}

BOOL CVoiceMonitor::CheckDevMonitor(int nDevID, int nChan)
{
	return (m_nMonitorDevID == nDevID && m_nMonitorChan == nChan) ? TRUE : FALSE;
}