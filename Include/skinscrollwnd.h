#if !defined(AFX_SKINSCROLLWND_H__891A5F44_7A55_46DF_8BD7_9C454283CE40__INCLUDED_)
#define AFX_SKINSCROLLWND_H__891A5F44_7A55_46DF_8BD7_9C454283CE40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinScrollWnd.h : header file
//
#include "SkinScrollBar.h"

/////////////////////////////////////////////////////////////////////////////
// CSkinScrollWnd window

#define SKINSCROLL_WND_PROP_KEY _T("__SkinScrollFrame__")

class CSkinScrollLimit : public CWnd
{
	DECLARE_DYNAMIC(CSkinScrollLimit)
public:
};

class CSkinScrollWnd : public CWnd, public CStateImgBase, public CTransparentWnd
{
	DECLARE_DYNAMIC(CSkinScrollWnd)

// Construction
public:
	CSkinScrollWnd();

// Attributes
private:
	BOOL		m_bInWndProc;
	HWND		m_hWndSkinnedCtrl;
	LONG_PTR	m_lpUserData;
public:
	int			m_nScrollWid;
	int			m_nBmpScrollWid;
	CSkinScrollBar	m_sbHorz,m_sbVert;
	CSkinScrollLimit m_wndLimit;
	HBITMAP		m_hBmpScroll;
	BOOL		m_bOp;
	int			m_nAngleType;
	BOOL		m_bResizingWnd;
	BOOL		m_bResizingBar;
// Operations
public:
	WNDPROC		m_funOldProc;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinScrollWnd)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SkinWindow(CWnd *pWnd, LPCTSTR szBmpPath);
	virtual ~CSkinScrollWnd();

	void SetUserData(LONG_PTR lpUserData) { m_lpUserData = lpUserData; }
	LONG_PTR GetUserData() const { return m_lpUserData; }

protected:
	BOOL m_bLastPaintTransparentDisabled;
	bool HasBorder() const;

	// Generated message map functions
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;
	afx_msg LRESULT OnDestMove(WPARAM wParam,LPARAM lParam);
	//{{AFX_MSG(CSkinScrollWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL		m_bLegacyMsg;
public:
	void SetLegacyMsg(BOOL bLegacy);
};

extern "C" BOOL UnskinWndScroll(CWnd *pWnd);

extern "C" CSkinScrollWnd* SkinWndScroll(CWnd *pWnd, LPCTSTR szBmpPath);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSCROLLWND_H__891A5F44_7A55_46DF_8BD7_9C454283CE40__INCLUDED_)
