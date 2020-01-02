#if !defined(AFX_DLGPLAY_H__D77A11B2_CFED_43C7_82A0_3B69A3E20CB9__INCLUDED_)
#define AFX_DLGPLAY_H__D77A11B2_CFED_43C7_82A0_3B69A3E20CB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPlay dialog

#include "SliCtrlEx.h"
#define WM_MSG_FILE_END				WM_USER+0x1005

class CDlgPlay : public CDialog
{
// Construction
public:
	CDlgPlay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPlay)
	enum { IDD = IDD_DLG_PLAY };
	CSliderCtrl	m_sliVolume;
	CButton	m_btnSound;
	CSliCtrlEx	m_sliPos;
	CStatic	m_stTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlay)
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnPlay();
	afx_msg void OnBtnPause();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnSlow();
	afx_msg void OnBtnFast();
	afx_msg void OnBtnStep();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChkSound();
	afx_msg void OnReleasedcaptureSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonFrowardIFram();
	afx_msg void OnButtonBackwardIFram();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgFileEnd(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	void	RestorePlay();
	void	UpdateRate();
	CString	FormatSecond(long nSecond);
	void	CloseFile();
	void	PlayFile();
	static void WINAPI EndCBFun(int nMsg, void* pUsr);
	void	DoEndCB(int nMsg);
	void	ChangeVolume();

private:
	long	m_lPlayHandle;
	BOOL	m_bPause;
	IDECFileInfo_S	m_FileInfo;
	DWORD	m_dwSetPos;
	int		m_nPlayRate;
	BOOL	m_bOpenSound;
	CString	m_strFileTime;
	CString m_strPlayFile;
public:
	afx_msg void OnBnClickedButtonSn();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAY_H__D77A11B2_CFED_43C7_82A0_3B69A3E20CB9__INCLUDED_)
