#pragma once
#include "XSpinButtonCtrl.h"

enum EImgSpinIdx
{
	IMG_SPIN_IDX_UP,
	IMG_SPIN_IDX_DOWN,
	IMG_SPIN_IDX_LEFT = IMG_SPIN_IDX_UP,
	IMG_SPIN_IDX_RIGHT = IMG_SPIN_IDX_DOWN,
	IMG_SPIN_IDX_COUNT
};

class CImgSpin : public CXSpinButtonCtrl, public CTransparentWnd
{
	DECLARE_DYNAMIC(CImgSpin)
public:
	CImgSpin();
	virtual ~CImgSpin();

private:
	CStateImgBase m_imgBtnUL, m_imgBtnDR;
protected:
	CRect m_rcBtn[IMG_SPIN_IDX_COUNT];
	CRect m_rcMidBar;
	int m_nMidBarWeight;
	int m_nBorderWeight;
	COLORREF m_clrMidBar;
	COLORREF m_clrBorder;
	int m_nDrawBorderL;
	int m_nDrawBorderR;
public:
	BOOL HasPic() const { return m_imgBtnUL.HasPic() && m_imgBtnDR.HasPic(); }
	void InitRect();
	bool SetStateImg(size_t idx, 
		LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);
	CSize GetImgSize(size_t idx, int state);
	void SetMidbarWeight(int nPx) { m_nMidBarWeight = nPx; }
	void SetBorderWeight(int nPx) { m_nBorderWeight = nPx; }
	void SetColorMidBar(COLORREF clr) { m_clrMidBar = clr; Invalidate(); }
	void SetColorBorder(COLORREF clr) { m_clrBorder = clr; Invalidate(); }

	// -1: check align type / 0: do not draw / 1: draw
	void SetDrawBorderL(int nDraw) { m_nDrawBorderL = nDraw; }
	// -1: check align type / 0: do not draw / 1: draw
	void SetDrawBorderR(int nDraw) { m_nDrawBorderR = nDraw; }

public:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};