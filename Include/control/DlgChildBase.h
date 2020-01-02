#pragma once
#include "DialogBase.h"

// 

class CDlgChildBase : public CDialogBase
{
public:
	CDlgChildBase(UINT nIDTemplate, CWnd * pParentWnd = NULL);
	~CDlgChildBase(void);


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

