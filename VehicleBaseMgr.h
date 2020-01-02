#pragma once


#define DEV_GROUP_NO_PARENT		0
#define DEV_GROUP_UN_REG		0
#define DEV_ID_UNVALID			-1

#define STATUS_ONLINE			0x0000001
#define STATUS_OFFLINE			0x0000010


#define DEV_TYPE_MDVR		0x00001	//MDVR
#define DEV_TYPE_DVR		0x00010	//DVR
#define DEV_TYPE_MOBLIE		0x00100	//moblie
#define DEV_TYPE_PAD		0x01000	//PAD

#define COLOR_TREE_MASK RGB(255,255,255) /*RGB(255-65,255-126,255-183)*/


typedef std::map<int, const GPSVehicleState_S*>		mapDeviceState;
typedef mapDeviceState::iterator	iterDeviceState;



class CVehicleBaseMgr  : public CStaticObject<CVehicleBaseMgr>
{
public:
	CVehicleBaseMgr();
	virtual ~CVehicleBaseMgr();

private:
	CVehicleBaseMgr(const CVehicleBaseMgr&);
	CVehicleBaseMgr& operator = (const CVehicleBaseMgr& );

protected:
	BOOL	FreeDevice(mapVehicleBase& mapDev);
	BOOL	FreeDevGroup(mapDevGroup& DevGroup);
	void	ClearDevNoExist(mapVehicleBase &mapDev);


public:
	void	UpdateVehiInfo(const GPSDevInfo_S* pDevice, unsigned int nCount);
	static void S_CopyVehiDevList(CVehicleBase* pNewVehiInfo, lstDevice& lstDev);
	static CVehicleBase* S_CopyVehicle(CVehicleBase* pSrc);
	void	UpdateVehiInfo(mapVehicleBase& Device, mapDevGroup& Group);
	void	UpdateVehiInfo(mapDevGroup& Group);
	//
	///////////////////////////
	void	MergeVehiInfo(CVehicleBaseMgr* pNewMgrDevice);
	void	PasteDevice(CVehicleBaseMgr& DestDevice);
	BOOL	FreeDevInfo();
public:
	int		GetAllDevMap(mapVehicleBase& mapDev);
	void	GetAllDev(GPSDeviceIDNO_S** ppDevice, int& nCount);
	CVehicleBase* FindDvsDeviceByID(int nID);
	CVehicleBase* FindDvsDeviceByIDNO(const char* pIDNO);
	CVDevGroup*	FindDvsGroupByID(int nID);
	void	SearchDevice(const CString& strDev, mapVehicleBase& mapDev);
	CVehicleBase* FindDevByName(const CString& strDevName);
	CVehicleBase* FindVehicleFromDev(const char* lpDevIDNO);
	CVehicleBase* FindVechicleFromDevID(const int& nID);
	CDevBase* FindDevByVehicleIDNO(const char* lpVehicleIDNO);
	CDevBase* FindDevByVehicleID(int nVehicleID);

	int		GetGroup(mapDevGroup& mapGroup);
	BOOL	GetGroupInfo(int nGroupID, GPSDEVGroup_S& DEVGroup, mapIDIRDEVGroup& ParentGroup, mapIDIRDEVGroup& ChildGroup);
	void	GetGroupDev(int nGroupID, mapIDIRDEVGroup& mapGroup, mapVehicleBase& mapDev);
	void	GetChildGroup(int nParentID, mapIDIRDEVGroup& AllGroup, mapIDIRDEVGroup& ChildGroup);
	void	GetChildGroup(int nParentID, mapIDIRDEVGroup& ChildGroup);
	void	GetGroupDev(int nGroupID, mapVehicleBase& mapDev);

	int		GetDeviceNum();
	int		GetOnlineDeviceNum();

	void FillDeviceInfoEx(CTreeCtrl& tree, LPCTSTR lpszRoot, BOOL bInsertChan, BOOL bShowAlarm, BOOL bShowAlarmOnly);
	void InsertChildGroupAndDevice(CTreeCtrl& tree, HTREEITEM hParentItem, int nParentGroupID, BOOL bInsertChan, BOOL bShowAlarm, BOOL bShowAlarmOnly);
	void InsertChildDevice(CTreeCtrl& tree, HTREEITEM hParentItem, int nGroupID, BOOL bInsertChan, int nDevType, BOOL bShowAlarm ,BOOL bShowAlarmOnly);

public:
	CString GetDevName(const char* pDevIDNO);

private:
	CMutexLock		m_LockDevice;
	int				m_nAddCount;

public:
 	mapDevGroup		m_mapDevGroup;
	mapVehicleBase  m_mapVehicleBase;
	mapVehicleBase	m_mapVehiDevIDNO;
};
