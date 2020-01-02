#if !defined(AFX_DLGRECPLAYBACKCONTROL_H__2DBC47A1_2C7E_4B39_887B_9D22E340AA1B__INCLUDED_)
#define AFX_DLGRECPLAYBACKCONTROL_H__2DBC47A1_2C7E_4B39_887B_9D22E340AA1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecPlaybackControl.h : header file
//


//#include "ProSliderCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgRecPlaybackControl dialog
class CPlayback;
class CDlgRecPlaybackControl : public CDialog
{
// Construction
public:
	CDlgRecPlaybackControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecPlaybackControl)
	enum { IDD = IDD_DLG_REC_PLAYBACK_CONTROL };
	CSliderCtrl m_sliderVol;
	CSliderCtrl	m_sliderTime;
	CButton	m_btnCapture;
	CButton	m_btnSound;
	CButton	m_btnIFrame;
	CButton	m_btnStop;
	CButton	m_btnPlay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecPlaybackControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecPlaybackControl)
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonIFrame();
	afx_msg void OnBtnCapture();
	afx_msg void OnButtonSound();
 	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LRESULT OnPlaybackPlayMsg(WPARAM wParm, LPARAM lParam);
// 	afx_msg LRESULT OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam);
// 	afx_msg LRESULT OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam);
//	afx_msg void OnReleasedcaptureSliderTime(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int Play(GPSFile_S* pFile, int nChannel, int nBegMinSecond, int nEndMinSecond, HWND hWnd);
	void Stop();
	void AdjustedWndRect();

private:
	void MoveCtrl();
	void ChangePlayBtnStatus();
	void ChangeSoundBtnStatus();
	void ChangeIFramBtnStatus();
	void EnableCtrl();

private:
	void DoPlayFailed();
	void DoPlayFinished();
	void DoPlayDownFinished();
	void UpdatePlayTime();
	void UpdateDownTime();
	void UpdateDownSpeed();

	void ChangeVolume();

private:
	CPlayback* m_pPlayback;
	int	m_nPlayType;
	int m_nPlayStatus;
	int m_nSoundStatus;
	BOOL m_bPlayIFrame;

	CString m_strPlayTime;
	CString m_strDownSpeed;
	CString m_strStartTime;
	CString m_strEndTime;

	int m_uiStartTime;
	int m_uiEndTime;
	CRect m_rcStartTime;
	CRect m_rcEndTime;
	CRect m_rcPlayTime;
	CRect m_rcDownSpeed;

	BOOL m_bThumbTrack;

//	CTipSmart m_Tip;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECPLAYBACKCONTROL_H__2DBC47A1_2C7E_4B39_887B_9D22E340AA1B__INCLUDED_)
