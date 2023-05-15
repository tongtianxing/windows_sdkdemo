// DlgSendFileToDev.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgSendFileToDev.h"
#include "afxdialogex.h"
#include "CommonFun.h"

#define SEND_ALL_FILE		0	//��������
#define SEND_FILE_TYPE_PICTURE	1	//ͼƬ


// CDlgSendFileToDev �Ի���
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

// CDlgSendFileToDev ��Ϣ�������
void CDlgSendFileToDev::LoadLanguage()
{
	//SetWindowText(LOADSTRINGEX(ID_STR_DLG_SEND_FILE_TITLE));//�豸����--����
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
	int nType = (int)m_cmbFlieType.GetItemData(m_cmbFlieType.GetCurSel());
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

//#define SEND_FILE_TYPE_UPGRADE	1	//�����ļ�
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
	


	//ListCtrolEx �ؼ��ĳ�ʼ��
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
		int nID = (int)m_lstEquipPromote.GetItemData(index);
		if (nDevID == nID)
		{
			return TRUE;
		}
	}
	return FALSE;
}

//�豸id
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
// 		//�����г����豸
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
		//����ť�ϵ��ָĳ�����
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
		case GPS_UPLOAD_MSG_FAILED:	//�ϴ������ļ�ʧ��
			{
				//lParamΪʧ��ԭ��
				StopUpload();

				SetUploadProcessTip(_T("Upload File Fail"));
				SetCtrlEnable(TRUE);
				m_btnPromote.SetWindowText(_T("Send"));
				return -1;
			}
			break;
		case GPS_UPLOAD_MSG_FINISHED:	//�ϴ������ļ����
			{
				SetUploadProcess(100);
				//				m_strLoadFileNote=LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_NOTE_SUCC);//�����ļ��ϴ�״̬:�ϴ������ļ����������ɹ�!

				m_btnPromote.SetWindowText(LOADSTRINGEX(ID_STR_DLG_VOIP_DEV_STOP));
				//				GetDlgItem(IDC_STATIC_UPLOAD_FILE)->SetWindowText(m_strLoadFileNote);
				//��ʼ�����豸
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
				SetUploadProcess((int)lParam);
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
		CImgBase::SDeleteImage(pImg);
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
	//����ļ��Ƿ�Ϸ�
	if(CheckFile() == FALSE)
	{
		//AfxMessageBox(_T("File error"));
		return;
	}
	//��ʼ������δ�����ɹ��ĳ���
	for (int nCurRow=0;nCurRow<m_lstEquipPromote.GetItemCount();nCurRow++)
	{
		CString strState = m_lstEquipPromote.GetItemText(nCurRow, PROMOTE_STATUS_COLUMN);
		if (strState != PROMTE_STATE_SUC)
		{
			m_lstEquipPromote.SetItemText(nCurRow, PROMOTE_COLUMN_DEV_PROMOTE, _T(""));
			m_lstEquipPromote.SetItemText(nCurRow, PROMOTE_COLUMN_DEV_STATE, _T("no Send"));			
		}
	}
	if (m_lPromoteHanle != NULL) //���������豸ʱ����Ҫֹͣ��
	{
		if (IDOK == AfxMessageBox(_T("Stop Send File?"), MB_OKCANCEL))
		{
			StopPromote();
			m_btnPromote.SetWindowText(_T("Send"));
			SetCtrlEnable(TRUE);
			m_bContinuePromote = TRUE;

			m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,LOADSTRINGEX(ID_STR_DLG_VOIP_DEV_STOP));//ֹͣ�豸����ʱ����ǰ����䡰ֹͣ������
		}
	}
	else//׼�������豸
	{
		if (m_lUploadHandle != NULL)//��������ļ���������......
		{
			//�ļ�������
			StopUpload();
			m_btnPromote.SetWindowText(_T("Send"));
			SetCtrlEnable(TRUE);
			SetUploadProcessTip(_T("File Stop Upload"));//ֹͣ�ϴ������ļ�
			m_bContinueUpload = TRUE;
		}
		else  //�����ļ��Ѿ��������
		{			
			if (m_bContinuePromote)
			{  
				m_nCurRow = -1;
				m_btnPromote.SetWindowText(LOADSTRINGEX(ID_STR_DLG_VOIP_DEV_STOP));
				PromoteContinueNext();
				return;
			}

			if (m_bContinueUpload)//֮ǰ����ϴ�û�ϴ����ֹͣ�ϴ������������ϴ������ļ�
			{
				//�ı䰴ť�������ʾ���֣�Ϊֹͣ����
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
					//��ʾ�û�ѡ�������ļ�
					AfxMessageBox(_T("Please Select File!"));
					return ;
				}

				if (m_lstEquipPromote.GetItemCount() <= 0)
				{
					//��ʾ�û�ѡ�������豸
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
				//�ı䰴ť�������ʾ���֣�Ϊֹͣ����
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
	int nDevID = (int)m_lstEquipPromote.GetItemData(m_nCurRow);
	int nFileType = (int)m_cmbFlieType.GetItemData(m_cmbFlieType.GetCurSel());

	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);
	NETCLIENT_DUOpenDevUploadFile(&m_lPromoteHanle, pDev->GetDevIDNOForChar(),
		nFileType, NULL, m_nlpSvrID,CStringA(m_szUploadDestFile));

	m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,_T("Sending"));//׼������
	NETCLIENT_DUSetDevUploadFileMsgCB(m_lPromoteHanle, this, FUNPromoteMsgCB);
	NETCLIENT_DUStartDevUploadFile(m_lPromoteHanle);
}

void CDlgSendFileToDev::StartPromote()
{
	SetCtrlEnable(FALSE);

	int nDevID = (int)m_lstEquipPromote.GetItemData(m_nCurRow);
	int nFileType = (int)m_cmbFlieType.GetItemData(m_cmbFlieType.GetCurSel());
	m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,_T("Sending"));//׼������

	CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);

	NETCLIENT_DUOpenDevUploadFile(&m_lPromoteHanle, pDev->GetDevIDNOForChar(),nFileType,NULL, m_nlpSvrID,CStringA(m_szUploadDestFile));

	m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE,_T("Sending"));//׼������
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

//ֹͣ���������
void CDlgSendFileToDev::PromoteContinueNext()
{
	int nListCount = m_lstEquipPromote.GetItemCount()-1;
	++m_nCurRow;
	//��������豸�Ѿ���ɣ���ֹͣ����
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
		//��ʾ�������;
		m_btnPromote.SetWindowText(_T("Send"));
		SetCtrlEnable(TRUE);
		
		AfxMessageBox(_T("Send OK"));		
		m_bContinuePromote = FALSE;
		return; //�����豸�����������
	}

	CString strState = m_lstEquipPromote.GetItemText(m_nCurRow, PROMOTE_STATUS_COLUMN);
	if (strState != PROMTE_STATE_SUC)
	{
		//�жϳ����Ƿ�����
		int nDevID = (int)m_lstEquipPromote.GetItemData(m_nCurRow);
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
	//��������豸�Ѿ���ɣ���ֹͣ����
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
		//��ʾ�������;
		m_btnPromote.SetWindowText(_T("Send"));
		SetCtrlEnable(TRUE);
		AfxMessageBox(_T("Send OK"));
		return; //�����豸�����������
	}

	CString strState = m_lstEquipPromote.GetItemText(m_nCurRow, PROMOTE_STATUS_COLUMN);
	if (strState != PROMTE_STATE_SUC)
	{
		//�жϳ����Ƿ�����
		int nDevID = (int)m_lstEquipPromote.GetItemData(m_nCurRow);
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
		case GPS_UPLOAD_MSG_FAILED:	//�豸����ʧ��
			{
				StopPromote();

				if (lParam == GPS_ERR_NORIGHT)
				{
					SetCtrlEnable(TRUE);
					m_btnPromote.SetWindowText(_T("Send"));
					AfxMessageBox(_T("Send Fail��"));					
					return -1;
				}

				// 				if(lParam == GPS_ERR_DEV_UP_UPGRADING)
				// 				{
				// 					CString str =LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_FAR_END);
				// 				    m_lstEquipPromote.SetItemText(m_nCurRow,3,str);
				// 				}
				else
				{
					m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE, _T("ʧ��"));
				}

				PromoteNextDevice();
			}
			break;
		case GPS_UPLOAD_MSG_FINISHED:	//�豸�������
			{				
				m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_PROMOTE,_T("100%"));
				//m_lstEquipPromote.SetItemText(m_nCurRow,3,LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_SUCC));
				m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_COLUMN_DEV_STATE, _T("Upload File OK"));
				m_lstEquipPromote.SetItemText(m_nCurRow,PROMOTE_STATUS_COLUMN,PROMTE_STATE_SUC);
				//CString m_strLoadFileNote = _T("");
				//m_strLoadFileNote=LOADSTRINGEX(ID_STR_DLG_DEV_PROMOTE_NOTE_SUCC);//�����ļ��ϴ�״̬:�ϴ������ļ����������ɹ�!
				//GetDlgItem(IDC_STATIC_UPLOAD_FILE)->SetWindowText(m_strLoadFileNote);
				if (m_bContinuePromote)//��������
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
