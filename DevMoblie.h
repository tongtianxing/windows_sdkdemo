// DevMoblie.h: interface for the CDevMoblie class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVMOBLIE_H__E1E65DE0_2199_4BF8_8BB5_39E62AB69D4D__INCLUDED_)
#define AFX_DEVMOBLIE_H__E1E65DE0_2199_4BF8_8BB5_39E62AB69D4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DevBase.h"
class CDevMoblie : public CDevBase  
{
	DECLARE_DYNAMIC(CDevMoblie);

public:
	CDevMoblie();
	virtual ~CDevMoblie();

	unsigned char GetSex();
	CString GetSexStr();
	CString GetIDCar();
	CString GetUserNum();
	CString GetGroupName();
	CString GetAddress();
	int GetPost();
	CString GetPostStr();
	int GetEquip();
	CString GetEquipStr();


};

#endif // !defined(AFX_DEVMOBLIE_H__E1E65DE0_2199_4BF8_8BB5_39E62AB69D4D__INCLUDED_)
