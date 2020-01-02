// SliCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "SliCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSliCtrlEx

CSliCtrlEx::CSliCtrlEx()
{
	m_bLBtnDown = FALSE;
}

CSliCtrlEx::~CSliCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CSliCtrlEx, CSliderCtrl)
	//{{AFX_MSG_MAP(CSliCtrlEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSliCtrlEx message handlers

void CSliCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl::OnLButtonDown(nFlags, point);

	m_bLBtnDown = TRUE;

	SetThumb(point);

//     CRect mChanRect;       
//     GetChannelRect(&mChanRect);    
// 	
//     int nMin,nMax;       
//     GetRange(nMin,nMax); 
// 	nMax = nMax + 1;
// 
// 	if (point.x >= mChanRect.left && point.x <= mChanRect.right)
// 	{
// 		double dPos = (point.x - mChanRect.left)*(nMax-nMin) * 1.0 /mChanRect.Width();
// 		double dCorrectionFactor = 0.5 *(1-dPos) - 0.5 *dPos;
// 		int nNewPos = (int)(nMin + (nMax-nMin)*dPos + dCorrectionFactor);
// 		if (nNewPos != GetPos())
// 		{
// 			SetPos(nNewPos);
// 		}
// 	}
}

void CSliCtrlEx::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLBtnDown = FALSE;
	CSliderCtrl::OnLButtonUp(nFlags, point);
}

bool CSliCtrlEx::SetThumb(const CPoint& point)
{
	const int nMin = GetRangeMin();
	const int nMax = GetRangeMax()+1;
	CRect rc;
	GetChannelRect(rc);
	double dPos;
	double dCorrectionFactor = 0.0;
	if (GetStyle() & TBS_VERT) 
	{
		// note: there is a bug in GetChannelRect, it gets the orientation of the rectangle mixed up
		dPos = (double)(point.y - rc.left)/(rc.right - rc.left);
	}
	else
	{
		dPos = (double)(point.x - rc.left)/(rc.right - rc.left);
	}
	// This correction factor is needed when you click inbetween tick marks
	// so that the thumb will move to the nearest one
	dCorrectionFactor = 0.5 *(1-dPos) - 0.5 *dPos;
	int nNewPos = (int)(nMin + (nMax-nMin)*dPos + dCorrectionFactor);
	const bool bChanged = (nNewPos != GetPos());
	if(bChanged)
	{
		SetPos(nNewPos);
	}
	return bChanged;
}