// SubVehiStatus.cpp: implementation of the CSubVehiStatus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "clientdemo.h"
#include "SubVehiStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSubVehiStatus::CSubVehiStatus()
{
}

CSubVehiStatus::~CSubVehiStatus()
{

}


void CSubVehiStatus::StartWork()
{
	NETCLIENT_VSOpenVehiStatus(&m_lVehi);
	NETCLIENT_VSSetStatusCB(m_lVehi, this, FUNVehiStatusCB);
	NETCLIENT_VSStartVSChan(m_lVehi);
}

void CSubVehiStatus::StopWork()
{
	NETCLIENT_VSSetStatusCB(m_lVehi, NULL, NULL);
	NETCLIENT_VSStopVSChan(m_lVehi);
	NETCLIENT_VSCloseVehiStatus(m_lVehi);	
	m_lVehi = NULL;
}

void CSubVehiStatus::UpdateDevice(GPSDeviceIDNO_S* pDevice, int nCount)
{
	NETCLIENT_VSSetStatusDevice(m_lVehi, pDevice, nCount);
}

void CSubVehiStatus::FUNVehiStatusCB(GPSVehicleState_S* pVehiRun, char* pOnline, int nCount, void* pUsr)
{
	CSubVehiStatus* pThis = (CSubVehiStatus*)pUsr;
	pThis->DoVehiStatus(pVehiRun, pOnline, nCount);
}

void CSubVehiStatus::DoVehiStatus(GPSVehicleState_S* pVehiRun, char* pOnline, int nCount)
{
	DeviceStatusChange_S* pStatus = new DeviceStatusChange_S;
	pStatus->pVehiRun = new GPSVehicleState_S[nCount];
	pStatus->pOnline = new char[nCount];
	pStatus->nCount = nCount;
	for (int i = 0; i < nCount; ++ i)
	{
		pStatus->pVehiRun[i] = pVehiRun[i];
		pStatus->pOnline[i] = pOnline[i];
	}
	
	if (!PostMessage(m_hWnd, m_nMsg, DLG_CTRL_MSG_DEVICE_STATUS_CHANGE, (WPARAM)pStatus))
	{
		SAFE_DELETE_ARRAY(pStatus->pVehiRun);
		SAFE_DELETE_ARRAY(pStatus->pOnline);
		SAFE_DELETE_OBJECT(pStatus);
	}
}
