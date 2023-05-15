
#pragma once

// 默认需添加ID=10101的对话框,包含IDOK,IDNO,IDCANCEL
// 其他请自定义ID号

class CImgBase;
class CDlgMsgTipBase : public CDlgPopupBase
{
public:
	CDlgMsgTipBase(UINT nType, CWnd* pParent = NULL);   // standard constructor
	CDlgMsgTipBase(UINT nType, int nDlgID, CWnd* pParent = NULL);

	enum { IDD = 10101/*IDD_DLG_MSG_TIP*/ };
	CCxTextButton	m_btnCannel;
	CCxTextButton	m_btnOK;
	CCxTextButton	m_btnNO;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void ScaleDPI_PostScale();

	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);


protected:
	afx_msg void OnNo();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()


	void CalcWndSize();
public:
	virtual void DoOnInitDialog(); //语言和其他信息
	virtual void DoOnPaint(HDC hDC);
	void SetDlgInfo(LPCTSTR lpszText = _T(""), LPCTSTR lpszTitle = _T(""));
	UINT GetType() { return m_nType; }

protected:
	UINT m_nType;
	CImgBase* m_pImgTip;

	CString m_strTitle;
	CString m_strText;
};
