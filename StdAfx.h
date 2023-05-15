// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E2623B2E_D745_4628_804B_2FC39509A80B__INCLUDED_)
#define AFX_STDAFX_H__E2623B2E_D745_4628_804B_2FC39509A80B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable : 4786)
#pragma warning(disable : 4996)
#include <map>
#include <list>
#include <vector>
#include <SHLWAPI.H>
#include <atlconv.h>

#define SAFE_DELETE_OBJECT(p) if ((p) != NULL) {delete (p); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p) if ((p) != NULL) {delete [] (p); (p) = NULL;}
#define SAFE_CLOSE_HANDLE(p) if ((p) != NULL) {CloseHandle((p)); (p) = NULL;}
#define SAFE_CLOSE_SOCKET(p) if ((p) != INVALID_SOCKET) {closesocket((p)); (p) = INVALID_SOCKET;}

//一个位的设置、清除、获取宏   
#define   BIT_SET(var, bit) ((var) |= (1<<(bit)))
#define   BIT_CLEAR(var, bit) ((var) &= ~(1<<(bit)))
#define   BIT_GET(var, bit) (((var)>>(bit)) & 0x01)


#include "MutexLock.h"
#include "PublicApi.h"
#include "StringSTL.h"
#include "StaticObject.h"
//#include "WndPublic.h"

#include "netclientapi.h"
#pragma comment(lib, "libnetclient.lib")
#include "Include/netmediaapi.h"
#pragma comment(lib, "libnetmedia.lib")
#include "Include/avdecoderapi.h"
#pragma comment(lib, "libavdecoder.lib")

#include "LangCmsCnt.h"
#include "Language.h"
// #ifdef _DEBUG
// #pragma comment(lib, "Lib/libwndcommond.lib")
// #pragma comment(lib, "libcommond.lib")
// #else
// #pragma comment(lib, "Lib/libwndcommon.lib")
// #pragma comment(lib, "libcommon.lib")
// #endif

#include <libcommon.h>
#include <libwndcommon.h>
#include "libcontrol.h"

// #ifdef _DEBUG
// #pragma comment(lib, "libwndcommon10D.lib")
// #pragma comment(lib, "libcommon10d.lib")
// #pragma comment(lib, "libcontrold.lib")
// #else
// #pragma comment(lib, "libwndcommon10.lib")
// #pragma comment(lib, "libcommon10.lib")
// #pragma comment(lib, "libcontrol.lib")
// #endif

#include "resource.h"
#include "commondef.h"
#include "CommonFun.h"
#include "DevMgrDef.h"
#include "VMgrDevice.h"
#include "FactoryDevice.h"
#include "VehicleBase.h"
#include "DevBase.h"

#include "AlarmTypeParse.h"
#include "GPSStatusParse.h"

#include "SvrVer.h"
#include "CharSetConvert.h"
#include "VehicleBaseMgr.h"


typedef struct tagDeviceStatusChange
{
	GPSVehicleState_S* pVehiRun;
	char* pOnline;
	int nCount;
}DeviceStatusChange_S;


#define MSG_LOGIN_INFO				WM_USER+0x1000
#define MSG_CONTROL_INFO			WM_USER+0x1001
#define MSG_ALARM_INFO				WM_USER+0x1002
#define MSG_ALARM_MSG				WM_USER+0x1003
#define MSG_NOTIFY_MSG				WM_USER+0x1005
#define MSG_TALKBACK_MSG			WM_USER+0x1006
#define MSG_DEVICE_INFO_CHANGE		WM_USER+0x1007
#define MSG_EVENT_CHANGE			WM_USER+0x1008
#define MSG_RECORD_TIME_OUT			WM_USER+0x1009
#define MSG_DEV_TRANSPARENT_DATA    WM_USER+0x100A		//设备透传上报信息

#define  ALARM_RECODER_STOP				0xFF 	   
#define  TIMER_IDEVENT_EXPIR			0xFFF


#define DLG_CTRL_MSG_DEVICE_STATUS_CHANGE		WM_USER + 0x2002


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E2623B2E_D745_4628_804B_2FC39509A80B__INCLUDED_)
