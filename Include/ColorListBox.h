#pragma once

class CColorListBox : public CListBox
{
	DECLARE_DYNAMIC(CColorListBox)

public:
	CColorListBox();
	virtual ~CColorListBox();

protected:
	COLORREF m_clrWndBk;
	COLORREF m_clrItemBk;
	COLORREF m_clrItemBkSel;
	COLORREF m_clrText;
	COLORREF m_clrTextSel;
	COLORREF m_clrTextDisabled;

	virtual void PreSubclassWindow() override;
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDS) override;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};