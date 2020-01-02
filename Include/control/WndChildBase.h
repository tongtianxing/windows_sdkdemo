#pragma once

// 此类为子窗口基类,在自身移动时改变父窗口位置

class CWndChildBase :
	public CWnd
{
public:
	CWndChildBase(void);
	~CWndChildBase(void);


protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	void MoveDialog(CPoint& inCursorPos);

private:
	BOOL m_Dragging;
	CPoint m_CursorPos;
};

