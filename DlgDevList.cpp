// DlgDevList.cpp : implementation file
//

#include "stdafx.h"
#include "DlgDevList.h"
#include "DevBase.h"
#include "VDvsDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDevList dialog


CDlgDevList::CDlgDevList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDevList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDevList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bMultiSelect = TRUE;
	m_bShowChan = TRUE;
	m_nSelectDevice = 0;
	m_nSelectChannel = CB_ERR;
}


void CDlgDevList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDevList)
	DDX_Control(pDX, IDC_TREE_ENC, m_treeDevice);
// 	DDX_Control(pDX, IDOK, m_btnOK);
// 	DDX_Control(pDX, IDCANCEL, m_btnCannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDevList, CDialog)
	//{{AFX_MSG_MAP(CDlgDevList)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_ENC, OnDblclkTreeDev)
	ON_NOTIFY(NM_CLICK, IDC_TREE_DEV, OnClickTreeDev)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDevList message handlers

BOOL CDlgDevList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	DWORD dwStyles = ::GetWindowLong(m_treeDevice.m_hWnd, GWL_STYLE);//获取树控制原风格 
	if (m_bMultiSelect)
	{
		dwStyles |= TVS_CHECKBOXES;
	}
	else
	{
		dwStyles &= ~TVS_CHECKBOXES; 
	}
	SetWindowLong(m_treeDevice.m_hWnd, GWL_STYLE, dwStyles);//设置风格
	InitTree();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDevList::OnOK() 
{
	// TODO: Add extra validation here
	if (m_bMultiSelect)
	{	
		GetDevIDList(m_lstIntID);
	}
	else
	{
		HTREEITEM hItem = m_treeDevice.GetSelectedItem();
		if (hItem)
		{
			CVehicleBase* pDevice = (CVehicleBase*)m_treeDevice.GetItemData(hItem);
			if (m_bShowChan)
			{
				m_nSelectDevice = NULL;
			}
			else
			{
				m_nSelectDevice = pDevice->GetID();
			}
		}
	}

	CDialog::OnOK();
}

void CDlgDevList::GetDevIDList(lstIntID& lstID)
{

	HTREEITEM hItemChild = m_treeDevice.GetRootItem();
	while (hItemChild)
	{
		
		if (m_treeDevice.GetCheck(hItemChild))
		{
			CVehicleBase* pDevice = (CVehicleBase*)m_treeDevice.GetItemData(hItemChild);
			lstID.push_back( pDevice->GetID());
		}
		hItemChild = m_treeDevice.GetNextSiblingItem(hItemChild);

	}
}

void CDlgDevList::GetChildIDList(HTREEITEM hItem, lstIntID& lstID)
{
	HTREEITEM hItemChild = m_treeDevice.GetChildItem(hItem);
	while (hItemChild)
	{
// 		if (CDevCtrlMgr::GetInstance()->IsDeviceItem(m_treeDevice, hItemChild))
// 		{
// 			if (m_treeDevice.GetMaskSelected(hItemChild))
// 			{
// 				CDevBase* pDevice = (CDevBase*)m_treeDevice.GetItemData(hItemChild);
// 				lstID.push_back( pDevice->GetID() );
// 			}
// 		}
// 		else
		{
			GetChildIDList(hItemChild, lstID);
		}
		hItemChild = m_treeDevice.GetNextSiblingItem(hItemChild);
	}
}

void CDlgDevList::OnDblclkTreeDev(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	*pResult = 0;
	if (!m_bMultiSelect)
	{
// 		HTREEITEM hItem = m_treeDevice.GetSelectedItem();
// 		if (CDevCtrlMgr::GetInstance()->IsDeviceItem(m_treeDevice, hItem)
// 			|| CDevCtrlMgr::GetInstance()->IsChannelItem(m_treeDevice, hItem))
		{
			OnOK();
		} 
	}
}

void CDlgDevList::LoadLanguage()
{
	SetWindowText(LOADSTRINGEX(ID_STR_SELECT_DEVICE));
	SetDlgItemText(IDOK, LOADSTRINGEX(ID_STR_OK));
	SetDlgItemText(IDCANCEL, LOADSTRINGEX(ID_STR_CANCEL));
}

void CDlgDevList::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(!m_bMultiSelect)
	{
//		CDevCtrlMgr::GetInstance()->DeleteCtrl(&m_treeDevice);
	}
		
	CDialog::OnCancel();
}

void CDlgDevList::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
//	CDevCtrlMgr::GetInstance()->DeleteCtrl(&m_treeDevice);
//	SAFE_DELETE_OBJECT(m_pImgSearch);
}


void CDlgDevList::OnClickTreeDev(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	CPoint pt;
	UINT nFlags;
	::GetCursorPos(&pt);
	::ScreenToClient(m_treeDevice.m_hWnd, &pt);
	HTREEITEM hItem = m_treeDevice.HitTest(pt,&nFlags);
	
// 	CString sMsg;
// 	sMsg.Format(_T("%s"), m_cTree.GetItemText(hItem));
// 	AfxMessageBox(sMsg);
	
	*pResult = 0;
}


void CDlgDevList::InitTree()
{
	mapVehicleBase mapDev;
	CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapDev);
	mapVehicleBaseIter iterB = mapDev.begin();
	mapVehicleBaseIter iterE = mapDev.end();	
	while (iterB != iterE)
	{
		CVehicleBase* pDevice = (*iterB).second;
		HTREEITEM hNew = NULL;
		hNew = m_treeDevice.InsertItem(pDevice->GetShowName(), hNew);
		m_treeDevice.SetItemData(hNew, (DWORD)pDevice);
		if (m_bShowChan)
		{
			for (int i = 0; i < pDevice->GetChannelNum(); ++ i)
			{
				HTREEITEM hTemp = NULL;
				hTemp = m_treeDevice.InsertItem(pDevice->GetChnName(i), hNew);
				if (m_bMultiSelect)
				{
					m_treeDevice.SetItemState(hTemp, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK );
				}
				m_treeDevice.SetItemData(hTemp, i);
			}
		}
		++ iterB;
	}
}