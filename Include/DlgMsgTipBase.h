
#pragma once

// Ĭ�������ID=10101�ĶԻ���,����IDOK,IDNO,IDCANCEL
// �������Զ���ID��

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
	virtual void DoOnInitDialog(); //���Ժ�������Ϣ
	virtual void DoOnPaint(HDC hDC);
	void SetDlgInfo(LPCTSTR lpszText = _T(""), LPCTSTR lpszTitle = _T(""));
	UINT GetType() { return m_nType; }

protected:
	UINT m_nType;
	CImgBase* m_pImgTip;

	CString m_strTitle;
	CString m_strText;
};
