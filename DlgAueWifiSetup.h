#pragma once
#include "afxwin.h"


// CDlgNetTypeAueWifi 对话框

class CDlgAueWifiSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgAueWifiSetup)

public:
	CDlgAueWifiSetup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAueWifiSetup();

// 对话框数据
	enum { IDD = IDD_DLG_AUE_WIFI_SETUP };
	CComboBox m_cmbChannel;
	CComboBox m_cmbMode;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL SetConfig();
	virtual BOOL GetConfig(BOOL& bGetRet);

	afx_msg void OnBnClickedBtnGetParam();
	afx_msg void OnBnClickedBtnSetParam();
	DECLARE_MESSAGE_MAP()

	void LoadLanguage();

	void FillGetReq(char* pBuf, int& nSize);
	void FillSetReq(char* pBuf, int& nSize);


	BOOL AnalyGetResp(const char* pBuf, int nSize);

	BOOL CheckParam();
	void EnableCtrl( BOOL bEnable );
public:
};
