#if !defined(AFX_DLGRECPLAYBACK_H__8B1E24AA_C1FA_4302_B963_CFF72B640E33__INCLUDED_)
#define AFX_DLGRECPLAYBACK_H__8B1E24AA_C1FA_4302_B963_CFF72B640E33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecPlayback.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecPlayback dialog
class CDlgPaneMap;
class CDlgPaneView;
class CDlgRecPlaybackControl;
class CDlgRecPlayback : public CDialog
{
// Construction
public:
	CDlgRecPlayback(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecPlayback)
	enum { IDD = IDD_DLG_REC_PLAYBACK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecPlayback)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecPlayback)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void Play(GPSFile_S* pFile, int nChannel, int nBegMinSecond);
	void Stop();
	void PlayPicture(CString str);
	void ChangeViewSize();
	void ShowViewTilte();

private:
	void MoveCtrl();
	void FirstPlay();

	void CreateMapDlg();
	
private:
//	CDlgPaneMap* m_pDlgPaneMap;
	CDlgPaneView* m_pDlgPaneView;
	CDlgRecPlaybackControl* m_pDlgControl;
	BOOL m_bFirst;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECPLAYBACK_H__8B1E24AA_C1FA_4302_B963_CFF72B640E33__INCLUDED_)
