#pragma once
#include "afxcmn.h"


// CDlgPanePtz 对话框

class CDlgPanePtz : public CDialog
{
	DECLARE_DYNAMIC(CDlgPanePtz)

public:
	CDlgPanePtz(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPanePtz();

// 对话框数据
	enum { IDD = IDD_DLG_PTZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	void OnBnClickedPtz(UINT nID);
	void PtzControl(int nCommand, int nParam = 0);
	BOOL CheckPoint();
	int GetPoint();

public:
	CSliderCtrl m_Slider;
	virtual BOOL OnInitDialog();
	int m_nPoint;
};
