// DlgGetDevIP.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGetDevIP.h"
#include "DlgDevList.h"
#include "DevBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGetDevIP dialog
#define WM_MSG_DEV_IP          WM_USER+0x00001
#define WM_MSG_DEV_IP_MSG          WM_USER+0x00002

CDlgGetDevIP::CDlgGetDevIP(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGetDevIP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGetDevIP)
		// NOTE: the ClassWizard will add member initialization here
	m_lHandle = 0;
	m_pDevice = NULL;
	m_DevCount = 0;
	//}}AFX_DATA_INIT
}


void CDlgGetDevIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGetDevIP)
	DDX_Control(pDX, IDC_LIST_DEV_IP, m_listDevIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGetDevIP, CDialog)
	//{{AFX_MSG_MAP(CDlgGetDevIP)
	ON_BN_CLICKED(IDC_BUTTON_SEL_DEV, OnButtonSelDev)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_MSG_DEV_IP, OnMsgDevIP)
	ON_MESSAGE(WM_MSG_DEV_IP_MSG, OnMsgDevIPMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGetDevIP message handlers

BOOL CDlgGetDevIP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	DWORD styles = m_listDevIP.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_listDevIP.SetExtendedStyle(styles );
	m_listDevIP.InsertColumn(0, _T("DevIDNO"), LVCFMT_CENTER, 100);
	m_listDevIP.InsertColumn(1, _T("IP"), LVCFMT_CENTER, 100);
	m_listDevIP.InsertColumn(2, _T("Port"), LVCFMT_CENTER, 50);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGetDevIP::OnButtonSelDev() 
{
	
	CDlgDevList dlg;
	dlg.SetShowChan(FALSE);
	if (dlg.DoModal() == IDOK)
	{
		lstIntID lst = dlg.GetDevList();
		m_DevCount = lst.size();
		if (lst.size() > 0)
		{
			SAFE_DELETE_OBJECT(m_pDevice);
			m_pDevice = new GPSDeviceIDNO_S[m_DevCount];
			iterIntID iter = lst.begin();
			int i = 0;
			CVehicleBase* pDev = NULL;
			while(iter != lst.end())
			{
				pDev = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByID(*iter);

				strncpy(m_pDevice[i].szDevIDNO, pDev->GetMainDevIDNO(), 32);
				++i;
				++iter;
			}
			m_listDevIP.DeleteAllItems();
			GetDevIP(m_pDevice, m_DevCount);
		}
	}
}


void CDlgGetDevIP::GetDevIP(GPSDeviceIDNO_S* pDevice, unsigned int nDevCount)
{
	if(m_lHandle == NULL)
	{
		NETCLIENT_DEVOpenGetDevIP(&m_lHandle);
		NETCLIENT_DEVSetGetDevIPCB(m_lHandle, this, FUNGetDevIPCB);
	}
	EnableCtrl(FALSE);
	NETCLIENT_DEVStartGetDevIP(m_lHandle, pDevice, nDevCount);
	
}

void CDlgGetDevIP::FUNGetDevIPCB(int nType, void* pData, void * pUsr)
{
	CDlgGetDevIP* pThis = (CDlgGetDevIP*)pUsr;
	pThis->DoGetDevIPCB(nType, pData);
}
void CDlgGetDevIP::DoGetDevIPCB(int nType, void* pData)
{
	if (nType == GPS_DOWN_CONFIG_DATA)
	{
		DeviceDevIPInfo_S* pTemp = (DeviceDevIPInfo_S*)pData;
		for ( int i=0; i<m_DevCount; i++)
		{
			if ( memcmp(m_pDevice[i].szDevIDNO, pTemp->DevIDNO.szDevIDNO, 32) == 0)
			{
				DeviceDevIPInfo_S* pResp = new DeviceDevIPInfo_S;
				*pResp = *pTemp;
				if(!PostMessage(WM_MSG_DEV_IP, nType, (LPARAM)pResp))
				{
					SAFE_DELETE_OBJECT(pResp);
				}
				break;
			}
		}
	}
	else
	{
		PostMessage(WM_MSG_DEV_IP_MSG, nType, 0);
	}
}

LRESULT CDlgGetDevIP::OnMsgDevIP(WPARAM wParam, LPARAM lParam)
{
	DeviceDevIPInfo_S* pResp = (DeviceDevIPInfo_S*)lParam;
	int nIndex = 0;
	m_listDevIP.InsertItem(nIndex, NULL);
	CVehicleBase* pVehi = CVehicleBaseMgr::GetInstance()->FindVehicleFromDev(pResp->DevIDNO.szDevIDNO);
	if (pVehi != NULL)
	{
		m_listDevIP.SetItemText(nIndex, 0, pVehi->GetShowName());
	}
	else
	{
		m_listDevIP.SetItemText(nIndex, 0, CString(pResp->DevIDNO.szDevIDNO));
	}
	m_listDevIP.SetItemText(nIndex, 1, CString(pResp->szIP));
	CString str;
	str.Format(_T("%d"), pResp->nPort);
	m_listDevIP.SetItemText(nIndex, 2, str);
	SAFE_DELETE_OBJECT(pResp);
	return 0;
}


LRESULT CDlgGetDevIP::OnMsgDevIPMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam == GPS_DOWN_CONFIG_FAILED)
	{
		AfxMessageBox(_T("Failed"));
		EnableCtrl(TRUE);
		NETCLIENT_DEVStopGetDevIPt(m_lHandle);
	}
	else if (wParam == GPS_DOWN_CONFIG_SUC)
	{
		EnableCtrl(TRUE);
		NETCLIENT_DEVStopGetDevIPt(m_lHandle);
	}
	return 0;
}
void CDlgGetDevIP::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_lHandle)
	{
		NETCLIENT_DEVCloseGetDevIP(m_lHandle);
	}
	SAFE_DELETE_OBJECT(m_pDevice);
}

void CDlgGetDevIP::EnableCtrl(BOOL bEnable)
{
	GetDlgItem(IDC_BUTTON_SEL_DEV)->EnableWindow(bEnable);
}