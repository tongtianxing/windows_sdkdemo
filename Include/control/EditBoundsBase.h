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

	// 输入值超出范围时调用此虚函数
	virtual void ValueOutOfRange() = 0;
	virtual void ValueOutOfRange64() {};
public:
	// 设置32位的数据范围,64位数据范围将会设0
	void SetValueRange(int nMinValue, int nMaxValue);

	// 设置64位的数据范围,32位数据范围将会设0
	void SetValueRange64(__int64 n64MinValue, __int64 n64MaxValue);

protected:
	// 32位有符号整数
	int m_nMinValue;
	int m_nMaxValue;

	// 64位有符号整数
	__int64 m_n64MinValue;
	__int64 m_n64MaxValue;
};


