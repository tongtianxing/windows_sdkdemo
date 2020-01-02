// #if !defined(AFX_DLGMSGTIP_H__E510FD51_0ABA_47AB_A3ED_25581AC30CAE__INCLUDED_)
// #define AFX_DLGMSGTIP_H__E510FD51_0ABA_47AB_A3ED_25581AC30CAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMsgTip.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgTip dialog

// 默认需添加ID=10101的对话框,包含IDOK,IDNO,IDCANCEL
// 其他请自定义ID号

class CImgBase;
class CDlgMsgTipBase : public CDlgPopupBase
{
// Construction
public:
	CDlgMsgTipBase(UINT nType, CWnd* pParent = NULL);   // standard constructor
	CDlgMsgTipBase(UINT nType, int nDlgID, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CDlgMsgTip)
	enum { IDD = 10101/*IDD_DLG_MSG_TIP*/ };
	CCxTextButton	m_btnCannel;
	CCxTextButton	m_btnOK;
	CCxTextButton	m_btnNO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMsgTip)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMsgTip)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnNo();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	void CalcWndSize();
public:
	virtual void DoOnInitDialog(); //语言和其他信息
	virtual void DoOnPaint(HDC hDC);
	void SetDlgInfo(LPCTSTR lpszText = _T(""), LPCTSTR lpszTitle = _T(""));
	UINT GetType() { return m_nType; }

protected:
	UINT m_nType;
	CImgBase* m_pImgTip;

	CString m_strTitle;
	CString m_strText;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_DLGMSGTIP_H__E510FD51_0ABA_47AB_A3ED_25581AC30CAE__INCLUDED_)
