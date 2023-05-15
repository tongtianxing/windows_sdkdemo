// TransparentWnd.h: interface for the CTransparentWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSPARENTWND_H__B16B73C1_7B5D_4ABA_87C8_A8BFE07C34DA__INCLUDED_)
#define AFX_TRANSPARENTWND_H__B16B73C1_7B5D_4ABA_87C8_A8BFE07C34DA__INCLUDED_

//#pragma  once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTransparentWnd
{
public:
	CTransparentWnd();
	virtual ~CTransparentWnd();

public:
	void SetDisableTransparent(BOOL bDisable = TRUE);
	void SetDisableBkColor(COLORREF clrBk);
	void DrawTransparent(CWnd* pWnd, CDC* pDC, BOOL bHasNC = FALSE, BOOL bBkOnly = FALSE, CPoint* ptTopLeft = NULL);
	void DrawTransparent(CWnd* pWnd, HDC hDC, BOOL bHasNC = FALSE, BOOL bBkOnly = FALSE, CPoint* ptTopLeft = NULL);

protected:
	BOOL m_bIsDisable;
	COLORREF m_clrBk;
	CDC m_dcBk;
	CBitmap m_bmpBk;
	CBitmap*m_bmpBkOld;
	BOOL m_bIncludeNC;
};

#endif // !defined(AFX_TRANSPARENTWND_H__B16B73C1_7B5D_4ABA_87C8_A8BFE07C34DA__INCLUDED_)
