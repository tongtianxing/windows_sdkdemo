#ifndef _COMMON_FUN_H_
#define _COMMON_FUN_H_


#define UNIT_COUNT 1000000.0
extern BOOL g_bPreviewAutoRecord ;


CString FormatLiCheng2String(const GPSVehicleGps_S& Gps);  //Get mileage string
CString FormatLiCheng2String(float fLiCheng, BOOL bUnit=TRUE);        //Get mileage string ,with unit or not

CString FormatYouliang2String(const UINT& uiYouLiang);

CString	FormatGpsSpeedAndDirection(const GPSVehicleGps_S& Gps);	//speed and direction
CString FormatSpeed2String(GPSVehicleGps_S& Gps);  //speed
CString FomatSpeedToString(float fSpeed);

CString FormatTime2String(const SYSTEMTIME& sysTime);

//GPS is valid or not
BOOL IsValidGPS(const GPSVehicleGps_S& gps);

CString FormatGPSToStr(const GPSVehicleGps_S& gps);
CString GetLang(const GPSVehicleGps_S& gps);
CString GetLat(const GPSVehicleGps_S& gps);
CString GetLang(const int& nLang);
CString GetLat(const int& nLat);


int		GetGpsDirection(int nDirection);

CString FormatGpsTime(SYSTEMTIME tm);
CString FormatGpsTimeEx(SYSTEMTIME tm);

void SplitStringToInt(CString str, const char* strSeps, DWORD* pData);

SYSTEMTIME Vonvert2SystemTime(const GPSTime_S& tm);
int CompareGPSTimeEx(const GPSTime_S& tm1, const GPSTime_S& tm2);

typedef std::vector<CString> vecString;
void ParseString(const char* szSrc, char cSplit, vecString& vecStr);

void FixGPS(CString strInLang, CString strInLat, CString& strOutLang, CString& strOuLat);
CString GetVRKey(int nDevID, int nChn, BOOL bMainStream);

BOOL IsValidGPS(const GPSVehicleGps_S& gps);
BOOL IsValidLastGPS(const GPSVehicleGps_S& gps);

void ShiftGpsVehiToGpsDev(GPSVehiDevRelation_S &sGpsDev, const GPSDevInfo_S& sGpsVehi);



int NetString2Int(const char* pBuf, int nCount);
BOOL SearchSection2Int(const char* pBuf, const char* pSection, int& nValue);
//查找的数据结果不要超过1024
BOOL SearchSection2Str(const char* pBuf, const char* pSection, CString& str);


#endif


