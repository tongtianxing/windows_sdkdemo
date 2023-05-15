#pragma once
#include "StateImgBase.h"
#include "TransparentWnd.h"

enum EImgSliderIdx
{
	IMG_SLIDER_IDX_THUMB,
	IMG_SLIDER_IDX_BAR_NORMAL,
	IMG_SLIDER_IDX_BAR_USED,
	IMG_SLIDER_IDX_COUNT
};

class CImgSliderCtrl : public CSliderCtrl, public CTransparentWnd, public CStateImgBase
{
	DECLARE_DYNAMIC(CImgSliderCtrl)

public:
	CImgSliderCtrl();
	virtual ~CImgSliderCtrl();

private:
	void SetExpand(int nIdx, int nBorderWidth, int nBorderHeight);

protected:
	BOOL m_bDragging;
	BOOL m_bReverseUsed;
	int m_nChannelBound;
	CRect m_rcChannel;
	CRect m_rcChannelUsed;
	CRect m_rcThumb;
	int m_nDragThumbOffset;

	BOOL m_bDrawColorChannel;
	COLORREF m_clrChannel;
	COLORREF m_clrChannelUsed;
public:
	void InitRect();
	void SetReverseUsed(BOOL bReverse);
	void SetChannelColor(COLORREF clr, COLORREF clrUsed);
protected:
	void UpdateThumbRect();
	void DrawThumb(HDC hDC);
	void DrawChannel(HDC hDC);
	int GetPointPos(CPoint point);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
