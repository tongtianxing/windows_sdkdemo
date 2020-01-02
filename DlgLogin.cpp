// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog

#define WM_MSG_LOGIN		WM_USER + 0x1000
#define WM_MSG_LOAD			WM_USER + 0x1001


CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogin)
//#ifdef _DEBUG

	m_strUser = _T("rcmadmin");
	m_strPsw = _T("000000");
	m_strIP = _T("114.55.118.196");

// #else
// 	m_strUser = _T("han1");
// 	m_strIP = _T("192.168.0.148");
// #endif
	m_usSvrPort = 6605;
	m_bLogining = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogin)
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_PSW, m_strPsw);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	//{{AFX_MSG_MAP(CDlgLogin)
	ON_MESSAGE(WM_MSG_LOGIN, OnMsgLogin)
	ON_MESSAGE(WM_MSG_LOAD, OnMsgLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin message handlers

void CDlgLogin::OnOK() 
{
	// TODO: Add extra validation here

	CWaitCursor wait;
 	if (!m_bLogining)
	{
		if (!UpdateData())
		{
			return ;
		}
		
		m_strUser.TrimLeft();
		m_strUser.TrimRight();
		m_strIP.TrimLeft();
		m_strIP.TrimRight();
		if (m_strUser.IsEmpty() || m_strIP.IsEmpty())
		{
			AfxMessageBox(_T("Name or Server ip is empty."));
			return ;
		}
				
		NETCLIENT_RegLoginMsg(this, FUNLoginMsgCB);
		int nEr  = NETCLIENT_LoginDirSvr(CStringA(m_strIP), m_usSvrPort, "", 
			CStringA(m_strUser), CStringA(m_strPsw), 1);
// 		m_strIP.ReleaseBuffer();
// 		m_strUser.ReleaseBuffer();
// 		m_strPsw.ReleaseBuffer();
//		NETCLIENT_SetUserSvrInfo(m_strIP.GetBuffer(0), m_usSvrPort);
//		PostMessage(WM_MSG_LOGIN, GPS_LOGIN_SUC, 0);
		theApp.SetLoginInfo(m_strIP, m_usSvrPort, _T(""), m_strUser, m_strPsw);
		m_bLogining = true;
		EnableCtrl(FALSE);
		m_bLoginSuc = FALSE;
	}
	else
	{
		NETCLIENT_RegLoginMsg(NULL, NULL);
		NETCLIENT_LogoutDirSvr();
		if (m_bLoginSuc)
		{
			m_loadThread.StopDeviceLoad();
			m_bLoginSuc = FALSE;
		}
		m_bLogining = false;
		EnableCtrl(TRUE);
	}

	
//	CDialog::OnOK();
}

void CDlgLogin::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDlgLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szBuf[10] = {0};
	int n = szBuf[9]-szBuf[0];
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLogin::EnableCtrl(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_USER)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PSW)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_IP)->EnableWindow(bEnable);
	GetDlgItem(IDOK)->EnableWindow(bEnable);
	GetDlgItem(IDCANCEL)->EnableWindow(bEnable);
}

void CDlgLogin::FUNLoginMsgCB(int nMsg, void * pUsr)
{
	CDlgLogin* pThis = (CDlgLogin*)pUsr;
	pThis->DoLoginMsgCB(nMsg);
}

void CDlgLogin::DoLoginMsgCB(int nMsg)
{
	PostMessage(WM_MSG_LOGIN, nMsg);
}

LRESULT CDlgLogin::OnMsgLogin(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case GPS_LOGIN_SUC:
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_CNT_SUC));
	//	theApp.SetSvrIP(m_strIP, GetSvrPort());
		CSvrVer::GetInstance()->SetSvrVer(NETCLIENT_GetSvrVersion());
		m_bLoginSuc = TRUE;
		m_loadThread.SetLoadMsg(GetSafeHwnd(), WM_MSG_LOAD);
		m_loadThread.StartDeviceLoad(FALSE);
		break;
	case GPS_LOGIN_FAILED:
		//	SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_CNT_ERR));
		//	m_stInfo.SetWindowText(LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_CNT_ERR));
		//		UpdateText();
//		OnLoginFailed(LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_CNT_ERR));
		break;
	case GPS_LOGIN_DISCNT:
		//SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_USR_ERR));
		//	UpdateText();
		break;
	case GPS_LOGIN_NAME_ERR:
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_USR_ERR));
		//		UpdateText();
	//	m_cmbUser.SetFocus();
	//	OnLoginFailed(LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_USR_ERR));
		break;
	case GPS_LOGIN_PWD_ERR:
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_PWD_ERR));
		//		UpdateText();
	//	OnLoginFailed(LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_PWD_ERR));
		break;
	case GPS_LOGIN_FULL_ERR:
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_FULL_ERR));
		//		UpdateText();
	//	OnLoginFailed(LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_FULL_ERR));
		break;
	case GPS_LOGIN_VER_ERR:
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_VER_ERR));
		//		UpdateText();
	//	DoVersionError();
		break;
		//	case GPS_LOGIN_EXIST:
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_EXIST));
		//		UpdateText();
		//		OnLoginFailed();
		//		break;
	case GPS_LOGIN_USR_DEL:
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_USER_DEL));
		//		UpdateText();
	//	OnLoginFailed(LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_USER_DEL));
		break;
	case GPS_LOGIN_EXPIRED:
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_USER_EXPIRED));
		//		UpdateText();
	//	OnLoginFailed(LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_USER_EXPIRED));
		break;
	case GPS_LOGIN_SERVER_EMPTY:
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_EXPIRED_TIP_FULL_EMPTY_ERR));
		//		UpdateText();
	//	OnLoginFailed(LOADSTRINGEX(ID_STR_DLG_EXPIRED_TIP_FULL_EMPTY_ERR));
		break;
	default:	
		//		SetDlgItemText(IDC_ST_INFO, LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_CNT_ERR));
		//		UpdateText();
	//	OnLoginFailed(LOADSTRINGEX(ID_STR_DLG_LOGIN_TIP_CNT_ERR));
		break;
	}

	if (wParam != GPS_LOGIN_SUC)
	{

		CString str;
		str.Format(_T("login fail error %d"), wParam);
		AfxMessageBox(str);
		EnableCtrl(TRUE);
	}
	
	UpdateData(FALSE);
	return 0;
}

LRESULT CDlgLogin::OnMsgLoad(WPARAM wParam, LPARAM lParam)
{
	if (!m_bLogining)
	{
		return 0;
	}
	
	switch(wParam)
	{
	case LOAD_ING:
		break;
	case LOAD_FAILED:
		AfxMessageBox(_T("load fail"));
		EnableCtrl(TRUE);
		break;
	case LOAD_FINISHED:
		NETCLIENT_RegLoginMsg(NULL, NULL);
		CDialog::OnOK();
		break;
	case LOAD_CONFIG_SUC:
		PostMessage(WM_MSG_LOAD, LOAD_FINISHED);
		break;
		
	}
	
	return 0;
}
