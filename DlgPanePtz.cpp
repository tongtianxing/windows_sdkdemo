// DlgPanePtz.cpp : 实现文件
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPanePtz.h"
#include "afxdialogex.h"
#include "clientdemoDlg.h"


// CDlgPanePtz 对话框

IMPLEMENT_DYNAMIC(CDlgPanePtz, CDialog)

CDlgPanePtz::CDlgPanePtz(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPanePtz::IDD, pParent)
	, m_nPoint(1)
{

}

CDlgPanePtz::~CDlgPanePtz()
{
}

void CDlgPanePtz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Text(pDX, IDC_ED_POINT, m_nPoint);
	DDV_MinMaxInt(pDX, m_nPoint, 1, 128);
}


BEGIN_MESSAGE_MAP(CDlgPanePtz, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_PTZ1, IDC_BTN_PTZ1+100, OnBnClickedPtz)
END_MESSAGE_MAP()


// CDlgPanePtz 消息处理程序


void CDlgPanePtz::OnBnClickedPtz( UINT nID )
{
	switch (nID)
	{
	case IDC_BTN_PTZ1:
		PtzControl(GPS_PTZ_MOVE_LEFT_TOP);
		break;
	case IDC_BTN_PTZ2:
		PtzControl(GPS_PTZ_MOVE_TOP);
		break;
	case IDC_BTN_PTZ3:
		PtzControl(GPS_PTZ_MOVE_RIGHT_TOP);
		break;
	case IDC_BTN_PTZ4:
		PtzControl(GPS_PTZ_MOVE_LEFT);
		break;
	case IDC_BTN_PTZ5:
		//PtzControl(GPS_PTZ_MOVE_LEFT_TOP);
		break;
	case IDC_BTN_PTZ6:
		PtzControl(GPS_PTZ_MOVE_RIGHT);
		break;
	case IDC_BTN_PTZ7:
		PtzControl(GPS_PTZ_MOVE_LEFT_BOTTOM);
		break;
	case IDC_BTN_PTZ8:
		PtzControl(GPS_PTZ_MOVE_BOTTOM);
		break;
	case IDC_BTN_PTZ9:
		PtzControl(GPS_PTZ_MOVE_RIGHT_BOTTOM);
		break;
	case IDC_BTN_PTZ10:
		PtzControl(GPS_PTZ_FOCUS_DEL);
		break;
	case IDC_BTN_PTZ11:
		PtzControl(GPS_PTZ_FOCUS_ADD);
		break;
	case IDC_BTN_PTZ12:
		PtzControl(GPS_PTZ_LIGHT_DEL);
		break;
	case IDC_BTN_PTZ13:
		PtzControl(GPS_PTZ_LIGHT_ADD);
		break;
	case IDC_BTN_PTZ14:
		PtzControl(GPS_PTZ_ZOOM_DEL);
		break;
	case IDC_BTN_PTZ15:
		PtzControl(GPS_PTZ_ZOOM_ADD);
		break;
	case IDC_BTN_PTZ_LIGHT_OPEN:
		PtzControl(GPS_PTZ_LIGHT_OPEN);
		break;
	case IDC_BTN_PTZ_LIGHT_CLOSE:
		PtzControl(GPS_PTZ_LIGHT_CLOSE);
		break;
	case IDC_BTN_PTZ_WIPER_OPEN:
		PtzControl(GPS_PTZ_WIPER_OPEN);
		break;
	case IDC_BTN_PTZ_WIPER_CLOSE:
		PtzControl(GPS_PTZ_WIPER_CLOSE);
		break;
	case IDC_BTN_PTZ_MOVE:
		if (CheckPoint())
		{
			PtzControl(GPS_PTZ_PRESET_MOVE, GetPoint());
		}
		break;
	case IDC_BTN_PTZ_SET:
		if (CheckPoint())
		{
			PtzControl(GPS_PTZ_PRESET_SET, GetPoint());
		}
		break;
	case IDC_BTN_PTZ_DEL:
		if (CheckPoint())
		{
			PtzControl(GPS_PTZ_PRESET_DEL, GetPoint());
		}
		break;
	}
}

void CDlgPanePtz::PtzControl( int nCommand, int nParam /*= 0*/ )
{
	CClientdemoDlg* pMainDlg = (CClientdemoDlg*)GetParent();
	pMainDlg->PtzControl(nCommand, nParam, m_Slider.GetPos());
}


BOOL CDlgPanePtz::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Slider.SetRange(GPS_PTZ_SPEED_MIN, GPS_PTZ_SPEED_MAX);
	m_Slider.SetPos(127);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_ED_POINT);
	if (pEdit)
	{
		pEdit->LimitText(3);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int CDlgPanePtz::GetPoint()
{
	return GetDlgItemInt(IDC_ED_POINT);;
}

BOOL CDlgPanePtz::CheckPoint()
{
	int nPoint = GetDlgItemInt(IDC_ED_POINT);
	if (nPoint < 1 || nPoint > 128)
	{
		CString strTemp;
		strTemp.Format(_T("Point[%d] Error!Range(%d~%d)"), nPoint, 1, 128);
		AfxMessageBox(strTemp);
		return FALSE;
	}
	return TRUE;
}
