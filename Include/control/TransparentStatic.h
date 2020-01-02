#if !defined(AFX_TRANSPARENTSTATIC_H__FD704FCC_30D4_4FBD_825F_A443955BDA2B__INCLUDED_)
#define AFX_TRANSPARENTSTATIC_H__FD704FCC_30D4_4FBD_825F_A443955BDA2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransparentStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransparentStatic window

class CTransparentStatic : public CStatic, public CTransparentWnd
{
// Construction
public:
	CTransparentStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransparentStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparentStatic)
	afx_msg void OnPaint();
// 	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
// 	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
// 	virtual void PreSubclassWindow();
// 	afx_msg BOOL OnEraseBkgnd(CDC*pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	void SetText( const CString &strText );
	void SetTextColor( COLORREF clrText );

private:
	CString m_strCap;
	COLORREF	m_clrFont;
	HBRUSH m_hBrushBK;

	void RefreshStatic();
public:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTSTATIC_H__FD704FCC_30D4_4FBD_825F_A443955BDA2B__INCLUDED_)
