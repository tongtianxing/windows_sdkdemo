// clientdemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "clientdemoDlg.h"
#include "VDvsDevice.h"
#include "DlgPaneView.h"
#include "Search.h"
#include "DlgLogQuery.h"
#include "DlgTransParam.h"
#include "DlgGetDevIP.h"
#include "DlgPlayback.h"
#include "Playback.h"
#include "DlgTransData.h"
#include "DownSnapshot.h"
#include "VoiceTalkback.h"
#include "DlgPanePtz.h"
#include "DlgParamConfig.h"
#include "DlgSendFileToDev.h"
#include "DlgParamerConf.h"

#define MSG_SUB_VEHI_STATUS   WM_USER+0x3001
#define MSG_SUB_VEHI_ALARM	  WM_USER+0x3002

const int DEV_CHANNEL_ALL = -1;
#define WM_MSG_SEARCH_MSG		WM_USER + 0x1001
#define WM_MSG_SEARCH_FILE		WM_USER + 0x1002



#define WM_MSG_FAILED	WM_USER+0x0001
#define WM_MSG_SUC		WM_USER+0x0002
#define WM_MSG_SET		WM_USER+0x0003

#define WM_MSG_DOWNLOAD		WM_USER + 0x1003
#define WM_MSG_SNAPSHOT		WM_USER + 0x1004

#define WM_MSG_CMSSEND_CTRL         WM_USER+0x106
#define WM_MSG_TQ_MSG			WM_USER+0x107

#define WM_MSG_PLAYBACK_PLAY	WM_USER+0x108

#define TIMER_DOWNLOAD		1
#define TIMER_SNAPSHOT		2

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define AUDIO_TYPE_TALKBACK		0	//对讲
#define AUDIO_TYPE_MONITOR		1	//监听
#define AUDIO_TYPE_BROADCAST	2	//广播

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientdemoDlg dialog

CClientdemoDlg::CClientdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientdemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientdemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_lVehiRun = NULL;
	m_pDlgPaneView = NULL;
	m_pFileSearch = NULL;
	m_DataBeg = COleDateTime::GetCurrentTime();
	m_DataEnd = COleDateTime::GetCurrentTime();
	m_lGetSnapshotPlan = NULL;
	m_lSetSnapshotPlan = NULL;
	m_pDownFile = NULL;
//	m_strSearchDevIDNO = "18575596496";
	m_lQueryTransparent = NULL;
	m_pPlayback = NULL;
	m_bStopSnapshot = FALSE;
	m_nDownMinSecond = 0;
	m_pSnapshot = NULL;
	m_pDlgPanePtz = NULL;
}

void CClientdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientdemoDlg)
	DDX_Control(pDX, IDC_COMBO_DEV, m_cmbDev);
	DDX_Control(pDX, IDC_LIST_GPS, m_lstGPS);
	DDX_Control(pDX, IDC_TREE_DEV, m_treeDev);
	//	DDX_Text(pDX, IDC_EDIT_DEV_IDNO, m_strSearchDevIDNO);
	DDX_Control(pDX, IDC_COMBO_SEARCH_CHANNEL, m_cmbSearchChannel);
	DDX_Control(pDX, IDC_COMBO_LOCATION, m_cmbLocation);
	DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_cmbFileType);
	DDX_Control(pDX, IDC_COMBO_FILE_ATTRIBUTE, m_cmbFileAttribute);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SEARCH_TIME, m_DataBeg);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SEARCH_TIME2, m_DataEnd);

	DDX_Control(pDX, IDC_LIST_FILE, m_lstSearch);
	DDX_Control(pDX, IDC_LIST_LOG, m_lstSearchLog);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_AUDIO, m_cmbAudio);
}

BEGIN_MESSAGE_MAP(CClientdemoDlg, CDialog)
	//{{AFX_MSG_MAP(CClientdemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_DEV, OnDblclkTreeDev)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_GET_COLORE, OnButtonGetColore)
	ON_BN_CLICKED(IDC_BUTTON_SET_COLORE, OnButtonSetColore)
	ON_BN_CLICKED(IDC_BUTTON_TRACK_BACK, OnButtonTrackBack)
	ON_BN_CLICKED(IDC_BUTTON_TRANS_PARAM, OnButtonTransParam)
	ON_BN_CLICKED(IDC_BUTTON_GET_DEV_IP, OnButtonGetDevIp)
	ON_BN_CLICKED(IDC_BUTTON_GET_SNAPSHOT, OnButtonGetSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_SET_SNAPSHOT, OnButtonSetSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK, OnButtonPlayback)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_ALARM, OnButtonClearAlarm)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_FILE, OnButtonPlayFile)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_LOG_SERACH, OnButtonDeviceLogSearch)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_READ_STATUS, OnBtnReadStatus)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SNAPSHOT, OnButtonAddSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SNAPSHOT, OnButtonDelSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_RESUME_DOWN, OnButtonResumeDown)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(IDC_BUTTON_TRANCE_SVR, OnButtonTranData)
	//}}AFX_MSG_MAP
	ON_MESSAGE(MSG_SUB_VEHI_ALARM, OnSubVehiAlarm)
	ON_MESSAGE(MSG_SUB_VEHI_STATUS, OnSubVehiStatus)

	ON_MESSAGE(WM_MSG_SEARCH_MSG, OnMsgSearchMsg)
	ON_MESSAGE(WM_MSG_SEARCH_FILE, OnMsgSearchFile)


	ON_MESSAGE(WM_MSG_FAILED, OnMsgFailed)
	ON_MESSAGE(WM_MSG_SUC, OnMsgSuc)
	ON_MESSAGE(WM_MSG_SET, OnMsgSet)
	
	ON_MESSAGE(WM_MSG_DOWNLOAD, OnMsgDownload)
	ON_MESSAGE(WM_MSG_CMSSEND_CTRL,OnCmsSendMessage)

	ON_MESSAGE(WM_MSG_TQ_MSG,OnTQMSG)
	ON_MESSAGE(WM_MSG_PLAYBACK_PLAY, OnPlaybackPlayMsg)
	
	ON_BN_CLICKED(IDC_BUTTON_ADD_SN, OnBnClickedButtonAddSn)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SN, OnBnClickedButtonDelSn)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_DEV, &CClientdemoDlg::OnNMRClickTreeDev)
	ON_COMMAND(ID_MAIN_FRONT, &CClientdemoDlg::OnMainFront)
	ON_COMMAND(ID_MENU_SEND_FILE, &CClientdemoDlg::OnMenuSendFile)
	ON_COMMAND(ID_MENU_PARAMER_CONFIG, &CClientdemoDlg::OnMenuParamerConfig)
	ON_COMMAND(ID_MENU_COORDINATE, &CClientdemoDlg::OnMenuCoordinate)
	ON_MESSAGE(WM_MSG_SNAPSHOT, OnMsgSnapshot)

	ON_BN_CLICKED(IDC_BTN_BROWSE, &CClientdemoDlg::OnBnClickedBtnBrowse)
	ON_NOTIFY(NM_CLICK, IDC_TREE_DEV, &CClientdemoDlg::OnNMClickTreeDev)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO_START, &CClientdemoDlg::OnBnClickedButtonAudioStart)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO_STOP, &CClientdemoDlg::OnBnClickedButtonAudioStop)
	ON_BN_CLICKED(IDC_BTN_FUNC_PTZ, &CClientdemoDlg::OnBnClickedBtnFuncPtz)
	ON_BN_CLICKED(IDC_CHK_PREVIEW_RECORD, &CClientdemoDlg::OnBnClickedChkPreviewRecord)
	ON_BN_CLICKED(IDC_BTN_OPEN_RECORD_PATH, &CClientdemoDlg::OnBnClickedBtnOpenRecordPath)
	ON_BN_CLICKED(IDC_BTN_PARAM_CONFIG, &CClientdemoDlg::OnBnClickedBtnParamConfig)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientdemoDlg message handlers

BOOL CClientdemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	CString strDir;
	strDir.Format(_T("%sShnapshot\\"), PATHGetAppPath());
	PATHCreateDirectory(strDir);
	SetDlgItemText(IDC_SNAPSHOT_PATH, strDir);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	DWORD styles = m_lstSearch.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lstSearch.SetExtendedStyle(styles );
	m_lstSearch.InsertColumn(0, _T("Datetime"), LVCFMT_LEFT, 120);
	m_lstSearch.InsertColumn(1, _T("Type"), LVCFMT_LEFT, 70);
	m_lstSearch.InsertColumn(2, _T("Device"), LVCFMT_LEFT, 90);
	m_lstSearch.InsertColumn(3, _T("Channel"), LVCFMT_LEFT, 90);
	m_lstSearch.InsertColumn(4, _T("Storage"), LVCFMT_LEFT, 90);
	m_lstSearch.InsertColumn(5, _T("Size(MB)"), LVCFMT_LEFT, 90);
	m_lstSearch.InsertColumn(6, _T("File"), LVCFMT_LEFT, 240);
	styles = m_lstSearchLog.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lstSearchLog.SetExtendedStyle(styles );
	m_lstSearchLog.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 120);
	m_lstSearchLog.InsertColumn(1, _T("time"), LVCFMT_LEFT, 70);
	m_lstSearchLog.InsertColumn(2, _T("type"), LVCFMT_LEFT, 90);
	m_lstSearchLog.InsertColumn(3, _T("event"), LVCFMT_LEFT, 90);
	
	
	CString str;
	int i;
	for (i = 0; i < 4; ++i)
	{
		str.Format(_T("Channel-%d"), i+1);
		m_cmbSearchChannel.AddString(str);
		m_cmbSearchChannel.SetItemData(i, i);
	}

	int nIndex = m_cmbSearchChannel.AddString(_T("All channels"));
	m_cmbSearchChannel.SetItemData(nIndex, DEV_CHANNEL_ALL);
	m_cmbSearchChannel.SetCurSel(0);


	nIndex = 0;
	nIndex = m_cmbLocation.AddString(_T("Device"));
	m_cmbLocation.SetItemData(nIndex, GPS_FILE_LOCATION_DEVICE);
	nIndex = m_cmbLocation.AddString(_T("Storage Server"));
	m_cmbLocation.SetItemData(nIndex, GPS_FILE_LOCATION_STOSVR);
	nIndex = m_cmbLocation.AddString(_T("Download Server"));
	m_cmbLocation.SetItemData(nIndex, GPS_FILE_LOCATION_DOWNSVR);
	m_cmbLocation.SetCurSel(0);
	
	nIndex = m_cmbFileType.AddString(_T("Record"));
	m_cmbFileType.SetItemData(nIndex, GPS_FILE_ATTRIBUTE_RECORD);
	// 	nIndex = m_cmbFileType.AddString("Picture");
	// 	m_cmbFileType.SetItemData(nIndex, GPS_FILE_ATTRIBUTE_JPEG);
	m_cmbFileType.SetCurSel(0);
	
	nIndex = m_cmbFileAttribute.AddString(_T("Normal"));
	m_cmbFileAttribute.SetItemData(nIndex, GPS_FILE_TYPE_NORMAL);
	nIndex = m_cmbFileAttribute.AddString(_T("Alarm"));
	m_cmbFileAttribute.SetItemData(nIndex, GPS_FILE_TYPE_ALARM);
	nIndex = m_cmbFileAttribute.AddString(_T("Both"));
	m_cmbFileAttribute.SetItemData(nIndex, GPS_FILE_TYPE_ALL);
	m_cmbFileAttribute.SetCurSel(2);

	nIndex = m_cmbAudio.AddString(_T("Talkback"));
	m_cmbAudio.SetItemData(nIndex, AUDIO_TYPE_TALKBACK);
	nIndex = m_cmbAudio.AddString(_T("Talkback Ex"));
	m_cmbAudio.SetItemData(nIndex, 1);
	m_cmbAudio.SetCurSel(0);

	CheckDlgButton(IDC_CHK_PREVIEW_RECORD, g_bPreviewAutoRecord);


	CVehicleBaseMgr::GetInstance()->FillDeviceInfoEx(m_treeDev, _T("All Device"), TRUE, FALSE, FALSE);

	/*mapIDIRDEVInfo mapDev;*/
	mapDvsDevice mapDev;
	CVMgrDevice::GetInstance()->GetAllDevMap(mapDev);
	AddDevice(mapDev);

	m_pDlgPaneView = new CDlgPaneView;
	m_pDlgPaneView->Create(CDlgPaneView::IDD, this);
	m_pDlgPaneView->SetWndMode(WND_MODE_4);
	m_pDlgPaneView->ShowWindow(SW_SHOW);

	NETCLIENT_MCRegMsgCB(this,FUNMCMsgCB);//Reg Callback Func
	InitDevCombox();

	MoveCtrl();

	StarSubVehi();

	NETMEDIA_SNOpenSnapshotTimer();
//	NETMEDIA_SNSetSnapshotTimerInterval(3);
	NETMEDIA_SNSetSnapshotTimerDataCB(this, FUNShnapshotTimerDataCB);

	NETMEDIA_QTStartQueryTransparentMgr();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientdemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientdemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
//GPS

int	CClientdemoDlg::StartVehiRun()
{
	int nRet = GPS_FALSE;
	if (NULL == m_lVehiRun)
	{
		NETCLIENT_VROpenVehiRun(&m_lVehiRun);
		NETCLIENT_VRSetRunningCB(m_lVehiRun, this, FUNVehiRunningCB);
		nRet = NETCLIENT_VRStartVRChan(m_lVehiRun);
		if (nRet != GPS_OK)
		{
			NETCLIENT_VRCloseVehiRun(m_lVehiRun); m_lVehiRun = NULL;
		}
	}
	
	return nRet;
}

int	CClientdemoDlg::StopVehiRun()
{
	int nRet = GPS_FALSE;
	if (m_lVehiRun)
	{		
		NETCLIENT_VRSetRunningCB(m_lVehiRun, NULL, NULL);
		NETCLIENT_VRStopVRChan(m_lVehiRun);
		NETCLIENT_VRCloseVehiRun(m_lVehiRun); m_lVehiRun = NULL;
		nRet = GPS_OK;
	}
	
	return nRet;
}

int	CClientdemoDlg::AddDevice(int nDevID, const char* szIDNO)
{
	int nRet = GPS_FALSE;
	if (m_lVehiRun == NULL)
	{
		nRet = StartVehiRun();
	}
	if (m_lVehiRun)
	{
		NETCLIENT_VRAddDevice(m_lVehiRun, nDevID, szIDNO);
		nRet = GPS_OK;
	}
	
	return nRet;
}

void CClientdemoDlg::AddDevice(mapDvsDevice mapDev)
{
	mapDvsDevIter Iter = mapDev.begin();
	CDevBase* pDev = NULL;;
	while(Iter != mapDev.end())
	{
		pDev = (CDevBase*)((*Iter).second);
		if(pDev)
		{
			AddDevice(pDev->GetID(), pDev->GetIDNOForChar());
		}
		++Iter;
	}
}

void CClientdemoDlg::FUNVehiRunningCB(GPSVehicleState_S* pVecRun, void* pUsr)
{
	CClientdemoDlg* pThis = (CClientdemoDlg*)pUsr;
	pThis->DoFUNVehiRunning(pVecRun);
}

void CClientdemoDlg::DoFUNVehiRunning(GPSVehicleState_S* pVecRun)
{
	static GPSVehicleState_S LastState = {0};
	if (memcmp(&LastState, pVecRun, sizeof(GPSVehicleState_S)) == 0)
	{
		return ;
	}
	LastState = *pVecRun;
	CString str;
	CString strName = _T("");
	CVehicleBase* pVehi = CVehicleBaseMgr::GetInstance()->FindVehicleFromDev(pVecRun->szDevIDNO);
	if (pVehi != NULL)
	{
		strName.Format(_T("%s"), pVehi->GetShowName());
	}
	else
	{
		strName.Format(_T("%s"), pVecRun->szDevIDNO);
	}
	CString strTemperature;
	FormatTemperatureInfo(pVecRun->Gps, pVehi, strTemperature);
	str.Format(_T("%s, id:%s, GPS:%s, speed:%s Other:%s"), FormatTime2String(Vonvert2SystemTime(pVecRun->Gps.Time)),
		strName, FormatGPSToStr(pVecRun->Gps), FormatGpsSpeedAndDirection(pVecRun->Gps), strTemperature
		);

	if(m_lstGPS.GetCount() > 100)
	{
		while(m_lstGPS.GetCount())
			m_lstGPS.DeleteString(0);
	}
	m_lstGPS.InsertString(0, str);
}

void CClientdemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	MoveCtrl();
}


void CClientdemoDlg::MoveCtrl()
{
	if (m_pDlgPaneView && m_pDlgPaneView->GetSafeHwnd())
	{
		CRect rcClient, rcTree, rcLst, rcMove;
		GetClientRect(rcClient);
		m_lstGPS.GetClientRect(rcLst);
		m_treeDev.GetClientRect(rcTree);
		
		rcMove.top = rcClient.top -5;
		rcMove.left = rcTree.right + 10;
		rcMove.right = rcClient.right - 10;
		rcMove.bottom = rcTree.bottom;
		m_pDlgPaneView->MoveWindow(rcMove);
	}
}

void CClientdemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_pDlgPaneView)
	{
		m_pDlgPaneView->DestroyWindow();
		SAFE_DELETE_OBJECT(m_pDlgPaneView);
	}
	if (m_pDlgPanePtz)
	{
		m_pDlgPanePtz->DestroyWindow();
		SAFE_DELETE_OBJECT(m_pDlgPanePtz);
	}

	StopSubVehi();
	StopVehiRun();

	if(m_pDownFile)
	{
		m_pDownFile->StopDowndFile();
		SAFE_DELETE_OBJECT(m_pDownFile);
	}

	if(m_pFileSearch)
	{
		m_pFileSearch->StopSearch();
		SAFE_DELETE_OBJECT(m_pFileSearch);
	}

	if (m_pSnapshot)
	{
		m_pSnapshot->StopDown();
		SAFE_DELETE_OBJECT(m_pSnapshot);
	}

	NETMEDIA_SNStopSnapshotTimer();
	NETMEDIA_QTStopQueryTransparentMgr();

	OnBnClickedButtonAudioStop();
// 	if(m_pDlgPlayback)
// 	{
// 		m_pDlgPlayback->DestroyWindow();
// 		SAFE_DELETE_OBJECT(m_pDlgPlayback);
// 	}
}


void CClientdemoDlg::OnDblclkTreeDev(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	*pResult = 0;
	{
		PreviewSelectNode(0);
	}
}

BOOL CClientdemoDlg::IsChannelItem(CTreeCtrl& tree, HTREEITEM hItem)
{
	if (hItem == m_treeDev.GetRootItem())
	{
		return FALSE;
	}

	HTREEITEM itemTmp = m_treeDev.GetChildItem(hItem);
	if(itemTmp)
	{
		return FALSE;
	}
// 	else
// 	{
// 		CObject* pObj = (CObject*)m_treeDev.GetItemData(hItem);
// 		if (pObj && 0 == strcmp("CVehicleBase", pObj->GetRuntimeClass()->m_lpszClassName))
// 		{
// 			return FALSE;
// 		}
// 	}

	return TRUE;
}
void CClientdemoDlg::PreviewSelectNode(BOOL bMain)
{
	HTREEITEM hItem = m_treeDev.GetSelectedItem();
	if (hItem)
	{
		int nWndIndex = 0;
		if (IsChannelItem(m_treeDev, hItem))
		{
			HTREEITEM hDevice= m_treeDev.GetParentItem(hItem);
			CVehicleBase* pVehi = (CVehicleBase*)m_treeDev.GetItemData(hDevice);
			if (pVehi != NULL)
			{
				int nChan = m_treeDev.GetItemData(hItem);
				CDevBase* pDevice = pVehi->GetDevByChn(nChan);
				if (pDevice != NULL)
				{
					int nRealChan = pDevice->GetRealChn(nChan+1);
					nRealChan--;
					if (m_pDlgPaneView->IsDevChnPreviewing(pDevice->GetID(), nRealChan, bMain, nWndIndex))
					{
						m_pDlgPaneView->StopVideoView(pDevice->GetID(), nRealChan);
						m_treeDev.SetItemText(hItem, pDevice->GetChnName(nRealChan));
						return;
					}
					else
					{
						int nIndex = m_pDlgPaneView->PreviewRealVideoDClik(pDevice->GetID(), nRealChan, bMain);
						if (nIndex != -1)
						{
							CString str;
							str.Format(_T("%s Play[%d]%s"), pDevice->GetChnName(nRealChan), nIndex+1,
								g_bPreviewAutoRecord ? _T(" Record") : _T(""));
							m_treeDev.SetItemText(hItem, str);
						}
						//m_pDlgPaneView->OnDevChanPreView(pDevice->GetID(), nRealChan, bMain);
					}
				}
			}
		}
	}
}

void CClientdemoDlg::StarSubVehi()
{
	m_subVehiAlarm.SetWndMsg(m_hWnd, MSG_SUB_VEHI_ALARM);
	m_subVehiStatus.SetWndMsg(m_hWnd, MSG_SUB_VEHI_STATUS);
	m_subVehiAlarm.StartWork();
	m_subVehiStatus.StartWork();
	GPSDeviceIDNO_S* pDevice = NULL;
	int nDeviceCount = 0;
	CVMgrDevice::GetInstance()->GetAllDev(&pDevice, nDeviceCount);
	m_subVehiAlarm.UpdateDevice(pDevice, nDeviceCount);
	m_subVehiStatus.UpdateDevice(pDevice, nDeviceCount);
	SAFE_DELETE_ARRAY(pDevice);
}

void CClientdemoDlg::StopSubVehi()
{
	m_subVehiStatus.StopWork();
	m_subVehiAlarm.StopWork();
}

LRESULT CClientdemoDlg::OnSubVehiAlarm(WPARAM wParm, LPARAM lParam)
{
	if (wParm == MSG_DEVICE_INFO_CHANGE)
	{
		return OnDeviceInfoChangeMessage((GPSDevInfo_S*)lParam);
	}
	else if (wParm == MSG_DEV_TRANSPARENT_DATA)
	{
		return ShowDevTran((GPSAlarmTPD_S*)lParam);
	}
	else if(wParm == MSG_ALARM_INFO)
	{
		GPSVehicleAlarm_S* pAlarm = (GPSVehicleAlarm_S*)lParam;
		return OnMsgAlarmInfo(pAlarm);
	}
	return 0;
}
LRESULT CClientdemoDlg::OnSubVehiStatus(WPARAM wParm, LPARAM lParam)
{
	if (wParm == DLG_CTRL_MSG_DEVICE_STATUS_CHANGE)
	{
		OnMsgDeviceStatusChange((DeviceStatusChange_S*)lParam);
	}
	return 0;
}

//Device Info Change
LRESULT CClientdemoDlg::OnDeviceInfoChangeMessage(GPSDevInfo_S* pBaseInfo)
{

	return 0;
}

LRESULT CClientdemoDlg::OnMsgAlarmInfo(GPSVehicleAlarm_S* pVehiAlarm)
{
	CString str;
	//Alarm Processing
	{
		CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(pVehiAlarm->szDevIDNO);
		if (pDevice)
		{
			if (GPS_ALARM_TYPE_DEV_ONLINE == pVehiAlarm->Alarm.AlarmType 
				|| GPS_ALARM_TYPE_DEV_DISONLINE == pVehiAlarm->Alarm.AlarmType)
			{
				//Online Status
				str = pDevice->GetShowName();
				BOOL bOnline = GPS_ALARM_TYPE_DEV_ONLINE == pVehiAlarm->Alarm.AlarmType;
				if (bOnline)
				{
					str += _T("online");
			//		DelSnapshot(pVehiAlarm->szDevIDNO);
				}
				else
				{
				//	AddSnapshot(pVehiAlarm->szDevIDNO);
					str += _T("offline");
				}
				switch(pVehiAlarm->Alarm.AlarmInfo)
				{
				case GPS_NETWOKR_TYPE_3G:
					str += _T("3G");
					break;
				case GPS_NETWOKR_TYPE_WIFI:
					str += _T("Wifi");
					break;
				case GPS_NETWORK_TYPE_NET:
					str += _T("wired network");
					break;
				case GPS_NETWORK_TYPE_4G:
					str += _T("4G");
					break;
				default:
					str += _T("unknow net type");
					break;
				}
				CString strTemp;
				//imei
				strTemp.Format(_T(" IMEI[%s]"), CString(pVehiAlarm->Alarm.szDesc));
				str += strTemp;

				//IMSI
				strTemp.Format(_T(" IMSI[%s]"), CString(pVehiAlarm->Alarm.szImgFile));
				str += strTemp;
			//	PANE_DEVICE()->DoDeviceOnlineStatus(pDevice, bOnline);
				TRACE("%s\n", str);
				
			}
			else if ( GPS_ALARM_TYPE_TALK_BACK_REQ == pVehiAlarm->Alarm.AlarmType)
			{
				DevTalkBackReq(pDevice, pVehiAlarm);
			}
			else if (GPS_ALARM_TYPE_SNAPSHOT_FINISH == pVehiAlarm->Alarm.AlarmType)
			{
				DoAlarmSnapshotFinish(pDevice, pVehiAlarm);
			}
			else
			{
				InsertListVehiAlarm(pVehiAlarm);
			}
		}
	}
	SAFE_DELETE_OBJECT(pVehiAlarm);


	return 0;
}

LRESULT CClientdemoDlg::ShowDevTran( GPSAlarmTPD_S* pNewAlarm )
{
	if (pNewAlarm->TPD.nType == 103)
	{
		std::vector<std::string> vecStr;		
		STRINGSplit(pNewAlarm->TPD.Data.cBuffer, '|', vecStr);
		// number of people
		int nCurPeopleNum = vecStr.size();
	}
	ASSERT(pNewAlarm != NULL);
	CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(pNewAlarm->szDevIDNO);
	//设备名
	CString strName(pNewAlarm->szDevIDNO);
	if (pDevice)
	{
		strName = pDevice->GetShowName();
	}
	//类型
	CString strType = _T("Transparent Data");
	//时间
	CString strTime = FormatTime2String(Vonvert2SystemTime(pNewAlarm->VehiAlarm.Time));
	//内容
	CString strContent = _T("");
	CString strTemp;
#ifdef _DEBUG
	strContent.Format(_T("(%d)%02X"), pNewAlarm->TPD.Data.nLength, (unsigned char)pNewAlarm->TPD.Data.cBuffer[0]);
	for (int i=1; i<pNewAlarm->TPD.Data.nLength; i++)
	{
		strTemp.Format(_T(" %02X"), (unsigned char)pNewAlarm->TPD.Data.cBuffer[i]);
		strContent += strTemp;
	}
#else
	strContent.Format(_T("(%d)%s"), pNewAlarm->TPD.Data.nLength, CString(pNewAlarm->TPD.Data.cBuffer));
#endif
	strTemp.Format(_T("%s,%s,Type:%s,Data:%s"), strName, strTime, strType, strContent);
	m_lstGPS.InsertString(0, strTemp);
	
	return 0;
}

void CClientdemoDlg::DevTalkBackReq( CDevBase* pDevice, GPSVehicleAlarm_S* pVehiAlarm )
{
	if (pDevice && pVehiAlarm)
	{
		CString strTemp;
		SYSTEMTIME stTime;
		GetLocalTime(&stTime);
		strTemp.Format(_T("%s,%s,Type:Device Request Intercom"), pDevice->GetShowName(), FormatTime2String(stTime));
		m_lstGPS.InsertString(0, strTemp);
		if (IDOK == AfxMessageBox(strTemp, MB_OKCANCEL))
		{
			m_cmbDev.SelectString(0, pDevice->GetShowName());
			OnBnClickedButtonAudioStop();
			m_cmbAudio.SetCurSel(1);
			OnBnClickedButtonAudioStart();
		}
	}
}

void CClientdemoDlg::InsertListVehiAlarm(GPSVehicleAlarm_S* pVehiAlarm)
{
	CString strAlarm;
	const CString strFalg = _T(",");
	CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(pVehiAlarm->szDevIDNO);

	GPSVehicleGps_S* pGps = &(pVehiAlarm->Alarm.Gps);
	if (pDevice)
	{
		strAlarm += pDevice->GetShowName();
	}
	else
	{
		strAlarm += pVehiAlarm->szDevIDNO;
	}
	strAlarm += strFalg;
	strAlarm += FormatTime2String(Vonvert2SystemTime(pVehiAlarm->Alarm.Time));
	strAlarm += strFalg;
	
	CString strAlarmDesc, strAlarmType;
	FormatAlarm2String(pVehiAlarm->Alarm, strAlarmType, strAlarmDesc, pDevice);
	strAlarm += strAlarmType;
	strAlarm += strFalg;
	strAlarm += strAlarmDesc;

	if (pGps)
	{
		strAlarm += strFalg;
		strAlarm += FormatGPSToStr(*pGps);

		CString strNormalStatus, strAlarmStatus;
		FormatStatus2String(*pGps, pDevice, strNormalStatus, strAlarmStatus);
		strAlarm += strFalg;
		strAlarm += strNormalStatus;

		strAlarm += strFalg;
		strAlarm += strAlarmStatus;
	}
	m_lstGPS.InsertString(0, strAlarm);
}

LRESULT CClientdemoDlg::OnMsgDeviceStatusChange(DeviceStatusChange_S* pStatus)
{

	for (int i = 0; i < pStatus->nCount; ++i)
	{
		TRACE("Device(%s)-Online(%d)\n", pStatus->pVehiRun[i].szDevIDNO, pStatus->pOnline[i]);
	}
	
	SAFE_DELETE_ARRAY(pStatus->pVehiRun);
	SAFE_DELETE_ARRAY(pStatus->pOnline);
	SAFE_DELETE_OBJECT(pStatus);
	
	return 0;
}
void CClientdemoDlg::DelAllRecItem()
{
	for (int i = 0; i < m_lstSearch.GetItemCount(); ++i)
	{
		GPSFile_S* pNewFile = (GPSFile_S*)m_lstSearch.GetItemData(i);
		SAFE_DELETE_OBJECT(pNewFile);
	}
	m_lstSearch.DeleteAllItems();
	
}

void CClientdemoDlg::OnBtnSearch()
{
	UpdateData();
	DelAllRecItem();
	CString strSearchDevIDNO;
	strSearchDevIDNO = GetSelDevIDNO();
	if (strSearchDevIDNO.IsEmpty() 
		|| m_cmbSearchChannel.GetCurSel() == CB_ERR
		|| m_cmbFileType.GetCurSel() == CB_ERR
		|| m_cmbLocation.GetCurSel() == CB_ERR
		|| m_cmbFileAttribute.GetCurSel() == CB_ERR)
	{
		AfxMessageBox(_T("Invalid search condition"));
		return;
	}
	char szDevIDNO[32] = {0};
	strncpy_s(szDevIDNO, CStringA(strSearchDevIDNO), 31);

	int nLocation = m_cmbLocation.GetItemData(m_cmbLocation.GetCurSel());

	if (CSvrVer::GetInstance()->IsSvrVerV7() )
	{
		if (nLocation == GPS_FILE_LOCATION_DOWNSVR
			|| nLocation == GPS_FILE_LOCATION_STOSVR)
		{
			// utf8 encode
			CVehicleBase* pVehicle = GetSelVehicle();
			strncpy_s(szDevIDNO, pVehicle->GetVehicleIDNOForChar(), 31);
		}
	}
	CWaitCursor wait;
// 	char szDevIDNO[MAX_PATH] = {0};
// #ifdef _UNICODE
// 	UcsToUtf8(strSearchDevIDNO, szDevIDNO, MAX_PATH);
// #else
// 	AnsiToUtf8(strSearchDevIDNO, szDevIDNO, MAX_PATH);
// #endif
// 	CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(szDevIDNO);
// 	if (pDevice)
	{
		if (NULL == m_pFileSearch)
		{
			m_pFileSearch = CSearch::GetNewRecSearch(nLocation, 
													m_cmbFileType.GetItemData(m_cmbFileType.GetCurSel()));
			m_pFileSearch->SetWndAndMsg(this->GetSafeHwnd(), WM_MSG_SEARCH_MSG, WM_MSG_SEARCH_FILE);
#if 1
			m_pFileSearch->StartSearch(szDevIDNO, //CStringA(strSearchDevIDNO), 
				m_cmbSearchChannel.GetItemData(m_cmbSearchChannel.GetCurSel()), 
				m_cmbFileAttribute.GetItemData(m_cmbFileAttribute.GetCurSel()), 
				m_DataBeg.GetYear(), m_DataBeg.GetMonth(), m_DataBeg.GetDay(), 0, 86399);
#else
			m_pFileSearch->StartSearchEx(szDevIDNO, //CStringA(strSearchDevIDNO), 
				m_cmbSearchChannel.GetItemData(m_cmbSearchChannel.GetCurSel()), 
				m_cmbFileAttribute.GetItemData(m_cmbFileAttribute.GetCurSel()), 
				m_DataBeg.GetYear(), m_DataBeg.GetMonth(), m_DataBeg.GetDay(), 0, 
				m_DataEnd.GetYear(), m_DataEnd.GetMonth(), m_DataEnd.GetDay(), 86399);
#endif
		}
		
		GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText(_T("Stop"));
	}	
}

LRESULT CClientdemoDlg::OnMsgSearchMsg(WPARAM wParam, LPARAM lParam)
{
	if (NULL != m_pFileSearch && NULL != m_pFileSearch->GetHandle())
	{
		switch(wParam)
		{
		case GPS_DOWNLOAD_MSG_FAILED:
			{
				AfxMessageBox(_T("Failure"));
				m_pFileSearch->StopSearch();
				SAFE_DELETE_OBJECT(m_pFileSearch);
				GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText(_T("Search"));
			}
			break;
		case GPS_DOWNLOAD_MSG_FINISHED:
			{
				AfxMessageBox(_T("Done"));
				GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText(_T("Search"));
				SAFE_DELETE_OBJECT(m_pFileSearch);
			}
			break;
		}
	}
	return 0;
}
int CClientdemoDlg::GetFileListIndex(GPSFile_S* pNewFile)
{
	int nCount = m_lstSearch.GetItemCount();
	int nInsertIndex = nCount;
	for (int i = 0; i < nCount; ++ i)
	{
		GPSFile_S* pFile = (GPSFile_S*)m_lstSearch.GetItemData(i);
		if (pNewFile->uiBegintime < pFile->uiBegintime)
		{
			nInsertIndex = i;
			break;
		}
	}
	return nInsertIndex;
}

CString	GetFileType(int nFileType)
{
	CString str= _T("");
	switch (nFileType)
	{
	case GPS_FILE_TYPE_NORMAL:
		str = _T("Normal");
		break;
	case GPS_FILE_TYPE_ALARM:
		str = _T("Alarm");
		break;
	}
	return str;
}

CString	GetFileSize(int nFileSize)
{
	double dMB = nFileSize * 1.0 / 1024 / 1024;
	CString str;
	str.Format(_T("%.3fMB"), dMB);
	return str;
}
LRESULT CClientdemoDlg::OnMsgSearchFile(WPARAM wParam, LPARAM lParam)
{
	GPSFile_S* pNewFile = (GPSFile_S*)wParam;
	int nIndex = GetFileListIndex(pNewFile);
	m_lstSearch.InsertItem(nIndex, NULL);
	CString str;
	CString date;
	date.Format(_T("%04d-%02d-%02d "), pNewFile->nYear, pNewFile->nMonth, pNewFile->nDay);
	if (GPS_FILE_ATTRIBUTE_JPEG == m_cmbFileAttribute.GetItemData(m_cmbFileAttribute.GetCurSel()))
	{
		str = FormatSecond(pNewFile->uiBegintime);
	}
	else
	{
		str = FormatSecond(pNewFile->uiBegintime);
		str += " - ";
		str += FormatSecond(pNewFile->uiEndtime);
		str = date + str;
	}
	m_lstSearch.SetItemText(nIndex, 0, str);
	m_lstSearch.SetItemText(nIndex, 1, GetFileType(pNewFile->nFileType));
	
	CString strChn;
	CString strDev;
	CString strID;
	//	GetDevAndChnName(pNewFile->szDevIDNO, pNewFile->nChn, strID, strDev, strChn);
	CVehicleBase* pVehi = CVehicleBaseMgr::GetInstance()->FindVehicleFromDev(pNewFile->szDevIDNO);
	if (pVehi)
	{
		strDev = pVehi->GetShowName();
	}
	else
	{
		strDev = CString(pNewFile->szDevIDNO);
	}
	m_lstSearch.SetItemText(nIndex, 2, strDev);
	
	//	strChn = GetChannelName(pNewFile);
	strChn.Format(_T("Channel-%d"), pNewFile->nChn+1);
	//	m_cmbSearchChannel.GetLBText(m_cmbSearchChannel.GetCurSel(), strChn);
	m_lstSearch.SetItemText(nIndex, 3, strChn);
	m_cmbLocation.GetLBText(m_cmbLocation.GetCurSel(), strChn);
	m_lstSearch.SetItemText(nIndex, 4, strChn);
	m_lstSearch.SetItemText(nIndex, 5, GetFileSize(pNewFile->nFileLen));
	m_lstSearch.SetItemText(nIndex, 6, CString(pNewFile->szFile));
	m_lstSearch.SetItemData(nIndex, (DWORD)pNewFile);
	return 0;
}

void CClientdemoDlg::OnButtonQuery() 
{
	CDlgLogQuery dlg;
	dlg.DoModal();
}

void CClientdemoDlg::OnButtonGetColore() 
{	
	AfxMessageBox(_T("Not implement"));	
}

void CClientdemoDlg::OnButtonSetColore() 
{	
	AfxMessageBox(_T("Not implement"));
}
#include "DlgTrackBack.h"
void CClientdemoDlg::OnButtonTrackBack() 
{	
	CDlgTrackBack dlg;
	dlg.DoModal();
}

void CClientdemoDlg::OnButtonTransParam() 
{	
	CDlgTransParam dlg;
	dlg.DoModal();
}

void CClientdemoDlg::OnButtonGetDevIp() 
{	
	CDlgGetDevIP dlg;
	dlg.DoModal();
}

void CClientdemoDlg::OnButtonGetSnapshot() 
{
	StopGetSnapshot();
	//	PostLoadMessage(LOAD_ING);
	NETCLIENT_USROpenDevSnapshotPlan(&m_lGetSnapshotPlan);
	NETCLIENT_USRSetDevSnapshotPlanCB(m_lGetSnapshotPlan, this, FUNSnapshotPlanCB);
	NETCLIENT_USRStartDevSnapshotPlan(m_lGetSnapshotPlan);

}

void CClientdemoDlg::StopGetSnapshot()
{
	if (m_lGetSnapshotPlan)
	{
		NETCLIENT_USRStopDevSnapshotPlan(m_lGetSnapshotPlan);
		NETCLIENT_USRCloseDevSnapshotPlan(m_lGetSnapshotPlan);
		m_lGetSnapshotPlan = NULL;
	}
}


void CClientdemoDlg::OnButtonSetSnapshot() 
{
	mapVehicleBase mapDev;
	int nSize = CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	if (nSize)
	{
		GPSDevSnapshotPlan_S* pOR = new GPSDevSnapshotPlan_S[nSize];
		int nIndex = 0;
		mapVehicleBaseIter item = mapDev.begin();
		mapVehicleBaseIter itemE = mapDev.end();
		CVehicleBase* pDev = NULL;
		while(item != itemE)
		{
			memset(&pOR[nIndex], 0, sizeof(GPSDevSnapshotPlan_S));
			pDev = (*item).second;
			strncpy(pOR[nIndex].szDevIDNO, pDev->GetMainDevIDNO(), sizeof(pOR[nIndex].szDevIDNO));

			for (int i = 0; i < pDev->GetChannelNum(); ++i)
			{
				if (i%2)
				{
					BIT_SET(pOR[nIndex].Plan.nChannel, i);
				}
			}
			++nIndex;
			++item;
		}

		NETCLIENT_MCSetDevSnapshotPlan(pOR, nSize, this, FUNSetDevSetCB, &m_lSetSnapshotPlan);
		SAFE_DELETE_ARRAY(pOR);
	}
}
CString FormatTime(int nSecond)
{
	CString strTime;
	strTime.Format(_T("%02d:%02d:%02d"), nSecond/3600, (nSecond%3600)/60, (nSecond%3600)%60);
	return strTime;
}
CString FormatWeek(int nWeek)
{
	switch(nWeek)
	{
	case 0:
		return _T("Sunday");
	case 1:
		return _T("Monday");
	case 2:
		return _T("Tuesday");
	case 3:
		return _T("Wednesday");
	case 4:
		return _T("Thursday");
	case 5:
		return _T("Friday");
	case 6:
		return _T("Saturday");
	}
	
	return _T("Sunday");
}

void CClientdemoDlg::FUNSnapshotPlanCB(int nType, void* pData, void * pUsr)
{
	CClientdemoDlg* pThis = (CClientdemoDlg*)pUsr;
	pThis->DoSnapshotPlanCB(nType, pData);
}
void CClientdemoDlg::DoSnapshotPlanCB(int nType, void* pData)
{
	if(GPS_DOWN_CONFIG_DATA == nType)
	{
		GPSDevSnapshotPlan_S* pOil = (GPSDevSnapshotPlan_S*)pData;
		CString strStartTime, strEndTime;
		for (int i = 0; i < 7; ++i)
		{
			TRACE("%s %s plan1:%s %s plan2:%s %s \n", pOil->szDevIDNO, FormatWeek(i),
				FormatTime(pOil->Plan.Day[i].nBegin[0]), FormatTime(pOil->Plan.Day[i].nEnd[0]),
				FormatTime(pOil->Plan.Day[i].nBegin[1]), FormatTime(pOil->Plan.Day[i].nEnd[1]));
		}
		//Prase channel
		//Please note：no recording if value is 1 and recording is value is 0
	}
	else if (GPS_DEV_DOWN_FAILED == nType)
	{
		PostMessage(WM_MSG_FAILED, 0, 0);
	}
	else if (GPS_DEV_DOWN_SUC == nType)
	{
		PostMessage(WM_MSG_SUC, 0, 0);
	}
}

void CClientdemoDlg::FUNSetDevSetCB(int nType, void* pData, void * pUsr)
{
	CClientdemoDlg* pThis = (CClientdemoDlg*)pUsr;
	pThis->DoSetDevMsg(nType, pData);
}

void CClientdemoDlg::DoSetDevMsg(int nType, void* pData)
{
	if (!PostMessage(WM_MSG_SET, nType, 0))
	{
		
	}
}

LRESULT CClientdemoDlg::OnMsgFailed(WPARAM wParam, LPARAM lParam)
{
//	m_stTip.SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_GET_FAILT));
	UpdateData(FALSE);
	return 0;
}
LRESULT CClientdemoDlg::OnMsgSuc(WPARAM wParam, LPARAM lParam)
{
//	m_stTip.SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_GET_SUCC));
	UpdateData(FALSE);
	
//	m_bLoadSuc = TRUE;
	return 0;
}
LRESULT CClientdemoDlg::OnMsgSet(WPARAM wParam, LPARAM lParam)
{
	if (GPS_DOWN_CONFIG_FAILED == wParam)
	{
// 		MSG_BOX_ID(ID_STR_PANE_SEND_CMD_SEND_FAILED);
// 		EnableCtrl(TRUE);
	}
	else if (GPS_DOWN_CONFIG_DATA == wParam)
	{
		//	PostMessage(WM_MSG_ADD_LINE_POINT_DATA, (WPARAM)pData);
	}
	else if (GPS_DOWN_CONFIG_SUC == wParam)
	{
// 		MSG_BOX_ID(ID_STR_DLG_SYSTEM_BTN_TIP_SUC);
// 		::PostMessage(GetParent()->GetSafeHwnd(), WM_CLOSE, 0, 0);
	}
	
	return 0;
}

void CClientdemoDlg::DoAlarmSnapshotFinish(CDevBase* pDevice, GPSVehicleAlarm_S* pVehiAlarm)
{
	GPSFile_S File = {0};
	GPSFile_S *pFile = &File;
	strncpy(pFile->szDevIDNO, pVehiAlarm->szDevIDNO, sizeof(pFile->szDevIDNO) - 1);
	//szImgFile : szFile  path of file
	strncpy(pFile->szFile, pVehiAlarm->Alarm.szImgFile, sizeof(pFile->szFile) - 1);
	//AlarmType : GPS_ALARM_TYPE_SNAPSHOT_FINISH
	//		pVehiAlarm->Alarm.AlarmType = GPS_ALARM_TYPE_SNAPSHOT_FINISH;
	//param[0] :  nChn  channel index
	pFile->nChn = pVehiAlarm->Alarm.Param[0];
	//param[1] : nFileLen ,length of file
	pFile->nFileLen = pVehiAlarm->Alarm.Param[1];
	//param[2] : nFileType file type
	pFile->nFileType = pVehiAlarm->Alarm.Param[2];
	//param[3] : nLocation , stroage  location
	pFile->nLocation = pVehiAlarm->Alarm.Param[3];
	//AlarmInfo : nSvrID Server ID
	pFile->nSvrID = pVehiAlarm->Alarm.AlarmInfo;

	DownFile(pFile);
}

GPSFile_S* CClientdemoDlg::GetSelFile()
{
	GPSFile_S* pFile = NULL;
	POSITION pos = m_lstSearch.GetFirstSelectedItemPosition();
	if (pos)
	{
		int nRealIndex = m_lstSearch.GetNextSelectedItem(pos);
		pFile = (GPSFile_S*)m_lstSearch.GetItemData(nRealIndex);
	}

	return pFile;
}
void CClientdemoDlg::OnButtonDown() 
{

	if (1)
	{	//Frame downooad
		DownFile(FALSE);
	}
	else
	{
		//Download file
		GPSFile_S* pFile = GetSelFile();
		if (pFile)
		{
			DownFile(pFile);
		}
	}

	/*
	GPSFile_S* pFile = GetSelFile();
	if (pFile == NULL)
	{
		AfxMessageBox(_T("please select file!");
		return;
	}

//	if (pFile->nChn == 98)
	{
		if(m_pPlayback)
		{
			StopVodDown();
		}
		else
		{
			m_pPlayback = new CPlayback;
			int nEndMinSecond = (pFile->uiEndtime - pFile->uiBegintime)*1000;
			SYSTEMTIME tm;
			GetLocalTime(&tm);
			char szFile[MAX_PATH] = {0};
			sprintf(szFile, "f:/BOCOM_%04d_%02d_%02d %02d_%02d_%02d.MPG", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
			m_pPlayback->Down(pFile, m_cmbSearchChannel.GetCurSel(), 0, nEndMinSecond, FALSE, szFile);
			m_pPlayback->SetMsgWnd(m_hWnd, WM_MSG_PLAYBACK_PLAY);
			SetTimer(TIMER_DOWNLOAD, 1, NULL);
			SetDlgItemText(IDC_BUTTON_DOWN, "Stop Down");
		}
	}
// 	else
// 	{
// 		DownFile(pFile);
// 	}
*/
}

void CClientdemoDlg::DownFile(GPSFile_S* pFile)
{
	if (m_pDownFile == NULL)
	{
		m_pDownFile = new CDownFile(pFile->nFileType);
		m_pDownFile->SetWndAndMsg(GetSafeHwnd(), WM_MSG_DOWNLOAD);
		CString str = pFile->szFile;
		str.Replace(_T("\\"), _T("/"));
		int nLen = str.ReverseFind(_T('/'));
		str = str.Right(str.GetLength() - nLen - 1);
		CString strFile;
		strFile.Format(_T("e:/%s"), str);
		m_pDownFile->StartDownFile(pFile, CStringA(strFile).GetBuffer(0));
	}
	else
	{
		AfxMessageBox(_T("Downing"));
	}
}

LRESULT CClientdemoDlg::OnMsgDownload(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case GPS_DOWNLOAD_MSG_FAILED:
		{
		//	MSG_BOX_STR(IDIRErrorString(lParam));
			if (m_pDownFile)
			{
				m_pDownFile->StopDowndFile();
				SAFE_DELETE_OBJECT(m_pDownFile);
			}
			AfxMessageBox(_T("down failed!"));
		}
		break;
	case GPS_DOWNLOAD_MSG_FINISHED:
		{
			if (m_pDownFile)
			{
				m_pDownFile->StopDowndFile();
				SAFE_DELETE_OBJECT(m_pDownFile);
			}
			AfxMessageBox(_T("down finished!"));
		}
		break;
	case GPS_DOWNLOAD_MSG_PROCESS:
		{
			double fPer = (lParam * 100.0) / m_pDownFile->GetFileInfo()->nFileLen;
			CString str;
			str.Format(_T("%0.2f%%"), fPer);
			SetDlgItemText(IDC_ST_DOWNLOAD, str);
			UpdateData(FALSE);
		}
		break;
	}
	return 0;
}

void CClientdemoDlg::OnButtonPlayback() 
{
	GPSFile_S* pFile = GetSelFile();
	if (pFile == NULL)
	{
		AfxMessageBox(_T("please select file!"));
		return;
	}

	Playback(pFile);
}

void CClientdemoDlg::Playback(GPSFile_S* pFile)
{
	CDlgPlayback dlg;
	dlg.Play(pFile, 0);
	dlg.DoModal();
}

void CClientdemoDlg::OnButtonClearAlarm() 
{
	CString strDevIDNO = GetSelDevIDNO();
	if (strDevIDNO.IsEmpty() == FALSE)
	{
		NETCLIENT_MCSendCtrl(CStringA(strDevIDNO), 18, CStringA(theApp.GetLoginUser()), CStringA(theApp.GetLoginPsw()));
	}
}
void CClientdemoDlg::InitDevCombox()
{
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	mapVehicleBaseIter iterB = mapDev.begin();
	mapVehicleBaseIter iterE = mapDev.end();
	CVehicleBase* pVehi = NULL;
	int nIndex = 0;
	while(iterB != iterE)
	{
		pVehi = (CVehicleBase*)iterB->second;
		if (pVehi != NULL)
		{
			m_cmbDev.InsertString(nIndex, pVehi->GetShowName());
			m_cmbDev.SetItemData(nIndex, DWORD(pVehi));
			nIndex++;
		}
		iterB++;
	}
	if (m_cmbDev.GetCount())
	{
		m_cmbDev.SetCurSel(0);
	}
}

void CClientdemoDlg::FUNMCMsgCB(GPSMCMsg_S* pMsg, void* pUsr)
{
	CClientdemoDlg* pThis = (CClientdemoDlg*)pUsr;
	pThis->DoCmdMsgCB(pMsg);
}

void CClientdemoDlg::DoCmdMsgCB(GPSMCMsg_S* pMsg)
{
    if (!PostMessage(WM_MSG_CMSSEND_CTRL, WPARAM(pMsg), 0))
	{
		NETCLIENT_MCReleaseMsg(pMsg);
	}
}

LRESULT CClientdemoDlg::OnCmsSendMessage(WPARAM wParam, LPARAM lParam)
{
	GPSMCMsg_S* pMsg =(GPSMCMsg_S*)wParam;
	if (pMsg != NULL)
	{
		switch (pMsg->nMsgType)
		{
		case GPS_MNGCMD_SEND_SMS:            //send msg
		//	DoSendCMSMsg(pMsg);
			break;
		case GPS_MNGCMD_SEND_PTZ:            //ptz
		//	DoSendCMSPTZ(pMsg);
			break; 
		case GPS_MNGCMD_CHANGE_USR_PWD:     //modify password
		//	DoChangeUsrPwd(pMsg); 
			break;
		case GPS_MNGCMD_SET_GPS_INTERVAL:   //GPS interval
		//	DoGpsInervalSet(pMsg);  
			break;
		case GPS_MNGCMD_SEND_CTRL:          //send power control, cut oil .etc command
			DoSendCtrl(pMsg);
			break;
		default:
			break;
		}		
	}
	
	NETCLIENT_MCReleaseMsg(pMsg);
	return 0;
}

void CClientdemoDlg::DoSendCtrl(GPSMCMsg_S* pMsg)
{
	char* szDevIDNO = (char*)(pMsg->pParam[0]); 
	int  nType = (int)(pMsg->pParam[1]);
	CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(szDevIDNO);
	if (NULL != pDevice)
	{
	//	EventInfo_S* pEvent = gEventPool.Alloc();
	//	if (NULL != pEvent)
		{
			CString strResult = _T("");
			if (GPS_OK == pMsg->nResult)	//OK
			{
			//	pEvent->Alarm = FALSE;
				
				if (nType == GPS_CTRL_TYPE_OIL_STOP)         //stop fuel
				{
			//		strResult = LOADSTRINGEX(ID_STR_MENU_DISCONNECT_OIL_SUC); //ok to stop fuel
				}
				else if (nType == GPS_CTRL_TYPE_OIL_RESTORE) //restore fuel
				{
			//		strResult = LOADSTRINGEX(ID_STR_MENU_CONNECT_OIL_SUC);
				}
				else if (nType == GPS_CTRL_TYPE_ELEC_STOP)   //power off
				{
			//		strResult = LOADSTRINGEX(ID_STR_MENU_TURNOFF_POWER_SUC);
				}
				else if (nType == GPS_CTRL_TYPE_ELEC_RESTORE) //power on
				{
			//		strResult = LOADSTRINGEX(ID_STR_MENU_TURNON_POWER_SUC);
				}
				else if (nType == GPS_CTRL_TYPE_REBOOT)       //reboot 
				{
			//		strResult = LOADSTRINGEX(ID_STR_MENU_RESTART_DEV_SUC);
				}
				else if (nType == GPS_CTRL_TYPE_RESET)        //reset
				{
			//		strResult = LOADSTRINGEX(ID_STR_MENU_FACTORY_SETTING_SUC);
				}
				else if (nType == GPS_CTRL_TYPE_CLEAR_ALARM)        //clear alarm
				{
					strResult = "OK to clear alarm";
				}
			}
			else		//Fails
			{
		//		pEvent->Alarm = TRUE;
				
				if (nType == GPS_CTRL_TYPE_OIL_STOP)         //stop fuel
				{
		//			strResult = LOADSTRINGEX(ID_STR_MENU_DISCONNECT_OIL_F); //stop fuel ok
				}
				
				else if (nType == GPS_CTRL_TYPE_OIL_RESTORE) //restore fule
				{
		//			strResult = LOADSTRINGEX(ID_STR_MENU_CONNECT_OIL_F);
				}
				else if (nType == GPS_CTRL_TYPE_ELEC_STOP)   //power off
				{
		//			strResult = LOADSTRINGEX(ID_STR_MENU_TURNOFF_POWER_F);
				}
				else if (nType == GPS_CTRL_TYPE_ELEC_RESTORE) //restore power
				{
		//			strResult = LOADSTRINGEX(ID_STR_MENU_TURNON_POWER_F);
				}
				else if (nType == GPS_CTRL_TYPE_REBOOT)       //restart
				{
		//			strResult = LOADSTRINGEX(ID_STR_MENU_RESTART_DEV_F);
				}
				else if (nType == GPS_CTRL_TYPE_RESET)        //reset
				{
		//			strResult = LOADSTRINGEX(ID_STR_MENU_FACTORY_SETTING_F);
				}
				else if (nType == GPS_CTRL_TYPE_CLEAR_ALARM)        //clear alarm
				{
					strResult = "Failed to clear alaram";
				}
			}
			AfxMessageBox(strResult);
			
// 			ShowSendCtrl(pMsg,strResult);
// 			
// 			pEvent->Desc.Format(_T("%s,%s"), pDevice->GetShowName(),strResult);
// 			pEvent->EventType = EVENT_TYPE_INFO;
// 			GetLocalTime(&(pEvent->Time));
// 			PANE_EVENT()->ShowEventInfo(pEvent);
		}
	}
	
}
#include "DlgPlay.h"
void CClientdemoDlg::OnButtonPlayFile() 
{
	CDlgPlay dlg;
	dlg.DoModal();
}
/*
 *Log Serach Param : Start Time,End Time, Log Type
Start Time：yymmdd hhmmss
End Time:yymmdd hhmmss
Log Type：0 System Log，1 Operator Log，2 Alarm Log，3 All Log
Note：140325 191000,140326 235959,1
*/
CString GetQueryParam(int nLogType)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString str;
	str.Format(_T("%02d%02d%02d %02d%02d%02d,%02d%02d%02d %02d%02d%02d,%d")
		, st.wYear-2000, st.wMonth, st.wDay, 0, 0, 0
		, st.wYear-2000, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
//		, st.wYear-2000, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond
		,nLogType);
	return str;
}
void CClientdemoDlg::OnButtonDeviceLogSearch()
{
	int nIndex = m_cmbDev.GetCurSel();
	char szIDNO[64] = {0};
	if (nIndex != CB_ERR)
	{
		CVehicleBase* pVehi = (CVehicleBase*)m_cmbDev.GetItemData(nIndex);
		if (pVehi != NULL)
		{
			strncpy(szIDNO, pVehi->GetMainDevIDNO(), sizeof(szIDNO));
		}
		else
		{
			AfxMessageBox(_T("please select device."));
		}
	}
	else
	{
		AfxMessageBox(_T("please select device."));
	}
	if(m_lQueryTransparent == NULL)
	{
		m_lstSearchLog.DeleteAllItems();
		NETMEDIA_QTOpenQueryTransparent(&m_lQueryTransparent, szIDNO);
		NETMEDIA_QTSetQueryTransparentMsgCB(m_lQueryTransparent, this, FUNQueryMsgCB);
		NETMEDIA_QTSetQueryTransparentDataCB(m_lQueryTransparent, this, FUNQueryDataCB);
		NETMEDIA_QTStartQueryTransparent(m_lQueryTransparent, 1, CStringA(GetQueryParam(3)));
	}
	else
	{
		AfxMessageBox(_T("Querying"));
	}
}

void CClientdemoDlg::FUNQueryDataCB(const char* pBuf, int nLen, void* pUsr)
{
	CClientdemoDlg* pThis = (CClientdemoDlg*)pUsr;
	pThis->DoQueryDataCB(pBuf, nLen);
}
void CClientdemoDlg::DoQueryDataCB(const char* pBuf, int nLen)
{
#pragma pack(1)
	struct NetLogFileInfo
	{
		unsigned char		Year;		
		unsigned char		Month; 		
		unsigned char		Day; 		
		unsigned char		Hour; 		
		unsigned char		Minute; 	
		unsigned char		Second; 	
		unsigned char 		type; 		
		unsigned char		reserve;	
		char 				event[256]; 
	};
#pragma pack()
	
	NetLogFileInfo* pFileInfo = (NetLogFileInfo* )pBuf;
	TRACE("%02d-%02d-%02d %02d:%02d:%02d %d  %s\n", pFileInfo->Year, pFileInfo->Month, pFileInfo->Day
		, pFileInfo->Hour, pFileInfo->Minute, pFileInfo->Second, pFileInfo->type, pFileInfo->event);
	int nIndex = 0;
	nIndex = m_lstSearchLog.InsertItem(nIndex, NULL);
	CString str;
	str.Format(_T("%d"), nIndex+1);
	m_lstSearchLog.SetItemText(nIndex, 0, str);
	str.Format(_T("%04d-%02d-%02d  %02d:%02d:%02d"), pFileInfo->Year+2000, pFileInfo->Month, pFileInfo->Day
		, pFileInfo->Hour, pFileInfo->Minute, pFileInfo->Second);
	m_lstSearchLog.SetItemText(nIndex, 1, str);
	str.Format(_T("%d"), pFileInfo->type);
	m_lstSearchLog.SetItemText(nIndex, 2, str);
	m_lstSearchLog.SetItemText(nIndex, 3, CString(pFileInfo->event));
}

void CClientdemoDlg::FUNQueryMsgCB(int nMsg, void* pUsr)
{
	CClientdemoDlg* pThis = (CClientdemoDlg*)pUsr;
	pThis->DoQueryMsgCB(nMsg);
}
/*
#define NETMEDIA_REAL_MSG_SUCCESS			0
#define NETMEDIA_REAL_MSG_CNT_DS_FD			-1
#define NETMEDIA_REAL_MSG_USR_NORIGHT		-2
#define NETMEDIA_REAL_MSG_MS_EMPTY			-3
#define NETMEDIA_REAL_MSG_CNT_MS_FD			-4
#define NETMEDIA_REAL_MSG_CNT_MS_SUC			-5
#define NETMEDIA_REAL_MSG_CNT_DEV_FD			-6
#define NETMEDIA_REAL_MSG_CNT_DEV_SUC		-7
#define NETMEDIA_REAL_MSG_MS_DISCONNECT		-8
#define NETMEDIA_REAL_MSG_USR_FULL_ERROR		-9
#define NETMEDIA_REAL_MSG_USR_ERROR			-10
#define NETMEDIA_REAL_MSG_UNKNOW				-11
#define NETMEDIA_REAL_MSG_FINISHED			-12
#define NETMEDIA_REAL_MSG_SESSION_END		-13
#define NETMEDIA_REAL_MSG_DEV_USED			-14
#define NETMEDIA_REAL_MSG_DEV_OFFLINE		-15	
#define NETMEDIA_REAL_MSG_PLAY_FINISHED		-16
*/
void CClientdemoDlg::DoQueryMsgCB(int nMsg)
{
	if (NETMEDIA_REAL_MSG_CNT_MS_SUC == nMsg)
	{
	}
	else 
	{
		if(!PostMessage(WM_MSG_TQ_MSG, WPARAM(nMsg), 0))
		{

		}
	}
}

LRESULT CClientdemoDlg::OnTQMSG(WPARAM wParam, LPARAM lParam)
{
// 	if (!m_lTransparentQuery)
// 	{
// 		return 0;
// 	}
// 	
// 	switch(wParam)
// 	{
// 	case NET_CNT_MSG_FAILED:
// 		{
// 			AfxMessageBox(_T("Transparent Query Failed");
// 		}
// 		break;
// 	case NET_CNT_MSG_DISCONNECT:
// 		{
// 			AfxMessageBox(_T("Transparent Query Failed");
// 		}
// 		break;
// 	case NET_CNT_MSG_FINISHED:
// 		{
// 			AfxMessageBox(_T("Transparent Query Success");
// 		}
// 		break;
// 	}
// 	MDVRNET_StopTransparentQuery(m_lTransparentQuery);
// 	MDVRNET_CloseTransparentQuery(m_lTransparentQuery); m_lTransparentQuery = NULL;
// 	return 0;
 	int nMsg = wParam;
	if (NULL != m_lQueryTransparent)
	{
		switch(nMsg)
		{
		case NETMEDIA_REAL_MSG_CNT_MS_SUC:
			break;
		case NETMEDIA_REAL_MSG_FINISHED:
			{
				DEBUGTraceOutput(_T("Done"));
				NETMEDIA_QTStopQueryTransparent(m_lQueryTransparent);
				NETMEDIA_QTCloseQueryTransparent(m_lQueryTransparent);
				m_lQueryTransparent = NULL;
			}
			break;
		case NETMEDIA_REAL_MSG_CNT_DS_FD:
		case NETMEDIA_REAL_MSG_CNT_MS_FD:
		case NETMEDIA_REAL_MSG_USR_NORIGHT:
		case NETMEDIA_REAL_MSG_UNKNOW:
//		default:
			{
				DEBUGTraceOutput(_T("Fails"));
				NETMEDIA_QTStopQueryTransparent(m_lQueryTransparent);
				NETMEDIA_QTCloseQueryTransparent(m_lQueryTransparent);
				m_lQueryTransparent = NULL;
			}
			break;

		}
	}	

	return 0;
}

LRESULT CClientdemoDlg::OnPlaybackPlayMsg(WPARAM wParm, LPARAM lParam)
{
	switch(wParm)
	{
// 	case MSG_PALYBACK_FINISHED:
// 	case MSG_PALYBACK_FAILED:
	case MSG_PALYBACK_DOWN_FINISHED:
		{
// 			AfxMessageBox(_T("Finish");
// 			KillTimer(TIMER_DOWNLOAD);
// 			SetDlgItemText(IDC_BUTTON_DOWN, "Start Down");
//  			StopVodDown();
		}
		break;
	default:
		break;
	}
	
	return 0;
}

void CClientdemoDlg::StopVodDown()
{
	m_pPlayback->StopDown();
	delete m_pPlayback;
	m_pPlayback = NULL;
	KillTimer(TIMER_DOWNLOAD);
	SetDlgItemText(IDC_BUTTON_DOWN, _T("Start Down"));
	AfxMessageBox(_T("Finish"));
}

// void CClientdemoDlg::OnButtonStartSnapshotTimer() 
// {
// 	mapDvsDevice mapDev;
// 	CVMgrDevice::GetInstance()->GetAllOnlineDev(mapDev);
// 	mapDvsDevIter Iter = mapDev.begin();
// 	mapDvsDevIter IterE = mapDev.end();
// 	while(Iter != IterE)
// 	{
// 		CDevBase* pDev = (*Iter).second;
// 		for (int i = 0; i < pDev->GetChannelNum(); ++i)
// 		{
// 			NETMEDIA_SNSetSnapshotDev(pDev->GetDevIDNO(), i, 0);
// 		}
// 		
// 		++Iter;
// 	}
//	SetTimer(TIMER_SNAPSHOT, 10000, NULL);

//}

// void CClientdemoDlg::OnButtonStopSnapshotTimer() 
// {
// 	NETMEDIA_SNStopSnapshotTimer();
// }

void CClientdemoDlg::FUNShnapshotTimerDataCB(const char* szDevIDNO, int nChn, const char* pBuf, int nLen, void* pUsr)
{
	CClientdemoDlg* pThis = (CClientdemoDlg*)pUsr;
	pThis->ShnapshotTimerDataCB(szDevIDNO, nChn, pBuf, nLen);
}

void CClientdemoDlg::ShnapshotTimerDataCB(const char* szDevIDNO, int nChn, const char* pBuf, int nLen)
{
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);
	CString strDir, str;
	strDir.Format(_T("%sShnapshot/"), PATHGetAppPath());
	PATHCreateDirectory(strDir);
	str.Format(_T("%s%s-%d-%04d-%02d-%02d %02d-%02d-%02d.jpg"), strDir, szDevIDNO, nChn, curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond);
	FILE* pFile = _tfopen(str, _T("wb+"));
	fwrite(pBuf, 1, nLen, pFile);
	fclose(pFile);

//	LOG_TRACE(LOG_LEVEL_HIGHEST, "Shnapshot %s-%d", szDevIDNO, nChn);
}

void CClientdemoDlg::OnTimer(UINT nIDEvent) 
{
	if (TIMER_DOWNLOAD == nIDEvent)
	{
		if (m_pPlayback)
		{
			int nProgress = 0;
			m_pPlayback->GetDownProgress(nProgress);
			CString str;
			str.Format(_T("Down: %d%%"), nProgress);
			SetDlgItemText(IDC_ST_DOWNLOAD, str);
			m_pPlayback->GetDownTime(m_nDownMinSecond);
			if (nProgress == 100)
			{
				StopVodDown();
			}
		}
	}
// 	else if (TIMER_SNAPSHOT == nIDEvent)
// 	{
// 		if (m_bStopSnapshot)
// 		{
// 			for (int i = 0; i < 4; ++i)
// 			{
// 				NETMEDIA_SNSetSnapshotDev("1000", i, 1, 120, 5, 8);
// 			}
// 			m_bStopSnapshot = FALSE;
// 		}
// 		else
// 		{
// 			for (int i = 0; i < 4; ++i)
// 			{
// 				NETMEDIA_SNSetSnapshotDev("1000", i, 0, 120, 5, 8);
// 			}
// 			m_bStopSnapshot = TRUE;
// 		}
// 		KillTimer(nIDEvent);
// 	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CClientdemoDlg::GetSelDev(char* szDevIDNO)
{
	BOOL bRet = FALSE;
	int nIndex = m_cmbDev.GetCurSel();
	if (nIndex != CB_ERR && szDevIDNO)
	{
		CVehicleBase* pVehi = (CVehicleBase*)m_cmbDev.GetItemData(nIndex);
		if (pVehi != NULL)
		{
			strncpy(szDevIDNO, pVehi->GetMainDevIDNO(), 64);
			bRet = TRUE;
		}
		
	}
	else
	{
		AfxMessageBox(_T("please select device."));
	}
	return bRet;
}

void CClientdemoDlg::OnBtnReadStatus() 
{
	char szIDNO[64] = {0};
	if (GetSelDev(szIDNO))
	{
		NETCLIENT_MCReadDevStatus(szIDNO, this, FUNMCReadStatusCB);
	}
}

void CClientdemoDlg::FUNMCReadStatusCB(GPSMCMsg_S* pMsg, void* pUsr)
{
	CClientdemoDlg* pThis = (CClientdemoDlg*)pUsr;
	pThis->DoReadStatus(pMsg);
}

void CClientdemoDlg::DoReadStatus(GPSMCMsg_S* pMsg)
{
	const char* szDevIDNO = (char*)pMsg->pParam[0];
	if (GPS_OK == pMsg->nResult)
	{
		GPSDeviceStatus_S* pDeviceStatus = (GPSDeviceStatus_S* )pMsg->pParam[1];
		CString str;
		str.Format(_T("3GFlow:%d, 4GFlow:%d"), pDeviceStatus->l3GFlow, pDeviceStatus->l4GFlow);
		AfxMessageBox(str);
	}
	else
	{
		AfxMessageBox(_T("DoReadStatus Failed"));
	}

	NETCLIENT_MCReleaseMsg(pMsg);
}
CString CClientdemoDlg::GetSnapshotCfg()
{
	CString str;
	str += PATHGetAppPath();
	str += "config.ini";
	return str;
}
UINT CClientdemoDlg::GetSnapshotDevTimeSecond()
{
	return GetPrivateProfileInt(_T("CONFIG"), _T("SnapshotDevTimeSecond"), 120, GetSnapshotCfg());
}
UINT CClientdemoDlg::GetSnapshotDevIntervalSecond()
{
	return GetPrivateProfileInt(_T("CONFIG"), _T("SnapshotDevIntervalSecond"), 10, GetSnapshotCfg());
}
UINT CClientdemoDlg::GetSnapshotDevSnapshotNum()
{
	return GetPrivateProfileInt(_T("CONFIG"), _T("SnapshotDevSnapshotNum"), 5, GetSnapshotCfg());
}

void CClientdemoDlg::OnButtonAddSnapshot() 
{
	char szDevIDNO[64] = {0};
	if (GetSelDev(szDevIDNO))
	{
		AddSnapshot(szDevIDNO);
		/*
		for (int i = 0; i < 4; ++i)
		{
			//add,delete ,change snapshot device
			//nType method
			// #define NETMEDIA_SNAPSHOT_TIMER_DEV_ADD		0	//add scheduled snaphot plan for a device
			// #define NETMEDIA_SNAPSHOT_TIMER_DEV_DEL		1	//remove snapshot plan
			// #define NETMEDIA_SNAPSHOT_TIMER_DEV_MODIFY	2	//modify plan
			//nTimeSecond - take snapshot every x second
			//nIntervalSecond - continous taking snapshot interval
			//nSnapshotNum - the number of continous taking snapshot.
			UINT nTimeSecond = GetSnapshotDevTimeSecond();
			UINT nIntervalSecond = GetSnapshotDevIntervalSecond();
			UINT nSnapshotNum = GetSnapshotDevSnapshotNum();
			NETMEDIA_SNSetSnapshotDev(szDevIDNO, i, NETMEDIA_SNAPSHOT_TIMER_DEV_ADD, nTimeSecond, nIntervalSecond, nSnapshotNum);
		}
		*/
	}
}

void CClientdemoDlg::OnButtonDelSnapshot() 
{
	char szDevIDNO[64] = {0};
	if (GetSelDev(szDevIDNO))
	{
		DelSnapshot(szDevIDNO);
		/*
		for (int i = 0; i < 4; ++i)
		{
			NETMEDIA_SNSetSnapshotDev(szDevIDNO, i, NETMEDIA_SNAPSHOT_TIMER_DEV_DEL, 120, 10, 5);
		}
		*/
	}
}
void CClientdemoDlg::AddSnapshot(char* szDevIDNO)
{
	for (int i = 0; i < 4; ++i)
	{
		UINT nTimeSecond = GetSnapshotDevTimeSecond();
		UINT nIntervalSecond = GetSnapshotDevIntervalSecond();
		UINT nSnapshotNum = GetSnapshotDevSnapshotNum();
		NETMEDIA_SNSetSnapshotDev(szDevIDNO, i, NETMEDIA_SNAPSHOT_TIMER_DEV_ADD, nTimeSecond, nIntervalSecond, nSnapshotNum);
	}
}
void CClientdemoDlg::DelSnapshot(char* szDevIDNO) 
{
	for (int i = 0; i < 4; ++i)
	{
		NETMEDIA_SNSetSnapshotDev(szDevIDNO, i, NETMEDIA_SNAPSHOT_TIMER_DEV_DEL, 120, 10, 5);
	}
}

void CClientdemoDlg::OnButtonResumeDown() 
{
	
	DownFile(TRUE);
}

void CClientdemoDlg::DownFile(BOOL bResumeDown)
{
	GPSFile_S* pFile = GetSelFile();
	if (pFile == NULL)
	{
		AfxMessageBox(_T("please select file!"));
		return;
	}
	
	//	if (pFile->nChn == 98)
	{
		if(m_pPlayback)
		{
			StopVodDown();
		}
		else
		{
			m_pPlayback = new CPlayback;
			int nStartMinSecond = 0;
			if (bResumeDown)
			{
				nStartMinSecond = m_nDownMinSecond;
			}
			int nEndMinSecond = (pFile->uiEndtime - pFile->uiBegintime)*1000;
			SYSTEMTIME tm;
			GetLocalTime(&tm);
			if (bResumeDown == FALSE)
			{
				CString strPath = PATHGetAppPath();
				strPath += _T("DOWNLOAD_FILE\\");
				strPath += CString(pFile->szDevIDNO);
				strPath += _T("\\");
				CString strTime;
				strTime.Format(_T("%04d-%02d-%02d\\"), tm.wYear, tm.wMonth, tm.wDay);
				strPath += strTime;
				PATHCreateDirectory(strPath);
				
				//m_strFileDown.Format(_T("c:/BOCOM_%04d_%02d_%02d %02d_%02d_%02d.MPG"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
				char szFile[MAX_PATH] = {0};
				AVDEC_MakeRecName(AVDEC_GetDecHandle(), &tm, &tm, pFile->nChn, pFile->nFileType, szFile);

				m_strFileDown = strPath + CString(szFile);
			}
		//	sprintf(szFile, "f:/BOCOM_%04d_%02d_%02d %02d_%02d_%02d.MPG", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
			m_pPlayback->Down(pFile, m_cmbSearchChannel.GetCurSel(), nStartMinSecond, nEndMinSecond, FALSE, CStringA(m_strFileDown), bResumeDown);
			m_pPlayback->SetMsgWnd(m_hWnd, WM_MSG_PLAYBACK_PLAY);
			SetTimer(TIMER_DOWNLOAD, 1000, NULL);
			SetDlgItemText(IDC_BUTTON_DOWN, _T("Stop Down"));
		}
	}
}

CVehicleBase* CClientdemoDlg::GetSelVehicle()
{
	int nIndex = m_cmbDev.GetCurSel();
	if (nIndex != CB_ERR)
	{
		return (CVehicleBase*)m_cmbDev.GetItemData(nIndex);
	}

	return NULL;
}

CString CClientdemoDlg::GetSelDevIDNO()
{
	CVehicleBase* pVehicle = GetSelVehicle();
	if (pVehicle)
	{
		return CString(pVehicle->GetMainDevIDNO());
	}
	return CString();
}

void CClientdemoDlg::OnBnClickedButtonAddSn()
{
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	mapVehicleBaseIter iter = mapDev.begin();
	while(iter != mapDev.end())
	{
		CVehicleBase* pDev = (*iter).second;
		if (pDev)
		{
			AddSnapshot(pDev->GetMainDevIDNO());
		}
		++iter;
	}
}


void CClientdemoDlg::OnBnClickedButtonDelSn()
{
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	mapVehicleBaseIter iter = mapDev.begin();
	int nCount = 0;
	while(iter != mapDev.end())
	{
		if (nCount > 80)
		{
			break;
		}
		CVehicleBase* pDev = (*iter).second;
		if (pDev)
		{
			DelSnapshot(pDev->GetMainDevIDNO());
		}
		++nCount;
		++iter;
	}
}

void CClientdemoDlg::OnButtonTranData() 
{
	
	CDlgTransData Dlg;
	Dlg.DoModal();
}


void CClientdemoDlg::OnNMRClickTreeDev(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint point;
	GetCursorPos(&point);

	CPoint pointInTree = point;
	m_treeDev.ScreenToClient(&pointInTree);

	UINT flag = TVHT_ONITEM;
	HTREEITEM hItem = m_treeDev.HitTest(pointInTree, &flag);
	
 	if (hItem)
	{
		m_treeDev.SelectItem(hItem);

		CMenu menu;
		menu.CreatePopupMenu();
		int nIndex = 0;
 		if (IsChannelItem(m_treeDev, hItem))
 		{
			
			menu.InsertMenu(nIndex++, MF_BYPOSITION, ID_MAIN_FRONT, _T("Front-end Capture"));
			//menu.LoadMenu(IDR_RCLICKMENU);
 		}
		else
		{
			CObject* pObj = (CObject*)m_treeDev.GetItemData(hItem);
			if (pObj && 0 == strcmp("CVehicleBase", pObj->GetRuntimeClass()->m_lpszClassName))
			{
				CVehicleBase* pVehi = (CVehicleBase*)pObj;
				if (pVehi->GetOnline())
				{
					menu.InsertMenu(nIndex++, MF_BYPOSITION, ID_MENU_SEND_FILE, _T("Send File"));
					menu.InsertMenu(nIndex++, MF_BYPOSITION, ID_MENU_PARAMER_CONFIG, _T("Config Parameters"));
					menu.InsertMenu(nIndex++, MF_BYPOSITION, ID_MENU_COORDINATE, _T("Navigation coordinates are issued"));
				}
				else
				{
#ifdef _DEBUG
					menu.InsertMenu(nIndex++, MF_BYPOSITION | MF_GRAYED, -1, pVehi->GetShowName() + _T("(Device is not online)"));
#endif // _DEBUG
				}
			}
		}
		if (nIndex)
		{
			CMenu* pPopup = &menu;
			POINT pt;
			::GetCursorPos(&pt);
			pPopup->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
		}
 	}

	*pResult = 0;
}


void CClientdemoDlg::OnMainFront()
{
	if (m_pSnapshot)
	{
		AfxMessageBox(_T("Was snapping pictures ... "));
		return;
	}
	HTREEITEM hItem = m_treeDev.GetSelectedItem();
	if (hItem)
	{
		int nWndIndex = 0;
		if (IsChannelItem(m_treeDev, hItem))
		{
			HTREEITEM hDevice= m_treeDev.GetParentItem(hItem);
			CVehicleBase* pVehi = (CVehicleBase*)m_treeDev.GetItemData(hDevice);
			if (pVehi != NULL)
			{
				int nChan = m_treeDev.GetItemData(hItem);
				CDevBase* pDevice = pVehi->GetDevByChn(nChan);
				if (pDevice != NULL)
				{
					int nRealChan = pDevice->GetRealChn(nChan+1);
					nRealChan--;


					m_pSnapshot = new CDownSnapshot;

					//TCHAR szTmpPath[MAX_PATH], szFilename[MAX_PATH];
					//::GetTempPath (MAX_PATH, szTmpPath);
					//::GetTempFileName (szTmpPath, TEXT("cmsclientbmp"), 0, szFilename);

					TCHAR szFilename[MAX_PATH] = {0};
					CString strFileName;

					SYSTEMTIME sysTime;
					::GetLocalTime(&sysTime);
					CString strPath;
					GetDlgItemText(IDC_SNAPSHOT_PATH, strPath);
					strFileName.Format(_T("%s%s-%s-%04d-%02d-%02d %02d-%02d-%02d.jpg"),
						strPath, pDevice->GetDevIDNO(), pDevice->GetChnName(nRealChan), 
						sysTime.wYear, sysTime.wMonth, sysTime.wDay,
						sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
					m_pSnapshot->SetDownFileName(strFileName);
					m_pSnapshot->SetDevInfo(pDevice->GetID(), nRealChan);

					m_pSnapshot->SetDownMsg(GetSafeHwnd(), WM_MSG_SNAPSHOT);
					m_pSnapshot->StartDown();
				}
			}
		}
	}
}

LRESULT CClientdemoDlg::OnMsgSnapshot( WPARAM wParm, LPARAM lParam )
{
	if (m_pSnapshot)
	{
		CString strFileName = m_pSnapshot->GetDownFileName();
		m_pSnapshot->StopDown();
		SAFE_DELETE_OBJECT(m_pSnapshot);
		switch(wParm)
		{
		case GPS_DOWNLOAD_MSG_FAILED:
			{
				AfxMessageBox(_T("Snapshot failed!\r\n") + strFileName);
			}
			break;
		case GPS_DOWNLOAD_MSG_FINISHED:
			{
				AfxMessageBox(_T("Snapshot finished!\r\n") + strFileName);
			}
			break;
		}

	}
	return 0;
}

void CClientdemoDlg::OnBnClickedBtnBrowse()
{
	TCHAR pszPath[MAX_PATH];
	BROWSEINFO bi;
	bi.hwndOwner      = this->GetSafeHwnd();
	bi.pidlRoot       = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle      = NULL;//TEXT("select folder");
	bi.ulFlags        = 0;//BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT
	bi.lpfn           = NULL;
	bi.lParam         = 0;
	bi.iImage         = 0;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl == NULL)
	{
		return;
	}

	if (SHGetPathFromIDList(pidl, pszPath))  
	{
		SetDlgItemText(IDC_SNAPSHOT_PATH, pszPath);
	}
}


void CClientdemoDlg::OnNMClickTreeDev(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint point;
	GetCursorPos(&point);

	CPoint pointInTree = point;
	m_treeDev.ScreenToClient(&pointInTree);

	UINT flag = TVHT_ONITEM;
	HTREEITEM hItem = m_treeDev.HitTest(pointInTree, &flag);
	if (hItem)
	{
		if (!IsChannelItem(m_treeDev, hItem))
		{
			CObject* pObj = (CObject*)m_treeDev.GetItemData(hItem);
			if (pObj && 0 == strcmp("CVehicleBase", pObj->GetRuntimeClass()->m_lpszClassName))
			{
				CVehicleBase* pVehi = (CVehicleBase*)m_treeDev.GetItemData(hItem);
				if (pVehi != NULL)
				{
					m_cmbDev.SelectString(0, pVehi->GetShowName());
				}
			}
		}
	}

	*pResult = 0;
}


void CClientdemoDlg::OnBnClickedButtonAudioStart()
{
	// TODO: 在此添加控件通知处理程序代码
// 	char szSession[64] = {0};
// 	NETCLIENT_GetSession(szSession, sizeof(szSession));

	int nIndex = m_cmbDev.GetCurSel();
	char szIDNO[64] = {0};
	if (nIndex == CB_ERR)
	{
		return;
	}
	CVehicleBase* pVehi = (CVehicleBase*)m_cmbDev.GetItemData(nIndex);

	int nAudio = m_cmbAudio.GetItemData(m_cmbAudio.GetCurSel());
	CString strDevIDNO(pVehi->GetMainDevice()->GetDevIDNOForChar());
	VOICETalkback()->StartTalkback(strDevIDNO, 0, 
		(AUDIO_TYPE_TALKBACK == nAudio) ? true : false);
	VOICETalkback()->OpenSound();
	m_cmbAudio.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_AUDIO_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_AUDIO_STOP)->EnableWindow(TRUE);
}


void CClientdemoDlg::OnBnClickedButtonAudioStop()
{
	// TODO: 在此添加控件通知处理程序代码
	int nAudio = m_cmbAudio.GetItemData(m_cmbAudio.GetCurSel());
// 	if (AUDIO_TYPE_TALKBACK == nAudio)
// 	{
// 		VOICETalkback()->CloseSound();
// 		VOICETalkback()->StopTalkback();
// 	}
// 	else
	{
		VOICETalkback()->CloseSound();
		VOICETalkback()->StopTalkback();
	}
	m_cmbAudio.EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_AUDIO_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_AUDIO_STOP)->EnableWindow(FALSE);
}



void CClientdemoDlg::OnBnClickedBtnFuncPtz()
{
	if (NULL == m_pDlgPanePtz)
	{
		m_pDlgPanePtz = new CDlgPanePtz;
		if (!m_pDlgPanePtz->Create(CDlgPanePtz::IDD, this))
		{
			SAFE_DELETE_OBJECT(m_pDlgPanePtz);
		}
	}
	if (m_pDlgPanePtz->GetSafeHwnd())
	{
		BOOL bIsShow = m_pDlgPanePtz->IsWindowVisible();
		m_pDlgPanePtz->ShowWindow(!bIsShow);
	}
}

BOOL CClientdemoDlg::PtzControl( int nCommand, int nParam, int nSpeed )
{
	BOOL bRet = FALSE;
	int nVehiID = 0;
	int nChannel = 0;
	if (m_pDlgPaneView->GetSafeHwnd())
	{
		m_pDlgPaneView->PtzControl(nCommand, nParam, nSpeed);
	}
	//if (m_pViewWnd[m_nActiveIndex]->GetPreviewDevice(nVehiID, nChannel))
	//{
	//	m_pViewWnd[m_nActiveIndex]->SetViewModeEx(VIEW_MODE_REAL);
	//	LongVehicleBase lVehicle = COMMONMGRVEHI_FindDvsDeviceByID(nVehiID);
	//	if (lVehicle)
	//	{
	//		LongDevBase lDev = COMMONVEHICLE_GetDevInfo(lVehicle, E_VEHI_LONGDEV_GetComDev);
	//		if (lDev == NULL)
	//		{
	//			lDev = COMMONVEHICLE_GetDevInfo(lVehicle, E_VEHI_LONGDEV_GetMainDevice);
	//		}
	//		if (lDev != NULL)
	//		{
	//			if(S_OK == NETCLIENT_MCSendPtz(COMMONDEV_GetIDNOForChar(lDev), nChannel, nCommand, nSpeed, nParam, this, FUNPtzMsgCB))
	//			{
	//				bRet = TRUE;
	//				COMMONDEV_SetPTZStatus(lDev, nCommand, nChannel);
	//			}
	//		}
	//	}
	//}
	return bRet;
}


void CClientdemoDlg::OnBnClickedChkPreviewRecord()
{
	CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHK_PREVIEW_RECORD));
	if (pBtn->GetSafeHwnd())
	{
		g_bPreviewAutoRecord = pBtn->GetCheck();
	}
}


void CClientdemoDlg::OnBnClickedBtnOpenRecordPath()
{
	CString strPath = PATHGetAppPath();
	strPath += _T("RECORD_FILE\\");

	if (PathFileExists(strPath))
	{
		::ShellExecute(NULL, _T("open"), _T("Explorer.exe"), strPath, NULL, SW_SHOWDEFAULT);
	}
}


void CClientdemoDlg::OnBnClickedBtnParamConfig()
{
	int nIndex = m_cmbDev.GetCurSel();
	if (nIndex != CB_ERR)
	{
		CVehicleBase* pVehi = (CVehicleBase*)m_cmbDev.GetItemData(nIndex);
		if (pVehi)
		{
			CDevBase* pDev = pVehi->GetMainDevice();
			if (pDev)
			{
				CDlgParamConfig dlg;
				dlg.SetDevID(pDev->GetID());
				dlg.DoModal();
			}
		}
	}
}

void CClientdemoDlg::OnMenuSendFile()
{
	int nIndex = m_cmbDev.GetCurSel();
	if (nIndex != CB_ERR)
	{
		CVehicleBase* pVehi = (CVehicleBase*)m_cmbDev.GetItemData(nIndex);
		if (pVehi)
		{
			CDevBase* pDev = pVehi->GetMainDevice();
			if (pDev)
			{
				CDlgSendFileToDev dlg;
				dlg.SetDevID(pDev->GetID());
				dlg.DoModal();
			}
		}
	}
}

void CClientdemoDlg::OnMenuParamerConfig()
{
	int nIndex = m_cmbDev.GetCurSel();
	if (nIndex != CB_ERR)
	{
		CVehicleBase* pVehi = (CVehicleBase*)m_cmbDev.GetItemData(nIndex);
		if (pVehi)
		{
			CDevBase* pDev = pVehi->GetMainDevice();
			if (pDev)
			{
				CDlgParamerConf dlg;
				dlg.SetDevice(pDev->GetID());
				//dlg.SetAueFunction(TRUE, 1, _T("11"), _T("11"));
				dlg.DoModal();
			}
		}
	}
}

void CClientdemoDlg::OnMenuCoordinate()
{
	int nIndex = m_cmbDev.GetCurSel();
	if (nIndex != CB_ERR)
	{
		CVehicleBase* pVehi = (CVehicleBase*)m_cmbDev.GetItemData(nIndex);
		if (pVehi)
		{
			CDevBase* pDev = pVehi->GetMainDevice();
			if (pDev)
			{
				CDlgParamerConf dlg;
				dlg.SetDevice(pDev->GetID());
				dlg.SetAueFunction(TRUE, 1, _T(""), _T(""));
				dlg.DoModal();
			}
		}
	}
}
