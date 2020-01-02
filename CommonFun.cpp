#include "stdafx.h"
#include "VDvsDevice.h"


BOOL g_bPreviewAutoRecord = FALSE;

CString FormatTime2String(const SYSTEMTIME& sysTime)
{
	CString str;
	str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay
		, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	return str;
}
// BOOL IsValidGPS(const GPSVehicleGps_S& gps)
// {
// 	return BIT_GET(gps.uiStatus[0], 0);
// }

CString FormatGPSToStr(const GPSVehicleGps_S& gps)
{
	CString str;
	if (IsValidGPS(gps))
	{
		if (!GetLang(gps).IsEmpty() && !GetLat(gps).IsEmpty())
		{
			str += GetLang(gps);
			str += _T(", ");
			str += GetLat(gps);
		}
	}
	else
	{
		str = _T("INVALID");
	}

	return str;
}

CString GetLang(const GPSVehicleGps_S& gps)
{
	CString strLang;
	if (BIT_GET(gps.uiStatus[0], 0))
	{
		strLang = GetLang(gps.nJingDu);
	}
	return strLang;
}
CString GetLat(const GPSVehicleGps_S& gps)
{
	CString strLat;
	if (BIT_GET(gps.uiStatus[0], 0))
	{
		strLat = GetLat(gps.nWeiDu);
	}
	return strLat;

}

CString GetLang(const int& nLang)
{
	CString strLang;
	strLang.Format(_T("%f"), nLang/UNIT_COUNT);
	return strLang;
}
CString GetLat(const int& nLat)
{
	CString strLat;
	strLat.Format(_T("%f"), nLat/UNIT_COUNT);
	return strLat;
}

// BOOL FormatGpsValue(GPSVehicleGps_S& Gps, CString& strLang, CString& strLat)
// {
// 	if ((Gps.uiStatus[0]&0x01))
// 	{
// 		strLang.Format("%f", Gps.nJingDu/UNIT_COUNT);
// 		strLat.Format("%f", Gps.nWeiDu/UNIT_COUNT);
// 		return TRUE;
// 	}
// 	else
// 	{
// 		return FALSE;
// 	}
// }

int	GetGpsDirection(int nDirection)
{
	return ((nDirection + 22) / 45 ) & 0x7;
}

CString FormatGpsDirection(int nDirection)
{
	CString str;
	switch( GetGpsDirection(nDirection) )
	{
	case 0:
		str = _T("NORTH");
		break;
	case 1:
		str = _T("NORTH_EAST");
		break;
	case 2:
		str = _T("EAST");
		break;
	case 3:
		str = _T("SOUTH_EAST");
		break;
	case 4:
		str = _T("SOUTH");
		break;
	case 5:
		str = _T("SOUTH_WEST");
		break;
	case 6:
		str = _T("WEST");
		break;
	case 7:
		str = _T("NORTH_WEST");
		break;
	default:
		break;
	}
	return str;
}

CString FormatGpsTime(SYSTEMTIME tm)
{
	CString str;
	str.Format(_T("%02d/%02d/%02d:%02d:%02d"), tm.wMonth, tm.wDay,
			tm.wHour, tm.wMinute, tm.wSecond);
	return str;
}

CString FormatGpsTimeEx(SYSTEMTIME tm)
{
	CString str;
	str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),tm.wYear,tm.wMonth, tm.wDay,tm.wHour, tm.wMinute, tm.wSecond);
	return str;
}


SYSTEMTIME Vonvert2SystemTime(const GPSTime_S& tm)
{
	SYSTEMTIME tm1;
	tm1.wYear = tm.ucYear+2000 ;
	tm1.wMonth = tm.ucMonth;
	tm1.wDay = tm.ucDay;
	tm1.wHour = tm.ucHour;
	tm1.wMinute = tm.ucMinute;
	tm1.wSecond = tm.ucSecond;

	return tm1;
}

int CompareData(const UINT& n1, const UINT& n2)
{
	int nRet = 0;
	if (n1 > n2)
	{
		nRet = 1;
	}
	else if (n1 < n2)
	{
		nRet = -1;
	}
	return nRet;
}

int CompareGPSTimeEx(const GPSTime_S& tm1, const GPSTime_S& tm2)
{
	int nRet = 0;
	UINT szTime1[6] = {tm1.ucYear, tm1.ucMonth, tm1.ucDay, tm1.ucHour, tm1.ucMinute, tm1.ucSecond};
	UINT szTime2[6] = {tm2.ucYear, tm2.ucMonth, tm2.ucDay, tm2.ucHour, tm2.ucMinute, tm2.ucSecond};
	for (int i = 0; i < 6; ++i)
	{
		nRet = CompareData(szTime1[i], szTime2[i]);
		if (nRet)
		{
			break;
		}
	}
	return nRet;
}

CString GetVRKey(int nDevID, int nChn, BOOL bMainStream)
{
	TCHAR szKey[64] = {0};
	_stprintf(szKey, _T("%d-%d-%d"), nDevID, nChn, bMainStream);
	return szKey;
}

// void FormatKeyToValue(const CString& strKey, int& nDevID, int& nChannel, BOOL& bMainStream)
// {
// 	char *str = (LPSTR)(LPCTSTR)strKey;
// 	char *pToken = strtok(str, "-");
// 	if (pToken)
// 	{
// 		nDevID = atoi(pToken);
// 		pToken = strtok(NULL, "-");
// 		if (pToken)
// 		{
// 			nChannel = atoi((pToken));
// 			pToken = strtok(NULL, "-");
// 			if (pToken)
// 			{
// 				bMainStream = atoi(pToken);
// 			}
// 		}
// 	}
// }
void SplitStringToInt(CString str, const char* strSeps, DWORD* pData)
{
	int nIndex = 0;
	char szBuf[1024] = {0};
	strcpy(szBuf, CStringA(str));
	char *pToken = strtok(szBuf, strSeps);
	while(pToken)
	{
		pData[nIndex] = atoi(pToken);
		pToken = strtok(NULL, ("-"));
		++nIndex;
	}
}

//Down File Function
BOOL GetDevAndChnName(const char* szDevIDNO, int nChn, CString& strID, CString& strDev, CString& strChn)
{
	CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvsDeviceByIDNO(szDevIDNO);
	if (pDevice)
	{
		strDev = pDevice->GetShowName();
		strChn = pDevice->GetChnName(nChn);
		strID = pDevice->GetDevIDNO();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CString GetFileName(CString strFilePath)
{
	CString strTemp =  strFilePath;
	int nPos = strTemp.ReverseFind(_T('\\'));
	if (nPos != -1)
	{
		strTemp = strTemp.Right(strTemp.GetLength() - nPos - 1);
	}
	else
	{
		nPos = strTemp.ReverseFind('/');
		strTemp = strTemp.Right(strTemp.GetLength() - nPos - 1);
	}
	strTemp.Replace(_T('\\'), _T('-'));
	strTemp.Replace(_T(':'), _T('-'));
	
	return strTemp;
}

BOOL IsFileEixt(CString strFilePath, DWORD& dwFileLen)
{
	CFileStatus rStatus;
	dwFileLen = 0;
	if (CFile::GetStatus(strFilePath, rStatus))
	{
		BOOL bRemove = FALSE;
		CFile file;
		if (file.Open(strFilePath, CFile::modeRead))
		{
			dwFileLen = file.GetLength();
			file.Close();
		}
		return TRUE;
	}

	return FALSE;
}




CString FormatLiCheng2String(const GPSVehicleGps_S& Gps)  
{
	CString str;
	float fLiCheng = 0.0;
//	if (CConfigGViewerINI::GetInstance()->GetDevSpeedUnit() == SPEED_TYPE_MILE)     //mp
	{
		fLiCheng = (Gps.uiLiCheng/1000.0)/1.6093;
		str.Format(_T("%0.2f %s"),fLiCheng, _T("mp"));
	}
// 	else
// 	{
// 		fLiCheng = (Gps.uiLiCheng)/1000.0;
// 		str.Format("%0.2f %s", fLiCheng,"km");
// 		
// 	}
	return str;
}

CString FormatLiCheng2String(float fLiCheng, BOOL bUnit)
{
	CString str;
	float fLiChengDir = 0.0;
//	if (CConfigGViewerINI::GetInstance()->GetDevSpeedUnit() == SPEED_TYPE_MILE)     //mp
	{		
		fLiChengDir = fLiCheng/1.6093;
		str.Format(_T("%0.2f"),fLiChengDir);
		if (bUnit)
		{
			str += _T(" mp");
		}
	}
// 	else
// 	{
// 		str.Format("%0.2f", fLiCheng);
// 		if (bUnit)
// 		{
// 			str += " km";
// 		}
// 	}

	return str;
}

CString FormatYouliang2String(const UINT& uiYouLiang)
{
	CString str;
	float fYouliang = uiYouLiang/100.0;
	str.Format(_T("%0.2f %s"), fYouliang, _T("L"));

	return str;
}

CString FomatSpeedToString(float fSpeed)
{
	CString str;
	
//	if (CConfigGViewerINI::GetInstance()->GetDevSpeedUnit() == SPEED_TYPE_MILE) 
	{
		fSpeed = fSpeed/1.6093;
		str.Format(_T("%0.2f %s"),fSpeed, _T("mp/h"));
	}
// 	else
// 	{
// 		str.Format("%0.2f %s", fSpeed,"km/h");
// 		
//	}
	return str;
}

CString FormatDirection2String(const GPSVehicleGps_S& Gps)  
{
	CString strDir;
	if ((Gps.uiStatus[0]>>0)&1 > 0)
	{
		strDir = FormatGpsDirection(Gps.uiHangXiang) ;
	}
	else
	{
		strDir = "INVALID";
	}
	
	return strDir;
}
CString	FormatGpsSpeedAndDirection(const GPSVehicleGps_S& Gps)
{
	CString str;
	CString strSpeed;
// 	if (CConfigGViewerINI::GetInstance()->GetDevSpeedUnit() == SPEED_TYPE_MILE)  
	{		
		float fMile = Gps.uiSpeed / 10 / 1.6093;
		strSpeed.Format(_T("%0.2f mp/h"),fMile);
	}
// 	else
// 	{
// 		strSpeed.Format("%0.2f km/h", Gps.uiSpeed/10.0);
// 	}
	
	str.Format(_T("%s(%s)"), strSpeed, FormatDirection2String(Gps));
	return str;
}

CString FormatSpeed2String(GPSVehicleGps_S& Gps)  
{
	CString str;
	
// 	if (CConfigGViewerINI::GetInstance()->GetDevSpeedUnit() == SPEED_TYPE_MILE) 
	{
		float fMile = 0.0;
		fMile = (Gps.uiSpeed/10.0)/1.6093;
		str.Format(_T("%0.2f %s"),fMile,_T("mp/h"));
	}
// 	else
// 	{
// 		float fMile = 0.0;
// 		fMile = Gps.uiSpeed/10.0;
// 		str.Format("%0.2f %s", fMile,"km/h");
// 		
// 	}
	return str;
}

// void ResizeListCtrl(CListCtrl& lst, int nIndex)
// {
// 	CRect rcClient;
// 	lst.GetClientRect(&rcClient);
// 	int nTotalLen = 0;
// 	for (int i = 0; i < nIndex; ++ i)
// 	{
// 		nTotalLen += lst.GetColumnWidth(i);
// 	}
// 	nTotalLen = (rcClient.right - rcClient.left) - nTotalLen;
// 	if (nTotalLen > lst.GetColumnWidth(nIndex))
// 	{
// 		lst.SetColumnWidth(nIndex, nTotalLen);
// 	}
// }

void ParseString(const char* szSrc, char cSplit, vecString& vecStr)
{
	const char* pTemp = szSrc;
	char* pFind = (char*)strchr(szSrc, cSplit);
	while(pFind != NULL)
	{
		CString str(pTemp, pFind - pTemp);
		vecStr.push_back(str);
		pTemp = pFind + 1;
		pFind = (char*)strchr(pTemp, cSplit);
	}
	if (*pTemp != '\0')
	{
		vecStr.push_back(pTemp);
	}
}



void FixGPS(CString strInLang, CString strInLat, CString& strOutLang, CString& strOuLat)
{
// 	if (CConfigGViewerINI::GetInstance()->GetMapGPSFix() && (CConfigGViewerINI::GetInstance()->GetMapType() == MAP_TYPE_GOOGLE))
// 	{
// 		double dOutLang = 0;
// 		double dOutLat = 0;
// 		MAP_FixGps(atof(strInLang), atof(strInLat), &dOutLang, &dOutLat);
// 		strOutLang.Format("%f", dOutLang);
// 		strOuLat.Format("%f", dOutLat);
// 	}
// 	else
	{
		strOutLang = strInLang;
		strOuLat = strInLat;
	}
}

BOOL IsValidGPS(const GPSVehicleGps_S& gps)
{
	return (BIT_GET(gps.uiStatus[0], 0) && gps.nJingDu != 0 && gps.nWeiDu != 0);
}
BOOL IsValidLastGPS(const GPSVehicleGps_S& gps)
{
	return (BIT_GET(gps.uiStatus[1], 18));
}

void ShiftGpsVehiToGpsDev(GPSVehiDevRelation_S &sGpsDev, const GPSDevInfo_S& sGpsVehi)
{
	USES_CONVERSION;
	sGpsDev.nID = sGpsVehi.nID;
	strncpy(sGpsDev.szVehiIDNO, sGpsVehi.szName, sizeof(sGpsDev.szVehiIDNO));
	strncpy(sGpsDev.szDevIDNO, sGpsVehi.szIDNO, sizeof(sGpsDev.szDevIDNO));
	strncpy(sGpsDev.szSIMCard, sGpsVehi.szSIMCard, sizeof(sGpsDev.szSIMCard));
	CString str=_T("");
	CString strAll = _T("");

	for (int nCh=1; nCh < sGpsVehi.ucChanNum; nCh++)
	{
		str.Format(_T("%d,"), nCh);
		strAll += str;
	}
	if (sGpsVehi.ucChanNum != 0)
	{
		str.Format(_T("%d"),sGpsVehi.ucChanNum);
		strAll += str;
	}
#ifdef _UNICODE
	strncpy(sGpsDev.szChnAttr,T2A(strAll), sizeof(sGpsDev.szChnAttr));
#else
	strncpy(sGpsDev.szChnAttr,strAll.GetBuffer(0), sizeof(sGpsDev.szChnAttr));
#endif
	
	

	for (int nInIO=1; nInIO < sGpsVehi.gDVRInfo.ucIoInNum; nInIO++)
	{
		str.Format(_T("%d,"), nInIO);
		strAll += str;
	}
	if (sGpsVehi.gDVRInfo.ucIoInNum != 0)
	{
		str.Format(_T("%d"),sGpsVehi.gDVRInfo.ucIoInNum);
		strAll += str;
	}
#ifdef _UNICODE
	strncpy(sGpsDev.szIOInAttr, T2A(strAll), sizeof(sGpsDev.szIOInAttr));
	strncpy(sGpsDev.szIOOutAttr, T2A(strAll), sizeof(sGpsDev.szIOOutAttr));
#else
	strncpy(sGpsDev.szIOInAttr, strAll.GetBuffer(0), sizeof(sGpsDev.szIOInAttr));
	strncpy(sGpsDev.szIOOutAttr, strAll.GetBuffer(0), sizeof(sGpsDev.szIOOutAttr));
#endif
	

	for (int nTemp=1; nTemp< sGpsVehi.gDVRInfo.ucTempSensorNum; nTemp++)
	{
		str.Format(_T("%d,"), nTemp);
		strAll += str;
	}
	if (sGpsVehi.gDVRInfo.ucTempSensorNum != 0)
	{
		str.Format(_T("%d"),sGpsVehi.gDVRInfo.ucTempSensorNum);
		strAll += str;
	}
#ifdef _UNICODE
	strncpy(sGpsDev.szTempAttr, T2A(strAll), sizeof(sGpsDev.szTempAttr));
#else
	strncpy(sGpsDev.szTempAttr, strAll.GetBuffer(0), sizeof(sGpsDev.szTempAttr));
#endif
	
	///////////////////////////////////////////
	sGpsDev.nMoudle = sGpsVehi.uiModule;	//Attr 1:Video 2:Capture 3:monitor 4:talkback
	sGpsDev.nDevType = sGpsVehi.nDevType;	//Device Type		MDVR、MOBILE、
	sGpsDev.nDevSubType = sGpsVehi.nDevSubType; 	//Device Chid Type		
	sGpsDev.cProtocol = sGpsVehi.cProtocol;
	sGpsDev.cAudioCodec = sGpsVehi.cAudioCodec;	
	sGpsDev.cDiskType = sGpsVehi.cDiskType;
	sGpsDev.cFactoryType = sGpsVehi.cFactoryType;
	sGpsDev.cFactoryDevType = sGpsVehi.cFactoryDevType;
	sGpsDev.cMainDevFlag = 1;
	sGpsDev.ucMapValid = sGpsVehi.ucMapValid;
	sGpsDev.ucMapType = sGpsVehi.ucMapType;
	sGpsDev.nOnline = sGpsVehi.nOnline;
	sGpsDev.nJingDu = sGpsVehi.nJingDu;				//longitude	4 Byte	9999999 = 9.999999 
	sGpsDev.nWeiDu = sGpsVehi.nWeiDu;				//latitude	4 Byte	9999999 = 9.999999
	sGpsDev.gDVRInfo = sGpsVehi.gDVRInfo;
}

int NetString2Int(const char* pBuf, int nCount)
{
	int nRet = 0;

	int nPre = 1;
	for (int i = nCount - 1; i >= 0; -- i)
	{
		if (pBuf[i] >= '0' && pBuf[i] <= '9')
		{
			nRet += ((pBuf[i] - '0') * nPre);
		}
		nPre *= 10;
	}
	return nRet;
}

BOOL SearchSection2Int(const char* pBuf, const char* pSection, int& nValue)
{
	BOOL bRet = FALSE;
	if (pBuf && pSection)
	{
		const char* pPosB = strstr(pBuf, pSection);
		if (pPosB)
		{
			pPosB += strlen(pSection);
			pPosB += 1;
			const char* pPosE = strchr(pPosB, '"');
			if (pPosE)
			{
				nValue = NetString2Int(pPosB, pPosE-pPosB);
				bRet = TRUE;
			}
		}
	}

	return bRet;
}
//查找的数据不要超过1024
BOOL SearchSection2Str(const char* pBuf, const char* pSection, CString& str)
{
	BOOL bRet = FALSE;
	if (pBuf && pSection)
	{
		const char* pPosB = strstr(pBuf, pSection);
		TRACE("%s\n",pPosB);
		if (pPosB)
		{
			pPosB += strlen(pSection);
			pPosB += 1;
			TRACE("===%s\n",pPosB);
			const char* pPosE = strchr(pPosB, '"');
			int nLen = pPosE-pPosB;
			if (pPosE && nLen>0)
			{
				char* pTmp = new char[nLen+1];
				memset(pTmp, 0, nLen+1);
				strncpy(pTmp, pPosB, nLen);
				str = pTmp;
				delete [] pTmp;
				pTmp = NULL;
				//bRet = TRUE;
			}
			else
			{
				str = _T("");
			}
			bRet = TRUE;
		}
	}

	return bRet;
}