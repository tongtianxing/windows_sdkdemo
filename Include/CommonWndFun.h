#ifndef _COMMON_FUN_WND_H_
#define _COMMON_FUN_WND_H_


#define IDC_POPUP_DLG_BTN_CLOSE		2000
#define IDC_POPUP_DLG_BTN_MIN		2001
#define IDC_PVVIDEO_WND_PLAY_BTN	2002
#define IDC_POPUP_DLG_BTN_SET		2003	//���ð�ť

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
#define DEFAULT_BORDER_COLOR		RGB(130, 135, 144)	//Ĭ�ϱ߿����ɫ


HBRUSH GetHBrushByClr(COLORREF clr);

//����ɫ����
void DrawWndBK(HDC hDC, const CRect& rcClient, COLORREF ColorBK = RGB(232, 235, 241));
void DrawWndBK(HDC hDC, CWnd* pWnd, COLORREF ColorBK = RGB(232, 235, 241));
void DrawWndBK(HDC hDC, const CRect& rcClient, HBRUSH hbr);
void DrawWndBK(HDC hDC, CWnd* pWnd, HBRUSH hbr);
//�����䱳��
void DrawGradientBK(HDC hDC, const CRect& rtZone, COLORREF ColorStart, COLORREF ColorEnd);
// ���߿�
void DrawWndFrameRect(CWnd* pWnd, HDC hDC, COLORREF ColorPen = RGB(180, 180, 180));
void DrawWndFrameRect(CWnd* pWnd, HDC hDC, HBRUSH hbr);
//����
void DrawLine(HDC hDc, const CPoint& PointStart, const CPoint& PonitEnd, COLORREF ColorPen = RGB(0, 0, 0), int nPDType = PS_SOLID/*�ߵ�����*/);
// ����ѡ��
void DrawCheckState(HDC hDC, const CRect& rtArea, COLORREF ColorBK = RGB(0, 0, 0));

//���漸���ƶ���ť�Ľӿڣ��ڸ�DPIʱ�ƶ���λ�ò��ԣ���Ҫ�����غ���CDialogBase::ScaleDPI_PostScale()�ڵ��� cmye 2022-03-29
//���ж����ť���Ի���ײ�
void MoveMultiBtnCenter(const HWND hWnd, UINT nSize, ...);
//void MoveBtnToButtomCenter(CWnd** ppWnd, UINT nSize, const HWND hWnd, int nButtomHightInerval=POPUP_DLG_BUTTOM_INERVAL);
//�ƶ���ť��ָ��λ��
void MoveBtn(int nLeft, int nTop, CButton& Btn);

//��ʵ��Բ
void DrawSolidCircle(HDC hDC, const CRect& rc, COLORREF ColorPen = RGB(0, 255, 0));

// ��Radio���Ŀؼ�,�������ı�,������ں���������
//void DrawRadioButton(HDC hDC, CWnd* pRadioBtn, const CString& strText);



// ��ȡĳ���ؼ��е��ı��ڵ�ǰ�����µĳߴ�
CSize GetControlTextSize(CWnd* pWnd, LPCTSTR szText = NULL);
#define	GetControlSize GetControlTextSize


// ���������������е�λ��
int GetHitTest(const CRect& rtArea, const CPoint& pt, const CSize& sizeBorder = CSize());

// �ж�ĳ���ַ����Ƿ�ΪС����ʽ
BOOL StringIsFloat(LPCTSTR lpszString);
// �ж�ĳ���ַ����Ƿ�Ϊ������ʽ
BOOL StringIsInt(LPCTSTR lpszString);
// �ı��Զ����У�������ӻ��з����ַ���
CString StringLineWrap(CString text, int nMaxWidth, HFONT hFont = NULL, LPCTSTR szLineBreak = _T("\r\n"));

// ϵͳdpi,��ʼ��ϵͳ��ǰdpi
void InitSystemDPI();
// ˢ��ϵͳdpi
void RefreshSystemDPI();
// ��ȡϵͳdpi,Ĭ��:96 150%:144
int GetSystemDPI();
// ����dpi�仯,��Ӧ�Ŵ�ֵ
int DPIConvert(int nOldData);
// ����dpi�仯,��Ӧ�Ŵ�ֵ��һ��
int DPIConvertHalf(int nOldData);
// ����dpi�仯���ӷŴ�ֵ�õ�ԭ��С
int DPIConvertInverse(int nConvertedData);


// �ͷ�ԭ��ˢ�����³�ʼ��Ϊָ����ɫ
//void ChangeSolidBrush(HBRUSH& hBrush, COLORREF colorNew);


// Ĭ�Ͽ���HOOK,һ����DLL�е���
void SetDefaultHook(BOOL bEnable);
BOOL IsDefaultHook();






#endif