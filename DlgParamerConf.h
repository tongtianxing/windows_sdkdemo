#if !defined(AFX_DLGPARAMERCONF_H__076FA8A8_FEA6_4929_A0C4_431E71D64D5A__INCLUDED_)
#define AFX_DLGPARAMERCONF_H__076FA8A8_FEA6_4929_A0C4_431E71D64D5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgParamerConf.h : header file
//
#include "DlgLoading.h"


typedef struct _tagMDVRConfigData
{
	int nLength;
	char cBuffer[1024];
}MDVRConfigData_S, *LPMDVRConfigData_S;

// 新增 [2016-10-19 ydl]
typedef struct _tagMDVRConfigDataEx
{
	int nLength;
	char cBuffer[2048];
}MDVRConfigDataEx_S, *LPMDVRConfigDataEx_S;

typedef BOOL (CALLBACK* FUNTransparentConfig)(int nType, MDVRConfigData_S* lpInConfig, MDVRConfigData_S* lpOutConfig, void* pUsr);

extern int g_nMapType;
extern CString g_strJingDu;
extern CString g_strWeiDu;


extern FUNTransparentConfig g_pfnTransparentConfig;
extern void*	g_pTransparentUser;

typedef void CPluginDeviceConfigEntity;

/////////////////////////////////////////////////////////////////////////////
// CDlgParamerConf dialog
/*class CDlgLoading;*/

class CDlgAueAlcoholSetup;
class CDlgAueCheckedSetup;
class CDlgAueCoordinateSetup;
class CDlgAueWifiSetup;
class CDlgParamerConf : public CDialog
{
// Construction
public:
	CDlgParamerConf(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgParamerConf)
	enum { IDD = IDD_DLG_PARAMER_CONFIG };
		// NOTE: the ClassWizard will add data members here
	CButton m_btnExport;
	CButton m_btnImport;
	CButton m_btnSaveMut;
	CButton m_btnSave;
	CButton m_btnCancel;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgParamerConf)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgParamerConf)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButSave();
	afx_msg void OnButSaveMut();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnGetParameterMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpLoadMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgPromote(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgGetParam(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgSetParam(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgShowDispaly(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	//设备ID
	void SetDevice(int nDevID) {	m_nDevID = nDevID;	}
	void SetTransparenParam(BOOL bTransparenParam=TRUE) { m_bTransparenParam = bTransparenParam; }

	void SetAueFunction(BOOL bEnable, int nMapType, LPCTSTR lpszJingDu, LPCTSTR lpszWeiDu);

protected:
	void Loadlanguage();
	//获取参数
	static void CALLBACK FUNGetDevParamerMsgCB(int nMsg, int nParam, void* pUsr);
	void   DoGetDevParamerMsgCB(int nMsg, int nParam);
    static void CALLBACK FUNDataCB(const char* pBuf, int nLen, long nPos, void* pUsr);
	void DoDataCB(const char* pBuf, int nLen, long nPos);
    BOOL StartGetDevParamer();
	void StopGetParmer();

	//上传服务器
	void    StopUpload();//释放资源
    void    StartUpload();//开始上传
    void    StartContinueUpload();	//继续开始上传
	static  void CALLBACK FUNUploadMsgCB(int nMsg, int nParam, void* pUsr);
	void    DoUploadMsgCB(int nMsg, int nParam);

	//下传设备
	static  void CALLBACK FUNPromoteMsgCB(int nMsg, int nParam, void* pUsr);
	void	DoPromoteMsgCB(int nMsg, int nParam);
	void    StartDownLoadToDevice();
	void    StartContinueDownLoadToDevice();
	void    StopPromote();
	
	void    OpenDownFile();
	void    CloseDownFile();

	void    EnableCtrl(BOOL bFlag);

	BOOL    ExitPublic();

	void    ParmerConfError(); //当获取参数、上传服务器、设备配置直接发生消息错误时的处理.
	void	ShowDlgLoading(BOOL bShow);

protected:
	static BOOL CALLBACK FUNTransparentConfig(int nType, MDVRConfigData_S* lpInConfig, MDVRConfigData_S* lpOutConfig, void* pUsr);
	static BOOL CALLBACK FUNTransparentConfigEx(int nType, MDVRConfigDataEx_S* lpInConfig, MDVRConfigDataEx_S* lpOutConfig, void* pUsr);
	BOOL DoTransparentConfig(int nType, MDVRConfigDataEx_S* lpInConfig, MDVRConfigDataEx_S* lpOutConfig);


	static BOOL CALLBACK FUNLoadConfigFile(BOOL bInput, const char* szCfgFile, void* pUsr);
	BOOL	DoLoadConfigFile(BOOL bInput, const char* szCfgFile);

	static void CALLBACK FUNGetDevConfig(GPSMCMsg_S* pMsg, void* pUsr);
	void	DoGetDevConfig(GPSMCMsg_S* pMsg);
	//关闭句柄
	void	CloseGetParamHandle();

	static void CALLBACK FUNSetDevConfig(GPSMCMsg_S* pMsg, void* pUsr);
	void	DoSetDevConfig(GPSMCMsg_S* pMsg);
	void	CloseSetParamHandle();

private:
	int		m_nDevID;
	int     m_nlpSvrID;	
	TCHAR	m_szFileName[MAX_PATH];	//A
	TCHAR	m_szSaveFileName[MAX_PATH];	//B
	char    m_szUploadDestFile[MAX_PATH];
	FILE*	m_pFile;
	FILE*   m_pSaveFile;
	BOOL    m_bFlag;

	GPSDEVUpgradeFile_S m_FileInfo;

	long	m_lParamerConfHandle;//设备获取参数
	long    m_lUploadHandle; 
//    long    m_lpSetDevCfg;
	long    m_lPromoteHanle;
	CDlgLoading* m_pDlgLoading;
	TCHAR	m_szExportCfgFile[MAX_PATH];

	HWND    m_hSheetWnd;
	CWnd*   m_pWnd;

	BOOL    m_bContinuePromote;
	BOOL    m_bContinueUpload;

    int     m_nFirstCount; 
	BOOL    m_bFlagIsImPort;

	long	m_lGetParamHandle;
	long	m_lSetParamHandle;
	//	CDlgLoading	m_dlgLoading;
	GPSConfigDataEx_S	m_ConfigData;
	BOOL	m_bGetParamSuc;
	int		m_nGetParamResult;
	BOOL	m_bSetParamSuc;
	BOOL	m_bIsTransparenEx;

	CPluginDeviceConfigEntity* m_pConfigEntity;

	//是否是透传参数
	BOOL	m_bTransparenParam;	//cooint有2种参数模式，文件和透传

	HANDLE m_hEventParam;

	// Aue校车定制功能
	BOOL	m_bAueCoordinate;


	CDlgAueAlcoholSetup* m_pDlgAueAlcoholSetup;
	CDlgAueCheckedSetup* m_pDlgAueCheckedSetup;
	CDlgAueCoordinateSetup* m_pDlgAueCoordinateSetup;
	CDlgAueWifiSetup* m_pDlgAueWifiSetup;
public:
	afx_msg void OnBnClickedButtonAueWifi();
	afx_msg void OnBnClickedButtonAueChecked();
	afx_msg void OnBnClickedButtonAueAlcohol();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPARAMERCONF_H__076FA8A8_FEA6_4929_A0C4_431E71D64D5A__INCLUDED_)
