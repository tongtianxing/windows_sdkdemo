#if !defined(AFX_PVVIDEOWND_H__7FFBDDA3_5FAE_4920_B0F7_90C7A242A1FD__INCLUDED_)
#define AFX_PVVIDEOWND_H__7FFBDDA3_5FAE_4920_B0F7_90C7A242A1FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PVVideoWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPVVideoWnd window
class CPVFrameWnd;
class CPVVideoWnd : public CWnd
{
private:
	typedef std::vector<CString>	vecString;

// Construction
public:
	CPVVideoWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPVVideoWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPVVideoWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPVVideoWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void	SetIndex(int nIndex) {	m_nIndex = nIndex; }
	int		GetIndex() {	return m_nIndex; }
	void	SetPVFrmWnd(CPVFrameWnd* pWnd) {	m_pFrameWnd = pWnd; }
	void	SetRectEmpty();
	void	Start();

public:
	void	CalcRectRegion(const CPoint& ptStart
				, const CPoint& ptEnd, RECT& rcRegion);
	BOOL	PlayValid();
	BOOL	DragValid();
	void	BeginDraw(CPoint point);
	void	GetLineString(HDC hDc, CRect& rcClient, CString strInfo, vecString& LineStr);

private:
	int		m_nIndex;
	CPVFrameWnd*	m_pFrameWnd;
	BOOL	m_bEnableDrag;
	BOOL	m_bEnableDraw;

	BOOL	m_bDrawing;
	CPoint	m_ptStart;
	CPoint	m_ptEnd;
	RECT	m_RectRegion;
	RECT	m_rcClient;
	BOOL	m_bRectValid;
	HCURSOR	m_hCursorSelect;
	BOOL	m_bSelected;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PVVIDEOWND_H__7FFBDDA3_5FAE_4920_B0F7_90C7A242A1FD__INCLUDED_)
