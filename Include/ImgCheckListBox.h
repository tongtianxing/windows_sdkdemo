#pragma once

#include "StateImgBase.h"

class CXTPButtonImgTheme;
class CImgCheckListBox : public CCheckListBox, public CStateImgBase
{
	DECLARE_DYNAMIC(CImgCheckListBox)

public:
	CImgCheckListBox();
	virtual ~CImgCheckListBox();

protected:
	COLORREF m_clrWndBk;
	COLORREF m_clrItemBk;
	COLORREF m_clrItemBkSel;
	COLORREF m_clrText;
	COLORREF m_clrTextSel;
	COLORREF m_clrTextDisabled;
	CXTPButtonImgTheme* m_pTheme;
public:
	BOOL HasTheme() const { return m_pTheme != NULL; }
	void SetTheme(CXTPButtonImgTheme* pTheme);
	CXTPButtonImgTheme* GetTheme() const { return m_pTheme; }

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDS) override;
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;
	virtual CRect OnGetCheckPosition(CRect rectItem, CRect rectCheckBox) override;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};