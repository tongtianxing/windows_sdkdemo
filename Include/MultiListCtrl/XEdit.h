// XEdit.h : header file
//

#ifndef XEDIT_H
#define XEDIT_H

extern UINT WM_XEDIT_KILL_FOCUS;
extern UINT WM_XEDIT_VK_ESCAPE;
extern UINT WM_XEDIT_ERROR;
typedef struct _tagXEditAttr_S
{
	BOOL bEdit;			//是否启用编辑模式
	BOOL bCheck;		//[CHECK]是否对参数进行检查(TRUE,FALSE)
	int nLimit;			//[LIMIT]:限制字符数量
	int nType;			//[TYPE]:字符类型(INT,FLOAT)
	union {
		int nMax;		//[NMAX]:设置参数的最大值(整数型),nType=INT
		float fMax;		//[FMAX]:设置参数的最大值(浮点型),nType=FLOAT
	};
	union {
		int nMin;		//[NMIN]:设置参数的最小值(整数型),nType=INT
		float fMin;		//[FMIN]:设置参数的最小值(浮点型),nType=FLOAT
	};
	CString strTheme;	//气泡提示标题
	CString strContext;	//气泡提示内容
}XEditAttr_S;
const int XEditAttr_LEN = sizeof(XEditAttr_S);


//以下字符串会在提示时格式化为相对应的内容
#define FORMAT_STR_MAX			_T("[MAX]")			//自动识别最大值类型
#define FORMAT_STR_NMAX			_T("[NMAX]")		//整数型最大值
#define FORMAT_STR_FMAX			_T("[FMAX]")		//浮点型最大值
#define FORMAT_STR_MIN			_T("[MIN]")			//自动识别
#define FORMAT_STR_NMIN			_T("[NMIN]")
#define FORMAT_STR_FMIN			_T("[FMIN]")
#define FORMAT_STR_CHECK		_T("[CHECK]")
#define FORMAT_STR_LIMIT		_T("[LIMIT]")
#define FORMAT_STR_TYPE			_T("[TYPE]")
#define FORMAT_STR_VALUE		_T("[VALUE]")
// 
/////////////////////////////////////////////////////////////////////////////
// CXEdit window
#define EDIT_INT	1	//整数
#define EDIT_FLOAT	2	//小数

class CXEdit : public CEdit
{
// Construction
public:
	CXEdit(CWnd *pParent, LPCTSTR lpszText);
	virtual ~CXEdit();

// Attributes
public:

// Operations
public:
	//检查参数的范围
	void SetParamRange(int Min, int Max, BOOL bCheck);
	//检查参数类型，参数为0时，不需要检查,1为数字，2为字符....
	void CheckParam(int nParam = 0);
	//设置气泡窗口提示内容
	void SetBalTip(const CString& strBalTheme, const CString& strContext);
	//设置EDIT的属性
	void SetEditAttr(const XEditAttr_S& sEdit);
	//设置显示内容
	void SetEditText(const CString& strText);

	void SetMessgeSet(BOOL bMessageSet);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXEdit)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString	m_strText;
	BOOL	m_bMessageSent;

	XEditAttr_S m_EditAttr;

	void SendRegisteredMessage(UINT nMsg, WPARAM wParam = 0, LPARAM lParam = 0);
	BOOL IsInteger(const CString &inStr) const; //是否是整数
	BOOL IsFloat(const CString &inStr) const; //是否是小数
	static DWORD WINAPI  ThreadProc(LPVOID pParam);
	// Generated message map functions

	// 提示信息格式化
	CString FormatStr(const CString& strStr);
	CString expandStrs(const TCHAR *lpszSrc);

public:
	CString GetBalTheme();
	CString GetBalContext();
protected:
	//{{AFX_MSG(CXEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnChange();
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XEDIT_H
