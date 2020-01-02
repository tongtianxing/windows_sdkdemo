#if !defined(AFX_MASKEDIT_H__03F27BF5_C403_4D39_A40E_03E766D505D8__INCLUDED_)
#define AFX_MASKEDIT_H__03F27BF5_C403_4D39_A40E_03E766D505D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaskEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaskEdit window

class CMaskEdit : public CEdit
{
// Construction
public:
	CMaskEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaskEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMaskEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMaskEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	LRESULT OnPaste( WPARAM, LPARAM);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASKEDIT_H__03F27BF5_C403_4D39_A40E_03E766D505D8__INCLUDED_)
