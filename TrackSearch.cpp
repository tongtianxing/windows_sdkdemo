// TrackSearch.cpp: implementation of the CTrackSearch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrackSearch.h"
#include "DlgTrackBack.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrackSearch::CTrackSearch()
{
	m_lVehiTrack = NULL;
	m_pTrackWnd = NULL;
	m_bSearching = FALSE;

	m_strDevIDNO = "";
	memset(&m_BegTime, 0, sizeof(m_BegTime));
	memset(&m_EndTime, 0, sizeof(m_BegTime));
	m_nQueryType = GPS_QUERY_TRACK_TYPE_GPS;
	m_nDistance = 0;
	m_nParkTime = 0;
}

CTrackSearch::~CTrackSearch()
{
	UnInit();
}
void CTrackSearch::SetTrackWnd(CDlgTrackBack* pTrackWnd)
{
	m_pTrackWnd = pTrackWnd;
}
void CTrackSearch::SetSearchInfo(const char* pDevIDNO, const SYSTEMTIME& BegTime, const SYSTEMTIME& EndTime, const int& nDistance, const int& nParkTime, const int& nQueryType)
{
	m_strDevIDNO = pDevIDNO;
	m_BegTime = BegTime;
	m_EndTime = EndTime;
	m_nQueryType = nQueryType;
	m_nDistance = nDistance;
	m_nParkTime = nParkTime;
}
BOOL CTrackSearch::IsSameSearchInfo(const char* pDevIDNO, const SYSTEMTIME& BegTime, const SYSTEMTIME& EndTime, const int& nDistance, const int& nParkTime, const int& nQueryType)
{
	CString strDevIDNO = pDevIDNO;
	if (m_strDevIDNO == strDevIDNO
		&& (0 == TIMECompareTime(BegTime, m_BegTime))
		&& (0 == TIMECompareTime(EndTime, m_EndTime))
		&& m_nDistance == nDistance
		&& m_nParkTime == nParkTime
		&& m_nQueryType == nQueryType)
	{
		return TRUE;
	}

	return FALSE;
}
BOOL CTrackSearch::Init()
{
	if (m_lVehiTrack == NULL)
	{
		NETCLIENT_VTOpenVehiTrack(&m_lVehiTrack);
		NETCLIENT_VTSetVTrackMsgCB(m_lVehiTrack, m_pTrackWnd, FUNVehiTrackMsgCB);
		NETCLIENT_VTSetVTrackDataCB(m_lVehiTrack, m_pTrackWnd, FUNVehiTrackDataCB);		
		NETCLIENT_VTSetVTrackCountCB(m_lVehiTrack, m_pTrackWnd, FUNTrackCountCB);		
	}
	return TRUE;
}
BOOL CTrackSearch::StartSearch()
{
	Init();
	m_bSearching = TRUE;
	m_bSearching = TRUE;
	if (CSvrVer::GetInstance()->IsSvrVerV7())
	{
		char szShowName[MAX_PATH] = {0};
#if defined(_UNICODE) || defined(UNICODE)  
		USES_CONVERSION;
		UcsToUtf8(m_strDevIDNO.GetBuffer(m_strDevIDNO.GetLength()), szShowName, MAX_PATH);
		/*NETCLIENT_VTStartVehiTrack(m_lVehiTrack, W2A(m_strDevIDNO.GetBuffer(0)), &m_BegTime, &m_EndTime, m_nQueryType, m_nDistance, m_nParkTime);*/
#else
		AnsiToUtf8(m_strDevIDNO.GetBuffer(m_strDevIDNO.GetLength()), szShowName, MAX_PATH);
		/*NETCLIENT_VTStartVehiTrack(m_lVehiTrack, m_strDevIDNO.GetBuffer(0), &m_BegTime, &m_EndTime, m_nQueryType, m_nDistance, m_nParkTime);*/
#endif
		NETCLIENT_VTStartVehiTrack(m_lVehiTrack, szShowName, &m_BegTime, &m_EndTime, m_nQueryType, m_nDistance, m_nParkTime);
	}
	else
	{
#if defined(_UNICODE) || defined(UNICODE)  
		USES_CONVERSION;
		NETCLIENT_VTStartVehiTrack(m_lVehiTrack, W2A(m_strDevIDNO.GetBuffer(0)), &m_BegTime, &m_EndTime, m_nQueryType, m_nDistance, m_nParkTime);
#else
		NETCLIENT_VTStartVehiTrack(m_lVehiTrack, m_strDevIDNO.GetBuffer(0), &m_BegTime, &m_EndTime, m_nQueryType, m_nDistance, m_nParkTime);
#endif
	}
	
	return TRUE;
}
BOOL CTrackSearch::IsSearching()
{
	return m_bSearching;
}
BOOL CTrackSearch::StopSearch()
{
	if (m_lVehiTrack)
	{
		NETCLIENT_VTStopVehiTrack(m_lVehiTrack);
		m_bSearching = FALSE;
	}

	return TRUE;
}
BOOL CTrackSearch::UnInit()
{
	NETCLIENT_VTCloseVehiTrack(m_lVehiTrack); 
	m_lVehiTrack = NULL;
	return TRUE;
}

void CTrackSearch::FUNVehiTrackMsgCB(int nMsg, int nParam, void* pUsr)
{
	CDlgTrackBack *pThis = (CDlgTrackBack*)pUsr;
	pThis->DoVehiTrackMsgCB(nMsg, nParam);
}

void CTrackSearch::FUNVehiTrackDataCB(GPSVehicleTrack_S* pVehiRun, void* pUsr)
{
	CDlgTrackBack *pThis = (CDlgTrackBack*)pUsr;
	pThis->DoVehiTrackDateCB(pVehiRun);
}

void CTrackSearch::FUNTrackCountCB(GPSTrackCount_S* pTrackCount, void* pUsr)
{
	CDlgTrackBack *pThis = (CDlgTrackBack*)pUsr;
	pThis->DoTrackCountCB(pTrackCount);
}
