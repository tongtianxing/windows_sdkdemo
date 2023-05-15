#pragma once

// 替换CXComboBox，去除CComboBox继承关系
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

	// 开启定时器,开启成功返回TRUE,否则返回FALSE
	// 延迟设置为0,会返回FALSE
	// 定时器通知,也会返回FALSE
	BOOL SetEditTimer();
	void KillEditTimer();

	// 检查参数
	BOOL CheckCommandParam(UINT nID, int nCode);

private:
	UINT m_nCtrlID;

	// 编辑事件延迟响应,默认1500,单位:毫秒
	int m_nEditDelayChange;

	// 延迟时间到,消息不用过滤
	BOOL m_bTimerSendEditChange;
public:
};