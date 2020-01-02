#if !defined(AFX_NUMEDIT_H__11741AE8_B3ED_4C67_83F4_79D3324F1EE4__INCLUDED_)
#define AFX_NUMEDIT_H__11741AE8_B3ED_4C67_83F4_79D3324F1EE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumEdit window

class CNumEdit : public CEdit
{
// Construction
public:
	CNumEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNumEdit();

	// Generated message map functions
	void SetPointEnable(BOOL bEnable = TRUE);
	void SetNumLimit(float fMin, float fMax);
protected:
	//{{AFX_MSG(CNumEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnUpdate();
	afx_msg void OnChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CString m_sValue;
	BOOL m_bPointEnable;
	CString m_str;
	float m_fMin;
	float m_fMax;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMEDIT_H__11741AE8_B3ED_4C67_83F4_79D3324F1EE4__INCLUDED_)
