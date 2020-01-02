#if !defined(AFX_PVVIEWWND_H__3F4E53C6_C1C1_438F_9B10_FC24075167A4__INCLUDED_)
#define AFX_PVVIEWWND_H__3F4E53C6_C1C1_438F_9B10_FC24075167A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PVViewWnd.h : header file
//

#include "PVVideoWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CPVViewWnd window

class CPVViewWnd : public CWnd
{
// Construction
public:
	CPVViewWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPVViewWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPVViewWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPVViewWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CPVVideoWnd&	GetVideoWnd() {	return m_VideoWnd; }
	void	SetPVFrameWnd(CPVFrameWnd* pPVFrameWnd) {	m_pPVFrameWnd = pPVFrameWnd;}
	void	SetActive(BOOL bActive);
	BOOL	GetActive() {	return m_bActive; }
	void	MoveWnd();
	void	Start();

protected:
	void	DrawActiveRect();
	void	ResetMarginRect();


private:
	CPVVideoWnd		m_VideoWnd;
	BOOL	m_bActive;
	CPVFrameWnd*	m_pPVFrameWnd;
	RECT	m_rcMarginTop;
	RECT	m_rcMarginBottom;
	RECT	m_rcMarginLeft;
	RECT	m_rcMarginRight;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PVVIEWWND_H__3F4E53C6_C1C1_438F_9B10_FC24075167A4__INCLUDED_)
