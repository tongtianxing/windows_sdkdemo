#include "StdAfx.h"
#include "GPSStatusParse.h"
#include "VDvsDevice.h"
#include "DevMoblie.h"
//#include "VMgrDeviceUserAlarmShield.h"

void AddSeparator(CString& str, CString strSeparator)
{
	if (!str.IsEmpty() && str.GetAt(str.GetLength()-1) != strSeparator)
	{
		str += strSeparator;
	}
}

void InsertAlarmStatus(int nAlarmType, CString& strNormalStatus, CString& strAlarmStatus, CString& status)
{
// 	if (CVMgrDeviceUserAlarmShield::GetInstance()->FindAlarmType(nAlarmType))
// 	{
// 		if (!strNormalStatus.IsEmpty())
// 		{
// 			strNormalStatus += ",";
// 		}
// 		strNormalStatus += status;
// 	}
// 	else
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += ",";
		}
		strAlarmStatus += status;
	}
}
void GetGPSStatus(unsigned int sStatus, CString& strNormalStatus, CString& strAlarmStatus)
{
	CString strGpsStatus = _T("");
	if (BIT_GET(sStatus, 0)) 
	{
		strGpsStatus = LOADSTRINGEX(ID_STR_CMS_GPS_VALID);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += ",";
		}
		strNormalStatus += strGpsStatus;
	}
	else
	{
		strGpsStatus = LOADSTRINGEX(ID_STR_CMS_GPS_INVALID); 
// 		if (!strAlarmStatus.IsEmpty())
// 		{
// 			strAlarmStatus += ",";
// 		}
	//	strAlarmStatus += strGpsStatus;
		InsertAlarmStatus(GPS_ALARM_TYPE_GPS_UNENABLE, strNormalStatus, strAlarmStatus, strGpsStatus);
	}
}

void GetACCStatus(unsigned int sStatus, int nParkTime, CString& strNormalStatus, CString& strAlarmStatus)
{
	CString strAccStatus = _T("");
	if (((sStatus>>1)&1) >0) 
	{
		if((sStatus>>13)&1 > 0  && nParkTime > 180) 
		{
			strAccStatus += LOADSTRINGEX(ID_STR_DLG_EVENT_RUNINT_ACC_OFF_0);	
		}
		else
		{
			strAccStatus += LOADSTRINGEX(ID_STR_DLG_CMS_STAITSTIC_ACC_ON);
		}
	}
	else if (((sStatus>>1)&1) <=0 )
	{
		strAccStatus += LOADSTRINGEX(ID_STR_DLG_CMS_STAITSTIC_ACC_OFF);
	}
	if (!strNormalStatus.IsEmpty())
	{
		strNormalStatus += ",";
	}
	strNormalStatus += strAccStatus;
}
void GetDirectionStatus(unsigned int sStatus, CString& strNormalStatus, CString& strAlarmStatus)
{
	if (((sStatus>>2)&1) > 0) 
	{
		CString strVehicleStatus = _T("");
		strVehicleStatus += LOADSTRINGEX(ID_STR_CMS_LEFT);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += ",";
		}
		strNormalStatus += strVehicleStatus;
	}
	
	if (((sStatus>>3)&1) > 0)
	{
		CString strVehicleStatus = _T("");
		strVehicleStatus += LOADSTRINGEX(ID_STR_CMS_RIGHT);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += ",";
		}
		strNormalStatus += strVehicleStatus;
	}
	
	if (((sStatus>>4)&1) > 0) 
	{
		CString strVehicleShaChe = _T("");
		strVehicleShaChe+=LOADSTRINGEX(ID_STR_CMS_BRAKE);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += ",";
		}
		strNormalStatus += strVehicleShaChe;
	}
	
	if (((sStatus>>5)&1) > 0) 
	{
		CString strVehicleZZ = ",";
		strVehicleZZ +=LOADSTRINGEX(ID_STR_CMS_POSITIVE);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += ",";
		}
		strNormalStatus += strVehicleZZ;
	}
	
	if (((sStatus>>6)&1) > 0) 
	{
		CString strVchicleFZ = _T("");
		strVchicleFZ +=LOADSTRINGEX(ID_STR_CMS_REVERSE);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += ",";
		}
		strNormalStatus += strVchicleFZ;
	}
}
void GetAntennaStatus(unsigned int sStatus, CString& strNormalStatus, CString& strAlarmStatus)
{
	CString strGpsStatus =  _T("");
	if (((sStatus>>7)&1) > 0) 
	{
		strGpsStatus += LOADSTRINGEX(ID_STR_CMS_GPS_ANTENNA_NORMAL);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += ",";
		}
		strNormalStatus += strGpsStatus;
	}
	else if (((sStatus>>7)&1) <= 0)
	{
		strGpsStatus += LOADSTRINGEX(ID_STR_CMS_GPS_ANTENNA_INVALID);
// 		if (!strAlarmStatus.IsEmpty())
// 		{
// 			strAlarmStatus += ",";
// 		}
//		strAlarmStatus += strGpsStatus;
		InsertAlarmStatus(GPS_ALARM_TYPE_GPS_SIGNAL_LOSS, strNormalStatus, strAlarmStatus, strGpsStatus);
	}
}

void GetHDDStatus(const GPSVehicleGps_S& Gps, CString& strNormalStatus, CString& strAlarmStatus, char cDiskType)
{
	unsigned int sStatus = Gps.uiStatus[0];
	if (!BIT_GET(sStatus, 31))
	{
		CString strDisk;
		if (GPS_DISK_TYPE_HDD == cDiskType)
		{
			strDisk = LOADSTRINGEX(ID_STR_CMS_GPS_DISK);
		}
		else if (GPS_DISK_TYPE_SSD == cDiskType)
		{
			strDisk = LOADSTRINGEX(ID_STR_CMS_GPS_SSD);
		}
		else
		{
			strDisk = LOADSTRINGEX(ID_STR_CMS_GPS_SD);
		}
		
		CString strDiskStatus;
		if (((sStatus>>28)&1) > 0)
		{
			if (((sStatus>>8)&3) == 0)
			{
				strDiskStatus += strDisk;
				if (GPS_DISK_TYPE_HDD != cDiskType)
				{
					strDiskStatus += _T("1");
				}
				strDiskStatus += LOADSTRINGEX(ID_STR_CMS_GPS_NOT_EXIST);
				InsertAlarmStatus(GPS_ALARM_TYPE_DISK1_NO_EXIST, strNormalStatus, strAlarmStatus, strDiskStatus);
			}
			else if (((sStatus>>8)&3) == 1)
			{
				strDiskStatus += strDisk;
				if (GPS_DISK_TYPE_HDD != cDiskType)
				{
					strDiskStatus += _T("1");
				}
				strDiskStatus += LOADSTRINGEX(ID_STR_CMS_GPS_EXIST);
				if (!strNormalStatus.IsEmpty())
				{
					strNormalStatus += _T(",");
				}
				strNormalStatus += strDiskStatus;
			}
			else if (((sStatus>>8)&3) == 2)
			{
				strDiskStatus += strDisk;
				if (GPS_DISK_TYPE_HDD != cDiskType)
				{
					strDiskStatus += _T("1");
				}
				strDiskStatus += LOADSTRINGEX(ID_STR_CMS_GPS_DISCONNECT_POWER);	
				InsertAlarmStatus(GPS_ALARM_TYPE_DISK1_NO_EXIST, strNormalStatus, strAlarmStatus, strDiskStatus);
			}

			if (GPS_DISK_TYPE_HDD == cDiskType)
			{
				strDisk = LOADSTRINGEX(ID_STR_CMS_GPS_SD);
			}
			
			strDiskStatus.Empty();
			if (((sStatus>>29)&3) == 0)
			{
				strDiskStatus += strDisk;
				if (GPS_DISK_TYPE_HDD != cDiskType)
				{
					strDiskStatus += _T("2");
				}
				strDiskStatus += LOADSTRINGEX(ID_STR_CMS_GPS_NOT_EXIST);
				InsertAlarmStatus(GPS_ALARM_TYPE_DISK2_NO_EXIST, strNormalStatus, strAlarmStatus, strDiskStatus);
			}
			else if (((sStatus>>29)&3) == 1)
			{
				strDiskStatus += strDisk;
				if (GPS_DISK_TYPE_HDD != cDiskType)
				{
					strDiskStatus += _T("2");
				}
				strDiskStatus += LOADSTRINGEX(ID_STR_CMS_GPS_EXIST);
				strNormalStatus += _T(",");
				strNormalStatus += strDiskStatus;
			}
			else if (((sStatus>>29)&3) == 2)
			{
				strDiskStatus += strDisk;
				if (GPS_DISK_TYPE_HDD != cDiskType)
				{
					strDiskStatus += _T("2");
				}
				strDiskStatus += LOADSTRINGEX(ID_STR_CMS_GPS_DISCONNECT_POWER);
				InsertAlarmStatus(GPS_ALARM_TYPE_DISK2_NO_EXIST, strNormalStatus, strAlarmStatus, strDiskStatus);
			}
		}
		else
		{
			if (((sStatus>>8)&3) == 0)
			{
				strDiskStatus += strDisk;
				strDiskStatus += LOADSTRINGEX(ID_STR_CMS_GPS_NOT_EXIST);
				InsertAlarmStatus(GPS_ALARM_TYPE_DISK1_NO_EXIST, strNormalStatus, strAlarmStatus, strDiskStatus);
			}
			else if (((sStatus>>8)&3) == 1)
			{
				strDiskStatus += strDisk;
				strDiskStatus += LOADSTRINGEX(ID_STR_CMS_GPS_EXIST);
				strNormalStatus += _T(",");
				strNormalStatus += strDiskStatus;
			}
			else if (((sStatus>>8)&3) == 2)
			{
				strDiskStatus += strDisk;
				strDiskStatus += LOADSTRINGEX(ID_STR_CMS_GPS_DISCONNECT_POWER);	
				InsertAlarmStatus(GPS_ALARM_TYPE_DISK1_NO_EXIST, strNormalStatus, strAlarmStatus, strDiskStatus);
			}
		}
		if ( GPS_VEHICLE_EXTRA_FALG_UAE == Gps.usExtraFlag)
		{
			const MDVRVehicleExtraUAE_S& Uae = reinterpret_cast<const GPSVehicleGpsNew_S*>(&Gps)->Extra.Uae;
			if (Uae.cDisk3Status != 3)
			{
				CString strDisk3Name;
				strDisk3Name = strDisk + _T("3");

				if (Uae.cDisk3Status == 0)
				{
					strDiskStatus.Format(_T("%s(%s)"), strDisk3Name, LOADSTRINGEX(ID_STR_CMS_GPS_NOT_EXIST));
				}
				else if (Uae.cDisk3Status == 1)
				{
					strDiskStatus.Format(_T("%s(%s)"), strDisk3Name, LOADSTRINGEX(ID_STR_CMS_GPS_EXIST));
				}
				else if (Uae.cDisk3Status == 2)
				{
					strDiskStatus.Format(_T("%s%s"), strDisk3Name, LOADSTRINGEX(ID_STR_CMS_GPS_DISCONNECT_POWER));
				}
				InsertAlarmStatus(0, strNormalStatus, strAlarmStatus, strDiskStatus);
			}
			if (Uae.cDisk4Status != 3)
			{
				CString strDisk4Name;
				strDisk4Name = strDisk + _T("4");

				if (Uae.cDisk3Status == 0)
				{
					strDiskStatus.Format(_T("%s(%s)"), strDisk4Name, LOADSTRINGEX(ID_STR_CMS_GPS_NOT_EXIST));
				}
				else if (Uae.cDisk3Status == 1)
				{
					strDiskStatus.Format(_T("%s(%s)"), strDisk4Name, LOADSTRINGEX(ID_STR_CMS_GPS_EXIST));
				}
				else if (Uae.cDisk3Status == 2)
				{
					strDiskStatus.Format(_T("%s%s"), strDisk4Name, LOADSTRINGEX(ID_STR_CMS_GPS_DISCONNECT_POWER));
				}
				InsertAlarmStatus(0, strNormalStatus, strAlarmStatus, strDiskStatus);
			}

		}
	}
}

void Get3GSingal(unsigned int sStatus, CString& strNormalStatus, CString& strAlarmStatus)
{
	CString str3GSingal = _T("");
	if (((sStatus>>10)&7) == 0)
	{
		str3GSingal += LOADSTRINGEX(ID_STR_CMS_3G_SIM_NOT_EXIST);
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += str3GSingal;
	}
	if (((sStatus>>10)&7) == 1)
	{
		str3GSingal += LOADSTRINGEX(ID_STR_CMS_3G_SIGNAL_WEAK);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += _T(",");
		}
		strNormalStatus += str3GSingal;
	}
	if (((sStatus>>10)&7) == 2)
	{
		str3GSingal += LOADSTRINGEX(ID_STR_CMS_3G_SIGNAL_POOR);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += _T(",");
		}
		strNormalStatus += str3GSingal;
	}
	if (((sStatus>>10)&7) == 3)
	{
		str3GSingal += LOADSTRINGEX(ID_STR_CMS_3G_SIGNAL_GENERAL);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += _T(",");
		}
		strNormalStatus += str3GSingal;
	}
	if (((sStatus>>10)&7) == 4)
	{
		str3GSingal += LOADSTRINGEX(ID_STR_CMS_3G_SIGNAL_GOOD);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += _T(",");
		}
		strNormalStatus += str3GSingal;
	}
	if (((sStatus>>10)&7) == 5) 
	{
		str3GSingal += LOADSTRINGEX(ID_STR_CMS_3G_SIGNAL_EXCELLENT);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += _T(",");
		}
		strNormalStatus += str3GSingal;
	}
	if (((sStatus>>10)&7) == 6) 
	{
		str3GSingal += LOADSTRINGEX(ID_STR_CMS_3G_NOT_EXIST);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += _T(",");
		}
		strNormalStatus += str3GSingal;
	}
	if (((sStatus>>10)&7) == 7) 
	{
		str3GSingal += LOADSTRINGEX(ID_STR_CMS_3G_SIGNAL_CLOSE);
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += _T(",");
		}
		strNormalStatus += str3GSingal;
	}
}
void GetSpeedStatus(unsigned int sStatus, int nParkTime, CString& strNormalStatus, CString& strAlarmStatus)
{
	if((sStatus>>13)&1 > 0)  
	{
		CString strVehicleStatus;
		int nHour = 0;
		int nMinute = 0;
		int nSecond = 0;
		
		nHour = nParkTime/3600;                            
		nMinute = (nParkTime - nHour*3600)/60;             
		nSecond = nParkTime - nHour*3600 - nMinute*60;     
		
		CString strTimeTip;
		if (nHour > 0)
		{
			strTimeTip.Format(LOADSTRINGEX(ID_STR_CMS_SFM_TIP),nHour,nMinute,nSecond);
		}
		else if (nHour <= 0)
		{
			if (nMinute > 0)
			{
				strTimeTip.Format(LOADSTRINGEX(ID_STR_CMS_FM_TIP),nMinute,nSecond);
			}
			else if (nMinute <= 0)
			{
				strTimeTip.Format(LOADSTRINGEX(ID_STR_CMS_M_TIP),nSecond);
			}
		}		
		
		strVehicleStatus += LOADSTRINGEX(ID_STR_CMS_DEVICE_STATIC);
		strVehicleStatus += strTimeTip;
		
		if (!strNormalStatus.IsEmpty())
		{
			strNormalStatus += _T(",");
		}
		strNormalStatus += strVehicleStatus;
	}
	else if ((sStatus>>14)&1 > 0) 
	{
		CString strVehicleOverSpeed = _T("");
		strVehicleOverSpeed += LOADSTRINGEX(ID_STR_CMS_DEVICE_OVER_SPEED);
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += strVehicleOverSpeed;
	}
}
void GetMapFenceStatus(unsigned int sStatus, CString& strAlarmStatus)
{
	if (BIT_GET(sStatus, 0))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_IN_FENCE);
	}
	else if (BIT_GET(sStatus, 1))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_OUT_FENCE);
	}

	if (BIT_GET(sStatus, 2))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN_OVER_SPEED);
	}
	else if (BIT_GET(sStatus, 3))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN_LOWE_SPEED);
	}
	else if (BIT_GET(sStatus, 4))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT_OVER_SPEED);
	}
	else if (BIT_GET(sStatus, 5))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT_LOWE_SPEED);
	}

	if (BIT_GET(sStatus, 6))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_IN_STOP);
	}
	else if (BIT_GET(sStatus, 7))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FENCE_OUT_STOP);
	}
}
CString GetTemperatureUnit(int nUnit)
{
	CString strUnit;

	switch (nUnit)
	{
	case 0:				strUnit = _T("¡æ");				break;
	case 1:				//strUnit = _T("%");				break;
	case 2:				strUnit = _T("%");				break;
	default:
		break;
	}
	return strUnit;
}

void FormatTemperatureInfo(const GPSVehicleGps_S& Gps, CVehicleBase* pVehi, CString& strNormalStatus)
{
	CString str, strTmp;
	CString strUnit;
	if (pVehi)
	{
		
		int nTempNum = pVehi->GetDeviceInfo()->gDVRInfo.ucTempSensorNum;
		float sCoachTemp = 0.0; 
		for (int i = 0; i < nTempNum; ++i)
		{
			if (i < 4)
			{
				str += pVehi->GetDeviceInfo()->gDVRInfo.szTempSensorName[i];
				str += _T(":");
				sCoachTemp = Gps.sTempSensor[i]/10.0;
			}
			else if (Gps.usExtraFlag == GPS_VEHICLE_EXTRA_FALG_UAE)
			{
				if (i == 4)
				{
					str += pVehi->GetDeviceInfo()->gDVRInfo.szTempSensorNameEx[0];
					str += _T(":");
					int nValue = reinterpret_cast<const GPSVehicleGpsNew_S*>(&Gps)->Extra.Uae.sSensor1;
					sCoachTemp = nValue/10.0;
				}
				else if (i == 5)
				{
					str += pVehi->GetDeviceInfo()->gDVRInfo.szTempSensorNameEx[1];
					str += _T(":");
					int nValue = reinterpret_cast<const GPSVehicleGpsNew_S*>(&Gps)->Extra.Uae.sSensor2;
					sCoachTemp = nValue/10.0;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}

			strUnit = GetTemperatureUnit(pVehi->GetDeviceInfo()->gDVRInfo.cSensorType[i]);

//			strTmp.Format("%g%s", sCoachTemp, LOADSTRINGEX(ID_STR_DLG_TRACK_TEMPER_SYMBOL));
			strTmp.Format(_T("%.1lf%s"), sCoachTemp, strUnit);

			str += strTmp;
			str += _T(" ");
		}
	}
	if (!strNormalStatus.IsEmpty() && !str.IsEmpty())
	{
		strNormalStatus += _T(",");
	}
	strNormalStatus += str;
}

void FormatFlowStatus(unsigned int sStatus, CString& strAlarmStatus)
{
	if (BIT_GET(sStatus, 9))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FLOW_DAY_OVER);
	}
	else if (BIT_GET(sStatus, 8))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FLOW_DAY_REMIND);
	}

	if (BIT_GET(sStatus, 11))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FLOW_MONTH_OVER);
	}
	else if (BIT_GET(sStatus, 10))
	{
		if (!strAlarmStatus.IsEmpty())
		{
			strAlarmStatus += _T(",");
		}
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_FLOW_MONTH_REMIND);
	}
}
void GetPowerDownStatus(unsigned int sStatus, CString& strAlarmStatus)
{
	if (BIT_GET(sStatus, 12))
	{
		AddSeparator(strAlarmStatus);
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_POWER_DOWN);
	}
}
void GetCarDoorStatus(unsigned int sStatus, CString& strAlarmStatus)
{
	if (BIT_GET(sStatus, 13))
	{
		AddSeparator(strAlarmStatus);
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_DOOR_OPEN);
	}
}
void GetCarZoneStatus(unsigned int sStatus, CString& strAlarmStatus)
{
	if (BIT_GET(sStatus, 14))
	{
		AddSeparator(strAlarmStatus);
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_ZONE_OPEN);
	}
}
void GetCarBatteryStatus(unsigned int sStatus, CString& strAlarmStatus)
{
	if (BIT_GET(sStatus, 16))
	{
		AddSeparator(strAlarmStatus);
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_BATTERY_BAD);
	}
	else if(BIT_GET(sStatus, 15))
	{
		AddSeparator(strAlarmStatus);
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_LOW_BATTERY_VOLTAGE);
	}
}
void GetCarEngineStatus(unsigned int sStatus, CString& strAlarmStatus)
{
	if (BIT_GET(sStatus, 17))
	{
		AddSeparator(strAlarmStatus);
		strAlarmStatus += LOADSTRINGEX(ID_STR_ALARM_TYPE_ENGINE_BAD);
	}
}
void FormatMDVRStatus2Str(const GPSVehicleGps_S& Gps, CDevBase* pDevice, CString& strNormalStatus, CString& strAlarmStatus)
{
	unsigned int sStatus = Gps.uiStatus[0];
	GetGPSStatus(sStatus, strNormalStatus, strAlarmStatus);
	if (pDevice->GetDevType() == GPS_DEV_TYPE_MDVR)
	{
		GetACCStatus(sStatus, Gps.nParkTime, strNormalStatus, strAlarmStatus);
		GetSpeedStatus(sStatus, Gps.nParkTime, strNormalStatus, strAlarmStatus);
	}
	GetDirectionStatus(sStatus, strNormalStatus, strAlarmStatus);
	GetAntennaStatus(sStatus, strNormalStatus, strAlarmStatus);
	GetHDDStatus(Gps, strNormalStatus, strAlarmStatus, pDevice->GetDeviceInfo()->cDiskType);
	Get3GSingal(sStatus, strNormalStatus, strAlarmStatus);
	GetMapFenceStatus(Gps.uiStatus[1], strAlarmStatus);
	FormatFlowStatus(Gps.uiStatus[1], strAlarmStatus);
	if (pDevice->GetDevType() == GPS_DEV_TYPE_MDVR)
	{
		CVDvsDevice* pDev = (CVDvsDevice*)pDevice;
		CVehicleBase* pVehi = CVehicleBaseMgr::GetInstance()->FindVechicleFromDevID(pDev->GetID());
		FormatTemperatureInfo(Gps, pVehi, strNormalStatus);

		GetPowerDownStatus(Gps.uiStatus[1], strAlarmStatus);
		GetCarDoorStatus(Gps.uiStatus[1], strAlarmStatus);
		GetCarZoneStatus(Gps.uiStatus[1], strAlarmStatus);
		GetCarBatteryStatus(Gps.uiStatus[1], strAlarmStatus);
		GetCarEngineStatus(Gps.uiStatus[1], strAlarmStatus);
	}
}
void FormatMobileStatus2Str(const GPSVehicleGps_S& Gps, CDevMoblie* pDevice, CString& strNormalStatus, CString& strAlarmStatus)
{
	
}

void FormatStatus2String(const GPSVehicleGps_S& Gps, CDevBase* pDevice, CString& strNormalStatus, CString& strAlarmStatus)
{
// 	if (pDevice->GetDevType() == GPS_DEV_TYPE_MDVR)
	{
		FormatMDVRStatus2Str(Gps, pDevice, strNormalStatus, strAlarmStatus);
	}
// 	else if (pDevice->GetDevType() == GPS_DEV_TYPE_MOBILE)
// 	{
// 		FormatMobileStatus2Str(Gps, (CDevMoblie*)pDevice, strNormalStatus, strAlarmStatus);
// 	}
}

void FormatProStatus(CString& strVehicleStaus, const CString& strPro, const CString& strProStatus)
{
	CString strHtmlBegin = _T("<span class ='b'>");
	CString strHtmlEnd = _T("</span>");
	CString strHuanHang = _T("<br/>");
	CString strHongGr = _T("");  
	CString strDH = _T(",");
	CString strMH = _T(":");

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += strPro;
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += strProStatus;
	strVehicleStaus += strHuanHang;
}

CString GetMDVRRunningStatus(const GPSVehicleGps_S& Gps, CVDvsDevice* pDevice, BOOL bIsTrackBack, float fCurCountLicheng)
{
	CString strVehicleStaus = _T("");
	CString strHtmlBegin = _T("<span class ='b'>");
	CString strHtmlEnd = _T("</span>");
	CString strHuanHang = _T("<br/>");
	CString strHongGr = _T("");  
	CString strDH = _T(",");
	CString strMH = _T(":");
	
	FormatProStatus(strVehicleStaus, LOADSTRINGEX(ID_STR_DLG_VIEW_MGR_LIST_POLL_TIME), FormatGpsTimeEx(Vonvert2SystemTime(Gps.Time)));
	
	//2¡¢Àï³Ì
	CString strLiCheng;
	if (bIsTrackBack)
	{
		strLiCheng.Format(_T("%s/%s"), FormatLiCheng2String(fCurCountLicheng, FALSE), FormatLiCheng2String(Gps));
	}
	else
	{
		strLiCheng = FormatLiCheng2String(Gps);
	}
	FormatProStatus(strVehicleStaus, LOADSTRINGEX(ID_STR_DLG_TRACK_LICHENG), strLiCheng);
	
	FormatProStatus(strVehicleStaus, LOADSTRINGEX(ID_STR_DLG_EVENT_LST_REAL_SPEED), FormatGpsSpeedAndDirection(Gps));

	
	if (pDevice->IsExistModuleOilSen())
	{
		FormatProStatus(strVehicleStaus, LOADSTRINGEX(ID_STR_DLG_TRACK_YOULIANG), FormatYouliang2String(Gps.uiYouLiang));
	}
#ifdef VERSIONS_ANSHI
	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += "ANSHI";
	strVehicleStaus += strMH;
	
	//	strVehicleStaus += strDriverName;
	strVehicleStaus += strHuanHang;
	
#endif

	if (pDevice->IsExistMoudleCountPeople())
	{
		if (GPS_VEHICLE_EXTRA_FALG_BUSODB == Gps.usExtraFlag
			|| GPS_VEHICLE_EXTRA_FALG_UAE == Gps.usExtraFlag)
		{
			CString strPeople;
			strPeople.Format(_T("%d"), Gps.uiPeopleCur);
			FormatProStatus(strVehicleStaus, _T("People:"), strPeople);
		}
	}
	
	CString strDriverName =pDevice->GetDevInfo()->szDriverName;
	if (!strDriverName.IsEmpty())
	{
		CString strTel = pDevice->GetDevInfo()->szDriverTele;
		if (!strTel.IsEmpty())
		{
			CString strTelPhone;
			strTelPhone.Format(_T("(%s)"),strTel);
			strDriverName += strTelPhone;			
		}
	}
	FormatProStatus(strVehicleStaus, LOADSTRINGEX(ID_STR_DLG_BCAST_DRIVER_NAME), strDriverName);

	CString str;
	if(bIsTrackBack || pDevice->GetGPSAddress().IsEmpty())
	{
		str = FormatGPSToStr(Gps);
	}
	else
	{
		str = pDevice->GetGPSAddress();
	}
	FormatProStatus(strVehicleStaus, LOADSTRINGEX(ID_STR_POSITION), str);
	
	
	CString strNormalStatus, strAlarmStatus;
	FormatStatus2String(Gps, pDevice, strNormalStatus, strAlarmStatus);
	
	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_DLG_BCAST_ALARM_STATUS);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += _T("<font color=#ff0000>");
	int nFirst = 0;
	int nSecond = 0;
	int nIndex = 40;
	while(nFirst != -1)
	{
		nSecond = strAlarmStatus.Find(_T(','), nFirst);
		if (nSecond == -1)
		{
			break;
		}
		if (nSecond > nIndex)
		{
			strAlarmStatus.Insert(nSecond+1, strHuanHang);
			nIndex = nSecond + 41;
		}
		nFirst = nSecond+1;
	}

	strVehicleStaus += strAlarmStatus;
	strVehicleStaus += _T("</font>");
	strVehicleStaus += strHuanHang;
	
	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_DLG_REC_SEARCH_LST_DOWN_STATUS);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;

	nFirst = 0;
	nSecond = 0;
	nIndex = 40;

	while(nFirst != -1)
	{
		nSecond = strNormalStatus.Find(_T(','), nFirst);
		if (nSecond == -1)
		{
			break;
		}
		if (nSecond > nIndex)
		{
			strNormalStatus.Insert(nSecond+1, strHuanHang);
			nIndex = nSecond + 41;
		}
		nFirst = nSecond+1;
	}
	
 	strVehicleStaus += strNormalStatus;
 	strVehicleStaus +=strHuanHang;
	
	return strVehicleStaus;
}
CString GetMoblieRunningStatus(const GPSVehicleGps_S& Gps, CDevMoblie* pDevice, BOOL bIsTrackBack)
{
	CString strVehicleStaus = _T("");
	CString strHtmlBegin = _T("<span class ='b'>");
	CString strHtmlEnd = _T("</span>");
	CString strHuanHang = _T("<br/>");
	CString strHongGr = _T("");
	CString strDH = _T(",");
	CString strMH = _T(":");

	strVehicleStaus = strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_DLG_VIEW_MGR_LIST_POLL_TIME);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += FormatGpsTimeEx(Vonvert2SystemTime(Gps.Time));
	strVehicleStaus += strHuanHang;

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_POSITION);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	if(bIsTrackBack || pDevice->GetGPSAddress().IsEmpty())
	{
		strVehicleStaus += FormatGPSToStr(Gps);
	}
	else
	{
		strVehicleStaus += pDevice->GetGPSAddress();
	}
 	strVehicleStaus += strHuanHang;

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_MOBILE_DEV_SEX);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += pDevice->GetSexStr();
	strVehicleStaus += strHuanHang;

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_MOBILE_DEV_ID_CAR);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += pDevice->GetIDCar();
	strVehicleStaus += strHuanHang;

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_MOBILE_DEV_USER_NUM);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += pDevice->GetUserNum();
	strVehicleStaus += strHuanHang;

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_MOBILE_DEV_POST);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += pDevice->GetPostStr();
	strVehicleStaus += strHuanHang;

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_MOBILE_DEV_EQUIP);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += pDevice->GetEquipStr();
	strVehicleStaus += strHuanHang;

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_DLG_DEVINFO_ST_PHONE);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += pDevice->GetSIMCar();
	strVehicleStaus += strHuanHang;

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_MOBILE_DEV_ADDRESS);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	strVehicleStaus += pDevice->GetAddress();
	strVehicleStaus += strHuanHang;

	strVehicleStaus += strHtmlBegin;
	strVehicleStaus += LOADSTRINGEX(ID_STR_DLG_DEVINFO_ST_REMARK);
	strVehicleStaus += strMH;
	strVehicleStaus += strHtmlEnd;
	//strVehicleStaus += pDevice->GetRemark();
	strVehicleStaus += strHuanHang;

	return strVehicleStaus;
}

CString GetVehicleRunningStaus(const GPSVehicleGps_S& Gps, CDevBase* pDevice, BOOL bIsTrackBack, float fCurCountLicheng)
{
	CString str;
	if (pDevice->GetDevType() == GPS_DEV_TYPE_MDVR)
	{
		str = GetMDVRRunningStatus(Gps, (CVDvsDevice*)pDevice, bIsTrackBack, fCurCountLicheng);
	}
	else if (pDevice->GetDevType() == GPS_DEV_TYPE_MOBILE)
	{
		str = GetMoblieRunningStatus(Gps, (CDevMoblie*)pDevice, bIsTrackBack);
	}
	return str;
}

int GetDevStatusNoOnline(const GPSVehicleGps_S* pGPS, BOOL bAlarm)
{
// 	int nCarState = LIST_ITEM_CAR_STATE_ONLINE;
// 	if (!bAlarm)
// 	{
// 		nCarState = LIST_ITEM_CAR_STATE_ALARM;
// 	}
// 	else
// 	{
// 		unsigned int sStatus = pGPS->uiStatus[0];
// 		if (((sStatus>>1)&1) >0)
// 		{
// 			if((sStatus>>13)&1 > 0  && pGPS->nParkTime > 180)
// 			{
// 				nCarState = LIST_ITEM_CAR_STATE_CONFIRMED_WARNING;	
// 			}
// 		}
// 	}
// 	return nCarState;
	return 0;
}

int GetDevStatus(const GPSVehicleGps_S* pGPS, BOOL bAlarm, CDevBase* pDevice)
{
// 	int nCarState = LIST_ITEM_CAR_STATE_ONLINE;
// 	if (!pDevice->GetOnline())
// 	{
// 		nCarState = LIST_ITEM_CAR_STATE_OFFLINE;
// 	}
// 	else
// 	{
// 		nCarState = GetDevStatusNoOnline(pGPS, bAlarm);
// 	}
// 	return nCarState;
	return 0;

}
CString GetMDVROtherStatus(CVDvsDevice* pDev, GPSVehicleGps_S& Gps)
{
	CString strDriverInfo, strDriverTel;
	CString strDriverName =pDev->GetDevInfo()->szDriverName;
	if (!strDriverName.IsEmpty())
	{
		CString strTel = pDev->GetDevInfo()->szDriverTele;
		if (!strTel.IsEmpty())
		{
			CString strTelPhone;
			strTelPhone.Format(_T("(%s)"),strTel);
			strDriverName += strTelPhone;			
		}
	}
	
	CString strOther;
	strOther += strDriverName;
	CString strLiCheng = FormatLiCheng2String(Gps);
	if (!strOther.IsEmpty() && !strLiCheng.IsEmpty())
	{
		strOther += _T(",");
	}
	strOther += strLiCheng;
	CString strYouliang;
	if (pDev->IsExistModuleOilSen())
	{
		strYouliang = FormatYouliang2String(Gps.uiYouLiang);
		if (!strOther.IsEmpty() && !strYouliang.IsEmpty())
		{
			strOther += _T(",");
		}
		strOther += strYouliang;
	}

	return strOther;
}

CString GetMoblieOtherStatus(CDevMoblie* pDev)
{
	CString strOther;
	return strOther;
}
CString FormatDevOtherStatus(CDevBase* pDev, GPSVehicleGps_S& Gps)
{
	CString str;
	if (pDev->GetDevType() == GPS_DEV_TYPE_MDVR)
	{
		str = GetMDVROtherStatus((CVDvsDevice*)pDev, Gps);
	}
	else if (pDev->GetDevType() == GPS_DEV_TYPE_MOBILE)
	{
		str = GetMoblieOtherStatus((CDevMoblie*)pDev);
	}
	return str;
}