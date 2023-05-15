
#pragma once

const int CHECK_BOX_STAT_NORMAL = 0;
const int CHECK_BOX_STAT_HILIGHT = 1;
const int CHECK_BOX_STAT_CHECKED = 2;
const int CHECK_BOX_STAT_DISABLED = 4;
const int CHECK_BOX_STAT_MIXED = 8;
const int CHECK_BOX_STAT_MAX = CHECK_BOX_STAT_NORMAL | CHECK_BOX_STAT_HILIGHT | CHECK_BOX_STAT_CHECKED | CHECK_BOX_STAT_DISABLED | CHECK_BOX_STAT_MIXED;
const int CHECK_BOX_STAT_COUNT = CHECK_BOX_STAT_MAX + 1;

class CXTPButtonImgTheme;
class CGuiCheckBox : public CButton
{
	DECLARE_DYNAMIC(CGuiCheckBox)

public:
	CGuiCheckBox();
	virtual ~CGuiCheckBox();


public:
	void DrawOrange(CDC* pDC, CRect rcTemp);
	BOOL GetCheckEx() const;
	void SetCheckEx(BOOL bCheckBtn = TRUE);
	void SetTextColor(COLORREF clrText);
	void SetCheckBKColor(COLORREF clrBk);

public:
	BOOL         m_bCheckBtn;
	BOOL         m_bPressBtn;
	BOOL         m_bSelected;
	BOOL		 m_bDrawParentArea;
	COLORREF     m_clrHigh;				//矩形边框颜色
	COLORREF     m_clrCheck;			//勾选标记颜色
	COLORREF     m_clrText;				//文本颜色
	COLORREF	 m_clrCheckBk;			//文本背景色(默认为窗口背景色)

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// 拦截父窗口的CHECK消息 设置和获取 [2017-3-23 ydl]
	afx_msg LRESULT OnMsgGetCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnMsgSetCheck(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgDrawParentArea(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	void UpdateCheckState();

	// 绘制父窗口的控件区域
	void DrawParentControl();

public:
	// 是否为透明背景
	BOOL IsTransparentMode();

protected:
	CXTPButtonImgTheme* m_pTheme;
public:
	BOOL HasTheme() const { return m_pTheme != NULL; }
	void SetTheme(CXTPButtonImgTheme* pTheme);
	CXTPButtonImgTheme* GetTheme() const { return m_pTheme; }
};
