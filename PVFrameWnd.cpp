// PVFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PVFrameWnd.h"
#include "DlgPaneView.h"
//#include "PVRealPlay.h"
#include "VDvsDevice.h"
//#include "VideoDataRecv.h"
#include "PVViewWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPVFrameWnd

CPVFrameWnd::CPVFrameWnd()
{
	m_pDlgPaneView = NULL;
	m_nIndex = 0;
//	m_pPVPlay = NULL;
//	m_pRealPlayer = NULL;

	m_bDivMode = FALSE;
	m_bPartMode = FALSE;
	m_nPlayMode = PV_MODE_NONE;
	m_nDivActIndex = 0;
	m_nViewSize = -1;

	m_strPollingGroupName = _T(""); 
	m_pMainView = NULL;
	m_lHandle = NULL;
	m_nDevID = 0;
	m_nChannel = -1;
	m_bMain = FALSE;
	m_lRecHandle = NULL;
	m_BegPos = m_EndPos = 0;
}

CPVFrameWnd::~CPVFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CPVFrameWnd, CWnd)
	//{{AFX_MSG_MAP(CPVFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()

	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_CHAN_REAL_FAILED, OnMsgChanRealFailed)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPVFrameWnd message handlers

int CPVFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
 	RECT rc = {0};
	m_pMainView = new CPVViewWnd;
	m_pMainView->Create(NULL, NULL, WS_VISIBLE|WS_CHILD, rc, this, 98);
	m_pMainView->SetPVFrameWnd(this);
	m_pMainView->GetVideoWnd().SetPVFrmWnd(this);
	m_pMainView->SetActive(FALSE);
	m_pMainView->GetVideoWnd().SetIndex(PV_MAIN_VIEW_ID);

// 	m_pRealPlayer = new CPVRealPlay;
// 	m_pRealPlayer->SetPVFrmWnd(this);
	return 0;
}
void CPVFrameWnd::Start()
{
	m_pMainView->Start();
}
void CPVFrameWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
//	m_pRealPlayer->StopPlay();
//	SAFE_DELETE_OBJECT(m_pRealPlayer);

	if (m_pMainView)
	{
		m_pMainView->DestroyWindow();
		SAFE_DELETE_OBJECT(m_pMainView);
	}
}

void CPVFrameWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
}

void CPVFrameWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	MoveCtrl();
}

void CPVFrameWnd::MoveCtrl()
{
	if (GetSafeHwnd() && m_pMainView->GetSafeHwnd())
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		RECT rcMove = rcClient;
		int i = 0;
		if (m_bDivMode)
		{
			int nPerWidth = rcClient.Width() / (PV_ROW_VIEW_NUM + 1);
			int nPerHeight = rcClient.Height() / (PV_ROW_VIEW_NUM + 1);
			int nLastWidth = rcClient.Width() - nPerWidth * PV_ROW_VIEW_NUM;
			int nLastHeight = rcClient.Height() - nPerHeight * PV_ROW_VIEW_NUM;

			rcMove.left = 0;
			rcMove.right = nPerWidth * PV_ROW_VIEW_NUM;
			rcMove.top = 0;
			rcMove.bottom = nPerHeight * PV_ROW_VIEW_NUM;
			m_pMainView->MoveWindow(&rcMove);

			if (m_bPartMode)
			{
				m_pMainView->ShowWindow(SW_HIDE);
			}
			else
			{
				m_pMainView->ShowWindow(SW_SHOW);
			}
		}
		else
		{
			rcMove = rcClient;
			m_pMainView->MoveWindow(&rcMove);
			m_pMainView->ShowWindow(SW_SHOW);
		}
	}
}

void CPVFrameWnd::SetActive(BOOL bActive)
{
	m_pMainView->SetActive(bActive);
}

void CPVFrameWnd::SetPartMode(BOOL bPart)
{
	m_bPartMode = bPart;
}


HWND CPVFrameWnd::GetPlayHwnd()
{
	return m_pMainView->GetVideoWnd().GetSafeHwnd();
}

void CPVFrameWnd::FlashPlayWnd()
{
// 	if (m_pPVPlay != NULL)
// 	{
// 		m_pPVPlay->FlashPlayWnd();
// 	}
}

void CPVFrameWnd::CloseSound()
{
// 	if (m_pPVPlay)
// 	{
// 		m_pPVPlay->CloseSound();
// 	}
}

void CPVFrameWnd::PlaySound()
{
// 	if (m_pPVPlay)
// 	{
// 		if (!m_pPVPlay->IsOpenSound())
// 		{
// 			MAIN_FRAME()->CloseAllSound();
// //			PANE_BCAST()->CloseBcastSound();
// 			if (PV_MODE_REAL == m_nPlayMode)
// 			{
// 				CVideoDataRecv::GetInstance()->PlayRealSound(m_pRealPlayer->GetDevID(), m_pRealPlayer->GetChannel(), 
// 									m_pRealPlayer->GetMainStream() ? NETMEDIA_REAL_TYPE_MAIN : NETMEDIA_REAL_TYPE_SUB);
// 			}
// 			m_pPVPlay->OpenSound(MAIN_FRAME()->GetSoundVolume());
// 		}
// 	}
}


void CPVFrameWnd::SnapDev()
{
	OnMenuPreviewSnapDev();
}

void CPVFrameWnd::Snapshot()
{
	OnMenuPreviewCapture();
}

void CPVFrameWnd::OnDIVLBtnDown(int nDivIndex)
{
	if (!m_bDivMode)
	{
		ASSERT(PV_MAIN_VIEW_ID == nDivIndex);
		m_pDlgPaneView->ViewActive(m_nIndex);
		m_nDivActIndex = 0;
	}
	else
	{
		if (PV_MAIN_VIEW_ID == nDivIndex)
		{
			m_pMainView->SetActive(TRUE);
		}
		else if (PV_PART_VIEW_ID == nDivIndex)
		{	
			m_pMainView->SetActive(FALSE);
		}
		else
		{
			m_pMainView->SetActive(FALSE);
		}
		m_nDivActIndex = nDivIndex;
	}
}

void CPVFrameWnd::OnDIVLBDblClk(int nDivIndex)
{
	if (!m_bDivMode)
	{
		ASSERT(PV_MAIN_VIEW_ID == nDivIndex);
		m_pDlgPaneView->ViewActive(m_nIndex);
		m_pDlgPaneView->ShowOneMax();
	}
}



void CPVFrameWnd::SetPVModeNone()
{
//	m_pPVPlay = NULL;
	m_nPlayMode = PV_MODE_NONE;
}

void CPVFrameWnd::SetPVModeReal()
{
//	m_pPVPlay = m_pRealPlayer;
	m_nPlayMode = PV_MODE_REAL;
}

void CPVFrameWnd::SetPVModeVod()
{
//	m_pPVPlay = NULL;
	m_nPlayMode = PV_MODE_VOD;
}

void CPVFrameWnd::OnMenuPreviewAudio() 
{
	// TODO: Add your command handler code here
	PlaySound();
}

void CPVFrameWnd::OnMenuPreviewStopAudio() 
{
	// TODO: Add your command handler code here
	CloseSound();
}

void CPVFrameWnd::OnMenuPreviewDevSetup() 
{
	// TODO: Add your command handler code here
	int nDevID = 0;
	int nChn = 0;
// 	if (m_pPVPlay && m_pPVPlay->GetPlayDev(nDevID, nChn))
// 	{
// 	//	MAIN_FRAME()->DoDeviceConfig(nDevID);
// 	}
}

void CPVFrameWnd::OnMenuPreviewSnapDev() 
{
// 	if (m_pPVPlay)
// 	{
// 		if (!IsPlayerMode())
// 		{
// 			int nDevID = 0;
// 			int nChn = 0;
// 			if (m_pPVPlay->GetPlayDev(nDevID, nChn))
// 			{
// 		//		MAIN_FRAME()->DoSnapshot(nDevID, nChn);
// 			}
// 		}	
// 	}
}

void CPVFrameWnd::OnMenuPreviewCapture() 
{
	// TODO: Add your command handler code here
// 	if (m_pPVPlay)
// 	{
// 		char   szTmpPath[MAX_PATH],szFilename[MAX_PATH] ;
// 		::GetTempPath (MAX_PATH, szTmpPath) ;
// 		::GetTempFileName (szTmpPath, TEXT("gViewerbmp"), 0, szFilename) ;
// 		if (m_pPVPlay->CaptureBmp(szFilename))
// 		{
// 			int nDevID = 0;
// 			int nChn = 0;
// 			if (m_pPVPlay->GetPlayDev(nDevID, nChn))
// 			{
// 				SYSTEMTIME tmNow;
// 				GetLocalTime(&tmNow);
// // 				CDlgSnapshot dlg;
// // 				dlg.SetBMPFile(szFilename, tmNow);
// // 				dlg.SetDevID(nDevID, nChn);
// // 				dlg.DoModal();
// 
// 			}
// 		}
// 	}
}


void CPVFrameWnd::StopChannelView()
{
	if (PV_MODE_REAL == m_nPlayMode)
	{
//		m_pRealPlayer->StopVideo();
		NETMEDIA_StopRealPlay(m_lHandle);
		NETMEDIA_CloseRealPlay(m_lHandle);
		m_lHandle = NULL;
	}

	if (m_lRecHandle)
	{
		AVDEC_CloseWriter(m_lRecHandle);
		m_lRecHandle = NULL;
	}

	ExitPlayMode();	
}

void CPVFrameWnd::OnMenuPreviewView() 
{
	// TODO: Add your command handler code here
	CWaitCursor wait;
	if (PV_MODE_REAL == m_nPlayMode)
	{
	//	m_pRealPlayer->StopVideo();
		NETMEDIA_StopRealPlay(m_lHandle);
	}
	if (m_lRecHandle)
	{
		AVDEC_CloseWriter(m_lRecHandle);
		m_lRecHandle = NULL;
	}
	ExitPlayMode();
}


BOOL CPVFrameWnd::GetSoundStatus()
{
// 	if (m_pPVPlay)
// 	{
// 		return m_pPVPlay->IsOpenSound();
// 	}
// 	else
	{
		return FALSE;
	}
}

BOOL CPVFrameWnd::PlayValid()
{
// 	if (m_pPVPlay /*&& m_pPVPlay->GetVideoWidth() && m_pPVPlay->GetVideoHeight()*/)
// 	{
// 		return TRUE;
// 	}
// 	else
	{
		return FALSE;
	}
}



void CPVFrameWnd::SetDrawRect(RECT& rcRegion, RECT& rcClient)
{
// 	if (m_pPVPlay)
// 	{
// 		m_pPVPlay->SetDrawRect(rcRegion, rcClient);
// 	}
}

void CPVFrameWnd::SetDrawEmpty()
{
// 	if (m_pPVPlay)
// 	{
// 		m_pPVPlay->SetDrawEmpty();
// 	}
}

void CPVFrameWnd::SetDrawFocus(BOOL bFocus)
{
// 	if (m_pPVPlay)
// 	{
// 		m_pPVPlay->SetDrawFocus(bFocus);
// 	}
}

BOOL CPVFrameWnd::IsPreviewing()
{
	return PV_MODE_NONE == m_nPlayMode ? FALSE : TRUE;
}

BOOL CPVFrameWnd::PlayRemoteFile(GPSFile_S *pFile)
{
	if (PV_MODE_NONE == m_nPlayMode)
	{
	}
	
	return FALSE;
}

BOOL CPVFrameWnd::IsPlayRemoteFile(GPSFile_S *pFile)
{
	return FALSE;
}

BOOL CPVFrameWnd::IsDevChnPreviewing(int nDevID, int nChn, BOOL bMain)
{
	if (PV_MODE_REAL == m_nPlayMode)
	{
		if (m_nDevID == nDevID 
			&& m_nChannel == nChn
			&& m_bMain == bMain)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CPVFrameWnd::IsDevChnPicture(int nDevID, int nChn)
{
	if (PV_MODE_PICTURE == m_nPlayMode)
	{
// 		if(m_pRealPicture->GetDevID() == nDevID && m_pRealPicture->IsPlaying())
// 		{
// 			return TRUE;
// 		}
	}

	return FALSE;
}

void CPVFrameWnd::OnMenuPreviewUp() 
{
	// TODO: Add your command handler code here
	GetPaneView()->SetWndMove(TRUE);
}

void CPVFrameWnd::OnMenuPreviewDown() 
{
	// TODO: Add your command handler code here
	GetPaneView()->SetWndMove(FALSE);
}

void CPVFrameWnd::UpdatePreview()
{
	if (PV_MODE_REAL == m_nPlayMode)
	{
		int nDevID = 0;
		int nChn = 0;
// 		m_pRealPlayer->GetPlayDev(nDevID, nChn);
// 		if ( NULL == CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID) )
// 		{
// 			m_pRealPlayer->StopVideo();
// 			ExitPlayMode();
// 		}
	}
}

CPVPlay* CPVFrameWnd::GetPVPlayPlayer()
{
	return NULL;
}

BOOL CPVFrameWnd::IsOpenSound()
{
	if (PV_MODE_REAL == m_nPlayMode)
	{
//		return m_pRealPlayer->IsOpenSound();
	}
	return FALSE;
}

void CPVFrameWnd::ExitPlayMode()
{
	SetPVModeNone();
	Invalidate();
}

void CPVFrameWnd::PreviewRealVideo(int nDevID, int nChn, BOOL bMainStream, int nPlayMode/*=PV_MODE_REAL*/)
{
	if (PV_MODE_NONE == m_nPlayMode)
	{
		if (PV_MODE_REAL == nPlayMode)
		{
			SetPVModeReal();
			CString strDevIDNO;
			if (m_lHandle == NULL)
			{
				CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);
				strDevIDNO = pDev->GetDevIDNO();
				NETMEDIA_OpenRealPlay(CStringA(strDevIDNO), nChn, NETMEDIA_REAL_TYPE_SUB, 0, TRUE, &m_lHandle);
				m_nDevID = nDevID;
				m_nChannel = nChn;
				m_bMain = bMainStream;

				if (g_bPreviewAutoRecord)
				{
					SYSTEMTIME stTime;
					GetLocalTime(&stTime);

					CString strPath;
					strPath.Format(_T("%sRECORD_FILE\\%s\\%04d-%02d-%02d\\"),
						PATHGetAppPath(), strDevIDNO, stTime.wYear, stTime.wMonth, stTime.wDay);
					PATHCreateDirectory(strPath);

					char szFileName[MAX_PATH] = {0};
					AVDEC_MakeRecName(NULL, &stTime, &stTime, m_nChannel, 0, szFileName);

					char szFullPath[MAX_PATH] = {0};
					sprintf(szFullPath, "%s%s", CStringA(strPath), szFileName);
					AVDEC_OpenWriter(NULL, &m_lRecHandle, szFullPath);
					m_BegPos = m_EndPos = 0;
				}
			}
			NETMEDIA_SetRealDataCallBack(m_lHandle, this, FUNRealDataCB);
			NETMEDIA_SetRealDecCallBack(m_lHandle, this, FUNRealDecCB);
			NETMEDIA_StartRealPlay(m_lHandle, GetPlayHwnd());
			NETMEDIA_SetStreamMode(m_lHandle, AVDEC_STREAM_MODE_REAL);
			NETMEDIA_PlaySound(m_lHandle, 1);
//			m_nPlayMode = PV_MODE_REAL;
// 			if (m_pRealPlayer->PreviewVideo(nDevID, nChn, bMainStream))
// 			{
// 				SetPVModeReal();
// 			//	if (MAIN_FRAME()->IsOpenSound())
// 				{
// 					PlaySound();
// 				}
// 			}

		}
	}
}

void CPVFrameWnd::FUNRealDataCB(const char* pFrameBuf , int nFrameLen, int nFrameType, unsigned __int64 llFrameStamp, void* pUsr)
{
	CPVFrameWnd* pThis = (CPVFrameWnd*)pUsr;
	DEBUGTraceOutput(_T("FUNRealDataCB %I64d, %08X,%d"), llFrameStamp, nFrameType, nFrameLen);

	long lRecHandle = pThis->m_lRecHandle;
	if (lRecHandle)
	{
		if (nFrameType == 1)
		{
			AVDEC_SetFileHead(lRecHandle, (char*)pFrameBuf, nFrameLen);
		}
		else
		{
			AVDEC_WriteFrame(lRecHandle, pFrameBuf, nFrameLen, nFrameType, llFrameStamp,
				&pThis->m_BegPos, &pThis->m_EndPos);
		}
	}
}

void CPVFrameWnd::FUNRealDecCB(unsigned char* pY, int nYStride, unsigned char* pU, unsigned char* pV, int nUVStride, 
	int nWidth, int nHeight, unsigned __int64 nStamp, int nType, void* pUsr)
{
	DEBUGTraceOutput(_T("FUNRealDecCB %I64d, %08X,%d"), nStamp, nType, nUVStride);
}
void CPVFrameWnd::PreviewDefaultAV()
{
	if (PV_MODE_NONE == m_nPlayMode)
	{
// 		if (m_pRealPlayer->PreviewDefault())
// 		{
// 			SetPVModeReal();
// 		//	if (MAIN_FRAME()->IsOpenSound())
// 			{
// 				PlaySound();
// 			}
// 		}
	}
}

void CPVFrameWnd::GetDefaultAV(int& nDevID, int& nChn)
{
	nDevID = m_nDevID;
	nChn = m_nChannel;
// 	if (m_pRealPlayer)
// 	{
// 		nChn = m_pRealPlayer->GetChannel();
// 	    nDevID = m_pRealPlayer->GetDevID();
// 	}	
}

void CPVFrameWnd::StopPreview()
{
	OnMenuPreviewView();
}

BOOL CPVFrameWnd::EnablePreview()
{
//	return m_pRealPlayer->EnablePreview();
	return FALSE;
}

BOOL CPVFrameWnd::IsPlayerMode()
{
	if (PV_MODE_VOD == m_nPlayMode)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CPVFrameWnd::IsPictureMode()
{
	return m_nPlayMode == PV_MODE_PICTURE ? TRUE : FALSE;
}

void CPVFrameWnd::DoCommandSnapshot()
{
// 	if (m_pPVPlay)
// 	{
// 		if (IsPlayerMode())
// 		{
// 			SYSTEMTIME sysTime;
// 			GetLocalTime(&sysTime);
// 			CString strFile;
// 			strFile.Format(_T("%04d-%02d-%02d %02d-%02d-%02d_%d")
// 				, sysTime.wYear, sysTime.wMonth, sysTime.wDay
// 				, sysTime.wHour, sysTime.wMinute, sysTime.wSecond
// 				, sysTime.wMilliseconds);
// 			CFileDialog SaveDialog(FALSE, _T("*.bmp"), strFile
// 				, OFN_NOCHANGEDIR|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
// 				, _T("BMP File(*.bmp)|*.bmp||"));
// 			if (IDOK == SaveDialog.DoModal())
// 			{
// 				m_pPVPlay->CaptureBmp(SaveDialog.GetPathName());		
// 			}
// 		}
// 		else
// 		{
// 			int nDevID = 0;
// 			int nChn = 0;
// 			if (m_pPVPlay->GetPlayDev(nDevID, nChn))
// 			{
// 		//		MAIN_FRAME()->DoSnapshot(nDevID, nChn);
// 			}
// 		}	
// 	}
}

void CPVFrameWnd::ChangeVolume(WORD wVolume)
{
// 	if (m_pPVPlay)
// 	{
// 		m_pPVPlay->ChangeVolume(wVolume);
// 	}
}

int	CPVFrameWnd::GetViewSize()
{
// 	if (VIEW_SIZE_UNDEFINE == m_nViewSize)
// 	{
// 		return CConfigGViewerINI::GetInstance()->GetViewSize();
// 	}
// 	else
	{
		return m_nViewSize;
	}
}

void CPVFrameWnd::SetViewSize(int nViewSize)
{
	m_nViewSize = nViewSize;
	m_pMainView->MoveWnd();
}

void CPVFrameWnd::SetViewMode(int nViewMode)
{
//	m_pRealPlayer->SetViewMode(nViewMode);
}

void CPVFrameWnd::SetDelayTime()
{
//	m_pRealPlayer->SetPlayDelayTime();
}

void CPVFrameWnd::OnMenuStartVideorecord() 
{
	// TODO: Add your command handler code here
// 	if (PV_MODE_REAL == m_nPlayMode)
// 	{
// 		if (CVideoRecord::GetInstance()->GetVidoRecordSize() >= VIDEORECORD_MAX_NUM)
// 		{
// 			CString str;
// 			str.Format(LOADSTRINGEX(ID_STR_DLG_VIDEO_MAX_NUM_TIP), VIDEORECORD_MAX_NUM);
// 			AfxMessageBox(str);
// 			return;
// 		}
// 		else
// 		{	
// 			CVideoRecord::GetInstance()->StartVideoRecord(m_pRealPlayer->GetDevID(), m_pRealPlayer->GetChannel(), m_pRealPlayer->GetMainStream());
// 		}
// 	}
}

void CPVFrameWnd::OnMenuStopVideorecord() 
{
	// TODO: Add your command handler code here
// 	if (PV_MODE_REAL == m_nPlayMode)
// 	{
// 		CVideoRecord::GetInstance()->StopVideoRecord(m_pRealPlayer->GetDevID(), m_pRealPlayer->GetChannel(), m_pRealPlayer->GetMainStream());
// 		CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByID(m_pRealPlayer->GetDevID());
// 		if (pDevice && PANE_DEVICE()->GetSafeHwnd())
// 		{
// 			PANE_DEVICE()->DoDeviceStatusChange(pDevice, FALSE, FALSE);
// 		}
// 	}
}

void CPVFrameWnd::AdjustedWndRect()
{
// 	if (NULL != m_pPVPlay)
// 	{
// 		m_pPVPlay->AdjustedWndRect();
// 	}
}

LRESULT CPVFrameWnd::OnMsgChanRealFailed(WPARAM wPram, LPARAM lParam)
{
// 	int nParam = (int)lParam;
// 	int nDevID = m_pRealPlayer->GetDevID();
// 	int nChan = m_pRealPlayer->GetChannel();
// 	CString strTip = (NETMEDIA_REAL_MSG_USR_NORIGHT == lParam) ? LOADSTRINGEX(ID_STR_DLG_VIEW_REQ_USR_NORIGHT) : LOADSTRINGEX(ID_STR_DLG_VIEW_REQ_USR_ERROR) ;
// 	CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);
// 	if (pDevice)
// 	{
// 		EventInfo_S* pEvent = gEventPool.Alloc();
// 		pEvent->Alarm = TRUE;
// 		pEvent->EventType = EVENT_TYPE_INFO;
// 		pEvent->Desc.Format("%s(%s):%s", pDevice->GetShowName(), pDevice->GetChnName(nChan), strTip) ;
// 		GetLocalTime(&(pEvent->Time));
// 		if (NULL != PANE_EVENT() && PANE_EVENT()->GetSafeHwnd())
// 		{
// 			PANE_EVENT()->PostMessage(WM_MSG_SHOW_EVENT, (WPARAM)pEvent, 0);
// 		}
// 		if (NULL != MAIN_FRAME() && MAIN_FRAME()->GetSafeHwnd())
// 		{
// 			MAIN_FRAME()->ShowPopup(pEvent->Desc, LOADSTRINGEX(ID_STR_EVENT_TYPE_INFO));
// 		}
// 	}
	StopPreview();

	return 0;
}

void CPVFrameWnd::GetFlowRate(int* lpFlowRate)
{
	if (PV_MODE_REAL == m_nPlayMode)
	{
//		m_pRealPlayer->GetFlowRate(lpFlowRate);
	}
	else
	{
		*lpFlowRate = 0;
	}
}

void CPVFrameWnd::CheckCloseVideo(DWORD dwTime)
{
	if (IsPreviewing())			
	{
		if (PV_MODE_POLLING != m_nPlayMode)
		{
// 			if (m_pRealPlayer)
// 			{
// 				DWORD DwVideoViewingTime = m_pRealPlayer->GetVideoTime();
// //				DEBUGTraceOutput("GetVideoTime %d, %d", DwVideoViewingTime, dwTime);
// //				if (dwTime > 0 && TIMEIsTimeOut(DwVideoViewingTime,dwTime))
// 				{
// 					StopPreview();
// 				}
// 			}
		}
	}
}


BOOL CPVFrameWnd::GetActive()
{	
	if (m_pMainView)
	{
		return m_pMainView->GetActive();
	}
	return FALSE;
}

CString	CPVFrameWnd::GetPlayTip()
{
	return "";
}

BOOL CPVFrameWnd::IsRecord()
{
	BOOL bRet = FALSE;
// 	if (m_pRealPlayer)
// 	{
// 		bRet = m_pRealPlayer->IsRecord();
// 	}
	return bRet;
}
BOOL CPVFrameWnd::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( (WM_KEYDOWN == pMsg->message) && (VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		return FALSE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CPVFrameWnd::IsModeWnd64()
{
	BOOL bRet = FALSE;
	if (m_pDlgPaneView && WND_MODE_64 == m_pDlgPaneView->GetWndMode())
		bRet = TRUE;

	return bRet;
}

void CPVFrameWnd::DoAlarmSnapshotFinish(CDevBase* pDevice, GPSVehicleAlarm_S* pVehiAlarm)
{
//	if (m_pRealPicture->IsPlaying() && pDevice->GetID() == m_pRealPicture->GetDevID())
	{
		GPSFile_S File = {0};
		GPSFile_S *pFile = &File;
		strncpy(pFile->szDevIDNO, pVehiAlarm->szDevIDNO, sizeof(pFile->szDevIDNO) - 1);
		//szImgFile
		strncpy(pFile->szFile, pVehiAlarm->Alarm.szImgFile, sizeof(pFile->szFile) - 1);
		//AlarmType  GPS_ALARM_TYPE_SNAPSHOT_FINISH
//		pVehiAlarm->Alarm.AlarmType = GPS_ALARM_TYPE_SNAPSHOT_FINISH;
		//param[0]  nChn 
		pFile->nChn = pVehiAlarm->Alarm.Param[0];
		//param[1]  nFileLen
		pFile->nFileLen = pVehiAlarm->Alarm.Param[1];
		//param[2]  nFileType 
		pFile->nFileType = pVehiAlarm->Alarm.Param[2];
		//param[3]  nLocation
		pFile->nLocation = pVehiAlarm->Alarm.Param[3];
		//AlarmInfo nSvrID
		pFile->nSvrID = pVehiAlarm->Alarm.AlarmInfo;
//		m_pRealPicture->NotifyNewPicture(pFile);
	}
}

