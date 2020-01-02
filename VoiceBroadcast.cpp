// VoiceBroadcast.cpp: implementation of the CVoiceBroadcast class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoiceBroadcast.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVoiceBroadcast::CVoiceBroadcast()
{
	m_lVoiceCom = NULL;
	m_hVoiceHwnd = NULL;
	m_uiVoiceMsg = 0;
}

CVoiceBroadcast::~CVoiceBroadcast()
{
	StopVoiceCom();
}

int	CVoiceBroadcast::StartVoiceCom(std::list<int>& lstDev)
{
	if (NULL == m_lVoiceCom)
	{
		NETMEDIA_BCOpenBroadcast(&m_lVoiceCom);
		NETMEDIA_BCSetBroadcastMsgCallBack(m_lVoiceCom, this, FUNVoiceComMsgCB);

		std::list<int>::iterator iter = lstDev.begin();
		std::list<int>::iterator iterE = lstDev.end();
		while (iter != iterE)
		{
			CVehicleBase* pVehicle = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByID( (*iter) );
			CDevBase* pDev = pVehicle->GetMainDevice();
			NETMEDIA_BCAddDevice(m_lVoiceCom, pDev->GetIDNOForChar(), 0);
			++ iter;
		}

		int nRet = NETMEDIA_BCStartBroadcast(m_lVoiceCom);
		if (nRet != GPS_OK)
		{
			NETMEDIA_BCCloseBroadcast(m_lVoiceCom); m_lVoiceCom = NULL;
			return nRet;
		}
		else
		{

			return GPS_OK;
		}
	}
	else
	{
		return GPS_FALSE;
	}
}

int	CVoiceBroadcast::StopVoiceCom()
{
	if (NULL != m_lVoiceCom)
	{
		NETMEDIA_BCStopBroadcast(m_lVoiceCom);
		NETMEDIA_BCCloseBroadcast(m_lVoiceCom);
		m_lVoiceCom = NULL;
		return GPS_OK;
	}
	else
	{
		return GPS_FALSE;
	}
}

BOOL CVoiceBroadcast::IsBroadcast()
{
	return (m_lVoiceCom != NULL) ? TRUE : FALSE;
}

void CVoiceBroadcast::FUNVoiceComMsgCB(int nMsg, void* pUsr)
{
	CVoiceBroadcast* pThis = (CVoiceBroadcast*)pUsr;
	pThis->DoVoiceComMsg(nMsg);
}

void CVoiceBroadcast::DoVoiceComMsg(int nMsg)
{
	if (m_hVoiceHwnd)
	{		
		PostMessage(m_hVoiceHwnd, m_uiVoiceMsg, nMsg, 0);
	}
}

void CVoiceBroadcast::SetVoiceMsg(HWND hVoice, UINT uiMsg)
{
	m_hVoiceHwnd = hVoice;
	m_uiVoiceMsg = uiMsg;
}
