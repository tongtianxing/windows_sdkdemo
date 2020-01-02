// DlgParamerConf.cpp : implementation file
//

#include "stdafx.h"
#include "DlgParamerConf.h"
#include "DlgLoading.h"

#include "DlgDevList.h"
#include "DlgAueCoordinateSetup.h"
#include "DlgAueCheckedSetup.h"
#include "DlgAueAlcoholSetup.h"
#include "DlgAueWifiSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_MSG_PARAMER_CONF 	WM_USER + 0x1903
#define WM_MSG_UPLOAD           WM_USER + 0x1904
#define WM_MSG_PROMOTE          WM_USER + 0x1905
#define WM_MSG_GET_PARAM        WM_USER + 0x1906
#define WM_MSG_SET_PARAM        WM_USER + 0x1907
#define WM_MSG_SHOW_DISPLAY     WM_USER + 0x1908

/////////////////////////////////////////////////////////////////////////////
// CDlgParamerConf dialog

int g_nMapType;
CString g_strJingDu;
CString g_strWeiDu;


FUNTransparentConfig g_pfnTransparentConfig = NULL;
void*	g_pTransparentUser = NULL;

CDlgParamerConf::CDlgParamerConf(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParamerConf::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgParamerConf)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nDevID = NULL;
	m_lParamerConfHandle = NULL;
	m_lUploadHandle = NULL;
//	m_lpSetDevCfg= NULL;
	m_lPromoteHanle = NULL;
	m_bFlag = FALSE;

	m_pFile = NULL;
	memset(m_szFileName, 0, sizeof(m_szFileName));
	memset(m_szUploadDestFile, 0, sizeof(m_szUploadDestFile));
	memset(&m_FileInfo, 0, sizeof(m_FileInfo));	
	m_hSheetWnd = NULL;
	m_pWnd = NULL;
	m_bContinuePromote = FALSE;
	m_bContinueUpload = FALSE;
	m_nFirstCount = 0;
	m_bFlagIsImPort = FALSE;

	memset(m_szSaveFileName, 0, sizeof(m_szSaveFileName));
	m_lGetParamHandle = NULL;
	m_lSetParamHandle = NULL;
	m_nGetParamResult = 0;
	memset(m_szExportCfgFile, 0, sizeof(m_szExportCfgFile));
	m_bIsTransparenEx = FALSE;

	m_pConfigEntity = NULL;
	m_pDlgLoading = NULL;
	m_bTransparenParam = FALSE;

	m_bAueCoordinate = FALSE;


	m_hEventParam=::CreateEvent(NULL, FALSE, FALSE, NULL);


	m_pDlgAueAlcoholSetup = NULL;
	m_pDlgAueCheckedSetup = NULL;
	m_pDlgAueCoordinateSetup = NULL;
	m_pDlgAueWifiSetup = NULL;
}

void CDlgParamerConf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgParamerConf)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_BUT_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_BUT_IMPORT, m_btnImport);
	DDX_Control(pDX, IDC_BUT_SAVE_MUT, m_btnSaveMut);
	DDX_Control(pDX, IDC_BUT_SAVE, m_btnSave);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgParamerConf, CDialog)
	//{{AFX_MSG_MAP(CDlgParamerConf)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUT_SAVE, OnButSave)
	ON_BN_CLICKED(IDC_BUT_SAVE_MUT, OnButSaveMut)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_PARAMER_CONF, OnGetParameterMsg)
	ON_MESSAGE(WM_MSG_UPLOAD, OnUpLoadMsg)
	ON_MESSAGE(WM_MSG_PROMOTE, OnMsgPromote)
	ON_MESSAGE(WM_MSG_GET_PARAM, OnMsgGetParam)
	ON_MESSAGE(WM_MSG_SET_PARAM, OnMsgSetParam)
	ON_MESSAGE(WM_MSG_SHOW_DISPLAY, OnMsgShowDispaly)
	ON_BN_CLICKED(IDC_BUTTON_AUE_WIFI, &CDlgParamerConf::OnBnClickedButtonAueWifi)
	ON_BN_CLICKED(IDC_BUTTON_AUE_CHECKED, &CDlgParamerConf::OnBnClickedButtonAueChecked)
	ON_BN_CLICKED(IDC_BUTTON_AUE_ALCOHOL, &CDlgParamerConf::OnBnClickedButtonAueAlcohol)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgParamerConf message handlers

BOOL CDlgParamerConf::PreTranslateMessage(MSG* pMsg) 
{

// 	if (IsDialogMessage(pMsg))
// 	{
// 		return TRUE;
// 	}
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgParamerConf::StartGetDevParamer()
{
	if (NULL == m_lParamerConfHandle)
	{
		OpenDownFile();
		if (m_pFile)
		{
			SetDlgItemText(IDC_ST_READ_TIP,LOADSTRINGEX(ID_STR_DLG_PARAMER_TIP_GET));//正在获取设备参数信息，请稍等......

			GetDlgItem(IDC_BUT_SAVE_MUT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUT_SAVE)->EnableWindow(FALSE);		
			GetDlgItem(IDC_BUT_EXPORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUT_IMPORT)->EnableWindow(FALSE);

			CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(m_nDevID);
			NETCLIENT_DLOpenGetDevCfg(&m_lParamerConfHandle, pDev->GetIDNOForChar());
			NETCLIENT_DLSetGetDCfgMsgCB(m_lParamerConfHandle, this, FUNGetDevParamerMsgCB);
			NETCLIENT_DLSetGetDCfgDataCB(m_lParamerConfHandle, this, FUNDataCB);
			NETCLIENT_DLStartGetDevCfg(m_lParamerConfHandle);

			return TRUE;
		}
	}
	return FALSE;
}

void CDlgParamerConf::FUNGetDevParamerMsgCB(int nMsg, int nParam, void* pUsr)
{
	CDlgParamerConf* pThis = (CDlgParamerConf*)pUsr;
	pThis->DoGetDevParamerMsgCB(nMsg, nParam);
}

void CDlgParamerConf::DoGetDevParamerMsgCB(int wParam, int lParam)
{
	PostMessage(WM_MSG_PARAMER_CONF, wParam, lParam);
}

void CDlgParamerConf::OpenDownFile()
{
	ASSERT(NULL == m_pFile);

	m_pFile = _tfopen(m_szExportCfgFile, _T("wb"));
}

void CDlgParamerConf::CloseDownFile()
{
	if (m_pFile)
	{
		fclose(m_pFile);	m_pFile = NULL;
	}
}

void CDlgParamerConf::DoDataCB(const char* pBuf, int nLen, long nPos)
{
//	TRACE("CDlgParamerConf::DoDataCB nPos:%d, nLength:%d\n", nPos, nLen);
	if (m_pFile)
	{
		long nCurPos = ftell(m_pFile);
		if (nPos > nCurPos)
		{
			int nWriteLen = nPos - nCurPos;
			if (nWriteLen > 0)
			{
				std::vector<char> VecBuf;
				VecBuf.resize(nWriteLen);
				int nFileWriteLen = fwrite(&VecBuf[0], 1, nWriteLen, m_pFile);
			}
		}
		else if (nPos < nCurPos)
		{
			fseek(m_pFile, nPos, SEEK_SET);
		}
		
		fwrite(pBuf, 1, nLen, m_pFile);
	}
}

void CDlgParamerConf::FUNDataCB(const char* pData, int nDataLen, long nPos, void* pUsr)
{
//	TRACE("CDlgParamerConf::FUNDataCB nPos:%d\n", nPos);
	CDlgParamerConf* pThis = (CDlgParamerConf*)pUsr;
	pThis->DoDataCB(pData, nDataLen, nPos);
}

void CDlgParamerConf::Loadlanguage()
{
//	SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_WINDOW_NAME)); //车辆参数配置

	GetDlgItem(IDC_BUT_SAVE_MUT)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_SAVE_MORE));//保存多个设备
	GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG));//配置
	GetDlgItem(IDCANCEL)->SetWindowText(LOADSTRINGEX(ID_STR_CANCEL));//退出

	SetDlgItemText(IDC_BUT_EXPORT,LOADSTRINGEX(ID_STR_DLG_PARAMER_EXPORT));//导出配置
	SetDlgItemText(IDC_BUT_IMPORT,LOADSTRINGEX(ID_STR_DLG_PARAMER_IMPORT));//导入配置

	SetDlgItemText(IDC_STATIC_TELL,LOADSTRINGEX(ID_STR_DLG_PARAMER_TIP));//提示:设备参数无修改,不会配置设备参数!	

	SetDlgItemText(IDC_BUTTON_AUE_ALCOHOL, _T("Alcohol"));
	SetDlgItemText(IDC_BUTTON_AUE_WIFI, _T("Wifi"));
	SetDlgItemText(IDC_BUTTON_AUE_CHECKED, _T("Checked"));
}


#define TIMER_SHOW_DISPLAY		1

BOOL CDlgParamerConf::OnInitDialog() 
{
	ModifyStyleEx(WS_EX_CONTROLPARENT, 0);
	CDialog::OnInitDialog();

	m_btnExport.ShowWindow(SW_HIDE);
	m_btnImport.ShowWindow(SW_HIDE);

	g_pfnTransparentConfig = FUNTransparentConfig;
	g_pTransparentUser = this;

	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(m_nDevID);
    CString strDevName = pDev->GetShowName();
	if (m_bAueCoordinate)
	{
		strDevName = _T("Navigation coordinates are issued");
	}
	else
	{
		strDevName += _T(" - Parameter Config");
	}

	SetWindowText(strDevName); //车辆参数配置

	if (m_pDlgLoading == NULL)
	{
		m_pDlgLoading = new CDlgLoading();
		m_pDlgLoading->Create( CDlgLoading::IDD, this );
	}

	Loadlanguage();
	int nWidth = 600;//800;
	int nHeight = 480;//640;
	if (m_bAueCoordinate)
	{
		nWidth = 360;
		nHeight = 200;
	}
	if (nWidth != 0 && nHeight != 0)
	{
		SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER);
		CenterWindow();
		CRect rcMove, rcClient;
		GetClientRect(&rcClient);
		CRect rcButton;
		if (!m_bAueCoordinate)
		{
			GetDlgItem(IDC_BUTTON_AUE_CHECKED)->GetClientRect(rcButton);
		}
		rcMove.left = rcClient.left + rcButton.Width() + 4;
		rcMove.right = rcClient.right - 1;
		rcMove.top = rcClient.top + 1;
		rcMove.bottom = rcClient.bottom - 5;
		GetDlgItem(IDC_ST_PARAMER_MAIN)->MoveWindow(&rcMove);
	}

	if (m_bAueCoordinate)
	{
		m_btnSaveMut.ShowWindow(SW_SHOW);
		m_btnSave.ShowWindow(SW_SHOW);
		m_btnCancel.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_TELL)->ShowWindow(SW_SHOW);
		PostMessage(WM_MSG_SHOW_DISPLAY);
	}
	else
	{
		CustomCreateDlg(m_pDlgAueAlcoholSetup, this);
		CustomCreateDlg(m_pDlgAueCheckedSetup, this);
		CustomCreateDlg(m_pDlgAueWifiSetup, this);
		m_pDlgAueWifiSetup->ShowWindow(SW_SHOW);

		CRect rcClient, rcGroup;
		GetClientRect(&rcClient);
		GetDlgItem(IDC_ST_PARAMER_MAIN)->GetWindowRect(rcGroup);
		ScreenToClient(rcGroup);
		CRect rcAue = rcClient;
		rcAue.left = rcGroup.left + 3;
		m_pDlgAueAlcoholSetup->MoveWindow(rcAue);
		m_pDlgAueCheckedSetup->MoveWindow(rcAue);
		m_pDlgAueWifiSetup->MoveWindow(rcAue);

		
		GetDlgItem(IDC_BUTTON_AUE_WIFI)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_AUE_CHECKED)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_AUE_ALCOHOL)->ShowWindow(SW_SHOW);
		m_btnSaveMut.ShowWindow(SW_HIDE);
		m_btnSave.ShowWindow(SW_HIDE);
		m_btnCancel.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_TELL)->ShowWindow(SW_HIDE);
		PostMessage(WM_MSG_SHOW_DISPLAY);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgParamerConf::StopGetParmer() 
{
	if (m_lParamerConfHandle != NULL)
	{	
		NETCLIENT_DLStopGetDevCfg(m_lParamerConfHandle);
		NETCLIENT_DLCloseGetDevCfg(m_lParamerConfHandle);	

		m_lParamerConfHandle = NULL;
	}
}

LRESULT CDlgParamerConf::OnGetParameterMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case GPS_DOWNLOAD_MSG_BEGIN:
		{
			//正在获取设备参数信息，请等待......
			SetDlgItemText(IDC_ST_READ_TIP,LOADSTRINGEX(ID_STR_DLG_PARAMER_TIP_GET));//正在获取设备参数信息，请稍等......
		}
		break;
	case GPS_DOWNLOAD_MSG_FAILED:
		{
			SetDlgItemText(IDC_ST_READ_TIP, LOADSTRINGEX(ID_STR_DLG_PARAMER_GET_FAILT));//获取设备参数失败!		
		
			ParmerConfError();
			m_bGetParamSuc = FALSE;
			m_nGetParamResult = lParam;
			m_pDlgLoading->CloseLoading();
			SetEvent(m_hEventParam);
		}
		break;
	case GPS_DOWNLOAD_MSG_FINISHED:
		{
			//close
			StopGetParmer();
		    CloseDownFile();
			GetDlgItem(IDC_BUT_SAVE_MUT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUT_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUT_EXPORT)->EnableWindow(TRUE);
     	    GetDlgItem(IDC_BUT_IMPORT)->EnableWindow(TRUE);		
//			PulginDeviceConfigMgrIns()->SetCurrentDeviceConfigEntity(m_pConfigEntity);
// 			CRect rc, rcClient;
// 			::GetWindowRect(m_hSheetWnd, rc);
// 			rc.bottom += 100;
// 			rc.left += 60;
// 			MoveWindow(rc);
			//SetDlgItemText(IDC_ST_READ_TIP, LOADSTRINGEX(ID_STR_DLG_PARAMER_GET_SUCC));	
			SetDlgItemText(IDC_ST_READ_TIP, _T(""));
			m_bGetParamSuc = TRUE;

			m_pDlgLoading->CloseLoading();
			SetEvent(m_hEventParam);
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return 0;
}

void CDlgParamerConf::StopUpload()
{
	if (m_lUploadHandle)
	{
		NETCLIENT_ULStopUpload(m_lUploadHandle);
		NETCLIENT_ULCloseUpload(m_lUploadHandle);
		m_lUploadHandle = NULL;
	}
}

void CDlgParamerConf::FUNUploadMsgCB(int nMsg, int nParam, void* pUsr)
{
	CDlgParamerConf* pThis = (CDlgParamerConf*)pUsr;
	pThis->DoUploadMsgCB(nMsg, nParam);	
}

LRESULT CDlgParamerConf::OnUpLoadMsg(WPARAM wParam, LPARAM lParam)
{   
	switch(wParam)
	{
	case GPS_UPLOAD_MSG_PROCESS:
		{
			//
			SetDlgItemText(IDC_ST_READ_TIP,LOADSTRINGEX(ID_STR_DLG_PARAMER_UP_FILE));

			m_pWnd = CWnd::FromHandle( m_hSheetWnd );
			if( m_pWnd != NULL )
			{
				m_pWnd->EnableWindow( FALSE );
			}
		}
		break;
	case GPS_UPLOAD_MSG_FAILED:
		{
			GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG));//"配置"
			
			m_pWnd = CWnd::FromHandle( m_hSheetWnd );

			if( m_pWnd != NULL )
			{
				m_pWnd->EnableWindow(TRUE);
			}
			
			EnableCtrl(TRUE);
			StopUpload();

			m_bGetParamSuc = FALSE;
			m_nGetParamResult = lParam;
			m_pDlgLoading->CloseLoading();
			SetEvent(m_hEventParam);
		}
		break;
	case GPS_UPLOAD_MSG_FINISHED:
		{
			SetDlgItemText(IDC_ST_READ_TIP, LOADSTRINGEX(ID_STR_DLG_PARAMER_UP_SUCC));//上传配置文件到服务器成功!
			
			NETCLIENT_ULGetDestFileName(m_lUploadHandle,&m_nlpSvrID, m_szUploadDestFile);
			StopUpload();
			StartDownLoadToDevice();
			SetEvent(m_hEventParam);
		}
		break;
	}
	
	return 0;
}

void CDlgParamerConf::FUNPromoteMsgCB(int nMsg, int nParam, void* pUsr)
{	
	CDlgParamerConf* pThis = (CDlgParamerConf*)pUsr;
	pThis->DoPromoteMsgCB(nMsg, nParam);
}

void CDlgParamerConf::DoPromoteMsgCB(int wParam, int lParam)
{
	PostMessage(WM_MSG_PROMOTE, wParam, lParam);
}

void CDlgParamerConf::StopPromote()
{
	if (m_lPromoteHanle != NULL)
	{
		NETCLIENT_ULStopSetDevCfg(m_lPromoteHanle);
		NETCLIENT_ULCloseSetDevCfg(m_lPromoteHanle);
		m_lPromoteHanle = NULL;
	}
}

LRESULT CDlgParamerConf::OnMsgPromote(WPARAM wParam, LPARAM lParam)
{
	if (m_lPromoteHanle != NULL)
	{
		switch(wParam)
		{
		case GPS_UPLOAD_MSG_FAILED:	//下载配置失败
			{
				StopPromote();

				GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG));//"配置"
				
				m_pWnd = CWnd::FromHandle( m_hSheetWnd );
				if( m_pWnd != NULL )
				{
					m_pWnd->EnableWindow(TRUE);
				}
				
				EnableCtrl(TRUE);
			
				GetDlgItem(IDC_ST_READ_TIP)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_DOWN_FAILT));//下传配置参数文件失败!
				
				m_bGetParamSuc = FALSE;
				m_nGetParamResult = lParam;
				m_pDlgLoading->CloseLoading();
			}
			break;
		case GPS_UPLOAD_MSG_FINISHED:	//完成
			{
				StopPromote();

				SetDlgItemText(IDC_ST_READ_TIP, LOADSTRINGEX(ID_STR_DLG_PARAMER_DOWN_SUCC));//下传配置文件到设备成功!
				GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG));//"配置"
				
				m_pWnd = CWnd::FromHandle( m_hSheetWnd );
				if( m_pWnd != NULL )
				{
					m_pWnd->EnableWindow(TRUE);
				}
				
				EnableCtrl(TRUE);

				m_bGetParamSuc = TRUE;
				m_pDlgLoading->CloseLoading();
			}
			break;
		case GPS_UPLOAD_MSG_PROCESS:
			{
//				GetDlgItem(IDC_ST_READ_TIP)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_TIP_DOWN));//"正在下传配置文件,请稍等......"
			}
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
	
	return 0;
}

void CDlgParamerConf::StartDownLoadToDevice()
{
	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(m_nDevID);
	//NETCLIENT_ULOpenSetDevCfg(&m_lPromoteHanle,m_nDevID,m_nlpSvrID,m_szUploadDestFile);
	NETCLIENT_ULOpenSetDevCfg(&m_lPromoteHanle, pDev->GetIDNOForChar(),m_nlpSvrID,m_szUploadDestFile);
	NETCLIENT_ULSetSetDCfgMsgCB(m_lPromoteHanle, this, FUNPromoteMsgCB);
	NETCLIENT_ULStartSetDevCfg(m_lPromoteHanle);
}

void CDlgParamerConf::StartContinueDownLoadToDevice()
{
	//NETCLIENT_ULOpenSetDevCfg(&m_lPromoteHanle,m_nDevID,m_nlpSvrID,m_szUploadDestFile);

	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(m_nDevID);
// #if defined(_UNICODE) || defined(UNICODE)  
// 	USES_CONVERSION;
// 	NETCLIENT_ULOpenSetDevCfg(&m_lPromoteHanle,pDevice->GetIDNOForChar(),m_nlpSvrID, W2A(m_szUploadDestFile));
// #else
	NETCLIENT_ULOpenSetDevCfg(&m_lPromoteHanle, pDev->GetIDNOForChar(),m_nlpSvrID, m_szUploadDestFile);
//#endif
	NETCLIENT_ULSetSetDCfgMsgCB(m_lPromoteHanle, this, FUNPromoteMsgCB);
	NETCLIENT_ULStartSetDevCfg(m_lPromoteHanle);
}

void CDlgParamerConf::DoUploadMsgCB(int wParam, int lParam)
{
	PostMessage(WM_MSG_UPLOAD, wParam, lParam);
}

void CDlgParamerConf::EnableCtrl(BOOL bFlag)
{
	GetDlgItem(IDC_BUT_SAVE_MUT)->EnableWindow(bFlag);

	GetDlgItem(IDC_BUT_EXPORT)->EnableWindow(bFlag);
	GetDlgItem(IDC_BUT_IMPORT)->EnableWindow(bFlag);
}

//开始上传
void CDlgParamerConf::StartUpload()
{
	//if (m_pConfigEntity->IsLoadConfigFile())
	//{
	//	ShowDlgLoading(TRUE);
	//}
#if defined(_UNICODE) || defined(UNICODE)  
	NETCLIENT_ULOpenDevParamFileW(&m_lUploadHandle, m_szSaveFileName);
	//USES_CONVERSION;
	//NETCLIENT_ULOpenDevParamFile(&m_lUploadHandle, W2A(m_szSaveFileName));
#else
	NETCLIENT_ULOpenDevParamFile(&m_lUploadHandle, m_szSaveFileName);
#endif

	NETCLIENT_ULSetUploadMsgCB(m_lUploadHandle, this, FUNUploadMsgCB);
	NETCLIENT_ULStartUpload(m_lUploadHandle);	
}

//继续开始上传
void CDlgParamerConf::StartContinueUpload()
{
	NETCLIENT_ULOpenDevParamFile(&m_lUploadHandle, m_szSaveFileName);
	NETCLIENT_ULSetUploadMsgCB(m_lUploadHandle, this, FUNUploadMsgCB);
	NETCLIENT_ULStartUpload(m_lUploadHandle);	
}

//保存自身
void CDlgParamerConf::OnButSave() 
{
	if(m_lPromoteHanle != NULL) //下传参数时，停止
	{
		StopPromote();
		EnableCtrl(TRUE);
		GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG));//配置
		SetDlgItemText(IDC_ST_READ_TIP,LOADSTRINGEX(ID_STR_DLG_PARAMER_DOWN_STOP));//"下传配置停止!"
		m_bContinuePromote = TRUE;	
	}
	else  //准备配置参数时
	{
		if (m_lUploadHandle != NULL)//如果上传配置文件到服务器......此时停止
		{
			StopUpload();
			GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG));//配置
			EnableCtrl(TRUE);
			GetDlgItem(IDC_ST_READ_TIP)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_UP_STOP));//"停止上传配置文件!"
			m_bContinueUpload = TRUE;
		}

		else  //配置文件已经上传完成
		{			
			if (m_bContinuePromote)
			{
				GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_STOP_CONFIG));//停止配置
				StartContinueDownLoadToDevice();
				return;
			}

			if (m_bContinueUpload)//之前如果上传没上传完就停止上传，继续重新上传文件
			{
				//改变按钮上面的显示的字，为停止配置
				GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_STOP_CONFIG));//停止配置	
				EnableCtrl(FALSE);
				StartContinueUpload();			
			}
			else
			{	
				//if (!m_pConfigEntity->ActivePage())//当前页面数据不合法
				//{
				//	return;
				//}
				//
				//if (!m_pConfigEntity->SaveLocalCfgFile(m_szSaveFileName))
				//{
				//	MSG_BOX_ID(ID_STR_DLG_PARAMER_TIP);					
				//	return ;
				//}
				//else
				{
					StartUpload();
					//改变按钮上面的显示的字，为停止升级
					GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_STOP_CONFIG));////停止配置
					EnableCtrl(FALSE);
				}
			}
		}
    }

}

//保存到多个设备
void CDlgParamerConf::OnButSaveMut() 
{
	
}

void CDlgParamerConf::ParmerConfError()
{
	if (m_lParamerConfHandle != NULL)
	{		
		StopGetParmer();
		CloseDownFile();		
	}
	
	if (m_lUploadHandle != NULL)
	{		
		StopUpload();	
	}
	
	if (m_lPromoteHanle != NULL)
	{	
		StopPromote();	
	}
}

BOOL CDlgParamerConf::ExitPublic()
{
	if (m_lParamerConfHandle != NULL)
	{	
		if (IDOK == AfxMessageBox(_T("是否停止获取设备参数?"), MB_OKCANCEL)) //是否停止获取设备参数?
		{
			StopGetParmer();
			CloseDownFile();
			return TRUE;
		}
		else
			return FALSE;
	}
	
	if (m_lUploadHandle != NULL)
	{
		if (IDOK == AfxMessageBox(_T("是否停止上传配置文件到服务器?"), MB_OKCANCEL)) //是否停止上传配置文件到服务器？
		{
			StopUpload();
			return TRUE;
		}
		else
			return FALSE;	
	}
	
	if (m_lPromoteHanle != NULL)
	{
		if (IDOK == AfxMessageBox(_T("是否要停止下传配置文件到设备?"), MB_OKCANCEL)) //是否要停止下传配置文件到设备？
		{
			StopPromote();
			return TRUE;
		}
		else
			return FALSE;
	}
	
	TRY
	{
		if (_tcsclen(m_szFileName) > 0)
		{
			CFile::Remove(m_szFileName);
			memset(m_szFileName, 0, sizeof(m_szFileName));
		}
		if (_tcsclen(m_szFileName) > 0)
		{
			CFile::Remove(m_szSaveFileName);
			memset(m_szSaveFileName, 0, sizeof(m_szSaveFileName));
		}
	}
	CATCH( CFileException, e )
	{
#ifdef _DEBUG
        afxDump << "File " << m_szFileName << " cannot be removed\n";
#endif
	}
	END_CATCH

	return TRUE;
}

void CDlgParamerConf::OnCancel() 
{
	if (ExitPublic())
		CDialog::OnCancel();
	else
		return;	
}

void CDlgParamerConf::OnDestroy() 
{
	CDialog::OnDestroy();

	ExitPublic();
	DestroyDlg(m_pDlgLoading);
	SAFE_CLOSE_HANDLE(m_hEventParam);
	CloseGetParamHandle();

}

BOOL CDlgParamerConf::FUNTransparentConfig(int nType, MDVRConfigData_S* lpInConfig, MDVRConfigData_S* lpOutConfig, void* pUsr)
{
	CDlgParamerConf* pThis = (CDlgParamerConf*)pUsr;
	MDVRConfigDataEx_S InConfig = {0};
	MDVRConfigDataEx_S OutConfig = {0};
	memcpy(&InConfig, lpInConfig, sizeof(MDVRConfigData_S));
	memcpy(&OutConfig, lpOutConfig, sizeof(MDVRConfigData_S));

	//OutConfig.nLength = 2048;
	BOOL bRet = pThis->DoTransparentConfig(nType, &InConfig, &OutConfig);

	memcpy(lpOutConfig, &OutConfig, sizeof(MDVRConfigData_S));
	return bRet;
}

BOOL CALLBACK CDlgParamerConf::FUNTransparentConfigEx( int nType, MDVRConfigDataEx_S* lpInConfig, MDVRConfigDataEx_S* lpOutConfig, void* pUsr )
{
	CDlgParamerConf* pThis = (CDlgParamerConf*)pUsr;
	return pThis->DoTransparentConfig(nType, lpInConfig, lpOutConfig);
}

BOOL CDlgParamerConf::DoTransparentConfig( int nType, MDVRConfigDataEx_S* lpInConfig, MDVRConfigDataEx_S* lpOutConfig )
{
	if (m_bAueCoordinate)
	{
		CDlgDevList dlg;
		dlg.SetMultiSelect(FALSE);
		dlg.SetShowChan(FALSE);
		int nRet = dlg.DoModal();
		if (IDOK == nRet)
		{
			int nVehiID = dlg.GetSelectDevice();
			CDevBase* pDev = CVehicleBaseMgr::GetInstance()->FindDevByVehicleID(nVehiID);
			if (pDev)
			{
				m_nDevID = pDev->GetID();
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	static int nSearchCount = 0;
	nSearchCount++;
	int nSearch = nSearchCount;
	m_bGetParamSuc = FALSE;
	m_nGetParamResult = 101;
	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(m_nDevID);
	/*ResetEvent(m_hEventParam);*/
	if (m_lGetParamHandle)
	{
		NETCLIENT_MCReleaseHandle(m_lGetParamHandle);
		m_lGetParamHandle = 0;
	}
	int nErr;
// 	if (CMgrAppInfo::GetInstance()->GetAppInfo().cVersionChangeEx >= GPS_VERSION_EX_7_6_0_6 
// 		&& (lpInConfig->nLength >= 1024 || lpOutConfig->nLength >= 1024))
// 	{
// 		lpOutConfig->nLength = 0;
// 		m_bIsTransparenEx = TRUE;
// 		GPSConfigDataEx_S ConfigData = {0};
// 		memcpy(&ConfigData, lpInConfig, sizeof(MDVRConfigData_S));
// 		nErr = NETCLIENT_MCTransparentConfigEx(pDev->GetIDNOForChar(), nType, &ConfigData, this, FUNGetDevConfig, &m_lGetParamHandle);
// 	}
// 	else
	{
		m_bIsTransparenEx = FALSE;
		GPSConfigData_S ConfigData = {0};
		memcpy(&ConfigData, lpInConfig, sizeof(MDVRConfigData_S));
		nErr = NETCLIENT_MCTransparentConfig(pDev->GetIDNOForChar(), nType, &ConfigData, this, FUNGetDevConfig, &m_lGetParamHandle);
	}

	CDlgLoading dlgLoading;
	dlgLoading.SetThreadHandle(m_hEventParam, 20000);
	dlgLoading.DoModal();

	if (nErr == GPS_OK /*&& WAIT_OBJECT_0 == ::WaitForSingleObject(m_hEventParam, 10000)*/)
	{
		//m_pDlgLoading->DoModal();
		if (m_bGetParamSuc)
		{
			lpOutConfig->nLength = m_ConfigData.nLength;
			memcpy(lpOutConfig->cBuffer, m_ConfigData.cBuffer, lpOutConfig->nLength);
		}
		else
		{
			if(nSearch == nSearchCount)
				AfxMessageBox(_T("操作失败!"));
		}
	}
	else
	{
		if(nSearch == nSearchCount)
		{
			//if (nErr == GPS_ERR_DEV_NO_RESP && m_bIsTransparenEx)
			//{
			//	lpOutConfig->nLength = 0;
			//	DoTransparentConfig(nType, lpInConfig, lpOutConfig);
			//}
			//else
			{
				AfxMessageBox(_T("操作失败!"));
			}
		}
	}
	return m_bGetParamSuc;
}

BOOL CDlgParamerConf::FUNLoadConfigFile(BOOL bInput, const char* szCfgFile, void* pUsr)
{
	CDlgParamerConf* pThis = (CDlgParamerConf*)pUsr;
	return pThis->DoLoadConfigFile(bInput, szCfgFile);
}

BOOL CDlgParamerConf::DoLoadConfigFile(BOOL bInput, const char* szCfgFile)
{
	if (bInput)
	{
		memset(m_szSaveFileName, 0, sizeof(m_szSaveFileName));

		_tcscpy(m_szSaveFileName, CString(szCfgFile));
		StartUpload();
		//m_pDlgLoading->DoModal();
		CDlgLoading dlgLoading;
		dlgLoading.SetThreadHandle(m_hEventParam, 20000);
		dlgLoading.DoModal();
		if (!m_bGetParamSuc)
		{
			//AfxMessageBox(IDIRErrorString(m_nGetParamResult));
		}
		else
		{
			//MSG_BOX_ID(ID_STR_DLG_PARAMER_INPUT_SUC);
		}
	}
	else
	{
		memset(m_szExportCfgFile, 0, sizeof(m_szExportCfgFile));
		_tcscpy(m_szExportCfgFile, CString(szCfgFile));
		m_bGetParamSuc = FALSE;
		StartGetDevParamer();
		if (m_pFile)
		{
			CDlgLoading dlgLoading;
			dlgLoading.SetThreadHandle(m_hEventParam, 20000);
			dlgLoading.DoModal();
		}
		else
		{
			m_bGetParamSuc = FALSE;
			//MSG_BOX_ID(GPS_ERR_FILE_USED);
		}
		if (!m_bGetParamSuc)
		{
			AfxMessageBox(_T("Fail"));
			//AfxMessageBox(IDIRErrorString(m_nGetParamResult));
		}
		else
		{
			AfxMessageBox(_T("OK"));
			//MSG_BOX_ID(ID_STR_DLG_PARAMER_EXPORT_SUC);
		}
	}
	
	return m_bGetParamSuc;
}

void CDlgParamerConf::FUNGetDevConfig(GPSMCMsg_S* pMsg, void* pUsr)
{
	CDlgParamerConf* pThis = (CDlgParamerConf*)pUsr;
	pThis->DoGetDevConfig(pMsg);
}

void CDlgParamerConf::DoGetDevConfig(GPSMCMsg_S* pMsg)
{
	if (pMsg != NULL && m_lGetParamHandle != NULL)
	{
		if (GPS_OK == pMsg->nResult)
		{
			m_bGetParamSuc = TRUE;

			if (m_bIsTransparenEx)
			{
				m_ConfigData = *((GPSConfigDataEx_S*)pMsg->pParam[0]);
			}
			else
			{
				GPSConfigData_S* pData = (GPSConfigData_S*)pMsg->pParam[0];
				m_ConfigData.nLength = pData->nLength;
				memcpy(m_ConfigData.cBuffer, pData->cBuffer, _countof(pData->cBuffer));
			}
		}
		else
		{
			m_bGetParamSuc = FALSE;
			m_nGetParamResult = pMsg->nResult;
		}
	}

	NETCLIENT_MCReleaseMsg(pMsg);
	SetEvent(m_hEventParam);

	if (!PostMessage(WM_MSG_GET_PARAM, (WPARAM)pMsg))
	{
		//m_pDlgLoading->CloseLoading();
	}
}

LRESULT CDlgParamerConf::OnMsgGetParam(WPARAM wParam, LPARAM lParam)
{
// 	SetEvent(m_hEventParam);
	m_pDlgLoading->CloseLoading();
	return 0;
}


//关闭句柄
void CDlgParamerConf::CloseGetParamHandle()
{
	if (m_lGetParamHandle)
	{
		NETCLIENT_MCReleaseHandle(m_lGetParamHandle);
		m_lGetParamHandle = NULL;
	}
}

void CDlgParamerConf::FUNSetDevConfig(GPSMCMsg_S* pMsg, void* pUsr)
{
	CDlgParamerConf* pThis = (CDlgParamerConf*)pUsr;
	pThis->DoSetDevConfig(pMsg);
}

void CDlgParamerConf::DoSetDevConfig(GPSMCMsg_S* pMsg)
{
	if (!PostMessage(WM_MSG_SET_PARAM, (WPARAM)pMsg))
	{
		NETCLIENT_MCReleaseMsg(pMsg);
	}
}

//关闭句柄
void CDlgParamerConf::CloseSetParamHandle()
{
	if (m_lSetParamHandle)
	{
		NETCLIENT_MCReleaseHandle(m_lSetParamHandle);
		m_lSetParamHandle = NULL;
	}
}

LRESULT CDlgParamerConf::OnMsgSetParam(WPARAM wParam, LPARAM lParam)
{
	GPSMCMsg_S* pMsg =(GPSMCMsg_S*)wParam;
	if (pMsg != NULL && m_lSetParamHandle != NULL)
	{
		if (GPS_OK == pMsg->nResult)
		{
			m_bSetParamSuc = TRUE;
		}
		else
		{
			m_bSetParamSuc = FALSE;
			AfxMessageBox(_T("操作失败!"));
		}
		CloseSetParamHandle();
	}
	
	NETCLIENT_MCReleaseMsg(pMsg);
	m_pDlgLoading->CloseLoading();
	return 0;
}

LRESULT CDlgParamerConf::OnMsgShowDispaly(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_ST_PARAMER_MAIN)->GetSafeHwnd();
	if (m_bAueCoordinate)
	{
		CustomCreateDlg(m_pDlgAueCoordinateSetup, GetDlgItem(IDC_ST_PARAMER_MAIN), SW_SHOW);
	}
	return 0;
}

void CDlgParamerConf::ShowDlgLoading(BOOL bShow)
{
	m_pDlgLoading->SetShow(bShow);
}

void CDlgParamerConf::OnTimer(UINT nIDEvent) 
{
	
	if (TIMER_SHOW_DISPLAY == nIDEvent)
	{
		/*ShowDlgLoading(TRUE);*/
		KillTimer(TIMER_SHOW_DISPLAY);
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgParamerConf::SetAueFunction( BOOL bEnable, int nMapType, LPCTSTR lpszJingDu, LPCTSTR lpszWeiDu )
{
	m_bAueCoordinate = bEnable;
	g_nMapType = nMapType;
	g_strJingDu = lpszJingDu;
	g_strWeiDu = lpszWeiDu;
}


void CDlgParamerConf::OnBnClickedButtonAueWifi()
{
	m_pDlgAueWifiSetup->ShowWindow(SW_SHOW);
	m_pDlgAueCheckedSetup->ShowWindow(SW_HIDE);
	m_pDlgAueAlcoholSetup->ShowWindow(SW_HIDE);
}


void CDlgParamerConf::OnBnClickedButtonAueChecked()
{
	m_pDlgAueWifiSetup->ShowWindow(SW_HIDE);
	m_pDlgAueCheckedSetup->ShowWindow(SW_SHOW);
	m_pDlgAueAlcoholSetup->ShowWindow(SW_HIDE);
}


void CDlgParamerConf::OnBnClickedButtonAueAlcohol()
{
	m_pDlgAueWifiSetup->ShowWindow(SW_HIDE);
	m_pDlgAueCheckedSetup->ShowWindow(SW_HIDE);
	m_pDlgAueAlcoholSetup->ShowWindow(SW_SHOW);
}
