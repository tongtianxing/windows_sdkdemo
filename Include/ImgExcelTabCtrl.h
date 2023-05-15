#pragma once
#include "StateImgBase.h"

enum EImgExcelTabCtrlIdx
{
	IMG_EXCEL_TAB_IDX_BODY,
	IMG_EXCEL_TAB_IDX_DROP,
	IMG_EXCEL_TAB_IDX_BODY_ALARM,
	IMG_EXCEL_TAB_IDX_COUNT
};

class CImgExcelTabCtrl : public CXTPExcelTabCtrl, public CStateImgBase
{
public:
	DECLARE_DYNAMIC(CImgExcelTabCtrl)
	CImgExcelTabCtrl(int nInterval = 0);
	virtual ~CImgExcelTabCtrl();
	virtual BOOL Create(DWORD dwStyle, const CRect& rect, CWnd* pParentWnd, UINT nID);
protected:
	int m_nInterval;
	int m_nTabReservedWidth;
	int m_nTabDropWidth;
public:
	void SetTabInterval(int nInterval);
	void SetTabReservedWidth(int nWidth);
	void SetTabDropWidth(int nWidth);
	void SetTabHeight(int nHeight);

	///////////////////////////////////////////////////////////////////////////////
	// Image
public:
	virtual bool SetStateImg(size_t idx, LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);
private:
	BOOL m_bTabBarVisible;
	COLORREF m_clrAlarmText;
public:
	void SetTabBarVisible(BOOL bVisible) { m_bTabBarVisible = bVisible; RecalcLayout(); }
	void SetAlarmTabTextColor(COLORREF color) { m_clrAlarmText = color; }

	///////////////////////////////////////////////////////////////////////////////
	// Tab
public:
	struct TabMenuEntry {
		CString strCaption;
		CWnd* pWnd;
		int nItem;
		TabMenuEntry(LPCTSTR szC, CWnd* pW, int nItem) : strCaption(szC), pWnd(pW), nItem(nItem) {}
	};
	struct TabInfo {
		CSize sizeCaption;
		CRect rcTab;
		CRect rcDrop;
		bool bSelected;
		bool bFocus;
		bool bFocusDrop;
		bool bDisabled;
		bool bShow;
		bool bMenu;
		bool bAlarm;
		int nSelectedMenuEntry;
		std::set<int> setAlarmRealIndex;
		std::vector<TabMenuEntry> vecMenuEntry;
		TabInfo(CWnd* pWndCtrl = NULL) :
			bSelected(false), bFocus(false), bFocusDrop(false), bDisabled(false), bShow(true), bMenu(false), bAlarm(false), nSelectedMenuEntry(-1) {}
	};
private:
	std::vector<TabInfo> m_vecTabInfo;
	int m_nHighlightIndex;
	virtual int InsertItem(int nItem, UINT nTextID, CWnd* pWndControl = NULL) override { return -1; }
public:
	virtual int InsertItem(int nItem, LPCTSTR szCaption = NULL, CWnd* pWndControl = NULL) override;
	virtual BOOL DeleteItem(int nItem) override;
	virtual BOOL DeleteAllItems();

	virtual int SetCurSel(int nItem) override;
	bool IsTabAlarm(int nItem) const;
	void SetTabAlarm(int nItem, bool bEnabled);
	void AppendTabMenu(int nTabItem, int nItem, LPCTSTR szCaption, CWnd* pWnd);

	virtual BOOL GetItemRect(int nItem, LPRECT lpRect) override;
	virtual int HitTest(TCHITTESTINFO* pHitTestInfo) const override;

	///////////////////////////////////////////////////////////////////////////////
	// Draw
public:
	virtual void RecalcLayout() override;
	// ÏÔÊ¾Òþ²ØÄ³Ïî
	void ShowItem(int nIndex, BOOL bShow = TRUE);
	BOOL IsShowItem(int nIndex) const;
private:
	BOOL m_bHasBorder;
	COLORREF m_clrBorder;
	CSize m_sizeTabPrev;
	int m_nHScrollPos;
public:
	void SetBorderColor(COLORREF clrBorder);
	///////////////////////////////////////////////////////////////////////////////
	// MFC
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuEntry(UINT uMenuID);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	void SetMsgMenuTabChange(int nMsg);

private:
	int m_nMsgMenuTabChange;
};