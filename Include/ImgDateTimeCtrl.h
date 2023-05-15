#pragma once
#include "CommonWndFun.h"

class CXTPDatePickerControlEx;
class CImgDateTimeCtrl : public CDateTimeCtrl, public CStateImgBase, public CTransparentWnd
{
	DECLARE_DYNAMIC(CImgDateTimeCtrl)
public:
	CImgDateTimeCtrl::CImgDateTimeCtrl() : CStateImgBase(5)
	{
		m_nSelectedRegion = -1;
		m_nTextLeft = DPIConvert(2);
		m_nTextTop = -1;

		m_clrText = COLOR_BLACK;
		m_clrTextSelected = COLOR_WHITE;
		m_clrTextSelectedBK = RGB(0, 120, 215);

		m_bResetInputBuf = FALSE;
		m_bShowingMonthDrop = FALSE;
		m_bCursorInDrop = FALSE;
		m_hWndUD = NULL;

		m_bCursorInSpinUp = FALSE;
		m_bCursorInSpinDown = FALSE;
		m_bClickedSpinUp = FALSE;
		m_bClickedSpinDown = FALSE;

		m_bHasFocus = FALSE;

		m_bLastPaintTransparentDisabled = -1;

#ifdef _XTP_INCLUDE_CONTROLS
		m_bHasXTP = TRUE;
#else
		m_bHasXTP = FALSE;
#endif
		m_pXTPDatePickerCtrl = NULL;
	}

	CImgDateTimeCtrl::~CImgDateTimeCtrl()
	{
	}

	virtual bool SetStateImg(size_t idx, LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL) override;

	enum EImgDTIndex
	{
		IMG_INDEX_BK,
		IMG_INDEX_DROP,
		IMG_INDEX_DROP_SHORT,
		IMG_INDEX_SPIN_UP,
		IMG_INDEX_SPIN_DOWN
	};

protected:
	BOOL m_bHasXTP;
	CXTPDatePickerControlEx* m_pXTPDatePickerCtrl;

	CString m_strFormat;

	struct TextRegion
	{
		TCHAR cType;
		BOOL bText;
		BOOL bEditable;
		CRect rcText;
		CString strText;
	};
	std::vector<TextRegion> m_vecTextRegion;
	int m_nSelectedRegion;
	void UpdateTextRegion();

	COLORREF m_clrText;
	COLORREF m_clrTextSelected;
	COLORREF m_clrTextSelectedBK;

	int m_nTextLeft;
	int m_nTextTop;

private:
	CSize m_sizeStr;
	CString m_strInputBuf;
	BOOL m_bResetInputBuf;

	BOOL m_bShowingMonthDrop;
	BOOL m_bCursorInDrop;

	HWND m_hWndUD;
	BOOL m_bCursorInSpinUp;
	BOOL m_bCursorInSpinDown;
	BOOL m_bClickedSpinUp;
	BOOL m_bClickedSpinDown;
	BOOL m_bHasFocus;

	BOOL m_bLastPaintTransparentDisabled;

	void AdjustDateTime(int nDir, BOOL bLoop);

public:
	void SetTextTop(int nTop) { m_nTextTop = nTop; UpdateTextRegion(); }
	void SetTextLeft(int nLeft) { m_nTextLeft = nLeft; UpdateTextRegion(); }
	void SetTextColor(COLORREF color) { m_clrText = color; }
	void SetSelectedTextColor(COLORREF color) { m_clrTextSelected = color; }
	void SetSelectedBkColor(COLORREF color) { m_clrTextSelectedBK = color; }

	DECLARE_MESSAGE_MAP()
	afx_msg void OnDtnDatetimechange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDropdown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnCloseup(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnXTPDatePickerSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pWnd);
	afx_msg void OnKillFocus(CWnd* pWnd);
};

