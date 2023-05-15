// PathManager.h: interface for the CPathManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHMANAGER_H__4B5D2FC7_B7FA_470D_B9CB_8EB41323DBA5__INCLUDED_)
#define AFX_PATHMANAGER_H__4B5D2FC7_B7FA_470D_B9CB_8EB41323DBA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//class CGlobalBrush;
class CImgBase;
class CPathManager : public CStaticObject<CPathManager>
{
public:
	CPathManager();
	virtual ~CPathManager();

	int GetUIStyle() const;

	CString GetImgPath();
	CString GetCommImgPath();
	CString GetLogPath();
	void DrawWndPopoTitle(HDC hDC, CRect rcClient, int nIsTitle);
	void DrawDlgPopupBase(HDC hDC, CRect rcClient);
	BOOL IsFlatDesign();
	DWORD GetDlgTitleTextColor();

	DWORD	GetRGBDlgPopupBase() { return m_dwRGBDlgPopupBase; }
	DWORD	GetRGBDlgPopupBaseBK() { return m_dwRGBDlgPopupBaseBK; }
	DWORD	GetRGBDlgPopupBaseCtrlBK() { return m_dwRGBDlgPopupBaseCtrlBK; }
	DWORD	GetRGBDlgPopupBaseCtrlText() { return m_dwRGBDlgPopupBaseCtrlText; }

	HBRUSH	GetRGBDlgPopupBaseHBrush();
	HBRUSH	GetRGBDlgPopupBaseBKHBrush();
	HBRUSH	GetRGBDlgPopupBaseCtrlBKHBrush();
	HBRUSH	GetRGBDlgPopupBaseCtrlTextHBrush();

	DWORD GetRGBBtnNormalText() { return m_dwRGBBtnNormalText; }
	DWORD GetRGBBtnOverText() { return m_dwRGBBtnOverText; }
	DWORD GetRGBBtnHilightText() { return m_dwRGBBtnHilightText; }
	DWORD GetRGBBtnHilightText2() { return m_dwRGBBtnHilightText2; }
	DWORD GetRGBBtnDisabledText() { return m_dwRGBBtnDisabledText; }

	DWORD GetRGBCheckState() { return m_dwRGBCheckState; }
	DWORD GetRGBTextColor() { return m_dwRGBTextColor; }

	DWORD GetRGBGroupText() { return m_dwRGBGroupText; }
	DWORD GetRGBBorder() { return m_dwRGBBorder; }
	DWORD GetRGBGroupBK() { return m_dwRGBGroupBK; }
	DWORD GetBroderStyle() { return m_dwBroderStyle; }

	BOOL GetButtonZoomSize() { return m_dwDPIButtonSizeZoom; }

	//当窗口分段时,左侧背景色
	DWORD GetRGBDlgLeftBK() { return m_dwRGBDlgLeft; }

	DWORD GetRGBEditText() { return m_dwRGBEditText; }
	DWORD GetRGBEditTextBK() { return m_dwRGBEditTextBK; }
	DWORD GetRGBEditTextBKDisabled() { return m_dwRGBEditTextBKDisabled; }

	BOOL IsDlgShowIcon() const;
	CImgBase* GetImgShowIcon();
	

private:
	void InitUIPath();
	int	InitUIStyle();
	void InitUIRGB();
	void InitDefaultUI();
	void InitBlueUI();
	int GetUIColor(LPCTSTR lpszKey, int nColor);
	// 获取整数值
	int GetUIColorEx(LPCTSTR lpszKey, int nValue);
	void SplitStringToIntEx(CString str, const TCHAR* strSeps, DWORD* pData);

private:
	//CGlobalBrush* m_pGlobalBrush;
	TCHAR m_strImgPath[MAX_PATH];
	TCHAR m_strCommImgPath[MAX_PATH];
	TCHAR m_strLogPath[MAX_PATH];
	 
	//CString m_strImgPath;
	//CString m_strCommImgPath;
	//CString m_strLogPath;
	int m_nUIStyle;

	//弹出窗口标题
	DWORD m_dwRGBWndPopoTitle[3];
	DWORD m_dwRGBWndPopoBottom[2];

	//弹出窗口边框颜色
	DWORD m_dwRGBDlgPopupBase;
	//弹出窗口背景颜色
	DWORD m_dwRGBDlgPopupBaseBK;
	//弹出窗口控件背景颜色(主要为CStatic)
	DWORD m_dwRGBDlgPopupBaseCtrlBK;
	//弹出窗口控件文本颜色(主要为CStatic)
	DWORD m_dwRGBDlgPopupBaseCtrlText;

	//左侧背景色
	DWORD m_dwRGBDlgLeft;

	//是否扁平风格
	int m_nFlatDesign;

	//listctrl颜色
	DWORD m_dwRGBListItemBK[2];
	DWORD m_dwRGBListHeadCtrlBK[2];
	DWORD m_dwRGBListItemBKFocus[2];

	// 按钮文本颜色
	DWORD m_dwRGBBtnNormalText;
	DWORD m_dwRGBBtnOverText;
	DWORD m_dwRGBBtnHilightText;
	DWORD m_dwRGBBtnHilightText2;
	DWORD m_dwRGBBtnDisabledText;

	// GUICheckBox
	DWORD m_dwRGBCheckState;
	DWORD m_dwRGBTextColor;

	// Group Static
	DWORD m_dwRGBGroupText;
	DWORD m_dwRGBBorder;
	DWORD m_dwRGBGroupBK;
	DWORD m_dwBroderStyle;

	// DPI 
	DWORD m_dwDPIButtonSizeZoom;

	// ImgEdit
	DWORD m_dwRGBEditText;
	DWORD m_dwRGBEditTextBK;
	DWORD m_dwRGBEditTextBKDisabled;

	// 窗口显示图标
	BOOL m_bIsDlgShowIcon;
	int m_nDlgShowIconID;

	CImgBase* m_pImgShowIcon;
};


inline CString GetThemePath()
{
	return CPathManager::GetInstance()->GetImgPath();
}
inline CString GetThemeCommPath()
{
	return CPathManager::GetInstance()->GetCommImgPath();
}
inline CString GetThemeLogPath()
{
	return CPathManager::GetInstance()->GetLogPath();
}

CString GetValidImgFilePath(LPCTSTR szPath, BOOL bCheckDPI = FALSE, int* pnBaseDPI = NULL);

#endif // !defined(AFX_PATHMANAGER_H__4B5D2FC7_B7FA_470D_B9CB_8EB41323DBA5__INCLUDED_)
