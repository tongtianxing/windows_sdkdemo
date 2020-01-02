#if !defined(AFX_CXTOOLBAR_H__93969B6C_DB02_4DDB_B69D_185B78BAD17C__INCLUDED_)
#define AFX_CXTOOLBAR_H__93969B6C_DB02_4DDB_B69D_185B78BAD17C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CxToolbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCxToolbar window

class CImgBase;
class CCxToolbar : public CWnd
{
private:
	typedef struct _tagBarBtn
	{
		int		ID;
		CString	str;
		BOOL	bActive;
		int		nWidth;
		CRect	Rect;
	}BarBtn_S;

	typedef std::vector<BarBtn_S>	vecBarBtn;

// Construction
public:
	CCxToolbar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCxToolbar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCxToolbar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCxToolbar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void	SetImage(LPCTSTR lpszExpand, LPCTSTR lpszColl);
	void	SetClkMsg(HWND hWnd, UINT uiMsg) {	m_hClkHwnd = hWnd; m_uiClkMsg = uiMsg;	}
	void	AddButton(int nID, LPCTSTR lpszTitle);
	void	SetCollapsed(BOOL bCollapsed) {	m_bCollapsed = bCollapsed; }

protected:
	int		PtInButton(CPoint point);

private:
	CImgBase*	m_pImageExpand;
	CImgBase*	m_pImageColl;
	HCURSOR	m_hCursorMove;
	BOOL	m_bCollapsed;
	CFont	m_fntTip;
	int		m_nLeaveWidth;
	RECT	m_rcCollBtn;

	vecBarBtn	m_vecBarBtn;

	HWND	m_hClkHwnd;
	UINT	m_uiClkMsg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXTOOLBAR_H__93969B6C_DB02_4DDB_B69D_185B78BAD17C__INCLUDED_)
