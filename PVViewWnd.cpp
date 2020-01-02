// PVViewWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PVViewWnd.h"
#include "PVFrameWnd.h"
#include "DlgPaneView.h"

#define PV_VIDEO_WND_ID			200

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPVViewWnd
const int LBTN_DRAG_TIMER = 1;

CPVViewWnd::CPVViewWnd()
{
	m_bActive = FALSE;
	m_pPVFrameWnd = NULL;
	ResetMarginRect();
}

CPVViewWnd::~CPVViewWnd()
{
}


BEGIN_MESSAGE_MAP(CPVViewWnd, CWnd)
	//{{AFX_MSG_MAP(CPVViewWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPVViewWnd message handlers

int CPVViewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	RECT rc = {0};
	m_VideoWnd.Create(NULL, NULL, WS_VISIBLE|WS_CHILD, rc, this, PV_VIDEO_WND_ID);

	return 0;
}
void CPVViewWnd::Start()
{
	m_VideoWnd.Start();
}
void CPVViewWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	m_VideoWnd.DestroyWindow();
}

void CPVViewWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	MoveWnd();
	CRgn rgn;
	RECT rc;
	GetClientRect(&rc);
	rgn.CreateRoundRectRgn(rc.left+1,rc.top-5,rc.right,rc.bottom, 5, 5);
	SetWindowRgn(rgn, TRUE);
	rgn.DeleteObject();
}

void CPVViewWnd::MoveWnd()
{
	if (m_pPVFrameWnd && m_VideoWnd.GetSafeHwnd())
	{
		RECT rc;
		GetClientRect(&rc);
	//	InflateRect(&rc, -4, -4);
		rc.left += 4;
		rc.bottom -= 4;
		rc.right -= 4;
		RECT rcMove;
		
		if (VIEW_SIZE_FULL == m_pPVFrameWnd->GetViewSize())
		{
			rcMove = rc;
			ResetMarginRect();
		}
		else 
		{
			int nWidth = rc.right - rc.left;
			int nHeight = rc.bottom - rc.top;
			double dbTemp = 1;
			if (VIEW_SIZE_4_3 == m_pPVFrameWnd->GetViewSize())
			{
				dbTemp = 4 * 1.0 / 3;
			}			
			else
			{
				dbTemp = 16 * 1.0 / 9;
			}
			CRect rcPos;
			rcPos.left = rcPos.top = 0;
			int nShowHeight = (int)(nWidth / dbTemp);
			if (nShowHeight > nHeight)
			{
				int nShowWidth = (int)(nHeight * dbTemp);
				if (nShowWidth > nWidth)
				{
					int nTemp = nHeight;
					while(TRUE)
					{
						nTemp -= 10;
						nShowWidth = (int)(nTemp * dbTemp);
						if (nShowWidth <= nWidth)
						{
							break;
						}
					}
					rcPos.right = nShowWidth;
					rcPos.bottom = nTemp;
				}
				else
				{
					rcPos.right = nShowWidth;
					rcPos.bottom = nHeight;
				}
			}
			else
			{
				rcPos.right = nWidth;
				rcPos.bottom = nShowHeight;
			}
			
			int nMiddleWidth = rc.left + nWidth / 2 ;
			int nMiddleHeight = rc.top + nHeight / 2;
			rcMove.left = nMiddleWidth - rcPos.Width() / 2;
			rcMove.right = nMiddleWidth + rcPos.Width() / 2;
			rcMove.top = nMiddleHeight - rcPos.Height() / 2;
			rcMove.bottom = nMiddleHeight + rcPos.Height() / 2;
		}

		GetClientRect(&rc);
		m_rcMarginTop.left = rc.left;
		m_rcMarginTop.right = rc.right;
		m_rcMarginTop.top = rc.top;
		m_rcMarginTop.bottom = rcMove.top;
		m_rcMarginBottom.left = rc.left;
		m_rcMarginBottom.right = rc.right;
		m_rcMarginBottom.top = rcMove.bottom - 1;
		m_rcMarginBottom.bottom = rc.bottom;
		
		m_rcMarginLeft.top = rcMove.top;
		m_rcMarginLeft.bottom = rcMove.bottom;
		m_rcMarginLeft.left = rc.left;
		m_rcMarginLeft.right = rcMove.left;
		m_rcMarginRight.top = rcMove.top;
		m_rcMarginRight.bottom = rcMove.bottom;
		m_rcMarginRight.left = rcMove.right - 1;
		m_rcMarginRight.right = rc.right;

		m_VideoWnd.MoveWindow(&rcMove);

		m_pPVFrameWnd->AdjustedWndRect();
	}
}

void CPVViewWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (m_bActive)
	{
		DrawActiveRect();
	}
	else
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		HBRUSH hBrush = (HBRUSH)::CreateSolidBrush(RGB(228,228,228));
		::FillRect(dc.GetSafeHdc(), &rcClient, hBrush);
		::DeleteObject(hBrush);
	}
}

void CPVViewWnd::SetActive(BOOL bActive)
{
	m_bActive = bActive;
	Invalidate();
}

void CPVViewWnd::DrawActiveRect()
{
	//	leeafu 2012-07-11
	//return ;
	if (GetSafeHwnd())
	{
		RECT rc;
		GetClientRect(&rc);
		CClientDC dc(this);
		CBrush brush(RGB(0,255,255));
		dc.FillRect(&m_rcMarginTop, &brush);
		dc.FillRect(&m_rcMarginBottom, &brush);
		dc.FillRect(&m_rcMarginLeft, &brush);
		dc.FillRect(&m_rcMarginRight, &brush);
	}
}

BOOL CPVViewWnd::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( (WM_KEYDOWN == pMsg->message) && (VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		return FALSE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

void CPVViewWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pPVFrameWnd->OnDIVLBtnDown(m_VideoWnd.GetIndex());
	/*
	if (m_VideoWnd.GetEnableDarg())
	{
		if (m_VideoWnd.DragValid())
		{
			SetTimer(LBTN_DRAG_TIMER, 250, NULL);
		}
	}
	*/
	CWnd::OnLButtonDown(nFlags, point);
}

void CPVViewWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pPVFrameWnd->OnDIVLBDblClk(m_VideoWnd.GetIndex());

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CPVViewWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pPVFrameWnd->OnDIVLBtnDown(m_VideoWnd.GetIndex());
//	m_pPVFrameWnd->OnDIVRBtnDown(m_VideoWnd.GetIndex());

	CWnd::OnRButtonDown(nFlags, point);
}

void CPVViewWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (LBTN_DRAG_TIMER == nIDEvent)
	{
		KillTimer(LBTN_DRAG_TIMER);
// 		m_VideoWnd.BeginDrag();
	}

	CWnd::OnTimer(nIDEvent);
}

void CPVViewWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// 	if (m_VideoWnd.GetEnableDarg())
// 	{
// 		KillTimer(LBTN_DRAG_TIMER);
// 	}

	CWnd::OnLButtonUp(nFlags, point);
}

void CPVViewWnd::ResetMarginRect()
{
	memset(&m_rcMarginTop, 0, sizeof(m_rcMarginTop));
	memset(&m_rcMarginBottom, 0, sizeof(m_rcMarginBottom));
	memset(&m_rcMarginLeft, 0, sizeof(m_rcMarginLeft));
	memset(&m_rcMarginRight, 0, sizeof(m_rcMarginRight));
}