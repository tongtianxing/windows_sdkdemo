// FactoryDevice.cpp: implementation of the CFactoryDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FactoryDevice.h"
#include "DevMoblie.h"
#include "VDvsDevice.h"
#include "VehicleBase.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFactoryDevice*	CFactoryDevice::g_DevFactory = NULL;

CFactoryDevice*	CFactoryDevice::GetInstance()
{
	if (NULL == g_DevFactory)
	{
		g_DevFactory = new CFactoryDevice;
	}
	return g_DevFactory;
}

void CFactoryDevice::DelInstance()
{
	if (g_DevFactory)
	{
		delete g_DevFactory;
		g_DevFactory = NULL;
	}
}
CFactoryDevice::CFactoryDevice()
{

}

CFactoryDevice::~CFactoryDevice()
{

}

CDevBase* CFactoryDevice::CreateObject(int nDevType)
{
	CDevBase* pDevice = NULL;
	if (nDevType == GPS_DEV_TYPE_MDVR || nDevType == GPS_DEV_TYPE_DVR)
	{
		pDevice = new CVDvsDevice;
	}
	else if (nDevType == GPS_DEV_TYPE_MOBILE)
	{
		pDevice = new CDevMoblie;
	}
	return pDevice;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFactoryVehicle::CFactoryVehicle()
{
	
}

CFactoryVehicle::~CFactoryVehicle()
{
	
}

CVehicleBase* CFactoryVehicle::CreateObject(int nDevType)
{
	return new CVehicleBase;
}