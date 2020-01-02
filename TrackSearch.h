// TrackSearch.h: interface for the CTrackSearch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACKSEARCH_H__7A3F7003_9E75_47E6_82BD_9995890D4DC6__INCLUDED_)
#define AFX_TRACKSEARCH_H__7A3F7003_9E75_47E6_82BD_9995890D4DC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgTrackBack;
class CTrackSearch  
{
public:
	CTrackSearch();
	virtual ~CTrackSearch();

	void SetTrackWnd(CDlgTrackBack* pTrackWnd);
	void SetSearchInfo(const char* pDevIDNO, const SYSTEMTIME& BegTime, const SYSTEMTIME& EndTime, const int& nDistance, const int& nParkTime, const int& nQueryType = GPS_QUERY_TRACK_TYPE_GPS);
	BOOL IsSameSearchInfo(const char* pDevIDNO, const SYSTEMTIME& BegTime, const SYSTEMTIME& EndTime, const int& nDistance, const int& nParkTime, const int& nQueryType = GPS_QUERY_TRACK_TYPE_GPS);
	BOOL Init();
	BOOL StartSearch();
	BOOL IsSearching();
	BOOL StopSearch();
	BOOL UnInit();

private:
	static void CALLBACK FUNVehiTrackMsgCB(int nMsg, int nParam, void* pUsr);
	static void CALLBACK FUNVehiTrackDataCB(GPSVehicleTrack_S* pVehiTrack, void* pUsr);
	static void CALLBACK FUNTrackCountCB(GPSTrackCount_S* pTrackCount, void* pUsr);

private:
	long m_lVehiTrack;
	BOOL m_bSearching;
	CDlgTrackBack* m_pTrackWnd;

	CString m_strDevIDNO;
	SYSTEMTIME m_BegTime;
	SYSTEMTIME m_EndTime;
	int m_nQueryType;
	int m_nDistance;
	int m_nParkTime;
};

#endif // !defined(AFX_TRACKSEARCH_H__7A3F7003_9E75_47E6_82BD_9995890D4DC6__INCLUDED_)
