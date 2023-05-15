#pragma once

#ifdef _XTP_INCLUDE_CONTROLS

const int XTP_BTN_OP_NORMAL   = 0;
const int XTP_BTN_OP_FOCUS    = 1;
const int XTP_BTN_OP_PUSHED   = 2;
const int XTP_BTN_OP_DISABLED = 3;
const int XTP_BTN_OP_MAX      = XTP_BTN_OP_DISABLED;

const int XTP_BTN_ST_NORMAL   = 0;
const int XTP_BTN_ST_CHECK    = 1;
const int XTP_BTN_ST_MIXED    = 2;

const int XTP_RADIO_ST_MAX    = (XTP_BTN_ST_CHECK << 2) + XTP_BTN_OP_MAX;
const int XTP_CHECK_ST_MAX    = (XTP_BTN_ST_MIXED << 2) + XTP_BTN_OP_MAX;

const int XTP_BTN_STAT_COUNT    = max(XTP_RADIO_ST_MAX, XTP_CHECK_ST_MAX) + 1;

/*
*  0: Normal
*  1: Focus
*  2: Push
*  3: Disabled
*  4: Checked Normal
*  5: Checked Focus
*  6: Checked Push
*  7: Checked Disabled
*  8: Mixed Normal
*  9: Mixed Focus
* 10: Mixed Push
* 11: Mixed Disabled
*/

class CXTPButton;
class CGuiCheckBox;
class CXTPButtonImgTheme : public CXTPButtonTheme
{
public:
	CXTPButtonImgTheme();
	virtual ~CXTPButtonImgTheme();

public:
	virtual void DrawButtonBackground(CDC* pDC, CXTPButton* pButton);
	virtual void DrawButtonBackground(CDC* pDC, CGuiCheckBox* pButton);
	virtual void DrawFocusRect(CDC* pDC, CXTPButton* pButton) {}
	virtual void DrawButtonVisualStyleBackground(CDC* pDC, CXTPButton* pButton) { DrawButtonBackground(pDC, pButton); }

public:
	virtual void DrawButton(CDC* pDC, CXTPButton* pButton);
	virtual void DrawButton(CDC* pDC, CGuiCheckBox* pButton);

protected:
	void DrawCheckBoxMark(CDC* pDC, const CRect& rcBtn, int nImgIdx, bool bRightButton = false);
	void DrawCheckBoxText(CDC* pDC, const CRect& rcBtn, int nImgIdx, 
		const CString& strText, UINT wAlignment, COLORREF clrText, bool bRightButton);
	
	// CXTPButton
	int GetButtonImgIdx(CXTPButton* pButton);
	virtual void DrawRadioButtonMark(CDC* pDC, CXTPButton* pButton);
	void DrawRadioButtonText(CDC* pDC, CXTPButton* pButton);
	virtual void DrawCheckBoxMark(CDC* pDC, CXTPButton* pButton);
	void DrawCheckBoxText(CDC* pDC, CXTPButton* pButton);
	virtual void DrawGroupBox(CDC* pDC, CXTPButton* pButton);
	void DrawGroupBoxText(CDC* pDC, CXTPButton* pButton);

	// CGuiCheckBox
	int GetButtonImgIdx(CGuiCheckBox* pButton);
	virtual void DrawCheckBoxMark(CDC* pDC, CGuiCheckBox* pButton);
	void DrawCheckBoxText(CDC* pDC, CGuiCheckBox* pButton);

protected:
	CImgBase* m_pImgRadioButtonMark;
	CRect m_rcImgRadioButton[XTP_BTN_STAT_COUNT];
	CImgBase* m_pImgCheckBoxMark;
	CRect m_rcImgCheckBox[XTP_BTN_STAT_COUNT];
	int m_nBaseDpi;
	void SetImgSprite(CImgBase*& pImg, CRect* pRc, LPCTSTR lpszImagePath, int nCount);
public:
	void SetImgRadioButtonMark(LPCTSTR lpszImagePath);
	void SetImgCheckBoxMark(LPCTSTR lpszImagePath);
	BOOL HasImgRadioBtn() const { return m_pImgRadioButtonMark && m_pImgRadioButtonMark->HasPic(); }
	BOOL HasImgCheckBox() const { return m_pImgCheckBoxMark && m_pImgCheckBoxMark->HasPic(); }
	CRect GetMarkRect() const;

public:
	void DrawCheckBox(CDC* pDC, const CRect& rc, int nState,
		const CString& strText, COLORREF clrText, UINT wAlignment);
};

#endif