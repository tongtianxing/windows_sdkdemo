#pragma once
#include "CxButton.h"

class CCxIconTextButton : public CCxButton
{
	DECLARE_DYNAMIC(CCxIconTextButton)
public:
	CCxIconTextButton();
	virtual ~CCxIconTextButton();

	virtual void PreSubclassWindow();

protected:
	virtual void DrawCaption(HDC hdc, int nImgIdx, const CRect& rc);

private:
	BOOL m_bIconRightAligned;
	int m_nIconLeft;
	int m_nIconTextInterval;
	CImgBase* m_pIconImgState[CX_BTN_STATE];
	int m_nIconBaseDpi[CX_BTN_STATE];
public:
	void SetIconStateImg(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL,
		LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);
	void SetIconRightAligned(BOOL bRight) { m_bIconRightAligned = bRight; }
	void SetIconLeft(int nLeft) { m_nIconLeft = nLeft; }
	void SetIconTextInterval(int nInterval) { m_nIconTextInterval = nInterval; }
	int GetContentWidth(int nImgIdx = IMG_BTN_STATE_NORMAL);

	CString     GetCaption() { return CCxButton::GetCaption(-1); }
	CString     GetCaptionOver() { return CCxButton::GetCaption(IMG_BTN_STATE_OVER); }
};

class CCxIconTextMenuButton : public CCxIconTextButton
{
	DECLARE_DYNAMIC(CCxIconTextMenuButton)
public:
	CCxIconTextMenuButton();
	virtual ~CCxIconTextMenuButton();
	virtual void DoMouseMoveIn();
};

class CCxIconTextLongButton : public CCxIconTextButton
{
	DECLARE_DYNAMIC(CCxIconTextLongButton)
public:
	CCxIconTextLongButton();
	virtual ~CCxIconTextLongButton();
	virtual CCxButton& SetStateImg(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL,
		LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);
};