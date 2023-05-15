#pragma once

// �滻CXComboBox��ȥ��CComboBox�̳й�ϵ
class CEditChangeDelayTimer: public CWnd
{
	
//class CXComboBox : public CComboBox
public:
	CEditChangeDelayTimer(UINT nCtrlID);
	DECLARE_DYNAMIC(CEditChangeDelayTimer)

protected:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

public:
	int GetEditDelayChange() const;
	void SetEditDelayChange(int val);

	// ������ʱ��,�����ɹ�����TRUE,���򷵻�FALSE
	// �ӳ�����Ϊ0,�᷵��FALSE
	// ��ʱ��֪ͨ,Ҳ�᷵��FALSE
	BOOL SetEditTimer();
	void KillEditTimer();

	// ������
	BOOL CheckCommandParam(UINT nID, int nCode);

private:
	UINT m_nCtrlID;

	// �༭�¼��ӳ���Ӧ,Ĭ��1500,��λ:����
	int m_nEditDelayChange;

	// �ӳ�ʱ�䵽,��Ϣ���ù���
	BOOL m_bTimerSendEditChange;
public:
};