#pragma once

class CImgRichEdit : public CRichEditCtrl, public CStateImgBase, public CTransparentWnd
{
	DECLARE_DYNAMIC(CImgRichEdit)

public:
	CImgRichEdit();
	virtual ~CImgRichEdit();

protected:
	COLORREF m_clrTextBK;
	COLORREF m_clrTextBKDisabled;
	virtual void PreSubclassWindow() override;
	bool HasBorder() const;

private:
	BOOL m_bLastPaintTransparentDisabled;
	BOOL m_bInNcPaint;

public:
	virtual bool SetStateImg(size_t idx, LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnSetFocus(CWnd* pWnd);
	afx_msg void OnKillFocus(CWnd* pWnd);
	afx_msg void OnSize(UINT type, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
};
