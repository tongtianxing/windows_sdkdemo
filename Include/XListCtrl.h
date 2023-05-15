
#pragma once
#include "StateImgBase.h"
#include "PPToolTip/PPTooltip.h"

//
#define LIST_ITEM_CAR_STATE_NORMAL		0
#define LIST_ITEM_CAR_STATE_ONLINE		1
#define LIST_ITEM_CAR_STATE_OFFLINE		2
#define LIST_ITEM_CAR_STATE_ALARM		3
#define LIST_ITEM_CAR_STATE_CONFIRMED_WARNING	4
#define LIST_ITEM_CAR_STATE_ALARM_HANDLED	5

#define STR_LIST_ITEM_CAR_STATE_NORMAL		_T("Normal")
#define STR_LIST_ITEM_CAR_STATE_ONLINE		_T("Online")
#define STR_LIST_ITEM_CAR_STATE_OFFLINE		_T("Offline")
#define STR_LIST_ITEM_CAR_STATE_ALARM		_T("Warning")
#define STR_LIST_ITEM_CAR_STATE_CONFIRMED_WARNING	_T("ConfirmedWarning")
#define STR_LIST_ITEM_CAR_STATE_ALARM_HANDLED	_T("Handled")
#define STR_LIST_ITEM_CAR_STATE_HEAVY_VEHICLE	_T("HeavyVehicle")

// 数字格式化,用来排序列表中的数字
#define LVIF_NUMBER_FORMAT		0x01000000
// 获取提示信息
#define LVIF_CUSTOM_TIP			0x02000000


#define COLUMN_DATA_VALUE_DATA		(-2)		//数据列属性,默认值
#define COLUMN_DATA_VALUE_STATUS	(-3)		//状态列属性,默认值

typedef struct _tagSortHeaderData
{
	int     nWidth;			//默认宽度
	TCHAR	szText[128];	//文本
	int     nTextFormat;	//文本方向,DT_LEFT
	LPARAM  lParam;			//绑定列参数

}SortHeaderData_S;

class CSortHeaderCtrl : public CHeaderCtrl
{
	// Construction
public:
	CSortHeaderCtrl();
	virtual ~CSortHeaderCtrl();

protected:
	virtual void Serialize(CArchive& ar);

	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	DECLARE_MESSAGE_MAP()

public:
	void SetSortArrow(const int iColumn, const BOOL bAscending);
	void SetHeadColor(const COLORREF& colorStart, const COLORREF& colorEnd);
	void SetHeadColorFocus(const COLORREF& colorStart, const COLORREF& colorEnd);
	void SetHeadColorVoid(const COLORREF& colorStart, const COLORREF& colorEnd);



	LRESULT OnLayout(WPARAM wParam, LPARAM lParam);

	void DrawCheckbox(int nCol, HDC hDC, CRect& rect, int nCheck);
	void DrawImgCheckbox(int nCol, HDC hDC, CRect& rect, int nCheck, BOOL bHilight);

	void SetShowCheck(BOOL bShow);
	BOOL GetShowCheck();
	void SetCheck(BOOL bCheck);
	BOOL GetCheck();

	BOOL IsShowIndex() const { return m_bIsShowIndex; }
	void SetShowIndex(BOOL val) { m_bIsShowIndex = val; }

	void InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat, int nWidth, LPARAM lData = 0);
	void DeleteColumn(int nCol);
	BOOL DeleteAllColumns();


	BOOL SetHeadItemData(int nColumn, LPARAM lData);
	LPARAM GetHeadItemData(int nColumn);

	// 根据列绑定数据搜索索引,失败返回-1
	int FindHeadItemByData(LPARAM lData);
	int FindHeadInsertIndexByData(LPARAM lData);

	UINT GetFormat(int nCol);

	void SetTextColor(COLORREF clr);

	CString GetText(int nIndex);
	int GetCount();

	void BackupData();
	std::vector<SortHeaderData_S> GetSortHeaderData() const;

	BOOL SetHeadItemWidth(int nColumn, int nWidth);
	int GetHeadItemWidth(int nColumn);

	BOOL SetHeadItemBakWidth(int nColumn, int nWidth);

	// 文字垂直居中
	BOOL IsTextVCenter() const { return m_bIsTextVCenter; }
	void SetTextVCenter(BOOL val) { m_bIsTextVCenter = val; }

	// 图片复选框
	void SetStateImgCheckBox(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL,
		LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);

	// 表头高度
	void SetHeight(int nItemHeight) { m_nHeight = nItemHeight; }
	int GetHeight() const { return m_nHeight; }
	void SetDefaultHeight(int nItemHeight) { m_nDefaultHeight = nItemHeight; }
	int GetDefaultHeight() const { return m_nDefaultHeight; }
	void SetBorder(COLORREF crBorder, int nBorderHeight);

	// 表头分割线
	// 0:关闭 1:全高度（旧风格） 2:上下留白8px
	void SetGridline(int nStyle, COLORREF crGridline = RGB(166, 166, 166));

protected:
	// 	int m_R;
	// 	int m_G;
	// 	int m_B;
	//	int m_Gradient;	// 画立体背景，渐变系数
	int m_nHeight;  //表头高度
	int m_nDefaultHeight; //没有设置表头高度时的高度
	int m_fontHeight; //字体高度
	int m_fontWith;   //字体宽度
	COLORREF m_color;

	//CMutexLock m_lockAttr;
	//std::map<int, SortHeaderData_S> m_mapAttr;
	//CPtrArray m_ptrArrAttr;
	std::vector<SortHeaderData_S> m_vecHeaderData;
	std::vector<SortHeaderData_S> m_vecHeaderDataBak;
	//CStringArray m_strArrText;	//列的文本
	//CPtrArray m_ptrArrData;		//列的属性
	//CUIntArray m_uiArrFormat;	//表示对齐类型的整型数组,0表示左对齐，1表示中间对齐，2表示右对齐

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
	COLORREF m_colorVoidStart;
	COLORREF m_colorVoidEnd;	//表头右边没有内容的渐变颜色

	HBRUSH m_hBrushCheckbox1;
	HBRUSH m_hBrushCheckbox2;

	// 增加CheckBox框,暂仅支持第0列
	BOOL m_bShowCheckBox;
	BOOL m_bCheckState;

	// 是否在列上增加编号
	BOOL m_bIsShowIndex;

	// 文字是否垂直居中
	BOOL m_bIsTextVCenter;

	BOOL m_bHasImgCheckbox;
	BOOL m_bCheckHighlight;
	CImgBase* m_pImgCheckBox[IMG_BTN_STATE_COUNT];
	int m_nCheckBoxBaseDpi[IMG_BTN_STATE_COUNT];

	int m_nBorderHeight;
	COLORREF m_colorBorder;

	int m_nGridlineStyle;	// 0:关闭 1:全高度（旧风格） 2:上下留白8px
};

/////////////////////////////////////////////////////////////////////////////
// CXListCtrl window
class CXListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CXListCtrl)

	// Construction

private:
	typedef std::map<CString, COLORREF> mapColor;
	typedef mapColor::iterator mapColorIter;

	typedef std::map<CString, HBRUSH> mapHBRUSH;
	typedef mapHBRUSH::iterator mapHBRUSHIter;

	typedef BOOL(CALLBACK* FUNClickColumnCB)(HWND hwnd, int nColumn, BOOL bSortAscending, void* pUsr);

	typedef int (CALLBACK* FUNCSortColumnCB)(int nColumnIndex, BOOL bSortAscending, LPARAM lParam1, LPARAM lParam2, void* pUsr);

	typedef void (CALLBACK* FUNCKeyDownF5)(void* pUsr);
public:
	CXListCtrl();
	virtual ~CXListCtrl();

protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnKeyDown(NMHDR *pNMHDR, LRESULT *pResult);
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//	virtual void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()

public:
	CSortHeaderCtrl* GetSortHeaderCtrl();
	CToolTipCtrl*	GetToolTipCtrl();

	BOOL	EnableTips(BOOL bEnable = TRUE);
	static int CALLBACK CompareFunction(LPARAM lParam1, LPARAM lParam2, LPARAM lParamData);
	int		DoCompare(LPARAM lParam1, LPARAM lParam2);
	void	Sort(int iColumn, BOOL bAscending);
	void	Sort();
	bool	IsNumber(LPCTSTR pszText);
	int		NumberCompare(LPCTSTR pszNumber1, LPCTSTR pszNumber2);
	bool	IsDate(LPCTSTR pszText);
	int		DateCompare(const CString& strDate1, const CString& strDate2);

	bool FindColColor(int col, COLORREF &color); //查找列颜色
	bool FindItemColor(int col, int row, COLORREF &color);
	HBRUSH FindItemHbrush(int row);
	bool FindColTextColor(int col, COLORREF &color); //查找列字体颜色
	bool FindItemTextColor(int col, int row, COLORREF &color);
	// 设置某个单元格的文本颜色
	void SetItemTextColor(int col, int row, COLORREF color);

	// 设置某个单元格的鼠标手类型(使用系统资源)
	void SetItemMouseType(int col, int row, int nResID = 32649);

	// 设置某个单元格的字体(上层释放对象)
	void SetItemTextFont(int col, int row, HFONT hFont);
	HFONT GetItemTextFont(int col, int row, BOOL bNonNull = FALSE);

	// 增加参数dwData:列的属性数据 [2017-7-25 ydl]
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1, LPARAM dwData = 0);

	BOOL DeleteColumn(int nCol);
	BOOL DeleteAllColumns();

	void SetVirtualColumnClick(void* pUsr, FUNClickColumnCB pfnClickColumnCB);

	// 回调函数返回-1,0,1时有效，其他参数按默认排序处理
	void SetCustomSort(void* pUsr, FUNCSortColumnCB pfnSortColumnCB);

	BOOL SetHeadItemData(int nColumn, LPARAM lData);
	LPARAM GetHeadItemData(int nColumn);

	// 根据列绑定数据搜索索引,失败返回-1
	int FindHeadItemByData(LPARAM lData);
	int FindHeadInsertIndexByData(LPARAM lData);

	// 获取列的数量
	int GetHeadItemCount();

	BOOL IsShowColumnIndex() const;
	void SetShowColumnIndex(BOOL val);

	void UpdateItemHeight();
public:
	void SetColor(const CString& strKey, COLORREF color);
	COLORREF GetColor(const CString& strKey);
	HBRUSH GetColorHbrush(const CString& strKey);
	void	SetExcelStyle(BOOL bExcelStyle) { m_bExcelStyle = bExcelStyle; }
	//	void	SetColor(COLORREF clrWarn, COLORREF clrNormal);

	void	SetItemDataEx(int nIndex, LPARAM lData);
	LPARAM	GetItemDataEx(int nIndex);

	void	SetItemDataPtrEx(int nIndex, void* pData);
	void*	GetItemDataPtrEx(int nIndex);

	void	SetItemStatus(int nIndex, LPCTSTR lpszStatus);
	CString GetItemStatus(int nIndex);

	void	SetExternItem(int nDataItem, int nStatusItem);
	void	GetExternItem(int& nDataItem, int& nStatusItem);
	BOOL	IsExternItem(int nItem);
	void	SetItemWarning(int nIndex, BOOL bWarning);
	void    SetItemConfirmedWarning(int nIndex);
	void	SetItemCarState(int nIndex, int nCarState);
	int		GetItemCarState(int nIndex);
	void	SortItem();

	// 每行的背景颜色
	void	SetItemBKColor(COLORREF color1, COLORREF color2);
	// 字颜色
	void	SetItemTextColor(COLORREF color);
	void	SetHilightTextColor(COLORREF color);
	//背景颜色
	//void	SetListBKColor(COLORREF color);
	//item焦点行背景颜色
	void	SetItemBKColorFocus(COLORREF color, BOOL bIsTextXOR = TRUE);
	//checkbox颜色
	void	SetCheckBoxColor(COLORREF color1, COLORREF color2);
	//xlist列表头
	//是否排序
	void	SetSortEnable(BOOL bSort = FALSE);
	//头的颜色
	void	SetHeadCtrlBKColor(const COLORREF& colorStart, const COLORREF& colorEnd);
	//头焦点状态颜色
	void	SetHeadCtrlBKColorFocus(const COLORREF& colorStart, const COLORREF& colorEnd);
	//头右边无内容颜色
	void	SetHeadCtrlBKColorVoid(const COLORREF& colorStart, const COLORREF& colorEnd);
	//头字体颜色
	void	SetHeadCtrlTextColor(const COLORREF& color);
	//头上下边框
	void	SetHeadCtrlBorder(const COLORREF& color, int nHeight = 1);
	//头列间分割线
	// 0:关闭 1:全高度（旧风格） 2:上下留白8px
	void	SetHeadCtrlGridline(int nStyle, const COLORREF& color = RGB(166, 166, 166));


	virtual BOOL GetCheckEx(int nItem) { return GetCheck(nItem); }
	virtual BOOL SetCheckEx(int nItem, BOOL bCheck) { return SetCheck(nItem, bCheck); }

	// 点击带有复选框的列
	virtual void OnHeadColumnClick(int nHeadItem);
	// 检查并排序指定列
	void DoColumnClickSort(int iColumn);

	//设置此列显示自定义颜色,颜色数据保存在此列
	void	SetColumnCustomColor(int nColumn);

	//获取tip显示的字符串,默认显示单元格里面的内容
	CString GetCurTipText();

	// 点是否在checkbox区域内
	BOOL PtInChkRect(int nItem, POINT pt);

	void SetHeadCtrlShowCheck(BOOL bShow = TRUE);
	BOOL GetHeadCtrlShowCheck();
	void SetHeadCtrlCheck(BOOL bCheck);
	BOOL GetHeadCtrlCheck();

	// 选中行是否用文本色作为背景色,默认为TRUE
	BOOL IsTextColorAsBKColor() const;
	void SetTextColorAsBKColor(BOOL bTextColorAsBKColor);

	int GetTipMaxChars() const;
	void SetTipMaxChars(int nTipMaxChars);

	// 删除所有选择项
	void DeleteAllSelectItems();

	// 设置右键点击的格子,用来复制数据使用
	void SetRClickInfo(int nItem, int nColumn);
	void SetRClickInfo(LPNMITEMACTIVATE pNMItemActivate);

	// 复制当前鼠标所在的单元格
	BOOL CopyGridData();
	BOOL CopyGridData(int nItem, int nColumn);
	// 复制当前鼠标所在行的数据(一行)
	BOOL CopyLineData();
	BOOL CopyLineData(int nItem);
	// 复制当前鼠标所在列的数据(一列)
	BOOL CopyColumnData();
	BOOL CopyColumnData(int nColumn);
	// 复制整个表的数据
	BOOL CopyAllData();

	void SetFUNCKeyDownF5(FUNCKeyDownF5 pfnKeyDownF5, void* pUsr);

	// 增加数据列和状态列,带属性,nIndex会+2
	void InsertDataAndStatusColumn(int& nIndex);

	// 列的序号发生变化,如插入/删除列,需要重新计算状态列的索引
	void RefreshDataAndStatusColumn();

	// 项高度,外部调用DPI转换
	void SetItemHeight(int nItemHeight);
	int GetItemHeight() const;
	void SetHeaderHeight(int nItemHeight);
	int GetHeaderHeight() const;
	void SetDefaultHeaderHeight(int nItemHeight);
	int GetDefaultHeaderHeight() const;


	void SetResizeColumn(int nResizeColumn);
	void SetResizeColumn2(int nResizeColumn1, int nResizeColumn2);
	int GetResizeColumn() const;
	int GetResizeColumn2() const;

	void ColumnResize();

	// 设置冒号字符串(最长10个字符)
	void SetCopyColon(LPCTSTR lpszColon);
	CString GetCopyColon();

	// 文字垂直居中
	BOOL IsTextVCenter() const { return m_bIsTextVCenter; }
	void SetTextVCenter(BOOL val) { m_bIsTextVCenter = val; }
	BOOL IsHeaderTextVCenter() const { return m_ctlHeader.IsTextVCenter(); }
	void SetHeaderTextVCenter(BOOL val) { m_ctlHeader.SetTextVCenter(val); }

	// 图片复选框
	void SetStateImgCheckBox(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL,
		LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);

	// 自定义网格线
	void SetGridline(BOOL bHorizontal, BOOL bVertical, COLORREF color = RGB(240, 240, 240));

private:
	void DrawCheckbox(int nItem, int nSubItem, HDC hDC, COLORREF crText, COLORREF crBkgnd, CRect& rect, int nCheck, CSize& size);
	void DrawImgCheckbox(int nItem, int nSubItem, HDC hDC, COLORREF crText, COLORREF crBkgnd, CRect& rect, int nCheck, int nHilight, CSize& sizeImg);
	void FillSolidRectEx(HDC hDC, CRect& rect, COLORREF clr);
	BOOL CreateToolTips();

	BOOL IsCustomColor(int nColumn);
	int GetCustomColor(int nItem, int nSubItem, BOOL bIsCustom);
	int FormatColorString2Int(LPCTSTR lpszColor);

	void OnKeyCtrlC();
	void OnKeyCtrlA();
	void OnKeyCtrlSpace();

	void CBKeyDownF5();

	CString GetKey(int col, int row);
protected:
	mapColor m_mapColor;
	std::map<CString, int> m_mapMouseType;
	std::map<CString, HFONT> m_mapFont;
	mapHBRUSH m_mapHBRUSH;

	CSortHeaderCtrl m_ctlHeader;
	int		m_iNumColumns;
	int		m_iSortColumn;
	BOOL	m_bSortAscending;
	int		m_nDataItem;
	int		m_nStatusItem;
	BOOL	m_bExcelStyle;
	int		m_nRowHeight;
	CString m_strCopyColon;	//冒号

	CPPToolTip	m_toolTip;
	int m_nItem;		// 鼠标所在的行
	int m_nSubItem;		// 鼠标所在的列
	BOOL m_bEnableTips; // 
	BOOL m_bSort;

	HBRUSH m_hBrushBK;
	HBRUSH m_hBrushText;
	COLORREF m_clrText;
	COLORREF m_clrHilightText;
	BOOL m_bHasHilightTextColor;
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

	// 选中行:文本颜色当做背景色
	BOOL m_bTextColorAsBKColor;

	// 提示信息显示的最大字符数,默认为256,最大应不超过10240
	int m_nTipMaxChars;

	// 焦点行颜色是否改变(暂定为黑色文字变白色文字)
	BOOL m_bIsTextXOR;

	// 右键点击的位置,用来复制数据使用
	int m_nRClickItem;
	int m_nRClickColumn;

	// 回调函数,当用户按下F5时
	FUNCKeyDownF5 m_pfnKeyDownF5;
	void* m_pUsrKeyDownF5;

	// 单项高度,默认为22
	int m_nItemHeight;

	// 对齐的最大宽度
	int m_nMaxResizeWidth;
	// 对齐列
	int m_nResizeColumn;
	int m_nResizeColumn2;
	BOOL m_bIsResizeColumnData;

	// 文字是否垂直居中
	BOOL m_bIsTextVCenter;

	BOOL m_bHasImgCheckbox;
	int m_nCheckHighlight;
	CImgBase* m_pImgCheckBox[IMG_BTN_STATE_COUNT];
	int m_nCheckBoxBaseDpi[IMG_BTN_STATE_COUNT];
	int m_nCheckboxWidth;

	// 自定义网格线
	BOOL m_bGridlineH;
	BOOL m_bGridlineV;
	COLORREF m_crGridline;
};

