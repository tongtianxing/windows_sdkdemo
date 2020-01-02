#if !defined(AFX_PVFRAMEWND_H__5EBABD12_13AA_48A6_8E7A_F85F0B74F166__INCLUDED_)
#define AFX_PVFRAMEWND_H__5EBABD12_13AA_48A6_8E7A_F85F0B74F166__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PVFrameWnd.h : header file
//


#define PV_DIV_VIEW_NUM		7
#define PV_ROW_VIEW_NUM		(PV_DIV_VIEW_NUM/2)		
#define PV_MAIN_VIEW_ID		-1
#define PV_PART_VIEW_ID		-2

#define PV_MODE_NONE		-1
#define PV_MODE_REAL		0
#define PV_MODE_POLLING		1
#define PV_MODE_VOD			2
#define PV_MODE_PICTURE		3		

#define WM_MSG_CHAN_REAL_FAILED WM_USER + 0x1000
/////////////////////////////////////////////////////////////////////////////
// CPVFrameWnd window

class CDlgPaneView;
class CPVPlay;
class CPVRealPlay;
class CPVViewWnd;
class CPVFrameWnd : public CWnd
{
// Construction
public:
	CPVFrameWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPVFrameWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPVFrameWnd();

	// Generated message map functions
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	//{{AFX_MSG(CPVFrameWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuPreviewAudio();
	afx_msg void OnMenuPreviewDevSetup();


	afx_msg void OnMenuPreviewPolling();
	afx_msg void OnMenuPreviewPollingAll();
	afx_msg void OnMenuPreviewSetup();
	afx_msg void OnMenuPreviewStopPollingAll();

	afx_msg void OnMenuPreviewView();
	afx_msg void OnMenuPreviewCapture();
	afx_msg void OnMenuPreviewSnapDev();
	afx_msg void OnMenuPreviewUp();
	afx_msg void OnMenuPreviewDown();
	afx_msg void OnMenuViewSize169();
	afx_msg void OnMenuViewSize43();
	afx_msg void OnMenuViewSizeFull();
	afx_msg void OnMenuViewModeReal();
	afx_msg void OnMenuViewModeSmooth();
	afx_msg void OnMenuPreviewStopAudio();
	afx_msg void OnMenuBcastStart();
	afx_msg void OnMenuStartVideorecord();
	afx_msg void OnMenuStopVideorecord();

	//}}AFX_MSG
	afx_msg LRESULT OnMsgChanRealFailed(WPARAM wPram, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:

public:
	void	MoveCtrl();
	void	SetIndex(int nIndex) {	m_nIndex = nIndex; }
	int		GetIndex()	{	return m_nIndex; }
	void	SetPaneView(CDlgPaneView* pDlg) {	m_pDlgPaneView = pDlg; }
	CDlgPaneView*  GetPaneView() {  return m_pDlgPaneView; }
	BOOL	IsPaneAlarmView();

	BOOL	GetActive();
	void	SetActive(BOOL bActive);
	void	SetPartMode(BOOL bPart);
	void	ShowPlayTip(LPCTSTR lpszTip);
	CString	GetPlayTip();
	void	ShowToolTip(LPCTSTR lpszTip);
	HWND	GetPlayHwnd();
	void	CloseSound();
	void	PlaySound();
	void	Snapshot();
	void	SnapDev();

	void    FlashPlayWnd();

	BOOL	GetDueStatus(CString& strTip);
	BOOL	GetSoundStatus();

	BOOL	PlayValid();
	void	SetDrawRect(RECT& rcRegion, RECT& rcClient);
	void	SetDrawEmpty();
	void	SetDrawFocus(BOOL bFocus);

	BOOL	IsPreviewing();
	BOOL	PlayRemoteFile(GPSFile_S *pFile);
	BOOL	IsPlayRemoteFile(GPSFile_S *pFile);
	BOOL	IsDevChnPreviewing(int nDevID, int nChn, BOOL bMain);
	BOOL	IsDevChnPicture(int nDevID, int nChn);
	void	UpdatePreview();
	CPVPlay*	GetPVPlayPlayer();
	BOOL	IsOpenSound();

	void	PreviewRealVideo(int nDevID, int nChn, BOOL bMainStream, int nPlayMode=PV_MODE_REAL);
	void	PreviewDefaultAV();
	void	GetDefaultAV(int& nDevID, int& nChn);
	void	StopPreview();
	BOOL	EnablePreview();

	void	DoCommandSnapshot();
	BOOL	IsPlayerMode();
	BOOL	IsPictureMode();
	void	ChangeVolume(WORD wVolume);

	int		GetViewSize();
	void	SetViewSize(int nViewSize);
	void	SetViewMode(int nViewMode);
	void	SetDelayTime();
	void	GetFlowRate(int* lpFlowRate);

	void    CheckCloseVideo(DWORD dwTime);

//	CPVRealPlay* GetPVRealPlay() {	return m_pRealPlayer; }

	int     GetPlayMode(){ return m_nPlayMode;}

	void    StopChannelView();
	void	Start();
	BOOL	IsRecord();
	BOOL	IsModeWnd64();

	void	DoAlarmSnapshotFinish(CDevBase* pDevice, GPSVehicleAlarm_S* pVehiAlarm);
	void	GetPictureImg(HDC hDC, CRect rcClient);

public:
	void	OnDIVLBtnDown(int nDivIndex);
	void	OnDIVLBDblClk(int nDivIndex);
	void	AdjustedWndRect();

public:
	static void WINAPI FUNRealDataCB(const char* pFrameBuf , int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp, void* pUsr);
	static void WINAPI FUNRealDecCB(unsigned char* pY, int nYStride, unsigned char* pU, unsigned char* pV, int nUVStride, 
		int nWidth, int nHeight, unsigned __int64 nStamp, int nType, void* pUsr);
protected:
	void	SetPVModeNone();
	void	SetPVModeReal();
	void	SetPVModeVod();
	void	ExitPlayMode();

private:
	CDlgPaneView*	m_pDlgPaneView;
	int		m_nIndex;
// 	CPVPlay*		m_pPVPlay;
// 	CPVRealPlay*	m_pRealPlayer;
	CString         m_strPollingGroupName;
	int		m_nPlayMode;

	CPVViewWnd		*m_pMainView;
	BOOL	m_bDivMode;
	BOOL	m_bPartMode;
	int		m_nDivActIndex;
	int		m_nViewSize;

	long m_lHandle;
	int m_nDevID;
	int m_nChannel;
	int m_bMain;

	long m_lRecHandle;
	long m_BegPos;
	long m_EndPos;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PVFRAMEWND_H__5EBABD12_13AA_48A6_8E7A_F85F0B74F166__INCLUDED_)
