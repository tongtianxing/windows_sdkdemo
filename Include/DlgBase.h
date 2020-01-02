#pragma once


// CDlgBase ¶Ô»°¿ò

class CDlgBase : public CDialog
{
public:
	CDlgBase(UINT nIDTemplate, CWnd * pParentWnd = NULL);
	virtual ~CDlgBase();

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	virtual void DoOnPain(HDC hDC);

protected:

	DECLARE_MESSAGE_MAP()


	HBRUSH	GetCtrlBKBrush();
	HBRUSH m_hBrushWhite;

};
