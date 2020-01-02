
#pragma once

#include "PictureEx.h"

// Ê¾Àý:CWndLoadingBase* p = new CWndLoadingBase;
//      p->Create(NULL, NULL, WS_VISIBLE|WS_CHILD, CRect(), this, 0);

class CWndLoadingBase : public CWnd
{
// Construction
public:
	CWndLoadingBase(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWndLoadingBase();

	CPictureEx	m_stcGif;
protected:


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:

	void StartShow(CWnd* pAlternateOwner = NULL);
	void StopShow();
	BOOL IsShow();
	void CloseLoading();

	void SetThreadHandle(const HANDLE& hHandle, DWORD dwMilliseconds);

	void SetShow(BOOL bShow, CWnd* pAlternateOwner = NULL);
protected:
	BOOL InitDialog();

	void InitCtrl();
	
	static DWORD WINAPI ThreadExeFun(PVOID lParam);
protected:
	CFont m_FontTip;

	HANDLE m_hHandle;
	DWORD m_dwMilliseconds;
	BOOL m_bOpenHandle;
	BOOL m_bClose;
};