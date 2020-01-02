#if !defined(AFX_XLISTCTRL_H__16DBEFA7_A8BC_48D3_ADE0_FEA7A243ABF4__INCLUDED_)
#define AFX_XLISTCTRL_H__16DBEFA7_A8BC_48D3_ADE0_FEA7A243ABF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XListCtrl.h : header file
//
#define LIST_ITEM_CAR_STATE_NORMAL		0
#define LIST_ITEM_CAR_STATE_ONLINE		1
#define LIST_ITEM_CAR_STATE_OFFLINE		2
#define LIST_ITEM_CAR_STATE_ALARM		3
#define LIST_ITEM_CAR_STATE_CONFIRMED_WARNING	4

#define STR_LIST_ITEM_CAR_STATE_NORMAL		_T("Normal")
#define STR_LIST_ITEM_CAR_STATE_ONLINE		_T("Online")
#define STR_LIST_ITEM_CAR_STATE_OFFLINE		_T("Offline")
#define STR_LIST_ITEM_CAR_STATE_ALARM		_T("Warning")
#define STR_LIST_ITEM_CAR_STATE_CONFIRMED_WARNING	_T("ConfirmedWarning")

// 数字格式化,用来排序列表中的数字
#define LVIF_NUMBER_FORMAT		0x01000000
// 获取提示信息
#define LVIF_CUSTOM_TIP			0x02000000


#define COLUMN_DATA_VALUE_DATA		(-2)		//数据列属性,默认值
#define COLUMN_DATA_VALUE_STATUS	(-3)		//状态列属性,默认值

class CSortHeaderCtrl : public CHeaderCtrl
{
	// Construction
public:
	CSortHeaderCtrl();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortHeaderCtrl)
public:
	virtual void Serialize(CArchive& ar);
	afx_msg void OnPaint();

	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CSortHeaderCtrl();
	
	void SetSortArrow( const int iColumn, const BOOL bAscending );
	void SetHeadColor(const COLORREF& colorStart, const COLORREF& colorEnd);
	void SetHeadColorFocus(const COLORREF& colorStart, const COLORREF& colorEnd);



	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );

	void DrawCheckbox(int nCol, HDC hDC, CRect& rect, int nCheck);

	void SetShowCheck(BOOL bShow);
	BOOL GetShowCheck();
	void SetCheck(BOOL bCheck);
	BOOL GetCheck();
// 	int m_R;
// 	int m_G;
// 	int m_B;
//	int m_Gradient;	// 画立体背景，渐变系数
	float m_Height;  //表头高度，这是倍数,
	int m_fontHeight; //字体高度
	int m_fontWith;   //字体宽度
	COLORREF m_color;


	CStringArray m_HChar;
	CString m_Format; //表示对齐类型的整型数组,0表示左对齐，1表示中间对齐，2表示右对齐

	HBRUSH m_hBrush1;
	HBRUSH m_hBrush2;
	// Generated message map functions
protected:
//	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	
	int m_iSortColumn;
	BOOL m_bSortAscending;
	COLORREF m_colorStart;
	COLORREF m_colorEnd;	//表头渐变颜色
	COLORREF m_colorStart1;
	COLORREF m_colorEnd1;	//表头选择后的渐变颜色
	
	HBRUSH m_hBrushCheckbox1;
	HBRUSH m_hBrushCheckbox2;
	
	// 增加CheckBox框,暂仅支持第0列
	BOOL m_bShowCheckBox;
	BOOL m_bCheckState;
	//{{AFX_MSG(CSortHeaderCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CXListCtrl window
class CXListCtrl : public CListCtrl
{
// Construction

private:
	typedef std::map<CString, COLORREF> mapColor;
	typedef mapColor::iterator mapColorIter;

	typedef std::map<CString, HBRUSH> mapHBRUSH;
	typedef mapHBRUSH::iterator mapHBRUSHIter;

	typedef BOOL (CALLBACK* FUNClickColumnCB)(HWND hwnd, int nColumn, BOOL bSortAscending, void* pUsr);

	typedef int (CALLBACK* FUNCSortColumnCB)(int nColumnIndex, BOOL bSortAscending, int nItem1, int nItem2, void* pUsr);
public:
	CXListCtrl();

// Attributes

public:
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXListCtrl)
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXListCtrl();

	// Generated message map functions
public:
	//{{AFX_MSG(CXListCtrl)
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	virtual void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL	EnableTips(BOOL bEnable=TRUE);
	static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
	int		DoCompare(LPARAM lParam1, LPARAM lParam2);
	void	Sort( int iColumn, BOOL bAscending );
	void	Sort();
	bool	IsNumber( LPCTSTR pszText );
	int		NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 );
	bool	IsDate( LPCTSTR pszText );
	int		DateCompare( const CString& strDate1, const CString& strDate2 );

	bool FindColColor(int col ,COLORREF &color); //查找列颜色
	bool FindItemColor(int col,int row,COLORREF &color);
	HBRUSH FindItemHbrush(int row);
 	bool FindColTextColor(int col,COLORREF &color); //查找列字体颜色
 	bool FindItemTextColor(int col,int row,COLORREF &color);

	// 增加参数dwData:列的属性数据 [2017-7-25 ydl]
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1, DWORD dwData = 0);

	void SetVirtualColumnClick(void* pUsr, FUNClickColumnCB pfnClickColumnCB);

	void SetCustomSort(void* pUsr, FUNCSortColumnCB pfnSortColumnCB);

	BOOL SetHeadItemData(int nColumn, DWORD dwData);
	DWORD GetHeadItemData(int nColumn);
public:
	void SetColor(const CString& strKey, COLORREF color);
	COLORREF GetColor(const CString& strKey);
	HBRUSH GetColorHbrush(const CString& strKey);
	void	SetExcelStyle(BOOL bExcelStyle) {	m_bExcelStyle = bExcelStyle; }
//	void	SetColor(COLORREF clrWarn, COLORREF clrNormal);
	void	SetItemDataEx(int nIndex, long nData);
	long	GetItemDataEx(int nIndex);
	void	SetExternItem(int nDataItem, int nStatusItem);
 	void	SetItemWarning(int nIndex, BOOL bWarning);
 	void    SetItemConfirmedWarning(int nIndex);
	void	SetItemCarState(int nIndex, int nCarState);
	int		GetItemCarState(int nIndex);
	void	SortItem();

	// 每行的背景颜色
	void	SetItemBKColor(COLORREF color1, COLORREF color2);
	// 字颜色
	void	SetItemTextColor(COLORREF color);
	//背景颜色
	//void	SetListBKColor(COLORREF color);
	//item背景颜色
	void	SetItemBKColorFocus(COLORREF color);
	//checkbox颜色
	void	SetCheckBoxColor(COLORREF color1, COLORREF color2);
	//xlist列表头
	//是否排序
	void	SetSortEnable(BOOL bSort=FALSE);
	//头的颜色
	void	SetHeadCtrlBKColor(const COLORREF& colorStart, const COLORREF& colorEnd);
	//头焦点状态颜色
	void	SetHeadCtrlBKColorFocus(const COLORREF& colorStart, const COLORREF& colorEnd);
	//头字体颜色
	void	SetHeadCtrlTextColor(const COLORREF& color);


	virtual BOOL GetCheckEx(int nItem)	{ return GetCheck(nItem); }
	virtual BOOL SetCheckEx(int nItem, BOOL bCheck)	{ return SetCheck(nItem, bCheck); }

	//设置此列显示自定义颜色,颜色数据保存在此列
	void	SetColumnCustomColor(int nColumn);

	//获取tip显示的字符串,默认显示单元格里面的内容
	virtual void GetTipText(int nItem, int nSubItem, LPTSTR lpszText, int nLen);
	
	// 点是否在checkbox区域内
	BOOL PtInChkRect(int nItem, POINT pt);

	void SetHeadCtrlShowCheck(BOOL bShow = TRUE);
	BOOL GetHeadCtrlShowCheck();
	void SetHeadCtrlCheck(BOOL bCheck);
	BOOL GetHeadCtrlCheck();
private:
	void DrawCheckbox(int nItem, int nSubItem, HDC hDC, COLORREF crText, COLORREF crBkgnd, CRect& rect, int nCheck, CSize& size);
	void FillSolidRectEx(HDC hDC, CRect& rect, COLORREF clr);
	BOOL CreateToolTips();

	BOOL IsCustomColor(int nColumn);
	int GetCustomColor(int nItem, int nSubItem, BOOL bIsCustom);
	int FormatColorString2Int(LPCTSTR lpszColor);

	void OnKeyCtrlC();
	void OnKeyCtrlA();
	void OnKeyCtrlSpace();
protected:
	mapColor m_mapColor;
	mapHBRUSH m_mapHBRUSH;

	CSortHeaderCtrl m_ctlHeader;
	int		m_iNumColumns;
	int		m_iSortColumn;
	BOOL	m_bSortAscending;
	int		m_nDataItem;
	int		m_nStatusItem;
	BOOL	m_bExcelStyle;
	int		m_nRowHeight;

	CToolTipCtrl	m_toolTip;
	int m_nItem;		// 鼠标所在的行
	int m_nSubItem;		// 鼠标所在的列
	BOOL m_bEnableTips; // 
	BOOL m_bSort;

	HBRUSH m_hBrushBK;
	HBRUSH m_hBrushText;
//	HBRUSH m_hBrushBkColor;
	HBRUSH m_hBrushItem;
	HBRUSH m_hBrushItem1;
	HBRUSH m_hBrushCheckbox1;
	HBRUSH m_hBrushCheckbox2;

	void* m_pUsrClickColumn;
	FUNClickColumnCB m_pfnClickColumnCB;

	std::map<int, int> m_mapColorColumn;	//颜色列,此列保存为颜色RGB整数值

	// 自定义排序规则,优先判断自定义规则
	void* m_pUsrSortColumn;
	FUNCSortColumnCB m_pfnSortColumnCB;

	int m_HotKeyCtrlSE;

	CWnd* m_pWndAttribute;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XLISTCTRL_H__16DBEFA7_A8BC_48D3_ADE0_FEA7A243ABF4__INCLUDED_)
