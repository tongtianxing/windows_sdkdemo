// SubAlarm.cpp: implementation of the CSubVehiAlarm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "clientdemo.h"
#include "SubVehiAlarm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
CSubVehiAlarm::CSubVehiAlarm()
{
}

CSubVehiAlarm::~CSubVehiAlarm()
{

}

void CSubVehiAlarm::StartWork()
{
	NETCLIENT_VAOpenVehiAlarm(&m_lVehi);
	NETCLIENT_VASetAlarmInfoCB(m_lVehi, this, FUNAlarmInfoCB);
	NETCLIENT_VAStartVAChan(m_lVehi);	
}

void CSubVehiAlarm::StopWork()
{
	NETCLIENT_VAStopVAChan(m_lVehi);
	NETCLIENT_VACloseVehiAlarm(m_lVehi);
	m_lVehi = NULL;
}

void CSubVehiAlarm::UpdateDevice(GPSDeviceIDNO_S* pDevice, int nCount)
{
	NETCLIENT_VASetAlarmDevice(m_lVehi, pDevice, nCount);
}

void CSubVehiAlarm::FUNAlarmInfoCB(const char* pAlarm, int nLength, void* pUsr)
{
	CSubVehiAlarm* pThis = (CSubVehiAlarm*)pUsr;
	pThis->DoAlarmInfo(pAlarm, nLength);
}

void CSubVehiAlarm::DoAlarmInfo(const char* pAlarm, int nLength)
{
	if (nLength < GPS_VEHICLE_ALARM_LENGTH)
	{
		return;
	}
	
	GPSVehicleAlarm_S* pVehiAlarm = (GPSVehicleAlarm_S*)pAlarm;

	if (GPS_ALARM_TYPE_DEVICE_INFO_CHANGE == pVehiAlarm->Alarm.AlarmType)
	{
		GPSDEVDevInfo_S* pBaseInfo = (GPSDEVDevInfo_S*)(pAlarm + GPS_VEHICLE_ALARM_LENGTH);
		GPSDEVDevInfo_S* pNewBaseInfo = new GPSDEVDevInfo_S;
		*pNewBaseInfo = *pBaseInfo;
		
		if (!PostMessage(m_hWnd, m_nMsg, MSG_DEVICE_INFO_CHANGE, (LPARAM)pNewBaseInfo))
		{
			SAFE_DELETE_OBJECT(pNewBaseInfo);
		}
	}
	else if (GPS_ALARM_TYPE_TRANS_PORT == pVehiAlarm->Alarm.AlarmType)
	{
		const int GPSAlarmTPD_LEN = sizeof(GPSAlarmTPD_S);
		if (nLength >= GPSAlarmTPD_LEN)
		{
			GPSAlarmTPD_S* pNewAlarm = new GPSAlarmTPD_S;
			memcpy(pNewAlarm, pAlarm, sizeof(GPSAlarmTPD_S));
			if(!PostMessage(m_hWnd, m_nMsg, MSG_DEV_TRANSPARENT_DATA, (LPARAM)pNewAlarm))
			{
				SAFE_DELETE_OBJECT(pNewAlarm);
			}
		}
	}
	else 
	{
		GPSVehicleAlarm_S* pNewAlarm = new GPSVehicleAlarm_S;
		*pNewAlarm = *pVehiAlarm;
		if (!PostMessage(m_hWnd, m_nMsg, MSG_ALARM_INFO, (LPARAM)pNewAlarm))
		{
			SAFE_DELETE_OBJECT(pNewAlarm);
		}
	}
}