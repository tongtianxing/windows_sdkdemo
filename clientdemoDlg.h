// clientdemoDlg.h : header file
//

#if !defined(AFX_CLIENTDEMODLG_H__B2B5E174_29A2_481D_A667_0788D78A0C88__INCLUDED_)
#define AFX_CLIENTDEMODLG_H__B2B5E174_29A2_481D_A667_0788D78A0C88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SubVehiStatus.h"
#include "SubVehiAlarm.h"
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CClientdemoDlg dialog
class CDlgPaneView;
class CSearch;
class CDownFile;
class CPlayback;
class CDownSnapshot;
class CDlgPanePtz;
class CClientdemoDlg : public CDialog
{
// Construction
public:
	CClientdemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientdemoDlg)
	enum { IDD = IDD_CLIENTDEMO_DIALOG };
	CComboBox	m_cmbDev;
	CListBox	m_lstGPS;
	CTreeCtrl	m_treeDev;
//	CString m_strSearchDevIDNO;
	CComboBox m_cmbSearchChannel;
	CComboBox m_cmbLocation;
	CComboBox m_cmbFileType;
	CComboBox m_cmbFileAttribute;
	COleDateTime	m_DataBeg;
	COleDateTime	m_DataEnd;

	CListCtrl m_lstSearch;
	CListCtrl m_lstSearchLog;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientdemoDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientdemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnDblclkTreeDev(NMHDR* pNMHDR, LRESULT* pResult);	afx_msg void OnBtnSearch();
	afx_msg void OnButtonQuery();
	afx_msg void OnButtonGetColore();
	afx_msg void OnButtonSetColore();
	afx_msg void OnButtonTrackBack();
	afx_msg void OnButtonTransParam();
	afx_msg void OnButtonGetDevIp();
	afx_msg void OnButtonGetSnapshot();
	afx_msg void OnButtonSetSnapshot();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonPlayback();
	afx_msg void OnButtonClearAlarm();
	afx_msg void OnButtonPlayFile();
	afx_msg void OnButtonDeviceLogSearch();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnReadStatus();
	afx_msg void OnButtonTrns();
	afx_msg void OnButtonAddSnapshot();
	afx_msg void OnButtonDelSnapshot();
	afx_msg void OnButtonResumeDown();
	afx_msg void OnButtonTranData();
	//}}AFX_MSG
	afx_msg LRESULT OnSubVehiAlarm(WPARAM wParm, LPARAM lParam);
	afx_msg LRESULT OnSubVehiStatus(WPARAM wParm, LPARAM lParam);
	afx_msg LRESULT OnMsgSearchMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgSearchFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgFailed(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgSuc(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgSet(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgDownload(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCmsSendMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTQMSG(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPlaybackPlayMsg(WPARAM wParm, LPARAM lParam);
	afx_msg LRESULT OnMsgSnapshot(WPARAM wParm, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	//GPS
	int		StartVehiRun();
	int		StopVehiRun();
	int		AddDevice(int nDevID, const char* szIDNO);
	void	AddDevice(mapDvsDevice mapDev);
	static void CALLBACK FUNVehiRunningCB(GPSVehicleState_S* pVecRun, void* pUsr);
	void	DoFUNVehiRunning(GPSVehicleState_S* pVecRun);

	long	m_lVehiRun;

	//video
	CDlgPaneView*	m_pDlgPaneView;
	void MoveCtrl();
	void PreviewSelectNode(BOOL bMain);
	BOOL	IsChannelItem(CTreeCtrl& tree, HTREEITEM hItem);
	

	//sub
	void StarSubVehi();
	void StopSubVehi();

	LRESULT OnDeviceInfoChangeMessage(GPSDevInfo_S* pBaseInfo);
	LRESULT OnMsgAlarmInfo(GPSVehicleAlarm_S* pVehiAlarm);
	LRESULT OnMsgDeviceStatusChange(DeviceStatusChange_S* pStatus);
	LRESULT ShowDevTran(GPSAlarmTPD_S* pNewAlarm);
	void DevTalkBackReq(CDevBase* pDevice, GPSVehicleAlarm_S* pVehiAlarm);

	//search
	void DelAllRecItem();
	int GetFileListIndex(GPSFile_S* pNewFile);

	//alarm
	void InsertListVehiAlarm(GPSVehicleAlarm_S* pVehiAlarm);

	//Snapshot plan
	void StopGetSnapshot();
	static void WINAPI FUNSnapshotPlanCB(int nType, void* pData, void * pUsr);
	void	DoSnapshotPlanCB(int nType, void* pData);
	static void WINAPI FUNSetDevSetCB(int nType, void* pData, void * pUsr);
	void DoSetDevMsg(int nType, void* pData);
	long m_lGetSnapshotPlan;
	long m_lSetSnapshotPlan;

	static void WINAPI FUNQueryMsgCB(int nMsg, void* pUsr);
	void DoQueryMsgCB(int nMsg);
	static void WINAPI FUNQueryDataCB(const char* pBuf, int nLen, void* pUsr);
	void DoQueryDataCB(const char* pBuf, int nLen);
	long m_lQueryTransparent;

	//snapshot
	void DoAlarmSnapshotFinish(CDevBase* pDevice, GPSVehicleAlarm_S* pVehiAlarm);

	//down file
	GPSFile_S* GetSelFile();
	void DownFile(GPSFile_S* pFile);

	//playback
	void Playback(GPSFile_S* pFile);

	void InitDevCombox();
	void DoSendCtrl(GPSMCMsg_S* pMsg);
	//command callback
	static	void CALLBACK FUNMCMsgCB(GPSMCMsg_S* pMsg, void* pUsr);
	void    DoCmdMsgCB(GPSMCMsg_S* pMsg);  

	//snapshot callback
	static void CALLBACK FUNShnapshotTimerDataCB(const char* szDevIDNO, int nChn, const char* pBuf, int nLen, void* pUsr);
	void ShnapshotTimerDataCB(const char* szDevIDNO, int nChn, const char* pBuf, int nLen);

	void StopVodDown();

	static void CALLBACK FUNMCReadStatusCB(GPSMCMsg_S* pMsg, void* pUsr);
	void DoReadStatus(GPSMCMsg_S* pMsg);

	//get device idno
	BOOL GetSelDev(char* szDevIDNO);

	
	void DownFile(BOOL bResumeDown);
	
	CVehicleBase* GetSelVehicle();
	CString GetSelDevIDNO();

	
	CString GetSnapshotCfg();
	UINT GetSnapshotDevTimeSecond();
	UINT GetSnapshotDevIntervalSecond();
	UINT GetSnapshotDevSnapshotNum();

	void AddSnapshot(char* szDevIDNO);
	void DelSnapshot(char* szDevIDNO);
	
public:
	BOOL PtzControl(int nCommand, int nParam, int nSpeed);

private:

	//Subscribe GPS
	CSubVehiAlarm m_subVehiAlarm;
	CSubVehiStatus m_subVehiStatus;

	//file
	CSearch* m_pFileSearch;
	
	//down file
	CDownFile* m_pDownFile;
	CPlayback* m_pPlayback;

	BOOL	m_bStopSnapshot;
	//download time
	int		m_nDownMinSecond;
	CString m_strFileDown;

	CDownSnapshot* m_pSnapshot;
	CDlgPanePtz* m_pDlgPanePtz;


public:
	afx_msg void OnBnClickedButtonAddSn();
	afx_msg void OnBnClickedButtonDelSn();
	afx_msg void OnNMRClickTreeDev(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMainFront();
	afx_msg void OnMenuSendFile();
	afx_msg void OnMenuParamerConfig();
	afx_msg void OnMenuCoordinate();
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnNMClickTreeDev(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_cmbAudio;
	afx_msg void OnBnClickedButtonAudioStart();
	afx_msg void OnBnClickedButtonAudioStop();
	afx_msg void OnBnClickedBtnFuncPtz();
	afx_msg void OnBnClickedChkPreviewRecord();
	afx_msg void OnBnClickedBtnOpenRecordPath();
	afx_msg void OnBnClickedBtnParamConfig();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMODLG_H__B2B5E174_29A2_481D_A667_0788D78A0C88__INCLUDED_)
