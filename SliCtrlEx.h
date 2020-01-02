#if !defined(AFX_SLICTRLEX_H__AEDBB6E6_02A9_491B_AFE1_4BA8AF58A273__INCLUDED_)
#define AFX_SLICTRLEX_H__AEDBB6E6_02A9_491B_AFE1_4BA8AF58A273__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SliCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSliCtrlEx window

class CSliCtrlEx : public CSliderCtrl
{
// Construction
public:
	CSliCtrlEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSliCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSliCtrlEx)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	BOOL	GetLBtnDown() {	return m_bLBtnDown;}

protected:
	bool	SetThumb(const CPoint& point);

private:
	BOOL	m_bLBtnDown;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLICTRLEX_H__AEDBB6E6_02A9_491B_AFE1_4BA8AF58A273__INCLUDED_)
