#pragma once


// CEditBounds

class CEditBoundsBase : public CImgEdit
{
	DECLARE_DYNAMIC(CEditBoundsBase)

public:
	CEditBoundsBase();
	virtual ~CEditBoundsBase();

protected:

	afx_msg void OnEnKillfocus();
	DECLARE_MESSAGE_MAP()

	// ����ֵ������Χʱ���ô��麯��
	virtual void ValueOutOfRange() = 0;
	virtual void ValueOutOfRange64() {};
public:
	// ����32λ�����ݷ�Χ,64λ���ݷ�Χ������0
	void SetValueRange(int nMinValue, int nMaxValue);

	// ����64λ�����ݷ�Χ,32λ���ݷ�Χ������0
	void SetValueRange64(__int64 n64MinValue, __int64 n64MaxValue);

protected:
	// 32λ�з�������
	int m_nMinValue;
	int m_nMaxValue;

	// 64λ�з�������
	__int64 m_n64MinValue;
	__int64 m_n64MaxValue;
};


