#if !defined(AFX_DRAGLISTCTRL_H__791F8955_B94A_424E_A09B_999FD166A410__INCLUDED_)
#define AFX_DRAGLISTCTRL_H__791F8955_B94A_424E_A09B_999FD166A410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DragListCtrl.h : header file
//
#include "XListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDragListCtrl window

class CDragListCtrl : public CXListCtrl
{
// Construction
public:
	CDragListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDragListCtrl();

	// Generated message map functions
public:
	//{{AFX_MSG(CDragListCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	void	SetDragBegMsg(UINT uiMsg)  {	m_uiDragBegMsg = uiMsg; }

private:
	UINT	m_uiDragBegMsg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGLISTCTRL_H__791F8955_B94A_424E_A09B_999FD166A410__INCLUDED_)
