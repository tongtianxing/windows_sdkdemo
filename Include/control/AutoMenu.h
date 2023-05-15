#pragma once

class CCustomMenu: public CMenu
{
	DECLARE_DYNAMIC(CCustomMenu)

public:
	CCustomMenu();
	~CCustomMenu();

protected:
	HFONT m_hFont;
	COLORREF m_clrItemBk[4];
	COLORREF m_clrItemText[4];
	struct ItemData_T
	{
		// 兼容没有OWNERDRAW的情况
		union
		{
			TCHAR szText[256];
			const CBitmap* pBitmap;
		};
		BOOL bBitmap;
		UINT_PTR nItemID;
		BOOL bPopup;		//弹出式菜单
		COLORREF colorBk;
		COLORREF colorText;
	};
	std::vector<ItemData_T*> m_vecItemData;
	int m_nCheckType;	// 0:disabled 1:radio 2:check


	virtual void DrawItem(LPDRAWITEMSTRUCT lpDS) override;
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) override;

	void DrawCheck(CDC* pDC, const CRect& rcCheck, COLORREF colorBk, COLORREF colorCheck);
	void DrawRadio(CDC* pDC, const CRect& rcCheck, COLORREF colorBk, COLORREF colorCheck);

public:
	BOOL AppendMenu(
		UINT nFlags,
		UINT_PTR nIDNewItem = 0,
		LPCTSTR lpszNewItem = NULL);

	BOOL AppendMenu(
		UINT nFlags,
		UINT_PTR nIDNewItem,
		const CBitmap* pBmp);

	BOOL InsertMenu(
		UINT nPosition,
		UINT nFlags,
		UINT_PTR nIDNewItem = 0,
		LPCTSTR lpszNewItem = NULL);

	BOOL InsertMenu(
		UINT nPosition,
		UINT nFlags,
		UINT_PTR nIDNewItem,
		const CBitmap* pBmp);

	BOOL DeleteMenu(
		UINT nPosition,
		UINT nFlags);

	UINT CheckMenuItem(
		UINT nIDCheckItem,
		UINT nCheck);

	BOOL CheckMenuRadioItem(
		UINT nIDFirst,
		UINT nIDLast,
		UINT nIDItem,
		UINT nFlags);

	void SetColorItemBk(COLORREF color) { m_clrItemBk[0] = color; }
	void SetColorItemBkOver(COLORREF color) { m_clrItemBk[1] = color; }
	void SetColorItemBkHilight(COLORREF color) { m_clrItemBk[2] = color; }
	void SetColorItemBkDisabled(COLORREF color) { m_clrItemBk[3] = color; }
	void SetColorItemText(COLORREF color) { m_clrItemText[0] = color; }
	void SetColorItemTextOver(COLORREF color) { m_clrItemText[1] = color; }
	void SetColorItemTextHilight(COLORREF color) { m_clrItemText[2] = color; }
	void SetColorItemTextDisabled(COLORREF color) { m_clrItemText[3] = color; }
	void SetColorItemBkEx(int nIndex, COLORREF colorBk = -1, COLORREF colorText = -1);
	void CopyMenuColor(const CCustomMenu& other);

	COLORREF GetColorItemBk() const { return m_clrItemBk[0]; }
	COLORREF GetColorItemBkOver() const { return m_clrItemBk[1]; }
	COLORREF GetColorItemBkHilight() const { return m_clrItemBk[2]; }
	COLORREF GetColorItemBkDisabled() const { return m_clrItemBk[3]; }
	COLORREF GetColorItemText() const { return m_clrItemText[0]; }
	COLORREF GetColorItemTextOver() const { return m_clrItemText[1]; }
	COLORREF GetColorItemTextHilight() const { return m_clrItemText[2]; }
	COLORREF GetColorItemTextDisabled() const { return m_clrItemText[3]; }

};

class CAutoPopupMenu
{
public:
	CAutoPopupMenu();
	~CAutoPopupMenu();

public:
	// 增加横线
	void AddSeparatorMenu();
	// 增加灰色无效菜单
	void AddDisableMenu(LPCTSTR lpszTip);
	// 以右键鼠标为准,显示菜单
	void ShowMenu(CWnd* pWnd);
	// 是否为空菜单
	BOOL IsEmpty();
	// 清空菜单
	HMENU Detach();
	// 创建弹出式菜单
	BOOL CreatePopupMenu();
public:
	void InsertMenu(UINT_PTR nIDNewItem, LPCTSTR lpszNewItem);
	void InsertMenuFlag(UINT nOtherFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem);
	void InsertChildMenu(CMenu& ChildMenu, LPCTSTR lpszNewItem);
	void InsertChildMenuAuto(CAutoPopupMenu& ChildMenu, LPCTSTR lpszNewItem);

	BOOL TrackPopupMenu(UINT nFlags, int x, int y, CWnd* pWnd, LPCRECT lpRect = 0);

	void EnableColorMenu(BOOL bEnable);

public:

	CCustomMenu* GetMenu();

	int GetIndex();

	CCustomMenu* operator & ();

private:
	CCustomMenu m_menu;
	int m_nIndex;
	BOOL m_bColorEnable;

	std::vector<CAutoPopupMenu*> m_vecSubMenu;

	HHOOK m_hHookWndProc;
};