
#pragma once

const int CHECK_BOX_STAT_NORMAL = 0;
const int CHECK_BOX_STAT_HILIGHT = 1;
const int CHECK_BOX_STAT_CHECKED = 2;
const int CHECK_BOX_STAT_DISABLED = 4;
const int CHECK_BOX_STAT_MIXED = 8;
const int CHECK_BOX_STAT_MAX = CHECK_BOX_STAT_NORMAL | CHECK_BOX_STAT_HILIGHT | CHECK_BOX_STAT_CHECKED | CHECK_BOX_STAT_DISABLED | CHECK_BOX_STAT_MIXED;
const int CHECK_BOX_STAT_COUNT = CHECK_BOX_STAT_MAX + 1;

class CXTPButtonImgTheme;
class CGuiCheckBox : public CButton
{
	DECLARE_DYNAMIC(CGuiCheckBox)

public:
	CGuiCheckBox();
	virtual ~CGuiCheckBox();


public:
	void DrawOrange(CDC* pDC, CRect rcTemp);
	BOOL GetCheckEx() const;
	void SetCheckEx(BOOL bCheckBtn = TRUE);
	void SetTextColor(COLORREF clrText);
	void SetCheckBKColor(COLORREF clrBk);

public:
	BOOL         m_bCheckBtn;
	BOOL         m_bPressBtn;
	BOOL         m_bSelected;
	BOOL		 m_bDrawParentArea;
	COLORREF     m_clrHigh;				//���α߿���ɫ
	COLORREF     m_clrCheck;			//��ѡ�����ɫ
	COLORREF     m_clrText;				//�ı���ɫ
	COLORREF	 m_clrCheckBk;			//�ı�����ɫ(Ĭ��Ϊ���ڱ���ɫ)

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// ���ظ����ڵ�CHECK��Ϣ ���úͻ�ȡ [2017-3-23 ydl]
	afx_msg LRESULT OnMsgGetCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnMsgSetCheck(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgDrawParentArea(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	void UpdateCheckState();

	// ���Ƹ����ڵĿؼ�����
	void DrawParentControl();

public:
	// �Ƿ�Ϊ͸������
	BOOL IsTransparentMode();

protected:
	CXTPButtonImgTheme* m_pTheme;
public:
	BOOL HasTheme() const { return m_pTheme != NULL; }
	void SetTheme(CXTPButtonImgTheme* pTheme);
	CXTPButtonImgTheme* GetTheme() const { return m_pTheme; }
};
