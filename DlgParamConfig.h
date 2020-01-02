#pragma once


// CDlgParamConfig 对话框

class CDlgParamConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgParamConfig)

public:
	CDlgParamConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgParamConfig();

// 对话框数据
	enum { IDD = IDD_DLG_PARAM_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnParamFileGet();
	afx_msg void OnBnClickedBtnParamFileUpdate();
	afx_msg void OnBnClickedBtnParamFileSet();
	afx_msg void OnBnClickedBtnParamFileClose();
	DECLARE_MESSAGE_MAP()


	//////////////////////////////////////////////////////////////////////////
	static void CALLBACK FUNGetDevParamerMsgCB(int nMsg, int nParam, void* pUsr);
	void DoGetDevParamerMsgCB(int nMsg, int nParam);
	LRESULT OnMsgParamGetMsg(WPARAM wParam, LPARAM lParam);

	static void CALLBACK FUNDataCB(const char* pData, int nDataLen, long nPos, void* pUsr);
	void DoDataCB(const char* pBuf, int nLen, long nPos);

	void StopGetDevParamer();
	void OpenDownFile();

	void CloseDownFile();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//开始上传
	void StartUpload();
	static void CALLBACK FUNUploadMsgCB(int nMsg, int nParam, void* pUsr);
	void DoUploadMsgCB(int nMsg, int nParam);

	LRESULT OnUpLoadMsg(WPARAM wParam, LPARAM lParam);

	void StopUpload();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	void StartDownLoadToDevice();
	static  void CALLBACK FUNPromoteMsgCB(int nMsg, int nParam, void* pUsr);
	void	DoPromoteMsgCB(int nMsg, int nParam);
	afx_msg LRESULT OnMsgPromote(WPARAM wParam, LPARAM lParam);
	void StopPromote();

public:
	void SetDevID(int nDevID);
private:
	int m_nDevID;
	CString m_strParamConfigFile;

	long m_lGetParamHandle;
	FILE* m_pFile;

	long m_lUploadHandle;
	int m_nlpSvrID;

	long m_lPromoteHanle;
	TCHAR m_szSvrFile[MAX_PATH];
public:
};
