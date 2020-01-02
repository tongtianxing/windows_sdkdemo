// WndPopoTitle.h: interface for the CWndPopoTitle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDPOPOTITLE_H__E955BFD2_E4EF_4F0A_A22D_F2FA60CAE3C8__INCLUDED_)
#define AFX_WNDPOPOTITLE_H__E955BFD2_E4EF_4F0A_A22D_F2FA60CAE3C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WND_POPO_TITLE		0
#define WND_POPO_BUTTOM		1

class CWndPopoTitle  : public CWndChildBase
{
public:
	CWndPopoTitle();
	virtual ~CWndPopoTitle();
protected:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtnClickedClose();
	afx_msg void OnBtnClickedSet();
//	afx_msg LRESULT OnNcHitTest(CPoint point);

	DECLARE_MESSAGE_MAP()

public:
	void SetBkGradientColor(COLORREF colorStart, COLORREF colorStop);
	void SetWndType(int nType);
	void SetTitleLog(LPCTSTR lpszTitleLog) { m_strTitleLog = lpszTitleLog; }

	void SetHeight(int nHeight) { m_nHeight = nHeight; }
	int GetHeight() { return m_nHeight; }
private:
	void DrawTitle(CRect rcClient, HDC hDC);
private:
	CCxButton m_btnClose;
	CCxButton m_btnSetting;
	int m_nWndType;			//0-±ÍÃ‚¿∏ 1- buttom
	COLORREF m_colorBKStart;
	COLORREF m_colorBKStop;
//	CImgBase* m_ImgTitleLog;
	CString m_strTitleLog;
	int m_nHeight;
};

#endif // !defined(AFX_WNDPOPOTITLE_H__E955BFD2_E4EF_4F0A_A22D_F2FA60CAE3C8__INCLUDED_)
