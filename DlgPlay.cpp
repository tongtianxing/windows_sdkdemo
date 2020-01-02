// DlgPlay.cpp : implementation file
//

#include "stdafx.h"
//#include "MDVRdemo.h"
#include "DlgPlay.h"

//#pragma comment(lib, "libmdvrplay.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_TIMER_PLAY_TIME			1

/////////////////////////////////////////////////////////////////////////////
// CDlgPlay dialog


CDlgPlay::CDlgPlay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPlay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lPlayHandle = NULL;
	m_bPause = FALSE;
	
	m_dwSetPos = GetTickCount();
	m_nPlayRate = AVDEC_PLAY_RATE_NORMAL;
	
	m_bOpenSound = FALSE;
}


void CDlgPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlay)
	DDX_Control(pDX, IDC_SLIDER2, m_sliVolume);
	DDX_Control(pDX, IDC_CHK_SOUND, m_btnSound);
	DDX_Control(pDX, IDC_SLIDER1, m_sliPos);
	DDX_Control(pDX, IDC_ST_TIME, m_stTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlay, CDialog)
	//{{AFX_MSG_MAP(CDlgPlay)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_PLAY, OnBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, OnBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_SLOW, OnBtnSlow)
	ON_BN_CLICKED(IDC_BTN_FAST, OnBtnFast)
	ON_BN_CLICKED(IDC_BTN_STEP, OnBtnStep)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_CHK_SOUND, OnChkSound)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, OnReleasedcaptureSlider2)
	ON_BN_CLICKED(IDC_BUTTON_FROWARD_I_FRAM, OnButtonFrowardIFram)
	ON_BN_CLICKED(IDC_BUTTON_BACKWARD_I_FRAM, OnButtonBackwardIFram)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_FILE_END, OnMsgFileEnd)
	ON_BN_CLICKED(IDC_BUTTON_SN, OnBnClickedButtonSn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlay message handlers
BOOL CDlgPlay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_sliVolume.SetRange(0, 100);
	m_sliVolume.SetPos(75);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPlay::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CloseFile();
}

void CDlgPlay::OnBtnOpen() 
{
	
	CFileDialog    fileOpenDlg(TRUE, NULL, NULL, OFN_READONLY , 
		_T("Rec Files(*.grec)|*.grec||"), NULL);
	if(fileOpenDlg.DoModal()==IDOK)
	{
		CloseFile();

		CString		strTemp;
		int nCount = 0;
        POSITION pos = fileOpenDlg.GetStartPosition();
		if (pos != NULL)
		{
			m_strPlayFile = fileOpenDlg.GetNextPathName(pos);

// 			FILE* pFile = fopen(m_strPlayFile.GetBuffer(0), "rb");
// 			if (pFile != NULL)
// 			{
// 				fclose(pFile);	pFile = NULL;
// 			}
			long lReader = NULL;
#ifdef _UNICODE
			USES_CONVERSION;
			if (S_OK == AVDEC_OpenReader(AVDEC_GetDecHandle(), &lReader, W2A(m_strPlayFile.GetBuffer(0))))
#else
			if (S_OK == AVDEC_OpenReader(AVDEC_GetDecHandle(), &lReader, m_strPlayFile.GetBuffer(0)))

#endif

			{
				IDECFileInfo_S FileInfo = {0};
				AVDEC_ReadFileInfo(lReader, &FileInfo);
				AVDEC_CloseReader(lReader);lReader = NULL;
			}
//			PlayFile();
		}
	}
}

void CDlgPlay::OnBtnPlay() 
{
	
	if (m_lPlayHandle)
	{
		if (m_bPause)
		{
			AVDEC_Pause(m_lPlayHandle, 0);
			m_bPause = FALSE;
		}
		else
		{
			if (m_nPlayRate != AVDEC_PLAY_RATE_NORMAL)
			{
				m_nPlayRate = AVDEC_PLAY_RATE_NORMAL;
				AVDEC_SetPlayRate(m_lPlayHandle, AVDEC_PLAY_RATE_NORMAL);
				UpdateRate();
			}
		}
	}
	else
	{
		PlayFile();
	}
}

void CDlgPlay::OnBtnPause() 
{
	
	if (m_lPlayHandle)
	{
		if (!m_bPause)
		{
			AVDEC_Pause(m_lPlayHandle, 1);
			m_bPause = TRUE;
		}
	}
}

void CDlgPlay::OnBtnStop() 
{
	
	CloseFile();
}

void CDlgPlay::OnBtnSlow() 
{
	
	if (m_lPlayHandle)
	{	
		RestorePlay();
		if (m_nPlayRate > (-1 * AVDEC_PLAY_FAST_MAX))
		{
			m_nPlayRate -= AVDEC_PLAY_FAST_RATE;
			AVDEC_SetPlayRate(m_lPlayHandle, m_nPlayRate);
			UpdateRate();
		}
	}
}

void CDlgPlay::OnBtnFast() 
{
	
	if (m_lPlayHandle)
	{	
		RestorePlay();
		if (m_nPlayRate < AVDEC_PLAY_FAST_MAX)
		{
			m_nPlayRate += AVDEC_PLAY_FAST_RATE;
			AVDEC_SetPlayRate(m_lPlayHandle, m_nPlayRate);
			UpdateRate();
		}
	}
}

void CDlgPlay::OnBtnStep() 
{
	
	if (m_lPlayHandle)
	{
		AVDEC_OneByOne(m_lPlayHandle);
	}
}

void CDlgPlay::RestorePlay()
{
	if (m_lPlayHandle)
	{
		if (m_bPause)
		{
			m_bPause = FALSE;
			AVDEC_Pause(m_lPlayHandle, 0);
		}
	}
}

void CDlgPlay::UpdateRate()
{
	int nTemp = m_nPlayRate;
	int nRate = 1;
	if (nTemp < 0)
	{
		nTemp = -1 * nTemp;
		nRate = -1;
	}
	for (int i = 0; i < nTemp; ++ i)
	{
		nRate = nRate * 2;
	}
	CString str;
	str.Format(_T("%dX"), nRate);
	SetDlgItemText(IDC_ST_RATE, str);
}

void CDlgPlay::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (ID_TIMER_PLAY_TIME == nIDEvent)
	{
		if (m_lPlayHandle)
		{
			long nMinSecond = 0;
			AVDEC_GetPlayTime(m_lPlayHandle, &nMinSecond);
			long nSecond = nMinSecond / 1000;
			CString str;
			str.Format(_T("%s / %s"), FormatSecond(nSecond), m_strFileTime);
			m_stTime.SetWindowText(str);
			
			if (!m_sliPos.GetLBtnDown() && TIMEIsTimeOut(m_dwSetPos, 1000))
			{
				m_sliPos.SetPos(nMinSecond);
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

CString	CDlgPlay::FormatSecond(long nSecond)
{
	CString str;
	str.Format(_T("%02d:%02d:%02d"), nSecond / 3600
		, (nSecond % 3600) / 60
		, nSecond % 60);
	return str;
}

void CDlgPlay::CloseFile()
{
	CWaitCursor wait;
	if (m_lPlayHandle)
	{
		AVDEC_Stop(m_lPlayHandle);
		AVDEC_CloseFile(m_lPlayHandle);
		m_lPlayHandle = NULL;
	}
	m_sliPos.SetPos(0);
	if (m_nPlayRate < AVDEC_PLAY_RATE_NORMAL)
	{
		m_nPlayRate = AVDEC_PLAY_RATE_NORMAL;
	}
	SetDlgItemText(IDC_ST_RATE, _T(""));
//	SetDlgItemText(IDC_ST_RANGE, "");
	SetDlgItemText(IDC_ST_TIME, _T(""));
	KillTimer(ID_TIMER_PLAY_TIME);
}

void CDlgPlay::PlayFile()
{
	CWaitCursor wait;
	if (!m_strPlayFile.IsEmpty())
	{
		AVDEC_OpenPlayHandle(AVDEC_GetDecHandle(), &m_lPlayHandle);
#ifdef _UNICODE
		USES_CONVERSION;
		if (S_OK == AVDEC_OpenFile(m_lPlayHandle, W2A(m_strPlayFile)))
#else
		if (S_OK == AVDEC_OpenFile(m_lPlayHandle, m_strPlayFile))
#endif
		{
			AVDEC_SetPlayWnd(m_lPlayHandle, GetDlgItem(IDC_ST_VIDEO)->GetSafeHwnd());
			AVDEC_SetEndCallBack(m_lPlayHandle, this, EndCBFun);
			AVDEC_GetFileInfo(m_lPlayHandle, &m_FileInfo);
			
			CString str;
			// 			str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d  -  %02d:%02d:%02d")
			// 				, m_tmBegin.wYear, m_tmBegin.wMonth, m_tmBegin.wDay
			// 				, m_tmBegin.wHour, m_tmBegin.wMinute, m_tmBegin.wSecond
			// 				, m_tmEnd.wHour, m_tmEnd.wMinute, m_tmEnd.wSecond);
			//m_stRange.SetWindowText(str);
			m_strFileTime = FormatSecond(m_FileInfo.nTotalMinSecond / 1000);
			str.Format(_T("%s / %s"), FormatSecond(0), m_strFileTime);
			m_stTime.SetWindowText(str);
			
			m_sliPos.SetRange(0, m_FileInfo.nTotalMinSecond);
			m_sliPos.SetPos(0);
			
			AVDEC_Play(m_lPlayHandle);
			if (m_bOpenSound)
			{
				AVDEC_PlaySound(m_lPlayHandle);
				ChangeVolume();
			}
			SetTimer(ID_TIMER_PLAY_TIME, 300, NULL);
		}
		else
		{
			AfxMessageBox(_T("Open File Failed"));
		}
	}
	else
	{
		OnBtnOpen();
	}
}

LRESULT CDlgPlay::OnMsgFileEnd(WPARAM wParam, LPARAM lParam)
{
	OnBtnStop();
	return 0;
}

void CDlgPlay::EndCBFun(int nMsg, void* pUsr)
{
	CDlgPlay* pThis = (CDlgPlay*)pUsr;
	pThis->DoEndCB(nMsg);
}

void CDlgPlay::DoEndCB(int nMsg)
{
	PostMessage(WM_MSG_FILE_END, nMsg, 0);
}

void CDlgPlay::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	*pResult = 0;
	int nPos = m_sliPos.GetPos();
	if (m_lPlayHandle)
	{
		AVDEC_SetPlayTime(m_lPlayHandle, nPos);
	}
	m_dwSetPos = GetTickCount();
}

void CDlgPlay::OnChkSound() 
{
	
	if (m_lPlayHandle)
	{
		m_bOpenSound = m_btnSound.GetCheck();
		if (m_bOpenSound)
		{
			AVDEC_PlaySound(m_lPlayHandle);
		}
		else
		{
			AVDEC_StopSound(m_lPlayHandle);
		}
	}
}

void CDlgPlay::OnReleasedcaptureSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	*pResult = 0;

	ChangeVolume();
}

void CDlgPlay::ChangeVolume()
{
	if (m_lPlayHandle)
	{
		int nPos = m_sliVolume.GetPos();
		AVDEC_SetVolume(m_lPlayHandle, nPos);		
	}
}


void CDlgPlay::OnButtonFrowardIFram() 
{
	
	if (m_lPlayHandle)
	{
		AVDEC_PlayOneIFrame(m_lPlayHandle, FALSE);
		m_bPause = TRUE;
	}
}

void CDlgPlay::OnButtonBackwardIFram() 
{
	
	if (m_lPlayHandle)
	{
		AVDEC_PlayOneIFrame(m_lPlayHandle, TRUE);
		m_bPause = TRUE;
	}
}
#include "DlgSnapshot.h"
void CDlgPlay::OnBnClickedButtonSn()
{
	if (m_lPlayHandle)
	{
		CString strFile = _T("f:\\123.bmp");
		AVDEC_CaptureBMP(m_lPlayHandle, CStringA(strFile));
// 		CString strFile = "f:/123.jpg";
// 		AVDEC_CaptureJPEG(m_lPlayHandle, strFile);
		SYSTEMTIME tmNow;
		GetLocalTime(&tmNow);
		CDlgSnapshot dlg;
		dlg.SetBMPFile(strFile, tmNow);
		dlg.SetDevID(10001, 1);
		dlg.DoModal();
	}
}
