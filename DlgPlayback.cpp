// DlgPlayback.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPlayback.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayback dialog


CDlgPlayback::CDlgPlayback(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayback::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPlayback)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPlayback::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayback)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlayback, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayback)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayback message handlers

BOOL CDlgPlayback::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_dlgRecPlayback.Create(CDlgRecPlayback::IDD, this);
	m_dlgRecPlayback.ShowWindow(SW_SHOW);
	MoveCtrl();

	SetTimer(1, 1000, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPlayback::MoveCtrl()
{
	CRect rc;
	GetClientRect(rc);
	m_dlgRecPlayback.MoveWindow(rc);
}

int CDlgPlayback::Play(GPSFile_S* pFile, int nChannel)
{
	m_File = *pFile;
	m_nChannel = nChannel;
	return 0;
}
void CDlgPlayback::Stop()
{
	m_dlgRecPlayback.Stop();
}

void CDlgPlayback::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(nIDEvent);
	m_dlgRecPlayback.Play(&m_File, m_nChannel, 0);
	
	CDialog::OnTimer(nIDEvent);
}
