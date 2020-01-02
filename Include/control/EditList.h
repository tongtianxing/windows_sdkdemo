#if !defined(AFX_EDITLIST_H__834127E6_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_)
#define AFX_EDITLIST_H__834127E6_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditList window
class CEditList : public CListCtrl
{
	// Construction
public:
	CEditList();

	CStringList m_strList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditList)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditList)
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	CEdit * EditItem( int nItem, int nSubItem);

public:
	void	SetBeginMsg(UINT nMsg)	{	m_nBeginMsg = nMsg; }
	void	SetEndMsg(UINT nMsg)	{	m_nEndMsg = nMsg; }

private:
	UINT	m_nBeginMsg;
	UINT	m_nEndMsg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLIST_H__834127E6_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_)
