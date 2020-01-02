// VehicleBase.cpp: implementation of the CVehicleBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "clientdemo.h"
#include "VehicleBase.h"
#include "DevBase.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CVehicleBase, CObject)

CVehicleBase::CVehicleBase()
{
	memset(&m_DevInfo, 0, sizeof(m_DevInfo));
	m_bAlarm = FALSE;
	m_lRegCount = 0;
	m_nGPSFailCount = 0;
	m_dBegTime = 0;
	m_bReGPS = TRUE;
	m_nGPSDevID = 0;
	memset(m_szVehiIDNO, 0, sizeof(m_szVehiIDNO));
	m_strGPSAddress = _T("");
	m_strCity = _T("");
	m_bParseAddressing = FALSE;
	m_nParseAddressFailed = 0;
	m_nParseAddressJingDu = 0;
	m_nParseAddressWeiDu = 0;
	m_curVehicleState = 2;
	memset(&m_GPSState, 0, sizeof(m_GPSState));
}

CVehicleBase::~CVehicleBase()
{

}

GPSDevInfo_S* CVehicleBase::GetDeviceInfo()
{
	return &m_DevInfo;
}
void CVehicleBase::SetDevInfo(const GPSDevInfo_S* pDevInfo)
{
	m_DevInfo = *pDevInfo;
}
void CVehicleBase::UpdateDevInfo(const GPSDEVDevInfo_S* pDevInfo)
{
	CAutoLock lock(m_LockDevice);
	GPSDevInfo_S NewDevInfo = m_DevInfo;
	strncpy(NewDevInfo.szName, pDevInfo->szName, sizeof(NewDevInfo.szName));
	strncpy(NewDevInfo.strRemark, pDevInfo->szVehiUse, sizeof(NewDevInfo.strRemark));
	NewDevInfo.ucChanNum = pDevInfo->ucChanNum;
	NewDevInfo.nDevType = pDevInfo->nType;
	strncpy(NewDevInfo.szSIMCard, pDevInfo->szSIMCard, sizeof(NewDevInfo.szSIMCard));
	
	int i = 0;
	if (pDevInfo->nType == GPS_DEV_TYPE_MDVR)
	{
		NewDevInfo.gDVRInfo.ucIoInNum = pDevInfo->ucIoInNum;
		NewDevInfo.gDVRInfo.ucTempSensorNum = pDevInfo->ucTempSensorNum;
		for ( i = 0; i < GPS_MAX_DEV_CHN_NUM; ++i)
		{
			strncpy(NewDevInfo.gDVRInfo.szChnName[i], pDevInfo->szChnName[i], sizeof(NewDevInfo.gDVRInfo.szChnName[i]));
		}
		for ( i = 0; i < 4; ++i)
		{
			strncpy(NewDevInfo.gDVRInfo.szIoInExtent[i], pDevInfo->szIoInExtent[i], sizeof(NewDevInfo.gDVRInfo.szIoInExtent[i]));
		}
		for ( i = 0; i < GPS_MAX_DEV_IO_NUM_OLD; ++i)
		{
			strncpy(NewDevInfo.gDVRInfo.szIoInName[i], pDevInfo->szIoInName[i], sizeof(NewDevInfo.gDVRInfo.szIoInName[i]));
		}
		for ( i = 0; i < GPS_MAX_TEMP_SENSOR_NUM; ++i)
		{
			strncpy(NewDevInfo.gDVRInfo.szTempSensorName[i], pDevInfo->szTempSensorName[i], sizeof(NewDevInfo.gDVRInfo.szTempSensorName[i]));
		}
		strncpy(NewDevInfo.gDVRInfo.szVehiColor, pDevInfo->szVehiColor, sizeof(NewDevInfo.gDVRInfo.szVehiColor));
		strncpy(NewDevInfo.gDVRInfo.szVehiBand, pDevInfo->szVehiBand, sizeof(NewDevInfo.gDVRInfo.szVehiBand));
		strncpy(NewDevInfo.gDVRInfo.szVehiType, pDevInfo->szVehiType, sizeof(NewDevInfo.gDVRInfo.szVehiType));
		strncpy(NewDevInfo.gDVRInfo.szVehiUse, pDevInfo->szVehiUse, sizeof(NewDevInfo.gDVRInfo.szVehiUse));
		strncpy(NewDevInfo.gDVRInfo.szVehiCampany, pDevInfo->szVehiCampany, sizeof(NewDevInfo.gDVRInfo.szVehiCampany));
		strncpy(NewDevInfo.gDVRInfo.szDriverName, pDevInfo->szDriverName, sizeof(NewDevInfo.gDVRInfo.szDriverName));
		strncpy(NewDevInfo.gDVRInfo.szDriverTele, pDevInfo->szDriverTele, sizeof(NewDevInfo.gDVRInfo.szDriverTele));
		strncpy(NewDevInfo.gDVRInfo.szReserve, pDevInfo->szDriverTele, sizeof(NewDevInfo.gDVRInfo.szReserve));
	}
	else if (pDevInfo->nType == GPS_DEV_TYPE_DVR)
	{
		NewDevInfo.DVSInfo.ucIoInNum = pDevInfo->ucIoInNum;
		NewDevInfo.DVSInfo.ucTempSensorNum = pDevInfo->ucTempSensorNum;
		for ( i = 0; i < GPS_MAX_DEV_CHN_NUM; ++i)
		{
			strncpy(NewDevInfo.DVSInfo.szChnName[i], pDevInfo->szChnName[i], sizeof(NewDevInfo.DVSInfo.szChnName[i]));
		}
		for ( i = 0; i < GPS_MAX_DEV_IO_NUM_OLD; ++i)
		{
			strncpy(NewDevInfo.DVSInfo.szIoInName[i], pDevInfo->szIoInName[i], sizeof(NewDevInfo.DVSInfo.szIoInName[i]));
		}
		for ( i = 0; i < 4; ++i)
		{
			strncpy(NewDevInfo.DVSInfo.szIoInName[i+GPS_MAX_DEV_IO_NUM_OLD], pDevInfo->szIoInExtent[i], sizeof(NewDevInfo.DVSInfo.szIoInName[i+GPS_MAX_DEV_IO_NUM_OLD]));
		}
		for ( i = 0; i < GPS_MAX_TEMP_SENSOR_NUM; ++i)
		{
			strncpy(NewDevInfo.DVSInfo.szTempSensorName[i], pDevInfo->szTempSensorName[i], sizeof(NewDevInfo.DVSInfo.szTempSensorName[i]));
		}
		strncpy(NewDevInfo.gDVRInfo.szDriverName, pDevInfo->szDriverName, sizeof(NewDevInfo.DVSInfo.szContactName));
		strncpy(NewDevInfo.gDVRInfo.szDriverTele, pDevInfo->szDriverTele, sizeof(NewDevInfo.DVSInfo.szContactTel));
	}
	NewDevInfo.nGroup = pDevInfo->nGroup;
	NewDevInfo.nOnline = pDevInfo->nOnline;
	NewDevInfo.uiModule = pDevInfo->uiModule;
	NewDevInfo.ucIcon = pDevInfo->ucIcon;
	
	NewDevInfo.cPayEnable = pDevInfo->cPayEnable;
	NewDevInfo.cPayPeriod = pDevInfo->cPayPeriod;
	NewDevInfo.cPayMonth = pDevInfo->cPayMonth;
	NewDevInfo.cPayDelayDay = pDevInfo->cPayDelayDay;
	NewDevInfo.uiPayBegin = pDevInfo->uiPayBegin;
	
	m_DevInfo = NewDevInfo;
	//xxxxxxxxxxxx
	//	m_DevStatus.SetDevInfo(&m_DevInfo);
}

BOOL CVehicleBase::GetOnline()
{
	//return m_DevInfo.nOnline; 
	BOOL bRet = FALSE;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while (iterE !=  iterB)
	{
		if ((*iterB)->GetOnline())
		{
			bRet = TRUE;
			break;
		}
		iterB ++;
	}
	return bRet;
}

void CVehicleBase::SetOnline(BOOL bOnline) 
{
	CDevBase* pDev = GetMainDevice();
	if (pDev)
	{
		pDev->SetOnline(bOnline);
	}
	//m_DevInfo.nOnline = bOnline;
}

CString	CVehicleBase::GetShowName() 
{
	CString strName;
	if (CSvrVer::GetInstance()->IsSvrVerV7())
	{

		const int nLen1 = sizeof(m_DevInfo.szIDNO);
		const int nLen2 = sizeof(m_DevInfo.strRemark);
		const int nLen3 = nLen1 + nLen2;
		char szGroup[nLen3] = {0};
		if (strlen(m_DevInfo.strRemark) > 0)
		{
			memcpy(szGroup, m_DevInfo.szIDNO, nLen1-1);
			memcpy(szGroup+nLen1-1, m_DevInfo.strRemark, nLen2);
		}
		else
		{
			memcpy(szGroup, m_DevInfo.szIDNO, nLen1-1);
		}
		const int nLen = 2*sizeof(szGroup);
		WCHAR szIDNOW[nLen] = {0};
		Utf8ToUcs(szGroup, szIDNOW, nLen);
		strName = szIDNOW;
	}
	else
	{
		{
			const int nLen1 = sizeof(m_DevInfo.szName);
			const int nLen2 = sizeof(m_DevInfo.strRemark);
			const int nLen3 = nLen1 + nLen2;
			char szGroup[nLen3] = {0};
			if (strlen(m_DevInfo.strRemark) > 0)
			{
				memcpy(szGroup, m_DevInfo.szName, nLen1-1);
				memcpy(szGroup+nLen1-1, m_DevInfo.strRemark, nLen2);
			}
			else
			{
				memcpy(szGroup, m_DevInfo.szName, nLen1-1);
			}
// 			const int nLen = 2*sizeof(szGroup);
// 			TCHAR szIDNOW[nLen] = {0};
// #ifdef _UNICODE
// 			Utf8ToUcs(szGroup, szIDNOW, nLen);
// #else
// 			Utf8ToAnsi(szGroup, szIDNOW, nLen);
// #endif
			strName = szGroup;
		}
	}
	
	return strName;
	
}


CString	CVehicleBase::GetDevIDNO() 
{
	CString strDevID;
	if (CSvrVer::GetInstance()->IsSvrVerV7())
	{
		strDevID = GetMainDevice()->GetShowName();
	}
	else
	{
		strDevID = GetMainDevice()->GetDevIDNO();
	}
	return strDevID;
}

char* CVehicleBase::GetVehicleIDNOForChar()
{
	return m_szVehiIDNO;
}

int	CVehicleBase::GetID()
{
	return m_DevInfo.nID; 
}
int	CVehicleBase::GetChannelNum()
{
	return m_DevInfo.ucChanNum;
}

CString CVehicleBase::GetChnName(UINT nChn)
{
	CString strChannelName = _T("");
	{
		if (true == CSvrVer::GetInstance()->IsSvrVerV6() && GPS_DEV_TYPE_DVR == m_DevInfo.nDevType)
		{
			const int nLen = 2*sizeof(m_DevInfo.DVSInfo.szChnName[nChn]);
			if(nChn < m_DevInfo.ucChanNum)
			{
#if defined(_UNICODE) || defined(UNICODE)  
				WCHAR szIDNOW[nLen] = {0};
				Utf8ToUcs(m_DevInfo.DVSInfo.szChnName[nChn], szIDNOW, nLen);
				strChannelName = szIDNOW;	
#else
				char szIDNOW[nLen] = {0};
				Utf8ToAnsi(m_DevInfo.DVSInfo.szChnName[nChn], szIDNOW, nLen);
				strChannelName = szIDNOW;
#endif
			}
		}
		else
		{
			const int nLen = 2*sizeof(m_DevInfo.gDVRInfo.szChnName[nChn]);
			if(nChn < m_DevInfo.ucChanNum)
			{
#if defined(_UNICODE) || defined(UNICODE)  
				WCHAR szIDNOW[nLen] = {0};
				Utf8ToUcs(m_DevInfo.gDVRInfo.szChnName[nChn], szIDNOW, nLen);
				strChannelName = szIDNOW;	
#else
				char szIDNOW[nLen] = {0};
				Utf8ToAnsi(m_DevInfo.gDVRInfo.szChnName[nChn], szIDNOW, nLen);
				strChannelName = szIDNOW;
#endif
			}
		}
	}
	if (strChannelName.IsEmpty())
	{
		strChannelName.Format(_T("%s%d"), LOADSTRINGEX(ID_STR_CHANNEL), nChn+1);
	}
	return strChannelName;
}

CString CVehicleBase::GetSIMCar()
{
	CString str;
	CDevBase* pDev = GetMainDevice();
	if (pDev)
	{
		str = pDev->GetSIMCar();
	}
	return str;
}

int CVehicleBase::GetDevType()
{
	return m_DevInfo.nDevType;
}

int CVehicleBase::GetDevSubType()
{
	return m_DevInfo.nDevSubType;
}

int CVehicleBase::GetIcon()
{
	return m_DevInfo.ucIcon;
}
int CVehicleBase::GetGroup()
{
	return m_DevInfo.nGroup;	
}

void CVehicleBase::SetGroup(int nParentID)
{
	m_DevInfo.nGroup = nParentID;
}

CString CVehicleBase::GetRemark()
{
	{
		const int nLen = 2*sizeof(m_DevInfo.strRemark);
#if defined(_UNICODE) || defined(UNICODE)  
		WCHAR szIDNOW[nLen] = {0};
		Utf8ToUcs(m_DevInfo.strRemark, szIDNOW, nLen);
		return szIDNOW;	
#else
		char szIDNOW[nLen] = {0}; 
		Utf8ToAnsi(m_DevInfo.strRemark, szIDNOW, nLen);
		return szIDNOW; 
#endif
	}
}

CString CVehicleBase::GetIOInName(UINT nIO)
{
	CString strIOName = _T("");
	{
		const int nLen = 2*sizeof(m_DevInfo.gDVRInfo.szIoInName[nIO]);
#if defined(_UNICODE) || defined(UNICODE)  
		WCHAR szIDNOW[nLen] = {0};
		if(nIO < GPS_MAX_DEV_IO_NUM_OLD)
		{
			Utf8ToUcs(m_DevInfo.gDVRInfo.szIoInName[nIO], szIDNOW, nLen);
			strIOName = szIDNOW;
		} 
		else if (nIO >= GPS_MAX_DEV_IO_NUM_OLD && nIO <= GPS_MAX_DEV_IO_NUM_NEW)
		{
			Utf8ToUcs(m_DevInfo.gDVRInfo.szIoInExtent[nIO - GPS_MAX_DEV_IO_NUM_OLD], szIDNOW, nLen);
			strIOName = szIDNOW;
		}
#else
		char szIDNOW[nLen] = {0};
		if(nIO < GPS_MAX_DEV_IO_NUM_OLD)
		{
			Utf8ToAnsi(m_DevInfo.gDVRInfo.szIoInName[nIO], szIDNOW, nLen);
			strIOName = szIDNOW;
		} 
		else if (nIO >= GPS_MAX_DEV_IO_NUM_OLD && nIO <= GPS_MAX_DEV_IO_NUM_NEW)
		{
			Utf8ToAnsi(m_DevInfo.gDVRInfo.szIoInName[nIO - GPS_MAX_DEV_IO_NUM_OLD], szIDNOW, nLen);
			strIOName = szIDNOW;
		}
#endif
	}
	
	if (strIOName.IsEmpty())
	{
		strIOName.Format(_T("%s %d"), _T("IO_"), nIO+1);
	}
	return strIOName;
}

int CVehicleBase::GetIOInNumber()
{
	return m_DevInfo.gDVRInfo.ucIoInNum;
}

CString CVehicleBase::GetTempSensorName(UINT nTempSensor)
{
	CString strChannelName = _T("");
	{
		const int nLen = 2*sizeof(m_DevInfo.gDVRInfo.szTempSensorName[nTempSensor]);
		if(nTempSensor < m_DevInfo.gDVRInfo.ucTempSensorNum)
		{
#if defined(_UNICODE) || defined(UNICODE)  
			WCHAR szIDNOW[nLen] = {0};
			Utf8ToUcs(m_DevInfo.gDVRInfo.szTempSensorName[nTempSensor], szIDNOW, nLen);
			strChannelName = szIDNOW;	
#else
			char szIDNOW[nLen] = {0};
			Utf8ToAnsi(m_DevInfo.gDVRInfo.szTempSensorName[nTempSensor], szIDNOW, nLen);
			strChannelName = szIDNOW;
#endif
		}
	}
	
	if (strChannelName.IsEmpty())
	{
		strChannelName.Format(_T("%s%d"), LOADSTRINGEX(ID_STR_DLG_TRACK_TMP), nTempSensor+1);
	}
	
	return strChannelName;
}

CString CVehicleBase::GetDriverName()
{
	CString str = _T("");
	{
		const int nLen = 2*sizeof(m_DevInfo.gDVRInfo.szDriverName);
#if defined(_UNICODE) || defined(UNICODE)  
		WCHAR szIDNOW[nLen] = {0};
		Utf8ToUcs(m_DevInfo.gDVRInfo.szDriverName, szIDNOW, nLen);
		str = szIDNOW;	
#else
		char szIDNOW[nLen] = {0};
		Utf8ToAnsi(m_DevInfo.gDVRInfo.szDriverName, szIDNOW, nLen);
		str = szIDNOW;
#endif
	}
	
	return str;
}

CString CVehicleBase::GetTel()
{
	CString str = _T("");
	{
		const int nLen = 2*sizeof(m_DevInfo.gDVRInfo.szDriverTele);
#if defined(_UNICODE) || defined(UNICODE)  
		WCHAR szIDNOW[nLen] = {0};
		Utf8ToUcs(m_DevInfo.gDVRInfo.szDriverTele, szIDNOW, nLen);
		str = szIDNOW;
#else
		char szIDNOW[nLen] = {0};
		Utf8ToAnsi(m_DevInfo.gDVRInfo.szDriverTele, szIDNOW, nLen);
		str = szIDNOW;
#endif
	}
	
	return str;
}

/////////////////////////////////////////////////////////////////////////////////

BOOL	CVehicleBase::UpdateVehiRunning(const GPSVehicleState_S* pRunning, BOOL bBigTime)
{
	m_DevStatus.UpdateVehiRunning(pRunning, bBigTime);
	BOOL bRet = FALSE;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while (iterB != iterE)
	{
		CDevBase* pDevice = (*iterB);
		if (stricmp(pDevice->GetDevIDNOForChar(), pRunning->szDevIDNO) == 0)
		{
			bRet = TRUE;
			pDevice->UpdateVehiRunning(pRunning, bBigTime);
			break;
		}
		++ iterB;
	}
	
	return bRet;
}

const GPSVehicleState_S* CVehicleBase::GetVehiRunning()
{
	const GPSVehicleState_S* reState = m_DevStatus.GetVehiRunning();
	int nCount = GetDevCount();  
	if (nCount > 1)
	{
		CDevBase* pFristDev = NULL;
		CDevBase* pSubDev = NULL;
		lstDeviceIter iterB = m_lstDevice.begin();
		lstDeviceIter iterE = m_lstDevice.end();
		if (iterB != iterE)
		{
			pFristDev = *iterB;
			iterB ++;
			pSubDev = *iterB;
		}
		if ((pFristDev != NULL)&&(pSubDev != NULL))
		{
			const GPSVehicleState_S* pFristGps = pFristDev->GetVehiRunning();
			const GPSVehicleState_S* pSubGps = pSubDev->GetVehiRunning();
			if ((pFristDev->GetOnline() && pSubDev->GetOnline())
				||(!pFristDev->GetOnline() && !pSubDev->GetOnline()))
			{
				
				if ((IsValidGPS(pFristGps->Gps)&&IsValidGPS(pSubGps->Gps))
					||(!IsValidGPS(pFristGps->Gps)&&!IsValidGPS(pSubGps->Gps))
					)
				{
					if (CompareGPSTimeEx(pFristGps->Gps.Time, pSubGps->Gps.Time) == -1)
					{
						reState =  pSubGps;
					}
					else
					{
						reState = pFristGps;
					}
				}
				else
				{
					
					if (IsValidGPS(pSubGps->Gps))
					{
						reState =  pSubGps;
					}
					else
					{
						reState =  pFristGps;
					}
					
				}
			}
			else
			{
				if (pFristDev->GetOnline()&&IsValidGPS(pFristGps->Gps))
				{
					reState = pFristGps;
				}
				else if (pSubDev->GetOnline()&&IsValidGPS(pSubGps->Gps))	
				{
					reState = pSubGps;
				}
				else if (IsValidGPS(pFristGps->Gps))
				{
					reState = pFristGps;
				}
				else if (IsValidGPS(pSubGps->Gps))
				{
					reState = pSubGps;
				}
			}
		}
	}
	
	return reState;
}

GPSTime_S CVehicleBase::GetVehiTime()
{
	const GPSVehicleState_S* reState = m_DevStatus.GetVehiRunning();
	GPSTime_S gpsTime = reState->Gps.Time;
	int nCount = GetDevCount();
	if (nCount > 1)
	{
		CDevBase* pFristDev = NULL;
		CDevBase* pSubDev = NULL;
		lstDeviceIter iterB = m_lstDevice.begin();
		lstDeviceIter iterE = m_lstDevice.end();
		if (iterB != iterE)
		{
			pFristDev = *iterB;
			iterB ++;
			pSubDev = *iterB;
		}
		
		if ((pFristDev != NULL)&&(pSubDev != NULL))
		{
			const GPSVehicleState_S* pFristGps = pFristDev->GetVehiRunning();
			const GPSVehicleState_S* pSubGps = pSubDev->GetVehiRunning();
			if ((pFristDev->GetOnline()&&pSubDev->GetOnline())
				||(!pFristDev->GetOnline()&&!pSubDev->GetOnline()))
			{
				if (CompareGPSTimeEx(pFristGps->Gps.Time, pSubGps->Gps.Time) == -1)
				{
					gpsTime = pSubGps->Gps.Time;
				}
			}
			else
			{
				if (pSubDev->GetOnline())
				{
					gpsTime = pSubGps->Gps.Time;
				}
			}
		}
	}
	return gpsTime;
}

BOOL CVehicleBase::IsUpdateVehiRunning()
{
	return m_DevStatus.IsUpdateVehiRunning();
}
void CVehicleBase::SetUpdateVehiRunning(BOOL bUpdateRunning)
{
	m_DevStatus.SetUpdateVehiRunning(bUpdateRunning);
}
BOOL CVehicleBase::IsVehiRunningValid()
{
	return m_DevStatus.IsVehiRunningValid();
}
const GPSVehicleState_S* CVehicleBase::GetVehiInitialStatus()
{
	return m_DevStatus.GetVehiRunning();
}
void CVehicleBase::SetVehiFixGPS(int nMapValid, int nMapType, int nJingdu, int nWeidu)
{
	m_DevInfo.ucMapValid = nMapValid;
	m_DevInfo.ucMapType = nMapType;
	m_DevInfo.nJingDu = nJingdu;
	m_DevInfo.nWeiDu = nWeidu;
}
/////////////////////////////////////////////////////////////////////////////////

void CVehicleBase::SetGPSAddress(const CString& strGPSAddress)
{
	m_strGPSAddress = strGPSAddress;
}

CString CVehicleBase::GetGPSAddress()
{
	CString strAddress;
	if (IsValidLastGPS(m_DevStatus.GetVehiRunning()->Gps))
	{
		strAddress = LOADSTRINGEX(ID_STR_DIRECTION_INVALID);
	}
	else
	{
		strAddress = m_strGPSAddress;
		if(strAddress.IsEmpty())
		{
			strAddress = FormatGPSToStr(m_DevStatus.GetVehiRunning()->Gps);
		}
	}
	
	return strAddress;
}

BOOL CVehicleBase::IsParseAddressing()
{
	return m_bParseAddressing;
}
void CVehicleBase::SetParseAddressState(BOOL bParseAddressing)
{
	m_bParseAddressing = bParseAddressing;
}
void CVehicleBase::SetParseAddressSuc(BOOL bSuc)
{
	if (bSuc)
	{
		m_nParseAddressFailed = 0;
	}
	else
	{
		++m_nParseAddressFailed;
		if (m_nParseAddressFailed >= 3)
		{
			m_strGPSAddress = _T("");
		}
	}
}


bool CVehicleBase::GetParseAddressSuc()
{
	return m_nParseAddressFailed > 0 ? false : true;
}
void CVehicleBase::SetParseAddressGps(int nJingDu, int nWeiDu)
{
	m_nParseAddressJingDu = nJingDu;
	m_nParseAddressWeiDu = nWeiDu;
}
bool CVehicleBase::IsParseAddressGpsSame(int nJingDu, int nWeiDu)
{
	if (m_nParseAddressJingDu != nJingDu || m_nParseAddressWeiDu != nWeiDu)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CVehicleBase::ParseCurGPS()
{
// 	const GPSVehicleState_S* pRunning = m_DevStatus.GetVehiRunning();
// 	if(pRunning)
// 	{
// 		if(CGPSAddreeParseManager::GetInstance()->AddGPSAddressParse(FUNParseAddressCB, this, GetID()
// 			, pRunning->Gps.nJingDu, pRunning->Gps.nWeiDu) == FALSE)
// 		{
// 			SetParseAddressState(FALSE);
// 		}
// 	}
}
void CVehicleBase::FUNParseAddressCB(BOOL bSuc, LPCTSTR szAddress, LPCTSTR szCity, long lUserData, void* pUsr)
{
	CVehicleBase* pThis = (CVehicleBase*)pUsr;
	pThis->DoParseAddressCB(bSuc, szAddress, szCity, lUserData);
}
void CVehicleBase::DoParseAddressCB(BOOL bSuc, LPCTSTR szAddress, LPCTSTR szCity, long lUserData)
{
	{
		BOOL bValid = bSuc && _tcsclen(szAddress) > 0 ? TRUE : FALSE;
		if (bValid)
		{
			SetGPSAddress(szAddress);
		}
		SetParseAddressState(FALSE);
		SetParseAddressSuc(bValid);
	}
}
	///////////////////////////////
void CVehicleBase::SetAlarm(BOOL bAlarm)
{
	m_bAlarm = bAlarm;
}

BOOL CVehicleBase::GetAlarm()	
{	
	return m_bAlarm; 
}

void	CVehicleBase::AddDevice(CDevBase* pDev)
{
	CDevBase* pNewDev = CVMgrDevice::S_CopyDevice(pDev);		
	CAutoLock lock(m_LockDevice);
	m_lstDevice.push_back(pNewDev);
}

void	CVehicleBase::DelDevice(CDevBase* pDev)
{
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iTer = m_lstDevice.begin();
	lstDeviceIter iTerE = m_lstDevice.end();
	while(iTer != iTerE)
	{
		if (((*iTer)->GetID()) == (pDev->GetID()))
		{
			SAFE_DELETE_OBJECT((*iTer));
			m_lstDevice.erase(iTer);
			break;
		}
		iTer++;
	}
}

void CVehicleBase::SetUpDateDeviceList(lstDevice lstDev)
{
	m_lstDevice.clear();
	m_lstDevice = lstDev;
}

void	CVehicleBase::ClearDevice()
{
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		CDevBase* pDevice = *iterB;
		/*SAFE_DELETE_OBJECT(pDevice);*/
		if (pDevice)
		{
			SAFE_DELETE_OBJECT(pDevice);
		}
		// 		delete pDevice;
		// 		pDevice = NULL;
		++ iterB;
	}
	m_lstDevice.clear();
}

lstDevice CVehicleBase::GetDevList() const
{
	return m_lstDevice;
}

CDevBase* CVehicleBase::GetDevice(const char* lpDevIDNO)
{
	USES_CONVERSION;
	CDevBase* pDev = NULL;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB !=  iterE)
	{
		if (strcmp((*iterB)->GetIDNOForChar(), lpDevIDNO) == 0)
		{
			pDev = *iterB;
			break;
		}
		iterB++;
	}
	
	return pDev;
}

CDevBase* CVehicleBase::GetMainDevice()
{
	CAutoLock lock(m_LockDevice);
	CDevBase* pDev = NULL;
	if (m_lstDevice.size() > 0)
	{

		lstDeviceIter iterB = m_lstDevice.begin();
		lstDeviceIter iterE = m_lstDevice.end();
		while(iterB !=  iterE)
		{
			if ((*iterB)->IsMainDev())
			{
				pDev = *iterB;
				break;
			}
			iterB++;
		}
		if (NULL == pDev)
		{
			pDev = *(m_lstDevice.begin());
		}
	}

	return pDev;
}

CDevBase* CVehicleBase::GetDevByChn(int nChn)
{
	CDevBase* pDev = NULL;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB !=  iterE)
	{
		CDevBase* pTmp = *iterB;
		if (pTmp && pTmp->IsExistMoudleChn(nChn+1))
		{
			pDev = pTmp;
			break;
		}
		iterB++;
	}
	
	return pDev;
}

CDevBase* CVehicleBase::GetDevByIOOut(int nIO)
{
	CDevBase* pDev = NULL;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB !=  iterE)
	{
		CDevBase* pTmp = *iterB;
		if (pTmp && pTmp->IsExistMoudleIOOut(nIO))
		{
			pDev = pTmp;
			break;
		}
		iterB++;
	}
	
	return pDev;
}
CDevBase* CVehicleBase::GetDevByIOIn(int nIO)
{
	CDevBase* pDev = NULL;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB !=  iterE)
	{
		CDevBase* pTmp = *iterB;
		if (pTmp && pTmp->IsExistMoudleIOIn(nIO))
		{
			pDev = pTmp;
			break;
		}
		iterB++;
	}
	
	return pDev;
}

CDevBase* CVehicleBase::GetDevByID(const int& nID)
{
	USES_CONVERSION;
	CDevBase* pDev = NULL;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB !=  iterE)
	{
		if ((*iterB)->GetID() == nID)
		{
			pDev = *iterB;
			break;
		}
		iterB++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GetDevWithGPS()
{
	CAutoLock lock(m_LockDevice);
	CDevBase* pDevice = NULL;
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	if (iterB != iterE)
	{
		if (m_lstDevice.size() == 2)
		{
			pDevice = *iterB;
			if (pDevice->IsExistMoudleVideo())
			{
				iterB++;
				pDevice = *iterB;
			}
		}
		else 
		{
			pDevice = *iterB;
		}
	}
	return pDevice;
}



char*	CVehicleBase::GetMainDevIDNO()
{
	return GetMainDevice()->GetIDNOForChar();
}
int CVehicleBase::GetMainDevID()
{
	return GetMainDevice()->GetID();
}

int CVehicleBase::GetDevCount()
{
	return m_lstDevice.size();
}


void CVehicleBase::SetVehiState(const int nState)
{
	m_curVehicleState = nState;
}
int CVehicleBase::GetVehiState() const
{
	return m_curVehicleState;
}

CDevBase* CVehicleBase::GetOtherInTwoDev(const CDevBase* pDev)
{
	int nCount = GetDevCount();
	ASSERT((nCount>1)&&(pDev != NULL));
	CDevBase* pOtherDev = NULL;
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while (iterB != iterE)
	{
		if (*iterB != pDev)
		{
			pOtherDev = *iterB;
		}
	}
	
	return pOtherDev;
}

BOOL CVehicleBase::GetALLDevIsSame()
{
	BOOL bSame = TRUE;
	if (GetDevCount() > 1)
	{
		lstDeviceIter iterB = m_lstDevice.begin();
		lstDeviceIter iterE = m_lstDevice.end();
		bool bVedio = (*iterB)->IsExistMoudleVideo();
		iterB++;
		while(iterE != iterB)
		{
			if (bVedio != (*iterB)->IsExistMoudleVideo())
			{
				bSame = FALSE;
				break;
			}
			iterB++;
		}
	}
	return bSame;
}

CDevBase* CVehicleBase::GetDevWithVedio()
{
	CDevBase *pDev = NULL;
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		if ((*iterB)->IsExistMoudleVideo())
		{
			pDev = *iterB;
		}
		iterB++;
	}
	
	return pDev;
}

CDevBase* CVehicleBase::GetDevWithoutVedio()
{
	CDevBase *pDev = NULL;
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		if (!(*iterB)->IsExistMoudleVideo())
		{
			pDev = *iterB;
		}
		iterB++;
	}
	
	return pDev;
}

CDevBase* CVehicleBase::GetDevByNum(int nNum)
{
	CDevBase* pDev = NULL;
	int nIndex = 1;
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		if (nIndex == nNum)
		{
			pDev = *iterB;
		}
		nIndex++;
		iterB++;
	}
	return pDev;
}

bool CVehicleBase::IsExistMoudleVideo()
{
	bool bRet = false;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		if ((*iterB)->IsExistMoudleVideo())
		{
			bRet = true;
			break;
		}
		iterB ++;
	}
	return bRet;
	
	//return GetMainDevice()->IsExistMoudleVideo();
}

bool CVehicleBase::IsExistMoudleSnapshot()
{
	/*return GetMainDevice()->IsExistMoudleSnapshot();*/
	bool bRet = false;
// 	lstDeviceIter lstDevB = m_lstDevice.begin();
// 	lstDeviceIter lstDevE = m_lstDevice.end();
// 	while(lstDevE != lstDevB)
// 	{
// 		if ((*lstDevB)->IsExistMoudleSnapshot())
// 		{
// 			bRet = true;
// 		}
// 		lstDevB++;
// 	}
	if (GetChannelNum() > 0)
	{
		bRet = true;
	}
	return bRet;
}

bool CVehicleBase::IsExistMoudleMonitor()
{

	bool bRet = false;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		if ((*iterB)->IsExistMoudleMonitor())
		{
			bRet = true;
			break;
		}
		iterB ++;
	}
	return bRet;

	//return GetMainDevice()->IsExistMoudleMonitor();
}

bool CVehicleBase::IsExistMoudleTalkback()
{
	bool bRet = false;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		if ((*iterB)->IsExistMoudleTalkback())
		{
			bRet = true;
			break;
		}
		iterB ++;
	}
	return bRet;
	//return GetMainDevice()->IsExistMoudleTalkback();
}

bool CVehicleBase::IsExistModuleTTS()
{
	bool bRet = false;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		if ((*iterB)->IsExistModuleTTS())
		{
			bRet = true;
		}
		iterB ++;
	}
	return bRet;
}

bool CVehicleBase::IsExistModuleOilCtrl()
{
	CDevBase* pDev = GetMainDevice();
	return GetMainDevice()->IsExistModuleOilCtrl();
}

bool CVehicleBase::IsExistModulePowerCtrl()
{
	return GetMainDevice()->IsExistModulePowerCtrl();
}

bool CVehicleBase::IsExistModuleBKTalk()
{
	bool bRet = false;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		if ((*iterB)->IsExistModuleBKTalk())
		{
			bRet = true;
			break;
		}
		iterB ++;
	}
	return bRet;

	//return GetMainDevice()->IsExistModuleBKTalk();
}

bool CVehicleBase::IsExistModuleOilSen()
{
	return GetMainDevice()->IsExistModuleOilSen();
}

bool CVehicleBase::IsExistMoudleChn(UINT nChn)
{
	return GetMainDevice()->IsExistMoudleChn(nChn);
}

bool CVehicleBase::IsExistMoudleIOIn(UINT nIO)
{
	return GetMainDevice()->IsExistMoudleIOIn(nIO);
}

bool CVehicleBase::IsExistMoudleIOOut(UINT nIO)
{
	return GetMainDevice()->IsExistMoudleIOOut(nIO);
}

bool CVehicleBase::IsExistMoudleODB()
{
	bool bRet = false;
	CAutoLock lock(m_LockDevice);
	lstDeviceIter iterB = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iterB != iterE)
	{
		if ((*iterB)->IsExistMoudleODB())
		{
			bRet = true;
			break;
		}
		iterB ++;
	}
	return bRet;
}

CDevBase* CVehicleBase::GetMoudleVideoDev()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistMoudleVideo())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GetMoudleSnapshot()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistMoudleSnapshot())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GetMoudleMonitor()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistMoudleMonitor())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GetMoudleTalkback()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistMoudleTalkback())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GettModuleTTS()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistModuleTTS())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GetModuleOilCtrl()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistModuleOilCtrl())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GetModulePowerCtrl()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistModulePowerCtrl())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GetModuleBKTalk()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistModuleBKTalk())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GetModuleOilSen()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistModuleOilSen())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

CDevBase* CVehicleBase::GetDevWithModulePeople()
{
	CDevBase* pDev = NULL;
	lstDeviceIter iter = m_lstDevice.begin();
	lstDeviceIter iterE = m_lstDevice.end();
	while(iter != iterE)
	{
		if ((*iter)->IsExistMoudleCountPeople())
		{
			pDev = *iter;
			break;
		}
		iter ++;
	}
	return pDev;
}

