#if !defined(AFX_DLGLOGQUERY_H__F35276D6_900D_4433_8BB9_BE720AD90B11__INCLUDED_)
#define AFX_DLGLOGQUERY_H__F35276D6_900D_4433_8BB9_BE720AD90B11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogQuery dialog

class CDlgLogQuery : public CDialog
{
// Construction
public:
	CDlgLogQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogQuery)
	enum { IDD = IDD_DIALOG_QUERY };
	CComboBox	m_cmbTPD;
	CComboBox	m_cmbArmType;
	CComboBox	m_cmbUser;
	CListCtrl	m_lstUserLog;
	CListCtrl	m_lstAlarm;
	CListCtrl	m_lstTPD;
	CDateTimeCtrl	m_dtEnd;
	CDateTimeCtrl	m_dtBeg;
	COleDateTime	m_DateBeg;
	COleDateTime	m_DateEnd;
	CTime	m_TimeBeg;
	CTime	m_TimeEnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogQuery)
	afx_msg void OnButtonUserLogQuery();
	afx_msg void OnButtonTPD();
	afx_msg void OnButtonAlarmLogQuery();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonUser();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgQueryMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgAlarmInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgAlamCount(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUserLog(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUserLogCount(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgTPD(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgTPDCount(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	//message
	static void CALLBACK FUNQueryMsgCB(int nMsg, int nParam, void* pUsr);
	void	DoQueryMsgCB(int nMsg, int nParam);

	//alarm
	static void CALLBACK FUNVehiAlarmCB(const GPSVehicleAlarm_S* pAlarm, void* pUsr);
	void	DoVehiAlarmCB(const GPSVehicleAlarm_S* pAlarm);
	static void CALLBACK FUNVehiArmCountCB(const GPSAlarmCount_S* pAlarmCount, void* pUsr);
	void	DoVehiArmCountCB(const GPSAlarmCount_S* pAlarmCount);

	//user
	static void CALLBACK FUNDownUsrMsgCB(int nType, void* pData, void * pUsr);
	void	DoDownUsrMsg(int nType, void* pData);

	//transparent port
	static void CALLBACK FUNTransPortDataCB(GPSTranPortData_S* pData, void* pUsr);
	void	DoFUNTransPortDataCB(GPSTranPortData_S* pAlarm);
	static void CALLBACK FUNTransPortDataCountCB(const GPSTranPortDataCount_S* pCount, void* pUsr);
	void	DoTransPortDataCountCB(const GPSTranPortDataCount_S* pCount);

	//user log
	static void CALLBACK FUNUsrLogCB(const GPSUsrLog_S* pUserLog, void* pUsr);
	void	DoUsrLogCB(const GPSUsrLog_S* pUserLog);
	static void CALLBACK FUNUsrLogCountCB(const GPSUsrLogCount_S* pUserLogCount, void* pUsr);
	void	DoUsrLogCountCB(const GPSUsrLogCount_S* pUserLogCount);

	void DeleteLogList(int nType);
	void InitAlarmTypeCmb();

	void InitAlarmList();
	void ShowAlarmInfo(GPSVehicleAlarm_S* pAlarm);
	void InsertListVehiAlarm(GPSVehicleAlarm_S* pAlarm, int nIndex);

	void InitUserLogList();
	void ShowUserLog(GPSUsrLog_S* pAlarm);

	void InitTPDList();
	void ShowTPD(GPSTranPortData_S* pAlarm);
private:
	long m_lTPDQuery;
	long m_lAlarmQuery;
	long m_lUserLogQuery;
	long m_lDownUsrList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGQUERY_H__F35276D6_900D_4433_8BB9_BE720AD90B11__INCLUDED_)
