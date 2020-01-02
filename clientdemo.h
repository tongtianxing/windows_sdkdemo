// clientdemo.h : main header file for the CLIENTDEMO application
//

#if !defined(AFX_CLIENTDEMO_H__AB805FF2_F271_4BE9_9770_BC074720D3E0__INCLUDED_)
#define AFX_CLIENTDEMO_H__AB805FF2_F271_4BE9_9770_BC074720D3E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientdemoApp:
// See clientdemo.cpp for the implementation of this class
//

class CClientdemoApp : public CWinApp
{
public:
	CClientdemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientdemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientdemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void	SetLoginInfo(LPCTSTR lpszIP, unsigned short usPort, LPCTSTR lpszCmp, LPCTSTR lpszUsr, LPCTSTR lpszPwd);
	CString GetLoginUser() { return m_strLoginUsr; }
	CString GetLoginPsw() { return m_strLoginPwd; }


private:
	CString	m_strDirSvrIP;
	unsigned short m_usDirSvrPort;
	CString	m_strLoginCmpny;
	CString	m_strLoginUsr;
	CString	m_strLoginPwd;

};
extern CClientdemoApp theApp;
//extern CObjPool<GPSVehicleState_S>	gVehiRunning;


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO_H__AB805FF2_F271_4BE9_9770_BC074720D3E0__INCLUDED_)
