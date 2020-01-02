#if !defined(AFX_STPICTURE_H__875B9604_C379_4055_875C_87CF31539DF2__INCLUDED_)
#define AFX_STPICTURE_H__875B9604_C379_4055_875C_87CF31539DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StPicture.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStPicture window
class CStPicture : public CStatic
{
// Construction
public:
	CStPicture();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStPicture)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStPicture();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStPicture)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	
	BOOL	LoadPic(TCHAR* pBuf, int nSize, int nPicType);
	BOOL	LoadPic(const TCHAR* szFile);
	int		GetPicWidth();
	int		GetPicHeight();

	virtual void DrawOther( HDC hMemDC, CRect rcClient) {};

		  

private:
	CImgBase*	m_cxImage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STPICTURE_H__875B9604_C379_4055_875C_87CF31539DF2__INCLUDED_)
