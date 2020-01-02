#if !defined(AFX_DLGPANEVIEW_H__D0C8BFE9_408D_4C94_B98A_269EA26D29CB__INCLUDED_)
#define AFX_DLGPANEVIEW_H__D0C8BFE9_408D_4C94_B98A_269EA26D29CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPaneView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaneView dialog

//#define VIEW_MAX_NUM	16
#ifdef VERSIONS_64
	#define VIEW_MAX_NUM	64
#else
	#define VIEW_MAX_NUM	16
#endif

const int WND_ROW_NUM = 4;
const int WND_MODE_1 = 1;
const int WND_MODE_4 = 2;
const int WND_MODE_9 = 3;
const int WND_MODE_16 = 4;
const int WND_MODE_36 = 6;
const int WND_MODE_64 = 8;

const int WND_MODE_6 = 10;
const int WND_MODE_8 = 11;
#define MAX_WND_MODE_NUM	WND_MODE_8

const int VIEW_TITLE_HEIGHT = 24;
const int VERTICAL_MOVE_COUNT = 4;


#define MSG_DLG_PANE_VIEW_FULL_SCREEN WM_USER+0x01

class CPVFrameWnd;
class CPVLocalPlay;
class CDlgTBarView;
class CPVPlay;
class CDlgPaneView : public CDialog
{
// Construction
public:
	CDlgPaneView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPaneView)
	enum { IDD = IDD_DLG_PREVIEW };
// 	CCxButton	m_btnViewWnd16;
// 	CCxButton	m_btnViewWnd9;
// 	CCxButton	m_btnViewWnd8;
// 	CCxButton	m_btnViewWnd6;
// 	CCxButton	m_btnViewWnd4;
// 	CCxButton	m_btnViewWnd1;
// 	CCxButton	m_btnViewWnd64;
// 	CCxButton	m_btnViewWnd36;
// 	CCxButton	m_btnViewUp;
// 	CCxButton	m_btnViewSizePrompt;
// 	CCxButton	m_btnViewMode;
// 	CCxButton	m_btnViewDown;
// 	CCxButton	m_btnTalkback;
// 	CCxButton	m_btnSound;
// 	CCxButton	m_btnCapture;
// 	CCxButton	m_btnCaptureDrop;
// 	CCxButton	m_btnAVStop;
// 	CCxButton	m_btnAVStart;
// 	CCxButton	m_btnAVStartDrop;
// 	CCxButton	m_btnAVStopDrop;
// 	CCxButton	m_btnScreen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaneView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaneView)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);

	void OnMenuViewSnapshot();

	afx_msg void OnMenuViewModeSmooth();
	afx_msg void OnMenuViewModeReal();
	afx_msg void OnMenuViewWnd();
	afx_msg void OnMenuViewDown();
	afx_msg void OnMenuViewUp();
	afx_msg void OnMenuViewAvStart();
	afx_msg void OnMenuViewAvStop();
	afx_msg void OnMenuViewAvStartAll();
	afx_msg void OnMenuViewAvStopAll();
	afx_msg void OnButtonCapture();
	afx_msg void OnButtonSound();
	afx_msg void OnButtonAvStart();
	afx_msg void OnButtonAvStop();

	afx_msg void OnMenuPreviewCapture();
	afx_msg void OnMenuPreviewSnapDev();

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	BOOL	FindActiveIndex(int nActiveIndex);
	void	AdjustActiveIndex();

	BOOL	IsEnableViewGroup();
	int		GetVideoNumber();

	static void CALLBACK FUNPtzMsgCB(GPSMCMsg_S* pMsg, void* pUsr);
	void	DoPtzMsgCB(GPSMCMsg_S* pMsg);

	LRESULT OnPtzMsg(WPARAM wParam, LPARAM lParam);

public:
	void	MoveCtrl();
	void	ShowVertical(BOOL bVertical);
	BOOL	IsShowVertical() {	return m_bShowVertical;}
	void	ViewActive(int nIndex);
	void	ShowOneMax();
	void	SetWndMode(int nMode);
	int		GetWndMode() {	return m_nWndMode; }

	void	SetWndMove(BOOL bUp);

	void	DoPlayAudio();
	void	DoSnapshot();
	void	DoSnapDev();

	void	CloseAllSound();

	void	DoSelect();
	void	IntoOneMax();
	void	UpdateSound();

	BOOL	IsActivePreview();
	BOOL	IsDevChnPreviewing(int nDevID, int nChn, BOOL bMain, int& nWndIndex);
	BOOL	IsDevChnPicture(int nDevID, int nChn, int& nWndIndex);

	void	UpdatePreviewDev();
	void	PreviewRealVideo(int nDevID, int nChn, BOOL bMainStream);
	void	PreviewAlarmVideo(int nDevID, int nChn, BOOL bMainStream);/////
	int 	PreviewRealVideoDClik(int nDevID, int nChn, BOOL bMainStream);
	void	OnDevChanPreView(int nDevID, int nChn, BOOL bMainStream);
	BOOL	IsPlayRemoteFile(GPSFile_S* pFile, int& nWndIndex);
	BOOL	PlayRemoteFile(GPSFile_S* pFile);
	void	StopPlay();
	CPVPlay*	GetPVPlayPlayer();

	void	ChangeVolume(WORD wVolume);
	void	PtzControl(int nCommand, int nParam, int nSpeed);
	void	ColorControl(int nBri, int nCon, int nHue, int nSat);

	void	ChangeViewMode();
	void	ChangeViewSize();
	void    SetDelayTime();

	void    SetWndInActive();
	void    StopAllVideo();
	CPVFrameWnd* GetPvFramWnd(int WndIndex);
	HWND GetPlaybackWnd();
	void	SetPVFrameWnd(int nWndIndex, CPVFrameWnd* pWnd);
	static void	SwapPvFrameWnd(CPVFrameWnd* pAlarm, CPVFrameWnd* pReal);
	void	OnVideoDrag(int nVideoDragfromIndex, int nVideoDragtoIndex);
	void	SetIndex(int nIndex) { m_nExCelIndex = nIndex; }
	int		GetIndex() { return m_nExCelIndex; }

	void    ShowVideoWnd(int nShowNum);
	
	void    MoveExtra(RECT rc, int nDiv);

	void    MoveNormal(RECT rc, int nWndMode);	
    void    MoveVideoWnd(int nIndex, RECT rcMove);
	int		GetVideoShowCount();
	void	PreviewVideo(int nDevID, int nChn, int nIndex);
	void    StopPreviewPolling();

	void    ResetPVPlayerTime();
	void    ResetPVPlayerTime(int nWndIndex);

	void    StopVideoView(int nID,int nChn);
	void	Start();
	void	ShowViewTilte();

	void	DoAlarmSnapshotFinish(CDevBase* pDevice, GPSVehicleAlarm_S* pVehiAlarm);
	BOOL	StartPicturePreview(int nDevID);
	BOOL	StopPicturePreview(int nDevID);

//	void	SetPaneViewMode(int nViewMode) { m_nViewMode = nViewMode; }


private:
	CPVFrameWnd* m_pViewWnd[VIEW_MAX_NUM];
	int		m_nWndMode;
	int		m_nActiveIndex;
	int		m_nVideoIndex;
	BOOL	m_bShowOneMax;
	BOOL	m_bShowVertical;

	int		m_nAlarmIndexOld;

	int		m_nExCelIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPANEVIEW_H__D0C8BFE9_408D_4C94_B98A_269EA26D29CB__INCLUDED_)
