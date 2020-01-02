// SvrVer.cpp: implementation of the CSvrVer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "clientdemo.h"
#include "SvrVer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSvrVer::CSvrVer(void)
{
	m_nSvrVer = 0;
}

CSvrVer::~CSvrVer(void)
{
	
}
void CSvrVer::SetSvrVer(int nSvrVer)
{
	m_nSvrVer = nSvrVer;
}

int CSvrVer::GetSvrVer()
{
	return m_nSvrVer;
}

bool CSvrVer::IsSvrVerV6()
{
	return (m_nSvrVer != GPS_SVR_VERSION_JT808);
}
bool CSvrVer::IsSvrVerV7()
{
	return (m_nSvrVer == GPS_SVR_VERSION_JT808);
}

bool CSvrVer::IsSvrVer(int nSvrVer)
{
	return (nSvrVer == m_nSvrVer);
}

