#ifndef _COMMON_FUN_WND_H_
#define _COMMON_FUN_WND_H_


#define IDC_POPUP_DLG_BTN_CLOSE		2000
#define IDC_POPUP_DLG_BTN_MIN		2001
#define IDC_PVVIDEO_WND_PLAY_BTN	2002
#define IDC_POPUP_DLG_BTN_SET		2003	//设置按钮

#define POPUP_DLG_TOP_INERVAL			4
#define POPUP_DLG_BUTTOM_INERVAL		12
#define POPUP_DLG_LEFT_INERVAL			5
#define POPUP_DLG_RIGHT_INERVAL			5
#define POPUP_DLG_BTN_CLOSE_WIDTH		20
#define POPUP_DLG_BTN_CLOSE_HIGHT		22

#define POPUP_DLG_LOGO_WIDTH			25
#define POPUP_DLG_LOGO_HIGHT			20
#define POPUP_DLG_TITLE_HIGHT			30
#define POPUP_DLG_BUTTOM_HIGHT			40

#define POPUP_DLG_BK_COLOR			RGB(255, 255, 255)
#define POPUP_DLG_TITLE_COLOR		RGB(200, 200, 200)
#define POPUP_DLG_BUTTOM_COLOR		RGB(200, 200, 200)
#define POPUP_DLG_FRAME_COLOR		RGB(0, 0, 0)
#define POPUP_DLG_TEXT_COLOR		RGB(60, 60, 60)


//画圆角
void DrawRoundRectRgn(CWnd* pWnd);
//画单色背景
void DrawWndBK(HDC hDC, CRect& rcClient, COLORREF ColorBK=RGB(232, 235, 241));
void DrawWndBK(HDC hDC, CWnd* pWnd, COLORREF ColorBK=RGB(232, 235, 241));
//画渐变背景
void DrawGradientBK(HDC hDC, const CRect& rtZone, COLORREF ColorStart, COLORREF ColorEnd);
// 画边框
void DrawWndFrameRect(CWnd* pWnd, HDC hDC, COLORREF ColorPen=RGB(180,180,180));
//画线
void DrawLine(HDC hDc, const CPoint& PointStart, const CPoint& PonitEnd, COLORREF ColorPen=RGB(0,0,0));
// 画勾选框
void DrawCheckState(HDC hDC, const CRect& rtArea, COLORREF ColorBK = RGB(0, 0, 0));

//排列多个按钮到对话框底部
void MoveMultiBtnCenter(const HWND hWnd, UINT nSize, ...);
//void MoveBtnToButtomCenter(CWnd** ppWnd, UINT nSize, const HWND hWnd, int nButtomHightInerval=POPUP_DLG_BUTTOM_INERVAL);
//移动按钮到指定位置
void MoveBtn(int nLeft, int nTop, CButton& Btn);

//画实心圆
void DrawSolidCircle(HDC hDC, const CRect& rc, COLORREF ColorPen=RGB(0,255,0));

// 画Radio风格的控件,仅绘制文本,风格需在函数外设置
//void DrawRadioButton(HDC hDC, CWnd* pRadioBtn, const CString& strText);


// 向CComboBox控件插入数据
void InsertCComboBoxData( CComboBox& cmb, int nIndex, LPCTSTR lpszStr, int nData );
void InsertCComboBoxData( CComboBox& cmb, LPCTSTR lpszStr, int nData );
// 通过比较ITEMDATA选择相应的item,返回选择的索引
int SearchCmbData(CComboBox& cmb, int nItemData, BOOL bSel);

// 向CEdit控件后面附加文本,参数三:预添加文件前附加字符串
void EditCtrlAddText( CEdit* pEdit, LPCTSTR lpszText, LPCTSTR lpszAddHead/* = _T("\r\n")*/ );

// 设置焦点到CEdit,一般用于启动时设置,避免控件文本被全选
void SetFocusEdit( CEdit* pEdit );

// 计算CListCtrl控件中被选择的项数
int GetListSelectCount( CListCtrl& lst );
// 重新设置某列的宽度
void ResizeListCtrl(CListCtrl& lst, int nIndex);
// 获取当前选择的第一项索引
int GetCurListSelectedItem(CListCtrl& lst);


// 获取某个控件中的文本在当前环境下的尺寸
CSize GetControlSize( CWnd* pWnd );


// 计算坐标在区域中的位置
int GetHitTest(const CRect& rtArea, const CPoint& pt, const CSize& sizeBorder = CSize());

// 判断某个字符串是否为小数格式
BOOL StringIsFloat(LPCTSTR lpszString);
// 判断某个字符串是否为整数格式
BOOL StringIsInt(LPCTSTR lpszString);


// 系统dpi,初始化系统当前dpi
void InitSystemDPI();
// 获取系统dpi,默认:96 150%:144
int GetSystemDPI();
// 根据dpi变化,对应放大值
int DPIConvert(int nOldData);
// 根据dpi变化,对应放大值的一半
int DPIConvertHalf(int nOldData);

// 使控件窗口宽度(高度,大小)相同,参数一是标准值
void ControlSameWidth(CWnd* pWnd, CWnd* pChangeWnd);
void ControlSameWidthMutli(CWnd* pWnd, CWnd** ppChangeWnd, int nCount);
void ControlSameHeight(CWnd* pWnd, CWnd* pChangeWnd);
void ControlSameHeightMutli(CWnd* pWnd, CWnd** ppChangeWnd, int nCount);
void ControlSameSize(CWnd* pWnd, CWnd* pChangeWnd, BOOL bChangeWidth, BOOL bChangeHeight);
void ControlSameSizeMutli(CWnd* pWnd, CWnd** ppChangeWnd, int nCount, BOOL bChangeWidth, BOOL bChangeHeight);




template <class T>
void CustomCreateDlg( T** pDlg, CWnd* pParent, int nCmdShow = SW_HIDE, BOOL bCenter = FALSE )
{
	CustomCreateDlg(*pDlg, pParent, nCmdShow, bCenter);
}
template <class T>
void CustomCreateDlg( T*& pDlg, CWnd* pParent, int nCmdShow = SW_HIDE, BOOL bCenter = FALSE )
{
	if (pDlg == NULL)
	{
		pDlg = new T;
		if (pDlg)
		{
			pDlg->Create(T::IDD, pParent);
			if (pDlg->GetSafeHwnd())
			{
				pDlg->ShowWindow(nCmdShow);
				if (bCenter)
				{
					pDlg->CenterWindow();
				}
			}
			else
			{
				SAFE_DELETE_OBJECT(pDlg);
			}
		}
	}
}
template <class T>
void ShowDlg(T* pDlg, bool bCenter = true)
{
	if (pDlg)
	{
		if (!pDlg->IsWindowVisible())
		{
			if (bCenter)
			{
				pDlg->CenterWindow();
			}
		}
		pDlg->ShowWindow(SW_SHOW);
		pDlg->SetForegroundWindow();
	}
}

template <class T>
void DestroyDlg(T** pDlg)
{
	DestroyDlg(*pDlg);
}

template <class T>
void DestroyDlg(T*& pDlg)
{
	if (pDlg)
	{
		pDlg->DestroyWindow();
		ASSERT(NULL == pDlg->GetSafeHwnd());
		SAFE_DELETE_OBJECT(pDlg);
	}
}




#endif