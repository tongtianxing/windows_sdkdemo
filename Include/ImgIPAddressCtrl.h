#pragma once

// 基本上是复制ImgEdit控件
// 在OnPaint上绘制热键文字
class CImgIPAddressCtrl : public CIPAddressCtrl, public CStateImgBase, public CTransparentWnd
{
	DECLARE_DYNAMIC(CImgIPAddressCtrl)

public:
	CImgIPAddressCtrl();
	virtual ~CImgIPAddressCtrl();

protected:
	COLORREF m_clrText;
	COLORREF m_clrTextDisabled;
	COLORREF m_clrTextBK;
	COLORREF m_clrTextBKDisabled;
	int m_nNcWidth;
	int m_nNcHeight;
private:
	BOOL m_bLastPaintTransparentDisabled;
	BOOL m_bCachedWndEnabled;

	virtual void PreSubclassWindow() override;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnSize(UINT type, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	// FIXME CIPAddressCtrl默认没有鼠标事件
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pWndOld);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnStyleChanged(int nFlags, LPSTYLESTRUCT ss);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};