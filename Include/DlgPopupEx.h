#if !defined(AFX_DLGPOPUPEX_H__C3FE2227_51D3_48AF_AE53_28A4C507C670__INCLUDED_)
#define AFX_DLGPOPUPEX_H__C3FE2227_51D3_48AF_AE53_28A4C507C670__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPopupEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPopupEx dialog

class CDlgPopupEx : public CDlgPopupBase
{
// Construction
public:
	CDlgPopupEx(UINT nIDTemplate, CWnd * pParentWnd = NULL);

// Dialog Data
	//{{AFX_DATA(CDlgPopupEx)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPopupEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPopupEx)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOPUPEX_H__C3FE2227_51D3_48AF_AE53_28A4C507C670__INCLUDED_)
