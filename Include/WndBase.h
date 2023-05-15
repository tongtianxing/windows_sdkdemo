#pragma once



// 此类仅处理窗口静态控件的风格 [2017-3-27 ydl]
class CWndBase : public CWnd
{
#ifdef _WIN64
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
#endif
};