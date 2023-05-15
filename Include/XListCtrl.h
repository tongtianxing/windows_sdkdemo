
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

// ���ָ�ʽ��,���������б��е�����
#define LVIF_NUMBER_FORMAT		0x01000000
// ��ȡ��ʾ��Ϣ
#define LVIF_CUSTOM_TIP			0x02000000


#define COLUMN_DATA_VALUE_DATA		(-2)		//����������,Ĭ��ֵ
#define COLUMN_DATA_VALUE_STATUS	(-3)		//״̬������,Ĭ��ֵ

typedef struct _tagSortHeaderData
{
	int     nWidth;			//Ĭ�Ͽ��
	TCHAR	szText[128];	//�ı�
	int     nTextFormat;	//�ı�����,DT_LEFT
	LPARAM  lParam;			//���в���

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

	// �����а�������������,ʧ�ܷ���-1
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

	// ���ִ�ֱ����
	BOOL IsTextVCenter() const { return m_bIsTextVCenter; }
	void SetTextVCenter(BOOL val) { m_bIsTextVCenter = val; }

	// ͼƬ��ѡ��
	void SetStateImgCheckBox(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL,
		LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);

	// ��ͷ�߶�
	void SetHeight(int nItemHeight) { m_nHeight = nItemHeight; }
	int GetHeight() const { return m_nHeight; }
	void SetDefaultHeight(int nItemHeight) { m_nDefaultHeight = nItemHeight; }
	int GetDefaultHeight() const { return m_nDefaultHeight; }
	void SetBorder(COLORREF crBorder, int nBorderHeight);

	// ��ͷ�ָ���
	// 0:�ر� 1:ȫ�߶ȣ��ɷ�� 2:��������8px
	void SetGridline(int nStyle, COLORREF crGridline = RGB(166, 166, 166));

protected:
	// 	int m_R;
	// 	int m_G;
	// 	int m_B;
	//	int m_Gradient;	// �����屳��������ϵ��
	int m_nHeight;  //��ͷ�߶�
	int m_nDefaultHeight; //û�����ñ�ͷ�߶�ʱ�ĸ߶�
	int m_fontHeight; //����߶�
	int m_fontWith;   //������
	COLORREF m_color;

	//CMutexLock m_lockAttr;
	//std::map<int, SortHeaderData_S> m_mapAttr;
	//CPtrArray m_ptrArrAttr;
	std::vector<SortHeaderData_S> m_vecHeaderData;
	std::vector<SortHeaderData_S> m_vecHeaderDataBak;
	//CStringArray m_strArrText;	//�е��ı�
	//CPtrArray m_ptrArrData;		//�е�����
	//CUIntArray m_uiArrFormat;	//��ʾ�������͵���������,0��ʾ����룬1��ʾ�м���룬2��ʾ�Ҷ���

	HBRUSH m_hBrush1;
	HBRUSH m_hBrush2;
	// Generated message map functions
protected:
	//	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );

	int m_iSortColumn;
	BOOL m_bSortAscending;
	COLORREF m_colorStart;
	COLORREF m_colorEnd;	//��ͷ������ɫ
	COLORREF m_colorStart1;
	COLORREF m_colorEnd1;	//��ͷѡ���Ľ�����ɫ
	COLORREF m_colorVoidStart;
	COLORREF m_colorVoidEnd;	//��ͷ�ұ�û�����ݵĽ�����ɫ

	HBRUSH m_hBrushCheckbox1;
	HBRUSH m_hBrushCheckbox2;

	// ����CheckBox��,�ݽ�֧�ֵ�0��
	BOOL m_bShowCheckBox;
	BOOL m_bCheckState;

	// �Ƿ����������ӱ��
	BOOL m_bIsShowIndex;

	// �����Ƿ�ֱ����
	BOOL m_bIsTextVCenter;

	BOOL m_bHasImgCheckbox;
	BOOL m_bCheckHighlight;
	CImgBase* m_pImgCheckBox[IMG_BTN_STATE_COUNT];
	int m_nCheckBoxBaseDpi[IMG_BTN_STATE_COUNT];

	int m_nBorderHeight;
	COLORREF m_colorBorder;

	int m_nGridlineStyle;	// 0:�ر� 1:ȫ�߶ȣ��ɷ�� 2:��������8px
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

	bool FindColColor(int col, COLORREF &color); //��������ɫ
	bool FindItemColor(int col, int row, COLORREF &color);
	HBRUSH FindItemHbrush(int row);
	bool FindColTextColor(int col, COLORREF &color); //������������ɫ
	bool FindItemTextColor(int col, int row, COLORREF &color);
	// ����ĳ����Ԫ����ı���ɫ
	void SetItemTextColor(int col, int row, COLORREF color);

	// ����ĳ����Ԫ������������(ʹ��ϵͳ��Դ)
	void SetItemMouseType(int col, int row, int nResID = 32649);

	// ����ĳ����Ԫ�������(�ϲ��ͷŶ���)
	void SetItemTextFont(int col, int row, HFONT hFont);
	HFONT GetItemTextFont(int col, int row, BOOL bNonNull = FALSE);

	// ���Ӳ���dwData:�е��������� [2017-7-25 ydl]
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1, LPARAM dwData = 0);

	BOOL DeleteColumn(int nCol);
	BOOL DeleteAllColumns();

	void SetVirtualColumnClick(void* pUsr, FUNClickColumnCB pfnClickColumnCB);

	// �ص���������-1,0,1ʱ��Ч������������Ĭ��������
	void SetCustomSort(void* pUsr, FUNCSortColumnCB pfnSortColumnCB);

	BOOL SetHeadItemData(int nColumn, LPARAM lData);
	LPARAM GetHeadItemData(int nColumn);

	// �����а�������������,ʧ�ܷ���-1
	int FindHeadItemByData(LPARAM lData);
	int FindHeadInsertIndexByData(LPARAM lData);

	// ��ȡ�е�����
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

	// ÿ�еı�����ɫ
	void	SetItemBKColor(COLORREF color1, COLORREF color2);
	// ����ɫ
	void	SetItemTextColor(COLORREF color);
	void	SetHilightTextColor(COLORREF color);
	//������ɫ
	//void	SetListBKColor(COLORREF color);
	//item�����б�����ɫ
	void	SetItemBKColorFocus(COLORREF color, BOOL bIsTextXOR = TRUE);
	//checkbox��ɫ
	void	SetCheckBoxColor(COLORREF color1, COLORREF color2);
	//xlist�б�ͷ
	//�Ƿ�����
	void	SetSortEnable(BOOL bSort = FALSE);
	//ͷ����ɫ
	void	SetHeadCtrlBKColor(const COLORREF& colorStart, const COLORREF& colorEnd);
	//ͷ����״̬��ɫ
	void	SetHeadCtrlBKColorFocus(const COLORREF& colorStart, const COLORREF& colorEnd);
	//ͷ�ұ���������ɫ
	void	SetHeadCtrlBKColorVoid(const COLORREF& colorStart, const COLORREF& colorEnd);
	//ͷ������ɫ
	void	SetHeadCtrlTextColor(const COLORREF& color);
	//ͷ���±߿�
	void	SetHeadCtrlBorder(const COLORREF& color, int nHeight = 1);
	//ͷ�м�ָ���
	// 0:�ر� 1:ȫ�߶ȣ��ɷ�� 2:��������8px
	void	SetHeadCtrlGridline(int nStyle, const COLORREF& color = RGB(166, 166, 166));


	virtual BOOL GetCheckEx(int nItem) { return GetCheck(nItem); }
	virtual BOOL SetCheckEx(int nItem, BOOL bCheck) { return SetCheck(nItem, bCheck); }

	// ������и�ѡ�����
	virtual void OnHeadColumnClick(int nHeadItem);
	// ��鲢����ָ����
	void DoColumnClickSort(int iColumn);

	//���ô�����ʾ�Զ�����ɫ,��ɫ���ݱ����ڴ���
	void	SetColumnCustomColor(int nColumn);

	//��ȡtip��ʾ���ַ���,Ĭ����ʾ��Ԫ�����������
	CString GetCurTipText();

	// ���Ƿ���checkbox������
	BOOL PtInChkRect(int nItem, POINT pt);

	void SetHeadCtrlShowCheck(BOOL bShow = TRUE);
	BOOL GetHeadCtrlShowCheck();
	void SetHeadCtrlCheck(BOOL bCheck);
	BOOL GetHeadCtrlCheck();

	// ѡ�����Ƿ����ı�ɫ��Ϊ����ɫ,Ĭ��ΪTRUE
	BOOL IsTextColorAsBKColor() const;
	void SetTextColorAsBKColor(BOOL bTextColorAsBKColor);

	int GetTipMaxChars() const;
	void SetTipMaxChars(int nTipMaxChars);

	// ɾ������ѡ����
	void DeleteAllSelectItems();

	// �����Ҽ�����ĸ���,������������ʹ��
	void SetRClickInfo(int nItem, int nColumn);
	void SetRClickInfo(LPNMITEMACTIVATE pNMItemActivate);

	// ���Ƶ�ǰ������ڵĵ�Ԫ��
	BOOL CopyGridData();
	BOOL CopyGridData(int nItem, int nColumn);
	// ���Ƶ�ǰ��������е�����(һ��)
	BOOL CopyLineData();
	BOOL CopyLineData(int nItem);
	// ���Ƶ�ǰ��������е�����(һ��)
	BOOL CopyColumnData();
	BOOL CopyColumnData(int nColumn);
	// ���������������
	BOOL CopyAllData();

	void SetFUNCKeyDownF5(FUNCKeyDownF5 pfnKeyDownF5, void* pUsr);

	// ���������к�״̬��,������,nIndex��+2
	void InsertDataAndStatusColumn(int& nIndex);

	// �е���ŷ����仯,�����/ɾ����,��Ҫ���¼���״̬�е�����
	void RefreshDataAndStatusColumn();

	// ��߶�,�ⲿ����DPIת��
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

	// ����ð���ַ���(�10���ַ�)
	void SetCopyColon(LPCTSTR lpszColon);
	CString GetCopyColon();

	// ���ִ�ֱ����
	BOOL IsTextVCenter() const { return m_bIsTextVCenter; }
	void SetTextVCenter(BOOL val) { m_bIsTextVCenter = val; }
	BOOL IsHeaderTextVCenter() const { return m_ctlHeader.IsTextVCenter(); }
	void SetHeaderTextVCenter(BOOL val) { m_ctlHeader.SetTextVCenter(val); }

	// ͼƬ��ѡ��
	void SetStateImgCheckBox(LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL,
		LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);

	// �Զ���������
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
	CString m_strCopyColon;	//ð��

	CPPToolTip	m_toolTip;
	int m_nItem;		// ������ڵ���
	int m_nSubItem;		// ������ڵ���
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

	std::map<int, int> m_mapColorColumn;	//��ɫ��,���б���Ϊ��ɫRGB����ֵ

	// �Զ����������,�����ж��Զ������
	void* m_pUsrSortColumn;
	FUNCSortColumnCB m_pfnSortColumnCB;

	int m_HotKeyCtrlSE;

	CWnd* m_pWndAttribute;

	// ѡ����:�ı���ɫ��������ɫ
	BOOL m_bTextColorAsBKColor;

	// ��ʾ��Ϣ��ʾ������ַ���,Ĭ��Ϊ256,���Ӧ������10240
	int m_nTipMaxChars;

	// ��������ɫ�Ƿ�ı�(�ݶ�Ϊ��ɫ���ֱ��ɫ����)
	BOOL m_bIsTextXOR;

	// �Ҽ������λ��,������������ʹ��
	int m_nRClickItem;
	int m_nRClickColumn;

	// �ص�����,���û�����F5ʱ
	FUNCKeyDownF5 m_pfnKeyDownF5;
	void* m_pUsrKeyDownF5;

	// ����߶�,Ĭ��Ϊ22
	int m_nItemHeight;

	// ����������
	int m_nMaxResizeWidth;
	// ������
	int m_nResizeColumn;
	int m_nResizeColumn2;
	BOOL m_bIsResizeColumnData;

	// �����Ƿ�ֱ����
	BOOL m_bIsTextVCenter;

	BOOL m_bHasImgCheckbox;
	int m_nCheckHighlight;
	CImgBase* m_pImgCheckBox[IMG_BTN_STATE_COUNT];
	int m_nCheckBoxBaseDpi[IMG_BTN_STATE_COUNT];
	int m_nCheckboxWidth;

	// �Զ���������
	BOOL m_bGridlineH;
	BOOL m_bGridlineV;
	COLORREF m_crGridline;
};

