// DlgAueCoordinateSetup.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgAueCoordinateSetup.h"
#include "afxdialogex.h"
#include "DlgParamerConf.h"


extern int g_nMapType;
extern CString g_strJingDu;
extern CString g_strWeiDu;
// CDlgAueCoordinateSetup 对话框

IMPLEMENT_DYNAMIC(CDlgAueCoordinateSetup, CDialog)

CDlgAueCoordinateSetup::CDlgAueCoordinateSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAueCoordinateSetup::IDD, pParent)
{

}

CDlgAueCoordinateSetup::~CDlgAueCoordinateSetup()
{
}

void CDlgAueCoordinateSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MAPTYPE, m_cmbMapType);
	DDX_Control(pDX, IDC_BTN_OK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CDlgAueCoordinateSetup, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CDlgAueCoordinateSetup::OnBnClickedBtnOk)
END_MESSAGE_MAP()


// CDlgAueCoordinateSetup 消息处理程序


BOOL CDlgAueCoordinateSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadLanguage();

	InsertCComboBoxData(m_cmbMapType, _T("Google"), 0);
	InsertCComboBoxData(m_cmbMapType, _T("Baudu"), 1);
	m_cmbMapType.SetCurSel((g_nMapType == 3) ? 1 : 0);

	SetDlgItemText(IDC_ED_JINGDU, g_strJingDu);
	SetDlgItemText(IDC_ED_WEIDU, g_strWeiDu);


	reinterpret_cast<CEdit*>(GetDlgItem(IDC_ED_JINGDU))->LimitText(16);
	reinterpret_cast<CEdit*>(GetDlgItem(IDC_ED_WEIDU))->LimitText(16);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgAueCoordinateSetup::LoadLanguage()
{
	SetDlgItemText(IDC_BTN_OK, _T("Send"));
}

void CDlgAueCoordinateSetup::OnBnClickedBtnOk()
{
	if (!CheckParam())
	{
		return ;
	}
	
	GetDlgItem(IDC_BTN_OK)->EnableWindow(FALSE);
	MDVRConfigData_S InConfig = {0};
	MDVRConfigData_S OutConfig = {0};
	FillSetReq(InConfig.cBuffer, InConfig.nLength);
	if (g_pfnTransparentConfig(0, &InConfig, &OutConfig, g_pTransparentUser))
	{
		int nResult = 0;
		AfxMessageBox(_T("OK!"));
		//if (AnalySetResp(nResult, OutConfig.cBuffer, OutConfig.nLength) && nResult)
		//{
		//	MSG_BOX_ID(ID_STR_SETPARASUC);
		//}
		//else
		//{
		//	MSG_BOX_ID(ID_STR_SETPARAFAIL);
		//}
	}
	GetDlgItem(IDC_BTN_OK)->EnableWindow();
}

BOOL CDlgAueCoordinateSetup::CheckParam()
{
	if (m_cmbMapType.GetCurSel() == CB_ERR)
	{
		AfxMessageBox(_T("ERR1"));
		return FALSE;
	}
	CString strTemp;
	GetDlgItemText(IDC_ED_JINGDU, strTemp);	
	double lfJingDu = _ttof(strTemp);
	if (!StringIsFloat(strTemp) || lfJingDu < -180 || lfJingDu > 180)
	{
		AfxMessageBox(_T("ERR2"));
		GetDlgItem(IDC_ED_JINGDU)->SetFocus();
		return FALSE;
	}

	GetDlgItemText(IDC_ED_WEIDU, strTemp);
	double lfWeiDu = _ttof(strTemp);
	if (!StringIsFloat(strTemp) || lfWeiDu < -90 || lfWeiDu > 90)
	{
		AfxMessageBox(_T("ERR3"));
		GetDlgItem(IDC_ED_WEIDU)->SetFocus();
		return FALSE;
	}

	return TRUE;
}

void CDlgAueCoordinateSetup::FillSetReq( char* pBuf, int& nSize )
{
	int nMapType = m_cmbMapType.GetItemData(m_cmbMapType.GetCurSel());
	double lfJingDu, lfWeiDu;
	CString strTemp;
	GetDlgItemText(IDC_ED_JINGDU, strTemp);
	lfJingDu = _ttof(strTemp);
	GetDlgItemText(IDC_ED_WEIDU, strTemp);
	lfWeiDu = _ttof(strTemp);

	CString str;
	str.Format(_T("<Parameter><DESTINATION_INFO Action=\"set\" map_type=\"%d\" latitude=\"%.6lf\" longtitude =\"%.6lf\"></DESTINATION_INFO ></Parameter>"),
		nMapType, lfJingDu, lfWeiDu);
	strncpy(pBuf, CStringA(str.GetBuffer(0)), 1024);
	DEBUGTraceOutput(_T("%s"), pBuf);
	nSize = str.GetLength();
	
}

void CDlgAueCoordinateSetup::OnCancel()
{

}
