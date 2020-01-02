// DlgTrackBack.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTrackBack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrackBack dialog
#define WM_TRACK_SEARCH_MSG						WM_USER + 0x1226
#define WM_TRACK_SEARCH_GPS_DATA				WM_USER + 0x1227	//real gps data
#define WM_TRACK_SEARCH_GPS_COUNT				WM_USER + 0x1228
#define WM_TRACK_READ_GPS_DATA					WM_USER + 0x1229	//gps data file


#define MAP_IMG_VEHICLE_ONLINE			0		//online
#define MAP_IMG_VEHICLE_DISONLINE		1		//offline
#define MAP_IMG_VEHICLE_STATIC		    2		//stop
#define MAP_IMG_VEHICLE_ALARM			3		//Alarm
#define MAP_IMG_VEHICLE_PARKING			4		//Parking
#define MAP_IMG_VEHICLE_QIDIAN			5		//Start
#define MAP_IMG_VEHICLE_ZHONGDIAN		6		//End
#define MAP_IMG_POSITION_MARKER			7		//Mark of position
#define MAP_IMG_ALARM_MARKER			8		//Mark of alarm


CDlgTrackBack::CDlgTrackBack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrackBack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrackBack)
		// NOTE: the ClassWizard will add member initialization here
	m_strParkingTime = _T("3");
	m_DataBeg = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CDlgTrackBack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrackBack)
	DDX_Control(pDX, IDC_LIST_TRACK, m_lstTrackData);
	DDX_Control(pDX, IDC_COMBO_DEV_IDNO, m_cmbDevIDNO);
	DDX_Control(pDX, IDC_DT_TIME_END, m_TimeCtrlEnd);
	DDX_Control(pDX, IDC_DT_TIME_BEG, m_TimeCtrlBeg);
	DDX_DateTimeCtrl(pDX, IDC_DT_DATE_BEGIN, m_DataBeg);
	DDX_DateTimeCtrl(pDX, IDC_DT_TIME_BEG, m_TimeBeg);
	DDX_DateTimeCtrl(pDX, IDC_DT_TIME_END, m_TimeEnd);
	DDX_Text(pDX, IDC_EDIT_PARKING_TIME, m_strParkingTime);
	DDV_MaxChars(pDX, m_strParkingTime, 4);
	DDX_Control(pDX, IDC_COMBO_MP, m_cmbTreakDis);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrackBack, CDialog)
	//{{AFX_MSG_MAP(CDlgTrackBack)
	ON_MESSAGE(WM_TRACK_SEARCH_MSG, OnVehiTrackMsgCB)
	ON_MESSAGE(WM_TRACK_SEARCH_GPS_DATA, OnSearchGPSData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrackBack message handlers

BOOL CDlgTrackBack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitList();

	m_TimeBeg.SetTime(0,0,0);
	m_TimeEnd.SetTime(23,59,59);
	UpdateData(FALSE);
	

	m_cmbTreakDis.SetCurSel(0);
	m_TimeCtrlBeg.SetFormat(_T("HH':'mm':'ss'"));
	m_TimeCtrlEnd.SetFormat(_T("HH':'mm':'ss'"));


	int nIndex = 0;
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	mapVehicleBaseIter mapDevIterB = mapDev.begin();
	mapVehicleBaseIter mapDevIterE = mapDev.end();
	while(mapDevIterB != mapDevIterE)
	{
		CVehicleBase* pVehi = (CVehicleBase*)mapDevIterB->second;
		if (pVehi != NULL)
		{
			m_cmbDevIDNO.InsertString(nIndex, pVehi->GetShowName());
			m_cmbDevIDNO.SetItemData(nIndex, DWORD(pVehi));
			nIndex ++;
		}
		mapDevIterB++;
	}

	if (m_cmbDevIDNO.GetCount() > 0)
	{
		m_cmbDevIDNO.SetCurSel(0);
	}
	
	m_TrackSearch.SetTrackWnd(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTrackBack::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (m_cmbDevIDNO.GetCurSel() == CB_ERR)
	{
		return;
	}
// 	CString strDevIDNO;
// 	m_cmbDevIDNO.GetLBText(m_cmbDevIDNO.GetCurSel(), strDevIDNO);

	CVehicleBase* pDevice = (CVehicleBase*)m_cmbDevIDNO.GetItemData(m_cmbDevIDNO.GetCurSel());
/*	CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(strDevIDNO);*/
	if (!pDevice)
	{
		return ;
	}
	

	SYSTEMTIME BegTime;
	memset(&BegTime,0,sizeof(BegTime));
	BegTime.wYear = m_DataBeg.GetYear();
	BegTime.wMonth = m_DataBeg.GetMonth();
	BegTime.wDay = m_DataBeg.GetDay();
	BegTime.wHour = m_TimeBeg.GetHour();
	BegTime.wMinute = m_TimeBeg.GetMinute();
	BegTime.wSecond = m_TimeBeg.GetSecond();
	
	SYSTEMTIME EndTime;
	memset(&EndTime,0,sizeof(EndTime));
	EndTime.wYear = m_DataBeg.GetYear();
	EndTime.wMonth = m_DataBeg.GetMonth();
	EndTime.wDay = m_DataBeg.GetDay();
	EndTime.wHour = m_TimeEnd.GetHour();
	EndTime.wMinute = m_TimeEnd.GetMinute();
	EndTime.wSecond = m_TimeEnd.GetSecond();
	
	if (TIMECompareTime(BegTime, EndTime) != -1)
	{
		AfxMessageBox(_T("time error"));
		GetDlgItem(IDC_DT_TIME_END)->SetFocus();
		return;
	}
	

	int nParkingTime = _ttoi(m_strParkingTime)*60;
	

	CString strDis = _T("");                       
	int nDis = 0;
	m_cmbTreakDis.GetLBText(m_cmbTreakDis.GetCurSel(),strDis);
	if ( _ttoi(strDis) <= 0 )
	{
		float fDis = _ttof(strDis);
// 		if (CConfigGViewerINI::GetInstance()->GetDevSpeedUnit() == SPEED_TYPE_MILE)  //mile
// 		{
// 			fDis = fDis * 1.6 * 1000; 
// 		}
// 		else
		{
			fDis = _ttof(strDis);
			fDis = fDis * 1000;
			
		}
		nDis = (int)fDis;
	}
	else
	{			
//		if (CConfigGViewerINI::GetInstance()->GetDevSpeedUnit() == SPEED_TYPE_MILE)  //mile
// 		{
// 			nDis = atoi(strDis) * 1.6 * 1000; 
// 		}
// 		else
		{
			nDis = _ttoi(strDis) * 1000; 
		}
	}
	
	{
		m_TrackSearch.SetSearchInfo(CStringA(pDevice->GetDevIDNO()), BegTime, EndTime, nDis, nParkingTime);
		m_TrackSearch.StartSearch();
		EnableCtrl(FALSE);
	}
}


void CDlgTrackBack::DoVehiTrackMsgCB(int nMsg, int nParam)
{
	PostMessage(WM_TRACK_SEARCH_MSG, nMsg, nParam);
}

//search gps data callback
void CDlgTrackBack::DoVehiTrackDateCB(GPSVehicleTrack_S* pVehiRun)
{	
	GPSVehicleTrack_S* pTmp = new GPSVehicleTrack_S;
	*pTmp = *pVehiRun;
	PostMessage(WM_TRACK_SEARCH_GPS_DATA, (WPARAM)pTmp, 0);
}

void CDlgTrackBack::DoTrackCountCB(GPSTrackCount_S* pTrackCount)
{
	//total number of GPS data data
}


LRESULT CDlgTrackBack::OnVehiTrackMsgCB(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case GPS_DOWNLOAD_MSG_FINISHED:
		{
			m_TrackSearch.StopSearch();
			EnableCtrl(TRUE);
		}
		break;
	case GPS_DOWNLOAD_MSG_FAILED:
		{
			m_TrackSearch.StopSearch();
			EnableCtrl(TRUE);
		}
		break;
	default:
		break;
	}
	
	return 0;
}

LRESULT CDlgTrackBack::OnSearchGPSData(WPARAM wParam, LPARAM lParam)
{
	GPSVehicleTrack_S* pTmp = (GPSVehicleTrack_S*)wParam;
	if (pTmp)
	{
		InsertListData(pTmp);
	}
	SAFE_DELETE_OBJECT(pTmp);

	return 0;
}

void CDlgTrackBack::InitList()
{
	int nIndex = 0;
	m_lstTrackData.InsertColumn(nIndex++, _T("Index"), LVCFMT_LEFT, 80);//Index
	m_lstTrackData.InsertColumn(nIndex++, _T("Time"), LVCFMT_LEFT, 130);//"GPS Time"
	m_lstTrackData.InsertColumn(nIndex++, _T("Location"), LVCFMT_LEFT, 160);//"Location"
	m_lstTrackData.InsertColumn(nIndex++, _T("Description"), LVCFMT_LEFT, 400);  //Description
	m_lstTrackData.InsertColumn(nIndex++, _T("Status"), LVCFMT_LEFT, 415);//"Status"
	m_lstTrackData.InsertColumn(nIndex++, _T("Alarm"), LVCFMT_LEFT, 310);//"Alarm"
}

void CDlgTrackBack::InsertListData(GPSVehicleTrack_S* pVecicleTrack)
{
	/*CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(pVecicleTrack->Alarm.szDevIDNO);*/
	if (pVecicleTrack != NULL)
	{
		CVehicleBase* pDevice = NULL;
		if (CSvrVer::GetInstance()->IsSvrVerV7())
		{
			pDevice = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByIDNO(pVecicleTrack->Alarm.szDevIDNO);
		}
		else
		{
			pDevice = CVehicleBaseMgr::GetInstance()->FindVehicleFromDev(pVecicleTrack->Alarm.szDevIDNO);
		}
		CString strIndex = _T("");
		int nIndex = m_lstTrackData.GetItemCount();
		strIndex.Format(_T("%d"), nIndex+1);
		CString strSpeed = FormatGpsSpeedAndDirection(pVecicleTrack->Alarm.Alarm.Gps);
		CString strDescrib = _T("");
		if (pDevice != NULL)
		{
			//	if (m_nSelRadioType == GPS_QUERY_TRACK_TYPE_GPS)           //GPS data
			{
				if(MAP_IMG_VEHICLE_STATIC == GetVehiRunImg(pVecicleTrack->Alarm.Alarm.Gps))  //if stop
				{			
					CString strParkingTime = _T("");
					strParkingTime.Format(LOADSTRINGEX(ID_STR_DLG_TRACK_PARKING_V), pVecicleTrack->Alarm.Alarm.Gps.nParkTime);   //"Parking %d second"
					strDescrib = strParkingTime ;
				}
			}
			m_lstTrackData.InsertItem(0,_T(""));
			m_lstTrackData.SetItemText(0, 0, strIndex);  
			m_lstTrackData.SetItemText(0, 1, FormatGpsTimeEx(Vonvert2SystemTime(pVecicleTrack->Alarm.Alarm.Gps.Time))); 
			m_lstTrackData.SetItemText(0, 2, FormatGPSToStr(pVecicleTrack->Alarm.Alarm.Gps));
			m_lstTrackData.SetItemText(0, 3, FormatOtherInfo(pDevice, pVecicleTrack->Alarm.Alarm.Gps));  
			CString strNormalStatus, strAlarmStatus;
			FormatStatus2String(pVecicleTrack->Alarm.Alarm.Gps, pDevice->GetMainDevice(), strNormalStatus, strAlarmStatus);
			m_lstTrackData.SetItemText(0, 4, strNormalStatus);  
			m_lstTrackData.SetItemText(0, 5, strAlarmStatus);  
			int nCarState = GetDevStatusNoOnline(&(pVecicleTrack->Alarm.Alarm.Gps), strAlarmStatus.IsEmpty());
		}
	}
}

CString CDlgTrackBack::FormatOtherInfo(CVehicleBase* pDev, const GPSVehicleGps_S& Gps)
{
	CString str;
	{
		CString strSpeed = FormatGpsSpeedAndDirection(Gps);
		if (!strSpeed.IsEmpty())
		{
			str += LOADSTRINGEX(ID_STR_DLG_EVENT_LST_REAL_SPEED);
			str += _T(":");
			str += strSpeed;
		}

		CString strTemperature = FormatTemperatureInfo((CVDvsDevice*)pDev->GetMainDevice(), Gps);
		if (!strTemperature.IsEmpty())
		{
			AddSeparator(str);
			str += LOADSTRINGEX(ID_STR_DLG_TRACK_TMP);
			str += _T(":");
			str += strTemperature;
		}
		CString strYouliang = FormatYouliang2String(Gps.uiYouLiang);
		if (!strYouliang.IsEmpty())
		{
			AddSeparator(str);
			str += LOADSTRINGEX(ID_STR_DLG_TRACK_YOULIANG);
			str += _T(":");
			str += strYouliang;
		}

		
		CString strDescrib = _T("");
//		if (m_nSelRadioType == GPS_QUERY_TRACK_TYPE_GPS)           //GPS Data
		{
			if(MAP_IMG_VEHICLE_STATIC == GetVehiRunImg(Gps))  //if stop
			{			
				CString strParkingTime;
				strParkingTime.Format(LOADSTRINGEX(ID_STR_DLG_TRACK_PARKING_V), Gps.nParkTime);   //"Parking %d s"
				strDescrib = strParkingTime ;
				if (!strDescrib.IsEmpty())
				{
					AddSeparator(str);
					str += strDescrib;
				}
			}
		}
	}
	
	return str;
}

CString CDlgTrackBack::FormatTemperatureInfo(CVDvsDevice* pDevice, const GPSVehicleGps_S& Gps)
{
	CString str, strTmp;
	str = "";
	if (pDevice)
	{
		int nTempNum = pDevice->GetDevInfo()->ucTempSensorNum;
		float sCoachTemp = 0.0; 
		for (int i = 0; i < nTempNum; ++i)
		{
			str += pDevice->GetDevInfo()->szTempSensorName[i];
			sCoachTemp = Gps.sTempSensor[i]/10.0;
			strTmp.Format(_T("%0.1f"), sCoachTemp);
			str += strTmp;
			str += _T(" ");
		}
	}
	return str;
}

int CDlgTrackBack::GetVehiRunImg(const GPSVehicleGps_S& Gps)
{
	int nImg = MAP_IMG_VEHICLE_ALARM;
	if (((Gps.uiStatus[0]>>7)&1) == 0)   //Atn is unnormal
	{
		nImg = MAP_IMG_VEHICLE_ALARM;
		return nImg;
	}
	else if (((Gps.uiStatus[0]>>8)&3) == 0 )  //HDD or SD dosenot exist
	{
		nImg = MAP_IMG_VEHICLE_ALARM;
		return nImg;
	}
	else if (((Gps.uiStatus[0]>>8)&3) == 2)  //HD power down
	{
		nImg = MAP_IMG_VEHICLE_ALARM;
		return nImg;
	}
	else if (((Gps.uiStatus[0]>>14))&1 == 1)  //Over speed
	{
		nImg = MAP_IMG_VEHICLE_ALARM;
		return nImg;
	}
	else if (((Gps.uiStatus[0]>>13))&1 == 1)  //Parking
	{
		nImg = MAP_IMG_VEHICLE_STATIC;
		return nImg;
	}
	else
	{
		nImg = MAP_IMG_VEHICLE_ONLINE;
		return nImg;
	}					
	
	return nImg;
	
}

void CDlgTrackBack::EnableCtrl(BOOL bEnable)
{
	GetDlgItem(IDOK)->EnableWindow(bEnable);
}