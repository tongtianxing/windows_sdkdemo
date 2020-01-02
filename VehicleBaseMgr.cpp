// VMgrDevice.cpp: implementation of the CVehicleBaseMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VehicleBaseMgr.h"
#include "VMgrDevice.h"
#include "VDvsDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVehicleBaseMgr::CVehicleBaseMgr()
{
	m_nAddCount = 0;
}

CVehicleBaseMgr::~CVehicleBaseMgr()
{
	FreeDevInfo();
}

BOOL CVehicleBaseMgr::FreeDevice(mapVehicleBase& DvsDevice)
{
	CAutoLock	m_cs(m_LockDevice);
	mapVehicleBaseIter iterB = DvsDevice.begin();
	mapVehicleBaseIter iterE = DvsDevice.end();
	while(iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		SAFE_DELETE_OBJECT(pDevice);
		++ iterB;
	}
	DvsDevice.clear();
	return TRUE;
}

BOOL CVehicleBaseMgr::FreeDevGroup(mapDevGroup& DevGroup)
{
	CAutoLock	cs(m_LockDevice);
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


BOOL CVehicleBaseMgr::FreeDevInfo()
{
	FreeDevice(m_mapVehicleBase);
	FreeDevGroup(m_mapDevGroup);
	return TRUE;
}
void CVehicleBaseMgr::UpdateVehiInfo(const GPSDevInfo_S* pDevInfo, unsigned int nCount)
{
	if (pDevInfo)
	{
		CVehicleBase* pDev = NULL;
		USES_CONVERSION;
		for (unsigned int i = 0; i < nCount; ++i)
		{
			pDev = FindDvsDeviceByIDNO(pDevInfo[i].szName);
			if (NULL == pDev)
			{
				pDev = CFactoryVehicle::GetInstance()->CreateObject();
				pDev->SetDevInfo(&pDevInfo[i]);
				CAutoLock lock(m_LockDevice);
				m_mapVehicleBase.insert(mapVehicleBase::value_type(pDev->GetVehicleIDNOForChar(), pDev));
				lock.Release();
			}
			else
			{
				pDev->SetDevInfo(&pDevInfo[i]);
			}
		}
	}
}
// void CVehicleBaseMgr::UpdateDevGroup(const GPSDEVGroup_S* pGroup, unsigned int nCount)
// {
// 
// }
// void CVehicleBaseMgr::UpdateDevState(const GPSVehicleState_S* pState, unsigned int nCount)
// {
// 
// }
void CVehicleBaseMgr::ClearDevNoExist(mapVehicleBase &mapDev)
{
	mapVehicleBaseIter IterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter IterE = m_mapVehicleBase.end();
	while (IterB != IterE)
	{
		CVehicleBase* pDevice = (*IterB).second;
		mapVehicleBaseIter iterF = mapDev.end();
		iterF = mapDev.find(pDevice->GetVehicleIDNOForChar());

		if (iterF == mapDev.end())
		{
			mapVehicleBaseIter iterTemp = IterB;
			++ IterB;
			SAFE_DELETE_OBJECT(pDevice);
			m_mapVehicleBase.erase(iterTemp);
		}
		else
		{
			++ IterB;
		}
	}
}

void CVehicleBaseMgr::S_CopyVehiDevList(CVehicleBase* pNewVehiInfo, lstDevice& lstDev)
{
	pNewVehiInfo->ClearDevice();
	lstDeviceIter iter = lstDev.begin();
	lstDeviceIter iterE = lstDev.end();
	while (iter != iterE)
	{
		CDevBase* pSrcDev = (*iter);
		pNewVehiInfo->AddDevice(pSrcDev);
		++ iter;
	}
}

CVehicleBase* CVehicleBaseMgr::S_CopyVehicle(CVehicleBase* pSrc)
{
	CVehicleBase* pNewVehiInfo = CFactoryVehicle::GetInstance()->CreateObject();
	pNewVehiInfo->SetVehiIDNO(pSrc->GetVehiIDNO());
	pNewVehiInfo->SetDevInfo(pSrc->GetDeviceInfo());
	pNewVehiInfo->SetOnline(pSrc->GetOnline());
	pNewVehiInfo->UpdateVehiRunning(pSrc->GetVehiRunning(), TRUE);
	lstDevice lstDev = pSrc->GetDevList();
	S_CopyVehiDevList(pNewVehiInfo, lstDev);
	return pNewVehiInfo;
}

void CVehicleBaseMgr::UpdateVehiInfo(mapVehicleBase& Device, mapDevGroup& Group)
{
	CAutoLock lock(m_LockDevice);
	if(m_nAddCount == 0)
	{
		//Update
		mapVehicleBaseIter IterB = Device.begin();
		mapVehicleBaseIter IterE = Device.end();
		while (IterB != IterE)
		{
			CVehicleBase* pVehicle = (*IterB).second;
			CVehicleBase* pNewVehiInfo = S_CopyVehicle(pVehicle);
			m_mapVehicleBase.insert(mapVehicleBase::value_type(pVehicle->GetVehicleIDNOForChar(), pNewVehiInfo));
			++ IterB;
		}
		m_nAddCount ++;
	}
	else
	{
		/*FreeDevice(m_mapVehicleBase);*/
		ClearDevNoExist(Device);
		mapVehicleBaseIter IterB = Device.begin();
		mapVehicleBaseIter IterE = Device.end();
		while (IterB != IterE)
		{
			CVehicleBase* pVehicle = (*IterB).second;
			mapVehicleBaseIter iterF = m_mapVehicleBase.find(pVehicle->GetVehicleIDNOForChar());
			if (iterF == m_mapVehicleBase.end())	//Add
			{
				CVehicleBase* pNewVehiInfo = S_CopyVehicle(pVehicle);
				m_mapVehicleBase.insert(mapVehicleBase::value_type(pVehicle->GetVehicleIDNOForChar(), pNewVehiInfo));
			}
			else
			{
				CVehicleBase* pVehiFind = (*iterF).second;
				//Update
				pVehiFind->SetDevInfo(pVehicle->GetDeviceInfo());
				pVehiFind->UpdateVehiRunning(pVehicle->GetVehiRunning(), TRUE);
				pVehiFind->SetOnline(pVehicle->GetOnline());
				S_CopyVehiDevList(pVehiFind, pVehicle->GetDevList());
			}
			++ IterB;
		}
	}

	{
		//Update
		int nTmp = Group.size();
		mapDevGroupIter IterB = Group.begin();
		mapDevGroupIter IterE = Group.end();
		while (IterB != IterE)
		{
			CVDevGroup* pGroup = (*IterB).second;
			mapDevGroupIter iterF = m_mapDevGroup.find(pGroup->GetGroupInfo()->nID);
			if (iterF == m_mapDevGroup.end())
			{
				//Add
				CVDevGroup* pNewGroup = new CVDevGroup;
				pNewGroup->SetGroupInfo(pGroup->GetGroupInfo());
				m_mapDevGroup.insert(mapDevGroup::value_type(pNewGroup->GetGroupInfo()->nID, pNewGroup));
			}
			else
			{
				//Update
				((*iterF).second)->SetGroupInfo(pGroup->GetGroupInfo());
			}
			++ IterB;
		}

		//Delete
		IterB = m_mapDevGroup.begin();
		IterE = m_mapDevGroup.end();
		while (IterB != IterE)
		{
			CVDevGroup* pGroup = (*IterB).second;
			mapDevGroupIter iterF = Group.find(pGroup->GetGroupInfo()->nID);
			if (iterF == Group.end())
			{
				mapDevGroupIter iterTemp = IterB;
				++ IterB;
				SAFE_DELETE_OBJECT(pGroup);
				m_mapDevGroup.erase(iterTemp);
			}
			else
			{
				++ IterB;
			}
		}
	}
}


//LQJ-2014.8.21-
void CVehicleBaseMgr::UpdateVehiInfo(mapDevGroup& Group)
{
	CAutoLock lock(m_LockDevice);

	{
		//Update
		int nTmp = Group.size();
		mapDevGroupIter IterB = Group.begin();
		mapDevGroupIter IterE = Group.end();
		while (IterB != IterE)
		{
			CVDevGroup* pGroup = (*IterB).second;
			mapDevGroupIter iterF = m_mapDevGroup.find(pGroup->GetGroupInfo()->nID);
			if (iterF == m_mapDevGroup.end())
			{
				//Add
				CVDevGroup* pNewGroup = new CVDevGroup;
				pNewGroup->SetGroupInfo(pGroup->GetGroupInfo());
				m_mapDevGroup.insert(mapDevGroup::value_type(pNewGroup->GetGroupInfo()->nID, pNewGroup));
			}
			else
			{
				//Update
				((*iterF).second)->SetGroupInfo(pGroup->GetGroupInfo());
			}
			++ IterB;
		}

		//Delete
		IterB = m_mapDevGroup.begin();
		IterE = m_mapDevGroup.end();
		while (IterB != IterE)
		{
			CVDevGroup* pGroup = (*IterB).second;
			mapDevGroupIter iterF = Group.find(pGroup->GetGroupInfo()->nID);
			if (iterF == Group.end())
			{
				mapDevGroupIter iterTemp = IterB;
				++ IterB;
				SAFE_DELETE_OBJECT(pGroup);
				m_mapDevGroup.erase(iterTemp);
			}
			else
			{
				++ IterB;
			}
		}
	}
}

void CVehicleBaseMgr::MergeVehiInfo(CVehicleBaseMgr* pNewMgrDevice)
{
	UpdateVehiInfo(pNewMgrDevice->m_mapVehicleBase, pNewMgrDevice->m_mapDevGroup);
}

void CVehicleBaseMgr::PasteDevice(CVehicleBaseMgr& DestDevice)
{
	CAutoLock	m_cs(m_LockDevice);
	mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter iterE = m_mapVehicleBase.end();
	while(iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		CVehicleBase* pNewDevice = CFactoryVehicle::GetInstance()->CreateObject();
		pNewDevice->SetDevInfo(pDevice->GetDeviceInfo());
		pNewDevice->SetOnline(pDevice->GetOnline());
	//	pNewDevice->SetAlarm(pDevice->GetAlarm());
		DestDevice.m_mapVehicleBase.insert(mapVehicleBase::value_type(pDevice->GetVehicleIDNOForChar(), pNewDevice));
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

CVehicleBase* CVehicleBaseMgr::FindDvsDeviceByIDNO(const char* strIDNO)
{
	CAutoLock	cs(m_LockDevice);
	CVehicleBase* pVehicle = NULL;
	mapVehicleBaseIter iterStr = m_mapVehicleBase.find(strIDNO);
	if (iterStr != m_mapVehicleBase.end())
	{
		pVehicle = (*iterStr).second;
	}

	return pVehicle;
}

CVehicleBase* CVehicleBaseMgr::FindDvsDeviceByID(int nID)
{
	CAutoLock	cs(m_LockDevice);
	CVehicleBase* pDevice = NULL;
	CVehicleBase* pDeviceTmp = NULL;
	mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter iterE = m_mapVehicleBase.end();
	while (iterB != iterE)
	{
		pDeviceTmp = (*iterB).second;
		if(pDeviceTmp && pDeviceTmp->GetID() == nID)
		{
			pDevice = pDeviceTmp;
			break;
		}
		++iterB;
	}
	return pDevice;
}

CVDevGroup* CVehicleBaseMgr::FindDvsGroupByID(int nID)
{
	CAutoLock	cs(m_LockDevice);
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

BOOL CVehicleBaseMgr::GetGroupInfo(int nGroupID, GPSDEVGroup_S& DEVGroup, mapIDIRDEVGroup& ParentGroup, mapIDIRDEVGroup& ChildGroup)
{
	CAutoLock	m_cs(m_LockDevice);
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

int CVehicleBaseMgr::GetGroup(mapDevGroup& mapGroup)
{
	mapGroup = m_mapDevGroup;
	return mapGroup.size();
}

void CVehicleBaseMgr::GetGroupDev(int nGroupID, mapVehicleBase& mapDev)
{
	CAutoLock	m_cs(m_LockDevice);
	mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter iterE = m_mapVehicleBase.end();
	while(iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		int nTempGroup = pDevice->GetGroup();
// 		if(IsMatchDev(pDevice, nOnline, nDevType, nArrears) && nGroupID == nTempGroup)
// 		{
		//	GPSDevInfo_S DevInfo = *(pDevice->GetDeviceInfo());
			mapDev.insert(mapVehicleBase::value_type(pDevice->GetVehicleIDNOForChar(), pDevice));
//		}
		++ iterB;
	}
}
void CVehicleBaseMgr::GetGroupDev(int nGroupID, mapIDIRDEVGroup& mapGroup, mapVehicleBase& mapDev/*, int nOnline, int nDevType, int nArrears*/)
{
	CAutoLock	m_cs(m_LockDevice);
	mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter iterE = m_mapVehicleBase.end();
	while(iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		int nTempGroup = pDevice->GetGroup();
		if (nGroupID == nTempGroup || mapGroup.find(nTempGroup) != mapGroup.end())
		{
// 			if(IsMatchDev(pDevice, nOnline, nDevType, nArrears))
// 			{
			//	GPSDevInfo_S DevInfo = *(pDevice->GetDeviceInfo());
				mapDev.insert(mapVehicleBase::value_type(pDevice->GetVehicleIDNOForChar(), pDevice));
//			}
		}
		++ iterB;
	}
}

void CVehicleBaseMgr::GetChildGroup(int nParentID, mapIDIRDEVGroup& AllGroup, mapIDIRDEVGroup& ChildGroup)
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
void CVehicleBaseMgr::GetChildGroup(int nParentID, mapIDIRDEVGroup& ChildGroup)
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

int	CVehicleBaseMgr::GetAllDevMap(mapVehicleBase& mapDev/*, int nOnline, int nDevType, int nArrears*/)
{
	CAutoLock	m_cs(m_LockDevice);
	mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter iterE = m_mapVehicleBase.end();
	while(iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
// 		if (IsMatchDev(pDevice, nOnline, nDevType, nArrears))
// 		{ 
			mapDev.insert(mapVehicleBase::value_type(pDevice->GetVehicleIDNOForChar(), pDevice));
//		}
		++ iterB;
	}
	
	return mapDev.size();
}


void CVehicleBaseMgr::GetAllDev(GPSDeviceIDNO_S** ppDevice, int& nCount)
{
	CAutoLock	m_cs(m_LockDevice);
	nCount = m_mapVehicleBase.size();
	if (nCount > 0)
	{
		*ppDevice = new GPSDeviceIDNO_S[nCount];
		int nIndex = 0;
		GPSDeviceIDNO_S* pDevice = *ppDevice;
		mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
		mapVehicleBaseIter iterE = m_mapVehicleBase.end();
		while(iterB != iterE)
		{
			CVehicleBase* pDvsDevice = (*iterB).second;
			strncpy(pDevice[nIndex].szDevIDNO, pDvsDevice->GetDeviceInfo()->szName, sizeof(pDevice[nIndex].szDevIDNO) - 1);
			++ nIndex;
			++ iterB;
		}
		nCount = nIndex;
	}
}


CVehicleBase* CVehicleBaseMgr::FindDevByName(const CString& strDevName)
{
	CAutoLock	m_cs(m_LockDevice);
	mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter iterE = m_mapVehicleBase.end();
	while(iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		CString strName = pDevice->GetShowName();

		if (strName == strDevName)
		{
			return pDevice;
		}
		++ iterB;
	}

	return NULL;
}

CVehicleBase* CVehicleBaseMgr::FindVehicleFromDev(const char* lpDevIDNO)
{
	CAutoLock	m_cs(m_LockDevice);
	mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter iterE = m_mapVehicleBase.end();
	while(iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		if (pDevice->GetDevice(lpDevIDNO))
		{
			return pDevice;
		}
		++ iterB;
	}
	return NULL;
}

CVehicleBase* CVehicleBaseMgr::FindVechicleFromDevID(const int& nID)
{
	CAutoLock	m_cs(m_LockDevice);
	mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter iterE = m_mapVehicleBase.end();
	while(iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		if (pDevice->GetDevByID(nID))
		{
			return pDevice;
		}
		++ iterB;
	}
	return NULL;
}

CDevBase* CVehicleBaseMgr::FindDevByVehicleIDNO(const char* lpVehicleIDNO)
{
	CDevBase* pDev = NULL;
	CVehicleBase* pVehicle = FindDvsDeviceByIDNO(lpVehicleIDNO);
	if (pVehicle)
	{
		pDev = pVehicle->GetMainDevice();
	}

	return pDev;
}

CDevBase* CVehicleBaseMgr::FindDevByVehicleID(int nVehicleID)
{
	CDevBase* pDev = NULL;
	CVehicleBase* pVehicle = FindDvsDeviceByID(nVehicleID);
	if (pVehicle)
	{
		pDev = pVehicle->GetMainDevice();
	}

	return pDev;
}


int	CVehicleBaseMgr::GetDeviceNum()
{
	return m_mapVehicleBase.size();
}

int	CVehicleBaseMgr::GetOnlineDeviceNum()
{
	CAutoLock lock(m_LockDevice);
	int nOnlineDevNum = 0;
	mapVehicleBaseIter iterB = m_mapVehicleBase.begin();
	mapVehicleBaseIter iterE = m_mapVehicleBase.end();
	while(iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		if (pDevice)
		{
			if(pDevice->GetOnline())
				++nOnlineDevNum;
		}
		++ iterB;
	}	
	return nOnlineDevNum;
}

CString CVehicleBaseMgr::GetDevName(const char* pDevIDNO)
{
	CString str;
	CVehicleBase* pDev = FindDvsDeviceByIDNO(pDevIDNO);
	if (pDev)
	{
		str = pDev->GetShowName();
	}

	return str;
}

void CVehicleBaseMgr::FillDeviceInfoEx(CTreeCtrl& tree, LPCTSTR lpszRoot, BOOL bInsertChan, BOOL bShowAlarm, BOOL bShowAlarmOnly)
{
	tree.DeleteAllItems();
	HTREEITEM hRoot = tree.InsertItem(lpszRoot);
	InsertChildGroupAndDevice(tree, hRoot, DEV_GROUP_NO_PARENT, bInsertChan, bShowAlarm, bShowAlarmOnly);
	tree.Expand(hRoot, TVE_EXPAND);
	tree.SelectItem(hRoot);
}

void CVehicleBaseMgr::InsertChildGroupAndDevice(CTreeCtrl& tree, HTREEITEM hParentItem, int nParentGroupID
											, BOOL bInsertChan, BOOL bShowAlarm, BOOL bShowAlarmOnly)
{
	//first insert child group 
	mapDevGroup mapGroup;
	int nSize = CVehicleBaseMgr::GetInstance()->GetGroup(mapGroup);
	mapDevGroupIter iterB = mapGroup.begin();
	mapDevGroupIter iterE = mapGroup.end();
	while(iterB != iterE)
	{
		CVDevGroup* pDevGroup = (*iterB).second;
		if (nParentGroupID == pDevGroup->GetGroupInfo()->nParent)
		{
			HTREEITEM hNew = tree.InsertItem(pDevGroup->GetGroupName(), hParentItem);
			tree.SetItemData(hNew, (DWORD)pDevGroup);
			InsertChildGroupAndDevice(tree, hNew, pDevGroup->GetGroupInfo()->nID, bInsertChan, bShowAlarm, bShowAlarmOnly);
			tree.Expand(hNew, TVE_EXPAND);
		}
		++ iterB;
	}
	//second insert child device
	InsertChildDevice(tree, hParentItem, nParentGroupID, bInsertChan, GPS_DEV_TYPE_MDVR, bShowAlarm, bShowAlarmOnly);
	InsertChildDevice(tree, hParentItem, nParentGroupID, bInsertChan, GPS_DEV_TYPE_MOBILE, bShowAlarm, bShowAlarmOnly);
	InsertChildDevice(tree, hParentItem, nParentGroupID, bInsertChan, GPS_DEV_TYPE_DVR, bShowAlarm, bShowAlarmOnly);
	tree.Expand(hParentItem, TVE_EXPAND);
}

void CVehicleBaseMgr::InsertChildDevice(CTreeCtrl& tree, HTREEITEM hParentItem, int nGroupID
									, BOOL bInsertChan, int nDevType, BOOL bShowAlarm ,BOOL bShowAlarmOnly)
{
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	mapVehicleBaseIter iterB = mapDev.begin();
	mapVehicleBaseIter iterE = mapDev.end();	
	while (iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		if (bShowAlarmOnly && !pDevice->GetAlarm())
		{
			++ iterB;
			continue;
		}
		
		if (pDevice->GetGroup() == nGroupID && nDevType == pDevice->GetDevType())
		{
			HTREEITEM hNew = NULL;
			hNew = tree.InsertItem(pDevice->GetShowName(), hParentItem);
			tree.SetItemData(hNew, (DWORD)pDevice);
			if (bInsertChan)
			{
				for (int i = 0; i < pDevice->GetChannelNum(); ++ i)
				{
					HTREEITEM hTemp = NULL;
					hTemp = tree.InsertItem(pDevice->GetChnName(i), hNew);
					tree.SetItemState(hTemp, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK );
					tree.SetItemData(hTemp, i);
				}
			}
		}
		++ iterB;
	}
}
