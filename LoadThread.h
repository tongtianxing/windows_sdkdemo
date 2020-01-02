// LoadThread.h: interface for the CLoadThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADTHREAD_H__E18C2BC6_24EE_4DDF_8AAD_D1F204BDE88A__INCLUDED_)
#define AFX_LOADTHREAD_H__E18C2BC6_24EE_4DDF_8AAD_D1F204BDE88A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define LOAD_FINISHED			0
#define LOAD_ING				1
#define LOAD_FAILED				2

#define LOAD_APP_INFO_SUC		3
#define LOAD_DOWN_DEV_SUC		4
#define LOAD_DOWN_ARMSHILED_SUC 5
#define LOAD_USER_PRIVILEGE		6
#define LOAD_MAY_MAP_SUC		7
#define LOAD_MAP_CONFIG_SUC		8
#define LOAD_MARKER_INFO_SUC	9
#define LOAD_SVR_CONFIG_SUC		10
#define LOAD_CONFIG_SUC			11
#define LOAD_USER_INFO_SUC		12
#define LOAD_USER_TYPE_SUC		13

class CLoadThread  
{
public:
	CLoadThread();
	virtual ~CLoadThread();

	typedef std::map<int, int>					mapAlarmTpye;

public:
	void	SetLoadMsg(HWND hWnd, UINT uiMsg) {	m_hMsgHwnd = hWnd; m_uiMsg = uiMsg; }

	void	StartDeviceLoad(BOOL bReload);
	void	StopDeviceLoad();
   

	void SetDownConfig(unsigned int nDownConfig);

protected:
	void	FreeDownDev();
	void	PostLoadMessage(WPARAM wParam, LPARAM lParam = 0);

protected:
	static void WINAPI FUNDownDevCB(int nType, void* pData, void * pUsr);
	void	DoDownDevCB(int nType, void* pData);


private:
	//Parent Window Hwnd
	HWND	m_hMsgHwnd;
	UINT	m_uiMsg;
	
	BOOL	m_bReload;
	
	mapDvsDevice	m_mapDevDevice;
	mapDevGroup		m_mapDevGroup;
	mapStrDevice	m_mapIdnoDevice;
	
	long	m_lDownHandle;
	
	mapVehicleBase		m_mapVehi;
};

#endif // !defined(AFX_LOADTHREAD_H__E18C2BC6_24EE_4DDF_8AAD_D1F204BDE88A__INCLUDED_)
