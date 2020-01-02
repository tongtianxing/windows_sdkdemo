#if !defined(AFX_DLGTRANSPARAM_H__6A8ABD6F_2F24_487A_9F88_0872D2286E6B__INCLUDED_)
#define AFX_DLGTRANSPARAM_H__6A8ABD6F_2F24_487A_9F88_0872D2286E6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTransParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTransParam dialog

class CDlgTransParam : public CDialog
{
// Construction
public:
	CDlgTransParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTransParam)
	enum { IDD = IDD_DIALOG_TRANS_PARAM };
	CComboBox	m_cmbDev;
	CString	m_strSetParamRec;
	CString	m_strSetParamSend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTransParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTransParam)
	afx_msg void OnButtonSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgGetParam(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	void DoTransparentConfig(CString strIDNO, int nType, GPSConfigData_S* lpInConfig);

	//parameters
	static void CALLBACK FUNGetDevConfig(GPSMCMsg_S* pMsg, void* pUsr);
	void	DoGetDevConfig(GPSMCMsg_S* pMsg);
	void	CloseGetParamHandle();
	
	void EnableCtrl(BOOL bEnable);
	long	m_lParamHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSPARAM_H__6A8ABD6F_2F24_487A_9F88_0872D2286E6B__INCLUDED_)
