#if !defined(AFX_DLGTRANSDATA_H__1E9A4D94_7ECC_461B_8CEC_6BE1A437D9BF__INCLUDED_)
#define AFX_DLGTRANSDATA_H__1E9A4D94_7ECC_461B_8CEC_6BE1A437D9BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTransData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTransData dialog

class CDlgTransData : public CDialog
{
// Construction
public:
	CDlgTransData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTransData)
	enum { IDD = IDD_DIALOG_TRANS_DATA };
	CComboBox	m_cmbDev;
	CString	m_strSend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTransData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTransData)
	afx_msg void OnButtonSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnResult(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitComb();
	
	//parameters
	static void CALLBACK FUNMCMsgCB(GPSMCMsg_S* pMsg, void* pUsr);
	void	DoMCMsgCB(GPSMCMsg_S* pMsg);
	
	void EnableCtrl(BOOL bEnable);
private:
	long m_lHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSDATA_H__1E9A4D94_7ECC_461B_8CEC_6BE1A437D9BF__INCLUDED_)
