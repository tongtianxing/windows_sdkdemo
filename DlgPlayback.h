#if !defined(AFX_DLGPLAYBACK_H__739587E9_5CFC_43DC_94D5_6A583D063C10__INCLUDED_)
#define AFX_DLGPLAYBACK_H__739587E9_5CFC_43DC_94D5_6A583D063C10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlayback.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayback dialog
#include "DlgRecPlayback.h"

class CDlgPlayback : public CDialog
{
// Construction
public:
	CDlgPlayback(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPlayback)
	enum { IDD = IDD_DIALOG_PLAYBACK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlayback)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlayback)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void MoveCtrl();


public:
	int Play(GPSFile_S* pFile, int nChannel);
	void Stop();

private:
	CDlgRecPlayback m_dlgRecPlayback;
	GPSFile_S m_File;
	int m_nChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAYBACK_H__739587E9_5CFC_43DC_94D5_6A583D063C10__INCLUDED_)
