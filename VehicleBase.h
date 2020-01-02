// VehicleBase.h: interface for the CVehicleBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VEHICLEBASE_H__3E1D28C5_48D3_4263_BAAE_128BFC004128__INCLUDED_)
#define AFX_VEHICLEBASE_H__3E1D28C5_48D3_4263_BAAE_128BFC004128__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DevStatus.h"

typedef std::vector<char*>			vecAlarmGUID;
typedef vecAlarmGUID::iterator			vecAlarmGUIDIter;
class CVehicleBase : public CObject
{
	DECLARE_DYNAMIC(CVehicleBase);
public:
	CVehicleBase();
	virtual ~CVehicleBase();
public:
	virtual GPSDevInfo_S* GetDeviceInfo();
	virtual void SetDevInfo(const GPSDevInfo_S* pDevInfo);
	virtual void UpdateDevInfo(const GPSDEVDevInfo_S* pDevInfo);
	virtual BOOL GetOnline();
	virtual void SetOnline(BOOL bOnline);
	virtual CString	GetShowName();
	virtual CString	GetDevIDNO();
	virtual	char* GetVehicleIDNOForChar();
	virtual int	GetID();
	virtual int	GetChannelNum();
	virtual CString GetChnName(UINT nChn);
	virtual CString GetSIMCar();
	virtual int GetDevType();
	virtual int GetDevSubType();
	virtual int GetIcon();
	virtual int GetGroup();
	virtual void SetGroup(int nParentID);
	virtual CString GetRemark();
	virtual CString GetIOInName(UINT nIO);
	virtual int GetIOInNumber();
	virtual CString GetTempSensorName(UINT nTempSensor);
	virtual CString GetDriverName();
	virtual CString GetTel();
	virtual BOOL	UpdateVehiRunning(const GPSVehicleState_S* pRunning, BOOL bBigTime);
	virtual const GPSVehicleState_S*	GetVehiRunning();
	virtual GPSTime_S GetVehiTime();
	//	hw 2015/1/5 
	virtual BOOL IsUpdateVehiRunning();
	virtual void SetUpdateVehiRunning(BOOL bUpdateRunning);
	virtual BOOL	IsVehiRunningValid();
	virtual const GPSVehicleState_S*	GetVehiInitialStatus();
	virtual void SetVehiFixGPS(int nMapValid, int nMapType, int nJingdu, int nWeidu);
	/////////////////////////////////////////////////////////////////////////////////

	virtual void SetGPSAddress(const CString& strGPSAddress);
	virtual CString GetGPSAddress();
	
	virtual BOOL IsParseAddressing();
	virtual void SetParseAddressState(BOOL bParseAddressing);
	virtual void SetParseAddressSuc(BOOL bSuc);
	
	virtual void	SetAlarm(BOOL bAlarm); 
	virtual BOOL	GetAlarm();

	bool GetParseAddressSuc();
	void SetParseAddressGps(int nJingDu, int nWeiDu);
	bool IsParseAddressGpsSame(int nJingDu, int nWeiDu);
	
	void ParseCurGPS();
	static void CALLBACK FUNParseAddressCB(BOOL bSuc, LPCTSTR szAddress, LPCTSTR szCity, long lUserData, void* pUsr);
	void	DoParseAddressCB(BOOL bSuc, LPCTSTR szAddress, LPCTSTR szCity, long lUserData);
	///////////////////////////////
protected:	
	long	m_lRegCount;
	BOOL	m_bAlarm;
	GPSDevInfo_S m_DevInfo;
	CString m_strGPSAddress;	
	CString m_strCity;			
	BOOL m_bParseAddressing;	
	int m_nParseAddressFailed;	
	int	m_nParseAddressJingDu;
	int	m_nParseAddressWeiDu;
	CDevStatus m_DevStatus;

public:
	void	SetVehiIDNO(const char* szVehiIdno) {	strncpy(m_szVehiIDNO, szVehiIdno, sizeof(m_szVehiIDNO));	}
	const char*	GetVehiIDNO() {	return m_szVehiIDNO;	}

	void	AddDevice(CDevBase* pDev);

	void	DelDevice(CDevBase* pDev);

	virtual void SetUpDateDeviceList(lstDevice lstDev);

	void	ClearDevice();

	lstDevice GetDevList() const;

	CDevBase* GetDevice(const char* lpDevIDNO);

	CDevBase* GetMainDevice();

	CDevBase* GetDevByChn(int nChn);

	CDevBase* GetDevByIOOut(int nIO);
	CDevBase* GetDevByIOIn(int nIO);

	CDevBase* GetDevByID(const int& nID);

	CDevBase* GetDevWithGPS();

	char*	GetMainDevIDNO();
	int GetMainDevID();

	int GetDevCount();

	
	void SetVehiState(const int nState);
	int GetVehiState() const;

	CDevBase* GetOtherInTwoDev(const CDevBase* pDev);

	BOOL GetALLDevIsSame();

	CDevBase* GetDevWithVedio();

	CDevBase* GetDevWithoutVedio();

	CDevBase* GetDevByNum(int nNum);

	CDevBase* GetDevWithModulePeople();

public:
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
	
	virtual CDevBase* GetMoudleVideoDev();
	virtual CDevBase* GetMoudleSnapshot();
	virtual CDevBase* GetMoudleMonitor();
	virtual CDevBase* GetMoudleTalkback();
	virtual CDevBase* GettModuleTTS();
	virtual CDevBase* GetModuleOilCtrl();
	virtual CDevBase* GetModulePowerCtrl();
	virtual CDevBase* GetModuleBKTalk();
	virtual CDevBase* GetModuleOilSen();
	
private:
	bool IsMoudle(int nMoudle);

private:
	CMutexLock		m_LockDevice;
	lstDevice		m_lstDevice;
	char			m_szVehiIDNO[128];
	int m_nGPSFailCount; 
	DWORD m_dBegTime;	
	BOOL m_bReGPS;			
	int m_nGPSDevID;		
	GPSVehicleState_S m_GPSState;
	int m_curVehicleState;
};

#endif // !defined(AFX_VEHICLEBASE_H__3E1D28C5_48D3_4263_BAAE_128BFC004128__INCLUDED_)
