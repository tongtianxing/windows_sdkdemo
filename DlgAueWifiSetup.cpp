// DlgNetTypeAueWifi.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgAueWifiSetup.h"
#include "afxdialogex.h"
#include "DlgParamerConf.h"


// CDlgNetTypeAueWifi 对话框

IMPLEMENT_DYNAMIC(CDlgAueWifiSetup, CDialog)

CDlgAueWifiSetup::CDlgAueWifiSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAueWifiSetup::IDD, pParent)
{

}

CDlgAueWifiSetup::~CDlgAueWifiSetup()
{
}

void CDlgAueWifiSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMBO_MODE, m_cmbMode);
}


BEGIN_MESSAGE_MAP(CDlgAueWifiSetup, CDialog)
	ON_BN_CLICKED(IDC_BTN_GET_PARAM, &CDlgAueWifiSetup::OnBnClickedBtnGetParam)
	ON_BN_CLICKED(IDC_BTN_SET_PARAM, &CDlgAueWifiSetup::OnBnClickedBtnSetParam)
END_MESSAGE_MAP()


// CDlgNetTypeAueWifi 消息处理程序


BOOL CDlgAueWifiSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadLanguage();

	reinterpret_cast<CEdit*>(GetDlgItem(IDC_ED_SSID))->LimitText(64);
	reinterpret_cast<CEdit*>(GetDlgItem(IDC_ED_PASSWORD))->LimitText(32);

	CString strTemp;
	for (int i=0; i<13; i++)
	{
		strTemp.Format(_T("%d"), i+1);
		InsertCComboBoxData(m_cmbChannel, strTemp, i);
	}
	m_cmbChannel.SetCurSel(0);

	InsertCComboBoxData(m_cmbMode, _T("AP mode"), 0);
	InsertCComboBoxData(m_cmbMode, _T("STATION mode"), 1);
	m_cmbMode.SetCurSel(0);

#ifdef _DEBUG
	AnalyGetResp("<Parameter len=\"0\"><WIFI Action=\"get\" mode=\"0\" SSID=\"test\" password=\"12345678\" channel=\"1\"></WIFI></Prameter>", 1);
	
#endif // _DEBUG

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgAueWifiSetup::LoadLanguage()
{
// 	SetDlgItemText(IDC_ST_PASSWORD, LOADSTRINGEX(ID_STR_PASSWORD));
// 	SetDlgItemText(IDC_ST_CHANNEL, LOADSTRINGEX(ID_STR_AUE_CHANNEL));
// 	SetDlgItemText(IDC_ST_MODE, LOADSTRINGEX(ID_STR_AUE_MODE));

}

BOOL CDlgAueWifiSetup::SetConfig()
{
	BOOL bRet = FALSE;
	if (!CheckParam())
	{
		return FALSE;
	}
	MDVRConfigData_S InConfig = {0};
	MDVRConfigData_S OutConfig = {0};
	FillSetReq(InConfig.cBuffer, InConfig.nLength);
	if (g_pfnTransparentConfig(0, &InConfig, &OutConfig, g_pTransparentUser))
	{
		int nResult = 0;
		//if (AnalySetResp(nResult, OutConfig.cBuffer, OutConfig.nLength) && nResult)
		{
			bRet = TRUE;
		}
	}
	//Invalidate();
	return bRet;
}

BOOL CDlgAueWifiSetup::GetConfig( BOOL& bGetRet )
{
	BOOL bRet = FALSE;
	MDVRConfigData_S InConfig = {0};
	MDVRConfigData_S OutConfig = {0};
	FillGetReq(InConfig.cBuffer, InConfig.nLength);
	bGetRet = g_pfnTransparentConfig(0, &InConfig, &OutConfig, g_pTransparentUser);
	if (bGetRet)
	{
		bRet = AnalyGetResp(OutConfig.cBuffer, OutConfig.nLength);
	}
	return bRet;
}

BOOL CDlgAueWifiSetup::AnalyGetResp( const char* pBuf, int nSize )
{
	BOOL bRet = FALSE;
	if (pBuf && nSize)
	{
		DEBUGTraceOutput(_T("get---%s"), pBuf);

		CString strSSID;
		CString strPassword;
		int nMode = 0;
		int nChannel = 0;

		if (SearchSection2Str(pBuf, "SSID=", strSSID)
			&& SearchSection2Str(pBuf, "password=", strPassword)
			&& SearchSection2Int(pBuf, "channel=", nChannel)
			&& SearchSection2Int(pBuf, "mode=", nMode))
		{
			bRet = TRUE;
			SetDlgItemText(IDC_ED_SSID, strSSID);
			SetDlgItemText(IDC_ED_PASSWORD, strPassword);
			SearchCmbData(m_cmbChannel, nChannel, TRUE);
			SearchCmbData(m_cmbMode, nMode, TRUE);
		}
	}

	return bRet;
}

void CDlgAueWifiSetup::FillGetReq( char* pBuf, int& nSize )
{
	CString str;
	str.Format(_T("<Parameter><WIFI Action=\"get\" mode=\"?\" SSID=\"?\" password=\"?\" channel=\"?\"></WIFI></Parameter>"));
	strncpy(pBuf, CStringA(str), 1024);
	DEBUGTraceOutput(_T("%s"), pBuf);
	nSize = str.GetLength();
}

void CDlgAueWifiSetup::FillSetReq( char* pBuf, int& nSize )
{
	CString strSSID;
	CString strPassword;
	int nMode = 0;
	int nChannel = 0;
	GetDlgItemText(IDC_ED_SSID, strSSID);
	GetDlgItemText(IDC_ED_PASSWORD, strPassword);
	nMode = m_cmbMode.GetItemData(m_cmbMode.GetCurSel());
	nChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

	CString str;
	str.Format(_T("<Parameter><WIFI Action=\"set\" mode=\"%d\" SSID=\"%s\" password=\"%s\" channel=\"%d\"></WIFI></Parameter>"),
		nMode, strSSID, strPassword, nChannel);
	strncpy(pBuf, CStringA(str.GetBuffer(0)), 1024);
	DEBUGTraceOutput(_T("%s"), pBuf);
	nSize = str.GetLength();
}

BOOL CDlgAueWifiSetup::CheckParam()
{
	CString strPassword;
	GetDlgItemText(IDC_ED_PASSWORD, strPassword);
	if (!strPassword.IsEmpty() && strPassword.GetLength() < 8)
	{
		AfxMessageBox(_T("ERR1!"));
		GetDlgItem(IDC_ED_PASSWORD)->SetFocus();
		return FALSE;
	}
	if (m_cmbMode.GetCurSel() == CB_ERR
		|| m_cmbChannel.GetCurSel() == CB_ERR)
	{
		AfxMessageBox(_T("ERR2!"));
		return FALSE;
	}
	return TRUE;
}


void CDlgAueWifiSetup::OnBnClickedBtnGetParam()
{
	BOOL bGetRet = FALSE;
	EnableCtrl(FALSE);
	GetConfig(bGetRet);
	EnableCtrl(TRUE);
	if (bGetRet)
	{
		AfxMessageBox(_T("Success!"));
	}
}


void CDlgAueWifiSetup::OnBnClickedBtnSetParam()
{
	EnableCtrl(FALSE);
	BOOL bSetRet = SetConfig();
	EnableCtrl(TRUE);
	if (bSetRet)
	{
		AfxMessageBox(_T("Success!"));
	}
}

void CDlgAueWifiSetup::EnableCtrl( BOOL bEnable )
{
	GetDlgItem(IDC_BTN_SET_PARAM)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_GET_PARAM)->EnableWindow(bEnable);
}
