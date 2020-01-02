// DlgTransData.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTransData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define		WM_APPROVE_RESULT		WM_USER + 1
/////////////////////////////////////////////////////////////////////////////
// CDlgTransData dialog


CDlgTransData::CDlgTransData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTransData)
	m_strSend = _T("");
	m_lHandle = NULL;
	//}}AFX_DATA_INIT
}


void CDlgTransData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTransData)
	DDX_Control(pDX, IDC_COMBO_DEV, m_cmbDev);
	DDX_Text(pDX, IDC_EDIT_SET_SEND, m_strSend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTransData, CDialog)
	//{{AFX_MSG_MAP(CDlgTransData)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_APPROVE_RESULT, OnResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTransData message handlers

void CDlgTransData::OnButtonSet() 
{
	
	UpdateData(TRUE);
	if (!m_strSend.IsEmpty())
	{
		char szData[256] = {0};
#if defined(_UNICODE) || defined(UNICODE)  
		USES_CONVERSION;
		memcpy(szData, W2A(m_strSend.GetBuffer(0)), sizeof(szData));
#else
		memcpy(szData, m_strSend.GetBuffer(0), sizeof(szData));
#endif	
		CVehicleBase* pVehi = (CVehicleBase*)m_cmbDev.GetItemData(m_cmbDev.GetCurSel());
		if (NULL != pVehi)
		{
			EnableCtrl(FALSE);
			
			NETCLIENT_MCTransparentPortData(pVehi->GetMainDevIDNO(), 0, szData, strlen(szData), this, FUNMCMsgCB, &m_lHandle);
		}
	}
}

BOOL CDlgTransData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitComb();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTransData::InitComb()
{
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	mapVehicleBaseIter iterB = mapDev.begin();
	mapVehicleBaseIter iterE = mapDev.end();
	int nIndex = 0;
	while(iterE !=  iterB)
	{
		CVehicleBase* pVehi = iterB->second;
		if (pVehi != NULL)
		{
			m_cmbDev.InsertString(nIndex, pVehi->GetShowName());
			m_cmbDev.SetItemData(nIndex, DWORD(pVehi));
			nIndex++;
		}
		iterB++;
	}
	if (m_cmbDev.GetCount()>0)
	{
		m_cmbDev.SetCurSel(0);
	}
}

void CDlgTransData::FUNMCMsgCB(GPSMCMsg_S* pMsg, void* pUsr)
{
	CDlgTransData* pThis = (CDlgTransData*)pUsr;
	pThis->DoMCMsgCB(pMsg);
}

void CDlgTransData::DoMCMsgCB(GPSMCMsg_S* pMsg)
{
	if (m_hWnd == NULL || FALSE == ::SendMessage(m_hWnd, WM_APPROVE_RESULT, 0, (LPARAM)pMsg))
	{
		NETCLIENT_MCReleaseMsg(pMsg);
	}
}
void CDlgTransData::EnableCtrl(BOOL bEnable)
{
	GetDlgItem(IDC_BUTTON_SET)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SET_SEND)->EnableWindow(bEnable);
	m_cmbDev.EnableWindow(bEnable);
}

void CDlgTransData::OnDestroy() 
{
	CDialog::OnDestroy();
	
}


LRESULT CDlgTransData::OnResult(WPARAM wParam, LPARAM lParam)
{
	GPSMCMsg_S* pMsg =(GPSMCMsg_S*)lParam;
	if (GPS_OK == pMsg->nResult)
	{
		AfxMessageBox(_T("success"));
		//MSG_BOX_ID(ID_STR_CMD_SEND_SUCCESS);
		//TaskSubmit();
	}
	else
	{
		AfxMessageBox(_T("fail"));
		//MSG_BOX_ID(ID_STR_CMD_SEND_FAILED);
	}
	EnableCtrl(TRUE);
	return FALSE;
}
