#pragma once


class CDevBase;


void AddSeparator(CString& str, CString strSeparator=_T(","));

void GetMapFenceStatus(unsigned int sStatus, CString& strAlarmStatus);

void FormatStatus2String(const GPSVehicleGps_S& Gps, CDevBase* pDevice, CString& strNormalStatus, CString& strAlarmStatus);

CString GetVehicleRunningStaus(const GPSVehicleGps_S& Gps, CDevBase* pDevice, BOOL bIsTrackBack=FALSE, float fCurCountLicheng=0.0);

int GetDevStatusNoOnline(const GPSVehicleGps_S* pGPS, BOOL bAlarm);

int GetDevStatus(const GPSVehicleGps_S* pGPS, BOOL bAlarm, CDevBase* pDevice);

CString FormatDevOtherStatus(CDevBase* pDev, GPSVehicleGps_S& Gps);

void FormatTemperatureInfo(const GPSVehicleGps_S& Gps, CVehicleBase* pVehi, CString& strNormalStatus);

