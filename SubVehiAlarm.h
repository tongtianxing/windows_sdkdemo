// SubAlarm.h: interface for the CSubAlarm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBVEHIALARM_H__CA1F8EC2_67C5_4EC0_B035_44E8291E79F3__INCLUDED_)
#define AFX_SUBVEHIALARM_H__CA1F8EC2_67C5_4EC0_B035_44E8291E79F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SubVehi.h"
class CSubVehiAlarm  : public CSubVehi
{
public:
	CSubVehiAlarm();
	virtual ~CSubVehiAlarm();

	virtual void StartWork();
	virtual void StopWork();
	virtual void UpdateDevice(GPSDeviceIDNO_S* pDevice, int nCount);

private:
	static void CALLBACK FUNAlarmInfoCB(const char* pAlarm, int nLenght, void* pUsr);
	void	DoAlarmInfo(const char* pAlarm, int nLength);

};

#endif // !defined(AFX_SUBALARM_H__CA1F8EC2_67C5_4EC0_B035_44E8291E79F3__INCLUDED_)
