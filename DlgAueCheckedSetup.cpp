// DlgVerifySetup.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgAueCheckedSetup.h"
#include "afxdialogex.h"
#include "DlgParamerConf.h"


// CDlgVerifySetup 对话框

IMPLEMENT_DYNAMIC(CDlgAueCheckedSetup, CDialog)

CDlgAueCheckedSetup::CDlgAueCheckedSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAueCheckedSetup::IDD, pParent)
{

}

CDlgAueCheckedSetup::~CDlgAueCheckedSetup()
{
}

void CDlgAueCheckedSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ALCOHOL_CHECKED, m_cmbAlcohol);
	DDX_Control(pDX, IDC_COMBO_FINGERPRINT_CHECKED, m_cmbFingerprint);
	DDX_Control(pDX, IDC_COMBO_FACE_CHECKED, m_cmbFace);
}


BEGIN_MESSAGE_MAP(CDlgAueCheckedSetup, CDialog)
	ON_BN_CLICKED(IDC_BTN_GET_PARAM, &CDlgAueCheckedSetup::OnBnClickedBtnGetParam)
	ON_BN_CLICKED(IDC_BTN_SET_PARAM, &CDlgAueCheckedSetup::OnBnClickedBtnSetParam)
END_MESSAGE_MAP()


// CDlgVerifySetup 消息处理程序


BOOL CDlgAueCheckedSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadLanguage();
	InitCmbControl(m_cmbAlcohol);
	InitCmbControl(m_cmbFingerprint);
	InitCmbControl(m_cmbFace);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgAueCheckedSetup::LoadLanguage()
{
// 	SetDlgItemText(IDC_ST_ALCOHOL_CHECKED, LOADSTRINGEX(ID_STR_AUE_ALCOHOL_CHK));
// 	SetDlgItemText(IDC_ST_FINGERPRINT_CHECKED, LOADSTRINGEX(ID_STR_AUE_FINGERPRINT_CHK));
// 	SetDlgItemText(IDC_ST_FACE_CHECKED, LOADSTRINGEX(ID_STR_AUE_FACE_CHK));
}

void CDlgAueCheckedSetup::InitCmbControl( CComboBox& cmb )
{
	cmb.ResetContent();
	InsertCComboBoxData(cmb, _T("Checked"), 0);
	InsertCComboBoxData(cmb, _T("No Checked"), 1);
	cmb.SetCurSel(0);
}

BOOL CDlgAueCheckedSetup::SetConfig()
{
	BOOL bRet = FALSE;
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

BOOL CDlgAueCheckedSetup::GetConfig( BOOL& bGetRet )
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

void CDlgAueCheckedSetup::FillGetReq( char* pBuf, int& nSize )
{
	CString str;
	str.Format(_T("<Parameter><LOGIN_CONFIG Action=\"get\"  alcohol_checked=\"?\" fingerprint_checked=\"?\" face_checked=\"?\"></LOGIN_CONFIG></Parameter>"));
	strncpy(pBuf, CStringA(str), 1024);
	DEBUGTraceOutput(_T("%s"), pBuf);
	nSize = str.GetLength();

}

void CDlgAueCheckedSetup::FillSetReq( char* pBuf, int& nSize )
{
	int nCheckAlcohol = m_cmbAlcohol.GetItemData(m_cmbAlcohol.GetCurSel());
	int nCheckFingerprint = m_cmbFingerprint.GetItemData(m_cmbFingerprint.GetCurSel());
	int nCheckFace = m_cmbFace.GetItemData(m_cmbFace.GetCurSel());
	
	CString str;
	str.Format(_T("<Parameter><LOGIN_CONFIG Action=\"set\" alcohol_checked=\"%d\" fingerprint_checked=\"%d\" face_checked=\"%d\"></LOGIN_CONFIG></Parameter>"),
		nCheckAlcohol, nCheckFingerprint, nCheckFace);
	strncpy(pBuf, CStringA(str.GetBuffer(0)), 1024);
	DEBUGTraceOutput(_T("%s"), pBuf);
	nSize = str.GetLength();

	
}

BOOL CDlgAueCheckedSetup::AnalyGetResp( const char* pBuf, int nSize )
{
	BOOL bRet = FALSE;
	if (pBuf && nSize)
	{
		DEBUGTraceOutput(_T("get---%s"), pBuf);

		int nCheckAlcohol = 0;
		int nCheckFingerprint = 0;
		int nCheckFace = 0;

		if (SearchSection2Int(pBuf, "alcohol_checked=", nCheckAlcohol)
			&& SearchSection2Int(pBuf, "fingerprint_checked=", nCheckFingerprint)
			&& SearchSection2Int(pBuf, "face_checked=", nCheckFace))
		{
			bRet = TRUE;
			SearchCmbData(m_cmbAlcohol, nCheckAlcohol, TRUE);
			SearchCmbData(m_cmbFingerprint, nCheckFingerprint, TRUE);
			SearchCmbData(m_cmbFace, nCheckFace, TRUE);
		}
	}

	return bRet;
}

void CDlgAueCheckedSetup::OnBnClickedBtnGetParam()
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

void CDlgAueCheckedSetup::OnBnClickedBtnSetParam()
{
	EnableCtrl(FALSE);
	BOOL bSetRet = SetConfig();
	EnableCtrl(TRUE);
	if (bSetRet)
	{
		AfxMessageBox(_T("Success!"));
	}
}

void CDlgAueCheckedSetup::EnableCtrl( BOOL bEnable )
{
	GetDlgItem(IDC_BTN_SET_PARAM)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_GET_PARAM)->EnableWindow(bEnable);
}
