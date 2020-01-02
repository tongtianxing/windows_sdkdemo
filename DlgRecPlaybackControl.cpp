// DlgRecPlaybackControl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecPlaybackControl.h"
//#include "UIManager.h"
#include "Playback.h"
#include "DlgSnapshot.h"
#include "DevBase.h"
#include "VMgrDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgRecPlaybackControl dialog

#define PLAYBACK_TYPE_UNKONW	-1
#define PLAYBACK_TYPE_RECORD	0
#define PLAYBACK_TYPE_PICTURE	1

#define PLAYBACK_PLAY_STATUS_STOP		0
#define PLAYBACK_PLAY_STATUS_PLAYING	1
#define PLAYBACK_PLAY_STATUS_PAUSE		2

#define PLAYBACK_SOUND_STATUS_CLOSE		0
#define PLAYBACK_SOUND_STATUS_OPEN		1

#define EVENT_GET_FLOW_RATE		1		//download speed
#define EVENT_GET_PLAY_TIME		2		//play time
#define EVENT_GET_DWON_TIME		3		//download time

#define WM_MSG_PLAYBACK_PLAY	WM_USER+0x0001

#define PLAYBACK_SILDER_TIME_RANGE		100
#define PLAYBACK_SILDER_VOLUME_RANGE	100


CDlgRecPlaybackControl::CDlgRecPlaybackControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecPlaybackControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecPlaybackControl)
		// NOTE: the ClassWizard will add member initialization here
	m_pPlayback = NULL;
	m_nPlayStatus = PLAYBACK_PLAY_STATUS_STOP;
	m_nSoundStatus = PLAYBACK_SOUND_STATUS_OPEN;
	m_bPlayIFrame = FALSE;
 	m_strStartTime = "00:00:00";
	m_strEndTime = "00:00:00";
	m_uiStartTime = 0;
	m_uiEndTime = 0;
	m_bThumbTrack = FALSE;
	m_nPlayType = PLAYBACK_TYPE_UNKONW;
	//}}AFX_DATA_INIT
}


void CDlgRecPlaybackControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecPlaybackControl)
	DDX_Control(pDX, IDC_SLIDER_VOL, m_sliderVol);
	DDX_Control(pDX, IDC_SLIDER_TIME, m_sliderTime);
	DDX_Control(pDX, IDC_BTN_CAPTURE, m_btnCapture);
	DDX_Control(pDX, IDC_BUTTON_SOUND, m_btnSound);
	DDX_Control(pDX, IDC_BUTTON_I_FRAME, m_btnIFrame);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_btnPlay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecPlaybackControl, CDialog)
	//{{AFX_MSG_MAP(CDlgRecPlaybackControl)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_I_FRAME, OnButtonIFrame)
	ON_BN_CLICKED(IDC_BTN_CAPTURE, OnBtnCapture)
	ON_BN_CLICKED(IDC_BUTTON_SOUND, OnButtonSound)
	ON_WM_HSCROLL()
//	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TIME, OnReleasedcaptureSliderTime)
	//}}AFX_MSG_MAP
// 	ON_MESSAGE(WM_BITMAPSLIDER_MOVED, OnBitmapSliderMoved)
// 	ON_MESSAGE(WM_BITMAPSLIDER_MOVING, OnBitmapSliderMoving)
	ON_MESSAGE(WM_MSG_PLAYBACK_PLAY, OnPlaybackPlayMsg)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecPlaybackControl message handlers

BOOL CDlgRecPlaybackControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pPlayback = new CPlayback;
	m_pPlayback->SetMsgWnd(m_hWnd, WM_MSG_PLAYBACK_PLAY);
	m_pPlayback->SetProgressMax(PLAYBACK_SILDER_TIME_RANGE);

	m_sliderTime.SetRange(0, PLAYBACK_SILDER_TIME_RANGE);
	
	m_sliderVol.SetRange( 0, PLAYBACK_SILDER_VOLUME_RANGE );
	m_sliderVol.SetPos( 30 );
	m_sliderVol.SetPageSize( 10 );

	m_btnIFrame.SetWindowText(LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_STEP));
	m_btnStop.SetWindowText(LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_STOP));
	m_btnCapture.SetWindowText(LOADSTRINGEX(ID_STR_DLG_SYSTEM_ST_PIC_CAPTURE));

	ChangePlayBtnStatus();
	ChangeSoundBtnStatus();

	EnableCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRecPlaybackControl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
//	CUIManager::GetInstance()->DrawDlgRecPlaybackControlBK(dc.GetSafeHdc(), this);
	::SetBkMode(dc.GetSafeHdc(), TRANSPARENT);
//	HGDIOBJ hOldFnt = ::SelectObject(dc.GetSafeHdc(), CGlobalFont::GetInstance()->GetTextFontHandle());
	::DrawText(dc.GetSafeHdc(), m_strStartTime, m_strStartTime.GetLength(), m_rcStartTime, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	::DrawText(dc.GetSafeHdc(), m_strEndTime, m_strEndTime.GetLength(), m_rcEndTime, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
 	::DrawText(dc.GetSafeHdc(), m_strPlayTime, m_strPlayTime.GetLength(), m_rcPlayTime, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
 	::DrawText(dc.GetSafeHdc(), m_strDownSpeed, m_strDownSpeed.GetLength(), m_rcDownSpeed, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
// 	if(hOldFnt)
// 	{
// 		::SelectObject(dc.GetSafeHdc(), hOldFnt);
// 	}

	// Do not call CDialog::OnPaint() for painting messages
}
BOOL CDlgRecPlaybackControl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( (WM_KEYDOWN == pMsg->message) && (VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		return FALSE;
	}
//	m_Tip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgRecPlaybackControl::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	KillTimer(EVENT_GET_PLAY_TIME);
	KillTimer(EVENT_GET_FLOW_RATE);
	KillTimer(EVENT_GET_DWON_TIME);
	m_pPlayback->Uninit();
	SAFE_DELETE_OBJECT(m_pPlayback);
}
void CDlgRecPlaybackControl::MoveCtrl()
{
	if (m_sliderTime.GetSafeHwnd())
	{
		CRect rcClient, rcMove, rcBtn;
		GetClientRect(rcClient);

		rcMove = rcClient;
		
		const int nStatic = 60;
		rcMove.left += 10;
		rcMove.right = rcMove.left + nStatic;
		rcMove.top += 4;
		rcMove.bottom = rcMove.top + 25;
		m_rcStartTime = rcMove;

//  		rcMove.top = rcClient.top + 5;
//  		rcMove.bottom = rcMove.top + 30;
		rcMove.left = rcMove.right;
		rcMove.right = rcClient.right - nStatic;
		m_sliderTime.MoveWindow(rcMove);

		rcMove.top = rcClient.top + 4;
		rcMove.left = rcMove.right;
		rcMove.right = rcMove.left + nStatic;
		m_rcEndTime = rcMove;

		const int nBtnInterval = 7;
		m_btnPlay.GetClientRect(rcBtn);
		rcMove.top = rcMove.bottom + 1;
		rcMove.bottom = rcMove.top + rcBtn.Height();
		rcMove.left = rcClient.left + nStatic + 5;
		rcMove.right = rcMove.left + rcBtn.Width();
		m_btnPlay.MoveWindow(rcMove);

		m_btnStop.GetClientRect(rcBtn);
		rcMove.left = rcMove.right + nBtnInterval;
		rcMove.right = rcMove.left + rcBtn.Width();
		m_btnStop.MoveWindow(rcMove);

		m_btnIFrame.GetClientRect(rcBtn);
		rcMove.left = rcMove.right + nBtnInterval;
		rcMove.right = rcMove.left + rcBtn.Width();
		m_btnIFrame.MoveWindow(rcMove);

		m_btnCapture.GetClientRect(rcBtn);
		rcMove.left = rcMove.right + nBtnInterval;
		rcMove.right = rcMove.left + rcBtn.Width();
		m_btnCapture.MoveWindow(rcMove);

		rcMove.left = rcMove.right - 60;
		rcMove.right = rcMove.left + nStatic;
		m_rcPlayTime = rcMove;

		rcMove.left = rcMove.right + 20;
		rcMove.right = rcMove.left + 2*nStatic;
		m_rcDownSpeed = rcMove;

		m_btnSound.GetClientRect(rcBtn);
		rcMove.left = rcClient.right - 100;
		rcMove.right = rcMove.left + rcBtn.Width();
		m_btnSound.MoveWindow(rcMove);

		rcMove.left = rcMove.right + 5;
		rcMove.right = rcClient.right - 5;
		m_sliderVol.MoveWindow(rcMove);
	}
}
void CDlgRecPlaybackControl::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	MoveCtrl();
}

void CDlgRecPlaybackControl::UpdatePlayTime()
{
	if (m_nPlayStatus == PLAYBACK_PLAY_STATUS_PLAYING)
	{
		int nPos = 0;
		CString strTime;
		if (S_OK == m_pPlayback->GetPlayProgress(nPos, strTime))
		{
			m_sliderTime.SetPos(nPos);
			GetDlgItem(IDC_STATIC_TIME)->SetWindowText(strTime);
			InvalidateRect(m_rcPlayTime);
		}
	}
}
void CDlgRecPlaybackControl::UpdateDownTime()
{
	if (m_nPlayStatus != PLAYBACK_PLAY_STATUS_STOP)
	{
		int nPos = 0;
		if (S_OK == m_pPlayback->GetDownProgress(nPos))
		{
//			m_sliderTime._SetPos(nPos);
		}
	}
}
void CDlgRecPlaybackControl::UpdateDownSpeed()
{	
	if (m_nPlayStatus != PLAYBACK_PLAY_STATUS_STOP)
	{
		int nFlowRate = 0;
		m_pPlayback->GetFlowRate(&nFlowRate);
		m_strDownSpeed.Format(_T("%d KB/S"), nFlowRate);
		InvalidateRect(m_rcDownSpeed);
//		TRACE("FlowRate = %d\n", nFlowRate);
	}
}
void CDlgRecPlaybackControl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (EVENT_GET_FLOW_RATE == nIDEvent)
	{
		UpdateDownSpeed();
	}
	else if (EVENT_GET_PLAY_TIME == nIDEvent)
	{
		if (m_bThumbTrack == FALSE)
		{
			UpdatePlayTime();
		}
	}
	else if (EVENT_GET_DWON_TIME == nIDEvent)
	{
		UpdateDownTime();
	}
	
	CDialog::OnTimer(nIDEvent);
}


int CDlgRecPlaybackControl::Play(GPSFile_S* pFile, int nChannel, int nBegMinSecond, int nEndMinSecond, HWND hWnd)
{
	int nRet = S_FALSE;
	nRet = m_pPlayback->Play(pFile, nChannel, nBegMinSecond, nEndMinSecond, m_bPlayIFrame, hWnd);
	if(S_OK == nRet)
	{
		m_sliderTime.SetPos(0);
//		m_sliderTime._SetPos(0);
		if (m_nSoundStatus == PLAYBACK_SOUND_STATUS_OPEN)
		{
			m_pPlayback->PlaySound(m_nSoundStatus);
		}
		if (pFile)
		{
			m_uiStartTime = pFile->uiBegintime;
			m_uiEndTime = pFile->uiEndtime;
			m_strStartTime = FormatSecond(pFile->uiBegintime);
			m_strEndTime = FormatSecond(pFile->uiEndtime);
		}
		InvalidateRect(m_rcStartTime);
		InvalidateRect(m_rcEndTime);
		m_nPlayStatus = PLAYBACK_PLAY_STATUS_PLAYING;
		ChangePlayBtnStatus();
		EnableCtrl();
		SetTimer(EVENT_GET_FLOW_RATE, 1000, NULL);
		SetTimer(EVENT_GET_PLAY_TIME, 1000, NULL);
		SetTimer(EVENT_GET_DWON_TIME, 1000, NULL);
	}
	else
	{
		m_nPlayStatus = PLAYBACK_PLAY_STATUS_STOP;
	}

	return nRet;
}

void CDlgRecPlaybackControl::Stop()
{
//	if (m_nPlayType == PLAYBACK_TYPE_RECORD)
	{
		if(m_nPlayStatus != PLAYBACK_PLAY_STATUS_STOP)
		{
			KillTimer(EVENT_GET_PLAY_TIME);
			KillTimer(EVENT_GET_FLOW_RATE);
			KillTimer(EVENT_GET_DWON_TIME);
			m_pPlayback->StopPlay();
			m_pPlayback->Uninit();
			m_nPlayStatus = PLAYBACK_PLAY_STATUS_STOP;
			ChangePlayBtnStatus();
			EnableCtrl();
		}
	}
// 	else if (m_nPlayType == PLAYBACK_TYPE_PICTURE)
// 	{
// 		m_nPlayStatus = PLAYBACK_PLAY_STATUS_STOP;
// 		EnableCtrl();
// 	}

}
void CDlgRecPlaybackControl::OnButtonPlay() 
{
	
	if (m_nPlayStatus == PLAYBACK_PLAY_STATUS_PLAYING)
	{
		m_pPlayback->Pause(TRUE);
		m_nPlayStatus = PLAYBACK_PLAY_STATUS_PAUSE;
		
	}
	else if (m_nPlayStatus == PLAYBACK_PLAY_STATUS_PAUSE)
	{
		m_pPlayback->Pause(FALSE);
		m_nPlayStatus = PLAYBACK_PLAY_STATUS_PLAYING;
	}
	else if (m_nPlayStatus == PLAYBACK_PLAY_STATUS_STOP)
	{
		Play(NULL, 0, 0, m_pPlayback->GetFileMinSecond(), NULL);
	}
	ChangePlayBtnStatus();
}

void CDlgRecPlaybackControl::OnButtonStop() 
{
	
	Stop();
}

void CDlgRecPlaybackControl::OnButtonIFrame() 
{
	
	if (m_bPlayIFrame)
	{
		m_bPlayIFrame = FALSE;
	}
	else
	{
		m_bPlayIFrame = TRUE;
	}
//	m_nPlayStatus = PLAYBACK_PLAY_STATUS_PLAYING;
	m_pPlayback->SetPlayIFrame(m_bPlayIFrame);
	ChangeIFramBtnStatus();
}

void CDlgRecPlaybackControl::OnBtnCapture() 
{
	
	if (m_nPlayStatus != PLAYBACK_PLAY_STATUS_STOP)
	{
		TCHAR szTmpPath[MAX_PATH] = {0};
		TCHAR szFilename[MAX_PATH] = {0};
		::GetTempPath (MAX_PATH, szTmpPath) ;
		::GetTempFileName (szTmpPath, TEXT("gViewerbmp"), 0, szFilename) ;
		if (S_OK == m_pPlayback->CaptureBMP(szFilename))
		{
			TCHAR szDevIDNO[64] = {0};
			int nChannel = 0;
			int nDevID = 0;
			m_pPlayback->GetFileDevAndChannel(szDevIDNO, 64, nChannel);
			CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(szDevIDNO);
			if (pDev)
			{
				nDevID = pDev->GetID();
			}
			SYSTEMTIME tmNow;
			GetLocalTime(&tmNow);
			CDlgSnapshot dlg;
			dlg.SetBMPFile(szFilename, tmNow);
			dlg.SetDevID(nDevID, nChannel);
			dlg.DoModal();
		}
	}
}

void CDlgRecPlaybackControl::OnButtonSound() 
{
	
	if (m_nPlayStatus != PLAYBACK_PLAY_STATUS_STOP)
	{
		if (m_nSoundStatus == PLAYBACK_SOUND_STATUS_CLOSE)
		{
			m_pPlayback->PlaySound(PLAYBACK_SOUND_STATUS_OPEN);
			m_nSoundStatus = PLAYBACK_SOUND_STATUS_OPEN;
		}
		else if(m_nSoundStatus == PLAYBACK_SOUND_STATUS_OPEN)
		{
			m_pPlayback->PlaySound(PLAYBACK_SOUND_STATUS_CLOSE);
			m_nSoundStatus = PLAYBACK_SOUND_STATUS_CLOSE;
		}
		ChangeSoundBtnStatus();
	}
}

void CDlgRecPlaybackControl::ChangePlayBtnStatus()
{
	if (m_nPlayStatus == PLAYBACK_PLAY_STATUS_PLAYING)
	{
// 		m_btnPlay.SetStateImg(GetThemePath()+"playback_pause.jpg", GetThemePath()+"playback_pause_over.jpg");
		m_btnPlay.SetWindowText(LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_PAUSE));
// 		m_Tip.AddTool(&m_btnPlay, LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_PAUSE));
	}
	else if (m_nPlayStatus == PLAYBACK_PLAY_STATUS_PAUSE || m_nPlayStatus == PLAYBACK_PLAY_STATUS_STOP)
	{
// 		m_btnPlay.SetStateImg(GetThemePath()+"playback_play.jpg", GetThemePath()+"playback_play_over.jpg");
		m_btnPlay.SetWindowText(LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_PLAY));
// 		m_Tip.AddTool(&m_btnPlay, LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_PLAY));
	}
}
void CDlgRecPlaybackControl::ChangeSoundBtnStatus()
{
	if (m_nSoundStatus == PLAYBACK_SOUND_STATUS_CLOSE)
	{
// 		m_btnSound.SetStateImg(GetThemePath()+"playback_sound_close.jpg", GetThemePath()+"playback_sound_close_over.jpg");
		m_btnSound.SetWindowText(LOADSTRINGEX(ID_STR_DLG_VIEW_START_AUDIO));
// 		m_Tip.AddTool(&m_btnSound, LOADSTRINGEX(ID_STR_DLG_VIEW_START_AUDIO));
	}
	else if(m_nSoundStatus == PLAYBACK_SOUND_STATUS_OPEN)
	{
// 		m_btnSound.SetStateImg(GetThemePath()+"playback_sound_open.jpg", GetThemePath()+"playback_sound_open_over.jpg");
		m_btnSound.SetWindowText(LOADSTRINGEX(ID_STR_DLG_VIEW_STOP_AUDIO));
// 		m_Tip.AddTool(&m_btnSound, LOADSTRINGEX(ID_STR_DLG_VIEW_STOP_AUDIO));
	}
}
void CDlgRecPlaybackControl::ChangeIFramBtnStatus()
{
	if (m_bPlayIFrame)
	{
// 		m_btnIFrame.SetOverStatus(TRUE);
		m_btnIFrame.SetWindowText(LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_STOP_STEP));
// 		m_Tip.AddTool(&m_btnIFrame, LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_STOP_STEP));
	}
	else
	{
// 		m_btnIFrame.SetOverStatus(FALSE);
		m_btnIFrame.SetWindowText(LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_STEP));
// 		m_Tip.AddTool(&m_btnIFrame, LOADSTRINGEX(ID_STR_DLG_PLAY_BTN_STEP));
	}
}

void CDlgRecPlaybackControl::EnableCtrl()
{
	BOOL bEnable = TRUE;
	if (m_nPlayStatus == PLAYBACK_PLAY_STATUS_STOP)
	{
		bEnable = FALSE;
		m_sliderTime.SetPos(0);
//		m_sliderTime._SetPos(0);
	}

//	m_btnPlay.EnableWindow(bEnable);
	m_btnStop.EnableWindow(bEnable);
	m_btnCapture.EnableWindow(bEnable);
// 	m_btnIFrame.EnableWindow(bEnable);
	m_btnSound.EnableWindow(bEnable);
	m_sliderTime.EnableWindow(bEnable);
}

void CDlgRecPlaybackControl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_TIME)
	{
		  switch(nSBCode)  
		  {  
		  case SB_PAGELEFT:
		  case SB_PAGERIGHT:  
		  case SB_LEFT:
		  case SB_RIGHT:
		  case SB_LINELEFT:
		  case SB_LINERIGHT:
		  case SB_THUMBPOSITION:
		  case SB_THUMBTRACK:
			  m_bThumbTrack = TRUE;
			  break;
		  case SB_ENDSCROLL:
			  {
				  m_pPlayback->SetPlayProgress(m_sliderTime.GetPos());
				  m_bThumbTrack = FALSE;
			  }
			  break;
		  default:  
			  break;  
        }  
	}
}

void CDlgRecPlaybackControl::DoPlayFinished()
{
	KillTimer(EVENT_GET_PLAY_TIME);
	KillTimer(EVENT_GET_FLOW_RATE);
	KillTimer(EVENT_GET_DWON_TIME);
	m_pPlayback->StopPlay();
	m_nPlayStatus = PLAYBACK_PLAY_STATUS_STOP;
	m_sliderTime.SetPos(0);
//	m_sliderTime._SetPos(0);
	m_strPlayTime = "";
	InvalidateRect(m_rcPlayTime);
	ChangePlayBtnStatus();
	EnableCtrl();
}

void CDlgRecPlaybackControl::DoPlayFailed()
{
	KillTimer(EVENT_GET_PLAY_TIME);
	KillTimer(EVENT_GET_FLOW_RATE);
	KillTimer(EVENT_GET_DWON_TIME);
	m_pPlayback->StopPlay();
	m_nPlayStatus = PLAYBACK_PLAY_STATUS_STOP;
	ChangePlayBtnStatus();
	EnableCtrl();
}

void CDlgRecPlaybackControl::DoPlayDownFinished()
{
	KillTimer(EVENT_GET_FLOW_RATE);
	KillTimer(EVENT_GET_DWON_TIME);
	m_strDownSpeed = "";
	InvalidateRect(m_rcDownSpeed);
//	m_sliderTime._SetPos(PLAYBACK_SILDER_TIME_RANGE);
}

LRESULT CDlgRecPlaybackControl::OnPlaybackPlayMsg(WPARAM wParm, LPARAM lParam)
{
	switch(wParm)
	{
	case MSG_PALYBACK_FINISHED:
		DoPlayFinished();
		break;
	case MSG_PALYBACK_FAILED:
		DoPlayFailed();
		break;
	case MSG_PALYBACK_DOWN_FINISHED:
		DoPlayDownFinished();
		break;

	default:
		break;
	}

	return 0;
}


// LRESULT CDlgRecPlaybackControl::OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam)
// {
// 	switch( wParam ) 
// 	{
// 	case IDC_STATIC_VOLUME :
// 		ChangeVolume();
// 		break;
// 	}
// 	return 0;
// }
// 
// LRESULT CDlgRecPlaybackControl::OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam)
// {
// 	switch( wParam )
// 	{
// 	case IDC_STATIC_VOLUME :
// 		ChangeVolume();
// 		break;
// 	}
// 	
// 	return 0;
// }

void CDlgRecPlaybackControl::ChangeVolume()
{
	if (m_nPlayStatus != PLAYBACK_PLAY_STATUS_STOP)
	{
		m_pPlayback->SetVolume(m_sliderVol.GetPos());
	}
}

// void CDlgRecPlaybackControl::OnReleasedcaptureSliderTime(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	
// 	
// 	*pResult = 0;
// }


void CDlgRecPlaybackControl::AdjustedWndRect()
{
	if (m_pPlayback)
	{
		m_pPlayback->AdjustedWndRect();
	}
}
