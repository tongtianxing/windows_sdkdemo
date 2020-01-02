
#pragma once

#include "PictureEx.h"

/*
说明:Loading对话框基类
使用方法:继承并设置窗口ID
*/

class CDlgLoadingBase : public CDialog
{
// Construction
public:
	CDlgLoadingBase(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLoadingBase();

// Dialog Data
	//{{AFX_DATA(CDlgLoading)
	//enum { IDD = IDD_DLG_LOADING };
	CPictureEx	m_stcGif;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLoading)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLoading)
	virtual BOOL OnInitDialog() override;
	virtual void OnOK() override;
	virtual void OnCancel() override;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnMsgLoadClose(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	void StartShow(CWnd* pAlternateOwner = NULL);
	void StopShow();
	BOOL IsShow();
	void CloseLoading();

	void SetThreadHandle(const HANDLE& hHandle, DWORD dwMilliseconds);

	void SetShow(BOOL bShow, CWnd* pAlternateOwner = NULL);
protected:
	void InitCtrl();
	
	static DWORD WINAPI ThreadExeFun(PVOID lParam);
protected:
	CFont m_FontTip;

	HANDLE m_hHandle;
	DWORD m_dwMilliseconds;
	BOOL m_bOpenHandle;
	BOOL m_bClose;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
