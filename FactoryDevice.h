// FactoryDevice.h: interface for the CFactoryDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACTORYDEVICE_H__A5CEEFF3_B8E7_488E_88C3_EA9E5CC5EB5A__INCLUDED_)
#define AFX_FACTORYDEVICE_H__A5CEEFF3_B8E7_488E_88C3_EA9E5CC5EB5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDevBase;
class CFactoryDevice 
{
private:
	static CFactoryDevice*	g_DevFactory;
	
public:
	static CFactoryDevice*	GetInstance();
	static void	DelInstance();

public:
	CFactoryDevice();
	virtual ~CFactoryDevice();

	CDevBase* CreateObject(int nDevType);
};

class CVehicleBase;
class CFactoryVehicle : public CStaticObject<CFactoryVehicle>
{
public:
	CFactoryVehicle();
	virtual ~CFactoryVehicle();
	
	CVehicleBase* CreateObject(int nDevType = 0);
};

#endif // !defined(AFX_FACTORYDEVICE_H__A5CEEFF3_B8E7_488E_88C3_EA9E5CC5EB5A__INCLUDED_)
