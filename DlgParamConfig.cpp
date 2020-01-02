// DlgParamConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgParamConfig.h"
#include "afxdialogex.h"


// CDlgParamConfig 对话框
#define WM_MSG_PARAM_GET_MSG		WM_USER + 0x100
#define WM_MSG_PARAM_UPLOAD_MSG		WM_USER + 0x101
#define WM_MSG_PARAM_PROMOTE_MSG	WM_USER + 0x102

IMPLEMENT_DYNAMIC(CDlgParamConfig, CDialog)

CDlgParamConfig::CDlgParamConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParamConfig::IDD, pParent)
{
	m_nDevID = 0;

	m_lGetParamHandle = NULL;
	m_pFile = NULL;

	m_lUploadHandle = NULL;
	m_nlpSvrID = 0;

	m_lPromoteHanle = NULL;
	memset(m_szSvrFile, 0, sizeof(m_szSvrFile));
}

CDlgParamConfig::~CDlgParamConfig()
{
}

void CDlgParamConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgParamConfig, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_PARAM_FILE_GET, &CDlgParamConfig::OnBnClickedBtnParamFileGet)
	ON_MESSAGE(WM_MSG_PARAM_GET_MSG, OnMsgParamGetMsg)
	ON_BN_CLICKED(IDC_BTN_PARAM_FILE_UPDATE, &CDlgParamConfig::OnBnClickedBtnParamFileUpdate)
	ON_BN_CLICKED(IDC_BTN_PARAM_FILE_SET, &CDlgParamConfig::OnBnClickedBtnParamFileSet)
	ON_BN_CLICKED(IDC_BTN_PARAM_FILE_CLOSE, &CDlgParamConfig::OnBnClickedBtnParamFileClose)
	ON_MESSAGE(WM_MSG_PARAM_UPLOAD_MSG, OnUpLoadMsg)
	ON_MESSAGE(WM_MSG_PARAM_PROMOTE_MSG, OnMsgPromote)
END_MESSAGE_MAP()


// CDlgParamConfig 消息处理程序


BOOL CDlgParamConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_BTN_PARAM_FILE_GET)->EnableWindow();
	GetDlgItem(IDC_BTN_PARAM_FILE_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PARAM_FILE_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PARAM_FILE_CLOSE)->EnableWindow(FALSE);

	m_strParamConfigFile.Format(_T("%s%d.conf"), PATHGetAppPath(), m_nDevID);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgParamConfig::OnDestroy()
{
	CDialog::OnDestroy();

	OnBnClickedBtnParamFileClose();
}


void CDlgParamConfig::OnBnClickedBtnParamFileGet()
{
	OpenDownFile();
	if (m_pFile)
	{
		CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(m_nDevID);
		if (pDev)
		{
			NETCLIENT_DLOpenGetDevCfg(&m_lGetParamHandle, pDev->GetDevIDNOForChar());
			NETCLIENT_DLSetGetDCfgMsgCB(m_lGetParamHandle, this, FUNGetDevParamerMsgCB);
			NETCLIENT_DLSetGetDCfgDataCB(m_lGetParamHandle, this, FUNDataCB);
			NETCLIENT_DLStartGetDevCfg(m_lGetParamHandle);
		}
	}
}

void CALLBACK CDlgParamConfig::FUNGetDevParamerMsgCB( int nMsg, int nParam, void* pUsr )
{
	CDlgParamConfig* pThis = (CDlgParamConfig*)pUsr;
	pThis->DoGetDevParamerMsgCB(nMsg, nParam);
}

void CDlgParamConfig::DoGetDevParamerMsgCB( int nMsg, int nParam )
{
	PostMessage(WM_MSG_PARAM_GET_MSG, nMsg, nParam);
}

LRESULT CDlgParamConfig::OnMsgParamGetMsg( WPARAM wParam, LPARAM lParam )
{
	switch(wParam)
	{
	case GPS_DOWNLOAD_MSG_BEGIN:
		{
			//正在获取设备参数信息，请等待......
			SetDlgItemText(IDC_ED_TIP, _T("Get Paramer! Please Wait...."));//正在获取设备参数信息，请稍等......
		}
		break;
	case GPS_DOWNLOAD_MSG_FAILED:
		{
			SetDlgItemText(IDC_ED_TIP, _T("Get Paramer Fail!"));//获取设备参数失败!		

			//ParmerConfError();
			//m_bGetParamSuc = FALSE;
			//m_nGetParamResult = lParam;
			//if (m_pConfigEntity->IsLoadConfigFile())
			//{
			//	ShowDlgLoading(FALSE);
			//	MSG_BOX_STR(IDIRErrorString(lParam));
			//
			//	//PostMessage(WM_SYSCOMMAND,SC_CLOSE);
			//}
			//SetEvent(m_hEventParam);
		}
		break;
	case GPS_DOWNLOAD_MSG_FINISHED:
		{
			//close
			StopGetDevParamer();
			CloseDownFile();
			GetDlgItem(IDC_BTN_PARAM_FILE_GET)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_PARAM_FILE_UPDATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_PARAM_FILE_SET)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_PARAM_FILE_CLOSE)->EnableWindow(TRUE);
			SetDlgItemText(IDC_ED_TIP, _T("Get Paramer Success!"));
			//m_bGetParamSuc = TRUE;
			//
			//if (m_pConfigEntity->IsLoadConfigFile())
			//{
			//	ShowDlgLoading(FALSE);
			//	m_hSheetWnd = m_pConfigEntity->DisplayConfig(GetDlgItem(IDC_ST_PARAMER_MAIN)->GetSafeHwnd(),m_szFileName);	
			//}
			//else
			//{
			//	m_pDlgLoading->CloseLoading();
			//}
			//SetEvent(m_hEventParam);
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return 0;
}

void CDlgParamConfig::StopGetDevParamer()
{
	if (m_lGetParamHandle != NULL)
	{	
		NETCLIENT_DLStopGetDevCfg(m_lGetParamHandle);
		NETCLIENT_DLCloseGetDevCfg(m_lGetParamHandle);	

		m_lGetParamHandle = NULL;
	}
}

void CALLBACK CDlgParamConfig::FUNDataCB( const char* pData, int nDataLen, long nPos, void* pUsr )
{
	CDlgParamConfig* pThis = (CDlgParamConfig*)pUsr;
	pThis->DoDataCB(pData, nDataLen, nPos);
}

void CDlgParamConfig::DoDataCB( const char* pBuf, int nLen, long nPos )
{
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

void CDlgParamConfig::OpenDownFile()
{
	ASSERT(NULL == m_pFile);

	//if (m_pConfigEntity->IsLoadConfigFile())
	{
		// #ifdef _DEBUG
		// 			_tcscpy(m_szFileName, _T("c:\\test.conf"));
		// 			m_pFile = _tfopen(m_szFileName, _T("wb"));
		// 			_tcscpy(m_szSaveFileName,_T("c:\\test1.conf"));
		// 			_tfopen(m_szSaveFileName, _T("wb"));
		// #else
		if (!m_strParamConfigFile.IsEmpty())
		{
			m_pFile = _tfopen(m_strParamConfigFile, _T("wb"));
		}
		else
		{
			TCHAR szTmpPath[MAX_PATH];//,szFilename[MAX_PATH] ;
			::GetTempPath (MAX_PATH, szTmpPath) ;
			::GetTempFileName (szTmpPath, TEXT("clientdemoparam"), 0, m_strParamConfigFile.GetBufferSetLength(MAX_PATH)) ;
			m_strParamConfigFile.ReleaseBuffer();
			m_pFile = _tfopen(m_strParamConfigFile, _T("wb"));
		}

		// 			TCHAR szSaveTmpPath[MAX_PATH];//,szFilename[MAX_PATH] ;
		// 			::GetTempPath (MAX_PATH, szSaveTmpPath) ;
		// 			::GetTempFileName (szSaveTmpPath, TEXT("cmsclientbmp"), 0, m_szSaveFileName) ;
		// 			_tfopen(m_szSaveFileName, _T("wb"));
		//#endif	
	}
	// 		else
	// 		{
	// 			m_pFile = _tfopen(m_strParamConfigFile, _T("wb"));
	// 		}
}

void CDlgParamConfig::CloseDownFile()
{
	if (m_pFile)
	{
		fclose(m_pFile);	m_pFile = NULL;
	}
}

void CDlgParamConfig::OnBnClickedBtnParamFileUpdate()
{
	::ShellExecute(NULL, _T("open"), _T("Explorer.exe"), _T(" /select,") + m_strParamConfigFile, NULL, SW_SHOWDEFAULT);
}

void CDlgParamConfig::OnBnClickedBtnParamFileSet()
{
	if (m_lUploadHandle == NULL)
	{
		StartUpload();
	}
	else
	{
		StopUpload();
	}

}

void CDlgParamConfig::OnBnClickedBtnParamFileClose()
{
	StopGetDevParamer();
	StopUpload();
	StopPromote();

	::DeleteFile(m_strParamConfigFile);

	GetDlgItem(IDC_BTN_PARAM_FILE_GET)->EnableWindow();
	GetDlgItem(IDC_BTN_PARAM_FILE_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PARAM_FILE_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PARAM_FILE_CLOSE)->EnableWindow(FALSE);
}

void CDlgParamConfig::StartUpload()
{
	int nRet = 0;
#if defined(_UNICODE) || defined(UNICODE)  
	NETCLIENT_ULOpenDevParamFileW(&m_lUploadHandle, m_strParamConfigFile);
#else
	CStringW str;
	str = m_strParamConfigFile + _T("0");
	nRet = NETCLIENT_ULOpenDevParamFileW(&m_lUploadHandle, str);
#endif

	nRet = NETCLIENT_ULSetUploadMsgCB(m_lUploadHandle, this, FUNUploadMsgCB);
	nRet = NETCLIENT_ULStartUpload(m_lUploadHandle);
}

void CALLBACK CDlgParamConfig::FUNUploadMsgCB( int nMsg, int nParam, void* pUsr )
{
	CDlgParamConfig* pThis = (CDlgParamConfig*)pUsr;
	pThis->DoUploadMsgCB(nMsg, nParam);
}

void CDlgParamConfig::DoUploadMsgCB( int nMsg, int nParam )
{
	PostMessage(WM_MSG_PARAM_UPLOAD_MSG, nMsg, nParam);
}

LRESULT CDlgParamConfig::OnUpLoadMsg( WPARAM wParam, LPARAM lParam )
{
	switch(wParam)
	{
	case GPS_UPLOAD_MSG_PROCESS:
		{
			//
			SetDlgItemText(IDC_ED_TIP, _T("Upload File!Please wait..."));
		}
		break;
	case GPS_UPLOAD_MSG_FAILED:
		{
			//GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG));//"配置"

			NETCLIENT_ULGetDestFileName(m_lUploadHandle, &m_nlpSvrID, m_szSvrFile);
			StopUpload();
			StartDownLoadToDevice();


			//m_bGetParamSuc = FALSE;
			//m_nGetParamResult = lParam;
			//if (m_pConfigEntity->IsLoadConfigFile())
			//{
			//	ShowDlgLoading(FALSE);
			//	MSG_BOX_STR(IDIRErrorString(lParam));
			//}
			//else
			//{
			//	m_pDlgLoading->CloseLoading();
			//}
			//SetEvent(m_hEventParam);
		}
		break;
	case GPS_UPLOAD_MSG_FINISHED:
		{
			SetDlgItemText(IDC_ED_TIP, _T("Upload File Success!"));//上传配置文件到服务器成功!

			NETCLIENT_ULGetDestFileName(m_lUploadHandle, &m_nlpSvrID, m_szSvrFile);
			StopUpload();
			StartDownLoadToDevice();
		}
		break;
	}

	return 0;
}

void CDlgParamConfig::StopUpload()
{
	if (m_lUploadHandle)
	{
		NETCLIENT_ULStopUpload(m_lUploadHandle);
		NETCLIENT_ULCloseUpload(m_lUploadHandle);
		m_lUploadHandle = NULL;
	}
}

void CDlgParamConfig::StartDownLoadToDevice()
{
	if (m_szSvrFile[0])
	{
		CDevBase* pDev = CVMgrDevice::GetInstance()->FindDvsDeviceByID(m_nDevID);
		NETCLIENT_ULOpenSetDevCfg(&m_lPromoteHanle, pDev->GetDevIDNOForChar(), m_nlpSvrID, m_szSvrFile);
		NETCLIENT_ULSetSetDCfgMsgCB(m_lPromoteHanle, this, FUNPromoteMsgCB);
		NETCLIENT_ULStartSetDevCfg(m_lPromoteHanle);
	}
}

void CALLBACK CDlgParamConfig::FUNPromoteMsgCB( int nMsg, int nParam, void* pUsr )
{
	CDlgParamConfig* pThis = (CDlgParamConfig*)pUsr;
	pThis->DoPromoteMsgCB(nMsg, nParam);
}

void CDlgParamConfig::DoPromoteMsgCB( int nMsg, int nParam )
{
	PostMessage(WM_MSG_PARAM_PROMOTE_MSG, nMsg, nParam);
}

LRESULT CDlgParamConfig::OnMsgPromote( WPARAM wParam, LPARAM lParam )
{
	if (m_lPromoteHanle != NULL)
	{
		switch(wParam)
		{
		case GPS_UPLOAD_MSG_FAILED:	//下载配置失败
			{
				StopPromote();

				//GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG));//"配置"


				GetDlgItem(IDC_ED_TIP)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_DOWN_FAILT));//下传配置参数文件失败!

				CString str;
				str.Format(_T("Err%d"), lParam);
				AfxMessageBox(str);
			}
			break;
		case GPS_UPLOAD_MSG_FINISHED:	//完成
			{
				StopPromote();

				SetDlgItemText(IDC_ED_TIP, LOADSTRINGEX(ID_STR_DLG_PARAMER_DOWN_SUCC));//下传配置文件到设备成功!
				//GetDlgItem(IDC_BUT_SAVE)->SetWindowText(LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG));//"配置"

				CString  strCuccess = LOADSTRINGEX(ID_STR_DLG_PARAMER_CONFIG_FINSH);//"配置已完成!"
				AfxMessageBox(strCuccess);	
			}
			break;
		case GPS_UPLOAD_MSG_PROCESS:
			{
				CString strUpSatue;
				strUpSatue.Format(_T("%s%d%%"), LOADSTRINGEX(ID_STR_DLG_PARAMER_UP_STAUE), lParam);
				SetDlgItemText(IDC_ED_TIP, strUpSatue);				
			}
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}

	return 0;
}

void CDlgParamConfig::StopPromote()
{
	if (m_lPromoteHanle != NULL)
	{
		NETCLIENT_ULStopSetDevCfg(m_lPromoteHanle);
		NETCLIENT_ULCloseSetDevCfg(m_lPromoteHanle);
		m_lPromoteHanle = NULL;
	}
}

void CDlgParamConfig::SetDevID( int nDevID )
{
	m_nDevID = nDevID;
}

