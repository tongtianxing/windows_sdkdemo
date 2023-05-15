#pragma once


class CXComboBox : public CComboBox
{
public:
	CXComboBox();


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
	// �༭�¼��ӳ���Ӧ,Ĭ��1500,��λ:����
	int m_nEditDelayChange;

	// �ӳ�ʱ�䵽,��Ϣ���ù���
	BOOL m_bTimerSendEditChange;
public:
};

