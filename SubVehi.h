// SubVehi.h: interface for the CSubVehi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBVEHI_H__B551F32C_5DBD_417D_882F_CC247C78B622__INCLUDED_)
#define AFX_SUBVEHI_H__B551F32C_5DBD_417D_882F_CC247C78B622__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSubVehi  
{
public:
	CSubVehi();
	virtual ~CSubVehi();

	virtual void SetWndMsg(HWND hWnd, int nMsg);
	virtual void StartWork();
	virtual void StopWork();
	virtual void UpdateDevice(GPSDeviceIDNO_S* pDevice, int nCount);

protected:
	HWND m_hWnd;
	int m_nMsg;
	long m_lVehi;
};

#endif // !defined(AFX_SUBVEHI_H__B551F32C_5DBD_417D_882F_CC247C78B622__INCLUDED_)
