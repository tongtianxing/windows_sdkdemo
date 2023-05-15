#pragma once
#include "CxButton.h"
#include <set>

class CCxButtonPanelSub : public CCxButton
{
	friend class CCxButtonPanel;
private:
	CCxButtonPanelSub() {}
	virtual ~CCxButtonPanelSub() {}

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CPoint ClientToParent(CPoint pt);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

// ��ť��壬�ϸ��հ�ť��ӵ�˳�����
// ����һЩ��ť��Զ�ڱ�İ�ť�ϲ�����������̨���������
class CCxButtonPanel : public CWnd, public CTransparentWnd
{
public:
	CCxButtonPanel();
	virtual ~CCxButtonPanel();

public:
	struct BtnInfo
	{
		CCxButtonPanelSub* pBtn;
		CRect rcRect;
	};
protected:
	std::vector<BtnInfo> m_lstButtons;
	int m_nBtnInfoHilight;
	int m_nBtnInfoOver;
	BOOL m_bIsLButtonDown;
public:
	int GetCount() const { return (int)m_lstButtons.size(); }
	CCxButtonPanelSub* CreateButton(LPCTSTR lpszCaption, DWORD dwStyle, const CRect& rect, UINT nID);

protected:
	virtual void PreSubclassWindow();
	void RedrawButtons(int nBtnBottom = 0);
	virtual void CaptureMouseMove(CPoint inPoint);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnBtnMove(WPARAM pBtn, LPARAM l = 0);
	afx_msg LRESULT OnBtnRedraw(WPARAM w = 0, LPARAM l = 0);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};

// �ֲ㰴ť��壬����������ÿ����ť����Ӧ
// ����һЩ��ť��Զ�ڱ�İ�ť�ϲ�����������̨���������
class CCxButtonPanelLayer : public CCxButtonPanel
{
public:
	CCxButtonPanelLayer();
	virtual ~CCxButtonPanelLayer();

protected:
	std::set<int> m_setLayerKey;
	std::map<int, std::list<int>> m_mapButtonLayer;
private:
	CCxButtonPanelSub* CreateButton(LPCTSTR lpszCaption, DWORD dwStyle, const CRect& rect, UINT nID) { return __super::CreateButton(lpszCaption, dwStyle, rect, nID); }
public:
	CCxButtonPanelSub* CreateButton(int layer, LPCTSTR lpszCaption, DWORD dwStyle, const CRect& rect, UINT nID);

protected:
	virtual void CaptureMouseMove(CPoint inPoint);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};


class CCxButtonPanelPtz : public CCxButtonPanelLayer
{
public:
	CCxButtonPanelPtz();
	virtual ~CCxButtonPanelPtz();

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};