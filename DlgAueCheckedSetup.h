#pragma once
#include "afxwin.h"


// CDlgVerifySetup 对话框

class CDlgAueCheckedSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgAueCheckedSetup)

public:
	CDlgAueCheckedSetup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAueCheckedSetup();

// 对话框数据
	enum { IDD = IDD_DLG_AUE_CHECKED_SETUP };
	CComboBox m_cmbAlcohol;
	CComboBox m_cmbFingerprint;
	CComboBox m_cmbFace;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL SetConfig();
	virtual BOOL GetConfig(BOOL& bGetRet);

	afx_msg void OnBnClickedBtnGetParam();
	afx_msg void OnBnClickedBtnSetParam();
	DECLARE_MESSAGE_MAP()

	void LoadLanguage();
	void InitCmbControl(CComboBox& cmb);

	void FillGetReq(char* pBuf, int& nSize);
	void FillSetReq(char* pBuf, int& nSize);


	BOOL AnalyGetResp(const char* pBuf, int nSize);

	void EnableCtrl( BOOL bEnable );
public:
};
