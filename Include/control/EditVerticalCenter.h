#pragma once


// 此编辑框
// 1.文本垂直方向会居中显示,需设置多行显示属性
// 2.可设置未输入数据时显示信息

class CEditVerticalCenter : public CEdit
{

public:
	CEditVerticalCenter();
	virtual ~CEditVerticalCenter();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

public:
	void SetDefText(LPCTSTR lpszDefText) { m_strDefText = lpszDefText; }
	void SetDefTextColor(COLORREF color) { m_ColorDefText = color; }
	
	void SetIgnoreFocus(BOOL bIgnore) { m_bIgnoreFocus = bIgnore; }
private:
	COLORREF	m_ColorDefText;	//默认文本的文字颜色
	CString		m_strDefText;	//编辑框无数据时显示的文本

	BOOL		m_bIgnoreFocus;//忽略焦点,默认获得焦点不显示默认文本
};