// DlgAueAlcoholSetup.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgAueAlcoholSetup.h"
#include "afxdialogex.h"
#include "DlgParamerConf.h"


#define RANGE_MIN_VALUE		0
#define RANGE_MAX_VALUE		255
// CDlgAueAlcoholSetup 对话框

IMPLEMENT_DYNAMIC(CDlgAueAlcoholSetup, CDialog)

CDlgAueAlcoholSetup::CDlgAueAlcoholSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAueAlcoholSetup::IDD, pParent)
{

}

CDlgAueAlcoholSetup::~CDlgAueAlcoholSetup()
{
}

void CDlgAueAlcoholSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAueAlcoholSetup, CDialog)
	ON_BN_CLICKED(IDC_BTN_GET_PARAM, &CDlgAueAlcoholSetup::OnBnClickedBtnGetParam)
	ON_BN_CLICKED(IDC_BTN_SET_PARAM, &CDlgAueAlcoholSetup::OnBnClickedBtnSetParam)
END_MESSAGE_MAP()


// CDlgAueAlcoholSetup 消息处理程序


BOOL CDlgAueAlcoholSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadLanguage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgAueAlcoholSetup::LoadLanguage()
{
// 	SetDlgItemText(IDC_ST_THRESHOLD, LOADSTRINGEX(ID_STR_AUE_THRESHOLD));
// 	SetDlgItemText(IDC_ST_ALCOHOL, LOADSTRINGEX(ID_STR_AUE_ALCOHOL));
}

BOOL CDlgAueAlcoholSetup::SetConfig()
{
	BOOL bRet = FALSE;
	if (!CheckParam())
	{
		AfxMessageBox(_T("ERR1!"));
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

BOOL CDlgAueAlcoholSetup::GetConfig( BOOL& bGetRet )
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

BOOL CDlgAueAlcoholSetup::AnalyGetResp( const char* pBuf, int nSize )
{
	BOOL bRet = FALSE;
	if (pBuf && nSize)
	{
		DEBUGTraceOutput(_T("get---%s"), pBuf);

		int nThreshold = 0;
		int nAlcohol = 0;

		if (SearchSection2Int(pBuf, "threshold=", nThreshold)
			&& SearchSection2Int(pBuf, "alcohol=", nAlcohol))
		{
			bRet = TRUE;
			nThreshold = min(max(RANGE_MIN_VALUE, nThreshold), RANGE_MAX_VALUE);
			nAlcohol = min(max(RANGE_MIN_VALUE, nAlcohol), RANGE_MAX_VALUE);
			SetDlgItemInt(IDC_ED_THRESHOLD, nThreshold);
			SetDlgItemInt(IDC_ED_ALCOHOL, nAlcohol);
			//SearchCmbData()
		}
	}

	return bRet;
}

void CDlgAueAlcoholSetup::FillGetReq( char* pBuf, int& nSize )
{
	CString str;
	str.Format(_T("<Parameter><ALCOHOL Action=\"get\"  threshold=\"?\" alcohol=\"?\"></ALCOHOL></Parameter>"));
	strncpy(pBuf, CStringA(str), 1024);
	DEBUGTraceOutput(_T("%s"), pBuf);
	nSize = str.GetLength();
}

void CDlgAueAlcoholSetup::FillSetReq( char* pBuf, int& nSize )
{
	int nThreshold = GetDlgItemInt(IDC_ED_THRESHOLD);
	int nAlcohol = GetDlgItemInt(IDC_ED_ALCOHOL);

	CString str;
	str.Format(_T("<Parameter><ALCOHOL Action=\"set\" threshold=\"%d\" alcohol=\"%d\"></ALCOHOL></Parameter>"),
		nThreshold, nAlcohol);
	strncpy(pBuf, CStringA(str.GetBuffer(0)), 1024);
	DEBUGTraceOutput(_T("%s"), pBuf);
	nSize = str.GetLength();

}

BOOL CDlgAueAlcoholSetup::CheckParam()
{
	int nThreshold = GetDlgItemInt(IDC_ED_THRESHOLD);
	int nAlcohol = GetDlgItemInt(IDC_ED_ALCOHOL);
	if (nThreshold < RANGE_MIN_VALUE || nThreshold > RANGE_MAX_VALUE
		|| nAlcohol < RANGE_MIN_VALUE || nAlcohol > RANGE_MAX_VALUE)
	{
		return FALSE;
	}
	return TRUE;

}


void CDlgAueAlcoholSetup::OnBnClickedBtnGetParam()
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


void CDlgAueAlcoholSetup::OnBnClickedBtnSetParam()
{
	EnableCtrl(FALSE);
	BOOL bSetRet = SetConfig();
	EnableCtrl(TRUE);
	if (bSetRet)
	{
		AfxMessageBox(_T("Success!"));
	}
}

void CDlgAueAlcoholSetup::EnableCtrl( BOOL bEnable )
{
	GetDlgItem(IDC_BTN_SET_PARAM)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_GET_PARAM)->EnableWindow(bEnable);
}
