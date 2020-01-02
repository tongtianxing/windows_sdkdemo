// SubVehiStatus.h: interface for the CSubVehiStatus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBVEHISTATUS_H__7F326BBA_D236_4620_A53E_192180C5EA17__INCLUDED_)
#define AFX_SUBVEHISTATUS_H__7F326BBA_D236_4620_A53E_192180C5EA17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SubVehi.h"
class CSubVehiStatus  : public CSubVehi
{
public:
	CSubVehiStatus();
	virtual ~CSubVehiStatus();

	virtual void StartWork();
	virtual void StopWork();
	virtual void UpdateDevice(GPSDeviceIDNO_S* pDevice, int nCount);

protected:
	static void WINAPI FUNVehiStatusCB(GPSVehicleState_S* pVehiRun, char* pOnline, int nCount, void* pUsr);
	void	DoVehiStatus(GPSVehicleState_S* pVehiRun, char* pOnline, int nCount);
};

#endif // !defined(AFX_SUBVEHISTATUS_H__7F326BBA_D236_4620_A53E_192180C5EA17__INCLUDED_)
