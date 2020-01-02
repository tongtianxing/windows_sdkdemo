#if !defined(AFX_XTPANEWND_H__53982FDB_EA99_40A3_864E_E2FF5C66A156__INCLUDED_)
#define AFX_XTPANEWND_H__53982FDB_EA99_40A3_864E_E2FF5C66A156__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XTPaneWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXTPaneWnd window

class CXTPFrame;
class CXTPaneWnd : public CWnd
{
// Construction
public:
	CXTPaneWnd(CXTPFrame* pFrame);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTPaneWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXTPaneWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXTPaneWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void	SetMinHeight(int nMinHeight)  {	m_nWndHeight = m_nMinHeight = nMinHeight; }
	int		GetMinHeight()  {	return m_nMinHeight; }
	void	SetLinkWnd(CWnd* pWnd) {	m_pLinkWnd = pWnd; }
	CWnd*	GetLinkWnd()	{	return m_pLinkWnd; }
	void	SetCollapsed(BOOL bCollasped)	{	m_bCollapsed = bCollasped; }
	BOOL	GetCollapsed()	{	return m_bCollapsed; }
	void	SetCaption(LPCTSTR lpszCaption) {	m_strCaption = lpszCaption; }
	CString	GetCaption() {	return m_strCaption; }
	void	SetResize(BOOL bResize)	{	m_bResize = bResize; }
	BOOL	GetResize()	{	return m_bResize; }
	void	SetWndHeight(int nWndHeight) {	m_nWndHeight = nWndHeight; }
	int		GetWndHeight() {	return m_nWndHeight; }
	void	SetEnableMove(BOOL bEnable) {	m_bEnableMoving = bEnable; }
	void	SetMoveEnd() {	m_bMoving = FALSE; }
	void	SetEnableCollasped(BOOL bEnable)	{	m_bEnableCollasped = bEnable;}
	
	void	SetImage(LPCTSTR lpszExpand, LPCTSTR lpszColl, LPCTSTR lpszMove);

protected:
	void	MoveCtrl();

private:
	CXTPFrame*	m_pXTPFrame;
	CWnd*		m_pLinkWnd;
	HCURSOR		m_hCursorMove;
	HCURSOR		m_hCursorSize;
	int		m_nMinHeight;
	int		m_nWndHeight;
	int		m_bResize;
	BOOL	m_bCollapsed;
	CString	m_strCaption;
	CFont	m_fntTip;
	BOOL	m_bEnableMoving;
	BOOL	m_bMoving;
	BOOL	m_bEnableCollasped;
	CImgBase*	m_pImageExpand;
	CImgBase*	m_pImageColl;
	CImgBase*	m_pImageMove;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTPANEWND_H__53982FDB_EA99_40A3_864E_E2FF5C66A156__INCLUDED_)
