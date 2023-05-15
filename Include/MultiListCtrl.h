

#ifndef MULTILISTCTRL_H
#define MULTILISTCTRL_H

#include "MultiListCtrl\XHeaderCtrl.h"
#ifndef DO_NOT_INCLUDE_XCOMBOLIST
#include "MultiListCtrl\XCombo.h"
#include "MultiListCtrl\AdvComboBox.h"
#endif
#include "MultiListCtrl\XEdit.h"

extern UINT WM_XLISTCTRL_COMBO_SELECTION;
extern UINT WM_XLISTCTRL_EDIT_END;
extern UINT WM_XLISTCTRL_CHECKBOX_CLICKED;
struct XLISTCTRLDATA
{
	// ctor
	XLISTCTRLDATA()
	{
		bEnabled = TRUE;
		bBold = FALSE;
		bModified = FALSE;
		nImage = -1;
#ifndef NO_XLISTCTRL_TOOL_TIPS
		strToolTip = _T("");
#endif
		bCombo = FALSE;
		bSort = FALSE;
		psa = NULL;
		nComboListHeight = 10;
		nInitialComboSel = -1;	// use default
		/*bEdit                = FALSE;*/
		sEdit.bEdit = FALSE;
		sEdit.bCheck = FALSE;
		sEdit.nMax = 0;
		sEdit.nMin = 0;
		sEdit.strContext = _T("");
		sEdit.strTheme = _T("");
		sEdit.nLimit = 10;
		sEdit.nType = EDIT_INT;
		/////////////////////////////
		crText = ::GetSysColor(COLOR_WINDOWTEXT);
		crBackground = ::GetSysColor(COLOR_WINDOW);

		bShowProgress = FALSE;
		nProgressPercent = 0;
		strProgressMessage = _T("");
		bShowProgressMessage = TRUE;
		nCheckedState = -1;
		bCheckedEnable = TRUE;
		dwItemData = 0;
	}

	BOOL			bEnabled;				// TRUE = enabled, FALSE = disabled (gray text)
	BOOL			bBold;					// TRUE = display bold text
	BOOL			bModified;				// TRUE = subitem has been modified
	int				nImage;					// index in image list, else -1
#ifndef NO_XLISTCTRL_TOOL_TIPS
	CString			strToolTip;				// tool tip text for cell
#endif

	// for combo
	BOOL			bCombo;					// TRUE = display combobox
	BOOL			bSort;					// TRUE = add CBS_SORT style;  this means
											// that the list will be re-sorted on
											// each AddString()
	CStringArray *	psa;					// pointer to string array for combo listbox
	int				nComboListHeight;		// combo listbox height (in rows)
	int				nInitialComboSel;		// initial combo listbox selection (0 = first)

	//for edit
	//BOOL		bEdit;						// true = enable editing
	XEditAttr_S		sEdit;                      // sEdit.bEdit, true = enable editing
	// for color
	COLORREF	crText;
	COLORREF	crBackground;

	// for progress
	BOOL		bShowProgress;				// true = show progress control
	int			nProgressPercent;			// 0 - 100
	CString		strProgressMessage;			// custom message for progress indicator -
											// MUST INCLUDE %d
	BOOL		bShowProgressMessage;		// TRUE = display % message, or custom message
											// if one is supplied
	// for checkbox
	int			nCheckedState;				// -1 = don't show, 0 = unchecked, 1 = checked
	BOOL		bCheckedEnable;				//checked not draw border,not change state

	DWORD_PTR		dwItemData;					// pointer to app's data
};
///////////////////////////////////////////////////////////////////////////////
// CMultiListCtrl class
class  CMultiListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMultiListCtrl)
// Construction
public:
	CMultiListCtrl();
	virtual ~CMultiListCtrl();
// Attributes
public:
	int		CountCheckedItems(int nSubItem);
	BOOL	DeleteAllItems();
	BOOL	DeleteItem(int nItem);
	void	DeleteProgress(int nItem, int nSubItem);
	int		FindDataItem(DWORD dwData);	//+++
	BOOL	GetBold(int nItem, int nSubItem);
	int		GetCellPadding() { return m_nPadding; }					//+++
	int		GetCheckbox(int nItem, int nSubItem);
	int		GetColumns();
	CString	GetComboText(int iItem, int iSubItem);
	int		GetCurSel();
	BOOL	GetEllipsis() { return m_bUseEllipsis; }				//+++
	BOOL	GetEnabled(int nItem);
	DWORD	GetExtendedStyleX() { return m_dwExtendedStyleX; }
	int		GetHeaderCheckedState(int nSubItem);
	int		GetItemCheckedState(int nItem, int nSubItem);			//+++
	BOOL	GetItemColors(int nItem,								//+++
		int nSubItem,
		COLORREF& crText,
		COLORREF& crBackground);
	LPARAM GetItemData(int nItem);
	BOOL	GetListModified() { return m_bListModified; }			//+++
	BOOL	GetModified(int nItem, int nSubItem);					//+++
	BOOL	GetSubItemRect(int iItem, int iSubItem, int nArea, CRect& rect);
	int		InsertItem(int nItem, LPCTSTR lpszItem);
	int		InsertItem(int nItem,
		LPCTSTR lpszItem,
		COLORREF crText,
		COLORREF crBackground);
	int		InsertItem(const LVITEM* pItem);
	BOOL	SetBold(int nItem, int nSubItem, BOOL bBold);
	void	SetCellPadding(int nPadding) { m_nPadding = nPadding; }	//+++
	BOOL	SetComboBox(int nItem,
		int nSubItem,
		BOOL bEnableCombo,
		CStringArray *psa,
		int nComboListHeight,
		int nInitialComboSel,
		BOOL bSort = FALSE);	//+++
	BOOL	SetCheckbox(int nItem, int nSubItem, int nCheckedState);
	BOOL	SetCheckboxEnable(int nItem, int nSubItem, BOOL bEnable = TRUE);
	virtual int SetColumnWidth(int nCol, int cx)
	{
		CListCtrl::SetColumnWidth(nCol, cx);
		int w = CListCtrl::GetColumnWidth(nCol);
		return CListCtrl::SetColumnWidth(nCol, w + (m_HeaderCtrl.GetSpacing() * 2));
	}
	BOOL	SetCurSel(int nItem, BOOL bEnsureVisible = FALSE);	//+++
	BOOL	SetEdit(int nItem, int nSubItem);
	////
	BOOL	SetEditParamRange(int nItem, int nSubItem, int nMin, int nMax, BOOL bCheck);		//设置EDIT的参数范围
	BOOL	SetEditBalTip(int nItem, int nSubItem, const CString& strTheme, const CString& strContext);		//设置气泡提示内容
	////
	BOOL	SetEditAttr(int nItem, int nSubItem, const XEditAttr_S &sEdit);	//设置EDIT的属性

	BOOL	SetEllipsis(BOOL bEllipsis)							//+++
	{
		BOOL bOldEllipsis = m_bUseEllipsis;
		m_bUseEllipsis = bEllipsis;
		return bOldEllipsis;
	}
	BOOL	SetEnabled(int nItem, BOOL bEnable);
	DWORD	SetExtendedStyleX(DWORD dwNewStyle)
	{
		DWORD dwOldStyle = m_dwExtendedStyleX;
		m_dwExtendedStyleX = dwNewStyle;
		return dwOldStyle;
	}
	void	SetHeaderAlignment(UINT nFormat) { m_HeaderCtrl.SetAlignment(nFormat); } //+++
	void	SetHeaderTextColor(COLORREF rgbText) { m_HeaderCtrl.SetTextColor(rgbText); } //+++
	void	SetHeaderBKColor(COLORREF rgbBK) { m_HeaderCtrl.SetBKColor(rgbBK); }
	BOOL	SetHeaderCheckedState(int nSubItem, int nCheckedState);
	void	SetItemCheckedState(int nItem, int nSubItem, int nCheckedState);		//+++
	int		SetItem(const LVITEM* pItem);
	void	SetItemColors(int nItem,								//+++
		int nSubItem,
		COLORREF crText,
		COLORREF crBackground);
	BOOL	SetItemData(int nItem, LPARAM dwData);
	BOOL	SetItemImage(int nItem, int nSubItem, int nImage);
	BOOL	SetItemText(int nItem, int nSubItem, LPCTSTR lpszText);
	BOOL	SetItemText(int nItem,
		int nSubItem,
		LPCTSTR lpszText,
		COLORREF crText,
		COLORREF crBackground);
	void	SetListModified(BOOL bListModified) { m_bListModified = bListModified; }	//+++
	void	SetModified(int nItem, int nSubItem, BOOL bModified);			//+++
	BOOL	SetProgress(int nItem,
		int nSubItem,
		BOOL bShowProgressText = TRUE,
		LPCTSTR lpszProgressText = NULL);
	void	UpdateProgress(int nItem, int nSubItem, int nPercent);
	void	UpdateSubItem(int nItem, int nSubItem);

#ifndef NO_XLISTCTRL_TOOL_TIPS
	void DeleteAllToolTips();
	BOOL SetItemToolTipText(int nItem, int nSubItem, LPCTSTR lpszToolTipText);
	CString GetItemToolTipText(int nItem, int nSubItem);
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
#endif

	void SetWindowColors(COLORREF crBKColor, COLORREF crTextColor)
	{
		m_crWindow = crBKColor;
		m_crWindowText = crTextColor;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiListCtrl)
public:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
// Implementation
public:
	CXHeaderCtrl	m_HeaderCtrl;
	CImageList		m_cImageList;	// Image list for the header control

protected:
	void	DrawCheckbox(int nItem,
		int nSubItem,
		CDC *pDC,
		COLORREF crText,
		COLORREF crBkgnd,
		CRect& rect,
		XLISTCTRLDATA *pCLD);
#ifndef DO_NOT_INCLUDE_XCOMBOLIST
	void	DrawComboBox(int nItem,
		int nSubItem);
#endif
	void	DrawEdit(int nItem, int nSubItem);
	int		DrawImage(int nItem,
		int nSubItem,
		CDC* pDC,
		COLORREF crText,
		COLORREF crBkgnd,
		CRect rect,
		XLISTCTRLDATA *pXLCD);
	void	DrawProgress(int nItem,
		int nSubItem,
		CDC *pDC,
		COLORREF crText,
		COLORREF crBkgnd,
		CRect& rect,
		XLISTCTRLDATA *pCLD);
	void	DrawText(int nItem,
		int nSubItem,
		CDC *pDC,
		COLORREF crText,
		COLORREF crBkgnd,
		CRect& rect,
		XLISTCTRLDATA *pCLD);
	void	GetColors();
	void	GetDrawColors(int nItem,
		int nSubItem,
		COLORREF& colorText,
		COLORREF& colorBkgnd);
	void	SubclassHeaderControl();

	BOOL			m_bHeaderIsSubclassed;
	BOOL			m_bUseEllipsis;			//+++
	BOOL			m_bListModified;		//+++
	DWORD			m_dwExtendedStyleX;
	int				m_nPadding;				//+++
	CString			m_strInitialString;		// used to save the initial string
											// for edit and combo fields
	BOOL			m_bInitialCheck;		// initial check state of a checkbox field
	BOOL			m_bGridLines;

	// for edit box 
	//CXEdit *		m_pEdit;  //+++
	CXEdit m_Edit;
	BOOL m_bError;	//判断输入的参数是否错的标志
	int				m_nEditItem;
	int				m_nEditSubItem;

#ifndef DO_NOT_INCLUDE_XCOMBOLIST	//-----------------------------------------
	BOOL			m_bComboIsClicked;
	int				m_nComboItem;
	int				m_nComboSubItem;
	CRect			m_rectComboButton;
	CRect			m_rectComboList;
	CXCombo *		m_pCombo;
	CFont			m_ListboxFont;
	BOOL			m_bFontIsCreated;
#endif	//---------------------------------------------------------------------

	COLORREF		m_cr3DFace;
	COLORREF		m_cr3DHighLight;
	COLORREF		m_cr3DShadow;
	COLORREF		m_crActiveCaption;
	COLORREF		m_crBtnFace;
	COLORREF		m_crBtnShadow;
	COLORREF		m_crBtnText;
	COLORREF		m_crGrayText;
	COLORREF		m_crHighLight;
	COLORREF		m_crHighLightText;
	COLORREF		m_crInactiveCaption;
	COLORREF		m_crInactiveCaptionText;
	COLORREF		m_crWindow;
	COLORREF		m_crWindowText;
	// Generated message map functions
protected:
	//{{AFX_MSG(CMultiListCtrl)
	afx_msg BOOL OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//}}AFX_MSG
#ifndef DO_NOT_INCLUDE_XCOMBOLIST
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnComboEscape(WPARAM, LPARAM);
	afx_msg LRESULT OnComboComplete(WPARAM, LPARAM);
#endif

#ifndef NO_XLISTCTRL_TOOL_TIPS
	virtual afx_msg BOOL OnToolTipText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
#endif

	afx_msg LRESULT OnXEditKillFocus(WPARAM, LPARAM);
	afx_msg LRESULT OnXEditEscape(WPARAM, LPARAM);
	afx_msg LRESULT OnEditError(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);

public:
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XLISTCTRL_H
