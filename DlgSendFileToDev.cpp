// DlgSendFileToDev.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgSendFileToDev.h"
#include "afxdialogex.h"
#include "CommonFun.h"

#define SEND_ALL_FILE		0	//所有类型
#define SEND_FILE_TYPE_PICTURE	1	//图片


// CDlgSendFileToDev 对话框
#define WM_MSG_UPLOAD	WM_USER + 0x1900
#define WM_MSG_PROMOTE	WM_USER + 0x1901
#define PROMOTE_COUNT   3

#define PROMTE_STATE_SUC   _T("SUCCESS")



IMPLEMENT_DYNAMIC(CDlgSendFileToDev, CDialog)

CDlgSendFileToDev::CDlgSendFileToDev(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSendFileToDev::IDD, pParent)
{
	m_strFilePath = _T("");
#ifdef VERSIONS_LIANTONG
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_LIANTONG);
#else
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
#endif
	//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strVersion = _T("");
	m_strDevType = _T("");
	//}}AFX_DATA_INIT
	memset(m_szUploadDestFile,0,sizeof(m_szUploadDestFile));
	m_nDevType = -1;
	m_lUploadHandle = NULL;
	m_lPromoteHanle = NULL;
	m_nCurRow = 0;
	m_nlpSvrID = -1;
	m_bContinuePromote = FALSE;
	m_bContinueUpload = FALSE;
	m_nCurRow = -1;
	m_lOldUploadHandle = NULL;

	m_nDevID = 0;
}

CDlgSendFileToDev::~CDlgSendFileToDev()
{
}

void CDlgSendFileToDev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_lstEquipPromote);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_strFilePath);
	DDX_Control(pDX, IDC_BTN_FILE_DOWN, m_btnFileDown);
	DDX_Control(pDX, IDOK, m_btnPromote);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_cmbFlieType);
}


BEGIN_MESSAGE_MAP(CDlgSendFileToDev, CDialog)
	ON_BN_CLICKED(IDC_BTN_FILE_DOWN, OnBtnFileDown)
	ON_BN_CLICKED(IDOK, OnBtnPromote)
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_UPLOAD, OnMsgUpload)
	ON_MESSAGE(WM_MSG_PROMOTE, OnMsgPromote)
END_MESSAGE_MAP()

// CDlgSendFileToDev 消息处理程序
void CDlgSendFileToDev::LoadLanguage()
{
	//SetWindowText(LOADSTRINGEX(ID_STR_DLG_SEND_FILE_TITLE));//设备升级--标题
	//SetDlgItemText(IDC_ST_FILE_NAME, LOADSTRINGEX(ID_STR_DLG_SEND_FILE_FILE));
	SetDlgItemText(IDC_BTN_FILE_DOWN,LOADSTRINGEX(ID_STR_DLG_PICPREVIEW_BTN_BROWSE));
	//SetDlgItemText(IDC_BT_DEL,LOADSTRINGEX(ID_STR_DLG_BCAST_BTN_DEL));
	//SetDlgItemText(IDC_BT_CLEAR,LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_CLEAR));
	SetDlgItemText(IDCANCEL,LOADSTRINGEX(ID_STR_EXIT));
	m_btnPromote.SetWindowText(_T("Send"));
	SetDlgItemText(IDC_STATIC_FILE_TYPE,LOADSTRINGEX(ID_STR_DLG_RECS_ST_FILE_TYPE));
	SetDlgItemText(IDC_STATIC_FILE_TYPE_TIP,LOADSTRINGEX(ID_STR_DLG_LOG_ARM_TIP_TITEL)
		+ _T("A image resolution is not more than 352 * 288."));
}

void CDlgSendFileToDev::OnCancel() 
{
	if (m_lUploadHandle != NULL)
	{
		if (IDOK == AfxMessageBox(_T("Stop Send File?"), MB_OKCANCEL))
		{
			StopUpload();
			CDialog::OnCancel();
		}
		else
			return;
	}
	if (m_lPromoteHanle != NULL)
	{
		if (IDOK == AfxMessageBox(_T("Stop Send File?"), MB_OKCANCEL))
		{
			StopPromote();
			CDialog::OnCancel();
		}
		else
			return;
	}
	else
		CDialog::OnCancel();

	m_bContinuePromote = FALSE;
	m_bContinueUpload = FALSE;
}

const int PROMOTE_COLUMN_DEV_NAME = 0;
//const int PROMOTE_COLUMN_DEV_TYPE = 1;
const int PROMOTE_COLUMN_DEV_PROMOTE = 1;
const int PROMOTE_COLUMN_DEV_STATE = 2;
const int PROMOTE_STATUS_COLUMN = 3;

void CDlgSendFileToDev::OnBtnFileDown() 
{
	m_strCurNote= _T("");
	m_strFilePath = _T("");
	UpdateData(FALSE);
	BOOL bIsChangeMap = FALSE;

	memset(&m_FileInfo,0,sizeof(GPSDEVUpgradeFile_S));
	int nType = m_cmbFlieType.GetItemData(m_cmbFlieType.GetCurSel());
	CString strText = TEXT("file (*.jpg;*.png;*.bmp)|*.jpg;*.png;*.bmp|All file(*.*)|*.*||");
	if (nType == SEND_FILE_TYPE_PICTURE)
	{
		strText = TEXT("file (*.jpg;*.png;*.bmp)|*.jpg;*.png;*.bmp||");
	}
	else if (nType == SEND_ALL_FILE)
	{
		strText = TEXT("All file(*.*)|*.*||");
	}
	CFileDialog hFileDlg(true,NULL ,
		NULL,
		OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST,
		strText,
		NULL);
	if(hFileDlg.DoModal() == IDOK)
	{
		m_strFilePath = hFileDlg.GetPathName();
		UpdateData(FALSE);
		for (int i=0;i<m_lstEquipPromote.GetItemCount();i++)
		{
			m_lstEquipPromote.SetItemText(i,PROMOTE_COLUMN_DEV_PROMOTE,_T(""));
			m_lstEquipPromote.SetItemText(i,PROMOTE_COLUMN_DEV_STATE, _T("no Send"));
			m_lstEquipPromote.SetItemText(i,PROMOTE_STATUS_COLUMN, _T("no Send"));
		}
	}
}

//#define SEND_FILE_TYPE_UPGRADE	1	//升级文件
BOOL CDlgSendFileToDev::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LoadLanguage();

	int nIndex = 0;
	m_cmbFlieType.InsertString(nIndex, _T("Face Image"));
	m_cmbFlieType.SetItemData(nIndex++, SEND_FILE_TYPE_PICTURE);
	m_cmbFlieType.InsertString(nIndex, _T("Fingerprint Image"));
	m_cmbFlieType.SetItemData(nIndex++, SEND_FILE_TYPE_PICTURE);
	m_cmbFlieType.InsertString(nIndex, _T("All File"));
	m_cmbFlieType.SetItemData(nIndex++, SEND_ALL_FILE);
	m_cmbFlieType.SetCurSel(0);
	


	//ListCtrolEx 控件的初始化
	DWORD styles = m_lstEquipPromote.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_lstEquipPromote.SetExtendedStyle(styles);

	m_lstEquipPromote.InsertColumn(PROMOTE_COLUMN_DEV_NAME,LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_DEV_NAME),LVCFMT_LEFT,90,0);
	m_lstEquipPromote.InsertColumn(PROMOTE_COLUMN_DEV_PROMOTE, _T("process"),LVCFMT_LEFT,70,0);
	CRect rc;
	m_lstEquipPromote.GetClientRect(&rc);
	m_lstEquipPromote.InsertColumn(PROMOTE_COLUMN_DEV_STATE,LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_STATE),LVCFMT_LEFT,rc.Width()-90-70,0);
	m_lstEquipPromote.InsertColumn(PROMOTE_STATUS_COLUMN,_T(""),LVCFMT_LEFT,0,0);
	m_lstEquipPromote.InsertColumn(4,_T(""),LVCFMT_LEFT,0,0);
	m_lstEquipPromote.InsertColumn(5,_T(""),LVCFMT_LEFT,0,0);


	if (m_nDevID)
	{
		InsertDevItem(m_nDevID);
	}
	return TRUE; 
}

void CDlgSendFileToDev::OnDropDevNode(int nType, int nID)
{
	CWaitCursor wait;
	if (DEVNODE_TYPE_ROOT == nType)
	{
		//AddRootNode();
	}
	else if (DEVNODE_TYPE_GROUP == nType)
	{	
		//AddGroupNode(nID);
	}
	else if (DEVNODE_TYPE_DEV == nType)
	{
		InsertDevItem(nID);
	}
	else
	{
		//ASSERT(FALSE);
	}
}

void CDlgSendFileToDev::AddRootNode()
{
}

void CDlgSendFileToDev::AddGroupNode(int nGroupID)
{
}

BOOL CDlgSendFileToDev::FindDeviceItem(int nDevID)
{
	for (int index = 0; index < m_lstEquipPromote.GetItemCount(); index++)
	{
		int nID = m_lstEquipPromote.GetItemData(index);
		if (nDevID == nID)
		{
			return TRUE;
		}
	}
	return FALSE;
}

//设备id
void CDlgSendFileToDev::InsertDevItem(int nDevID)
{

	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);
	CVehicleBase* pVehicle = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByID(nDevID);
	if (pDev && pVehicle)
	{
		int nIndex = m_lstEquipPromote.GetItemCount();
		if (FindDeviceItem(nDevID))
		{
			return;
		}
	//	if (pDevice->GetOnline() && pDevice->IsMoblieType() == FALSE)
		{
			CString strName = pVehicle->GetShowName();
			m_lstEquipPromote.InsertItem(nIndex, strName);
			m_lstEquipPromote.SetItemText(nIndex, PROMOTE_COLUMN_DEV_PROMOTE, _T(""));
			m_lstEquipPromote.SetItemText(nIndex, PROMOTE_COLUMN_DEV_STATE, _T("no Send"));
			m_lstEquipPromote.SetItemData(nIndex, nDevID);
		}
	}
}

// void CDlgSendFileToDev::AddDevList( LongVehicleBase* pVehicle, int nCount )
// {
// 	for (int i=0; i<nCount; i++)
// 	{
// 		LongVehicleBase lVehicle = pVehicle[i];
// 		//找所有车辆设备
// 		LongDevBase* pDev = NULL;
// 		int nCount = 0;
// 		COMMONVEHICLE_GetDevList(lVehicle, &pDev, nCount);
// 		for (int i=0; i<nCount; i++)
// 		{
// 			LongDevBase lDev = pDev[i];
// 			if (lDev)
// 			{
// 				InsertDevItem(COMMONDEV_GetDevInt(lDev, E_DEV_INT_GetID));						
// 			}
// 		}
// 		LIBCOMMON_Release(pDev);
// 	}
// }

void CDlgSendFileToDev::OnDestroy() 
{
	CDialog::OnDestroy();

	StopUpload();
	StopPromote();
}

HCURSOR CDlgSendFileToDev::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDlgSendFileToDev::FUNUploadMsgCB(int nMsg, int nParam, void* pUsr)
{
	CDlgSendFileToDev* pThis = (CDlgSendFileToDev*)pUsr;
	pThis->DoUploadMsgCB(nMsg, nParam);
}

void CDlgSendFileToDev::DoUploadMsgCB(int wParam, int lParam)
{
	PostMessage(WM_MSG_UPLOAD, wParam, lParam);
}

void CDlgSendFileToDev::StopPromote()
{
	if (m_lPromoteHanle != NULL)
	{
		NETCLIENT_DUStopDevUploadFile(m_lPromoteHanle);
		NETCLIENT_DUCloseDevUploadFile(m_lPromoteHanle);
		m_lPromoteHanle = NULL;
	}
}

void CDlgSendFileToDev::StopUpload()
{
	if (m_lUploadHandle != NULL)
	{
		NETCLIENT_ULStopUpload(m_lUploadHandle);
		NETCLIENT_ULCloseUpload(m_lUploadHandle);
		m_lUploadHandle = NULL;
		//将按钮上的字改成升级
	}
}

void CDlgSendFileToDev::SetUploadProcess(int nProcess)
{
	static DWORD dwTime = 0;
	if (nProcess == 100 || TIMEIsTimeOut(dwTime, 50))
	{
		dwTime = GetTickCount();
		CString strTemp;
		strTemp.Format(_T("%2d%%"), nProcess);
		SetUploadProcessTip(strTemp);
	}
}

void CDlgSendFileToDev::SetUploadProcessTip( LPCTSTR lpszTip )
{
	CString strTemp;
	strTemp.Format(_T("%s%s"), _T("Process:"), lpszTip);
	SetDlgItemText(IDC_STATIC_UPLOAD_FILE, strTemp);
}

LRESULT CDlgSendFileToDev::OnMsgUpload(WPARAM wParam, LPARAM lParam)
{
	if (m_lUploadHandle != NULL)
	{
		switch(wParam)
		{
		case GPS_UPLOAD_MSG_FAILED:	//上传升级文件失败
			{
				//lParam为失败原因
				StopUpload();

				SetUploadProcessTip(_T("Upload File Fail"));
				SetCtrlEnable(TRUE);
				m_btnPromote.SetWindowText(_T("Send"));
				return -1;
			}
			break;
		case GPS_UPLOAD_MSG_FINISHED:	//上传升级文件完成
			{
				SetUploadProcess(100);
				//				m_strLoadFileNote=LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_NOTE_SUCC);//升级文件上传状态:上传升级文件到服务器成功!

				m_btnPromote.SetWindowText(LOADSTRINGEX(ID_STR_DLG_VOIP_DEV_STOP));
				//				GetDlgItem(IDC_STATIC_UPLOAD_FILE)->SetWindowText(m_strLoadFileNote);
				//开始升级设备
				m_bUploadSuc = TRUE;
				m_bContinueUpload = FALSE;
				char szUploadDestFile[MAX_PATH] = {0};
				NETCLIENT_ULGetDestFileName(m_lUploadHandle,&m_nlpSvrID, szUploadDestFile);
				_tcsncpy(m_szUploadDestFile, CString(szUploadDestFile), sizeof(m_szUploadDestFile)/sizeof(TCHAR)-1);

				StopUpload();
				m_nCurRow = -1;
				PromoteNextDevice();
			}
			break;
		case GPS_UPLOAD_MSG_PROCESS:
			{
				SetUploadProcess(lParam);
			}
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}	
	return 0;
}
BOOL CDlgSendFileToDev::CheckFilePic()
{
	BOOL bRet = FALSE;
	CImgBase* pImg = CImgBase::SCreateImage();
	if (pImg)
	{
		if(pImg->LoadFile(m_strFilePath))
		{
			if (pImg->GetHeight() > 0 && pImg->GetWidth() > 0
				&& pImg->GetHeight() <= 288 && pImg->GetWidth() <= 352)
			{
				bRet = TRUE;
			}
			else
			{
				AfxMessageBox(_T("Image Err!352*288."));
			}
		}
		else
		{
			AfxMessageBox(_T("Image Err."));
		}
		SAFE_DELETE_OBJECT(pImg);
	}
	return bRet;
}
BOOL CDlgSendFileToDev::CheckFile()
{
	BOOL bRet = FALSE;
	int nCurSel = m_cmbFlieType.GetCurSel();
	if (nCurSel != CB_ERR)
	{
		if (m_cmbFlieType.GetItemData(nCurSel) == SEND_FILE_TYPE_PICTURE)
		{
			bRet = CheckFilePic();
		}
		else if (m_cmbFlieType.GetItemData(nCurSel) == SEND_ALL_FILE)
		{
			bRet = TRUE;
		}
	}
	else
	{
		AfxMessageBox(_T("Please Select File Type."));
	}
	return bRet;
}
void CDlgSendFileToDev::OnBtnPromote() 
{
	//检查文件是否合法
	if(CheckFile() == FALSE)
	{
		//AfxMessageBox(_T("File error"));
		return;
	}
	//初始化所有未升级成功的车辆
	for (int nCurRow=0;nCurRow<m_lstEquipPromote.GetItemCount();nCurRow++)
	{
		CString strState = m_lstEquipPromote.GetItemText(nCurRow, PROMOTE_STATUS_COLUMN);
		if (strState != PROMTE_STATE_SUC)
		{
			m_lstEquipPromote.SetItemText(nCurRow, PROMOTE_COLUMN_DEV_PROMOTE, _T(""));
			m_lstEquipPromote.SetItemText(nCurRow, PROMOTE_COLUMN_DEV_STATE, _T("no Send"));			
		}
	}
	if (m_lPromoteHanle != NULL) //正在升级设备时，需要停止？
	{
		if (IDOK == AfxMessageBox(_T("Stop Send File?"), MB_OKCANCEL))
		{
			StopPromote();
			m_btnPromote.SetWindowText(_T("Send"));
			SetCtrlEnable(TRUE);
			m_bContinuePromote = TRUE;

			m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,LOADSTRINGEX(ID_STR_DLG_VOIP_DEV_STOP));//停止设备升级时，当前行填充“停止升级”
		}
	}
	else//准备升级设备
	{
		if (m_lUploadHandle != NULL)//如果升级文件正在升级......
		{
			//文件升级中
			StopUpload();
			m_btnPromote.SetWindowText(_T("Send"));
			SetCtrlEnable(TRUE);
			SetUploadProcessTip(_T("File Stop Upload"));//停止上传升级文件
			m_bContinueUpload = TRUE;
		}
		else  //升级文件已经升级完成
		{			
			if (m_bContinuePromote)
			{  
				m_nCurRow = -1;
				m_btnPromote.SetWindowText(LOADSTRINGEX(ID_STR_DLG_VOIP_DEV_STOP));
				PromoteContinueNext();
				return;
			}

			if (m_bContinueUpload)//之前如果上传没上传完就停止上传，继续重新上传升级文件
			{
				//改变按钮上面的显示的字，为停止升级
				m_btnPromote.SetWindowText(LOADSTRINGEX(ID_STR_DLG_VOIP_DEV_STOP));
				SetCtrlEnable(FALSE);

				GetDlgItem(IDC_STATIC_UPLOAD_FILE)->SetWindowText(_T(""));
				NETCLIENT_ULOpenDevParamFile(&m_lUploadHandle, m_strFilePath);

				NETCLIENT_ULSetUploadMsgCB(m_lUploadHandle, this, FUNUploadMsgCB);
				NETCLIENT_ULStartUpload(m_lUploadHandle);	
			}
			else
			{
				if (m_strFilePath.IsEmpty())
				{
					//提示用户选择升级文件
					AfxMessageBox(_T("Please Select File!"));
					return ;
				}

				if (m_lstEquipPromote.GetItemCount() <= 0)
				{
					//提示用户选择升级设备
					AfxMessageBox(_T("Please Select Device!"));
					return ;
				}

				CString strTemp ;
				GetDlgItem(IDOK)->GetWindowText(strTemp);
				if (strTemp == LOADSTRINGEX(ID_STR_DLG_DEV_STOP))
				{
					m_btnPromote.SetWindowText(_T("Send"));
					SetCtrlEnable(TRUE);
					return;
				}


				if (CSvrVer::GetInstance()->IsSvrVerV7())
				{
					GPSDEVUpgradeFile_S FileInfo = {0};
					NETCLIENT_GetDevUpgradeFileInfo(m_strFilePath, &FileInfo);
					NETCLIENT_ULOpenDevUpgradeFile(&m_lUploadHandle, &FileInfo, m_strFilePath);
				}
				else
				{
					NETCLIENT_ULOpenDevParamFile(&m_lUploadHandle, m_strFilePath);
				}
				//USES_CONVERSION;	
				//NETCLIENT_ULOpenDevParamFile(&m_lUploadHandle, W2A(m_strFilePath));
			//	NETCLIENT_ULOpenFile2SvrMD5(&m_lUploadHandle, W2A(m_strFilePath), m_cmbFlieType.GetCurSel());
				//NETCLIENT_ULOpenDevParamFile(&m_lUploadHandle, m_strFilePath);
				NETCLIENT_ULSetUploadMsgCB(m_lUploadHandle, this, FUNUploadMsgCB);
				NETCLIENT_ULStartUpload(m_lUploadHandle);
				//改变按钮上面的显示的字，为停止升级
				m_btnPromote.SetWindowText(LOADSTRINGEX(ID_STR_DLG_VOIP_DEV_STOP));
				SetCtrlEnable(FALSE);
				m_lOldUploadHandle = m_lUploadHandle;
			}
		}		
	}
}

void CDlgSendFileToDev::StartContinuePromote()
{
	SetCtrlEnable(FALSE);
	int nDevID = m_lstEquipPromote.GetItemData(m_nCurRow);  
	int nFileType = m_cmbFlieType.GetItemData(m_cmbFlieType.GetCurSel());

	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);
	NETCLIENT_DUOpenDevUploadFile(&m_lPromoteHanle, pDev->GetDevIDNOForChar(),
		nFileType, NULL, m_nlpSvrID,CStringA(m_szUploadDestFile));

	m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,_T("Sending"));//准备升级
	NETCLIENT_DUSetDevUploadFileMsgCB(m_lPromoteHanle, this, FUNPromoteMsgCB);
	NETCLIENT_DUStartDevUploadFile(m_lPromoteHanle);
}

void CDlgSendFileToDev::StartPromote()
{
	SetCtrlEnable(FALSE);

	int nDevID = m_lstEquipPromote.GetItemData(m_nCurRow); 
	int nFileType = m_cmbFlieType.GetItemData(m_cmbFlieType.GetCurSel());
	m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,_T("Sending"));//准备升级

	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);

	NETCLIENT_DUOpenDevUploadFile(&m_lPromoteHanle, pDev->GetDevIDNOForChar(),nFileType,NULL, m_nlpSvrID,CStringA(m_szUploadDestFile));

	m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,_T("Sending"));//准备升级
	NETCLIENT_DUSetDevUploadFileMsgCB(m_lPromoteHanle, this, FUNPromoteMsgCB);
	NETCLIENT_DUStartDevUploadFile(m_lPromoteHanle);
}

void CDlgSendFileToDev::FUNPromoteMsgCB(int nMsg, int nParam, void* pUsr)
{	
	CDlgSendFileToDev* pThis = (CDlgSendFileToDev*)pUsr;
	pThis->DoPromoteMsgCB(nMsg, nParam);
}

void CDlgSendFileToDev::DoPromoteMsgCB(int wParam, int lParam)
{
	PostMessage(WM_MSG_PROMOTE, wParam, lParam);
}

//停止后继续升级
void CDlgSendFileToDev::PromoteContinueNext()
{
	int nListCount = m_lstEquipPromote.GetItemCount()-1;
	++m_nCurRow;
	//如果升级设备已经完成，则停止升级
	if (nListCount < m_nCurRow)
	{
		//if (theApp.m_pMainWnd->IsIconic())
		//{
		//	theApp.m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
		//}

		if (this->IsIconic())
		{
			this->ShowWindow(SW_NORMAL);
		}

		SetCtrlEnable(TRUE);
		StopPromote();
		//提示升级完成;
		m_btnPromote.SetWindowText(_T("Send"));
		SetCtrlEnable(TRUE);
		
		AfxMessageBox(_T("Send OK"));		
		m_bContinuePromote = FALSE;
		return; //升级设备数量到达，返回
	}

	CString strState = m_lstEquipPromote.GetItemText(m_nCurRow, PROMOTE_STATUS_COLUMN);
	if (strState != PROMTE_STATE_SUC)
	{
		//判断车辆是否在线
		int nDevID = m_lstEquipPromote.GetItemData(m_nCurRow); 
		CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);
		BOOL bOnline = pDev ? pDev->GetOnline() : FALSE;
		if(!bOnline)
		{
			m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,LOADSTRINGEX(ID_STR_MODIFY_DEV_DIS_ONLINE));
			PromoteContinueNext();			
		}
		else
			StartContinuePromote();
	}
	else
		PromoteContinueNext();
}

void CDlgSendFileToDev::PromoteNextDevice()
{	
	int nListCount = m_lstEquipPromote.GetItemCount()-1;
	++m_nCurRow;
	//如果升级设备已经完成，则停止升级
	if (nListCount < m_nCurRow)
	{		
// 		if (theApp.m_pMainWnd->IsIconic())
// 		{
// 			theApp.m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
// 		}

		if (this->IsIconic())
		{
			this->ShowWindow(SW_NORMAL);
		}

		StopPromote();
		//提示升级完成;
		m_btnPromote.SetWindowText(_T("Send"));
		SetCtrlEnable(TRUE);
		AfxMessageBox(_T("Send OK"));
		return; //升级设备数量到达，返回
	}

	CString strState = m_lstEquipPromote.GetItemText(m_nCurRow, PROMOTE_STATUS_COLUMN);
	if (strState != PROMTE_STATE_SUC)
	{
		//判断车辆是否在线
		int nDevID = m_lstEquipPromote.GetItemData(m_nCurRow); 
		CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);
		BOOL bOnline = pDev ? pDev->GetOnline() : FALSE;
		if(!bOnline)
		{
			m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,LOADSTRINGEX(ID_STR_MODIFY_DEV_DIS_ONLINE));
			PromoteNextDevice();			
		}
		else
			StartPromote();
	}
	else
		PromoteNextDevice();
}

LRESULT CDlgSendFileToDev::OnMsgPromote(WPARAM wParam, LPARAM lParam)
{
	if (m_lPromoteHanle != NULL)
	{
		switch(wParam)
		{
		case GPS_UPLOAD_MSG_FAILED:	//设备升级失败
			{
				StopPromote();

				if (lParam == GPS_ERR_NORIGHT)
				{
					SetCtrlEnable(TRUE);
					m_btnPromote.SetWindowText(_T("Send"));
					AfxMessageBox(_T("Send Fail！"));					
					return -1;
				}

				// 				if(lParam == GPS_ERR_DEV_UP_UPGRADING)
				// 				{
				// 					CString str =LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_FAR_END);
				// 				    m_lstEquipPromote.SetItemText(m_nCurRow,3,str);
				// 				}
				else
				{
					m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE, _T("失败"));
				}

				PromoteNextDevice();
			}
			break;
		case GPS_UPLOAD_MSG_FINISHED:	//设备升级完成
			{				
				m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_PROMOTE,_T("100%"));
				//m_lstEquipPromote.SetItemText(m_nCurRow,3,LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_SUCC));
				m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE, _T("Upload File OK"));
				m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_STATUS_COLUMN,PROMTE_STATE_SUC);
				//CString m_strLoadFileNote = _T("");
				//m_strLoadFileNote=LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_NOTE_SUCC);//升级文件上传状态:上传升级文件到服务器成功!
				//GetDlgItem(IDC_STATIC_UPLOAD_FILE)->SetWindowText(m_strLoadFileNote);
				if (m_bContinuePromote)//继续下载
				{
					PromoteContinueNext();
				}
				else
				{
					PromoteNextDevice();
				}
			}
			break;
		case GPS_UPLOAD_MSG_PROCESS:
			{
				CString strPro;
				strPro.Format(_T("%d"),lParam);
				strPro+="%";
				m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_PROMOTE,strPro);
				m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,LOADSTRINGEX(ID_STR_DLG_DEV_UP_FILE));
			}
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}

	return 0;
}

void CDlgSendFileToDev::SetCtrlEnable(BOOL bFlag)
{
	GetDlgItem(IDC_BTN_FILE_DOWN)->EnableWindow(bFlag);
	// 	GetDlgItem(IDC_BT_DEL)->EnableWindow(bFlag);
	// 	GetDlgItem(IDC_BT_CLEAR)->EnableWindow(bFlag);
}

void CDlgSendFileToDev::SetDevID( int nDevID )
{
	m_nDevID = nDevID;
}
