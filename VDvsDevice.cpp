// VDvsDevice.cpp: implementation of the CVDvsDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VDvsDevice.h"
//#include "ObjPool.h"
//#include "VideoRecord.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//extern CObjPool<IDNAlarmData_S>		gAlarmPool;
//extern BOOL CompareAlarm(const char* GUID, IDNAlarmData_S* pData);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CVDevGroup, CObject)
CVDevGroup::CVDevGroup()
{
	memset(&m_GroupInfo, 0, sizeof(m_GroupInfo));
}

CVDevGroup::~CVDevGroup()
{

}

CString CVDevGroup::GetGroupName()
{
	CString str;
	{
		const int nLen1 = sizeof(m_GroupInfo.szName);
		const int nLen2 = sizeof(m_GroupInfo.szRemarks);
		const int nLen3 = nLen1 + nLen2;
		char szGroup[nLen3] = {0};
		if (strlen(m_GroupInfo.szRemarks) > 0)
		{
			memcpy(szGroup, m_GroupInfo.szName, nLen1-1);
			memcpy(szGroup+nLen1-1, m_GroupInfo.szRemarks, nLen2);
		}
		else
		{
			memcpy(szGroup, m_GroupInfo.szName, nLen1-1);
		}
		const int nLen = 2*sizeof(szGroup);
#if defined(_UNICODE) || defined(UNICODE) 
		WCHAR szIDNOW[nLen] = {0};
		Utf8ToUcs(szGroup, szIDNOW, nLen);
		str = szIDNOW;
#else
		char szIDNOW[nLen] = {0};
		Utf8ToAnsi(szGroup, szIDNOW, nLen);
		str = szIDNOW;
#endif
	}
	return str;
}

//////////////////////////////////////////////////////////////////////////
//CVDvsDevice Construction/Destruction 
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CVDvsDevice, CObject)
CVDvsDevice::CVDvsDevice()
{
	m_lRegCount = 0;
	m_bAlarm = FALSE;
	memset(&m_VehiRunning, 0, sizeof(m_VehiRunning));
}

CVDvsDevice::~CVDvsDevice()
{
}

CString CVDvsDevice::GetIOName(UINT nIO)
{
	CString strIOName;
	if(nIO < GPS_MAX_DEV_IO_NUM_OLD)
	{
		strIOName = m_DevInfo.gDVRInfo.szIoInName[nIO];
		if (strIOName.IsEmpty())
		{
			strIOName.Format(_T("%s %d"), _T("IO_"), nIO+1);
		}
	}
	return strIOName;
}

int CVDvsDevice::GetIONumber()
{
	return m_DevInfo.gDVRInfo.ucIoInNum;
}
