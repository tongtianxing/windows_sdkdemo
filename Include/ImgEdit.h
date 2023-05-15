#pragma once

class CImgEdit : public CEdit, public CStateImgBase, public CTransparentWnd
{
	DECLARE_DYNAMIC(CImgEdit)

public:
	CImgEdit();
	virtual ~CImgEdit();

protected:
	COLORREF m_clrText;
	COLORREF m_clrTextBK;
	COLORREF m_clrTextBKDisabled;
	int m_nNcWidth;
	int m_nNcHeight;
	int m_nTextLeft;
	int m_nTextRight;
	virtual void PreSubclassWindow() override;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;
	bool HasBorder() const;

private:
	COLORREF m_clrEmptyTip;
	CString m_strEmptyTip;
	BOOL m_bLastPaintTransparentDisabled;
	BOOL m_bCachedWndEnabled;

public:
	void SetTextColor(COLORREF color);
	void SetTextBKColor(COLORREF color);
	void SetTextBKDisabledColor(COLORREF color);
	void SetTextEmptyTipColor(COLORREF color) { m_clrEmptyTip = color; }
	void SetBorderWidth(int nWidth);
	void SetBorderHeight(int nHeight);
	void SetTextLeft(int nWidth);
	void SetTextRight(int nWidth);
	virtual bool SetStateImg(size_t idx, LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);
	void SetEmptyTip(const CString& strTip) { m_strEmptyTip = strTip; }

	DECLARE_MESSAGE_MAP()
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnSize(UINT type, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnStyleChanged(int nFlags, LPSTYLESTRUCT ss);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
