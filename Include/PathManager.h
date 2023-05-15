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

	//�����ڷֶ�ʱ,��౳��ɫ
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
	// ��ȡ����ֵ
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

	//�������ڱ���
	DWORD m_dwRGBWndPopoTitle[3];
	DWORD m_dwRGBWndPopoBottom[2];

	//�������ڱ߿���ɫ
	DWORD m_dwRGBDlgPopupBase;
	//�������ڱ�����ɫ
	DWORD m_dwRGBDlgPopupBaseBK;
	//�������ڿؼ�������ɫ(��ҪΪCStatic)
	DWORD m_dwRGBDlgPopupBaseCtrlBK;
	//�������ڿؼ��ı���ɫ(��ҪΪCStatic)
	DWORD m_dwRGBDlgPopupBaseCtrlText;

	//��౳��ɫ
	DWORD m_dwRGBDlgLeft;

	//�Ƿ��ƽ���
	int m_nFlatDesign;

	//listctrl��ɫ
	DWORD m_dwRGBListItemBK[2];
	DWORD m_dwRGBListHeadCtrlBK[2];
	DWORD m_dwRGBListItemBKFocus[2];

	// ��ť�ı���ɫ
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

	// ������ʾͼ��
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
