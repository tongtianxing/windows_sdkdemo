// LoadThread.cpp: implementation of the CLoadThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoadThread.h"
#include "VDvsDevice.h"
#include "DevMoblie.h"
#include "FactoryDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoadThread::CLoadThread()
{
	m_hMsgHwnd = NULL;
	m_uiMsg = 0;
	m_bReload = FALSE;
	m_lDownHandle = NULL;
}

CLoadThread::~CLoadThread()
{
	StopDeviceLoad();
}

void CLoadThread::StartDeviceLoad(BOOL bReload)
{
	StopDeviceLoad();
	m_bReload = bReload;
	PostLoadMessage(LOAD_ING);
	NETCLIENT_DEVOpenDevDownEx(&m_lDownHandle);
	NETCLIENT_DEVRegDevDownCBEx(m_lDownHandle, this, FUNDownDevCB);
	NETCLIENT_DEVStartDevDownEx(m_lDownHandle, 0,0/*GPS_DEV_DOWN_USR_PERMIT, GPS_DEV_TYPE_ALL*/);
}

void CLoadThread::StopDeviceLoad()
{
	NETCLIENT_DEVStopDevDownEx(m_lDownHandle);
	NETCLIENT_DEVCloseDevDownEx(m_lDownHandle);
	m_lDownHandle = NULL;
	FreeDownDev();
}

void CLoadThread::FreeDownDev()
{
	mapDvsDevIter iterB = m_mapDevDevice.begin();
	mapDvsDevIter iterE = m_mapDevDevice.end();
	while(iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		SAFE_DELETE_OBJECT(pDevice);
		++ iterB;
	}
	m_mapDevDevice.clear();
	
	mapVehicleBaseIter iterVB = m_mapVehi.begin();
	mapVehicleBaseIter iterVE = m_mapVehi.end();
	while(iterVB != iterVE)
	{
		CVehicleBase* pDevice = (*iterVB).second;
		SAFE_DELETE_OBJECT(pDevice);
		++ iterVB;
	}
	m_mapVehi.clear();

	mapDevGroupIter iterGB = m_mapDevGroup.begin();
	mapDevGroupIter iterGE = m_mapDevGroup.end();
	while(iterGB != iterGE)
	{
		CVDevGroup* pDevGroup = (*iterGB).second;
		SAFE_DELETE_OBJECT(pDevGroup);
		++ iterGB;
	}
	m_mapDevGroup.clear();


}

void CLoadThread::FUNDownDevCB(int nType, void* pData, void * pUsr)
{
	CLoadThread* pThis = (CLoadThread*)pUsr;
	pThis->DoDownDevCB(nType, pData);
}

void CLoadThread::DoDownDevCB(int nType, void* pData)
{
	if (GPS_DEV_DOWN_DEV == nType) 
	{
		GPSDevInfo_S *pVehiInfo = (GPSDevInfo_S*)pData;
		CVehicleBase *pVehi = CFactoryVehicle::GetInstance()->CreateObject(pVehiInfo->nDevType);
		if (pVehi !=  NULL)
		{
			pVehi->SetDevInfo(pVehiInfo);
			m_mapVehi.insert(mapVehicleBase::value_type(pVehiInfo->szIDNO, pVehi));
			pVehi->SetVehiIDNO(pVehiInfo->szIDNO);
		}
		if (true == CSvrVer::GetInstance()->IsSvrVerV6())
		{
			GPSVehiDevRelation_S DevInfo = {0};
			//hw 2015/1/5
			ShiftGpsVehiToGpsDev(DevInfo, *pVehiInfo);
			CDevBase* pDev = CFactoryDevice::GetInstance()->CreateObject(DevInfo.nDevType);
			if (pDev != NULL)
			{
				pDev->SetDevRelationInfo(&DevInfo);
				pVehi->AddDevice(pDev);
				m_mapDevDevice.insert(mapDvsDevice::value_type(DevInfo.nID, pDev));
				m_mapIdnoDevice.insert(mapStrDevice::value_type(DevInfo.szDevIDNO, pDev));
			}
		}
	}
	else if (GPS_DEV_DOWN_GROUP == nType)
	{
		GPSDEVGroup_S* pDevGroup = (GPSDEVGroup_S*)pData;
		CVDevGroup* pGroup = new CVDevGroup;
		pGroup->SetGroupInfo(pDevGroup);
		m_mapDevGroup.insert(mapDevGroup::value_type(pDevGroup->nID, pGroup));
	}
	else if (GPS_DEV_DOWN_FAILED == nType)
	{
		PostLoadMessage(LOAD_FAILED);
	}
	else if (GPS_DEV_DOWN_SUC == nType)
	{
		if (m_bReload)
		{
			CVMgrDevice	MgrDevice;
			CVehicleBaseMgr MgrVehicle;
			MgrVehicle.UpdateVehiInfo(m_mapVehi, m_mapDevGroup);
			MgrDevice.UpdateDevInfo(m_mapDevDevice);
		}
		else
		{
			//		CVersionForDJWL::GetInstance()->FreeOldGroup(m_mapDevGroup);
			CVehicleBaseMgr::GetInstance()->UpdateVehiInfo(m_mapVehi, m_mapDevGroup);
			CVMgrDevice::GetInstance()->UpdateDevInfo(m_mapDevDevice);
		}
		PostLoadMessage(LOAD_CONFIG_SUC);
	}
	else if (GPS_DEV_DOWN_RELATION == nType)
	{
		GPSVehiDevRelation_S *pDevInfo = (GPSVehiDevRelation_S*)pData;
		mapVehicleBaseIter iterB = m_mapVehi.find(pDevInfo->szVehiIDNO);
		mapVehicleBaseIter iterE = m_mapVehi.end();
		
		if(iterB != iterE)
		{

			//hw 2015/1/6
			CVehicleBase* pVehi = (*iterB).second;
			CDevBase* pDev = CFactoryDevice::GetInstance()->CreateObject(pDevInfo->nDevType);
			
			if (pDev != NULL)
			{
				pDev->SetDevRelationInfo(pDevInfo);
				pVehi->AddDevice(pDev);
				m_mapDevDevice.insert(mapDvsDevice::value_type(pDevInfo->nID, pDev));
				m_mapIdnoDevice.insert(mapStrDevice::value_type(pDevInfo->szDevIDNO, pDev));
			}
			iterB ++;
		}
	}
}

void CLoadThread::PostLoadMessage(WPARAM wParam, LPARAM lParam)
{
	if (m_hMsgHwnd)
	{
		::PostMessage(m_hMsgHwnd, m_uiMsg, wParam, lParam);
	}
}
