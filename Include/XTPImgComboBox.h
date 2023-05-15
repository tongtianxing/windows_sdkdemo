#pragma once

#ifdef _XTP_INCLUDE_CONTROLS

enum EImgComboBoxIdx
{
	IMG_COMBO_IDX_BODY,
	IMG_COMBO_IDX_DROP,
	IMG_COMBO_IDX_COUNT
};

class CXListCtrl;
class CXTPImgComboBox : public CXTPComboBox, public CStateImgBase, public CTransparentWnd
{
public:
	CXTPImgComboBox();
	virtual ~CXTPImgComboBox();

	DECLARE_DYNAMIC(CXTPImgComboBox)

private:
	HWND m_hwndList;
	HWND m_hwndEdit;
protected:
	BOOL m_bTextCenter;
	int m_nTextTop;
	int m_nTextLeft;
	int m_nDropBtnWidth;
	int m_nComboboxHeight;
	BOOL m_bDropBtnCompact;
	COLORREF m_ColorOverText;
	COLORREF m_ColorHilightText;
	COLORREF m_ColorUnEnableText;
	COLORREF m_ColorEditBK;
	CString m_strEmptyTip;
	BOOL m_bLastPaintTransparentDisabled;
	int m_nInResize;
	BOOL m_bEnableKeyboardNavOnEdit;
	int GetDrawIndex() const;
	int GetDrawIndex(bool inSelected, bool inFocused, bool inDisabled) const;
	void DoDrawItem(CDC* pDC, int nImgIdx, const CRect& rcClient);
	void DrawButtonImage(CDC* pDC, int nImgIdx, const CRect& rcClient);
	void DrawDropImage(CDC* pDC, int nImgIdx, const CRect& rcClient);
	void DrawCaption(CDC* pDC, int nImgIdx, const CRect& rcAvailable);
	void ResizeEdit();
	static HWND CreateDropListWnd(const CRect& rcList);
	void ShowDropListWnd(int nShow = -1);

public:
	void SetTextColorNormal(COLORREF color) { SetTextColor(color); }
	void SetTextColorOver(COLORREF color) { m_ColorOverText = color; }
	void SetTextColorHilight(COLORREF color) { m_ColorHilightText = color; }
	void SetTextColorUnEnable(COLORREF color) { m_ColorUnEnableText = color; }
	void SetEditBK(COLORREF color) { m_ColorEditBK = color; }
	void SetTextCenter(BOOL bCenter) { m_bTextCenter = bCenter; }
	//void SetTextOffset(int nOffset) { m_nTextOffset = nOffset; }
	void SetTextTop(int nTop) { m_nTextTop = nTop; ResizeEdit(); }
	void SetTextLeft(int nLeft) { m_nTextLeft = nLeft; ResizeEdit(); }
	void SetDropBtnWidth(int nWidth);
	void SetComboBoxHeight(int nHeight);
	void SetDropBtnCompact(BOOL bEnable) { m_bDropBtnCompact = bEnable; }
	void SetEmptyTip(const CString& strTip) { m_strEmptyTip = strTip; }

	bool IsResizing() const { return m_nInResize != 0; }
	void SetEnableKeyboardNavOnEdit(BOOL bEnable) { m_bEnableKeyboardNavOnEdit = bEnable; }
	bool IsEnableKeyboardNavOnEdit() const { return !!m_bEnableKeyboardNavOnEdit; }

	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnCbSetCurSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnComboListSelect(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnCbnSelChange();
	afx_msg BOOL OnCbnKillFocus();

public:
	// 获取下拉列表
	CXListCtrl* GetDropList();
};

#endif