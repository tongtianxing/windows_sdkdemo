#if !defined(AFX_DLGPOPUPBASE_H__275A9D74_0891_4350_B461_AD324CE1F943__INCLUDED_)
#define AFX_DLGPOPUPBASE_H__275A9D74_0891_4350_B461_AD324CE1F943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DialogBase.h"
// DlgPopupBase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPopupBase dialog

class CWndPopoTitle;
class CDlgPopupBase : public CDialogBase
{
// Construction
public:
	CDlgPopupBase(UINT nIDTemplate, CWnd * pParentWnd = NULL);
	virtual ~CDlgPopupBase();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPopupBase)
//	protected:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nFlags, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPopupBase)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual int DoOnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void DoOnPaint(HDC hDC);
	virtual void DoOnSize(UINT nFlags, int cx, int cy);
	virtual void MoveBtn(int nLeft, int nTop, CButton& Btn);

	void SetTitleLog(LPCTSTR lpszTitleLog);
	void SetTitleBK(COLORREF colorStart, COLORREF colorStop);
	void SetButtomBK(COLORREF colorStart, COLORREF colorStop);

	void SetTitleHeight(int nHeight) { m_nTitleHeight = nHeight; }

	void SetWindowText(LPCTSTR lpszTitle);


	BOOL IsReSize() const { return m_bReSize; }
	void SetReSize(BOOL bReSize) { m_bReSize = bReSize; }

	CSize GetSizeBorder() const { return m_sizeBorder; }
	void SetSizeBorder(CSize size) { m_sizeBorder = size; }

protected:
	void DrawTitle(CRect rcClient, HDC hDC);
//	void DrawBK(CRect rcClient, HDC hDC);
	void DrawButtom(CRect rcClient, HDC hDC);
//	void MoveDialog(CPoint& inCursorPos);
protected:
	CWndPopoTitle *m_pWndPopoTitle;
	CWndPopoTitle *m_pWndPopoButtom;
	CWndShadow m_Shadow;

// 	bool	m_Dragging;
// 	CPoint	m_CursorPos;

	COLORREF m_colorTitleStart;
	COLORREF m_colorTitleStop;
	COLORREF m_colorButtomStart;
	COLORREF m_colorButtomStop;
	int m_nTitleHeight;

	// 调整大小
	BOOL m_bReSize;
	// 大小边界,默认x=y=6
	CSize m_sizeBorder;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOPUPBASE_H__275A9D74_0891_4350_B461_AD324CE1F943__INCLUDED_)
