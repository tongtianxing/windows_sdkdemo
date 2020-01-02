#if !defined(AFX_DLGSNAPSHOT_H__09385144_03BD_4ACE_B3B4_F100576E871F__INCLUDED_)
#define AFX_DLGSNAPSHOT_H__09385144_03BD_4ACE_B3B4_F100576E871F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSnapshot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSnapshot dialog
class CDownSnapshot;
class CDlgSnapshot : public CDialog
{
// Construction
public:
	CDlgSnapshot(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSnapshot)
	enum { IDD = IDD_DLG_SNAPSHOT };
	CStPicture	m_stPic;
	CButton m_btnBrowse;
	CButton m_btnSave;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSnapshot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSnapshot)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtnSave();
	afx_msg void OnBtnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void	LoadLanguage();
	void	SetDLSnap(CDownSnapshot* pSnapshot) {	m_pDLSnapshot = pSnapshot; }
	void	SetBMPFile(const TCHAR* szBmpFile, SYSTEMTIME& bmpTime) {		_tcscpy(m_szBMPFile, szBmpFile);	m_tmBMPTime = bmpTime;	}
	void	SaveBMPFile();
	CString	GetDevImgPath(const TCHAR* szDevID, const TCHAR* szDevNO, BOOL bDevive);
	void    SetDevID(int nDevID, int nChn);

	void	SetSaveFile(CString strFile);

private:
	CDownSnapshot*	m_pDLSnapshot;
	TCHAR			m_szBMPFile[MAX_PATH];
	SYSTEMTIME		m_tmBMPTime;
	int				m_nDevID;
	int				m_nChn;
	CString			m_strFilePath; //Save Picture Full Path
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSNAPSHOT_H__09385144_03BD_4ACE_B3B4_F100576E871F__INCLUDED_)
