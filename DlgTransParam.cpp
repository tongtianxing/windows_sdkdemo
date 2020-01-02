// DlgTransParam.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTransParam.h"
#include "DevBase.h"
#include "VMgrDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTransParam dialog

#define WM_MSG_GET_PARAM        WM_USER + 0x1906
#define WM_MSG_SET_PARAM        WM_USER + 0x1907

CDlgTransParam::CDlgTransParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTransParam)
	m_strSetParamRec = _T("");
	m_strSetParamSend = _T("<Parameter><CHANNEL_SET Action=\"get\" StreamType=\"0\" ChannelId=\"0\" isRec=\"?\" Resolution=\"?\" FrameRate=\"?\" Quality=\"?\" HaveAudio=\"?\" /></Parameter>");
	m_lParamHandle = NULL;
	//}}AFX_DATA_INIT
}


void CDlgTransParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTransParam)
	DDX_Control(pDX, IDC_COMBO_DEV, m_cmbDev);
	DDX_Text(pDX, IDC_EDIT_SET_REC, m_strSetParamRec);
	DDX_Text(pDX, IDC_EDIT_SET_SEND, m_strSetParamSend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTransParam, CDialog)
	//{{AFX_MSG_MAP(CDlgTransParam)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_MESSAGE(WM_MSG_GET_PARAM, OnMsgGetParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTransParam message handlers

void CDlgTransParam::OnButtonSet() 
{
	
	UpdateData(TRUE);
	if (m_strSetParamSend.IsEmpty())
	{
		return;
	}
	if (m_strSetParamSend.GetLength() > 1024)
	{
		return;
	}
	int nIndex = m_cmbDev.GetCurSel();
	if (nIndex == CB_ERR)
	{
		return;
	}
	GPSConfigData_S Config = {0};
	strncpy(Config.cBuffer, CStringA(m_strSetParamSend), 1024);
	CString strIDNO;
	Config.nLength = m_strSetParamSend.GetLength();

	/*m_cmbDev.GetLBText(nIndex, strIDNO);*/
	
	CVehicleBase* pVehi = (CVehicleBase*)m_cmbDev.GetItemData(nIndex);
	if (pVehi != NULL)
	{
		DoTransparentConfig(pVehi->GetMainDevice()->GetDevIDNO(), 0, &Config);
	}
	
}


BOOL CDlgTransParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	mapVehicleBaseIter iterB = mapDev.begin();
	mapVehicleBaseIter iterE = mapDev.end();
	int nIndex = 0;
	while(iterE != iterB)
	{
		CVehicleBase* pVehi = (CVehicleBase*)iterB->second;
		if (pVehi != NULL)
		{
			m_cmbDev.InsertString(nIndex, pVehi->GetShowName());
			m_cmbDev.SetItemData(nIndex, DWORD(pVehi));
			nIndex ++;
		}
		iterB++;
	}
	if (m_cmbDev.GetCount() > 0)
	{
		m_cmbDev.SetCurSel(0);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTransParam::DoTransparentConfig(CString strIDNO, int nType, GPSConfigData_S* lpInConfig)
{
	EnableCtrl(FALSE);
	NETCLIENT_MCTransparentConfig(CStringA(strIDNO), nType, lpInConfig, this, FUNGetDevConfig, &m_lParamHandle);
}

void CDlgTransParam::FUNGetDevConfig(GPSMCMsg_S* pMsg, void* pUsr)
{
	CDlgTransParam* pThis = (CDlgTransParam*)pUsr;
	pThis->DoGetDevConfig(pMsg);
}

void CDlgTransParam::DoGetDevConfig(GPSMCMsg_S* pMsg)
{
	if (!PostMessage(WM_MSG_GET_PARAM, (WPARAM)pMsg))
	{
		NETCLIENT_MCReleaseMsg(pMsg);
	}
}

LRESULT CDlgTransParam::OnMsgGetParam(WPARAM wParam, LPARAM lParam)
{
	GPSMCMsg_S* pMsg =(GPSMCMsg_S*)wParam;
	if (pMsg != NULL && m_lParamHandle != NULL)
	{
		if (GPS_OK == pMsg->nResult)
		{
			GPSConfigData_S* pTmp = (GPSConfigData_S*)(pMsg->pParam[0]);
			m_strSetParamRec = pTmp->cBuffer;
			UpdateData(FALSE);
			AfxMessageBox(_T("OK"));
		}
		else
		{
			AfxMessageBox(_T("Fails"));
		}
		EnableCtrl(TRUE);
		CloseGetParamHandle();
	}
	
	NETCLIENT_MCReleaseMsg(pMsg);
	return 0;
}

void CDlgTransParam::CloseGetParamHandle()
{
	if (m_lParamHandle)
	{
		NETCLIENT_MCReleaseHandle(m_lParamHandle);
		m_lParamHandle = NULL;
	}
}

void CDlgTransParam::EnableCtrl(BOOL bEnable)
{
	GetDlgItem(IDC_BUTTON_SET)->EnableWindow(bEnable);
}
