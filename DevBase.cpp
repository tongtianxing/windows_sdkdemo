// DevBase.cpp: implementation of the CDevBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DevBase.h"
//#include "GpsConvert.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDevBase, CObject)

CDevBase::CDevBase()
{
	/*memset(&m_VehiRunning, 0, sizeof(m_VehiRunning));*/
	m_bAlarm = FALSE;
	m_lRegCount = 0;
	m_strGPSAddress = "";
	m_bParseAddressing = FALSE;
	m_nParseAddressFailed = 0;
	m_nParseAddressJingDu = 0;
	m_nParseAddressWeiDu = 0;
	memset(&m_DevRalationInfo, 0, sizeof(m_DevRalationInfo));
}

CDevBase::~CDevBase()
{

}

BOOL CDevBase::GetOnline()
{
	return m_DevRalationInfo.nOnline; 
}
void CDevBase::SetOnline(BOOL bOnline) 
{
	m_DevRalationInfo.nOnline = bOnline;
}
CString	CDevBase::GetShowName() 
{	
	CVehicleBase* pVehicle = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByIDNO(m_DevRalationInfo.szVehiIDNO);
	CString strShowName = _T("");
	if (pVehicle != NULL)
	{
		strShowName = pVehicle->GetShowName();
	}
	
	return strShowName;
}

CString	CDevBase::GetDevIDNO() 
{
	return CString(m_DevRalationInfo.szDevIDNO);
}
char* CDevBase::GetDevIDNOForChar()
{
	return m_DevRalationInfo.szDevIDNO;
}

int	CDevBase::GetID()
{
	return m_DevRalationInfo.nID; 
}
int	CDevBase::GetChannelNum()
{
	return m_mapChn.size();
}

CString CDevBase::GetChnName(UINT nChn)
{
	int nVehicleChn = nChn;
	CVehicleBase* pVehicle = NULL;
	if (CSvrVer::GetInstance()->IsSvrVerV7())
	{
		pVehicle = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByIDNO(m_DevRalationInfo.szVehiIDNO);
	}
	else
	{
		pVehicle = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByIDNO(m_DevRalationInfo.szDevIDNO);
	}
	ASSERT(pVehicle);
	if (IsMainDev() == false)
	{
		nVehicleChn += pVehicle->GetMainDevice()->GetChannelNum();
	}
	
	return pVehicle->GetChnName(nVehicleChn);
}

CString CDevBase::GetSIMCar()
{
	CString strSIMCar = m_DevRalationInfo.szSIMCard;
	return strSIMCar;
}
// UINT CDevBase::GetModule()
// {
// 	return m_DevRalationInfo.uiModule;
// }
int CDevBase::GetDevType()
{
	return m_DevRalationInfo.nDevType;
}

int CDevBase::GetDevSubType()
{
	return m_DevRalationInfo.nDevSubType;
}

// int CDevBase::GetIcon()
// {
// 	return m_DevRalationInfo.ucIcon;
// }
// int CDevBase::GetGroup()
// {
// 	return m_DevRalationInfo.nGroup;	
// }
// CString CDevBase::GetRemark()
// {
// 	return m_DevRalationInfo.strRemark;
// }

char CDevBase::GetProtocol()
{
	return m_DevRalationInfo.cProtocol;
}


BOOL CDevBase::UpdateVehiRunning(const GPSVehicleState_S* pRunning, BOOL bBigTime)
{
	return m_DevStatus.UpdateVehiRunning(pRunning, bBigTime);
}

const GPSVehicleState_S* CDevBase::GetVehiRunning()
{
	return m_DevStatus.GetVehiRunning();
}
BOOL CDevBase::IsUpdateVehiRunning()
{
	return m_DevStatus.IsUpdateVehiRunning();
}
void CDevBase::SetUpdateVehiRunning(BOOL bUpdateRunning)
{
	m_DevStatus.SetUpdateVehiRunning(bUpdateRunning);
}
const GPSVehicleState_S* CDevBase::GetVehiInitialStatus()
{
	return m_DevStatus.GetVehiRunning();
}

void CDevBase::SetVehiFixGPS(int nMapValid, int nMapType, int nJingdu, int nWeidu)
{
	m_DevRalationInfo.ucMapValid = nMapValid;
	m_DevRalationInfo.ucMapType = nMapType;
	m_DevRalationInfo.nJingDu = nJingdu;
	m_DevRalationInfo.nWeiDu = nWeidu;
}
BOOL CDevBase::IsVehiRunningValid()
{
	return m_DevStatus.IsVehiRunningValid();	
}

void CDevBase::SetAlarm(BOOL bAlarm)
{
	m_bAlarm = bAlarm;
}

BOOL CDevBase::GetAlarm()
{
	return m_bAlarm;
}
SYSTEMTIME CDevBase::ConvertToSystemTime(const GPSTime_S& IdnTime)
{
	SYSTEMTIME tm;
	
	tm.wYear = IdnTime.ucYear + 2000;
	tm.wMonth = IdnTime.ucMonth;
	tm.wDay = IdnTime.ucDay;
	tm.wHour = IdnTime.ucHour;
	tm.wMinute = IdnTime.ucMinute;
	tm.wSecond = IdnTime.ucSecond;
	
	return tm;
}

// BOOL CDevBase::IsVehiRunningValid()
// {
// 	return (m_VehiRunning.Gps.Time.ucYear != 0 && m_VehiRunning.Gps.Time.ucMonth != 0) ? TRUE : FALSE;	
// }

void CDevBase::SetGPSAddress(const CString& strGPSAddress)
{
	m_strGPSAddress = strGPSAddress;
}
CString CDevBase::GetGPSAddress()
{
	return m_strGPSAddress;
}
BOOL CDevBase::IsParseAddressing()
{
	return m_bParseAddressing;
}
void CDevBase::SetParseAddressState(BOOL bParseAddressing)
{
	m_bParseAddressing = bParseAddressing;
}
void CDevBase::SetParseAddressSuc(BOOL bSuc)
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
			m_strGPSAddress = "";
		}
	}
}


////////////////////////////////////////////////////////////
//字符转换成整形
void StrVecToIntMap(mapInt& Int, const std::vector<std::string>& vecStr)
{
	Int.clear();
	int nValue = 0;
	for (int i = 0; i < vecStr.size(); ++i)
	{
		nValue = atoi(vecStr[i].c_str());
		Int.insert(mapInt::value_type(nValue, nValue));
	}
}
void CDevBase::UpdateMoudleInfo()
{
	std::vector<std::string> vecStr;
	STRINGSplit(m_DevRalationInfo.szChnAttr, ',', vecStr);
	StrVecToIntMap(m_mapChn, vecStr);
	vecStr.clear();

	STRINGSplit(m_DevRalationInfo.szIOInAttr, ',', vecStr);
	StrVecToIntMap(m_mapIOIn, vecStr);
	vecStr.clear();

	STRINGSplit(m_DevRalationInfo.szIOOutAttr, ',', vecStr);
	StrVecToIntMap(m_mapIOOut, vecStr);
	vecStr.clear();

}
void CDevBase::SetDevRelationInfo(const GPSVehiDevRelation_S* pInfo)
{
	m_DevRalationInfo = *pInfo;
	UpdateMoudleInfo();
}
GPSVehiDevRelation_S* CDevBase::GetDevRelationInfo()
{
	return &m_DevRalationInfo;
}

void CDevBase::UpdateDevInfo(const GPSDEVDevInfo_S* pDevInfo)
{
	
}
char* CDevBase::GetIDNOForChar()
{
	return m_DevRalationInfo.szDevIDNO;
}
bool CDevBase::IsMainDev()
{
	bool bRet = false;
	if (m_DevRalationInfo.cMainDevFlag)
	{
		bRet = true;
	}

	return bRet;
}

bool CDevBase::IsExistMoudleVideo()
{

	bool bRet = true;
	if (CSvrVer::GetInstance()->IsSvrVerV7())
	{
		bRet = IsExistMoudle(GPS_DEV_MOUDLE_VIDEO);
	}
	return bRet;
}

bool CDevBase::IsExistMoudleSnapshot()
{
	bool bRet = true;
	if (CSvrVer::GetInstance()->IsSvrVerV7())
	{
		bRet = IsExistMoudle(GPS_DEV_MOUDLE_SNAPSHOT);
	}
	return bRet;
}

bool CDevBase::IsExistMoudleMonitor()
{
	bool bRet = true;
	if (CSvrVer::GetInstance()->IsSvrVerV7())
	{
		bRet = IsExistMoudle(GPS_DEV_MOUDLE_MONITOR);
	}
	return bRet;
}

bool CDevBase::IsExistMoudleTalkback()
{
	bool bRet = true;
	if (CSvrVer::GetInstance()->IsSvrVerV7())
	{
		bRet = IsExistMoudle(GPS_DEV_MOUDLE_TALK);
	}
	return bRet;
}


bool CDevBase::IsExistModuleOilCtrl()
{
	return IsExistMoudle(GPS_DEV_MODULE_OIL_CONTROL);
}

bool CDevBase::IsExistModulePowerCtrl()
{
	return IsExistMoudle(GPS_DEV_MODULE_POWER_CONTROL);
}

bool CDevBase::IsExistModuleTTS()
{
	return IsExistMoudle(GPS_DEV_MODULE_TTS);
}

bool CDevBase::IsExistModuleBKTalk()
{
	return IsExistMoudle(GPS_DEV_MODULE_BK_TALK);
}

bool CDevBase::IsExistModuleOilSen()
{
	bool bRet = false;
	if (CSvrVer::GetInstance()->IsSvrVerV7())
	{
		bRet = IsExistMoudle(GPS_DEV_MOUDLE_OIL_SEN);
	}
	else
	{
		bRet = IsExistMoudle(GPS_DEV_MOUDLE_OIL_SEN_V6);
	}
	return bRet;
}

bool CDevBase::IsExistMoudle(int nMoudle)
{
	return BIT_GET(m_DevRalationInfo.nMoudle, nMoudle);;
}

bool CDevBase::IsExistMoudleChn(UINT nChn)
{
	return m_mapChn.find(nChn) != m_mapChn.end();
}

bool CDevBase::IsExistMoudleIOIn(UINT nIO)
{
	return m_mapIOIn.find(nIO) != m_mapIOIn.end();
}

bool CDevBase::IsExistMoudleIOOut(UINT nIO)
{
	return m_mapIOOut.find(nIO) != m_mapIOOut.end();
}

bool CDevBase::IsExistMoudleODB()
{
	return IsExistMoudle(GPS_DEV_MOUDLE_ODB);
}


char* CDevBase::GetVehicleForChar()
{
	return m_DevRalationInfo.szVehiIDNO;
}


int CDevBase::GetRealChn(int nChn)
{
	int reChn = -1;
	mapIntIter iter = m_mapChn.find(nChn);
#ifdef _DEBUG
	mapIntIter iterB = m_mapChn.begin();
	mapIntIter iterE = m_mapChn.end();
	while(iterB != iterE)
	{
		DEBUGTraceOutput(_T("%d-%d\n"),iterB->first, iterB->second);
		iterB++;
	}
#endif
	if (iter != m_mapChn.end())
	{
		reChn = iter->second;
	}

	return reChn;
}

bool CDevBase::IsExistMoudleCountPeople()
{
	return IsExistMoudle(GPS_DEV_MOUDLE_COUNT_PEOPLE);
}
