#pragma once


// CXSpinButtonCtrl

class CXSpinButtonCtrl : public CSpinButtonCtrl
{
	DECLARE_DYNAMIC(CXSpinButtonCtrl)

public:
	CXSpinButtonCtrl();
	virtual ~CXSpinButtonCtrl();

protected:
	afx_msg void OnDeltapos(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
public:
	CWnd* SetBuddy(int nEditID);
	CWnd* SetBuddy(CWnd* pEdit);

	// 当CEdit控件内容发送变化时,可调用此接口检查内容范围
	// 参数用来校验ID是否一致(DEBUG)
	void CheckEditChange(int nEditID = -1);
};


