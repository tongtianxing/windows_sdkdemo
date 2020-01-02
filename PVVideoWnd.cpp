// PVVideoWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PVVideoWnd.h"
#include "PVFrameWnd.h"
#include "DlgPaneView.h"
//#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int LBTN_SEL_TIMER = 1;
const int LBTN_DRAG_TIMER = 2;

/////////////////////////////////////////////////////////////////////////////
// CPVVideoWnd

CPVVideoWnd::CPVVideoWnd()
{
	m_nIndex = 0;
	m_pFrameWnd = NULL;
	m_bEnableDrag = FALSE;
	m_bEnableDraw = FALSE;

	m_bDrawing = FALSE;
	m_ptStart.x = m_ptStart.y = 0;
	m_ptEnd.x = m_ptEnd.y = 0;
	memset(&m_RectRegion, 0, sizeof(m_RectRegion));
	memset(&m_rcClient, 0, sizeof(m_rcClient));
	m_bRectValid = FALSE;
	m_hCursorSelect = ::LoadCursor(NULL, MAKEINTRESOURCE(32649));
//	m_pImgBK = NULL;
}

CPVVideoWnd::~CPVVideoWnd()
{
}


BEGIN_MESSAGE_MAP(CPVVideoWnd, CWnd)
	//{{AFX_MSG_MAP(CPVVideoWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPVVideoWnd message handlers
int CPVVideoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
// 	CRect rect, rcMove;
// 	GetClientRect(&rect);
// 	rcMove.top  = rect.top + POPUP_DLG_TOP_INERVAL;
// 	rcMove.right = rect.right - POPUP_DLG_RIGHT_INERVAL;
// 	rcMove.left = rcMove.right - POPUP_DLG_BTN_CLOSE_WIDTH;
// 	rcMove.bottom = rcMove.top + POPUP_DLG_BTN_CLOSE_HIGHT;
//  	if(!m_btnPlay.Create("", WS_CHILD|WS_VISIBLE|WS_TABSTOP, rcMove, this, IDC_PVVIDEO_WND_PLAY_BTN))
//  		return -1;
// 
// 	m_btnPlay.SetIcon(IDI_ICON_VIDEO_PLAY, IDI_ICON_VIDEO_PLAY_OVER);
// 	m_btnPlay.DrawBorder(FALSE);
// 
	return 0;
}
void CPVVideoWnd::Start()
{
	CRect rc;
	GetClientRect(&rc);
// 	if (m_btnPlay.GetSafeHwnd())
// 	{
// 		m_btnPlay.MoveWindow((rc.Width()-64)/2, (rc.Height()-64)/2, 64, 64);
// 		m_btnPlay.DrawTransparent(TRUE);
// 		m_btnPlay.Invalidate(TRUE);
// 	}
	return;
	CRgn rgn;
	rgn.CreateRoundRectRgn(rc.left+1,rc.top+6,rc.right,rc.bottom, 5, 5);
	SetWindowRgn(rgn, TRUE);
	rgn.DeleteObject();
}
void CPVVideoWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	// TODO: Add your message handler code here
}
void CPVVideoWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rc;
	GetClientRect(&rc);
// 	if (m_btnPlay.GetSafeHwnd())
// 	{
// 		m_btnPlay.MoveWindow((rc.Width()-64)/2, (rc.Height()-64)/2, 64, 64);
// 		m_btnPlay.DrawTransparent(TRUE);
// 	}
	CRgn rgn;
	rgn.CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom, 5, 5);
	SetWindowRgn(rgn, TRUE);
	rgn.DeleteObject();
}

void CPVVideoWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	CRect rcClient, rcMove;
	GetClientRect(&rcClient);
	HBRUSH hBrush = (HBRUSH)::CreateSolidBrush(RGB(0,0,0));
	::FillRect(dc.GetSafeHdc(), &rcClient, hBrush);
	::DeleteObject(hBrush);

}

void CPVVideoWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pFrameWnd->OnDIVLBtnDown(m_nIndex);

	CWnd::OnLButtonDown(nFlags, point);
}

void CPVVideoWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}

void CPVVideoWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDrawing)
	{
		if(abs(point.x-m_ptStart.x)<5 || 
			abs(point.y-m_ptStart.y)<5 )
		{
			m_bRectValid = FALSE;
			m_pFrameWnd->SetDrawEmpty();
		}
		else
		{
			CPoint pt = point;
			RECT rcClient;
			GetClientRect(&rcClient);
			if (pt.x > rcClient.right)
			{
				pt.x = rcClient.right;
			}
			else if (pt.x < rcClient.left)
			{
				pt.x = rcClient.left;
			}

			if (pt.y > rcClient.bottom)
			{
				pt.y = rcClient.bottom;
			}
			else if (pt.y < rcClient.top)
			{
				pt.y = rcClient.top;
			}

			CalcRectRegion(m_ptStart, pt, m_RectRegion);
			m_bRectValid = TRUE;
			m_pFrameWnd->SetDrawRect(m_RectRegion, rcClient);
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CPVVideoWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pFrameWnd->OnDIVLBDblClk(m_nIndex);
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CPVVideoWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// 	m_pFrameWnd->OnDIVLBtnDown(m_nIndex);
// 	m_pFrameWnd->OnDIVRBtnDown(m_nIndex);
	CWnd::OnRButtonDown(nFlags, point);
}

BOOL CPVVideoWnd::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( (WM_KEYDOWN == pMsg->message) && (VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		return FALSE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

void CPVVideoWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (LBTN_SEL_TIMER == nIDEvent)
	{
		KillTimer(LBTN_SEL_TIMER);
	}
	else if (LBTN_DRAG_TIMER == nIDEvent)
	{
		KillTimer(LBTN_DRAG_TIMER);
//		BeginDrag();
	}

	CWnd::OnTimer(nIDEvent);
}

void CPVVideoWnd::CalcRectRegion(const CPoint& ptStart, const CPoint& ptEnd, RECT& rcRegion)
{
	if ( ptStart.x < ptEnd.x )
	{
		if (ptStart.y < ptEnd.y)
		{
			rcRegion.left=ptStart.x;
			rcRegion.top=ptStart.y;
			rcRegion.right=ptEnd.x;
			rcRegion.bottom=ptEnd.y;
		}
		else
		{
			rcRegion.left=ptStart.x;
			rcRegion.top=ptEnd.y;
			rcRegion.right=ptEnd.x;
			rcRegion.bottom=ptStart.y;
		}
	}
	else
	{
		if (ptStart.y > ptEnd.y)
		{
			rcRegion.left=ptEnd.x;
			rcRegion.top=ptEnd.y;
			rcRegion.right=ptStart.x;
			rcRegion.bottom=ptStart.y;
		}
		else
		{
			rcRegion.left=ptEnd.x;
			rcRegion.top=ptStart.y;
			rcRegion.right=ptStart.x;
			rcRegion.bottom=ptEnd.y;
		}
	}
}

BOOL CPVVideoWnd::PlayValid()
{
	return m_pFrameWnd->PlayValid();
}

BOOL CPVVideoWnd::DragValid()
{
//	return m_pFrameWnd->DragValid(m_nIndex);
	return FALSE;
}

void CPVVideoWnd::BeginDraw(CPoint point)
{
	m_bSelected = FALSE;
	m_bDrawing = TRUE;
	m_ptStart = point;
	m_pFrameWnd->SetDrawFocus(FALSE);
}

void CPVVideoWnd::SetRectEmpty()
{
	m_bRectValid = FALSE;
}

void CPVVideoWnd::GetLineString(HDC hDc, CRect& rcClient, CString strInfo, vecString& LineStr)
{
	CString strTemp = strInfo;
	while(TRUE)
	{
		BOOL bLine = FALSE;
		SIZE sz;
		int nLen = strTemp.GetLength();
		int i =0;
		for (i = 0; i < nLen; ++ i)
		{
			::GetTextExtentPoint(hDc, strTemp, i, &sz);
			if (sz.cx >= rcClient.Width())
			{
				bLine = TRUE;
				break;
			}
		}

		if (bLine)
		{
			i = i - 1;
			int k = 0;
			for (k = 0; k < i; ++ k)
			{
				BYTE bTemp = BYTE(strTemp.GetAt(i));
				if ( IsDBCSLeadByte( bTemp ) )
				{
					++ k;
				}
			}
			if ( k != i)
			{
				i = i - 1;
			}
			CString str = strTemp.Left(i);
			LineStr.push_back(str);
			strTemp = strTemp.Right(nLen - i);
		}
		else
		{
			LineStr.push_back(strTemp);
			break;
		}
	}
}
