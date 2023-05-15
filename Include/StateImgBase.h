#pragma once
#include <array>

enum ImgBtnState
{
	IMG_BTN_STATE_NORMAL = 0,
	IMG_BTN_STATE_HIGHLIGHT,
	IMG_BTN_STATE_OVER,
	IMG_BTN_STATE_DISABLED,
	IMG_BTN_STATE_COUNT
};

class CSkinScrollWnd;
// ��״̬ͼƬ������࣬ʵ��������CCxButton�Ĺ���
class CStateImgBase
{
	friend class CSkinScrollWnd;
protected:
	std::vector<std::array<CImgBase*, IMG_BTN_STATE_COUNT>> m_vecImg;
private:
	HWND m_hwnd;
	bool m_bOverStatus;
	bool m_bHilightStatus;
	bool m_bDisabled;
	std::vector<CSize> m_vecExpandBorderSize;
	std::vector<std::array<HBITMAP, IMG_BTN_STATE_COUNT>> m_vecBmpExpand;

	// ����DPI,Ĭ��100,���ʹ��200%ʱΪ200
	std::vector<std::array<int, IMG_BTN_STATE_COUNT>> m_vecBaseDpi;

protected:
	bool IsFocused() const { return m_bOverStatus || (m_hwnd && (::GetFocus() == m_hwnd || ::GetCapture() == m_hwnd)); }
	bool IsSelected() const { return m_bHilightStatus || (m_hwnd && ::GetCapture() == m_hwnd); }
	bool IsDisabled() const { return m_bDisabled || (m_hwnd && !::IsWindowEnabled(m_hwnd)); }
public:
	CStateImgBase(size_t size);
	virtual ~CStateImgBase();
	void InitState(CWnd* pWnd) { m_hwnd = pWnd->GetSafeHwnd(); }

	int GetDrawIndex() const { return GetDrawIndex(IsSelected(), IsFocused(), IsDisabled()); }
	int GetDrawIndex(LPDRAWITEMSTRUCT pdis) const;
	int GetDrawIndex(bool inSelected, bool inFocused, bool inDisabled) const;

	bool IsOverStatus() { return m_bOverStatus; }
	bool IsHilightStatus() { return m_bHilightStatus; }
	void SetOverStatus(BOOL bOver, BOOL bRedraw = TRUE);
	void SetHilightStatus(BOOL bHilight, BOOL bRedraw = TRUE);
	void SetDisabled(BOOL bDisabled, BOOL bRedraw = TRUE);

	bool HasPic(int nIdx = 0) const { CImgBase* pImg = m_vecImg[nIdx][IMG_BTN_STATE_NORMAL]; return pImg && !!pImg->HasPic(); }

	virtual bool SetStateImg(size_t idx, LPCTSTR lpszNormal = NULL, LPCTSTR lpszOver = NULL, LPCTSTR lpszHighLight = NULL, LPCTSTR lpszDisable = NULL);

	CSize GetImgSize(size_t idx, int state);

	void DrawImg(size_t idx, int state, HDC hdc, const RECT& rc);
	void DrawImgEx(size_t idx, int state, HDC hdc, const RECT& rc, const LPRECT rcClip = NULL);

public:
	// ����ָ�������ߴ粻����
	// ���β���ҪDPIConvert
	// ��ԭͼƬ�и�ɾŹ���ֻ�����м���ǿ飬�����浽BITMAP
	void SetExpand(int nIdx, int nBorderWidth, int nBorderHeight);

protected:
	// �������BITMAP��ע��˽ӿڲ��ǹرչ���
	// ��Ҫ�ر�ʱ����SetExpand(nIdx, 0, 0)
	void ClearExpand(int nIdx = -1);

	// �ؽ�����BITMAP
	void RebuildExpand(int nIdx, HDC hdc, const RECT& rc);

};
