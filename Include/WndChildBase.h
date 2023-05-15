#pragma once

// ����Ϊ�Ӵ��ڻ���,�������ƶ�ʱ�ı丸����λ��

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
	bool m_Dragging;
	CPoint m_CursorPos;

	CRect m_initRect;
	CWnd *m_pParent;
	DWORD m_dwLastMove;
};

