#pragma once



// ����������ھ�̬�ؼ��ķ�� [2017-3-27 ydl]
class CWndBase : public CWnd
{
#ifdef _WIN64
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
#endif
};