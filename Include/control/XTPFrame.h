#if !defined(AFX_XTPFRAME_H__F480DA72_3A16_47E7_AF00_782FAB0FA87B__INCLUDED_)
#define AFX_XTPFRAME_H__F480DA72_3A16_47E7_AF00_782FAB0FA87B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XTPFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXTPFrame window
class CXTPaneWnd;
class CXTPFrame : public CWnd
{
private:
	typedef std::vector<CXTPaneWnd*>	vecPaneWnd;
	typedef vecPaneWnd::iterator	iterPaneWnd;

// Construction
public:
	CXTPFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTPFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXTPFrame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXTPFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CXTPaneWnd*	AddPaneWnd(CWnd* pWnd, int nMinHeight = 100);
	CXTPaneWnd*	FindPaneWnd(CWnd* pLinkWnd);
	void	ResizePane();
	void	SetBeginMove(CXTPaneWnd* pPane, CPoint pt);
	void	CollaspedPane(CXTPaneWnd* pPane);
	void	MoveNavPane();

protected:
	int		FindPaneIndex(CXTPaneWnd* pPane);
	void	AddExpandPaneHeight(int nHeight);
	void	ReduceExpandPaneHeight(int iPane, int nHeight);
	BOOL	ReduceOnePane(int nIndex, int& nLeftHeight);
	int		GetPaneTotalHeight(int nPane);
	int		GetPaneFixHeight(int nPane);
	void	DrawDragTrack(CPoint pt);
	void	CalcPaneSize();
	BOOL	EnableMove(int nIndex, int nSize);

private:
	int			m_nPaneID;
	vecPaneWnd	m_vecPaneWnd;
	BOOL		m_bDraging;
	int			m_nDragTop;
	int			m_nDragBottom;
	int			m_nDragPane;
	int			m_nDragPaneTop;
	int			m_nDragNextPaneBottom;
	CPoint		m_DragPoint;
	HCURSOR		m_CursorSize;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTPFRAME_H__F480DA72_3A16_47E7_AF00_782FAB0FA87B__INCLUDED_)
