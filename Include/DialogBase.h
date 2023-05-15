#pragma once


struct DataEnumCtrlDPIAdapt_S
{
	double lfMix;
	HWND hParent;
	CRect rcParent;
	CRect rcParentOrig;
	//std::map<HWND, std::pair<CRect, CRect>> mapChildRect;
	std::map<std::string, std::pair<LOGFONT, HFONT>> mapFontCache;
};

// 此类仅处理窗口静态控件的风格 [2017-3-27 ydl]
class CDialogBase : public CDialog
{
public:
	CDialogBase(UINT nIDTemplate, CWnd * pParentWnd = NULL);
	~CDialogBase(void);

	virtual BOOL OnInitDialog() override;
	virtual LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam) override;

private:
	static std::map<HWND, DataEnumCtrlDPIAdapt_S> m_mapDataEnumCtrlDPIAdapt;	// 不在CDialogBase里增加成员变量

	void ScaleDPI_PreInit();
	void ScaleDPI_PostDefInit();
	void ScaleDPI_PostSubclassInit();
	virtual void ScaleDPI_PostScale() {}

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
#ifdef _WIN64
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
#endif

public:
// 	// 参数nCtrlID为控件ID
// 	void GetDlgItemWindowRect(int nCtrlID, LPRECT lpRect);
// 
// 	//
// 	void GetDlgItemClientRect(int nCtrlID, LPRECT lpRect);
// 
// 	// 
// 	BOOL ShowDlgItem(int nCtrlID, int nCmdShow);
// 
// 	//
// 	void MoveDlgItem(int nCtrlID, LPCRECT lpRect, BOOL bRepaint = TRUE);
// 
// 	//
// 	BOOL EnableDlgItem(int nCtrlID, BOOL bEnable = TRUE);
// 	
// 
// 	// CEdit控件
// 	BOOL SetEditCtrlReadOnly(int nEditID, BOOL bReadOnly = TRUE);
// 
// 	BOOL EditCtrlLimitText(int nEditID, int nChars);
};