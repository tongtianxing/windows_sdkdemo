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

	// 开启定时器,开启成功返回TRUE,否则返回FALSE
	// 延迟设置为0,会返回FALSE
	// 定时器通知,也会返回FALSE
	BOOL SetEditTimer();
	void KillEditTimer();

	// 检查参数
	BOOL CheckCommandParam(UINT nID, int nCode);

private:
	// 编辑事件延迟响应,默认1500,单位:毫秒
	int m_nEditDelayChange;

	// 延迟时间到,消息不用过滤
	BOOL m_bTimerSendEditChange;
public:
};

