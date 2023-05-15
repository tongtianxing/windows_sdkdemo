#pragma once

#ifdef _XTP_INCLUDE_CONTROLS


class CXTPDatePickerPaintManagerEx;
class CXTPDatePickerItemMonthEx : public CXTPDatePickerItemMonth
{
protected:
	int m_nHeaderHeight;
	int m_nDaysOfWeekWeekHeight;
	int m_nWeekNumberWidth;
	friend class CXTPDatePickerPaintManagerEx;

public:
	CXTPDatePickerItemMonthEx(CXTPDatePickerControl* pControl, COleDateTime dtMonth, int nRow, int nCol,
		int nHeaderHeight, int nDaysOfWeekWeekHeight, int nWeekNumberWidth);

	virtual ~CXTPDatePickerItemMonthEx() {} // needed for dynamic_cast

	void AutoAdjustLayoutEx(CRect rcClient, BOOL bCompact = FALSE);
	void OnLButtonDownEx(UINT nFlags, CPoint point);
};

class CXTPDatePickerControlEx : public CXTPDatePickerControl
{
	DECLARE_DYNAMIC(CXTPDatePickerControlEx)
	typedef CString(CALLBACK * FUNCGetStringText)(int nYear, int nMonth, int nDay, void* pUsr);

public:
	CXTPDatePickerControlEx() : CXTPDatePickerControl()
	{
		m_nHeaderHeight = DPIConvert(18);
		m_nDaysOfWeekHeight = DPIConvert(18);
		m_nWeekNumberWidth = DPIConvert(18);
		m_bShrinkWeekNums = FALSE;
		m_bDropdown = FALSE;
		m_bMultiLine = FALSE;
		SetBorderStyle(xtpDatePickerBorderStatic);
		m_pfnGetText = NULL;
		m_pUsrGetText = NULL;
	}
	friend class CXTPDatePickerItemMonthEx;

protected:
	int m_nHeaderHeight;
	int m_nDaysOfWeekHeight;
	int m_nWeekNumberWidth;
	BOOL m_bShrinkWeekNums;
	BOOL m_bDropdown;
	BOOL m_bMultiLine;	//显示多行文本
	COLORREF m_clrText2;
	COLORREF m_clrFrameRect;
	CFont m_fontText2;
	FUNCGetStringText m_pfnGetText;
	void*	m_pUsrGetText;
public:
	void SetYearsButton(BOOL bEnable) { m_bYearsTriangle = bEnable; }
	void SetHeaderHeight(int nHeight) { m_nHeaderHeight = nHeight; }
	void SetDaysOfWeekHeight(int nHeight) { m_nDaysOfWeekHeight = nHeight; }
	void SetWeekNumberWidth(int nWidth) { m_nWeekNumberWidth = nWidth; }
	void SetShrinkWeekNums(BOOL bEnable) { m_bShrinkWeekNums = bEnable; }
	void SetDropDown(BOOL bDropdown) { m_bDropdown = bDropdown; }
	void SetMultiLine(BOOL bMultiLine);
	BOOL IsMultiLine() { return m_bMultiLine; }
	COLORREF GetStringText2() { return m_clrText2; }
	COLORREF GetColorFrameRect() { return m_clrFrameRect; }
	CFont* GetFontText2() { return &m_fontText2; }
	void SetFUNCText2CB(void* pUsr, FUNCGetStringText pfnGetStringText);
	CString GetStringText2(int nYear, int nMonth, int nDay);

	bool HasThemeEx() const;
	void SetColorWndBk(COLORREF clr)           { if (HasThemeEx()) m_pPaintManager->m_clrControlBack = clr; }
	void SetColorTitleBk(COLORREF clr)         { if (HasThemeEx()) m_pPaintManager->m_clrMonthHeaderBack = clr; }
	void SetColorTitleText(COLORREF clr)       { if (HasThemeEx()) m_pPaintManager->m_clrMonthHeaderText = clr; }
	void SetColorTitleButton(COLORREF clr)     { if (HasThemeEx()) m_pPaintManager->m_clrMonthHeaderButton = clr; }
	void SetColorDaysOfWeekBk(COLORREF clr)    { if (HasThemeEx()) m_pPaintManager->m_clrDaysOfWeekBack = clr; }
	void SetColorDaysOfWeekText(COLORREF clr)  { if (HasThemeEx()) m_pPaintManager->m_clrDaysOfWeekText = clr; }
	void SetColorNonMonthDayBk(COLORREF clr)   { if (HasThemeEx()) m_pPaintManager->m_clrNonMonthDayBack = clr; }
	void SetColorNonMonthDayText(COLORREF clr) { if (HasThemeEx()) m_pPaintManager->m_clrNonMonthDayText = clr; }
	void SetColorDayBk(COLORREF clr)           { if (HasThemeEx()) m_pPaintManager->m_clrDayBack = clr; }
	void SetColorDayText(COLORREF clr)         { if (HasThemeEx()) m_pPaintManager->m_clrDayText = clr; }
	void SetColorSelectedBk(COLORREF clr)      { if (HasThemeEx()) m_pPaintManager->m_clrSelectedDayBack = clr; }
	void SetColorSelectedText(COLORREF clr)    { if (HasThemeEx()) m_pPaintManager->m_clrSelectedDayText = clr; }
	void SetColorTodayBk(COLORREF clr)         { if (HasThemeEx()) m_pPaintManager->m_clrHighlightToday = clr; }
	void SetColorListCtrlBk(COLORREF clr)      { if (HasThemeEx()) m_pPaintManager->m_clrListControlBack = clr; }
	void SetColorListCtrlText(COLORREF clr)    { if (HasThemeEx()) m_pPaintManager->m_clrListControlText = clr; }

	virtual void CreateMonthArray();
	virtual void AdjustLayout();
	virtual void AdjustLayout(CRect rcClient);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};

class CXTPDatePickerPaintManagerEx : public CXTPDatePickerPaintManager
{
public:
	CXTPDatePickerPaintManagerEx();
	virtual void DrawScrollTriangle(CDC* pDC, CRect rcSpot, BOOL bLeftDirection,
		COLORREF clrColor = 0, BOOL bYears = FALSE);
	virtual void DrawDaysOfWeek(CDC* pDC, CXTPDatePickerItemMonth* pMonth);
	virtual BOOL DrawDay(CDC* pDC, CXTPDatePickerItemDay* pDay);
};

#endif