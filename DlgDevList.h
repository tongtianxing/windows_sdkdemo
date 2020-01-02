#if !defined(AFX_DLGDEVLIST_H__4799DB36_3D2D_4CA9_BD09_8647B1F15EEC__INCLUDED_)
#define AFX_DLGDEVLIST_H__4799DB36_3D2D_4CA9_BD09_8647B1F15EEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDevList.h : header file
//
typedef std::list<int>			lstIntID;
typedef lstIntID::iterator		iterIntID;

/////////////////////////////////////////////////////////////////////////////
// CDlgDevList dialog

class CVMgrDevice;
class CDlgDevList : public CDialog
{
// Construction
public:
	CDlgDevList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDevList)
	enum { IDD = IDD_DLG_DEVLIST };
//	CComboBox	m_cmbDev;
	CTreeCtrl m_treeDevice;
// 	CCxTextButton m_btnOK;
// 	CCxTextButton m_btnCannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDevList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDevList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkTreeDev(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeDev(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void	SetMgrDevice(CVMgrDevice* pMgrDevice) {	m_pMgrDevice = pMgrDevice; }
	lstIntID&	GetDevList()	{	return m_lstIntID; }
	void	SetMultiSelect(BOOL bMulti) {	m_bMultiSelect = bMulti;	}
	void	SetShowChan(BOOL bShow) {	m_bShowChan = bShow;	}
	int		GetSelectDevice() {	return m_nSelectDevice; }
	int		GetSelectChannel() {	return m_nSelectChannel; }
	
protected:
	void	InitTree();
	void	GetDevIDList(lstIntID& lstID);
	void	LoadLanguage();
	void	GetChildIDList(HTREEITEM hItem, lstIntID& lstID);

private:
	CImageList	m_ImageList;
	CImageList	m_ImageStatus;
	CBitmap		m_TreeBmp;
	lstIntID	m_lstIntID;
	CVMgrDevice* m_pMgrDevice;
	BOOL		m_bMultiSelect;
	BOOL		m_bShowChan;
	int		m_nSelectDevice;
	int		m_nSelectChannel;
//	CImgBase*	m_pImgSearch;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVLIST_H__4799DB36_3D2D_4CA9_BD09_8647B1F15EEC__INCLUDED_)
