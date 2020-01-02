// DevStatus.cpp: implementation of the CDevStatus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "clientdemo.h"
#include "DevStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDevStatus::CDevStatus()
{
//	m_pVehiRunning = gVehiRunning.Alloc();
	m_pVehiRunning = new GPSVehicleState_S;
	memset(m_pVehiRunning, 0, sizeof(GPSVehicleState_S));
	m_nSurplusDay = 0;
	m_bUpdateRunning = TRUE;
	m_bFirstGPS = TRUE;
// 	m_nJingDu = 0;
// 	m_nWeiDu = 0;
}

CDevStatus::~CDevStatus()
{
	//gVehiRunning.Free(m_pVehiRunning);
	SAFE_DELETE_OBJECT(m_pVehiRunning);
}

BOOL CDevStatus::UpdateVehiRunning(const GPSVehicleState_S* pRunning, BOOL bBigTime)
{
	BOOL bRet = FALSE;
	if (m_bFirstGPS == FALSE && bBigTime && m_pVehiRunning)
	{
		if(1 == CompareGPSTimeEx(pRunning->Gps.Time, m_pVehiRunning->Gps.Time))
		{
			*m_pVehiRunning = *pRunning;
			bRet = TRUE;
		}
	}
	else
	{
		*m_pVehiRunning = *pRunning;
		if(IsValidGPS(m_pVehiRunning->Gps))
		{
// 			m_nJingDu = m_pVehiRunning->Gps.nJingDu;
// 			m_nWeiDu = m_pVehiRunning->Gps.nWeiDu;
		}
		bRet = TRUE;
	}

	if(bRet)
	{
	//	CGpsConvert::GetInstance()->GPSConvert(&m_VehiRunning);
		m_bUpdateRunning = TRUE;
	}
	return bRet;
}

const GPSVehicleState_S* CDevStatus::GetVehiRunning()
{
	return m_pVehiRunning;
}
BOOL CDevStatus::IsUpdateVehiRunning()
{
	return m_bUpdateRunning;
}
void CDevStatus::SetUpdateVehiRunning(BOOL bUpdateRunning)
{
	m_bUpdateRunning = FALSE;
}

BOOL CDevStatus::NeverOnline()
{
	if(m_pVehiRunning)
	{
		GPSVehicleGps_S& Gps = m_pVehiRunning->Gps;
		static const int GPS_TIME_LENGTH = sizeof(Gps.Time);
		char szTemp[MAX_PATH] = {0};
		if (0 == memcmp( (char*)(&Gps) + GPS_TIME_LENGTH, szTemp, GPS_VEHICLE_GPS_LENGTH - GPS_TIME_LENGTH))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CDevStatus::IsVehiRunningValid()
{
	BOOL bRet = FALSE;
	if(m_pVehiRunning)
	{
		if (NeverOnline())
		{
			bRet = FALSE;
		}
		else
		{
			bRet = (m_pVehiRunning->Gps.Time.ucYear != 0 && m_pVehiRunning->Gps.Time.ucMonth != 0) ? TRUE : FALSE;
		}		
	}
	return bRet;
}

int CDevStatus::GetDevStatus()
{
	return 0;
}

int CDevStatus::GetChannelStatus(int nChannel)
{
	return 0;
}

SYSTEMTIME AddMonth(SYSTEMTIME& tm, unsigned int nMonth)
{
	while(nMonth--)
	{
		tm.wMonth += 1;
		if(tm.wMonth > 12)
		{
			tm.wYear += 1;
			tm.wMonth = 1;
		}
	}
	return tm;
}
