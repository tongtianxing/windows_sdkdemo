// DevBase.h: interface for the CDevBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVBASE_H__E3DB76CB_470D_4CE0_BEFF_E0764286CAA9__INCLUDED_)
#define AFX_DEVBASE_H__E3DB76CB_470D_4CE0_BEFF_E0764286CAA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DevStatus.h"

typedef std::vector<char*>			vecAlarmGUID;
typedef vecAlarmGUID::iterator			vecAlarmGUIDIter;

class CDevBase : public CObject
{
	DECLARE_DYNAMIC(CDevBase);

public:
	CDevBase();
	virtual ~CDevBase();

public:
	virtual GPSDevInfo_S* GetDeviceInfo() { return &m_DevInfo; }
	virtual void SetDevInfo(const GPSDevInfo_S* pDevInfo) { m_DevInfo = *pDevInfo; }
	virtual BOOL GetOnline();
	virtual void SetOnline(BOOL bOnline);
	virtual CString	GetShowName();
	virtual CString	GetDevIDNO();
	virtual char* CDevBase::GetDevIDNOForChar();
	virtual int	GetID();
	virtual int	GetChannelNum();
	virtual CString GetChnName(UINT nChn);
	virtual CString GetSIMCar();
	/*virtual UINT GetModule();*/
	virtual int GetDevType();
	virtual int GetDevSubType();
// 	virtual int GetIcon();
// 	virtual int GetGroup();
// 	virtual CString GetRemark();
	virtual	char GetProtocol();

	virtual SYSTEMTIME ConvertToSystemTime(const GPSTime_S& IdnTime);
	
	virtual BOOL	UpdateVehiRunning(const GPSVehicleState_S* pRunning, BOOL bBigTime);
	virtual const GPSVehicleState_S*	GetVehiRunning();
	virtual BOOL IsUpdateVehiRunning();
	virtual void SetUpdateVehiRunning(BOOL bUpdateRunning);
	virtual BOOL	IsVehiRunningValid();
	virtual const GPSVehicleState_S*	GetVehiInitialStatus();
	virtual void SetVehiFixGPS(int nMapValid, int nMapType, int nJingdu, int nWeidu);
	
	virtual void	SetAlarm(BOOL bAlarm); 
	virtual BOOL	GetAlarm();

// 	virtual GPSVehicleState_S	GetVehiRunning()	{	return m_VehiRunning;	}
// 	virtual BOOL	IsVehiRunningValid();
// 	
// 	virtual void	SetAlarm(BOOL bAlarm); 
// 	virtual BOOL	GetAlarm()	{	return m_bAlarm; }

	virtual void SetGPSAddress(const CString& strGPSAddress);
	virtual CString GetGPSAddress();
	virtual BOOL IsParseAddressing();
	virtual void SetParseAddressState(BOOL bParseAddressing);
	virtual void SetParseAddressSuc(BOOL bSuc);
	
	bool GetParseAddressSuc() 
	{
		return m_nParseAddressFailed > 0 ? false : true;
	}
	void SetParseAddressGps(int nJingDu, int nWeiDu)
	{
		m_nParseAddressJingDu = nJingDu;
		m_nParseAddressWeiDu = nWeiDu;
	}
	bool IsParseAddressGpsSame(int nJingDu, int nWeiDu)
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
	
public:
	void	AddReg();
	void	Release();
	

protected:	
	long	m_lRegCount;
	BOOL	m_bAlarm;
	
	GPSVehicleState_S	m_VehiRunning;
	GPSDevInfo_S m_DevInfo;

	CString m_strGPSAddress;	
	BOOL m_bParseAddressing;	
	int m_nParseAddressFailed;	//Fail three times ,Clear Address
	int	m_nParseAddressJingDu;
	int	m_nParseAddressWeiDu;

public:
	void	SetDevRelationInfo(const GPSVehiDevRelation_S* pInfo);
	GPSVehiDevRelation_S* GetDevRelationInfo();
	
	void UpdateDevInfo(const GPSDEVDevInfo_S* pDevInfo);
	
	virtual	char* GetIDNOForChar();

	
	virtual char* GetVehicleForChar();

public:
	virtual bool IsMainDev();
	virtual bool IsExistMoudleVideo();
	virtual bool IsExistMoudleSnapshot();
	virtual bool IsExistMoudleMonitor();
	virtual bool IsExistMoudleTalkback();
	virtual bool IsExistModuleTTS();
	virtual bool IsExistModuleOilCtrl();
	virtual bool IsExistModulePowerCtrl();
	virtual bool IsExistModuleBKTalk();
	virtual bool IsExistModuleOilSen();
	virtual bool IsExistMoudleChn(UINT nChn);
	virtual bool IsExistMoudleIOIn(UINT nIO);
	virtual bool IsExistMoudleIOOut(UINT nIO);
	virtual bool IsExistMoudleODB();
	virtual bool IsExistMoudleCountPeople();
	int GetRealChn(int nChn);

protected:
	bool IsExistMoudle(int nMoudle);
	void UpdateMoudleInfo();
	
protected:
	GPSVehiDevRelation_S m_DevRalationInfo;
	mapInt m_mapChn;
	mapInt m_mapIOIn;
	mapInt m_mapIOOut;
	CDevStatus m_DevStatus;
};

#endif // !defined(AFX_DEVBASE_H__E3DB76CB_470D_4CE0_BEFF_E0764286CAA9__INCLUDED_)
