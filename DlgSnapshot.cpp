// DlgSnapshot.cpp : implementation file
//

#include "stdafx.h"
#include "DlgSnapshot.h"
//#include "DownSnapshot.h"
//#include "VersionForUndefine.h"
#include "SHLWAPI.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSnapshot dialog

CDlgSnapshot::CDlgSnapshot(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSnapshot::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSnapshot)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pDLSnapshot = NULL;
	m_nDevID = 0;
	m_nChn = 0;
	m_strFilePath = _T("");
	memset(m_szBMPFile, 0, sizeof(m_szBMPFile));
	memset(&m_tmBMPTime, 0, sizeof(m_tmBMPTime));
}


void CDlgSnapshot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSnapshot)
	DDX_Control(pDX, IDC_ST_PIC, m_stPic);
	DDX_Control(pDX, IDC_BTN_BROWSE, m_btnBrowse);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSnapshot, CDialog)
	//{{AFX_MSG_MAP(CDlgSnapshot)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSnapshot message handlers

BOOL CDlgSnapshot::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	LoadLanguage();
	if (m_strFilePath.IsEmpty())
	{
		SaveBMPFile();
	}

// 	if (m_pDLSnapshot != NULL)
// 	{
// 		m_stPic.LoadPic(m_pDLSnapshot->GetDownFileName());
// 	}
// 	else
// 	{
// 		m_stPic.LoadPic(m_szBMPFile);
// 	}
// 	memset(m_szBMPFile, 0, MAX_PATH);
// 	memcpy(m_szBMPFile, "f:/789.jpg", 10);
	BOOL bRet = m_stPic.LoadPic(m_szBMPFile);

	int nWidth = m_stPic.GetPicWidth();
	int nHeight = m_stPic.GetPicHeight();

	double dbTemp = nWidth * 1.0 / nHeight;
	CRect rc;
	m_stPic.GetClientRect(&rc);

	CRect rcPic;
	rcPic.left = rcPic.top = 0;
	int nShowHeight = (int)(rc.Width() / dbTemp);
	if (nShowHeight > rc.Height())
	{
		int nShowWidth = (int)(rc.Height() * dbTemp);
		if (nShowWidth > rc.Width())
		{
			rcPic.right = rc.Width();
			rcPic.bottom = rc.Height();
		}
		else
		{
			rcPic.right = nShowWidth;
			rcPic.bottom = rc.Height();
		}
	}
	else
	{
		rcPic.right = rc.Width();
		rcPic.bottom = nShowHeight;
	}

	CRect rcClient;
	GetClientRect(&rcClient);

	CWnd* pBtn = GetDlgItem(IDC_BTN_SAVE);
	CRect rcBtn;
	pBtn->GetClientRect(&rcBtn);
	pBtn->ClientToScreen(&rcBtn);
	ScreenToClient(&rcBtn);


	RECT rcMove;
	int nMiddleWidth = rcClient.left + rcClient.Width() / 2 ;
	int nMiddleHeight = rcClient.top + (rcBtn.top+20) / 2;
	rcMove.left = nMiddleWidth - rcPic.Width() / 2;
	rcMove.right = nMiddleWidth + rcPic.Width() / 2;
	rcMove.top = nMiddleHeight - rcPic.Height() / 2;
	rcMove.bottom = nMiddleHeight + rcPic.Height() / 2;
	m_stPic.MoveWindow(&rcMove);

	/*CVehicleBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByID(m_nDevID);*/
// 	if (pDevice && m_nChn>=0)
// 	{
// 		CString str;
// 		str.Format(_T("%s-%s"), pDevice->GetShowName(), pDevice->GetChnName(m_nChn));
// 		SetWindowText(str);
// 	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSnapshot::SetSaveFile(CString strFile)
{
	m_strFilePath = strFile;
}

void CDlgSnapshot::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}

void CDlgSnapshot::OnBtnSave() 
{
	CDialog::OnCancel();
	
	/*
	CString strFile;
	if (m_pDLSnapshot != NULL)
	{
		CString strName;
		CString strChn;
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		CVehicleBase* pDevice = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByID(m_pDLSnapshot->GetDevID());
		if (pDevice)
		{
			strName = pDevice->GetShowName();
			strChn = pDevice->GetChnName(m_pDLSnapshot->GetDevChn());
		}
		
		strFile.Format(_T("%s_%s___%04d-%02d-%02d %02d-%02d-%02d")
			, strName, strChn
			, sysTime.wYear, sysTime.wMonth, sysTime.wDay
			, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
		CFileDialog SaveDialog(FALSE, _T("*.jpg"), strFile
			, OFN_NOCHANGEDIR|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
			, _T("JPEG(*.jpg)|*.jpg||"));
		if (IDOK == SaveDialog.DoModal())
		{
			CString str = SaveDialog.GetPathName();
			CopyFile(m_pDLSnapshot->GetDownFileName(), str, FALSE);
		}
	}
	else
	{
		strFile.Format(_T("%04d-%02d-%02d %02d-%02d-%02d")
			, m_tmBMPTime.wYear, m_tmBMPTime.wMonth, m_tmBMPTime.wDay
			, m_tmBMPTime.wHour, m_tmBMPTime.wMinute, m_tmBMPTime.wSecond);
		CFileDialog SaveDialog(FALSE, _T("*.bmp"), strFile
			, OFN_NOCHANGEDIR|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
			, _T("BMP(*.bmp)|*.bmp||"));
		if (IDOK == SaveDialog.DoModal())
		{
			CString str = SaveDialog.GetPathName();
			CopyFile(m_szBMPFile, str.GetBuffer(0), FALSE);
		}
	}
	*/
}

void CDlgSnapshot::SaveBMPFile()
{
	/*
	CString strFile;
	
	CString strName;
	CString strChn;
	CString strDevNO;
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	CVehicleBase* pDevice = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByID(m_nDevID);
	if (pDevice)
	{
		strName = pDevice->GetShowName();
		strChn = pDevice->GetChnName(m_nChn);
		strDevNO = pDevice->GetDevIDNO();
	}

	CString strDir = GetDevImgPath(strName, strDevNO, (pDevice != NULL) ? TRUE : FALSE);
	
	BOOL bVersion = CVersionForUndefine::GetInstance()->IsVersion();
	if (bVersion)
	{
		strFile.Format(_T("%s %04d-%02d-%02d %02d-%02d-%02d"),
			strName, sysTime.wYear, sysTime.wMonth, sysTime.wDay
			, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	}
	else
	{
	    strFile.Format(_T("%s-%04d%02d%02d-%02d%02d%02d"),
		    strChn, sysTime.wYear, sysTime.wMonth, sysTime.wDay
		    , sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	}
	
	CString strFilePath;
	
	
	if (m_pDLSnapshot != NULL)
	{
		strFilePath.Format(_T("%s\\%s.JPG"), strDir, strFile);
		if (MoveFileEx(m_pDLSnapshot->GetDownFileName(), strFilePath, MOVEFILE_COPY_ALLOWED))
		{
			m_strFilePath = strFilePath;
		}
		
	}
	else
	{
		strFilePath.Format(_T("%s\\%s.BMP"), strDir, strFile);
		if(MoveFileEx(m_szBMPFile, strFilePath, MOVEFILE_COPY_ALLOWED))
		{
			m_strFilePath = strFilePath;
		}
	}	
	*/
}

CString CDlgSnapshot::GetDevImgPath(LPCTSTR szDevID, LPCTSTR szDevNO, BOOL bDevive)
{
	CString strSaveDir = "f:/";
	CString strDevDir;
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	if (bDevive)
	{
		strDevDir.Format(_T("%s%s(%s)\\%04d-%02d-%02d"), strSaveDir, szDevID, szDevNO,
				tm.wYear, tm.wMonth, tm.wDay);
	}
	else
	{
		strDevDir.Format(_T("%s%d\\%04d-%02d-%02d"), strSaveDir, m_nDevID,
				tm.wYear, tm.wMonth, tm.wDay);
	}
	if (!PathFileExists(strDevDir))
	{
		PATHCreateDirectory(strDevDir);
	}
	return strDevDir;
}

void CDlgSnapshot::SetDevID(int nDevID, int nChn)
{
	m_nDevID = nDevID;
	m_nChn = nChn;
}

void CDlgSnapshot::OnBtnBrowse() 
{
	
	if (!m_strFilePath.IsEmpty())
	{
		ShellExecute(NULL, _T("open"), _T("Explorer.exe"), _T(" /select,") + m_strFilePath, NULL, SW_SHOWDEFAULT);
	}
// 	else
// 	{
// 		ShellExecute(NULL, _T("open"), _T("Explorer.exe"), CConfigGViewerINI::GetInstance()->GetImgPath(), NULL, SW_SHOWDEFAULT);
// 	}
}

void CDlgSnapshot::LoadLanguage()
{
	SetDlgItemText(IDC_BTN_BROWSE, LOADSTRINGEX(ID_STR_DLG_SYSTEM_BTN_BROWSE));
}

int CDlgSnapshot::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	return 0;
}
