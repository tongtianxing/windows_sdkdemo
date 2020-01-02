////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_SKINCOMBOBOX_H__83303B81_8425_4D99_BFE3_D6C89494C75D__INCLUDED_)
#define AFX_SKINCOMBOBOX_H__83303B81_8425_4D99_BFE3_D6C89494C75D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinComboBox.h : header file

/////////////////////////////////////////////////////////////////////////////
// CSkinComboBox  window

class CSkinComboBox : public CComboBox
{
	// Construction
public:
	CSkinComboBox ();
	virtual ~CSkinComboBox ();

	// Implementation
public:
	void SetComboBitmap(UINT nIDLeft, UINT nIDRight, UINT nIDCenter);

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinComboBox )
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinComboBox )
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Attributes
protected:
	//-------------Combo Box image scheme-----------------------------
	//		-------------------------------------------------------
	//	   | m_nIDLeft	-----m_nIDCenter-----			|m_nIDRight|
	//		-------------------------------------------------------
	//-----------------------------------------------------------------
	UINT	m_nIDLeft;			//Resource IDs for ComboBox
	UINT	m_nIDRight;		//Resource IDs for ComboBox
	UINT	m_nIDCenter;		//Resource IDs for ComboBox
	CFont	m_Font;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINCOMBOBOX_H__83303B81_8425_4D99_BFE3_D6C89494C75D__INCLUDED_)
