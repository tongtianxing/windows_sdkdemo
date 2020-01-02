// VMgrDevice.cpp: implementation of the CVMgrDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VDvsDevice.h"
//#include "VideoRecord.h"
//#include "DevCtrl.h"
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

CVMgrDevice*	CVMgrDevice::g_DevMgr = NULL;

CVMgrDevice*	CVMgrDevice::GetInstance()
{
	if (NULL == g_DevMgr)
	{
		g_DevMgr = new CVMgrDevice;
	}
	return g_DevMgr;
}

void CVMgrDevice::DelInstance()
{
	if (g_DevMgr)
	{
		delete g_DevMgr;
		g_DevMgr = NULL;
	}
}
CVMgrDevice::CVMgrDevice()
{
}

CVMgrDevice::~CVMgrDevice()
{
	FreeDevInfo();
}

BOOL CVMgrDevice::FreeDvsDevice(mapDvsDevice& DvsDevice)
{
	CAutoLock	m_cs(m_LockDvsDev);
	mapDvsDevIter iterB = DvsDevice.begin();
	mapDvsDevIter iterE = DvsDevice.end();
	while(iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		SAFE_DELETE_OBJECT(pDevice);
		++ iterB;
	}
	DvsDevice.clear();
	return TRUE;
}

BOOL CVMgrDevice::FreeDevGroup(mapDevGroup& DevGroup)
{
	CAutoLock	cs(m_LockDvsDev);
	mapDevGroupIter iterB = DevGroup.begin();
	mapDevGroupIter iterE = DevGroup.end();
	while(iterB != iterE)
	{
		CVDevGroup* pDevGroup = (*iterB).second;
		SAFE_DELETE_OBJECT(pDevGroup);
		++ iterB;
	}
	DevGroup.clear();
	return TRUE;
}

void CVMgrDevice::ClearDevNoExist(mapDvsDevice& mapDev)
{
	mapDvsDevIter IterB = m_mapDvsDevice.begin();
	mapDvsDevIter IterE = m_mapDvsDevice.end();
	while (IterB != IterE)
	{
		CDevBase* pDevice = (*IterB).second;
		mapDvsDevIter iterF = mapDev.find(pDevice->GetID());
		if (iterF == mapDev.end())
		{
			mapDvsDevIter iterTemp = IterB;
			++ IterB;
			SAFE_DELETE_OBJECT(pDevice);
			m_mapDvsDevice.erase(iterTemp);
		}
		else
		{
			++ IterB;
		}
	}
}

BOOL CVMgrDevice::FreeDevInfo()
{
	FreeDvsDevice(m_mapDvsDevice);
	FreeDevGroup(m_mapDevGroup);
	return TRUE;
}

CDevBase* CVMgrDevice::FindDvsDeviceByIDNO(const CString& strIDNO)
{
	CAutoLock	cs(m_LockDvsDev);
	mapDvsDevIter iterB = m_mapDvsDevice.begin();
	mapDvsDevIter iterE = m_mapDvsDevice.end();
	while (iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		CString strTemp = pDevice->GetDevIDNO();
		if (strTemp == strIDNO)
		{
			return (*iterB).second;
		}
		++ iterB;
	}
	return NULL;
}

CDevBase* CVMgrDevice::FindDvsDeviceByID(int nID)
{
	CAutoLock	cs(m_LockDvsDev);
	mapDvsDevIter iterB = m_mapDvsDevice.find(nID);
	mapDvsDevIter iterE = m_mapDvsDevice.end();
	if (iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		return pDevice;
	}
	else
	{
		return NULL;
	}
}

CVDevGroup* CVMgrDevice::FindDvsGroupByID(int nID)
{
	CAutoLock	cs(m_LockDvsDev);
	mapDevGroupIter iterB = m_mapDevGroup.find(nID);
	mapDevGroupIter iterE = m_mapDevGroup.end();
	if (iterB != iterE)
	{
		CVDevGroup* pGroup = (*iterB).second;
		return pGroup;
	}
	else
	{
		return NULL;
	}
}
// BOOL CVMgrDevice::GetUnRegDevice(int nUnRegGroup)
// {
// 	mapDvsDevIter iterB = m_mapDvsDevice.begin();
// 	mapDvsDevIter iterE = m_mapDvsDevice.end();
// 	while (iterB != iterE)
// 	{
// 		CDevBase* pDevice = (*iterB).second;
// 		if (pDevice->GetGroup() == nUnRegGroup)
// 		{
// 			return TRUE;
// 		}
// 		++ iterB;
// 	}
// 	return FALSE;
// }

void CVMgrDevice::UpdateDevInfo(mapDvsDevice& Device)
{
	CAutoLock lock(m_LockDvsDev);
	//Update
	if (m_nAddCount == 0)
	{
		mapDvsDevIter IterB = Device.begin();
		mapDvsDevIter IterE = Device.end();
		while (IterB != IterE)
		{
			CDevBase* pDevice = (*IterB).second;
			
			CDevBase* pNewDevInfo = S_CopyDevice(pDevice);
			m_mapDvsDevice.insert(mapDvsDevice::value_type(pDevice->GetID(), pNewDevInfo));
			
			++ IterB;
		}
		m_nAddCount ++;
	}
	else
	{
		/*FreeDevice(m_mapDevice);*/
		ClearDevNoExist(Device);
		mapDvsDevIter IterB = Device.begin();
		mapDvsDevIter IterE = Device.end();
		while (IterB != IterE)
		{
			CDevBase* pDevice = (*IterB).second;
			mapDvsDevIter iterF = m_mapDvsDevice.find(pDevice->GetID());
			if (iterF == m_mapDvsDevice.end())
			{
				//Add
				CDevBase* pNewDevInfo = S_CopyDevice(pDevice);
				////////////////////////////////////////////////
				m_mapDvsDevice.insert(mapDvsDevice::value_type(pNewDevInfo->GetID(), pNewDevInfo));
			}
			else
			{
				//Update
				((*iterF).second)->SetDevRelationInfo(pDevice->GetDevRelationInfo());
				////////////////////////////////////////////////////////////////
				((*iterF).second)->UpdateVehiRunning(pDevice->GetVehiRunning(), TRUE);
				((*iterF).second)->SetOnline(pDevice->GetOnline());
			}
			++ IterB;
		}
	}
	m_mapStrDevice.clear();
	//Delete
	mapDvsDevIter IterB = m_mapDvsDevice.begin();
	mapDvsDevIter IterE = m_mapDvsDevice.end();
	while (IterB != IterE)
	{
		CDevBase* pDevice = (*IterB).second;
		mapDvsDevIter iterF = Device.find(pDevice->GetID());
		if (iterF == Device.end())
		{
			mapDvsDevIter iterTemp = IterB;
			++ IterB;
			SAFE_DELETE_OBJECT(pDevice);
			m_mapDvsDevice.erase(iterTemp);
		}
		else
		{
			m_mapStrDevice.insert(mapStrDevice::value_type(pDevice->GetIDNOForChar(), pDevice));
			++ IterB;
		}
	}
}

BOOL CVMgrDevice::GetGroupInfo(int nGroupID, GPSDEVGroup_S& DEVGroup, mapIDIRDEVGroup& ParentGroup, mapIDIRDEVGroup& ChildGroup)
{
	CAutoLock	m_cs(m_LockDvsDev);
	mapDevGroupIter iter = m_mapDevGroup.find(nGroupID);
	mapDevGroupIter iterE = m_mapDevGroup.end();
	if (iter != iterE)
	{
		DEVGroup = *(((*iter).second)->GetGroupInfo());
		
		int nParent = DEVGroup.nParent;
		iter = m_mapDevGroup.find(nParent);
		while (iter != iterE)
		{
			CVDevGroup* pGroup = ((*iter).second);
			ParentGroup.insert( mapIDIRDEVGroup::value_type(pGroup->GetGroupInfo()->nID, *(pGroup->GetGroupInfo())) );
			nParent = pGroup->GetGroupInfo()->nParent;
			iter = m_mapDevGroup.find(nParent);
		}

		mapIDIRDEVGroup TempAllGroup;
		mapIDIRDEVGroup TempClildGroup;
		iter = m_mapDevGroup.begin();
		while (iter != iterE)
		{
			CVDevGroup* pGroup = ((*iter).second);
			if (pGroup->GetGroupInfo()->nParent == nGroupID)
			{
				ChildGroup.insert( mapIDIRDEVGroup::value_type(pGroup->GetGroupInfo()->nID, *(pGroup->GetGroupInfo())) );
				TempClildGroup.insert( mapIDIRDEVGroup::value_type(pGroup->GetGroupInfo()->nID, *(pGroup->GetGroupInfo())) );
			}
			else
			{
				int nTempGroup = pGroup->GetGroupInfo()->nID;
				if (ParentGroup.find(nTempGroup) == ParentGroup.end())
				{
					TempAllGroup.insert( mapIDIRDEVGroup::value_type(pGroup->GetGroupInfo()->nID, *(pGroup->GetGroupInfo())) );
				}
			}
			++ iter;
		}
		
		mapIDIRGroupIter Giter = TempClildGroup.begin();
		mapIDIRGroupIter GiterE = TempClildGroup.end();
		while (Giter != GiterE)
		{
			GetChildGroup( (*Giter).second.nID, TempAllGroup, ChildGroup);
			++ Giter;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int CVMgrDevice::GetGroup(mapDevGroup& mapGroup)
{
	mapGroup = m_mapDevGroup;
	return mapGroup.size();
}

// void CVMgrDevice::GetGroupDevEx(int nGroupID, mapIDIRDEVGroup& mapGroup, mapIDIRDEVInfo& mapDev)
// {
// 	CAutoLock	m_cs(m_LockDvsDev);
// 	mapDvsDevIter iterB = m_mapDvsDevice.begin();
// 	mapDvsDevIter iterE = m_mapDvsDevice.end();
// 	while(iterB != iterE)
// 	{
// 		CDevBase* pDevice = (*iterB).second;
// 		int nTempGroup = pDevice->GetGroup();
// 		if (nGroupID == nTempGroup || mapGroup.find(nTempGroup) != mapGroup.end())
// 		{
// 			if (pDevice->GetOnline() == TRUE)  
// 			{
// 				GPSDevInfo_S DevInfo = *(pDevice->GetDeviceInfo());
// 			    mapDev.insert(mapIDIRDEVInfo::value_type(pDevice->GetID(), DevInfo));
// 			}			
// 		}
// 		++ iterB;
// 	}
// }
// void CVMgrDevice::GetGroupDev(int nGroupID, mapIDIRDEVInfo& mapDev)
// {
// 	CAutoLock	m_cs(m_LockDvsDev);
// 	mapDvsDevIter iterB = m_mapDvsDevice.begin();
// 	mapDvsDevIter iterE = m_mapDvsDevice.end();
// 	while(iterB != iterE)
// 	{
// 		CDevBase* pDevice = (*iterB).second;
// 		int nTempGroup = pDevice->GetGroup();
// 		if (nGroupID == nTempGroup)
// 		{
// 			GPSDevInfo_S DevInfo = *(pDevice->GetDeviceInfo());
// 			mapDev.insert(mapIDIRDEVInfo::value_type(pDevice->GetID(), DevInfo));
// 		}
// 		++ iterB;
// 	}
// }
// void CVMgrDevice::GetGroupDev(int nGroupID, mapIDIRDEVGroup& mapGroup, mapIDIRDEVInfo& mapDev)
// {
// 	CAutoLock	m_cs(m_LockDvsDev);
// 	mapDvsDevIter iterB = m_mapDvsDevice.begin();
// 	mapDvsDevIter iterE = m_mapDvsDevice.end();
// 	while(iterB != iterE)
// 	{
// 		CDevBase* pDevice = (*iterB).second;
// 		int nTempGroup = pDevice->GetGroup();
// 		if (nGroupID == nTempGroup || mapGroup.find(nTempGroup) != mapGroup.end())
// 		{
// 			GPSDevInfo_S DevInfo = *(pDevice->GetDeviceInfo());
// 			mapDev.insert(mapIDIRDEVInfo::value_type(pDevice->GetID(), DevInfo));
// 		}
// 		++ iterB;
// 	}
// }

void CVMgrDevice::GetChildGroup(int nParentID, mapIDIRDEVGroup& AllGroup, mapIDIRDEVGroup& ChildGroup)
{
	mapIDIRDEVGroup TempGroup;
	mapIDIRGroupIter iter = AllGroup.begin();
	mapIDIRGroupIter iterE = AllGroup.end();
	while (iter != iterE)
	{
		mapIDIRGroupIter iterTemp = iter;
		++ iter;
		if (((*iterTemp).second).nParent == nParentID)
		{
			ChildGroup.insert(mapIDIRDEVGroup::value_type(((*iterTemp).second).nID, ((*iterTemp).second)));
			TempGroup.insert(mapIDIRDEVGroup::value_type(((*iterTemp).second).nID, ((*iterTemp).second)));
			AllGroup.erase(iterTemp);
		}
	}

	iter = TempGroup.begin();
	iterE = TempGroup.end();
	while (iter != iterE)
	{
		GetChildGroup( (*iter).second.nID, AllGroup, ChildGroup);
		++ iter;
	}
}
void CVMgrDevice::GetChildGroup(int nParentID, mapIDIRDEVGroup& ChildGroup)
{
	mapDevGroupIter iter = m_mapDevGroup.begin();
	mapDevGroupIter iterE = m_mapDevGroup.end();
	CVDevGroup* pGroup = NULL;
	while (iter != iterE)
	{
		GPSDEVGroup_S Group = {0};
		pGroup = (*iter).second;
		if (pGroup->GetGroupInfo()->nParent == nParentID)
		{
			Group = *(pGroup->GetGroupInfo());
			ChildGroup.insert(mapIDIRDEVGroup::value_type(Group.nID, Group));
		}
		++ iter;
	}
}
int CVMgrDevice::GetAllOnlineDev(mapIDIRDEVInfo& mapDevInof, BOOL bOnline)
{
	CAutoLock	m_cs(m_LockDvsDev);
	mapDvsDevIter iterB = m_mapDvsDevice.begin();
	mapDvsDevIter iterE = m_mapDvsDevice.end();
	while(iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		if (pDevice->GetOnline() == bOnline)
		{
			GPSDevInfo_S DevInfo = *(pDevice->GetDeviceInfo());
			mapDevInof.insert(mapIDIRDEVInfo::value_type(pDevice->GetID(), DevInfo));
		}
		++ iterB;
	}

	return mapDevInof.size();
}

int	CVMgrDevice::GetAllOnlineDev(mapDvsDevice& mapDev, BOOL bOnline)
{
	CAutoLock	m_cs(m_LockDvsDev);
	mapDvsDevIter iterB = m_mapDvsDevice.begin();
	mapDvsDevIter iterE = m_mapDvsDevice.end();
	while(iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		if (pDevice->GetOnline() == bOnline)
		{
			mapDev.insert(mapDvsDevice::value_type(pDevice->GetID(), pDevice));
		}
		++ iterB;
	}
	
	return mapDev.size();
}

int CVMgrDevice::GetAllDev(mapIDIRDEVInfo& mapDev)
{
	CAutoLock	m_cs(m_LockDvsDev);
	mapDvsDevIter iterB = m_mapDvsDevice.begin();
	mapDvsDevIter iterE = m_mapDvsDevice.end();
	while(iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		GPSDevInfo_S DevInfo = *(pDevice->GetDeviceInfo());
		mapDev.insert(mapIDIRDEVInfo::value_type(pDevice->GetID(), DevInfo));
		++ iterB;
	}
	return mapDev.size();
}

int CVMgrDevice::GetAllDevMap(mapDvsDevice& mapDev)
{
	mapDev = m_mapDvsDevice;
	return mapDev.size();
}
void CVMgrDevice::GetAllDev(GPSDeviceIDNO_S** ppDevice, int& nCount)
{
	CAutoLock	m_cs(m_LockDvsDev);
	nCount = m_mapDvsDevice.size();
	if (nCount > 0)
	{
		*ppDevice = new GPSDeviceIDNO_S[nCount];
		int nIndex = 0;
		GPSDeviceIDNO_S* pDevice = *ppDevice;
		mapDvsDevIter iterB = m_mapDvsDevice.begin();
		mapDvsDevIter iterE = m_mapDvsDevice.end();
		while(iterB != iterE)
		{
			CDevBase* pDvsDevice = (*iterB).second;
			strncpy(pDevice[nIndex].szDevIDNO, CStringA(pDvsDevice->GetDevIDNO()), sizeof(pDevice[nIndex].szDevIDNO) - 1);
			++ nIndex;
			++ iterB;
		}
		nCount = nIndex;
	}
}

//modify 2012.1.4
void CVMgrDevice::GetOnlineDev(mapIDIRDEVInfo& mapDev, int iMaxCount)
{
	CAutoLock	m_cs(m_LockDvsDev);
	mapDvsDevIter iterB = m_mapDvsDevice.begin();
	mapDvsDevIter iterE = m_mapDvsDevice.end();
	while(iterB != iterE && mapDev.size() < iMaxCount)
	{
		CDevBase* pDevice = (*iterB).second;
		if (pDevice->GetOnline())
		{
			GPSDevInfo_S DevInfo = *(pDevice->GetDeviceInfo());
			mapDev.insert(mapIDIRDEVInfo::value_type(pDevice->GetID(), DevInfo));
		}
		++ iterB;
	}
}

void CVMgrDevice::PasteDevice(CVMgrDevice& DestDevice)
{
	CAutoLock	m_cs(m_LockDvsDev);
	mapDvsDevIter iterB = m_mapDvsDevice.begin();
	mapDvsDevIter iterE = m_mapDvsDevice.end();
	while(iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		CDevBase* pNewDevice = CFactoryDevice::GetInstance()->CreateObject(pDevice->GetDevType());
		pNewDevice->SetDevInfo(pDevice->GetDeviceInfo());
		pNewDevice->SetOnline(pDevice->GetOnline());
		pNewDevice->SetAlarm(pDevice->GetAlarm());
		DestDevice.m_mapDvsDevice.insert(mapDvsDevice::value_type(pDevice->GetID(), pNewDevice));
		++ iterB;
	}
	
	mapDevGroupIter iterGB = m_mapDevGroup.begin();
	mapDevGroupIter iterGE = m_mapDevGroup.end();
	while(iterGB != iterGE)
	{
		CVDevGroup* pGroup = (*iterGB).second;
		CVDevGroup* pNewGroup = new CVDevGroup;
		pNewGroup->SetGroupInfo(pGroup->GetGroupInfo());
		DestDevice.m_mapDevGroup.insert(mapDevGroup::value_type(pGroup->GetGroupInfo()->nID, pNewGroup));
		++ iterGB;
	}
}

void CVMgrDevice::MergeDevInfo(CVMgrDevice* pNewMgrDevice)
{
	UpdateDevInfo(pNewMgrDevice->m_mapDvsDevice);
}

void CVMgrDevice::SearchDevice(const CString& strDev, mapIDIRDEVInfo& mapDev)
{
	CAutoLock	m_cs(m_LockDvsDev);
	mapDvsDevIter iterB = m_mapDvsDevice.begin();
	mapDvsDevIter iterE = m_mapDvsDevice.end();
	while(iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		CString strName = pDevice->GetShowName();

		//Add lyong
		CString strDevID = pDevice->GetDevIDNO();

		if (-1 != strName.Find(strDev))
		{
			mapDev.insert(mapIDIRDEVInfo::value_type(pDevice->GetID(), *(pDevice->GetDeviceInfo())));
		}
		else if (-1 != strDevID.Find(strDev))
		{
			mapDev.insert(mapIDIRDEVInfo::value_type(pDevice->GetID(), *(pDevice->GetDeviceInfo())));
		}	
		++ iterB;
	}
}

void CVMgrDevice::UpdateMgrMapDvsDevice(GPSDevInfo_S* pBaseInfo)
{
	CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(pBaseInfo->szIDNO);
	if (pDevice)
	{
		pDevice->SetDevInfo(pBaseInfo);
	}
}

int	CVMgrDevice::GetDeviceNum()
{
	return m_mapDvsDevice.size();
}
int	CVMgrDevice::GetOnlineDeviceNum()
{
	CAutoLock lock(m_LockDvsDev);
	int nOnlineDevNum = 0;
	mapDvsDevIter iterB = m_mapDvsDevice.begin();
	mapDvsDevIter iterE = m_mapDvsDevice.end();
	while(iterB != iterE)
	{
		CDevBase* pDevice = (*iterB).second;
		if (pDevice)
		{
			if(pDevice->GetOnline())
				++nOnlineDevNum;
		}
		++ iterB;
	}	
	return nOnlineDevNum;
}

CDevBase* CVMgrDevice::S_CopyDevice(CDevBase* pDevice)
{
	CDevBase* pNewDevInfo = CFactoryDevice::GetInstance()->CreateObject(pDevice->GetDevType());
	pNewDevInfo->SetDevRelationInfo(pDevice->GetDevRelationInfo());
	pNewDevInfo->SetOnline(pDevice->GetOnline());
	pNewDevInfo->UpdateVehiRunning(pDevice->GetVehiRunning(), TRUE);
	return pNewDevInfo;
}