// VMgrDevice.h: interface for the CVMgrDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMGRDEVICE_H__9037E462_21FE_452E_A505_78E5A6FBC317__INCLUDED_)
#define AFX_VMGRDEVICE_H__9037E462_21FE_452E_A505_78E5A6FBC317__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*===========================================================================

Copyright (c) 2009, 
  
V 1.0
	
Author£º	afu	(imafu@hotmail.com)
	  
ClassName£º	CVMgrDevice
		
Description£º	Device Management Class
		  
Design£º	The client edit device properties including: name, device ID, and other information for the equipment to report information (including equipment IP, service port and channel number, etc.)

History£º	1¡¢the generated date£º2009-06-20

Not implemented:
1, modify channel names
2, increase the device type (such as hd equipment or equipment) of low




===========================================================================*/

#define DEV_GROUP_NO_PARENT		0
#define DEV_GROUP_UN_REG		0
#define DEV_ID_UNVALID			-1

class CVMgrDevice
{
private:
	static CVMgrDevice*	g_DevMgr;

public:
	static CVMgrDevice*	GetInstance();
	static void	DelInstance();
	
public:
	CVMgrDevice();
	virtual ~CVMgrDevice();

private:	
	CVMgrDevice(const CVMgrDevice&);
	CVMgrDevice& operator = (const CVMgrDevice& );

protected:
	BOOL	FreeDvsDevice(mapDvsDevice& DvsDevice);
	BOOL	FreeDevGroup(mapDevGroup& DevGroup);
	
	void	ClearDevNoExist(mapDvsDevice& mapDev);
public:
	BOOL	FreeDevInfo();

	CDevBase* FindDvsDeviceByID(int nID);
	CDevBase* FindDvsDeviceByIDNO(const CString& strIDNO);
	CVDevGroup*	FindDvsGroupByID(int nID);

/*	BOOL	GetUnRegDevice(int nUnRegGroup);*/
	void	UpdateDevInfo(mapDvsDevice& Device);

	BOOL	GetGroupInfo(int nGroupID, GPSDEVGroup_S& DEVGroup, mapIDIRDEVGroup& ParentGroup, mapIDIRDEVGroup& ChildGroup);
	void	GetGroupDev(int nGroupID, mapIDIRDEVGroup& mapGroup, mapIDIRDEVInfo& mapDev);
	void    GetGroupDevEx(int nGroupID, mapIDIRDEVGroup& mapGroup, mapIDIRDEVInfo& mapDev);
	void	GetChildGroup(int nParentID, mapIDIRDEVGroup& AllGroup, mapIDIRDEVGroup& ChildGroup);
	void	GetChildGroup(int nParentID, mapIDIRDEVGroup& ChildGroup);
	void	GetGroupDev(int nGroupID, mapIDIRDEVInfo& mapDev);

	int GetAllDevMap(mapDvsDevice& mapDev);
	int		GetAllDev(mapIDIRDEVInfo& mapDev);
	void	GetAllDev(GPSDeviceIDNO_S** ppDevice, int& nCount);
	int GetGroup(mapDevGroup& mapGroup);

	int     GetAllOnlineDev(mapIDIRDEVInfo& mapDevInof, BOOL bOnline = TRUE);
	int	GetAllOnlineDev(mapDvsDevice& mapDev, BOOL bOnline = TRUE);
	void	GetOnlineDev(mapIDIRDEVInfo& mapDev, int iMaxCount);

	void	PasteDevice(CVMgrDevice& DestDevice);
	void	MergeDevInfo(CVMgrDevice* pNewMgrDevice);

	void	SearchDevice(const CString& strDev, mapIDIRDEVInfo& mapDev);

	void	UpdateMgrMapDvsDevice(GPSDevInfo_S* pBaseInfo);


	int		GetDeviceNum();
	int		GetOnlineDeviceNum();

	static CDevBase* S_CopyDevice(CDevBase* pDevice);
	
private:
	CMutexLock		m_LockDvsDev;
	mapDvsDevice	m_mapDvsDevice;
	mapStrDevice	m_mapStrDevice;
	mapDevGroup		m_mapDevGroup;
	int m_nAddCount;
};

#endif // !defined(AFX_VMGRDEVICE_H__9037E462_21FE_452E_A505_78E5A6FBC317__INCLUDED_)
