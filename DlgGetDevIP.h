#if !defined(AFX_DLGGETDEVIP_H__1157BE95_0E34_4951_BC46_816B1854B643__INCLUDED_)
#define AFX_DLGGETDEVIP_H__1157BE95_0E34_4951_BC46_816B1854B643__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetDevIP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGetDevIP dialog

class CDlgGetDevIP : public CDialog
{
// Construction
public:
	CDlgGetDevIP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGetDevIP)
	enum { IDD = IDD_DIALOG_GET_DEV_IP };
	CListCtrl	m_listDevIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGetDevIP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGetDevIP)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSelDev();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnMsgDevIP(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgDevIPMsg(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	static void CALLBACK FUNGetDevIPCB(int nType, void* pData, void * pUsr);
	void DoGetDevIPCB(int nType, void* pData);

	void GetDevIP(GPSDeviceIDNO_S* pDevice, unsigned int nDevCount);
	void EnableCtrl(BOOL bEnable);
private:
	long m_lHandle;
	GPSDeviceIDNO_S* m_pDevice;
	int m_DevCount;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETDEVIP_H__1157BE95_0E34_4951_BC46_816B1854B643__INCLUDED_)
