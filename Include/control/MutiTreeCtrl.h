#if !defined(AFX_MUTITREECTRL_H__1298A0CF_BFBF_414E_A1E1_BA18D9B39FBB__INCLUDED_)
#define AFX_MUTITREECTRL_H__1298A0CF_BFBF_414E_A1E1_BA18D9B39FBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MutiTreeCtrl.h : header file
//

/********************************************************************
	created:	2003/05/06
	created:	6:5:2003   12:08
	filename: 	d:\w\mutitreectrl.h
	file path:	d:\w
	file base:	mutitreectrl
	file ext:	h
	author:		Íõ¼ÑºÀ
	
	purpose:	
*********************************************************************/

/////////////////////////////////////////////////////////////////////////////
// CMutiTreeCtrl window

class CMutiTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CMutiTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMutiTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetItemState( HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch=TRUE);
	virtual ~CMutiTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMutiTreeCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStateIconClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	UINT m_uFlags;
	void TravelSiblingAndParent(HTREEITEM hItem, int nState);
	void TravelChild(HTREEITEM hItem,int nState);

public:
	void	SetStateChangeMsg(UINT nMsg) {	m_nStateChangeMsg = nMsg; }
	BOOL	GetMaskSelected(HTREEITEM hItem);

private:
	UINT	m_nStateChangeMsg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUTITREECTRL_H__1298A0CF_BFBF_414E_A1E1_BA18D9B39FBB__INCLUDED_)
