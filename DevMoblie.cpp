// DevMoblie.cpp: implementation of the CDevMoblie class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DevMoblie.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDevMoblie, CObject)

CDevMoblie::CDevMoblie()
{

}

CDevMoblie::~CDevMoblie()
{

}

unsigned char CDevMoblie::GetSex()
{
	return m_DevInfo.gMobileDevInfo.nSex;
}
CString CDevMoblie::GetSexStr()
{
	CString str;
	if (GPS_MOBILE_USER_SEX_MAN == m_DevInfo.gMobileDevInfo.nSex)
	{
		str = "male";
	}
	else if (GPS_MOBLIE_USER_SEX_WOMAN == m_DevInfo.gMobileDevInfo.nSex)
	{
		str = "female";
	}
	return str;
}
CString CDevMoblie::GetIDCar()
{
	return m_DevInfo.gMobileDevInfo.strIDCar;
}
CString CDevMoblie::GetUserNum()
{
	return m_DevInfo.gMobileDevInfo.strUserNumber;
}
CString CDevMoblie::GetGroupName()
{
	return m_DevInfo.gMobileDevInfo.strGroupName;
}
CString CDevMoblie::GetAddress()
{
	return m_DevInfo.gMobileDevInfo.strAddress;
}
int CDevMoblie::GetPost()
{
	return m_DevInfo.gMobileDevInfo.nUserPost;
}
CString CDevMoblie::GetPostStr()
{
	CString str;
	return str;
}
int CDevMoblie::GetEquip()
{
	return m_DevInfo.gMobileDevInfo.nEquip;
}
CString CDevMoblie::GetEquipStr()
{
	CString str;
	return str;
}
