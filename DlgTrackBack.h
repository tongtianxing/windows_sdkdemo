#if !defined(AFX_DLGTRACKBACK_H__B28ECE7E_44BF_451F_AAE2_65521E70660D__INCLUDED_)
#define AFX_DLGTRACKBACK_H__B28ECE7E_44BF_451F_AAE2_65521E70660D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrackBack.h : header file
//
#include "TrackSearch.h"
#include "VDvsDevice.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgTrackBack dialog

class CDlgTrackBack : public CDialog
{
// Construction
public:
	CDlgTrackBack(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTrackBack)
	enum { IDD = IDD_DIALOG_TRACK_BACK };
	CListCtrl	m_lstTrackData;
	CComboBox	m_cmbDevIDNO;
	CComboBox	m_cmbTreakDis;
	CDateTimeCtrl	m_TimeCtrlEnd;
	CDateTimeCtrl	m_TimeCtrlBeg;
	COleDateTime	m_DataBeg;
	COleDateTime	m_TimeBeg;
	COleDateTime	m_TimeEnd;
	CString	m_strParkingTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrackBack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrackBack)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg LRESULT OnVehiTrackMsgCB(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSearchGPSData(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	void InitList();
	void InsertListData(GPSVehicleTrack_S* pVecicleTrack);
	CString FormatOtherInfo(CVehicleBase* pDev, const GPSVehicleGps_S& Gps);
	CString FormatTemperatureInfo(CVDvsDevice* pDevice, const GPSVehicleGps_S& Gps);
	int GetVehiRunImg(const GPSVehicleGps_S& Gps);
	void EnableCtrl(BOOL bEnable);

public:
	void	DoVehiTrackMsgCB(int nMsg, int nParam);
	void    DoVehiTrackDateCB(GPSVehicleTrack_S* pVehiRun);
	void    DoTrackCountCB(GPSTrackCount_S* pTrackCount);

private:
	CTrackSearch m_TrackSearch;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRACKBACK_H__B28ECE7E_44BF_451F_AAE2_65521E70660D__INCLUDED_)
