// SubVehi.cpp: implementation of the CSubVehi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "clientdemo.h"
#include "SubVehi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSubVehi::CSubVehi()
{
	m_hWnd = NULL;
	m_nMsg = 0;
	m_lVehi = NULL;
}

CSubVehi::~CSubVehi()
{

}

void CSubVehi::SetWndMsg(HWND hWnd, int nMsg)
{
	m_hWnd = hWnd;
	m_nMsg = nMsg;
}

void CSubVehi::StartWork()
{

}
void CSubVehi::StopWork()
{

}

void CSubVehi::UpdateDevice(GPSDeviceIDNO_S* pDevice, int nCount)
{

}