#if !defined(AFX_DLGLOADING_H__D0FC07E3_60D4_4A7A_A891_A17FD0DB63F5__INCLUDED_)
#define AFX_DLGLOADING_H__D0FC07E3_60D4_4A7A_A891_A17FD0DB63F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DlgLoadingBase.h"

// CDlgLoading类移动到libcontrol工程中 [2016-9-12 ydl]

class CDlgLoading : public CDlgLoadingBase
{
// Construction
public:
	CDlgLoading(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLoading();

// Dialog Data
	//{{AFX_DATA(CDlgLoading)
	enum { IDD = IDD_DLG_LOADING };
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOADING_H__D0FC07E3_60D4_4A7A_A891_A17FD0DB63F5__INCLUDED_)
