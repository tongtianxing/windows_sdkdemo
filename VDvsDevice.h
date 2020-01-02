// VDvsDevice.h: interface for the CVDvsDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VDVSDEVICE_H__AB311169_785F_455F_BD5A_2B8302F8657A__INCLUDED_)
#define AFX_VDVSDEVICE_H__AB311169_785F_455F_BD5A_2B8302F8657A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DevBase.h"


#define NO_PARENT	-1
#define NO_DEVICE	-1

class CVDevGroup : public CObject
{
	DECLARE_DYNAMIC(CVDevGroup);
public:
	CVDevGroup();
	virtual ~CVDevGroup();
	
public:
	GPSDEVGroup_S*	GetGroupInfo() {	return &m_GroupInfo;}
	CString GetGroupName();
	void	SetGroupInfo(const GPSDEVGroup_S* pGroupInfo) { m_GroupInfo = *pGroupInfo; }
	
private:
	GPSDEVGroup_S	m_GroupInfo;
};

class CVDvsDevice  : public CDevBase
{	
	DECLARE_DYNAMIC(CVDvsDevice);
public:
	CVDvsDevice();
	virtual ~CVDvsDevice();
	
public:
	GPSMDVRInfo_S*	GetDevInfo() {	return &m_DevRalationInfo.gDVRInfo;}
	CString GetIOName(UINT nIO);
	int GetIONumber();
};

#endif // !defined(AFX_VDVSDEVICE_H__AB311169_785F_455F_BD5A_2B8302F8657A__INCLUDED_)
