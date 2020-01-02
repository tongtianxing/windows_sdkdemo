// DlgRecPlayback.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecPlayback.h"
//#include "DlgPaneMap.h"
#include "DlgPaneView.h"
#include "DlgRecPlaybackControl.h"
#include "DevBase.h"
#include "PVFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecPlayback dialog


CDlgRecPlayback::CDlgRecPlayback(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecPlayback::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecPlayback)
		// NOTE: the ClassWizard will add member initialization here
//	m_pDlgPaneMap = NULL;
	m_pDlgPaneView = NULL;
	m_pDlgControl = NULL;
	m_bFirst = TRUE;
	//}}AFX_DATA_INIT
}


void CDlgRecPlayback::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecPlayback)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecPlayback, CDialog)
	//{{AFX_MSG_MAP(CDlgRecPlayback)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecPlayback message handlers

BOOL CDlgRecPlayback::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRecPlayback::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
// 	CMemDC dcMem(&dc);
// 	CRect rc, rcMove;
// 	GetClientRect(&rc);
// 	DrawWndBK(dcMem->GetSafeHdc(), this, RGB(192, 191, 190));
// 	rc.DeflateRect(1, 1, 1, 1);
// //	DrawWndBK(dc.GetSafeHdc(), rc, RGB(230, 230, 229));
// 	DrawWndBK(dcMem->GetSafeHdc(), rc, RGB(255,255,255));
	
// 	DrawWndFrameRect(this, dc.GetSafeHdc(), RGB(192, 191, 190));
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgRecPlayback::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	MoveCtrl();
}
void CDlgRecPlayback::MoveCtrl()
{
	if(m_pDlgPaneView && m_pDlgPaneView->GetSafeHwnd())
	{
		CRect rc, rcMove;
		GetClientRect(&rc);
		int nDlgControlHeight = 65;
		rcMove = rc;
		if (m_bFirst == FALSE)
		{
// 			rcMove.top -= 1;
// 			rcMove.left = rc.Width()*0.618;
// 			m_pDlgPaneMap->MoveWindow(rcMove);
			
			rcMove.top += 1;
			rcMove.right = rcMove.left-1;
			rcMove.left = rc.left+1;
			rcMove.bottom -= nDlgControlHeight;
		}
		else
		{
			rcMove.top += 1;
			int nWidth = rc.Height()*4/3;
			if(rc.Width() > nWidth)
			{
				int nSpace = (rc.Width()-nWidth)/2;
				rcMove.left = rc.left + nSpace;
				rcMove.right = rc.right - nSpace;
			}
			rcMove.bottom -= nDlgControlHeight;
		}
		m_pDlgPaneView->MoveWindow(rcMove);
		rcMove.top = rcMove.bottom+1;
		rcMove.bottom = rc.bottom-1;
		m_pDlgControl->MoveWindow(rcMove);
		m_pDlgControl->AdjustedWndRect();
	}
}
int CDlgRecPlayback::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	m_pDlgPaneView = new CDlgPaneView;
	m_pDlgPaneView->Create(CDlgPaneView::IDD, this);
//	m_pDlgPaneView->SetPaneViewMode(PANE_VIEW_MODE_PLAYBACK);
	m_pDlgPaneView->SetWndMode(WND_MODE_1);
	m_pDlgPaneView->ShowWindow(SW_SHOW);

	m_pDlgControl = new CDlgRecPlaybackControl;
	m_pDlgControl->Create(CDlgRecPlaybackControl::IDD, this);
	m_pDlgControl->ShowWindow(SW_SHOW);


	return 0;
}

void CDlgRecPlayback::CreateMapDlg()
{
// 	if (m_pDlgPaneMap = NULL)
// 	{
// 		m_pDlgPaneMap = new CDlgPaneMap;
// 		m_pDlgPaneMap->SetInitMapLoad(DLG_MAP_TYPE_REC_BACK);
// 		m_pDlgPaneMap->Create(CDlgPaneMap::IDD, this);
// 	}
}

void CDlgRecPlayback::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
// 	if (m_pDlgPaneMap)
// 	{
// 		m_pDlgPaneMap->DestroyWindow();
// 		SAFE_DELETE_OBJECT(m_pDlgPaneMap);
// 	}
	if (m_pDlgPaneView)
	{
		m_pDlgPaneView->DestroyWindow();
//		SAFE_DELETE_OBJECT(m_pDlgPaneView);
	}
	if (m_pDlgControl)
	{
		m_pDlgControl->DestroyWindow();
		SAFE_DELETE_OBJECT(m_pDlgControl);
	}
}

void CDlgRecPlayback::FirstPlay()
{
// 	if (m_bFirst)
// 	{
// 		CreateMapDlg();
// 		m_pDlgPaneMap->LoadMap();
// 		m_bFirst = FALSE;
// 		m_pDlgPaneMap->ShowWindow(SW_SHOW);
// 		MoveCtrl();
// 	}
}

void CDlgRecPlayback::Play(GPSFile_S* pFile, int nChannel, int nBegMinSecond)
{
	//Don't load a map, if playback to load maps, delete FirstPlay() comments
//	FirstPlay();
	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(pFile->szDevIDNO);
	CString str;
	str.Format(_T("%s - %s"), pDev->GetShowName(), pDev->GetChnName(nChannel));
//	m_pDlgPaneView->UpDateViewTitile(str, 0);
	int nEndMinSecond = (pFile->uiEndtime - pFile->uiBegintime)*1000;
	m_pDlgControl->Play(pFile, nChannel, nBegMinSecond, nEndMinSecond, m_pDlgPaneView->GetPlaybackWnd());
}
void CDlgRecPlayback::PlayPicture(CString str)
{
//	m_pDlgPaneView->PlayPicture(str);
}
void CDlgRecPlayback::Stop()
{
	m_pDlgControl->Stop();
}
void CDlgRecPlayback::ChangeViewSize()
{
	m_pDlgPaneView->ChangeViewSize();
}

void CDlgRecPlayback::ShowViewTilte()
{
//	m_pDlgPaneView->ShowViewTilte();
}