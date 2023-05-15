#pragma once


// CStaticScroll

class CStaticScroll : public CStatic
{
	DECLARE_DYNAMIC(CStaticScroll)

public:
	CStaticScroll();
	virtual ~CStaticScroll();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void	SetTextScroll(CString strText);
private:
	int m_iExtend;
	CString m_strText;
	CString m_strTextNew;
	HGDIOBJ m_font;
public:
};


