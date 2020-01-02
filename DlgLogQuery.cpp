// DlgLogQuery.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLogQuery.h"
#include "DevBase.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogQuery dialog
#define QUERY_TYPE_ALARM	0
#define QUERY_TYPE_USER_LOG 1
#define QUERY_TYPE_TPD		2


#define WM_MSG_QUERY_MSG	WM_USER+0x1000
#define WM_MSG_ALARM_IFNO	WM_USER+0x1001
#define WM_MSG_ALARM_COUNT	WM_USER+0x1002
#define WM_MSG_USER_LOG		WM_USER+0x1003
#define WM_MSG_USER_LOG_COUNT	WM_USER+0x1004
#define WM_MSG_TPD			WM_USER+0x1005
#define WM_MSG_TPD_COUNT	WM_USER+0x1006



CDlgLogQuery::CDlgLogQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogQuery)
		// NOTE: the ClassWizard will add member initialization here
	m_lAlarmQuery = NULL;
	m_lUserLogQuery = NULL;
	m_lDownUsrList = NULL;
	m_lTPDQuery = NULL;
	m_DateBeg = COleDateTime::GetCurrentTime();
	m_DateEnd = COleDateTime::GetCurrentTime();
	m_TimeBeg = CTime(2010,1,1,0,0,0);
	m_TimeEnd = CTime(2010,1,1,23,59,59);
	
	//}}AFX_DATA_INIT
}


void CDlgLogQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogQuery)
	DDX_Control(pDX, IDC_COMBO_TPD, m_cmbTPD);
	DDX_Control(pDX, IDC_COMBO_ALARM_TYPE, m_cmbArmType);
	DDX_Control(pDX, IDC_COMBO_USER, m_cmbUser);
	DDX_Control(pDX, IDC_LIST_USER_LOG, m_lstUserLog);
	DDX_Control(pDX, IDC_LIST_ALARM, m_lstAlarm);
	DDX_Control(pDX, IDC_LIST_TPD, m_lstTPD);
	DDX_DateTimeCtrl(pDX, IDC_DATE_BEG, m_DateBeg);
	DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_DateEnd);
	DDX_DateTimeCtrl(pDX, IDC_TIME_BEG, m_TimeBeg);
	DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_TimeEnd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogQuery, CDialog)
	//{{AFX_MSG_MAP(CDlgLogQuery)
	ON_BN_CLICKED(IDC_BUTTON_TPD, OnButtonTPD)
	ON_BN_CLICKED(IDC_BUTTON_USER_LOG_QUERY, OnButtonUserLogQuery)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_LOG_QUERY, OnButtonAlarmLogQuery)
	ON_BN_CLICKED(IDC_BUTTON_USER, OnButtonUser)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_QUERY_MSG, OnMsgQueryMsg)
	ON_MESSAGE(WM_MSG_ALARM_IFNO, OnMsgAlarmInfo)
	ON_MESSAGE(WM_MSG_ALARM_COUNT, OnMsgAlamCount)
	ON_MESSAGE(WM_MSG_USER_LOG, OnMsgUserLog)
	ON_MESSAGE(WM_MSG_USER_LOG_COUNT, OnMsgUserLogCount)
	ON_MESSAGE(WM_MSG_TPD, OnMsgTPD)
	ON_MESSAGE(WM_MSG_TPD_COUNT, OnMsgTPDCount)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogQuery message handlers

void CDlgLogQuery::OnButtonUserLogQuery() 
{
	
	UpdateData();
	if (m_DateBeg > m_DateEnd)
	{
		GetDlgItem(IDC_DATE_BEG)->SetFocus();
		return ;
	}
	
	if (m_TimeBeg >= m_TimeEnd)
	{
		GetDlgItem(IDC_TIME_BEG)->SetFocus();
		return ;
	}
	int nCount = m_cmbUser.GetCount();
	if (nCount <= 0)
	{
		return;
	}
	int* pUserID = new int[nCount];
	for (int i = 0; i < m_cmbUser.GetCount(); ++i)
	{
		pUserID[i] = m_cmbUser.GetItemData(i);
	}
	//time
	SYSTEMTIME timeBeg;
	SYSTEMTIME timeEnd;
	
	timeBeg.wYear = m_DateBeg.GetYear();
	timeBeg.wMonth = m_DateBeg.GetMonth();
	timeBeg.wDay = m_DateBeg.GetDay();
	timeBeg.wHour = m_TimeBeg.GetHour();
	timeBeg.wMinute = m_TimeBeg.GetMinute();
	timeBeg.wSecond = m_TimeBeg.GetSecond();
	
	timeEnd.wYear = m_DateEnd.GetYear();
	timeEnd.wMonth = m_DateEnd.GetMonth();
	timeEnd.wDay = m_DateEnd.GetDay();
	timeEnd.wHour = m_TimeEnd.GetHour();
	timeEnd.wMinute = m_TimeEnd.GetMinute();
	timeEnd.wSecond = m_TimeEnd.GetSecond();

	m_lstUserLog.DeleteAllItems();
	NETCLIENT_OpenUsrLogQueryEx(&m_lUserLogQuery, 0, 100);
	NETCLIENT_SetUsrLogMsgCB(m_lUserLogQuery, this, FUNQueryMsgCB);
	NETCLIENT_SetUsrLogDataCB(m_lUserLogQuery, this, FUNUsrLogCB);
	NETCLIENT_SetUsrLogCountCB(m_lUserLogQuery, this, FUNUsrLogCountCB);
	NETCLIENT_StartUsrLogQuery(m_lUserLogQuery, pUserID, nCount, &timeBeg, &timeEnd);

}

void CDlgLogQuery::OnButtonTPD() 
{
	
	UpdateData();
	DeleteLogList(QUERY_TYPE_TPD);
	
	//IDNO
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	int nDevCount = mapDev.size();
	if (nDevCount < 1)
	{
		return;
	}
	GPSDeviceIDNO_S* szDevice = new GPSDeviceIDNO_S[nDevCount];
	mapVehicleBaseIter iter = mapDev.begin();
	for (int i = 0 ; i < nDevCount; ++i)
	{
		CVehicleBase* pVehi = iter->second;
		if (pVehi != NULL)
		{
			strcpy(szDevice[i].szDevIDNO, pVehi->GetMainDevIDNO());
		}
		
		iter++;
	}
	
	//time
	SYSTEMTIME timeBeg;
	SYSTEMTIME timeEnd;
	
	timeBeg.wYear = m_DateBeg.GetYear();
	timeBeg.wMonth = m_DateBeg.GetMonth();
	timeBeg.wDay = m_DateBeg.GetDay();
	timeBeg.wHour = m_TimeBeg.GetHour();
	timeBeg.wMinute = m_TimeBeg.GetMinute();
	timeBeg.wSecond = m_TimeBeg.GetSecond();
	
	timeEnd.wYear = m_DateEnd.GetYear();
	timeEnd.wMonth = m_DateEnd.GetMonth();
	timeEnd.wDay = m_DateEnd.GetDay();
	timeEnd.wHour = m_TimeEnd.GetHour();
	timeEnd.wMinute = m_TimeEnd.GetMinute();
	timeEnd.wSecond = m_TimeEnd.GetSecond();
	int nType = m_cmbTPD.GetItemData(m_cmbTPD.GetCurSel());
		
	NETCLIENT_TPOpenTransPortData(&m_lTPDQuery, 0, 190);
	NETCLIENT_TPSetTransPortMsgCB(m_lTPDQuery, this, FUNQueryMsgCB);
	NETCLIENT_TPSetTransPortDataCB(m_lTPDQuery, this, FUNTransPortDataCB);
	NETCLIENT_TPSetTransPortDataCountCB(m_lTPDQuery, this, FUNTransPortDataCountCB);
	NETCLIENT_TPStartTransPort(m_lTPDQuery, szDevice, nDevCount, nType, &timeBeg, &timeEnd);

	SAFE_DELETE_ARRAY(szDevice);
}


void CDlgLogQuery::OnButtonAlarmLogQuery() 
{
	
	UpdateData();
	DeleteLogList(QUERY_TYPE_ALARM);
	
	//IDNO
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	int nDevCount = mapDev.size();
	if (nDevCount < 1)
	{
		return;
	}
	GPSDeviceIDNO_S* szDevice = new GPSDeviceIDNO_S[nDevCount];
	mapVehicleBaseIter iter = mapDev.begin();
	for (int i = 0 ; i < nDevCount; ++i)
	{
		CVehicleBase* pVehi = iter->second;
		if (pVehi != NULL)
		{			
			strcpy(szDevice[i].szDevIDNO, pVehi->GetMainDevIDNO());
		}
		
		iter++;
	}


	//alarm type
	int szArmType[2];
	szArmType[0] = GPS_ALARM_TYPE_URGENCY_BUTTON;
	szArmType[1] = GPS_ALARM_TYPE_END_URGENCY_BUTTON;

	//time
	SYSTEMTIME timeBeg;
	SYSTEMTIME timeEnd;

	timeBeg.wYear = m_DateBeg.GetYear();
	timeBeg.wMonth = m_DateBeg.GetMonth();
	timeBeg.wDay = m_DateBeg.GetDay();
	timeBeg.wHour = m_TimeBeg.GetHour();
	timeBeg.wMinute = m_TimeBeg.GetMinute();
	timeBeg.wSecond = m_TimeBeg.GetSecond();
	
	timeEnd.wYear = m_DateEnd.GetYear();
	timeEnd.wMonth = m_DateEnd.GetMonth();
	timeEnd.wDay = m_DateEnd.GetDay();
	timeEnd.wHour = m_TimeEnd.GetHour();
	timeEnd.wMinute = m_TimeEnd.GetMinute();
	timeEnd.wSecond = m_TimeEnd.GetSecond();


	int nAlarmType = m_cmbArmType.GetItemData(m_cmbArmType.GetCurSel());

	NETCLIENT_OpenAlarmQuery(&m_lAlarmQuery, 0, 190);
	NETCLIENT_SetAlarmQueryMsgCB(m_lAlarmQuery, this, FUNQueryMsgCB);
	NETCLIENT_SetAlarmQueryDataCB(m_lAlarmQuery, this, FUNVehiAlarmCB);
	NETCLIENT_SetAlarmQueryCountCB(m_lAlarmQuery, this, FUNVehiArmCountCB);
	if (GPS_ALARM_TYPE_ALL == nAlarmType)
	{
		NETCLIENT_StartAlarmQuery(m_lAlarmQuery, szDevice, nDevCount, NULL, 0, &timeBeg, &timeEnd);
	}
 	else
 	{
 		NETCLIENT_StartAlarmQuery(m_lAlarmQuery, szDevice, nDevCount, &nAlarmType, 1, &timeBeg, &timeEnd);
 	}
	SAFE_DELETE_ARRAY(szDevice);

}

const int ALARM_VEHI_ITEM = 0;	
const int ALARM_TIME_ITEM = 1;	
const int ALARM_TYPE_ITEM = 2;	
const int ALARM_GPS_ADDRESS_ITEM = 3; 
// const int ALARM_LONG_ITEM = 3;	
// const int ALARM_LAT_ITEM = 4;	
const int ALARM_INFO_ITEM = 4;	
const int ALARM_STATUS_ITEM = 5;
//const int ALARM_CONFIRM_STA = 7;
const int ALARM_DATA_ITEM = 6;
const int ALARM_STA_ITEM = 7;
void CDlgLogQuery::InitAlarmList()
{
	DWORD styles = m_lstAlarm.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lstAlarm.SetExtendedStyle(styles );
	m_lstAlarm.InsertColumn(ALARM_VEHI_ITEM, LOADSTRINGEX(ID_STR_DLG_EVENT_LST_REAL_VEHI), LVCFMT_LEFT, 80);
	m_lstAlarm.InsertColumn(ALARM_TIME_ITEM, LOADSTRINGEX(ID_STR_DLG_EVENT_LST_ALARM_TIME), LVCFMT_LEFT, 130);
	m_lstAlarm.InsertColumn(ALARM_TYPE_ITEM, LOADSTRINGEX(ID_STR_DLG_EVENT_LST_ALARM_TYPE), LVCFMT_LEFT, 100);
	m_lstAlarm.InsertColumn(ALARM_GPS_ADDRESS_ITEM, LOADSTRINGEX(ID_STR_DLG_REC_SEARCH_LST_DOWN_REC_LOACATION), LVCFMT_LEFT, 160);
	m_lstAlarm.InsertColumn(ALARM_INFO_ITEM, LOADSTRINGEX(ID_STR_DLG_EVENT_LST_ALARM_INFO), LVCFMT_LEFT, 200);
	m_lstAlarm.InsertColumn(ALARM_STATUS_ITEM, LOADSTRINGEX(ID_STR_DLG_EVENT_LST_REAL_STATUS), LVCFMT_LEFT, 200);
}

void CDlgLogQuery::InitUserLogList()
{
	DWORD styles = m_lstAlarm.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lstUserLog.SetExtendedStyle(styles );
	m_lstUserLog.InsertColumn(0, _T("User ID"), LVCFMT_LEFT, 80);
	m_lstUserLog.InsertColumn(1, _T("time"), LVCFMT_LEFT, 200);
	m_lstUserLog.InsertColumn(2, _T("nMainType"), LVCFMT_LEFT, 130);
	m_lstUserLog.InsertColumn(3, _T("nSubType"), LVCFMT_LEFT, 100);
	m_lstUserLog.InsertColumn(4, _T("szDevIDNO"), LVCFMT_LEFT, 160);
	m_lstUserLog.InsertColumn(5, _T("info"), LVCFMT_LEFT, 200);
}

void CDlgLogQuery::InitTPDList()
{
	DWORD styles = m_lstTPD.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lstTPD.SetExtendedStyle(styles );
	m_lstTPD.InsertColumn(0, _T("DevIDNO"), LVCFMT_LEFT, 80);
	m_lstTPD.InsertColumn(1, _T("Type"), LVCFMT_LEFT, 80);
	m_lstTPD.InsertColumn(2, _T("time"), LVCFMT_LEFT, 200);
	m_lstTPD.InsertColumn(3, _T("Length"), LVCFMT_LEFT, 100);
	m_lstTPD.InsertColumn(4, _T("data"), LVCFMT_LEFT, 160);
}
BOOL CDlgLogQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitAlarmTypeCmb();
	InitAlarmList();
	InitUserLogList();
	InitTPDList();
	int nIndex = m_cmbTPD.AddString(_T("Transparent Trans"));
	m_cmbTPD.SetItemData(nIndex, 1);
	m_cmbTPD.SetCurSel(nIndex);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgLogQuery::OnButtonUser() 
{
	
	while(m_cmbUser.GetCount())
	{
		m_cmbUser.DeleteString(0);
	}
	NETCLIENT_USROpenDownUsrListEx(&m_lDownUsrList, 0);
	NETCLIENT_USRSetDownUsrListCB(m_lDownUsrList, this, FUNDownUsrMsgCB);
	NETCLIENT_USRStartDownUsrList(m_lDownUsrList);
}

void CDlgLogQuery::FUNDownUsrMsgCB(int nType, void* pData, void * pUsr)
{
	CDlgLogQuery* pThis = (CDlgLogQuery*)pUsr;
	pThis->DoDownUsrMsg(nType, pData);
}

void CDlgLogQuery::DoDownUsrMsg(int nType, void* pData)
{
	if(GPS_DOWN_CONFIG_DATA == nType || GPS_DOWN_ALL_USER_INFO == nType)
	{
		//	m_lstUser.push_back(*(UserBasicInfo_S*)pData);
		UserBasicInfo_S* pUser = (UserBasicInfo_S*)pData;
		TRACE("%d, %s\n", pUser->nUserID, pUser->szUserName);
		int nIndex = m_cmbUser.AddString(pUser->szUserName);
		m_cmbUser.SetItemData(nIndex, pUser->nUserID);
	}
	else if (GPS_DOWN_CONFIG_FAILED == nType)
	{
		//	PostLoadMessage(LOAD_FAILED);
	}
	else if (GPS_DOWN_CONFIG_SUC == nType)
	{
		//	PostLoadMessage(LOAD_USER_PRIVILEGE);
	}
}
void CDlgLogQuery::FUNQueryMsgCB(int nMsg, int nParam, void* pUsr)
{
	CDlgLogQuery* pThis = (CDlgLogQuery*)pUsr;
	pThis->DoQueryMsgCB(nMsg, nParam);
}

void CDlgLogQuery::DoQueryMsgCB(int nMsg, int nParam)
{
	PostMessage(WM_MSG_QUERY_MSG, nMsg, nParam);
}

void CDlgLogQuery::FUNVehiAlarmCB(const GPSVehicleAlarm_S* pAlarm, void* pUsr)
{
	CDlgLogQuery* pThis = (CDlgLogQuery*)pUsr;
	pThis->DoVehiAlarmCB(pAlarm);
}

void CDlgLogQuery::DoVehiAlarmCB(const GPSVehicleAlarm_S* pAlarm)
{
	GPSVehicleAlarm_S* pNewAlarm = new GPSVehicleAlarm_S;
	*pNewAlarm = *pAlarm;
	PostMessage(WM_MSG_ALARM_IFNO, (WPARAM)pNewAlarm, 0);
}

void CDlgLogQuery::FUNVehiArmCountCB(const GPSAlarmCount_S* pAlarmCount, void* pUsr)
{
	CDlgLogQuery* pThis = (CDlgLogQuery*)pUsr;
	pThis->DoVehiArmCountCB(pAlarmCount);
}
void CDlgLogQuery::DoVehiArmCountCB(const GPSAlarmCount_S* pAlarmCount)
{
	GPSAlarmCount_S* pNewAlarmCount = new GPSAlarmCount_S;
	memcpy(pNewAlarmCount, pAlarmCount, sizeof(GPSAlarmCount_S));
	/**pNewAlarmCount = *pAlarmCount;*/
	PostMessage(WM_MSG_ALARM_COUNT, (WPARAM)pNewAlarmCount, 0);
}


void CDlgLogQuery::FUNTransPortDataCB(GPSTranPortData_S* pAlarm, void* pUsr)
{
	CDlgLogQuery* pThis = (CDlgLogQuery*)pUsr;
	pThis->DoFUNTransPortDataCB(pAlarm);
}

void CDlgLogQuery::DoFUNTransPortDataCB(GPSTranPortData_S* pAlarm)
{
	GPSTranPortData_S* pNewAlarm = new GPSTranPortData_S;
	*pNewAlarm = *pAlarm;
	PostMessage(WM_MSG_TPD, (WPARAM)pNewAlarm, 0);
}

void CDlgLogQuery::FUNTransPortDataCountCB(const GPSTranPortDataCount_S* pAlarmCount, void* pUsr)
{
	CDlgLogQuery* pThis = (CDlgLogQuery*)pUsr;
	pThis->DoTransPortDataCountCB(pAlarmCount);
}
void CDlgLogQuery::DoTransPortDataCountCB(const GPSTranPortDataCount_S* pAlarmCount)
{
	GPSTranPortDataCount_S* pNewAlarmCount = new GPSTranPortDataCount_S;
	*pNewAlarmCount = *pAlarmCount;
	PostMessage(WM_MSG_TPD_COUNT, (WPARAM)pNewAlarmCount, 0);
}

LRESULT CDlgLogQuery::OnMsgAlamCount(WPARAM wParam, LPARAM lParam)
{
	GPSAlarmCount_S* pAlarmCount = (GPSAlarmCount_S*)wParam;
	CString str;
	str.Format(_T("Count:%d"), pAlarmCount->nCount);
	GetDlgItem(IDC_STATIC_ALARM_LOG_COUNT)->SetWindowText(str);
	UpdateData(FALSE);
	return 0;
}

LRESULT CDlgLogQuery::OnMsgUserLogCount(WPARAM wParam, LPARAM lParam)
{
	GPSUsrLogCount_S* pUserLogCount = (GPSUsrLogCount_S*)wParam;
	CString str;
	str.Format(_T("Count:%d"), pUserLogCount->nCount);
	GetDlgItem(IDC_STATIC_USER_LOG_COUNT)->SetWindowText(str);
	UpdateData(FALSE);
	return 0;
}

LRESULT CDlgLogQuery::OnMsgTPDCount(WPARAM wParam, LPARAM lParam)
{
	GPSTranPortDataCount_S* pUserLogCount = (GPSTranPortDataCount_S*)wParam;
	CString str;
	str.Format(_T("Count:%d"), pUserLogCount->nCount);
	GetDlgItem(IDC_STATIC_TPD_COUNT)->SetWindowText(str);
	UpdateData(FALSE);
	return 0;
}

LRESULT CDlgLogQuery::OnMsgQueryMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case GPS_DOWNLOAD_MSG_FAILED:
		{
			GetDlgItem(IDC_STATIC_TIP)->SetWindowText(_T("Failed"));
			
		}
		break;
	case GPS_DOWNLOAD_MSG_FINISHED:
		{
			GetDlgItem(IDC_STATIC_TIP)->SetWindowText(_T("Success"));
		}
		break;
	}

	UpdateData(FALSE);
	return 0;
}

LRESULT CDlgLogQuery::OnMsgAlarmInfo(WPARAM wParam, LPARAM lParam)
{
	GPSVehicleAlarm_S* pVehiAlarm  = (GPSVehicleAlarm_S*)wParam;
	ShowAlarmInfo(pVehiAlarm);
	delete pVehiAlarm;
	pVehiAlarm = NULL;
	return 0;
}

void CDlgLogQuery::FUNUsrLogCB(const GPSUsrLog_S* pUserLog, void* pUsr)
{
	CDlgLogQuery* pThis = (CDlgLogQuery*)pUsr;
	pThis->DoUsrLogCB(pUserLog);
}
void CDlgLogQuery::DoUsrLogCB(const GPSUsrLog_S* pUserLog)
{
	GPSUsrLog_S* pNewUserLog = new GPSUsrLog_S;
	*pNewUserLog = *pUserLog;
	PostMessage(WM_MSG_USER_LOG, (WPARAM)pNewUserLog, 0);
}
void CDlgLogQuery::FUNUsrLogCountCB(const GPSUsrLogCount_S* pUserLogCount, void* pUsr)
{
	CDlgLogQuery* pThis = (CDlgLogQuery*)pUsr;
	pThis->DoUsrLogCountCB(pUserLogCount);
}
void CDlgLogQuery::DoUsrLogCountCB(const GPSUsrLogCount_S* pUserLogCount)
{
	GPSUsrLogCount_S* pNewUserLogCount = new GPSUsrLogCount_S;
	*pNewUserLogCount = *pUserLogCount;
	PostMessage(WM_MSG_USER_LOG_COUNT, (WPARAM)pNewUserLogCount, 0);
}

LRESULT CDlgLogQuery::OnMsgTPD(WPARAM wParam, LPARAM lParam)
{
	GPSTranPortData_S* pUserLog  = (GPSTranPortData_S*)wParam;
	ShowTPD(pUserLog);
	delete pUserLog;
	pUserLog = NULL;
	return 0;
	
}
LRESULT CDlgLogQuery::OnMsgUserLog(WPARAM wParam, LPARAM lParam)
{
	GPSUsrLog_S* pUserLog  = (GPSUsrLog_S*)wParam;
	ShowUserLog(pUserLog);
	delete pUserLog;
	pUserLog = NULL;
	return 0;
	
}
void CDlgLogQuery::InitAlarmTypeCmb()
{
	while(m_cmbArmType.GetCount())
	{
		m_cmbArmType.DeleteString(0);
	}
	int nIndex = 0;
	nIndex = m_cmbArmType.AddString(_T("ALL"));
	m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_ALL);
	{
		nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_URGENCY_BUTTON));
		m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_URGENCY_BUTTON);
	}
	nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_SHAKE));
	m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_SHAKE);
	nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_VIDEO_LOST));
	m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_VIDEO_LOST);
	nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_DISK_ERROR));
	m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_DISK_ERROR);
	

	nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_MOTION_DETECT));
	m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_MOTION);
	
	{

		nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_GPS_SIGNAL_LOSS));
		m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_GPS_SIGNAL_LOSS);
		
		
		{
			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_DOOR_OPEN_LAWLESS));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_DOOR_OPEN_LAWLESS);
			
			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_OVERSPEED));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_OVERSPEED);
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_PARK_TOO_LONG));	
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_PARK_TOO_LONG);
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_TEMPERATOR));	
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_TEMPERATOR);
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_EVENT_TYPE_REFUEL));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_REFUEL);
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_EVENT_TYPE_STILL_FUEL));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_STILL_FUEL);
			
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN_OVER_SPEED));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_IN_FENCE_OVER_SPEED);
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN_LOWE_SPEED));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_IN_FENCE_LOW_SPEED);
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN_STOP));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_IN_FENCE_STOP);
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT_OVER_SPEED));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_OUT_FENCE_OVER_SPEED);
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT_LOWE_SPEED));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_OUT_FENCE_LOW_SPEED);
			

			nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT_STOP));
			m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_OUT_FENCE_STOP);
			
		}
		

		nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN));
		m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_IN_FENCE);
		

		nIndex = m_cmbArmType.AddString(LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT));
		m_cmbArmType.SetItemData(nIndex, GPS_ALARM_TYPE_OUT_FENCE);
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	//	m_nAlarmTypeCount = nIndex+1;
	
	m_cmbArmType.SetCurSel(0);
}

void CDlgLogQuery::ShowAlarmInfo(GPSVehicleAlarm_S* pVehiAlarm)
{
	int nCount = m_lstAlarm.GetItemCount();
	int nIndex = 0;
	InsertListVehiAlarm(pVehiAlarm, nIndex);
}

void CDlgLogQuery::InsertListVehiAlarm(GPSVehicleAlarm_S* pVehiAlarm, int nIndex)
{
	CVehicleBase* pDevice = CVehicleBaseMgr::GetInstance()->FindVehicleFromDev(pVehiAlarm->szDevIDNO);
	m_lstAlarm.InsertItem(nIndex, NULL);
	
	GPSVehicleGps_S* pGps = &(pVehiAlarm->Alarm.Gps);
	if (pDevice)
	{
		CString str = pDevice->GetShowName();
		m_lstAlarm.SetItemText(nIndex, ALARM_VEHI_ITEM, pDevice->GetShowName());
	}
	else
	{
		m_lstAlarm.SetItemText(nIndex, ALARM_VEHI_ITEM, CString(pVehiAlarm->szDevIDNO));
	}
	
	CString strTime;
	
	if (pVehiAlarm->Alarm.AlarmType == GPS_ALARM_TYPE_DOWN_FINISH)
	{
		GPSTime_S& Time = pVehiAlarm->Alarm.srcTime;
		strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), 
			Time.ucYear + 2000, Time.ucMonth, Time.ucDay, Time.ucHour, Time.ucMinute, Time.ucSecond);
	}
	else
	{
		GPSTime_S& Time = pVehiAlarm->Alarm.Time;
		strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), 
			Time.ucYear + 2000, Time.ucMonth, Time.ucDay, Time.ucHour, Time.ucMinute, Time.ucSecond);
	}
	m_lstAlarm.SetItemText(nIndex, ALARM_TIME_ITEM, strTime);
	
	CString strAlarmDesc, strAlarmType;
	FormatAlarm2String(pVehiAlarm->Alarm, strAlarmType, strAlarmDesc, pDevice->GetMainDevice());
	m_lstAlarm.SetItemText(nIndex, ALARM_TYPE_ITEM, strAlarmType);
	m_lstAlarm.SetItemText(nIndex, ALARM_INFO_ITEM, strAlarmDesc);
	
	if (pGps != NULL)
	{
		m_lstAlarm.SetItemText(nIndex, ALARM_GPS_ADDRESS_ITEM, FormatGPSToStr(*pGps));
		CString strNormalStatus, strAlarmStatus;
		FormatStatus2String(*pGps, pDevice->GetMainDevice(), strNormalStatus, strAlarmStatus);
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += strNormalStatus;
		m_lstAlarm.SetItemText(nIndex, ALARM_STATUS_ITEM, strAlarmStatus);
	}
}



void CDlgLogQuery::ShowUserLog(GPSUsrLog_S* pUserLog)
{
	int nCount = m_lstAlarm.GetItemCount();
	int nIndex = 0;
	m_lstUserLog.InsertItem(nIndex, NULL);
	CString str, strMainType, strSubType, strInfo;
	GetUserLog(pUserLog, strMainType, strSubType, strInfo);
	str.Format(_T("%d"), pUserLog->nUsrID);
	m_lstUserLog.SetItemText(nIndex, 0, str);
	
	CString strTime;
	GPSTime_S& Time = pUserLog->time;
	strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), 
		Time.ucYear + 2000, Time.ucMonth, Time.ucDay, Time.ucHour, Time.ucMinute, Time.ucSecond);
	m_lstUserLog.SetItemText(nIndex, 1, strTime);
	m_lstUserLog.SetItemText(nIndex, 2, strMainType);
	m_lstUserLog.SetItemText(nIndex, 3, strSubType);
	m_lstUserLog.SetItemText(nIndex, 4, CString(pUserLog->szDevIDNO));
	m_lstUserLog.SetItemText(nIndex, 5, strInfo);
}

void CDlgLogQuery::ShowTPD(GPSTranPortData_S* pUserLog)
{
	int nCount = m_lstTPD.GetItemCount();
	int nIndex = 0;
	m_lstTPD.InsertItem(nIndex, NULL);
	CString str;
	m_lstTPD.SetItemText(nIndex, 0, CString(pUserLog->szDevIDNO));
	str.Format(_T("%d"), pUserLog->nType);
	m_lstTPD.SetItemText(nIndex, 1, str);
	CString strTime;
	SYSTEMTIME& Time = pUserLog->Time;
	strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), 
		Time.wYear, Time.wMonth, Time.wDay, Time.wHour, Time.wMinute, Time.wSecond);
	m_lstTPD.SetItemText(nIndex, 2, strTime);
	str.Format(_T("%d"), pUserLog->nLength);
	m_lstTPD.SetItemText(nIndex, 3, str);
	m_lstTPD.SetItemText(nIndex, 4, CString(pUserLog->cData));
}
void CDlgLogQuery::DeleteLogList(int nType)
{
	if (nType == QUERY_TYPE_ALARM)
	{
		m_lstAlarm.DeleteAllItems();
	}
	else if ( nType == QUERY_TYPE_TPD)
	{
		m_lstTPD.DeleteAllItems();
	}
	else
	{
		m_lstUserLog.DeleteAllItems();
	}
}

