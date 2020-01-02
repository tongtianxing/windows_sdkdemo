// DlgPaneView.cpp : implementation file
//

#include "stdafx.h"
#include "DlgPaneView.h"
#include "VDvsDevice.h"
#include "PVFrameWnd.h"
//#include "PVRealPlay.h"
//#include "DlgPanePreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_IDEVENT_CLOSEVIDEO 0x0001 
#define WM_MSG_PTZ_CTRL		WM_USER + 0x1000
/////////////////////////////////////////////////////////////////////////////
// CDlgPaneView dialog

CDlgPaneView::CDlgPaneView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPaneView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaneView)
	//}}AFX_DATA_INIT
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		m_pViewWnd[i] = NULL;
//		m_ViewTime[i] = CTime::GetCurrentTime();
	}

	m_nWndMode = WND_MODE_9;
	m_nActiveIndex = -1;
	m_nVideoIndex = 0;
	m_bShowOneMax = FALSE;
	m_bShowVertical = FALSE;
	m_nAlarmIndexOld = 0;
	m_nExCelIndex = 0;
}


void CDlgPaneView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaneView)
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_WND_9, m_btnViewWnd9);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_WND_8, m_btnViewWnd8);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_WND_6, m_btnViewWnd6);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_WND_4, m_btnViewWnd4);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_WND_16, m_btnViewWnd16);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_WND_1, m_btnViewWnd1);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_WND_64, m_btnViewWnd64);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_WND_36, m_btnViewWnd36);
// 	
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_UP, m_btnViewUp);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_SIZE_PROMPT, m_btnViewSizePrompt);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_MODE, m_btnViewMode);
// 	DDX_Control(pDX, IDC_BUTTON_VIEW_DOWN, m_btnViewDown);
// 	DDX_Control(pDX, IDC_BUTTON_TALKBACK, m_btnTalkback);
// 	DDX_Control(pDX, IDC_BUTTON_SOUND, m_btnSound);
// 	DDX_Control(pDX, IDC_BUTTON_CAPTURE, m_btnCapture);
// 	DDX_Control(pDX, IDC_BUTTON_AV_STOP, m_btnAVStop);
// 	DDX_Control(pDX, IDC_BUTTON_AV_START, m_btnAVStart);
// 	DDX_Control(pDX, IDC_BUTTON_START_DROP, m_btnAVStartDrop);
// 	DDX_Control(pDX, IDC_BUTTON_STOP_DROP, m_btnAVStopDrop);
// 	DDX_Control(pDX, IDC_BUTTON_CAPTURE_DROP, m_btnCaptureDrop);
// 	DDX_Control(pDX, IDC_BUTTON_SCREEN, m_btnScreen);
	
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaneView, CDialog)
	//{{AFX_MSG_MAP(CDlgPaneView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_MESSAGE(WM_MSG_PTZ_CTRL, OnPtzMsg)

// 	ON_COMMAND(ID_MENU_VIEW_SIZE_4_3, OnMenuViewSize43)
// 	ON_COMMAND(ID_MENU_VIEW_SIZE_16_9, OnMenuViewSize169)
// 	ON_COMMAND(ID_MENU_VIEW_SIZE_FULL, OnMenuViewSizeFull)
// 
// 	ON_COMMAND(ID_MENU_VIEW_MODE_SMOOTH, OnMenuViewModeSmooth)
// 	ON_COMMAND(ID_MENU_VIEW_MODE_REAL, OnMenuViewModeReal)
// 
// 	ON_COMMAND(ID_MENU_VIEW_AUDIO_COM, OnMenuViewAudioCom)
// 
// 	ON_COMMAND(ID_MENU_PREVIEW_WND_1, OnMenuView1)
// 	ON_COMMAND(ID_MENU_PREVIEW_WND_4, OnMenuView4)
// 	ON_COMMAND(ID_MENU_PREVIEW_WND_9, OnMenuView9)
// 	ON_COMMAND(ID_MENU_PREVIEW_WND_16, OnMenuView16)
// 	ON_COMMAND(ID_MENU_PREVIEW_WND_6, OnMenuPreviewWnd6)
// 	ON_COMMAND(ID_MENU_PREVIEW_WND_8, OnMenuPreviewWnd8)
// 
// 	ON_COMMAND(ID_MENU_VIEW_WND, OnMenuViewWnd)
// 
// 	ON_COMMAND(ID_MENU_VIEW_DOWN, OnMenuViewDown)
// 	ON_COMMAND(ID_MENU_VIEW_UP, OnMenuViewUp)
// 
// 	ON_COMMAND(ID_MENU_PREVIEW_CAPTURE, OnMenuPreviewCapture)
// 	ON_COMMAND(ID_MENU_VIEW_SNAP_DEV, OnMenuPreviewSnapDev)
// 
// 
// 	ON_COMMAND(ID_MENU_AV_START, OnMenuViewAvStart)
// 	ON_COMMAND(ID_MENU_AV_STOP, OnMenuViewAvStop)
// 
// 	ON_COMMAND(ID_MENU_VIEW_AV_START, OnMenuViewAvStart)
// 	ON_COMMAND(ID_MENU_VIEW_AV_STOP, OnMenuViewAvStop)
// 	ON_COMMAND(ID_MENU_VIEW_AV_START_ALL, OnMenuViewAvStartAll)
// 	ON_COMMAND(ID_MENU_VIEW_AV_STOP_ALL, OnMenuViewAvStopAll)
// 
// 	ON_COMMAND(ID_MENU_VIEW_AV_CLEAR, OnMenuViewAvClear)
// 	ON_COMMAND(ID_MENU_VIEW_AV_CLEAR_ALL, OnMenuViewAvClearAll)
// 
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_WND_1, OnButtonViewWnd1)
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_WND_4, OnButtonViewWnd4)
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_WND_6, OnButtonViewWnd6)
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_WND_8, OnButtonViewWnd8)
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_WND_9, OnButtonViewWnd9)
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_WND_16, OnButtonViewWnd16)
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_WND_64, OnButtonViewWnd64)
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_WND_36, OnButtonViewWnd36)
// 
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_UP, OnButtonViewUp)
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_DOWN, OnButtonViewDown)
// 	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, OnButtonCapture)
// 	ON_BN_CLICKED(IDC_BUTTON_SOUND, OnButtonSound)
// 	ON_BN_CLICKED(IDC_BUTTON_TALKBACK, OnButtonTalkback)
// 	ON_BN_CLICKED(IDC_BUTTON_AV_START, OnButtonAvStart)
// 	ON_BN_CLICKED(IDC_BUTTON_AV_STOP, OnButtonAvStop)
// 	ON_BN_CLICKED(IDC_BUTTON_SCREEN, OnButtonFullScreen)
	
	//}}AFX_MSG_MAP
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_SIZE_PROMPT, OnButtonSizePromptDropDown)
// 	ON_BN_CLICKED(IDC_BUTTON_VIEW_MODE, OnButtonViewModeDropDown)
// 
// 	ON_BN_CLICKED(IDC_BUTTON_CAPTURE_DROP, OnButtonCaptureModeDropDown)
// 	ON_BN_CLICKED(IDC_BUTTON_START_DROP, OnButtonAVStartDropDown)
// 	ON_BN_CLICKED(IDC_BUTTON_STOP_DROP, OnButtonAVStopDropDown)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaneView message handlers
BOOL CDlgPaneView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	int i = 0;
	RECT rc;
	CString str;
	for (i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		str.Format(_T("%d"), i + 1);
		m_pViewWnd[i] = new CPVFrameWnd;
		m_pViewWnd[i]->SetPaneView(this);
		m_pViewWnd[i]->SetIndex(i);
		m_pViewWnd[i]->Create(NULL, NULL, WS_CHILD|WS_VISIBLE, rc, this, 100 + i);
		m_pViewWnd[i]->ShowWindow(SW_HIDE);
	}

	SetTimer(TIMER_IDEVENT_CLOSEVIDEO,2000,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgPaneView::Start()
{
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		m_pViewWnd[i]->Start();

		MoveCtrl();
	}
}
void CDlgPaneView::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	MoveCtrl();
}

void CDlgPaneView::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	KillTimer(TIMER_IDEVENT_CLOSEVIDEO);
	int i = 0;
	for (i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		if (m_pViewWnd[i])
		{
			m_pViewWnd[i]->DestroyWindow();
			SAFE_DELETE_OBJECT(m_pViewWnd[i]);
		}
	}
}

BOOL CDlgPaneView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( (WM_KEYDOWN == pMsg->message) && (VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		return FALSE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgPaneView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
// 	CRect rcClient, rc;
// 	GetClientRect(&rcClient);
//	CUIManager::GetInstance()->DrawDlgPaneView(dc.GetSafeHdc(), rcClient, IsAlarmView());
	// Do not call CDialog::OnPaint() for painting messages
}

const int VIDEO_INTERVAL = 8;

void CDlgPaneView::MoveCtrl()
{
	if (NULL == m_pViewWnd[0] || !m_pViewWnd[0]->GetSafeHwnd())
	{
		return ;
	}
	
	CRect rc;
	GetClientRect(&rc);
	InflateRect(&rc, -1, -1);

	int nTop = rc.top;

	RECT rcMove;
	rc.top = nTop;
	
	int i = 0;
	int j = 0;
// 	if (m_bShowVertical)
// 	{
// 		int nTop = rc.top;
// 		int nBottom = rc.bottom;
// 		int nPerHeight = (nBottom - nTop) / WND_ROW_NUM;
// 		for(i = WND_ROW_NUM; i < VIEW_MAX_NUM; ++ i)
// 		{
// 			int nWndIndex = (m_nVideoIndex + i) % VIEW_MAX_NUM;
// 			m_pViewWnd[nWndIndex]->ShowWindow(SW_HIDE);
// 		}
// 		
// 		for(i = 0; i < WND_ROW_NUM; ++ i)
// 		{
// 			rcMove.left = rc.left;
// 			rcMove.right = rc.right;
// 			rcMove.top = nTop;
// 			if (WND_ROW_NUM == (i + 1))
// 			{
// 				rcMove.bottom = nBottom;
// 			}
// 			else
// 			{
// 				rcMove.bottom = nTop + nPerHeight;
// 			}
// 
// 			nTop += nPerHeight;
// 
// 			int nWndIndex = (m_nVideoIndex + i) % VIEW_MAX_NUM;
// 			m_pViewWnd[nWndIndex]->MoveWindow(&rcMove);
// 			m_pViewWnd[nWndIndex]->ShowWindow(SW_SHOW);
// 		}
// 	}
// 	else
	{
		if (m_bShowOneMax)
		{
			for (i = 0; i < VIEW_MAX_NUM; ++i)
			{
				if (i != m_nActiveIndex)
				{
					m_pViewWnd[i]->ShowWindow(SW_HIDE);
				}
			}
			rcMove = rc;
			rcMove.bottom = rc.bottom - 1;
			m_pViewWnd[m_nActiveIndex]->ShowWindow(SW_SHOW);
			m_pViewWnd[m_nActiveIndex]->MoveWindow(&rcMove);
			m_pViewWnd[m_nActiveIndex]->Invalidate();
		}
		else
		{
			int nWndMode = m_nWndMode;
			int nShowNum = 0;
			if (WND_MODE_1 == m_nWndMode || WND_MODE_4 == m_nWndMode
				|| WND_MODE_9 == m_nWndMode || WND_MODE_16 == m_nWndMode
				|| WND_MODE_36 == m_nWndMode || WND_MODE_64 == m_nWndMode)
			{
				ShowVideoWnd(nWndMode * nWndMode);
				MoveNormal(rc, nWndMode);
			}
			else if (WND_MODE_6 == m_nWndMode)
			{
				ShowVideoWnd(6);
				MoveExtra(rc, 3);
			}
			else if (WND_MODE_8 == m_nWndMode)
			{
				ShowVideoWnd(8);
				MoveExtra(rc, 4);
			}
			else 
			{
				ASSERT(FALSE);
			}
		}
	}
}

void CDlgPaneView::ShowVideoWnd(int nShowNum)
{
	int i = 0;
	int nEndIndex = m_nVideoIndex + nShowNum;
	if (nEndIndex >= VIEW_MAX_NUM)
	{
		for (i = nEndIndex - VIEW_MAX_NUM; i < m_nVideoIndex; ++i)
		{
			m_pViewWnd[i]->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		for (i = 0; i < m_nVideoIndex; ++i)
		{
			m_pViewWnd[i]->ShowWindow(SW_HIDE);
		}
		for (i = nEndIndex; i < VIEW_MAX_NUM; ++i)
		{
			m_pViewWnd[i]->ShowWindow(SW_HIDE);
		}
	}
}

void CDlgPaneView::MoveNormal(RECT rc, int nWndMode)
{
	int i = 0;
	int j = 0;
	RECT rcMove;
	int iPerWidth = (rc.right - rc.left) / nWndMode;
	int iPerHeigth = (rc.bottom - rc.top) / nWndMode;
	
	if (iPerWidth != 0 && iPerHeigth != 0)
	{
		for (i = 0; i < nWndMode; ++i)
		{
			for ( j = 0; j < nWndMode; ++j)
			{
				if (j == 0)
				{
					rcMove.left = rc.left + iPerWidth *j + VIDEO_INTERVAL;
				}
				else
				{
					rcMove.left = rc.left + iPerWidth *j + VIDEO_INTERVAL/2;
				}
				if (j == nWndMode -1)
				{
					rcMove.right = rc.left + iPerWidth*(j+1) - VIDEO_INTERVAL;
				}
				else
				{
					rcMove.right = rc.left + iPerWidth*(j+1) - VIDEO_INTERVAL/2;
				}
				if (i == 0)
				{
					rcMove.top = rc.top + iPerHeigth *i + VIDEO_INTERVAL;
				}
				else
				{
					rcMove.top = rc.top + iPerHeigth *i + VIDEO_INTERVAL/2;
				}
				if (i == nWndMode-1)
				{
					rcMove.bottom = rc.top + iPerHeigth*(i+1) - VIDEO_INTERVAL;
				}
				else
				{
					rcMove.bottom = rc.top + iPerHeigth*(i+1) - VIDEO_INTERVAL/2;
				}

				int nTemp = i*m_nWndMode + j + m_nVideoIndex;
				if (nTemp >= VIEW_MAX_NUM)
				{
					nTemp = nTemp - VIEW_MAX_NUM;
				}
				m_pViewWnd[nTemp]->MoveWindow(&rcMove);
				m_pViewWnd[nTemp]->ShowWindow(SW_SHOW);
				m_pViewWnd[nTemp]->Invalidate();
			}
		}
	}
}

void CDlgPaneView::MoveVideoWnd(int nIndex, RECT rcMove)
{
	if (nIndex >= VIEW_MAX_NUM)
	{
		nIndex = nIndex - VIEW_MAX_NUM;
	}
	
	m_pViewWnd[nIndex]->MoveWindow(&rcMove);
	m_pViewWnd[nIndex]->ShowWindow(SW_SHOW);
	m_pViewWnd[nIndex]->Invalidate();
}

void CDlgPaneView::MoveExtra(RECT rc, int nDiv)
{
	int iPerWidth = (rc.right - rc.left) / nDiv;
	int iPerHeigth = (rc.bottom - rc.top) / nDiv;
	int i = 0;
	RECT rcMove;
	
	//first
	rcMove.left = rc.left + VIDEO_INTERVAL;
	rcMove.right = rc.left + iPerWidth * (nDiv-1) - VIDEO_INTERVAL/2;
	rcMove.top = rc.top + VIDEO_INTERVAL;
	rcMove.bottom = rcMove.top + iPerHeigth * (nDiv-1) - VIDEO_INTERVAL - VIDEO_INTERVAL;
	int nWndIndex = m_nVideoIndex;
	MoveVideoWnd(nWndIndex, rcMove);
	++ nWndIndex;
	
	//second
	rcMove.left = rc.left + iPerWidth * (nDiv-1) + VIDEO_INTERVAL/2;
	rcMove.right = rc.right - VIDEO_INTERVAL;
	for (i = 0; i < (nDiv - 1); ++ i)
	{
		if(i == 0)
		{
			rcMove.top = rc.top  + iPerHeigth * i + VIDEO_INTERVAL;
		}
		else
		{
			rcMove.top = rc.top  + iPerHeigth * i + VIDEO_INTERVAL/2;
		}
		if (i == nDiv -2 )
		{
			rcMove.bottom = rc.top + iPerHeigth * (i+1) - VIDEO_INTERVAL;
		}
		else
		{
			rcMove.bottom = rc.top + iPerHeigth * (i+1) - VIDEO_INTERVAL/2;
		}
		MoveVideoWnd(nWndIndex, rcMove);
		++ nWndIndex;
	}
	
	//third
    rcMove.top = rc.bottom - iPerHeigth;
	rcMove.bottom = rc.bottom - VIDEO_INTERVAL;
	for (i = 0; i < nDiv; ++ i)
	{
		if (i == 0)
		{
			rcMove.left = rc.left + iPerWidth*i + VIDEO_INTERVAL;
		}
		else
		{
			rcMove.left = rc.left + iPerWidth*i + VIDEO_INTERVAL/2;
		}
		if (i == nDiv-1)
		{
			rcMove.right = rc.left + iPerWidth*(i+1) - VIDEO_INTERVAL;
		}
		else
		{
			rcMove.right = rc.left + iPerWidth*(i+1) - VIDEO_INTERVAL/2;
		}
		MoveVideoWnd(nWndIndex, rcMove);
		++ nWndIndex;
	}
}

void CDlgPaneView::SetWndMode(int nMode)
{
	int nBegIndex = 0;
	int nEndIndex = 0;
	if (m_nWndMode == nMode)
	{
		m_nVideoIndex = 0;
	}
	else
	{
		m_nVideoIndex = 0;
// 		m_pViewButtom[m_nWndMode]->SetOverStatus(FALSE);
// 		m_pViewButtom[nMode]->SetOverStatus(TRUE);
	}
	
	m_bShowOneMax = FALSE;
	m_nWndMode = nMode;
	int nActive = m_nActiveIndex;

	int nTemp = m_nVideoIndex + m_nWndMode * m_nWndMode;
	if (nTemp >= VIEW_MAX_NUM)
	{
		if (m_nActiveIndex >= nTemp - VIEW_MAX_NUM 
			&& m_nActiveIndex < m_nVideoIndex)
		{
			nActive = m_nVideoIndex;
		}
	}
	else
	{
		if (m_nActiveIndex < m_nVideoIndex
			|| m_nActiveIndex >= nTemp)
		{	
			nActive = m_nVideoIndex;
		}
	}

	ViewActive(nActive);

	MoveCtrl();
}

void CDlgPaneView::SetWndMove(BOOL bUp)
{
	if (bUp)
	{
		if (m_bShowVertical)
		{
			m_nVideoIndex += VERTICAL_MOVE_COUNT;
			
			if (m_nVideoIndex >= VIEW_MAX_NUM)
			{
				m_nVideoIndex = 0;
			}
		}
		else 
		{
			int nVideoNum = GetVideoNumber();
			if (m_bShowOneMax)
			{
				int nShowIndex = m_nActiveIndex + 1;
				if (nShowIndex >= VIEW_MAX_NUM)
				{
					nShowIndex = 0;
				}
				
				if (!FindActiveIndex(nShowIndex))
				{
					m_nVideoIndex += nVideoNum;
					if (m_nVideoIndex >= VIEW_MAX_NUM)
					{
						m_nVideoIndex = m_nVideoIndex - VIEW_MAX_NUM;
					}
				}
				
				ViewActive(nShowIndex);
			}
			else
			{
				m_nVideoIndex += nVideoNum;
				if (m_nVideoIndex >= VIEW_MAX_NUM)
				{
					m_nVideoIndex = m_nVideoIndex - VIEW_MAX_NUM;
				}
			}
		}
	}
	else
	{
		if (m_bShowVertical)
		{
			m_nVideoIndex -= VERTICAL_MOVE_COUNT;
			if (m_nVideoIndex < 0)
			{
				m_nVideoIndex = VIEW_MAX_NUM - VERTICAL_MOVE_COUNT;
			}
		}
		else
		{
			int nVideoNum = GetVideoNumber();
			if (m_bShowOneMax)
			{
				int nShowIndex = m_nActiveIndex - 1;
				if (nShowIndex < 0)
				{
					nShowIndex = VIEW_MAX_NUM - 1;
				}
			
				if (!FindActiveIndex(nShowIndex))
				{
					//m_nVideoIndex -= (m_nWndMode * m_nWndMode);
					m_nVideoIndex -= nVideoNum;
					if (m_nVideoIndex < 0)
					{
						m_nVideoIndex = VIEW_MAX_NUM + m_nVideoIndex;
					}
				}
				
				ViewActive(nShowIndex);
			}
			else
			{
				//m_nVideoIndex -= (m_nWndMode * m_nWndMode);
				m_nVideoIndex -= nVideoNum;
				if (m_nVideoIndex < 0)
				{
					m_nVideoIndex = VIEW_MAX_NUM + m_nVideoIndex;
				}
			}
		}
	}
	AdjustActiveIndex();
	MoveCtrl();
}

void CDlgPaneView::ShowVertical(BOOL bVertical) 
{	
	m_bShowVertical = bVertical; 
	m_nVideoIndex = 0;
	AdjustActiveIndex();
}

void CDlgPaneView::ViewActive(int nIndex)
{
	if (m_nActiveIndex != nIndex)
	{
		if ( m_nActiveIndex >= 0)
		{
			m_pViewWnd[m_nActiveIndex]->SetActive(FALSE);
		}
	//	if(MAIN_FRAME()->IsOpenSound())
		{
// 			m_pViewWnd[m_nActiveIndex]->CloseSound();
// 			m_pViewWnd[nIndex]->PlaySound();
		}
		m_nActiveIndex = nIndex;
		m_pViewWnd[m_nActiveIndex]->SetActive(TRUE);

//		UpdateToolBar();
	}
	else if( m_nActiveIndex >= 0)
	{
		m_pViewWnd[m_nActiveIndex]->SetActive(TRUE);
//		UpdateToolBar();
	}

}

void CDlgPaneView::ShowOneMax()
{
	if (!m_bShowVertical)
	{
		m_bShowOneMax = !m_bShowOneMax;
		MoveCtrl();
	}
}

void CDlgPaneView::DoPlayAudio() 
{
	
	m_pViewWnd[m_nActiveIndex]->PlaySound();
}


void CDlgPaneView::DoSnapshot() 
{
	
	m_pViewWnd[m_nActiveIndex]->Snapshot();	
}

void CDlgPaneView::DoSnapDev() 
{
	
	m_pViewWnd[m_nActiveIndex]->SnapDev();	
}


void CDlgPaneView::CloseAllSound()
{	
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		m_pViewWnd[i]->CloseSound();
	}
//	SetSoundStatus(FALSE);
}

void CDlgPaneView::IntoOneMax()
{
	if (!m_bShowOneMax)
	{
		m_bShowOneMax = TRUE;
		MoveCtrl();
	}
}
void CDlgPaneView::DoSelect()
{
	UpdateSound();
}

void CDlgPaneView::UpdateSound()
{
// 	if (MAIN_FRAME()->IsOpenSound())
// 	{
// 		if (m_pViewWnd[m_nActiveIndex]->IsPreviewing())
// 		{
// 			m_pViewWnd[m_nActiveIndex]->PlaySound();
// 		}
// 	}
// 	SetSoundStatus(MAIN_FRAME()->IsOpenSound());
}



BOOL CDlgPaneView::IsActivePreview()
{
	return m_pViewWnd[m_nActiveIndex]->IsPreviewing();
}

BOOL CDlgPaneView::IsDevChnPreviewing(int nDevID, int nChn, BOOL bMain, int& nWndIndex)
{
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		if (m_pViewWnd[i]->IsDevChnPreviewing(nDevID, nChn, bMain))
		{
			nWndIndex = i + 1;
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL CDlgPaneView::IsDevChnPicture(int nDevID, int nChn, int& nWndIndex)
{
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		if (m_pViewWnd[i]->IsDevChnPicture(nDevID, nChn))
		{
			nWndIndex = i + 1;
			return TRUE;
		}
	}
	
	return FALSE;
}

void CDlgPaneView::UpdatePreviewDev()
{
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		m_pViewWnd[i]->UpdatePreview();
	}
}

void CDlgPaneView::PreviewRealVideo(int nDevID, int nChn, BOOL bMainStream)
{
	ASSERT(!IsActivePreview());
	m_pViewWnd[m_nActiveIndex]->PreviewRealVideo(nDevID, nChn, bMainStream);
}

void CDlgPaneView::PreviewAlarmVideo(int nDevID, int nChn, BOOL bMainStream)
{
	int nWndIndex = CB_ERR;

	if (!IsDevChnPreviewing(nDevID, nChn, bMainStream, nWndIndex))
	{
		if (!IsActivePreview())
		{
			nWndIndex = m_nActiveIndex;
		}
		else
		{
			int nWndNum = WND_MODE_4 * WND_MODE_4; // if alarm video number is 4，preview screen can be set to 1 or 4
			for (int i = 0; i < nWndNum; ++ i)
			{
				if (!m_pViewWnd[i]->IsPreviewing())
				{
					nWndIndex = i ;
					break;
				}
			}
		}
		
		if (CB_ERR == nWndIndex)
		{
			m_pViewWnd[m_nAlarmIndexOld]->StopPreview();
			nWndIndex = m_nAlarmIndexOld;
			m_nAlarmIndexOld = (m_nAlarmIndexOld + 1)%4;
		}
		
// 		int nRealWndIndex = CB_ERR;
// 		if (PANE_VIEW()->IsDevChnPreviewing(nDevID, nChn, bMainStream, nRealWndIndex))
// 		{
// 			CPVFrameWnd* pAlarmPV = GetPvFramWnd(nWndIndex);
// 			CPVFrameWnd* pRealPV = PANE_VIEW()->GetPvFramWnd(nRealWndIndex-1);
// 			CDlgPaneView::SwapPvFrameWnd(pAlarmPV, pRealPV);
// 		}
// 		else
// 		{
		m_pViewWnd[nWndIndex]->PreviewRealVideo(nDevID, nChn, bMainStream);
//		}
	}
//	m_ViewTime[nWndIndex] = CTime::GetCurrentTime();
}

int CDlgPaneView::PreviewRealVideoDClik( int nDevID, int nChn, BOOL bMainStream )
{
	if (!m_pViewWnd[m_nActiveIndex]->IsPreviewing())
	{
		PreviewRealVideo(nDevID, nChn, bMainStream);
//		m_ViewTime[m_nActiveIndex] = CTime::GetCurrentTime();
		return m_nActiveIndex;
	}

	for (int i = 0 ; i < VIEW_MAX_NUM; ++i)
	{
		if (m_pViewWnd[i]->IsWindowVisible() && !m_pViewWnd[i]->IsPreviewing() && i != m_nActiveIndex)
		{
			m_pViewWnd[i]->PreviewRealVideo(nDevID, nChn, bMainStream);
			return i;
		}
	}

	return -1;
}

void CDlgPaneView::OnDevChanPreView(int nDevID, int nChn, BOOL bMainStream)
{
	if (m_pViewWnd[m_nActiveIndex]->IsPreviewing())
	{
		m_pViewWnd[m_nActiveIndex]->StopPreview();
	}
	m_pViewWnd[m_nActiveIndex]->PreviewRealVideo(nDevID, nChn, bMainStream);
}

BOOL CDlgPaneView::IsPlayRemoteFile(GPSFile_S* pFile, int& nWndIndex)
{
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		if (m_pViewWnd[i]->IsPlayRemoteFile(pFile))
		{
			nWndIndex = i + 1;
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL CDlgPaneView::PlayRemoteFile(GPSFile_S* pFile)
{
	int nWndIndex = 0;
	if (IsPlayRemoteFile(pFile, nWndIndex))
	{
		CString str;
// 		str.Format(LOADSTRINGEX(ID_STR_DLG_RECS_PLAY_RUNNING), nWndIndex);
// 		MSG_BOX_STR(str);
		return FALSE;
	}
	
	BOOL bRet = m_pViewWnd[m_nActiveIndex]->PlayRemoteFile(pFile);
	
	return bRet;
}

BOOL CDlgPaneView::FindActiveIndex(int nActiveIndex)
{
	BOOL bFind = FALSE;
	int nCount = 0;
	if (m_bShowVertical)
	{
		nCount = VERTICAL_MOVE_COUNT;
	}
	else
	{
		nCount = m_nWndMode * m_nWndMode;
	}
	
	for (int i = 0; i < nCount; ++ i)
	{
		int nWndIndex = (m_nVideoIndex + i) % VIEW_MAX_NUM;
		if (nWndIndex == nActiveIndex)
		{
			bFind = TRUE;
			break;
		}
	}
	return bFind;
}

void CDlgPaneView::AdjustActiveIndex()
{
	if (m_bShowVertical)
	{
		if (!FindActiveIndex(m_nActiveIndex))
		{
			ViewActive(m_nVideoIndex);
		}
	}
	else
	{
		if (!FindActiveIndex(m_nActiveIndex))
		{
			ViewActive(m_nVideoIndex);
		}
	}
}

void CDlgPaneView::ChangeVolume(WORD wVolume)
{
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		m_pViewWnd[i]->ChangeVolume(wVolume);
	}
}

void CDlgPaneView::StopPlay()
{
	m_pViewWnd[m_nActiveIndex]->OnMenuPreviewView();
}

CPVPlay* CDlgPaneView::GetPVPlayPlayer()
{
	return m_pViewWnd[m_nActiveIndex]->GetPVPlayPlayer();
}
/*

#define GPS_PTZ_MOVE_LEFT				0	//左
#define GPS_PTZ_MOVE_RIGHT				1	//右
#define GPS_PTZ_MOVE_TOP				2	//上
#define GPS_PTZ_MOVE_BOTTOM				3	//下
#define GPS_PTZ_MOVE_LEFT_TOP			4	//左上
#define GPS_PTZ_MOVE_RIGHT_TOP			5	//右上
#define GPS_PTZ_MOVE_LEFT_BOTTOM		6	//左下
#define GPS_PTZ_MOVE_RIGHT_BOTTOM		7	//右下

#define GPS_PTZ_FOCUS_DEL				8	//焦距变小
#define GPS_PTZ_FOCUS_ADD				9	//焦距变大
#define GPS_PTZ_LIGHT_DEL				10	//光圈变小
#define GPS_PTZ_LIGHT_ADD				11	//光圈变大
#define GPS_PTZ_ZOOM_DEL				12	//焦点后调(倍数)
#define GPS_PTZ_ZOOM_ADD				13	//焦点前调
#define GPS_PTZ_LIGHT_OPEN				14	//灯光
#define GPS_PTZ_LIGHT_CLOSE				15
#define GPS_PTZ_WIPER_OPEN				16	//雨刷
#define GPS_PTZ_WIPER_CLOSE				17
#define GPS_PTZ_CRUISE					18	//自动巡航
#define GPS_PTZ_MOVE_STOP				19	//停止

#define GPS_PTZ_PRESET_MOVE				21	//调用
#define GPS_PTZ_PRESET_SET				22	//设置
#define GPS_PTZ_PRESET_DEL				23	//删除

#define GPS_PTZ_SPEED_MIN				0
#define GPS_PTZ_SPEED_MAX				255
*/
void CDlgPaneView::PtzControl(int nCommand, int nParam, int nSpeed)
{
	int nDevice = 0;
	int nChannel = 0;
	CPVFrameWnd* pPVFrameWnd = m_pViewWnd[m_nActiveIndex];
 	//if (m_pViewWnd[m_nActiveIndex]->GetPreviewDevice(nDevice, nChannel))
	if (pPVFrameWnd && pPVFrameWnd->IsPreviewing())
 	{
		int nDevID = 0, nChn = 0;
		pPVFrameWnd->GetDefaultAV(nDevID, nChn);
 		CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);	
 		if (pDevice != NULL)
 		{
 			NETCLIENT_MCSendPtz(CStringA(pDevice->GetDevIDNO()), nChannel, nCommand, nSpeed, nParam, this, FUNPtzMsgCB);
 		}
 	}
	else
	{
		CString strTemp;
		strTemp.Format(_T("Error:Wnd[%d] No Preview!"), m_nActiveIndex+1);
		AfxMessageBox(strTemp);
	}
}

void CDlgPaneView::ColorControl(int nBri, int nCon, int nHue, int nSat)
{
	int nDevice = 0;
	int nChannel = 0;
// 	if (m_pViewWnd[m_nActiveIndex]->GetPreviewDevice(nDevice, nChannel))
// 	{
// //		NETCLIENT_ColorControl(nDevice, nChannel, nBri, nCon, nHue, nSat);
// 	}
}

void CDlgPaneView::ChangeViewMode()
{
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		m_pViewWnd[i]->SetViewMode(VIEW_MODE_UNDEFINE);
	}
}

void CDlgPaneView::ChangeViewSize()
{
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		m_pViewWnd[i]->SetViewSize(VIEW_SIZE_UNDEFINE);
	}
}

void CDlgPaneView::SetDelayTime()
{
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		m_pViewWnd[i]->SetDelayTime();
	}
}

void CDlgPaneView::OnMenuViewSnapshot() 
{
	// TODO: Add your command handler code here
	DoSnapshot();
}

BOOL CDlgPaneView::IsEnableViewGroup()
{
	return m_bShowVertical || !(VIEW_MAX_NUM == GetVideoNumber() && !m_bShowOneMax);
}


void CDlgPaneView::OnMenuViewWnd() 
{
	// TODO: Add your command handler code here
	SetWndMode(m_nWndMode);
}


void CDlgPaneView::OnMenuViewDown() 
{
	// TODO: Add your command handler code here
	if (IsEnableViewGroup())
	{
		SetWndMove(TRUE);
	}
}

void CDlgPaneView::OnMenuViewUp() 
{
	// TODO: Add your command handler code here
	if (IsEnableViewGroup())
		SetWndMove(FALSE);
}

void CDlgPaneView::OnMenuViewAvStart() 
{
	// TODO: Add your command handler code here
//	if(IS_PRIVILEGE_TIP(PRIVI_VIDEO))
	{
		if (!m_pViewWnd[m_nActiveIndex]->IsPreviewing())
		{
			m_pViewWnd[m_nActiveIndex]->PreviewDefaultAV();
		}
	}
}

void CDlgPaneView::OnMenuViewAvStop() 
{
	// TODO: Add your command handler code here
	if (m_pViewWnd[m_nActiveIndex]->IsPreviewing())
	{
		m_pViewWnd[m_nActiveIndex]->StopPreview();
	}
}


void CDlgPaneView::OnMenuViewAvStartAll() 
{
	// TODO: Add your command handler code here
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{
		if (!m_pViewWnd[i]->IsPreviewing())
		{
			m_pViewWnd[i]->PreviewDefaultAV();
		}
	}
}

void CDlgPaneView::OnMenuViewAvStopAll() 
{
	// TODO: Add your command handler code here
	for (int i = 0; i < VIEW_MAX_NUM; ++ i)
	{	
		if (m_pViewWnd[i]->IsPreviewing())
		{
			m_pViewWnd[i]->StopPreview();
		}
	}
}

void CDlgPaneView::SetWndInActive()
{
	for(int index = 0; index < VIEW_MAX_NUM; index++)
	{
		m_pViewWnd[index]->SetActive(FALSE);
	}
}

void CDlgPaneView::StopAllVideo()
{
	for(int index = 0; index < VIEW_MAX_NUM; index++)
	{
		if(m_pViewWnd[index]->IsPreviewing())
		{
			m_pViewWnd[index]->OnMenuPreviewView();
		}
	}
}

void CDlgPaneView::StopVideoView(int nDevID,int nChn)
{
	for(int index = 0; index < VIEW_MAX_NUM; index++)
	{
		if(m_pViewWnd[index]->IsPreviewing())
		{
			if (m_pViewWnd[index]->IsDevChnPreviewing(nDevID, nChn, FALSE))
			{
				m_pViewWnd[index]->StopChannelView();
			}
		}
	}
}

CPVFrameWnd* CDlgPaneView::GetPvFramWnd(int WndIndex)
{
	ASSERT(WndIndex >=0 && WndIndex < VIEW_MAX_NUM);
	return m_pViewWnd[WndIndex];
}

HWND CDlgPaneView::GetPlaybackWnd()
{
	return m_pViewWnd[0]->GetPlayHwnd();
}

void CDlgPaneView::SetPVFrameWnd(int nWndIndex, CPVFrameWnd* pWnd)
{
	m_pViewWnd[nWndIndex] = pWnd;
}

void CDlgPaneView::SwapPvFrameWnd(CPVFrameWnd* pAlarmPV, CPVFrameWnd* pRealPV)
{
	CString strTitle;
	int AlarmIndex = pAlarmPV->GetIndex();
	int ViewIndex = pRealPV->GetIndex();
	CDlgPaneView* pAlarmDlg = pAlarmPV->GetPaneView();
	CDlgPaneView* pViewDlg = pRealPV->GetPaneView();

	pAlarmPV->SetIndex(ViewIndex);
	pAlarmPV->SetPaneView(pViewDlg);
	pAlarmPV->SetParent(pViewDlg);

	
	pRealPV->SetIndex(AlarmIndex);
	pRealPV->SetPaneView(pAlarmDlg);
	pRealPV->SetParent(pAlarmDlg);

	
	pAlarmDlg->SetPVFrameWnd(AlarmIndex, pRealPV);
	strTitle.Format(_T("%d"), AlarmIndex + 1);
	pRealPV->SetActive(FALSE);
	pAlarmDlg->MoveCtrl();

	pViewDlg->SetPVFrameWnd(ViewIndex, pAlarmPV);
	pViewDlg->MoveCtrl();

	pAlarmDlg->ViewActive(0);
}



int	CDlgPaneView::GetVideoNumber()
{
	int nRet = 0;
	if (WND_MODE_1 == m_nWndMode || WND_MODE_4 == m_nWndMode
		|| WND_MODE_9 == m_nWndMode || WND_MODE_16 == m_nWndMode
		|| WND_MODE_36 == m_nWndMode || WND_MODE_64 == m_nWndMode)
	{
		nRet = m_nWndMode * m_nWndMode;
	}
	else if (WND_MODE_6 == m_nWndMode)
	{
		nRet = 6;
	}
	else if (WND_MODE_8 == m_nWndMode)
	{
		nRet = 8;
	}
	else 
	{
		ASSERT(FALSE);
	}
	return nRet;
}

int	CDlgPaneView::GetVideoShowCount()
{
	if (m_bShowVertical)
	{
		return 4;
	}
	else
	{
		if (m_bShowOneMax)
		{
			return 1;
		}
		else
		{
			return GetVideoNumber();
		}
	}
}

void CDlgPaneView::PreviewVideo(int nDevID, int nChn, int nIndex)
{
	int nTemp = m_nVideoIndex + nIndex;
	nTemp %= VIEW_MAX_NUM;
	m_pViewWnd[nTemp]->PreviewRealVideo(nDevID, nChn, FALSE);
}

void CDlgPaneView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TIMER_IDEVENT_CLOSEVIDEO)
	{

	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgPaneView::ResetPVPlayerTime(int nWndIndex)
{
// 	CPVRealPlay* pPVPlayer = m_pViewWnd[nWndIndex]->GetPVRealPlay();
// 	if (pPVPlayer)
// 	{
// 		pPVPlayer->SetVideoTime();
// 	}
}

void CDlgPaneView::ResetPVPlayerTime()
{
	for (int nWndVideoIndex=0; nWndVideoIndex<16 ;nWndVideoIndex++)
	{
		if (m_pViewWnd[nWndVideoIndex]->IsPreviewing())			
		{
			int nPlayMode = m_pViewWnd[nWndVideoIndex]->GetPlayMode();
			if (PV_MODE_POLLING == nPlayMode)
			{

			}
			else
			{
				ResetPVPlayerTime(nWndVideoIndex);
// 				CPVRealPlay* pPVPlayer = m_pViewWnd[nWndVideoIndex]->GetPVRealPlay();
// 				if (pPVPlayer)
// 				{
// 					pPVPlayer->SetVideoTime();
// 				}
			}				
		}		
	}
}


void CDlgPaneView::DoAlarmSnapshotFinish(CDevBase* pDevice, GPSVehicleAlarm_S* pVehiAlarm)
{
	for (int i = 0; i < VIEW_MAX_NUM; ++i)
	{
		m_pViewWnd[i]->DoAlarmSnapshotFinish(pDevice, pVehiAlarm);
	}	
}

BOOL CDlgPaneView::StartPicturePreview(int nDevID)
{
	BOOL bRet = FALSE;
	int nIndex = -1;
	if (!m_pViewWnd[m_nActiveIndex]->IsPreviewing())
	{
		nIndex = m_nActiveIndex;
	}
	else
	{
		for (int i = 0 ; i < VIEW_MAX_NUM; ++i)
		{
			if (m_pViewWnd[i]->IsWindowVisible() && !m_pViewWnd[i]->IsPreviewing() && i != m_nActiveIndex)
			{
				nIndex = i;
				break;
			}
		}
	}
	
	if (nIndex >= 0 && nIndex < VIEW_MAX_NUM)
	{
		m_pViewWnd[nIndex]->PreviewRealVideo(nDevID, 0, 0, PV_MODE_PICTURE);
		bRet = TRUE;
	}
	
	return bRet;
}

BOOL CDlgPaneView::StopPicturePreview(int nDevID)
{
	BOOL bRet = FALSE;
	for(int index = 0; index < VIEW_MAX_NUM; index++)
	{
		if(m_pViewWnd[index]->IsPreviewing())
		{
			if (m_pViewWnd[index]->IsDevChnPreviewing(nDevID, 0, FALSE))
			{
				m_pViewWnd[index]->StopChannelView();
				bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}

void CALLBACK CDlgPaneView::FUNPtzMsgCB( GPSMCMsg_S* pMsg, void* pUsr )
{
	CDlgPaneView* pThis = (CDlgPaneView*)pUsr;
	pThis->DoPtzMsgCB(pMsg);
}

void CDlgPaneView::DoPtzMsgCB( GPSMCMsg_S* pMsg )
{
	if ( !IsWindow(m_hWnd) || !PostMessage(WM_MSG_PTZ_CTRL, (WPARAM)pMsg) )
	{
		NETCLIENT_MCReleaseMsg(pMsg);
	}
}

LRESULT CDlgPaneView::OnPtzMsg( WPARAM wParam, LPARAM lParam )
{
	GPSMCMsg_S* pMsg = (GPSMCMsg_S* )wParam;
	if (GPS_OK != pMsg->nResult)
	{
		CString strTemp;
		strTemp.Format(_T("PTZ Operator Fail!Error Code:%d"), pMsg->nResult);
		AfxMessageBox(strTemp);
	}
	else
	{
#ifdef _DEBUG
		AfxMessageBox(_T("PTZ Operator OK!"));
#endif // _DEBUG
	}

	NETCLIENT_MCReleaseMsg(pMsg);
	return 0;
}
