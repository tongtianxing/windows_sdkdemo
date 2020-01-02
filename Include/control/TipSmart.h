// TipSmart.h: interface for the CTipSmart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIPSMART_H__7D727E66_A20A_4A41_8365_A0747B06A3A8__INCLUDED_)
#define AFX_TIPSMART_H__7D727E66_A20A_4A41_8365_A0747B06A3A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTipSmart  
{
public:
	CTipSmart();
	virtual ~CTipSmart();

	void Init(CWnd* pParentWnd);
	BOOL RelayEvent(MSG* pMsg);
	void AddTool(CWnd * pWnd, LPCTSTR lpszString = NULL);

protected:
	CPPToolTip	m_TTipCtrl;
	CWnd* m_pParentWnd;
};

#endif // !defined(AFX_TIPSMART_H__7D727E66_A20A_4A41_8365_A0747B06A3A8__INCLUDED_)
