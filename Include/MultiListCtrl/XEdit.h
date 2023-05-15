// XEdit.h : header file
//

#ifndef XEDIT_H
#define XEDIT_H

extern UINT WM_XEDIT_KILL_FOCUS;
extern UINT WM_XEDIT_VK_ESCAPE;
extern UINT WM_XEDIT_ERROR;
typedef struct _tagXEditAttr_S
{
	BOOL bEdit;			//�Ƿ����ñ༭ģʽ
	BOOL bCheck;		//[CHECK]�Ƿ�Բ������м��(TRUE,FALSE)
	int nLimit;			//[LIMIT]:�����ַ�����
	int nType;			//[TYPE]:�ַ�����(INT,FLOAT)
	union {
		int nMax;		//[NMAX]:���ò��������ֵ(������),nType=INT
		float fMax;		//[FMAX]:���ò��������ֵ(������),nType=FLOAT
	};
	union {
		int nMin;		//[NMIN]:���ò�������Сֵ(������),nType=INT
		float fMin;		//[FMIN]:���ò�������Сֵ(������),nType=FLOAT
	};
	CString strTheme;	//������ʾ����
	CString strContext;	//������ʾ����
}XEditAttr_S;
const int XEditAttr_LEN = sizeof(XEditAttr_S);


//�����ַ���������ʾʱ��ʽ��Ϊ���Ӧ������
#define FORMAT_STR_MAX			_T("[MAX]")			//�Զ�ʶ�����ֵ����
#define FORMAT_STR_NMAX			_T("[NMAX]")		//���������ֵ
#define FORMAT_STR_FMAX			_T("[FMAX]")		//���������ֵ
#define FORMAT_STR_MIN			_T("[MIN]")			//�Զ�ʶ��
#define FORMAT_STR_NMIN			_T("[NMIN]")
#define FORMAT_STR_FMIN			_T("[FMIN]")
#define FORMAT_STR_CHECK		_T("[CHECK]")
#define FORMAT_STR_LIMIT		_T("[LIMIT]")
#define FORMAT_STR_TYPE			_T("[TYPE]")
#define FORMAT_STR_VALUE		_T("[VALUE]")
// 
/////////////////////////////////////////////////////////////////////////////
// CXEdit window
#define EDIT_INT	1	//����
#define EDIT_FLOAT	2	//С��

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
	//�������ķ�Χ
	void SetParamRange(int Min, int Max, BOOL bCheck);
	//���������ͣ�����Ϊ0ʱ������Ҫ���,1Ϊ���֣�2Ϊ�ַ�....
	void CheckParam(int nParam = 0);
	//�������ݴ�����ʾ����
	void SetBalTip(const CString& strBalTheme, const CString& strContext);
	//����EDIT������
	void SetEditAttr(const XEditAttr_S& sEdit);
	//������ʾ����
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
	BOOL IsInteger(const CString &inStr) const; //�Ƿ�������
	BOOL IsFloat(const CString &inStr) const; //�Ƿ���С��
	static DWORD WINAPI  ThreadProc(LPVOID pParam);
	// Generated message map functions

	// ��ʾ��Ϣ��ʽ��
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
