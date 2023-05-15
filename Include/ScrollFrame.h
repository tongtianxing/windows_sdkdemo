#pragma once


class CScrollFrame
{
public:
	CScrollFrame(CWnd* pWnd)
		: m_pWnd(pWnd)
	{
		m_bShowVertScroll = FALSE;
		m_bShowHorzScroll = FALSE;
	}

public:
	virtual void MoveCtrl(const CRect& rtChild);
	virtual void OnHScroll(UINT nSBCode, UINT nPos);
	virtual void OnVScroll(UINT nSBCode, UINT nPos);
	virtual void OnMouseWheel(short zDelta);

protected:
	void CalcScroll(UINT nSBCode, UINT nPos, SCROLLINFO& scrollinfo, int& nAmount);


private:
	CWnd* m_pWnd;
	BOOL m_bShowVertScroll;
	BOOL m_bShowHorzScroll;
};