// Common.cpp: implementation of the CCommon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "clientdemo.h"
#include "Common.h"

#include "UsrLogDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void GetClientSubTypeLog(GPSUsrLog_S* pUserLog, CString& strSubType, CString& strInfo)
{
	switch(pUserLog->nSubType)
	{
	case USRLOG_LOGIN_SUB_TYPE_LOGIN:
		strSubType = _T("User Logined");
		strInfo.Format(_T("IP:%s, Session:%s"), pUserLog->szParam1, pUserLog->szParam2);
		break;
	case USRLOG_LOGIN_SUB_TYPE_LOGOUT:
		strSubType = _T("User Logout");
		strInfo = _T("");
		break;
	case USRLOG_LOGIN_SUB_TYPE_INTERUPT:
		strSubType = _T("Network disconnect");
		break;
	case USRLOG_LOGIN_SUB_TYPE_TRANSFER:
		strSubType = _T("Transfer");
		strInfo.Format(_T("Server IDNO:%s, IP:%s"), pUserLog->szParam1, pUserLog->szParam2);
		break;
	case USRLOG_LOGIN_SUB_TYPE_UNKOWN_USR:
		strSubType = _T("Invaid user or password");
		strInfo.Format(_T("IP:%s, User:%s, Password:%s"), pUserLog->szParam1, pUserLog->szParam2, pUserLog->szParam3);
		break;
	case USRLOG_LOGIN_SUB_TYPE_GET_SVR_FAILED:
		strSubType = _T("Failed to get an usable server");
		strInfo.Format(_T("IP:%s"), pUserLog->szParam1);
		break;
	default:
		strSubType = _T("Unknow log");
		strInfo = _T("");
		break;
	}
}

void GetDevCtrlSubTypeLog(GPSUsrLog_S* pUserLog, CString& strSubType, CString& strInfo)
{
	switch(pUserLog->nSubType)
	{
	case USRLOG_DEV_CTRL_SUB_TYPE_SEND_TEXT:
		strSubType = _T("Send TTS Command");
		strInfo.Format(_T("TTS:%s"), pUserLog->szParam1);
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SEND_SMS:
		strSubType = _T("Send message to device");
		strInfo.Format(_T("Phone:%s, Content:%s"), pUserLog->szParam1, pUserLog->szParam2);
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SEND_CTRL:
		strSubType = _T("Send command");
		strInfo.Format(_T("Cmd:%s, User:%s, Password:%s"), pUserLog->szParam1, pUserLog->szParam2, pUserLog->szParam3);
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SEND_PTZ:
		strSubType = _T("PTZ Control");
		strInfo.Format(_T("Channel:%s, Cmd:%s, Speed:%s, Param:%s"), pUserLog->szParam1, pUserLog->szParam2, pUserLog->szParam3, pUserLog->szParam4);
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_READ_STATUS:
		strSubType = _T("Get Status");
		break;
	case USRLOG_DEV_CTRL_SUB_TYP_SET_GPSINTERVAL:
		strSubType = _T("Send GPS interval");
		strInfo.Format(_T("Time:%s"), pUserLog->szParam1);
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_READ_MOTION:
		strSubType = _T("Motion Detect");
		strInfo.Format(_T("Channel:%s"), pUserLog->szParam1);
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SET_MOTION:
		strSubType = _T("Set motion detection");
		strInfo.Format(_T("Channel:%s"), pUserLog->szParam1);
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_READ_NETFLOW_STATISTICS:
		strSubType = _T("Get network flow statistics");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SET_NETFLOW_PARAM:
		strSubType = _T("Set network flow");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_CLEAR_NETFLOW_STATISTICS:
		strSubType = _T("Clear network flow data");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_ADJUST_NETFLOW_STATISTICS:
		strSubType = _T("Adjust newet flow");
		strInfo.Format(_T("flow:%s"), pUserLog->szParam1);
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SEND_DISPATCH_COMMAND:
		strSubType = _T("Send dispatch commnad");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SEND_CFG_VIDEO_COMMAND:
		strSubType = _T("Send video configuration");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_GET_CFG_VIDEO_COMMAND:
		strSubType = _T("Get Video configuration");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SEND_CFG_AUDIO_COMMAND:
		strSubType = _T("Send audio configuration");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_GET_CFG_AUDIO_COMMAND:
		strSubType = _T("Get audio configuration");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SEND_CFG_AUDIO_INPUT_COMMAND:
		strSubType = _T("Configue audio input");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_GET_CFG_AUDIO_INPUT_COMMAND:
		strSubType = _T("Get audio input configuration ");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SEND_CFG_PTZ_COMMAND:
		strSubType = _T("Config ptz");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_GET_CFG_PTZ_COMMAND:
		strSubType = _T("Get ptz configuration");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_GET_PARAM:
		strSubType = _T("Get Param");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SET_PARAM:
		strSubType = _T("Set Param");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_TRANSPARENT_CONFIG:
		strSubType = _T("Set transparent config");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_FREE_PRESET_GET:
		strSubType = _T("Get free preset bit");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_GET_VIDEO_COLOR:
		strSubType = _T("Get video color");
		break;
	case USRLOG_DEV_CTRL_SUB_TYPE_SET_VIDEO_COLOR:
		strSubType = _T("Set video color");
		break;

	default:
		strSubType = _T("Unknow log");
		break;
	}
}

void GetMediaSubTypeLog(GPSUsrLog_S* pUserLog, CString& strSubType, CString& strInfo)
{
	switch(pUserLog->nSubType)
	{
	case USRLOG_MEDIA_SUB_TYPE_VIDEO:
		strSubType = _T("Preview");
		strInfo.Format(_T("Channel:%s"), pUserLog->szParam1);
		break;
	case USRLOG_MEDIA_SUB_TYPE_AUDIO:
		strSubType = _T("Listen");
		strInfo.Format(_T("Channel:%s"), pUserLog->szParam1);
		break;
	case USRLOG_MEDIA_SUB_TYPE_SNAPSHOT:
		strSubType = _T("Snapshot");
		strInfo.Format(_T("Channel:%s"), pUserLog->szParam1);
		break;
	case USRLOG_MEDIA_SUB_TYPE_REC_SEARCH:
		strSubType = _T("Search");
		strInfo.Format(_T("Channel:%s, Time:%s"), pUserLog->szParam1, pUserLog->szParam2);
		break;
	case USRLOG_MEDIA_SUB_TYPE_REC_DOWN:
		strSubType = _T("Download video");
		strInfo.Format(_T("File :%s"), pUserLog->szParam1);
		break;
	case USRLOG_MEDIA_SUB_TYPE_DLOWN_DEV_PARAM:
		strSubType = _T("Get device param");
		break;
	case USRLOG_MEDIA_SUB_TYPE_UPLOAD_DEV_PARAM_FILE:
		strSubType = _T("Upload device param");
		strInfo.Format(_T("File length :%s"), pUserLog->szParam1);
		break;
	case USRLOG_MEDIA_SUB_TYPE_UPLOAD_DEVICE_PARAM:
		strSubType = _T("Device info");
		strInfo.Format(_T("file :%s, length :%s"), pUserLog->szParam1, pUserLog->szParam2);
		break;
	case USRLOG_MEDIA_SUB_TYPE_UPLOAD_DEV_UP_FILE:
		strSubType = _T("Upload firmware");
		strInfo.Format(_T("Version :%s, Device type:%s, Length:%s"), pUserLog->szParam1, pUserLog->szParam2, pUserLog->szParam3);
		break;
	case USRLOG_MEDIA_SUB_TYPE_UPLOAD_UPGRADE_DEVICE:
		strSubType = _T("Upgrade remotely");
		strInfo.Format(_T("Version :%s, File:%s"), pUserLog->szParam1, pUserLog->szParam2);
		break;
	case USRLOG_MEDIA_SUB_TYPE_PLAYBACK:
		strSubType = _T("Playback remotly");
		strInfo.Format(_T("File:%s"), pUserLog->szParam1);
		break;
	case USRLOG_MEDIA_SUB_TYPE_BROADCAST:
		strSubType = _T("Broadcast");
		strInfo.Format(_T("Channel:%s"), pUserLog->szParam1);
		break;
	default:
		strSubType = _T("Unknow");
		break;
	}
	
}

void GetUserLog(GPSUsrLog_S* pUserLog, CString& strMainType, CString& strSubType, CString& strInfo)
{
	switch(pUserLog->nMainType)
	{
	case USRLOG_MAIN_TYPE_LOGIN:
		strMainType = "User Login";
		GetClientSubTypeLog(pUserLog, strSubType, strInfo);
		break;
	case USRLOG_MAIN_TYPE_DEVICE_CTRL:
		strMainType = "Device Control";
		GetDevCtrlSubTypeLog(pUserLog, strSubType, strInfo);
		break;
	case USRLOG_MAIN_TYPE_MEDIA:
		strMainType = "Media type";
		GetMediaSubTypeLog(pUserLog, strSubType, strInfo);
		break;
	default:
		strMainType = "Unknow";
		break;
	}
}
