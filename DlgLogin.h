#if !defined(AFX_DLGLOGIN_H__20B65B3F_3902_4B05_9392_E76C2DDFE24D__INCLUDED_)
#define AFX_DLGLOGIN_H__20B65B3F_3902_4B05_9392_E76C2DDFE24D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogin.h : header file
//
#include "LoadThread.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog

class CDlgLogin : public CDialog
{
// Construction
public:
	CDlgLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogin)
	enum { IDD = IDD_DIALOG_LOGIN };
	CString	m_strIP;
	CString	m_strPsw;
	CString	m_strUser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogin)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnMsgLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgLoad(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	static void WINAPI FUNLoginMsgCB(int nMsg, void * pUsr);
	void	DoLoginMsgCB(int nMsg);

private:
	void	EnableCtrl(BOOL bEnable);
	unsigned short m_usSvrPort;
	bool		m_bLogining;
	BOOL		m_bLoginSuc;
	CLoadThread	m_loadThread;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGIN_H__20B65B3F_3902_4B05_9392_E76C2DDFE24D__INCLUDED_)
