#if !defined(AFX_CHECKBOX_H__38E72D24_A4C7_11D5_B914_000000000000__INCLUDED_)
#define AFX_CHECKBOX_H__38E72D24_A4C7_11D5_B914_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CGuiCheckBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiCheckBox window
class CGuiCheckBox : public CButton
{
    // Construction
public:
    CGuiCheckBox();
    virtual ~CGuiCheckBox();
    
    
    // Attributes
public:  
    void DrawOrange(CDC* pDC, CRect m_rcTemp);
	BOOL GetCheckEx() { return m_bCheckBtn; }
	void SetCheckEx(BOOL bCheckBtn = TRUE);
	void SetTextColor(COLORREF clrText);
	void SetCheckBKColor(COLORREF clrBk);
    
public:
    BOOL         m_bCheckBtn;
    BOOL         m_bPressBtn;
    BOOL         m_bSelected;
    COLORREF     m_clrHigh;				//矩形边框颜色
    COLORREF     m_clrCheck;			//勾选标记颜色
    COLORREF     m_clrText;				//文本颜色
	COLORREF	 m_clrCheckBk;			//文本背景色(默认为窗口背景色)
    
public:
    // Overrides
    //{{AFX_VIRTUAL(CGuiCheckBox)
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL
    
protected:
    //{{AFX_MSG(CGuiCheckBox)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
	// 拦截父窗口的CHECK消息 设置和获取 [2017-3-23 ydl]
	afx_msg LRESULT OnMsgGetCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnMsgSetCheck(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
    
    DECLARE_MESSAGE_MAP()

	void UpdateCheckState();
};

////////////////////////////////////////////
/////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKBOX_H__38E72D24_A4C7_11D5_B914_000000000000__INCLUDED_)