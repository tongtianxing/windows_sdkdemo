#include "StdAfx.h"
#include "AlarmTypeParse.h"
#include "VDvsDevice.h"
#include "DevMoblie.h"


CString	FormatSecond(int nSecond)
{
	CString str;
	str.Format(_T("%02d:%02d:%02d"), nSecond / 3600, nSecond % 3600 / 60, nSecond % 60);
	return str;
}
CString	GetChannelString(int nDevID, int nChnInfo)
{
	CString strRet;
	CString strTemp;
	CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByID(nDevID);
	for (int i = 0; i < GPS_MAX_DEV_CHN_NUM; ++ i)
	{
		if ( (nChnInfo>>i) & 0x01 )
		{
			if (pDevice)
			{
				strTemp = pDevice->GetChnName(i);
			}
			else
			{
				strTemp.Format(_T("%s%d"), LOADSTRINGEX(ID_STR_CHANNEL), i + 1);
			}
			if (!strRet.IsEmpty())
			{
				strRet += ",";
			}
			strRet += strTemp;
		}
	}
	return strRet;
}
CString GetFenceAlarm(GPSAlarmInfo_S& ArmInfo)
{
	CString strMark = _T(""); 
	CString strType = "";
	int nAlarmType = ArmInfo.AlarmType;
	switch (nAlarmType)
	{
	case GPS_ALARM_TYPE_IN_FENCE:
	case GPS_ALARM_TYPE_END_IN_FENCE:
		strMark = LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN);
		break;
	case GPS_ALARM_TYPE_OUT_FENCE:
	case GPS_ALARM_TYPE_END_OUT_FENCE:
		strMark = LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT);
		break;
	case GPS_ALARM_TYPE_IN_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_END_IN_FENCE_OVER_SPEED:
		strMark = LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN_OVER_SPEED);
		break;
	case GPS_ALARM_TYPE_OUT_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_END_OUT_FENCE_OVER_SPEED:
		strMark = LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT_OVER_SPEED);
		break;
	case GPS_ALARM_TYPE_IN_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_END_IN_FENCE_LOW_SPEED:
		strMark = LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN_LOWE_SPEED);
		break;
	case GPS_ALARM_TYPE_OUT_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_END_OUT_FENCE_LOW_SPEED:
		strMark = LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT_LOWE_SPEED);
		break;
	case GPS_ALARM_TYPE_IN_FENCE_STOP:
	case GPS_ALARM_TYPE_END_IN_FENCE_STOP:
		strMark = LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN_STOP);
		break;
	case GPS_ALARM_TYPE_OUT_FENCE_STOP:
	case GPS_ALARM_TYPE_END_OUT_FENCE_STOP:
		strMark = LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT_STOP);
		break;
	}

	switch(nAlarmType)
	{
	case GPS_ALARM_TYPE_END_IN_FENCE:
	case GPS_ALARM_TYPE_END_OUT_FENCE:
	case GPS_ALARM_TYPE_END_IN_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_END_OUT_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_END_IN_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_END_OUT_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_END_IN_FENCE_STOP:
	case GPS_ALARM_TYPE_END_OUT_FENCE_STOP:
		strType = LOADSTRINGEX(ID_STR_ALARM_END);
		break;
	case GPS_ALARM_TYPE_IN_FENCE:
	case GPS_ALARM_TYPE_OUT_FENCE:
	case GPS_ALARM_TYPE_IN_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_OUT_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_IN_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_OUT_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_IN_FENCE_STOP:
	case GPS_ALARM_TYPE_OUT_FENCE_STOP:
		strType = LOADSTRINGEX(ID_STR_ALARM_START);
		break;
	}

	strMark += strType;
	return strMark;
}

void GetSignalLossAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_GPS_SIGNAL_LOSS == ArmInfo.AlarmType) 
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);	
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_GPS_SIGNAL_LOSS), strMark);
}
void GetUserDefineAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_USEDEFINE == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_USEDEFINE), strMark);
}
void GetIOAlarm(int nIO, GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc, CDevBase* pDevice)
{
	CString strMark = _T("");
	CString strAlarm = _T("");
	if (pDevice && pDevice->GetDevType() == GPS_DEV_TYPE_MDVR)
	{
		CString strTemp;
		CVDvsDevice* pDev = (CVDvsDevice*)pDevice;
		if (nIO <= 8)
		{
			strTemp += pDev->GetDevInfo()->szIoInName[nIO - 1];
		}
		else
		{
			strTemp += pDev->GetDevInfo()->szIoInExtent[nIO - 9];
		}
		int nLen = _tcslen(strTemp);
		if (nLen == 0)
		{
			CString strIO;
			strIO.Format(_T("IO_%d"), nIO);
			strAlarm.Format(LOADSTRINGEX(ID_STR_DLG_ALARM_IO_TIP), strIO);					
		}
		else
		{
			strAlarm.Format(LOADSTRINGEX(ID_STR_DLG_ALARM_IO_TIP), strTemp);
		}	
	}
	
	if (GPS_ALARM_TYPE_IO_1 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_2 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_3 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_4 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_5 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_6 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_7 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_8 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_9 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_10 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_11 == ArmInfo.AlarmType
		|| GPS_ALARM_TYPE_IO_12 == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), strAlarm, strMark);
}
void GetUrgencyButtonAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_URGENCY_BUTTON == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_URGENCY_BUTTON), strMark);
}
void GetShakeAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_SHAKE == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_SHAKE), strMark);

	short shAlarmInfo = ArmInfo.AlarmInfo;
	if (shAlarmInfo)
	{
		if (shAlarmInfo & 0x7)
		{
			if (shAlarmInfo & 0x1)				strDesc += _T("X");
			if (shAlarmInfo & 0x2)				strDesc += _T("Y");
			if (shAlarmInfo & 0x4)				strDesc += _T("Z");
			strDesc += _T(" Direction Alarm");
		}
	}
}

void GetparkTooLongAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_PARK_TOO_LONG == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	CString strTemp;
	strDesc.Format(_T("%s%s %s%s"), LOADSTRINGEX(ID_STR_DESC_PARK_LAST_TIME), FormatSecond(ArmInfo.AlarmInfo)
		, LOADSTRINGEX(ID_STR_DESC_PARK_SETUP_TIME), FormatSecond(ArmInfo.Param[0]));
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_PARK_TOO_LONG), strMark);
}
void GetVideoLostAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc, CDevBase* pDev)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_VIDEO_LOST == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);	
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	strDesc = GetChannelString(pDev->GetID(), ArmInfo.AlarmInfo);
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_VIDEO_LOST), strMark);
}
void GetVideoMaskAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc, CDevBase* pDev)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_VIDEO_MASK == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
		strDesc = GetChannelString(pDev->GetID(), ArmInfo.AlarmInfo);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_VIDEO_MASK), strMark);
}
void GetDoorOpenLawlessAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_DOOR_OPEN_LAWLESS == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);	
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_DOOR_OPEN_LAWLESS), strMark);	
}
void GetWrongPwdAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_WRONG_PWD == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_WRONG_PWD), strMark);
}
void GetFireLowlessAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_FIRE_LOWLESS == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_FIRE_LOWLESS), strMark);
}
void GetTemperatorAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_TEMPERATOR == ArmInfo.AlarmType)
	{
		float fRealTmep = (ArmInfo.Param[0])/100.0;
		float fLowest = (ArmInfo.Param[1])/100.0;
		float fHightest = (ArmInfo.Param[2])/100.0;
		
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
		CString strTemp;
		if (0 == ArmInfo.AlarmInfo)
		{
			strTemp = LOADSTRINGEX(ID_STR_TEMPERATOR_DEVICE);
		}
		else if (1 == ArmInfo.AlarmInfo)
		{
			strTemp = LOADSTRINGEX(ID_STR_TEMPERATOR_MOTER);
		}
		else if (2 == ArmInfo.AlarmInfo)
		{
			strTemp = LOADSTRINGEX(ID_STR_TEMPERATOR_COACH);
		}
		strDesc.Format(_T("%s:%0.2f %s,%s:%0.2f %s, %s:%0.2f %s")
			, strTemp, fRealTmep ,LOADSTRINGEX(ID_STR_DLG_MOTION_UNIT_DC)
			,LOADSTRINGEX(ID_STR_DESC_TEMP_LOWEST), fLowest,LOADSTRINGEX(ID_STR_DLG_MOTION_UNIT_DC)
			, LOADSTRINGEX(ID_STR_DESC_TEMP_HIGHTEST) , fHightest,LOADSTRINGEX(ID_STR_DLG_MOTION_UNIT_DC));
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_TEMPERATOR), strMark);
}
void GetDiskErrAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_DISK_ERROR == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_DISK_ERROR), strMark);
}
void GetOverSpeedAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_OVERSPEED == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
		
		float fRealSpeed = (ArmInfo.Param[0])/100.0;
		float fLowest = (ArmInfo.Param[1])/100.0;
		float fHightest = (ArmInfo.Param[2])/100.0;
		
//		if (CConfigGViewerINI::GetInstance()->GetDevSpeedUnit() == 0) 
		{
			strDesc.Format(_T("%s:%0.2f km/h, %s:%0.2f km/h, %s:%0.2f km/h")
				, LOADSTRINGEX(ID_STR_DESC_SPEED_ALARM), fRealSpeed 
				, LOADSTRINGEX(ID_STR_DESC_SPEED_LOWEST), fLowest
				, LOADSTRINGEX(ID_STR_DESC_SPEED_HIGHTEST), fHightest);
		}
// 		else if (CConfigGViewerINI::GetInstance()->GetDevSpeedUnit() == SPEED_TYPE_MILE)  
// 		{
// 			fRealSpeed = fRealSpeed/1.6093;
// 			fLowest = fLowest/1.6093;
// 			fHightest = fHightest/1.6093;
// 			
// 			strDesc.Format("%s:%0.2f mp/h, %s:%0.2f mp/h, %s:%0.2f mp/h"
// 				, LOADSTRINGEX(ID_STR_DESC_SPEED_ALARM), fRealSpeed 
// 				, LOADSTRINGEX(ID_STR_DESC_SPEED_LOWEST), fLowest
// 				, LOADSTRINGEX(ID_STR_DESC_SPEED_HIGHTEST), fHightest);
// 		}
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	if ( ArmInfo.AlarmInfo == 0)
	{
		strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_EVENT_TYPE_OVERSPEED), strMark);
	}
	else if ( ArmInfo.AlarmInfo == 1)
	{
		strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_LOW_SPEED), strMark);					
	}
}
void GetBeyondBoundsAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_BEYOND_BOUNDS == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
		CString strTemp;
		if (0 == ArmInfo.AlarmInfo)
		{
			strTemp = LOADSTRINGEX(ID_STR_DESC_BEYOND_BOUNDS_INT);
		}
		else
		{
			strTemp = LOADSTRINGEX(ID_STR_DESC_BEYOND_BOUNDS_OUT);
		}
		strDesc.Format(_T("%s, %s: %d"), strTemp, LOADSTRINGEX(ID_STR_DESC_BEYOND_BOUNDS_NO), ArmInfo.Param[0]);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_BEYOND_BOUNDS), strMark);
}
void GetDoorAbnormalAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	CString strMark = _T("");
	if (GPS_ALARM_TYPE_DOOR_ABNORMAL == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
		CString strTemp;
		if (0 == ArmInfo.AlarmInfo)
		{
			strTemp = LOADSTRINGEX(ID_STR_DESC_DOOR_ABNORMAL_1);
		}
		else if (1 == ArmInfo.AlarmInfo)
		{
			strTemp = LOADSTRINGEX(ID_STR_DESC_DOOR_ABNORMAL_2);
		}
		else if (2 == ArmInfo.AlarmInfo)
		{
			strTemp = LOADSTRINGEX(ID_STR_DESC_DOOR_ABNORMAL_3);
		}
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_DOOR_ABNORMAL), strMark);
}
void GetMotionAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc, CDevBase* pDev)
{
	CString strMark = _T(""); 
	if (GPS_ALARM_TYPE_MOTION == ArmInfo.AlarmType)
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_START);
		strDesc = GetChannelString(pDev->GetID(), ArmInfo.AlarmInfo);
	}
	else
	{
		strMark = LOADSTRINGEX(ID_STR_ALARM_END);
		strDesc = GetChannelString(pDev->GetID(), ArmInfo.AlarmInfo);
	}
	
	strType.Format(_T("%s %s"), LOADSTRINGEX(ID_STR_ALARM_TYPE_MOTION_DETECT), strMark);  
}

void GetOilAlarm(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc, CDevBase* pDev)
{
	CString strTmp;
	switch(ArmInfo.AlarmType)
	{
	case GPS_ALARM_TYPE_REFUEL:
	case GPS_ALARM_TYPE_END_REFUEL:
		strType = LOADSTRINGEX(ID_STR_DLG_ARMSETUP_ADD_OIL);
		strTmp = LOADSTRINGEX(ID_STR_EVENT_TYPE_REFUEL);
		break;
	case GPS_ALARM_TYPE_STILL_FUEL:
	case GPS_ALARM_TYPE_END_STILL_FUEL:
		strType = LOADSTRINGEX(ID_STR_DLG_ARMSETUP_DEC_OIL);
		strTmp = LOADSTRINGEX(ID_STR_EVENT_TYPE_STILL_FUEL);
		break;

	}
	//AlarmInfo for fuel oil (9999 = 99.99 L), Param[0] for oil before refueling
	strDesc.Format(_T("%s:%s, %s:%s"), LOADSTRINGEX(ID_STR_EVENT_TYPE_ALARM_OIL_BEGIN), 
		FormatYouliang2String(ArmInfo.Param[0]), strTmp, FormatYouliang2String(ArmInfo.AlarmInfo));
}

void FormatGetDriverOn(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc, CDevBase* pDev)
{
	//司机开车验证通过事件 Param[0]:按位表示，0位：指纹，1位：酒精，2位：人脸

	strType = _T("Driver drove through verification");
	int nType = ArmInfo.Param[0];
	if (nType & 0x7)
	{
		CString strCheck;
		if (BIT_GET(nType, 0))
		{
			if (!strCheck.IsEmpty())
			{
				strCheck += _T(",");
			}
			strCheck += _T("Fingerprint");
		}
		if (BIT_GET(nType, 1))
		{
			if (!strCheck.IsEmpty())
			{
				strCheck += _T(",");
			}
			strCheck += _T("Alcohol");
		}
		if (BIT_GET(nType, 2))
		{
			if (!strCheck.IsEmpty())
			{
				strCheck += _T(",");
			}
			strCheck += _T("Human face");
		}
		strDesc.Format(_T("Check Items:%s"), strCheck);
	}
	else
	{
		strDesc.Format(_T("Check Items:none(%X)"), nType);
	}
}


void FormatMDVRAlarm2String(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc, CDevBase* pDevice)
{
	if (ArmInfo.AlarmType == GPS_ALARM_TYPE_CUSTOM)
	{
		return FormatCustomAlarm2String(ArmInfo, strType, strDesc, pDevice);
	}
	switch(ArmInfo.AlarmType)
	{
	case GPS_ALARM_TYPE_GPS_SIGNAL_LOSS:
	case GPS_ALARM_TYPE_END_GPS_SIGNAL_LOSS:
		GetSignalLossAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_USEDEFINE:
	case GPS_ALARM_TYPE_END_USEDEFINE:
		GetUserDefineAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_IO_1:
	case GPS_ALARM_TYPE_END_IO_1:
		GetIOAlarm(1, ArmInfo, strType, strDesc, pDevice);
		break;
    case GPS_ALARM_TYPE_IO_2:
	case GPS_ALARM_TYPE_END_IO_2:
		GetIOAlarm(2, ArmInfo, strType, strDesc, pDevice);
		break;
    case GPS_ALARM_TYPE_IO_3:
    case GPS_ALARM_TYPE_END_IO_3:
		GetIOAlarm(3, ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_IO_4:
	case GPS_ALARM_TYPE_END_IO_4:
		GetIOAlarm(4, ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_IO_5:
	case GPS_ALARM_TYPE_END_IO_5:
		GetIOAlarm(5, ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_IO_6:
	case GPS_ALARM_TYPE_END_IO_6:
		GetIOAlarm(6, ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_IO_7:
	case GPS_ALARM_TYPE_END_IO_7:
		GetIOAlarm(7, ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_IO_8:
	case GPS_ALARM_TYPE_END_IO_8:
		GetIOAlarm(8, ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_IO_9:
	case GPS_ALARM_TYPE_END_IO_9:
		GetIOAlarm(9, ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_IO_10:
	case GPS_ALARM_TYPE_END_IO_10:
		GetIOAlarm(10, ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_IO_11:
	case GPS_ALARM_TYPE_END_IO_11:
		GetIOAlarm(11, ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_IO_12:
	case GPS_ALARM_TYPE_END_IO_12:
		GetIOAlarm(12, ArmInfo, strType, strDesc, pDevice);
		break;

	case GPS_ALARM_TYPE_URGENCY_BUTTON:
	case GPS_ALARM_TYPE_END_URGENCY_BUTTON:
		GetUrgencyButtonAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_SHAKE:
	case GPS_ALARM_TYPE_END_SHAKE:
		GetShakeAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_PARK_TOO_LONG:
	case GPS_ALARM_TYPE_END_PARK_TOO_LONG:
		GetparkTooLongAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_VIDEO_LOST:
	case GPS_ALARM_TYPE_END_VIDEO_LOST:
		GetVideoLostAlarm(ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_VIDEO_MASK:
	case GPS_ALARM_TYPE_END_VIDEO_MASK:
		GetVideoMaskAlarm(ArmInfo, strType, strDesc, pDevice);
		break;
	case GPS_ALARM_TYPE_DOOR_OPEN_LAWLESS:
	case GPS_ALARM_TYPE_END_DOOR_OPEN_LAWLESS:
		GetDoorOpenLawlessAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_WRONG_PWD:
	case GPS_ALARM_TYPE_END_WRONG_PWD:
		GetWrongPwdAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_FIRE_LOWLESS:
	case GPS_ALARM_TYPE_END_FIRE_LOWLESS:
		GetFireLowlessAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_TEMPERATOR:
	case GPS_ALARM_TYPE_END_TEMPERATOR:
		GetTemperatorAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_DISK_ERROR:
	case GPS_ALARM_TYPE_END_DISK_ERROR:
		GetDiskErrAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_OVERSPEED:
	case GPS_ALARM_TYPE_END_OVERSPEED:
		GetOverSpeedAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_BEYOND_BOUNDS:
	case GPS_ALARM_TYPE_END_BEYOND_BOUNDS:
		GetBeyondBoundsAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_DOOR_ABNORMAL:
	case GPS_ALARM_TYPE_END_DOOR_ABNORMAL:
		GetDoorAbnormalAlarm(ArmInfo, strType, strDesc);
		break;
	case GPS_ALARM_TYPE_DEV_ONLINE:
		{
			strType = LOADSTRINGEX(ID_STR_ALARM_TYPE_DEV_ONLINE);
		}
		break;
	case GPS_ALARM_TYPE_DEV_DISONLINE:
		{
			strType = LOADSTRINGEX(ID_STR_ALARM_TYPE_DEV_DISONLINE);
		}
		break;

	case GPS_ALARM_TYPE_ACC_ON:
		{
			strType = LOADSTRINGEX(ID_STR_ALARM_TYPE_ACC_ON);
		}
		break;

	case GPS_ALARM_TYPE_ACC_OFF:
		{
			strType = LOADSTRINGEX(ID_STR_ALARM_TYPE_ACC_OFF);
		}
		break;
	case GPS_ALARM_TYPE_MOTION:      
	case GPS_ALARM_TYPE_END_MOTION: 
		GetMotionAlarm(ArmInfo, strType,strDesc, pDevice);
		break;

	case GPS_ALARM_TYPE_REFUEL:
	case GPS_ALARM_TYPE_END_REFUEL:
	case GPS_ALARM_TYPE_STILL_FUEL:
	case GPS_ALARM_TYPE_END_STILL_FUEL:
		GetOilAlarm(ArmInfo, strType,strDesc, pDevice);
		break;

	case GPS_ALARM_TYPE_IN_FENCE:
	case GPS_ALARM_TYPE_OUT_FENCE:
	case GPS_ALARM_TYPE_IN_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_OUT_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_IN_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_OUT_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_IN_FENCE_STOP:
	case GPS_ALARM_TYPE_OUT_FENCE_STOP:
	case GPS_ALARM_TYPE_END_IN_FENCE:
	case GPS_ALARM_TYPE_END_OUT_FENCE:
	case GPS_ALARM_TYPE_END_IN_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_END_OUT_FENCE_OVER_SPEED:
	case GPS_ALARM_TYPE_END_IN_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_END_OUT_FENCE_LOW_SPEED:
	case GPS_ALARM_TYPE_END_IN_FENCE_STOP:
	case GPS_ALARM_TYPE_END_OUT_FENCE_STOP:
		{
			strType = GetFenceAlarm(ArmInfo);
		}
		break;
	case GPS_ALARM_TYPE_SMOKE_SENSOR:
		strType = _T("Smoke alarm ") + LOADSTRINGEX(ID_STR_ALARM_START);
		break;
	case GPS_ALARM_TYPE_END_SMOKE_SENSOR:
		strType = _T("Smoke alarm ") + LOADSTRINGEX(ID_STR_ALARM_END);
		break;
		
		case GPS_ALARM_TYPE_DRIVER_ON:
		case GPS_ALARM_TYPE_END_DRIVER_ON:
			FormatGetDriverOn(ArmInfo, strType, strDesc, pDevice);
		break;
	default :
		{
			strType = LOADSTRINGEX(ID_STR_TYPE_UNKNOW);
		}
		break;
	}
}

void FormatMobileAlarm2String(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc)
{
	int nStrTypeID = ID_STR_TYPE_UNKNOW;
	switch(ArmInfo.AlarmType)
	{
	case GPS_ALARM_TYPE_DEV_ONLINE:
		{
			nStrTypeID = ID_STR_ALARM_TYPE_DEV_ONLINE;
		}
		break;
	case GPS_ALARM_TYPE_DEV_DISONLINE:
		{
			nStrTypeID = ID_STR_ALARM_TYPE_DEV_DISONLINE;
		}
		break;
	case GPS_ALARM_TYPE_FIRE:
		nStrTypeID = ID_STR_ALARM_TYPE_FIRE;
		break;
	case GPS_ALARM_TYPE_PANIC:
		nStrTypeID = ID_STR_ALARM_TYPE_PANIC;
		break;
	case GPS_ALARM_TYPE_TASK_FINISHED:
		nStrTypeID = ID_STR_ALARM_TYPE_TASK_FINISHED;
		break;
	case GPS_ALARM_TYPE_IMAGE_UPLOAD:
		nStrTypeID = ID_STR_ALARM_TYPE_IMAGE_UPLOAD;
		break;
	}
	strType = LOADSTRINGEX(nStrTypeID);
	strDesc = ArmInfo.szDesc;
}

void FormatAlarm2String(GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc, CDevBase* pDevice)
{   
//	if (pDevice->GetDevType() == GPS_DEV_TYPE_MDVR)
	{
		FormatMDVRAlarm2String(ArmInfo, strType, strDesc, pDevice);
	}
// 	else if(pDevice->GetDevType() == GPS_DEV_TYPE_MOBILE)
// 	{
// 		FormatMobileAlarm2String(ArmInfo, strType, strDesc);
// 	}
}
void GetXcSwipeCard( GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc )
{
	strType = _T("Swipe Card Alarm");
	int nType = ArmInfo.Param[0];
	if (nType == 0)
	{
		strDesc.Format(_T("Get On! Card Nunber:%s"), CString(ArmInfo.szDesc));
	}
	else if (nType == 1)
	{
		strDesc.Format(_T("Get Off! Card Nunber:%s"), CString(ArmInfo.szDesc));
	}
}

void FormatCustomAlarm2String( GPSAlarmInfo_S& ArmInfo, CString& strType, CString& strDesc, CDevBase* pDevice )
{
	switch (ArmInfo.AlarmInfo)
	{
	case CUSTOM_ALARM_TYPE_XC_SWIPE_CARD:
		GetXcSwipeCard(ArmInfo, strType, strDesc);
		break;
	}
}
