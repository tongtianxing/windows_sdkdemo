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
// 四状态图片对象基类，实现类似于CCxButton的功能
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

	// 基础DPI,默认100,如果使用200%时为200
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
	// 保留指定的外框尺寸不缩放
	// 传参不需要DPIConvert
	// 将原图片切割成九宫格，只缩放中间的那块，并缓存到BITMAP
	void SetExpand(int nIdx, int nBorderWidth, int nBorderHeight);

protected:
	// 清除缓存BITMAP，注意此接口不是关闭功能
	// 需要关闭时调用SetExpand(nIdx, 0, 0)
	void ClearExpand(int nIdx = -1);

	// 重建缓存BITMAP
	void RebuildExpand(int nIdx, HDC hdc, const RECT& rc);

};
