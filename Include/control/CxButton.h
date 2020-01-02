#if !defined(AFX_CXBUTTON_H__49A7F64F_32B8_4CA0_8060_E1AFA43D4465__INCLUDED_)
#define AFX_CXBUTTON_H__49A7F64F_32B8_4CA0_8060_E1AFA43D4465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CxButton.h : header file
//
#define CX_BTN_STATE	4
/////////////////////////////////////////////////////////////////////////////
// CCxButton window
class CImgBase;
class CCxButton : public CButton
{
// Construction
public:
	CCxButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCxButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCxButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCxButton)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	int		GetDrawIndex(bool inSelected, bool inFocused, bool inDisabled);
	void	CaptureMouseMove(CPoint inPoint);
	void	CreateFont(CFont* pFont, BYTE lfCharSet, long lHeight, long lWeight, TCHAR* lpFaceName);
	CString GetCaption(int nImageIndex = -1);

public:
	virtual void SetStateImg(LPCTSTR lpszNormal=NULL, LPCTSTR lpszOver=NULL, LPCTSTR lpszHighLight=NULL, LPCTSTR lpszDisable=NULL);

	void	SetBoldText(BOOL bBold=TRUE) { m_bBold = bBold; }
	void	SetCaption(LPCTSTR lpszCaption = NULL);
	void	SetCaptionOver(LPCTSTR lpszCaption);
	void	SetTextLeft(int nLeft) {	m_nTextLeft = nLeft; }
	void	SetTextTop(int nTextTop) { m_nTextTop = nTextTop; }
	void	SetOverStatus(BOOL bOver) {	m_bOverStatus = bOver;	Invalidate();	}
	void	SetOverTextColor(COLORREF ColorOverText);
	void	SetNormalTextColor(COLORREF ColorNormalText);
	BOOL	IsOverStatus() { return m_bOverStatus; }
	void	SetUserData(int nUserData) { m_nUserData = nUserData; }
	int		GetUserData() { return m_nUserData; }
	void	SetTextNormalFont(BYTE lfCharSet, long lHeight, long lWeight, TCHAR* lpFaceName);
	void	SetTextOverFont(BYTE lfCharSet, long lHeight, long lWeight, TCHAR* lpFaceName);

	virtual void DoMouseMoveIn();
	virtual void DoMouseMoveOut();

	void	CalcDPIConvert(BOOL bCheckDPI = TRUE);
private:
	void	UpdateText();
	
protected:
	HCURSOR m_hCursor;
	CImgBase*	m_pImgState[CX_BTN_STATE];
	CString	m_strCaption;
	CString m_strCaptionOver;
	int		m_nTextLeft;
	int		m_nTextTop;
	BOOL	m_bOverStatus;
	COLORREF m_ColorOverText;
	COLORREF m_ColorNormalText;
	COLORREF m_ColorUnEnableText;
	BOOL	m_bBold;
	int		m_nUserData;
	CFont* m_pfTextNormal;
	CFont* m_pfTextOver;
//	CTransparentWnd m_Transparent;
};

/////////////////////////////////////////////////////////////////////////////
#define  WM_MSG_PTZ_BTN  WM_USER + 0x101

class CCxPTZButton : public CCxButton  
{
public:
	CCxPTZButton();
	virtual ~CCxPTZButton();
protected:
	//{{AFX_MSG(CCxButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define  WM_MSG_MENU_BTN_LBUTTON_DOWN	WM_USER + 0x110
#define  WM_MSG_MENU_BTN_MOUSE_IN		WM_USER + 0x111
#define  WM_MSG_MENU_BTN_MOUSE_OUT		WM_USER + 0x112

class CCxMenuButton : public CCxButton  
{
public:
	CCxMenuButton();
	virtual ~CCxMenuButton();
	//{{AFX_MSG(CCxButton)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual void DoMouseMoveIn();
};

/////////////////////////////////////////////////////////////////////////////
//	未设置SetCaption函数时候使用GetWindowText()获取按钮的Caption
////////////////////////////////////////////////////////////////////////////
class CCxTextButton : public CCxButton  
{
public:
	CCxTextButton();
	virtual ~CCxTextButton();
	//{{AFX_MSG(CCxButton)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
//	长图片按钮
////////////////////////////////////////////////////////////////////////////
class CCxLongTextButton :public CCxTextButton
{
public:
	CCxLongTextButton();
	virtual ~CCxLongTextButton();
	//{{AFX_MSG(CCxButton)
	virtual void	SetStateImg(LPCTSTR lpszNormal=NULL, LPCTSTR lpszOver=NULL, LPCTSTR lpszHighLight=NULL, LPCTSTR lpszDisable=NULL);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXBUTTON_H__49A7F64F_32B8_4CA0_8060_E1AFA43D4465__INCLUDED_)