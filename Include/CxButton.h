#if !defined(AFX_CXBUTTON_H__49A7F64F_32B8_4CA0_8060_E1AFA43D4465__INCLUDED_)
#define AFX_CXBUTTON_H__49A7F64F_32B8_4CA0_8060_E1AFA43D4465__INCLUDED_

#include <TransparentWnd.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CX_BTN_STATE	4

class CImgBase;
class CCxButton : public CButton, public CTransparentWnd
{
	DECLARE_DYNAMIC(CCxButton)

public:
	CCxButton();

public:
	enum ImgBtnState
	{
		IMG_BTN_STATE_NORMAL = 0,
		IMG_BTN_STATE_HIGHLIGHT,
		IMG_BTN_STATE_OVER,
		IMG_BTN_STATE_DISABLED,
		IMG_BTN_STATE_COUNT
	};


public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

protected:
	virtual void DoDrawItem(HDC hdc, int nImgIdx, const CRect& rc);
	virtual void DrawBackground(HDC hdc, int nImgIdx, const CRect& rc);
	virtual void DrawButtonImage(HDC hdc, int nImgIdx, const CRect& rc);
	virtual void DrawCaption(HDC hdc, int nImgIdx, const CRect& rc);
protected:
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	virtual ~CCxButton();

protected:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

protected:
	int		GetDrawIndex(bool inSelected, bool inFocused, bool inDisabled);
	void	CaptureMouseMove(CPoint inPoint);
	void	CreateFont(CFont* pFont, BYTE lfCharSet, long lHeight, long lWeight, LPCTSTR lpFaceName);
	CString GetCaption(int nImageIndex = -1);

public:
	virtual CCxButton& SetStateImg(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL,
		LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL, BOOL bLoad = FALSE);
	// 非虚函数,设置图片并设置DPI计算
	virtual CCxButton& SetStateImgDPI(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL,
		LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL, BOOL bCheckDPI = TRUE);

	CCxButton&	SetBoldText(BOOL bBold = TRUE);
	CCxButton&	SetCaption(LPCTSTR lpszCaption = NULL);
	CCxButton&	SetCaptionOver(LPCTSTR lpszCaption);
	CCxButton&	SetTextLeft(int nLeft);
	CCxButton&	SetTextTop(int nTextTop);
	CCxButton&	SetOverStatus(BOOL bOver, BOOL bRedraw = TRUE);
	CCxButton&	SetHilightStatus(BOOL bHilight, BOOL bRedraw = TRUE);
	CCxButton&	SetOverTextColor(COLORREF ColorOverText, BOOL bSetHilightColor = TRUE);
	CCxButton&	SetNormalTextColor(COLORREF ColorNormalText);
	CCxButton&  SetHilightTextColor(COLORREF color);
	CCxButton&  SetUnEnableTextColor(COLORREF color);
	BOOL	IsOverStatus() { return m_bOverStatus; }
	BOOL	IsHilightStatus() { return m_bHilightStatus; }
	CCxButton&	SetUserData(int nUserData);
	int		GetUserData() { return m_nUserData; }
	CCxButton&	SetTextNormalFont(BYTE lfCharSet, long lHeight, long lWeight, LPCTSTR lpFaceName);
	CCxButton&	SetTextOverFont(BYTE lfCharSet, long lHeight, long lWeight, LPCTSTR lpFaceName);
	CCxButton&  SetWordEllipsis(BOOL bEllipsis);
	BOOL	IsWordEllipsis() { return m_bWordEllipsis; }

	virtual void DoMouseMoveIn();
	virtual void DoMouseMoveOut();

	CCxButton&	CalcDPIConvert(BOOL bCheckDPI = TRUE);


	// 判断img是否全部加载失败
	// 小于0:判断全部  0:lpszNormal  1:lpszOver  2:lpszHighLight  3:lpszDisable
	BOOL IsLoadImgFail(int nIndex = -1);

	void SetBtnBkColor(COLORREF bk);
	COLORREF GetBtnBkColor() const;

	void SetBtnBkOverColor(COLORREF bk, BOOL bSetHilightColor = TRUE);
	COLORREF GetBtnBkOverColor() const;

	void SetBtnBkLightColor(COLORREF bk);
	COLORREF GetBtnBkLightColor() const;

	COLORREF GetColorOverText() const;
	COLORREF GetColorNormalText() const;
	COLORREF GetColorUnEnableText() const;

	void SetTransparent(BOOL bEnable, BOOL bEraseByCtlColor = FALSE);
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
	BOOL	m_bHilightStatus;
	COLORREF m_ColorOverText;
	COLORREF m_ColorNormalText;
	COLORREF m_ColorHilightText;
	COLORREF m_ColorUnEnableText;
	BOOL	m_bBold;
	int		m_nUserData;
	CFont* m_pfTextNormal;
	CFont* m_pfTextOver;
//	CTransparentWnd m_Transparent;

	// 按钮背景色,默认为白色
	COLORREF m_ColorBk;
	COLORREF m_ColorBkOver;
	COLORREF m_ColorBkLight;

	// 基础DPI,默认100,如果使用200%时为200
	int		m_nBaseDpi[CX_BTN_STATE];

	// 文字自动截断
	BOOL	m_bWordEllipsis;
};

/////////////////////////////////////////////////////////////////////////////
#define  WM_MSG_PTZ_BTN  WM_USER + 0x101

class CCxPTZButton : public CCxButton
{
	DECLARE_DYNAMIC(CCxPTZButton)
public:
	CCxPTZButton();
	virtual ~CCxPTZButton();

protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

//////////////////////////////////////////////////////////////////////////
#define WM_MSG_WND_CLICK			WM_USER + 0x102	//点击鼠标	WPARAM:CtrlID  LPARAM:message

template<class T/* = CCxButton*/>
class CWndClickT : public T
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		switch (pMsg->message)
		{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			GetParent()->PostMessage(WM_MSG_WND_CLICK, GetDlgCtrlID(), pMsg->message);
			break;
		}
		return T::PreTranslateMessage(pMsg);
	}
};



/////////////////////////////////////////////////////////////////////////////
#define  WM_MSG_MENU_BTN_LBUTTON_DOWN	WM_USER + 0x110	
#define  WM_MSG_MENU_BTN_MOUSE_IN		WM_USER + 0x111	
#define  WM_MSG_MENU_BTN_MOUSE_OUT		WM_USER + 0x112	

class CCxMenuButton : public CCxButton
{
	DECLARE_DYNAMIC(CCxMenuButton)
public:
	CCxMenuButton();
	virtual ~CCxMenuButton();
	virtual void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()

public:
	virtual void DoMouseMoveIn();
};

/////////////////////////////////////////////////////////////////////////////
//	未设置SetCaption函数时候使用GetWindowText()获取按钮的Caption
////////////////////////////////////////////////////////////////////////////
class CCxTextButton : public CCxButton
{
	DECLARE_DYNAMIC(CCxTextButton)
public:
	CCxTextButton();
	virtual ~CCxTextButton();
	//virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DrawCaption(HDC hdc, int nImgIdx, const CRect& rc) override;
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
//	长图片按钮
////////////////////////////////////////////////////////////////////////////
class CCxLongTextButton :public CCxTextButton
{
	DECLARE_DYNAMIC(CCxLongTextButton)
public:
	CCxLongTextButton();
	virtual ~CCxLongTextButton();
	virtual CCxButton&	SetStateImg(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);
	virtual CCxButton&  SetStateImgDPI(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL, BOOL bCheckDPI = TRUE);
	DECLARE_MESSAGE_MAP()
};



#define BTN_FUNC_FOR_EACH(data, f)	\
	auto Iter = std::begin(data); \
	auto IterE = std::end(data); \
	while (IterE != Iter) \
	{ \
		auto pBtn = (*Iter); \
		if (pBtn->GetSafeHwnd()) \
		{ \
			pBtn->f; \
		} \
		Iter++; \
	}


template <class T>
void SetStateImg_Batch(T& data, LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL)
{
	BTN_FUNC_FOR_EACH(data, SetStateImg(lpszNormal, lpszOver, lpszHighLight, lpszDisable));
}

template <class T>
void SetStateImgDPI_Batch(T& data, LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL, BOOL bCheckDPI = TRUE)
{
	BTN_FUNC_FOR_EACH(data, SetStateImgDPI(lpszNormal, lpszOver, lpszHighLight, lpszDisable, bCheckDPI));
}

template <class T>
void SetBoldText_Batch(T& data, BOOL bBold = TRUE) { BTN_FUNC_FOR_EACH(data, SetBoldText(bBold)); }

template <class T>
void SetCaption_Batch(T& data, LPCTSTR lpszCaption = NULL) { BTN_FUNC_FOR_EACH(data, SetCaption(lpszCaption)); }

template <class T>
void SetCaptionOver_Batch(T& data, LPCTSTR lpszCaption) { BTN_FUNC_FOR_EACH(data, SetCaptionOver(lpszCaption)); }

template <class T>
void SetTextLeft_Batch(T& data, int nLeft) { BTN_FUNC_FOR_EACH(data, SetTextLeft(nLeft)); }

template <class T>
void SetTextTop_Batch(T& data, int nTextTop) { BTN_FUNC_FOR_EACH(data, SetTextTop(nTextTop)); }

template <class T>
void SetOverStatus_Batch(T& data, BOOL bOver) { BTN_FUNC_FOR_EACH(data, SetOverStatus(bOver)); }

template <class T>
void SetOverTextColor_Batch(T& data, COLORREF ColorOverText, BOOL bSetHilightColor = TRUE) { BTN_FUNC_FOR_EACH(data, SetOverTextColor(ColorOverText, bSetHilightColor)); }

template <class T>
void SetNormalTextColor_Batch(T& data, COLORREF ColorNormalText) { BTN_FUNC_FOR_EACH(data, SetNormalTextColor(ColorNormalText)); }

template <class T>
void SetLightTextColor_Batch(T& data, COLORREF ColorOverText) { BTN_FUNC_FOR_EACH(data, SetHilightTextColor(ColorOverText)); }

template <class T>
void SetUserData_Batch(T& data, int nUserData) { BTN_FUNC_FOR_EACH(data, SetUserData(nUserData)); }

template <class T>
void SetTextNormalFont_Batch(T& data, BYTE lfCharSet, long lHeight, long lWeight, TCHAR* lpFaceName)
{
	BTN_FUNC_FOR_EACH(data, SetTextNormalFont(lfCharSet, lHeight, lWeight, lpFaceName));
}

template <class T>
void SetTextOverFont_Batch(T& data, BYTE lfCharSet, long lHeight, long lWeight, TCHAR* lpFaceName)
{
	BTN_FUNC_FOR_EACH(data, SetTextOverFont(lfCharSet, lHeight, lWeight, lpFaceName));
}

template <class T>
void CalcDPIConvert_Batch(T& data, BOOL bCheckDPI = TRUE) { BTN_FUNC_FOR_EACH(data, CalcDPIConvert(bCheckDPI)); }

template <class T>
void SetBtnBkColor_Batch(T& data, COLORREF bk) { BTN_FUNC_FOR_EACH(data, SetBtnBkColor(bk)); }

template <class T>
void SetBtnBkOverColor_Batch(T& data, COLORREF bk, BOOL bSetHilightColor = TRUE) { BTN_FUNC_FOR_EACH(data, SetBtnBkOverColor(bk, bSetHilightColor)); }

template <class T>
void SetBtnBkLightColor_Batch(T& data, COLORREF bk) { BTN_FUNC_FOR_EACH(data, SetBtnBkLightColor(bk)); }




#endif // !defined(AFX_CXBUTTON_H__49A7F64F_32B8_4CA0_8060_E1AFA43D4465__INCLUDED_)