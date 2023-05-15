////////////////////////////////////////////////////////////////
// ColorPicker.h : header file                                //
//															  //
// Copyright 2001 WangJun									  //
// All Rights Reserved.										  //
//															  //
// Email: wangjun98@sohu.com								  //
// URL:   http://www.vckbase.com							  //
//															  //
// 1.0     2001/10/6   First release version.				  //
//															  //
////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORPICKER_H__52F28BCF_DBD4_49A1_8293_1B7FBFB8735D__INCLUDED_)
#define AFX_COLORPICKER_H__52F28BCF_DBD4_49A1_8293_1B7FBFB8735D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorPicker.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorPicker window

class CColorPicker : public CButton
{
	DECLARE_DYNAMIC(CColorPicker)

// Construction
public:
	CColorPicker();
	virtual ~CColorPicker();
	static void	SetMetrics();

// Attributes
public:

// Operations
public:
	void		SetColor(COLORREF ref);
	void		SetBuddy(HWND hWnd);
	COLORREF	GetColor();
	void		GetColor(CString& strColor);
//	CPoint m_OldPos;
	//CPoint m_CurrentPos;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPicker)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
private:
	void		DestroyPaletteWindow();
	BOOL		CreatePaletteWindow();
	static	LRESULT FAR PASCAL PaletteWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

public:
	static HWND CreatePaletteWindowIndependent(HWND hParent, LPPOINT ptTopLeft, COLORREF color = COLOR_WHITE, LONG_PTR pUserData = NULL);

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorPicker)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	HWND		m_hwndBuddy;
	COLORREF	m_CurrentColor;
	HWND		m_hPaletteWnd;
	BOOL		m_bPaletteWndActive;
	HCURSOR		m_hCursorStraw;

	static int COLOR_GRID_SIZE;
	static int COLOR_GRID_ROWS;
	static int COLOR_GRID_COLS;
	static CRect COLOR_DLG_RECT;
	static CRect COLOR_DLG_GRID_RECT;
	static CRect COLOR_DLG_INFO_RECT;
	static CPen COLOR_PEN_SHADOW;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPICKER_H__52F28BCF_DBD4_49A1_8293_1B7FBFB8735D__INCLUDED_)
