// clientdemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "clientdemo.h"
#include "clientdemoDlg.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientdemoApp

BEGIN_MESSAGE_MAP(CClientdemoApp, CWinApp)
	//{{AFX_MSG_MAP(CClientdemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientdemoApp construction

CClientdemoApp::CClientdemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClientdemoApp object

CClientdemoApp theApp;
//CObjPool<GPSVehicleState_S>	gVehiRunning;

/////////////////////////////////////////////////////////////////////////////
// CClientdemoApp initialization
BOOL CClientdemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

//	CImgGdiPlus::SInitGuidPlus();

 	NETCLIENT_Initialize();
  	NETCLIENT_MCStartWork();
  	AVDEC_Initialize(0);

	CString strFile;
	strFile = PATHGetAppPath();
	strFile = _T("Language\\english");
	CLanguage::GetInstance()->SetLanguage(strFile);

	CDlgLogin dlgLogin;
	if (IDOK != dlgLogin.DoModal())
	{
		return FALSE;
	}


	CClientdemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	CVMgrDevice::DelInstance();
	CFactoryDevice::DelInstance();
	AVDEC_UnInitialize(AVDEC_GetDecHandle());
	NETCLIENT_MCStopWork();
	NETCLIENT_UnInitialize();
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


void CClientdemoApp::SetLoginInfo(LPCTSTR lpszIP, unsigned short usPort, LPCTSTR lpszCmp, LPCTSTR lpszUsr, LPCTSTR lpszPwd)
{
	m_strDirSvrIP = lpszIP;
	m_usDirSvrPort = usPort;
	m_strLoginCmpny = lpszCmp; 
	m_strLoginUsr = lpszUsr;
	m_strLoginPwd = lpszPwd;
}
