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
#define DEFAULT_BORDER_COLOR		RGB(130, 135, 144)	//默认边框的颜色


HBRUSH GetHBrushByClr(COLORREF clr);

//画单色背景
void DrawWndBK(HDC hDC, const CRect& rcClient, COLORREF ColorBK = RGB(232, 235, 241));
void DrawWndBK(HDC hDC, CWnd* pWnd, COLORREF ColorBK = RGB(232, 235, 241));
void DrawWndBK(HDC hDC, const CRect& rcClient, HBRUSH hbr);
void DrawWndBK(HDC hDC, CWnd* pWnd, HBRUSH hbr);
//画渐变背景
void DrawGradientBK(HDC hDC, const CRect& rtZone, COLORREF ColorStart, COLORREF ColorEnd);
// 画边框
void DrawWndFrameRect(CWnd* pWnd, HDC hDC, COLORREF ColorPen = RGB(180, 180, 180));
void DrawWndFrameRect(CWnd* pWnd, HDC hDC, HBRUSH hbr);
//画线
void DrawLine(HDC hDc, const CPoint& PointStart, const CPoint& PonitEnd, COLORREF ColorPen = RGB(0, 0, 0), int nPDType = PS_SOLID/*线的类型*/);
// 画勾选框
void DrawCheckState(HDC hDC, const CRect& rtArea, COLORREF ColorBK = RGB(0, 0, 0));

//下面几个移动按钮的接口，在高DPI时移动的位置不对，需要在重载函数CDialogBase::ScaleDPI_PostScale()内调用 cmye 2022-03-29
//排列多个按钮到对话框底部
void MoveMultiBtnCenter(const HWND hWnd, UINT nSize, ...);
//void MoveBtnToButtomCenter(CWnd** ppWnd, UINT nSize, const HWND hWnd, int nButtomHightInerval=POPUP_DLG_BUTTOM_INERVAL);
//移动按钮到指定位置
void MoveBtn(int nLeft, int nTop, CButton& Btn);

//画实心圆
void DrawSolidCircle(HDC hDC, const CRect& rc, COLORREF ColorPen = RGB(0, 255, 0));

// 画Radio风格的控件,仅绘制文本,风格需在函数外设置
//void DrawRadioButton(HDC hDC, CWnd* pRadioBtn, const CString& strText);



// 获取某个控件中的文本在当前环境下的尺寸
CSize GetControlTextSize(CWnd* pWnd, LPCTSTR szText = NULL);
#define	GetControlSize GetControlTextSize


// 计算坐标在区域中的位置
int GetHitTest(const CRect& rtArea, const CPoint& pt, const CSize& sizeBorder = CSize());

// 判断某个字符串是否为小数格式
BOOL StringIsFloat(LPCTSTR lpszString);
// 判断某个字符串是否为整数格式
BOOL StringIsInt(LPCTSTR lpszString);
// 文本自动换行，返回添加换行符的字符串
CString StringLineWrap(CString text, int nMaxWidth, HFONT hFont = NULL, LPCTSTR szLineBreak = _T("\r\n"));

// 系统dpi,初始化系统当前dpi
void InitSystemDPI();
// 刷新系统dpi
void RefreshSystemDPI();
// 获取系统dpi,默认:96 150%:144
int GetSystemDPI();
// 根据dpi变化,对应放大值
int DPIConvert(int nOldData);
// 根据dpi变化,对应放大值的一半
int DPIConvertHalf(int nOldData);
// 根据dpi变化，从放大值得到原大小
int DPIConvertInverse(int nConvertedData);


// 释放原画刷并重新初始化为指定颜色
//void ChangeSolidBrush(HBRUSH& hBrush, COLORREF colorNew);


// 默认开启HOOK,一般在DLL中调用
void SetDefaultHook(BOOL bEnable);
BOOL IsDefaultHook();






#endif