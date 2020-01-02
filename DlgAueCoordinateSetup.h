#pragma once
#include "afxwin.h"


// CDlgAueCoordinateSetup 对话框

class CDlgAueCoordinateSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgAueCoordinateSetup)

public:
	CDlgAueCoordinateSetup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAueCoordinateSetup();

// 对话框数据
	enum { IDD = IDD_DLG_AUE_COORDINATE_SETUP };
	CComboBox m_cmbMapType;
	CButton m_btnOK;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual void OnCancel();

	afx_msg void OnBnClickedBtnOk();
	DECLARE_MESSAGE_MAP()

	void LoadLanguage();
	BOOL CheckParam();

	void FillSetReq(char* pBuf, int& nSize);
public:
};
