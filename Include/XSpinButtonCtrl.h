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

	// ��CEdit�ؼ����ݷ��ͱ仯ʱ,�ɵ��ô˽ӿڼ�����ݷ�Χ
	// ��������У��ID�Ƿ�һ��(DEBUG)
	void CheckEditChange(int nEditID = -1);
};


