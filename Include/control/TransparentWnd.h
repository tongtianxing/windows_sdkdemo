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

	void DrawTransparent(CWnd* pWnd, CDC* pDC);
	void DrawTransparent(CWnd* pWnd, HDC hDC);

protected:
	CDC m_dcBk ;
    CBitmap m_bmpBk ;
    CBitmap*m_bmpBkOld ;
};

#endif // !defined(AFX_TRANSPARENTWND_H__B16B73C1_7B5D_4ABA_87C8_A8BFE07C34DA__INCLUDED_)
